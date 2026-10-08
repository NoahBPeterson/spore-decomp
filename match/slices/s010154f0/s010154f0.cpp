// Slice s010154f0 -- SP::cSimulatorUniverse::cSimulatorUniverse (0x010154f0, 2301 bytes).
// Constructs the universe simulator: base ctor, 9 inline event/action sub-objects registered in the
// event vector_map, three empty maps, then reads the tuning property list (0x3e9793b5/0x2ae0c7e).
// Field offsets are the retail ones from the disassembly (they differ from the 2008 PDB).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).  Property reads follow the cCityGameTuning::Init pattern (s00cef050).
#include "types.h"

typedef unsigned int size_t;
inline void* operator new(size_t, void* p) { return p; }
inline void operator delete(void*, void*) {}

// ---- property access ---------------------------------------------------------------------
struct Property {
    uint8_t pad[0x12];
    uint16_t mType;                                           // +0x12
    int* GetInt();                                            // 0x0041e990
    float* GetFloat();                                        // 0x0041ea70
};
struct cPropertyList {
    virtual void vf0();
    virtual int Release();                                    // +0x04
    virtual void vf2(); virtual void vf3(); virtual void vf4(); virtual void vf5(); virtual void vf6();
    virtual void vf7(); virtual void vf8();
    virtual bool GetProperty(uint32_t id, Property** out);    // +0x24
};
struct PropListPtr {
    cPropertyList* mpObject;
    PropListPtr() : mpObject(0) {}
    cPropertyList** AsPPTypeParam()
    {
        if (mpObject) {
            cPropertyList* const p = mpObject;
            mpObject = 0;
            p->Release();
        }
        return &mpObject;
    }
};
struct IPropertyManager {
    virtual void vf0(); virtual void vf1(); virtual void vf2(); virtual void vf3(); virtual void vf4();
    virtual void vf5(); virtual void vf6(); virtual void vf7(); virtual void vf8(); virtual void vf9();
    virtual void vf10();
    virtual bool GetPropertyList(uint32_t instance, uint32_t group, cPropertyList** out);   // +0x2c
};
IPropertyManager* PropertyManager();                          // 0x0067de30

static inline void LoadInt(cPropertyList* l, uint32_t id, int& dst)
{
    Property* p;
    if (l && l->GetProperty(id, &p) && p->mType == 9)
        dst = *p->GetInt();
}
static inline void LoadFloat(cPropertyList* l, uint32_t id, float& dst)
{
    Property* p;
    if (l && l->GetProperty(id, &p) && p->mType == 13)
        dst = *p->GetFloat();
}
static inline float GetFloatDef(cPropertyList* l, uint32_t id, float def)
{
    Property* p;
    if (l && l->GetProperty(id, &p) && p->mType == 13)
        return *p->GetFloat();
    return def;
}

// EA float->int64 helper: fistp in the current (round-to-nearest) mode.
inline __int64 FloatToInt64(float f)
{
    __declspec(align(8)) __int64 result;
    __asm fld   f
    __asm fistp result
    return result;
}

// ---- EASTL pieces --------------------------------------------------------------------------
struct RBAnchor {
    void* right;
    void* left;
    void* parent;
    int color;
    RBAnchor() : left(0), parent(0), color(0) {}
};
struct RBMap {
    uint32_t mCompare;
    RBAnchor mAnchor;
    int mnSize;
    RBMap()
    {
        mAnchor.right = &mAnchor;
        mAnchor.left = &mAnchor;
        mAnchor.parent = 0;
        *(char*)&mAnchor.color = 0;
        mnSize = 0;
    }
};

struct UniverseAction;
struct UniverseEvent;
struct ActionVector {
    UniverseAction** mpBegin;
    UniverseAction** mpEnd;
    UniverseAction** mpCapacity;
    void DoInsertValue(UniverseAction** pos, UniverseAction* const& v);   // 0x00b96600
    void push_back(UniverseAction* const& v)
    {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) UniverseAction*(v);
        else
            DoInsertValue(mpEnd, v);
    }
};
struct EventMap {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    EventMap() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ActionVector& operator[](UniverseEvent* const& key);       // 0x01015410
};

// ---- inline-constructed event / action sub-objects -----------------------------------------
struct V4  { virtual void f(); };                                         // vptr only
struct V8  { virtual void f(); int pad; };                                // vptr + unwritten word
struct E10 { virtual void f(); int pad; int a; int b; E10() : a(0), b(0) {} };
struct E08 { virtual void f(); int a; E08() : a(0) {} };
struct EF  { virtual void f(); float a; EF() : a(0.0f) {} };
struct EFI { virtual void f(); float a; int b; EFI() : a(0.0f), b(0) {} };
struct GrobWarAttackEvent {
    virtual void f();
    int a; float x, y, z; int b;
    GrobWarAttackEvent() : a(0), b(0) { x = 0.0f; y = 0.0f; z = 0.0f; }
    void Init();                                                          // 0x0100e150
};

struct GonzagoA { virtual void a0(); int padA; };
struct GonzagoB { virtual void b0(); int padB; };
struct cGonzagoSimulator : GonzagoA, GonzagoB {
    cGonzagoSimulator();                                                  // 0x00b5b6c0
};

