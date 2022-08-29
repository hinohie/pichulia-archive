#include <stdio.h>
#include "priority_map.h"

int main()
{
    int i, j, k;
    std::priority_map<int, int> tm;
    tm.insert(3, 5);
    tm.insert(5, 8);
    tm.insert(8, 1);

    printf("%zu %d == %d\n", tm.size(), tm.top(), 8);

    tm.insert(5, 3);
    printf("%zu %d == %d\n", tm.size(), tm.top(), 5);

    tm.pop();
    printf("%zu %d == %d\n", tm.size(), tm.top(), 3);
    
    tm.pop();
    printf("%zu %d == %d\n", tm.size(), tm.top(), 1);
}