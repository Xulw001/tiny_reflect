/**
 * @file type_id_info.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief This file defines the TypeIdInfo class, which provides information about type IDs.
 * @version 0.1
 * @date 2026-01-17
 *
 * @copyright Copyright (c) 2026
 */
#ifndef TYPE_ID_INFO_H
#define TYPE_ID_INFO_H

#include "type_id.h"

namespace reflect {
/**
 * @brief Provides information about a type ID.
 *
 * This class provides a way to associate a type ID with its corresponding type name.
 * It is used internally by the reflection system to manage type information.
 *
 * @see TypeId
 */
struct TypeIdInfo {
   private:
    struct TypeInfo {
        size_t type_id;
        const char* name;
    };

   public:
    static TypeIdInfo& GetInstance() {
        static TypeIdInfo instance;
        return instance;
    }

    /**
     * @brief Registers a type ID and its corresponding type name.
     *
     * @param id The type ID to be registered.
     * @param name The type name associated with the type ID.
     */
    void regist_type(size_t id, const char* name) { type_info_.emplace_back(TypeInfo{id, name}); }

    /**
     * @brief Retrieves the type name associated with a given type ID.
     *
     * @param id The type ID for which to retrieve the type name.
     * @return const char* The type name associated with the given type ID,
     *         or nullptr if no type is associated with the ID.
     */
    const char* get_type_name(size_t id) const {
        if (id < MAX_CPPTYPE || id - MAX_CPPTYPE + 1 > type_info_.size()) {
            return nullptr;
        }
        return type_info_[id - MAX_CPPTYPE].name;
    };

   private:
    std::vector<TypeInfo> type_info_;  ///< A vector of TypeInfo objects that stores type information.
};
}  // namespace reflect

#endif