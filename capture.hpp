
#ifndef   CAPTURE_HPP
#define   CAPTURE_HPP

#include "opencv2/opencv.hpp"

#define CAPTURE_FRAME_RATE_JPN_EAST 50
#define CAPTURE_FRAME_RATE_JPN_WEST 60


class Capture
{
private:
    cv::VideoCapture *cap;
    cv::Mat frame;
    cv::Mat frameTmp;

public:
    // Basic functions
    bool initDevice(int);
    void closeDevice();

    void read();

    // filters
    void beautifulSkinFilter();
    void noiseReduction();

    // getter
    cv::Mat getFrame();


};

#endif
