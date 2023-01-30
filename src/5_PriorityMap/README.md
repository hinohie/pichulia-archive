# pichulia-archive/src/5_PriorityMap

![wahaha_saki](../../res/images/wahahaha.jpg)

TODO : Explain me.

```
test type : Full random with connected  , n : 200000, m : 600000, repeat 10 times.
standard dijkstra :                560 ms
standard spfa     :                150 ms
spfa with SLF     :                140 ms
spfa with LLL     :                164 ms
priority_map      :               1339 ms
test type : Stressful connect for dijk 1, n : 200000, m : 600000, repeat 10 times.
standard dijkstra :                387 ms
standard spfa     :                 40 ms
spfa with SLF     :                 32 ms
spfa with LLL     :                 47 ms
priority_map      :                771 ms
test type : Stressful connect for dijk 2, n : 200000, m : 600000, repeat 10 times.
standard dijkstra :                780 ms
standard spfa     :                 84 ms
spfa with SLF     :                 47 ms
spfa with LLL     :                 71 ms
priority_map      :                491 ms
test type : Full connected prefect graph, n : 5000, m : 24995000, repeat 10 times.
standard dijkstra :                374 ms
standard spfa     :                413 ms
spfa with SLF     :                353 ms
spfa with LLL     :                568 ms
priority_map      :                560 ms
test type : Sparse connected 2D space   , n : 50000, m : 1485840, repeat 10 times.
standard dijkstra :                208 ms
standard spfa     :                211 ms
spfa with SLF     :                153 ms
spfa with LLL     :                143 ms
priority_map      :                285 ms
```

As you can see, SPFA is fastest.
Even fully connected graph, SPFA is fastest.
Don't use this priority_map.
