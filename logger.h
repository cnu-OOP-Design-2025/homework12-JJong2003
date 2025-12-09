
#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>
#include <string>

class Logger {
private:
    static std::unique_ptr<Logger> instance;
    static std::mutex init_mtx;
    static std::mutex write_mtx;
    std::ofstream logFile;

    Logger() {
        Logger::logFile.open("Test/output2.txt", std::ios::trunc);
        if (Logger::logFile.is_open()) {
            Logger::logFile << "[Init] Logger started." << std::endl;
        } else {
            throw std::runtime_error("Failed to open log file");
        }
    }

public:
    ~Logger() {
        if (Logger::logFile.is_open()) {
            Logger::logFile << "[Shutdown] Logger closed." << std::endl;
            Logger::logFile.close();
        }
    }

    static Logger* getInstance(const std::string& filename = "Test/output2.txt") {
        std::lock_guard<std::mutex> lock(init_mtx);
        if (!Logger::instance) {
            Logger::instance.reset(new Logger());
        }
        return instance.get();
    }

    void log(const std::string& message) {
        /* TODO */
        std::lock_guard<std::mutex> lock(write_mtx);
        Logger::logFile << message << std::endl;
    }

    

};

std::unique_ptr<Logger> Logger::instance;
std::mutex Logger::init_mtx;
std::mutex Logger::write_mtx;
