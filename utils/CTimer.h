//
// Created by chengli on 18-5-16.
//

#ifndef GPGPU_CTIMER_H
#define GPGPU_CTIMER_H

#include <sys/time.h>
#include <stdlib.h>

class CTimer{
public:
    CTimer(){init();};

    /*
     * get elapsed time from last reset()
     * or class construction
     * @return the e;a[sed time.
     * */
    long getTime();

    /*
     * reset the timer
     * */
    void reset();

private:
    timeval _time;
    long _lStart;
    long _lStop;
    void init();
};


#endif //GPGPU_CTIMER_H
