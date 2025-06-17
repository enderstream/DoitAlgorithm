#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <unordered_map>

#ifdef BOJ // 백준 채점환경
constexpr bool local = false;
#else // 로컬
constexpr bool local = true;
#endif

#define FAST_IO                       \
    std::ios::sync_with_stdio(false); \
    std::cin.tie(nullptr);            \
    std::cout.tie(nullptr);
#define debug            \
    if constexpr (local) \
    std::cout
#define endl "\n"

using namespace std;

void solution(int N, int M);

int main(int argc, const char *argv[])
{
    FAST_IO;
    debug << "\n";
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N, M;
    cin >> N >> M;

    solution(N, M);
    return 0;
}

void solution(int N, int M)
{
    int A, B;
    vector<vector<int>> order_info(N + 1); // 학생들의 키 비교 정보
    vector<int> students(N + 1, 0);        // 학생들 키의 진입 차수
    for (int i = 0; i < M; i++)            // 학생들의 키 비교정보를 삽입
    {
        cin >> A >> B;
        order_info[A].push_back(B);
        students[B]++; // 진입 차수 증가
    }

    // 진입 차수가 0인 노드 찾기 :: 맨 앞에 올 학생 전부 찾기
    queue<int> Q;
    int first = 0;
    for (int i = 1; i <= N; i++)
        if (students[i] == 0)
            Q.push(i);

    while (!Q.empty())
    {
        first = Q.front();
        Q.pop();
        cout << first << " ";

        for (const int &next_student : order_info[first])
        {
            students[next_student]--;
            if (students[next_student] == 0)
                Q.push(next_student);
        }
    }
}
