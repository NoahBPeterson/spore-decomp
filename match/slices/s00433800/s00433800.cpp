// Timed fade/effect-instance controller (fields at 0x00..0x34) and helpers.
// Unoptimized module: /Od /Ob1 /arch:SSE.
#include "types.h"

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
};
struct Matrix3 {
    float m[9];
    Matrix3() {}
    Matrix3(const Matrix3& o);          // 0041CB40
};

extern Vector3 g_DefaultPos;                    // 015D22F0
extern Matrix3 g_IdentityMatrix;                // 015D2638
extern const float kZero;                       // 01485378
extern const float kDefaultDelay;               // 01488874 (0.1f)
extern const float kOne;                        // 01485720

// Transform-update message: flags select which parts are valid.
struct XformMsg {
    uint16_t flags;
    uint16_t count;
    Vector3  pos;
    float    scale;
    Matrix3  rot;
    XformMsg();
    XformMsg(void* src);                          // 0040CE80
    void SetPos(const Vector3& v)   { pos = v; flags |= 4; ++count; }
    void SetScale(float s)          { scale = s; ++count; }
    void SetRot(const Matrix3& m)   { rot = m; flags |= 2; ++count; }
};

// @ 0x00434040
XformMsg::XformMsg()
    : flags(0), count(0), pos(g_DefaultPos), scale(kOne), rot(g_IdentityMatrix)
{
    uint32_t u0, u1, u2, u3, u4, u5, u6, u7, u8, u9, u10;   // unused locals present in the original frame
}

struct Handle {
    virtual void AddRef();
    virtual void Release();
    virtual void v2();
    virtual void Stop(int);
    virtual bool IsPlaying();
    virtual void v5();
    virtual void SetXform(XformMsg*);
};

struct Mixer {
    virtual void p0();
    virtual void p1();
    virtual void p2();
    virtual void p3();
    virtual void p4();
    virtual void p5();
    virtual void p6();
    virtual void p7();
    virtual void p8();
    virtual void p9();
    virtual void p10();
    virtual void p11();
    virtual void p12();
    virtual void p13();
    virtual void p14();
    virtual void p15();
    virtual void p16();
    virtual void p17();
    virtual void p18();
    virtual void p19();
    virtual void p20();
    virtual void p21();
    virtual void p22();
    virtual void p23();
    virtual void p24();
    virtual void p25();
    virtual void p26();
    virtual void p27();
    virtual void p28();
    virtual void SetValue(uint32_t key, uint32_t id, float v, int flag);   // slot 0x74
    virtual void SetFade(uint32_t key, uint32_t id, float v, int flag);    // slot 0x78
};

struct Owner {
    uint32_t pad0[4];
    uint32_t key;      // +0x10
    uint32_t pad1;
    Mixer*   mixer;    // +0x18
    void* GetSource();       // 0043D220
    void  Refresh();         // 0043D420
};

struct EffectDef;
struct Factory { Handle* Create(); };                                  // 0045AC20
Factory* __stdcall GetFactory(EffectDef*, int, XformMsg*, void*);      // 00401050

// Intrusive smart pointer to a Handle.
struct HandlePtr {
    Handle* p;
    HandlePtr() : p(0) {}
    Handle* get() const { return p; }
    Handle* operator->() const { return p; }
    void reset(Handle* n) {
        if (p) {
            Handle* old = p;
            if (n) n->AddRef();
            p = n;
            if (old) old->Release();
        }
    }
    void assign(Handle* n) {
        if (n != p) {
            Handle* old = p;
            if (n) n->AddRef();
            p = n;
            if (old) old->Release();
        }
    }
};

struct FadeController {
    uint32_t   id;          // +0x00
    float      duration;    // +0x04
    float      time;        // +0x08
    float      fadeTime;    // +0x0C
    uint8_t    flag10;      // +0x10
    uint8_t    playing;     // +0x11
    uint16_t   pad12;
    EffectDef* effect;      // +0x14
    uint32_t   pad18[3];
    uint32_t   loopMode;    // +0x24
    uint8_t    flag28;      // +0x28
    uint8_t    fadingOut;   // +0x29
    uint16_t   pad2a;
    Owner*     owner;       // +0x2C
    HandlePtr  handle;      // +0x30

    FadeController();
    void SetOwner(Owner* o);
    void ReleaseHandle();
    void Update(float dt);
    uint8_t IsActive();
    uint8_t IsPlaying();
    void Stop();
    void FinishFade();     // 004341C0
};

