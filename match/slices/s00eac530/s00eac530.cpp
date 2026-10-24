// Slice s00eac530 -- SP::Audio::cPlayerCityMusic (the city music player) methods
// plus the two free helpers that walk its 0x6c-stride element arrays.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <math.h>

#define PV(n) virtual void v##n();

// the audio system singleton (obtained via EA::Audio::GetSystemAT)
struct SysAT {
    PV(0) PV(1) PV(2) PV(3) PV(4)
    virtual void Slot14(uint32_t, void**, uint32_t);   // 0x14
    PV(6) PV(7) PV(8) PV(9) PV(10) PV(11) PV(12) PV(13)
    virtual void Slot38(int);                    // 0x38
    virtual void Slot3c(int, float);             // 0x3c
    virtual void Slot40(int, int);               // 0x40
    PV(17) PV(18) PV(19) PV(20) PV(21)
    virtual void Slot58();                       // 0x58
};

// ---------------------------------------------------------------------------
// property objects and the inlined property-read helpers (the same idiom as
// the sibling slices s004063d0 / s00f0cad0)
// ---------------------------------------------------------------------------
struct cProperty {
    uint32_t  pad0[4];                           // +0x00
    uint16_t  pad10;                             // +0x10
    uint16_t  mnType;                            // +0x12
    float*    GetValueFloat();                   // 0x0041ea70
    uint32_t* GetValueUInt32();                  // 0x0041ea00
    bool*     GetValueBool();                    // 0x0041e920
};

struct cPropertyList {
    virtual int  AddRef();                       // +0x00
    virtual int  Release();                      // +0x04
    virtual void f8();  virtual void fc();       // +0x08
    virtual void f10(); virtual void f14(); virtual void f18(); virtual void f1c();
    virtual void f20();
    virtual bool Query(uint32_t id, void* out);  // +0x24
};

// the object handed back by SysAT::Slot14
struct IPropsObj {
    virtual int  AddRef();                       // +0x00
    virtual int  Release();                      // +0x04
    virtual void f8();  virtual void fc(); virtual void f10(); virtual void f14();
    virtual void f18(); virtual void f1c(); virtual void f20();
    virtual bool Query(uint32_t id, void* out);  // +0x24
    virtual void f28(); virtual void f2c();
    virtual bool QueryFloat(uint32_t id, void* out);   // +0x30
};

// the factory handed back by 0x008de1a0
struct IPropertyMgr {
    virtual int  AddRef();                       // +0x00
    virtual int  Release();                      // +0x04
    virtual void f8();                           // +0x08
    virtual bool Get2(void* a, void* b, int, int, int, int);   // +0x0c
};

void* GetEapdObjectError();                      // 0x008de1a0 (cdecl)
void  PropertyPairRead(void* a, void* b, void* c);       // 0x00eed0b0 (cdecl)
bool  SP_GetPropertyAsVector3(void* list, uint32_t id, void* out);  // 0x006a1110
bool  SP_GetPropertyAsFloat(void* list, uint32_t id, void* out);    // 0x0040cf10

inline bool ReadFloat(cPropertyList* list, uint32_t id, float& value)
{
    cProperty* prop;
    if (list && list->Query(id, &prop) && prop->mnType == 0xd) {
        value = *prop->GetValueFloat();
        return true;
    }
    return false;
}

inline bool ReadUInt(cPropertyList* list, uint32_t id, uint32_t& value)
{
    cProperty* prop;
    if (list && list->Query(id, &prop) && prop->mnType == 0xa) {
        value = *prop->GetValueUInt32();
        return true;
    }
    return false;
}

inline bool ReadBool(cPropertyList* list, uint32_t id, uint8_t& value)
{
    cProperty* prop;
    if (list && list->Query(id, &prop) && prop->mnType == 1) {
        value = (uint8_t)*prop->GetValueBool();
        return true;
    }
    return false;
}

SysAT* GetSystemAT();                            // 0x00a206f0 (cdecl)
void   SetGlobalProperty(int, float);            // 0x005ca880 (cdecl)
void   PauseSound(void*, int);                   // 0x00a37290 (cdecl)

extern int32_t g_1488414[];                      // 0x01488414  global property id table

// EA's floating-point helper: truncating float->int on an SSE1-only target
// (cl would otherwise emit a __ftol2_sse call).  asm block of 7 instructions.
#pragma warning(disable : 4035)
__forceinline int FloorToInt(float f)
{
    __asm {
        movss    xmm0, f
        cvtss2si eax, xmm0
        cvtsi2ss xmm1, eax
        mov      ecx, eax
        sub      ecx, 1
        ucomiss  xmm0, xmm1
        cmovb    eax, ecx
    }
}

