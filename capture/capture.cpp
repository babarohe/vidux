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

void do_nothing(int size, void*){}

/**
 * @fn
 * Ruddy filter
 * @param void
 * @return void
 */
void Capture::ruddyFilter()
{
    // Adjust value
    static double adjustHue = 7;
    static int _intAdjustHue = 0;
    static int adjustLightness = -20;
    static int adjustSaturation = 74;

    // Color range specification
    static double centerHue = 9.0;
    static double hueRange = 7.0;
    static int _intCenterHue = centerHue;
    static int _intHueRange = hueRange;

    static int minLightness = 42;
    static int maxLightness = 130;

    static int minSaturation = 117;
    static int maxSaturation = 255;
    static int showRangeFlag = 0;

    cv::createTrackbar("adjustHue", "ruddyFilter()", &_intAdjustHue, 255, do_nothing);
    // cv::createTrackbar("adjustLightness", "ruddyFilter()", &adjustLightness, 255, do_nothing);
    cv::createTrackbar("adjustSaturation", "ruddyFilter()", &adjustSaturation, 255, do_nothing);

    cv::createTrackbar("centerHue", "ruddyFilter()", &_intCenterHue, 360, do_nothing);
    cv::createTrackbar("hueRange", "ruddyFilter()", &_intHueRange, 360, do_nothing);
    cv::createTrackbar("minLightness", "ruddyFilter()", &minLightness, 255, do_nothing);
    cv::createTrackbar("maxLightness", "ruddyFilter()", &maxLightness, 255, do_nothing);
    cv::createTrackbar("minSaturation", "ruddyFilter()", &minSaturation, 255, do_nothing);
    cv::createTrackbar("maxSaturation", "ruddyFilter()", &maxSaturation, 255, do_nothing);

    cv::createTrackbar("showRangeFlag", "ruddyFilter()", &showRangeFlag, 1, do_nothing);


    adjustHue = _intAdjustHue;
    centerHue = _intCenterHue;
    hueRange = _intHueRange;

    specificHueFilter(centerHue,
        hueRange,
        minLightness,
        maxLightness,
        minSaturation,
        maxSaturation,
        adjustHue,
        adjustLightness,
        adjustSaturation,
        showRangeFlag);

}


/**
 * @fn
 * Tone up skin filter
 * @param void
 * @return void
 */
void Capture::toneUpSkinFilter()
{
    // Adjust value
    static double adjustHue = 0;
    static int _intAdjustHue = 0;
    static int adjustLightness = 6;
    static int adjustSaturation = 0;

    // Color range specification
    static double centerHue = 20.0;
    static double hueRange = 70.0;
    static int _intCenterHue = centerHue;
    static int _intHueRange = hueRange;

    static int minLightness = 50;
    static int maxLightness = 255;

    static int minSaturation = 38;
    static int maxSaturation = 255;
    static int showRangeFlag = 0;

    cv::createTrackbar("adjustHue", "toneUpSkinFilter()", &_intAdjustHue, 255, do_nothing);
    cv::createTrackbar("adjustLightness", "toneUpSkinFilter()", &adjustLightness, 255, do_nothing);
    cv::createTrackbar("adjustSaturation", "toneUpSkinFilter()", &adjustSaturation, 255, do_nothing);

    cv::createTrackbar("centerHue", "toneUpSkinFilter()", &_intCenterHue, 360, do_nothing);
    cv::createTrackbar("hueRange", "toneUpSkinFilter()", &_intHueRange, 360, do_nothing);
    cv::createTrackbar("minLightness", "toneUpSkinFilter()", &minLightness, 255, do_nothing);
    cv::createTrackbar("maxLightness", "toneUpSkinFilter()", &maxLightness, 255, do_nothing);
    cv::createTrackbar("minSaturation", "toneUpSkinFilter()", &minSaturation, 255, do_nothing);
    cv::createTrackbar("maxSaturation", "toneUpSkinFilter()", &maxSaturation, 255, do_nothing);

    cv::createTrackbar("showRangeFlag", "toneUpSkinFilter()", &showRangeFlag, 1, do_nothing);


    adjustHue = _intAdjustHue;
    centerHue = _intCenterHue;
    hueRange = _intHueRange;


    specificHueFilter(centerHue,
        hueRange,
        minLightness,
        maxLightness,
        minSaturation,
        maxSaturation,
        adjustHue,
        adjustLightness,
        adjustSaturation,
        showRangeFlag);

}

