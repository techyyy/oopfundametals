#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

class sorting{
      public:
      template <typename T> size_t getMax(vector<T> &arr, int n) 
      { 
            T mx = arr[0]; 
            for (int i = 1; i < n; i++) 
                  if (arr[i] > mx) 
                        mx = arr[i]; 
            return mx; 
      } 

      template <typename T> void countSort(vector<T> &arr, int n, int exp) 
      { 
            T output[n]; 
            int i, count[10] = {0}; 
            for (i = 0; i < n; i++) 
                  count[(arr[i]/exp) % 10 ]++; 

            for (i = 1; i < 10; i++) 
                  count[i] += count[i - 1]; 

            for (i = n - 1; i >= 0; i--) 
            { 
                  output[count[ (arr[i]/exp)%10 ] - 1] = arr[i]; 
                  count[ (arr[i]/exp)%10 ]--; 
            } 
            
            for (i = 0; i < n; i++) 
                  arr[i] = output[i]; 
      } 

      template <typename T> void radixsort(vector<T> &arr, int n) 
      { 
            size_t m = getMax(arr, n); 
            for (int exp = 1; m/exp > 0; exp *= 10) 
                  countSort(arr, n, exp); 
      } 

      template <typename T> void insertionSort(vector<T> &arr, int n)  
      {  
            int i, j;  
            size_t key;
            for (i = 1; i < n; i++) 
            {  
                  key = arr[i];  
                  j = i - 1;  
            
                  while (j >= 0 && arr[j] > key) 
                  {  
                        arr[j + 1] = arr[j];  
                        j = j - 1;  
                  }  
                  arr[j + 1] = key;  
            }  
      }  

      template <typename T> merge(vector<T> &arr, size_t l, size_t m, size_t r) 
      { 
            int i, j, k; 
            size_t n1 = m - l + 1; 
            size_t n2 = r - m; 
            
            vector<T> L(n1), R(n2); 
            
            for (i = 0; i < n1; i++) 
                  L[i] = arr[l + i]; 
            for (j = 0; j < n2; j++) 
                  R[j] = arr[m + 1 + j]; 
            
            i = 0; 
            j = 0; 
            k = l; 
            while (i < n1 && j < n2) { 
                  if (L[i] <= R[j]) { 
                        arr[k] = L[i]; 
                        i++; 
                  } 
                  else { 
                        arr[k] = R[j]; 
                        j++; 
                  } 
                  k++; 
            } 

            while (i < n1) { 
                  arr[k] = L[i]; 
                  i++; 
                  k++; 
            } 
            
            while (j < n2) { 
                  arr[k] = R[j]; 
                  j++; 
                  k++; 
            } 
      } 
      
      template <typename T> void mergeSort(vector<T> &arr, size_t l, size_t r) 
      { 
            if (l < r) { 
                  size_t m = l + (r - l) / 2; 
            
                  mergeSort(arr, l, m); 
                  mergeSort(arr, m + 1, r); 
            
                  merge(arr, l, m, r); 
            } 
      } 

      template <typename T> size_t medianOfThree(T &a, T &b, T &c, size_t ai, size_t bi, size_t ci)
      {
            if (a >= b && a <= c)
                  return ai;
            if (b >= a && b <= c)
                  return bi;
            return ci;
      }

      template <typename T> size_t quicksortPartition(vector<T> &A, size_t lo, size_t hi)
      {
            size_t ci = (int)(0.5*(lo+hi)+0.5);
            size_t pivotIndex = medianOfThree(A[lo], A[ci], A[hi], lo, ci, hi);
            T pivot = A[pivotIndex];

            size_t i = lo;
            size_t j = hi;
            while(true)
            {
                  while(A[i] <= pivot && i < pivotIndex) i++;
                  while(A[j] >= pivot && j > pivotIndex) j--;
                  if (i == pivotIndex && j == pivotIndex)
                        return pivotIndex;

                  T tmp = A[i];
                  A[i] = A[j];
                  A[j] = tmp;

                  if(i == pivotIndex)
                        pivotIndex = j;
                  else if(j == pivotIndex)
                        pivotIndex = i;
            }
      }

      template <typename T> void quicksort(vector<T> &A, size_t lo, size_t hi)
      {
            if (lo < hi)
            {
                  size_t p = quicksortPartition<T>(A, lo, hi);
                  if (p > 0) 
                        quicksort<T>(A, lo, p-1);
                  quicksort<T>(A, p+1, hi);
            }
      }

      template <typename T> void quicksort(vector<T> &A)
      {
            if (A.size() <= 1)
                  return;
            quicksort(A, 0, A.size()-1);
      }

      template <typename T> bool resultIsValid(const vector<T> &A)
      {
            for(size_t i = 1; i < A.size(); i++)
                  if (A[i] < A[i-1])
                        return false;
            return true;
      }

      void fillVector(vector<double> &test){
            int numVals = rand() % 100;
            for(int i=0;i<1000000;i++)
                  test.insert(test.begin(), (rand() % 100) - 50);
      }

      void testSorts()
      {
                  vector<double> test(1000000);
                  fillVector(test);
                  quicksort(test);
                  bool valid = resultIsValid(test);
                  cout << "Quicksort is " << valid << endl;
                  fillVector(test);
                  mergeSort(test, 0, 999999);
                  valid = resultIsValid(test);
                  cout << "Mergesort is " << valid << endl;
                  fillVector(test);
                  insertionSort(test, 1000000);
                  valid = resultIsValid(test);
                  cout << "Insertionsort is " << valid << endl;
                  fillVector(test);
                  radixsort(test, 1000000);
                  valid = resultIsValid(test);
                  cout << "Radixsort is " << valid << endl;
	}

      };




