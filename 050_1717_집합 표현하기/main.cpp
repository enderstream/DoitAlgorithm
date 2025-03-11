#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

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

void solution(int n, int m);
int find_head(vector<int> &set, int e);

int main(int argc, char const *argv[])
{
    FAST_IO;
    debug << "\n";
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int n, m;
    cin >> n >> m;

    solution(n, m);

    return 0;
}

void solution(int n, int m)
{
    vector<int> set(n + 1);
    for (int i = 0; i <= n; i++)
        set[i] = i;

    for (int i = 0; i < m; i++)
    {
        int cmd, a, b;
        cin >> cmd >> a >> b;
        if (cmd == 0) // unionise
        {
            int head_a = find_head(set, a);
            int head_b = find_head(set, b);
            int new_head = min(head_a, head_b);
            set[head_a] = new_head; // set[a] = new_head 하면 안됨!!!
            set[head_b] = new_head; // set[b] = new_head 하면 안됨!!!
        }
        else if (find_head(set, a) == find_head(set, b)) // cmd == 1 and same head
            cout << "YES\n";
        else // cmd == 1 and diff head
            cout << "NO\n";
    }
}

int find_head(vector<int> &set, int e)
{
    // 내가 루트라면 즉시 리턴
    if (set[e] == e)
        return e;

    // 루트 찾기
    int root = e;
    while (set[root] != root)
        root = set[root];

    // 경로 압축
    while (e != root)
    {
        int parent = set[e]; // 부모를 일단 따로 저장
        set[e] = root;       // 나는 내 부모를 루트로 교체
        e = parent;          // 부모를 나로 교체해서 다음 루프에서 부모의 부모도 루트로 교체되도록 설정
    }
    return root;
}