#pragma once
// versie zonder std::array

// NB: dit is een "hack-debug-logger"
// Om het volgens het boekje te doen, zou een channel gebruikt moeten worden.

class Logger : public rtos::task<> {
private:
    static const int LogSize = 200;           // Passing size by template parameter would be nicer..
    // Don't select the LogSize too high, or you may suffer from stack overflow troubles.
    hwlib::target::pin_in &buttonDump;       // A press on this button (active low) activates the dump.

    const char* arTextLogs [LogSize] = { };  // Circular buffer.
    int32_t arIntLogs [LogSize] = { };

    unsigned long logCount = 0;              // Absolute count of logs
    unsigned long latestBatchCount = 0;      // Count of logs since last dump.
    unsigned int index = 0;                  // Index to write next log to.
    const int minInt = -(1 << 30); // of zo..
private:
    void main() {
        unsigned int j = 0;            // lokale enumeratievariabele
        bool prevPress = true;
        while (true) {
            bool buttonReadDump = !buttonDump.read();

            if (buttonReadDump && !prevPress) {
                int nFirstLogSequenceNumber = (logCount - latestBatchCount);
                hwlib::cout << "-------------------------------------" << hwlib::endl;
                hwlib::cout << "--------------Log Dump---------------" << hwlib::endl;
                hwlib::cout << "sequenceNumber of first log: " << nFirstLogSequenceNumber << hwlib::endl;
                hwlib::cout << "-------------------------------------" << hwlib::endl;
                // for (auto &log : logs)
                j = index; // start at oldest entry of the circular buffers.
                for (unsigned int i = 0; i < LogSize; i++) {
                    //hwlib::cout << j;
                    if (arTextLogs[j] != nullptr) {
                        hwlib::cout << arTextLogs[j] << hwlib::endl;
                    } else if (arIntLogs[j] != minInt) {
                        hwlib::cout << arIntLogs[j] << hwlib::endl;
                    }

                    j += 1;
                    if (j > (LogSize - 1)) {
                        j = 0;
                    }
                }

                ClearTextLogs();
                ClearIntLogs();
                latestBatchCount = 0;

//                rtos::display_statistics();
//                rtos::statistics_clear();

                hwlib::wait_ms(100);
            }
            prevPress = buttonReadDump;
            hwlib::wait_ms(100);
        }
    }

public:
    Logger(unsigned int priority, hwlib::target::pin_in &buttonDump)
            : rtos::task<>(priority, "Logger"), buttonDump(buttonDump) {
        ClearTextLogs();
        ClearIntLogs();
    }

    void logText(const char *text) {
        if(latestBatchCount>=LogSize) return;
        arTextLogs[index] = text;
        arIntLogs[index] = minInt;

        IncreaseCount();
    }

    void logInt(int32_t intNumber) {
        if(latestBatchCount>=LogSize) return;
        arTextLogs[index] = nullptr;
        arIntLogs[index] = intNumber;

        IncreaseCount();
    }

private:
    void IncreaseCount() {
        logCount++;
        latestBatchCount++;
        index++;

        if (latestBatchCount > LogSize) {
            latestBatchCount = LogSize; // LogSize is the deepest possible history.
        }

        if (index > (LogSize - 1)) {
            index = 0;
        }
    }

    void ClearTextLogs()
    {
        int i=0;
        for(i=0;i<LogSize;i++)
        {
            arTextLogs[i] = nullptr;
        }
    }

    void ClearIntLogs() {
        int i = 0;
        for (i = 0; i < LogSize; i++) {
            arIntLogs[i] = minInt;
        }
    }
};