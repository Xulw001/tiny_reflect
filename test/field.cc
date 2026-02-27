/**
 * @file field.cc
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief
 * @version 0.1
 * @date 2026-01-15
 *
 * @copyright Copyright (c) 2026
 */

#include <iostream>
#include <string>
#include <unordered_map>

#include "reflect.h"

struct A : public reflect::Constructible<A> {
    int a = 0;
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

struct C : public reflect::Constructible<C> {
    std::vector<A> a;
    std::vector<B> b;
    std::vector<long> c;
    std::vector<uint8_t> d;
    std::vector<std::string> e;
    std::vector<float> f;
};

#ifdef NDEBUG
#define LOG std::cout
#else
#define LOG \
    while (false) std::cout
#endif

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
    field_f.set(obj, std::string("Hello, World!"));
    field_g.set(obj, true);

    LOG << "a: " << field_a.get<int>(obj) << std::endl;
    LOG << "b: " << field_b.get<const float>(obj) << std::endl;
    LOG << "c: " << field_c.get<double>(obj) << std::endl;
    LOG << "d: " << field_d.get<long>(obj) << std::endl;
    LOG << "e: " << field_e.get<char>(obj) << std::endl;
    LOG << "f: " << field_f.get<const std::string&>(obj) << std::endl;
    LOG << "g: " << field_g.get<bool>(obj) << std::endl;
}

void field_loop(const reflect::Type& type, reflect::Object obj,
                void (*print_value)(const reflect::Field& field,
                                    reflect::Object obj),
                void (*set_value)(const reflect::Field& field,
                                  reflect::Object obj)) {
    for (size_t i = 0; i < type->field_count(); ++i) {
        const reflect::Field& field = type->field(i);
        if (print_value) print_value(field, obj);
        if (set_value) set_value(field, obj);
    }
}

void print_value(const reflect::Field& field, reflect::Object obj) {
    if (field->is_object()) {
        LOG << field->name() << ": (object)" << " => {{" << std::endl;
        const char* name =
            reflect::TypeIdInfo::GetInstance().get_type_name(field->type_id());
        if (name == nullptr) return;
        auto& type = reflect::TypeInfo().GetInstance().load(name);
        auto& sub_obj = field->GetObject(obj);
        field_loop(type, sub_obj, print_value, nullptr);
        LOG << "}}" << std::endl;
    } else {
        if (field->type_id() == reflect::get_type_id<bool>()) {
            LOG << field->name() << ": " << std::boolalpha
                << field->get<bool>(obj) << std::endl;
        } else if (field->type_id() == reflect::get_type_id<char>()) {
            LOG << field->name() << ": " << field->get<char>(obj) << std::endl;
        } else if (field->type_id() == reflect::get_type_id<unsigned char>()) {
            LOG << field->name() << ": " << field->get<unsigned char>(obj)
                << std::endl;
        } else if (field->type_id() == reflect::get_type_id<short>()) {
            LOG << field->name() << ": " << field->get<short>(obj) << std::endl;
        } else if (field->type_id() == reflect::get_type_id<unsigned short>()) {
            LOG << field->name() << ": " << field->get<unsigned short>(obj)
                << std::endl;
        } else if (field->type_id() == reflect::get_type_id<int>()) {
            LOG << field->name() << ": " << field->get<int>(obj) << std::endl;
        } else if (field->type_id() == reflect::get_type_id<unsigned int>()) {
            LOG << field->name() << ": " << field->get<unsigned int>(obj)
                << std::endl;
        } else if (field->type_id() == reflect::get_type_id<long long>()) {
            LOG << field->name() << ": " << field->get<long long>(obj)
                << std::endl;
        } else if (field->type_id() ==
                   reflect::get_type_id<unsigned long long>()) {
            LOG << field->name() << ": " << field->get<unsigned long long>(obj)
                << std::endl;
        } else if (field->type_id() == reflect::get_type_id<long>()) {
            LOG << field->name() << ": " << field->get<long>(obj) << std::endl;
        } else if (field->type_id() == reflect::get_type_id<unsigned long>()) {
            LOG << field->name() << ": " << field->get<unsigned long>(obj)
                << std::endl;
        } else if (field->type_id() == reflect::get_type_id<float>()) {
            LOG << field->name() << ": " << field->get<float>(obj) << std::endl;
        } else if (field->type_id() == reflect::get_type_id<double>()) {
            LOG << field->name() << ": " << field->get<double>(obj)
                << std::endl;
        } else if (field->type_id() == reflect::get_type_id<std::string>()) {
            LOG << field->name() << ": " << field->get<std::string>(obj)
                << std::endl;
        }
    }
}

