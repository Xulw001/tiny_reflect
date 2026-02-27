/**
 * @file type.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief Internal type metadata & access utilities (reflection system)
 * @version 0.2
 * @date 2026-02-22
 *
 * @copyright Copyright (c) 2026
 */
#ifndef TYPE_H
#define TYPE_H

#include <cstring>

#include "constructor.h"
#include "field/object.h"
#include "field/type.h"
#include "repeated_field/object.h"
#include "repeated_field/type.h"
#include "type_id_info.h"

namespace reflect {
/**
 * @struct TypeInternal
 * @brief Internal type metadata
 * @details Holds type name, constructor, fields, and type ID for registration
 */
struct TypeInternal : public ObjectInternal {
   public:
    /**
     * @brief Construct a new TypeInternal object
     * @param name Type name
     * @param constructor Constructor for the type
     * @param type_id Unique type ID for registration
     * @note Registers type with TypeIdInfo upon construction
     */
    explicit TypeInternal(const char* name, const Constructor& constructor,
                          const std::size_t type_id)
        : name_(name), constructor_(constructor), type_id_(type_id) {
        TypeIdInfo::GetInstance().regist_type(type_id_, name_);
    };

    /**
     * @brief Add field to type
     * @tparam C Class type containing the field
     * @tparam T Field value type
     * @param name Field name
     * @param ptr Pointer to class member (T C::*)
     * @return TypeInternal& for chaining
     */
    template <typename C, typename T>
    TypeInternal& field(const char* name, T C::* ptr) {
        auto& it = field(name);
        if (it == default_) {
            map_.emplace_back(new FieldBase<C, T>(name, ptr));
        }
        return *this;
    }

    /**
     * @brief Get type name
     * @return const char* Type name
     */
    const char* name() const noexcept { return name_; }

    /**
     * @brief Create instance of the type
     * @return New instance (via constructor_)
     */
    Pointer create() const { return constructor_(); }

    /**
     * @brief Get number of fields in type
     * @return Field count (std::size_t)
     */
    std::size_t field_count() const noexcept { return map_.size(); }

    /**
     * @brief Get field by index
     * @param i Field index (0-based)
     * @return const Field& Field at index i
     * @throws std::out_of_range If index is out of bounds
     */
    const Field& field(std::size_t i) const {
        if (i >= map_.size()) {
            throw std::out_of_range("field index out of range");
        }
        return map_[i];
    }

    /**
     * @brief Get field by name
     * @param name Field name to search for
     * @return const Field& Matching field (or default_ if not found)
     */
    const Field& field(const char* name) const noexcept {
        for (auto it = map_.begin(); it != map_.end(); it++) {
            if (std::strcmp((*it)->name(), name) == 0) {
                return *it;
            }
        }
        return default_;
    }

    TypeInternal(const TypeInternal&) = delete;
    TypeInternal& operator=(const TypeInternal&) = delete;

   private:
    const Field default_;      ///< Default empty field
    const char* name_;         ///< Type name
    Constructor constructor_;  ///< Type constructor
    std::vector<Field> map_;   ///< Type fields (vector of Field)
    std::size_t type_id_;      ///< Unique type ID
};

/**
 * @struct TypeBase
 * @brief Template base class for TypeInternal(object types only)
 * @tparam T Object type (enabled if is_object<T>::value is true)
 */
template <typename T,
          typename std::enable_if<is_object<T>::value, int>::type = 0>
struct TypeBase : public TypeInternal {
   public:
    /**
     * @brief Construct a new TypeBase object
     * @param name Type name
     * @param constructor Constructor for the type
     * @note Type ID = get_type_id<T>()
     */
    explicit TypeBase(const char* name, const Constructor& constructor)
        : TypeInternal(name, constructor, get_type_id<T>()) {};
};

/**
 * @typedef Type
 * @brief Unique pointer to TypeInternal
 */
using Type = std::unique_ptr<TypeInternal>;

}  // namespace reflect

#endif