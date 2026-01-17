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

#include "type_info.h"

struct A : public reflect::Constructible<A> {
    int a;
    float b;
    double c;
    long d;
    char e;
    std::string f;
    bool g;
};

struct B : public reflect::Constructible<B> {
    A a;
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

void field_loop(const reflect::Type& type,
                reflect::Object obj,
                void (*print_value)(const reflect::Field& field, reflect::ConstObject obj),
                void (*set_value)(const reflect::Field& field, reflect::Object obj)) {
    for (size_t i = 0; i < type->field_count(); ++i) {
        const reflect::Field& field = type->field(i);
        if (print_value)
            print_value(field, obj);
        if (set_value)
            set_value(field, obj);
    }
}

void print_value(const reflect::Field& field, reflect::ConstObject obj) {
    switch (field->type()) {
    case reflect::TypeEnum::CPPTYPE_BOOL:
        std::cout << field->name() << ": " << std::boolalpha << field->get<bool>(obj) << std::endl;
        break;
    case reflect::TypeEnum::CPPTYPE_INT8:
        std::cout << field->name() << ": " << field->get<char>(obj) << std::endl;
        break;
    case reflect::TypeEnum::CPPTYPE_UINT8:
        std::cout << field->name() << ": " << field->get<char>(obj) << std::endl;
        break;
    case reflect::TypeEnum::CPPTYPE_INT16:
        std::cout << field->name() << ": " << field->get<short>(obj) << std::endl;
        break;
    case reflect::TypeEnum::CPPTYPE_UINT16:
        std::cout << field->name() << ": " << field->get<unsigned short>(obj) << std::endl;
        break;
    case reflect::TypeEnum::CPPTYPE_INT32:
        std::cout << field->name() << ": " << field->get<int>(obj) << std::endl;
        break;
    case reflect::TypeEnum::CPPTYPE_UINT32:
        std::cout << field->name() << ": " << field->get<unsigned int>(obj) << std::endl;
        break;
    case reflect::TypeEnum::CPPTYPE_INT64:
        std::cout << field->name() << ": " << field->get<long long>(obj) << std::endl;
        break;
    case reflect::TypeEnum::CPPTYPE_UINT64:
        std::cout << field->name() << ": " << field->get<unsigned long long>(obj) << std::endl;
        break;
    case reflect::TypeEnum::CPPTYPE_LONG:
        std::cout << field->name() << ": " << field->get<long>(obj) << std::endl;
        break;
    case reflect::TypeEnum::CPPTYPE_ULONG:
        std::cout << field->name() << ": " << field->get<unsigned long>(obj) << std::endl;
        break;
    case reflect::TypeEnum::CPPTYPE_FLOAT:
        std::cout << field->name() << ": " << field->get<float>(obj) << std::endl;
        break;
    case reflect::TypeEnum::CPPTYPE_DOUBLE:
        std::cout << field->name() << ": " << field->get<double>(obj) << std::endl;
        break;
    case reflect::TypeEnum::CPPTYPE_STRING:
        std::cout << field->name() << ": " << field->get<std::string>(obj) << std::endl;
        break;
    case reflect::TypeEnum::CPPTYPE_OBJECT: {
        std::cout << field->name() << ": (object)" << " => {{" << std::endl;
        const char* name = reflect::TypeIdInfo::GetInstance().get_type_name(field->type_id());
        if (name == nullptr) throw std::runtime_error("unknown type");
        auto& type = reflect::TypeInfo().GetInstance().load(name);
        auto& sub_obj = field->getObject(obj);
        field_loop(type, const_cast<reflect::Object&>(sub_obj), print_value, nullptr);
        std::cout << "}}" << std::endl;
    } break;
    default:
        std::cout << field->name() << ": (unknown type)" << std::endl;
        break;
    }
}

void set_value(const reflect::Field& field, reflect::Object obj) {
    switch (field->type()) {
    case reflect::TypeEnum::CPPTYPE_BOOL:
        field->set(obj, true);
        break;
    case reflect::TypeEnum::CPPTYPE_INT8:
        field->set(obj, 'A');
        break;
    case reflect::TypeEnum::CPPTYPE_UINT8:
        field->set(obj, 0x7f);
        break;
    case reflect::TypeEnum::CPPTYPE_INT16:
        field->set(obj, 12345);
        break;
    case reflect::TypeEnum::CPPTYPE_UINT16:
        field->set(obj, -12345);
        break;
    case reflect::TypeEnum::CPPTYPE_INT32:
        field->set(obj, 123);
        break;
    case reflect::TypeEnum::CPPTYPE_UINT32:
        field->set(obj, -123);
        break;
    case reflect::TypeEnum::CPPTYPE_INT64:
        field->set(obj, 1234567890123LL);
        break;
    case reflect::TypeEnum::CPPTYPE_UINT64:
        field->set(obj, 1234567890123ULL);
        break;
    case reflect::TypeEnum::CPPTYPE_LONG:
        field->set(obj, 100000L);
        break;
    case reflect::TypeEnum::CPPTYPE_ULONG:
        field->set(obj, -100000L);
        break;
    case reflect::TypeEnum::CPPTYPE_FLOAT:
        field->set(obj, 3.14f);
        break;
    case reflect::TypeEnum::CPPTYPE_DOUBLE:
        field->set(obj, 2.71828);
        break;
    case reflect::TypeEnum::CPPTYPE_STRING:
        field->set(obj, "Hello, World!");
        break;
    case reflect::TypeEnum::CPPTYPE_OBJECT: {
        const char* name = reflect::TypeIdInfo::GetInstance().get_type_name(field->type_id());
        if (name == nullptr) throw std::runtime_error("unknown type");
        auto& type = reflect::TypeInfo().GetInstance().load(name);
        auto& sub_obj = field->getObject(obj);
        field_loop(type, sub_obj, nullptr, set_value);
    } break;
    default:
        break;
    }
}

void test_type() {
    reflect::Type type(new reflect::TypeBase<A>("A", &A::constructor));
    type->field("a", &A::a)
        .field("b", &A::b)
        .field("c", &A::c)
        .field("d", &A::d)
        .field("e", &A::e)
        .field("f", &A::f)
        .field("g", &A::g);

    auto obj = type->create();

    std::cout << "Type name: " << type->name() << std::endl;
    std::cout << "Field count: " << type->field_count() << std::endl;
    std::cout << "before: {" << std::endl;
    field_loop(type, obj, print_value, set_value);
    std::cout << "}" << std::endl;
    std::cout << "after: {" << std::endl;
    field_loop(type, obj, print_value, nullptr);
    std::cout << "}" << std::endl;
}

void test_manager() {
    auto& type_A = reflect::TypeInfo().GetInstance().regist<A>("A");
    type_A->field("a", &A::a)
        .field("b", &A::b)
        .field("c", &A::c)
        .field("d", &A::d)
        .field("e", &A::e)
        .field("f", &A::f)
        .field("g", &A::g);
    auto& type = reflect::TypeInfo().GetInstance().load("A");
    std::cout << "Type name: " << type->name() << std::endl;
    std::cout << "Field count: " << type->field_count() << std::endl;
}

void test_object() {
    auto& type_A = reflect::TypeInfo().GetInstance().regist<A>("A");
    type_A->field("a", &A::a)
        .field("b", &A::b)
        .field("c", &A::c)
        .field("d", &A::d)
        .field("e", &A::e)
        .field("f", &A::f)
        .field("g", &A::g);

    auto& type_B = reflect::TypeInfo().GetInstance().regist<B>("B");
    type_B->field("a", &B::a);

    auto obj = type_B->create();
    std::cout << "Type name: " << type_B->name() << std::endl;
    std::cout << "Field count: " << type_B->field_count() << std::endl;
    std::cout << "before: {" << std::endl;
    field_loop(type_B, obj, print_value, set_value);
    std::cout << "}" << std::endl;
    std::cout << "after: {" << std::endl;
    field_loop(type_B, obj, print_value, nullptr);
    std::cout << "}" << std::endl;
}

int main(int argc, char** argv) {
    if (argc > 1) {
        std::string arg = argv[1];
        if (arg == "field") {
            if (argc > 2) {
                std::string arg1 = argv[2];
                if (arg1 == "object") {
                    test_object();
                    return 0;
                }
            }
            test_field();
            return 0;
        } else if (arg == "type") {
            test_type();
            return 0;
        } else if (arg == "manager") {
            test_manager();
            return 0;
        }
    }
    std::cout << "Usage: " << argv[0] << " (field [object] | type | manager)" << std::endl;
    return 0;
}