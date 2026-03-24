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

volatile int array_sum[8];// 각 스레드마다 지역변수로 합을 구해서 마지막에 한번만 락을 걸어서 더하는 방법


void array_add(int num_thread ,int thread_Id) {
	auto loop = 5000'0000 / num_thread;
	volatile int local_sum = 0;
	for (auto i = 0; i < loop; ++i)
	{
		local_sum += 2;
	}
	array_sum[thread_Id] = local_sum;

}

bool CAS(volatile int* ptr, int expected, int desired) {
	
	return std::atomic_compare_exchange_strong(
		reinterpret_cast<volatile std::atomic<int>*>(ptr),
		&expected,
		desired
	);	
}
volatile int LOCK = 0; // 0 = unlock , 1 = 어떤 쓰레드가 락 얻음


void CAS_LOCK()
{
	// 딴쓰레드가 락을 얻었으면 기다는거죠 
	// 락을 얻은 쓰레드가 언락 할 때까지 기다림??
	// 여기서 발생하는 데이터 레이스를 cas를 사용해서 업애줘야 한다. 여기를 아토믹하게 바꾸어 주어야 한다.
	 while (1 == LOCK); LOCK = 1; 
}
void CAS_UNLOCK()
{
	LOCK = 0;
}


void add(int num_thread) {
	auto loop = 5000'0000 / num_thread;
	for (auto i = 0; i < loop; ++i)
	{

		CAS_LOCK();
		sum = sum + 2;
		CAS_UNLOCK();
	}
}

void atomic_add(int num_thread) {
	auto loop = 5000'0000 / num_thread;
	for (auto i = 0; i < loop; ++i)
	{
		atomic_sum += 2;
	}
}
void optimal_add(int num_thread) {

	auto loop = 5000'0000 / num_thread;
	volatile int local_sum = 0;
	for (auto i = 0; i < loop; ++i)
	{
		local_sum += 2;
	}
	mylock.lock();
	sum += local_sum;
	mylock.unlock();
}
int main()
{

	{
		std::cout << "시작" << std::endl;
		auto start = high_resolution_clock::now();
		for (auto i = 0; i < 5000'0000; ++i) sum = sum + 2;
		std::cout << "Single thread Sum = " << sum << std::endl;
		auto end = high_resolution_clock::now() - start;
		std::cout << "time :" << duration_cast<milliseconds>(end).count() << std::endl;
	}
	{
		
		for (auto num : { 1,2,4,6,8 }) {
			auto s = high_resolution_clock::now();
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

	
}