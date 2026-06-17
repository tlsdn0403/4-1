# 고급 멀티쓰레드 프로그래밍 기말 O/X 모의문제

기말 범위 중심. 맞으면 O, 틀리면 X. 족보 스타일처럼 틀리면 감점이 있다고 생각하고 애매한 문장은 비우는 연습을 권장한다.

영어 용어는 가능한 한 `영어(한글 뜻)` 형태로 같이 적었다.

## 문제

### 1. Consensus object(합의 객체), Consensus number(합의수), Universality(만능성)

1. Consensus object(합의 객체)의 `decide()`는 모든 호출에 대해 같은 값을 반환해야 한다. ( )
2. Consensus object(합의 객체)가 반환하는 값은 반드시 호출자들이 제안한 값 중 하나여야 한다. ( )
3. mutex(상호배제 잠금)로 구현한 consensus(합의)는 항상 wait-free(무대기) consensus object(합의 객체)이다. ( )
4. CAS 하나를 이용하면 여러 스레드 중 최초로 성공한 제안을 선택하는 consensus(합의) 구현이 가능하다. ( )
5. atomic read/write register(원자적 읽기/쓰기 레지스터)의 consensus number(합의수)는 무한대이다. ( )
6. FIFO queue(선입선출 큐)의 consensus number(합의수)는 2로 설명된다. ( )
7. CAS는 무한대의 consensus number(합의수)를 갖는 동기화 연산으로 설명된다. ( )
8. Universal construction(만능 구성)에서 Log(로그)는 method invocation(메서드 호출)들의 순서를 저장한다. ( )
9. Universal construction(만능 구성)의 각 노드는 consensus object(합의 객체)를 가져 다음 노드를 하나로 합의하게 할 수 있다. ( )
10. 순차 객체가 deterministic(결정적)하지 않아도 Universal construction(만능 구성)에서 항상 같은 결과를 보장한다. ( )

### 2. ABA problem(ABA 문제), EBR(에폭 기반 메모리 회수), 메모리 재사용

11. ABA 문제는 queue(큐)에서만 발생하고 stack/list(스택/리스트)에서는 발생하지 않는다. ( )
12. ABA는 값이 A에서 B로 바뀌었다가 다시 A가 되어 CAS가 중간 변화를 감지하지 못하는 문제이다. ( )
13. 포인터와 stamp(스탬프, 버전값)를 함께 저장하면 ABA 문제를 완화할 수 있다. ( )
14. stamped pointer(스탬프 포인터)에서는 포인터 값이 바뀔 때 stamp(스탬프)도 함께 바뀌어야 한다. ( )
15. 128bit stamped pointer(128비트 스탬프 포인터)를 쓰면 모든 load/store(읽기/쓰기)가 atomic(원자적)일 필요가 없어진다. ( )
16. `atomic<shared_ptr<T>>`(원자적 shared_ptr)는 참조 카운트 때문에 노드 재사용 문제를 완화할 수 있지만 성능 문제가 있을 수 있다. ( )
17. 강의자료에서는 `atomic<shared_ptr<T>>`(원자적 shared_ptr)가 내부적으로 lock(잠금)을 써서 lock-free(무잠금)가 아닐 수 있다고 설명한다. ( )
18. EBR(Epoch Based Reclamation, 에폭 기반 메모리 회수)은 제거된 노드를 즉시 delete하지 않고 안전해질 때까지 보관하는 방식이다. ( )
19. EBR(에폭 기반 메모리 회수)에서 method(메서드) 진입 시 스레드의 local epoch(지역 에폭)를 활성 상태로 표시하고, 종료 시 비활성 값으로 바꾼다. ( )
20. retired node(회수 대기 노드)의 epoch(에폭)가 모든 활성 스레드의 local epoch(지역 에폭)보다 오래된 경우 재사용 가능하다고 볼 수 있다. ( )

### 3. Lock-free Queue(무잠금 큐)

