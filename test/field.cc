/**
 * @file field.cc
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief
 * @version 0.1
 * @date 2026-01-15
 *
 * @copyright Copyright (c) 2026
 */
#include "field.h"

#include <iostream>
#include <string>
#include <unordered_map>

#include "constructor.h"
#include "field/bool.h"
#include "field/decimal.h"
#include "field/integer.h"
#include "field/text.h"

struct A : public reflect::Constructible<A> {
    int a;
    float b;
    double c;
    long d;
    char e;
    std::string f;
    bool g;
};

/**
 * @brief Tests the functionality of the reflect::FieldBase class.
 */
void test_field() {
    reflect::FieldBase<A, int> field_a("a", &A::a);
    reflect::FieldBase<A, float> field_b("b", &A::b);
    reflect::FieldBase<A, double> field_c("c", &A::c);
    reflect::FieldBase<A, long> field_d("d", &A::d);
    reflect::FieldBase<A, char> field_e("e", &A::e);
    reflect::FieldBase<A, std::string> field_f("f", &A::f);
    reflect::FieldBase<A, bool> field_g("g", &A::g);

    A obj;
    field_a.set(obj, 42);
    field_b.set(obj, 3.14f);
    field_c.set(obj, 2.71828);
    field_d.set(obj, 100000L);
    field_e.set(obj, 'z');
    field_f.set(obj, "Hello, World!");
    field_g.set(obj, true);

    std::cout << "a: " << field_a.get<int>(obj) << std::endl;
    std::cout << "b: " << field_b.get<float>(obj) << std::endl;
    std::cout << "c: " << field_c.get<double>(obj) << std::endl;
    std::cout << "d: " << field_d.get<long>(obj) << std::endl;
    std::cout << "e: " << field_e.get<char>(obj) << std::endl;
    std::cout << "f: " << field_f.get<std::string>(obj) << std::endl;
    std::cout << "g: " << field_g.get<bool>(obj) << std::endl;
}

int main() {
    test_field();
    return 0;
}