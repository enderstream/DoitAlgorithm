#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
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
    freopen("input.txt", "r", stdin);

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
    stack<int> branch_stack;

    stack<vector<int>> stack;
    stack.push({-1, i, 1});

    while (!stack.empty())
    {
        vector<int> top = stack.top();
        stack.pop();
        int person = top[1];
        int depth = top[2];

        if (!branch_stack.empty() && branch_stack.top() != top[0])
        {
            visited[branch_stack.top()] = false;
            branch_stack.pop();
        }

        if (depth == 5)
            return true;

        if (friends[person].size() == 0)
            continue;

        bool has_branch = false;
        for (auto f : friends[person])
            if (!visited[f])
            {
                has_branch = true;
                stack.push({person, f, depth + 1});
            }
        if (has_branch)
        {
            visited[person] = true;
            branch_stack.push(person);
        }
    }
    return false;
}