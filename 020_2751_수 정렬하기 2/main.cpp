#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void solution(int N, vector<int> &vec);
void iterative_merge_sort(int N, vector<int> &vec);
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
    iterative_merge_sort(N, vec);

    for (int i = 0; i < N; i++)
        cout << vec[i] << "\n";
}

void iterative_merge_sort(int N, vector<int> &vec)
{
    for (int delta = 1; delta < N; delta *= 2)
        for (int idx = 0; idx < N; idx += delta * 2)
        {
            vector<int> vec_i = safe_slice(vec, idx, delta);
            vector<int> vec_j = safe_slice(vec, idx + delta, delta);
            int i = 0, j = 0, k = idx;
            while (i < vec_i.size() && j < vec_j.size())
                vec[k++] = (vec_i[i] < vec_j[j]) ? vec_i[i++] : vec_j[j++];
            while (i < vec_i.size())
                vec[k++] = vec_i[i++];
            while (j < vec_j.size())
                vec[k++] = vec_j[j++];
        }
}

vector<int> safe_slice(const vector<int> &vec, int start, int len)
{
    if (start >= static_cast<int>(vec.size()))
        return vector<int>();
    int end = min(static_cast<int>(vec.size()), start + len);
    return vector<int>(vec.begin() + start, vec.begin() + end);
}