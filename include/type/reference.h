/**
 * @file reference.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief Type-safe reference wrapper for reflection system
 * @version 0.1
 * @date 2026-02-21
 *
 * @copyright Copyright (c) 2026
 */
#ifndef TYPE_REFERENCE_H
#define TYPE_REFERENCE_H

#include <type_traits>

#include "type/exception.h"
#include "type_id.h"

namespace reflect {
/**
 * @class Reference
 * @brief Type-safe reference wrapper for reflection system
 * @details Reference wrapper with type ID and void pointer, enabling type-safe
 *          casting via the reflection system's type ID mechanism.
 * @note Non-owning (does not manage object lifetime); friend of Value class
 */
class Reference {
    friend class Value;

   public:
    /**
     * @brief Construct from typed value (cv-qualifiers handled)
     * @tparam T Type of the input value (may be cv-qualified)
     * @tparam U Unqualified type of T (std::remove_cv<T>::type, default)
     * @param value Reference to the object to wrap
     * @note const_cast removes const for uniform void* storage
     */
    template <typename T, typename U = typename std::remove_cv<T>::type>
    explicit Reference(T& value) noexcept {
        type_id_ = get_type_id<T>();
        pointer_ = const_cast<U*>(std::addressof(value));
    }

    /**
     * @brief Gets the type ID of the wrapped object
     * @return Unique type ID (std::size_t)
     */
    std::size_t type_id() const noexcept { return type_id_; }

    /**
     * @brief Type-safe cast to the target type T
     * @tparam T Target type to cast to (may be cv-qualified)
     * @return Reference to wrapped object (cast to T&)
     * @throws ReflectException On type mismatch
     */
    template <typename T>
    T& cast() const {
        using U = typename std::remove_cv<T>::type;
        if (type_id_ != get_type_id<U>()) {
            throw ReflectException("type mismatch!");
        }
        return *static_cast<T*>(pointer_);
    }

   private:
    /**
     * @brief Default constructor (private, for Value use only)
     */
    Reference() = default;

   private:
    std::size_t type_id_;  ///< The type ID of the wrapped object
    void* pointer_;        ///< The pointer to the underlying object
};

}  // namespace reflect

#endif