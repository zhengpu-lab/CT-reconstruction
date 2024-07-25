#include <opencv2/opencv.hpp>
#include <vector>
int SLModel() {
    struct Params {
        double param1, param2, param3, param4, param5, param6;
    };
    // 图像的尺寸
    int rows = 256;
    int cols = 256;
    std::vector<Params> shep = {
        {1, 0.69, 0.92, 0, 0, 0},
        {0.2, 0.6624, 0.8740, 0, -0.0184, 0},
        {0, 0.1100, 0.3100, 0.22, 0, -18},
        {0, 0.1600, 0.4100, -0.22, 0, 18 },
        {0.5, 0.2100, 0.2500, 0, 0.35, 0},
        {0.4, 0.0460, 0.0460, 0, 0.1, 0},
        {0.4, 0.0460, 0.0460, 0, -0.1, 0},
        {0.3, 0.0460, 0.0230, -0.08, -0.605, 0},
        {0.3, 0.0230, 0.0230, 0, -0.606, 0},
        {0.3, 0.0230, 0.0460, 0.06, -0.605, 0}
    };
    // 创建灰度图像
    cv::Mat grayImage(rows, cols, CV_8UC1, cv::Scalar(0)); // 初始化为黑色背景
    for (const auto& params : shep) {
        double rho = params.param1;
        double a= params.param2;
        double b = params.param3;
        double x = params.param4;
        double y = params.param5;
        double alpha = params.param6;
        // 椭圆的参数
        cv::Point center1(cols * (x - (-1)) / (1 - (-1)), rows * (-y - (-1)) / (1 - (-1)));
        cv::Size axes1(cols / 2 * a, rows / 2 * b);
        double angle1 = -alpha;
        cv::Scalar color1(255 * rho);
        // 绘制并填充椭圆
        cv::ellipse(grayImage, center1, axes1, angle1, 0, 360, color1, cv::FILLED);
    }
    // 显示图像
    cv::imshow("S-L头模型", grayImage);
    // 等待键盘事件
    cv::waitKey(0); // 等待任意键按下
    // 保存图像
    cv::imwrite("S-L头模型.png", grayImage);
    return 0;
}