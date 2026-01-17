/**
 * @file type_id.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief This header file defines a mechanism for generating unique type IDs
 *        for C++ types. It includes a base class for ID generation and a
 *        template struct to retrieve type IDs for specific types.
 * @version 0.1
 * @date 2026-01-15
 *
 * @copyright Copyright (c) 2026
 */
#ifndef TYPE_ID_H
#define TYPE_ID_H

#include <atomic>

#include "type_traits.h"

namespace reflect {

/**
 * @brief Base class for generating unique type IDs.
 *
 * This class provides a static method to generate unique IDs for types
 * using an atomic counter. The IDs are generated starting from a predefined
 * maximum value (MAX_CPPTYPE).
 */
struct TypeIdBase {
    /**
     * @brief Generates a unique ID.
     *
     * @return size_t A unique ID for a type.
     */
    static size_t generate_id() {
        static std::atomic<size_t> counter{MAX_CPPTYPE};
        return counter++;
    }
};

/**
 * @brief Template struct for obtaining a unique type ID for a given type T.
 *
 * This struct uses the TypeIdBase to generate a unique ID for the type T
 * when the get_type_id method is called for the first time.
 */
template <typename T>
struct TypeId {
    /**
     * @brief Retrieves the unique type ID for type T.
     *
     * @return size_t The unique type ID for type T.
     */
    static size_t get_type_id() {
        static const size_t id = TypeIdBase::generate_id();
        return id;
    }

   private:
};

/**
 * @brief Retrieves the type ID for a given type T.
 *
 * This function checks if T is derived from ObjectInternal. If it is,
 * it retrieves the type ID using TypeId<T>. Otherwise, it retrieves the
 * type ID from TypeTraits<T>.
 *
 * @tparam T The type for which to retrieve the ID.
 * @return size_t The type ID for type T.
 */
template <typename T>
size_t get_type_id() {
    if (std::is_base_of<ObjectInternal, T>::value) {
        return TypeId<T>::get_type_id();
    } else {
        return TypeTraits<T>::value;
    }
}
}  // namespace reflect

#endif