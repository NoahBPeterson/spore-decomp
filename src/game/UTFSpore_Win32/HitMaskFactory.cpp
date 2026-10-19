// src/game/UTFSpore_Win32/HitMaskFactory.cpp -- migrated from slice(s) s00997f50, s00996f10 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/HitMaskFactory.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/UTFWinExtras/cXHTMLFrameSet.h"
#include "EA/UTFWinExtras/WinXHTML.h"
#include "EA/Thread/Mutex.h"
#include "EA/UTFWinTools/RWTextureFactory.h"
#include "EA/UTFWinTools/SerCollection.h"
#include "EA/UTFWinTools/SerScope.h"
#include "EA/ResourceMan/Key.h"

// unnamed retail callees and globals (address in the comment)
extern "C" long _InterlockedExchangeAdd(volatile long*, long);
extern "C" long _InterlockedExchange(volatile long*, long);
extern "C" void  FUN_00f47380(void* p);                                 // operator delete
extern "C" void* FUN_00f473a0(unsigned size, const char* cat, int a, int b, int c, int d);
extern "C" void  FUN_0087cde0(void* a);                                 // 0x87cde0
extern "C" char  FUN_0087ce00(void* a);                                 // 0x87ce00
extern "C" char  FUN_0087d0b0(void* a, void* b);                        // 0x87d0b0
extern "C" void* FUN_0087ced0(int a);                                   // 0x87ced0
extern "C" char  FUN_0087cf00(void* a, void* b, int c);                 // 0x87cf00
extern "C" void  FUN_0087cef0(void* a);                                 // gfree
extern "C" void  FUN_0087d070(void);                                    // 0x87d070
extern "C" void  FUN_00957300(void* a, int b, void* c);                 // 0x957300
extern "C" void  FUN_00957230(void* a, int b, void* c);                 // 0x957230
extern "C" unsigned g_frameMapTypes[];                                 // 0x1446868
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)

// ---- items of slice s00996f10 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long _InterlockedExchangeAdd(volatile long*, long);
extern "C" long _InterlockedExchange(volatile long*, long);
extern "C" void  FUN_00f47380(void* p);                                 // operator delete
extern "C" void* FUN_00f473a0(unsigned size, const char* cat, int a, int b, int c, int d);
extern "C" void  FUN_0087cde0(void* a);                                 // 0x87cde0
extern "C" char  FUN_0087ce00(void* a);                                 // 0x87ce00
extern "C" char  FUN_0087d0b0(void* a, void* b);                        // 0x87d0b0
extern "C" void* FUN_0087ced0(int a);                                   // 0x87ced0
extern "C" char  FUN_0087cf00(void* a, void* b, int c);                 // 0x87cf00
extern "C" void  FUN_0087cef0(void* a);                                 // gfree
extern "C" void  FUN_0087d070(void);                                    // 0x87d070
extern "C" void  FUN_00957300(void* a, int b, void* c);                 // 0x957300
extern "C" void  FUN_00957230(void* a, int b, void* c);                 // 0x957230
extern "C" unsigned g_frameMapTypes[];                                 // 0x1446868
struct Obj33 {
    char pad[0x18];
    Obj33* ctor();                                 // 0x997b60
    void clear();                                  // 0x997ba0
    void* ScalarDtor(unsigned flags);              // 0x997cc0
    int  GetSupportedTypes(unsigned* out, unsigned n); // 0x997d40
    bool CanConvert(int a, int id);                // 0x997d80
    int  Release();                                // 0x997d90
    void* ctor2();                                 // 0x997f30
};
// ---- items of slice s00996f10 end

// ---- items of slice s00997f50 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Obj34 {
    char pad[0x40];
    void* ctor();          // 0x997f50
    void* ScalarDtor(unsigned flags);  // 0x998000
};
struct HMFactory { bool CreateResource(int param2, void** out, void* p4, void* p5); };
// ---- items of slice s00997f50 end

// @ 0x00997d40
int Obj33::GetSupportedTypes(unsigned* out, unsigned n)
{
    unsigned i = 0;
    if (n > 0) {
        do {
            if (i >= 6)
                break;
            out[i] = g_frameMapTypes[i];
            i++;
        } while (i < n);
    }
    return 6;
}

// @ 0x00997d80
bool Obj33::CanConvert(int a, int id)
{
    (void)a;
    return id == 0x19aef76;
}

// @ 0x00997d90
int Obj33::Release()
{
    char* p = (char*)this + 0x28;
    volatile long* rc = (volatile long*)(p + 4);
    int n = _InterlockedExchangeAdd(rc, -1) - 1;
    if (n == 0) {
        _InterlockedExchange(rc, 1);
        if (p != 0)
            (*(void(__thiscall**)(void*, int))((char*)*(void**)p + 8))(p, 1);
    }
    return n;
}

