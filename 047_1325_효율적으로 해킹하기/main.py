import sys
from collections import deque

sys.stdin = open("./input.txt", "r")
input = lambda: sys.stdin.readline().strip()


def BFS(target: int, N: int, trust_network: list) -> int:
    infested = 0
    visited = [False] * (N + 1)
    visited[target] = True
    Q = deque([target])

    while Q:
        PC = Q.popleft()
        for next_PC in trust_network[PC]:
            if not visited[next_PC]:
                infested += 1
                visited[next_PC] = True
                Q.append(next_PC)
    return infested


def solution(N: int, trust_network: list):
    max_infested = 0
    infested = [0] * (N + 1)
    for i in range(1, N + 1):
        infested[i] = BFS(i, N, trust_network)
        max_infested = max(max_infested, infested[i])

    for i in range(1, N + 1):
        if infested[i] == max_infested:
            print(i, end=" ")


if __name__ == "__main__":
    N, M = map(int, input().split())
    trust_network = [[] for _ in range(N + 1)]
    for _ in range(M):
        u, v = map(int, input().split())
        trust_network[v].append(u)
    solution(N, trust_network)
