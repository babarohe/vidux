#include "main.hpp"
#include "opencv2/opencv.hpp"

#define APP_NAME "VIDUX"
#define MONITOR_WINDOW_NAME "VIDUX - Minitor"

using namespace cv;

int main(int argc, char *argv[])
{
    // Open the camera
    cv::VideoCapture cap(0);

    if(!cap.isOpened())
    {
        // 失敗時閉じる
        return -1;
    }


    cv::Mat frame;
    while(true)
    {
        // フレーム取得
        cap.read(frame);
        //
        //取得したフレーム画像に対して，クレースケール変換や2値化などの処理を書き込む．
        //

        // モニター表示
        cv::imshow(MONITOR_WINDOW_NAME, frame);

        const int key = cv::waitKey(1);
        if(key == 'q')
        {
            break;
        }
        else if(key == 's')
        {
            cv::imwrite("img.png", frame);
        }
    }
    cv::destroyAllWindows();
    return 0;



    Mat edges;
    namedWindow(MONITOR_WINDOW_NAME, 1);
    while(true)
    {
        Mat frame;
        cap >> frame; // get a new frame from camera
        cvtColor(frame, edges, COLOR_BGR2GRAY);
        GaussianBlur(edges, edges, Size(7,7), 1.5, 1.5);
        Canny(edges, edges, 0, 30, 3);
        imshow(MONITOR_WINDOW_NAME, edges);
        if(waitKey(30) >= 0) break;
    }
    // the camera will be deinitialized automatically in VideoCapture destructor
    return 0;
}
