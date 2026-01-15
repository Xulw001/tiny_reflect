/**
 * @file pointer.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief This file defines the Pointer class, which manages a unique pointer to an ObjectInternal instance.
 * @version 0.1
 * @date 2026-01-15
 *
 * @copyright Copyright (c) 2026
 */
#ifndef POINTER_H
#define POINTER_H
#include <memory>

#include "object.h"

namespace reflect {
/**
 * @brief A class that manages a pointer to an ObjectInternal instance.
 *
 * The Pointer class encapsulates a unique pointer to an ObjectInternal object,
 * providing a way to manage the object's lifetime automatically. It allows
 * conversion to a reference of ObjectInternal for easy access to the underlying object.
 */
struct Pointer {
   public:
    /**
     * @brief Constructs a Pointer with the given ObjectInternal pointer.
     *
     * @param ptr A pointer to an ObjectInternal object.
     */
    Pointer(ObjectInternal* ptr) : ptr_(ptr) { ; }

    /**
     * @brief Converts the Pointer to a reference of ObjectInternal.
     *
     * This operator allows the Pointer to be used as if it were a reference
     * to the underlying ObjectInternal object.
     *
     * @return A reference to the ObjectInternal object.
     */
    operator ObjectInternal&() { return *ptr_.get(); }

   private:
    std::unique_ptr<ObjectInternal> ptr_;  ///< Unique pointer to manage ObjectInternal's lifetime.
};

using ConstPointer = const Pointer;

}  // namespace reflect

#endif