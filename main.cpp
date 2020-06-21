#include "opencv2/opencv.hpp"

#include "main.hpp"


#define APP_NAME "VIDUX"
// #define MONITOR_WINDOW_NAME "VIDUX - Monitor(Master)"
#define MONITOR_WINDOW_NAME "VIDUX - Monitor"
#define MAX_CAPTURE_DEVICE 3


int main(int argc, char *argv[])
{

    // Open the capture device
    Capture captures[MAX_CAPTURE_DEVICE];

    if(captures[0].initDevice(2))
    {
        // if open failed it exit
        return -1;
    }

    if(captures[1].initDevice(0))
    {
        // if open failed it exit
        return -1;
    }

    int devices = 2;


    while(true)
    {
        for (int i = 0; i < devices; i++)
        {
            captures[i].read();
            // cv::imshow("before", captures[i].getFrame());


            // ----------------------------------------------------------------
            // ビデオフィルタ
            // ----------------------------------------------------------------
            // ノイズリダクション
            captures[i].beautifulSkinFilter();
            captures[i].gammaFilter(1.1);


            // ----------------------------------------------------------------
            // 描画lutMat
            // ----------------------------------------------------------------
            // モニター表示
            std::string windowName = MONITOR_WINDOW_NAME;

            std::ostringstream ossDeviceId;
            ossDeviceId << i;
            windowName += "(Device: " + ossDeviceId.str() + ")";

            cv::imshow(windowName, captures[i].getFrame());


        }



        // ----------------------------------------------------------------
        // ユーザ操作
        // ----------------------------------------------------------------
        const int key = cv::waitKey(1);
        if(key == 'q')
        {
            break;
        }
        else if(key == 's')
        {
            cv::imwrite("vidux-master.jpg", captures[0].getFrame());
        }
    }

    // Window を開放
    cv::destroyAllWindows();

    // キャプチャデバイスを開放
    for (int i = 0; i < devices; i++)
    {
        captures[i].closeDevice();
    }

    return 0;

}
