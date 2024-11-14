import sys
from collections import deque

sys.stdin = open("./input.txt", "r")
input = lambda: sys.stdin.readline().strip()


def BFS(A: int, B: int, C: int) -> list:
    capacity = [A, B, C]
    visited = set()
    volumes = [C]
    movements = [(0, 1), (0, 2), (1, 0), (1, 2), (2, 0), (2, 1)]
    Q = deque([[0, 0, C]])
    visited.add((0, 0))

    while Q:
        curr = Q.popleft()
        for movement in movements:
            send = movement[0]
            recv = movement[1]
            ABC = [curr[i] for i in range(3)]
            if ABC[send] == 0:
                continue

            ABC[recv] += ABC[send]
            ABC[send] = 0
            if ABC[recv] > capacity[recv]:
                ABC[send] = ABC[recv] - capacity[recv]
                ABC[recv] = capacity[recv]
            if (ABC[0], ABC[1]) in visited:
                continue
            visited.add((ABC[0], ABC[1]))
            Q.append([ABC[0], ABC[1], ABC[2]])
            if ABC[0] == 0:
                volumes.append(ABC[2])

    return volumes


def solution(A: int, B: int, C: int):
    print(*sorted(BFS(A, B, C)))


if __name__ == "__main__":
    A, B, C = map(int, input().split())
    solution(A, B, C)
