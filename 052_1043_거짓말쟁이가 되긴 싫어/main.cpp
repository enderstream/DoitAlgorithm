#include <iostream>
#include <vector>
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

int solution(int N, int M);
int find_head(vector<int> &people, int e);

int main(int argc, const char *argv[])
{
    FAST_IO;
    debug << "\n";
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N, M;
    cin >> N >> M;

    cout << solution(N, M);
    return 0;
}

int solution(int N, int M)
{
    vector<int> people(N + 1); // 사람 정보
    for (int i = 1; i <= N; i++)
        people[i] = i; // 헤드를 자기 자신으로 초기화

    int cnt, danger, another_danger, danger_head;
    cin >> cnt; // 위험한 사람 수 입력

    if (cnt == 0) // 아무도 진실을 모르면 모조리 구라 ㄱㄱ
        return M;

    if (cnt >= 1) // 1명 이상이라면 일단 맨 첫번째 사람은 조심해야함
    {
        cin >> danger;
        people[danger] = danger;
    }
    if (cnt >= 2)
        for (int i = 1; i < cnt; i++)
        {
            // 2명 이상이라면 싹다 묶음 -> 조심해야할 첫 사람과 유니온
            cin >> another_danger;
            int head_1 = find_head(people, danger);
            int head_2 = find_head(people, another_danger);
            int new_head = min(head_1, head_2);
            people[head_1] = new_head; // 첫사람과 다음사람 head 업데이트
            people[head_2] = new_head;
        }

    vector<vector<int>> parties(M); // 파티 정보
    for (int i = 0; i < M; i++)     // 파티 정보 입력
    {
        cin >> cnt; // 파티 참석자 수
        parties[i].resize(cnt);
        for (int j = 0; j < cnt; j++)
            cin >> parties[i][j]; // 파티에 참석 인원 정보 수집

        int person_1 = parties[i][0];
        for (int j = 1; j < cnt; j++) // 파티 참석자들을 분석
        {
            // 같은 파티에 참석한 사람들은 전부 유니온
            int head_1 = find_head(people, person_1);
            int head_2 = find_head(people, parties[i][j]);
            int new_head = min(head_1, head_2);
            people[head_1] = new_head;
            people[head_2] = new_head;
        }
    }

    int safe = 0;
    bool flag;
    danger_head = find_head(people, danger); // 맨처음 위험인물 의 head를 가져옴
    for (int i = 0; i < M; i++)
    {
        // 파티를 순회하면서
        flag = true;
        for (int j = 0; j < parties[i].size(); j++)
            if (danger_head == find_head(people, parties[i][j]))
            {
                // 각 파티마다 참석자 중 위험인물이 발견되는 즉시 break
                flag = false;
                break;
            }
        if (flag) // 위험인물이 없었으므로 구라ㄱㄱ
            safe++;
    }

    return safe;
}

int find_head(vector<int> &people, int e)
{
    if (people[e] == e)
        return e;

    // 루트 찾기
    int root = e;
    while (people[root] != root)
        root = people[root];

    while (e != root)
    {
        int parent = people[e];
        people[e] = root;
        e = parent;
    }
    return root;
}