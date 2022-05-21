#include<algorithm>
#include<vector>
using namespace std;
class SuffixArray {
public:
    const static int MAX_STRING = 200009;
    const static int MAX_LEN = 200009;
    const static int LOG_LEN = 20;
    const static int INF = 1000000009;
    int pa[LOG_LEN][MAX_LEN];
    int len_sum[MAX_STRING + 1];
    int n;
    int m;
    SuffixArray() {
        inil();
    }
    void inil() {
        n = 0;
    }
    void add(int* a, int al) {
        for (int i = 0; i < al; ++i)
            pa[0][i + len_sum[n]] = a[i];
        len_sum[n + 1] = len_sum[n] + al;
        n++;
    }
    void add(char* a, int al) {
        for (int i = 0; i < al; ++i)
            pa[0][i + len_sum[n]] = a[i];
        len_sum[n + 1] = len_sum[n] + al;
        n++;
    }
    int next[MAX_LEN];
    int ccnt[MAX_LEN + MAX_STRING + 1];
    int ord[MAX_LEN];
    int ord2[MAX_LEN];
    void sort_c(int si, int ei) {
        if (ei - si <= 1)return;
        int i, j, k;
        int mi = (si + ei) / 2;
        sort_c(si, mi);
        sort_c(mi, ei);
        for (i = k = si, j = mi; i < mi && j < ei; ++k) {
            if (ccnt[i] < ccnt[j])ord[k] = ccnt[i++];
            else ord[k] = ccnt[j++];
        }
        for (; i < mi; ++k)ord[k] = ccnt[i++];
        for (; j < ei; ++k)ord[k] = ccnt[j++];
        for (i = si; i < ei; ++i)
            ccnt[i] = ord[i];
    }
    int find_c(int si, int ei, int key) {
        int l, r, mid;
        l = si; r = ei;
        while (l < r) {
            mid = (l + r) / 2;
            if (ccnt[mid] == key)return mid;
            if (ccnt[mid] < key)l = mid + 1;
            else r = mid;
        }
        return l;
    }
    void pre_build() {
        int i, j, k;
        for (i = 0; i < len_sum[n]; ++i)
            ccnt[i] = pa[0][i];
        k = len_sum[n];
        sort_c(0, k);
        for (i = j = 0; i < k; ++i) {
            if (ccnt[i] != ccnt[j]) {
                ++j;
                ccnt[j] = ccnt[i];
            }
        }
        k = j + 1;
        for (i = 0; i < len_sum[n]; ++i) {
            pa[0][i] = find_c(0, k, pa[0][i]);
        }
 
    }
    void build() // O(n (log n) )
    {
        pre_build();
        int i, j, k;
        int len;
        len = 1;
        m = 0;
        for (j = 0; j < LOG_LEN - 1; ++j) {
            //make pa[j+1][i] by pa[j][i]
            //sort by pair(pa[j][i], pa[j][i+len]). len = 2^j
            //pa[j+1][i] is rank of pair.
            int rank = 0;
            for (i = 0; i <= n + len_sum[n]; ++i) {
                ccnt[i] = 0;
            }
            for (i = 0; i < n; ++i) {
                for (k = len_sum[i]; k < len_sum[i + 1]; k++)
                {
                    if (k + len < len_sum[i + 1])
                    {
                        next[k] = pa[j][k + len] + n;
                    }
                    else
                    {
                        next[k] = i;
                    }
                    ++ccnt[next[k]];
                }
            }
            for (i = 0; i < n + len_sum[n]; ++i) {
                ccnt[i + 1] += ccnt[i];
            }
            for (i = n - 1; i >= 0; --i) {
                for (k = len_sum[i + 1] - 1; k >= len_sum[i]; --k)
                {
                    ord[--ccnt[next[k]]] = k;
                }
            }
            for (i = 0; i < len_sum[n]; ++i) {
                ccnt[i] = 0;
            }
            for (i = 0; i < len_sum[n]; ++i) {
                ++ccnt[pa[j][i]];
            }
            for (i = 0; i < len_sum[n] - 1; ++i) {
                ccnt[i + 1] += ccnt[i];
            }
            for (i = len_sum[n] - 1; i >= 0; --i) {
                ord2[--ccnt[pa[j][ord[i]]]] = ord[i];
            }
            rank = 0;
            for (i = 0; i < len_sum[n];i++) {
                pa[j + 1][ord2[i]] = rank;
                if (i + 1 < len_sum[n] && pa[j][ord2[i]] == pa[j][ord2[i + 1]] && next[ord2[i]] == next[ord2[i + 1]])
                    continue;
                ++rank;
            }
 
            m = j + 1;
 
            if (rank == len_sum[n]) break;
            len *= 2;
        }
    }
    int get_length(int pi, int _pl, int qi, int _ql) {
        // return longest common string length with
        // a[pi][pl] ^ a[qi][ql].
        // pi is string number. pl is position of suffix string.
        if (pi == qi && _pl == _ql) {
            return len_sum[pi + 1] - len_sum[pi] - _pl;
        }
        int res = 0;
        int i, j, k;
        int len;
        int pl = len_sum[pi] + _pl;
        int ql = len_sum[qi] + _ql;
        len = 1 << (m - 1);
        for (j = m - 1; j >= 0; --j) {
            if (pa[j][pl] == pa[j][ql]) {
                res += len;
                pl += len;
                ql += len;
            }
            len /= 2;
        }
        if (res > len_sum[pi + 1] - len_sum[pi] - _pl)
            res = len_sum[pi + 1] - len_sum[pi] - _pl;
        if (res > len_sum[qi + 1] - len_sum[qi] - _ql)
            res = len_sum[qi + 1] - len_sum[qi] - _ql;
        return res;
    }
 
    int* suffix_array() {
        return pa[m];
    }
    int get_rank(int pi, int pl) {
        return pa[m][len_sum[pi] + pl];
    }
};

/* How to use?
int n;
char a[200009];
int m;
char b[200009];
SuffixArray sf;
int rv[200009];
int main() {
    int i, j, k, l;
    scanf("%s", a);
    for (n = 0; a[n]; n++);
    scanf("%s", b);
    for (m = 0; b[m]; m++);
    sf.inil();
    sf.add(a, n);
    sf.add(b, m);
    sf.build();
    int* r = sf.suffix_array();
    for (i = 0; i < n+m; i++) {
        rv[r[i]] = i;
    }
    
    int res=0;
    int ri=0;
    for (i = 1; i < n+m; i++) {
        int pi = rv[i - 1];
        int qi = rv[i];
        if ((pi < n) ^ (qi < n))
        {
            int len;
            if (pi < n)len = sf.get_length(0, pi, 1, qi - n);
            else len = sf.get_length(1, pi - n, 0, qi);
            if (res < len) {
                res = len;
                ri = pi < n ? pi : qi;
            }
        }
    }
    printf("%d\n", res);
    a[ri + res] = 0;
    printf("%s\n", a + ri);
}

*/