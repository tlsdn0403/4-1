#include <iostream>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
#include <queue>

constexpr int MAX_THREADS = 16;
constexpr int NUM_TEST = 400'0000;
constexpr int RANGE = 1000;



class NODE {
public:
	int data;
	NODE* next;
	bool removed = false; // Flag to indicate if the node is removed
	std::mutex mtx; // Mutex for thread safety
	NODE(int value) : data(value), next(nullptr) {}
	void lock() { mtx.lock(); }
	void unlock() { mtx.unlock(); }
};

class MEMORY_POOL {
private:
	std::queue<NODE*> get_pool;
	std::queue<NODE*> free_pool;
public:
	MEMORY_POOL()
	{
		//for (int i = 0; i < NUM_TEST / 3; ++i) {
		//	get_pool.push(new NODE(0));
		//}
	}
	~MEMORY_POOL() {
		while (!get_pool.empty()) {
			delete get_pool.front();
			get_pool.pop();
		}
		while (!free_pool.empty()) {
			delete free_pool.front();
			free_pool.pop();
		}
	}

	NODE* get_node(int value) {
		if (get_pool.empty()) {
			return new NODE(value);
		}
		else {
			NODE* node = get_pool.front();
			get_pool.pop();
			node->data = value;
			node->next = nullptr;
			node->removed = false;
			return node;
		}
	}
	void free_node(NODE* node) {
		free_pool.push(node);
	}
	void recycle_nodes() {
		get_pool = std::move(free_pool);
	}
};

MEMORY_POOL memory_pool[MAX_THREADS];
thread_local int thread_id = 999;

class DUMMY_MUTEX {
public:
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
		std::cout << "Testing Course Grain Synchronization List\n";
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
			mtx.unlock(); // Unlock the mutex before returning
			return false; // Element already exists
		}
		else {
			NODE* new_node = memory_pool[thread_id].get_node(x);
			pred->next = new_node;
			new_node->next = curr;
			mtx.unlock(); // Unlock the mutex after modifying the list
			return true; // Element added successfully
		}
	}

	bool Remove(int x)
	{

		mtx.lock(); // Lock the mutex to ensure thread safety
		NODE* pred = head;
		NODE* curr = pred->next;
		while (curr->data < x) {
			pred = curr;
			curr = curr->next;
		}

		if (curr->data != x) {
			mtx.unlock(); // Unlock the mutex before returning
			return false; // Element already exists
		}
		else {
			pred->next = curr->next;
			memory_pool[thread_id].free_node(curr); // Recycle the removed node back to the memory pool
			mtx.unlock(); // Unlock the mutex after modifying the list
			return true; // Element added successfully
		}
	}

	bool Contains(int x)
	{

		mtx.lock(); // Lock the mutex to ensure thread safety
		NODE* pred = head;
		NODE* curr = pred->next;
		while (curr->data < x) {
			pred = curr;
			curr = curr->next;
		}

		if (curr->data == x) {
			mtx.unlock(); // Unlock the mutex before returning
			return true; // Element already exists
		}
		else {
			mtx.unlock(); // Unlock the mutex after modifying the list
			return false; // Element added successfully
		}
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
	NODE* head, * tail;
public:
	FLIST()
	{
		std::cout << "Testing Fine Grain Synchronization List\n";
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
			pred->unlock(); curr->unlock(); // Unlock the mutex before returning
			return false; // Element already exists
		}
		else {
			NODE* new_node = new NODE{ x };
			new_node->next = curr;
			pred->next = new_node;
			pred->unlock(); curr->unlock(); // Unlock the mutex after modifying the list
			return true; // Element added successfully
		}
	}

	bool Remove(int x)
	{
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

		if (curr->data != x) {
			pred->unlock(); curr->unlock(); // Unlock the mutex before returning
			return false; // Element already exists
		}
		else {
			pred->next = curr->next;
			pred->unlock(); curr->unlock(); // Unlock the mutex after modifying the list
			delete curr;
			return true; // Element added successfully
		}
	}

	bool Contains(int x)
	{
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
			pred->unlock(); curr->unlock(); // Unlock the mutex before returning
			return true; // Element already exists
		}
		else {
			pred->unlock(); curr->unlock(); // Unlock the mutex after modifying the list
			return false; // Element added successfully
		}
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

