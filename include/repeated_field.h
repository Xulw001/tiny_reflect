/**
 * @file repeated_field.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief This file contains the definition of the RepeatedFieldInternal class, which
 *        represents a repeated field in a reflective object.
 * @version 0.1
 * @date 2026-01-17
 *
 * @copyright Copyright (c) 2026
 */
#ifndef REPEATED_FIELD_H
#define REPEATED_FIELD_H

#include "field.h"

namespace reflect {
/**
 * @brief The RepeatedFieldInternal class represents a repeated field in a reflective object.
 * It inherits from the FieldInternal class and provides additional functionality for
 * handling repeated fields.
 */
struct RepeatedFieldInternal : public FieldInternal {
   public:
    explicit RepeatedFieldInternal(const char* name, TypeEnum type)
        : FieldInternal(name, type, true) {};

    /**
     * @brief Gets the number of elements in the repeated field.
     *
     * This function is a template specialization of the size function for repeated
     * fields. It returns the number of elements in the repeated field.
     *
     * @param obj The object whose field size is to be retrieved.
     * @return The number of elements in the repeated field.
     */
    virtual size_t size(ConstObject obj) const = 0;

    /**
     * @brief Gets the value of a boolean field at the given index.
     *
     * This function is a template specialization of the get function for boolean
     * fields. It returns the value of the boolean field at the given index.
     *
     * @param obj The object whose field value is to be retrieved.
     * @param i The index of the field value to be retrieved.
     * @return The value of the boolean field at the given index.
     */
    template <typename T>
    typename std::enable_if<std::is_same<T, bool>::value, bool>::type get(ConstObject obj,
                                                                          size_t i) const {
        return getBool(obj, i);
    }

    /**
     * @brief Gets the value of a string field at the given index.
     *
     * This function is a template specialization of the get function for string
     * fields. It returns the value of the string field at the given index.
     *
     * @param obj The object whose field value is to be retrieved.
     * @param i The index of the field value to be retrieved.
     * @return The value of the string field at the given index.
     */
    template <typename T>
    typename std::enable_if<std::is_same<T, std::string>::value, std::string>::type get(
        ConstObject obj, size_t i) const {
        return getText(obj, i);
    }

    /**
     * @brief Gets the value of an integral field at the given index.
     *
     * This function is a template specialization of the get function for integral
     * fields. It returns the value of the integral field at the given index.
     *
     * @param obj The object whose field value is to be retrieved.
     * @param i The index of the field value to be retrieved.
     * @return The value of the integral field at the given index.
     */
    template <typename T>
    typename std::enable_if<std::is_integral<T>::value && !std::is_same<T, bool>::value, T>::type
    get(ConstObject obj, size_t i) const {
        return getInteger(obj, i).get<T>();
    }

    /**
     * @brief Gets the value of a floating-point field at the given index.
     *
     * This function is a template specialization of the get function for floating-point
     * fields. It returns the value of the floating-point field at the given index.
     *
     * @param obj The object whose field value is to be retrieved.
     * @param i The index of the field value to be retrieved.
     * @return The value of the floating-point field at the given index.
     */
    template <typename T>
    typename std::enable_if<std::is_floating_point<T>::value, T>::type get(ConstObject obj,
                                                                           size_t i) const {
        return getDecimal(obj, i).get<T>();
    }

    /**
     * @brief Gets the object at the given index from the given object's repeated field.
     *
     * This function is a template specialization of the getObject function for repeated
     * fields. It returns the object at the given index from the given object's repeated
     * field.
     *
     * @param obj The object whose field object is to be retrieved.
     * @param i The index of the field object to be retrieved.
     * @return The object at the given index from the given object's repeated field.
     */
    virtual ConstObject getObject(ConstObject obj, size_t i) const { return obj; };

    /**
     * @brief Adds a boolean value to the given object's repeated field.
     *
     * This template specialization of the add function is used for boolean types. It
     * adds the boolean value to the given object's repeated field.
     *
     * @param obj The object to which the value is to be added.
     * @param v The boolean value to be added to the object's repeated field.
     */
    void add(Object obj, bool v) const { addBool(obj, v); }

    /**
     * @brief Adds a string value to the given object's repeated field.
     *
     * This template specialization of the add function is used for string types. It
     * adds the string value to the given object's repeated field.
     *
     * @param obj The object to which the value is to be added.
     * @param v The string value to be added to the object's repeated field.
     */
    void add(Object obj, const char* v) const { addText(obj, v); }
    void add(Object obj, const std::string& v) const { addText(obj, v); }

