/**
 * @file object.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief Object field metadata + reflection utilities (non-array)
 * @version 0.2
 * @date 2026-02-23
 *
 * @copyright Copyright (c) 2026
 */
#ifndef FIELD_OBJECT_H
#define FIELD_OBJECT_H

#include "field.h"
#include "type_traits.h"

namespace reflect {
/**
 * @struct FieldBase
 * @brief Field type for non-array, object fields
 * @details Holds C's T member pointer; implements object field get/set
 * @tparam C Containing class type
 * @tparam T Field value type (non-const, non-array, object)
 * @see FieldInternal
 */
template <typename C, typename T>
struct FieldBase<C, T, false, true, const_disable<T>> : public FieldInternal {
   public:
    /**
     * @brief Constructor for FieldBase
     * @param name Field name
     * @param ptr Pointer to class member (T C::*)
     */
    explicit FieldBase(const char* name, T C::* ptr)
        : ptr_(ptr), FieldInternal(name, get_type_id<T>(), false, true) {}

    FieldBase(const FieldBase&) = delete;
    FieldBase& operator=(const FieldBase&) = delete;

    /**
     * @brief Get object field value
     */
    virtual Object GetObject(Object obj) const override {
        return static_cast<C&>(obj).*ptr_;
    };

    /**
     * @brief Set object field value
     */
    virtual void SetObject(Object obj, Object o) const override {
        static_cast<C&>(obj).*ptr_ = static_cast<T&>(o);
    }

   private:
    T C::* ptr_;  ///< Pointer to C's T object member (field)
};
}  // namespace reflect

#endif