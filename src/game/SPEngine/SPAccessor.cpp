// src/game/SPEngine/SPAccessor.cpp -- migrated from slice(s) s00b318d0, s0080d670, s004da330 by tools/migrate/rewrite.py
// Object file: SPEngine/SPAccessor.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "cSPUILayeredObject.h"
#include <intrin.h>
#include "EA/ArgScript/cArguments.h"
#include "EA/ArgScript/cCommandBase.h"
#include "SP/cGonzagoSubsystem.h"
#include "SP/cVarListSerializer.h"
#include <xmmintrin.h>
#include <new>

// unnamed retail callees and globals (address in the comment)
extern void* GetManager();   // 0x0067dcd0
#pragma pack(push, 4)

// ---- items of slice s004da330 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern void* GetManager();   // 0x0067dcd0
struct IResourceManager {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c(uint32_t a, int b, int c, int d, int e, int f);
};
// ---- items of slice s004da330 end

// ---- items of slice s0080d670 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned char  u8;
void  __cdecl  VisitTree(void*, void*, void*);    // 0x807d30 SPUIHelpers::VisitWindowTreeDepthFirst
// ---- items of slice s0080d670 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
u8 __cdecl FUN_0080d6b0(void* p, u8* p2)  // 0x0080d6b0 (stays in the slice: not this object's)
{
    VisitTree(p, 0, (void*)*(int*)(p2 + 4));
    return *p2;
}

// ---- items of slice s00b318d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) unsigned long __cdecl wcstoul(const wchar_t*, wchar_t**, int);
extern "C" __declspec(dllimport) int __cdecl wcsncmp(const wchar_t*, const wchar_t*, unsigned);
extern "C" __declspec(dllimport) wchar_t* __cdecl wcschr(const wchar_t*, wchar_t);
#pragma intrinsic(_ReadWriteBarrier)
#define VT(p) (*(void***)(p))
#define VFN(p, off, T) ((T)(VT(p)[(off) / 4]))
void  __cdecl operator_delete__(void* p);                    // 00f47380
struct IRef { virtual void r0(); virtual void Release(); };
struct cTranslatorBase {
    int mBase4;
    cTranslatorBase();
    ~cTranslatorBase() throw();                                  // 005725a0
    virtual void t0();
};
struct WStr {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCap;
    WStr(const wchar_t* s) : mpBegin(0), mpEnd(0), mpCap(0) { RangeInit(s); }
    ~WStr() { if (((unsigned)((char*)mpCap - (char*)mpBegin) & ~1u) > 2 && mpBegin) operator_delete__(mpBegin); }
    void RangeInit(const wchar_t* s);                            // 00579a90
    void append(const wchar_t* s);                               // 005c3d90
    void assign(const wchar_t* b, const wchar_t* e);             // 00423650
    unsigned size() const { return mpEnd - mpBegin; }
};
struct WStrEmpty {
    wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCap;
    WStrEmpty() : mpBegin((wchar_t*)0x1667bac), mpEnd((wchar_t*)0x1667bac), mpCap((wchar_t*)0x1667bae) {}
    ~WStrEmpty() { if (((unsigned)((char*)mpCap - (char*)mpBegin) & ~1u) > 2 && mpBegin) operator_delete__(mpBegin); }
};
bool __cdecl WStrEquals(const WStrEmpty* s, const wchar_t* lit);  // 006ab760
void* __cdecl SP_StringDetokenizer();                            // 0067de50
void* __cdecl SP_PropertyManager();                              // 0067de30
bool __cdecl GetFloatProperty(void* plist, unsigned id, float* out);   // 0040cf10
bool __cdecl TryGetUIntProperty(void* plist, unsigned id, unsigned* out); // 00410370
void __cdecl SetNumberStringD(double v, wchar_t* buf, unsigned cap, int flags);  // 00881ea0
void __cdecl SetNumberStringI(__int64 v, wchar_t* buf, unsigned cap);             // 00881ae0
struct cTokenTranslator : cTranslatorBase {
    IRef* mpPropList;                                            // +8
    virtual ~cTokenTranslator();
    virtual bool Lookup(const wchar_t* tok, void* outStr);       // slot 0x10 (approx.)
    bool Translate(const wchar_t* tok, WStr* out);
    void* FUN_00b324b0(unsigned int flags);
};
// ---- items of slice s00b318d0 end

