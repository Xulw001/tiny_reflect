/**
 * @file object.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief Base class and reference types for reflection-enabled objects
 * @version 0.1
 * @date 2026-01-15
 *
 * @copyright Copyright (c) 2026
 */
#ifndef OBJECT_H
#define OBJECT_H

namespace reflect {
/**
 * @struct ObjectInternal
 * @brief Base class for reflection-enabled custom objects
 * @note Inheritance from this class is required for custom types to support
 *       reflection
 */
struct ObjectInternal {
    virtual ~ObjectInternal() = default;
};

/**
 * @typedef Object
 * @brief Mutable reference to ObjectInternal
 */
using Object = ObjectInternal&;

/**
 * @typedef ConstObject
 * @brief Const reference to ObjectInternal
 */
using ConstObject = const ObjectInternal&;
}  // namespace reflect

#endif