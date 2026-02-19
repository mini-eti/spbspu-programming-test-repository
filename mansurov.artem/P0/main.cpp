#include <iostream>
#include <limits>
#include <cstring>

namespace goltsov
{
  double my_abs(double x)
  {
    return x < 0.0 ? -x : x;
  }

  double sqrt_newton(double x);

  int* sort(int* a, size_t n)
  {
    for (size_t i = 0; i < n; ++i)
    {
      for (size_t j = i + 1; j < n; ++j)
      {
        if (a[j] < a[i])
        {
          int temp = a[i];
          a[i] = a[j];
          a[j] = temp;
        }
      }
    }
    return a;
  }

  double median(int* a, size_t n)
  {
    if (n % 2 == 0)
    {
      return static_cast<double>(a[n/2] + a[n/2 - 1]) / 2.0;
    }
    else
    {
      return static_cast<double>(a[n/2]);
    }
  }

  int* resize_with_copy(int* a, int* b, size_t old_n, size_t new_n)
  {
    int* new_a = new int[new_n];
    for (size_t i = 0; i < old_n; ++i)
    {
      new_a[i] = a[i];
    }
    for (size_t i = old_n; i < new_n; ++i)
    {
      new_a[i] = b[i - old_n];
    }
    return new_a;
  }

  int sumMas(int* a, size_t n)
  {
    int sum = 0;
    for (size_t i = 0; i < n; ++i)
    {
      sum += a[i];
    }
    return sum;
  }

  double average(int* a, size_t n)
  {
    int sum = sumMas(a, n);
    return static_cast<double>(sum) / static_cast<double>(n);
  }

  double sigma(int* a, size_t n, double aver)
  {
    double sum = 0.0;
    for (size_t i = 0; i < n; ++i)
    {
      double diff = static_cast<double>(a[i]) - aver;
      sum += diff * diff;
    }
    return sqrt_newton(sum / static_cast<double>(n));
  }

  double sqrt_newton(double x)
  {
    if (x < 0.0)
    {
      throw 1;
    }
    if (x == 0.0 || x == 1.0)
    {
      return x;
    }
    double guess = x / 2.0;
    const double epsilon = 1e-10;
    while (my_abs(guess * guess - x) > epsilon)
    {
      guess = (guess + x / guess) / 2.0;
    }
    return guess;
  }

  int count_positive(int* a, size_t n)
  {
    int cnt = 0;
    for (size_t i = 0; i < n; ++i)
    {
      if (a[i] > 0)
      {
        ++cnt;
      }
    }
    return cnt;
  }

  int count_negative(int* a, size_t n)
  {
    int cnt = 0;
    for (size_t i = 0; i < n; ++i)
    {
      if (a[i] < 0)
      {
        ++cnt;
      }
    }
    return cnt;
  }
}

int main(int argc, char** argv)
{
  if (argc != 2)
  {
    return 4;
  }

  const char* trait = argv[1];

  size_t total_size = 0;
  int* all_el = nullptr;
  size_t empty = 0;

  while (true)
  {
    size_t n = 0;
    if (!(std::cin >> n))
    {
      if (std::cin.eof())
      {
        if (total_size == 0)
        {
          return 6;
        }
        break;
      }
      else
      {
        return 2;
      }
    }
    if (n == 0)
    {
      empty += 1;
      continue;
    }
    int* mas = nullptr;
    try
    {
      mas = new int[n];
    }
    catch (...)
    {
      return 1;
    }
    for (size_t i = 0; i < n; ++i)
    {
      if (!(std::cin >> mas[i]))
      {
        if (std::cin.eof())
        {
          if (i == 0)
          {
            delete[] mas;
            return 3;
          }
          else
          {
            delete[] mas;
            return 7;
          }
        }
        else
        {
          delete[] mas;
          return 2;
        }
      }
    }
    int* new_all = goltsov::resize_with_copy(all_el, mas, total_size, total_size + n);
    delete[] all_el;
    delete[] mas;
    all_el = new_all;
    total_size += n;
  }

  if (total_size == 0)
  {
    return 6;
  }

  goltsov::sort(all_el, total_size);

  double avg = goltsov::average(all_el, total_size);
  double sig = goltsov::sigma(all_el, total_size, avg);
  double med = goltsov::median(all_el, total_size);
  int pos = goltsov::count_positive(all_el, total_size);
  int neg = goltsov::count_negative(all_el, total_size);

  if (strcmp(trait, "size") == 0)
  {
    std::cout << total_size << '\n';
  }
  else if (strcmp(trait, "median") == 0)
  {
    std::cout << med << '\n';
  }
  else if (strcmp(trait, "average") == 0)
  {
    std::cout << avg << '\n';
  }
  else if (strcmp(trait, "sigma") == 0)
  {
    std::cout << sig << '\n';
  }
  else if (strcmp(trait, "positive") == 0)
  {
    std::cout << pos << '\n';
  }
  else if (strcmp(trait, "negative") == 0)
  {
    std::cout << neg << '\n';
  }
  else if (strcmp(trait, "empty") == 0)
  {
    std::cout << empty << '\n';
  }
  else if (strcmp(trait, "all") == 0)
  {
    std::cout << total_size << ' ' << med << ' ' << avg << ' ' << sig << ' ' << empty << '\n';
  }
  else if (strcmp(trait, "maxln") && strcmp(trait, "maxseq") && strcmp(trait, "minln") && strcmp(trait, "minseq")
    && strcmp(trait, "medianln") && strcmp(trait, "sum-negative") && strcmp(trait, "sum-positive") && strcmp(trait, "dobsov"))
  {
    delete[] all_el;
    return 5;
    std::cerr << "<NOT SUPPORT>" << '\n';
  }
  else
  {
    std::cout << "<NOT SUPPORT>" << '\n';
  }

  delete[] all_el;
  return 0;
}