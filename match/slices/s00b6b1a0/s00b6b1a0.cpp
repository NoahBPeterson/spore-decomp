// Slice s00b6b1a0 (batch gold6): SP conversation-target / creature display
// subtitle + rollover helpers.
//
//   00b6b1a0  builds a tooltip charge text and drives two 5-window progress
//             bars plus two named windows (a range caption and a colour swatch)
//   00b6b4c0  pick the creature rollover subtitle (~Pet / ~Baby / ~Epic /
//             ~MiniBoss / ~Alpha / species UiName)
//   00b6b810  same subtitle selection driven by the citizen archetype
//   00b6ba50  "convincing text" for a hatchery/creature id (cString lookup,
//             falling back to an empty EStr)
//
// Flags: /O2 /MD /Gy /TP
//
// The migrated headers carry the 2008 dev-PDB layout, which is shifted relative
// to retail, so the stub classes below carry role-named fields at the retail
// offsets read straight off the disassembly.

#include "types.h"

#pragma warning(disable : 4100)

typedef unsigned int  u32;
typedef unsigned char u8;
typedef unsigned short u16;

// ---------------------------------------------------------------------------
// fixed globals
// ---------------------------------------------------------------------------
extern wchar_t       gEmptyString16;    // 0x01667bac eastl::gEmptyString16 (L"")
extern const wchar_t gStr013ec468;      // 0x013ec468 default text key/name
extern float         kFloat100;         // 0x013ec4d0 100.0f
extern float         kFloat50;          // 0x013f1cac  50.0f

struct cToolGate;
extern cToolGate* gToolGate;            // 0x0169d3c8

// ---------------------------------------------------------------------------
// external free functions
// ---------------------------------------------------------------------------
struct cTextRoot;

void EA_Locale_SetNumberString(int value, int sign, wchar_t* buf, int count);  // 0x00881ae0
void SP_DeleteArray(void* p);                                                  // 0x00f47380 operator delete[]
cTextRoot* FUN_0067de40();                                                     // 0x0067de40

struct cToolGate {
    void FUN_00cfe780(void* obj);       // 0x00cfe780
};

// ---------------------------------------------------------------------------
// eastl::basic_string<wchar_t>
// ---------------------------------------------------------------------------
struct WString {
    const wchar_t* mBegin;   // +0x00
    const wchar_t* mEnd;     // +0x04
    const wchar_t* mCap;     // +0x08

    void assign(const wchar_t* b, const wchar_t* e);   // 0x00423650
    void RangeInitialize(const wchar_t* s);            // 0x00579a90
    ~WString() {
        if ((((u32)((const char*)mCap - (const char*)mBegin)) & 0xfffffffeu) > 2 && mBegin != 0)
            delete[] (wchar_t*)mBegin;
    }
};

// ---------------------------------------------------------------------------
// SP::cString  (a.k.a. cString_s006b_47a0)
// ---------------------------------------------------------------------------
struct cString {
    u32 m00;        // +0x00
    u32 m04;        // +0x04
    u32 m08;        // +0x08
    u32 m0c;        // +0x0c
    u16 m10;        // +0x10
    u16 m12;        // +0x12

    cString();                                         // 0x006b5060
    cString(u32 a, u32 b, const wchar_t* text);        // 0x006b5770
    u8  Load(u32 a, u32 b, int c);                     // 0x006b54b0
    const wchar_t* GetText();                          // 0x006b55c0
    ~cString();                                        // 0x006b5240
};

// ---------------------------------------------------------------------------
// EStr: the 0x54-byte wide externalised string returned through a hidden
// return buffer (arg0) as MSVC does for large aggregates.
// ---------------------------------------------------------------------------
struct EStr {
    wchar_t* mBegin;    // +0x00
    wchar_t* mEnd;      // +0x04
    wchar_t* mCap;      // +0x08
    u32      m0c;       // +0x0c
    wchar_t* m10;       // +0x10
                        // +0x14: 0x40-byte inline buffer

    EStr* Construct(const wchar_t* text);              // 0x006743f0
    EStr* Init(const wchar_t* a, const wchar_t* b);    // 0x00672750
};

// ---------------------------------------------------------------------------
// text-object hierarchy used by the subtitle formatter
// ---------------------------------------------------------------------------
struct cTextObj;
struct cTextRoot {
    virtual void      r00();
    virtual void      r04();
    virtual void      r08();
    virtual void      r0c();
    virtual void      r10();
    virtual void      r14();
    virtual void      r18();
    virtual void      r1c();
    virtual cTextObj* r20();                            // +0x20
};

