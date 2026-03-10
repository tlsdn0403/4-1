#include<iostream>	
#include<thread>
#include<mutex>
#include<chrono>
#include<vector>
#include<atomic>


std::mutex mylock;
volatile int sum; // 실행속도 꼼수 부리지 마라
std::atomic<int> atomic_sum; // 아토믹
using namespace std::chrono;
void add(int num_thread) {
	auto loop = 5000'0000 / num_thread;
	for (auto i = 0; i < loop; ++i)
	{
		
		mylock.lock();
		sum = sum + 2;
		mylock.unlock();
	}
}

void atomic_add(int num_thread) {
	auto loop = 5000'0000 / num_thread;
	for (auto i = 0; i < loop; ++i)		
	{
		atomic_sum += 2;
	}
}
int main()
{
	{
		std::cout << "start" << std::endl;
		auto start = high_resolution_clock::now();
		for (auto i = 0; i < 5000'0000; ++i) sum = sum + 2;
		std::cout << "Single thread Sum = " << sum << std::endl;
		auto end = high_resolution_clock::now() - start;
		std::cout << "time :" << duration_cast<milliseconds>(end).count() << std::endl;

		

	}
	{
		auto s = high_resolution_clock::now();
		for (auto num : { 1,2,4,6,8 }) {
			sum = 0;
			std::vector<std::thread> threads;
			for (int i = 0; i < num; ++i) {
				threads.emplace_back(add, num);
			}
			for (auto& t : threads)t.join();

			std::cout << "Thread num = " << num << " ";
			std::cout << "Multi thread Sum = " << sum << std::endl;
			auto t = high_resolution_clock::now() - s;
			std::cout << "time :" << duration_cast<milliseconds>(t).count() << std::endl;
		}
	}

	{
		auto s = high_resolution_clock::now();
		for (auto num : { 1,2,4,6,8 }) {
			atomic_sum = 0;
			std::vector<std::thread> threads;
			for (int i = 0; i < num; ++i) {
				threads.emplace_back(atomic_add, num);
			}
			for (auto& t : threads)t.join();

			std::cout << "Thread num = " << num << " ";
			std::cout << "atomic Multi thread Sum = " << atomic_sum << std::endl;
			auto t = high_resolution_clock::now() - s;
			std::cout << "time :" << duration_cast<milliseconds>(t).count() << std::endl;
		}
	}
	
}