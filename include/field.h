/**
 * @file field.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief Internal field metadata & access utilities (reflection system)
 * @version 0.3
 * @date 2026-02-22
 *
 * @copyright Copyright (c) 2026
 */
#ifndef FIELD_H
#define FIELD_H

#include <memory>

#include "object.h"
#include "type/exception.h"
#include "type/reference.h"
#include "type/value.h"
#include "type_traits.h"

namespace reflect {
/**
 * @struct FieldInternal
 * @brief Representation a field in an object
 * @details Holds field name/type ID/array/object flags, provides methods for
 *          getting and setting field values, and provides type checking.
 */
struct FieldInternal : public ObjectInternal {
   public:
    /**
     * @brief Construct a new FieldInternal object
     * @param name Field name (non-null)
     * @param type_id Field type ID
     * @param array Whether the field is an array
     * @param object Whether the field is an object
     */
    explicit FieldInternal(const char* name, std::size_t type_id, bool array,
                           bool object) noexcept
        : name_(name), type_id_(type_id), array_(array), object_(object) {};

    /**
     * @brief Get field name
     * @return const char* Field name
     */
    const char* name() const noexcept { return name_; }

    /**
     * @brief Check if field is array
     * @return true if field is an array, false otherwise
     */
    bool is_array() const noexcept { return array_; }

    /**
     * @brief Check if field is object
     * @return true if field is an object, false otherwise
     */
    bool is_object() const noexcept { return object_; }

    /**
     * @brief Get field type ID
     * @return Field type ID (std::size_t)
     */
    virtual std::size_t type_id() const noexcept { return type_id_; }

    /**
     * @brief Get field value from Object
     * @tparam T Type to get (decayed to U via std::decay)
     * @tparam U Decayed type of T (default)
     * @param obj Object to get field from
     * @return Reference to field value (cast to T)
     * @throws ReflectException If type does not match field type
     */
    template <typename T, typename U = typename std::decay<T>::type>
    T& get(Object obj) const {
        if (type_id_ != get_type_id<U>()) {
            throw ReflectException("type mismatch!");
        }
        return GetField(obj).cast<U>();
    }

    /**
     * @brief Set field value with lvalue reference
     * @tparam T Type of the value to set
     * @param obj Object to set field on
     * @param value Lvalue reference to value
     * @throws ReflectException If type does not match field type
     */
    template <typename T>
    void set(Object obj, T& value) const {
        if (type_id_ != get_type_id<T>()) {
            throw ReflectException("type mismatch!");
        }
        SetField(obj, Reference(value));
    }

    /**
     * @brief Set field value with rvalue reference
     * @tparam T Type of the value to set
     * @param obj Object to set field on
     * @param value Rvalue reference to value
     * @note This overload allows setting field with move semantics
     * @throws ReflectException If type does not match field type
     */
    template <typename T>
    void set(Object obj, T&& value) const {
        if (type_id_ != get_type_id<T>()) {
            throw ReflectException("type mismatch!");
        }
        SetField(obj, Value(in_place_type_t<T>{}, value));
    }

    /**
     * @brief Get object from field
     * @param obj Object to get field from
     * @return Object representing the field value
     * @note Override in derived classes for actual object retrieval
     * @throws ReflectException If field is not an object
     */
    virtual Object GetObject(Object obj) const {
        if (!object_) {
            throw ReflectException::format("Field[%s] is not an object", name_);
        }
        return obj;
    }

    /**
     * @brief Set object to field
     * @param obj Object to set field on
     * @param sub Sub-object to set
     * @note Override in derived classes for actual object assignment
     * @throws ReflectException If field is not an object
     */
    virtual void SetObject(Object obj, Object sub) const {
        if (!object_) {
            throw ReflectException::format("Field[%s] is not an object", name_);
        }
    }

   protected:
    /**
     * @brief Get the field value as Reference
     * @param obj Object to get field from
     * @return Reference to field value
     * @note Override in derived classes for actual field value
     */
    virtual Reference GetField(Object obj) const { return Reference(obj); };

    /**
     * @brief Set field with Reference
     * @param obj Object to set field on
     * @param ref Reference to set
     * @note Override in derived classes for actual field assignment
     */
    virtual void SetField(Object obj, Reference ref) const { ; }

    /**
     * @brief Set field with Value
     * @param obj Object to set field on
     * @param val Value to set
     * @note Override in derived classes for actual field assignment
     */
    virtual void SetField(Object obj, Value val) const { ; }

   private:
    const char* name_;     ///< The name of the field
    std::size_t type_id_;  ///< The type Id of the field
    bool array_;           ///< Indicates if the field is an array
    bool object_;          ///< Indicates if the field is an object
};

/**
 * @struct FieldBase
 * @brief Field template base class (inherits FieldInternal)
 * @tparam C Class type containing the field
 * @tparam T Field value type
 * @tparam array Whether T is a repeated (array) type
 * @tparam object Whether T is an object type
 * @tparam const_disable Disables const types
 */
template <typename C, typename T, bool array = is_repeated<T>::value,
          bool object = is_object<typename value_type<T>::type>::value,
          typename = const_disable<T>>
struct FieldBase : public FieldInternal {};

/**
 * @typedef Field
 * @brief Unique pointer to FieldInternal
 */
using Field = std::unique_ptr<FieldInternal>;

}  // namespace reflect

#endif