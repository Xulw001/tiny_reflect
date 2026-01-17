/**
 * @file type_info.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief This file defines the TypeInfo class, which provides
 *        management of type information for the reflection system.
 * @version 0.1
 * @date 2026-01-16
 *
 * @copyright Copyright (c) 2026
 */
#ifndef TYPE_INFO_H
#define TYPE_INFO_H

#include <unordered_map>

#include "type.h"
namespace reflect {

class TypeInfo {
   public:
    static TypeInfo& GetInstance() {
        static TypeInfo instance;
        return instance;
    }

    /**
     * @brief Registers a type with a given name.
     *
     * @tparam T The type to register.
     * @param name The name of the type.
     * @return Type& A reference to the registered type.
     */
    template <typename T>
    Type& regist(const char* name) {
        return map_.emplace(name, new TypeBase<T>(name, &T::constructor)).first->second;
    }

    /**
     * @brief Loads a type by its name.
     *
     * @param name The name of the type.
     * @return const Type& A reference to the loaded type.
     */
    const Type& load(const char* name) const {
        auto it = map_.find(name);
        if (it != map_.end()) {
            return it->second;
        }
        throw "class not found!";
    }

   private:
    struct Hash {
        std::size_t operator()(const char* s) const {
            return std::hash<std::string>()(s);
        }
    };

    struct Equal {
        bool operator()(const char* a, const char* b) const {
            return std::strcmp(a, b) == 0;
        }
    };

   private:
    std::unordered_map<const char*, Type, Hash, Equal> map_;  ///< A map of type names to their corresponding Type objects.
};

}  // namespace reflect

#endif