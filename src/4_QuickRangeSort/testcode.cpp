#include<stdio.h>
#include<algorithm>
#include<vector>
#include<deque>
#include<queue>
#include<random>
#include<string>
#include<unordered_map>
#include<assert.h>
#include<time.h>
using namespace std;
using lld = long long int;
using pii = pair<int, int>;
const lld M = 1000000007;
const int MAX_N = 200000;
const int SMALL_N = 20;
const int MIN_VALUE = -1000000000;
const int MAX_VALUE = 1000000000;

static mt19937 rnd;
void setseed(lld seed){
  rnd = mt19937(seed);
}
int nextint(int s, int t){
  return (int)(rnd()%(t-s+1))+s;
}

//
int n, m;
int a[MAX_N+1];
int orig_a[MAX_N+1];
int result_a[MAX_N+1];

int op_type;
lld type_sum[109];
void inil()
{
  int i, j, k;
  for(i=0;i<n;i++){
    a[i] = orig_a[i];
  }
}

namespace QUICK_NAIVE{
  void process_insert(int* const& a, const int& si, const int& ei) noexcept{
    int i, j, k;
    for(i=si+1;i<ei;i++){
      for(j=i;j>si;j--){
        if(a[j-1] > a[j]){
          swap(a[j-1], a[j]);
        }
        else{
          break;
        }
      }
    }
  }
  void quick_naive(int* const& a, const int& si, const int& ei) noexcept{
    if(si == ei)return;
    if(si == ei - 1)return;
    if(si == ei - 2)
    {
      if(a[si] > a[si+1]){
        swap(a[si], a[si+1]);
      }
      return;
    }
    if(ei - si <= SMALL_N)
    {
      process_insert(a, si, ei);
      return;
    }
    int mi = nextint(si, ei-1);
    int pivot = a[mi];
    swap(a[si], a[mi]);
    int i = si + 1;
    int j = ei - 1;
    while(i<=j)
    {
      while(i<=j){
        if(a[i] <= pivot){
          i++;
        }
        else{
          break;
        }
      }
      while(j>si){
        if(a[j] >= pivot){
          j--;
        }
        else{
          break;
        }
      }
      if(i>=j)break;
      swap(a[i], a[j]);
      i++;j--;
    }
    swap(a[si], a[j]);
    quick_naive(a, si, j);
    quick_naive(a, i, ei);
  }
  void process_quick()
  {
    quick_naive(a, 0, n);
  }
} // namespace QUICK_NAIVE

namespace QUICK_RANGE{
  void process_insert(int* const& a, const int& si, const int& ei) noexcept{
    int i, j, k;
    for(i=si+1;i<ei;i++){
      for(j=i;j>si;j--){
        if(a[j-1] > a[j]){
          swap(a[j-1], a[j]);
        }
        else{
          break;
        }
      }
    }
  }
  void quick_range(int* const& a, const int& si, const int& ei, const int& minn, const int& maxx) noexcept{
    if(minn >= maxx)return;
    if(si == ei)return;
    if(si == ei - 1)return;
    if(si == ei - 2)
    {
      if(a[si] > a[si+1]){
        swap(a[si], a[si+1]);
      }
      return;
    }
    if(maxx == minn + 1)
    {
      // only two number exist. can we optimize here?
      int i = si;
      int j = ei - 1;

      while(i<j){
        while(i<j)
        {
          if(a[i] == maxx)break;
          i++;
        }
        while(i<j){
          if(a[j] == minn)break;
          j--;
        }
        if(i<j){
          a[i] = minn;
          a[j] = maxx;
          i++;
          j--;
        }
      }
      return;
    }
    if(ei - si <= SMALL_N)
    {
      process_insert(a, si, ei);
      return;
    }
    int pivot = ((minn ^ maxx) >> 1) + (minn & maxx);
    int i = si;
    int j = ei - 1;
    int pi, pj;
    while(i<=j)
    {
      while(i<=j){
        pi = a[i];
        if(pi <= pivot){
          i++;
        }
        else{
          break;
        }
      }
      while(j>=si){
        pj = a[j];
        if(pj > pivot){
          j--;
        }
        else{
          break;
        }
      }
      if(i>=j)break;
      swap(a[i], a[j]);
      i++;j--;
    }
    quick_range(a, si, j + 1, minn, pivot);
    quick_range(a, i, ei, pivot+1, maxx);
  }
  void process_range()
  {
    quick_range(a, 0, n, MIN_VALUE, MAX_VALUE);
  }
} // namespace QUICK_RANGE

