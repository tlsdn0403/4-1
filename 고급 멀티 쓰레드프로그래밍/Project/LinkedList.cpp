#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>

class NODE {
public:
	int data;
	NODE* next;
	std::mutex mtx; // Mutex for fine-grained locking
	NODE(int value) : data(value), next(nullptr) {}

	void lock() {
		mtx.lock();
	}
	void unlock() {
		mtx.unlock();
	}
};

class DUMMY_MUTEX {
	private:
		void lock() {}
		void unlock() {}
};

class CLIST {
private:
	NODE* head, * tail;
	std::mutex mtx; // Mutex for thread safety
public:
	CLIST()
	{
		head = new NODE{ std::numeric_limits<int>::min() };
		tail = new NODE{ std::numeric_limits<int>::max() };
		head->next = tail;
	}

	void clear()
	{
		NODE* current = head->next;
		while (head->next != tail) {
			NODE* temp = head->next;
			head->next = temp->next;
			delete temp;
		}
	}

	bool Add(int x)
	{
		mtx.lock(); // Lock the mutex to ensure thread safety
		NODE* pred = head;
		NODE* curr = pred->next;

		while (curr->data < x) {
			pred = curr;
			curr = curr->next;
		}
		
		if (curr->data == x) {
			mtx.unlock();
			return false;
		}
		else {
			NODE* new_node = new NODE{ x };
			pred->next = new_node;
			new_node->next = curr;
			mtx.unlock(); 
			return true; 
		}
	}

	bool Remove(int x)
	{
		mtx.lock();

		NODE* pred = head;
		NODE* curr = pred->next;

		while (curr != tail) {
			// 찾았다면
			if (curr->data == x) {
				pred->next = curr->next;
				delete curr;
				mtx.unlock();
				return true;
			}
			pred = curr;
			curr = curr->next;
		}

		mtx.unlock();
		return false;
	}

	bool Contains(int x)
	{
		mtx.lock();

		NODE* pred = head;
		NODE* curr = pred->next;

		while (curr != tail) {
			if (curr->data == x)
			{
				mtx.unlock();
				return true;
			}
		
		}
		mtx.unlock();
		return false;
	}

	void print20()
	{
		NODE* curr = head->next;
		int count = 0;
		while (curr != tail && count < 20) {
			std::cout << curr->data << ", ";
			curr = curr->next;
			count++;
		}
		std::cout << "\n";
	}
};

class FLIST {
private:
	NODE* head;
	NODE* tail;

public:
	FLIST() {
		head = new NODE{ std::numeric_limits<int>::min() };
		tail = new NODE{ std::numeric_limits<int>::max() };
		head->next = tail;
	}

	~FLIST() {
		clear();
	}

	void clear() {
		while (head->next != tail) {
			NODE* temp = head->next;
			head->next = temp->next;
			delete temp;
		}
	}

	bool Add(int x) {
		head->lock();
		NODE* pred = head;
		NODE* curr = pred->next;
		curr->lock();

		while (curr->data < x) {
			pred->unlock();
			pred = curr;
			curr = curr->next;
			curr->lock();
		}
		if (curr->data == x) {
			curr->unlock();
			pred->unlock();
			return false;
		}
		else {
			NODE* new_node = new NODE{ x };
			pred->next = new_node;
			new_node->next = curr;
			curr->unlock();
			pred->unlock();
			return true;
		}
		
	}

	bool Remove(int x) {
		head->lock();
		NODE* pred = head;
		NODE* curr = pred->next;
		curr->lock();

		while (curr->data < x) {
			pred->unlock();
			pred = curr;
			curr = curr->next;
			curr->lock();

		}

		if (curr->data == x) {
			pred->next = curr->next;
			curr->unlock();
			pred->unlock();
			// 언락을 하고 딜리트 해야한다.
			delete curr;
			return true;
		}

		curr->unlock();
		pred->unlock();
		return false;
	}

