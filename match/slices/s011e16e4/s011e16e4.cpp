// Slice s011e16e4: tail of the import-thunk table followed by a small
// hand-written delay-load style stub (pushad/popad, unbalanced stack cleanup
// via "pop ebx"), so the stub is reconstructed with naked inline asm.
//
// 0x011e16e4..0x011e171a are linker-generated import thunks
// (jmp dword ptr [__imp_X]) and are not compiler output; see nonmatching.txt.

extern "C" int g_stubState;     // 0x015cfe88
extern "C" int g_stubResult;    // 0x015cfe8c
extern "C" void *g_stubTable[]; // 0x015cfe90: { slot, name } pairs, name==0 terminated
extern "C" char g_stubDllName[];   // 0x01720000
extern "C" char g_stubProcName[];  // 0x0172000a
extern "C" char g_stubInitName[];  // 0x0150e828
extern "C" void *g_impLoadLibraryA;    // IAT slot 0x013cc0e8 (kernel32!LoadLibraryA)
extern "C" void *g_impGetProcAddress;  // IAT slot 0x013cc0bc (kernel32!GetProcAddress)

// @ 0x011e1720
extern "C" int GetStubResult_011e1720()
{
    return g_stubResult;
}

// @ 0x011e1726
extern "C" __declspec(naked) int StubInit_011e1726()
{
    __asm {
        pushad
        push    offset g_stubDllName
        call    dword ptr [g_impLoadLibraryA]
        test    eax, eax
        mov     esi, eax
        mov     dword ptr [g_stubState], 0xfffffffe
        je      done
        push    offset g_stubProcName
        push    esi
        call    dword ptr [g_impGetProcAddress]
        test    eax, eax
        je      fail
        mov     ebp, eax
        push    offset g_stubInitName
        call    ebp
        pop     ebx
        test    eax, eax
        je      fail
        call    eax
        test    eax, eax
        js      fail
        mov     dword ptr [g_stubState], 0
        mov     dword ptr [g_stubResult], 0xfffffffd
        mov     esi, offset g_stubTable
    next:
        mov     eax, dword ptr [esi + 4]
        test    eax, eax
        je      done
        push    eax
        call    ebp
        pop     ebx
        test    eax, eax
        je      skip
        mov     dword ptr [esi], eax
    skip:
        add     esi, 8
        jmp     next
    fail:
        mov     dword ptr [g_stubState], 0xffffffff
    done:
        popad
        mov     eax, dword ptr [g_stubState]
        ret
    }
}