// @ 0x004da3a0
void ResourceManager(uint32_t param)
{
    IResourceManager* p = (IResourceManager*)GetManager();
    p->v0c(param, 0, 0, 0, 0, 0);
}

// @ 0x0080d710
void __stdcall FUN_0080d710(void* a, int b, u8 c)
{
    u8 local[8];
    local[0] = c;
    *(int*)(local + 4) = b;
    VisitTree(a, (void*)FUN_0080d6b0, local);
}

// @ 0x00b324f0
bool cTokenTranslator::Translate(const wchar_t* tok, WStr* out)
{
    bool result = false;
    if (wcsncmp(tok, L"^p", 2) == 0) {
        WStr s(tok);
        int idx[3];
        int count = 0;
        int pos = 1;
        while (count < 3) {
            ++pos;
            wchar_t* p = 0;
            if ((unsigned)pos < s.size()) {
                for (p = s.mpBegin + pos; p != s.mpEnd; ++p)
                    if (*p == L'^') break;
                if (p == s.mpEnd) p = 0;
            }
            if (!p) { pos = -1; }
            else pos = (int)(p - s.mpBegin);
            if (pos == -1) break;
            idx[count] = pos;
            s.mpBegin[pos] = 0;
            ++count;
        }
        if (count != 3)
            return false;
        WStrEmpty str2;
        const wchar_t* t2 = s.mpBegin + idx[0] + 1;
        if (!Lookup(t2, &str2)) {
            void* det = SP_StringDetokenizer();
            void* d2 = VFN(det, 0x10, void*(__thiscall*)(void*))(det);
            if (!VFN(d2, 0x10, bool(__thiscall*)(void*, const wchar_t*, void*))(d2, t2, &str2))
                return result;
        }
        if (WStrEquals(&str2, L"1"))
            out->append(s.mpBegin + idx[1] + 1);
        else
            out->append(s.mpBegin + idx[2] + 1);
        result = true;
        return result;
    }
    if (wcsncmp(tok, L"prop_file:1", 10) == 0) {
        const wchar_t* bang = wcschr(tok + 10, L'!');
        if (bang) {
            unsigned a = wcstoul(tok + 10, 0, 16);
            unsigned b = wcstoul(bang + 1, 0, 16);
            void* pm = SP_PropertyManager();
            IRef** ref = &mpPropList;
            if (*ref) {
                IRef* old = *ref;
                *ref = 0;
                old->Release();
            }
            result = VFN(pm, 0x2c, bool(__thiscall*)(void*, unsigned, unsigned, IRef**))(pm, b, a, ref);
        }
    }
    if (mpPropList) {
        wchar_t buf[256];
        if (wcsncmp(tok, L"tuning_float:", 13) == 0) {
            unsigned id = wcstoul(tok + 13, 0, 16);
            float fv;
            if (GetFloatProperty(mpPropList, id, &fv)) {
                SetNumberStringD((double)fv, buf, 0x100, 0);
                out->append(buf);
                result = true;
            }
        } else if (wcsncmp(tok, L"tuning_int:", 11) == 0) {
            unsigned id = wcstoul(tok + 11, 0, 16);
            unsigned iv;
            if (TryGetUIntProperty(mpPropList, id, &iv)) {
                SetNumberStringI((int)iv, buf, 0x100);
                out->append(buf);
                result = true;
            }
        }
    }
    wchar_t brk[3];
    wchar_t nl[2];
    brk[0] = 0x62; brk[1] = 0x72; brk[2] = 0;
    nl[0] = 0xa; nl[1] = 0;
    const wchar_t* a = tok;
    const wchar_t* b = brk;
    int cmp = 0;
    for (;;) {
        if (*a != *b) { cmp = (*a < *b) ? -1 : 1; break; }
        if (*a == 0) break;
        ++a; ++b;
    }
    if (cmp != 0)
        return result;
    const wchar_t* e = nl;
    while (*e) ++e;
    out->assign(nl, e);
    return true;
}