21. Lock-free queue(무잠금 큐)의 enqueue(삽입)는 `tail->next`에 새 노드를 CAS로 연결하려고 시도한다. ( )
22. enqueue(삽입)에서 새 노드 연결에 성공한 뒤 `tail` 갱신은 반드시 같은 스레드만 수행해야 한다. ( )
23. 어떤 스레드가 `tail` 갱신 전에 멈추더라도 다른 스레드가 `tail` 전진을 도울 수 있어야 non-blocking(비멈춤) 성질에 가깝다. ( )
24. enqueue(삽입)에서 `last != tail`이면 관찰한 tail 정보가 낡았으므로 다시 읽는 것이 자연스럽다. ( )
25. enqueue(삽입)에서 `next != nullptr`이면 tail이 뒤처진 상태일 수 있으므로 `CAS(&tail, last, next)`를 시도할 수 있다. ( )
26. dequeue(제거)에서 `head == tail`이고 `next != nullptr`이면 tail 전진을 도와야 할 수 있다. ( )
27. dequeue(제거)에서 `next == nullptr`이면 queue(큐)가 빈 상태라고 판단할 수 있다. ( )
28. lock-free queue(무잠금 큐)에서 `delete first`를 즉시 해도 다른 스레드가 그 노드를 절대 참조하지 않으므로 안전하다. ( )
29. queue(큐)의 ABA 문제는 노드 재사용과 관련이 있다. ( )
30. 강의자료의 lock-free queue(무잠금 큐)는 완전히 정리되지 않은 중간 상태를 허용하고, 다른 연산이 이를 도와 완성할 수 있게 한다. ( )

### 4. Lock-free Stack(무잠금 스택), Backoff(백오프), Elimination(소거)

31. Lock-free stack(무잠금 스택)의 push(삽입)는 새 노드의 next를 old top(기존 top)으로 두고 top을 CAS로 바꾼다. ( )
32. Lock-free stack(무잠금 스택)의 pop(제거)은 old top(기존 top)의 next를 new top(새 top)으로 삼아 top을 CAS로 바꾼다. ( )
33. Lock-free stack(무잠금 스택)은 top 하나에 CAS가 몰리므로 contention(경쟁)이 생길 수 있다. ( )
34. Backoff(백오프)는 CAS 실패 후 잠시 기다려 충돌 확률을 줄이는 기법이다. ( )
35. backoff loop(백오프 루프)에서 매번 공유 메모리를 읽으면 bus/cache(버스/캐시) 부담이 줄어든다. ( )
36. x86의 `_mm_pause()`는 spin-wait(스핀 대기) 중 CPU 부담을 낮추는 데 사용될 수 있다. ( )
37. Elimination(소거)은 push와 pop이 만나면 stack(스택)에 접근하지 않고 값을 직접 교환하게 하는 아이디어이다. ( )
38. EliminationArray(소거 배열)의 range(범위)는 경쟁 정도에 따라 조절될 수 있다. ( )
39. push와 push가 만나도 서로를 정상적으로 소거했다고 볼 수 있다. ( )
40. EliminationBackoffStack(소거 백오프 스택)은 부하가 높을수록 성공적인 소거가 늘어 확장성이 좋아질 가능성이 있다. ( )

### 5. SkipList(스킵리스트)

41. SkipList(스킵리스트)는 평균적으로 linked list(연결 리스트)보다 검색 시간이 짧아질 수 있다. ( )
42. 병행 SkipList(스킵리스트)에서는 Add(추가) 중 0레벨은 연결되었지만 윗레벨은 아직 연결되지 않은 중간 상태가 생길 수 있다. ( )
43. `fullyLinked == false`인 노드는 아직 완전히 추가되었다고 보면 안 된다. ( )
44. Remove(삭제)에서 `marked/removed`는 논리적 삭제 상태를 나타낸다. ( )
45. Lazy SkipList(게으른 동기화 스킵리스트)의 Add(추가)는 모든 레벨 연결이 끝난 후 `fullyLinked`를 true로 만든다. ( )
46. Lazy SkipList(게으른 동기화 스킵리스트)의 Remove(삭제)는 victim(삭제 대상 노드)을 먼저 mark(마킹)하고 이후 링크를 실제로 제거할 수 있다. ( )
47. SkipList(스킵리스트) Remove(삭제)에서 위 레벨 링크 제거와 아래 레벨 링크 제거 순서는 오동작과 관계가 없다. ( )
48. Lock-free SkipList(무잠금 스킵리스트)에서는 모든 next에 mark bit(마크 비트)를 합성해서 사용할 수 있다. ( )
49. Lock-free SkipList(무잠금 스킵리스트)의 Find(검색)는 marked link(마킹된 링크)를 만나면 CAS로 물리적 제거를 도울 수 있다. ( )
50. Lock-free SkipList(무잠금 스킵리스트)에서 0레벨의 존재 여부와 mark(마킹) 여부는 원소가 집합에 존재하는지 판단하는 핵심 기준이 될 수 있다. ( )

