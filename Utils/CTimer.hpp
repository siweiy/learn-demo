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

class Timer
{
public:
    /***
     * @brief Timer start record
    */
    inline void start() { _start = clock(); }

    /***
     * @brief Timer stop record
     * @return: type long, Unit Microseconds
    */
    inline long end(std::string str = "timer") {
        _end = clock();
        double elapsedTime = ((double)(_end - _start)/CLOCKS_PER_SEC);

#ifdef DEBUG
        std::cout << str << ":" << elapsedTime << "ms" << std::endl;
#endif
        return elapsedTime;
    }

private:
    clock_t _start, _end;
};
