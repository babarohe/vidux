#include "opencv2/opencv.hpp"

#include "main.hpp"

#define APP_NAME "VIDUX"
#define MONITOR_WINDOW_NAME "VIDUX - Monitor(Master)"

using namespace cv;

int main(int argc, char *argv[])
{
    // Open the capture device
    Capture capture;

    if(capture.initDevice(0))
    {
        // if open failed it exit
        return -1;
    }


    while(true)
    {
        capture.read();

        cv::imshow("before", capture.getFrame());


        // ----------------------------------------------------------------
        // ビデオフィルタ
        // ----------------------------------------------------------------
        // ノイズリダクション
        capture.beautifulSkinFilter();


        // ----------------------------------------------------------------
        // 描画
        // ----------------------------------------------------------------
        // モニター表示
        cv::imshow(MONITOR_WINDOW_NAME, capture.getFrame());



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
            cv::imwrite("vidux-capture.jpg", capture.getFrame());
        }
    }

    // Window を開放
    cv::destroyAllWindows();

    // キャプチャデバイスを開放
    capture.closeDevice();

    return 0;

}
