
#include "vidux-capture-main.hpp"


int main(int argc, char *argv[])
{
    // ----------------------------------------------------------------
    // GTK+3.0 Open
    // ----------------------------------------------------------------
    ViduxCaptureGui gui;
    gui.init();
    gui.main();

    // ----------------------------------------------------------------
    // OpenCV Open
    // ----------------------------------------------------------------
    int index = 0;

    if (argc > 1)
    {
        index = atoi(argv[1]);
    }

    // Open the capture device
    Capture capture;

    if(capture.initDevice(index))
    {
        // if open failed it exit
        return -1;
    }

    // Initialize video filter
    capture.initFilters();

    // ----------------------------------------------------------------
    // ウィンドウ事前処理
    // ----------------------------------------------------------------
    // デバイスIDの文字列取得
    std::ostringstream ossDeviceId;
    ossDeviceId << index;

    // 入力ウィンドウ名
    std::string windowNameInput = APPLICATION_NAME;
    windowNameInput += " [FRAME_ID_INPUT(0x00), dev=\"/dev/video" + ossDeviceId.str() + "\"]";

    // 出力ウィンドウ名
    std::string windowNameBufferMain = APPLICATION_NAME;
    windowNameBufferMain += " [FRAME_ID_BUFFER_MAIN(0x01), dev=\"/dev/video" + ossDeviceId.str() + "\"]";


    // ----------------------------------------------------------------
    // ウィンドウ生成
    // ----------------------------------------------------------------
    cv::namedWindow("ruddyFilter()");
    cv::namedWindow("toneUpSkinFilter()");
    cv::namedWindow(windowNameInput);
    cv::namedWindow(windowNameBufferMain);


    while(true)
    {
        // ----------------------------------------------------------------
        // ビデオ取得
        // ----------------------------------------------------------------
        capture.read();


        // ----------------------------------------------------------------
        // ビデオフィルタ
        // ----------------------------------------------------------------
        // 血色フィルタ
        capture.ruddyFilter();

        // トーンアップフィルタ
        capture.toneUpSkinFilter();

        // 美肌フィルタ
        capture.beautifulSkinFilter();

        // ガンマ調整
        capture.gammaFilter(1.15);


        // ----------------------------------------------------------------
        // 描画
        // ----------------------------------------------------------------
        cv::imshow(windowNameInput, capture.getFrame(FRAME_ID_INPUT));
        cv::imshow(windowNameBufferMain, capture.getFrame());


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
            cv::imwrite("capture.jpg", capture.getFrame());
        }
    }

    // ----------------------------------------------------------------
    // クローズ処理
    // ----------------------------------------------------------------
    // Window を開放
    cv::destroyAllWindows();

    // キャプチャデバイスを開放
    capture.closeDevice();


    return 0;

}
