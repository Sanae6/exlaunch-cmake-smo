#include "lib.hpp"
#include "types.h"

namespace nn {
    namespace ro {
        Result LookupSymbol(uintptr_t* pOutAddress, const char* name);
    }
} // namespace nn

namespace exl {
    namespace ro {
        uintptr_t GetSymbol(const char* name) {
            uintptr_t address = 0;
            Result rc = nn::ro::LookupSymbol(&address, name);
            if (R_FAILED(rc))
                EXL_ABORT(0x421);
            return address;
        }
    } // namespace ro
} // namespace exl
