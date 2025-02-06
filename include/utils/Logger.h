//
// Created by Yeo Shu Heng on 6/2/25.
//

#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <iostream>

class Logger {
  private:
    static LogLevel c_level;
  public:
    enum LogLevel { DEBUG, INFO, WARNING, ERROR };

    static void initialize(LogLevel level) {
      c_level = level;
    };

    static void log(LogLevel level, std::string s) {
       if (level >= c_level) {
         std::cout << s << std::endl;
       }
    };
}

#endif //LOGGER_H
