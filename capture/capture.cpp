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
 * Initialize filters
 * @return void
 */

void Capture::initFilters()
{
    // ----------------------------------------------------------------
    // ruddyFilter()
    // ----------------------------------------------------------------
    // Color detection
    ruddyFilterColorDetectionParams.centerHue = 9.0;
    ruddyFilterColorDetectionParams.hueRange = 7.0;
    ruddyFilterColorDetectionParams.minLightness = 42;
    ruddyFilterColorDetectionParams.maxLightness = 130;
    ruddyFilterColorDetectionParams.minSaturation = 117;
    ruddyFilterColorDetectionParams.maxSaturation = 255;
    ruddyFilterColorDetectionParams.showDetectionRangeFlag = 0;

    // Adjust value
    ruddyFilterAdjustColorParams.adjustHue = 7;
    ruddyFilterAdjustColorParams.adjustLightness = -20;
    ruddyFilterAdjustColorParams.adjustSaturation = 74;


    // ----------------------------------------------------------------
    // toneUpSkinFilter()
    // ----------------------------------------------------------------
    // Color detection
    toneUpSkinFilterColorDetectionParams.centerHue = 20.0;
    toneUpSkinFilterColorDetectionParams.hueRange = 70.0;
    toneUpSkinFilterColorDetectionParams.minLightness = 50;
    toneUpSkinFilterColorDetectionParams.maxLightness = 255;
    toneUpSkinFilterColorDetectionParams.minSaturation = 38;
    toneUpSkinFilterColorDetectionParams.maxSaturation = 255;
    toneUpSkinFilterColorDetectionParams.showDetectionRangeFlag = 1;

    // Adjust value
    toneUpSkinFilterAdjustColorParams.adjustHue = 0;
    toneUpSkinFilterAdjustColorParams.adjustLightness = 6;
    toneUpSkinFilterAdjustColorParams.adjustSaturation = 0;


    // ----------------------------------------------------------------
    // beautifulSkinFilter()
    // ----------------------------------------------------------------
    beautifulSkinFilterParams.d = 4;
    beautifulSkinFilterParams.sigmaColor = 72.0;
    beautifulSkinFilterParams.sigmaSpace = 6.0;
    beautifulSkinFilterParams.borderType = 4;


    return;
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
    cv::bilateralFilter(bufferTemporaryFrame, bufferMainFrame, beautifulSkinFilterParams.d, beautifulSkinFilterParams.sigmaColor, beautifulSkinFilterParams.sigmaSpace, beautifulSkinFilterParams.borderType);

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
    colorHlsSpecificFilter(ruddyFilterColorDetectionParams, ruddyFilterAdjustColorParams, ruddyFilterColorDetectionParams.showDetectionRangeFlag);

}


/**
 * @fn
 * Tone up skin filter
 * @param void
 * @return void
 */
void Capture::toneUpSkinFilter()
{
    colorHlsSpecificFilter(toneUpSkinFilterColorDetectionParams, toneUpSkinFilterAdjustColorParams, toneUpSkinFilterColorDetectionParams.showDetectionRangeFlag);

}

/**
 * @fn
 * Color hls filter
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
void Capture::colorHlsSpecificFilter(hlsColorDetection_t hlsColorDetection, hlsAdjustColor_t hlsAdjustColor, bool showDetectionRangeFlag)
{
    double centerHue        = hlsColorDetection.centerHue;
    double hueRange         = hlsColorDetection.hueRange;
    int minLightness        = hlsColorDetection.minLightness;
    int maxLightness        = hlsColorDetection.maxLightness;
    int minSaturation       = hlsColorDetection.minSaturation;
    int maxSaturation       = hlsColorDetection.maxSaturation;

    double adjustHue        = hlsAdjustColor.adjustHue;
    int adjustLightness     = hlsAdjustColor.adjustLightness;
    int adjustSaturation    = hlsAdjustColor.adjustSaturation;



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
                        if (!showDetectionRangeFlag)
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
    return cv::Mat();
}


int Capture::_utilCutRange(int value, int min, int max)
{
    // Upper
    value = std::max(min, value);

    // Lower
    value = std::min(max, value);

    return value;
}
