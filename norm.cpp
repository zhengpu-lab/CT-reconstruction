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
	// ��һ������
	double scale = 255.0 / (maxVal - minVal);
	// ȷ������ĳߴ�
	int rows = static_cast<int>(rec.size());
	int cols = rows > 0 ? static_cast<int>(rec[0].size()) : 0;
	// ������һ����� cv::Mat ����
	cv::Mat normalizedMat(rows, cols, CV_8UC1);
	// ִ�й�һ������
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < cols; ++j) {
			// ȷ�����������ֵ���
			uchar val = static_cast<uchar>((rec[i][j] - minVal) * scale);
			normalizedMat.at<uchar>(i, j) = val;
		}
	}
	return normalizedMat;
}
