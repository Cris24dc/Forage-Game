#include "logger.hpp"

void logMessage(LogLevel level, const std::string msg) {
    switch(level) {
        case LogLevel::INFO:
            std::cout << "[INFO] " << msg << std::endl;
            break;
        case LogLevel::WARN:
            std::cout << "[WARN] " << msg << std::endl;
            break;
        case LogLevel::ERROR:
            std::cout << "[ERROR] " << msg << " | SDL Error: " << SDL_GetError() << std::endl;
            break;
    }
}