class OLIST {
private:
	NODE* head, * tail;
public:
	OLIST()
	{
		std::cout << "Testing Optimistic Synchronization List\n";
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

	bool validate(NODE* pred, NODE* curr)
	{
		NODE* node = head;
		while (node->data <= pred->data) {
			if (node == pred) {
				return pred->next == curr; // Check if pred still points to curr
			}
			node = node->next;
		}
		return false; // Validation failed
	}

	bool Add(int x)
	{
		while (true) {
			NODE* pred = head;
			NODE* curr = pred->next;
			while (curr->data < x) {
				pred = curr;
				curr = curr->next;
			}

			pred->lock(); 	curr->lock();
			if (false == validate(pred, curr)) {
				pred->unlock(); curr->unlock(); // Unlock the mutex before retrying
				continue;
			}

			if (curr->data == x) {
				pred->unlock(); curr->unlock(); // Unlock the mutex before returning
				return false; // Element already exists
			}
			else {
				NODE* new_node = memory_pool[thread_id].get_node(x);
				new_node->next = curr;
				pred->next = new_node;
				pred->unlock(); curr->unlock(); // Unlock the mutex after modifying the list
				return true; // Element added successfully
			}
		}
	}

	bool Remove(int x)
	{
		while (true) {
			NODE* pred = head;
			NODE* curr = pred->next;
			while (curr->data < x) {
				pred = curr;
				curr = curr->next;
			}

			pred->lock(); 	curr->lock();
			if (false == validate(pred, curr)) {
				pred->unlock(); curr->unlock(); // Unlock the mutex before retrying
				continue;
			}
			if (curr->data != x) {
				pred->unlock(); curr->unlock(); // Unlock the mutex before returning
				return false; // Element already exists
			}
			else {
				pred->next = curr->next;
				pred->unlock(); curr->unlock(); // Unlock the mutex after modifying the list
				memory_pool[thread_id].free_node(curr); // Recycle the removed node back to the memory pool
				return true; // Element added successfully
			}
		}
	}

	bool Contains(int x)
	{
		while (true) {
			NODE* pred = head;
			NODE* curr = pred->next;
			while (curr->data < x) {
				pred = curr;
				curr = curr->next;
			}

			pred->lock(); 	curr->lock();
			if (false == validate(pred, curr)) {
				pred->unlock(); curr->unlock(); // Unlock the mutex before retrying
				continue;
			}

			if (curr->data == x) {
				pred->unlock(); curr->unlock(); // Unlock the mutex before returning
				return true; // Element already exists
			}
			else {
				pred->unlock(); curr->unlock(); // Unlock the mutex after modifying the list
				return false; // Element added successfully
			}
		}
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

class ZLIST {
private:
	NODE* head, * tail;
public:
	ZLIST()
	{
		std::cout << "Testing Optimistic Synchronization List\n";
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

	bool validate(NODE* pred, NODE* curr)
	{
		return (!pred->removed) && (!curr->removed)
			&& (pred->next == curr); // Check if pred still points to curr and both nodes are not removed
	}

	bool Add(int x)
	{
		NODE* new_node = memory_pool[thread_id].get_node(x);
		while (true) {
			NODE* pred = head;
			NODE* curr = pred->next;
			while (curr->data < x) {
				pred = curr;
				curr = curr->next;
			}

			pred->lock(); 	curr->lock();
			if (false == validate(pred, curr)) {
				pred->unlock(); curr->unlock(); // Unlock the mutex before retrying
				continue;
			}

			if (curr->data == x) {
				pred->unlock(); curr->unlock(); // Unlock the mutex before returning
				memory_pool[thread_id].free_node(new_node); // Recycle the unused node back to the memory pool
				return false; // Element already exists
			}
			else {
				new_node->next = curr;
				pred->next = new_node;
				pred->unlock(); curr->unlock(); // Unlock the mutex after modifying the list
				return true; // Element added successfully
			}
		}
	}

	bool Remove(int x)
	{
		while (true) {
			NODE* pred = head;
			NODE* curr = pred->next;
			while (curr->data < x) {
				pred = curr;
				curr = curr->next;
			}

			pred->lock(); 	curr->lock();
			if (false == validate(pred, curr)) {
				pred->unlock(); curr->unlock(); // Unlock the mutex before retrying
				continue;
			}
			if (curr->data != x) {
				pred->unlock(); curr->unlock(); // Unlock the mutex before returning
				return false; // Element already exists
			}
			else {
				curr->removed = true; // Mark the node as removed
				pred->next = curr->next;
				pred->unlock(); curr->unlock(); // Unlock the mutex after modifying the list
				memory_pool[thread_id].free_node(curr); // Recycle the removed node back to the memory pool
				return true; // Element added successfully
			}
		}
	}

	bool Contains(int x)
	{
		NODE* n = head;
		while (n->data < x) {
			n = n->next;
		}
		return (n->data == x) && (!n->removed); // Check if the node exists and is not removed
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

class NODE_SP {
public:
	int data;
	std::shared_ptr<NODE_SP> next;
	bool removed = false; // Flag to indicate if the node is removed
	std::mutex mtx; // Mutex for thread safety
	NODE_SP(int value) : data(value), next(nullptr) {}
	void lock() { mtx.lock(); }
	void unlock() { mtx.unlock(); }
};

class ZLIST_SP {
private:
	std::shared_ptr<NODE_SP> head, tail;
public:
	ZLIST_SP()
	{
		std::cout << "Testing Optimistic Synchronization List\n";
		head = std::make_shared<NODE_SP>(std::numeric_limits<int>::min());
		tail = std::make_shared<NODE_SP>(std::numeric_limits<int>::max());
		head->next = tail;
	}

	void clear()
	{
		head->next = tail; // Reset the list to its initial state
	}

	bool validate(const std::shared_ptr<NODE_SP>& pred,
		const std::shared_ptr<NODE_SP>& curr)
	{
		return (!pred->removed) && (!curr->removed)
			&& (pred->next == curr); // Check if pred still points to curr and both nodes are not removed
	}

	bool Add(int x)
	{
		std::shared_ptr<NODE_SP> new_node = std::make_shared<NODE_SP>(x);
		while (true) {
			std::shared_ptr<NODE_SP> pred = head;
			std::shared_ptr<NODE_SP> curr = pred->next;
			while (curr->data < x) {
				pred = curr;
				curr = curr->next;
			}

			pred->lock(); 	curr->lock();
			if (false == validate(pred, curr)) {
				pred->unlock(); curr->unlock(); // Unlock the mutex before retrying
				continue;
			}

			if (curr->data == x) {
				pred->unlock(); curr->unlock(); // Unlock the mutex before returning
				return false; // Element already exists
			}
			else {
				new_node->next = curr;
				pred->next = new_node;
				pred->unlock(); curr->unlock(); // Unlock the mutex after modifying the list
				return true; // Element added successfully
			}
		}
	}

	bool Remove(int x)
	{
		while (true) {
			std::shared_ptr<NODE_SP> pred = head;
			std::shared_ptr<NODE_SP> curr = pred->next;
			while (curr->data < x) {
				pred = curr;
				curr = curr->next;
			}

			pred->lock(); 	curr->lock();
			if (false == validate(pred, curr)) {
				pred->unlock(); curr->unlock(); // Unlock the mutex before retrying
				continue;
			}
			if (curr->data != x) {
				pred->unlock(); curr->unlock(); // Unlock the mutex before returning
				return false; // Element already exists
			}
			else {
				curr->removed = true; // Mark the node as removed
				pred->next = curr->next;
				pred->unlock(); curr->unlock(); // Unlock the mutex after modifying the list
				return true; // Element added successfully
			}
		}
	}

	bool Contains(int x)
	{
		std::shared_ptr<NODE_SP> n = head;
		while (n->data < x) {
			n = n->next;
		}
		return (n->data == x) && (!n->removed); // Check if the node exists and is not removed
	}

	void print20()
	{
		std::shared_ptr<NODE_SP> curr = head->next;
		int count = 0;
		while (curr != tail && count < 20) {
			std::cout << curr->data << ", ";
			curr = curr->next;
			count++;
		}
		std::cout << "\n";
	}
};

class NODE_ASP {
public:
	int data;
	std::atomic<std::shared_ptr<NODE_ASP>> next;
	bool removed = false; // Flag to indicate if the node is removed
	std::mutex mtx; // Mutex for thread safety
	NODE_ASP(int value) : data(value), next(nullptr) {}
	void lock() { mtx.lock(); }
	void unlock() { mtx.unlock(); }
};

class ZLIST_ASP {
private:
	std::atomic<std::shared_ptr<NODE_ASP>> head, tail;
public:
	ZLIST_ASP()
	{
		std::cout << "Testing Optimistic Synchronization List\n";
		head = std::make_shared<NODE_ASP>(std::numeric_limits<int>::min());
		tail = std::make_shared<NODE_ASP>(std::numeric_limits<int>::max());
		head.load()->next = tail.load();
	}

	void clear()
	{
		head.load()->next = tail.load(); // Reset the list to its initial state
	}

	bool validate(const std::shared_ptr<NODE_ASP>& pred,
		const std::shared_ptr<NODE_ASP>& curr)
	{
		return (!pred->removed) && (!curr->removed)
			&& (pred->next.load() == curr); // Check if pred still points to curr and both nodes are not removed
	}

	bool Add(int x)
	{
		std::shared_ptr<NODE_ASP> new_node = std::make_shared<NODE_ASP>(x);
		while (true) {
			std::shared_ptr<NODE_ASP> pred = head;
			std::shared_ptr<NODE_ASP> curr = pred->next;
			while (curr->data < x) {
				pred = curr;
				curr = curr->next;
			}

			pred->lock(); 	curr->lock();
			if (false == validate(pred, curr)) {
				pred->unlock(); curr->unlock(); // Unlock the mutex before retrying
				continue;
			}

			if (curr->data == x) {
				pred->unlock(); curr->unlock(); // Unlock the mutex before returning
				return false; // Element already exists
			}
			else {
				new_node->next = curr;
				pred->next = new_node;
				pred->unlock(); curr->unlock(); // Unlock the mutex after modifying the list
				return true; // Element added successfully
			}
		}
	}

	bool Remove(int x)
	{
		while (true) {
			std::shared_ptr<NODE_ASP> pred = head;
			std::shared_ptr<NODE_ASP> curr = pred->next;
			while (curr->data < x) {
				pred = curr;
				curr = curr->next;
			}

			pred->lock(); 	curr->lock();
			if (false == validate(pred, curr)) {
				pred->unlock(); curr->unlock(); // Unlock the mutex before retrying
				continue;
			}
			if (curr->data != x) {
				pred->unlock(); curr->unlock(); // Unlock the mutex before returning
				return false; // Element already exists
			}
			else {
				curr->removed = true; // Mark the node as removed
				pred->next = curr->next.load();
				pred->unlock(); curr->unlock(); // Unlock the mutex after modifying the list
				return true; // Element added successfully
			}
		}
	}

	bool Contains(int x)
	{
		std::shared_ptr<NODE_ASP> n = head;
		while (n->data < x) {
			n = n->next;
		}
		return (n->data == x) && (!n->removed); // Check if the node exists and is not removed
	}

	void print20()
	{
		std::shared_ptr<NODE_ASP> curr = head.load()->next;
		int count = 0;
		while (curr != tail.load() && count < 20) {
			std::cout << curr->data << ", ";
			curr = curr->next;
			count++;
		}
		std::cout << "\n";
	}
};

class LFNODE {
	// atomic longlong을 사용하여 포인터와 마크 비트를 함께 저장하는 구조체
	std::atomic<long long> next;
	
public:
	int data;
	long long epoch; // EBR을 위한 에폭 정보
	LFNODE(int value) : data(value), next(0) {}
	void set_next(LFNODE* next_node) {
		next = reinterpret_cast<long long>(next_node);
	}

	/*FNODE* get_next() {
		return reinterpret_cast<LFNODE*>(next.load());
	}
	LFNODE* get_next(bool* removed) {
		long long temp = next.load();
		*removed = (temp & 1) == 1; // Check if the least significant bit is set (marked as removed)
		return reinterpret_cast<LFNODE*>(temp);
	}*/
	LFNODE* get_next() {
		// 뒤에 마킹 값을 제거하고 줘야지 주소값을 똑바로준다
		long long temp = next.load();
		return reinterpret_cast<LFNODE*>(temp - (temp % 2));
	}

	LFNODE* get_next(bool* removed) {
		long long temp = next.load();
		*removed = (temp & 1) == 1;
		return reinterpret_cast<LFNODE*>(temp - (temp % 2));
	}
	bool get_mark() {
		return (next.load() & 1) == 1; // Check if the least significant bit is set (marked as removed)
	}
	// next가 가르키길 기대하는 노드 , 바꾸고싶은 새 노드, 기대하는 removed 상태 , 바꾸고싶은 새 removed 상태
	bool CAS(LFNODE* expected_node, LFNODE* new_node,
		bool expected_removed, bool new_removed)
	{
		// 최하위 비트에 expected_remove를 붙힘
		long long expected_value = reinterpret_cast<long long>(expected_node) | (expected_removed ? 1 : 0);
		long long new_value = reinterpret_cast<long long>(new_node) | (new_removed ? 1 : 0);
		//현재 next가 기대값과 같으면 새 값으로 원자적으로 변경한다
		return next.compare_exchange_strong(expected_value, new_value);
	}
};
class LF_MEMORY_POOL {
private:
	std::queue<LFNODE*> get_pool;
	std::queue<LFNODE*> free_pool;
public:
	LF_MEMORY_POOL()
	{
		//for (int i = 0; i < NUM_TEST / 3; ++i) {
		//	get_pool.push(new NODE(0));
		//}
	}
	~LF_MEMORY_POOL() {
		while (!get_pool.empty()) {
			delete get_pool.front();
			get_pool.pop();
		}
		while (!free_pool.empty()) {
			delete free_pool.front();
			free_pool.pop();
		}
	}

	LFNODE* get_node(int value) {
		if (get_pool.empty()) {
			return new LFNODE(value);
		}
		else {
			LFNODE* node = get_pool.front();
			get_pool.pop();
			node->data = value;
			node->set_next(nullptr);
			return node;
		}
	}
	void free_node(LFNODE* node) {
		free_pool.push(node);
	}
	void recycle_nodes() {
		get_pool = std::move(free_pool);
	}
};

LF_MEMORY_POOL lf_memory_pool[MAX_THREADS];

class EBR {
	// 읽을 때 제대로된 값이 읽혀야 해서 아토믹으로
	alignas(64) std::atomic<long long> g_epoch = 0; //글로벌 에폭 시간 관리가 된다.

	class ThreadInfo {
	public:
		alignas(64) std::atomic<long long> local_epoch;
		std::queue<LFNODE*> free_nodes;
		ThreadInfo() {
			local_epoch = std::numeric_limits<long long>::max(); // 초기값은 무한대로 설정하여 아직 진입하지 않았음을 나타냄
		}
		~ThreadInfo()
		{
			while(!free_nodes.empty()) {
				delete free_nodes.front();
				free_nodes.pop();
			}
		}
	};
	ThreadInfo thread_info[MAX_THREADS];


	// 사진에서 회색공간 빈 공간은 무슨 값이 되어야 할까? 특별한 시간 0 넣어도 되지만 +무한대를 넣는것이 낫다.
	// 0으로 해두면 크기비교할 때 문제가 될 수 있다/

	public:
	void enter() {
		thread_info[thread_id].local_epoch = ++g_epoch; // 현재 글로벌 에폭을 로컬 에폭으로 설정하여 진입 시점을 기록
	}
	void leave() {
		thread_info[thread_id].local_epoch = std::numeric_limits<long long>::max(); // 진입하지 않았음을 나타내는 무한대로 설정
	}
	void freenode(LFNODE* node) {
		node->epoch = g_epoch; // 노드에 현재 에폭을 기록
		thread_info[thread_id].free_nodes.push(node); // 노드를 프리 노드 큐에 추가
	}
	LFNODE* get_node(int x) {
		if(this->thread_info[thread_id].free_nodes.empty()) {
			return new LFNODE(x);
		}
		else {
			LFNODE* node = thread_info[thread_id].free_nodes.front();
			long long current_epch = g_epoch;
			for (int i = 0; i < MAX_THREADS; ++i) {
				if (thread_info[i].local_epoch <= node->epoch) {
					return new LFNODE(x);
				}
			}
			thread_info[thread_id].free_nodes.pop();
			node->data = x;
			node->set_next(nullptr);
			return node; // Return a node that can be safely reused
		}
	}
};

EBR EBR_memory_pool[MAX_THREADS];

class LFLIST {
private:
	LFNODE* head, * tail;
public:
	LFLIST()
	{
		std::cout << "Testing Lock Free Synchronization List\n";
		head = new LFNODE{ std::numeric_limits<int>::min() };
		tail = new LFNODE{ std::numeric_limits<int>::max() };
		head->set_next(tail);
	}

	~LFLIST() {
		clear();
		delete head;
		delete tail;
	}

	void clear()
	{
		LFNODE* current = head->get_next();
		while (head->get_next() != tail) {
			LFNODE* temp = head->get_next();
			head->set_next(temp->get_next());
			delete temp;
		}
	}

	void find(int x, LFNODE*& pred, LFNODE*& curr)
	{
		pred = head;
		curr = pred->get_next();
		while (true) {
			// Check if curr is marked as removed
			bool removed = false;
			while (true) {
				LFNODE* succ = curr->get_next(&removed); //next 노드와 removed인지 상태도 같이 가져옴
				if (false == removed) break; // If curr is not removed, break the inner loop
				pred->CAS(curr, succ, false, false);
				curr = succ;
			}
			if (curr->data >= x) break;
			pred = curr;
			curr = curr->get_next();
		}
	}

	bool Add(int x)
	{
		LFNODE* pred, * curr;
		while (true) {
			// 들어갈 위치를 찾음
			find(x, pred, curr);
			// 같은 값이 있으면 실패
			if (curr->data == x) return false; // Element already exists
			else {
				// 새 노드를 만듦
				LFNODE* new_node = lf_memory_pool[thread_id].get_node(x);
				// 새 노드의 next를 current로 설정
				new_node->set_next(curr);
				//pred->next가 아직도 curr이고 mark도 false라면 pred->next를 new_node로 바꿔라
				if (true == pred->CAS(curr, new_node, false, false))
					return true; // Attempt to link the new node between pred and curr
				lf_memory_pool[thread_id].free_node(new_node); // Recycle the unused node back to the memory pool
				// 다시 시도
			}
		}
	}

	bool Remove(int x)
	{
		LFNODE* pred, * curr;
		while (true) {
			// 들어갈 위치를 찾음
			find(x, pred, curr);
			// 삭제할 노드 없으면 실패
			if (curr->data != x) return false;
			bool removed = false;
			LFNODE* succ = curr->get_next(&removed);
			// 삭제하려는 값을 어떤놈이 지웠다. 다시해보자
			if (true == removed) continue;

			bool snip = curr->CAS(succ, succ, false, true);// 마킹 값만 TRUE로 바꾸자
			if (false == snip)
				continue;

			if (pred->CAS(curr, succ, false, false)) {
				//curr 를 succ으로 바꾸고 지우기
				lf_memory_pool[thread_id].free_node(curr); // Recycle the removed node back to the memory pool
			}
			//실패해도 그냥 쓰레기 남겨놓은 채로 return을 하자
			return true;
		}
	}

	bool Contains(int x)
	{
		bool removed = false;
		LFNODE* curr = head;

		while (curr->data < x) {
			curr = curr->get_next();          // curr = curr.next.getReference()
			curr->get_next(&removed);         // curr.next.get(marked)
		}

		curr->get_next(&removed);
		return (curr->data == x) && !removed;
	}

	void print20()
	{
		LFNODE* curr = head->get_next();
		int count = 0;
		while (curr != tail && count < 20) {
			std::cout << curr->data << ", ";
			curr = curr->get_next();
			count++;
		}
		std::cout << "\n";
	}
};

class LFEBRLIST {
private:
	LFNODE* head, * tail;
public:
	LFEBRLIST()
	{
		std::cout << "Testing Lock Free Synchronization List\n";
		head = new LFNODE{ std::numeric_limits<int>::min() };
		tail = new LFNODE{ std::numeric_limits<int>::max() };
		head->set_next(tail);
	}

	~LFEBRLIST() {
		clear();
		delete head;
		delete tail;
	}

	void clear()
	{
		LFNODE* current = head->get_next();
		while (head->get_next() != tail) {
			LFNODE* temp = head->get_next();
			head->set_next(temp->get_next());
			delete temp;
		}
	}

	void find(int x, LFNODE*& pred, LFNODE*& curr)
	{
		pred = head;
		curr = pred->get_next();
		while (true) {
			// Check if curr is marked as removed
			bool removed = false;
			while (true) {
				LFNODE* succ = curr->get_next(&removed); //next 노드와 removed인지 상태도 같이 가져옴
				if (false == removed) break; // If curr is not removed, break the inner loop
				pred->CAS(curr, succ, false, false);
				curr = succ;
			}
			if (curr->data >= x) break;
			pred = curr;
			curr = curr->get_next();
		}
	}

	bool Add(int x)
	{
		LFNODE* pred, * curr;
		while (true) {
			// 들어갈 위치를 찾음
			find(x, pred, curr);
			// 같은 값이 있으면 실패
			if (curr->data == x) return false; // Element already exists
			else {
				// 새 노드를 만듦
				LFNODE* new_node = EBR_memory_pool[thread_id].get_node(x);
				// 새 노드의 next를 current로 설정
				new_node->set_next(curr);
				//pred->next가 아직도 curr이고 mark도 false라면 pred->next를 new_node로 바꿔라
				if (true == pred->CAS(curr, new_node, false, false))
					return true; // Attempt to link the new node between pred and curr
				EBR_memory_pool[thread_id].freenode(new_node); // Recycle the unused node back to the memory pool
				// 다시 시도
			}
		}
	}

	bool Remove(int x)
	{
		LFNODE* pred, * curr;
		while (true) {
			// 들어갈 위치를 찾음
			find(x, pred, curr);
			// 삭제할 노드 없으면 실패
			if (curr->data != x) return false;
			bool removed = false;
			LFNODE* succ = curr->get_next(&removed);
			// 삭제하려는 값을 어떤놈이 지웠다. 다시해보자
			if (true == removed) continue;

			bool snip = curr->CAS(succ, succ, false, true);// 마킹 값만 TRUE로 바꾸자
			if (false == snip)
				continue;

			if (pred->CAS(curr, succ, false, false)) {
				//curr 를 succ으로 바꾸고 지우기
				EBR_memory_pool[thread_id].freenode(curr); // Recycle the removed node back to the memory pool
			}
			//실패해도 그냥 쓰레기 남겨놓은 채로 return을 하자
			return true;
		}
	}

	bool Contains(int x)
	{
		bool removed = false;
		LFNODE* curr = head;

		while (curr->data < x) {
			curr = curr->get_next();          // curr = curr.next.getReference()
			curr->get_next(&removed);         // curr.next.get(marked)
		}

		curr->get_next(&removed);
		return (curr->data == x) && !removed;
	}

	void print20()
	{
		LFNODE* curr = head->get_next();
		int count = 0;
		while (curr != tail && count < 20) {
			std::cout << curr->data << ", ";
			curr = curr->get_next();
			count++;
		}
		std::cout << "\n";
	}
};



LFEBRLIST my_set;

#include <array>

class HISTORY {
public:
	int op;
	int i_value;
	bool o_value;
	HISTORY(int o, int i, bool re) : op(o), i_value(i), o_value(re) {}
};

std::array<std::vector<HISTORY>, MAX_THREADS> history;

void check_history(int num_threads)
{
	std::array <int, RANGE> survive = {};
	std::cout << "Checking Consistency : ";
	if (history[0].size() == 0) {
		std::cout << "No history.\n";
		return;
	}
	for (int i = 0; i < num_threads; ++i) {
		for (auto& op : history[i]) {
			if (false == op.o_value) continue;
			if (op.op == 3) continue;
			if (op.op == 0) survive[op.i_value]++;
			if (op.op == 1) survive[op.i_value]--;
		}
	}
	for (int i = 0; i < RANGE; ++i) {
		int val = survive[i];
		if (val < 0) {
			std::cout << "ERROR. The value " << i << " removed while it is not in the set.\n";
			exit(-1);
		}
		else if (val > 1) {
			std::cout << "ERROR. The value " << i << " is added while the set already have it.\n";
			exit(-1);
		}
		else if (val == 0) {
			if (my_set.Contains(i)) {
				std::cout << "ERROR. The value " << i << " should not exists.\n";
				exit(-1);
			}
		}
		else if (val == 1) {
			if (false == my_set.Contains(i)) {
				std::cout << "ERROR. The value " << i << " shoud exists.\n";
				exit(-1);
			}
		}
	}
	std::cout << " OK\n";
}

void benchmark_check(int num_threads, int th_id)
{
	thread_id = th_id;
	for (int i = 0; i < NUM_TEST / num_threads; ++i) {
		int op = rand() % 3;
		switch (op) {
		case 0: {
			int v = rand() % RANGE;
			history[th_id].emplace_back(0, v, my_set.Add(v));
			break;
		}
		case 1: {
			int v = rand() % RANGE;
			history[th_id].emplace_back(1, v, my_set.Remove(v));
			break;
		}
		case 2: {
			int v = rand() % RANGE;
			history[th_id].emplace_back(2, v, my_set.Contains(v));
			break;
		}
		}
	}
	memory_pool[thread_id].recycle_nodes();
}
void benchmark(int num_threads, int tid)
{
	thread_id = tid;
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
	memory_pool[thread_id].recycle_nodes(); // Recycle nodes back to the memory pool after the benchmark
}

int main()
{
	using namespace std::chrono;

	std::cout << "Strting Error Check.\n";
	for (int num_threads = 1; num_threads <= MAX_THREADS; num_threads *= 2) {
		std::vector<std::thread> threads;
		for (auto& h : history) h.clear();
		auto start_time = high_resolution_clock::now();
		for (int j = 0; j < num_threads; ++j) {
			threads.emplace_back(benchmark_check, num_threads, j);
		}
		for (auto& thread : threads) {
			thread.join();
		}
		auto end_time = high_resolution_clock::now();
		auto elapsed = end_time - start_time;
		auto exec_ms = duration_cast<milliseconds>(elapsed).count();
		my_set.print20();
		std::cout << "Threads: " << num_threads << ", Time: " << exec_ms << " seconds\n";
		check_history(num_threads);
		my_set.clear();
	}

	std::cout << "Strting Performance Check.\n";
	for (int num_threads = 1; num_threads <= MAX_THREADS; num_threads *= 2) {
		std::vector<std::thread> threads;
		auto start_time = high_resolution_clock::now();
		for (int j = 0; j < num_threads; ++j) {
			threads.emplace_back(benchmark, num_threads, j);
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
		std::string temp;
		std::getline(std::cin, temp);
	}
}