	bool Contains(int x) {
		
		head->lock();
		NODE* pred = head;
		NODE* curr = pred->next;
		curr->lock();

		while (curr->data < x) {
			pred->unlock();
			pred = curr;
			curr = curr->next;
			curr->lock();

		}

		if (curr->data == x) {
			curr->unlock();
			pred->unlock();
			return true;
		}

		curr->unlock();
		pred->unlock();
		return false;
	}

	void print20() {
		NODE* curr = head->next;
		int count = 0;
		while (curr != tail && count < 20) {
			std::cout << curr->data << ", ";
			curr = curr->next;
			count++;
		}
		std::cout << "\n";
	}
};

class OLIST {
private:
	NODE* head;
	NODE* tail;

public:
	OLIST() {
		head = new NODE{ std::numeric_limits<int>::min() };
		tail = new NODE{ std::numeric_limits<int>::max() };
		head->next = tail;
	}


	void clear() {
		while (head->next != tail) {
			NODE* temp = head->next;
			head->next = temp->next;
			delete temp;
		}
	}

	bool Add(int x) {

		NODE* pred = head;
		NODE* curr = pred->next;


		while (curr->data < x) {

			pred = curr;
			curr = curr->next;
		}
		pred->lock();
		curr->lock();
		if (curr->data == x) {
			curr->unlock();
			pred->unlock();
			return false;
		}
		else {
			NODE* new_node = new NODE{ x };
			pred->next = new_node;
			new_node->next = curr;
			curr->unlock();
			pred->unlock();
			return true;
		}

	}

	bool Remove(int x) {

		NODE* pred = head;
		NODE* curr = pred->next;


		while (curr->data < x) {

			pred = curr;
			curr = curr->next;


		}
		pred->lock();
		curr->lock();

		if (curr->data == x) {
			pred->next = curr->next;
			curr->unlock();
			pred->unlock();
			// 언락을 하고 딜리트 해야한다.
			delete curr;
			return true;
		}

		curr->unlock();
		pred->unlock();
		return false;
	}

	bool Contains(int x) {


		NODE* pred = head;
		NODE* curr = pred->next;

		while (curr->data < x) {

			pred = curr;
			curr = curr->next;


		}

		pred->lock();
		curr->lock();
		if (curr->data == x) {
			curr->unlock();
			pred->unlock();
			return true;
		}

		curr->unlock();
		pred->unlock();
		return false;
	}

	void print20() {
		NODE* curr = head->next;
		int count = 0;
		while (curr != tail && count < 20) {
			std::cout << curr->data << ", ";
			curr = curr->next;
			count++;
		}
		std::cout << "\n";
	}
};
constexpr int MAX_THREADS = 16;
constexpr int NUM_TEST = 400'0000;

OLIST my_set;

void benchmark(int num_threads)
{
	const int LOOP = NUM_TEST / num_threads;
	for (int i = 0; i < LOOP; ++i) {
		int value = rand() % 1000;
		int op = rand() % 3;
		switch (op) {
		case 0:
			my_set.Add(value);
			break;
		case 1:
			my_set.Remove(value);
			break;
		case 2:
			my_set.Contains(value);
			break;
		}
	}
}

int main()
{
	using namespace std::chrono;
	for (int num_threads = 1; num_threads <= MAX_THREADS; num_threads *= 2) {
		std::vector<std::thread> threads;
		auto start_time = high_resolution_clock::now();
		for (int j = 0; j < num_threads; ++j) {
			threads.emplace_back(benchmark, num_threads);
		}
		for (auto& thread : threads) {
			thread.join();
		}
		auto end_time = high_resolution_clock::now();
		auto elapsed = end_time - start_time;
		auto exec_ms = duration_cast<milliseconds>(elapsed).count();
		my_set.print20();
		std::cout << "Threads: " << num_threads << ", Time: " << exec_ms << " seconds\n";
		my_set.clear();
	}
}