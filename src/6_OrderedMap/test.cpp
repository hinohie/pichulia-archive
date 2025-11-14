 /**
  * Copyright (c) 2022. Eunki Hong @pichulia
  *
  * CC BY-SA 4.0 License.
  * You are free to:
  *  - Share — copy and redistribute the material in any medium or format
  *  - Adapt — remix, transform, and build upon the material
  *   for any purpose, even commercially.
  * The licensor cannot revoke these freedoms as long as you follow the license terms.
  * Under the following terms:
  *  - Attribution — You must give appropriate credit, provide a link to the license,
  *   and indicate if changes were made. You may do so in any reasonable manner,
  *  but not in any way that suggests the licensor endorses you or your use.
  * - ShareAlike — If you remix, transform, or build upon the material,
  *  you must distribute your contributions under the same license as the original.
  * - No additional restrictions — You may not apply legal terms or technological measures
  *  that legally restrict others from doing anything the license permits.
  *  - Notices — You do not have to comply with the license for elements of the material
  *  in the public domain or where your use is permitted by an applicable exception or limitation.
  *  No warranties are given. The license may not give you all of
  * the permissions necessary for your intended use. For example,
  * other rights such as publicity, privacy, or moral rights may limit how you use the material.
  * You can find the full license text at https://creativecommons.org/licenses/by-sa/4.0/legalcode
  */

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