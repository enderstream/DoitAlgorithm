#include <iostream>
#include <string>
#include <stack>
using namespace std;

string solution(int n);

int main(int argc, const char *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("./input.txt", "r", stdin);

    int n;
    cin >> n;

    cout << solution(n);
    return 0;
}

string solution(int n)
{
    int i = 1;
    int seq;
    cin >> seq;
    string operation = "";
    stack<int> stack;
    while (!stack.empty() || i <= n)
        if (i < seq)
        {
            stack.push(i++);
            operation += "+\n";
        }
        else if (i == seq)
        {
            operation += "+\n-\n";
            cin >> seq;
            i++;
        }
        else if (stack.top() == seq)
        {
            stack.pop();
            operation += "-\n";
            cin >> seq;
        }
        else if (stack.top() > seq)
            return "NO";

    return operation;
}