struct cTextObj {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30(cString* out, u32* key, int flag); // +0x30
};

// ---------------------------------------------------------------------------
// UI window (only the four slots these helpers touch are meaningful)
// ---------------------------------------------------------------------------
struct cUIWindow {
    virtual void       w00();
    virtual void       w04(float f);                    // +0x04
    virtual void       w08();
    virtual cUIWindow* w0c(u32 key);                    // +0x0c
    virtual void       w10();
    virtual void       w14();
    virtual void       w18();
    virtual void       w1c();
    virtual void       w20();
    virtual void       w24();
    virtual void       w28();
    virtual void       w2c();
    virtual void       w30();
    virtual void       w34();
    virtual void       w38();
    virtual void       w3c();
    virtual void       w40();
    virtual void       w44();
    virtual void       w48();
    virtual void       w4c();
    virtual void       w50();
    virtual void       w54();
    virtual void       w58();
    virtual void       w5c(u32 color);                 // +0x5c
    virtual void       w60();
    virtual void       w64();
    virtual void       w68();
    virtual void       w6c();
    virtual void       w70();
    virtual void       w74();
    virtual void       w78();
    virtual void       w7c();
    virtual void       w80(const wchar_t* text);        // +0x80
};

struct cSPUILayout {
    cUIWindow* FindWindowByID(u32 id, int flag);        // 0x008105b0
};

// ---------------------------------------------------------------------------
// object handed to the text-command helpers
// ---------------------------------------------------------------------------
struct cObjBase {                                       // anything with slot +0x0c
    virtual void  b00();
    virtual void  b04();
    virtual void  b08();
    virtual void* b0c(u32 key);                         // +0x0c
};

struct cSpeciesProfile {
    void GetUiName(WString* out);                       // 0x004da330
};

struct cSpeciesInfo {
    u8  pad000[0x15c];
    int m15c;                                           // +0x15c
};

struct cCreature {                                      // cSPCreatureCitizen-ish
    virtual void  c00();
    virtual void  c04();
    virtual void  c08();
    virtual void* c0c(u32 key);                         // +0x0c
    u8  pad010[0xb20 - 0x10];
    cSpeciesProfile* mSpecies;                          // +0xb20
    u8  padb24[0xb38 - 0xb24];
    WString mName;                                      // +0xb38
    u8  padb44[0xb58 - 0xb44];
    u8  mFlagsB58;                                      // +0xb58

    u8      FUN_00c0b770();                             // 0x00c0b770
    u8      IsLeader();                                 // 0x00c232d0
    u8      Flag388();                                  // 0x00c0c0e0
    u8      Flag389();                                  // 0x00c0c100
    int     FUN_00c22dc0();                             // 0x00c22dc0
    cSpeciesInfo* FUN_00c04590();                       // 0x00c04590  Get()
};

// the object FUN_00b6b1a0 drives (holds the layout + a tooltip window)
struct cConvSelf {
    u8 pad000[0x50];
    cSPUILayout* mLayout;                               // +0x50
    u8 pad054[0xa8 - 0x54];
    cUIWindow*   mWnd;                                  // +0xa8
};

// the target FUN_00b6b1a0 walks (flag counts + a couple of member helpers)
struct cConvTarget {
    u8  pad000[0x668];
    int m668;                                           // +0x668
    int m66c;                                           // +0x66c

    int FUN_00bd8960();                                 // 0x00bd8960
    int FUN_00bd9b70();                                 // 0x00bd9b70
};

// the object v0c() of FUN_00b6ba50 yields
struct cConvInfo {
    u8  pad000[0x64c];
    u32 mId;                                            // +0x64c
};

// ---------------------------------------------------------------------------
// property system stubs (colour lookup in FUN_00b6b1a0)
// ---------------------------------------------------------------------------
struct cPropDesc {
    u8  pad000[0x12];
    u16 mType;                                          // +0x12
    u32* GetUInt();                                     // 0x0041ea00
};

struct cProp {
    virtual void p00();
    virtual void p04();
    virtual void p08();
    virtual void p0c();
    virtual void p10();
    virtual void p14();
    virtual void p18();
    virtual void p1c();
    virtual void p20();
    virtual u8   p24(u32 key, cPropDesc** out);         // +0x24
};

struct AutoRefTarget { virtual void a00(); virtual void Release(); };

struct cPropertyManager {
    virtual void q00();
    virtual void q04();
    virtual void q08();
    virtual void q0c();
    virtual void q10();
    virtual void q14();
    virtual void q18();
    virtual void q1c();
    virtual void q20();
    virtual void q24();
    virtual void q28();
    virtual void q2c(void* owner, u32 key, cProp** out);  // +0x2c
};

