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
    // Copy to Temporary buffer
    bufferMainFrame.copyTo(bufferTemporaryFrame);

    // Execute bilateral filter
    cv::bilateralFilter(bufferTemporaryFrame, bufferMainFrame, 4, 72, 6, 4);

}

/**
 * @fn
 * Ruddy filter
 * @param void
 * @return void
 */
void Capture::ruddyFilter()
{
    // 血色感出すフィルター
    specificHueFilter();

}


void Capture::specificHueFilter()
{
    // Convert color to HLS color
    cv::cvtColor(bufferMainFrame, bufferTemporaryFrame, cv::COLOR_BGR2HLS);

    int cols = bufferTemporaryFrame.cols;
    int rows = bufferTemporaryFrame.rows;

    int adjustHue = 0;
    int adjustLightness = -30;
    int adjustSaturation = 0;

    double centerHue = 7.0;
    double hueRange = 12.0;

    double minHue = centerHue - hueRange / 2.0;
    double maxHue = centerHue + hueRange / 2.0;

    int minLightness = 20;
    int maxLightness = 255;

    int minSaturation = 0;
    int maxSaturation = 200;


    // Mat to vector
    std::vector<cv::Mat> hlsChannels;
    cv::split(bufferTemporaryFrame, hlsChannels);


    int hueValue;
    int lightnessValue;
    int saturationValue;

    for (int row = 0; row < rows; row++) {
        // Horizontal scan
        for (int col = 0; col < cols; col++) {
            // Vertical scan
            hueValue = static_cast<int>(hlsChannels[HLS_CHANNEL_HUE].at<uchar>(row, col));
            lightnessValue = static_cast<int>(hlsChannels[HLS_CHANNEL_LIGHTNESS].at<uchar>(row, col));
            saturationValue = static_cast<int>(hlsChannels[HLS_CHANNEL_SATURATION].at<uchar>(row, col));


            if (((minHue <= hueValue) && (hueValue <= maxHue))) {
                // Inrange hue
                if (((minLightness <= lightnessValue) && (lightnessValue <= maxLightness))) {
                    // Inrange Lightness
                    if (((minSaturation <= saturationValue) && (saturationValue <= maxSaturation))) {
                        // hlsChannels[HLS_CHANNEL_HUE].at<uchar>(row, col) = _utilCutRange(hueValue + adjustHue, 0, HLS_HUE_MAX_VALUE);
                        // hlsChannels[HLS_CHANNEL_LIGHTNESS].at<uchar>(row, col) = _utilCutRange(lightnessValue + adjustLightness, 0, HLS_LIGHTNESS_MAX_VALUE);
                        // hlsChannels[HLS_CHANNEL_SATURATION].at<uchar>(row, col) = _utilCutRange(saturationValue + adjustSaturation, 0, HLS_SATURATION_MAX_VALUE);

                        hlsChannels[HLS_CHANNEL_HUE].at<uchar>(row, col) = _utilCutRange(45, 0, HLS_HUE_MAX_VALUE);
                        hlsChannels[HLS_CHANNEL_LIGHTNESS].at<uchar>(row, col) = _utilCutRange(127, 0, HLS_LIGHTNESS_MAX_VALUE);
                        hlsChannels[HLS_CHANNEL_SATURATION].at<uchar>(row, col) = _utilCutRange(255, 0, HLS_SATURATION_MAX_VALUE);
                    }
                }
            }
        }
    }

    // Writeback to bufferTemporary
    cv::merge(hlsChannels, bufferTemporaryFrame);

    // Convert color and write back
    cv::cvtColor(bufferTemporaryFrame, bufferMainFrame, cv::COLOR_HLS2BGR);

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
    return bufferMainFrame;
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
        return bufferMainFrame;
    }
}


int Capture::_utilCutRange(int value, int min, int max)
{
    // Upper
    value = std::max(min, value);

    // Lower
    value = std::min(max, value);

    return value;
}
