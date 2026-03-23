#include<iostream>
#include<thread>

volatile int* bound;
volatile bool done = false;

void thread1() {
	for (int i = 0; i < 10000000; ++i) {
		*bound = -(1 + *bound);
	}
	done = true;
}

void spy() {
	int error = 0;	
	while (!done) {
		// 릴리즈 모드에선 value에 들어있는 값이 디버깅에서 옳게 들어간 게 아닐 수 있다. 디버그 모드로 돌려라
		// 디버깅을 해봐도 value의 값이 65535 나오는데 , bound는 0 , -1 이 나온다 어떻게 된걸까?
		// 멀티코어 cpu에서 발생하는 error이다.

		int value = *bound; // 공유변수를 여러 번 나눠서 읽으면 안된다.
		if ((value != 0) && (value != -1)) {
			++error;
		}
		
	}
	std::cout << "Memory Error: "<< error << std::endl;
}	

int main() {
	int ARR[32];   //128 바이트
	int* p = &ARR[31];  //빈 공간의 나머지 원소에 들어가게 되면 캐시라인이 64바이트이므로 32개의 int가 들어갈 수 있다. 그래서 31번째 원소에 주소를 넣어주면 나머지 원소는 빈 공간이 된다.
	long long temp = reinterpret_cast<long long>(p);
	long long remainder = temp % 64;

	temp = temp - remainder; // 주소가 들어있는데 나머지만큼 주소가 줄어들겠죠. , temp는 나머지 원소의 살짝 앞에있는 주소를 가르키게 된다.
	temp = temp - 2;
	bound = reinterpret_cast<int *>(temp);  // 바운드가 가르키는 주소는 ARR안에 있다.
	*bound = 0;

	std::thread t1(thread1);
	std::thread t2(spy);
	t1.join();
	t2.join();
}	