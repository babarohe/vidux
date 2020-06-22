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


void Capture::closeDevice()
{
    cap->release();
    delete(cap);
}


/**
 * @fn
 * Read capture device
 * @param void
 * @return void
 */
void Capture::read()
{
    // Read frame from capture
    cap->read(inputFrame);
    inputFrame.copyTo(bufferMainFrame);
}

/**
 * @fn
 * Beautiful skin filter
 * @param void
 * @return void
 */
void Capture::beautifulSkinFilter()
{
    // Execute bilateral filter
    cv::bilateralFilter(bufferMainFrame, bufferTemporaryFrame, 4, 72, 6, 4);

    // Copy from Temporary buffer
    bufferTemporaryFrame.copyTo(bufferMainFrame);

    // cv::cvtColor(bufferTemporaryFrame, bufferMainFrame, cv::COLOR_RGB2RGBA);

}


/**
 * @fn
 * Noise reduction filter
 * @param void
 * @return void
 */
void Capture::noiseReductionFilter()
{
    cv::medianBlur(bufferMainFrame, bufferMainFrame, 3);
}


/**
 * @fn
 * Gamma filter
 * @param void
 * @return void
 */
void Capture::gammaFilter(double gamma)
{
    uchar lut[256];

    for (int i = 0; i < 256; i++)
    {
        lut[i] = (int)(pow((double)i / 255.0, 1.0 / gamma) * 255.0);
    }

    // Convart lockup table
    cv::LUT(bufferMainFrame, cv::Mat(1, 256, CV_8UC1, lut), bufferMainFrame);

}

/**
 * @fn
 * Get a frame
 * @param void
 * @return cv::Mat
 */
cv::Mat Capture::getFrame()
{
    return bufferTemporaryFrame;
}


/**
 * @fn
 * Get a frame
 * @param void
 * @return cv::Mat
 */
cv::Mat Capture::getFrame(int frameId)
{
    if (frameId == FRAME_ID_INPUT)
    {
        return inputFrame;
    }
    else if (frameId == FRAME_ID_BUFFER_MAIN)
    {
        return bufferMainFrame;
    }
    else if (frameId == FRAME_ID_BUFFER_TEMPORARY)
    {
        return bufferTemporaryFrame;
    }
    else if (frameId == FRAME_ID_OUTPUT)
    {
        return bufferTemporaryFrame;
    }
}
