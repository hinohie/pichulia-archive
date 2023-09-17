#include<stdio.h>
#include<algorithm>
#include<vector>
#include<deque>
#include<queue>
#include<random>
#include<string>
#include<unordered_map>
#include<set>
#include<assert.h>
#include<time.h>
#include<bitset>
#include<deque>
#include "priority_map_lite.h"
using namespace std;
using lld = long long int;
using pii = pair<int, int>;
using pil = pair<int, lld>;
const int MAX_N = 200000;
const int MAX_M = 600000;
const int MIN_VALUE = 50;
const int MAX_VALUE = 100;
const int SMALL_N = 20;
const int tc_count = 10;

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
void inil(bool need_judge)
{
  int i, j, k;
  for(i=0;i<n;i++){
    if(need_judge) my_d[i] = -1;
    else orig_d[i] = -1;
  }
}

// SPFA
namespace PICHULIA
{
  void process_spfa()
  {
    // Store into my_d
    std::queue<int> que;
    std::vector<bool> mask(n, false);
    my_d[si] = 0;
    que.push(si);
    mask[si] = true;
    while(!que.empty())
    {
      int qi = que.front();
      que.pop();
      mask[qi] = false;
      lld tm = my_d[qi];
      for(auto& iter : v[qi]){
        int ei = iter.first;
        if(my_d[ei] < 0 || my_d[ei] > tm + iter.second)
        {
          my_d[ei] = tm + iter.second;
          if(!mask[ei])
          {
            mask[ei] = true;
            que.push(ei);
          }
        }
      }
    }
  }
} // namespace PICHULIA

// SPFA (with SLF optimize)
namespace PICHULIA
{
  void process_spfa_slf()
  {
    // Store into my_d
    std::deque<int> que;
    std::vector<bool> mask(n, false);
    my_d[si] = 0;
    que.push_back(si);
    mask[si] = true;
    while(!que.empty())
    {
      int qi = que.front();
      que.pop_front();
      mask[qi] = false;
      lld tm = my_d[qi];
      for(auto& iter : v[qi]){
        int ei = iter.first;
        if(my_d[ei] < 0 || my_d[ei] > tm + iter.second)
        {
          my_d[ei] = tm + iter.second;
          if(!mask[ei])
          {
            mask[ei] = true;
            if(!que.empty() && my_d[ei] < my_d[que.front()]){
              que.push_front(ei);
            }
            else{
              que.push_back(ei);
            }
          }
        }
      }
    }
  }
} // namespace PICHULIA

// SPFA (with LLL optimize)
namespace PICHULIA
{
  void process_spfa_lll()
  {
    // Store into my_d
    std::queue<int> que;
    std::vector<bool> mask(n, false);
    my_d[si] = 0;
    que.push(si);
    mask[si] = true;
    lld quesum = 0;
    while(!que.empty())
    {
      int qi = que.front();
      que.pop();
      mask[qi] = false;
      lld tm = my_d[qi];
      quesum -= tm;
      for(auto& iter : v[qi]){
        int ei = iter.first;
        if(my_d[ei] < 0 || my_d[ei] > tm + iter.second)
        {
          if(!mask[ei])
          {
            mask[ei] = true;
            que.push(ei);
            my_d[ei] = tm + iter.second;
            quesum += my_d[ei];
          }
          else
          {
            quesum -= my_d[ei];
            my_d[ei] = tm + iter.second;
            quesum += my_d[ei];
          }
          // We can assume that at least 1 element is in queue
          while(quesum < que.size() * my_d[que.front()])
          {
            int tqi = que.front();
            que.pop();
            que.push(tqi);
          }
        }
      }
    }
  }
} // namespace PICHULIA

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
    tq.reserve(n);
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
    "Full random with connected  ",
    "Stressful connect for dijk 1",
    "Stressful connect for dijk 2",
    "Full connected prefect graph",
    "Sparse connected 2D space   ", ///< This tc spend near 10 minute. Just skip it normal case.
};
const string type_name[] = {
  "standard dijkstra",
  "standard spfa    ",
  "spfa with SLF    ",
  "spfa with LLL    ",
  "priority_map     ",
};
void (*const op_func[])(void) = {
  PICHULIA::process_priority_queue,
  PICHULIA::process_spfa,
  PICHULIA::process_spfa_slf,
  PICHULIA::process_spfa_lll,
  PICHULIA::process_priority_map,
};
const int tv_max = 4;
const int op_max = 5;
static_assert(sizeof(tv_name) / sizeof(tv_name[0]) >= tv_max);
static_assert(sizeof(type_name) / sizeof(type_name[0]) >= op_max);
static_assert(sizeof(op_func) / sizeof(op_func[0]) >= op_max);

