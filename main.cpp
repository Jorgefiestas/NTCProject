#include <iostream>
#include <chrono>
#include <vector>
#include <unordered_set>
#include <random>

#include "DirectBitmap.hpp"
#include "VirtualBitmap.hpp"
#include "MultiresolutionBitmap.hpp"

const int NDBM = 10000000;
const int NVBM = 1000000;

int main () {

	DirectBitmap<NDBM> dbm;
	VirtualBitmap<NVBM> vbm(0, 1000000, NDBM);
	MRBitmap<5, 1000000> mrbm;

	std::chrono::time_point<std::chrono::system_clock> start, end;
	unsigned long long elapsed_time;

	std::random_device rd;
	std::vector<int> requests;
	for (int i = 0; i < 10000000; i++) {
		 requests.push_back(rd() % NDBM);
	}

	std::unordered_set<int> st;
	start = std::chrono::system_clock::now();
	for (int r : requests) {
		st.insert(r);
	}
	end = std::chrono::system_clock::now();

	elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
	std::cout << "Control: " << elapsed_time << " " << st.size() << std::endl;

	start = std::chrono::system_clock::now();
	for (int r : requests) {
		dbm.insert(r);
	}
	end = std::chrono::system_clock::now();

	elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
	std::cout << "Direct Bitmap: " << elapsed_time << " " << dbm.getCount() << std::endl;

	start = std::chrono::system_clock::now();
	for (int r : requests) {
		vbm.insert(r);
	}
	end = std::chrono::system_clock::now();

	elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
	std::cout << "Virtual Bitmap: " << elapsed_time << " " << vbm.getCount() << std::endl;

	start = std::chrono::system_clock::now();
	for (int r : requests) {
		mrbm.insert(r);
	}
	end = std::chrono::system_clock::now();

	elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
	std::cout << "Multi-resolution Bitmap: " << elapsed_time << " " << mrbm.getCount() << std::endl;
	
	return 0;
}
