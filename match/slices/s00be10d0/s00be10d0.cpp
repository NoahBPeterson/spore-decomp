// Slice s00be10d0: 0x00be1860 (1563 bytes, thiscall(int otherId, float amount, Ctx* ctx), ret 0xc).
//
// A creature/civ took part in a fight: scales `amount` into a "damage" value (x1/6, x1/3 more when
// the other side is this object's own owner), credits it to the civ, shows a floating "+N" number
// effect when the camera looks towards the target, records a relationship event, accumulates the
// value in a per-other map and posts an event line. Finally pushes the counters to a global tracker.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (SSE scalar float, no EH).
#include "types.h"

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float a, float b, float c) : x(a), y(b), z(c) {}
    Vec3(const Vec3& o) : x(o.x), y(o.y), z(o.z) {}
};

struct Zero3 { int a, b, c; };

struct XformMsg {        // 0x38 bytes: flags, count, pos(+4), scale(+0x10), rot(+0x14)
    char pad[0x38];
    XformMsg();          // 0x00434040
    void Set(const void* x);   // 0x00571d40
};

struct string16 { wchar_t* b; wchar_t* e; wchar_t* c; unsigned a; };

struct StrObj {          // 0x1c bytes, ref counted; wide string at +0xc
    virtual void AddRef();
    virtual void Release();
    int rc;
    int pad;
    string16 s;
    StrObj();            // 0x0057a6d0
};

template <class T>
struct Ref {             // EA::AutoRefCount<T> (ctor out-of-line at 0x00572660)
    T* p;
    __declspec(noinline) Ref(T* q) : p(q) { if (q) q->AddRef(); }   // 0x00572660 (out of line)
    ~Ref() { if (p) p->Release(); }
};

struct IFx {
    virtual void v0();
    virtual void Release();                 // +4
    virtual void Show(int x);               // +8
    virtual void v3(); virtual void v4(); virtual void v5();
    virtual void SetXform(XformMsg* m);     // +0x18
    virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17(); virtual void v18();
    virtual void SetObj(int kind, StrObj* o);   // +0x4c
};

struct FxPtr {
    IFx* p;
    FxPtr() : p(0) {}
    ~FxPtr() { if (p) p->Release(); }
    void reset() { if (p) { IFx* o = p; p = 0; o->Release(); } }
};

struct EffMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual void Create(unsigned id, int zero, FxPtr* out);   // +0x2c
};

struct Pos {             // sub-object with a vtable (at Cls+0x120 and Ctx+0x34)
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual void* GetPos();                // +0x2c
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21();
    virtual bool IsActive();               // +0x58
};

struct Noun {            // civ-like object
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual int GetId();                   // +0x4c
    char pad[0x40 - 4 - 19 * 0 - 0];
    int f40;
    char pad2[0x89 - 0x44];
    bool flag89;
    void __thiscall Credit(float v, int one);   // 0x00befd80
    char* __thiscall Stats();                   // 0x00bef950
};

struct NounMgr {
    Noun* __thiscall Find(int id);              // 0x00b25f40
    Noun* __thiscall GetPlayerCivilization();   // 0x00b25fb0
};

struct Cam { Vec3* __thiscall GetAnchorDirection1(); };   // 0x00b10260

struct FloatMap { float* __thiscall Get(int* key); };      // 0x00be0790

struct Tracker { void __thiscall Update(int count, int v, float f); };   // 0x00ceead0

struct Ctx {
    char pad[0x34];
    Pos p34;
    char pad2[0xc50 - 0x38];
    float f;
};

NounMgr* NounManager();                        // 0x00b3d300
EffMgr* EffectsManager();                      // 0x0067ddd0
Cam* GetCameraCtl();                           // 0x00b3d280
Vec3* __cdecl normalized_safe(Vec3* out, const Vec3* in);   // 0x00449c20
void* operator new(unsigned size, const char* tag, int a, int b, int c, int d);   // 0x00f473a0
void SetNumberString(__int64 value, wchar_t* buffer, int bufferSize);    // 0x00881ae0
void __cdecl WStr_Format(void* str, const wchar_t* fmt, ...);            // 0x0041e050
void __cdecl PostEvent(int id, char* a, char* b, Zero3* z, int pcF40, int srcF40, unsigned val);   // 0x00e3c7c0
struct Rel { float __thiscall RecordEvent(int a, int b, int key, float f); };   // 0x00d06240
Rel* RelationshipManager();                    // 0x00b3d2c0
__forceinline int RoundToInt(float f) { __asm cvtss2si eax, f }

