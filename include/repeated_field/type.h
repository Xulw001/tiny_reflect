/**
 * @file type.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief Repeated (array) field metadata + reflection utilities (non-object)
 * @version 0.1
 * @date 2026-02-23
 *
 * @copyright Copyright (c) 2026
 */
#ifndef REPEATED_FIELD_TYPE_H
#define REPEATED_FIELD_TYPE_H

#include "repeated_field.h"
#include "type_traits.h"

namespace reflect {
/**
 * @struct FieldBase
 * @brief Field type for array (vector) non-object fields
 * @details Holds C's std::vector<T> member pointer; implements repeated field
 *          get/set
 * @tparam C Containing class type
 * @tparam T Vector element type (non-bool, non-const, non-object)
 * @see RepeatedFieldInternal
 */
template <typename C, typename T>
struct FieldBase<C, std::vector<T>, true, false, const_disable<T>>
    : public RepeatedFieldInternal {
   public:
    /**
     * @brief Constructor for FieldBase
     * @param name Field name
     * @param ptr Pointer to class member (std::vector<T> C::*)
     * @note Type ID = get_type_id<T>(); bool T is forbidden (static_assert)
     */
    explicit FieldBase(const char* name, std::vector<T> C::* ptr)
        : ptr_(ptr), RepeatedFieldInternal(name, get_type_id<T>(), false) {
        static_assert(!std::is_same<T, bool>::value,
                      "bool type is not supported in repeated fields");
    }

    FieldBase(const FieldBase&) = delete;
    FieldBase& operator=(const FieldBase&) = delete;

    /**
     * @brief Get array field size
     */
    virtual std::size_t size(Object obj) const override {
        auto& array = static_cast<C&>(obj).*ptr_;
        return array.size();
    }

    /**
     * @brief Get array element as Reference
     */
    virtual Reference GetField(Object obj, size_t i) const override {
        return Reference((static_cast<C&>(obj).*ptr_)[i]);
    };

    /**
     * @brief Set array element with Reference
     */
    virtual void SetField(Object obj, size_t i, Reference ref) const override {
        (static_cast<C&>(obj).*ptr_)[i] = ref.cast<T>();
    }

    /**
     * @brief Set array element with Value
     */
    virtual void SetField(Object obj, size_t i, Value val) const override {
        (static_cast<C&>(obj).*ptr_)[i] = std::move(val.Access().cast<T>());
    }

    /**
     * @brief Add array element with Reference
     */
    virtual void AddField(Object obj, Reference ref) const override {
        (static_cast<C&>(obj).*ptr_).emplace_back(ref.cast<T>());
    }

    /**
     * @brief Add array element with Value
     */
    virtual void AddField(Object obj, Value val) const override {
        (static_cast<C&>(obj).*ptr_)
            .emplace_back(std::move(val.Access().cast<T>()));
    }

   private:
    std::vector<T> C::* ptr_;  ///< Pointer to C's std::vector<T> repeated field
};
}  // namespace reflect

#endif