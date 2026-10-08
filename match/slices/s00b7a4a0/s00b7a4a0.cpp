// Slice s00b7a4a0 -- 0x00b7a880: per-frame update of the paired "beam" light objects that
// are attached to the nearby interactable objects around the current aim point.
#include "types.h"
#include <math.h>

struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float ax, float ay, float az) { x = ax; y = ay; z = az; }
};
// per-field float copy (movss) instead of the integer copy of a plain POD
struct FVec3 : Vec3 {
    FVec3() {}
    FVec3(const FVec3& o) { x = o.x; y = o.y; z = o.z; }
    FVec3& operator=(const FVec3& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Mat3 { float m[9]; };
struct Quat { float x, y, z, w; };

extern FVec3 g_zeroVec;     // 0x01687ad4
extern FVec3 g_axisVec;     // 0x016880e0
extern Mat3 g_identity;    // 0x016880f0

struct Light;
struct SrcObj;

#define VPAD10(p) virtual void p##0(); virtual void p##1(); virtual void p##2(); virtual void p##3(); \
    virtual void p##4(); virtual void p##5(); virtual void p##6(); virtual void p##7(); \
    virtual void p##8(); virtual void p##9();

struct LightOwner {
    VPAD10(a) VPAD10(b) VPAD10(c) VPAD10(d) VPAD10(e) VPAD10(f) VPAD10(g) VPAD10(h) VPAD10(i)
    virtual void pad90();
    virtual void Update(Light* l, int flag);   // slot 91 (+0x16c)
};

struct Transform { uint32_t pad[5]; Mat3 mat; };

struct SrcObj {
    virtual void AddRef();
    virtual void Release();
    uint32_t pad[13];
    Vec3 pos;          // +0x38
    float padA;        // +0x44
    float sizeA;       // +0x48
    float sizeB;       // +0x4c
    Transform* GetTransform();   // 0x00b73e70
};

struct Light {
    LightOwner* owner;   // +0x00
    uint32_t flags;      // +0x04
    uint16_t dirty;      // +0x08
    uint16_t dirtyCount; // +0x0a
    Vec3 pos;            // +0x0c
    float scale;         // +0x18
    Mat3 mat;            // +0x1c
    uint32_t pad40[9];
    SrcObj* ref;         // +0x64
    uint32_t pad68;
    float radius;        // +0x6c
    Vec3 bmin;           // +0x70
    Vec3 bmax;           // +0x7c
    void Mark(uint16_t f) { dirty |= f; dirtyCount++; }
};

struct Located {
    virtual void l0(); virtual void l1(); virtual void l2(); virtual void l3(); virtual void l4();
    virtual void l5(); virtual void l6(); virtual void l7(); virtual void l8(); virtual void l9();
    virtual void l10();
    virtual const Vec3* GetPosition();     // +0x2c
    virtual const Quat* GetOrientation();  // +0x30
};

struct Avatar { uint32_t pad[0xc0 / 4]; Located loc; };

struct NounManager {
    Avatar* GetAvatar();   // 0x00b1fdb0
};

struct Viewer {
    void GetCameraLocationInfo(Vec3* a, Vec3* b, Vec3* c, Vec3* d);   // 0x007c3d30
};

struct ViewerHolder {
    virtual void h0(); virtual void h1(); virtual void h2(); virtual void h3(); virtual void h4();
    virtual void h5(); virtual void h6();
    virtual Viewer* GetViewer();           // +0x1c
};
struct AppSub {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual ViewerHolder* GetHolder();     // +0x50
};
struct AppObj { virtual void a0(); virtual void a1(); };

struct AimSource {
    virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
    virtual void m5(); virtual void m6(); virtual void m7(); virtual void m8(); virtual void m9();
    virtual void m10(); virtual void m11(); virtual void m12(); virtual void m13();
    virtual Vec3* GetPoint(Vec3* out, int flag, FVec3 hint);   // +0x38
};

struct BeamArea {
    void GetEndPoints(Vec3* start, Vec3* end);   // 0x00cb8ba0
};
struct SpaceToolData {
    uint32_t pad[0x124 / 4];
    BeamArea* area;          // +0x124
    uint32_t pad2[(0x174 - 0x128) / 4];
    uint32_t flags174;
    bool HasFlag();                                       // 0x0104cd50
    void* GetStrategy();                                  // 0x0104f930
};
struct Inventory {
    SpaceToolData* GetTool();     // 0x00ff3f00
};
struct SpaceGame {
    Inventory* GetPlayerInventory();   // 0x00a1ad60
};

struct PtrVec {
    SrcObj** begin;
    SrcObj** end;
    SrcObj** cap;
    int zero;
    SrcObj* buf[256];
};

struct BeamMgr;
AppSub* __cdecl App();                       // 0x0067dd10
unsigned __cdecl GetCurrentGameMode();       // 0x00b5b800
NounManager* __cdecl GetNounManager();       // 0x00b3d300
SpaceGame* __cdecl SpaceGameGet();           // 0x01002bd0
AimSource* __cdecl GetAimSource();           // 0x00b3d240
Vec3* __cdecl RotateByQuat(Vec3* out, const Vec3* v, const Quat* q);   // 0x0059aed0
void __cdecl operator_delete_array(void* p);                          // 0x00f47380 (operator delete[])

struct BeamMgr {
    uint32_t pad0[0x5508 / 4];
    Light** lightBegin;       // +0x5508
    Light** lightEnd;         // +0x550c
    uint32_t pad1[(0x55a0 - 0x5510) / 4];
    uint32_t objMask;         // +0x55a0
    void Gather(const Vec3* pos, PtrVec* out, uint32_t mask, float radius, char flag, Vec3* extra); // 0x00b79c30
    void UpdateBeams();       // 0x00b7a880
};

// BeamMgr::UpdateBeams @ 0x00b7a880
void BeamMgr::UpdateBeams()
{
    Viewer* viewer = App()->GetHolder()->GetViewer();
    Vec3 camPos(g_zeroVec.x, g_zeroVec.y, g_zeroVec.z);
    Vec3 camDir(g_zeroVec.x, g_zeroVec.y, g_zeroVec.z);
    if (viewer)
        viewer->GetCameraLocationInfo(&camPos, &camDir, 0, 0);

    Vec3 target(g_zeroVec.x, g_zeroVec.y, g_zeroVec.z);
    Vec3 second(g_zeroVec.x, g_zeroVec.y, g_zeroVec.z);
    Vec3* pSecond = 0;
    float radius = 20.0f;
    Vec3 scratch;
    unsigned mode = GetCurrentGameMode();
    if (mode == 0x1654c05) {
        radius = 22.5f;
        Avatar* av = GetNounManager()->GetAvatar();
        if (av) {
            Located* loc = &av->loc;
            const Vec3* a = RotateByQuat(&scratch, &g_axisVec, loc->GetOrientation());
            float d = camDir.x * a->x + a->y * camDir.y + a->z * camDir.z;
            float px = camDir.x - d * a->x;
            float pz = camDir.z - a->z * d;
            float py = camDir.y - a->y * d;
            float inv = 1.0f / sqrtf(py * py + (pz * pz + px * px));
            Vec3 n(inv * px * 16.0f, py * inv * 16.0f, pz * inv * 16.0f);
            const Vec3* lp = loc->GetPosition();
            target.x = n.x + lp->x;
            target.z = lp->z + n.z;
            target.y = lp->y + n.y;
            second = *loc->GetPosition();
            pSecond = &second;
            goto done;
        } else {
            SpaceToolData* tool = SpaceGameGet()->GetPlayerInventory()->GetTool();
            if (tool && tool->HasFlag() && tool->GetStrategy() && tool->area) {
                Vec3 end;
                tool->area->GetEndPoints(&scratch, &end);
                target = end;
                goto done;
            }
        }
        goto dflt;
    } else if (mode == 0x1654c01) {
    dflt:
        target.x = camDir.x * 20.0f + camPos.x;
        target.y = camDir.y * 20.0f + camPos.y;
        target.z = camDir.z * 20.0f + camPos.z;
    } else {
        const Vec3* r = GetAimSource()->GetPoint(&scratch, 1, g_zeroVec);
        target = *r;
    }
done:

    PtrVec v;
    v.zero = 0;
    v.begin = v.buf;
    v.end = v.buf;
    v.cap = v.buf + 256;
    Gather(&target, &v, objMask, radius, 1, pSecond);

    Light** d = lightBegin;
    Light** e = lightEnd;
    SrcObj** s = v.begin;
    if (d != e) {
        do {
            if (s == v.end)
                break;
            SrcObj* src = *s;
            if (src) {
                Light* l1 = *d;
                Light** n = d + 1;
                d = n;
                if (n != e) {
                    Light* l2 = *n;
                    d = n + 1;
                    float a55 = src->sizeA * 0.55f;
                    float h = a55 * 0.5f;
                    float t = src->sizeB * 0.35f;
                    float u = src->sizeB - t;

                    l1->pos = src->pos;
                    l1->Mark(4);
                    Transform* tr = src->GetTransform();
                    l1->mat = tr->mat;
                    l1->Mark(2);
                    {
                        Vec3 hi(h, h, t);
                        Vec3 lo(-h, -h, 0.0f);
                        l1->bmax = hi;
                        l1->bmin = lo;
                        Vec3 ext(hi.x - lo.x, hi.y - lo.y, hi.z - lo.z);
                        l1->radius = sqrtf(ext.x * ext.x + ext.y * ext.y + ext.z * ext.z);
                    }
                    {
                        SrcObj* old = l1->ref;
                        if (src != old) {
                            src->AddRef();
                            l1->ref = src;
                            if (old) old->Release();
                        }
                    }
                    l1->flags |= 1;
                    l1->owner->Update(l1, 1);

                    float x = src->pos.x, y = src->pos.y, z = src->pos.z;
                    float inv = 1.0f / sqrtf(x * x + y * y + z * z);
                    l2->Mark(4);
                    l2->pos.x = x * inv * t + src->pos.x;
                    l2->pos.y = src->pos.y + y * inv * t;
                    l2->pos.z = src->pos.z + z * inv * t;
                    Transform* tr2 = src->GetTransform();
                    l2->mat = tr2->mat;
                    l2->Mark(2);
                    {
                        Vec3 hi(a55, a55, u);
                        Vec3 lo(-a55, -a55, 0.0f);
                        l2->bmax = hi;
                        l2->bmin = lo;
                        Vec3 ext(hi.x - lo.x, hi.y - lo.y, hi.z - lo.z);
                        l2->radius = sqrtf(ext.x * ext.x + ext.y * ext.y + ext.z * ext.z);
                    }
                    {
                        SrcObj* old = l2->ref;
                        if (src != old) {
                            src->AddRef();
                            l2->ref = src;
                            if (old) old->Release();
                        }
                    }
                    l2->flags |= 1;
                    l2->owner->Update(l2, 1);
                    d = n + 1;
                    s++;
                    continue;
                }
            } else {
                s++;
                continue;
            }
            e = lightEnd;
        } while (d != e);
    }
    while (d != lightEnd) {
        Light* l = *d;
        l->mat = g_identity;
        l->scale = 1.0f;
        l->pos = g_zeroVec;
        l->dirty = 0;
        l->dirtyCount = 0;
        SrcObj* r = l->ref;
        if (r) {
            l->ref = 0;
            r->Release();
        }
        l->flags &= ~1u;
        l->owner->Update(l, 0);
        d++;
    }
    if (v.begin && v.begin[-1])
        operator_delete_array(v.begin);
}
