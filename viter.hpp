#ifndef VITER_HPP
#define VITER_HPP

namespace topit
{
  template< class T >
  struct Vector;

  template< class T >
  struct VIter
  {
    friend struct Vectror< T >;

    VIter();
    VIter< T > & operator++();
    VIter< T > & operator++(int);
    VIter< T > & operator--();
    VIter< T > & operator--(int);
    bool operator==(const VIter< T > & rhs) const;
    bool operator!=(const VIter< T > & rhs) const;
    T & operator*() const;
    T & operator->() const;

    private:
      T * val_;
      VIter(T * val):
        val_(val)
      {};
  };
}

#endif