#define GET_SYMBOL(name) exl::ro::GetSymbol(#name)

namespace exl {
    namespace ro {
        uintptr_t GetSymbol(const char* name);
    }
} // namespace exl