struct cPropSetter { void* mPtr; };                     // first field of 0xb8dad0()'s result
struct cPlanet {
    u8 pad000[0x13c];
    cPropSetter* m13c;                                  // +0x13c

    cPropSetter* FUN_00b8dad0();                        // 0x00b8dad0
};
struct cLivingUniverse {
    u8 pad000[0x13c];
    cPlanet* mActivePlanet;                             // +0x13c
};

cPropertyManager* SP_PropertyManager();                 // 0x0067de30
cLivingUniverse*  SP_GetActivePlanet();                 // 0x01021260

// ---------------------------------------------------------------------------
// context tag destroyed by 0x006886e0 after the subtitle has been built
// ---------------------------------------------------------------------------
struct cCtxTag {
    u32 mKey;                                           // +0x00
    void Destroy();                                     // 0x006886e0
};

// ===========================================================================
// @ 0x00b6b1a0 FUN_00b6b1a0
// ===========================================================================
void FUN_00b6b1a0(cConvSelf* self, cConvTarget* obj) {
    WString text;
    text.mBegin = &gEmptyString16;
    text.mEnd   = &gEmptyString16;
    text.mCap   = &gEmptyString16 + 1;

    if (obj != 0) {
        wchar_t buf[0x28];
        buf[0] = 0;
        int n = obj->FUN_00bd8960();
        EA_Locale_SetNumberString(n, n >> 31, buf, 0x28);
        wchar_t* end = buf;
        while (*end != 0)
            ++end;
        text.assign(buf, end);

        int diff = obj->m668 - obj->m66c;

        for (int i = 0; i < 5; ++i) {
            cUIWindow* win = self->mLayout->FindWindowByID(i + 0x4fe1aa0, 1);
            cUIWindow* fill = win->w0c(0x10edf11);
            if (fill != 0) {
                float f = 0.0f;
                if (diff > 0) {
                    if (i < diff)
                        f = kFloat100;
                } else if (diff < 0) {
                    if (i < -diff)
                        f = kFloat50;
                }
                fill->w04(f);
            }
        }

        cUIWindow* caption = self->mLayout->FindWindowByID(0x2cf2f74, 1);
        if (caption != 0) {
            gToolGate->FUN_00cfe780(obj);
            {
                cString s;
                s.Load(0xdc351566, 0x68c71fb, 0);
                {
                    WString cap;
                    cap.mBegin = 0;
                    cap.mEnd   = 0;
                    cap.mCap   = 0;
                    cap.RangeInitialize(s.GetText());
                    caption->w80(cap.mBegin);
                }
            }
        }

        cUIWindow* swatch = self->mLayout->FindWindowByID(0x68da668, 1);
        if (swatch != 0) {
            u32 color = 0xffffffffu;
            cLivingUniverse* universe = SP_GetActivePlanet();
            if (universe != 0) {
                cPlanet* planet = universe->mActivePlanet;
                if (planet != 0) {
                    cPropertyManager* pm = SP_PropertyManager();
                    cProp* prop = 0;
                    cPropSetter* holder = planet->FUN_00b8dad0();
                    pm->q2c(holder->mPtr, 0x34d97fa, &prop);
                    if (prop != 0) {
                        cPropDesc* desc = 0;
                        if (prop->p24(0x58cbb75, &desc) && desc->mType == 0x000a)
                            color = *desc->GetUInt();
                    }
                    if (prop != 0)
                        prop->p04();
                }
            }
            color |= 0xff000000u;
            swatch->w5c(color);
        }

        int count = obj->FUN_00bd9b70();
        for (int i = 0; i < 5; ++i) {
            cUIWindow* win = self->mLayout->FindWindowByID(i + 0x4fe38f0, 1);
            cUIWindow* fill = win->w0c(0x10edf11);
            if (fill != 0) {
                float f = (i < count) ? kFloat100 : 0.0f;
                fill->w04(f);
            }
        }
    }

    self->mWnd->w80(text.mBegin);
}

