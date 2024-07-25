#include<vector>
#include <cmath>
std::vector<std::vector<double>> medfuncRLfilteredbackprojection(int theta_num, int N, std::vector<std::vector<double>> R, double delta, std::vector<double>fh_RL) {
	std::vector<std::vector<double>> rec_RL(N, std::vector<double>(N, 0));
	for (int i = 0; i < theta_num; i++) {
		std::vector<double> pm(N, 0);
		for (int j = 0; j < N; j++) {
			pm[j] = R[j][i];
		}
		int lenA = fh_RL.size();
		int lenB = pm.size();
		int lenOut= lenA + lenB - 1;
		std::vector<double> conv(lenOut, 0);
		// 执行线性卷积
		for (int m = 0; m < lenOut; ++m) {
			for (size_t n = 0; n <= m; ++n) {
				if (n < lenA && m - n < lenB) {
					conv[m] += fh_RL[n] * pm[m - n];
				}
			}
		}
		std::vector<double> pm_RL(N, 0);
		for (int m = 0; m < N; m++) {
			pm_RL[m] = conv[ceil((lenOut - lenA) / 2) - 1 + m];
		}
		double Cm = (N / 2) * (1 - cos(i * delta) - sin(i * delta));
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				double Xrm = Cm + k * cos(i * delta) + j * sin(i * delta);
				int n = floor(Xrm);
				double t = Xrm - n;
				if (n < 0) n = 0;
				if (n > N - 2)n = N - 2;
				double p = (1 - t) * pm_RL[n] + t * pm_RL[n + 1];
				rec_RL[k][j] = rec_RL[k][j] + p;
			}
		}
	}
	return rec_RL;
}