bool judge(bool need_judge){
  int i, j, k;
  if(!need_judge)return true;
  for(i=0;i<n;i++){
    if(orig_d[i] != my_d[i]){
      printf("pung at %s %d, (you : %lld, expect : %lld)\n",type_name[op_type].c_str(), i, my_d[i], orig_d[i]);
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
    v[i].clear();
    v[i].shrink_to_fit();
    random_box[i] = i;
  }

  shuffle(random_box, random_box+n, rnd);

  std::set<pii> ss;

  si = random_box[0];
  int edge_cnt=0;
  if(tv == 1)
  {
    // stressful for dijkstra. We don't care about MIN_VALUE, MAX_VALUE here.
    int tn = n-nextint(10, 100);
    if(m < 2*(tn-1) + (n-tn))m = 2*(tn-1) + (n-tn);
    int target_value = 2*n+2;
    for(i=1;i<tn;i++){
      int si = random_box[0];
      int ei = random_box[i];
      ss.insert(pii(si, ei));
      v[si].push_back(pil(ei, i));
      edge_cnt++;
    }
    for(i=1;i<tn;i++){
      int si = random_box[i];
      int ei = random_box[tn];
      ss.insert(pii(si, ei));
      v[si].push_back(pil(ei, target_value + n - 2*i));
      edge_cnt++;
    }
    for(i=0;i<n;i++){
      int si = random_box[tn];
      int ei = random_box[i];
      if(i == tn)continue;
      ss.insert(pii(si, ei));
      v[si].push_back(pil(ei, nextint(MIN_VALUE, MAX_VALUE)));
      edge_cnt++;
    }
    while(edge_cnt < m){
      int si = random_box[nextint(0, n-1)];
      int ei = random_box[nextint(0, n-1)];
      if(si == ei)continue;
      if(ss.find(pii(si, ei)) != ss.end())continue;

      ss.insert(pii(si, ei));
      v[si].push_back(pil(ei, nextint(target_value + 2*n, target_value + 3*n)));
      edge_cnt++;
    }
  }
  else if(tv == 2)
  {
    // stressful for dijkstra. We don't care about MIN_VALUE, MAX_VALUE here.
    int tn = MAX_M/MAX_N - 1;
    if(m < tn*n-1) m = tn*n-1;
    int target_value = 2*n+2;
    for(int j=0; j<tn; j++){
      for(i=tn;i<n;i++){
        int si = random_box[j];
        int ei = random_box[i];
        ss.insert(pii(si, ei));
        v[si].push_back(pil(ei, target_value*2 + tn*2 + (tn - j*2)));
        edge_cnt++;
      }
      if(j != 0){
        int si = random_box[j-1];
        int ei = random_box[j];
        ss.insert(pii(si, ei));
        v[si].push_back(pil(ei, 1));
        edge_cnt++;
      }
    }

    while(edge_cnt < m){
      int si = random_box[nextint(tn, n-1)];
      int ei = random_box[nextint(tn, n-1)];
      if(si == ei)continue;
      if(ss.find(pii(si, ei)) != ss.end())continue;

      ss.insert(pii(si, ei));
      v[si].push_back(pil(ei, nextint(1, target_value)));
      edge_cnt++;
    }
  }
  else if(tv == 3)
  {
    //n = (int)floor(sqrt(MAX_M));
    n = 5000;
    m = n*(n-1);
    si = 0;
    for(i=0;i<n;i++){
      for(j=i+1;j<n;j++){
        int si = i;
        int ei = j;
        v[si].push_back(pil(ei, nextint(MIN_VALUE, MAX_VALUE)));
        v[ei].push_back(pil(si, nextint(MIN_VALUE, MAX_VALUE)));
      }
    }
    for(i=0;i<n;i++){
      shuffle(v[i].begin(), v[i].end(), rnd);
    }
  }
  else if(tv == 4)
  {
    //n = (int)floor(sqrt(MAX_M));
    n = 50000;
    m = 0;
    si = 0;
    vector<std::pair<lld, lld>> pt(n);
    for(i=0;i<n;i++){
      pt[i].first = nextint(0, 500'000'000);
      pt[i].second = nextint(0, 500'000'000);
    }
    auto cal_dist = [](const std::pair<lld, lld>& p, const std::pair<lld, lld>& q){
        lld dx = p.first - q.first;
        lld dy = p.second - q.second;
        lld dist = (lld)(sqrt(dx*dx + dy*dy)) - 1;
        if(dist < 1) dist = 1;
        return dist;
    };
    for(i=0;i<n;i++){
      // Connect only for short enough points
      lld min_dist = -1;
      for(j=0;j<n;j++){
        int si = i;
        int ei = j;
        if(i==j)continue;
        lld dist = cal_dist(pt[si], pt[ei]);
        if(min_dist < 0 || min_dist > dist){
          min_dist = dist;
        }
      }
      for(j=0;j<n;j++){
        int si = i;
        int ei = j;
        if(i==j)continue;
        lld dist = cal_dist(pt[si], pt[ei]);
        if(dist * 2 <= min_dist * 11)
        {
          v[si].push_back(pil(ei, dist));
          m++;
        }
      }
    }
    for(i=0;i<n;i++){
      shuffle(v[i].begin(), v[i].end(), rnd);
    }
  }
  else // if tv == 0
  {
    for(i=1;i<n;i++){
      int si = random_box[nextint(0, i-1)];
      int ei = random_box[i];
      ss.insert(pii(si, ei));
      v[si].push_back(pil(ei, nextint(MIN_VALUE, MAX_VALUE)));
      edge_cnt++;
    }
    while(edge_cnt < m){
      int si = random_box[nextint(0, n-1)];
      int ei = random_box[nextint(0, n-1)];
      if(si == ei)continue;
      if(ss.find(pii(si, ei)) != ss.end())continue;

      ss.insert(pii(si, ei));
      v[si].push_back(pil(ei, nextint(MIN_VALUE, MAX_VALUE)));
      edge_cnt++;
    }
    for(i=0;i<n;i++){
      shuffle(v[i].begin(), v[i].end(), rnd);
    }
  }
}
void test_all(int tv)
{
  for(int repeat_cnt; repeat_cnt < tc_count; repeat_cnt++)
  {
    generate_a(tv);
    for(op_type = 0; op_type < op_max; op_type++)
    {
      inil(op_type != 0);
      long t1, t2;
      t1 = clock();
      op_func[op_type]();
      t2 = clock();
      //printf("tv %3d %s // %ld ms\n", op_type, type_name[op_type].c_str(), t2 - t1);
      type_sum[op_type] += (t2 - t1) * 1000 / CLOCKS_PER_SEC;
      assert(judge(op_type != 0));
    }
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
    test_all(tv);
    printf("test type : %s, n : %d, m : %d, repeat %d times.\n", tv_name[tv].c_str(), n, m, tc_count);
    for(i=0;i<op_max;i++){
      printf("%s : %18lld ms\n", type_name[i].c_str(), type_sum[i]);
    }
    tv++;
  }
}