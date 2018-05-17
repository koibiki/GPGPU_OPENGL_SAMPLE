//
// Created by chengli on 18-5-16.
//

#include "utils/CSystem.h"

void CSystem::allocate(unsigned int unRows, unsigned int unCols, float ** & aatArray) {
    aatArray = new float *[unRows];
    aatArray[0] = new float[unRows * unCols];
    for (unsigned int unRow = 1; unRow < unRows; unRow++) {
        aatArray[unRow] = &aatArray[0][unCols * unRow];
    }
}

void CSystem::deallocate(float ** & aatArray) {
    delete[] aatArray[0];
    delete[] aatArray;
    aatArray = 0;
}


void CSystem::allocate(int unRows, int unCols, int unSlices, float *** & aaatArray) {
    aaatArray = new float **[unSlices];
    aaatArray[0] = new float *[unSlices * unCols];
    aaatArray[0][0] = new float[unSlices * unRows * unCols];
    for (unsigned int unSlice = 0; unSlice < unSlices; unSlice++) {
        aaatArray[unSlice] = &aaatArray[0][unRows * unSlice];
        for (unsigned int unRow = 0; unRow < unRows; unRow++) {
            aaatArray[unSlice][unRow] = &aaatArray[0][0][unCols * (unRow + unRows * unSlice)];
        }
    }
}


void CSystem::deallocate(float *** & aaatArray) {
    delete[] aaatArray[0][0];
    delete[] aaatArray[0];
    delete[] aaatArray;
    aaatArray = 0;
}