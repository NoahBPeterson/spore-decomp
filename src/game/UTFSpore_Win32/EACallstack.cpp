// src/game/UTFSpore_Win32/EACallstack.cpp -- migrated from slice(s) s0091a680 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EACallstack.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/IO/FileStream.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl memset(void* pDst, int nValue, size_t nLen);
extern "C" __declspec(dllimport) void* __stdcall GetCurrentProcess();
extern "C" __declspec(dllimport) void* __stdcall GetCurrentThread();
extern void* gReadMemoryRoutine;            // 0x01667b54
extern void* gFunctionTableRoutine;         // 0x01667b58
#include <intrin.h>

// ---- items of slice s0091a680 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl memset(void* pDst, int nValue, size_t nLen);
extern "C" __declspec(dllimport) void* __stdcall GetCurrentProcess();
extern "C" __declspec(dllimport) void* __stdcall GetCurrentThread();
void  __fastcall FUN_0091b350(void* pDbgHelp);                        // 0x0091b350
struct cContext {
    uint32_t mContextFlags;                 // +0x000
    uint8_t  mRest[0x2cc - 4];              // +0x004
};
struct cAddress64 {
    void*    mpOffset;                      // +0x00
    uint32_t mPad04;                        // +0x04
    uint32_t mnMode;                        // +0x08
    uint32_t mPad0C;                        // +0x0c
};
struct cStackFrame {
    cAddress64 mAddrPC;                     // +0x00
    uint32_t   mPad10[2];                   // +0x10
    cAddress64 mAddrStack;                  // +0x18
    cAddress64 mAddrFrame;                  // +0x24
    uint8_t    mRest[0xa4 - 0x30];          // +0x30
};
typedef int (__stdcall* StackWalk64Fn)(uint32_t nMachine, void* hProcess, void* hThread,
                                       cStackFrame* pFrame, cContext* pContext, void* pReadMemory,
                                       void* pFunctionTable, void* pGetModuleBase,
                                       void* pTranslate);
extern StackWalk64Fn gStackWalk64;          // 0x01667b50
extern void* gReadMemoryRoutine;            // 0x01667b54
extern void* gFunctionTableRoutine;         // 0x01667b58
extern uint32_t gDbgHelpInitState;          // 0x01667b40
// ---- items of slice s0091a680 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern StackWalk64Fn gStackWalk64;          // 0x01667b50
extern uint32_t gDbgHelpInitState;          // 0x01667b40

// @ 0x0091b3d0
uint32_t GetCallstack(void** pOut, uint32_t nMaxFrames, const void** pContext)
{
    uint32_t nFrames = 0;
    if (gDbgHelpInitState == 0) FUN_0091b350(&gDbgHelpInitState);
    if (gStackWalk64 == 0) {
        pOut[0] = 0;
        return 0;
    }

    cContext context;
    memset(&context, 0, 0x2cc);
    context.mContextFlags = 0x10001;

    void* pPC;
    void* pStack;
    void* pFramePtr;
    if (pContext) {
        pPC = (void*)pContext[0];
        pStack = (void*)pContext[1];
        pFramePtr = (void*)pContext[2];
    } else {
        pPC = _ReturnAddress();
        pStack = _AddressOfReturnAddress();
        pFramePtr = (void*)((char*)_AddressOfReturnAddress() + sizeof(void*));
    }

    cStackFrame frame;
    memset(&frame, 0, 0xa4);
    frame.mAddrPC.mpOffset = pPC;
    frame.mAddrPC.mnMode = 3;
    frame.mAddrStack.mpOffset = pStack;
    frame.mAddrStack.mnMode = 3;
    frame.mAddrFrame.mpOffset = pFramePtr;
    frame.mAddrFrame.mnMode = 3;

    void* hProcess = GetCurrentProcess();
    void* hThread = GetCurrentThread();
    int nSkip = 0;
    while (nFrames < nMaxFrames - 1) {
        if (!gStackWalk64(0x14c, hProcess, hThread, &frame, &context, 0, gReadMemoryRoutine,
                          gFunctionTableRoutine, 0))
            break;
        if (frame.mAddrStack.mpOffset == 0) break;
        if (pContext != 0 || nSkip > 0) pOut[nFrames++] = frame.mAddrPC.mpOffset;
        ++nSkip;
    }
    pOut[nFrames] = 0;
    return nFrames;
}
