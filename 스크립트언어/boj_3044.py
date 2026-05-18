import sys
from collections import deque


MOD = 1_000_000_000


def mark_reachable(start, graph, n):
    seen = [False] * (n + 1)
    stack = [start]
    seen[start] = True

    while stack:
        cur = stack.pop()
        for nxt in graph[cur]:
            if not seen[nxt]:
                seen[nxt] = True
                stack.append(nxt)

    return seen


def main():
    input = sys.stdin.readline
    n, m = map(int, input().split())

    graph = [[] for _ in range(n + 1)]
    reverse_graph = [[] for _ in range(n + 1)]

    for _ in range(m):
        a, b = map(int, input().split())
        graph[a].append(b)
        reverse_graph[b].append(a)

    from_start = mark_reachable(1, graph, n)
    to_finish = mark_reachable(2, reverse_graph, n)
    valid = [from_start[i] and to_finish[i] for i in range(n + 1)]

    indegree = [0] * (n + 1)
    valid_count = 0
    for node in range(1, n + 1):
        if valid[node]:
            valid_count += 1
            for nxt in graph[node]:
                if valid[nxt]:
                    indegree[nxt] += 1

    queue = deque(i for i in range(1, n + 1) if valid[i] and indegree[i] == 0)
    topo = []

    while queue:
        cur = queue.popleft()
        topo.append(cur)
        for nxt in graph[cur]:
            if valid[nxt]:
                indegree[nxt] -= 1
                if indegree[nxt] == 0:
                    queue.append(nxt)

    if len(topo) != valid_count:
        print("inf")
        return

    dp = [0] * (n + 1)
    over = [False] * (n + 1)
    dp[1] = 1

    for cur in topo:
        for nxt in graph[cur]:
            if not valid[nxt]:
                continue

            if over[cur] or over[nxt] or dp[nxt] + dp[cur] >= MOD:
                over[nxt] = True
            dp[nxt] = (dp[nxt] + dp[cur]) % MOD

    if over[2]:
        print(f"{dp[2]:09d}")
    else:
        print(dp[2])


if __name__ == "__main__":
    main()
