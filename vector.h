//
// Created by jesus on 09.06.18.
//

#ifndef UNTITLED_fixed_vector_H
#define UNTITLED_fixed_vector_H

#include <iostream>
#include <cassert>
#include <cstring>

//std::string len_er = "СТОП! Это полиция вместимости вектора. Сейчас ты добавил элемент, когда не было свободного места. На этот раз без штрафов, впредь будь осторожнее!";

[[noreturn]] inline void throw_len_er() {
    throw std::length_error(
            "СТОП! Это полиция вместимости вектора. Сейчас ты добавил элемент, когда не было свободного места. На этот раз без штрафов, впредь будь осторожнее!");
};

template<typename T, std::size_t N>
struct fixed_vector {
    typedef T *iterator;
    typedef T const *const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
private:
    //T *_data;z
    typename std::aligned_storage<sizeof(T), alignof(T)>::type _data[N];
    std::size_t _size;
    std::size_t _capacity;

    std::size_t increase_capacity() const;

    void new_fixed_vector(std::size_t);

public:
    iterator begin();

    iterator end();

    const_iterator begin() const;

    const_iterator end() const;

    reverse_iterator rbegin();

    reverse_iterator rend();

    const_reverse_iterator rbegin() const;

    const_reverse_iterator rend() const;

    fixed_vector();

    //fixed_vector(std::size_t, T value = T());

    fixed_vector(fixed_vector const &other);

/*
    template<typename It>
    fixed_vector(It first, It last) {
        std::size_t _number = last - first;
        _data = (T *) operator new(sizeof(T) * _number);
        _size = _number;
        _capacity = _number;

        for (std::size_t i = 0; i < _size; ++i) {
            _data[i] = *(first + i);
        }
    }
*/
    ~fixed_vector();

    void push_back(T const &);

    void pop_back();

    T &back();

    T &front();

    T const &back() const;

    T const &front() const;

    T &get(std::size_t);

    bool empty() const;

    T &operator[](std::size_t);

    T const &operator[](std::size_t) const;

    fixed_vector &operator=(fixed_vector const &other);

    std::size_t size() const;

    std::size_t max_size() const;

    std::size_t capacity() const;

    T *data();

    T const *data() const;

    void reserve(std::size_t);

    void shrink_to_fit();

    void clear();

    iterator insert(const_iterator _pos, T const &value);

    iterator erase(const_iterator pos);

    iterator erase(const_iterator first, const_iterator last);

    //void resize(std::size_t, T value = T());

    //void assign(std::size_t, T value = T());

    void swap(fixed_vector &);

    //void swap(fixed_vector &a, fixed_vector &b);

    //void copy_all(T*, T *, std::size_t);
};

template<typename U>
void destroy(U *data, std::size_t size,
             typename std::enable_if<!std::is_trivially_destructible<U>::value>::type * = nullptr) {
    for (std::size_t i = size; i != 0; --i) {
        data[i - 1].~U();
    }
}

template<typename U>
void destroy(U *, std::size_t,
             typename std::enable_if<std::is_trivially_destructible<U>::value>::type * = nullptr) {}

template<typename U>
void copy_all(U *destination, U const *source, std::size_t size) {
    if (size != 0) {
        //destroy(destination, size);
        for (std::size_t i = 0; i != size; ++i)
            new(destination + i)U(source[i]);
    }
}

template<typename U>
void construct_all(U *destination, U const *source, std::size_t size, std::size_t size_destination) {
    destroy(destination, size_destination);
    for (std::size_t i = 0; i != size; ++i)
        new(destination + i)U(source[i]);
}

template<typename T, std::size_t N>
fixed_vector<T, N>::fixed_vector() {
    //_data = nullptr;
    _size = 0;
    _capacity = N;
}

/*
template<typename T, std::size_t N>
fixed_vector<T, N>::fixed_vector(std::size_t n, T value) {
    //fixed_vector();
    //_data = (T *) operator new(sizeof(T) * n);
    _size = n;
    _capacity = n;

    for (std::size_t i = 0; i < _size; ++i) {
        *(_data + i) = value;
    }
}*/

template<typename T, std::size_t N>
fixed_vector<T, N>::fixed_vector(fixed_vector const &other) : fixed_vector() {
    new_fixed_vector(other.size());
    copy_all(reinterpret_cast<T *>(_data), reinterpret_cast<const T *>(other._data), other._size);
    _size = other._size;
    _capacity = other._capacity;
}