// the 0x38-byte object at cPlayerCityMusic+0x160 (a stopwatch that is also used as
// a direct property list)
struct Stopwatch160 {
    uint32_t m0;                                 // +0x00  (abs +0x160)
    uint32_t m4;                                 // +0x04  (abs +0x164)
    float    m8;                                 // +0x08  (abs +0x168)
    uint32_t mc;                                 // +0x0c  (abs +0x16c)
    float    m10;                                // +0x10  (abs +0x170)
    float    m14;                                // +0x14  tempo multiplier
    float    m18;                                // +0x18  (abs +0x178)
    float    m1c;                                // +0x1c  (abs +0x17c)
    float    m20;                                // +0x20  (abs +0x180)
    float    m24;                                // +0x24  (abs +0x184)
    float    m28;                                // +0x28  (abs +0x188)
    float    m2c;                                // +0x2c  (abs +0x18c, vector3 x)
    float    m30;                                // +0x30  (abs +0x190)
    float    m34;                                // +0x34  (abs +0x194)
    void     Start();                            // 0x00435480
    int64_t  GetElapsedTimeFloat();              // 0x0093a3a0
    void     SetBoolProperty();                  // 0x0093a2e0
};

// the creature object returned by cPlayerCityMusic::GetCreature() (only the
// single field the voice reaches into is named)
struct cCreatureBase {
    char  pad000[0x1e0];
    float m1e0;                                  // +0x1e0
};

namespace SP {
namespace Audio {

struct cPlayerCityMusic {
    char         pad000[0x100];
    uint8_t      m100;                           // +0x100  paused flag
    uint8_t      m101;                           // +0x101
    char         pad102[0x108 - 0x102];
    void*        mp108;                          // +0x108  property scratch
    void*        mp10c;                          // +0x10c  sound handle
    char         pad110[0x118 - 0x110];
    uint32_t     m118;                           // +0x118  sound id
    cPropertyList* mp11c;                        // +0x11c  property list
    uint8_t      m120;                           // +0x120
    bool         m121;                           // +0x121
    char         pad122[0x123 - 0x122];
    uint8_t      m123;                           // +0x123
    char         pad124[0x127 - 0x124];
    uint8_t      m127;                           // +0x127
    char         pad128[0x12c - 0x128];
    float        m12c;                           // +0x12c
    float        m130;                           // +0x130
    float        m134;                           // +0x134
    float        m138;                           // +0x138
    float        m13c;                           // +0x13c
    int32_t      m140;                           // +0x140
    float        m144;                           // +0x144
    float        m148;                           // +0x148
    char         pad14c[0x150 - 0x14c];
    float        m150;                           // +0x150  accumulated duration
    float        m154;                           // +0x154
    char         pad158[0x160 - 0x158];
    Stopwatch160 m160;                           // +0x160
    float*       mp198;                          // +0x198  per-slot value array
    char         pad19c[0x1a4 - 0x19c];
    uint32_t     m1a4;                           // +0x1a4
    char         pad1a8[0x1c4 - 0x1a8];
    uint32_t     m1c4;                           // +0x1c4
    uint32_t     m1c8;                           // +0x1c8
    char         pad1cc[0x1e0 - 0x1cc];
    float*       mp1e0;                          // +0x1e0  note-duration array

    cCreatureBase* GetCreature();                // 0x006c0200
    void        CommitAllProperties();           // 0x00eab900

    void        FUN_00eac530();                  // 0x00eac530
    void        SetPosition(float*);             // 0x00eacd50
    bool        SelectRhythm(uint32_t);          // 0x00eacdb0
    bool        SelectInstrument(uint32_t);      // 0x00eace30
    void        PlayMelody(uint32_t);            // 0x00eaceb0
    void        PlayNote(uint32_t);              // 0x00eacf10
    void        FUN_00eacf70(uint8_t);           // 0x00eacf70
    void        Pause(uint8_t);                  // 0x00eacff0
    long double FUN_00ead040();                  // 0x00ead040
    void        FUN_00ead090(int, float);        // 0x00ead090
    void        SetNoteDuration(int, float);     // 0x00ead0c0
};

}  // namespace Audio
}  // namespace SP

