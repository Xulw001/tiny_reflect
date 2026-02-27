/**
 * @file type_info.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief Singleton type registry (reflection system)
 * @version 0.2
 * @date 2026-02-23
 *
 * @copyright Copyright (c) 2026
 */
#ifndef TYPE_INFO_H
#define TYPE_INFO_H

#include <cstring>
#include <unordered_map>

#include "type.h"

namespace reflect {
/**
 * @class TypeInfo
 * @brief Singleton type registry (reflection system)
 * @details Provides methods to register and load types by name
 */
class TypeInfo {
   public:
    /**
     * @brief Get singleton instance (thread-safe)
     * @return Reference to the singleton instance
     */
    static TypeInfo& GetInstance() {
        static TypeInfo instance;
        return instance;
    }

    /**
     * @brief Register type T with name
     * @tparam T Type to register (object type only)
     * @param name Type name (unique)
     * @return Type& Registered type reference
     */
    template <typename T>
    Type& regist(const char* name) {
        return map_.emplace(name, new TypeBase<T>(name, &T::constructor))
            .first->second;
    }

    /**
     * @brief Load type by name
     * @param name Type name to look up
     * @return const Type& Matching type (or default_ if not found)
     */
    const Type& load(const char* name) const {
        auto it = map_.find(name);
        if (it != map_.end()) {
            return it->second;
        }
        return default_;
    }

   private:
    /**
     * @brief Hash functor for const char* keys
     */
    struct Hash {
        std::size_t operator()(const char* s) const {
            return std::hash<std::string>()(s);
        }
    };

    /**
     * @brief Equality functor for const char* keys
     */
    struct Equal {
        bool operator()(const char* a, const char* b) const {
            return std::strcmp(a, b) == 0;
        }
    };

   private:
    const Type default_;  ///< Default empty Type (returned if not found)
    std::unordered_map<const char*, Type, Hash, Equal>
        map_;  ///< Type registry (name -> Type)
};

}  // namespace reflect

#endif