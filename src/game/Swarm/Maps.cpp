// src/game/Swarm/Maps.cpp -- migrated from slice(s) s00a77c80 by tools/migrate/rewrite.py
// Object file: Swarm/Maps.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include <intrin.h>

// ---- items of slice s00a77c80 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(size_t size, const char* pName, int a, int b, const char* file, int line);  // 0xf473a0
void* operator new[](size_t size, const char* pName, int a, int b, const char* file, int line);
struct IRefObj { virtual void AddRef(); virtual void Release(); };   // slots 0 (AddRef), 1 (Release)
struct B4 {                      // second base at +4: vptr + counter
    virtual ~B4() {}
    int mRef;
    B4() { mRef = 0; }
};
struct MapInfoBase : IRefObj, B4 {   // 0xc bytes (Swarm::MapInfo, 0x00a77e00)
    MapInfoBase();
    virtual void Release();
    virtual ~MapInfoBase() {}
};
struct IItem { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
               virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7(uint32_t a); };
struct MapInfoMid : IRefObj, B4 {    // 0x40 bytes
    uint32_t mUnk0c[4];
    bool     mB1c;
    int      mI20, mI24;
    float    mF28, mF2c;
    int      mI30;
    bool     mOwnsItem;
    IItem*   mpItem;
    bool     mB3c;
    MapInfoMid() { mB1c = false; mI20 = 0; mI24 = 0; mF28 = 1.0f; mF2c = 1.0f; mI30 = 0;
                   mOwnsItem = false; mpItem = 0; mB3c = false; }
    virtual void Apply();
    // @ 0x00a77f50  (deleting dtor of MapInfoMid)
    virtual ~MapInfoMid() { if (mpItem && mOwnsItem) mpItem->v7(mI30); }
};
struct MapInfoD2 : MapInfoMid {  // 0x44 bytes
    uint32_t x[1];
    MapInfoD2();                                         // 0x00a77fa0
    void Init76070(void*, int, int, bool, void*, bool);  // 0x00a76070
    virtual void Apply(); };
struct MapInfoD3 : MapInfoMid {  // 0x48 bytes
    uint32_t x[2];
    MapInfoD3();                                         // 0x00a78000
    void Init76420(void*, int, int, bool, void*, bool);  // 0x00a76420
    virtual void Apply(); };
struct MapInfoD4 : MapInfoMid {  // 0x48 bytes
    uint32_t x[2];
    MapInfoD4();                                         // 0x00a78050
    void Init769b0(void*, int, int, bool, void*);        // 0x00a769b0
    virtual void Apply(); };
struct MapInfoD5 : MapInfoMid {  // 0x50 bytes
    uint32_t x[4];
    MapInfoD5();                                         // 0x00a780a0
    void Init76b80(void*, int, int, bool, void*);        // 0x00a76b80
    virtual void Apply(); };
struct MapInfoMid2 : MapInfoMid { uint32_t x40; MapInfoMid2() { x40 = 0; } };
struct MapInfoD6 : MapInfoMid2 {  // 0x48 bytes
    uint32_t x44;
    MapInfoD6();                                         // 0x00a781a0
    void Init76070(void*, int, int, bool, void*, bool);  // 0x00a76070
    virtual void Apply(); };
struct MapInfoD0 : MapInfoMid {  // 0x50 bytes; used for kinds 2/3
    uint32_t x[4];
    MapInfoD0();                                         // 0x00a77ef0
    void Init75810(void*, int, int, bool, void*, bool);  // 0x00a75810
    void Init758b0(void*, int, int, bool, void*, int, bool);   // 0x00a758b0
    virtual void Apply(); };
struct MapInfoD7 : MapInfoMid {  // 0x80 bytes
    uint32_t x[0x10];
    MapInfoD7();                                         // 0x00a76cf0 (other slice)
    void Init77b70(int, void*, void*);                   // 0x00a77b70
    void Init75340(int, uint32_t, uint32_t);             // 0x00a75340
    void Init752d0(int, void*);                          // 0x00a752d0
    virtual void Apply(); };
