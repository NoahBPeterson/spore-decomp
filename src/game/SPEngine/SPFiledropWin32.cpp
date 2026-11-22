// src/game/SPEngine/SPFiledropWin32.cpp -- migrated from slice(s) s006bb1c0 by tools/migrate/rewrite.py
// Object file: SPEngine/SPFiledropWin32.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cString.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) void __stdcall ReleaseStgMedium(void*);
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long*);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long*);
extern "C" __declspec(dllimport) int  __stdcall CoLockObjectExternal(void*, int, int);
extern "C" __declspec(dllimport) int  __stdcall OleUninitialize(void);
extern "C" int   __cdecl memcmp(const void*, const void*, size_t);
extern unsigned char g_guid_014dd504[16];  // 0x014dd504 IID
extern unsigned char g_guid_014dd514[16];  // 0x014dd514 IID
#include <intrin.h>
#pragma intrinsic(memcmp)

// ---- items of slice s006bb1c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void* HWND;
struct IUnknownStub { void** vtbl; };
extern "C" __declspec(dllimport) void __stdcall ReleaseStgMedium(void*);
extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long*);
extern "C" __declspec(dllimport) long __stdcall InterlockedDecrement(long*);
extern "C" __declspec(dllimport) int  __stdcall RevokeDragDrop(HWND);
extern "C" __declspec(dllimport) int  __stdcall CoLockObjectExternal(void*, int, int);
extern "C" __declspec(dllimport) int  __stdcall OleUninitialize(void);
void __cdecl FUN_00688dd0(void*);
struct HasStg { char pad[0x1c]; void* mpStg; void Release(); };
struct RefObj { void** vtbl; long mRefCount; };
extern "C" int   __cdecl memcmp(const void*, const void*, size_t);
void  __cdecl FUN_00688d50(void* p);                                                // 0x00688d50
void  __cdecl FUN_00688e50(void* p);                                                // 0x00688e50
struct Win32Point { long x, y; };
__declspec(dllimport) void* __stdcall SetFocus(void*);
__declspec(dllimport) int   __stdcall ScreenToClient(void*, Win32Point*);
__declspec(dllimport) long  __stdcall SendMessageA(void*, unsigned, unsigned, long);
extern unsigned char g_guid_014dd504[16];  // 0x014dd504 IID
extern unsigned char g_guid_014dd514[16];  // 0x014dd514 IID
// ---- items of slice s006bb1c0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" __declspec(dllimport) int  __stdcall RevokeDragDrop(HWND);

// @ 0x006bb7b0
int __cdecl FUN_006bb7b0(const void* a, const void* b)
{
    return memcmp(a, b, 16) == 0;
}

// @ 0x006bb820
void HasStg::Release()
{
    if (mpStg) ReleaseStgMedium(mpStg);
}

// @ 0x006bb830
long __stdcall FUN_006bb830(void* obj, const void* riid, void** ppv)
{
    if (FUN_006bb7b0(riid, g_guid_014dd514) || FUN_006bb7b0(riid, g_guid_014dd504)) {
        ((void(__stdcall*)(void*))((IUnknownStub*)obj)->vtbl[1])(obj);
        *ppv = obj;
        return 0;
    }
    *ppv = 0;
    return (long)0x80004002;
}

// @ 0x006bb890
long __stdcall FUN_006bb890(long* p)
{
    return InterlockedIncrement(p + 1);
}

// @ 0x006bb8b0
long __stdcall FUN_006bb8b0(RefObj* p)
{
    long n = InterlockedDecrement(&p->mRefCount);
    if (n == 0) {
        if (p) ((void(__thiscall*)(RefObj*, int))p->vtbl[7])(p, 1);
        n = 0;
    }
    return n;
}

// @ 0x006bb8e0
long __stdcall FUN_006bb8e0(void* pThis, IUnknownStub* pUnk, unsigned arg2, unsigned x, unsigned y, unsigned* pOut)
{
    char* self = (char*)pThis;
    int r = ((int(__stdcall*)(IUnknownStub*, void*))pUnk->vtbl[5])(pUnk, self + 0x10);
    self[0xc] = (char)(r == 0);
    if (r == 0) {
        *pOut = 1;
        void* h = *(void**)(self + 8);
        SetFocus(h);
        Win32Point pt; pt.x = (long)x; pt.y = (long)y;
        ScreenToClient(h, &pt);
        unsigned short m = (unsigned short)SendMessageA(h, 0xd7, 0,
            (long)(((unsigned)(unsigned short)pt.y << 16) | (unsigned short)pt.x));
        SendMessageA(h, 0xb1, m, m);
        r = ((int(__stdcall*)(IUnknownStub*, void*, void*))pUnk->vtbl[3])(pUnk, self + 0x10, self + 0x24);
        self[0xc] = (char)(r == 0);
        if (r == 0) FUN_00688d50(self + 0x24);
    } else {
        *pOut = 0;
    }
    return 0;
}

// @ 0x006bb9b0
long __stdcall FUN_006bb9b0(void* pThis, unsigned arg1, unsigned x, unsigned y, unsigned* pOut)
{
    char* self = (char*)pThis;
    if (self[0xc] != 0) {
        Win32Point pt;
        pt.x = (long)x;
        *pOut = 1;
        void* h = *(void**)(self + 8);
        pt.y = (long)y;
        ScreenToClient(h, &pt);
        unsigned short r = (unsigned short)SendMessageA(h, 0xd7, 0,
            (long)(((unsigned)(unsigned short)pt.y << 16) | (unsigned short)pt.x));
        SendMessageA(h, 0xb1, r, r);
        return 0;
    }
    *pOut = 0;
    return 0;
}

// @ 0x006bba40
int __stdcall FUN_006bba40(void* p)
{
    char* c = (char*)p;
    if (c[0xc]) {
        FUN_00688dd0(c + 0x24);
        ReleaseStgMedium(c + 0x24);
        c[0xc] = 0;
    }
    return 0;
}

// @ 0x006bba70
long __stdcall FUN_006bba70(void* pThis, unsigned arg1, unsigned arg2, unsigned x, unsigned y, unsigned* pOut)
{
    char* self = (char*)pThis;
    void* h = *(void**)(self + 8);
    Win32Point pt; pt.x = (long)x; pt.y = (long)y;
    ScreenToClient(h, &pt);
    unsigned short r = (unsigned short)SendMessageA(h, 0xd7, 0,
        (long)(((unsigned)(unsigned short)pt.y << 16) | (unsigned short)pt.x));
    SendMessageA(h, 0xb1, r, r);
    if (self[0xc] != 0) {
        FUN_00688e50(self + 0x24);
        self[0xc] = 0;
        *pOut = 2;
        return 0;
    }
    *pOut = 0;
    return 0;
}

// @ 0x006bbb10
int __cdecl FUN_006bbb10(HWND hwnd, IUnknownStub* p)
{
    RevokeDragDrop(hwnd);
    CoLockObjectExternal(p, 0, 1);
    ((void(__stdcall*)(IUnknownStub*))p->vtbl[2])(p);
    return OleUninitialize();
}
