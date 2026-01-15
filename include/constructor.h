/**
 * @file constructor.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief This header file defines the Constructible template struct, which provides
 *        a mechanism for constructing objects of a specified type T using dynamic
 *        memory allocation. It also defines a type alias for a constructor function
 *        pointer.
 * @version 0.1
 * @date 2026-01-15
 *
 * @copyright Copyright (c) 2026
 */
#ifndef CONSTRUCTOR_H
#define CONSTRUCTOR_H

#include "pointer.h"

namespace reflect {
/**
 * @brief A template struct that provides a way to construct objects of type T.
 *
 * This struct inherits from ObjectInternal and includes a static method
 * to create a new instance of T using dynamic memory allocation.
 *
 * @tparam T The type of object that can be constructed.
 */
template <typename T>
struct Constructible : public ObjectInternal {
   public:
    /**
     * @brief Constructs a new instance of T.
     *
     * @return Pointer A pointer to the newly created instance of T.
     */
    static Pointer constructor() {
        return Pointer(new T());
    }
};

using Constructor = Pointer (*)();
};  // namespace reflect

#endif