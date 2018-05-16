//
// Created by chengli on 18-5-16.
//

#ifndef GPGPU_CREADER_H
#define GPGPU_CREADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

class CReader{
public:
    CReader(){init();}

    char * textFileRead(char  * chFileName);

private:
    void init(void);
    FILE *_fp;
    char  * _content;
    int _count;
};

#endif //GPGPU_CREADER_H
