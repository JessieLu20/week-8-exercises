#include <iostream>
#include <chrono>
#include <memory>
#include <cmath>

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::milliseconds;

int main() {

  const int N = 800000000;
  double dx = 1.0f/N;

  auto start = high_resolution_clock::now();

  double sum = 0.0f;
 
  
  #pragma omp parallel
  {
    double partial_sums = 0.0f;
    #pragma omp for
    for(int i=0; i<N; ++i) {
      double x = i*dx;
      partial_sums += 4.0f/(1.0f + x*x)*dx;
    }
    #pragma omp atomic
    sum+=partial_sums;
  }


  auto stop = high_resolution_clock::now();
  auto duration = duration_cast<milliseconds>(stop - start);

  std::cout << "Result: " << sum << std::endl;
  std::cout << "Time for " << N << " iterations: " << duration.count() << std::endl;

  return 0;
}
