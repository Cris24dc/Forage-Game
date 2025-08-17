#ifndef LOGGER_HPP
#define LOGGER_HPP

#include <SDL2/SDL.h>
#include <iostream>
#include <string>

enum class LogLevel { INFO, WARN, ERROR };

void logMessage(LogLevel level, const std::string msg);

#endif