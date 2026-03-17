#include<iostream>
#include<thread>

volatile int x,y;
constexpr int LOOP = 5000'0000;

int trace_x[LOOP],trace_y[LOOP];

void thread_x() {
	for (int i = 0; i < LOOP; ++i) {
		x = i;
		std::atomic_thread_fence(std::memory_order_seq_cst); // 메모리 배리어
		trace_y[i] = y;
	}
}	

void thread_y() {
	for (int i = 0; i < LOOP; ++i) {
		y = i;
		std::atomic_thread_fence(std::memory_order_seq_cst); // 메모리 배리어
		trace_x[i] = x;
	}
}

int main() {
	std::thread t1(thread_x);
	std::thread t2(thread_y);
	t1.join();
	t2.join();
	int count = 0;
	for (int i = 0; i < LOOP-1; ++i) {
		if (trace_x[i] == trace_x[i+1]) {
			if (trace_y[trace_x[i]] == trace_y[trace_x[i] + 1]) {
				if (trace_y[trace_x[i]] == i) {
					++count;
					std::cout << "Memory error at " << i << " trace_x = " << trace_x[i] << " trace_y = " << trace_y[trace_x[i]] << std::endl;
				}
			}
		}
	}
	std::cout << "count of memory error = " << count << std::endl;
}