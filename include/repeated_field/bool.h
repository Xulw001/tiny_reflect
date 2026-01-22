/**
 * @file bool.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief This file defines the FieldBase template specialization for repeated boolean fields.
 * @version 0.2
 * @date 2026-01-22
 *
 * @copyright Copyright (c) 2026
 */
#ifndef REPEATED_FIELD_BOOL_H
#define REPEATED_FIELD_BOOL_H

#include "field.h"

namespace reflect {
/**
 * @brief Specialization of RepeatedFieldInternal for std::vector<bool>.
 */
template <typename C>
struct FieldBase<C, std::vector<bool>> : public RepeatedFieldInternal {
   public:
    explicit FieldBase(const char* name, std::vector<bool> C::* ptr)
        : ptr_(ptr), RepeatedFieldInternal(name, TypeTraits<bool>::value) {
        ;
    }

    FieldBase(const FieldBase&) = delete;
    FieldBase& operator=(const FieldBase&) = delete;

    /**
     * @brief Get the number of elements in the repeated field.
     *
     * @param obj The object from which to get the size of the repeated field.
     * @return size_t The number of elements in the repeated field.
     */
    virtual size_t size(ConstObject obj) const {
        auto& array = static_cast<const C&>(obj).*ptr_;
        return array.size();
    }

    /**
     * @brief Get the boolean value at the specified index.
     *
     * @param obj The object from which to get the boolean value.
     * @param i The index of the element to get.
     * @return bool The boolean value at the specified index.
     */
    virtual Boolean getBool(ConstObject obj, size_t i) const {
        return Boolean((static_cast<const C&>(obj).*ptr_)[i]);
    }

    /**
     * @brief Add a boolean value to the end of the repeated field.
     *
     * @param obj The object to which the boolean value is to be added.
     * @param v The boolean value to add.
     */
    virtual void addBool(Object obj, const Boolean& v) const {
        (static_cast<C&>(obj).*ptr_).push_back(v.get());
    }

    /**
     * @brief Set the boolean value at the specified index.
     *
     * @param obj The object in which to set the boolean value.
     * @param i The index of the element to set.
     * @param v The boolean value to set.
     */
    virtual void setBool(Object obj, size_t i, const Boolean& v) const {
        (static_cast<C&>(obj).*ptr_)[i] = v.get();
    }

   private:
    std::vector<bool> C::* ptr_;  ///< Pointer to the repeated field in the object
};
}  // namespace reflect

#endif