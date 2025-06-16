#include <iostream>
#include <string>
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

void solution(string &s1, string &s2);

int main(int argc, char const *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    string s1, s2;
    cin >> s1 >> s2;

    solution(s1, s2);
    return 0;
}

void solution(string &s1, string &s2)
{
    int s1_len = s1.length(), s2_len = s2.length();
    vector<vector<int>> DP(s1_len + 1, vector<int>(s2_len + 1));

    for (int i = 1; i <= s1_len; i++)
        for (int j = 1; j <= s2_len; j++)
            if (s1[i - 1] == s2[j - 1])
                DP[i][j] = DP[i - 1][j - 1] + 1;
            else
                DP[i][j] = max(DP[i - 1][j], DP[i][j - 1]);

    cout << DP[s1_len][s2_len];
    
    string LCS = "";
    if (DP[s1_len][s2_len] != 0)
    {
        while (s1_len != 0 && s2_len != 0)
            if (s1[s1_len - 1] == s2[s2_len - 1])
            {
                LCS += s1[s1_len - 1];
                s1_len--;
                s2_len--;
            }
            else if (DP[s1_len - 1][s2_len] > DP[s1_len][s2_len - 1])
                s1_len--;
            else
                s2_len--;

        reverse(LCS.begin(), LCS.end());
        cout << "\n" << LCS;
    }
}