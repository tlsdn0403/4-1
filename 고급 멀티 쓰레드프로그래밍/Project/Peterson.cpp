#include<iostream>	
#include<thread>
#include<mutex>
#include<chrono>
#include<vector>
#include<atomic>




volatile int sum; // 실행속도 꼼수 부리지 마라
std::mutex mylock;

using namespace std::chrono;


void add() {
	auto loop = 5000'0000 / 2;
	for (auto i = 0; i < loop; ++i)
	{

		mylock.lock();
		sum = sum + 2;
		mylock.unlock();
	}
}

//std::atomic<int>  victim = 2;
//std::atomic<bool> flag[2]{ false,false };
volatile int victim = 2;
volatile bool flag[2]{ false,false };

void p_lock(int thread_id) {
	int other = 1 - thread_id;
	flag[thread_id] = true;
	victim = thread_id;
	std::atomic_thread_fence(std::memory_order_seq_cst); // 메모리 배리어
	while (flag[other] && victim == thread_id);
}
void p_unlock(int thread_id) {
	flag[thread_id] = false;
}
void Peterson_add(int thread_id) {

	auto loop = 5000'0000 / 2;

	for (auto i = 0; i < loop; ++i)
	{
		p_lock(thread_id);
		sum =sum+ 2;
		p_unlock(thread_id);
	}
	

}
int main()
{

	{
		std::cout << "Start" << std::endl;
		auto start = high_resolution_clock::now();
		for (auto i = 0; i < 5000'0000; ++i) sum = sum + 2;
		std::cout << "Single thread Sum = " << sum << std::endl;
		auto end = high_resolution_clock::now() - start;
		std::cout << "time :" << duration_cast<milliseconds>(end).count() << std::endl;
	}
	{

		for (auto num : { 2 }) {
			auto s = high_resolution_clock::now();
			sum = 0;
			std::vector<std::thread> threads;
			for (int i = 0; i < num; ++i) {
				threads.emplace_back(add); // 인자 제거
			}
			for (auto& t : threads)t.join();

			std::cout << "Thread num = " << num << " ";
			std::cout << "Multi thread Sum = " << sum << std::endl;
			auto t = high_resolution_clock::now() - s;
			std::cout << "time :" << duration_cast<milliseconds>(t).count() << std::endl;
		}
	}


	{

		for (auto num : { 2 }) {
			auto s = high_resolution_clock::now();
			sum = 0;
			std::vector<std::thread> threads;
			for (int i = 0; i < num; ++i) {
				threads.emplace_back(Peterson_add, i);
			}
			for (auto& t : threads)t.join();

			std::cout << "Thread num = " << num << " ";
			std::cout << "Peterson thread Sum = " << sum << std::endl;
			auto t = high_resolution_clock::now() - s;
			std::cout << "time :" << duration_cast<milliseconds>(t).count() << std::endl;
		}
	}


}