// src/game/SPCreatureAnim/SPAppModeCreatureAnimViewer.cpp -- migrated from slice(s) s00a0d2d0 by tools/migrate/rewrite.py
// Object file: SPCreatureAnim/SPAppModeCreatureAnimViewer.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>

// ---- items of slice s00a0d2d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
struct WideStr {                                                     // DynamicString, 16 bytes
    uint16_t* begin;                                                 // +0x00
    uint16_t* end;                                                   // +0x04
    uint16_t* cap;                                                   // +0x08
    void*     a0c;                                                   // +0x0c
    void AllocateSelf(int n);                                        // 0x00429760
    void Assign(const uint16_t* b, const uint16_t* e);               // 0x00423650
};
typedef WideStr WStr;
void* __cdecl WCopy(void* dst, const void* src, uint n);             // 0x011e0744
void  __cdecl operator_delete__(void* p);                            // 0x00f47380
void  __cdecl FUN_00a0be60(void* end, uint count, const void* value);// 0x00a0be60
WStr*  __cdecl ConvertToString16(void* out, const char* s, int n);   // 0x0093c5a0
uint   __cdecl FNV1_String16(const uint16_t* s, uint basis, uint x); // 0x00932f30
uint16_t* __cdecl strchr16(const uint16_t* s, int c);                // 0x013cc458
struct KFBase {                                                      // 0x14-byte sub-object
    uint32_t w[5];
    void operator=(const KFBase& o);                                 // 0x00a0b110
};
struct KF {                                                          // 0x18 element
    KFBase b;                                                        // +0x00
    float  prob;                                                     // +0x14
};
struct RecDtor { void dtor(void* b, void* e); };                     // 0x00a0bc90
struct Rec {                                                         // 0x1c record
    float    f0;                                                     // +0x00
    float    f4;                                                     // +0x04
    uint32_t f8;                                                     // +0x08
    WideStr  s;                                                      // +0x0c
    uint32_t f18;                                                    // +0x18
    void ctorFrom(const Rec& o);                                     // 0x00a093b0
};
struct KVec {                                                        // vector<KF>
    KF* begin;                                                       // +0x00
    KF* end;                                                         // +0x04
    KF* cap;                                                         // +0x08
    void* copyCtor(const KVec& src);                                 // 0x00a0d350
    KVec& operator=(const KVec& o);                                  // 0x00a0dd90
    void  resize(uint a);                                            // 0x00a0e0b0
    void  insertAt(KF* pos, uint count, const KF& value);            // 0x00a0da40
};
struct RecVec {                                                      // vector<Rec>
    Rec* begin;                                                      // +0x00
    Rec* end;                                                        // +0x04
    Rec* cap;                                                        // +0x08
    void resize(uint a);                                             // 0x00a0d660
    void growAt(Rec* end, const Rec& value);                         // 0x00a0bcf0
};
struct Parser {
    const char** MainArguments(int n);                               // 0x00838320
    const char** OptionArguments(const char* name, int n);           // 0x00838330
};
struct Host2 {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
virtual void v8();
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
virtual void v13();
virtual void v14();
virtual void v15();
virtual void v16();
virtual void v17();
virtual void v18();
virtual void v19();
virtual void v20();
virtual void v21();
virtual void v22();
virtual void v23();
virtual void v24();
virtual void v25();
virtual void v26();
virtual void v27();
virtual void v28();
virtual void v29();
virtual void v30();
virtual void v31();
virtual void v32();
virtual void v33();
virtual void v34();
    virtual void  v35(void* x);                                      // +0x8c
virtual void  v36();
virtual void v37();
    virtual float v38(const char* s);                                // +0x98
    virtual void  v39();
    virtual uint  v40(const char* s);                                // +0xa0
};
struct S {
    uint32_t id;                                                     // +0x00
    WideStr  s;                                                      // +0x04
    float    f14;                                                    // +0x14
    float    f18;                                                    // +0x18
    uint8_t  b1c, b1d, b1e;                                          // +0x1c,1d,1e
    uint32_t f20;                                                    // +0x20
    uint32_t f24;                                                    // +0x24
    uint32_t f28;                                                    // +0x28
    KVec     vec;                                                    // +0x2c
    S(const S& o);                                                   // 0x00a0d7a0
    S& operator=(const S& o);                                        // 0x00a0df30
    void reset();                                                    // 0x00a0e250
};
struct ObjA {                                                        // this+0xc -> this
    uint8_t pad00[0x38];                                             // +0x00
    RecVec* pv;                                                      // +0x38
};
struct Cheat {
    uint8_t pad00[0x04];                                             // +0x00
    Host2*  f04;                                                     // +0x04
    uint8_t pad08[0x04];                                             // +0x08
    ObjA*   f0c;                                                     // +0x0c
    void Execute_880(void* parser);                                  // 0x00a0d880
};
// ---- items of slice s00a0d2d0 end

