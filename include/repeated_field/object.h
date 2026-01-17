/**
 * @file object.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief This file defines the FieldBase template specialization for repeated object fields.
 * @version 0.1
 * @date 2026-01-17
 *
 * @copyright Copyright (c) 2026
 */
#ifndef REPEATED_FIELD_OBJECT_H
#define REPEATED_FIELD_OBJECT_H

#include "field.h"
#include "type_id.h"

namespace reflect {
/**
 * @brief Specialization of FieldBase for repeated object fields.
 */
template <typename C, typename T>
struct FieldBase<C, std::vector<T>, typename std::enable_if<std::is_base_of<ObjectInternal, T>::value>::type>
    : public RepeatedFieldInternal {
   public:
    explicit FieldBase(const char* name, std::vector<T> C::* ptr)
        : ptr_(ptr), type_id_(get_type_id<T>()), RepeatedFieldInternal(name, TypeTraits<T>::value) {
        ;
    }

    FieldBase(const FieldBase&) = delete;
    FieldBase& operator=(const FieldBase&) = delete;

    /**
     * @brief Retrieves the size of the repeated field in the given object.
     *
     * @param obj The object from which to retrieve the size of the repeated field.
     * @return size_t The size of the repeated field in the given object.
     */
    virtual size_t size(ConstObject obj) const {
        auto& array = static_cast<const C&>(obj).*ptr_;
        return array.size();
    }

    virtual size_t type_id() const { return type_id_; }

    /**
     * @brief Retrieves the ObjectInternal at the specified index from the repeated field.
     *
     * @param obj The object from which to retrieve the ObjectInternal.
     * @param i The index of the element to retrieve.
     * @return The ObjectInternal at the specified index from the repeated field.
     */
    virtual ConstObject getObject(ConstObject obj, size_t i) const {
        return (static_cast<const C&>(obj).*ptr_)[i];
    };

    /**
     * @brief Retrieves the ObjectInternal at the specified index from the repeated field.
     *
     * @param obj The object from which to retrieve the ObjectInternal.
     * @param i The index of the element to retrieve.
     * @return The ObjectInternal at the specified index from the repeated field.
     */
    virtual Object getObject(Object obj, size_t i) const {
        return (static_cast<C&>(obj).*ptr_)[i];
    };

    /**
     * @brief Adds a new element to the repeated field.
     *
     * @param obj The object to which the element is to be added.
     * @param o The element to be added.
     */
    virtual void add(Object obj, ConstObject o) const {
        (static_cast<C&>(obj).*ptr_).emplace_back(static_cast<const T&>(o));
    }

    /**
     * @brief Sets the ObjectInternal at the specified index in the repeated field.
     *
     * @param obj The object in which to set the ObjectInternal.
     * @param i The index of the element to set.
     * @param o The ObjectInternal to set.
     */
    virtual void set(Object obj, size_t i, ConstObject o) const {
        (static_cast<C&>(obj).*ptr_)[i] = static_cast<const T&>(o);
    }

   private:
    std::vector<T> C::* ptr_;  ///< Pointer to the repeated field.
    size_t type_id_;           ///< Type id of the field.
};

}  // namespace reflect

#endif