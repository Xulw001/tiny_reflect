/**
 * @file type.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief Field metadata + reflection utilities (non-array/non-object fields)
 * @version 0.1
 * @date 2026-02-23
 *
 * @copyright Copyright (c) 2026
 */
#ifndef FIELD_TYPE_H
#define FIELD_TYPE_H

#include "field.h"
#include "type_traits.h"

namespace reflect {
/**
 * @struct FieldBase
 * @brief Field type for non-array, non-object fields
 * @details Holds C's T member pointer; implements field get/set
 * @tparam C Containing class type
 * @tparam T Field value type (non-const, non-array, non-object)
 * @see FieldInternal
 */
template <typename C, typename T>
struct FieldBase<C, T, false, false, const_disable<T>> : public FieldInternal {
   public:
    /**
     * @brief Constructor for FieldBase
     * @param name Field name
     * @param ptr Pointer to class member (T C::*)
     */
    explicit FieldBase(const char* name, T C::* ptr)
        : ptr_(ptr), FieldInternal(name, get_type_id<T>(), false, false) {}

    FieldBase(const FieldBase&) = delete;
    FieldBase& operator=(const FieldBase&) = delete;

    /**
     * @brief Get field value as Reference
     */
    virtual Reference GetField(Object obj) const override {
        return Reference(static_cast<C&>(obj).*ptr_);
    };

    /**
     * @brief Set field value with Reference
     */
    virtual void SetField(Object obj, Reference ref) const override {
        static_cast<C&>(obj).*ptr_ = ref.cast<T>();
    }

    /**
     * @brief Set field value with Value
     */
    virtual void SetField(Object obj, Value val) const override {
        static_cast<C&>(obj).*ptr_ = std::move(val.Access().cast<T>());
    }

   private:
    T C::* ptr_;  ///< Pointer to C's T member (field)
};
}  // namespace reflect

#endif