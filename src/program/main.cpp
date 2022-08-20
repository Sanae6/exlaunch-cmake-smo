#include "al/util.hpp"
#include "heap/seadHeapMgr.h"
#include "hook/trampoline_hook.hpp"
#include "lib.hpp"
#include "logging/logger.hpp"
#include "players/ButterflyPlayerFactory.hpp"
#include "debugMenu.hpp"

using CodePatcher = exl::patch::CodePatcher;
using namespace exl::armv8;

#define STRINGIFY(x) x
#define TOSTRING(x) STRINGIFY(x)

HOOK_DEFINE_TRAMPOLINE(LoggerSetup) {
    static void Callback() {
        Orig();
        Logger* logger = Logger::createInstance(al::getSequenceHeap());
        EXL_ASSERT(logger != nullptr);
        #ifdef LOGGER_IP
        logger->init(TOSTRING(LOGGER_IP), 3080);
        Logger::log("Hello world!\n");

        EXL_ASSERT(logger->getLogState() != SOCKET_LOG_UNAVAILABLE);
        EXL_ASSERT(logger->getLogState() != SOCKET_LOG_DISCONNECTED);
        EXL_ASSERT(logger->getLogState() != SOCKET_LOG_UNINITIALIZED);
//        #else
//        #error "Logger IP not set!"
        #endif
    }
};

HOOK_DEFINE_REPLACE(PlayerFactorySwap) {
    static void Callback(void* factoryThis) {
        new (factoryThis) ButterflyPlayerFactory();
    }
};

namespace al {
    void createSequenceHeap();
}

extern "C" void _ZNK16HakoniwaSequence8drawMainEv(HakoniwaSequence* hakoniwaThis);
extern "C" void _ZN2al12LayoutSystem4initEv(void* layoutSystemThis);
extern "C" void _ZN13PlayerFactoryC2Ev(void* factoryThis);

extern "C" void exl_main(void* x0, void* x1) {
    /* Setup hooking enviroment. */
    envSetOwnProcessHandle(exl::util::proc_handle::Get());
    exl::hook::Initialize();

    LoggerSetup::InstallAtFuncPtr(al::createSequenceHeap);
//    PlayerFactorySwap::InstallAtFuncPtr(_ZN13PlayerFactoryC2Ev);
//    SetupDebugMenu::InstallAtFuncPtr(_ZN2al12LayoutSystem4initEv);
//    DrawDebugMenu::InstallAtFuncPtr(_ZNK16HakoniwaSequence8drawMainEv);
//    50F274: // HakoniwaSequence::drawMain
//             MOV X0, X19 // HakoniwaSequence
//                 MOV X1, SP // viewport
//                 MOV X2, X20 // drawContext
//                 BL hHakoniwaSequenceDrawMain
//    CodePatcher patcher(0x50F274);
//    patcher.WriteInst(inst::MovRegister(reg::X0, reg::X19));
//    patcher.WriteInst(inst::MovRegister(reg::X1, reg::SP));
//    patcher.WriteInst(inst::MovRegister(reg::X2, reg::X20));
//    patcher.BranchLinkInst((void*)drawDebugMenu);
}

extern "C" NORETURN void exl_exception_entry() {
    /* TODO: exception handling */
    EXL_ABORT(0x420);
}