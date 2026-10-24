// Slice s00c35810 (batch gold7).  Region 0x00c35810-0x00c368bc.
// SP::Simulator cGameBundle family: the space-stage bundle (spatial object at
// +0x34, interaction target at +0x108), its ground-container sibling, and the
// small cEmpire / serializer / vtable-dispatch helpers around them.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "s00c35810.h"
#include <math.h>

// ---------------------------------------------------------------------------
// thiscall callee typedefs (the original calls these out of line)
// ---------------------------------------------------------------------------
typedef void* (__thiscall *Fn_p)(void*, uint32_t);
typedef void* (__thiscall *Fn_p0)(void*);
typedef void  (__thiscall *Fn_v)(void*, uint32_t);
typedef void  (__thiscall *Fn_v0)(void*);
typedef float*(__thiscall *Fn_fp)(void*);
typedef void  (__thiscall *Fn_vf)(void*, float*);

// ---------------------------------------------------------------------------
// the out-of-line thiscall callees, modelled as members of the object they are
// invoked on so the compiler uses the ecx convention naturally.
// ---------------------------------------------------------------------------
struct CallTarget0320 { void* Func(uint32_t key); };  // 0x00ac0320
struct CallTargetB18460 { void* Func(uint32_t key); }; // 0x00b18460
struct CallTargetC884f0 { void* Func(uint32_t key); }; // 0x00c884f0
struct CallTargetCEE250 { void* Func(uint32_t key); }; // 0x00cee250
// polymorphic view: calling v1/v7 emits an explicit `mov eax,[ecx]; call [eax+N]`
struct VObj {
    virtual void v0();
    virtual void v1();   // slot 1 (+0x04)
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();   // slot 7 (+0x1c)
};
struct StreamWrite       { uint32_t Slot18(); };       // vtable slot 6 (0x18)
struct CastTarget        { StreamWrite* GetStream(); };// vtable slot 8 (0x20)
struct SerObj {
    void     Ctor(void* self, void* nameTbl, uint32_t hash);   // 0x692f90
    void     Serialize(uint32_t stream);                       // 0x692900
    void     Read(uint32_t stream);                            // 0x693e10
    uint32_t GetFields(uint32_t vec);                          // 0x695960
};

// small polymorphic views for the raw vtable-slot calls in 00c364e0/367e0/36870
struct VObj1 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    void Set2c(uint32_t v);   // slot 11 (+0x2c)
};
struct VObj2 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4();
    uint32_t Get50(uint32_t key);   // slot 5 (+0x14)
};
struct VObj3 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    void Slot30(void* obj);   // slot 12 (+0x30)
};
struct VObj4 {
    virtual void v0(); virtual void v1(); virtual void v2();
    void* Cast15(uint32_t key);   // slot 3 (+0xc)  -- see note
};
struct PlanetModelT { void DirToSurface(); };
struct C0B7C0 { uint8_t Pick(void* b); };   // 0x00c0b7c0 thiscall helper
struct C0AC79D0 { uint32_t Get(); };         // 0x00ac79d0 thiscall on FUN_00b3d2b0()
struct C0B25C30 { uint32_t Get(); };         // 0x00b25c30 thiscall on NounManager()
struct C0BFC5F0 { uint32_t Get(); };         // 0x00bfc5f0 thiscall on NounManager()
struct C0C88870 { void Base(); };            // 0x00c88870 thiscall base func
struct C0C90460 { uint32_t Test(); };        // 0x00c90460 thiscall test
struct Obj274 { uint8_t pad[0x274]; void* p274; };  // object exposing +0x274
struct C0EB0EA0 { void* Ctor(); };           // 0x00eb0ea0 cPlayerCityMusic ctor
struct C0EAB410 { void* Ctor(uint32_t kind); }; // 0x00eab410 ctor
struct C0C35320 { void PickRandomPersonality(); }; // 0x00c35320
struct C0B7F1F0 { void* Build(); };          // 0x00b7f1f0 BuildSurfaceOrientation