struct Cls {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual int GetId();                   // +0x4c
    char pad0[0x120 - 4];
    Pos sub;                               // +0x120
    char pad1[0x340 - 0x124];
    int* vb;                               // +0x340
    int* ve;                               // +0x344
    char pad2[0x570 - 0x348];
    FloatMap map570;                       // +0x570 (rb-tree header; real layout unknown)
    char pad3[0x590 - 0x570 - sizeof(FloatMap)];
    Noun* n590;                            // +0x590
    char pad4[0x64c - 0x594];
    int f64c;                              // +0x64c
    void __thiscall Fn(int otherId, float amount, Ctx* ctx);   // 0x00be1860
};

extern Tracker g_tracker;   // 0x0169c254

static inline void PopupNumber(Ctx* ctx, float value)
{
}

// @ 0x00be1860
void __thiscall Cls::Fn(int otherId, float amount, Ctx* ctx)
{
    bool same = otherId == GetId();
    float dmg = amount * 0.16666667f;
    if (same) dmg = dmg * 0.33333334f;
    if (dmg > 0.0f) {
        float big = dmg * 8.0f;
        n590->Credit(big, 1);
        if (sub.IsActive() && GetCameraCtl()) {
            Vec3 t1;
            Vec3 d = *GetCameraCtl()->GetAnchorDirection1();
            Vec3* n1 = normalized_safe(&t1, &d);
            Vec3* n2 = normalized_safe(&d, (const Vec3*)sub.GetPos());
            if (0.6f < (n2->z * n1->z + n2->y * n1->y) + n1->x * n2->x) {
                FxPtr fx;
                EffMgr* em = EffectsManager();
                fx.reset();
                em->Create(0xdbf1ae1f, 0, &fx);
                if (fx.p) {
                    XformMsg m;
                    m.Set(ctx->p34.GetPos());
                    fx.p->SetXform(&m);
                    StrObj* o = new ("Simulator", 0, 0, 0, 0) StrObj();
                    Ref<StrObj> r(o);
                    wchar_t buf[64];
                    SetNumberString((__int64)RoundToInt(big), buf, 0x40);
                    buf[63] = 0;
                    StrObj* so = r.p;
                    WStr_Format(&so->s, L"%lc%lc%ls", 0x268a, 0x2b, buf);
                    fx.p->SetObj(8, so);
                    fx.p->Show(0);
                }
            }
        }
        float small = dmg * 4.0f;
        Noun* noun = NounManager()->Find(otherId);
        noun->Credit(small, 1);
        if (noun == NounManager()->GetPlayerCivilization() && GetCameraCtl()) {
            Vec3 t1;
            Vec3 d = *GetCameraCtl()->GetAnchorDirection1();
            Vec3* n1 = normalized_safe(&t1, &d);
            Vec3* n2 = normalized_safe(&d, (const Vec3*)sub.GetPos());
            if (0.6f < (n2->z * n1->z + n2->y * n1->y) + n1->x * n2->x) {
                FxPtr fx;
                EffMgr* em = EffectsManager();
                fx.reset();
                em->Create(0xdbf1ae1f, 0, &fx);
                if (fx.p) {
                    XformMsg m;
                    m.Set(ctx->p34.GetPos());
                    fx.p->SetXform(&m);
                    StrObj* o = new ("Simulator", 0, 0, 0, 0) StrObj();
                    Ref<StrObj> r(o);
                    wchar_t buf[64];
                    SetNumberString((__int64)RoundToInt(small), buf, 0x40);
                    buf[63] = 0;
                    StrObj* so = r.p;
                    WStr_Format(&so->s, L"%lc%lc%ls", 0x268a, 0x2b, buf);
                    fx.p->SetObj(8, so);
                    fx.p->Show(0);
                }
            }
        }
        if (!same) {
            RelationshipManager()->RecordEvent(GetId(), noun->GetId(), 0x526e4ee, 1.0f);
            RelationshipManager()->RecordEvent(noun->GetId(), GetId(), 0x526e4ee, 1.0f);
        }
        int key = otherId;
        *map570.Get(&key) += dmg;
        bool cached = noun->flag89;
        if (sub.IsActive() != cached) {
            Noun* src;
            unsigned val;
            int x, pcf;
            if (sub.IsActive()) {
                src = noun;
                x = noun->f40;
                pcf = NounManager()->GetPlayerCivilization()->f40;
                val = (unsigned)big;
            } else if (noun->flag89) {
                src = n590;
                x = n590->f40;
                pcf = NounManager()->GetPlayerCivilization()->f40;
                val = (unsigned)small;
            } else {
                goto done;
            }
            {
                Zero3 z = { 0, 0, 0 };
                PostEvent(0x8452100, NounManager()->GetPlayerCivilization()->Stats() + 0x504,
                          src->Stats() + 0x504, &z, pcf, x, val);
            }
        }
    }
done:
    g_tracker.Update(ve - vb, f64c, ctx->f);
}
