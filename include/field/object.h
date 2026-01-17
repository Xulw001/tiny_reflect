/**
 * @file object.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief This header file defines the FieldBase template structure
 *        for the type is derived from ObjectInternal.
 *
 * @tparam C The class type that contains the member variable.
 * @tparam T The type of the member variable.
 *
 * @version 0.1
 * @date 2026-01-16
 *
 * @copyright Copyright (c) 2026
 */
#ifndef FIELD_OBJECT_H
#define FIELD_OBJECT_H

#include "field.h"

namespace reflect {
template <typename C, typename T>
struct FieldBase<C, T, typename std::enable_if<std::is_base_of<ObjectInternal, T>::value>::type>
    : public FieldInternal {
   public:
    /**
     * @brief Constructs a FieldBase for an ObjectInternal type.
     *
     * @param name The name of the field.
     * @param ptr A pointer to the ObjectInternal member of class C.
     */
    explicit FieldBase(const char* name, T C::* ptr)
        : ptr_(ptr), FieldInternal(name, TypeEnum::CPPTYPE_OBJECT, false) { ; }

    FieldBase(const FieldBase&) = delete;
    FieldBase& operator=(const FieldBase&) = delete;

    /**
     * @brief Retrieves the ObjectInternal from the given object.
     *
     * @param obj The object from which to retrieve the ObjectInternal.
     * @return The ObjectInternal of the member.
     */
    virtual ConstObject getObject(ConstObject obj) const {
        return static_cast<const C&>(obj).*ptr_;
    };

    /**
     * @brief Sets the ObjectInternal of the member in the given object.
     *
     * @param obj The object in which to set the ObjectInternal.
     * @param o The ObjectInternal to set.
     */
    virtual void set(Object obj, ConstObject o) const {
        static_cast<C&>(obj).*ptr_ = static_cast<const T&>(o);
    }

   private:
    T C::* ptr_;  ///< Pointer to the object member
};
}  // namespace reflect

#endif