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