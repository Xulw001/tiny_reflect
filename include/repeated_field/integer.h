/**
 * @file integer.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief This file defines the FieldBase template specialization for repeated integral fields.
 * @version 0.2
 * @date 2026-01-22
 *
 * @copyright Copyright (c) 2026
 */
#ifndef REPEATED_FIELD_INTEGER_H
#define REPEATED_FIELD_INTEGER_H

#include "field.h"

namespace reflect {
/**
 * @brief Specialization of RepeatedFieldInternal for std::vector<T>, where T is an integral type.
 */
template <typename C, typename T>
struct FieldBase<C, std::vector<T>, typename std::enable_if<std::is_integral<T>::value>::type>
    : public RepeatedFieldInternal {
   public:
    explicit FieldBase(const char* name, std::vector<T> C::* ptr)
        : ptr_(ptr), RepeatedFieldInternal(name, TypeTraits<T>::value) {
        ;
    }

    FieldBase(const FieldBase&) = delete;
    FieldBase& operator=(const FieldBase&) = delete;

    /**
     * @brief Retrieves the size of the repeated field in the given object.
     *
     * @param obj The object from which to retrieve the size of the repeated field.
     * @return The size of the repeated field in the given object.
     */
    virtual size_t size(ConstObject obj) const {
        auto& array = static_cast<const C&>(obj).*ptr_;
        return array.size();
    }

    /**
     * @brief Retrieves the integer value at the specified index in the given object.
     *
     * @param obj The object from which to retrieve the integer value.
     * @param i The index of the integer value to retrieve.
     * @return The integer value at the specified index in the given object.
     */
    virtual Integer getInteger(ConstObject obj, size_t i) const {
        return Integer((static_cast<const C&>(obj).*ptr_)[i]);
    }

    /**
     * @brief Adds an integer value to the repeated field in the given object.
     *
     * @param obj The object to which the integer value is to be added.
     * @param v The integer value to be added to the repeated field.
     */
    virtual void addInteger(Object obj, const Integer& v) const {
        (static_cast<C&>(obj).*ptr_).push_back(v.get<T>());
    }

    /**
     * @brief Sets the integer value at the specified index in the given object.
     *
     * @param obj The object in which to set the integer value.
     * @param i The index of the element to set.
     * @param v The integer value to set.
     */
    virtual void setInteger(Object obj, size_t i, const Integer& v) const {
        (static_cast<C&>(obj).*ptr_)[i] = v.get<T>();
    }

   private:
    std::vector<T> C::* ptr_;  ///< The pointer to the vector field.
};
}  // namespace reflect

#endif