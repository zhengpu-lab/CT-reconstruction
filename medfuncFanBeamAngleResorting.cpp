#include<vector>
#include<iostream>
#include<opencv2/opencv.hpp>
#include"func.h"
std::vector<std::vector<double>> medfuncFanBeamAngleResorting(std::vector<std::vector<double>> P, int N, int SOD, double delta_beta, double delta_gamma) {
    int N_d = P.size(); // 获取行数
    int beta_num = 0;
    if (N_d > 0) {
        beta_num = P[0].size(); // 获取第一行的大小，即列数
    }
    double delta_theta = 1;
    std::vector<double>theta;
    for (double i = 0; i < 360; i += delta_theta) {
        theta.push_back(i);
    }
    int Np = 260;
    int Mp = theta.size();
    delta_gamma = delta_gamma * CV_PI / 180;
    delta_theta=delta_theta * CV_PI / 180;
    delta_beta = delta_beta * CV_PI / 180;
    //double d = SOD * sin(floor(N_d / 2) * delta_gamma) / (floor(N_d / 2));
    double d = 1;
    std::vector<std::vector<double>>pp(N_d, std::vector<double>(Mp, 0));
    for (int k1 = 0; k1 <N_d; k1++) {
        for (int k2 = 0; k2 < Mp; k2++) {
            double t = k2 * (delta_theta / delta_beta) - (k1- floor(N_d / 2)) * (delta_gamma / delta_beta);
            int n = floor(t);
            double u = t - n;
            if ((n >= 0) && (n < beta_num-1)) {
                pp[k1][k2] = (1 - u) * P[k1][n] + u * P[k1][n + 1];
            }
        }
    }
    cv::Mat normalized_pp = medfuncnorm(pp);
    cv::imshow("normalized_pp", normalized_pp);
    cv::waitKey(0); // 等待用户按键
    std::vector<std::vector<double>>PP(Np, std::vector<double>(Mp, 0));

    for (int k1 = 0; k1 < Mp; k1++) {
        for (int k2 = 0; k2 <Np; k2++) {
            double tt = 1 / delta_gamma * asin((k2- floor(Np / 2)) * d / SOD)+ floor(Np / 2);
            int m = floor(tt);
            double uu = tt - m;
            if ((m >=0) && (m <(N_d-1))) {
                PP[k2][k1] = (1 - uu) * pp[m][k1] + uu * pp[m + 1][k1];
            }
        }
    }
    return PP;
}