#ifndef DEFINE_DBITMAP
#define DEFINE_DBITMAP

#include <math.h>

template <std::size_t N>
class DirectBitmap {
	private:
		unsigned long long bitmap[N / 64 + 1];
		int count = 0;
	
	public:
		DirectBitmap() = default;

		void insert (int idx) {
			idx = idx % N;
			int i = idx / 64;
			int j = idx % 64;

			int setBefore = __builtin_popcount(bitmap[i]);
			bitmap[i] = bitmap[i] | (1 << j);
			int setAfter = __builtin_popcount(bitmap[i]);

			if (setBefore != setAfter) {
				count++;
			}
		}

		void clear() {
			memset(bitmap, 0, sizeof bitmap);
			count = 0;
		}


		int  getCount() {
			double z = N - count;
			return (double)N * log((double)N / z);
		}
};

#endif
