/**
 * @file constructor.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief CRTP utilities for reflection-aware object construction
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
 * @struct Constructible
 * @brief CRTP base for reflection-enabled default-constructible types
 * @tparam T Derived type to enable reflection-supported default construction
 * @note T must be a default-constructible type
 */
template <typename T>
struct Constructible : public ObjectInternal {
   public:
    /**
     * @brief Creates T instance wrapped in RAII-managed Pointer
     * @return Pointer owning the new T instance
     */
    static Pointer constructor() { return Pointer(new T()); }
};

/**
 * @typedef Constructor
 * @brief Function pointer for reflection object construction
 */
using Constructor = Pointer (*)();
};  // namespace reflect

#endif