### 6. OpenMP(오픈MP), TBB(스레딩 빌딩 블록), CUDA(쿠다), Transactional Memory(트랜잭션 메모리)

51. OpenMP(오픈MP)는 컴파일러 directive(지시문)와 함수, 변수로 구성된 병렬 프로그래밍 API이다. ( )
52. OpenMP(오픈MP)는 기존 코드를 자동으로 분석해 안전한 부분만 알아서 병렬화한다. ( )
53. OpenMP(오픈MP) `for`는 loop-carried dependency(루프 반복 간 의존성)를 프로그래머 대신 자동으로 검증한다. ( )
54. `#pragma omp critical`과 `#pragma omp atomic`은 모두 data race(데이터 레이스)를 줄이는 데 사용할 수 있다. ( )
55. TBB(Threading Building Blocks, 스레딩 빌딩 블록) `parallel_for`를 쓰려면 작업 범위를 TBB가 나눌 수 있는 형태로 표현해야 한다. ( )
56. TBB `concurrent_hash_map`은 원소 접근에 accessor(접근자)를 사용하는 방식으로 설명된다. ( )
57. TBB `concurrent_queue`의 `try_pop()`은 실패 가능성을 반환하는 형태이다. ( )
58. CUDA(쿠다)는 NVIDIA의 GPGPU 프로그래밍 모델로, host(호스트)와 device(디바이스) 메모리 구분이 등장한다. ( )
59. Transactional Memory(트랜잭션 메모리)는 여러 메모리 연산으로 이루어진 코드 구간을 atomic(원자적)하게 보이도록 하려는 모델이다. ( )
60. HTM(Hardware Transactional Memory, 하드웨어 트랜잭션 메모리)은 hardware(하드웨어) 용량 한계와 conflict(충돌) 때문에 transaction(트랜잭션)이 abort(중단)될 수 있다. ( )

## 정답

1 O, 2 O, 3 X, 4 O, 5 X, 6 O, 7 O, 8 O, 9 O, 10 X

11 X, 12 O, 13 O, 14 O, 15 X, 16 O, 17 O, 18 O, 19 O, 20 O

21 O, 22 X, 23 O, 24 O, 25 O, 26 O, 27 O, 28 X, 29 O, 30 O

31 O, 32 O, 33 O, 34 O, 35 X, 36 O, 37 O, 38 O, 39 X, 40 O

41 O, 42 O, 43 O, 44 O, 45 O, 46 O, 47 X, 48 O, 49 O, 50 O

51 O, 52 X, 53 X, 54 O, 55 O, 56 O, 57 O, 58 O, 59 O, 60 O

## 헷갈리기 쉬운 오답 포인트

- ABA는 queue(큐) 전용 문제가 아니라 CAS로 포인터를 바꾸는 lock-free stack/list/free-list(무잠금 스택/리스트/프리 리스트)에서도 생긴다.
- `sum = sum + 2`는 atomic(원자적) 변수라도 load(읽기)와 store(쓰기)가 분리될 수 있어 `sum += 2`와 다르다.
- fence(펜스)는 순서 제어이지, 일반 변수 data race(데이터 레이스)를 자동으로 없애는 도구가 아니다.
- lock-free(무잠금)는 전체 진행 보장이지 각 스레드의 starvation(기아) 없음 보장이 아니다.
- TBB concurrent container(병행 컨테이너)도 모든 메서드가 무조건 안전한 것은 아니며, 문서/강의에서 unsafe method(안전하지 않은 메서드)가 따로 나온다.
