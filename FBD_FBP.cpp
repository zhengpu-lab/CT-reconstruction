#include<iostream>
#include<vector>
#include <cmath>
#include"func.h"
#include <opencv2/opencv.hpp>
#include <algorithm>
using namespace std;
int fbdfbp() {
	int N = 256;//ͼ���С
	int size[2] = { N,N };
	vector<double> beta;
	for (double i = 0; i < 360; i += 1) {
		beta.push_back(i);
	}
	double SOD = 250;
	int N_d = 380;
	double delta_dd = (N / 2) / (SOD - (N / 2)) * SOD / (N / 2);
	vector<vector<double>> P(N_d, vector<double>(beta.size(), 0));
	P = medfuncFanBeamDistanceForwardProjection(N, beta, SOD, N_d, delta_dd);
	vector<double> fh_RL(N_d, 0);
	fh_RL = medfuncFanBeamRlfilter2(N_d, delta_dd);
	vector<vector<double>> rec_RL(N, vector<double>(N, 0));
	rec_RL = medfuncFanBeamDistanceFBP(P, fh_RL, beta, SOD, N, N_d, delta_dd);

	cv::Mat normalized_RL_rec = medfuncnorm(rec_RL);
	cv::Mat normalized_P = medfuncnorm(P);
	cv::imshow("normalized_P", normalized_P);
	cv::waitKey(0); // �ȴ��û�����
	cv::Mat image = cv::imread("S-Lͷģ��.png", cv::IMREAD_GRAYSCALE);
	// ȷ�����ڵĴ�С
	int width = image.cols * 2; // ��������ͼ�������ͬ�Ŀ��
	int height = image.rows; // ��������ͼ�������ͬ�ĸ߶ȣ�����������������
	// ����һ���հ׵Ĵ�ͼ��
	cv::Mat displayImage = cv::Mat::zeros(height, width, image.type());
	// ��ͼ���Ƶ���ͼ����ض�����
	cv::Rect roi1(0, 0, image.cols, image.rows);
	cv::Rect roi2(image.cols, 0, normalized_RL_rec.cols, normalized_RL_rec.rows);
	image.copyTo(displayImage(roi1));
	normalized_RL_rec.copyTo(displayImage(roi2));
	// ��ʾ�ϲ����ͼ��
	cv::imshow("Four Images in One Window", displayImage);
	cv::waitKey(0); // �ȴ��û�����

	return 0;
}