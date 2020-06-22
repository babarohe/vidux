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
    cap = new cv::VideoCapture(index);
    // cap->set(cv::CAP_PROP_FOURCC,  cv::CV_FOURCC('H', '2', '6', '4'));
    // cap->set(cv::CAP_PROP_FPS, CAPTURE_FRAME_RATE_JPN_EAST);
    // cap->set(cv::CAP_PROP_FRAME_WIDTH, 1280);
    // cap->set(cv::CAP_PROP_FRAME_HEIGHT, 720);

    return !cap->isOpened();
}

void Capture::gammaFilter(double gamma)
{
    uchar lut[256];

    for (int i = 0; i < 256; i++)
    {
        lut[i] = (int)(pow((double)i / 255.0, 1.0 / gamma) * 255.0);
    }

    // Convart lockup table
    cv::LUT(frame, cv::Mat(1, 256, CV_8UC1, lut), frame);

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
    cv::bilateralFilter(frame, frameTmp, 4, 70, 6, 4);
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
    cap->read(frameRaw);
    frameRaw.copyTo(frame);
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


/**
 * @fn
 * Get a frame
 * @param void
 * @return cv::Mat
 */
cv::Mat Capture::getFrame(int frameId)
{
    if (frameId == FRAME_ID_PROCESSED)
    {
        return frame;
    }
    else if (frameId == FRAME_ID_RAW_INPUT)
    {
        return frameRaw;
    }
}
