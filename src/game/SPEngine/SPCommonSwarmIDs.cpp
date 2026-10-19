// src/game/SPEngine/SPCommonSwarmIDs.cpp -- migrated from slice(s) s00ebdc20 by tools/migrate/rewrite.py
// Object file: SPEngine/SPCommonSwarmIDs.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cPlanetModel.h"
#include <math.h>

// ---- items of slice s00ebdc20 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vec3 { float x, y, z; };
struct Matrix3 {
    float m[9];
    Matrix3() {}
    Matrix3(const Matrix3& o);          // 0x0041cb40 (out of line copy)
};
extern Vec3 g_DefaultOffset;             // 0x016c7440
extern Matrix3 g_IdentityMatrix;         // 0x016c741c
struct TransformPod {                    // same layout as Transform, no constructor
    uint16_t mnFlags;
    uint16_t mnCount;
    Vec3     mOffset;
    float    mfScale;
    Matrix3  mRotation;
};
struct Quat { float x, y, z, w; };
struct EffectHandle {
    virtual void v0();
    virtual void Release();              // +4
    virtual void v2(int);                // +8
    virtual void Stop(int);              // +0xc
    virtual bool IsValid();              // +0x10
    virtual void v5();
    virtual void SetTransform(const void*);   // +0x18
};
struct EffectsManager {
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
    virtual void PlayEffect(uint32_t id, int flags, EffectHandle** out);   // +0x2c
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
    virtual struct EffectLibrary* GetLibrary(uint32_t id, int flags);        // +0x8c
};
struct EffectLibrary {
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
    virtual const Vec3* GetDirection(Vec3* out, const Vec3* pos);            // +0x28
};
EffectsManager* GetEffectsManager();     // 0x0067ddd0
struct PlanetModel {
    Quat* BuildSurfaceOrientation(Quat* out, const Vec3* pos);  // 0x00b7f190 (stdcall)
    const Vec3* SnapToSurface(Vec3* out, const Vec3* in);        // 0x00b81630 (stdcall)
};
PlanetModel* GetPlanetModel();           // 0x00b3d350
Matrix3* Matrix3FromQuaternion(Matrix3* out, const Quat* q);   // 0x0059c190 (cdecl)
struct Timer {                           // cSPTimer / cGonzagoTimer, 0x20 bytes
    uint32_t pad[8];
    uint64_t GetElapsedTime() const;     // 0x00bc3190
    void Restart();                      // 0x00bc3130
    ~Timer();                            // 0x00b638b0
};
struct EffectDef {
    uint32_t pad00;
    uint32_t effectIdA;       // +04
    uint32_t effectIdB;       // +08
    uint32_t animId;          // +0c
    uint32_t pad10;
    int      type;            // +14 : Update: 1 = point, 2 = segment; Tick: 1 = flying, 2/3 = surface snapped
    float    radius;          // +18
    float    segLen;          // +1c
    float    scale;           // +20
    uint32_t pad24[3];
    float    startDelay;      // +30
    float    lifetime;        // +34
    float    magnitude;       // +38
    uint8_t  continuous;      // +3c
    uint8_t  scaleByObj;      // +3d
    uint8_t  pad3e[2];
    float    mulNoFlagB;      // +40
    float    mulWithAnim;     // +44
    float    accel;           // +48
    float    moverScale;      // +4c
    uint8_t  useLibrary;      // +50
    uint8_t  followFocus;     // +51
};
struct Entry {                // 0x50 bytes
    EffectDef*   def;         // +00
    int          state;       // +04: 0 = waiting, 1 = just started, 2 = running
    float        radius;      // +08: distance from the planet centre the entry is kept at
    Vec3         pos;         // +0c
    Vec3         vel;         // +18
    uint32_t     pad24;
    Timer        timer;       // +28
    EffectHandle* effect1;    // +48: primary effect, oriented every tick
    EffectHandle* effect2;    // +4c: secondary effect created by the interaction pass
    Entry& operator=(const Entry& o);    // 0x00ebbc10
    __forceinline ~Entry()
    {
        if (effect2) effect2->Release();
        if (effect1) effect1->Release();
    }
};
struct Mover {                // component 0xb033b403
    uint32_t pad[0x1c5];
    int      state;           // +0x714
    float Radius();                          // 0x00c3be10
    void  Push(const Vec3* v, float dt);     // 0x00c37f70
};
struct GameObj {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual void ApplyImpulse(float mag, int a, int b, const Vec3* dir, int c);  // +0x18
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
    virtual float GetScale();                         // +0x58
    virtual void* Cast(uint32_t id);                  // +0x5c
};
struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char              mColor;
};
void EaFree(void*);                       // 0x00f47380 operator delete[]
struct WorldMap {
    uint32_t         mCompare;
    rbtree_node_base mAnchor;             // +4
    uint32_t         mnSize;              // +0x14
    uint32_t         mAllocator;
    void DoNukeSubtree(rbtree_node_base* pNode);   // 0x009a9600
    void reset()
    {
        mAnchor.mpNodeRight  = &mAnchor;
        mAnchor.mpNodeLeft   = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor       = 0;
        mnSize               = 0;
    }
    __forceinline void clear()
    {
        rbtree_node_base* pNode = mAnchor.mpNodeParent;
        while (pNode) {
            DoNukeSubtree(pNode->mpNodeRight);
            rbtree_node_base* const pNodeLeft = pNode->mpNodeLeft;
            EaFree(pNode);
            pNode = pNodeLeft;
        }
        reset();
    }
};
bool AreEffectsActive();                           // 0x00ebb8b0 (cdecl)
void GetFocusPoint(Vec3* out, Vec3* out2);         // 0x00ebb980 (cdecl)
const Vec3* OrthogonalVector(Vec3* out, const Vec3* in);   // 0x006985b0 (cdecl)
void RandomDiskPoint(float* out);                  // 0x00ebbb40 (cdecl)
struct Effects {
    uint32_t  pad00[2];
    Entry*    mpBegin;        // +08
    Entry*    mpEnd;          // +0c
    uint32_t  pad10[8];
    WorldMap  mWorlds;        // +0x30

