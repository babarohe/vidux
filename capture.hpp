
#ifndef   CAPTURE_HPP
#define   CAPTURE_HPP

#include "opencv2/opencv.hpp"

#define CAPTURE_FRAME_RATE_JPN_EAST 50
#define CAPTURE_FRAME_RATE_JPN_WEST 60

#define FRAME_ID_INPUT 0
#define FRAME_ID_BUFFER_MAIN 1
#define FRAME_ID_BUFFER_TEMPORARY 2
#define FRAME_ID_OUTPUT 3

#define HLS_CHANNEL_HUE 0
#define HLS_CHANNEL_LIGHTNESS 1
#define HLS_CHANNEL_SATURATION 2

#define HLS_HUE_MAX_VALUE 180
#define HLS_LIGHTNESS_MAX_VALUE 255
#define HLS_SATURATION_MAX_VALUE 255


class Capture
{
private:
    cv::VideoCapture *cap;
    cv::Mat inputFrame;
    cv::Mat bufferMainFrame;
    cv::Mat bufferTemporaryFrame;
    cv::Mat outputFrame;
    int _utilCutRange(int, int, int);

public:
    // Basic functions
    bool initDevice(int);
    void closeDevice();

    void read();

    // filters
    void gammaFilter(double);
    void beautifulSkinFilter();
    void toneUpSkinFilter();
    void ruddyFilter();
    void specificHueFilter(double, double, int, int, int, int, double, int, int, bool = false);
    void noiseReductionFilter();

    // getter
    cv::Mat getFrame();
    cv::Mat getFrame(int);


};

#endif
