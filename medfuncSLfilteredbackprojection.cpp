#include<vector>
#include <cmath>
std::vector<std::vector<double>> medfuncSLfilteredbackprojection(int theta_num, int N, std::vector<std::vector<double>> R, double delta, std::vector<double>fh_SL) {
	std::vector<std::vector<double>> rec_SL(N, std::vector<double>(N, 0));
	for (int i = 0; i < theta_num; i++) {
		std::vector<double> pm(N, 0);
		for (int j = 0; j < N; j++) {
			pm[j] = R[j][i];
		}
		int lenA = fh_SL.size();
		int lenB = pm.size();
		int lenOut = lenA + lenB - 1;
		std::vector<double> conv(lenOut, 0);
		// 执行线性卷积
		for (int m = 0; m < lenOut; ++m) {
			for (size_t n = 0; n <= m; ++n) {
				if (n < lenA && m - n < lenB) {
					conv[m] += fh_SL[n] * pm[m - n];
				}
			}
		}
		std::vector<double> pm_SL(N, 0);
		for (int m = 0; m < N; m++) {
			pm_SL[m] = conv[ceil((lenOut - lenA) / 2) - 1 + m];
		}
		double Cm = (N / 2) * (1 - cos(i * delta) - sin(i * delta));
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				double Xrm = Cm + k * cos(i * delta) + j * sin(i * delta);
				int n = floor(Xrm);
				double t = Xrm - n;
				if (n < 0) n = 0;
				if (n > N - 2)n = N - 2;
				double p = (1 - t) * pm_SL[n] + t * pm_SL[n + 1];
				rec_SL[k][j] = rec_SL[k][j] + p;
			}
		}
	}
	return rec_SL;
}