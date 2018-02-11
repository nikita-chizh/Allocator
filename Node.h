//
// Created by normalteam on 12.10.16.
//

#ifndef TZTEST_NODE_H
#define TZTEST_NODE_H

template <class Obj_Type>
struct Node {
    Node *next;
    Node *prev;
    Obj_Type* data;

    Node(){
        next= nullptr;
        prev = nullptr;
        data = nullptr;
    }

    explicit Node(const Obj_Type& obj){
        next= nullptr;
        prev = nullptr;
        this->data = new Obj_Type(obj);
    }

    ~Node(){
        delete data;
        next = nullptr;
        prev = nullptr;
    }
};


#endif //TZTEST_NODE_H
