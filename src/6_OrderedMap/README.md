# pichulia-archive/src/6_OrderedMap

The data structure s.t. very fast to find / insert / remove, and quite slow for iteration.
The iteration speed is same as `std::list` iteration.


We use find operation by `std::unordered_map`, and data stored in `std::list`.

| Operation | TimeComplexity    |
|-----------|-------------------|
| insert    | O(H) (H = hashing)|
| erase     | O(H)              |
| find      | O(H)              |
| iteration | O(N)              |

TODO : Explain me.
