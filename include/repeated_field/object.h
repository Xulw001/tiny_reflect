/**
 * @file object.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief Repeated (array) object field metadata + reflection utilities
 * @version 0.2
 * @date 2026-02-23
 *
 * @copyright Copyright (c) 2026
 */
#ifndef REPEATED_FIELD_OBJECT_H
#define REPEATED_FIELD_OBJECT_H

#include "repeated_field.h"
#include "type_traits.h"

namespace reflect {
/**
 * @struct FieldBase
 * @brief Field type for array (vector) object fields
 * @details Holds C's std::vector<T> member pointer; implements repeated object
 *          get/set
 * @tparam C Containing class type
 * @tparam T Vector element type (non-const, object)
 * @see RepeatedFieldInternal
 */
template <typename C, typename T>
struct FieldBase<C, std::vector<T>, true, true, const_disable<T>>
    : public RepeatedFieldInternal {
   public:
    /**
     * @brief Constructor for FieldBase
     * @param name Field name
     * @param ptr Pointer to class member (std::vector<T> C::*)
     */
    explicit FieldBase(const char* name, std::vector<T> C::* ptr)
        : ptr_(ptr), RepeatedFieldInternal(name, get_type_id<T>(), true) {}

    FieldBase(const FieldBase&) = delete;
    FieldBase& operator=(const FieldBase&) = delete;

    /**
     * @brief Get array field size
     */
    virtual size_t size(Object obj) const override {
        auto& array = static_cast<const C&>(obj).*ptr_;
        return array.size();
    }

    /**
     * @brief Get array object element
     */
    virtual Object GetObject(Object obj, size_t i) const override {
        return (static_cast<C&>(obj).*ptr_)[i];
    }

    /**
     * @brief Set array object element
     */
    virtual void SetObject(Object obj, size_t i, Object sub) const override {
        (static_cast<C&>(obj).*ptr_)[i] = static_cast<T&>(sub);
    }

    /**
     * @brief Add array object element
     */
    virtual void AddObject(Object obj, Object sub) const override {
        (static_cast<C&>(obj).*ptr_).emplace_back(static_cast<T&>(sub));
    }

   private:
    std::vector<T> C::*
        ptr_;  ///< Pointer to C's std::vector<T> object repeated field
};

}  // namespace reflect

#endif