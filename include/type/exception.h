/**
 * @file exception.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief Specialized exception for reflection system errors
 * @version 0.1
 * @date 2026-02-24
 *
 * @copyright Copyright (c) 2026
 */
#ifndef TYPE_EXCEPTION_H
#define TYPE_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace reflect {
/**
 * @class ReflectException
 * @brief Exception class for reflection system errors
 * @details Specialized exception class derived from std::exception, providing
 *          both direct message construction and formatted message support.
 * @extends std::exception
 * @note Formatted messages limited to 1023 bytes (truncated if longer)
 */
class ReflectException : public std::exception {
   public:
    /**
     * @brief Constructs from C-string message
     * @param message Null-terminated C string error message
     */
    explicit ReflectException(const char* message) : message_(message) {}

    /**
     * @brief Construct from std::string message (move-optimized)
     * @param message std::string error message
     */
    explicit ReflectException(std::string message)
        : message_(std::move(message)) {}

    /**
     * @brief Create formatted exception message(printf-style)
     * @tparam Args Variadic template args for format placeholders
     * @param format printf-style format string
     * @param args Arguments for format substitution
     * @return ReflectException instance with formatted error message
     * @warning Truncated to 1023 bytes if message is too long
     */
    template <typename... Args>
    static ReflectException format(const char* format, Args&&... args) {
        char buffer[1024];
        snprintf(buffer, sizeof(buffer), format, std::forward<Args>(args)...);
        return ReflectException(buffer);
    }

    /**
     * @brief Get error message (std::exception override)
     * @return Null-terminated C string of the error message
     */
    const char* what() const noexcept override { return message_.c_str(); }

   private:
    std::string message_;
};
}  // namespace reflect

#endif