// ===========================================================================
// cGameBundle::CastTo -- try the interaction target, the game data and the
// spatial object for the requested interface id
// ===========================================================================
// @ 0x00c35ad0
void* cGameBundle::CastTo(uint32_t key)
{
    if (key == 0x4ffcdeda)
        return this;
    void* r = ((CallTarget0320*)mInteract)->Func(key);
    if (r)
        return r;
    r = ((CallTargetB18460*)this)->Func(key);
    if (r)
        return r;
    return ((CallTargetC884f0*)mSpatial)->Func(key);
}

// ===========================================================================
// cGameBundle::Set12c134 -- store the state word and the scalar
// ===========================================================================
// @ 0x00c35b20
void cGameBundle::Set12c134(uint32_t a, float f)
{
    mField12c = a;
    mField134 = f;
}

// ===========================================================================
// cGameBundle::IsState0Or4 -- true when the state word is 0, 1 or 4
// ===========================================================================
// @ 0x00c35d20
bool cGameBundle::IsState0Or4()
{
    int32_t s = (int32_t)mField12c;
    return (s >= 0 && (s <= 1 || s == 4)) ? true : false;
}

// ===========================================================================
// cGameBundle::IsState234 -- true when the state word is 2, 3 or 4
// ===========================================================================
// @ 0x00c35d40
bool cGameBundle::IsState234()
{
    return (uint32_t)(mField12c - 2) <= 2U;
}

// ---------------------------------------------------------------------------
// the name-tag callee: thiscall, self in ecx, then (obj, global, wide-name)
// ---------------------------------------------------------------------------
struct TagTarget { uint32_t Tag(void* obj, void* global, const wchar_t* name); }; // 0x00695b40

// ===========================================================================
// ground-container name-tag helper
// ===========================================================================
// @ 0x00c35d90
bool FUN_00c35d90(void* self, void** obj)
{
    if (*obj)
        ((TagTarget*)self)->Tag(*obj, &g_p15816b8, g_wcGameBundleContainer);
    return true;
}

// ===========================================================================
// cGameBundleGroundContainer::CastTo
// ===========================================================================
// ===========================================================================
// cGameBundleGroundContainer::CastTo
// ===========================================================================
// @ 0x00c36560
void* cGameBundleGroundContainer::CastTo(uint32_t key)
{
    void* r = this;
    if (key != 0xeef202b7)
    {
        r = ((CallTargetB18460*)this)->Func(key);
        if (!r)
            r = ((CallTargetCEE250*)mSpatial)->Func(key);
    }
    return r;
}

// ===========================================================================
// cGameBundle::Write -- spatial object + game data + the var-list serializer
// ===========================================================================
// @ 0x00c35c60
void cGameBundle::Write(uint32_t s)
{
    char buf[0xa14];
    ((BaseSpatial*)mSpatial)->Write(s);
    ((BaseGameData*)this)->Write(s);
    ((SerObj*)buf)->Ctor(this, &g_p1573038, 0x1a80d26);
    ((SerObj*)buf)->Serialize(s);
}

// ===========================================================================
// cGameBundle::Read
// ===========================================================================
// @ 0x00c35cb0
void cGameBundle::Read(uint32_t s)
{
    char buf[0xa14];
    ((BaseSpatial*)mSpatial)->Read(s);
    ((BaseGameData*)this)->Read(s);
    ((SerObj*)buf)->Ctor(this, &g_p1573038, 0x1a80d26);
    ((SerObj*)buf)->Serialize(s);
}

// ===========================================================================
// cGameBundle::GetFieldValues -- sum the field counts of both serializers
// ===========================================================================
// @ 0x00c35e70
uint32_t cGameBundle::GetFieldValues(uint32_t s)
{
    struct Ser { uint8_t b[0xa14]; };

    uint32_t a = ((BaseGameData*)this)->WriteAsText(s);
    Ser serHi;
    Ser serLo;
    ((SerObj*)&serHi)->Ctor(mSpatial, &g_p157a1f8, 0x1a80d26);
    a += ((SerObj*)&serHi)->GetFields(s);
    ((SerObj*)&serLo)->Ctor(this, &g_p1573038, 0x1a80d26);
    uint32_t c = ((SerObj*)&serLo)->GetFields(s);
    return c + a;
}

