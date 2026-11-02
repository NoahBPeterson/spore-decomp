// src/game/SPGonzago/SPGameBundleView.cpp -- migrated from slice(s) s00e8c120 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPGameBundleView.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cAnimatingCreature.h"
#include "SP/cPlanetModel.h"
#include "SP/cPropertyList.h"

// unnamed retail callees and globals (address in the comment)
extern float kEffectNearDist;      // 0x01581338
extern float kOneF;                // 0x01485720  1.0f
#include <math.h>

// ---- items of slice s00e8c120 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned short     u16;
typedef unsigned int       u32;
void* operator new(u32 size, u32 tag, int a, int b, int c, int d);
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Mat3 { float m[9]; };
struct XformMsg {
    u16   flags;      // +0x00  |2 = rotation, |4 = position
    u16   count;      // +0x02
    Vec3  pos;        // +0x04
    float scale;      // +0x10
    Mat3  rot;        // +0x14
    XformMsg();       // 0x00434040
};
struct Transform {
    u16   flags;
    u16   count;
    Vec3  pos;
    float scale;
    Mat3  rot;
    Transform();                                  // 0x00409930
    void SetB(const Vec3& up, const Vec3& dir);   // 0x006ba840 (MatOwner::SetB)
    void SetPosition(const Vec3& v) { flags |= 4; ++count; pos = v; }
    void SetScale(float s) { scale = s; ++count; }
};
extern float kEffectNearDist;      // 0x01581338
extern u32   kFadeTableA;          // 0x01486408
extern u32   kFadeTableB;          // 0x01486498
u32   FUN_00b3d520(void* p);       // 0x00b3d520
void* FUN_00b3d2b0();              // 0x00b3d2b0
void* FUN_00b3d300();              // 0x00b3d300
void* FUN_00ac79d0(void* p);       // 0x00ac79d0
void* FUN_00bfc5f0(void* p);       // 0x00bfc5f0
bool  FUN_00c0b780(int p);         // 0x00c0b780
bool  FUN_00c8e870(int p);         // 0x00c8e870
void  FUN_00e92af0();              // 0x00e92af0
void  FUN_00e92ca0(void* self, int a, int b);    // 0x00e92ca0
extern float kOneF;                // 0x01485720  1.0f
extern u32   kEffectViewVtbl;      // 0x01486518
static u32 kFadeConstLit = 0xb4b1178d;
union Int3 { int i; int v; };
struct cIVisualEffect {
    void AddRef();                    // 0x00a02c30
    void Release();                   // 0x00a05270
    char pad[0x80];
    float mAlpha;                     // +0x80
    char pad2[0x128 - 0x84];
    struct cEffectParam* mp128;       // +0x128
    int   m12c;                       // +0x12c
    int   m130;                       // +0x130
    char pad3[0x180 - 0x134];
    struct cEffectState* mpState;     // +0x180
    void SetShown(int b);             // 0x00a047d0
    int  GetLevel();                  // 0x00a02bd0
    bool  IsInView();                 // 0x00c35d10
    void  FUN_00c35b60();             // 0x00c35b60
    void  FUN_00c88530(float d);      // 0x00c88530
};
struct cEffectState { int pad; u32 mFlags; };   // +4: bit0 "interactable", bit14, bit18
struct cEffectParam {
    int  FUN_00c22850();                          // 0x00c22850
    void FUN_00c22870();                          // 0x00c22870
    void FUN_00c23300(const void* c, int f);      // 0x00c23300
};
struct cTransform34 {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
virtual void s11();
virtual void s12();
virtual void s13();
virtual void s14();
virtual void s15();
    virtual void SetDist(float d);                // slot 16 (+0x40)  0x00c88530
    char pad[0x34];
};
struct cMsgTarget {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
    virtual void Send(XformMsg* m);      // slot 6 (+0x18)
    virtual void s7();
    virtual void Prepare(XformMsg* m);   // slot 8 (+0x20)
};
struct cAnimComp {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
    virtual void s10();
    virtual const Vec3* GetPosition();            // slot 11 (+0x2c)
    virtual const void* GetOrientation();         // slot 12 (+0x30)
    virtual float GetScale();                     // slot 13 (+0x34)
virtual void s14();
virtual void s15();
virtual void s16();
virtual void s17();
    virtual bool IsReady();                       // slot 18 (+0x48)
    virtual void SetFlag(bool b);                 // slot 19 (+0x4c)
virtual void s20();
virtual void s21();
    virtual bool IsActive();                      // slot 22 (+0x58)
virtual void s23();
virtual void s24();
virtual void s25();
virtual void s26();
virtual void s27();
    virtual float GetHeight();                    // slot 28 (+0x70)
    virtual float GetRadius();                    // slot 29 (+0x74)
    char pad0[0x50 - 4];
    u32  mStateFlags;                             // +0x50 (creature +0x110); bit 11 = "needs name effect"
    char pad1[0x68 - 0x54];
    float mViewDistance;                          // +0x68 (creature +0x128)
    char pad2[0x74 - 0x6c];
    bool mDirty;                                  // +0x74 (creature +0x134)
    bool mHasView;                                // +0x75 (creature +0x135)
    bool pad3;
    bool mOnPlanet;                               // +0x77 (creature +0x137)
    bool IsDirty() const { return mDirty; }
    bool ConsumeDirty() { if (mDirty) { mDirty = false; return true; } return false; }
    void ClearNeedsNameEffect() { mStateFlags &= ~0x800u; }
    bool NeedsNameEffect() const { return (mStateFlags & 0x800) != 0; }
    void FUN_00c89d60(Transform* t);              // 0x00c89d60
    void FUN_00c8aa60();                          // 0x00c8aa60
};
struct cCreatureState { char pad[0x648]; int mCount648; char pad2[0x694 - 0x64c]; u32 mCount694; char pad3[0x69c - 0x698]; u32 mCount69c; };
class cAnimatingBase {
public:
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
    virtual u32  GetType();                       // slot 8 (+0x20)
    char pad0[0xc0 - 4];
};
class cAnimatingCreature_s00e8_c120 : public cAnimatingBase, public cAnimComp {   // cAnimComp subobject at +0xc0
public:
    char pad1[0x330 - 0x138];
    int  m330;                                    // +0x330
    char pad2[0xb20 - 0x334];
    cCreatureState* mpState;                      // +0xb20
    char pad3[0xb54 - 0xb24];
    cIVisualEffect* mpOverheadEffect;             // +0xb54
    u32  mFlagsB58;                               // +0xb58 (bit 9 = fixed LOD)
    char pad4[0xb5d - 0xb5c];
    bool mbB5D;                                   // +0xb5d
    bool mbB5E;                                   // +0xb5e
    char pad5[0xbb0 - 0xb5f];
    bool mbBB0;                                   // +0xbb0
    char pad6[0xe58 - 0xbb1];
    float mfE58;                                  // +0xe58
    char pad7[0xe68 - 0xe5c];
    bool mbE68;                                   // +0xe68
    char pad8[0xf90 - 0xe69];
    bool mbF90;                                   // +0xf90

