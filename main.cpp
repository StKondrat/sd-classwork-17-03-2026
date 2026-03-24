#include <iostream>
#include "top-it-vector.hpp"

bool testEmptyVector()
{
  // std::cout << __func__ << "\n";
  topit::Vector< int > v;
  return v.isEmpty();
}

bool testElementInboundAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  try
  {
  int & val = v.at(0);
  return val == 1;
  }
  catch(...)
  {
    return false;
  }
}

bool testElementInboundConstAccess()
{
  topit::Vector< int > v;
  v.pushBack(1);
  const topit::Vector< int > & rv = v;

  try
  {
  const int & val = rv.at(0);
  return val == 1;
  }
  catch(...)
  {
    return false;
  }
}

bool testElementOutOfBoundConstAccess()
{
  const topit::Vector< int > v;
  try
  {
    v.at(0);
    return false;
  }
  catch(const std::out_of_range &)
  {
    return true;
  }
  catch(...)
  {
    return false;
  }
}

bool testElementOutOfBoundAccess()
{
  topit::Vector< int > v;
  try
  {
    v.at(0);
    return false;
  }
  catch(const std::out_of_range &)
  {
    return true;
  }
  catch(...)
  {
    return false;
  }
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
    { "Inbound access", testElementInboundAccess },
    { "Out of bound access", testElementOutOfBoundAccess},
    { "Inbound const access", testElementInboundConstAccess},
    { "Out of bound const access", testElementOutOfBoundConstAccess},
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
  // Подсчет пройденных/непройденных
  // Выводить только непройденные
}
