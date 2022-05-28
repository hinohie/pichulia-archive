const int MAX_N = 1000000;
const int SMALL_N = 20;
const int MIN_VALUE = -1000000000;
const int MAX_VALUE = 1000000000;

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