#include <algorithm>
#include <iostream>
#include <math.h>
#include <string>
#include <utility>
#include <vector>

bool is_prime(int n) {
  if (n <= 2)
    return n == 2;
  if (n % 2 == 0)
    return false;
  int i = 3;
  while (true) {
    if (i * i > n)
      return true;
    if (n % i == 0)
      return false;
    i += 2;
  }
}

void f(int n, std::vector<int> const &primes) {
  int num = 1;

  std::vector<std::pair<int, int>> res;
  while (true) {
    std::vector<bool> vec(n + 1, true);
    vec.at(0) = false;
    vec.at(1) = false;
    vec.at(n - 1) = false;
    vec.at(n) = false;

    for (int j = 0; j < num; j++) {
      int p = primes.at(j);
      for (int k = p; k < n; k += p) {
        vec.at(k) = false;
      }
    }
    int count = std::count(vec.cbegin(), vec.cend(), true);
    res.push_back({primes.at(num - 1), count});
    num++;
    if (count == 0)
      break;
  }

  for (size_t i = res.size(); i > 0; i--) {
    const std::pair<int, int> &pair = res.at(i - 1);
    if (i == res.size())
      continue;
    const std::pair<int, int> &pair2 = res.at(i);

    int v = pair.second;
    int v2 = pair2.second;

    if (v == v2 + 1)
      continue;

    int sqrtN = sqrtl(n);
    int sqrtP = -1;
    while (true) {
      if (is_prime(sqrtN)) {
        sqrtP = sqrtN;
        break;
      }
      sqrtN--;
    }

    std::cout << n << " " << pair2.first << " " << sqrtP << "\n";
    break;
  }
}

int main() {
  const int N = 10000;

  std::vector<int> primes;
  for (int i = 1; i <= N; i++) {
    if (is_prime(i))
      primes.push_back(i);
  }

  for (int i = 10; i <= N; i += 2) {
    f(i, primes);
  }
}
