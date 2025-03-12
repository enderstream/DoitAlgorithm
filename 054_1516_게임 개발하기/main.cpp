#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
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
void solution(int N);

int main(int argc, char const *argv[])
{
    FAST_IO;
    debug << "\n";
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N;
    cin >> N;

    solution(N);
    return 0;
}

void solution(int N)
{
    int pre_build;
    // unordered_map<int, vector<int>> order_info;
    vector<vector<int>> order_info(N + 1); // 건물 건설 순서 :: 번호 -> 해금되는 건물들
    vector<int> build_time(N + 1, 0);      // 건물별 건설 소요 시간
    vector<int> buildings(N + 1, 0);       // 건물들의 진입 차수 벡터
    vector<int> DP(N + 1, 0);              // 건물별 누적 건설 소요 시간 벡터

    for (int i = 1; i <= N; i++)
    {
        cin >> build_time[i] >> pre_build;
        while (pre_build != -1)
        {
            order_info[pre_build].push_back(i);
            buildings[i]++;
            cin >> pre_build;
        }
    }

    // 제일 먼저 지을 수 있는 건물들을 찾아서 큐에 삽입
    queue<int> Q;
    for (int i = 1; i <= N; i++)
        if (buildings[i] == 0)
            Q.push(i);

    int building;
    while (!Q.empty()) // 위상 정렬
    {
        building = Q.front();
        Q.pop();
        for (const int &next_building : order_info[building])
        {
            buildings[next_building]--;
            if (buildings[next_building] == 0)
                Q.push(next_building);
            // 선행 건물들 중 가장 오래 걸리는 시간을 계산
            DP[next_building] = max(DP[next_building], DP[building] + build_time[building]);
            // building: 현재 처리 중인 건물
            // next_building: building이 지어진 후에 지을 수 있게 되는 다음 건물
            // DP[building]: building을 짓기 시작하기 전까지 걸린 시간
            // build_time[building]: building을 짓는 데 걸리는 시간
            // DP[building] + build_time[building]: building이 완성되는 시점 = next_building을 시작할 수 있는 시점
            // max(DP[next_building], ...): 여러 선행 건물들 중 가장 늦게 완성되는 시간을 선택
        }
    }
    for (int i = 1; i <= N; i++)
        cout << DP[i] + build_time[i] << "\n";
}

/*
76번 라인의 코드를 이해하기 위해선 위상 정렬에서의 DP(동적 계획법) 활용을 이해해야 합니다.

```cpp
DP[next_building] = max(DP[next_building], DP[building] + build_time[building]);
```

이 라인은 "선행 건물들 중 가장 오래 걸리는 경로"를 계산합니다. 자세히 설명하겠습니다:

### 왜 이런 계산이 필요한가?

이 문제에서는:
1. 건물마다 건설 시간이 있습니다
2. 어떤 건물을 짓기 위해서는 선행 건물들이 완성되어야 합니다
3. 여러 건물을 동시에 지을 수 있습니다
4. 각 건물이 완성되는 **최소 시간**을 구해야 합니다

### 계산 과정 설명

`DP[i]`의 의미: 건물 i를 짓기 **직전까지** 걸리는 시간 (선행 건물들이 모두 완성될 때까지의 시간)

이 값을 이용해 실제 건물 i의 완성 시간은 `DP[i] + build_time[i]`로 계산됩니다.

코드 76번 라인에서 하는 일:

```cpp
DP[next_building] = max(DP[next_building], DP[building] + build_time[building]);
```

여기서:
- `building`: 현재 처리 중인 건물
- `next_building`: building이 지어진 후에 지을 수 있게 되는 다음 건물
- `DP[building]`: building을 짓기 시작하기 전까지 걸린 시간
- `build_time[building]`: building을 짓는 데 걸리는 시간
- `DP[building] + build_time[building]`: building이 완성되는 시점 = next_building을 시작할 수 있는 시점
- `max(DP[next_building], ...)`: 여러 선행 건물들 중 가장 늦게 완성되는 시간을 선택

### 예시로 이해하기

예제를 사용해서 설명해 보겠습니다:

```
5
10 -1       # 건물 1: 건설 시간 10, 선행 건물 없음
10 1 -1     # 건물 2: 건설 시간 10, 선행 건물 1
4 1 -1      # 건물 3: 건설 시간 4, 선행 건물 1
4 3 1 -1    # 건물 4: 건설 시간 4, 선행 건물 3, 1
3 3 -1      # 건물 5: 건설 시간 3, 선행 건물 3
```

처리 과정:
1. 초기에 DP[1~5] = [0, 0, 0, 0, 0]
2. 진입 차수가 0인 건물 1을 큐에 넣음
3. 건물 1 처리:
   - 건물 2, 3, 4의 선행 건물임
   - DP[2] = max(0, 0 + 10) = 10
   - DP[3] = max(0, 0 + 10) = 10
   - DP[4] = max(0, 0 + 10) = 10
4. 건물 3 처리:
   - 건물 4, 5의 선행 건물임
   - DP[4] = max(10, 10 + 4) = 14
   - DP[5] = max(0, 10 + 4) = 14
5. ...

이렇게 계산한 DP 배열에 각 건물의 건설 시간을 더하면 최종 완성 시간이 됩니다.

### 핵심 아이디어

이 코드의 핵심은 **선행 작업들 중 가장 늦게 끝나는 시간**을 기준으로 다음 작업을 시작할 수 있다는 것입니다. 건물을 동시에 지을 수 있지만, 모든 선행 건물이 완성되어야 다음 건물을 지을 수 있기 때문입니다.
*/