namespace PICHULIA2{
  void process_insert(int* const& a, const int& si, const int& ei) noexcept{
    int i, j, k;
    for(i=si+1;i<ei;i++){
      for(j=i;j>si;j--){
        if(a[j-1] > a[j]){
          swap(a[j-1], a[j]);
        }
        else{
          break;
        }
      }
    }
  }
  void process_reverse(int* const& a, const int& si, const int& ei) noexcept{
    int i, j, k;
    for(i=si,j=ei-1;i<j;i++,j--){
      swap(a[i], a[j]);
    }
  }
  void quick_range(int* const& a, const int& si, const int& ei, const int& minn, const int& maxx) noexcept{
    if(minn >= maxx)return;
    if(si == ei)return;
    if(si == ei - 1)return;
    if(si == ei - 2)
    {
      if(a[si] > a[si+1]){
        swap(a[si], a[si+1]);
      }
      return;
    }
    if(maxx == minn + 1)
    {
      // only two number exist. can we optimize here?
      int i = si;
      int j = ei - 1;
      int pv, qv;

      while(i<j){
        while(i<j)
        {
          pv = a[i];
          if(pv == maxx)break;
          i++;
        }
        while(i<j){
          qv = a[j];
          if(qv == minn)break;
          j--;
        }
        if(i<j){
          a[i] = minn;
          a[j] = maxx;
          i++;
          j--;
        }
      }
      return;
    }
    if(ei - si <= SMALL_N)
    {
      process_insert(a, si, ei);
      return;
    }
    int pivot = ((minn ^ maxx) >> 1) + (minn & maxx);//minn + ((lld)maxx - (lld)minn) / 2;
    int i = si;
    int j = ei - 1;
    int pi, pj;
    int pmin = pivot;
    int pmax = minn;
    int qmin = maxx;
    int qmax = pivot;
    int inverse_cnt_left = 0;
    int valid_cnt_left = 0;
    int inverse_cnt_right = 0;
    int valid_cnt_right = 0;
    bool first_pi = true;
    bool first_pj = true;
    int prev_pi;
    int prev_pj;
    while(i<=j)
    {
      while(i<=j){
        pi = a[i];
        if(pi <= pivot){
          if(first_pi){
            first_pi = false;
          }
          else{
            if(prev_pi > pi){
              inverse_cnt_left++;
            }
            if(prev_pi < pi){
              valid_cnt_left++;
            }
          }
          prev_pi = pi;
          i++;
        }
        else{
          break;
        }
        pmin = min(pmin, pi);
        pmax = max(pmax, pi);
      }
      while(j>=si){
        pj = a[j];
        if(pj > pivot){
          if(first_pj){
            first_pj = false;
          }
          else{
            if(pj > prev_pj){
              inverse_cnt_right++;
            }
            if(pj < prev_pj){
              valid_cnt_right++;
            }
          }
          prev_pj = pj;
          j--;
        }
        else{
          break;
        }
        qmin = min(qmin, pj);
        qmax = max(qmax, pj);
      }
      if(i>=j)break;
      swap(a[i], a[j]);
      if(first_pi){
        first_pi = false;
      }
      else{
        if(prev_pi > pj){
          inverse_cnt_left++;
        }
        if(prev_pi < pj){
          valid_cnt_left++;
        }
      }
      if(first_pj){
        first_pj = false;
      }else{
        if(pi > prev_pj){
          inverse_cnt_right++;
        }
        if(pi < prev_pj){
          valid_cnt_right++;
        }
      }
      i++;j--;
      prev_pi = pj;
      prev_pj = pi;
      pmin = min(pmin, pj);
      pmax = max(pmax, pj);
      qmin = min(qmin, pi);
      qmax = max(qmax, pi);
    }

    if(inverse_cnt_left > 0)
    {
      if(valid_cnt_left == 0){
        // hard_reverse
        process_reverse(a, si, j + 1);
      }else{
        quick_range(a, si, j + 1, pmin, pmax);
      }
    }
    if(inverse_cnt_right > 0)
    {
      if(valid_cnt_right == 0){
        // hard_reverse
        process_reverse(a, i, ei);
      }else{
        quick_range(a, i, ei, qmin, qmax);
      }
    }
  }
  void process_pichulia2()
  {
    quick_range(a, 0, n, MIN_VALUE, MAX_VALUE);
  }
} // namespace PICHULIA2

