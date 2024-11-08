import sys

sys.stdin = open("./input.txt", "r")
input = lambda: sys.stdin.readline().strip()


def solution(num_str: str):
    print(sum(map(int, num_str)))


if __name__ == "__main__":
    N = int(input())  # dummy
    num_str = input()
    solution(num_str)
