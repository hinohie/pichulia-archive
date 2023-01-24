#include <stdio.h>
#include <algorithm>
#include "ordered_map.h"

#include <vector>

int main()
{
    int i, j, k;
    int n, m;
    wahaha::ordered_map<int, int> tm;

    n = 10;
    std::vector<int> key{0, 5, 1, 6, 2, 7, 3, 8, 4, 9};
    std::vector<int> expected{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for(i=0;i<n;i++){
        tm.insert(key[i], expected[i]);
        int cnt = 0;
        for(const auto& iter : tm){
            assert(++cnt == iter.second);
        }
    }
    printf("passed\n");
}