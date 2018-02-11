//
// Created by nikita on 30.01.18.
//

#ifndef ALLOCATOR_MY_ALLOCATOR_H
#define ALLOCATOR_MY_ALLOCATOR_H

#include "Memory_Pool.h"
#include <iostream>
#include <vector>

template<typename T, unsigned int BLOCK_SIZE>
struct My_Allocator {
    My_Allocator() = default;


    using value_type = T;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using reference = value_type &;
    using const_reference = const value_type &;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    Memory_Pool<T, BLOCK_SIZE> pool;
    template<typename U>
    struct rebind {
        typedef My_Allocator<U, BLOCK_SIZE> other;
    };

    T *allocate(std::size_t n) {
        auto p = pool.alloc();
        return reinterpret_cast<pointer>(p);
    };

    void deallocate(T *p, std::size_t n) {
        pool.dealloc(p);
    }

    template<typename ... Args>
    void construct(pointer p, Args &&...args) {
        new(p) T(std::forward<Args>(args)...);
    }

    void destroy(pointer p) {
        p->~T();
    }
};

#endif //ALLOCATOR_MY_ALLOCATOR_H
