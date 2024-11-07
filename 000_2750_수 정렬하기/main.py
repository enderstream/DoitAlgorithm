import sys

sys.stdin = open("./input.txt", "r")
input = lambda: sys.stdin.readline().strip()


def solution(lst:list):
    lst.sort()
    for num in lst:
        print(num)


if __name__ == "__main__":
    N = int(input())
    lst = [int(input()) for _ in range(N)]
    solution(lst)
