#include<iostream>	
#include<thread>

int a{};
void func1()
{
	for (int i = 0; i < 10; i++)a += i;

}

int main()
{
	std::thread t1(func1);
	std::thread t2(func1);
	func1();
	t1.join();
	t2.join();
	std::cout << a << std::endl;
	return 0;
}