void set_value(const reflect::Field& field, reflect::Object obj) {
    if (field->is_object()) {
        const char* name =
            reflect::TypeIdInfo::GetInstance().get_type_name(field->type_id());
        if (name == nullptr) return;
        auto& type = reflect::TypeInfo().GetInstance().load(name);
        auto& sub_obj = field->GetObject(obj);
        field_loop(type, sub_obj, nullptr, set_value);
    } else {
        if (field->type_id() == reflect::get_type_id<bool>()) {
            field->set(obj, true);
        } else if (field->type_id() == reflect::get_type_id<char>()) {
            field->set(obj, 'A');
        } else if (field->type_id() == reflect::get_type_id<unsigned char>()) {
            field->set(obj, 97);
        } else if (field->type_id() == reflect::get_type_id<short>()) {
            field->set(obj, 12345);
        } else if (field->type_id() == reflect::get_type_id<unsigned short>()) {
            field->set(obj, -12345);
        } else if (field->type_id() == reflect::get_type_id<int>()) {
            field->set(obj, 123);
        } else if (field->type_id() == reflect::get_type_id<unsigned int>()) {
            field->set(obj, -123u);
        } else if (field->type_id() == reflect::get_type_id<long long>()) {
            field->set(obj, 1234567890123LL);
        } else if (field->type_id() ==
                   reflect::get_type_id<unsigned long long>()) {
            field->set(obj, 1234567890123ULL);
        } else if (field->type_id() == reflect::get_type_id<long>()) {
            field->set(obj, 100000L);
        } else if (field->type_id() == reflect::get_type_id<unsigned long>()) {
            field->set(obj, -100000UL);
        } else if (field->type_id() == reflect::get_type_id<float>()) {
            field->set(obj, 3.14f);
        } else if (field->type_id() == reflect::get_type_id<double>()) {
            field->set(obj, 2.71828);
        } else if (field->type_id() == reflect::get_type_id<std::string>()) {
            field->set(obj, std::string("Hello, World!"));
        }
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

    LOG << "Type name: " << type->name() << std::endl;
    LOG << "Field count: " << type->field_count() << std::endl;
    LOG << "before: {" << std::endl;
    field_loop(type, obj, print_value, set_value);
    LOG << "}" << std::endl;
    LOG << "after: {" << std::endl;
    field_loop(type, obj, print_value, nullptr);
    LOG << "}" << std::endl;
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
    LOG << "Type name: " << type->name() << std::endl;
    LOG << "Field count: " << type->field_count() << std::endl;
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
    LOG << "Type name: " << type_B->name() << std::endl;
    LOG << "Field count: " << type_B->field_count() << std::endl;
    LOG << "before: {" << std::endl;
    field_loop(type_B, obj, print_value, set_value);
    LOG << "}" << std::endl;
    LOG << "after: {" << std::endl;
    field_loop(type_B, obj, print_value, nullptr);
    LOG << "}" << std::endl;
}

void print_repeated_value(const reflect::RepeatedField& field,
                          reflect::Object obj) {
    if (!field->is_array()) return;
    LOG << field->name() << ": (array)" << " => [" << std::endl;
    for (int i = 0; i < field->size(obj); ++i) {
        if (field->is_object()) {
            LOG << "(object) => {{" << std::endl;
            const char* name = reflect::TypeIdInfo::GetInstance().get_type_name(
                field->type_id());
            if (name == nullptr) return;
            auto& type = reflect::TypeInfo().GetInstance().load(name);
            auto& sub_obj = field->GetObject(obj, i);
            field_loop(type, sub_obj, print_value, nullptr);
            LOG << "}}" << std::endl;
        } else {
            if (field->type_id() == reflect::get_type_id<char>()) {
                LOG << field->name() << ": " << field->get<char>(obj, i)
                    << std::endl;
            } else if (field->type_id() ==
                       reflect::get_type_id<unsigned char>()) {
                LOG << field->name() << ": "
                    << (char)field->get<unsigned char>(obj, i) << std::endl;
            } else if (field->type_id() == reflect::get_type_id<short>()) {
                LOG << field->name() << ": " << field->get<short>(obj, i)
                    << std::endl;
            } else if (field->type_id() ==
                       reflect::get_type_id<unsigned short>()) {
                LOG << field->name() << ": "
                    << field->get<unsigned short>(obj, i) << std::endl;
            } else if (field->type_id() == reflect::get_type_id<int>()) {
                LOG << field->name() << ": " << field->get<int>(obj, i)
                    << std::endl;
            } else if (field->type_id() ==
                       reflect::get_type_id<unsigned int>()) {
                LOG << field->name() << ": " << field->get<unsigned int>(obj, i)
                    << std::endl;
            } else if (field->type_id() == reflect::get_type_id<long long>()) {
                LOG << field->name() << ": " << field->get<long long>(obj, i)
                    << std::endl;
            } else if (field->type_id() ==
                       reflect::get_type_id<unsigned long long>()) {
                LOG << field->name() << ": "
                    << field->get<unsigned long long>(obj, i) << std::endl;
            } else if (field->type_id() == reflect::get_type_id<long>()) {
                LOG << field->name() << ": " << field->get<long>(obj, i)
                    << std::endl;
            } else if (field->type_id() ==
                       reflect::get_type_id<unsigned long>()) {
                LOG << field->name() << ": "
                    << field->get<unsigned long>(obj, i) << std::endl;
            } else if (field->type_id() == reflect::get_type_id<float>()) {
                LOG << field->name() << ": " << field->get<float>(obj, i)
                    << std::endl;
            } else if (field->type_id() == reflect::get_type_id<double>()) {
                LOG << field->name() << ": " << field->get<double>(obj, i)
                    << std::endl;
            } else if (field->type_id() ==
                       reflect::get_type_id<std::string>()) {
                LOG << field->name() << ": " << field->get<std::string>(obj, i)
                    << std::endl;
            }
        }
    }
    LOG << "]" << std::endl;
}

void set_repeated_value(const reflect::RepeatedField& field,
                        reflect::Object obj) {
    if (!field->is_array()) return;
    if (field->is_object()) {
        auto name =
            reflect::TypeIdInfo::GetInstance().get_type_name(field->type_id());
        if (name == nullptr) return;
        auto& type = reflect::TypeInfo().GetInstance().load(name);
        auto sub_obj = type->create();
        field_loop(type, sub_obj, nullptr, set_value);
        field->AddObject(obj, sub_obj);
    } else if (field->type_id() == reflect::get_type_id<char>()) {
        field->add(obj, 'A');
    } else if (field->type_id() == reflect::get_type_id<unsigned char>()) {
        field->add(obj, (unsigned char)97);
    } else if (field->type_id() == reflect::get_type_id<short>()) {
        field->add(obj, (short)12345);
    } else if (field->type_id() == reflect::get_type_id<unsigned short>()) {
        field->add(obj, (unsigned short)-12345);
    } else if (field->type_id() == reflect::get_type_id<int>()) {
        field->add(obj, 123);
    } else if (field->type_id() == reflect::get_type_id<unsigned int>()) {
        field->add(obj, -123u);
    } else if (field->type_id() == reflect::get_type_id<long long>()) {
        field->add(obj, 1234567890123LL);
    } else if (field->type_id() == reflect::get_type_id<unsigned long long>()) {
        field->add(obj, 1234567890123ULL);
    } else if (field->type_id() == reflect::get_type_id<long>()) {
        field->add(obj, 100000L);
    } else if (field->type_id() == reflect::get_type_id<unsigned long>()) {
        field->add(obj, -100000UL);
    } else if (field->type_id() == reflect::get_type_id<float>()) {
        field->add(obj, 3.14f);
    } else if (field->type_id() == reflect::get_type_id<double>()) {
        field->add(obj, 2.71828);
    } else if (field->type_id() == reflect::get_type_id<std::string>()) {
        field->add(obj, std::string(""));
        field->add(obj, std::string("Hello, World!"));
        field->set(obj, 0, std::string("Fine!"));
    }
}

void field_loop(const reflect::Type& type, reflect::Object obj,
                void (*print_value)(const reflect::RepeatedField& field,
                                    reflect::Object obj),
                void (*set_value)(const reflect::RepeatedField& field,
                                  reflect::Object obj)) {
    for (size_t i = 0; i < type->field_count(); ++i) {
        const reflect::Field& field = type->field(i);
        if (print_value)
            print_value(static_cast<const reflect::RepeatedField&>(field), obj);
        if (set_value)
            set_value(static_cast<const reflect::RepeatedField&>(field), obj);
    }
}

void test_repeated() {
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

    auto& type_C = reflect::TypeInfo().GetInstance().regist<C>("C");
    type_C->field("a", &C::a)
        .field("b", &C::b)
        .field("c", &C::c)
        .field("d", &C::d)
        .field("e", &C::e)
        .field("f", &C::f);

    auto obj = type_C->create();
    LOG << "Type name: " << type_C->name() << std::endl;
    LOG << "Field count: " << type_C->field_count() << std::endl;
    LOG << "before: {" << std::endl;
    field_loop(type_C, obj, print_repeated_value, set_repeated_value);
    LOG << "}" << std::endl;
    LOG << "after: {" << std::endl;
    field_loop(type_C, obj, print_repeated_value, nullptr);
    LOG << "}" << std::endl;
}

int main(int argc, char** argv) {
    try {
        if (argc > 1) {
            std::string arg = argv[1];
            if (arg == "field") {
                if (argc > 2) {
                    std::string arg1 = argv[2];
                    if (arg1 == "object") {
                        test_object();
                        return 0;
                    } else if (arg1 == "repeated") {
                        test_repeated();
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
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    std::cout << "Usage: " << argv[0]
              << " (field [object|repeated] | type | manager)" << std::endl;
    return 0;
}