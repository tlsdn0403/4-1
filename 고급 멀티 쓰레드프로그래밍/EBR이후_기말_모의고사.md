# EBR 이후 기말 범위 모의고사

범위: EBR(Epoch Based Reclamation, 에폭 기반 메모리 회수) 이후를 중심으로, lock-free queue(무잠금 큐), ABA/stamped pointer(스탬프 포인터), lock-free stack(무잠금 스택), backoff(백오프), elimination(소거), skip list(스킵리스트), consensus/universal construction(합의/범용 구성), TBB/OpenMP/CUDA/Transactional Memory(트랜잭션 메모리)를 포함한다.

정답과 해설은 맨 아래에 모아 두었다.

## 문제

### 1. O/X

맞으면 O, 틀리면 X를 쓰시오. 틀리면 감점이 있다고 가정한다.

1. EBR(Epoch Based Reclamation, 에폭 기반 메모리 회수)는 삭제된 노드를 즉시 `delete`하지 않고, 모든 활성 스레드가 해당 노드를 더 이상 볼 수 없다고 판단될 때 재사용한다. ( )
2. EBR에서 어떤 스레드가 method(메서드)에 진입한 뒤 local epoch(지역 에폭)를 갱신하지 않고 오래 멈추면, 다른 스레드의 노드 재사용이 지연될 수 있다. ( )
3. stamped pointer(스탬프 포인터)를 사용하면 ABA 문제뿐 아니라 delete된 노드 접근으로 인한 page fault(페이지 폴트) 문제도 자동으로 사라진다. ( )
4. free-list(해제 리스트)에 삭제 노드를 넣는 것은 C library가 메모리 페이지를 OS에 반환해 page fault가 나는 위험을 줄이는 데 도움이 된다. ( )
5. free-list에 넣기만 하면 다른 스레드가 옛 주소를 들고 있어도 언제든 즉시 새 노드로 재사용해도 안전하다. ( )
6. ABA 문제는 lock-free queue(무잠금 큐)에서만 발생하고 lock-free stack(무잠금 스택)에서는 발생하지 않는다. ( )
7. CAS(compare-and-swap, 비교 후 교환) 대상 포인터가 A에서 B로 바뀌었다가 다시 A로 돌아오면, stamp(스탬프)가 없는 CAS는 중간 변화를 감지하지 못할 수 있다. ( )
8. stamped pointer에서 포인터 값은 같아도 stamp 값이 다르면 CAS는 실패해야 한다. ( )

9. lock-free queue(무잠금 큐)의 enqueue(삽입)에서 `tail->next` CAS가 성공하면 새 노드는 이미 큐에 연결된 것이다. ( )
10. enqueue에서 `tail->next` CAS 성공 후 `tail` 갱신 CAS가 실패하면 enqueue 자체도 실패한 것이므로 처음부터 다시 해야 한다. ( )
11. enqueue에서 `tail->next != nullptr`이면 현재 `tail`은 실제 꼬리보다 뒤처진 상태라고 볼 수 있다. ( )
12. enqueue에서 다른 스레드가 미처 `tail`을 전진시키지 못한 상태를 발견하면, 현재 스레드가 CAS로 `tail`을 `next`로 밀어 줄 수 있다. ( )
13. lock-free queue에서 helping(도와주기)을 허용하지 않으면, `tail->next` 연결 후 멈춘 스레드 때문에 다른 스레드가 모두 기다리는 blocking(멈춤 가능) 상황이 생길 수 있다. ( )
14. dequeue(삭제)에서 제거된 노드를 즉시 `delete`해도, CAS가 atomic(원자적)이므로 다른 스레드가 그 노드에 접근하는 문제는 생기지 않는다. ( )
15. lock-free queue의 dummy node(더미 노드)는 head/tail 경계 상황을 단순화하는 데 도움이 된다. ( )
16. CAS 실패는 항상 현재 스레드의 연산이 아무 진전 없이 낭비되었다는 뜻이며, 다른 스레드의 진행과는 무관하다. ( )

