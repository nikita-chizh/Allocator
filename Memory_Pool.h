//
// Created by Никита on 27/01/2018.
//

#ifndef HW3_MEMORY_POOL_H
#define HW3_MEMORY_POOL_H

#include <memory>
#include <stack>
#include <vector>

template <class T, unsigned int BLOCK_SIZE>
class Memory_Pool {
private:

    u_int32_t block_size = BLOCK_SIZE;
    std::stack<T*> free_chunks;
    using Blocks = std::vector<std::unique_ptr<T[]>>;
    Blocks blocks;

    void add_block(){
        blocks.push_back({nullptr});
        blocks.back() = std::make_unique<T[]>(block_size);
        for(int i = 0; i < block_size; ++i){
            free_chunks.push(&blocks.back()[i]);
        }
    }
public:

    Memory_Pool(){
        add_block();
    }
    
    T* alloc(){
        if(free_chunks.empty())
            add_block();
        T* res =  free_chunks.top();
        free_chunks.pop();
        return res;
    }

    void dealloc(T* ptr){
        free_chunks.push(ptr);
    }

};


#endif //HW3_MEMORY_POOL_H