// ===========================================================================
// cGameBundle::Ctor
// ===========================================================================
// @ 0x00c35dc0
cGameBundle* cGameBundle::Ctor()
{
    ((BaseGameData*)this)->Ctor();
    ((BaseSpatial*)mSpatial)->Ctor();
    ((BaseInteract*)mInteract)->Ctor();
    mpVtbl   = g_p146b998;
    mpVtbl2  = g_p146b984;
    *(void**)mSpatial  = g_p146b8c0;
    *(void**)mInteract = g_p146b8a0;
    mpField120 = 0;
    mField124  = 0;
    mpField128 = 0;
    mField130  = 0;
    mField138  = 0;
    *(uint8_t*)((char*)this + 0xa4) = 0;
    ((BaseSpatial*)mSpatial)->SetFloat(g_f1581338);
    return this;
}

// ===========================================================================
// cGameBundle::Dtor
// ===========================================================================
// @ 0x00c35f70
void cGameBundle::Dtor()
{
    mpVtbl  = g_p146b998;
    mpVtbl2 = g_p146b984;
    *(void**)mSpatial  = g_p146b8c0;
    *(void**)mInteract = g_p146b8a0;
    void* p128 = mpField128;
    if (p128)
        ((VObj*)p128)->v7();
    if (mpField120)
        ((VObj*)mpField120)->v1();
    ((BaseInteract*)mInteract)->Reset();
    ((BaseSpatial*)mSpatial)->Dtor();
    ((BaseGameData*)this)->Dtor();
}

// ===========================================================================
// cGameBundle::Reset128And2c
// ===========================================================================
// @ 0x00c35fe0
void cGameBundle::Reset128And2c()
{
    if (mpField128)
    {
        void* p = mpField128;
        mpField128 = 0;
        ((VObj*)p)->v7();
    }
    ((BaseInteract*)mInteract)->Dtor();
    if (mpOwner)
    {
        void* p = mpOwner;
        mpOwner = 0;
        ((VObj*)p)->v1();
    }
    ((BaseSpatial*)mSpatial)->Exit();
}

// ===========================================================================
// cGameBundleGroundContainer::Ctor
// ===========================================================================
// @ 0x00c36510
cGameBundleGroundContainer* cGameBundleGroundContainer::Ctor()
{
    ((BaseGameData*)this)->Ctor();
    ((GroundBase*)mSpatial)->Ctor();
    *(void**)mSpatial = g_p146bac0;
    mpVtbl  = g_p146ba68;
    mpVtbl2 = g_p146ba58;
    mField58 = 0.0f;
    mpField5c = 0;
    return this;
}

// ===========================================================================
// cGameBundleGroundContainer::Dtor2c
// ===========================================================================
// @ 0x00c36690
void cGameBundleGroundContainer::Dtor2c()
{
    ((GroundBase*)mSpatial)->Dtor();
    if (mpOwner2c)
    {
        void* p = mpOwner2c;
        mpOwner2c = 0;
        ((VObj*)p)->v1();
    }
}

// ===========================================================================
// cGameBundleGroundContainer::Init
// ===========================================================================
// @ 0x00c365a0
void cGameBundleGroundContainer::Init(uint32_t obj)
{
    ((GroundBase*)mSpatial)->InitObj(obj, 1000, g_f13ec5b4, 0.0f, 1);
    ((BaseGameData*)this)->GetFieldValues(obj);
}

