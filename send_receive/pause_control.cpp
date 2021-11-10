#include "pause_control.h"

Pause_control::Pause_control(Decode_control & d_control):
    task(2, "pause_control"),
    pauseChannel (this, "pauseChannel"),
    d_control (d_control)
{}

void Pause_control::pause_detected(int length) {
    pauseChannel.write(length);
}

void Pause_control::main() {
    uint16_t msg;
    int counter;
    uint16_t checksum_mask;
    uint16_t checksum_recieved;
    uint16_t checksum_generated;

    int length;
    bool discard = 0;
    bool first_msg;

    while (true) {
        switch (state) {
            case IDLE:
                wait(pauseChannel);
                length = pauseChannel.read();
                hwlib::cout << length << hwlib::endl;
                if (4000 < length && length < 5000) {
                    msg = 0x01;
                    counter = 0;
                    first_msg = 1;
                    state = MESSAGE;

                    hwlib::cout << "first msg" << hwlib::endl;
                } else if (3000 < length && length < 4000) {
                        msg = 0x01;
                        counter = 0;
                        first_msg = 0;
                    if (discard) {
                        discard = 0;
                        state = IDLE;
                        break;

                    } else {
                        state = MESSAGE;
                        hwlib::cout << "discard" << hwlib::endl;
                    }
                } else {
                    state = IDLE;
                }
                break;

            case MESSAGE:
                if (counter < 15) {
                    wait(pauseChannel);
                    length = pauseChannel.read();
                    if (length > 200 && length < 2000) {
                        msg <<= 1;
                        msg |= (length > 1000) ? 1 : 0;
                        counter++;
                    } else {
                        state = IDLE;
                        break;
                    }
                } else {
                    checksum_mask = 0x1F;
                    checksum_recieved = msg & checksum_mask;
                    checksum_generated = generate_checksum(msg);
                    if (first_msg) {
                        if (checksum_recieved == checksum_generated) {
                            d_control.decode_msg(msg);
                            discard = 1;
                            state = IDLE;
                        } else {
                            state = IDLE;
                        }
                    } else {
                        if (checksum_recieved == checksum_generated) {
                            d_control.decode_msg(msg);
                            state = IDLE;
                        } else {
                            state = IDLE;
                        }
                    }
                    break;
                }
        }
    }
}
