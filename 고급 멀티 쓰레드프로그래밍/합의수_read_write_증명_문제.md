# Atomic Read/Write 합의수 증명형 문제

범위: `05-2 이론`의 consensus number(합의수), bivalent/univalent(양가/일가 상태), atomic read/write memory(원자적 읽기/쓰기 메모리) 증명.

정답과 해설은 맨 아래에 모아 두었다.

## 문제

1. Atomic read/write memory(원자적 읽기/쓰기 메모리)만으로 2-thread consensus(2개 스레드 합의)를 구현한다고 가정한다. 다음 그림에서 `S`는 critical state(임계상태)이다.

```text
        S  ← critical state(임계상태), bivalent(0/1 둘 다 가능)
       / \
 A.read  B.step
     /      \
 s'' : 0   s' : 1
```

`A.read`가 `S`를 0-valent(0-일가상태)로 바꾸는 결정적 step(단계)이 될 수 없는 이유를 쓰시오. 단, `B.step`은 read(읽기) 또는 write(쓰기)일 수 있다.

2. 다음 그림은 `A.read` 이후 B가 실행되는 경우와, `A.read` 없이 B만 실행되는 경우를 비교한 것이다.

```text
경로 1
S -- A.read --> s'' -- B.step --> s1

경로 2
S ------------ B.step ---------> s'
```

B가 `s1`과 `s'`를 구분할 수 없는 이유를 쓰시오.

3. 다음 상황에서 `A.write(x1)`와 `B.write(x2)`가 서로 다른 register(레지스터)에 대한 write(쓰기)라고 하자.

```text
        S
       / \
 A.write(x1)       B.write(x2)
      /                 \
 sA : 0              sB : 1

단, x1 != x2
```

다음 두 실행의 최종 메모리 상태가 같은 이유를 쓰시오.

```text
실행 1: S -> A.write(x1) -> B.write(x2)
실행 2: S -> B.write(x2) -> A.write(x1)
```

4. 3번 상황에서 두 실행의 최종 메모리 상태가 같다면, 왜 이것이 contradiction(모순)을 만드는지 쓰시오.

5. 다음 상황에서 `A.write(x1, v0)`와 `B.write(x1, v1)`는 같은 register(레지스터) `x1`에 대한 write(쓰기)이다.

```text
        S
       / \
 A.write(x1, v0)    B.write(x1, v1)
       /                  \
   sA : 0              sB : 1
```

다음 두 상태가 구별되지 않는 이유를 쓰시오.

```text
상태 1: S -> A.write(x1, v0) -> B.write(x1, v1)
상태 2: S -> B.write(x1, v1)
```

6. 5번에서 `상태 1`은 왜 0으로 결정되어야 하고, `상태 2`는 왜 1로 결정되어야 하는지 쓰시오.

7. 다음 문장의 빈칸을 채우시오.

```text
같은 register에 대한 두 write(쓰기)는 뒤의 write가 앞의 write를 ______A______.
따라서 A.write 후 B.write 상태는 ______B______만 수행한 상태와 구별되지 않는다.
그런데 한쪽은 0-valent, 다른 한쪽은 1-valent여야 하므로 ______C______이 생긴다.
```

8. 다음 O/X 문제에 답하시오.

```text
A. read(읽기)는 공유 메모리 값을 바꾸지 않으므로 임계상태를 일가상태로 바꾸는 결정적 step이 될 수 없다. ( )

B. 서로 다른 register에 대한 write들은 실행 순서를 바꾸면 최종 메모리 상태도 반드시 달라진다. ( )

C. 같은 register에 대한 두 write는 마지막 write만 남기 때문에 앞 write의 흔적이 사라질 수 있다. ( )

D. atomic read/write memory만으로는 2-thread wait-free consensus를 구현할 수 없다. ( )

E. atomic read/write memory의 consensus number(합의수)는 2이다. ( )
```

9. 다음 증명 흐름에서 A, B, C에 들어갈 말을 쓰시오.

