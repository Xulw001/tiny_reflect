/**
 * @file pointer.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief Smart pointer for ObjectInternal
 * @version 0.2
 * @date 2026-01-22
 *
 * @copyright Copyright (c) 2026
 */
#ifndef POINTER_H
#define POINTER_H

#include <memory>

#include "object.h"

namespace reflect {
/**
 * @struct Pointer
 * @brief Smart pointer wrapper for ObjectInternal (unique ownership)
 * @details Provides RAII-managed access to ObjectInternal instances,with
            implicit conversion to Object for compatibility with
            reflection system APIs.
 */
struct Pointer {
    template <typename T>
    friend struct Constructible;

   public:
    /**
     * @brief Implicit conversion to mutable ObjectInternal reference
     * @return Reference to the managed ObjectInternal instance
     */
    operator ObjectInternal&() { return *ptr_.get(); }

   private:
    /**
     * @brief Constructs a Pointer from a raw ObjectInternal pointer
     * @param ptr Raw pointer to an ObjectInternal instance (must not be null)
     * @note The Pointer takes ownership of the provided raw pointer,
     *       and ptr must not be managed elsewhere.
     */
    explicit Pointer(ObjectInternal* ptr) noexcept : ptr_(ptr) { ; }

   private:
    std::unique_ptr<ObjectInternal>
        ptr_;  ///< Unique pointer to manage ObjectInternal's lifetime
};

/**
 * @typedef ConstPointer
 * @brief Const-qualified Pointer type (read-only access to ObjectInternal)
 */
using ConstPointer = const Pointer;

}  // namespace reflect

#endif