// @ 0x004339f0
FadeController::FadeController()
    : id(0), duration(kZero), time(kZero), fadeTime(kDefaultDelay), flag10(0), playing(0),
      effect(0), flag28(1), fadingOut(0), owner(0), handle()
{
}

// @ 0x00433a80
void FadeController::SetOwner(Owner* o) { owner = o; }

// @ 0x00433aa0
void FadeController::ReleaseHandle()
{
    owner = 0;
    if (handle.get()) {
        handle->Stop(0);
        handle.reset(0);
    }
}

// @ 0x004340c0
uint8_t FadeController::IsActive() { return (playing && !fadingOut) ? 1 : 0; }

// @ 0x00434100
uint8_t FadeController::IsPlaying() { return playing; }

// @ 0x00434120
void FadeController::Stop()
{
    time = kZero;
    if (handle.get()) {
        handle->Stop(0);
        handle.reset(0);
    }
    fadingOut = 1;
}

// @ 0x00433b30
void FadeController::Update(float dt)
{
    if (playing) {
        bool wasExpired = (time > duration && fadingOut) ? 1 : 0;
        time = time + dt;

        if (!fadingOut) {
            float v = time;
            if (time > duration) {
                if (loopMode == 1) {
                    time = time - duration;
                    v = time;
                    if (effect) {
                        XformMsg src(owner->GetSource());
                        XformMsg msg;
                        msg.SetScale(src.scale);
                        msg.SetPos(src.pos);
                        msg.SetRot(src.rot);
                        handle.assign(GetFactory(effect, 0, &msg, this)->Create());
                    }
                } else {
                    v = duration;
                    Stop();
                }
            }
            Mixer* m = owner->mixer;
            uint32_t k = owner->key;
            m->SetValue(k, id, v, 0);
            owner->Refresh();
            if (handle.get() && handle->IsPlaying()) {
                XformMsg src(owner->GetSource());
                XformMsg msg;
                msg.SetScale(src.scale);
                msg.SetPos(src.pos);
                msg.SetRot(src.rot);
                handle->SetXform(&msg);
            }
        } else {
            if (time > fadeTime) {
                time = fadeTime;
                playing = 0;
            }
            if (time > kZero) {
                Mixer* m = owner->mixer;
                uint32_t k = owner->key;
                m->SetFade(k, id, kOne - time / fadeTime, 0);
            }
            if (!playing) FinishFade();
        }
    }
}

// ---- 0x00433800 ----
struct Property {
    uint8_t  pad[0x12];
    uint16_t type;
    int*     GetInt();          // 0041E990
};
struct PropertyList {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, Property** out);   // slot 0x24
};
struct Stat { uint32_t id; float value; };
struct StatTable { Stat* stats; };
extern uint32_t g_StatIds[6];                // 013EBD44
int FindStatIndex(uint32_t id);              // 004336A0 (cdecl)

// @ 0x00433800
void ApplyIntProperties(PropertyList* props, StatTable* table)
{
    int count = 6;
    for (int i = 0; i < count; i++) {
        int value = 0;
        uint32_t id = g_StatIds[i];
        bool ok;
        Property* prop;
        if (props && props->GetProperty(id, &prop) && prop->type == 9) {
            value = *prop->GetInt();
            ok = true;
        } else {
            ok = false;
        }
        if (ok) {
            int idx = FindStatIndex(g_StatIds[i]);
            if (idx != -1) {
                float* f = &table->stats[idx].value;
                *f = (float)value + *f;
            }
        }
    }
}

// @ 0x004338e0
struct StatVec {
    Stat* begin;
    Stat* end;
    void Resize(uint32_t n);
    void Grow(Stat* at, uint32_t cnt, const Stat* fill);    // 004CEF00
    void EraseTail(Stat* first, Stat* last);                // 00530C80
};
void StatVec::Resize(uint32_t n)
{
    if (n > (uint32_t)(end - begin)) {
        Stat fill;
        fill.value = *(const float*)&kOne;
        Stat* at;
        uint32_t add = n - (end - begin);
        at = end;
        uint32_t u0, u1, u2, u3, u4, u5;   // unused locals present in the original frame
        Grow(at, add, &fill);
    } else {
        EraseTail(begin + n, end);
    }
}

// @ 0x00433960
struct Bounds {
    Vector3 min;
    Vector3 max;
    uint32_t pad18;
    uint8_t flag;
    Bounds();
};
extern Vector3 g_DefaultBounds;                    // 015D255C
Bounds::Bounds()
    : min(g_DefaultBounds), max(g_DefaultBounds), pad18(0), flag(0)
{
}