```text
atomic read/write memory(원자적 읽기/쓰기 메모리)로 2-thread consensus가 가능하다고 가정
        |
        v
protocol tree(프로토콜 트리)에 critical state(임계상태) S가 존재
        |
        v
S에서 A의 step은 0-valent, B의 step은 1-valent로 이동한다고 볼 수 있음
        |
        v
A와 B의 step을 경우분석:
    1. read 포함       -> ______A______
    2. 서로 다른 write -> ______B______
    3. 같은 곳 write   -> ______C______
        |
        v
모든 경우 모순
        |
        v
atomic read/write memory의 consensus number(합의수)는 1
```

10. 다음을 시험 답안식으로 3문장 이내로 설명하시오.

```text
왜 atomic read/write memory(원자적 읽기/쓰기 메모리)의 consensus number(합의수)는 1인가?
```

## 정답 및 해설

1. `A.read`는 공유 메모리 값을 바꾸지 않고 A의 local state(지역 상태)만 바꾼다. B는 A가 read를 했는지 안 했는지를 공유 메모리만 보고 알 수 없다. 따라서 `A.read` 하나가 다른 스레드에게 보이는 상태를 0-valent로 확정시키는 결정적 변화가 될 수 없다.

2. `A.read`는 A 내부의 local state(지역 상태)만 바꾸고 shared memory(공유 메모리)를 바꾸지 않는다. 그래서 B 입장에서는 `S`에서 바로 실행한 것과, A가 몰래 read를 한 뒤 실행한 것을 구분할 수 없다. B가 구분할 수 없는 두 상태에서 서로 다른 결정값을 내야 한다면 모순이다.

3. 서로 다른 register에 대한 write는 서로 독립적이다. `A.write(x1)`와 `B.write(x2)`는 다른 칸을 쓰므로 순서를 바꾸어도 최종 상태는 `x1`에는 A가 쓴 값, `x2`에는 B가 쓴 값이 남는다. 따라서 두 실행의 최종 공유 메모리 상태는 같다.

4. `S -> A.write(x1)`가 0-valent라면 그 뒤에 B가 실행되어도 최종 결정은 0이어야 한다. 반대로 `S -> B.write(x2)`가 1-valent라면 그 뒤에 A가 실행되어도 최종 결정은 1이어야 한다. 그런데 두 최종 상태는 같으므로 같은 상태에서 0과 1을 동시에 강제해야 하는 모순이 생긴다.

5. 같은 register `x1`에 대한 write는 마지막 write가 이전 write를 덮어쓴다. `A.write(x1, v0)` 뒤에 `B.write(x1, v1)`를 하면 최종적으로 `x1`에는 `v1`만 남는다. 따라서 이 상태는 `B.write(x1, v1)`만 수행한 상태와 공유 메모리상 구별되지 않는다.

6. `상태 1`은 `S -> A.write(x1, v0)` 이후에 도달한 상태이고, 이 상태가 0-valent라고 가정했으므로 이후 어떤 실행을 해도 0으로 결정되어야 한다. `상태 2`는 `S -> B.write(x1, v1)` 이후 상태이고, 이 상태가 1-valent라고 가정했으므로 1로 결정되어야 한다. 그런데 둘은 구별되지 않는 상태이므로 모순이다.

7. A = 덮어쓴다, B = B.write, C = 모순.

8. A: O, B: X, C: O, D: O, E: X.

9. A = read는 공유 메모리를 바꾸지 않아 다른 스레드가 구분할 수 없다. B = 서로 다른 write는 순서를 바꾸어도 최종 상태가 같다. C = 같은 register에 대한 write는 뒤 write가 앞 write를 덮어, 앞 write가 있었는지 구분할 수 없다.

10. Atomic read/write memory(원자적 읽기/쓰기 메모리)는 read(읽기)와 write(쓰기)만 제공하므로 여러 스레드 중 최초 승자를 원자적으로 확정하는 conditional update(조건부 갱신)를 할 수 없다. 2-thread consensus를 가정하면 임계상태에서 read 포함, 서로 다른 write, 같은 register write의 모든 경우가 구별 불가능성 때문에 모순이 된다. 따라서 2개 스레드 wait-free consensus(무대기 합의)를 구현할 수 없고, consensus number(합의수)는 1이다.
