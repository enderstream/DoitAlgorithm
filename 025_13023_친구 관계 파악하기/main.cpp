#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>

using namespace std;

typedef unordered_map<int, vector<int>> dict;

int solution(int N, dict &friends);
bool find_friend_chain(dict &friends, int N, int i);

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("./input.txt", "r", stdin);

    int N, M;
    cin >> N >> M;

    dict friends;
    for (int i = 0; i < N; i++)
        friends[i];

    for (int i = 0; i < M; i++)
    {
        int friend1, friend2;
        cin >> friend1 >> friend2;
        friends[friend1].push_back(friend2);
        friends[friend2].push_back(friend1);
    }

    cout << solution(N, friends);
    return 0;
}

int solution(int N, dict &friends)
{
    for (int i = 0; i < N; i++)
        if (find_friend_chain(friends, N, i))
            return 1;
    return 0;
}

bool find_friend_chain(dict &friends, int N, int i)
{
    vector<bool> visited(N, false);
    stack<pair<int, int>> stack;
    stack.push(pair<int, int>(i, 1));
    while (!stack.empty())
    {
        pair<int, int> top = stack.top();
        stack.pop();
        int person = top.first;
        int depth = top.second;

        if (depth == N)
            return true;
            
        if (friends[person].size() == 0)
            continue;
        
        for (auto f : friends[person])
        {
            if (!visited[f])
            {
                visited[f] = true;
                stack.push(pair<int, int>(f, depth + 1));
            }
        }
    }
    return false;
}