    void SetLOD(int lod);                         // 0x00c0c300
    const Vec3* GetBasePosition();                // 0x00c0e580
    bool FUN_00c0c130();                          // 0x00c0c130
    bool FUN_00c0c0e0();                          // 0x00c0c0e0
    void SetEffectParam(bool v, u32 hash, u32 id);   // 0x00c201a0
    cMsgTarget* FindEffect(u32 id);               // 0x00c14e70
    void KillEffect(u32 id, int flag);            // 0x00c17350
    void CreateEffect(u32 hash, u32 id);          // 0x00c1d400
    bool IsInView();                              // 0x00c35d10
    void FUN_00c35b60();                          // 0x00c35b60
    float FUN_00c41ec0();                         // 0x00c41ec0
    cTransform34* mp34;                           // +0x34
};
namespace SP {
class cEffectView {
public:
    virtual void v0();
    virtual void HandleUpdate(int a, int b);      // slot 1 (+4)
virtual void v2();
virtual void v3();
    virtual void SetShown(bool b);                // slot 4 (+0x10)
    virtual void v5();
    virtual void SetActive(bool b);               // slot 6 (+0x18)
    virtual bool IsActive();                      // slot 7 (+0x1c)

    char pad0[8];
    cAnimatingCreature_s00e8_c120* mpCreature;               // +0x0c
    cIVisualEffect* mpEffect;                     // +0x10
    bool mbActive;                                // +0x14
    char pad1[3];
    Vec3  mVec;                                   // +0x18
    u32   m24;                                    // +0x24
    u32   m28;                                    // +0x28
    u32   m2c;                                    // +0x2c
    u32   m30;                                    // +0x30
    u32   m34;                                    // +0x34
    u32   m38;                                    // +0x38
    u32   m3c;                                    // +0x3c

    void SetTrackedEffect(cAnimatingCreature_s00e8_c120* c); // 0x00e8c9a0
    cEffectView* Initialize();                    // 0x00e8cc90
    Vec3* ComputeFade(Vec3* out, int& ok, void* c);   // 0x00e8cd30
    cEffectView* CreateFor(cAnimatingCreature_s00e8_c120* c);                  // 0x00e8cec0
    void HandleMessage(int a, int b);             // 0x00e8cf50
};
}
// ---- items of slice s00e8c120 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern u32   kFadeTableA;          // 0x01486408
extern u32   kFadeTableB;          // 0x01486498
extern u32   kEffectViewVtbl;      // 0x01486518

// @ 0x00e8cc90
SP::cEffectView* SP::cEffectView::Initialize()
{
    FUN_00e92af0();
    Vec3 one;
    one.x = kOneF;
    one.y = kOneF;
    one.z = kOneF;
    mVec = one;                // +0x18
    m24 = 0x3f6368f1;          // +0x24
    m28 = 0;                   // +0x28
    *(void**)this = (void*)kEffectViewVtbl;   // +0x00
    m2c = 0x5c4fce4c;          // +0x2c
    m34 = 0;                   // +0x34
    m38 = 1;                   // +0x38
    m3c = 0;                   // +0x3c
    return this;
}

