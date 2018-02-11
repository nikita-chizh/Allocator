#include <map>
#include "Linked_List.h"
#include "My_Allocator.h"
#include "Check.h"

int factorial(int n)
{
    if(n > 1)
        return n * factorial(n - 1);
    else
        return 1;
}

int main() {
//    //standart alloc
    std::map<int, int> map1;
    for (int i = 0; i < 10; ++i) {
        map1.insert(std::pair<int, int>{i, factorial(i)});
    }
    for (auto &ref: map1) {
        std::cout << ref.first <<" "<<ref.second << std::endl;
    }
    //my alloc
    std::map<int, int, std::less<>, My_Allocator<int, 10>> map2;
    for (int i = 0; i < 10; ++i) {
        map2.insert(std::pair<int, int>{i, factorial(i)});
    }
    for (auto &ref: map2) {
        std::cout << ref.first <<" "<<ref.second << std::endl;
    }
    //standart alloc
    Linked_List<int> list1;
    for(int i = 0; i < 10; ++i){
        list1.insert(i);
    }
    list1.show();
    //my alloc
    Linked_List<int, My_Allocator<int, 10>> list2;
    for(int i = 0; i < 10; ++i){
        list2.insert(i);
    }
    list2.show();

    return 0;
}