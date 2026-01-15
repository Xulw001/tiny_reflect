/**
 * @file text.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief This header file defines the FieldBase template structure for string fields.
 *
 * @tparam C The class type that contains the string member variable.
 *
 * @version 0.1
 * @date 2026-01-15
 *
 * @copyright Copyright (c) 2026
 */
#ifndef FIELD_TEXT_H
#define FIELD_TEXT_H

#include "field.h"

namespace reflect {
template <typename C>
struct FieldBase<C, std::string> : public FieldInternal {
   public:
    /**
     * @brief Constructs a FieldBase object for a string member variable.
     *
     * @param name The name of the field.
     * @param ptr Pointer to the string member variable in class C.
     */
    explicit FieldBase(const char* name, std::string C::* ptr)
        : ptr_(ptr), FieldInternal(name, TypeTraits<std::string>::value, false) {
        ;
    }

    FieldBase(const FieldBase&) = delete;
    FieldBase& operator=(const FieldBase&) = delete;

    /**
     * @brief Retrieves the string value from the specified object.
     *
     * @param obj The object from which to retrieve the string value.
     * @return The string value of the member variable.
     */
    virtual std::string getText(ConstObject obj) const { return static_cast<const C&>(obj).*ptr_; }

    /**
     * @brief Sets the string value of the specified object.
     *
     * @param obj The object in which to set the string value.
     * @param v The new string value to set.
     */
    virtual void setText(Object obj, const std::string& v) const { static_cast<C&>(obj).*ptr_ = v; }

   private:
    std::string C::* ptr_;  ///< Pointer to the string member variable.
};
}  // namespace reflect

#endif