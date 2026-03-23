#include<iostream>	
#include<thread>
#include<mutex>
#include<chrono>
#include<vector>
#include<atomic>
#include<algorithm>



volatile int sum; // 실행속도 꼼수 부리지 마라
std::mutex mylock;

using namespace std::chrono;

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


 std::vector<std::atomic<bool>> a_flag;
 std::vector<std::atomic<int>> a_label;

void atomic_b_lock(int threadID ,int threadNum){
	a_flag[threadID] = true;
	int maxNum = 0;
	for (int i = 0; i < threadNum; ++i) {
		// 내 대기표는 가장큰 대기표 + 1
		int currentNum = a_label[i];
		maxNum = std::max(currentNum, maxNum);
	}
	a_label[threadID] = maxNum +1 ;
	for (int i = 0; i < threadNum; ++i) {
		if (i == threadID)
			continue;
		// i가 대기표를 가지고 있고 , 대기표의 번호가 나보다 작거나, 만약에 같다면 , 나의 쓰레드 아이디가 더 크다면 기다리자.
		while (a_flag[i] &&(a_label[i] < a_label[threadID] ||(a_label[i] == a_label[threadID] && i < threadID))) {
			// 기다림
		}
	}
}
void atomic_b_unlock(int threadID) {
	a_flag[threadID] = false;
}

void atomic_bakeryAdd(int num ,int threadID) {
	auto loop = 5000'0000 / num;
	volatile int localSum = 0;
	for (auto i = 0; i < loop; ++i)
	{
		localSum = localSum + 2;
	}
	atomic_b_lock(threadID, num);
	sum = sum + localSum;
	atomic_b_unlock(threadID);
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
	{

		for (auto num : { 1,2,4,8 }) {
			auto s = high_resolution_clock::now();
			sum = 0;
			std::vector<std::thread> threads;
			for (int i = 0; i < num; ++i) {
				threads.emplace_back(mutexAdd ,num); // 인자 제거
			}
			for (auto& t : threads)t.join();

			std::cout << "Thread num = " << num << " ";
			std::cout << "Mutex thread Sum = " << sum << std::endl;
			auto t = high_resolution_clock::now() - s;
			std::cout << "time :" << duration_cast<milliseconds>(t).count() << std::endl;
		}
	}

	{

		for (auto num : { 1,2,4,8 }) {
			auto s = high_resolution_clock::now();
			sum = 0;
			std::vector<std::thread> threads;
			a_flag = std::vector<std::atomic<bool>>(num);
			a_label = std::vector<std::atomic<int>>(num );

			for (int i = 0; i < num; ++i) {
				threads.emplace_back(atomic_bakeryAdd , num ,i); // 인자 제거
			}
			for (auto& t : threads)t.join();

			std::cout << "Thread num = " << num << " ";
			std::cout << "Bakery thread Sum = " << sum << std::endl;
			auto t = high_resolution_clock::now() - s;
			std::cout << "time :" << duration_cast<milliseconds>(t).count() << std::endl;
		}
	}



}