// ===========================================================================
// @ 0x00b6b4c0 FUN_00b6b4c0
// ===========================================================================
EStr* FUN_00b6b4c0(EStr* result, void* obj) {
    cCreature* creature = 0;
    if (obj != 0)
        creature = (cCreature*)((cObjBase*)obj)->b0c(0xd0036e08);

    cCtxTag ctx;
    ctx.mKey = 0xcaa303ac;

    WString name;
    name.mBegin = &gEmptyString16;
    name.mEnd   = &gEmptyString16;
    name.mCap   = &gEmptyString16 + 1;

    creature->mSpecies->GetUiName(&name);

    if (creature->FUN_00c04590() != 0 && creature->FUN_00c04590()->m15c == 7) {
        cString s(0xad56080c, 0x564e650, L"~Pet");
        cTextObj* t = FUN_0067de40()->r20();
        t->v30(&s, &ctx.mKey, 1);
        result->Construct(s.GetText());
        return result;
    }
    if (creature->FUN_00c0b770() == 0) {
        cString s(0xad56080c, 0xb32fe522, L"~Baby");
        cTextObj* t = FUN_0067de40()->r20();
        t->v30(&s, &ctx.mKey, 1);
        result->Construct(s.GetText());
        return result;
    }
    if (creature->Flag388()) {
        cString s(0xad56080c, 0x595b72b, L"~Epic");
        cTextObj* t = FUN_0067de40()->r20();
        t->v30(&s, &ctx.mKey, 1);
        result->Construct(s.GetText());
        return result;
    }
    if (creature->Flag389()) {
        cString s(0xad56080c, 0x94acb6f7, L"~MiniBoss");
        cTextObj* t = FUN_0067de40()->r20();
        t->v30(&s, &ctx.mKey, 1);
        result->Construct(s.GetText());
        return result;
    }
    if ((creature->mFlagsB58 & 1) != 0) {
        cString s(0xad56080c, 0xf32fe51b, L"~Alpha");
        cTextObj* t = FUN_0067de40()->r20();
        t->v30(&s, &ctx.mKey, 1);
        result->Construct(s.GetText());
        ctx.Destroy();
        return result;
    }

    result->Construct(name.mBegin);
    ctx.Destroy();
    return result;
}

// ===========================================================================
// @ 0x00b6b810 FUN_00b6b810
// ===========================================================================
EStr* FUN_00b6b810(EStr* result, void* obj) {
    cCreature* creature = 0;
    if (obj != 0)
        creature = (cCreature*)((cObjBase*)obj)->b0c(0x4f176642);

    WString name;
    name.mBegin = &gEmptyString16;
    name.mEnd   = &gEmptyString16;
    name.mCap   = &gEmptyString16 + 1;

    u32 key = 0xcb37547d;
    if (&creature->mName != &name)
        name.assign(creature->mName.mBegin, creature->mName.mEnd);

    if (creature->IsLeader()) {
        cString s(0xf71fa311, 0x4bd540b, name.mBegin);
        cTextObj* t = FUN_0067de40()->r20();
        t->v30(&s, &key, 1);
        result->Construct(s.GetText());
    } else if (creature->FUN_00c0b770() == 0) {
        key = 0xcaa303ac;
        cString s(0xad56080c, 0xb32fe522, L"~Baby");
        cTextObj* t = FUN_0067de40()->r20();
        t->v30(&s, &key, 1);
        result->Construct(s.GetText());
    } else {
        u32 sub;
        switch (creature->FUN_00c22dc0()) {
        case 1: sub = 0x567d1d3; break;
        case 2: sub = 0x567d1d2; break;
        case 3: sub = 0x567d1d1; break;
        case 4: sub = 0x567d1d6; break;
        case 5: sub = 0x567d1d7; break;
        case 6: sub = 0x567d1d8; break;
        case 7: sub = 0x567d1d5; break;
        case 8: sub = 0x567d1d4; break;
        case 9: sub = 0x567d1d0; break;
        default:
            result->Construct(name.mBegin);
            goto epilogue;
        }
        {
            cString s(0xf71fa311, sub, name.mBegin);
            cTextObj* t = FUN_0067de40()->r20();
            t->v30(&s, &key, 1);
            result->Construct(s.GetText());
        }
    }

epilogue:
    return result;
}

// ===========================================================================
// @ 0x00b6ba50 FUN_00b6ba50
// ===========================================================================
EStr* FUN_00b6ba50(EStr* result, void* obj) {
    if (obj != 0) {
        cConvInfo* info = (cConvInfo*)((cObjBase*)obj)->b0c(0x4e3faaf);
        if (info != 0) {
            u32 id = info->mId;
            cString s;
            if (s.Load(0x2db6dad3, id, 0)) {
                result->Construct(s.GetText());
                return result;
            }
        }
    }

    result->m10    = (wchar_t*)((char*)result + 0x14);
    wchar_t* base  = result->m10;
    result->mCap   = base + 0x20;
    result->mEnd   = base;
    result->mBegin = base;
    base[0]        = 0;
    result->Init(&gStr013ec468, &gStr013ec468);
    return result;
}