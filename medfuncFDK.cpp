#include<vector>
#include <opencv2/opencv.hpp>
#include<cmath>
std::vector<std::vector<std::vector<double>>>medfuncFDK(std::vector<std::vector<std::vector<double>>>P, int N, double SOD, int theta_num, int detector_length){
	std::vector<double> fh_RL(N, 0);
	double dd = detector_length / N;
	for (int k1 = 0; k1 < N; k1++) {
		fh_RL[k1] = -1 / (2 * CV_PI*CV_PI * pow((N / 2-k1)* dd, 2));
		if ((k1 - N / 2) % 2 == 0) {
			fh_RL[k1] = 0;
		}
	}
	fh_RL[N / 2] = 1 / (8*dd*dd);
	std::vector<std::vector<std::vector<double>>>rec(N, std::vector<std::vector<double>>(N, std::vector<double>(N, 0)));
	for (int i = 0; i < theta_num; i++) {
		//std::cout << i << std::endl;
		double beta = i * 360 / theta_num * CV_PI / 180;
		std::vector<std::vector<double>>weighted_project_beta(N, std::vector<double>(N, 0));
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				weighted_project_beta[j][k] = P[j][k][i] * SOD / sqrt(SOD * SOD + pow((N / 2-j) * dd, 2) + pow((N / 2-k) * dd, 2));
			}
		}
		std::vector<std::vector<double>>filtered_project(N, std::vector<double>(N, 0));
		for (int k = 0; k < N; k++) {
			std::vector<double>pm(N, 0);
			for (int j = 0; j < N; j++) {
				pm[j] = weighted_project_beta[k][j];
			}
			int lenA = fh_RL.size();
			int lenB = pm.size();
			int lenOut = lenA + lenB - 1;
			std::vector<double> conv(lenOut, 0);
			// 执行线性卷积
			for (int m = 0; m < lenOut; ++m) {
				for (size_t n = 0; n <= m; ++n) {
					if (n < lenA && m - n < lenB) {
						conv[m] += fh_RL[n] * pm[m - n];
					}
				}
			}
			for (int m = 0; m < N; m++) {
				filtered_project[k][m]= conv[ceil((lenOut - lenA) / 2) - 1 + m];
			}
		}
		
		for (int k1 = 0; k1 < N; k1++) {
			double x = dd * (N / 2-k1);
			for (int k2 = 0; k2 < N; k2++) {
				double y = dd * (N / 2 - k2);
				double U = (SOD + x * sin(beta) - y * cos(beta)) / SOD;
				double a = (x * cos(beta) + y * sin(beta)) / U;
				double xx = floor(a / dd + N / 2);
				double u1 = a / dd + N / 2 - xx;
				for (int k3 = 0; k3 < N; k3++) {
					double z = dd * (N / 2 - k3);
					double b = z / U;
					double yy = floor(b / dd + N / 2);
					double u2 = b / dd + N / 2 - yy;
					if ((xx >= 0) && (xx < N - 1) && (yy >= 0) && (yy < N - 1)) {
						double temp = (1 - u1) * (1 - u2) * weighted_project_beta[yy][xx] + (1 - u1) * u2 * weighted_project_beta[yy][xx + 1] + u1 * (1 - u2) * weighted_project_beta[yy + 1][xx] + u1 * u2 * weighted_project_beta[yy + 1][xx + 1];
						rec[k1][N - 1 - k2][k3] += temp/U*U*2* CV_PI / theta_num;
					}
					//else {
					//	rec[k1][k2][k3] += rec[k1][k2][k3] * CV_PI / 180 / dd;
					//}123-143-112-444//132-332//213-411//231-411//312-334//321-143
				}
			}
		}
	}
	return rec;
}