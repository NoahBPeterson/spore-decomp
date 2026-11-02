// src/game/UTFSpore_Win32/EADasm.cpp -- migrated from slice(s) s0091b5d0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EADasm.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Dasm/DisassemblerX86.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) void* __stdcall LoadLibraryA(const char*);
extern "C" __declspec(dllimport) void* __stdcall GetProcAddress(void*, const char*);
extern "C" __declspec(dllimport) int   __stdcall FreeLibrary(void*);
extern "C" __declspec(dllimport) int   __cdecl sprintf(char*, const char*, ...);
extern "C" char g_vtbl_dasmx86[];      // 0x0143ce14
extern "C" char g_vtbl_dasmbase[];     // 0x014a21fc
extern "C" char g_s_kernel32[];        // 0x01409dcc
extern "C" char g_s_getproductinfo[];  // 0x01409dbc
extern "C" char g_s_dasmdll[];         // 0x0143ce04
extern "C" char g_s_dasminit[];        // 0x0143cdf4
extern "C" char g_s_cleanup[];         // 0x0143cde4
extern "C" char g_s_disasm[];          // 0x0143cdd4
extern "C" char g_s_formatinsn[];      // 0x0143cdc0
extern "C" char g_s_fmt08x[];          // 0x013fa098  "%08x"
extern "C" char g_s_invalid[];         // 0x0143ce3c  "(invalid) 0x%02x"
extern "C" char g_s_nodll[];           // 0x0143ce1c  "DLL not found, no disassembly."
extern "C" int  g_hDasmDll;            // 0x01667b74
extern "C" int  g_fnInit;              // 0x01667b64
extern "C" int  g_fnCleanup;           // 0x01667b68
extern "C" int  g_fnDisasm;            // 0x01667b6c
extern "C" int  g_fnFormatInsn;        // 0x01667b70

// ---- items of slice s0091b5d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
typedef unsigned int   u32;
extern "C" __declspec(dllimport) void* __stdcall LoadLibraryA(const char*);
extern "C" __declspec(dllimport) void* __stdcall GetProcAddress(void*, const char*);
extern "C" __declspec(dllimport) int   __stdcall FreeLibrary(void*);
extern "C" __declspec(dllimport) int   __cdecl sprintf(char*, const char*, ...);
void* OpDelete(void* p);                                    // 0x00f47380
void  MemCopy(void* d, const void* s, unsigned n);          // 0x011e073e
extern "C" char g_vtbl_dasmx86[];      // 0x0143ce14
extern "C" char g_vtbl_dasmbase[];     // 0x014a21fc
extern "C" char g_s_kernel32[];        // 0x01409dcc
extern "C" char g_s_getproductinfo[];  // 0x01409dbc
extern "C" char g_s_dasmdll[];         // 0x0143ce04
extern "C" char g_s_dasminit[];        // 0x0143cdf4
extern "C" char g_s_cleanup[];         // 0x0143cde4
extern "C" char g_s_disasm[];          // 0x0143cdd4
extern "C" char g_s_formatinsn[];      // 0x0143cdc0
extern "C" char g_s_fmt08x[];          // 0x013fa098  "%08x"
extern "C" char g_s_invalid[];         // 0x0143ce3c  "(invalid) 0x%02x"
extern "C" char g_s_nodll[];           // 0x0143ce1c  "DLL not found, no disassembly."
extern "C" int  g_hDasmDll;            // 0x01667b74
extern "C" int  g_fnInit;              // 0x01667b64
extern "C" int  g_fnCleanup;           // 0x01667b68
extern "C" int  g_fnDisasm;            // 0x01667b6c
extern "C" int  g_fnFormatInsn;        // 0x01667b70
extern "C" u8   g_osProbed;            // 0x01667b78
extern "C" u8   g_hasGetProductInfo;   // 0x01667b79
struct DisassemblerX86 {
    void* vftable;                       // 0x000
    void* Ctor2();                       // 0x0091b5d0
    void* Dasm(const u8* start, const u8* end, u32 u3, u32 u4); // 0x0091b6d0
    void  Dtor();                        // 0x0091b6b0
    int   Undecorate(char* out, const char* sym, u32 len, u32 flags); // 0x0091b840
    u8*   ScalarDtor(u8 flags);          // 0x0091b810
};
// ---- items of slice s0091b5d0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" u8   g_osProbed;            // 0x01667b78
extern "C" u8   g_hasGetProductInfo;   // 0x01667b79

