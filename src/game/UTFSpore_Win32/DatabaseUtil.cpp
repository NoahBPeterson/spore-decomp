// src/game/UTFSpore_Win32/DatabaseUtil.cpp -- migrated from slice(s) s008dd0d0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/DatabaseUtil.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ResourceMan/Key.h"
#include "eastl/allocator.h"
#include "EA/ResourceMan/Manager.h"
#include "EA/ResourceMan/Database.h"
#include "EA/SharedLibrary.h"

// unnamed retail callees and globals (address in the comment)
extern "C" long _InterlockedExchangeAdd(volatile long*, long);
extern "C" long _InterlockedExchange(volatile long*, long);
extern "C" long _InterlockedIncrement(volatile long*);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange, _InterlockedIncrement)

extern "C" __declspec(dllimport) int __cdecl towlower(int c);
extern "C" int __cdecl iswctype(unsigned c, unsigned t);

// name-from-key hooks (address in the name)
extern void* g_pfn_154c464;
extern void* g_pfn_154c468;

// ---- items of slice s008dd0d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Str { void append(const wchar_t* s); };
// ---- items of slice s008dd0d0 end

// @ 0x008dd7d0
extern "C" unsigned FUN_008dd7d0(const unsigned short* s, int count)
{
    unsigned h = 0x811c9dc5;
    while (count-- != 0) {
        h = h * 0x1000193 ^ (unsigned short)towlower(*s++);
    }
    return h;
}

// @ 0x008dd820
extern "C" unsigned short* FUN_008dd820(unsigned short* p, unsigned short* end, char a3, char a4)
{
    unsigned short* start = p;
    if (a3 != 0) {
        for (; p != end; ++p)
            if (*p == 0x5f)
                start = p + 1;
    }
    if ((int)((end - start) & 0xfffffffe) < 0x10)
        return 0;
    if (*start == 0x30 && (start[1] == 0x78 || start[1] == 0x58))
        start += 2;
    else if (!iswctype(*start, 4))
        return 0;
    int n = 0;
    unsigned short* q = start;
    if (start != end) {
        do { if (!iswctype(*q, 0x80)) return 0; ++q; ++n; } while (q != end);
        if (n == 8 || (n == 0x10 && a4))
            return start;
    }
    return 0;
}

// @ 0x008dd8d0
extern "C" void FUN_008dd8d0(void* a, void* b)
{
    g_pfn_154c464 = a;
    g_pfn_154c468 = b;
}

// @ 0x008dd8f0
extern "C" int FUN_008dd8f0(int* self, void* out)
{
    (void)self; (void)out;
    return 0;
}

struct Stream_s008ddb00 {
    virtual void f00(); virtual void f04(); virtual void f08(); virtual void f0c();
    virtual void f10(); virtual void f14(); virtual void f18();
    virtual unsigned GetSize();                              // +0x1c
    virtual void f20(); virtual void f24(); virtual void f28(); virtual void f2c();
    virtual unsigned Read(int buf, unsigned n);              // +0x30
};
struct Record_s008ddb00 {
    virtual void f00(); virtual void f04();
    virtual void Release();                                  // +0x08
    virtual void f0c(); virtual void f10(); virtual void f14();
    virtual Stream_s008ddb00* GetStream();                   // +0x18
    virtual void f1c(); virtual void f20();
    virtual void Close();                                    // +0x24
};
struct Db_s008ddb00 {
    virtual void f00(); virtual void f04(); virtual void f08(); virtual void f0c();
    virtual void f10(); virtual void f14(); virtual void f18(); virtual void f1c();
    virtual void f20(); virtual void f24(); virtual void f28(); virtual void f2c();
    virtual void f30();
    virtual bool OpenRecord(int key, Record_s008ddb00** out, int mode, int flags, int a5, int a6);   // +0x34
};
// @ 0x008ddb00
extern "C" unsigned FUN_008ddb00(Db_s008ddb00* self, int a2, int a3, unsigned a4, int a5, int a6)
{
    unsigned result = 0;
    Record_s008ddb00* io = 0;
    if (self->OpenRecord(a2, &io, 1, 3, a5, a6)) {
        Stream_s008ddb00* s = io->GetStream();
        if (s != 0) {
            unsigned avail = s->GetSize();
            if (avail > a4)
                avail = a4;
            result = s->Read(a3, avail);
            io->Close();
        }
    }
    if (io != 0)
        io->Release();
    return result;
}

struct IStrm_8ddb90 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual char Read(int a, int b);                 // +0x38
};
struct IRec_8ddb90 {
    virtual void v00(); virtual void v04();
    virtual void Release();                          // +0x08
    virtual void v0c(); virtual void v10(); virtual void v14();
    virtual IStrm_8ddb90* GetStream();               // +0x18
    virtual void v1c(); virtual void v20();
    virtual void Close();                            // +0x24
};
struct IDb_8ddb90 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30();
    virtual char OpenRecord(int key, IRec_8ddb90** out, int a, int b, int c, int d);   // +0x34
};
// @ 0x008ddb90
extern "C" char FUN_008ddb90(void* self, int a2, int a3, int a4, int a5)
{
    char result = 0;
    IRec_8ddb90* io = 0;
    if (((IDb_8ddb90*)self)->OpenRecord(a2, &io, 2, 2, a5, 0)) {
        IStrm_8ddb90* s = io->GetStream();
        if (s != 0)
            result = s->Read(a3, a4);
        io->Close();
    }
    if (io != 0)
        io->Release();
    return result;
}

// 0x008ddc10 (byte-exact lifted version: match/slices/s008ddc10/s008ddc10.cpp)
extern "C" char FUN_008ddc10(int a1, void* out, void* pKey)
{
    wchar_t buf[0x104];
    if (pKey == 0)
        return 0;
    if (((int (__thiscall*)(void*))(((void**)*(void**)pKey)[0x0c / 4]))(pKey) != 0x34728492)
        return 0;
    if (!((char (__thiscall*)(void*, int, void*))(((void**)*(void**)pKey)[0x64 / 4]))(pKey, a1, buf))
        return 0;
    ((Str*)out)->append(buf);
    return 1;
}

// @ 0x008ddc80
namespace EA {
namespace ResourceMan {
void DefaultCreateNameFromKey(Key const & key, eastl::basic_string<wchar_t, eastl::allocator> & out, Manager const * a3, Database const * a4, wchar_t const * a5)
{
    (void)key; (void)out; (void)a3; (void)a4; (void)a5;
}
}
}  // namespace EA::ResourceMan