// @ 0x00997dc0
bool ReadResource(char* self, char* p2, void* p3)
{
    int i2 = (*(int(__thiscall**)(char*))((char*)*(void**)self + 0x10))(self);
    unsigned ebx = *(unsigned*)(i2 + 4) - 0x2f7d0000;
    if (p2 == 0)
        return false;
    char* ebp = (char*)(*(void*(__thiscall**)(char*, int))((char*)*(void**)p2 + 0xc))(p2, 0xf074e1c8);
    if (ebp == 0)
        return false;
    int q = (*(int(__thiscall**)(char*))((char*)*(void**)self + 0x10))(self);
    int ca = *(int*)(q + 0);
    int cb = *(int*)(q + 4);
    int cc = *(int*)(q + 8);
    *(int*)(p2 + 8) = ca;
    *(int*)(p2 + 0xc) = (int)p3;
    *(int*)(p2 + 0x10) = cc;
    int local[2];
    FUN_0087cde0(local);
    int u = (*(int(__thiscall**)(char*))((char*)*(void**)self + 0x18))(self);
    if (!FUN_0087ce00((void*)u))
        return false;
    if (!FUN_0087d0b0((void*)(ebx + 0x0), local))
        return false;
    char* img = (char*)FUN_0087ced0(0);
    if (img == 0) {
        FUN_0087d070();
        return true;
    }
    int w = *(int*)(img + 0x10);
    int row = ((*(int*)(img + 0x18) + (*(int*)(img + 0x18) >> 31 & 7)) >> 3) * w;
    int h = *(int*)(img + 0x14);
    unsigned char* buf = (unsigned char*)FUN_00f473a0(h * row, "UTFWin/HitMaskImage", 0, 0, 0, 0);
    if (FUN_0087cf00(img, buf, row)) {
        if (*(int*)(img + 0x18) == 0x20)
            FUN_00957300(local, w, buf);
        else if (*(int*)(img + 0x18) == 8)
            FUN_00957230(local, w, buf);
    }
    FUN_00f47380(buf);
    FUN_0087cef0(img);
    FUN_0087d070();
    (void)cb;
    return true;
}

// @ 0x00997f30
void* Obj33::ctor2()
{
    unsigned char* p = (unsigned char*)this;
    *(void**)p = (void*)0x13effa8;
    _InterlockedExchange((volatile long*)(p + 4), 0);
    *(void**)p = (void*)0x1446894;
    return this;
}

// @ 0x00997f50
void* Obj34::ctor()
{
    char* a = (char*)this;
    *(void**)(a + 4) = (void*)0x13ef094;
    *(unsigned*)(a + 8) = 0;
    *(void**)(a + 0) = (void*)0x141a380;
    *(void**)(a + 4) = (void*)0x141a37c;
    *(unsigned*)(a + 0x14) = 0;
    *(unsigned*)(a + 0x18) = 0;
    *(unsigned*)(a + 0x1c) = 0;
    *(void**)(a + 0x28) = (void*)0x13ebcdc;
    _InterlockedExchange((volatile long*)(a + 0x2c), 0);
    *(unsigned*)(a + 0x30) = 0;
    *(unsigned*)(a + 0x34) = 0;
    *(unsigned*)(a + 0x38) = 0;
    *(void**)(a + 0) = (void*)0x14468e0;
    *(void**)(a + 4) = (void*)0x14468dc;
    *(void**)(a + 0x28) = (void*)0x14468c8;
    return a;
}

// @ 0x00998000
void* Obj34::ScalarDtor(unsigned flags)
{
    char* a = (char*)this;
    *(void**)(a + 0x28) = (void*)0x13eb938;
    int p = *(int*)(a + 0x14);
    if (p != 0 && *(int*)(p - 4) != 0)
        FUN_00f47380((void*)p);
    *(void**)(a + 4) = (void*)0x13ef094;
    *(void**)(a + 0) = (void*)0x13eb938;
    if (flags & 1)
        FUN_00f47380(a);
    return a;
}

// @ 0x00998050
bool HMFactory::CreateResource(int param2, void** out, void* p4, void* p5)
{
    char* self = (char*)this;
    char* obj = (char*)FUN_00f473a0(0x3c, "UTFWin/HitMaskResource", 0, 0, 0, 0);
    if (obj == 0) {
        // fall through as 0
    } else {
        ((Obj34*)obj)->ctor();
    }
    (*(void(__thiscall**)(char*))*(void**)obj)(obj);
    char* res = obj + 0x28;
    if (param2 != 0) {
        char ok = (*(char(__thiscall**)(char*, int, char*, void*, void*))((char*)*(void**)self + 0x24))(
            self, param2, res, p4, p5);
        if (!ok) {
            (*(void(__thiscall**)(char*))((char*)*(void**)obj + 4))(obj);
            return false;
        }
    }
    *out = res;
    return true;
}