// one 0x6c-byte element of the city-music element arrays
struct Elem6c {
    virtual void V0();
    virtual void V1();
    virtual void Slot8(int);                     // +0x008
    char pad[0x6c - 0x04];
};

// ===========================================================================
// @ 0x00eac530
// ===========================================================================
void SP::Audio::cPlayerCityMusic::FUN_00eac530()
{
    PropertyPairRead(&mp108, &m160.m10, &m160.m14);

    IPropertyMgr* mgr = (IPropertyMgr*)GetEapdObjectError();
    if (mp11c != 0) {
        cPropertyList* old = mp11c;
        mp11c = 0;
        old->Release();
    }
    mgr->Get2(&mp108, &mp11c, 0, 0, 0, 0);

    if (mp11c != 0) {
        ReadUInt (mp11c, 0x6dba9e07, m1a4);
        ReadFloat(mp11c, 0xcce9e754, m160.m28);
        SP_GetPropertyAsVector3(mp11c, 0xb14ca983, &m160.m2c);
        SP_GetPropertyAsVector3(mp11c, 0x4888547a, &mp198);
        ReadFloat(mp11c, 0x8d3ef5d0, m160.m18);
        ReadFloat(mp11c, 0x4102db36, m160.m1c);
        ReadFloat(mp11c, 0x0eb4af2d, m160.m20);
        ReadFloat(mp11c, 0x298a6aff, m160.m24);
        ReadUInt (mp11c, 0xb6878619, m118);
        ReadBool (mp11c, 0xc125ef88, m120);
        m121 = ReadFloat(mp11c, 0x66ef9aba, m138)
            && ReadFloat(mp11c, 0xe4dd1818, m13c)
            && SP_GetPropertyAsFloat(mp11c, 0x0cd928a9, &m140);
        if (m121) {
            ReadFloat(mp11c, 0x7d383db4, m144);
            ReadFloat(mp11c, 0x61709942, m148);
            m148 = m148 + 1.0f;
        }
        ReadFloat(mp11c, 0xc9a583f6, m160.m8);
        ReadFloat(mp11c, 0xc9a583f6, m160.m8);
        ReadFloat(mp11c, 0xddd19567, m150);
        ReadFloat(mp11c, 0xd861c661, m154);
    }

    IPropsObj* local = 0;
    SysAT* sys = GetSystemAT();
    if (sys != 0) {
        if (local != 0) {
            IPropsObj* old = local;
            local = 0;
            old->Release();
        }
        sys->Slot14(m118, (void**)&local, 0x21407ee);
    }
    if (local != 0) {
        local->QueryFloat(0xf616b72, &m130);
        local->QueryFloat(0x3593710, &m134);
        local->Query(0x6dd08218, &m127);
    }
    if (m127) {
        if (m120)
            m120 = 0;
    }
    if (m127) {
        m12c = m134;
        m123 = 1;
    } else {
        m12c = m130;
    }
    ReadBool(mp11c, 0xda75d09a, m123);
    if (local != 0)
        local->Release();
}

// ===========================================================================
// The music "voice" sub-object embedded at cPlayerCityMusic + 0x34.  It is a
// polymorphic object in its own right (its vtable pointer sits at +0x00); the
// containing cPlayerCityMusic begins 0x34 bytes below it.
// ===========================================================================
struct cSPVector3 { float x, y, z; };

struct cSPTransform {
    float m[12];                                     // opaque 0x30-byte transform
    cSPTransform();                                  // 0x00409930
    void SetA(const cSPVector3* v);                  // 0x006ba800
    void TransformVector(const cSPVector3* v);       // 0x0049d640
};

float*     FUN_0059aed0(float* out, const void* key, uint32_t value);  // 0x0059aed0
cSPVector3* normalized_safe(cSPVector3* out, const cSPVector3* in);    // 0x00449c20
float      CeilF(float x);                                             // 0x0083ce70
void       RecordEvent4(uint32_t group, uint32_t id, float v, uint32_t p);  // 0x00435f40

struct g16c7aa4_t { int32_t pad[0xcc / 4]; int32_t mCC; };
extern g16c7aa4_t* g_16c7aa4;                                          // 0x016c7aa4
extern char        g_16c71e8[];                                        // 0x016c71e8
extern float       g_15a9108;                                          // 0x015a9108

