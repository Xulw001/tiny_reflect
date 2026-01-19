# tiny_reflect
## Description
A simple reflection framework that only supports reflection on data types.

## Usage
- All types wants to be reflected must inherit from Constructible.
```cpp
struct A : public reflect::Constructible<A> {
    int a;
    float b;
    double c;
    long d;
    char e;
    std::string f;
    bool g;
};
```
- Regist the type include fields before reflection.
```cpp
reflect::regist<A>("A")
    ->field("a", &A::a)
    .field("b", &A::b)
    .field("c", &A::c)
    .field("d", &A::d)
    .field("e", &A::e)
    .field("f", &A::f)
    .field("g", &A::g);
```
- Get the type, and enumerate all member variables.
```cpp
auto& type = reflect::load("A");
for (size_t i = 0; i < type->field_count(); ++i) {
    const reflect::Field& field = type->field(i);
    std::cout << "name: " << field->name() << std::endl;
    std::cout << "type_id: " << field->type_id() << std::endl;
    std::cout << "is_array: " << std::boolalpha << field->is_array() << std::endl;
}
```
- Get the value of field from the entity.
```cpp
switch (field->type()) {
case reflect::TypeEnum::CPPTYPE_BOOL:
    std::cout << std::boolalpha << field->get<bool>(obj, i) << ",";
    break;
case reflect::TypeEnum::CPPTYPE_OBJECT: {
    auto& type = reflect::load(field->type_id());
    auto& sub_obj = field->getObject(obj);
} break;
}
```
- Set the value of field from the entity.
```cpp
switch (field->type()) {
case reflect::TypeEnum::CPPTYPE_BOOL:
    field->set(obj, true);
    break;
case reflect::TypeEnum::CPPTYPE_OBJECT: {
    auto& type = reflect::load(field->type_id());
    auto& sub_obj = field->getObject(obj);
} break;
}
```
- Get the value of repeated field from the entity.
```cpp
if (field->is_array()) {
    switch (field->type()) {
    case reflect::TypeEnum::CPPTYPE_BOOL:
        std::cout << std::boolalpha << field->get<bool>(obj, i) << ",";
        break;
    case reflect::TypeEnum::CPPTYPE_OBJECT: {
        auto& type = reflect::load(field->type_id());
        auto& sub_obj = field->getObject(obj);
    } break;
    }
}
```
- Set the value of repeated field from the entity.
```cpp
if (field->is_array()) {
    switch (field->type()) {
    case reflect::TypeEnum::CPPTYPE_BOOL:
        field->add(obj, true);
        break;
    case reflect::TypeEnum::CPPTYPE_OBJECT: {
        auto& type = reflect::load(field->type_id());
        auto& sub_obj = type->create();
        field->add(obj, sub_obj);
    } break;
    }
}
```