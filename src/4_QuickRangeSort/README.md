# pichulia-archive/src/4_QuickRangeSort
TODO : Explain me.

```
PS D:\code\vscode2\test> .\main.exe
test type : Full random     , n : 200000 value range(-1000000000 ~ 1000000000) repeat 100 times.
std::sort   :                941
quick_naive :               1086
quick_range :               1227
test type : Sorted          , n : 200000 value range(-1000000000 ~ 1000000000) repeat 100 times.
std::sort   :                131
quick_naive :                287
quick_range :                198
test type : Almost sorted   , n : 200000 value range(-1000000000 ~ 1000000000) repeat 100 times.
std::sort   :                156
quick_naive :                313
quick_range :                 98
test type : Reversed        , n : 200000 value range(-1000000000 ~ 1000000000) repeat 100 times.
std::sort   :                150
quick_naive :                248
quick_range :                138
test type : Almost reversed , n : 200000 value range(-1000000000 ~ 1000000000) repeat 100 times.
std::sort   :                405
quick_naive :                415
quick_range :                306
```

As you can see, std::sort is fastest.
Don't use this quick sort.

```
PS D:\code\vscode2\test> .\main.exe
test type : Full random     , n : 200000 value range(-10 ~ 10) repeat 100 times.
std::sort   :                455
quick_naive :              22048
quick_range :                181
test type : Sorted          , n : 200000 value range(-10 ~ 10) repeat 100 times.
std::sort   :                136
quick_naive :                 60
quick_range :                 32
test type : Almost sorted   , n : 200000 value range(-10 ~ 10) repeat 100 times.
std::sort   :                154
quick_naive :                649
quick_range :                 41
test type : Reversed        , n : 200000 value range(-10 ~ 10) repeat 100 times.
std::sort   :                136
quick_naive :                336
quick_range :                 39
test type : Almost reversed , n : 200000 value range(-10 ~ 10) repeat 100 times.
std::sort   :                 92
quick_naive :               1902
quick_range :                 50
```

But if value range is small enough, it will be fast enough.
But if this case, you'd better use Count Sort.
So... Don't use this quick sort.