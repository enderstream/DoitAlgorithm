#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

void solution(int N, int K, vector<int> &vec);
void iterative_quick_sort(int N, vector<int> &vec);
int partition(vector<int> &vec, int start, int end);

int main(int argc, const char *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("./input.txt", "r", stdin);

    int N, K;
    cin >> N >> K;

    vector<int> vec(N, 0);
    for (int i = 0; i < N; i++)
        cin >> vec[i];

    solution(N, K, vec);
    return 0;
}

void solution(int N, int K, vector<int> &vec)
{
    iterative_quick_sort(N, vec);
    cout << vec[K - 1];
}

void iterative_quick_sort(int N, vector<int> &vec)
{
    // quick sort는 최악으로는 N^2
    stack<int> stk;
    stk.push(0);
    stk.push(N - 1);

    while (!stk.empty())
    {
        int end = stk.top();
        stk.pop();
        int start = stk.top();
        stk.pop();
        int pivot = partition(vec, start, end);

        if (pivot - 1 > start)
        {
            stk.push(start);
            stk.push(pivot - 1);
        }
        if (pivot + 1 < end)
        {
            stk.push(pivot + 1);
            stk.push(end);
        }
    }
}
int partition(vector<int> &vec, int start, int end)
{
    int pivot = vec[start];
    int left = start + 1;
    int right = end;
    while (true)
    {
        while (left <= right && vec[left] <= pivot)
            left++;
        while (left <= right && vec[right] > pivot)
            right--;
        if (left > right)
            break;
        else
            swap(vec[left], vec[right]);
    }
    swap(vec[start], vec[right]);
    return right;
}
