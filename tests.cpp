#define BOOST_TEST_MODULE TestMain

#include <boost/test/unit_test.hpp>
#include "Memory_Pool.h"
#include "Check.h"
#include <iostream>

BOOST_AUTO_TEST_SUITE(test_pool)
    uint8_t size = 4;
    int b_size = 10;

    BOOST_AUTO_TEST_CASE(test_alloc) {
        Memory_Pool<Check, 4> pool;
        Check* f;
        Check* s;
        f =  pool.alloc();
        new(f) Check({1,2,3});
        s =  pool.alloc();
        new(s) Check({1,2,3});
        BOOST_CHECK(*f == *s);
    }

    BOOST_AUTO_TEST_CASE(test_realloc) {
        Memory_Pool<Check, 4> pool;
        std::vector<Check*> checks_p(b_size);
        std::vector<Check> checks;
        for(int i = 0; i < b_size; ++i){
            checks_p[i] = pool.alloc();
            new(checks_p[i]) Check({i,i+1,u_int64_t(i+2)});
            checks.emplace_back(Check({i, i+1, u_int64_t(i+2)}));
        }
        for(int i = 0; i < b_size; ++i){
            BOOST_CHECK(checks[i] == *checks_p[i]);
        }
    }

    BOOST_AUTO_TEST_CASE(test_dealloc) {
        std::vector<Check*> checks_p(size);
        Memory_Pool<Check, 4> pool;
        std::vector<Check> checks;
        for(int i = 0; i < size; ++i){
            checks_p[i] = pool.alloc();
            new(checks_p[i]) Check({i,i+1,u_int64_t(i+2)});
        }
        for(int i = 0; i < size; ++i){
            pool.dealloc(checks_p[i]);
        }
        //
        for(int i = 0; i < size; ++i){
            checks_p[i] = pool.alloc();
            new(checks_p[i]) Check({i,i+5,u_int64_t(i+7)});
            checks.emplace_back(Check({i, i+5, u_int64_t(i+7)}));
        }
        for(int i = 0; i < size; ++i){
            BOOST_CHECK(checks[i] == *checks_p[i]);
        }
    }

BOOST_AUTO_TEST_SUITE_END()
