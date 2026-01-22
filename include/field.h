/**
 * @file field.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief This file defines the FieldInternal structure and FieldBase template for handling
 *        reflection of various data types in a generic manner. It provides methods to get
 *        and set values of different types, including boolean, string, integral, and
 *        floating-point types.
 * @version 0.2
 * @date 2026-01-22
 *
 * @copyright Copyright (c) 2026
 */
#ifndef FIELD_H
#define FIELD_H
#include <memory>

#include "type/boolean.h"
#include "type/decimal.h"
#include "type/integer.h"
#include "type/text.h"
#include "type_traits.h"

namespace reflect {

/**
 * @brief The FieldInternal struct provides an interface for accessing and modifying
 *        fields of different types in a reflective manner.
 */
struct FieldInternal : public ObjectInternal {
   public:
    /**
     * @brief Construct a new FieldInternal object.
     *
     * @param name The name of the field.
     * @param type The type of the field.
     * @param array Indicates if the field is an array.
     */
    explicit FieldInternal(const char* name, TypeEnum type, bool array)
        : name_(name), type_(type), array_(array) {};

    /**
     * @brief Get the type of the field.
     *
     * @return TypeEnum The type of the field.
     */
    TypeEnum type() const { return type_; }

    /**
     * @brief Get the name of the field.
     *
     * @return const char* The name of the field.
     */
    const char* name() const { return name_; }

    /**
     * @brief Check if the field is an array.
     *
     * @return true if the field is an array, false otherwise.
     */
    bool is_array() const { return array_; }

    /**
     * @brief Get the type id of the field.
     *
     * @return size_t The type id of the field.
     */
    virtual size_t type_id() const { return type_; }

    // Template methods for getting values of different types
    template <typename T>
    typename std::enable_if<std::is_same<T, bool>::value, bool>::type get(ConstObject obj) const {
        return getBool(obj).get();
    }

    template <typename T>
    typename std::enable_if<std::is_same<T, std::string>::value, std::string>::type get(
        ConstObject obj) const {
        return getText(obj).get();
    }

    template <typename T>
    typename std::enable_if<std::is_integral<T>::value && !std::is_same<T, bool>::value, T>::type
    get(ConstObject obj) const {
        return getInteger(obj).get<T>();
    }

    template <typename T>
    typename std::enable_if<std::is_floating_point<T>::value, T>::type get(ConstObject obj) const {
        return getDecimal(obj).get<T>();
    }

    /**
     * @brief Get the object associated with this field.
     *
     * @param obj The object from which to get the field.
     * @return ConstObject The associated object.
     */
    virtual ConstObject getObject(ConstObject obj) const { return obj; };

    /**
     * @brief Get the object associated with this field.
     *
     * @param obj The object from which to get the field.
     * @return Object The associated object.
     * */
    virtual Object getObject(Object obj) const { return obj; };

    // Template methods for setting values of different types
    void set(Object obj, bool v) const { setBool(obj, Boolean(v)); }
    void set(Object obj, const char* v) const { setText(obj, Text(v)); }
    void set(Object obj, const std::string& v) const { setText(obj, Text(v)); }

    template <typename T, typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
    void set(Object obj, T v) const {
        setInteger(obj, Integer(v));
    }

    template <typename T, typename std::enable_if<std::is_floating_point<T>::value, int>::type = 1>
    void set(Object obj, T v) const {
        setDecimal(obj, Decimal(v));
    }

    /**
     * @brief Set the object associated with this field.
     *
     * @param obj The object to set the field on.
     * @param o The object to associate with this field.
     */
    virtual void set(Object obj, ConstObject o) const { ; }

   protected:
    // Protected methods for getting values
    virtual Boolean getBool(ConstObject obj) const { return Boolean(true); }
    virtual Integer getInteger(ConstObject obj) const { return Integer(0); }
    virtual Text getText(ConstObject obj) const { return Text(""); }
    virtual Decimal getDecimal(ConstObject obj) const { return Decimal(0.0f); };

    // Protected methods for setting values
    virtual void setBool(Object obj, const Boolean& v) const { ; }
    virtual void setInteger(Object obj, const Integer& v) const { ; }
    virtual void setText(Object obj, const Text& v) const { ; }
    virtual void setDecimal(Object obj, const Decimal& v) const { ; }

   private:
    const char* name_;  ///< The name of the field.
    TypeEnum type_;     ///< The type of the field.
    bool array_;        ///< Indicates if the field is an array.
};

/**
 * @brief The FieldBase template provides a base for creating field types with specific
 *        characteristics.
 */
template <typename C, typename T, typename = void>
struct FieldBase : public FieldInternal {};

/**
 * @brief A unique pointer type for FieldInternal.
 */
using Field = std::unique_ptr<FieldInternal>;

}  // namespace reflect

#endif