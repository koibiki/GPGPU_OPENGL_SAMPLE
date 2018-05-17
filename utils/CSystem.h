//
// Created by chengli on 18-5-16.
//

#ifndef GPGPU_CSYSTEM_H
#define GPGPU_CSYSTEM_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

class CSystem {
public:

    CSystem() {};

    void allocate(unsigned int unRows, unsigned int unCols, float **&aatArray);

    void deallocate(float **&aatArray);

    void allocate(int unRows, int unCols, int unSlices, float ***&aaatArray);

    void deallocate(float ***&aaatArray);

};

#endif //GPGPU_CSYSTEM_H
