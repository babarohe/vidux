#include "opencv2/opencv.hpp"

#include "main.hpp"

#define APP_NAME "VIDUX"
// #define MONITOR_WINDOW_NAME "VIDUX - Monitor(Master)"
#define MONITOR_WINDOW_NAME "VIDUX - Monitor"
#define MAX_CAPTURE_DEVICE 3


int main(int argc, char *argv[])
{
    int index = 0;

    if (argc > 1)
    {
        index = atoi(argv[1]);
    }

    // Open the capture device
    Capture captures[MAX_CAPTURE_DEVICE];
    int devices = 0;

    if(captures[0].initDevice(index))
    {
        // if open failed it exit
        return -1;
    }
    devices++;

    // if(captures[1].initDevice(2))
    // {
    //     // if open failed it exit
    //     return -1;
    // }
    // devices++;

    // ----------------------------------------------------------------
    // 仮想デバイス初期化
    // ----------------------------------------------------------------
    // v4l2sink sink;


    cv::Mat masterFrame;
    // int r = sink.init(masterFrame.cols, masterFrame.rows, masterFrame.channels() == 1 ? v4l2sink::GRAY: v4l2sink::RGB);

    cv::namedWindow("ruddyFilter()");
    cv::namedWindow("toneUpSkinFilter()");


    while(true)
    {
        for (int i = 0; i < devices; i++)
        {
            // ----------------------------------------------------------------
            // ビデオ取得
            // ----------------------------------------------------------------
            captures[i].read();


            // ----------------------------------------------------------------
            // ビデオフィルタ
            // ----------------------------------------------------------------
            // 血色フィルタ
            captures[i].ruddyFilter();

            // トーンアップフィルタ
            captures[i].toneUpSkinFilter();

            // 美肌フィルタ
            captures[i].beautifulSkinFilter();

            // ガンマ調整
            captures[i].gammaFilter(1.15);


            // ----------------------------------------------------------------
            // 描画lutMat
            // ----------------------------------------------------------------
            // モニター表示
            std::string windowName = MONITOR_WINDOW_NAME;

            std::ostringstream ossDeviceId;
            ossDeviceId << i;
            windowName += "[FRAME_ID_BUFFER_MAIN(0x01), dev=" + ossDeviceId.str() + "]";

            cv::imshow(windowName, captures[i].getFrame());


            std::string windowNameRaw = MONITOR_WINDOW_NAME;
            windowNameRaw += " [FRAME_ID_INPUT(0x00), dev=" + ossDeviceId.str() + "]";

            cv::imshow(windowNameRaw, captures[i].getFrame(FRAME_ID_INPUT));

            captures[i].getFrame().copyTo(masterFrame);

        }


        // マスターフレーム表示
        // cv::imshow("VIDUX - Monitor (Mixed_Master)", masterFrame);

        // r = sink.write((const char*)masterFrame.data, masterFrame.cols * masterFrame.rows * masterFrame.channels());


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
