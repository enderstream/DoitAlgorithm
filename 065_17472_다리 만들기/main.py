from heapq import heappush, heappop
import sys

# sys.stdin = open("./input.txt", "r")


def prim(start, graph):
    heap = []
    visited = {}
    sum_weight = 0  # 최소 비용 합계
    heappush(heap, (0, *start))
    cnt = 0  # 연결 개수 세기
    while heap:
        weight, cur_i, cur_j = heappop(heap)
        if (cur_i, cur_j) in visited:
            continue
        visited[(cur_i, cur_j)] = 1
        # if weight > 0:
        #     print(f"added_bridge: {weight} {cur_i} {cur_j}")
        sum_weight += weight
        cnt += 1

        for next_n in graph[(cur_i, cur_j)]:
            # print(graph[(cur_i,cur_j)])
            # print('-'*10)
            n_weight, n_i, n_j = next_n
            if (n_i, n_j) not in visited:
                heappush(heap, next_n)

    return sum_weight, cnt


N, M = map(int, input().split())  # 행렬의 세로, 가로 크기
matrix = [list(map(int, input().split())) for _ in range(N)]  # 섬 정보

# 1. 인접 리스트 만들기
# 1-1 각 노드별(섬이 있는 좌표별) 인접리스트 생성
# 1-1-1 각 좌표별 최대 4개가 다른 노드와 연결될 수 있음
# 1-1-2 각 좌표별 상,하,좌,우 4방향으로 맵을 탐색하면서 가장 가까운 다른 노드를 해당 좌표의 연결 정보로 저장 (가중치는 떨어져 있는 거리)
# 1-1-3 한칸 떨어져있으면 가중치는 0, 두칸 떨어져있으면 가중치 1이며, 문제 요구 조건에 따라 가중치가 1로 연결된 노드는 저장하지 않음.
dirs = [(-1, 0), (1, 0), (0, -1), (0, 1)]
start = (0, 0)  # 섬이 있는 좌표 아무 곳이나 상관 없음 (프림 알고리즘의 시작 좌표)
graph = dict()
for i in range(N):
    for j in range(M):
        if matrix[i][j]:
            start = (i, j)
            conn = []
            for d in dirs:
                ni, nj = i + d[0], j + d[1]
                dis = 0
                while 0 <= ni < N and 0 <= nj < M and not matrix[ni][nj]:
                    ni, nj = ni + d[0], nj + d[1]
                    dis += 1
                # 가중치가 1인 경우 저장하지 않음
                if 0 <= ni < N and 0 <= nj < M and dis != 1:
                    conn.append((dis, ni, nj))
            graph[(i, j)] = conn

# 2.프림 알고리즘을 통해 최소 신장 트리 구하기
min_cost, cnt = prim(start, graph)
print(f"cnt: {cnt}")
print(f"total_connection: {len(graph)}") # len(graph)의 의미는 섬의 개수
print(graph) # debug
if cnt != len(graph):  # 모두 연결할 수 없는 경우 -1 출력
    print(-1)
else:
    print(min_cost)
