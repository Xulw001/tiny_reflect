/**
 * @file value.h
 * @author xulw (nevermore.xulw@hotmail.com)
 * @brief Value type wrapper for reflection system
 * @version 0.1
 * @date 2026-02-21
 *
 * @copyright Copyright (c) 2026
 */
#ifndef TYPE_VALUE_H
#define TYPE_VALUE_H

#include "reference.h"

namespace reflect {
/**
 * @struct in_place_type_t
 * @brief Tag type for in-place construction (Value class)
 * @details Used to distinguish between heap and stack-allocated construction
 *          of values in the Value class
 * @tparam T Type for in-place construction
 * @note Pure tag type (no members) for overload resolution
 */
template <typename T>
struct in_place_type_t {};

/**
 * @struct Value
 * @brief Type-erased value wrapper for reflection system
 * @details Stores and manages values of any type, supporting both stack-
 *          and heap-allocated storage based on type properties.
 */
class Value {
    /**
     * @union Storage
     * @brief Union for storage of values of any type
     * @details Supports both stack-allocated and heap-allocated storage,
     *          depending on type properties.
     * @note Buffer size matches sizeof(void*) (same as ptr_) to optimize stack
     *       usage.
     */
    union Storage {
        constexpr Storage() : ptr_{nullptr} {}

        Storage(const Storage&) = delete;
        Storage& operator=(const Storage&) = delete;

        void* ptr_;  ///< Heap storage pointer
        std::aligned_storage<sizeof(ptr_), alignof(void*)>
            buffer_;  ///< Stack-allocated inline buffer
    };

    /**
     * @struct ManagerCond
     * @brief Condition for stack/heap storage manager selection
     * @details Compile-time trait to choose StackManager/HeapManager for type T
     * @tparam T Type for manager selection
     * @note Evaluates to true if type T is nothrow constructible, fits within
     *       stack storage, and has alignment compatible with stack storage.
     */
    template <typename T>
    using ManagerCond =
        std::integral_constant<bool, std::is_nothrow_constructible<T>::value &&
                                         sizeof(T) <= sizeof(Storage) &&
                                         alignof(T) <= alignof(Storage)>;

    template <typename T>
    struct StackManager;

    template <typename T>
    struct HeapManager;

    template <typename T>
    using Manager = selector_t<ManagerCond<T>, StackManager<T>, HeapManager<T>>;

   public:
    constexpr Value() noexcept : manager_(nullptr) {}
    Value(const Value& other) = delete;
    Value& operator=(const Value& other) = delete;

    Value(Value&& other) {
        if (other.manager_ == nullptr) {
            manager_ = nullptr;
        } else {
            Args args;
            args.value = this;
            other.manager_(Oper::Swap, &other, &args);
        }
    }

    Value& operator=(Value&& other) {
        if (!other.HasValue()) {
            Reset();
        } else if (this != &other) {
            Reset();
            Args args;
            args.value = this;
            other.manager_(Oper::Swap, &other, &args);
        }
        return *this;
    }

    /**
     * @brief In-place constructs Value of type T
     * @tparam T Type of the value to store
     * @param in_place_type_t<T> Tag for in-place construction (unused)
     * @param args Arguments to forward to the constructor of T
     * @note uses Manager<T> for creation/management
     */
    template <typename T, typename... Args>
    explicit Value(in_place_type_t<T>, Args&&... args)
        : manager_(&Manager<T>::manage) {
        Manager<T>::create(storage_, std::forward<Args>(args)...);
    }

    /**
     * @brief Destructor for Value (cleans up stored value)
     * @note Uses Reset() for conditional destruction.
     */
    ~Value() { Reset(); }

    /**
     * @brief Checks if the Value has a stored value
     * @return True if the Value has a stored value, false otherwise
     */
    bool HasValue() const noexcept { return manager_ != nullptr; }

    /**
     * @brief Resets Value (destroys stored value, marks as empty)
     * @note only destroys value if has value
     */
    void Reset() noexcept {
        if (HasValue()) {
            manager_(Oper::Destroy, this, nullptr);
            manager_ = nullptr;
        }
    }

