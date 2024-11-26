#include "global.h"
#include <string>

std::string stringifyTime(int time) {
    int minutes = time / 60;
    int seconds = time % 60;
    if (seconds < 10) {
        return std::to_string(minutes)+":0"+std::to_string(seconds);
    } else {
        return std::to_string(minutes)+":"+std::to_string(seconds);
    }
}