17. lock-free stack(무잠금 스택)의 push(삽입)는 새 노드의 `next`를 old top(기존 top)으로 두고 top을 새 노드로 CAS한다. ( )
18. lock-free stack의 pop(삭제)은 old top을 읽은 뒤 old top의 next를 new top(새 top)으로 삼아 top을 CAS한다. ( )
19. lock-free stack에서 top 하나에 CAS가 몰리면 contention(경쟁)이 커져 성능이 나빠질 수 있다. ( )
20. backoff(백오프)는 CAS 실패 후 잠시 기다려 충돌을 줄일 수 있지만, 너무 오래 기다리면 임계 구간이 비어 있어도 진입이 늦어질 수 있다. ( )
21. elimination(소거)은 push와 pop이 만나면 central stack(중앙 스택)에 접근하지 않고 값을 직접 교환하게 하는 기법이다. ( )
22. push와 push가 만나면 서로 값을 교환해 두 연산을 소거할 수 있다. ( )
23. elimination array(소거 배열)의 range(범위)는 경쟁 정도에 따라 조절될 수 있다. ( )
24. 경쟁이 낮은 상황에서는 elimination을 시도하는 비용이 오히려 손해가 될 수 있다. ( )

25. 병행 skip list(스킵리스트)에서는 한 노드가 여러 level(레벨)의 link(링크)에 걸쳐 있으므로 add/remove 중간 상태가 linked list(연결 리스트)보다 복잡하다. ( )
26. `fullyLinked == false`인 노드는 모든 레벨 연결이 끝난 것이 아니므로 일반적으로 set(집합)에 존재한다고 판단하면 안 된다. ( )
27. `marked` 또는 `removed` 표시가 된 노드는 logical deletion(논리적 삭제)이 된 것으로 볼 수 있다. ( )
28. lock-free skip list의 find(검색)는 marked link(마킹된 링크)를 발견하면 물리적 제거를 도울 수 있다. ( )
29. skip list에서 remove는 보통 논리적 삭제 표시 없이 바로 모든 level link를 끊어도 항상 안전하다. ( )
30. skip list의 높은 level은 검색 속도를 높이기 위한 것이며, 실제 존재 여부 판단은 보통 lowest level(최하위 레벨)의 연결/마킹 상태와 밀접하다. ( )

31. atomic read/write register(원자적 읽기/쓰기 레지스터)의 consensus number(합의수)는 1이다. ( )
32. FIFO queue(선입선출 큐)의 consensus number(합의수)는 2로 설명된다. ( )
33. CAS의 consensus number(합의수)는 무한대이다. ( )
34. Universal construction(범용 구성)에서 log node(로그 노드)의 `invoc`에는 해당 노드가 수행할 method invocation(메서드 호출 정보)이 들어간다. ( )
35. Universal construction에서 각 node의 `decideNext`는 여러 후보 next node(다음 노드) 중 하나를 합의하기 위해 사용된다. ( )

36. TBB(Threading Building Blocks, 스레딩 빌딩 블록) `concurrent_queue`에서 `empty()`가 false였으면 바로 다음 `try_pop()`은 반드시 성공한다. ( )
37. TBB `concurrent_hash_map`의 `accessor`(접근자)를 오래 들고 있으면 다른 스레드의 접근 성능에 영향을 줄 수 있다. ( )
38. OpenMP(오픈MP) `parallel for`는 loop-carried dependency(반복 간 의존성)를 자동으로 제거해 주므로 공유 변수 갱신을 신경 쓰지 않아도 된다. ( )
39. CUDA(쿠다) 기본 프로그래밍 모델에서는 host(호스트) 메모리와 device(디바이스) 메모리가 구분되며, 보통 명시적인 복사가 필요하다. ( )
40. Transactional Memory(트랜잭션 메모리)는 충돌이 심하거나 transaction(트랜잭션)이 너무 크면 abort(중단)가 늘어 성능이 나빠질 수 있다. ( )