template<typename T, std::size_t N>
fixed_vector<T, N>::~fixed_vector() {
    for (std::size_t i = 0; i < _size; ++i) {
        reinterpret_cast<const T *>(_data + i)->~T();
    }
    //operator delete(_data);
    _size = 0;
    _capacity = 0;
}

template<typename T, std::size_t N>
void fixed_vector<T, N>::new_fixed_vector(std::size_t new_capacity) {
    assert(new_capacity >= _size);
    fixed_vector<T, N> temp;
    if (new_capacity != 0) {
        //temp._data = (T *) operator new(sizeof(T) * new_capacity);
        temp._capacity = new_capacity;
        copy_all(reinterpret_cast<T *>(temp._data), reinterpret_cast<const T *>(_data), _size);
        temp._size = _size;
    }
    swap(temp);
}

template<typename T, std::size_t N>
void fixed_vector<T, N>::push_back(const T &value) {
    if (_size != _capacity) {
        //_data[_size] = value;
        new(_data + _size)T(value);
        ++_size;
    } else {
        throw_len_er();
        /*fixed_vector<T, N> temp;
        temp.new_fixed_vector(increase_capacity());
        copy_all(temp._data, _data, _size);
        temp._size = _size;
        temp.push_back(value);
        swap(temp);*/
    }
}

template<typename T, std::size_t N>
void fixed_vector<T, N>::pop_back() {
    assert(_size != 0);
    reinterpret_cast<const T *>(_data + _size - 1)->~T();
    _size--;
}

template<typename T, std::size_t N>
T &fixed_vector<T, N>::back() {
    return *((T *) _data + _size - 1);
}

template<typename T, std::size_t N>
T const &fixed_vector<T, N>::back() const {
    return *((T *) _data + _size - 1);
    //return _data[_size - 1];
}

template<typename T, std::size_t N>
T &fixed_vector<T, N>::front() {
    return *((T *) _data);
}

template<typename T, std::size_t N>
T const &fixed_vector<T, N>::front() const {
    return *((T *) _data);
}

template<typename T, std::size_t N>
T &fixed_vector<T, N>::get(std::size_t i) {
    return *((T *) _data + i);
    //return (T)(_data[i]);
}

template<typename T, std::size_t N>
bool fixed_vector<T, N>::empty() const {
    return _size == 0;
}

template<typename T, std::size_t N>
T &fixed_vector<T, N>::operator[](std::size_t n) {
    //return _data[n];
    return *((T *) _data + n);
}

template<typename T, std::size_t N>
T const &fixed_vector<T, N>::operator[](std::size_t n) const {
    return _data[n];
}

template<typename T, size_t N>
fixed_vector<T, N> &fixed_vector<T, N>::operator=(const fixed_vector &other) {
    construct_all(reinterpret_cast<T *>(_data), reinterpret_cast<const T *>(other._data), other._size, _size);
    return *this;
}

template<typename T, std::size_t N>
std::size_t fixed_vector<T, N>::size() const {
    return _size;
}

template<typename T, std::size_t N>
std::size_t fixed_vector<T, N>::max_size() const {
    return _capacity;
}

template<typename T, std::size_t N>
std::size_t fixed_vector<T, N>::capacity() const {
    return _capacity;
}

template<typename T, std::size_t N>
T *fixed_vector<T, N>::data() {
    return (T *) _data;
}

template<typename T, std::size_t N>
T const *fixed_vector<T, N>::data() const {
    return (T *) _data;
}

template<typename T, std::size_t N>
void fixed_vector<T, N>::reserve(std::size_t n) {
    if (n < _capacity) {
        return;
    } else {
        new_fixed_vector(n);
    }
}

template<typename T, std::size_t N>
void fixed_vector<T, N>::shrink_to_fit() {

}

template<typename T, std::size_t N>
void fixed_vector<T, N>::clear() {
    destroy(_data, _size);
    for (std::size_t i = _size; i != 0; --i) {
        reinterpret_cast<const T *>(_data + i - 1)->~T();
    }
    _size = 0;
}

