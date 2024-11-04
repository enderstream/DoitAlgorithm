#include <iostream>
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

typedef priority_queue<int, vector<int>, greater<int>> min_heap;

void solution(int N, min_heap &card_deck);

int main(int argc, char const *argv[])
{
    FAST_IO;
    if constexpr (local)
        (void)!freopen("./input.txt", "r", stdin);

    int N;
    cin >> N;

    min_heap card_deck;
    for (int i = 1; i <= N; i++)
    {
        int card;
        cin >> card;
        card_deck.push(card);
    }

    solution(N, card_deck);
    return 0;
}

void solution(int N, min_heap &card_deck)
{
    int total_compare = 0;
    while (card_deck.size() > 1)
    {
        int deck1 = card_deck.top();
        card_deck.pop();
        int deck2 = card_deck.top();
        card_deck.pop();

        total_compare += deck1 + deck2;

        card_deck.push(deck1 + deck2);
    }
    
    cout << total_compare;
}