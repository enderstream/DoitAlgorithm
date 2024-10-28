#include <iostream>
#include <stack>

using namespace std;

void solution(stack<int> &stack_L, stack<int> &stack_R);

int main(int argc, char const *argv[])
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    freopen("./input.txt", "r", stdin);

    int N;
    cin >> N;
    stack<int> stack_L;
    stack<int> stack_R;
    for (int i = 0; i < N; i++)
    {
        int num;
        cin >> num;
        stack_L.push(num);
    }

    solution(stack_L, stack_R);
    return 0;
}

void solution(stack<int> &stack_L, stack<int> &stack_R)
{
    stack<int> answer;
    while (!stack_L.empty())
    {
        int num = stack_L.top();
        stack_L.pop();
        if (stack_R.empty()) // 머야 아무도 없어?
        {
            answer.push(-1);
            stack_R.push(num);
        }
        else if (stack_R.top() <= num) // 여기 대빵이 나보다 약해?
        {
            while (stack_R.top() <= num) // 나보다 쎈놈 나올때 까지 팝
            {
                stack_R.pop();
                if (stack_R.empty()) // 머야? 전멸이야?
                {
                    stack_R.push(num); // 내가 대빵먹어야지
                    answer.push(-1);
                    break;
                }
                else if (stack_R.top() > num) // 아이고 행님 그게 아니라요
                {
                    answer.push(stack_R.top());
                    stack_R.push(num); // 제가 행님 딱가리 할게용
                    break;
                }
            }
        }
        else // 나보다 쎈놈이 바로 나왔네... : 입구컷
        {
            answer.push(stack_R.top());
            stack_R.push(num); // 제가 행님 딱가리 할게용
        }
    }

    while (!answer.empty())
    {
        cout << answer.top() << " ";
        answer.pop();
    }
}