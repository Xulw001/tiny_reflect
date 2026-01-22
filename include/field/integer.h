/**
 * @file integer.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief This header file defines the FieldBase template structure for integral types.
 * @tparam C The class type that contains the integral member.
 * @tparam T The integral type of the member.
 *
 * @version 0.2
 * @date 2026-01-22
 *
 * @copyright Copyright (c) 2026
 */
#ifndef FIELD_INTEGER_H
#define FIELD_INTEGER_H

#include "field.h"

namespace reflect {
template <typename C, typename T>
struct FieldBase<C, T, typename std::enable_if<std::is_integral<T>::value>::type>
    : public FieldInternal {
   public:
    /**
     * @brief Constructs a FieldBase for an integral member.
     *
     * @param name The name of the field.
     * @param ptr A pointer to the integral member of class C.
     */
    explicit FieldBase(const char* name, T C::* ptr)
        : ptr_(ptr), FieldInternal(name, TypeTraits<T>::value, false) {
        ;
    }

    FieldBase(const FieldBase&) = delete;
    FieldBase& operator=(const FieldBase&) = delete;

    /**
     * @brief Retrieves the integer value from the given object.
     *
     * @param obj The object from which to retrieve the integer value.
     * @return The integer value of the member.
     */
    virtual Integer getInteger(ConstObject obj) const {
        return Integer(static_cast<const C&>(obj).*ptr_);
    }

    /**
     * @brief Sets the integer value of the member in the given object.
     *
     * @param obj The object in which to set the integer value.
     * @param v The integer value to set.
     */
    virtual void setInteger(Object obj, const Integer& v) const {
        static_cast<C&>(obj).*ptr_ = v.get<T>();
    }

   private:
    T C::* ptr_;  // Pointer to the integral member
};
}  // namespace reflect

#endif