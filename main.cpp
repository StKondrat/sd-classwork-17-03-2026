#include <iostream>
#include "top-it-vector.hpp"

bool testEmptyVector()
{
  topit::Vector< int > v;
  return v.isEmpty();
}

bool testGetSize()
{
  topit::Vector< int > v;
  v.pushBack(1);
  bool res = v.getSize() == 1;
  return res;
}

bool testGetCapacity()
{
  topit::Vector< int > v;
  v.pushBack(1);
  bool res = v.getCapacity() == 1;
  return res;
}

bool testPushBack()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  bool res = v.getSize() == 2 && v.getCapacity() == 2;
  return res;
}

bool testPopBack()
{
  topit::Vector< int > v;
  v.pushBack(1);
  v.pushBack(2);
  v.popBack();
  bool res = v.getSize() == 1 && v.getCapacity() == 2;
  return res;
}

int main()
{
  using test_t = std::pair< const char *, bool(*)() >;
  test_t tests[] = 
  {
    { "Empty vector", testEmptyVector },
    { "Get size", testGetSize },
    { "Get capacity", testGetCapacity },
    { "Push back", testPushBack },
    { "Pop back", testPopBack }
  };

  const size_t count = sizeof(tests) / sizeof(test_t);
  std::cout << std::boolalpha;
  bool pass = true;

  for (size_t i = 0; i < count; ++i)
  {
    bool res = tests[i].second();
    std::cout << tests[i].first << ": " << res << "\n";
    pass = pass && res;
  }

  std::cout << "RESULT: " << pass << "\n";
}
