#include "pause_control.h"

Pause_control::Pause_control(Decode_control & d_control, Logger & log):
    task(2, "pause_control"),
    pauseChannel (this, "pauseChannel"),
    d_control (d_control),
    logger(log)
{}

void Pause_control::pause_detected(int length) {
    pauseChannel.write(length);
}

void Pause_control::main() {
    uint16_t msg;
    int counter;
    uint16_t checksum_mask;
    uint16_t checksum_received;
    uint16_t checksum_generated;

    int length;
    bool discard = 0;
    bool first_msg;

    while (true) {
        switch (state) {
            case IDLE:
//                logger.logText("STATE: IDLE");
                wait(pauseChannel);
                length = pauseChannel.read();
                if (4000 < length && length < 5200) {
//                    logger.logText("4000-5200");
                    msg = 0x00;
                    counter = 0;
                    first_msg = 1;
                    state = MESSAGE;

                }
                else if (3000 < length && length < 4000) {
//                    logger.logText("3000-4000");
                    msg = 0x01;
                    counter = 0;
                    first_msg = 0;
                    if (discard) {
//                        logger.logText("discard");
                        discard = 0;
                        state = IDLE;
                    }
                    else {
                        state = MESSAGE;
                    }
                }
                else {
                    state = IDLE;
                }
                break;

            case MESSAGE:
//                logger.logText("STATE: MSG");
                wait(pauseChannel);
                length = pauseChannel.read();
                if(length > 200 && length < 2000){
//                    logger.logText("valid_pause");
                    msg <<= 1;
                    msg |= (length > 1000) ? 0 : 1;
                    counter ++;
//                    logger.logText("msg_value:");
//                    logger.logInt(msg);
                    if(counter < 16){
//                        logger.logText("counter < 16");
                        state = MESSAGE;
                    }
                    else{
                        checksum_mask = 0x1F;
                        checksum_received = msg & checksum_mask;
                        checksum_generated = generate_checksum(msg);
                        if(first_msg){
//                            logger.logText("first_msg");
                            if(checksum_received == checksum_generated){
//                                logger.logText("checksum = good");
                                d_control.decode_msg(msg);
                                discard = 1;
                                state = IDLE;
                            }
                            else{
                                state = IDLE;
                            }

                        }
                        else{
//                            logger.logText("second_msg");
                            if(checksum_received == checksum_generated){
//                                logger.logText("checksum = good");
                                d_control.decode_msg(msg);
                                state = IDLE;
                            }
                            else{
                                state = IDLE;
                            }
                        }
                    }
                }
                else{
                    state = IDLE;
                }
                break;

        }
    }
}