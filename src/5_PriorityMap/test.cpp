#include <stdio.h>
#include <algorithm>
#include "priority_map.h"

int main()
{
    int i, j, k;
    int n, m;
    wahaha::priority_map<int, std::pair<int, int>> tm;

    scanf("%d",&n);
    for(i=1;i<=n;i++){
        scanf("%d",&j);
        tm.insert(i, std::pair<int, int>(-j, -i));
    }
    scanf("%d",&m);
    while(m--){
        int cmd;
        scanf("%d",&cmd);
        if(cmd==2){
            printf("%d\n",-tm.top().second);
        }
        else{
            scanf("%d %d",&i,&j);
            tm.insert(i, std::pair<int, int>(-j, -i));
        }
    }
}