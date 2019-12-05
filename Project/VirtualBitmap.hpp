#ifndef DEFINE_VBITMAP
#define DEFINE_VBITMAP

#include <math.h>

template <std::size_t N>
class VirtualBitmap {
	private:
		unsigned long long bitmap[N / 64 + 1];
		int count = 0;
		int lower_bound;
		int upper_bound;
		int h;
	
	public:
		VirtualBitmap (int lower_bound, int upper_bound, int h) :
			lower_bound(lower_bound), upper_bound(upper_bound), h(h) {}

		void insert (int idx) {
			if (idx > upper_bound || idx < lower_bound) {
				return;
			}

			idx -= lower_bound;

			int i = idx / 64;
			int j = idx % 64;

			int setBefore = __builtin_popcount(bitmap[i]);
			bitmap[i] |= (1 << j);
			int setAfter = __builtin_popcount(bitmap[i]);

			if (setBefore != setAfter) {
				count++;
			}
		}

		void clear() {
			memset(bitmap, 0, sizeof bitmap);
			count = 0;
		}

		int getCount() {
			double z = N - count;
			return (double)h * log((double)N / z);
		}
};

#endif