/**
 * @fn
 * Ruddy filter
 *
 * * Color range specification
 * @param double centerHue [0.0 ~ 360.0]
 * @param double hueRange [0.0 ~ 180.0]
 * @param int minLightness [0 ~ 255]
 * @param int maxLightness [0 ~ 255]
 * @param int minSaturation [0 ~ 255]
 * @param int maxSaturation [0 ~ 255]
 *
 * Adjust value
 * @param double adjustHue [-180.0 ~ 180.0]
 * @param int adjustLightness [-255 ~ 255]
 * @param int adjustSaturation [-255 ~ 255]
 *
 * @return void
 */
void Capture::specificHueFilter(
    double centerHue,
    double hueRange,
    int minLightness,
    int maxLightness,
    int minSaturation,
    int maxSaturation,
    double adjustHue,
    int adjustLightness,
    int adjustSaturation,
    bool showRangeFlag)
{
    // Convert color to HLS color
    cv::cvtColor(bufferMainFrame, bufferTemporaryFrame, cv::COLOR_BGR2HLS);

    int cols = bufferTemporaryFrame.cols;
    int rows = bufferTemporaryFrame.rows;

    int minHue = (int)((centerHue - hueRange / 2.0) / 2.0);
    int maxHue = (int)((centerHue + hueRange / 2.0) / 2.0);

    // Mat to vector
    std::vector<cv::Mat> hlsChannels;
    cv::split(bufferTemporaryFrame, hlsChannels);


    int hueValue;
    int lightnessValue;
    int saturationValue;

    for (int row = 0; row < rows; row++)
    {
        // Horizontal scan
        for (int col = 0; col < cols; col++)
        {
            // Vertical scan
            hueValue = static_cast<int>(hlsChannels[HLS_CHANNEL_HUE].at<uchar>(row, col));
            lightnessValue = static_cast<int>(hlsChannels[HLS_CHANNEL_LIGHTNESS].at<uchar>(row, col));
            saturationValue = static_cast<int>(hlsChannels[HLS_CHANNEL_SATURATION].at<uchar>(row, col));


            if (((minHue <= hueValue) && (hueValue <= maxHue)))
            {
                // Inrange hue
                if (((minLightness <= lightnessValue) && (lightnessValue <= maxLightness)))
                {
                    // Inrange Lightness
                    if (((minSaturation <= saturationValue) && (saturationValue <= maxSaturation)))
                    {
                        if (!showRangeFlag)
                        {
                            hlsChannels[HLS_CHANNEL_HUE].at<uchar>(row, col) = _utilCutRange(hueValue + (int)(adjustHue / 2.0) % HLS_HUE_MAX_VALUE , 0, HLS_HUE_MAX_VALUE);
                            hlsChannels[HLS_CHANNEL_LIGHTNESS].at<uchar>(row, col) = _utilCutRange(lightnessValue + adjustLightness, 0, HLS_LIGHTNESS_MAX_VALUE);
                            hlsChannels[HLS_CHANNEL_SATURATION].at<uchar>(row, col) = _utilCutRange(saturationValue + adjustSaturation, 0, HLS_SATURATION_MAX_VALUE);
                        }
                        else
                        {
                            hlsChannels[HLS_CHANNEL_HUE].at<uchar>(row, col) = _utilCutRange(45, 0, HLS_HUE_MAX_VALUE);
                            hlsChannels[HLS_CHANNEL_LIGHTNESS].at<uchar>(row, col) = _utilCutRange(127, 0, HLS_LIGHTNESS_MAX_VALUE);
                            hlsChannels[HLS_CHANNEL_SATURATION].at<uchar>(row, col) = _utilCutRange(255, 0, HLS_SATURATION_MAX_VALUE);

                        }
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
