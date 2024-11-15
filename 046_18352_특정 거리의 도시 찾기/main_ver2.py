import sys
from collections import defaultdict, deque

sys.stdin = open("./input.txt", "r")
input = lambda: sys.stdin.readline().strip()


def BFS(N: int, K: int, X: int, city: defaultdict) -> list:
    visited = [False] * (N + 1)
    dist = [0] * (N + 1)
    Q = deque([X])
    visited[X] = True

    while Q:
        curr = Q.popleft()
        for node in range(1, N + 1):
            if visited[node] or city.get(curr) is None or node not in city[curr]:
                continue

            dist[node] = dist[curr] + 1

            if dist[node] > K:
                return dist
            visited[node] = True
            Q.append(node)
    return dist


def solution(N: int, K: int, X: int, city: defaultdict):
    dist = BFS(N, K, X, city)
    K_dist = []
    for i in range(1, N + 1):
        if dist[i] == K:
            K_dist.append(i)

    if K_dist:
        K_dist.sort()
        for node in K_dist:
            print(node)
    else:
        print(-1)


if __name__ == "__main__":
    N, M, K, X = map(int, input().split())
    city = defaultdict(set)
    for _ in range(M):
        u, v = map(int, input().split())
        city[u].add(v)
    solution(N, K, X, city)
