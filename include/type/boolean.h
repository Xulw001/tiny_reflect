/**
 * @file boolean.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief This header file defines the Boolean class, which encapsulates a
 *        boolean value.
 * @version 0.1
 * @date 2026-01-22
 *
 * @copyright Copyright (c) 2026
 */
#ifndef TYPE_BOOLEAN_H
#define TYPE_BOOLEAN_H

#include "object.h"

namespace reflect {

/**
 * @brief A class representing a boolean value.
 *
 * This class inherits from ObjectInternal and encapsulates a boolean value.
 * It provides a constructor to initialize the value and a method to retrieve
 * it.
 */
struct Boolean : public ObjectInternal {
   public:
    /**
     * @brief Constructs a Boolean object with the given value.
     */
    explicit Boolean(bool v) : value_(v) {}

    /**
     * @brief Retrieves the stored boolean value.
     *
     * @return The stored boolean value.
     */
    bool get() const { return value_; }

   private:
    bool value_;
};
}  // namespace reflect

#endif