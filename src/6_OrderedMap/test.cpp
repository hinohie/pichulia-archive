#include <stdio.h>
#include <algorithm>
#include "ordered_map.h"

#include <vector>
#include <random>

static std::mt19937 rnd;

int main()
{
    int i, j, k;
    int n, m;
    wahaha::ordered_map<int, int> tm;

    n = 10000;
    std::vector<int> key(n);
    std::vector<int> expected(n);
    for(i=0;i<n;i++){
        key[i] = i+1;
        expected[i] = i+1;
    }
    std::shuffle(key.begin(), key.end(), rnd);
    for(i=0;i<n;i++){
        tm.insert(key[i], expected[i]);
        int cnt = 0;
        for(const auto& iter : tm){
            assert(key[cnt] == iter.first);
            assert(++cnt == iter.second);
        }
    }
    printf("passed\n");
}