template<typename T, std::size_t N>
typename fixed_vector<T, N>::iterator fixed_vector<T, N>::insert(const_iterator _pos, const T &value) {
    iterator pos = (T *) _data + (_pos - (T *) _data);
    if (_size == _capacity) {
        throw_len_er();
        /*fixed_vector temp;
        temp.new_fixed_vector(increase_capacity());
        copy_all(temp._data, _data, pos - begin());
        temp._size = pos - begin();
        auto result = temp.end();
        temp.push_back(value);
        copy_all(temp.end(), pos, end() - pos);
        temp._size = temp._size + end() - pos;
        swap(temp);
        return result;*/
    }
    push_back(value);
    for (auto i = (end() - 1); i != pos; --i) {
        std::swap(*(i - 1), *i);
        //T _temp = *(i - 1);
        //*(i - 1) = *i;
        //*i = _temp;
    }
    //*pos = value;
    return pos;
}

template<typename T, std::size_t N>
typename fixed_vector<T, N>::iterator fixed_vector<T, N>::erase(const_iterator pos) {
    iterator _pos = (T *) _data + (pos - (T *) _data);
    return erase(_pos, _pos + 1);
}

template<typename T, std::size_t N>
typename fixed_vector<T, N>::iterator fixed_vector<T, N>::erase(const_iterator first, const_iterator last) {
    iterator _first = (T *) _data + (first - (T *) _data);
    iterator _last = (T *) _data + (last - (T *) _data);
    iterator result = _first;
    iterator finish = end();
    while (_last != finish) {
        T x = *_first;
        *_first = *_last;
        *_last = x;

        ++_first;
        ++_last;
    }
    destroy(_first, _last - _first);
    _size = _first - (T *) _data;
    return result;
}
/*
template<typename T, std::size_t N>
void fixed_vector<T, N>::resize(std::size_t n, T value) {
    fixed_vector<T, N> temp(n);
    if (_size > n) {
        copy_all(temp._data, _data, n);
    } else {
        copy_all(temp._data, _data, _size);
        for (std::size_t i = _size; i != n; ++i) {
            temp._data[i] = value;
        }
    }
    swap(temp);
}*/
/*
template<typename T, std::size_t N>
void fixed_vector<T, N>::assign(std::size_t n, T value) {
    fixed_vector<T, N> temp;
    for (std::size_t i = 0; i != n; ++i) {
        reinterpret_cast<T&>(temp._data[i]) = value;
    }
    destroy(_data, _size);
    swap(temp);
}*/

template<typename T, std::size_t N>
void fixed_vector<T, N>::swap(fixed_vector &other) {
    //using std::swap;
    //iterator __data = _data;
    std::size_t __size = _size;
    std::size_t __capacity = _capacity;
    construct_all(reinterpret_cast<T *>(_data), reinterpret_cast<const T *>(other._data), other._size, _size);
    //_data = other._data;
    _size = other._size;
    _capacity = other._capacity;
    construct_all(reinterpret_cast<T *>(other._data), reinterpret_cast<const T *>(_data), _size, other._size);
    //other._data = __data;
    other._size = __size;
    other._capacity = __capacity;

}

template<typename T, std::size_t N>
std::size_t fixed_vector<T, N>::increase_capacity() const {
    return (_capacity + 1) * 2;
}

template<typename T, std::size_t N>
typename fixed_vector<T, N>::iterator fixed_vector<T, N>::begin() {
    return (T *) _data;
}

template<typename T, std::size_t N>
typename fixed_vector<T, N>::iterator fixed_vector<T, N>::end() {
    return (T *) _data + _size;
}

template<typename T, std::size_t N>
typename fixed_vector<T, N>::const_iterator fixed_vector<T, N>::begin() const {
    return (T *) _data;
}

template<typename T, std::size_t N>
typename fixed_vector<T, N>::const_iterator fixed_vector<T, N>::end() const {
    return (T *) _data + _size;
}

template<typename T, std::size_t N>
typename fixed_vector<T, N>::reverse_iterator fixed_vector<T, N>::rbegin() {
    return reverse_iterator(end());
}

template<typename T, std::size_t N>
typename fixed_vector<T, N>::reverse_iterator fixed_vector<T, N>::rend() {
    return reverse_iterator(begin());
}

template<typename T, std::size_t N>
typename fixed_vector<T, N>::const_reverse_iterator fixed_vector<T, N>::rbegin() const {
    return const_reverse_iterator(end());
}

template<typename T, std::size_t N>
typename fixed_vector<T, N>::const_reverse_iterator fixed_vector<T, N>::rend() const {
    return const_reverse_iterator(begin());
}

#endif //UNTITLED_fixed_vector_H