// ===========================================================================
// cGameBundleGroundContainer::Write
// ===========================================================================
// @ 0x00c366c0
bool cGameBundleGroundContainer::Write(void* stream)
{
    uint32_t key = 0xeef202b7;
    StreamWrite* w = ((CastTarget*)stream)->GetStream();
    uint32_t sink = w->Slot18();
    FUN_0093aa70((void*)sink, &key, 1, 0);
    bool r = ((GroundBase*)mSpatial)->WriteObj((uint32_t)stream);
    uint32_t zero = 0;
    StreamWrite* w2 = ((CastTarget*)stream)->GetStream();
    uint32_t sink2 = w2->Slot18();
    FUN_0093aa70((void*)sink2, &zero, 1, 0);
    return r;
}

// ===========================================================================
// cGameBundleGroundContainer::Read
// ===========================================================================
// @ 0x00c36740
bool cGameBundleGroundContainer::Read(void* stream)
{
    uint32_t key = 0;
    StreamWrite* w = ((CastTarget*)stream)->GetStream();
    uint32_t sink = w->Slot18();
    FUN_0093a780((void*)sink, &key, 1, 0);
    bool r = ((GroundBase*)mSpatial)->ReadObj((uint32_t)stream);
    uint32_t zero = 0;
    StreamWrite* w2 = ((CastTarget*)stream)->GetStream();
    uint32_t sink2 = w2->Slot18();
    FUN_0093a780((void*)sink2, &zero, 1, 0);
    return r;
}

// ===========================================================================
// ground-container: stream factory shim
// ===========================================================================
// @ 0x00c364e0
bool FUN_00c364e0(void* a, void* b)
{
    uint32_t v = 0;
    void* p = *(void**)b;
    if (p != 0)
    {
        typedef uint32_t (__thiscall* Fn)(void*, uint32_t);
        v = ((Fn)(*(void***)p)[5])(p, 0x179c807);
    }
    typedef void (__thiscall* Fn2)(void*, uint32_t);
    ((Fn2)(*(void***)a)[11])(a, v);
    return true;
}

// ===========================================================================
// ground-container: direction -> surface position
// ===========================================================================
// @ 0x00c365e0
void* __stdcall FUN_00c365e0(void* param1, void* param2)
{
    typedef float* (__thiscall* FnDir)(void*);
    void* base = (char*)param2 + 0x34;
    float* p = ((FnDir)(*(void***)base)[11])(base);
    void* pm = (void*)FUN_00b3d350((uint32_t)param1, (uint32_t)p);
    ((PlanetModelT*)pm)->DirToSurface();
    return param1;
}

// ===========================================================================
// cGameBundleGroundContainer: orientation helper
// ===========================================================================
// @ 0x00c367e0
struct FF367E0 {
    void Apply(void* obj);
};
void FF367E0::Apply(void* obj)
{
    typedef float* (__thiscall* FnDir)(void*);
    typedef void (__thiscall* FnSet)(void*, const float*);
    void* base = (char*)obj + 0x34;
    float* f = ((FnDir)(*(void***)base)[11])(base);
    if (f[0] == g_f168df38 && f[1] == g_f168df3c && f[2] == g_f168df40)
    {
        float v[3];
        v[0] = g_kOne;
        v[1] = 0.0f;
        v[2] = 0.0f;
        ((FnSet)(*(void***)base)[14])(base, v);
    }
    typedef void (__thiscall* Fn30)(void*, void*);
    ((Fn30)(*(void***)this)[12])(this, obj);
}

// ===========================================================================
// cGameBundle::ComputeState -- 0..6 derived from the state word / scalar
// ===========================================================================
// @ 0x00c35b60
uint32_t cGameBundle::ComputeState()
{
    if (mField130 == 0)
    {
        float base = g_Zero15812d0;
        switch (mField12c)
        {
        case 1: base = g_Zero15812d4; break;
        case 2: base = g_Zero15812d8; break;
        case 3: base = g_Zero15812dc; break;
        case 4: base = g_Zero15812e0; break;
        }
        float v = mField134;
        if (base * g_kThreeTenths <= v)
        {
            if (base * g_kSixTenths <= v)
                return 3;
            return 2;
        }
        if (base * g_kTwoHundredths <= v)
            return 1;
        return 0;
    }
    if (mField124 != 0)
        return 6;
    float v = mField134;
    if (g_kFive <= v)
    {
        if (g_kTen <= v)
        {
            if (g_kTwentyFive <= v)
            {
                if (g_kFifty <= v)
                    return 5;
                return 4;
            }
            return 3;
        }
        return 2;
    }
    return 1;
}

