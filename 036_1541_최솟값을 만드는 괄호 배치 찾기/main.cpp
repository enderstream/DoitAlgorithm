#include <iostream>
#include <vector>
#include <string>

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

vector<string> expression_tokenizer(string &expression);
void solution(string &expression);

int main(int argc, char const *argv[])
{
    FAST_IO;
    if constexpr (local)
    {
        (void)!freopen("./input.txt", "r", stdin);
        debug << "\n";
    }

    string expression;
    getline(cin, expression);

    solution(expression);
    return 0;
}

vector<string> expression_tokenizer(string &expression)
{
    vector<string> tokens;
    string token = "";

    for (auto &exp : expression)
        if (exp == '+' || exp == '-')
        {
            tokens.push_back(token);
            token.clear();
            tokens.push_back(string(1, exp));
        }
        else if (exp != '0' || (!token.empty() && token[0] != '0'))
            token += exp;
    tokens.push_back(token);

    return tokens;
}

void solution(string &expression)
{
    int min_sum = 0;
    vector<string> tokens = expression_tokenizer(expression);
    int i = 0;
    while (i < tokens.size())
    {
        if (tokens[i] == "-")
        {
            int j = i + 1;
            while (j < tokens.size() && tokens[j] != "-")
            {
                if (tokens[j] != "+")
                    min_sum -= stoi(tokens[j]);
                j++;
            }
            i = j - 1;
        }
        else if (tokens[i] != "+")
            min_sum += stoi(tokens[i]);
        i++;
    }

    cout << min_sum;
}
