//
// Created by Никита on 28/01/2018.
//

#ifndef ALLOCATOR_CHECK_H
#define ALLOCATOR_CHECK_H

#include <unistd.h>
#include <ostream>

struct Check {
    int a, b;
    unsigned long c;

    Check() : a(1), b(1), c(1) {

    }

    Check(int a, int b, unsigned long c) : a(a), b(b), c(c) {

    }

    friend bool operator == (const Check &left, const Check &right);

    friend std::ostream& operator << (std::ostream &s, const Check &v);


};

std::ostream& operator << (std::ostream &s, const Check &v){
    s << '(' << v.a << ", " << v.b << ", " << v.c << ')';
    return s;
}

bool operator == (const Check &left, const Check &right) {
    return left.a == right.a && left.b == right.b && left.c == right.c;
}

#endif //ALLOCATOR_CHECK_H
