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

bool testCopyConstructorForEmpty()
{
  topit::Vector< int > v;
  topit::Vector< int > yav = v;
  return v == yav;
}

bool testCopyConstructorForNonEmpty()
{
  topit::Vector< int > v;
  v.pushBack(1);
  topit::Vector< int > yav = v;
  return v == yav;
}

bool testCopyOperatorForEmpty()
{
  topit::Vector< int > v;
  topit::Vector< int > cv;
  cv = v;
  bool res = cv == v;
  v.pushBack(1);
  res = res || !(v == cv);
  return res;
}

bool testCopyOperatorForNonEmpty()
{
  topit::Vector< int > v;
  v.pushBack(1);
  topit::Vector< int > cv;
  cv = v;
  return cv == v;
}

bool testMoveConstructorForEmpty()
{
  topit::Vector< int > v;
  topit::Vector< int > mcv = std::move(v);
  try
  {
    v.at(0);
    return false;
  }
  catch (std::out_of_range &)
  {
    return mcv.isEmpty();
  }
  catch (...)
  {
    return false;
  }
}

bool testMoveConstructorForNonEmpty()
{
  topit::Vector< int > v;
  v.pushBack(1);
  topit::Vector< int > mcv = std::move(v);
  bool res = mcv.getSize() == 1 && mcv[0] == 1;
  try
  {
    v.at(0);
    return false;
  }
  catch (std::out_of_range &)
  {
    return res;
  }
  catch (...)
  {
    return false;
  }
}

bool testMoveOperatorForEmpty()
{
  topit::Vector< int > v;
  topit::Vector< int > mov;
  mov = std::move(v);
  try
  {
    v.at(0);
    return false;
  }
  catch (std::out_of_range &)
  {
    return mov.isEmpty();
  }
  catch (...)
  {
    return false;
  }
}

bool testMoveOperatorForNonEmpty()
{
  topit::Vector< int > v;
  v.pushBack(1);
  topit::Vector< int > mov;
  mov = std::move(v);
  bool res = mov.getSize() == 1 && mov[0] == 1;
  try
  {
    v.at(0);
    return false;
  }
  catch (std::out_of_range &)
  {
    return res;
  }
  catch (...)
  {
    return false;
  }
}

int main()
{
  using test_t = std::pair< const char *, bool(*)() >;
  test_t tests[] =
  {
    { "Empty vector", testEmptyVector },
    { "Inbound access", testElementInboundAccess },
    { "Out of bound access", testElementOutOfBoundAccess },
    { "Inbound const access", testElementInboundConstAccess },
    { "Out of bound const access", testElementOutOfBoundConstAccess },
    { "Get size", testGetSize },
    { "Get capacity", testGetCapacity },
    { "Push back", testPushBack },
    { "Pop back", testPopBack },
    { "Copy empty vector", testCopyConstructorForEmpty },
    { "Copy non-empty vector", testCopyConstructorForNonEmpty },
    { "Copy empty vector with operator ", testCopyOperatorForEmpty },
    { "Copy non-empty vector with operator", testCopyOperatorForNonEmpty },
    { "Move empty vector ", testMoveConstructorForEmpty },
    { "Move non-empty vector", testMoveConstructorForNonEmpty},
    { "Move empty vector with operator ", testMoveOperatorForEmpty },
    { "Move non-empty vector with operator", testMoveOperatorForNonEmpty }
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
