#include<vector>

std::vector<double> medfuncRlfilterfunction(int N, int d) {
	std::vector<double> fh_RL(N, 0);
	for (int k1 = 0; k1 < N; k1++) {
		fh_RL[k1] = -1 / (4 * asin(1) * asin(1) * pow((k1 - N / 2) * d, 2));
		if ((k1 - N / 2) % 2 == 0) {
			fh_RL[k1] = 0;
		}
	}
	fh_RL[N / 2] = 1 / (4 * pow(d, 2));
	return fh_RL;
}