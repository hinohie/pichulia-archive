const int MAX_N = 1000000;
const int SMALL_N = 20;
const int MIN_VALUE = -1000000000;
const int MAX_VALUE = 1000000000;

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