struct CityMusicVoice {
    // --- vtable (the slots at +0x2c and +0x5c are the two used below) ------
    virtual void         V00();
    virtual void         V04();
    virtual void         V08();
    virtual void         V0c();
    virtual void         V10();
    virtual void         V14();
    virtual void         V18();
    virtual void         V1c();
    virtual void         V20();
    virtual void         V24();
    virtual void         V28();
    virtual cSPVector3*  V2c(float t);               // +0x2c
    virtual void         V30();
    virtual void         V34();
    virtual void         V38();
    virtual void         V3c();
    virtual void         V40();
    virtual void         V44();
    virtual void         V48();
    virtual void         V4c();
    virtual void         V50();
    virtual void         V54();
    virtual void         V58();
    virtual cSPVector3*  V5c(cSPVector3* out);       // +0x5c

    // --- data -------------------------------------------------------------
    void        func58h(uint32_t id);                // 0x00c886d0
    void        FUN_00eaca50(uint32_t id);           // 0x00eaca50
    char        pad04[0xe0 - 0x04];
    void*       mpE0;                                // +0xe0  pending event object
    char        padE4[0xed - 0xe4];
    uint8_t     mEd;                                 // +0xed
    char        padEE[0xf4 - 0xee];
    uint8_t     mF4;                                 // +0xf4  position initialised
    char        padF5[0xf7 - 0xf5];
    uint8_t     mF7;                                 // +0xf7
    char        padF8[0x104 - 0xf8];
    float       m104;                                // +0x104
    char        pad108[0x110 - 0x108];
    float       m110;                                // +0x110
    float       m114;                                // +0x114
    float       m118;                                // +0x118
    float       m11c;                                // +0x11c
    float       m120;                                // +0x120
    cSPVector3  mV124;                               // +0x124
};

// ===========================================================================
// @ 0x00eaca50
// ===========================================================================
void CityMusicVoice::FUN_00eaca50(uint32_t id)
{
    func58h(id);                                     // 0x00c886d0

    if (mF7 == 0)
        return;
    if (g_16c7aa4->mCC != 1)
        return;

    SP::Audio::cPlayerCityMusic* owner = (SP::Audio::cPlayerCityMusic*)((char*)this - 0x34);
    cCreatureBase* creature = owner->GetCreature();  // 0x006c0200
    if (creature == 0)
        return;

    float range;
    if (mEd != 0)
        range = m114 - m110;
    else
        range = m120 - m11c;
    if (range == 0.0f)
        return;

    // the vector this voice samples its position into (reused by both halves)
    cSPVector3 v;

    if (mF4 == 0) {
        float* p = FUN_0059aed0(&v.x, g_16c71e8, id);
        mV124.x = p[0];
        mV124.y = p[1];
        mV124.z = p[2];

        if (mEd != 0) {
            if (creature->m1e0 == 1.0f)
                creature->m1e0 = m104;
        }
        cSPTransform xf;                             // 0x00409930
        float lo, hi;
        if (mEd != 0) {
            lo = m110;
            hi = m114;
        } else {
            lo = m11c;
            hi = m120;
        }
        cSPVector3* n = normalized_safe(&v,
            V2c((creature->m1e0 - lo) * g_15a9108 / (hi - lo)));   // 0x00449c20
        xf.SetA(n);                                  // 0x006ba800
        xf.TransformVector(&mV124);                  // 0x0049d640
        mF4 = 1;
    }

    cSPVector3* q = V5c(&v);                         // vtable +0x5c
    long double dot = mV124.x * (long double)q->x
                    + mV124.y * (long double)q->y
                    + mV124.z * (long double)q->z;
    float t = (float)(acos(dot) / g_15a9108);        // 0x011e08c8

    float lo, hi;
    if (mEd != 0) {
        lo = m110;
        hi = m114;
    } else {
        lo = m11c;
        hi = m120;
    }
    t = lo + (hi - lo) * t;
    if (t == creature->m1e0)
        return;
    creature->m1e0 = t;

    if (mEd == 0) {
        void* ev = mpE0;
        if (ev == 0)
            return;
        RecordEvent4((uint32_t)ev, 0x71bc3009, t, 0);   // 0x00435f40
    } else {
        long double c = CeilF(t);                    // 0x0083ce70
        if (m118 == c)
            return;
        m118 = (float)c;
        owner->CommitAllProperties();                // 0x00eab900
    }
}

// ===========================================================================
// @ 0x00eacd50
// ===========================================================================
void SP::Audio::cPlayerCityMusic::SetPosition(float* p)
{
    if (mp10c != 0) {
        SetGlobalProperty(0x40ef6b1b, p[0]);
        SetGlobalProperty(0x40ef6b1a, p[1]);
        SetGlobalProperty(0x40ef6b19, p[2]);
    }
}

