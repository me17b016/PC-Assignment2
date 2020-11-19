#include<iostream>
#include<cmath>
#include<omp.h>
#include<string>
#include<chrono>
#include<time.h>
#include<vector>

typedef long double ld;

using namespace std;

int main(int argc, char** argv) {

  int nthreads = 4;
  int N = stoi(argv[1]);
  int n = N + 2;
  double T = stold(argv[2]);
  double *arr = (double*)malloc((N * N + 4 * (N + 1)) * sizeof(double));
 
  for (int i = 0; i < 2; i++) {
    for (int j = 1; j < N + 1; j++) {
      arr[i * (N + 2) + j] = rand() % 50;
      if (!i || !j || i == N + 1 || j == N + 1) arr[i * n + j] = 0;
    }
  }
  int cnt = 0;

  // Normal code
  /*vector<vector<double>> a1(N + 2, vector<double>(N + 2, 0));
  for (int i = 1; i < N + 1; i++) {
    for (int j = 1; j < N + 1; j++) a1[i][j] = arr[i * (N + 2) + j];
  }
  while (1) {
    vector<vector<double>> a2(N + 2, vector<double>(N + 2, 0));
    double ma = 0;
    for (int i = 1; i < N + 1; i++) {
      for (int j = 1; j < N + 1; j++) {
        a2[i][j] = (a1[i][j] + a1[i - 1][j] + a1[i + 1][j] + a1[i][j - 1] + a1[i][j + 1]) / 5;
        ma = max(ma, abs(a1[i][j] - a2[i][j]));
      }
    }
    if (ma > T) {
      cnt++;
      for (int i = 1; i < N + 1; i++) {
        for (int j = 1; j < N + 1; j++) a1[i][j] = a2[i][j];
      }
    }
    else break;
  }
  cout << cnt << '\n';
  //*/

  cnt = 0;
  double* a2 = new double[n * n];
  for (int i = 0; i < n * n; i++) a2[i] = 0;
  auto start = chrono::high_resolution_clock::now();
  while (1) {
    double ma = 0;
    #pragma omp parallel for collapse(2) schedule(static) num_threads(nthreads) reduction(max:ma) 
    for (int i = 1; i < N + 1; i++) {
      for (int j = 1; j < N + 1; j++) {
        int t = i * n + j;
        a2[t] = (arr[t] + arr[t - n] + arr[t + n] + arr[t - 1] + arr[t + 1]) / 5;
        ma = max(ma, abs(arr[t] - a2[t]));
      }
    }
    if (ma > T) {
      cnt++;
      #pragma omp parallel for collapse(2) schedule(static) num_threads(4)
      for (int i = 1; i < N + 1; i++) {
        for (int j = 1; j < N + 1; j++) {
          int t = i * n + j; arr[t] = a2[t];
        }
      }
    }
    else break;
  }
  auto end = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::microseconds>(end - start);
  cout << "Time take is " << duration.count() << " us" << '\n';
  cout << "Number of Iterations: " << cnt << '\n';
  cout << "Number of threads " << nthreads << '\n'; 
  cout << "----------------\n";
}

/***************
Code using single FOR LOOP
# Just copy paste this code in WHILE LOOP
--------------------------------------------

#pragma omp parallel for num_threads(4) schedule(static) reduction(max:ma)
  for (int i = 0; i < N * N; i++) {
    int t = n + (i / N) * n + 1 + i - (i / N) * N;
    a2[t] = (arr[t] + arr[t - n] + arr[t + n] + arr[t - 1] + arr[t + 1]) / 5;
    ma = max(ma, abs(a2[t] - arr[t]));
  }

  if (ma > T) {
    cnt++;
    #pragma omp parallel for schedule(static) num_threads(4)
    for (int i = 0; i < N * N; i++) {
      int t = n + (i / N) * n + 1 + i - (i / N) * N;
      arr[t] = a2[t];
    }
  }
  else break;

-------------------------------------------
**************/

/*************
SOME OBERVATIONS
CPU: Intel i5-8250U  8th generation 4 Cores
* Vector is slower than Array
* 1D array is faster than 2D
* Code runs fastest when Number of Threads == Num of CPU Cores (+- 1), for smaller N (<20) only 1 threads is giving best performance
* Above Code with single FOR LOOP is slighty slower than using "Collapse" clause in omp, 
  which means Collapse is very optimised implementation than mine
* Static scheduling is faster than Dynamic

******************/
