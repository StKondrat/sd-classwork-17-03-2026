#ifndef TOP_IT_VECTOR_HPP
#define TOP_IT_VECTOR_HPP

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace topit
{
  template< class T >
  struct Vector
  {
    Vector();
    ~Vector();
    Vector(const Vector &);
    Vector(Vector &&) noexcept;
    Vector(size_t size, const T & init);
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
    void insert(size_t i, const Vector< T > & rhs, size_t start, size_t end);
    void erase(size_t i);
    void erase(size_t start, size_t end);
    void swap(Vector< T > & rhs) noexcept;

    private:
      T * data_;
      size_t size_;
      size_t capacity_;
      explicit Vector(size_t size);
  };
  template< class T >
  bool operator==(const Vector< T > & lhs, const Vector< T > & rhs);
}

template< class T >
topit::Vector< T >::Vector():
  data_(nullptr),
  size_(0),
  capacity_(0)
{}

template< class T >
topit::Vector< T >::~Vector()
{
  delete[] data_;
}

template< class T >
topit::Vector< T >::Vector(const Vector< T > & rhs):
  Vector(rhs.getSize())
{
  for (size_t i = 0; i < rhs.getSize(); ++i)
  {
    data_[i] = rhs[i];
  }
}

template< class T >
topit::Vector< T >::Vector(Vector< T > && rhs) noexcept:
  data_(rhs.data_),
  size_(rhs.size_),
  capacity_(rhs.capacity_)
{
  rhs.data_ = nullptr;
  rhs.size_ = 0;
  rhs.capacity_ = 0;
}

template< class T >
topit::Vector< T >::Vector(size_t size, const T & init):
  Vector(size)
{
  for (size_t i = 0; i < size; ++i)
  {
    data_[i] = init;
  }
}

template< class T >
topit::Vector< T > & topit::Vector< T >::operator=(const Vector< T > & rhs)
{
  Vector< T > cpy = rhs;
  swap(cpy);
  return *this;
}

template< class T >
topit::Vector< T > & topit::Vector< T >::operator=(Vector< T > && rhs)
{
  Vector< T > cpy(std::move(rhs));
  swap(cpy);
  return *this;
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
  const T & ret = cthis->at(id);
  return const_cast< T & >(ret);
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
void topit::Vector< T >::pushBack(const T & v)
{
  if (size_ < capacity_)
  {
    data_[size_] = v;
    ++size_;
    return;
  }

  T * newData = nullptr;
  try
  {
    newData = new T[capacity_ + 1];
    for (size_t i = 0; i < size_; ++i)
    {
      newData[i] = data_[i];
    }
    newData[size_] = v;
  }
  catch(...)
  {
    delete[] newData;
    throw;
  }
  delete[] data_;
  data_ = newData;
  ++capacity_;
  ++size_;
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
void topit::Vector< T >::insert(size_t i, const T & v)
{
  if (i > size_)
  {
    throw std::out_of_range("bad id");
  }

  const size_t newCapacity = (size_ < capacity_) ? capacity_ : (capacity_ + 1);
  T * newData = nullptr;
  try
  {
    newData = new T[newCapacity];
    for (size_t j = 0; j < i; ++j)
    {
      newData[j] = data_[j];
    }
    newData[i] = v;
    for (size_t j = i; j < size_; ++j)
    {
      newData[j + 1] = data_[j];
    }
  }
  catch(...)
  {
    delete[] newData;
    throw;
  }

  delete[] data_;
  data_ = newData;
  capacity_ = newCapacity;
  ++size_;
}

template< class T >
void topit::Vector< T >::insert(size_t i, const Vector< T > & rhs, size_t start, size_t end)
{
  if (i > size_ || start > end || end > rhs.getSize())
  {
    throw std::out_of_range("bad id");
  }

  topit::Vector< T > temp = *this;
  size_t pos = i;

  for (size_t j = start; j < end; ++j)
  {
    temp.insert(pos++, rhs[j]);
  }

  *this = temp;
}

template< class T >
void topit::Vector< T >::erase(size_t i)
{
  if (i >= size_)
  {
    throw std::out_of_range("bad id");
  }

  T * newData = nullptr;
  try
  {
    newData = new T[capacity_];
    for (size_t j = 0; j < i; ++j)
    {
      newData[j] = data_[j];
    }
    for (size_t j = i; j < size_ - 1; ++j)
    {
      newData[j] = data_[j + 1];
    }
  }
  catch(...)
  {
    delete[] newData;
    throw;
  }

  delete[] data_;
  data_ = newData;
  --size_;
}

template< class T >
void topit::Vector< T >::erase(size_t start, size_t end)
{
  if (end > size_ || start > end)
  {
    throw std::out_of_range("bad id");
  }

  topit::Vector< T > temp = *this;

  for (size_t i = start; i < end; ++i)
  {
    temp.erase(start);
  }

  *this = temp;
}

template< class T >
void topit::Vector< T >::swap(Vector< T > & rhs) noexcept
{
  std::swap(data_, rhs.data_);
  std::swap(size_, rhs.size_);
  std::swap(capacity_, rhs.capacity_);
}

template< class T >
topit::Vector< T >::Vector(size_t size):
  data_(size ? new T[size] : nullptr),
  size_(size),
  capacity_(size)
{}

template< class T >
bool topit::operator==(const topit::Vector< T > & lhs, const topit::Vector< T > & rhs)
{
  bool isEqual = lhs.getSize() == rhs.getSize();
  for (size_t i = 0; (i < lhs.getSize()) && (isEqual = isEqual && lhs[i] == rhs[i]); ++i);
  return isEqual;
}

#endif
