/**
 * @file text.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief This header file defines the Text class, which encapsulates a
 *        text value.
 * @version 0.1
 * @date 2026-01-22
 *
 * @copyright Copyright (c) 2026
 */
#ifndef TYPE_TEXT_H
#define TYPE_TEXT_H

#include <string>

#include "object.h"

namespace reflect {

/**
 * @brief A class representing a text value.
 *
 * This class encapsulates a text value and provides methods to access it.
 */
struct Text : public ObjectInternal {
   public:
    /**
     * @brief Constructs a Text object with the given value.
     */
    explicit Text(const std::string& v) : value_(v) { ; }
    explicit Text(const char* v) : value_(v) { ; }

    /**
     * @brief Retrieves the stored text value.
     *
     * @return The stored text value.
     */
    const std::string& get() const { return value_; }

   private:
    std::string value_;
};
}  // namespace reflect

#endif