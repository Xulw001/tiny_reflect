/**
 * @file text.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief This file defines the FieldBase template specialization for repeated string fields.
 * @version 0.1
 * @date 2026-01-17
 *
 * @copyright Copyright (c) 2026
 */
#ifndef REPEATED_FIELD_TEXT_H
#define REPEATED_FIELD_TEXT_H

#include "field.h"

namespace reflect {
/**
 * @brief Specialization of RepeatedFieldInternal for std::vector<std::string>.
 */
template <typename C>
struct FieldBase<C, std::vector<std::string>> : public RepeatedFieldInternal {
   public:
    explicit FieldBase(const char* name, std::vector<std::string> C::* ptr)
        : ptr_(ptr), RepeatedFieldInternal(name, TypeTraits<std::string>::value) {
        ;
    }

    FieldBase(const FieldBase&) = delete;
    FieldBase& operator=(const FieldBase&) = delete;

    /**
     * @brief Returns the number of elements in the repeated string field.
     *
     * @param obj The object from which to retrieve the size of the repeated string field.
     * @return size_t The number of elements in the repeated string field.
     */
    virtual size_t size(ConstObject obj) const {
        auto& array = static_cast<const C&>(obj).*ptr_;
        return array.size();
    }

    /**
     * @brief Retrieves the string value at the specified index from the repeated string field.
     *
     * @param obj The object from which to retrieve the string value.
     * @param i The index of the element to retrieve.
     * @return The string value at the specified index.
     */
    virtual std::string getText(ConstObject obj, size_t i) const {
        return (static_cast<const C&>(obj).*ptr_)[i];
    }

    /**
     * @brief Adds a string value to the end of the repeated string field.
     *
     * @param obj The object to which the string value is to be added.
     * @param v The string value to add.
     */
    virtual void addText(Object obj, const std::string& v) const {
        (static_cast<C&>(obj).*ptr_).push_back(v);
    }

    /**
     * @brief Sets the string value at the specified index in the repeated string field.
     *
     * @param obj The object in which to set the string value.
     * @param i The index of the element to set.
     * @param v The string value to set.
     */
    virtual void setText(Object obj, size_t i, const std::string& v) const {
        (static_cast<C&>(obj).*ptr_)[i] = v;
    }

   private:
    std::vector<std::string> C::* ptr_; ///< Pointer to the repeated string field in the object.
};
}  // namespace reflect

#endif