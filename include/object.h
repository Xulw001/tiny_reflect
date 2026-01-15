/**
 * @file object.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief This file defines the internal object representation for reflection.
 * @version 0.1
 * @date 2026-01-15
 *
 * @copyright Copyright (c) 2026
 */
#ifndef OBJECT_H
#define OBJECT_H

namespace reflect {
/**
 * @brief Base class for internal object representation.
 *
 * This class serves as a base for all objects that will be reflected upon.
 * It provides a virtual destructor to ensure proper cleanup of derived classes.
 */
struct ObjectInternal {
    virtual ~ObjectInternal() = default;  ///< Virtual destructor for proper cleanup.
};

using Object = ObjectInternal&;             ///< Alias for a reference to a non-const ObjectInternal.
using ConstObject = const ObjectInternal&;  ///< Alias for a reference to a const ObjectInternal.
}  // namespace reflect

#endif