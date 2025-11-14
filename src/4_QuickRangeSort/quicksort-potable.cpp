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