struct MapDescription {
    virtual void d0();
    uint32_t mField4;          // +4
    uint32_t mA8, mAC;         // +8, +0xc  (read as one 64-bit id)
    uint32_t mFlags;           // +0x10
    uint32_t mKind;            // +0x14
    int      mI18, mI1c;       // +0x18, +0x1c
    float    mV20[4];          // +0x20 (16 bytes read raw)
    int8_t   mType30;          // +0x30
    int8_t   mFlag31;          // +0x31
    uint32_t mPad32;
    uint32_t mPairs[8];        // +0x38: 4 x 64-bit
    float    mVecs[16];        // +0x58: 4 x 16 bytes
    MapDescription();
};
struct IContext {
virtual void c0();
virtual void c1();
virtual void c2();
virtual void c3();
virtual void c4();
    virtual void* GetSink();                                   // +0x14
virtual void c6();
virtual void c7();
virtual void c8();
virtual void c9();
virtual void c10();
virtual void c11();
virtual void c12();
virtual void c13();
virtual void c14();
virtual void c15();
virtual void c16();
virtual void c17();
virtual void c18();
virtual void c19();
virtual void c20();
virtual void c21();
virtual void c22();
virtual void c23();
virtual void c24();
virtual void c25();
virtual void c26();
virtual void c27();
virtual void c28();
virtual void c29();
virtual void c30();
virtual void c31();
virtual void c32();
virtual void c33();
    virtual void AddEntry(uint32_t a, uint32_t b, IRefObj* o);  // +0x88
};
struct RefHolder {
    IRefObj* p;
    RefHolder& operator=(IRefObj* o);   // 0x00b5f950 (out of line)
    ~RefHolder() { if (p) p->Release(); }
};
static inline bool BitAt(uint32_t v, int n) { return ((v >> n) & 1) != 0; }
// ---- items of slice s00a77c80 end

// @ 0x00a781f0
void Add(MapDescription* d, IContext* ctx)
{
    void* sink = ctx->GetSink();
    RefHolder result;
    result.p = 0;
    switch (d->mKind) {
    case 3:
        if (d->mType30 != 4) {
            MapInfoD0* o = new("Swarm/MapInfo", 0, 0, 0, 0) MapInfoD0();
            uint32_t f = d->mFlags;
            o->Init758b0(d->mV20, d->mI18, d->mI1c, BitAt(f, 0), sink, d->mType30, BitAt(f, 1));
            result = o;
        } else {
            MapInfoD2* o = new("Swarm/MapInfo", 0, 0, 0, 0) MapInfoD2();
            uint32_t f = d->mFlags;
            o->Init76070(d->mV20, d->mI18, d->mI1c, BitAt(f, 0), sink, BitAt(f, 1));
            result = o;
        }
        break;
    case 4:
    case 5: {
        MapInfoD6* o = new("Swarm/MapInfo", 0, 0, 0, 0) MapInfoD6();
        uint32_t f = d->mFlags;
        o->Init76070(d->mV20, d->mI18, d->mI1c, BitAt(f, 0), sink, BitAt(f, 1));
        result = o;
        break; }
    case 2: {
        MapInfoD0* o = new("Swarm/MapInfo", 0, 0, 0, 0) MapInfoD0();
        uint32_t f = d->mFlags;
        o->Init75810(d->mV20, d->mI18, d->mI1c, BitAt(f, 0), sink, BitAt(f, 1));
        result = o;
        break; }
    case 1: {
        MapInfoD3* o = new("Swarm/MapInfo", 0, 0, 0, 0) MapInfoD3();
        uint32_t f = d->mFlags;
        o->Init76420(d->mV20, d->mI18, d->mI1c, BitAt(f, 0), sink, BitAt(f, 1));
        result = o;
        break; }
    case 6: {
        MapInfoD7* o = new("Swarm/MapInfo", 0, 0, 0, 0) MapInfoD7();
        o->Init77b70(d->mFlag31, d->mV20, sink);
        for (int i = 0; i < 4; ++i) {
            uint32_t m = 1u << i;
            if ((unsigned)(i + 2) < 10 && (d->mFlags & _rotl(m, 2)) != 0)
                o->Init75340(i, d->mPairs[i * 2], d->mPairs[i * 2 + 1]);
            else if ((unsigned)(i + 6) < 10 && (d->mFlags & _rotl(m, 6)) != 0)
                o->Init752d0(i, &d->mVecs[i * 4]);
        }
        if (!o) return;
        o->AddRef();
        result.p = o;
        break; }
    case 7: {
        MapInfoD4* o = new("Swarm/MapInfo", 0, 0, 0, 0) MapInfoD4();
        o->Init769b0(d->mV20, d->mI18, d->mI1c, BitAt(d->mFlags, 0), sink);
        result = o;
        break; }
    case 8: {
        MapInfoD5* o = new("Swarm/MapInfo", 0, 0, 0, 0) MapInfoD5();
        o->Init76b80(d->mV20, d->mI18, d->mI1c, BitAt(d->mFlags, 0), sink);
        result = o;
        break; }

    case 0:
        result = new("Swarm/MapInfo", 0, 0, 0, 0) MapInfoBase();
        break;
    default:
        return;
    }
    if (result.p) ctx->AddEntry(d->mA8, d->mAC, result.p);
}