// ===========================================================================
// pick helper over an owned +0x64 object
// ===========================================================================
// @ 0x00c36870
bool FUN_00c36870(cGameObj64* a, void* b)
{
    if (a->mpField64 && (C0B7C0*)a->mpField64)
    {
        typedef void* (__thiscall* Fn)(void*, uint32_t);
        void* r = ((Fn)(*(void***)a->mpField64)[3])(a->mpField64, 0xd0036e08);
        if (r && *(uint8_t*)((char*)r + 0xb5e) == 0 &&
            *(uint8_t*)((char*)r + 0x135) != 0 && b)
        {
            if (((C0B7C0*)r)->Pick(b))
                return true;
        }
    }
    return false;
}


// ===========================================================================
// owned-object ownership vs NounManager test (0x00c36030)
// ===========================================================================
struct FF36030 {
    bool Test();   // 0x00c36030
};
// @ 0x00c36030
bool FF36030::Test()
{
    void* p = *(void**)((char*)this + 0xf4);
    if (p == 0)
        return false;
    void* q = *(void**)((char*)p + 0x18);
    if (q == 0)
        return false;
    typedef uint8_t (__thiscall* FnA)(void*);
    if (((FnA)(*(void***)q)[11])(q) != 0)
        return false;

    void* p2 = *(void**)((char*)this + 0xf4);
    if (p2 == (void*)(uint32_t)((C0AC79D0*)FUN_00b3d2b0())->Get())
        return true;

    void* owned = *(void**)((char*)p + 0x18);
    typedef void* (__thiscall* FnC)(void*, uint32_t);
    void* t = owned ? ((FnC)(*(void***)owned)[3])(owned, 0xee9b2232) : 0;
    void* u = (void*)(uint32_t)((C0B25C30*)FUN_00b3d300())->Get();
    if (t != 0 && u != 0)
        return t == u;

    void* owned2 = *(void**)((char*)p + 0x18);
    void* g = (void*)(uint32_t)FUN_00ac8730(owned2);
    void* h = (void*)(uint32_t)((C0BFC5F0*)FUN_00b3d300())->Get();
    if (g != 0 && h != 0)
        return g == h;
    return false;
}

// ===========================================================================
// direction -> surface position push (0x00c360f0)
// ===========================================================================
struct FF360F0 {
    void Push();   // 0x00c360f0
};
// @ 0x00c360f0
void FF360F0::Push()
{
    typedef float* (__thiscall* FnDir)(void*);
    typedef void  (__thiscall* FnSet)(void*, const float*);

    ((C0C88870*)this)->Base();   // 0x00c88870

    void* owned = *(void**)((char*)this + 0xf4);
    if (owned == 0)
        return;
    typedef void* (__thiscall* FnCast)(void*, uint32_t);
    void* obj = ((FnCast)(*(void***)owned)[5])(owned, 0x4f396a66);
    if (obj == 0)
        return;

    float scale = g_f15812f4;
    if (((C0C90460*)obj)->Test() != 0)
        scale = g_f15812f8;
    else
    {
        typedef uint32_t (__thiscall* FnId)(void*);
        uint32_t e = ((FnId)(*(void***)obj)[19])(obj);
        if (e == FUN_01021090())
            scale = g_f15812f8;
    }

    float* d = ((FnDir)(*(void***)this)[11])(this);
    float inv = (float)(1.0 / sqrt((double)(d[0] * d[0] + d[1] * d[1] + d[2] * d[2] + g_f13ec4b8)));
    float sx = d[0] * inv * scale;
    float sy = d[1] * inv * scale;
    float sz = d[2] * inv * scale;
    float* pos = ((FnDir)(*(void***)this)[11])(this);
    float out[3];
    out[0] = pos[0] + sx;
    out[1] = pos[1] + sy;
    out[2] = pos[2] + sz;
    ((FnSet)(*(void***)this)[14])(this, out);
}