    void Bake(GameObj* obj, float dt);               // 0x00ebc2f0
    void PostUpdate(Mover* mover, float dt);         // 0x00ebcc80
    void Finish(GameObj* obj);                       // 0x00ebbfb0
    void Update(GameObj* obj, float dt);             // 0x00ebdc20
    void PreUpdate(float dt);                        // 0x00ebd420
    void Tick(float dt);                             // 0x00ebe3e0
};
// ---- items of slice s00ebdc20 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern Vec3 g_DefaultOffset;             // 0x016c7440
extern Matrix3 g_IdentityMatrix;         // 0x016c741c

// @ 0x00ebe3e0
void Effects::Tick(float dt)
{
    PreUpdate(dt);
    bool active = AreEffectsActive();
    if (mpBegin == mpEnd)
        return;
    bool noEffects = !active;
    Entry* e = mpBegin;
    do {
        bool kill = noEffects;
        float el = (float)e->timer.GetElapsedTime() * 0.001f;
        EffectDef* d = e->def;
        if (e->state == 0) {
            if (el > d->startDelay) {
                e->timer.Restart();
                e->state = 1;
            }
        } else if ((unsigned)(e->state - 1) < 2) {
            if (el > d->lifetime)
                kill = true;
        }

        if (d->type == 1) {
            Vec3 n;
            if (d->followFocus) {
                Vec3 tgt, unused;
                GetFocusPoint(&tgt, &unused);
                float dx = tgt.x - e->pos.x;
                float dy = tgt.y - e->pos.y;
                float dz = tgt.z - e->pos.z;
                float inv = 1.0f / sqrtf((dx * dx + (dy * dy + dz * dz)) + 1e-8f);
                float k = d->accel;
                n.x = k * (inv * dx);
                n.y = (dy * inv) * k;
                n.z = (dz * inv) * k;
            } else if (d->useLibrary) {
                EffectLibrary* lib = GetEffectsManager()->GetLibrary(0x354a47b, 0);
                Vec3 tmp;
                const Vec3* q = lib->GetDirection(&tmp, &e->pos);
                n.x = q->x * 50.0f;
                n.y = q->y * 50.0f;
                n.z = q->z * 50.0f;
            } else {
                float px = e->pos.x;
                float inv = 1.0f / sqrtf((e->pos.y * e->pos.y + px * px) + e->pos.z * e->pos.z);
                Vec3 u;
                u.x = px * inv;
                u.y = e->pos.y * inv;
                u.z = e->pos.z * inv;
                Vec3 qtmp;
                const Vec3* q = OrthogonalVector(&qtmp, &u);
                float inv2 = 1.0f / sqrtf((q->x * q->x + q->y * q->y) + q->z * q->z);
                Vec3 w;
                w.x = q->x * inv2;
                w.y = q->y * inv2;
                w.z = q->z * inv2;
                Vec3 c;
                c.x = w.z * u.y - w.y * u.z;
                c.y = u.z * w.x - w.z * u.x;
                c.z = w.y * u.x - u.y * w.x;
                float inv3 = 1.0f / sqrtf(c.y * c.y + (c.z * c.z + c.x * c.x));
                Vec3 cn;
                cn.x = inv3 * c.x;
                cn.y = c.y * inv3;
                cn.z = c.z * inv3;
                float r[2];
                RandomDiskPoint(r);
                Vec3 dd;
                dd.x = r[0] * w.x + r[1] * cn.x;
                dd.y = w.y * r[0] + r[1] * cn.y;
                dd.z = w.z * r[0] + r[1] * cn.z;
                float k = d->accel * 0.3f;
                float inv4 = 1.0f / sqrtf((dd.y * dd.y + (dd.z * dd.z + dd.x * dd.x)) + 1e-8f);
                n.x = e->vel.x + ((inv4 * dd.x) * k) * dt;
                n.y = e->vel.y + ((dd.y * inv4) * k) * dt;
                n.z = e->vel.z + ((dd.z * inv4) * k) * dt;
            }
            float tx = dt * e->vel.x + e->pos.x;
            float ty = e->vel.y * dt + e->pos.y;
            float tz = e->vel.z * dt + e->pos.z;
            float inv5 = 1.0f / sqrtf(tx * tx + (tz * tz + ty * ty));
            float rad = e->radius;
            e->pos.x = rad * (inv5 * tx);
            e->pos.y = rad * (ty * inv5);
            e->pos.z = rad * (tz * inv5);
            e->vel = n;
        } else if ((unsigned)(d->type - 2) < 2) {
            Vec3 tmp;
            const Vec3* s = GetPlanetModel()->SnapToSurface(&tmp, &e->pos);
            e->pos.x = s->x;
            e->pos.y = s->y;
            e->pos.z = s->z;
        }

        TransformPod xf;
        xf.mnFlags = 0;
        xf.mnCount = 0;
        xf.mOffset = g_DefaultOffset;
        xf.mfScale = 1.0f;
        xf.mRotation = g_IdentityMatrix;
        xf.mOffset = e->pos;
        xf.mnFlags = 4;
        xf.mnCount = 1;
        xf.mfScale = d->scale;
        xf.mnCount = 2;
        Quat qtmp;
        Quat* q = GetPlanetModel()->BuildSurfaceOrientation(&qtmp, &e->pos);
        Matrix3 mtmp;
        xf.mRotation = *Matrix3FromQuaternion(&mtmp, q);
        xf.mnFlags |= 2;
        xf.mnCount++;
        e->effect1->SetTransform(&xf);

        if (kill) {
            e->effect1->Stop(0);
            if (e->effect2)
                e->effect2->Stop(0);
            *e = *(mpEnd - 1);
            mpEnd--;
            mpEnd->~Entry();
        } else {
            e++;
        }
    } while (e != mpEnd);
}
