#ifndef DEFINE_MRBITMAP
#define DEFINE_MRBITMAP

#include <math.h>

template <std::size_t R, std::size_t N>
class MRBitmap {
	private:
		unsigned long long *bitmap[R];
		double count[R];
		int lower_bound;
		int upper_bound;
		int h;
	
	public:
		MRBitmap () {
			int d = 1;
			for (int i = 0; i < R; i++) {
				bitmap[i] = new unsigned long long[N / (d * 64) + 1];
				d <<= 1;
			}
		}

		void insert (int idx) {
			idx = idx % N;

			int r = idx / N;

			idx = idx % N;
			idx = idx / (1 << r);

			int i = idx / 64;
			int j = idx % 64;

			int setBefore = __builtin_popcount(bitmap[r][i]);
			bitmap[r][i] |= (1 << j);
			int setAfter = __builtin_popcount(bitmap[r][i]);

			if (setBefore != setAfter) {
				count[r]++;
			}
		}

		void clear() {
			for(int i = 0; i < R; i++) {
				memset(bitmap[i], 0, sizeof bitmap[i]);
				count[i] = 0;
			}
		}

		int getCount() {
			for (int i = 0 ; i < R; i++) {
				double sizeR = N / (1 << i);
				std::cout << std::endl << i << " " << count[i];
				count[i] = (double) N * log(sizeR / (sizeR - count[i]));
				std::cout << std::endl << i << " " << count[i] << std::endl;
			}
			
			int base = R - 1;
			while (base > 0 && count[base] <= 100000) {
				base--;
			}

			base++;

			int m = 0;
			for (int i = base; i < R; i++) {
				m += N * log(N / (N - count[i]));
			}

			int factor = (1 << (R - 1));
			return factor * m;
		}
};

#endif