### 2. 단답형

41. EBR에서 제거된 노드를 즉시 `delete`하지 않는 이유를 2가지 쓰시오.

42. stamped pointer(스탬프 포인터)가 ABA를 막는 원리를 한 줄로 설명하시오.

43. stamped pointer를 써도 `delete` 문제가 남는 이유를 설명하시오.

44. lock-free queue(무잠금 큐)의 enqueue(삽입)에서 다른 스레드가 `tail`을 대신 전진시킬 수 있어야 하는 이유를 쓰시오.

45. lock-free stack(무잠금 스택)에서 elimination(소거)이 고경쟁 상황에서 성능을 높일 수 있는 이유를 쓰시오.

46. 병행 skip list(스킵리스트)에서 `fullyLinked`와 `marked/removed`가 각각 무엇을 의미하는지 쓰시오.

### 3. 코드 빈칸

47. 다음 lock-free queue enqueue 코드의 빈칸을 채우시오.

```cpp
void enq(int x)
{
    Node* e = new Node(x);
    while (true) {
        Node* last = tail;
        Node* next = last->next;
        if (last != tail) continue;

        if (next == nullptr) {
            if (CAS(&(last->next), ______A______, ______B______)) {
                CAS(&tail, ______C______, ______D______);
                return;
            }
        } else {
            CAS(&tail, ______E______, ______F______);
        }
    }
}
```

48. 다음 lock-free stack push/pop 코드의 빈칸을 채우시오.

```cpp
void push(int x)
{
    Node* n = new Node(x);
    while (true) {
        Node* old_top = top;
        n->next = ______A______;
        if (CAS(&top, ______B______, ______C______)) return;
    }
}

int pop()
{
    while (true) {
        Node* old_top = top;
        if (old_top == nullptr) return -1;
        Node* new_top = ______D______;
        if (CAS(&top, ______E______, ______F______)) {
            return ______G______;
        }
    }
}
```

49. 다음은 EBR의 매우 단순화된 형태이다. 빈칸을 채우시오.

```cpp
enter(tid):
    local_epoch[tid] = ______A______

leave(tid):
    local_epoch[tid] = ______B______

can_reuse(node):
    return node.retire_epoch ______C______ min(local_epoch[])
```

50. 다음 코드는 consensus object(합의 객체)를 이용하는 universal construction(범용 구성)의 로그 노드이다. 각 필드의 의미를 쓰시오.

```cpp
class NODE {
public:
    Invocation invoc;
    Consensus decideNext;
    NODE* next;
    volatile int seq;
};
```

## 정답 및 해설

### 1. O/X 정답

1 O, 2 O, 3 X, 4 O, 5 X, 6 X, 7 O, 8 O  
9 O, 10 X, 11 O, 12 O, 13 O, 14 X, 15 O, 16 X  
17 O, 18 O, 19 O, 20 O, 21 O, 22 X, 23 O, 24 O  
25 O, 26 O, 27 O, 28 O, 29 X, 30 O  
31 O, 32 O, 33 O, 34 O, 35 O  
36 X, 37 O, 38 X, 39 O, 40 O

### 2. 헷갈리는 O/X 해설

3. stamped pointer(스탬프 포인터)는 포인터가 A-B-A로 돌아오는 ABA는 막지만, 이미 delete된 노드를 다른 스레드가 역참조하는 use-after-free(해제 후 사용) 문제를 자동으로 막지는 못한다.

5. free-list(해제 리스트)에 넣는 것만으로 "즉시 재사용 안전"이 보장되지는 않는다. 안전한 재사용 시점은 EBR(에폭 기반 메모리 회수)이나 Hazard Pointer(해저드 포인터) 같은 방식으로 판단해야 한다.

10. `last->next` CAS가 성공하면 새 노드는 이미 큐에 연결되었으므로 enqueue 자체는 성공이다. `tail` 갱신 CAS는 실패해도 다른 스레드가 이미 밀어줬을 수 있으므로 반환해도 된다.

