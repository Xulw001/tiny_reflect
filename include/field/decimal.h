/**
 * @file decimal.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief This file defines the FieldBase template specialization for floating-point types.
 * @tparam C The class type that contains the floating-point member.
 * @tparam T The floating-point type (e.g., float, double) of the member.
 *
 * @version 0.1
 * @date 2026-01-15
 *
 * @copyright Copyright (c) 2026
 */
#ifndef FIELD_DECIMAL_H
#define FIELD_DECIMAL_H

#include "field.h"

namespace reflect {
template <typename C, typename T>
struct FieldBase<C, T, typename std::enable_if<std::is_floating_point<T>::value>::type>
    : public FieldInternal {
   public:
    /**
     * @brief Constructs a FieldBase object.
     *
     * @param name The name of the field.
     * @param ptr Pointer to the floating-point member of class C.
     */
    explicit FieldBase(const char* name, T C::* ptr)
        : ptr_(ptr), FieldInternal(name, TypeTraits<T>::value, false) {
        ;
    }

    FieldBase(const FieldBase&) = delete;
    FieldBase& operator=(const FieldBase&) = delete;

    /**
     * @brief Gets the decimal value from the specified object.
     *
     * @param obj The object from which to retrieve the decimal value.
     * @return Decimal The decimal value of the floating-point member.
     */
    virtual Decimal getDecimal(ConstObject obj) const { return static_cast<const C&>(obj).*ptr_; }

    /**
     * @brief Sets the decimal value for the specified object.
     *
     * @param obj The object to which the decimal value will be set.
     * @param v The decimal value to set.
     */
    virtual void setDecimal(Object obj, Decimal v) const {
        static_cast<C&>(obj).*ptr_ = v.get<T>();
    }

   private:
    T C::* ptr_;  ///< Pointer to the floating-point member of class C.
};
}  // namespace reflect

#endif