    /**
     * @brief Gets Reference to stored value
     * @return Type-safe reference to stored value
     * @throws ReflectException If Value is empty
     */
    Reference Access() {
        if (manager_) {
            Args args;
            manager_(Oper::Access, this, &args);
            return args.ref;
        }
        throw ReflectException("Value has no stored value!");
    }

    /**
     * @brief Gets type ID of stored value
     * @return Unique type ID of stored value (std::size_t)
     * @throws ReflectException If Value is empty
     */
    std::size_t TypeId() const {
        if (manager_) {
            Args args;
            manager_(Oper::TypeId, this, &args);
            return args.type_id;
        }
        throw ReflectException("Value has no stored value!");
    }

   private:
    enum class Oper { Access, TypeId, Swap, Destroy };

    /**
     * @struct Args
     * @brief Arguments union for Value operations
     * @details Holds args for Value operations (Access/TypeId/Swap/Destroy)
     */
    union Args {
        Reference ref;
        std::size_t type_id;
        Value* value;
    };

    /**
     * @brief Manager for stack-allocated values
     * @details Handles construction, destruction, and access to stack-
     *          allocated values of type T.
     */
    template <typename T>
    struct StackManager {
        /**
         * @brief Constructs a stack-allocated value of type T
         * @param storage Storage buffer for the value
         * @param args Arguments to forward to the constructor of T
         */
        template <typename... Args>
        static void create(Storage& storage, Args&&... args) {
            new (&storage.buffer_) T(std::forward<Args>(args)...);
        }

        /**
         * @brief Manages stack-allocated values of type T
         * @param oper Operation to perform (Access, TypeId, Swap, Destroy)
         * @param value Pointer to the Value instance
         * @param args Arguments for the operation
         */
        static void manage(Oper oper, const Value* value, Args* args) {
            auto ptr = reinterpret_cast<const T*>(&value->storage_.buffer_);
            switch (oper) {
            case Oper::Access:
                args->ref.pointer_ = const_cast<T*>(ptr);
                args->ref.type_id_ = get_type_id<T>();
                break;
            case Oper::TypeId:
                args->type_id = get_type_id<T>();
                break;
            case Oper::Swap:
                ::new (&args->value->storage_.buffer_)
                    T(std::move(*const_cast<T*>(ptr)));
                ptr->~T();
                args->value->manager_ = value->manager_;
                const_cast<Value*>(value)->manager_ = nullptr;
                break;
            case Oper::Destroy:
                ptr->~T();
                break;
            }
        }
    };

    /**
     * @brief Manager for heap-allocated values
     * @details Handles construction, destruction, and access to heap-
     *          allocated values of type T.
     */
    template <typename T>
    struct HeapManager {
        /**
         * @brief Constructs a heap-allocated value of type T
         * @param storage Storage buffer for the value
         * @param args Arguments to forward to the constructor of T
         */
        template <typename... Args>
        static void create(Storage& storage, Args&&... args) {
            storage.ptr_ = new T(std::forward<Args>(args)...);
        }
        /**
         * @brief Manages heap-allocated values of type T
         * @param oper Operation to perform (Access, TypeId, Swap, Destroy)
         * @param value Pointer to the Value instance
         * @param args Arguments for the operation
         */
        static void manage(Oper oper, const Value* value, Args* args) {
            auto ptr = reinterpret_cast<const T*>(value->storage_.ptr_);
            switch (oper) {
            case Oper::Access:
                args->ref.pointer_ = const_cast<T*>(ptr);
                args->ref.type_id_ = get_type_id<T>();
                break;
            case Oper::TypeId:
                args->type_id = get_type_id<T>();
                break;
            case Oper::Swap:
                args->value->storage_.ptr_ = value->storage_.ptr_;
                args->value->manager_ = value->manager_;
                const_cast<Value*>(value)->manager_ = nullptr;
                break;
            case Oper::Destroy:
                delete ptr;
                break;
            }
        }
    };

   private:
    void (*manager_)(Oper, const Value*, Args*);  /// < The manager function
    Storage storage_;  ///< The storage for the managed object
};
}  // namespace reflect

#endif