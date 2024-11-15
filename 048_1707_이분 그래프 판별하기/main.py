import sys

sys.stdin = open("./input.txt", "r")
input = lambda: sys.stdin.readline().strip()


def DFS(target: int, visited: list, V: int, graph: list) -> str:
    flag = 1
    stack = [target]
    visited[target] = flag
    while stack:
        node = stack.pop()
        flag = visited[node]
        for next_node in graph[node]:
            if not visited[next_node]:
                visited[next_node] = -flag
                stack.append(next_node)
            elif visited[next_node] == flag:
                return "NO"
    return "YES"


def solution(V: int, graph: list):
    visited = [0] * (V + 1)
    for i in range(V + 1):
        if not visited[i] and "NO" == DFS(i, visited, V, graph):
            print("NO")
            break
    else:
        print("YES")


if __name__ == "__main__":
    K = int(input())
    for _ in range(K):
        V, E = map(int, input().split())
        graph = [[] for _ in range(V + 1)]
        for _ in range(E):
            u, v = map(int, input().split())
            graph[u].append(v)
            graph[v].append(u)
        solution(V, graph)