// @ 0x0091b5d0
void* DisassemblerX86::Ctor2()
{
    u8* p = (u8*)this;
    int cached = g_hDasmDll;
    vftable = (void*)g_vtbl_dasmx86;
    if (cached != 0)
        return p;
    if (g_osProbed == 0) {
        void* h = LoadLibraryA(g_s_kernel32);
        if (h != 0) {
            if (GetProcAddress(h, g_s_getproductinfo) != 0)
                g_hasGetProductInfo = 1;
            FreeLibrary(h);
        }
        g_osProbed = 1;
    }
    if (g_hasGetProductInfo != 0)
        return p;
    g_hDasmDll = (int)LoadLibraryA(g_s_dasmdll);
    if (g_hDasmDll == 0)
        return p;
    g_fnInit = (int)GetProcAddress((void*)g_hDasmDll, g_s_dasminit);
    g_fnCleanup = (int)GetProcAddress((void*)g_hDasmDll, g_s_cleanup);
    g_fnDisasm = (int)GetProcAddress((void*)g_hDasmDll, g_s_disasm);
    g_fnFormatInsn = (int)GetProcAddress((void*)g_hDasmDll, g_s_formatinsn);
    return p;
}

// @ 0x0091b6b0
void DisassemblerX86::Dtor()
{
    int fn = g_fnCleanup;
    vftable = (void*)g_vtbl_dasmx86;
    if (fn != 0)
        ((void (__cdecl*)())fn)();
    vftable = (void*)g_vtbl_dasmbase;
}

// @ 0x0091b6d0
void* DisassemblerX86::Dasm(const u8* start, const u8* end, u32 u3, u32 u4)
{
    u8* p = (u8*)this;
    MemCopy(p, 0, 0x1f0);
    const u8* s = start;
    const u8* e = end;
    if (s >= e) {
        *(u32*)(p + 0x1d8) = 1;
        return (void*)e;
    }
    if ((u3 | u4) != 0) {
        *(u32*)(p + 0x1e0) = u3;
        *(u32*)(p + 0x1e4) = u4;
    } else {
        *(u32*)(p + 0x1e0) = (u32)s;
        *(u32*)(p + 0x1e4) = 0;
    }
    char* text = (char*)p;
    char* dst = text + 0x11;
    sprintf(text, g_s_fmt08x, (void*)*(u32*)(p + 0x1e0));
    if (g_fnInit != 0) {
        u32 n = ((u32 (__cdecl*)(const u8*, int, u32, char*))g_fnDisasm)(
                    s, (int)(e - s), *(u32*)(p + 0x1e0), text + 0x10);
        if (n != 0) {
            ((void (__cdecl*)(char*, char*, u32, u32))g_fnFormatInsn)(dst, text + 0x11, 0x20, 2);
            return (void*)(s + n);
        }
        sprintf(dst, g_s_invalid, *s);
        *(u32*)(p + 0x1d8) |= 1;
        *(u8*)(p + 0x31) = 0;
        return (void*)(s + 1);
    }
    sprintf(dst, g_s_nodll);
    *(u32*)(p + 0x1d8) |= 1;
    *(u8*)(p + 0x31) = 0;
    return (void*)e;
}

// @ 0x0091b810
u8* DisassemblerX86::ScalarDtor(u8 flags)
{
    int fn = g_fnCleanup;
    vftable = (void*)g_vtbl_dasmx86;
    if (fn != 0)
        ((void (__cdecl*)())fn)();
    vftable = (void*)g_vtbl_dasmbase;
    if ((flags & 1) != 0)
        OpDelete(this);
    return (u8*)this;
}
