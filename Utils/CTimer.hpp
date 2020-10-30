#pragma once

#include <iostream>
#include <sys/time.h>

#define DEBUG

class CTimer
{
public:
    /***
     * @brief Timer start record
    */
    inline void start() { gettimeofday(&startTime, NULL); }

    /***
     * @brief Timer stop record
     * @return: type long, Unit Microseconds
    */
    inline long end(std::string str = "timer") {
        gettimeofday(&endTime, NULL);
        long elapsedTime = (endTime.tv_sec - startTime.tv_sec) * 1000 * 1000 +
                           (endTime.tv_usec - startTime.tv_usec);
#ifdef DEBUG
        std::cout << str << ":" << elapsedTime / 1000 << "ms" << std::endl;
#endif
        return elapsedTime;
    }

private:
    struct timeval startTime, endTime;
};