// ===========================================================================
// @ 0x00eacdb0
// ===========================================================================
bool SP::Audio::cPlayerCityMusic::SelectRhythm(uint32_t v)
{
    if (m1c4 != 0)
        SetGlobalProperty(0x7df75892, (float)m1c4);

    bool changed = (m1c4 != v);
    m1c4 = changed ? v : 0;
    if (m1c4 != 0)
        SetGlobalProperty(0xec66947a, (float)m1c4);
    return changed;
}

// ===========================================================================
// @ 0x00eace30
// ===========================================================================
bool SP::Audio::cPlayerCityMusic::SelectInstrument(uint32_t v)
{
    bool changed = (m1c8 != v);
    if (!changed)
        SetGlobalProperty(0xcbc8ae11, (float)m1c8);

    m1c8 = changed ? v : 0;
    if (m1c8 != 0)
        SetGlobalProperty(0xf7db2353, (float)m1c8);
    return changed;
}

// ===========================================================================
// @ 0x00eaceb0
// ===========================================================================
void SP::Audio::cPlayerCityMusic::PlayMelody(uint32_t a)
{
    SysAT* s = GetSystemAT();
    if (s != 0) {
        s->Slot38(0x3cdd1a9);
        s->Slot40(0x34753a7, 0x4b64ae20);
        s->Slot3c(0x34753aa, (float)a);
        s->Slot58();
    }
}

// ===========================================================================
// @ 0x00eacf10
// ===========================================================================
void SP::Audio::cPlayerCityMusic::PlayNote(uint32_t a)
{
    SysAT* s = GetSystemAT();
    if (s != 0) {
        s->Slot38(0x3cdd1a9);
        s->Slot40(0x34753a7, 0x4405c487);
        s->Slot3c(0x34753aa, (float)a);
        s->Slot58();
    }
}

// ===========================================================================
// @ 0x00eacf70
// ===========================================================================
void SP::Audio::cPlayerCityMusic::FUN_00eacf70(uint8_t v)
{
    if (m101 != v)
        SetGlobalProperty(0x6c3a5e1c, (float)v);
    m101 = v;
}

// ===========================================================================
// @ 0x00eacff0
// ===========================================================================
void SP::Audio::cPlayerCityMusic::Pause(uint8_t p)
{
    if (mp10c != 0 && p != m100) {
        PauseSound(mp10c, p);
        m100 = p;
        if (p != 0)
            m160.SetBoolProperty();
        else
            m160.Start();
    }
}

// ===========================================================================
// @ 0x00ead040
// ===========================================================================
long double SP::Audio::cPlayerCityMusic::FUN_00ead040()
{
    Stopwatch160* sw = &m160;
    int64_t t = sw->GetElapsedTimeFloat();
    long double e = (long double)t;
    e = e * sw->m14;
    float f = (float)e;
    int i = FloorToInt(f);
    return e - (long double)i;
}

// ===========================================================================
// @ 0x00ead090
// ===========================================================================
void SP::Audio::cPlayerCityMusic::FUN_00ead090(int idx, float v)
{
    mp198[idx] = v;
    SetGlobalProperty(g_1488414[idx], v);
}

// ===========================================================================
// @ 0x00ead0c0
// ===========================================================================
void SP::Audio::cPlayerCityMusic::SetNoteDuration(int idx, float v)
{
    float* slot = mp1e0 + idx;
    m150 = m150 + (v - *slot);
    *slot = v;

    SysAT* s = GetSystemAT();
    if (s != 0) {
        s->Slot38(0x3cdd1a9);
        s->Slot40(0x34753a7, 0xe7b72656);
        s->Slot3c(0x34753aa, (float)(uint32_t)idx);
        s->Slot58();
    }

    s = GetSystemAT();
    if (s != 0) {
        s->Slot38(0x3cdd1a9);
        s->Slot40(0x34753a7, 0xc309bcc9);
        s->Slot3c(0x34753aa, v);
        s->Slot58();
    }
}

// ===========================================================================
// @ 0x00eacfb0
// ===========================================================================
Elem6c* FUN_00eacfb0(Elem6c* a, Elem6c* b, Elem6c* c)
{
    while (a != b) {
        a->Slot8(0);
        a += 1;
        c += 1;
    }
    return c;
}