    /**
     * @brief Sets a boolean value in the given object's repeated field at the given index.
     *
     * This template specialization of the set function is used for boolean types. It
     * sets the boolean value in the given object's repeated field at the given index.
     *
     * @param obj The object whose field value is to be set.
     * @param i The index of the field value to be set.
     * @param v The boolean value to be set in the object's repeated field.
     */
    void set(Object obj, size_t i, bool v) const { setBool(obj, i, v); }

    /**
     * @brief Sets a string value in the given object's repeated field at the given index.
     *
     * This template specialization of the set function is used for string types. It
     * sets the string value in the given object's repeated field at the given index.
     *
     * @param obj The object whose field value is to be set.
     * @param i The index of the field value to be set.
     * @param v The string value to be set in the object's repeated field.
     */
    void set(Object obj, size_t i, const char* v) const { setText(obj, i, v); }
    void set(Object obj, size_t i, const std::string& v) const { setText(obj, i, v); }

    /**
     * @brief Adds a value of type T to the given object at the end of its corresponding field.
     *
     * This template specialization of the add function is used for integral types. It
     * adds the value of type T to the given object at the end of its corresponding field.
     *
     * @param obj The object to which the value is to be added.
     * @param v The value to be added to the object's field.
     */
    template <typename T,
              typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
    void add(Object obj, T v) const {
        addInteger(obj, v);
    }

    /**
     * @brief Adds a value of type T to the given object at the end of its floating-point field.
     *
     * This template specialization of the add function is used for floating-point types. It
     * adds the value of type T to the given object at the end of its floating-point field.
     *
     * @param obj The object to which the value is to be added.
     * @param v The value to be added to the object's field.
     */
    template <typename T,
              typename std::enable_if<std::is_floating_point<T>::value, int>::type = 1>
    void add(Object obj, T v) const {
        addDecimal(obj, v);
    }

    /**
     * @brief Sets the value of an integral field at the given index.
     *
     * This template specialization of the set function is used for integral types. It
     * sets the value of the integral field at the given index.
     *
     * @param obj The object whose field value is to be set.
     * @param i The index of the field value to be set.
     * @param v The value to be set for the field at the given index.
     */
    template <typename T,
              typename std::enable_if<std::is_integral<T>::value, int>::type = 0>
    void set(Object obj, size_t i, T v) const {
        setInteger(obj, i, v);
    }

    /**
     * @brief Sets the value of a floating-point field at the given index.
     *
     * This template specialization of the set function is used for floating-point types. It
     * sets the value of the floating-point field at the given index.
     *
     * @param obj The object whose field value is to be set.
     * @param i The index of the field value to be set.
     * @param v The value to be set for the field at the given index.
     */
    template <typename T,
              typename std::enable_if<std::is_floating_point<T>::value, int>::type = 1>
    void set(Object obj, size_t i, T v) const {
        setDecimal(obj, i, v);
    }

    /**
     * @brief Adds the value of the given ConstObject to the given object at the end of its field.
     *
     * This function adds the value of the given ConstObject to the given object at the end of its field.
     *
     * @param obj The object to which the value is to be added.
     * @param o The value to be added to the object's field.
     */
    virtual void add(Object obj, ConstObject o) const { ; }

    /**
     * @brief Sets the value of the given ConstObject at the given index in the given object's field.
     *
     * This function sets the value of the given ConstObject at the given index in the given object's field.
     *
     * @param obj The object whose field value is to be set.
     * @param i The index of the field value to be set.
     * @param o The value to be set for the field at the given index.
     */
    virtual void set(Object obj, size_t i, ConstObject o) const { ; }

   protected:
    virtual void setBool(Object obj, size_t i, bool v) const { ; }
    virtual void setInteger(Object obj, size_t i, Integer v) const { ; }
    virtual void setText(Object obj, size_t i, const std::string& v) const { ; }
    virtual void setDecimal(Object obj, size_t i, Decimal v) const { ; }

    virtual void addBool(Object obj, bool v) const { ; }
    virtual void addInteger(Object obj, Integer v) const { ; }
    virtual void addText(Object obj, const std::string& v) const { ; }
    virtual void addDecimal(Object obj, Decimal v) const { ; }

    virtual bool getBool(ConstObject obj, size_t i) const { return true; }
    virtual Integer getInteger(ConstObject obj, size_t i) const { return 0; }
    virtual std::string getText(ConstObject obj, size_t i) const { return ""; }
    virtual Decimal getDecimal(ConstObject obj, size_t i) const { return 0.0f; };
};

struct RepeatedField : public Field {
   public:
    RepeatedFieldInternal* operator->() { return static_cast<RepeatedFieldInternal*>(this->get()); }
    const RepeatedFieldInternal* operator->() const {
        return static_cast<const RepeatedFieldInternal*>(this->get());
    }
};

}  // namespace reflect

#endif