struct cSimulatorUniverse : cGonzagoSimulator {
    PropListPtr mTuning;           // +0x10
    int m14;                       // +0x14
    RBMap mTimeOfLastUpdate;       // +0x18 (anchor +0x1c)
    int pad30;
    V4 ev34;                       // +0x34
    V8 ac38;                       // +0x38
    E10 ev40;                      // +0x40
    V8 ac50;                       // +0x50
    E10 ev58;                      // +0x58
    V8 ac68;                       // +0x68
    E10 ev70;                      // +0x70
    V8 ac80;                       // +0x80
    E10 ev88;                      // +0x88
    V8 ac98;                       // +0x98
    E10 eva0;                      // +0xa0
    V4 acb0;                       // +0xb0
    GrobWarAttackEvent evb4;       // +0xb4
    V4 accc;                       // +0xcc
    E08 evd0;                      // +0xd0
    V4 acd8;                       // +0xd8
    EF evdc;                       // +0xdc
    V4 ace4;                       // +0xe4
    EFI eve8;                      // +0xe8
    V4 acf4;                       // +0xf4
    EventMap mEventList;           // +0xf8
    int pad104[3];
    int m110;                      // +0x110
    int m114;                      // +0x114
    int m118;                      // +0x118
    unsigned m11c;                 // +0x11c
    int m120;                      // +0x120
    unsigned m124;                 // +0x124
    int m128, m12c, m130;
    int m134, m138;
    float f13c, f140, f144, f148, f14c, f150, f154;
    int m158;
    unsigned m15c;
    float f160, f164, f168, f16c, f170, f174, f178;
    RBMap mAwarenessValue;         // +0x17c (anchor +0x180)
    int pad194[1];
    RBMap mThird;                  // +0x198 (anchor +0x19c)
    int pad1ac;

    cSimulatorUniverse();
    virtual void a0();
    virtual void b0();
};

extern cSimulatorUniverse* gUniverse;                                     // 0x016dc798

// @ 0x010154f0  SP::cSimulatorUniverse::cSimulatorUniverse
cSimulatorUniverse::cSimulatorUniverse()
    : m14(0), m110(-1), m114(0), m120(2), m124(0), m128(0), m12c(0), m130(0),
      f13c(0.0f), f140(0.0f), f144(0.0f), f148(0.0f), f150(0.0f), f154(0.0f), m158(0), m15c(0)
{
    gUniverse = this;
    IPropertyManager* mgr = PropertyManager();
    mgr->GetPropertyList(0x3e9793b5, 0x2ae0c7e, mTuning.AsPPTypeParam());
    {
        Property* p;
        cPropertyList* t = mTuning.mpObject;
        if (t && t->GetProperty(0x4a4b35f, &p) && p->mType == 9)
            m124 = *p->GetInt();
    }
    m124 = m124 * 1000;
    LoadInt(mTuning.mpObject, 0x4a5e5bb, m118);
    {
        float v = 0.0f;
        LoadFloat(mTuning.mpObject, 0x4a5e5bc, v);
        v *= 1000.0f;
        m11c = (unsigned)FloatToInt64(v);
    }
    LoadFloat(mTuning.mpObject, 0x4a5e5bd, f13c);
    LoadFloat(mTuning.mpObject, 0x4a5e5be, f140);
    LoadFloat(mTuning.mpObject, 0x4a5e5bf, f144);
    LoadFloat(mTuning.mpObject, 0x4a5e5c0, f148);
    LoadFloat(mTuning.mpObject, 0x4a5e5d0, f14c);
    LoadFloat(mTuning.mpObject, 0x4a5e5c1, f154);
    LoadFloat(mTuning.mpObject, 0x4a5e5d1, f150);
    {
        float v = 0.0f;
        LoadFloat(mTuning.mpObject, 0x4a5e5d2, v);
        v *= 1000.0f;
        m15c = (unsigned)FloatToInt64(v);
    }
    LoadFloat(mTuning.mpObject, 0x55b9da9, f160);
    LoadFloat(mTuning.mpObject, 0x55b9da7, f164);
    LoadFloat(mTuning.mpObject, 0x55b9da5, f168);
    LoadFloat(mTuning.mpObject, 0x55b9da4, f16c);
    LoadFloat(mTuning.mpObject, 0x55b9da2, f170);
    LoadFloat(mTuning.mpObject, 0x55b9d9f, f178);
    LoadFloat(mTuning.mpObject, 0x55b9d9c, f174);
    evb4.Init();
    {
        UniverseAction* a = (UniverseAction*)&ac38;
        UniverseEvent* e = (UniverseEvent*)&ev34;
        mEventList[e].push_back(a);
    }
    {
        UniverseAction* a = (UniverseAction*)&ac50;
        UniverseEvent* e = (UniverseEvent*)&ev40;
        mEventList[e].push_back(a);
    }
    {
        UniverseAction* a = (UniverseAction*)&ac68;
        UniverseEvent* e = (UniverseEvent*)&ev58;
        mEventList[e].push_back(a);
    }
    {
        UniverseAction* a = (UniverseAction*)&ac80;
        UniverseEvent* e = (UniverseEvent*)&ev70;
        mEventList[e].push_back(a);
    }
    {
        UniverseAction* a = (UniverseAction*)&ac98;
        UniverseEvent* e = (UniverseEvent*)&ev88;
        mEventList[e].push_back(a);
    }
    {
        UniverseAction* a = (UniverseAction*)&acb0;
        UniverseEvent* e = (UniverseEvent*)&eva0;
        mEventList[e].push_back(a);
    }
    {
        UniverseAction* a = (UniverseAction*)&accc;
        UniverseEvent* e = (UniverseEvent*)&evb4;
        mEventList[e].push_back(a);
    }
    {
        UniverseAction* a = (UniverseAction*)&ace4;
        UniverseEvent* e = (UniverseEvent*)&evdc;
        mEventList[e].push_back(a);
    }
    {
        UniverseAction* a = (UniverseAction*)&acf4;
        UniverseEvent* e = (UniverseEvent*)&eve8;
        mEventList[e].push_back(a);
    }
}
