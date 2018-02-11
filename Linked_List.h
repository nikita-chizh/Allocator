//
// Created by nikita on 12.10.16.
//

#ifndef TZTEST_LINKED_LIST_H
#define TZTEST_LINKED_LIST_H

#include "Node.h"
#include <iostream>
#include <typeinfo>
#include "My_Allocator.h"

template<class Obj_Type, class Alloc_Type = std::allocator<Obj_Type>>
class Linked_List {
private:
    using node_alloc_t = typename std::allocator_traits<Alloc_Type>::template rebind_alloc<Node<Obj_Type>>;
    node_alloc_t node_alloc;

    Node<Obj_Type> *head;

public:
    Linked_List() {
        head = nullptr;
    }

    explicit Linked_List(const Obj_Type &obj) {
        head = node_alloc.allocate(1);
        new(head) Node<Obj_Type>();
    }

    ~Linked_List() {
        if (head == nullptr) {
            return;
        }
        Node<Obj_Type> *iterator = head;
        Node<Obj_Type> *priv = nullptr;
        bool is_std_alloc = typeid(Alloc_Type) == typeid(std::allocator<Obj_Type>);
        while (iterator != nullptr) {
            priv = iterator;
            iterator = iterator->next;
            node_alloc.deallocate(priv, std::size_t(1));
            if(is_std_alloc)
                node_alloc.destroy(priv);
        }
    }

    void show() const {
        if (head == nullptr) {
            return;
        }
        Node<Obj_Type> *iterator = head;
        Node<Obj_Type> *prev = nullptr;
        int debug_counter = 0;
        while (iterator != nullptr) {
            prev = iterator;
            iterator = iterator->next;
            std::cout << *(prev->data) << " ";
            ++debug_counter;
        }
        std::cout<<std::endl;
    }

    void insert(Obj_Type &obj) {
        auto new_node = node_alloc.allocate(1);
        node_alloc.construct(new_node, obj);
        if (head == nullptr) {
            head = new_node;
            return;
        }
        auto iterator = head;
        Node<Obj_Type> *prev = nullptr;
        while (iterator != nullptr) {
            prev = iterator;
            iterator = iterator->next;
        }
        insert_node(new_node, prev);
    }


private:
    void insert_node(Node<Obj_Type> *new_node, Node<Obj_Type> *prev) {
        new_node->next = nullptr;
        new_node->prev = prev;
        if (prev != nullptr) {
            prev->next = new_node;
        }
    }

};



#endif
