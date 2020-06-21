#include "main.hpp"
#include "opencv2/opencv.hpp"

#define APP_NAME "VIDUX"
#define MONITOR_WINDOW_NAME "VIDUX - Monitor"

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
    cv::Mat filterBuf;

    // cv::Mat frame = cv::Mat(cv::Size(640, 480), CV_8UC3);

    while(true)
    {
        // フレーム取得
        cap.read(frame);

        // 正規化処理
        // cv::cvtColor(frame, frame, cv::COLOR_BGR2BGRA);
        // cv::cvtColor(frame, frame, CV_BGR2GRAY, 1);

        cv::imshow("before", frame);


        // 映像処理
        // cv::GaussianBlur(frame, frame, Size(7,7), 1.5, 1.5);
        // cv::medianBlur(frame, frame, 3);
        cv::bilateralFilter(frame, filterBuf, 5, 76, 12, 4);
        cv::cvtColor(filterBuf, frame, cv::COLOR_RGB2RGBA);


        // モニター表示
        cv::imshow(MONITOR_WINDOW_NAME, frame);
        // cv::imshow("after", frame);

        const int key = cv::waitKey(1);
        if(key == 'q')
        {
            break;
        }
        else if(key == 's')
        {
            cv::imwrite("vidux-capture.jpg", frame);
        }
    }

    // Window を開放
    cv::destroyAllWindows();

    // キャプチャデバイスを開放
    cap.release();

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
