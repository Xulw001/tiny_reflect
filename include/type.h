/**
 * @file type.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief This file defines the TypeInternal structure, which is responsible for
 *        managing type information, including fields and constructors.
 * @version 0.1
 * @date 2026-01-15
 *
 * @copyright Copyright (c) 2026
 */
#ifndef TYPE_H
#define TYPE_H

#include "constructor.h"
#include "field.h"
#include "field/bool.h"
#include "field/decimal.h"
#include "field/integer.h"
#include "field/text.h"

namespace reflect {

struct TypeInternal : public ObjectInternal {
   public:
    /**
     * @brief Constructs a TypeInternal instance with a given name and constructor.
     *
     * @param name The name of the type.
     * @param constructor The constructor for creating instances of the type.
     */
    explicit TypeInternal(const char* name, const Constructor& constructor)
        : name_(name), constructor_(constructor) {
          };

    /**
     * @brief Registers a field with the type.
     *
     * @tparam C The class type that contains the field.
     * @tparam T The type of the field.
     * @param name The name of the field.
     * @param ptr Pointer to the field in the class.
     * @return TypeInternal& Reference to the current TypeInternal instance.
     */
    template <typename C, typename T>
    TypeInternal& field(const char* name, T C::* ptr) {
        map_.emplace_back(new FieldBase<C, T>(name, ptr));
        return *this;
    }

    /**
     * @brief Gets the name of the type.
     *
     * @return const char* The name of the type.
     */
    const char* name() const { return name_; }

    /**
     * @brief Creates an instance of the type using the constructor.
     *
     * @return Pointer A pointer to the newly created instance.
     */
    Pointer create() const { return constructor_(); }

    /**
     * @brief Gets the count of fields registered with the type.
     *
     * @return size_t The number of fields.
     */
    size_t field_count() const { return map_.size(); }

    /**
     * @brief Gets a field by its index.
     *
     * @param i The index of the field.
     * @return const Field& Reference to the field.
     */
    const Field& field(size_t i) const { return map_[i]; }

    /**
     * @brief Gets a field by its name.
     *
     * @param name The name of the field.
     * @return const Field& Reference to the field.
     */
    const Field& field(const char* name) const {
        for (auto it = map_.begin(); it != map_.end(); it++) {
            if (std::strcmp((*it)->name(), name) == 0) {
                return *it;
            }
        }
        return *map_.end();
    }

    TypeInternal(const TypeInternal&) = delete;
    TypeInternal& operator=(const TypeInternal&) = delete;
    TypeInternal(TypeInternal&&) = default;
    TypeInternal& operator=(TypeInternal&&) = default;

   private:
    const char* name_;         ///< The name of the type.
    Constructor constructor_;  ///< The constructor for creating instances of the type.
    std::vector<Field> map_;   ///< A vector storing the fields associated with the type.
};

using Type = std::unique_ptr<TypeInternal>;

}  // namespace reflect

#endif