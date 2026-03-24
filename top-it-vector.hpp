#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP

#include <cstddef>

namespace topit
{
  template< class T >
  struct Vector
  {
    Vector();
    ~Vector();
    Vector(const Vector &);
    Vector(Vector &&);
    Vector< T > & operator=(const Vector< T > &);
    Vector< T > & operator=(Vector< T > &&);

    bool isEmpty() const noexcept;
    size_t getSize() const noexcept;
    size_t getCapacity() const noexcept;

    T & operator[](size_t id) noexcept;
    const T & operator[](size_t id) const noexcept;
    T & at(size_t id);
    const T & at(size_t id) const;

    void pushBack(const T & v);
    void popBack();
    void insert(size_t i, const T & v);
    void erase(size_t i);

    private:
      T * data_;
      size_t size_;
      size_t capacity_;
  };
  template< class T >
  bool operator==(const Vector< T > & lhs, const Vector< T > & rhs);
}

template< class T >
bool topit::Vector< T >::isEmpty() const noexcept
{
  return !size_;
}

template< class T >
size_t topit::Vector< T >::getSize() const noexcept
{
  return size_;
}

template< class T >
size_t topit::Vector< T >::getCapacity() const noexcept
{
  return capacity_;
}

template< class T >
void topit::Vector< T >::pushBack(const T & v)
{
  T * newData = nullptr;
  if (size_ == capacity_)
  {
    try
    {
      newData = new T[capacity_ + 1];
      for (size_t i = 0; i < size_; ++i)
      {
        newData[i] = data_[i];
      }
    }
    catch(...)
    {
      delete[] newData;
      throw;
    }
    ++capacity_;
    delete[] data_;
    data_ = newData;
  }
  data_[size_] = v;
  ++size_;
}

template< class T >
topit::Vector< T >::Vector(const Vector< T > & rhs)
{}

template< class T >
bool topit::operator==(const topit::Vector< T > & lhs, const topit::Vector< T > & rhs)
{
  bool isEqual = lhs.getSize() == rhs.getSize();
  for (size_t i = 0; (i < lhs.getSize()) && (isEqual = isEqual && lhs[i] == rhs[i]); ++i);
  return isEqual;
}

template< class T >
T & topit::Vector< T >::operator[](size_t id) noexcept
{
  const Vector< T > * cthis = this;
  return const_cast< T & >((*cthis)[id]);
}

template< class T >
const T & topit::Vector< T >::operator[](size_t id) const noexcept
{
  return data_[id];
}

template< class T >
T & topit::Vector< T >::at(size_t id)
{
  const Vector< T > * cthis = this;
  return const_cast< T & >(cthis->at(id));
}

template< class T >
const T & topit::Vector< T >::at(size_t id) const
{
  if (id < getSize())
  {
    return (*this)[id];
  }
  throw std::out_of_range("bad id");
}

template< class T >
void topit::Vector< T >::popBack()
{
  if (size_ > 0)
  {
    --size_;
  }
}

template< class T >
topit::Vector< T >::~Vector()
{
  delete[] data_;
}

template< class T >
topit::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}

#endif