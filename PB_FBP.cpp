#include<iostream>
#include<vector>
#include <cmath>
#include"func.h"
#include <opencv2/opencv.hpp>
#include <algorithm>
using namespace std;
int pbfbp() {
	int N = 256;//ͼ���С
	int size[2] = { N,N };
	vector<double> theta;
	for (double i = 0; i < 180; i += 1) {
		theta.push_back(i);
	}
	double norm = 0;
	for (int i = 0; i < 2; i++) {
		norm += pow(size[i] - floor((size[i] - 1) / 2) - 1, 2);
	}
	int N_d = 2 * ceil(sqrt(norm)) + 3;
	vector<vector<double>> P(N_d, vector<double>(theta.size(), 0));
	P = medfuncParallelBeamForwardProjection(theta, N, N_d);
	int rows = N_d;
	int cols = theta.size();
	int e = floor((rows - N - 1) / 2 + 1) + 1;
	vector<vector<double>> R(N, vector<double>(theta.size(), 0));
	for (int i = e; i <= e + N - 1; i++) {
		for (int j = 0; j < cols; j++) {
			R[i - e][j] = P[i][j];
		}
	}
	int d = 1;
	vector<double> fh_RL(N, 0);
	fh_RL = medfuncRlfilterfunction(N, d);
	vector<double> fh_SL(N, 0);
	fh_SL = medfuncSlfilterfunction(N, d);
	vector<vector<double>> rec(N, vector<double>(N, 0));
	rec = medfuncBackprojection(theta.size(), N, R, CV_PI / 180);
	vector<vector<double>> rec_RL(N, vector<double>(N, 0));
	rec_RL = medfuncRLfilteredbackprojection(theta.size(), N, R, CV_PI / 180, fh_RL);
	vector<vector<double>> rec_SL(N, vector<double>(N, 0));
	rec_SL = medfuncSLfilteredbackprojection(theta.size(), N, R, CV_PI / 180, fh_SL);
	cv::Mat normalized_rec = medfuncnorm(rec);
	cv::Mat normalized_RL_rec = medfuncnorm(rec_RL);
	cv::Mat normalized_SL_rec = medfuncnorm(rec_SL);
	cv::Mat image = cv::imread("S-Lͷģ��.png", cv::IMREAD_GRAYSCALE);
	// ȷ�����ڵĴ�С
	int width = image.cols * 2; // ��������ͼ�������ͬ�Ŀ��
	int height = image.rows * 2; // ��������ͼ�������ͬ�ĸ߶ȣ�����������������
	// ����һ���հ׵Ĵ�ͼ��
	cv::Mat displayImage = cv::Mat::zeros(height, width, image.type());
	// ��ͼ���Ƶ���ͼ����ض�����
	cv::Rect roi1(0, 0, image.cols, image.rows);
	cv::Rect roi2(image.cols, 0, normalized_rec.cols, normalized_rec.rows);
	cv::Rect roi3(0, image.rows, normalized_RL_rec.cols, normalized_RL_rec.rows);
	cv::Rect roi4(image.cols, image.rows, normalized_SL_rec.cols, normalized_SL_rec.rows);
	image.copyTo(displayImage(roi1));
	normalized_rec.copyTo(displayImage(roi2));
	normalized_RL_rec.copyTo(displayImage(roi3));
	normalized_SL_rec.copyTo(displayImage(roi4));
	// ��ʾ�ϲ����ͼ��
	cv::imshow("Four Images in One Window", displayImage);
	cv::waitKey(0); // �ȴ��û�����

	return 0;
}