namespace PICHULIA {
  void process_std()
  {
    sort(a,a+n);
  }
} // namespace PICHULIA

const int tc_count = 100;
const int op_max = 3;
const int tv_max = 5;
const string tv_name[]{
    "Full random     ",
    "Sorted          ",
    "Almost sorted   ",
    "Reversed        ",
    "Almost reversed ",
};
const int tv_N[] ={
    MAX_N,
    MAX_N,
    MAX_N,
    MAX_N,
    MAX_N,
};
const string type_name[] = {
    "std::sort  ",
    "quick_naive",
    "quick_range",
    "pichulia2  ",
};
void (*const op_func[])(void) = {
    PICHULIA::process_std,
    QUICK_NAIVE::process_quick,
    QUICK_RANGE::process_range,
    PICHULIA2::process_pichulia2,
};
static_assert(sizeof(tv_name) / sizeof(tv_name[0]) >= tv_max);
static_assert(sizeof(tv_N) / sizeof(tv_N[0]) >= tv_max);
static_assert(sizeof(type_name) / sizeof(type_name[0]) >= op_max);
static_assert(sizeof(op_func) / sizeof(op_func[0]) >= op_max);

bool judge(){
  int i, j, k;
  for(i=0;i<n;i++){
    if(a[i] != result_a[i]){
      printf("pung at %s %d, (you : %d, expect : %d)\n",type_name[op_type].c_str(), i, a[i], result_a[i]);
      return false;
    }
  }
  return true;
}
void generate_a(int tv)
{
  int i, j, k;
  n = tv_N[tv];
  for(i=0;i<n;i++){
    orig_a[i] = nextint(MIN_VALUE, MAX_VALUE);
    result_a[i] = orig_a[i];
  }
  if(tv == 1 || tv == 2 || tv == 3 || tv == 4)
  {
    sort(orig_a, orig_a+n);
    if(tv == 3 || tv == 4)
    {
      reverse(orig_a, orig_a+n);
    }
    if(tv == 2 || tv == 4)
    {
      // Rarely shuffle.
      for(i=0;i<n/100;i++){
        j = nextint(0, n-1);
        k = nextint(0, n-1);
        swap(orig_a[j], orig_a[k]);
      }
    }
  }
  sort(result_a, result_a+n);
}

void test_all(int tv)
{
  for(int repeat_cnt; repeat_cnt < tc_count; repeat_cnt++)
  {
    generate_a(tv);
    for(op_type = 0; op_type < op_max; op_type++)
    {
      long t1, t2;
      inil();
      t1 = clock();
      op_func[op_type]();
      t2 = clock();
      //printf("tv %3d %s // %ld ms\n", ogv, type_name[op_type].c_str(), t2 - t1);
      type_sum[op_type] += t2 - t1;
      assert(judge());
    }
  }
}
int main(){
  int t=1, tv=0;
  int i, j, k, l;
  t = tv_max;
  while(t--)
  {
    for(i=0;i<op_max;i++){
      type_sum[i] = 0;
    }
    printf("test type : %s, n : %d value range(%d ~ %d) repeat %d times.\n",tv_name[tv].c_str(), tv_N[tv], MIN_VALUE, MAX_VALUE, tc_count);
    test_all(tv);
    for(i=0;i<op_max;i++){
      printf("%s : %18lld\n", type_name[i].c_str(), type_sum[i]);
    }
    tv++;
  }
}