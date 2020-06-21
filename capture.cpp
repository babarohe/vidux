#include "capture.hpp"
#include <iostream>


/**
 * @fn
 * Initialize capture device
 * @param int index
 * @return success: false, failed: true
 */

bool Capture::initDevice(int index)
{
    std::cout << "Open Device" << std::endl;
    cap = new cv::VideoCapture(0);
    // cap->set(cv::CAP_PROP_FPS, CAPTURE_FRAME_RATE_JPN_EAST);
    // cap->set(cv::CAP_PROP_FRAME_WIDTH, 1280);
    // cap->set(cv::CAP_PROP_FRAME_HEIGHT, 720);

    return !cap->isOpened();
}


void Capture::closeDevice()
{
    cap->release();
    delete(cap);
}

/**
 * @fn
 * Beautiful skin filter
 * @param void
 * @return void
 */
void Capture::beautifulSkinFilter()
{
    // 美肌フィルタ
    cv::bilateralFilter(frame, frameTmp, 5, 74, 12, 4);
    cv::cvtColor(frameTmp, frame, cv::COLOR_RGB2RGBA);
}


/**
 * @fn
 * Beautiful skin filter
 * @param void
 * @return void
 */
void Capture::noiseReduction()
{
    // 美肌フィルタ
    cv::medianBlur(frame, frame, 3);
}


/**
 * @fn
 * Read capture device
 * @param void
 * @return void
 */
void Capture::read()
{
    cap->read(frame);
}


/**
 * @fn
 * Get a frame
 * @param void
 * @return cv::Mat
 */
cv::Mat Capture::getFrame()
{
    return frame;
}