// ===========================================================================
// cEmpire: assign the home-star / music / personality (0x00c359a0)
// ===========================================================================
struct FF359A0 {
    void Setup(void* star, uint8_t flag);   // 0x00c359a0
};
struct NounMgr {
    uint32_t ClassifyById(uint32_t id);   // 0x00b20790
    void*    GetFeedback(uint32_t id);    // 0x00b20750
};
struct StarMgr {
    void* GetPlayerStar();                // 0x00885c90
};
// @ 0x00c359a0
void FF359A0::Setup(void* star, uint8_t flag)
{
    *(void**)((char*)this + 0x84) = star;
    NounMgr* nm = (NounMgr*)FUN_00b3d300();

    void* picked = 0;
    if (flag)
    {
        if (nm->ClassifyById((uint32_t)star) == 4)
        {
            void* fb = nm->GetFeedback((uint32_t)star);
            if (fb)
            {
                typedef void* (__thiscall* FnCast)(void*, uint32_t);
                void* o = ((FnCast)(*(void***)fb)[3])(fb, 0x901f1362);
                picked = *(void**)((char*)o + 0x274);
            }
            else
            {
                picked = ((Obj274*)0)->p274;
            }
        }
        else
        {
            void* p = FUN_00f473a0(0x220, "Simulator", 0, 0, 0, 0);
            if (p)
                picked = ((C0EB0EA0*)p)->Ctor();
        }
    }
    else
    {
        void* pl = ((StarMgr*)FUN_00b3d2a0())->GetPlayerStar();
        if (pl == *(void**)((char*)this + 0x84))
        {
            void* p = FUN_00f473a0(0x28, "Simulator", 0, 0, 0, 0);
            if (p)
                picked = ((C0EAB410*)p)->Ctor(4);
        }
        else
        {
            void* p = FUN_00f473a0(0x28, "Simulator", 0, 0, 0, 0);
            if (p)
                picked = ((C0EAB410*)p)->Ctor(3);
        }
    }

    void* old = *(void**)((char*)this + 0x104);
    if (picked != old)
    {
        if (picked)
            ((VObj*)picked)->v0();
        *(void**)((char*)this + 0x104) = picked;
        if (old)
            ((VObj*)old)->v1();
    }
    *(uint32_t*)((char*)this + 0x50) |= 0x10;
    if (flag)
    {
        *(uint32_t*)((char*)this + 0x50) |= 0x44;
        *(uint32_t*)((char*)this + 0x58) = 0x11;
        return;
    }
    ((C0C35320*)this)->PickRandomPersonality();
}

