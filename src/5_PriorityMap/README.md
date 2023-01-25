# pichulia-archive/src/5_PriorityMap

![wahaha_saki](../../res/images/wahahaha.jpg)

TODO : Explain me.

```
test type : Full random with connected  , n : 200000, m : 600000, repeat 10 times.
standard dijkstra :                587 ms
standard spfa     :                149 ms
spfa with SLF     :                146 ms
spfa with LLL     :                168 ms
priority_map      :               1344 ms
test type : Stressful connect for dijk 1, n : 200000, m : 600000, repeat 10 times.
standard dijkstra :                407 ms
standard spfa     :                 46 ms
spfa with SLF     :                 37 ms
spfa with LLL     :                 52 ms
priority_map      :                827 ms
test type : Stressful connect for dijk 2, n : 200000, m : 600000, repeat 10 times.
standard dijkstra :                834 ms
standard spfa     :                101 ms
spfa with SLF     :                 54 ms
spfa with LLL     :                 78 ms
priority_map      :                533 ms
```
As you can see, SPFA is fastest.
Don't use this priority_map.
