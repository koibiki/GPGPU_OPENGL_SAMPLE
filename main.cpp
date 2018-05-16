#include <iostream>
#include "utils/CTimer.h"
#include "utils/CSystem.h"

#define WIDTH 1024
#define HEIGHT 1024
#define CHANNEL 4
#define RADIUS 2

using namespace std;

int main() {
    std::cout << "Hello, World!" << std::endl;
    int nState = EXIT_SUCCESS;
    int unWidth = (int) WIDTH;
    int unHeight = (int) HEIGHT;
    int unChannel = (int) CHANNEL;
    int unRadius = (int) RADIUS;


    float ***fx;
    int unData = 0;

    CSystem cSystem;


    cSystem.allocate(unHeight, unWidth, unChannel, fx);
    for (int i = 0; i < unHeight; i++) {
        for (int j = 0; j < unWidth; j++) {
            for (int k = 0; k < unChannel; k++) {
                fx[k][j][i] = (float) unData;
                unData++;
            }
        }
    }

    float ***fy;
    cSystem.allocate(unHeight, unWidth, unChannel, fy);
    for (int i = 0; i < unHeight; i++) {
        for (int j = 0; j < unWidth; j++) {
            for (int k = 0; k < unChannel; k++) {
                fy[k][j][i] = 0.0f;
            }
        }
    }

    CTimer timer;
    timer.reset();

    float fSum = 0.0f;
    int unTotal = 0;


    for (int i = 0; i < unHeight; i++) {
        for (int j = 0; j < unWidth; j++) {
            for (int k = 0; k < unChannel; k++) {
                for (int ii = i - unRadius; ii <= i + unRadius; ii++) {
                    for (int jj = j - unRadius; jj <= j + unRadius; jj++) {
                        if (ii >= 0 && jj >= 0 && ii < unHeight && jj < unWidth) {
                            fSum += fx[k][jj][ii];
                            unTotal++;
                        }
                    }
                }
                fy[k][j][i] =fSum/(float) unTotal;
                unTotal = 0;
                fSum = 0.0f;
            }
        }
    }

    long lTime = timer.getTime();
    cout << "Time elapsed: " << lTime << " milliseconds." << endl;

    cSystem.deallocate(fx);
    cSystem.deallocate(fy);


    return nState;
}