// @ 0x00a0d660
void RecVec::resize(uint a)
{
    uint n = (uint)(end - begin);
    if (a > n) {
        Rec tmp;
        tmp.f0 = 1.0f;
        tmp.f4 = -1.0f;
        tmp.f8 = 0;
        tmp.s.begin = (uint16_t*)0x01667bac;
        tmp.s.end   = (uint16_t*)0x01667bac;
        tmp.s.cap   = (uint16_t*)0x01667bae;
        FUN_00a0be60(end, a - n, &tmp);
        if ((((char*)tmp.s.cap - (char*)tmp.s.begin) & 0xfffffffe) > 2 && tmp.s.begin != 0)
            operator_delete__(tmp.s.begin);
    } else {
        RecDtor* rd = (RecDtor*)this;
        rd->dtor(begin + a, end);
    }
}

// @ 0x00a0d7a0
S::S(const S& o)
{
    id = o.id;
    s.begin = 0;
    s.end = 0;
    s.cap = 0;
    int n = (int)(o.s.end - o.s.begin);
    s.AllocateSelf(n + 1);
    WCopy(s.begin, o.s.begin, (uint)n * 2);
    s.end = (uint16_t*)((char*)s.begin + n * 2);
    *s.end = 0;
    f14 = o.f14;
    f18 = o.f18;
    b1c = o.b1c;
    b1d = o.b1d;
    b1e = o.b1e;
    f20 = o.f20;
    f24 = o.f24;
    f28 = o.f28;
    vec.copyCtor(o.vec);
}

// @ 0x00a0d850
void __cdecl FUN_00a0d850(KF* first, KF* last, const KF* value)
{
    for (; first != last; ++first) {
        first->b = value->b;
        first->prob = value->prob;
    }
}

// @ 0x00a0d880
void Cheat::Execute_880(void* parser)
{
    const char** a = ((Parser*)parser)->MainArguments(1);

    RecVec* v = (RecVec*)(*(char**)((char*)f0c + 0x3c) - 0x18);
    v->resize((uint)(v->end - v->begin) + 1);

    Rec* last = v->end - 1;
    WStr tmp;
    WStr* r = ConvertToString16(&tmp, a[0], -1);
    if (r != &last->s)
        last->s.Assign(r->begin, r->end);
    if ((((char*)tmp.cap - (char*)tmp.begin) & 0xfffffffe) > 2 && tmp.begin != 0)
        operator_delete__(tmp.begin);

    uint id;
    const char** o = ((Parser*)parser)->OptionArguments("instanceId", 1);
    if (o != 0) {
        id = f04->v40(o[0]);
    } else {
        uint16_t* str = last->s.begin;
        uint16_t* pw = strchr16(str, '/');
        if (pw != 0)
            str = pw + 1;
        id = FNV1_String16(str, 0x811c9dc5, 1);
    }
    last->f8 = id;

    const char** ds = ((Parser*)parser)->OptionArguments("durationScale", 1);
    if (ds != 0)
        last->f0 = f04->v38(ds[0]);

    const char** du = ((Parser*)parser)->OptionArguments("duration", 1);
    if (du != 0)
        last->f4 = f04->v38(du[0]);
}
