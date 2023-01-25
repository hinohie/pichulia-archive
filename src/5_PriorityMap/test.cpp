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
#include "priority_map.h"
using namespace std;
using lld = long long int;
using pii = pair<int, int>;
using pil = pair<int, lld>;
const int MAX_N = 200000;
const int MAX_M = 400000;
const int MIN_VALUE = 1;
const int MAX_VALUE = 1000;
const int SMALL_N = 20;
const int tc_count = 1;

static mt19937 rnd;
void setseed(lld seed){
  rnd = mt19937(seed);
}
int nextint(int s, int t){
  return (int)(rnd()%(t-s+1))+s;
}

//
int n, m;
vector<pair<int, lld>> v[MAX_N+1];
lld orig_d[MAX_N+1];
lld my_d[MAX_N+1];

int random_box[MAX_N+1];
int si;

int op_type;
lld type_sum[109];
void inil()
{
  int i, j, k;
  for(i=0;i<n;i++){
    orig_d[i] = my_d[i] = -1;
  }
}

// Standard dijkstra
namespace PICHULIA
{
  void process_priority_queue()
  {
    // Store into orig_d
    using pli = pair<lld, int>;
    std::priority_queue<pli> tq;
    orig_d[si] = 0;
    tq.push(pli(0, si));
    while(!tq.empty())
    {
      pli tt = tq.top();
      tq.pop();
      lld tm = -tt.first;
      int ti = tt.second;
      if(orig_d[ti] != tm)continue;
      for(auto& iter : v[ti]){
        int ei = iter.first;
        if(orig_d[ei] < 0 || orig_d[ei] > tm + iter.second)
        {
          orig_d[ei] = tm + iter.second;
          tq.push(pli(-orig_d[ei], ei));
        }
      }
    }
  }
} // namespace PICHULIA

// dijkstra with priority_map
namespace PICHULIA
{
  void process_priority_map()
  {
    // Store into my_d
    wahaha::priority_map<int, lld> tq;
    my_d[si] = 0;
    tq.insert(si, 0);
    while(!tq.empty())
    {
      int ti = tq.topKey();
      lld tm = -tq.top();
      tq.pop();
      for(auto& iter : v[ti]){
        int ei = iter.first;
        if(my_d[ei] < 0 || my_d[ei] > tm + iter.second)
        {
          my_d[ei] = tm + iter.second;
          tq.insert(ei, -my_d[ei]);
        }
      }
    }
  }
} // namespace PICHULIA
//
const string tv_name[]{
    "Full random with connected",
};
const string type_name[] = {
  "standard dijkstra",
  "priority_map     ",
};
void (*const op_func[])(void) = {
  PICHULIA::process_priority_queue,
  PICHULIA::process_priority_map,
};
const int tv_max = 1;
const int op_max = 2;
static_assert(sizeof(tv_name) / sizeof(tv_name[0]) >= tv_max);
static_assert(sizeof(type_name) / sizeof(type_name[0]) >= op_max);
static_assert(sizeof(op_func) / sizeof(op_func[0]) >= op_max);

bool judge(){
  int i, j, k;
  for(i=0;i<n;i++){
    if(orig_d[i] != my_d[i]){
      printf("pung at %s %d, (you : %d, expect : %d)\n",type_name[op_type].c_str(), i, orig_d[i], my_d[i]);
      return false;
    }
  }
  return true;
}
//

void generate_a(int tv)
{
  int i, j, k;
  //n = tv_N[tv];
  n = MAX_N;
  m = MAX_M;
  for(i=0;i<n;i++){
    random_box[i] = i;
  }

  shuffle(random_box, random_box+n, rnd);

  si = random_box[0];
  int edge_cnt=0;
  for(i=0;i<n-1;i++){
    int si = random_box[i];
    int ei = random_box[i+1];
    v[si].push_back(pil(ei, nextint(MIN_VALUE, MAX_VALUE)));
    edge_cnt++;
  }
  while(edge_cnt < m){
    int si = random_box[nextint(0, n-1)];
    int ei = random_box[nextint(0, n-1)];
    if(si == ei)continue;
    v[si].push_back(pil(ei, nextint(MIN_VALUE, MAX_VALUE)));
    edge_cnt++;
  }
  for(i=0;i<n;i++){
    shuffle(v[i].begin(), v[i].end(), rnd);
  }
}
void test_all(int tv)
{
  for(int repeat_cnt; repeat_cnt < tc_count; repeat_cnt++)
  {
    generate_a(tv);
    inil();
    for(op_type = 0; op_type < op_max; op_type++)
    {
      long t1, t2;
      t1 = clock();
      op_func[op_type]();
      t2 = clock();
      //printf("tv %3d %s // %ld ms\n", op_type, type_name[op_type].c_str(), t2 - t1);
      type_sum[op_type] += t2 - t1;
    }
    assert(judge());
  }
}
int main()
{
  int t=1, tv=0;
  int i, j, k, l;
  t = tv_max;
  while(t--)
  {
    for(i=0;i<op_max;i++){
      type_sum[i] = 0;
    }
    printf("test type : %s, n : %d, m : %d, value range(%d ~ %d) repeat %d times.\n", tv_name[tv].c_str(), MAX_N, MAX_M, MIN_VALUE, MAX_VALUE, tc_count);
    test_all(tv);
    for(i=0;i<op_max;i++){
      printf("%s : %18lld\n", type_name[i].c_str(), type_sum[i]);
    }
    tv++;
  }
}