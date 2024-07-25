#include <opencv2/opencv.hpp>
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

void minMaxNormalization(std::vector<std::vector<double>>& data) {
    // 寻找最大值和最小值
    double minVal = 100000000;
    double maxVal = -100000000;
    for (auto row : data) {
        for (auto elem : row) {
            if (elem > maxVal) {
                maxVal = elem;
            }
            if (elem < minVal) {
                minVal = elem;
            }
        }
    }
    // 遍历数组进行归一化
    for (auto& row : data) {
        for (auto& value : row) {
            value =(value - minVal)*255 / (maxVal - minVal);
        }
    }
}
int pp() {
    // 加载图像
    cv::Mat image = cv::imread("S-L头模型.png");
    // 定义直线上的两个点
    double delta_theta = 0.5;
    double delta_distance = 1;
    double right_angle = std::asin(1);
    int numRows = 362; // 行数
    int numCols = 360; // 列数
    std::vector<std::vector<double>> vec(numRows, std::vector<double>(numCols, 0));
    int rows = -1;
    int cols = -1;
    for (double i = 0; i < 180; i += delta_theta) {
        cols += 1;
        double theta = i * 2 * right_angle / 180;
        for (double j = -181; j < 181; j+= delta_distance) {
            rows += 1;
            cv::Point pt1(0 + j * cos(right_angle - theta), 0 + j * sin(-right_angle - theta)); // 直线上的一个点
            cv::Point pt2(362 * cos(theta)-j*cos(right_angle-theta), 362 * sin(theta) + j * sin(right_angle - theta)); // 直线上的另一个点
            // 计算像素值之和
            int sum = 0;
            int count = 0;
            // 计算直线的参数
            double dx = pt2.x - pt1.x;
            double dy = pt2.y - pt1.y;
            double gradient = dy / dx; // 斜率
            double intercept = pt1.y - gradient * pt1.x; // y轴截距
            // 遍历直线上的点
            int x_before = -10000;
            int y_before = -10000;
            for (double t = 0; t <= 1; t += 0.1) { // 步长可以根据图像分辨率调整
                int x = static_cast<int>(pt1.x + t * dx);
                int y = static_cast<int>(pt1.y + t * dy);
                // 确保点在图像范围内
                if ((x_before == x) && (y_before == y)) {
                    continue;
                }
                if (x >= 0 && x < image.cols && y >= 0 && y < image.rows) {
                    // 累加像素值
                    sum += image.at<uchar>(y, x);
                    count++;
                }
            }
            if (rows >= 362 || cols >= 360){
                std::cout << rows << "数组越界" << cols<<std::endl;
                break;
            }
            vec[rows][cols] = sum;
        }
        rows = -1;
    }
    minMaxNormalization(vec);
    cv::Mat mat_8u(numRows, numCols, CV_8UC1, cv::Scalar(0));
    for (int i = 0; i < numRows; ++i) {
        for (int j = 0; j < numCols; ++j) {
            mat_8u.at<uchar>(i, j) = static_cast<uchar>(vec[i][j]);
        }
    }
    // 显示图像
    cv::imshow("平行投影", mat_8u);
    // 等待键盘事件
    cv::waitKey(0); // 等待任意键按下
    // 保存图像
    cv::imwrite("平行投影.png", mat_8u);
    return 0;
}