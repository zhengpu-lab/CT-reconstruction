#include <opencv2/opencv.hpp>
#include<vector>
cv::Mat medfuncnorm(std::vector<std::vector<double>> rec) {
	double minVal = std::numeric_limits<double>::max();
	double maxVal = std::numeric_limits<double>::lowest();
	for (const auto& row : rec) {
		for (double val : row) {
			if (val < minVal) minVal = val;
			if (val > maxVal) maxVal = val;
		}
	}
	// 归一化比例
	double scale = 255.0 / (maxVal - minVal);
	// 确保矩阵的尺寸
	int rows = static_cast<int>(rec.size());
	int cols = rows > 0 ? static_cast<int>(rec[0].size()) : 0;
	// 创建归一化后的 cv::Mat 对象
	cv::Mat normalizedMat(rows, cols, CV_8UC1);
	// 执行归一化操作
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			// 确保不会产生数值溢出
			uchar val = static_cast<uchar>((rec[i][j] - minVal) * scale);
			normalizedMat.at<uchar>(i, j) = val;
		}
	}
	return normalizedMat;
}
