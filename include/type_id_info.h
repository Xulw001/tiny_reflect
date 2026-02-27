/**
 * @file type_id_info.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief Singleton type ID-name mapping utilities for reflection system
 * @version 0.2
 * @date 2026-02-21
 *
 * @copyright Copyright (c) 2026
 */
#ifndef TYPE_ID_INFO_H
#define TYPE_ID_INFO_H

#include <vector>

#include "type/exception.h"
#include "type_id.h"

namespace reflect {
/**
 * @struct TypeIdInfo
 * @brief Singleton for type ID-name mapping (reflection)
 * @details Manages registration and lookup of type names for unique type IDs.
 * @note Lazy singleton; registrations are non-overwriting
 */
struct TypeIdInfo {
   private:
    /**
     * @struct TypeInfo
     * @brief Internal ID-name pair storage
     */
    struct TypeInfo {
        size_t type_id;
        const char* name;
    };

   public:
    /**
     * @brief Gets singleton instance (lazy, thread-safe)
     * @return Reference to the single TypeIdInfo instance
     */
    static TypeIdInfo& GetInstance() {
        static TypeIdInfo instance;
        return instance;
    }

    /**
     * @brief Registers ID-name mapping (non-overwriting)
     * @param id Type ID (must be in CustomConfig::CPPTYPE range)
     * @param name Type name (non-null)
     * @note Does not overwrite existing mappings
     */
    void regist_type(size_t id, const char* name) {
        if (get_type_name(id) != nullptr) return;
        type_info_.emplace_back(TypeInfo{id, name});
    }

    /**
     * @brief Looks up type name by ID
     * @param id Type ID to look up
     * @return Type name (nullptr if invalid/unregistered)
     * @note Invalid if < CPPTYPE or out of registered range
     */
    const char* get_type_name(size_t id) const {
        if (id < CustomConfig::CPPTYPE ||
            id - CustomConfig::CPPTYPE + 1 > type_info_.size()) {
            return nullptr;
        }
        return type_info_[id - CustomConfig::CPPTYPE].name;
    };

   private:
    std::vector<TypeInfo>
        type_info_;  ///< Stores registered type ID-name mappings
};
}  // namespace reflect

#endif