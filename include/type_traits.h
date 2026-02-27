/**
 * @file type_traits.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief Type traits for reflection system
 * @version 0.2
 * @date 2026-02-24
 *
 * @copyright Copyright (c) 2026
 */
#ifndef TYPE_TRAITS_H
#define TYPE_TRAITS_H

#include <vector>

#include "object.h"

namespace reflect {

template <typename>
struct is_repeated : std::false_type {};

template <typename T>
struct is_repeated<std::vector<T>> : std::true_type {};

template <typename T>
using is_object = typename std::is_base_of<ObjectInternal, T>;

template <typename T>
struct value_type {
    using type = T;
};

template <typename T>
struct value_type<std::vector<T>> {
    using type = T;
};

template <typename T>
using value_type_t = typename value_type<T>::type;

template <typename cond, typename First, typename Second>
using selector_t = typename std::conditional<cond::value, First, Second>::type;

template <typename T>
using const_disable = typename std::enable_if<!std::is_const<T>::value>::type;

}  // namespace reflect

#endif