
#ifndef   CAPTURE_HPP
#define   CAPTURE_HPP

#include "opencv2/opencv.hpp"

#define CAPTURE_FRAME_RATE_JPN_EAST 50
#define CAPTURE_FRAME_RATE_JPN_WEST 60

#define FRAME_ID_INPUT 0
#define FRAME_ID_BUFFER_MAIN 1
#define FRAME_ID_BUFFER_TEMPORARY 2
#define FRAME_ID_OUTPUT 3

class Capture
{
private:
    cv::VideoCapture *cap;
    cv::Mat inputFrame;
    cv::Mat bufferMainFrame;
    cv::Mat bufferTemporaryFrame;
    cv::Mat outputFrame;

public:
    // Basic functions
    bool initDevice(int);
    void closeDevice();

    void read();

    // filters
    void beautifulSkinFilter();
    void gammaFilter(double);
    void noiseReductionFilter();

    // getter
    cv::Mat getFrame();
    cv::Mat getFrame(int);


};

#endif
