// Slice s00a05c20: SP::cAnimatingCreature (anim_creature) - registration, construction,
// feedback-record queries and the anim target setters - plus
// cSPCreatureAnimWorld::UpdateAutoBaking.
//
// Layouts are retail offsets read off the disassembly; field names are Claude-coined.
// Module flags: /O2 /MD /Gy /TP /arch:SSE
#include "types.h"
#include <math.h>
#include <intrin.h>

typedef unsigned int uint;

// --------------------------------------------------------------------------- value types
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& o) : x(o.x), y(o.y), z(o.z) {}
    Vector3& operator=(const Vector3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Vector4 {
    float x, y, z, w;
    Vector4() {}
    Vector4(const Vector4& o) : x(o.x), y(o.y), z(o.z), w(o.w) {}
    Vector4& operator=(const Vector4& o) { x = o.x; y = o.y; z = o.z; w = o.w; return *this; }
};

struct BoundingBox {
    Vector3 mn;                         // +0x00
    Vector3 mx;                         // +0x0c
    void Reset();                       // 0x00409c00 (thiscall, ret 0)
    void Extend(const Vector3& v);      // 0x0041bd50 (thiscall, ret 4)
};

// --------------------------------------------------------------------------- forward decls
struct anim_creature;
struct queued_blender;
struct creature_instance_data;

struct RefObj {                         // resource object returned by the creator vtable
    uint32_t pad00;                     // +0x00
    uint32_t flags;                     // +0x04
    uint32_t pad08[0x38 / 4];           // +0x08 .. +0x3f
    uint32_t refcount;                  // +0x40
    uint32_t pad44[(0x6c - 0x44) / 4];  // +0x44 .. +0x6b
    float    f6c;                       // +0x6c
    BoundingBox box;                    // +0x70
};

struct Creator {
    virtual RefObj* slot0();
    virtual RefObj* slot1();
    virtual RefObj* slot2();
    virtual RefObj* Create(uint32_t a, uint32_t b, uint32_t c);   // vtable slot 3 (vtbl+0xc)
};

struct AnimData {                       // *(creature_instance_data + 0)
    uint8_t pad[0x358];
    float   minx, miny, minz;           // +0x358
    float   sizeX, sizeY, sizeZ;        // +0x364
    float   f370;                       // +0x370
};

struct creature_instance_data {
    void*    field0;                    // +0x000
    uint32_t pad04[(0x2c0 / 4) - 1];    // +0x004
    void*    model;                     // +0x2c0
};

struct queued_blender {
    void SetBakeParam(float dt, bool first);                                                    // 0x009ff4b0 (ret 8)
    void UpdateCreatureBodies(uint a1, float a2, float a3, uint a4, uint a5, uint a6, float a7); // 0x00a010c0 (ret 0x1c)
};

// --------------------------------------------------------------------------- anim_creature
struct anim_creature {                  // 0x19c bytes
    void*    vtbl;                      // +0x00 (set explicitly by the ctor)

    Vector3  mPos;                      // +0x04
    Vector4  mRot;                      // +0x10
    uint32_t pad20[7];                  // +0x20 .. +0x3b
    float    f3c;                       // +0x3c
    float    f40, f44, f48, f4c;        // +0x40 .. +0x4c
    uint32_t f50;                       // +0x50
    uint32_t f54;                       // +0x54
    uint32_t f58;                       // +0x58
    uint32_t pad5c;                     // +0x5c
    uint32_t f60;                       // +0x60
    uint8_t  f64;                       // +0x64
    uint8_t  pad65[3];
    float    slots[7];                  // +0x68 .. +0x83
    uint8_t  f84;                       // +0x84
    uint8_t  pad85[3];
    uint32_t f88;                       // +0x88
    struct { int32_t a, b; uint32_t c; } arr8c[16];  // +0x8c .. +0x14b
    uint32_t f14c;                      // +0x14c
    uint8_t  f150;                      // +0x150
    uint8_t  f151;                      // +0x151
    uint8_t  pad152[2];
    uint32_t f154;                      // +0x154
    uint32_t f158;                      // +0x158
    anim_creature* f15c;                // +0x15c
    uint32_t f160;                      // +0x160
    float    f164;                      // +0x164
    float    f168;                      // +0x168
    float    f16c;                      // +0x16c
    uint32_t f170;                      // +0x170
    int32_t  f174;                      // +0x174
    uint32_t f178;                      // +0x178
    creature_instance_data* instance;   // +0x17c
    RefObj*  f180;                      // +0x180
    queued_blender* blender;            // +0x184
    uint32_t f188;                      // +0x188
    uint32_t f18c;                      // +0x18c
    void*    world;                     // +0x190
    uint32_t f194;                      // +0x194
    int32_t  f198;                      // +0x198

    anim_creature(const Vector3& pos, const Vector4& rot);   // 0x00a05d60 (ret 8)

    void  Release();                                          // 0x00a05270
    void  SetTargetRoot(anim_creature* target);               // 0x00a06250
    void  SetTargetBody(anim_creature* target, uint value);   // 0x00a062a0
    float GetFeedbackValue(uint key);                         // 0x00a060a0
};

// forward-declare the vtable (relocation target for the ctor's vptr store)
extern void* const s_animCreatureVtbl[];

// --------------------------------------------------------------------------- free functions
void __cdecl RegisterCreature(anim_creature* ac);   // 0x00a05c20
void __cdecl UpdateBakeTarget(anim_creature* ac, uint value, bool b);   // 0x00a04630

// --------------------------------------------------------------------------- feedback rbtree
struct FeedbackRecord {                 // 0x1c bytes
    float    f0;
    float    f4;
    uint32_t f8;
    uint32_t fC;
    uint32_t f10;
    uint32_t f14;
    uint32_t f18;
};

struct FeedbackEvent {                  // 0x18 bytes
    FeedbackRecord* begin;              // +0x00
    FeedbackRecord* end;                // +0x04
    uint32_t f08, f0c, f10;             // +0x08
    float    time;                      // +0x14
};

struct FeedbackNode {
    uint32_t        pad00[0x10];        // +0x00 .. +0x3f
    FeedbackEvent*  begin;              // +0x40
    FeedbackEvent*  end;                // +0x44
};

struct FeedbackTree {                   // rbtree<unsigned, ...>
    void find(FeedbackNode** pResult, const uint* key);   // 0x00e5c780 (ret 8)
};

extern FeedbackTree g_feedbackTree;     // 0x01551a68
extern FeedbackNode g_feedbackEnd;      // 0x01551a6c (end sentinel node)

struct OutRec {                         // feedback output record (3 dwords)
    int32_t z;
    float   y;
    float   x;
};

struct Rng {
    double GenerateDouble();            // 0x009362d0 (ret 0)
};
extern Rng g_rng;                       // 0x0166cd30

extern uint32_t* g_feedbackTime;        // 0x0166cc08 (+0x14 holds the time stamp)

// --------------------------------------------------------------------------- thiscall callees
// lookup helpers are free cdecl functions
bool  __cdecl LookupA(void* data, uint key, void** pOut);           // 0x009a38f0
void* __cdecl LookupB(void* a, uint key, void* c);                  // 0x009a4430
uint  __cdecl LookupC(void* data, void* o);                         // 0x009a4550

struct XC {                             // object helpers (Prepare / Release)
    void  Prepare();                                            // 0x0099c660
    void  Release();                                            // 0x0099d060
    uint32_t pad[0x11c / 4];
    float f11c;                                                 // +0x11c
    float f120;                                                 // +0x120
};

struct FbHandle {                       // object looked up into `p`
    void Release();                                             // 0x0099f0b0
};

// --------------------------------------------------------------------------- anim world
struct Variant {                        // 0x14 bytes
    void*    mValue;                    // +0x00
    uint32_t pad04[3];                  // +0x04 .. +0x0f
    uint16_t mFlags;                    // +0x10
    uint16_t mType;                     // +0x12
    void Destruct(bool b);              // 0x0093db80 (thiscall, ret 4)
};

struct PropHolder {                     // property bag at mManager + 0x50
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual Variant* GetProperty(uint32_t id);          // slot 10 (vtbl+0x28)
};

struct cViewer {
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4();
    virtual void c5(); virtual void c6(); virtual void c7(); virtual void c8(); virtual void c9();
    virtual void c10(); virtual void c11();
    virtual void* c12(uint32_t a);                      // slot 12 (vtbl+0x30)

    void GetCameraLocationInfo(Vector3* out, int a, int b, int c);   // 0x007c3d30 (ret 0x10)
};

struct AnimWorld {
    virtual void w0();  virtual void w1();  virtual void w2();  virtual void w3();  virtual void w4();
    virtual void w5();  virtual void w6();  virtual void w7();  virtual void w8();  virtual void w9();
    virtual void w10(); virtual void w11(); virtual void w12(); virtual void w13(); virtual void w14();
    virtual void w15(); virtual void w16(); virtual void w17(); virtual void w18(); virtual void w19();
    virtual void w20();
    virtual uint w21(uint a, float b);                  // slot 21 (vtbl+0x54)

    uint32_t pad04[6];                  // +0x04 .. +0x1b
    void*    mManager;                  // +0x1c
    uint32_t mSeq;                      // +0x20
    anim_creature** mpBegin;            // +0x24
    anim_creature** mpEnd;              // +0x28
    uint32_t pad2c[8];                  // +0x2c .. +0x4b
    void*    mEffectsWorld;             // +0x4c
    uint8_t  pad50[0x3038 - 0x50];      // +0x50 .. +0x3037
    uint8_t  mAutoBaking;               // +0x3038

    void UpdateAutoBaking(float dt, cViewer* viewer);   // 0x00a06310 (ret 8)
};

struct VariantBuilder {
    void SetU32(uint32_t* pValue);      // 0x00422eb0 (thiscall, ret 4)
};

// --------------------------------------------------------------------------- externs
extern float g_variantFloatDefault;     // 0x015d1168
extern uint32_t g_variantUintDefault;   // 0x015d9c68
extern uint8_t  g_variantBoolDefault;   // 0x015d9c70
extern float    g_f1;                   // 0x015518e0..ec (1.0f x4) -- four separate slots
extern float    g_f2;
extern float    g_f3;
extern float    g_f4;
extern const float g_half;              // 0x01471064
extern const float g_one;               // 0x01485720
extern const float g_neg10;             // 0x013f561c
extern const float g_zero;              // 0x01485378
extern const float g_tenth;             // 0x01550a88
extern const double g_tenthD;           // 0x01447a10

cViewer* __cdecl GetViewer();           // 0x0067dd50

// =========================================================================== 0x00a05c20
// @ 0x00a05c20
void __cdecl RegisterCreature(anim_creature* ac)
{
    void* model = ac->instance->model;
    if (model != 0) {
        ac->f180 = (RefObj*)*(uint32_t*)((char*)model + 8);
        return;
    }
    if (ac->f180 != 0)
        return;

    Creator* creator = *(Creator**)((char*)ac->world + 0x44);
    ac->f180 = creator->Create(0x2ebcd6a6u, 0xd94352edu, 0);
    ac->f180->refcount++;
    if (ac->f180 == 0)
        return;

    ac->f180->flags |= 0x200;
    ac->f180->box.Reset();

    AnimData* data = *(AnimData**)ac->instance;

    Vector3 mn, mx;
    mn.x = data->minx;
    mn.y = data->miny;
    mn.z = data->minz;
    mx.x = data->sizeX + data->minx;
    mx.y = data->sizeY + data->miny;
    mx.z = data->sizeZ + data->minz;

    ac->f180->box.Extend(mn);
    ac->f180->box.Extend(mx);
    ac->f180->f6c = data->f370 * g_half;
}

// =========================================================================== 0x00a05d60
// @ 0x00a05d60
anim_creature::anim_creature(const Vector3& pos, const Vector4& rot)
{
    *(void**)this = (void*)s_animCreatureVtbl;

    mPos = pos;
    mRot = rot;

    f3c  = 1.0f;
    f40  = 0.0f;
    f44  = 0.0f;
    f48  = 0.0f;
    f4c  = 0.0f;
    f50  = 0;
    f54  = 4;
    f58  = 0;
    f64  = 1;
    slots[3] = g_f1;
    slots[4] = g_f2;
    slots[5] = g_f3;
    slots[6] = g_f4;
    f84  = 0;
    f88  = 1;
    {
        int32_t* p = (int32_t*)arr8c;
        for (int i = 15; i >= 0; --i) {
            p[0] = -1;
            p[1] = -1;
            p[2] = 0;
            p += 3;
        }
    }
    f150 = 1;
    f154 = 1;
    f14c = 0;
    f151 = 0;
    f158 = 0;
    f15c = 0;
    f160 = 0;
    _ReadWriteBarrier();
    f164 = 0.0f;
    f168 = -10.0f;
    f16c = 1.0f;
    f170 = 0;
    f174 = -1;
    f178 = 0;
    instance = 0;
    _ReadWriteBarrier();
    f180 = 0;
    blender = 0;
    f188 = 0;
    f18c = 0;
    f194 = 0;
    f198 = 0;
}

// =========================================================================== 0x00a05ee0
// @ 0x00a05ee0
uint __cdecl GetFeedbackRecords(uint key, uint unused, OutRec* out, uint maxCount, uint* outTime)
{
    FeedbackNode* it;
    g_feedbackTree.find(&it, &key);

    if (out == 0 || it == &g_feedbackEnd)
        return 0;

    uint n = (uint)(it->end - it->begin);
    uint pick = 0;
    if (n > 1) {
        double r = g_rng.GenerateDouble();
        for (uint i = 0; i < n; ++i) {
            if (r < it->begin[i].time) {
                pick = i;
                break;
            }
        }
    }

    FeedbackEvent* e = it->begin + pick;
    uint count = (uint)(e->end - e->begin);
    uint num   = maxCount < count ? maxCount : count;

    for (uint i = 0; i < num; ++i) {
        out[i].z = (int32_t)e->begin[i].f8;
        out[i].y = e->begin[i].f4;
        out[i].x = e->begin[i].f0;
    }

    if (outTime != 0)
        *outTime = g_feedbackTime[5];

    return num;
}

// =========================================================================== 0x00a060a0
// @ 0x00a060a0
float anim_creature::GetFeedbackValue(uint key)
{
    FeedbackNode* it;
    g_feedbackTree.find(&it, &key);

    if (it == &g_feedbackEnd)
        return 0.0f;

    uint n = (uint)(it->end - it->begin);
    if (n != 1)
        return 0.0f;

    FeedbackEvent* e = it->begin;
    uint cnt = (uint)(e->end - e->begin);
    if (cnt == 0)
        return 0.0f;

    for (uint i = 0; i < cnt; ++i) {
        FeedbackRecord* rec = e->begin + i;
        FbHandle* p = 0;
        bool ok = LookupA(*(void**)instance, rec->f8, (void**)&p);
        if (!ok) {
            XC* o = (XC*)LookupB(0, rec->f8, 0);
            if (o != 0) {
                o->Prepare();
                if (LookupC(*(void**)instance, o) != 0) {
                    o->Release();
                    if (p != 0) p->Release();
                } else {
                    o->Release();
                    if (p != 0) p->Release();
                    continue;
                }
            } else {
                if (p != 0) p->Release();
                continue;
            }
        } else {
            if (p != 0) p->Release();
        }

        float level = rec->f4;
        if (level >= g_zero)
            return rec->f0 * level;

        XC* o2 = (XC*)LookupB(0, rec->f8, 0);
        if (o2 == 0)
            return 0.0f;
        o2->Prepare();
        float v = (o2->f120 - g_one) * o2->f11c * rec->f0;
        o2->Release();
        return v;
    }
    return 0.0f;
}

// =========================================================================== 0x00a06250
// @ 0x00a06250
void anim_creature::SetTargetRoot(anim_creature* target)
{
    f154 = 0;
    f158 = 1;
    anim_creature* old = f15c;
    if (target != old) {
        if (target != 0)
            target->f198++;
        f15c = target;
        if (old != 0)
            old->Release();
    }
    f160 = 0;
}

// =========================================================================== 0x00a062a0
// @ 0x00a062a0
void anim_creature::SetTargetBody(anim_creature* target, uint value)
{
    f154 = 0;
    f158 = 2;
    anim_creature* old = f15c;
    if (target == old) {
        f160 = value;
        return;
    }
    if (target != 0)
        target->f198++;
    f15c = target;
    if (old != 0)
        old->Release();
    f160 = value;
}

// =========================================================================== 0x00a06310
// @ 0x00a06310
void AnimWorld::UpdateAutoBaking(float dt, cViewer* viewer)
{
    AnimWorld* world = this;
    if (world->mpBegin == world->mpEnd)
        return;

    PropHolder* props = (PropHolder*)((char*)world->mManager + 0x50);

    Variant* dv = props->GetProperty(0xf29f5604u);
    float dtScale;
    {
        uint16_t t = dv->mType;
        float* p;
        if (t == 0xd || t == 0x10)
            p = (dv->mFlags & 0x30) ? (float*)dv->mValue : (t ? (float*)dv : 0);
        else
            p = &g_variantFloatDefault;
        dtScale = *p;
    }
    dt = dtScale * dt;

    uint32_t flag;
    bool     madeVariant = false;
    Variant  tmp;
    if (world->mAutoBaking) {
        Variant* fv = props->GetProperty(0xda61d1cu);
        uint16_t t = fv->mType;
        if (t == 9 || t == 0x10) {
            if (fv->mFlags & 0x30)
                flag = *(uint32_t*)fv->mValue;
            else
                flag = t ? *(uint32_t*)fv : 0;
        } else {
            flag = g_variantUintDefault;
        }
    } else {
        tmp.mFlags = 0;
        tmp.mType  = 0;
        uint32_t zero = 0;
        ((VariantBuilder*)&tmp)->SetU32(&zero);
        madeVariant = true;
        uint16_t t = tmp.mType;
        if (t == 9 || t == 0x10) {
            if (tmp.mFlags & 0x30)
                flag = *(uint32_t*)tmp.mValue;
            else
                flag = t ? *(uint32_t*)&tmp : 0;
        } else {
            flag = g_variantUintDefault;
        }
    }
    if (madeVariant && (tmp.mFlags & 4))
        tmp.Destruct(false);

    bool  bakeFlag;
    {
        Variant* bv = props->GetProperty(0xe0e98b25u);
        uint16_t t = bv->mType;
        if (t == 1 || t == 0x10) {
            if (bv->mFlags & 0x30)
                bakeFlag = *(uint8_t*)bv->mValue != 0;
            else
                bakeFlag = t ? (*(uint8_t*)bv != 0) : false;
        } else {
            bakeFlag = g_variantBoolDefault != 0;
        }
    }

    Vector3 camPos;
    cViewer* v = viewer;
    if (v == 0) {
        v = (cViewer*)GetViewer()->c12(0);
    }
    if (v != 0)
        v->GetCameraLocationInfo(&camPos, 0, 0, 0);

    uint n = (uint)(world->mpEnd - world->mpBegin);
    for (uint i = 0; i < n; ++i) {
        anim_creature* ac = world->mpBegin[i];
        if (!ac->f64)
            continue;
        uint idx = ac->f54 == 4 ? ac->f50 : ac->f54;
        ac->blender->SetBakeParam(dt, idx == 0);
    }

    float power = (float)pow((double)(dt / 0.1f), 0.1);

    uint m = (uint)(world->mpEnd - world->mpBegin);
    for (uint i = 0; i < m; ++i) {
        anim_creature* ac = world->mpBegin[i];
        if (!ac->f64)
            continue;
        uint idx = ac->f54 == 4 ? ac->f50 : ac->f54;
        uint handle = *(uint*)&ac->slots[idx];
        creature_instance_data* inst = ac->instance;

        float dz = camPos.z - *(float*)((char*)inst + 0x20);
        float dy = camPos.y - *(float*)((char*)inst + 0x1c);
        float dx = camPos.x - *(float*)((char*)inst + 0x18);
        float distSq = dz * dz + dy * dy + dx * dx;

        uint shouldBake = world->w21(handle, distSq);
        ac->blender->UpdateCreatureBodies(
            (uint)(size_t)world->mEffectsWorld, dt, power, idx == 0, shouldBake, handle, distSq);

        if (ac->instance != 0) {
            RegisterCreature(ac);
            uint state;
            if (flag == 0xffffffffu)      state = 0;
            else if (flag == 1)           state = 1;
            else                          state = ac->f88 & 1;
            UpdateBakeTarget(ac, flag, state == 0);
        }
    }

    world->mSeq++;
}
