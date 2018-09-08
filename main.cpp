#include "vector.h"

template<typename T, size_t N>
void show_fixed_vector(fixed_vector<T, N> &v) {
    std::cout << "back: " << v.back() << " size:" << v.size() <<
              " capacity:" << v.capacity() << std::endl;
    std::cout << "fixed_vector: ";
    size_t size = v.size();
    for (size_t i = 0; i < size; ++i) {
        std::cout << v.get(i) << ' ';
    }
    std::cout << std::endl << std::endl;
}

template<typename T, size_t N>
void test_push_back(fixed_vector<T, N> &v, int j) {
    std::cout << "TESTING PUSH_BACK" << std::endl;
    for (int i = 0; i < j; ++i) {
        v.push_back(i);
        std::cout << i << ": push_back(" << i << "): ";
        show_fixed_vector(v);
    }
    std::cout << std::endl;
}

template<typename T, size_t N>
void test_insert_begin(fixed_vector<T, N> &v, int j) {
    std::cout << "TESTING INSERT begin" << std::endl;
    for (int i = 0; i < j; ++i) {
        v.insert(v.begin() + i, -i);
        std::cout << i << ": insert(begin+" << i << "): ";
        show_fixed_vector(v);
    }
    std::cout << std::endl;
}

template<typename T, size_t N>
void test_insert_end(fixed_vector<T, N> &v, int j) {
    std::cout << "TESTING INSERT end" << std::endl;
    for (int i = 0; i < j; ++i) {
        v.insert(v.end() - i, -i);
        std::cout << i << ": insert(end()-" << i << "): ";
        show_fixed_vector(v);
    }
    std::cout << std::endl;
}

template<typename T, size_t N>
void test_pop_back(fixed_vector<T, N> &v, int j) {
    std::cout << "TESTING POP_BACK" << std::endl;
    for (int i = 0; i < j; ++i) {
        v.pop_back();
        std::cout << i << ": pop_back(): ";
        show_fixed_vector(v);
    }
    std::cout << std::endl;
}

template<typename T, size_t N>
void test_resize(fixed_vector<T, N> &v, size_t size, T value) {
    std::cout << "TESTING RESIZE" << std::endl;
    std::cout << "BEFORE: ";
    show_fixed_vector(v);
    v.resize(size, value);
    std::cout << ": resize(" << size << ", " << value << "): ";
    show_fixed_vector(v);
    std::cout << std::endl;
}

template<typename T, size_t N>
void test_assign(fixed_vector<T, N> &v, size_t size, T value) {
    std::cout << "TESTING ASSIGN" << std::endl;
    std::cout << "BEFORE: ";
    show_fixed_vector(v);
    v.assign(size, value);
    std::cout << ": assign(" << size << ", " << value << "): ";
    show_fixed_vector(v);
    std::cout << std::endl;
}

template<typename T, size_t N>
void test_clear(fixed_vector<T, N> &v, int j) {
    std::cout << "TESTING CLEAR" << std::endl;
    std::cout << "BEFORE: ";
    show_fixed_vector(v);
    for (int i = 0; i < j; ++i) {
        v.clear();
        std::cout << i << ": clear(): ";
        show_fixed_vector(v);
    }
    std::cout << std::endl;
}

template<typename T, size_t N>
void test_empty(fixed_vector<T, N> &v) {
    std::cout << "============" << std::endl;
    std::cout << "TESTING EMPTY" << std::endl;
    show_fixed_vector(v);
    if (v.empty()) {
        std::cout << "YES, I AM EMPTY!!!";
    } else {
        std::cout << "nooo, I am fat as creator's cat :(";
    }
    std::cout << std::endl << "============" << std::endl;
    std::cout << std::endl;
}

template<typename T, size_t N>
void test_reserve(fixed_vector<T, N> &v, size_t size) {
    std::cout << "TESTING RESERVE" << std::endl;
    std::cout << "BEFORE: ";
    show_fixed_vector(v);
    v.reserve(size);
    std::cout << ": reserve(" << size << "): ";
    show_fixed_vector(v);
    std::cout << std::endl;
}

template<typename T, size_t N>
void test_erase(fixed_vector<T, N> &v) {
    std::cout << "TESTING ERASE one" << std::endl;
    std::cout << "BEFORE: ";
    show_fixed_vector(v);
    v.erase(v.begin());
    std::cout << ": erase(v.begin()): ";
    show_fixed_vector(v);
    v.erase(v.begin() + 1);
    std::cout << ": erase(v.begin()+1): ";
    show_fixed_vector(v);
    v.erase(v.end() - 1);
    std::cout << ": erase(v.end()-1): ";
    show_fixed_vector(v);
    std::cout << std::endl;
}

template<typename T, size_t N>
void test_data(fixed_vector<T, N> &v) {
    std::cout << "TESTING data" << std::endl;
    show_fixed_vector(v);
    std::cout << "v.data()=" << v.data();
    std::cout << std::endl << std::endl;
}

template<typename T, size_t N>
void test_iterators(fixed_vector<T, N> &v) {
    std::cout << "TESTING iterators" << std::endl;
    std::cout << "v.begin()=" << v.begin() << "   v.rbegin()=" << &*v.rbegin() << std::endl;
    std::cout << "v.rend() =" << &*v.rend() << "   v.end()   =" << &*v.end() << std::endl;
}

int main() {
    std::cout << "PART 1. Testing fixed_vector<int>" << std::endl;
    int j = 20;
    size_t const x = 100;
    fixed_vector<int, x> v;
    std::cout << "size:" << v.size() <<
              " capacity:" << v.capacity() << std::endl;
    std::cout << "~~~~~~~" << std::endl;
    try {
        test_push_back(v, j);
        test_insert_begin(v, j);
        test_insert_end(v, j);
        test_pop_back(v, j);
        test_erase(v);
        test_iterators(v);
    } catch (std::length_error const &e) {
        std::cout << "nice";
    }

    std::cout << "PART 2. Pushes" << std::endl;
    j = 20;
    const size_t y = 5;
    fixed_vector<int, y> v2;
    std::cout << "size:" << v.size() <<
              " capacity:" << v.capacity() << std::endl;
    std::cout << "~~~~~~~" << std::endl;
    try {
        test_push_back(v2, j);
    } catch (std::length_error const &e) {
        std::cout << "Проверка пушей: " << e.what();
    }

    std::cout << "PART 3. Inserts" << std::endl;
    j = 20;
    fixed_vector<int, y> v3;
    std::cout << "size:" << v.size() <<
              " capacity:" << v.capacity() << std::endl;
    std::cout << "~~~~~~~" << std::endl;
    try {
        test_insert_begin(v3, j);
    } catch (std::length_error const &e) {
        std::cout << "Проверка инсертов: " << e.what();
    }


    show_fixed_vector(v2);
    show_fixed_vector(v3);

    v2 = v3;

    show_fixed_vector(v2);
    show_fixed_vector(v3);
    //test_pop_back(v3, 7);

    //std::cout << "~~~~~~~" << std::endl;
    //std::cout << "PART 2. Testing fixed_vector<int>(It first, It last)" << std::endl;
    //int a[2];
    //a[0] = 0;
    //a[1] = 1;
    //fixed_vector<int, 100> v2(&a[0], &a[2]);
    //show_fixed_vector(v2);

    return 0;
}