14. atomic CAS(원자적 비교 후 교환)는 포인터 변경의 원자성만 보장한다. 다른 스레드가 이미 읽어 둔 노드를 `delete`하면 use-after-free나 page fault가 생길 수 있다.

16. CAS 실패는 다른 스레드가 먼저 성공해 자료구조를 변경했다는 뜻일 수 있다. lock-free 알고리즘에서는 내 CAS 실패가 전체 시스템 관점의 진행을 의미할 수 있다.

22. elimination(소거)은 push와 pop처럼 서로 반대 의미의 연산이 만나야 가능하다. push-push는 둘 다 값을 넣으려는 연산이므로 서로 소거할 수 없다.

29. skip list(스킵리스트)는 여러 레벨 링크가 있으므로 먼저 logical deletion(논리적 삭제)을 표시하고, 이후 물리적 링크 제거를 진행하거나 도와주는 방식이 필요하다.

36. `empty()`와 `try_pop()` 사이에 다른 스레드가 원소를 가져갈 수 있으므로 `empty() == false`가 다음 `try_pop()` 성공을 보장하지 않는다.

38. OpenMP(오픈MP)는 반복문을 병렬 실행해 줄 뿐, 공유 변수 갱신의 data race(데이터 레이스)를 자동으로 올바르게 고쳐 주지 않는다. reduction(리덕션), atomic(원자적), critical(임계 구역) 등이 필요할 수 있다.

### 3. 단답형 정답

41. 다른 스레드가 삭제된 노드의 주소를 이미 읽어 들고 있을 수 있기 때문이다. 즉시 `delete`하면 use-after-free(해제 후 사용), page fault(페이지 폴트), ABA 관련 문제가 생길 수 있다.

42. 포인터와 함께 stamp/version(스탬프/버전)을 저장하고, 포인터가 바뀔 때마다 stamp도 증가시켜 A-B-A로 주소가 돌아와도 CAS가 변경 사실을 감지하게 한다.

43. stamp는 CAS 비교 대상의 변화는 감지하지만, 어떤 스레드가 이미 들고 있는 raw pointer(생 포인터)가 delete된 메모리를 가리키는 문제는 막지 못한다. 그래서 EBR, Hazard Pointer, 안전한 free-list 재사용이 필요하다.

44. 어떤 스레드가 `tail->next`에 새 노드를 연결한 뒤 `tail` 갱신 전에 멈추면 tail이 뒤처진 상태가 된다. 다른 스레드가 이를 기다리면 blocking이 되므로, 발견한 스레드가 `tail`을 `next`로 전진시켜 helping(도와주기)을 해야 한다.

45. 고경쟁 상황에서는 모든 push/pop이 top 하나에 CAS를 시도해 충돌한다. elimination은 push와 pop이 중앙 stack에 접근하지 않고 직접 값을 교환하게 해 top CAS 경쟁을 줄인다.

46. `fullyLinked`는 노드가 필요한 모든 레벨에 완전히 연결되었는지를 나타낸다. `marked/removed`는 논리적으로 삭제가 시작되었거나 삭제된 상태를 나타낸다.

### 4. 코드 빈칸 정답

47. A `nullptr`, B `e`, C `last`, D `e`, E `last`, F `next`

48. A `old_top`, B `old_top`, C `n`, D `old_top->next`, E `old_top`, F `new_top`, G `old_top->value` 또는 `old_top->data`

49. A `global_epoch` 또는 `++global_epoch`, B `INF` 또는 `numeric_limits<long long>::max()`, C `<`

50. `invoc`에는 로그에 기록할 메서드 호출 정보가 저장된다. `decideNext`는 여러 스레드가 제안한 다음 노드 후보 중 하나를 합의하기 위한 consensus object(합의 객체)이다. `next`는 실제 다음 로그 노드 포인터이다. `seq`는 로그에서의 순서 번호이다.
