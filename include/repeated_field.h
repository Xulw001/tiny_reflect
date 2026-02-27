/**
 * @file repeated_field.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief Internal repeated field metadata & access utilities
 * @version 0.2
 * @date 2026-01-22
 *
 * @copyright Copyright (c) 2026
 */
#ifndef REPEATED_FIELD_H
#define REPEATED_FIELD_H

#include "field.h"

namespace reflect {
/**
 * @struct RepeatedFieldInternal
 * @brief Internal representation of a repeated (array) field
 * @details Provides size/get/add/set operations for array fields
 */
struct RepeatedFieldInternal : public FieldInternal {
   public:
    /**
     * @brief Construct a new RepeatedFieldInternal object
     * @param name Field name (non-null)
     * @param type_id Field type ID
     * @param object Whether the field is an object
     */
    explicit RepeatedFieldInternal(const char* name, std::size_t type_id,
                                   bool object)
        : FieldInternal(name, type_id, true, object) {};

    /**
     * @brief Get array field size (pure virtual)
     * @param obj Object to get field size from
     * @return Array element count (std::size_t)
     * @note Override in derived classes for actual size retrieval
     */
    virtual std::size_t size(Object obj) const = 0;

    /**
     * @brief Get array element by index
     * @tparam T Type to get (decayed to U via std::decay)
     * @param obj Object to get element from
     * @param i Element index
     * @return Reference to element (cast to T)
     * @throws ReflectException If type does not match field type
     */
    template <typename T, typename U = typename std::decay<T>::type>
    T& get(Object obj, size_t i) const {
        if (type_id() != get_type_id<U>()) {
            throw ReflectException("type mismatch!");
        }
        return GetField(obj, i).cast<U>();
    }

    /**
     * @brief Add element to array (lvalue reference)
     * @tparam T Type of the value to add
     * @param obj Object to add element to
     * @param value Lvalue reference to value
     * @throws ReflectException If type does not match field type
     */
    template <typename T>
    void add(Object obj, T& value) const {
        if (type_id() != get_type_id<T>()) {
            throw ReflectException("type mismatch!");
        }
        AddField(obj, Reference(value));
    }

    /**
     * @brief Add element to array (rvalue reference)
     * @tparam T Type of the value to add
     * @param obj Object to add element to
     * @param value Rvalue reference to value
     * @throws ReflectException If type does not match field type
     */
    template <typename T>
    void add(Object obj, T&& value) const {
        if (type_id() != get_type_id<T>()) {
            throw ReflectException("type mismatch!");
        }
        AddField(obj, Value(in_place_type_t<T>{}, value));
    }

    /**
     * @brief Set array element by index (lvalue reference)
     * @tparam T Type of the value to set
     * @param obj Object to set element on
     * @param i Element index
     * @param value Lvalue reference to value
     * @throws ReflectException If type does not match field type
     */
    template <typename T>
    void set(Object obj, size_t i, T& value) const {
        if (type_id() != get_type_id<T>()) {
            throw ReflectException("type mismatch!");
        }
        SetField(obj, i, Reference(value));
    }

    /**
     * @brief Set array element by index (rvalue reference)
     * @tparam T Type of the value to set
     * @param obj Object to set element on
     * @param i Element index
     * @param value Rvalue reference to value
     * @throws ReflectException If type does not match field type
     */
    template <typename T>
    void set(Object obj, size_t i, T&& value) const {
        if (type_id() != get_type_id<T>()) {
            throw ReflectException("type mismatch!");
        }
        SetField(obj, i, Value(in_place_type_t<T>{}, value));
    }

    /**
     * @brief Get object from repeated field element
     * @param obj Object to get sub-object from
     * @param i Element index
     * @return Object at specified index
     * @note Override in derived classes for actual object retrieval
     * @throws ReflectException If field is not an object
     */
    virtual Object GetObject(Object obj, size_t i) const {
        if (!is_object()) {
            throw ReflectException::format("Field[%s] is not an object",
                                           name());
        }
        return obj;
    }

    /**
     * @brief Set object to repeated field element
     * @param obj Object to set element on
     * @param i Element index
     * @param sub Sub-object to set
     * @note Override in derived classes for actual object assignment
     * @throws ReflectException If field is not an object
     */
    virtual void SetObject(Object obj, size_t i, Object sub) const {
        if (!is_object()) {
            throw ReflectException::format("Field[%s] is not an object",
                                           name());
        }
    }

    /**
     * @brief Add object to repeated field
     * @param obj Object to add element to
     * @param sub Sub-object to add
     * @throws ReflectException If field is not an object
     * @note Override in derived classes for actual object addition
     */
    virtual void AddObject(Object obj, Object sub) const {
        if (!is_object()) {
            throw ReflectException::format("Field[%s] is not an object",
                                           name());
        }
    }

   protected:
    /**
     * @brief Get array element as Reference
     * @param obj Object to get element from
     * @param i Element index
     * @return Reference to element
     * @note Override in derived classes for actual field value retrieval
     */
    virtual Reference GetField(Object obj, size_t i) const {
        return Reference(obj);
    };

    /**
     * @brief Set array element with Reference
     * @param obj Object to set element on
     * @param i Element index
     * @param ref Reference to value to set
     * @note Override in derived classes for actual element assignment
     */
    virtual void SetField(Object obj, size_t i, Reference ref) const { ; }

    /**
     * @brief Set array element with Value
     * @param obj Object to set element on
     * @param i Element index
     * @param val Value to set
     * @note Override in derived classes for actual element assignment
     */
    virtual void SetField(Object obj, size_t i, Value val) const { ; }

    /**
     * @brief Add element with Reference
     * @param obj Object to add element to
     * @param ref Reference to value to add
     * @note Override in derived classes for actual element addition
     */
    virtual void AddField(Object obj, Reference ref) const { ; }

    /**
     * @brief Add element with Value
     * @param obj Object to add element to
     * @param val Value to add
     * @note Override in derived classes for actual element addition
     */
    virtual void AddField(Object obj, Value val) const { ; }
};

/**
 * @struct RepeatedField
 * @brief Wrapper for RepeatedFieldInternal (inherits Field)
 * @details Provides operator-> to cast to RepeatedFieldInternal*
 */
struct RepeatedField : public Field {
   public:
    /**
     * @brief GetRepeatedFieldInternal pointer
     * @return Pointer to internal repeated field
     */
    RepeatedFieldInternal* operator->() {
        return static_cast<RepeatedFieldInternal*>(this->get());
    }

    /**
     * @brief Get const RepeatedFieldInternal pointer
     * @return Const pointer to internal repeated field
     */
    const RepeatedFieldInternal* operator->() const {
        return static_cast<const RepeatedFieldInternal*>(this->get());
    }
};

}  // namespace reflect

#endif