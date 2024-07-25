#include<vector>

std::vector<double> medfuncSlfilterfunction(int N, int d) {
	std::vector<double> fh_SL(N, 0);
	for (int k1 = 0; k1 < N; k1++) {
		fh_SL[k1] = -2 / (4 * asin(1) * asin(1) * d*d*(4*pow(k1 - N / 2, 2)-1));
	}
	return fh_SL;
}