/**
 *  Murmure - Net-SNMP MIB Versatile Extender
 *  Developed by Christian Visintin
 * 
 * 	Copyright (C) 2018 - 2019 Christian Visintin
 *
 *	This file is part of "Murmure"
 *
 *  Murmure is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *  Murmure is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
**/

#include <chrono>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <utils/logger.hpp>
#include <sstream>

using namespace logger;

/**
 * @function getLevelName
 * @description given integer log level, get the log level name
 * @param int level
 * @returns std::string: log level name
**/

std::string getLevelName(int level) {

  switch (level) {
    case LOG_DEBUG:
      return "DEBUG";
    case LOG_INFO:
      return "INFO";
    case LOG_FATAL:
      return "FATAL";
    case LOG_WARN:
      return "WARN";
    case LOG_ERROR:
      return "ERROR";
    default:
      return "UNKNOWN";
  }

}

/**
 * @function log
 * @description write log message to file
 * @param std::string component
 * @param int log level
 * @param std::string logContent
**/

void log(std::string component, int level, std::string logContent) {

  //Check if this message has to be logged
  if (level > logLevel) {
    return;
  }

  std::stringstream logstream;
  std::ofstream logFileStream;

  //Prepare data to write
  auto now = std::chrono::system_clock::now();
  auto in_time_t = std::chrono::system_clock::to_time_t(now);

  logstream << std::put_time(std::localtime(&in_time_t), "%Y/%m/%d-%H:%M:%S [") << getLevelName(level) << "]" << component << ": " << logContent << "\n";
  std::string logStr = logstream.str();

  logFileStream.open(logfile, std::ofstream::out | std::ofstream::app);
  if (logFileStream.is_open()) {
    logFileStream << logStr;
    logFileStream.close();
  }
  if (logger::stdout) {
    std::cout << logStr;
  }
  return;
}