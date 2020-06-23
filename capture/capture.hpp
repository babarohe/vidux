
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


#define HAACASCADE_EYE_PATH "./resource/haarcascades/haarcascade_eye.xml"
#define HAACASCADE_FACE_PATH "./resource/haarcascades/haarcascade_frontalface_alt.xml"

typedef struct
{
    // Hue
    double centerHue;
    double hueRange;

    // Lightness
    int minLightness;
    int maxLightness;

    // Saturation
    int minSaturation;
    int maxSaturation;

    // flag
    int showDetectionRangeFlag = 0;

} hlsColorDetection_t;

typedef struct
{
    double adjustHue;
    int adjustLightness;
    int adjustSaturation;

} hlsAdjustColor_t;

typedef struct
{
    int d;
    double sigmaColor;
    double sigmaSpace;
    int borderType;

} bilateralFilter_t;

class Capture
{
private:
    cv::VideoCapture *cap;
    cv::Mat inputFrame;
    cv::Mat grayscaleFrame;
    cv::Mat bufferMainFrame;
    cv::Mat bufferTemporaryFrame;
    cv::Mat outputFrame;

    cv::CascadeClassifier *cascadeEye;
    cv::CascadeClassifier *cascadeFace;


    int _utilCutRange(int, int, int);



public:
    // ruddyFilter() params
    hlsColorDetection_t ruddyFilterColorDetectionParams;
    hlsAdjustColor_t ruddyFilterAdjustColorParams;

    // toneUpSkinFilter() params
    hlsColorDetection_t toneUpSkinFilterColorDetectionParams;
    hlsAdjustColor_t toneUpSkinFilterAdjustColorParams;

    // beautifulSkinFilter() params
    bilateralFilter_t beautifulSkinFilterParams;

    // Basic functions
    bool initDevice(int);
    void closeDevice();
    void initFilters();

    void read();

    // filters
    void gammaFilter(double);
    void beautifulSkinFilter();
    void toneUpSkinFilter();
    void ruddyFilter();
    void colorHlsSpecificFilter(hlsColorDetection_t, hlsAdjustColor_t, bool = false);
    void noiseReductionFilter();


    // Tracking
    void faceTracking();


    // getter
    cv::Mat getFrame();
    cv::Mat getFrame(int);


};

#endif
