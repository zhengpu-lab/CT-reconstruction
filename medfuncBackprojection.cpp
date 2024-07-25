#include<vector>

std::vector<std::vector<double>> medfuncBackprojection(int theta_num, int N, std::vector<std::vector<double>> R, double delta) {
	std::vector<std::vector<double>> rec(N, std::vector<double>(N, 0));
	for (int i = 0; i < theta_num; i++) {
		std::vector<std::vector<double>> pm(N, std::vector<double>(1, 0));
		for (int j = 0; j < N; j++) {
			pm[j][0] = R[j][i];
		}
		double Cm = (N / 2) * (1 - cos(i * delta) - sin(i * delta));
		for (int j = 0; j < N; j++) {
			for (int k = 0; k < N; k++) {
				double Xrm = Cm + k * cos(i * delta) + j * sin(i * delta);
				int n = floor(Xrm);
				double t = Xrm - n;
				if (n < 0) n = 0;
				if (n > N - 2)n = N - 2;
				double p = (1 - t) * pm[n][0] + t * pm[n + 1][0];
				rec[k][j] = rec[k][j] + p;
			}
		}
	}
	return rec;
}