//
// Created by chengli on 18-5-16.
//
#include "utils/CTimer.h"

void CTimer::init() {
    _lStart = 0;
    _lStop = 0;
    gettimeofday(&_time, NULL);
    _lStart = (_time.tv_sec * 1000) + (_time.tv_usec / 1000);
}

long CTimer::getTime() {
    gettimeofday(&_time, NULL);
    _lStop = (_time.tv_sec * 1000) + (_time.tv_usec / 1000) - _lStart;
    return _lStop;
}


void CTimer::reset(void) {
    init();
}