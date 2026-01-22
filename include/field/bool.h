/**
 * @file bool.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief This file defines the FieldBase template specialization for boolean fields.
 * @tparam C The class type that contains the boolean member variable.
 *
 * @version 0.2
 * @date 2026-01-22
 *
 * @copyright Copyright (c) 2026
 */
#ifndef FIELD_BOOL_H
#define FIELD_BOOL_H

#include "field.h"

namespace reflect {
template <typename C>
struct FieldBase<C, bool> : public FieldInternal {
   public:
    /**
     * @brief Construct a new FieldBase object.
     *
     * @param name The name of the field.
     * @param ptr Pointer to the boolean member variable of class C.
     */
    explicit FieldBase(const char* name, bool C::* ptr)
        : ptr_(ptr), FieldInternal(name, TypeTraits<bool>::value, false) {
        ;
    }

    FieldBase(const FieldBase&) = delete;
    FieldBase& operator=(const FieldBase&) = delete;

    /**
     * @brief Get the boolean value from the object.
     *
     * @param obj The object from which to get the boolean value.
     * @return bool The boolean value of the member variable.
     */
    virtual Boolean getBool(ConstObject obj) const {
        return Boolean(static_cast<const C&>(obj).*ptr_);
    }

    /**
     * @brief Set the boolean value of the object.
     *
     * @param obj The object in which to set the boolean value.
     * @param v The boolean value to set.
     */
    virtual void setBool(Object obj, const Boolean& v) const {
        static_cast<C&>(obj).*ptr_ = v.get();
    }

   private:
    bool C::* ptr_;  // Pointer to the boolean member variable
};
}  // namespace reflect

#endif