// @ 0x00e8cd30
Vec3* SP::cEffectView::ComputeFade(Vec3* out, int& ok, void* c)
{
    out->x = 0.0f;
    out->y = 0.0f;
    out->z = 0.0f;

    cIVisualEffect* fx = 0;
    if (c) {
        fx = (cIVisualEffect*)((void* (__stdcall*)(void*, u32))((*((void***)c))[3]))(c, 0x4ffcdeda);
        if (fx)
            fx->AddRef();
    }
    if (fx) {
        int a = fx->m12c;
        fx->FUN_00c35b60();
        int b = fx->m130;

        if (m34 == (u32)a && m38 == (u32)b && m3c == 0) {
            out->x = *(float*)&m24;
            out->y = *(float*)&m28;
            out->z = *(float*)&m2c;
        } else {
            m34 = (u32)a;
            m38 = (u32)b;
            m3c = 0;

            cEffectParam* p1 = fx->mp128;
            int v1 = p1 ? (int)((void* (__stdcall*)(cEffectParam*, u32))((*((void***)p1))[5]))(p1, 0x4f176642) : 0;
            cEffectParam* p2 = fx->mp128;
            int v2 = p2 ? (int)((void* (__stdcall*)(cEffectParam*, u32))((*((void***)p2))[5]))(p2, 0x4f396a66) : 0;

            if (fx->mp128 == FUN_00ac79d0(FUN_00b3d2b0()))
                v2 = (int)FUN_00bfc5f0(FUN_00b3d300());

            if ((v1 && FUN_00c0b780(v1)) || (v2 && !FUN_00c8e870(v2)))
                ;   // fall through
            else if (a == 3)
                a = 0;

            int sel;
            if (ok == 1) {
                if (a <= 4 && b <= 6)
                    sel = ((int*)&kFadeTableA)[(a * 7) + b];
                else
                    sel = 0;
            } else {
                sel = ((int*)&kFadeTableB)[b + a * 4];
            }

            out->x = *(float*)&sel;
            out->y = (float)m28;
            out->z = *(float*)&kFadeConstLit;
        }
        fx->Release();
    }
    return out;
}

// @ 0x00e8cec0
SP::cEffectView* SP::cEffectView::CreateFor(cAnimatingCreature_s00e8_c120* c)
{
    cEffectView* v = (cEffectView*)operator new(0x40, 0x1460d64, 0, 0, 0, 0);
    if (v)
        v = v->Initialize();

    Vec3 tmp;
    Int3 ok;
    mpCreature = c;
    mVec.x = 1.0f;
    mVec.y = 1.0f;
    mVec.z = 1.0f;
    ok.v = 0;
    ComputeFade(&tmp, ok.i, c);
    m24 = *(u32*)&tmp.x;
    m28 = *(u32*)&tmp.y;
    m2c = *(u32*)&tmp.z;

    int h = FUN_00b3d520(this);
    ((void (__stdcall*)(cEffectView*, void*, int))((*((void***)v))[10]))(v, &m24, h);
    return v;
}

// @ 0x00e8cf50
void SP::cEffectView::HandleMessage(int a, int b)
{
    FUN_00e92ca0(this, a, b);

    cAnimatingCreature_s00e8_c120* c = mpCreature;
    cIVisualEffect* fx = 0;
    if (c) {
        fx = (cIVisualEffect*)((void* (__stdcall*)(cAnimatingCreature_s00e8_c120*, u32))((*((void***)c))[3]))(c, 0x4ffcdeda);
        if (fx)
            fx->AddRef();
    }

    bool inView = fx && fx->IsInView();
    SetActive(!inView);

    if (!IsActive()) {
        if (fx)
            fx->Release();
        return;
    }

    Vec3 tmp;
    ComputeFade(&tmp, (int&)b, fx);

    if (!(tmp.x == (float)m24 && tmp.y == (float)m28 && tmp.z == (float)m2c)) {
        cEffectParam* p = fx->mp128;
        cEffectParam* saved = p;
        if (p) {
            p = (cEffectParam*)((void* (__stdcall*)(cEffectParam*, u32))((*((void***)p))[5]))(p, 0x4f176642);
            if (p && p->FUN_00c22850() == 1)
                p->FUN_00c22870();
        }
        if (kEffectNearDist > (float)fx->m130)
            fx->FUN_00c88530(kEffectNearDist);
        else
            c->mp34->SetDist(kEffectNearDist);

        m24 = *(u32*)&tmp.x;
        m28 = *(u32*)&tmp.y;
        m2c = *(u32*)&tmp.z;

        int h = FUN_00b3d520(this);
        ((void (__stdcall*)(cEffectView*, u32*, int))((*((void***)this))[10]))(this, &m24, h);
        ((void (__stdcall*)(cEffectView*, u32*))((*((void***)this))[3]))(this, &m24);

        if (saved && saved->FUN_00c22850() == 1)
            saved->FUN_00c23300(c, -1);
    }

    if (fx)
        fx->Release();
}