// ===========================================================================
// cEmpire::Remove -- unlink a planet/star from this empire (0x00c35810)
// ===========================================================================
struct C0B8DE30v { uint32_t Run(); };        // thiscall on planet
struct C0BBA790v { uint32_t* Get(); };       // thiscall on star
struct C0CE6950v { uint32_t GetComm(); };    // thiscall GetCommContext
struct C01021AB0 { void Notify(void* obj); };// 0x01021ab0 thiscall on global
struct MsgSrv {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5();
    void Emit4(uint32_t a, uint32_t b, uint32_t c, uint32_t d);  // slot 6 (+0x18)
};
// @ 0x00c35810
uint32_t cEmpire::Remove(void* planet)
{
    if (planet == 0)
        return 0;
    if (mEmpireId == FUN_01021090())
        ((C01021AB0*)g_p16dda8c)->Notify(planet);

    uint32_t star = ((C0B8DE30v*)planet)->Run();
    uint32_t found = 0;
    uint32_t* vec = ((C0BBA790v*)star)->Get();
    int32_t n = (int32_t)(((int32_t)vec[1] - (int32_t)vec[0]) >> 2);
    if (n > 0)
    {
        uint32_t* data = (uint32_t*)vec[0];
        for (int32_t i = 0; i < n; i++)
        {
            uint32_t c = data[i];
            if (c != (uint32_t)planet && c != 0 &&
                FUN_00c70150((void*)(uint32_t)c, this, 0))
            {
                found = c;
                break;
            }
        }
    }

    uint32_t ctx = ((C0CE6950v*)planet)->GetComm();
    if (ctx == mCommContext)
    {
        if (found == 0 &&
            (uint32_t)(((char*)mStarsEnd - (char*)mStarsBegin)) == 4)
            FUN_00ba5bc0(this, 6);
        mCommContext = (uint32_t)-1;
        mFieldB0 = (uint32_t)-1;
        typedef uint32_t (__cdecl* FnSM)(uint32_t, uint32_t);
        uint32_t sm = ((FnSM)FUN_00b3d2a0)(mEmpireId, 0);
        FUN_00baf630(sm);
        MsgSrv* ms = (MsgSrv*)FUN_0067dcc0();
        ms->Emit4(0x43f2586, 0, 0, 0);
    }

    uint32_t pid = FUN_01021090();
    int32_t an = (int32_t)(((int32_t)mAlliesEnd - (int32_t)mAlliesBegin) >> 2);
    if (an > 0)
    {
        for (int32_t k = 0; k < an; k++)
        {
            if (mAlliesBegin[k] == pid)
            {
                MsgSrv* ms = (MsgSrv*)FUN_0067dcc0();
                ms->Emit4(0x43f2585, 0, 0, 0);
                break;
            }
        }
    }

    if (found != 0)
    {
        if (mCommContext == (uint32_t)-1)
            FUN_00c316c0(this, (void*)(uint32_t)found);
        return 1;
    }
    return FUN_00c34ee0(this, 1);
}

// ===========================================================================
// cGameBundle ground-container: surface orientation push (0x00c36300)
// ===========================================================================
struct EffMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    uint8_t Acquire(uint32_t key, void** out, uint32_t c);  // slot 11 (+0x2c)
};
struct Spatial34 {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10();
    float* GetPos();     // slot 11 (+0x2c)
    float* GetDir();     // slot 12 (+0x30)  -- direction quat
    float  GetScalar();  // slot 13 (+0x34)
    void   SetVal(const void*);  // slot 14 (+0x38)
};
struct Acquired {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5();
    void Push(const void* v);   // slot 6 (+0x18)
};
// @ 0x00c36300
void FUN_00c36300(void* self)
{
    void* held = 0;
    EffMgr* em = (EffMgr*)FUN_0067ddd0();
    if (held)
    {
        void* p = held;
        held = 0;
        ((VObj*)p)->v1();
    }
    if (em->Acquire(0xd6276f0c, &held, 0) == 0)
    {
        if (held)
            ((VObj*)held)->v2();
        return;
    }

    Spatial34* base = (Spatial34*)((char*)self + 0x34);
    float* q = base->GetDir();
    float quat[4];
    quat[0] = q[0]; quat[1] = q[1]; quat[2] = q[2]; quat[3] = q[3];
    float* pf = base->GetPos();
    float pos[3];
    pos[0] = pf[0]; pos[1] = pf[1]; pos[2] = pf[2];

    void* pm = (void*)FUN_00b3d350((uint32_t)pos, (uint32_t)quat);
    void* orient = ((C0B7F1F0*)pm)->Build();
    (void)orient;
    float scalar = base->GetScalar();
    (void)scalar;

    // build the surface vector record and hand it to the acquired sink
    float rec[6];
    rec[0] = g_f168df28;
    rec[1] = g_f168df2c;
    rec[2] = g_f168df30;
    rec[3] = g_kOne;
    rec[4] = scalar;
    rec[5] = 0.0f;
    ((Acquired*)held)->Push(rec);
    if (held)
        ((VObj*)held)->v2();
}
