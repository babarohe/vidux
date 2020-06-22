
#include "vidux-selector-main.hpp"


/**
 * VIDUX SELECTOR
*/

int main(int argc, char *argv[])
{
    cv::VideoCapture caps[MAX_SCAN_DEVICE];

    bool isOpeneds[MAX_SCAN_DEVICE];

    std::string windowNames[MAX_SCAN_DEVICE];
    int deviceCounter = 0;

    for (int i = 0; i < MAX_SCAN_DEVICE; i++)
    {
        // デバイス初期化
        caps[i] = cv::VideoCapture(i);

        // Openできたか
        isOpeneds[i] = caps[i].isOpened();


        if (isOpeneds[i])
        {
            std::cout << "OPENED Index=" << i << std::endl;


            // Window名生成
            std::string windowName = APPLICATION_NAME;
            std::ostringstream ossDeviceId;
            ossDeviceId << i;
            windowName += " Index=" + ossDeviceId.str() + "";

            windowNames[deviceCounter] = windowName;

            cv::namedWindow(windowName);
            deviceCounter++;
        }
    }


    // for (int i = 0; i < MAX_SCAN_DEVICE; i++)
    // {
    //     if (isOpeneds[i])
    //     {
    //         // 開けた
    //         cv::imshow();
    //     }
    //     else
    //     {
    //         // 開けない
    //     }
    // }



    // ----------------------------------------------------------------
    // クローズ処理
    // ----------------------------------------------------------------
    // Window を開放
    cv::destroyAllWindows();

    // キャプチャデバイスを開放
    for (int i = 0; i < MAX_SCAN_DEVICE; i++)
    {
        if (isOpeneds[i])
        {
            // 開放
            caps[i].release();
        }
    }


    return 0;

}
