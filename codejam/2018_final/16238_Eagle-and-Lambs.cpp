/**
algo: math
If you select the cell having more than A lambs, it doesn't matter the sequence selecting cell.
If the number of lambs in cell  assume f(n), the sum is like below. (1 <= n <= A)

SUM =  {f(1) - 0} + {f(2) - 1} + ... + {f(n-1) - (n-2)} + {f(n) - (n-1)}  = {f(1) ~ f(n)} - { 1 + 2 + 3 + ... (n-1) }

Therefore, the best solution is that the eager start to eat lambs in the cell having the biggest number of lambs.
**/
#include <iostream>
#include <set>
#include <iterator>
#include <algorithm>

int getMax(std::multiset<int>& sets)
{
    int days = 0, sum = 0;
    auto iter = std::rbegin(sets);
    while (iter != std::rend(sets) && *iter - days > 0) {
        sum += *iter - days;
        iter++, days++;
    }
    return sum;
}

int main()
{
    int n, a;
    std::multiset<int> sets;
    std::cin >> n;
    for (int i = 0; i < n; i++) {
        std::cin >> a;
        sets.insert(a);
    }
    std::cout << getMax(sets) << std::endl;
    return 0;
}
