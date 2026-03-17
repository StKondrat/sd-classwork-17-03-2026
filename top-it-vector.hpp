#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP

#include <cstddef>

namespace
{
  template< class T >
  struct Vector
  {
    private:
      T * data;
      size_t size;
      size_t capacity;
  };
}

#endif