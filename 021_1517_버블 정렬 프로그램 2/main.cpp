#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solution(int N, vector<int> &vec);
long iterative_merge_sort(int N, vector<int> &vec);
vector<int> safe_slice(const vector<int> &vec, int start, int len);

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("./input.txt", "r", stdin);

    int N;
    cin >> N;

    vector<int> vec(N, 0);
    for (int i = 0; i < N; i++)
        cin >> vec[i];

    solution(N, vec);
    return 0;
}

void solution(int N, vector<int> &vec)
{
    cout << iterative_merge_sort(N, vec);
}

long iterative_merge_sort(int N, vector<int> &vec)
{
    long swap_cnt = 0;
    for (int len = 1; len < N; len *= 2)
        for (int idx = 0; idx < N; idx += len * 2)
        {
            vector<int> vec_i = safe_slice(vec, idx, len);
            vector<int> vec_j = safe_slice(vec, idx + len, len);
            int i = 0, j = 0, k = idx;
            while (i < vec_i.size() && j < vec_j.size())
                if (vec_i[i] <= vec_j[j])
                    vec[k++] = vec_i[i++];
                else
                {
                    swap_cnt += (static_cast<int>(vec_i.size()) - i);
                    vec[k++] = vec_j[j++];
                }

            while (i < vec_i.size())
                vec[k++] = vec_i[i++];
            while (j < vec_j.size())
                vec[k++] = vec_j[j++];
        }
    return swap_cnt;
}

vector<int> safe_slice(const vector<int> &vec, int start, int len)
{
    if (start >= static_cast<int>(vec.size()))
        return vector<int>();
    int end = min(static_cast<int>(vec.size()), start + len);
    return vector<int>(vec.begin() + start, vec.begin() + end);
}