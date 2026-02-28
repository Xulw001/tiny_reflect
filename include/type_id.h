/**
 * @file type_id.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief Reflection system unique type ID generation (config/type-driven)
 * @version 0.2
 * @date 2026-02-21
 *
 * @copyright Copyright (c) 2026
 */
#ifndef TYPE_ID_H
#define TYPE_ID_H

#include <atomic>

#include "type_traits.h"

namespace reflect {
/**
 * @struct DefaultConfig
 * @brief Default configuration for type ID generation, starting from 0x0.
 */
struct DefaultConfig {
    const static std::size_t CPPTYPE = 0x0;
};

/**
 * @struct CustomConfig
 * @brief Custom configuration for type ID generation, starting from 0x10000.
 */
struct CustomConfig {
    const static std::size_t CPPTYPE = 0x10000;
};

/**
 * @struct TypeIdBase
 * @brief Thread-safe config-driven unique type ID generator base
 * @details Generates unique type IDs via atomic counter starting at
 *          Config::CPPTYPE
 * @tparam Config Struct with CPPTYPE (starting value for ID counter)
 * @note Thread-safe via std::atomic; IDs increment sequentially
 */
template <typename Config>
struct TypeIdBase {
    /**
     * @brief Generates a unique type ID (atomic increment)
     * @return Unique type ID (size_t) incremented from Config::CPPTYPE
     */
    static size_t generate_id() {
        static std::atomic<size_t> counter{Config::CPPTYPE};
        return counter++;
    }
};

/**
 * @struct TypeId
 * @brief Type-specific unique ID generator (config-driven, thread-safe)
 * @details Generates a fixed unique type ID for T via TypeIdBase<Config>;
 *          initialized once (static const) and constant for program lifetime
 * @tparam T Type to generate a unique ID for
 * @note Thread-safe initialization via static const; single ID per T+Config
 * combination (no duplicate IDs)
 */
template <typename T, typename Config>
struct TypeId {
    /**
     * @brief Gets fixed unique ID for T
     * @return Fixed size_t ID for T, generated once via TypeIdBase<Config>
     */
    static size_t get_type_id() {
        static const size_t id = TypeIdBase<Config>::generate_id();
        return id;
    }
};

/**
 * @typedef ConfigSelector
 * @brief Config selector for type ID generation (object vs non-object)
 * @details Uses selector_t to choose CustomConfig for object types and
 *          DefaultConfig for non-objects
 * @tparam T Target type to select config for(volatile qualifiers removed)
 * @tparam U Unqualified type of T (std::remove_volatile<T>::type, default)
 */
template <typename T, typename U = typename std::remove_volatile<T>::type>
using ConfigSelector = selector_t<is_object<U>, CustomConfig, DefaultConfig>;

/**
 * @brief Gets fixed unique type ID for T (ConfigSelector-driven)
 * @tparam T Non-reference type to get unique ID for (enabled via enable_if)
 * @return Fixed unique size_t ID for T (from TypeId<T, ConfigSelector<T>>)
 * @note Enabled only for non-reference types; volatile qualifiers are ignored
 */
template <typename T,
          typename std::enable_if<!std::is_reference<T>::value, int>::type = 0>
inline size_t get_type_id() {
    return TypeId<T, ConfigSelector<T>>::get_type_id();
}

}  // namespace reflect

#endif