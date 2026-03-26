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


void add(int num) {
	auto loop = 5000'0000 / num;
	for (auto i = 0; i < loop; ++i) {
		sum = sum + 2;
	}
}

void mutexAdd(int num) {
	auto loop = 5000'0000 / num;
	for (auto i = 0; i < loop; ++i)
	{

		mylock.lock();
		sum = sum + 2;
		mylock.unlock();
	}
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
	// 여기서 발생하는 데이터 레이스를 cas를 사용해서 없애줘야 한다. 여기를 아토믹하게 바꾸어 주어야 한다.
	// lock 의 값이 0이면 1로 바꿔주고 true 리턴 아니면 false
	while (!CAS(&LOCK, 0, 1)) {

	}
}
void CAS_UNLOCK()
{
	CAS(&LOCK, 1, 0);  //이것도 해주는 게 완벽
}


void CAS_add(int num_thread) {
	auto loop = 5000'0000 / num_thread;
	for (auto i = 0; i < loop; ++i)
	{

		CAS_LOCK();
		sum = sum + 2;
		CAS_UNLOCK();
	}
}

void mutex_add(int num_thread) {

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

// ------------------------- volatile 빵집 --------------------------
volatile int v_flag[8] = {};
volatile int v_label[8] = {};

void volatile_b_lock(int threadID, int threadNum) {
	v_flag[threadID] = true;
	int maxNum = 0;
	for (int i = 0; i < threadNum; ++i) {
		// 내 대기표는 가장큰 대기표 + 1
		int currentNum = v_label[i];
		maxNum = std::max(currentNum, maxNum);
	}
	v_label[threadID] = maxNum + 1;
	for (int i = 0; i < threadNum; ++i) {
		if (i == threadID)
			continue;
		// i가 대기표를 가지고 있고 , 대기표의 번호가 나보다 작거나, 만약에 같다면 , 나의 쓰레드 아이디가 더 크다면 기다리자.
		while (v_flag[i] && (v_label[i] < v_label[threadID] || (v_label[i] == v_label[threadID] && i < threadID))) {
			// 기다림
		}
	}
}

void volatile_b_unlock(int threadID) {
	v_flag[threadID] = false;
}

void volatile_bakeryAdd(int num, int threadID) {
	auto loop = 5000'0000 / num;

	for (auto i = 0; i < loop; ++i)
	{
		volatile_b_lock(threadID, num);
		sum = sum + 2;
		volatile_b_unlock(threadID);
	}

}


// ------------------------- 아토믹 빵집 --------------------------
std::vector<std::atomic<bool>> a_flag;
std::vector<std::atomic<int>> a_label;

void atomic_b_lock(int threadID, int threadNum) {
	a_flag[threadID] = true;
	int maxNum = 0;
	for (int i = 0; i < threadNum; ++i) {
		// 내 대기표는 가장큰 대기표 + 1
		int currentNum = a_label[i];
		maxNum = std::max(currentNum, maxNum);
	}
	a_label[threadID] = maxNum + 1;
	for (int i = 0; i < threadNum; ++i) {
		if (i == threadID)
			continue;
		// i가 대기표를 가지고 있고 , 대기표의 번호가 나보다 작거나, 만약에 같다면 , 나의 쓰레드 아이디가 더 크다면 기다리자.
		while (a_flag[i] && (a_label[i] < a_label[threadID] || (a_label[i] == a_label[threadID] && i < threadID))) {
			// 기다림
		}
	}
}
void atomic_b_unlock(int threadID) {
	a_flag[threadID] = false;
}

void atomic_bakeryAdd(int num, int threadID) {
	auto loop = 5000'0000 / num;

	for (auto i = 0; i < loop; ++i)
	{
		atomic_b_lock(threadID, num);
		atomic_sum = atomic_sum + 2;
		atomic_b_unlock(threadID);
	}
}

int main()
{

	{
		for (auto num : { 1,2,4,8 }) {
			auto s = high_resolution_clock::now();
			sum = 0;
			std::vector<std::thread> threads;
			for (int i = 0; i < num; ++i) {
				threads.emplace_back(add, num); // 인자 제거
			}
			for (auto& t : threads)t.join();

			std::cout << "Thread num = " << num << " ";
			std::cout << "Normal thread Sum = " << sum << std::endl;
			auto t = high_resolution_clock::now() - s;
			std::cout << "time :" << duration_cast<milliseconds>(t).count() << std::endl;
		}
	}
	//{

	//	for (auto num : { 1,2,4,8 }) {
	//		auto s = high_resolution_clock::now();
	//		sum = 0;
	//		std::vector<std::thread> threads;
	//		for (int i = 0; i < num; ++i) {
	//			threads.emplace_back(mutexAdd, num); // 인자 제거
	//		}
	//		for (auto& t : threads)t.join();

	//		std::cout << "Thread num = " << num << " ";
	//		std::cout << "Mutex thread Sum = " << sum << std::endl;
	//		auto t = high_resolution_clock::now() - s;
	//		std::cout << "time :" << duration_cast<milliseconds>(t).count() << std::endl;
	//	}
	//}

	//{

	//	for (auto num : { 1,2,4,8 }) {
	//		auto s = high_resolution_clock::now();
	//		sum = 0;
	//		std::vector<std::thread> threads;;
	//		for (int i = 0; i < num; ++i) {
	//			threads.emplace_back(volatile_bakeryAdd, num, i); // 인자 제거
	//		}
	//		for (auto& t : threads)t.join();

	//		std::cout << "Thread num = " << num << " ";
	//		std::cout << "volatile Bakery thread Sum = " << sum << std::endl;
	//		auto t = high_resolution_clock::now() - s;
	//		std::cout << "time :" << duration_cast<milliseconds>(t).count() << std::endl;
	//	}
	//}

	//{

	//	for (auto num : { 1,2,4,8 }) {
	//		auto s = high_resolution_clock::now();
	//		atomic_sum = 0;
	//		std::vector<std::thread> threads;
	//		a_flag = std::vector<std::atomic<bool>>(num);
	//		a_label = std::vector<std::atomic<int>>(num);

	//		for (int i = 0; i < num; ++i) {
	//			threads.emplace_back(atomic_bakeryAdd, num, i); // 인자 제거
	//		}
	//		for (auto& t : threads)t.join();

	//		std::cout << "Thread num = " << num << " ";
	//		std::cout << "Atomic Bakery thread Sum = " << atomic_sum << std::endl;
	//		auto t = high_resolution_clock::now() - s;
	//		std::cout << "time :" << duration_cast<milliseconds>(t).count() << std::endl;
	//	}
	//}
	{

		for (auto num : { 1,2,4,8 }) {
			auto s = high_resolution_clock::now();
			sum = 0;
			std::vector<std::thread> threads;
			for (int i = 0; i < num; ++i) {
				threads.emplace_back(CAS_add, num);
			}
			for (auto& t : threads)t.join();

			std::cout << "Thread num = " << num << " ";
			std::cout << "CAS thread Sum = " << sum << std::endl;
			auto t = high_resolution_clock::now() - s;
			std::cout << "time :" << duration_cast<milliseconds>(t).count() << std::endl;
		}
	}
}