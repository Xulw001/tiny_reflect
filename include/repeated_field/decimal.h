/**
 * @file decimal.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief This file defines the FieldBase template specialization for repeated decimal fields.
 * @version 0.1
 * @date 2026-01-17
 *
 * @copyright Copyright (c) 2026
 */
#ifndef REPEATED_FIELD_DECIMAL_H
#define REPEATED_FIELD_DECIMAL_H

#include "field.h"

namespace reflect {
/**
 * @brief Specialization of RepeatedFieldInternal for std::vector<T>, where T is a floating-point type.
 */
template <typename C, typename T>
struct FieldBase<C, std::vector<T>, typename std::enable_if<std::is_floating_point<T>::value>::type>
    : public RepeatedFieldInternal {
   public:
    explicit FieldBase(const char* name, std::vector<T> C::* ptr)
        : ptr_(ptr), RepeatedFieldInternal(name, TypeTraits<T>::value) {
        ;
    }

    FieldBase(const FieldBase&) = delete;
    FieldBase& operator=(const FieldBase&) = delete;

    /**
     * @brief Returns the size of the vector field.
     *
     * This function returns the number of elements contained in the vector field.
     *
     * @param obj The object from which to retrieve the size of the vector field.
     * @return size_t The size of the vector field.
     */
    virtual size_t size(ConstObject obj) const {
        auto& array = static_cast<const C&>(obj).*ptr_;
        return array.size();
    }

    /**
     * @brief Returns the decimal value at the specified index.
     *
     * @param obj The object from which to retrieve the decimal value.
     * @param i The index of the element to retrieve.
     * @return Decimal The decimal value at the specified index.
     **/
    virtual Decimal getDecimal(ConstObject obj, size_t i) const {
        return (static_cast<const C&>(obj).*ptr_)[i];
    }

    /**
     * @brief Adds a new decimal value to the vector field.
     *
     * @param obj The object to which the decimal value is to be added.
     * @param v The decimal value to add.
     */
    virtual void addDecimal(Object obj, Decimal v) const {
        (static_cast<C&>(obj).*ptr_).push_back(v.get<T>());
    }

    /**
     * @brief Sets the decimal value at the specified index.
     *
     * @param obj The object to which the decimal value is to be set.
     * @param i The index of the element to set.
     * @param v The decimal value to set.
     */
    virtual void setDecimal(Object obj, size_t i, Decimal v) const {
        (static_cast<C&>(obj).*ptr_)[i] = v.get<T>();
    }

   private:
    std::vector<T> C::* ptr_;  ///< Pointer to the vector field.
};
}  // namespace reflect

#endif