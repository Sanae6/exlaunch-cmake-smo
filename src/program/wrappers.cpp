#include "types.h"
#ifdef LOGGER_IP
#include "util/logger.hpp"
#endif
#include "util/symbol.hpp"
#include "lib.hpp"
#include "clr/rtrsetup.hpp"

extern "C" uintptr_t ExlaunchGetSymbol(const char* text) {
    return exl::ro::GetSymbol(text);
}

extern "C" void ExlaunchLog(const char* text) {
#ifdef LOGGER_IP
    exl::logger::log("%s\n", text);
#endif
}

extern "C" void ExlaunchAbort(uint32_t value) {
    exl::diag::AbortImpl(exl::diag::AbortCtx{
            static_cast<Result>(value)
    });
}

extern "C" uintptr_t ExlaunchHook(uintptr_t hook, uintptr_t callback, bool trampoline) {
    return exl::util::Hook::HookFuncCommon(hook, callback, trampoline);
}

static bool socketInitialized = false;
MAKE_HOOK_T(int, _socketInitialize, (void* pool, u64 poolSize, u64 allocPoolSize, s32 concurLimit), {
    if (socketInitialized) return 0;
    socketInitialized = true;
    int res = impl(pool, poolSize, allocPoolSize, concurLimit);
    exl::logger::init();
    return res;
})

extern void exl_setup() {
    envSetOwnProcessHandle(exl::util::proc_handle::Get());
    exl::util::Hook::Initialize();

#ifdef LOGGER_IP
    _socketInitializeImpl =
            (int(*)(void*, u64, u64, s32))
            exl::util::Hook::HookFunc((int(*)(void*, u64, u64, s32))exl::ro::GetSymbol("_ZN2nn6socket10InitializeEPvmmi"), &_socketInitializeHook, true);
#endif
}