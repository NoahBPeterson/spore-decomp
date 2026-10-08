// Per-frame integration of a surface-bound mover (planet surface movement), mode 0 = free, mode 1 = on surface.
#include <math.h>
#include "types.h"

struct Vec3f { float x, y, z; };
struct Vec4f { float x, y, z, w; };

extern Vec3f g_ZeroVec;                 // 0x0167eb8c

class cPlanetModel {
public:
    float GetWaterHeight();                                      // 0x00b7e390
    float GetScale();                                            // 0x00b7e490
    Vec3f* ProjectToTangent(Vec3f* out, Vec3f* pos);             // 0x00b7e3b0 (ret 8)
    Vec3f* DirectionToSurfacePosition(Vec3f* out, Vec3f* dir);   // 0x00b815a0 (ret 8)
    Vec4f* OrientationAt(Vec4f* out, Vec3f* pos, Vec3f* up);     // 0x00b7f1f0 (ret 0xc)
    float GetRadiusAt(Vec3f* pos);                               // 0x00b7ef70 (ret 4)
};

// Target object at this+0x40; vtable slots as used here.
class cMoverTarget {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a();
    virtual Vec3f* GetPosition();                 // +0x2c
    virtual Vec3f* GetUp();                       // +0x30
    virtual void v0d();
    virtual void SetPosition(Vec3f* p);           // +0x38
    virtual void SetOrientation(Vec4f* q);        // +0x3c
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
    virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
    virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
    virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v2a(); virtual void v2b();
    virtual void v2c(); virtual void v2d(); virtual void v2e(); virtual void v2f();
    virtual void v30(); virtual void v31();
    virtual float GetRotateFactor();              // +0xc8
    void SetVelocityDir(Vec3f* v);                // 0x00c41d60 (ret 4)
    void SetAngularDir(Vec3f* v);                 // 0x00c41d90 (ret 4)
    char pad[0x48];
    uint32_t flags;                               // +0x50
};

cPlanetModel* PlanetModel();                      // 0x00b3d350
Vec3f* Normalize(Vec3f* out, Vec3f* in);          // 0x00436ce0 (cdecl)
float Dot3(Vec3f* v);                             // 0x004885d0 (v . v)
float VectorLength(Vec3f* v);                     // 0x0040ae50
Vec4f* QuatDelta(Vec4f* out, Vec4f* w, Vec4f* q); // 0x007dcb00 (cdecl)
Vec4f* QuatNormalize(Vec4f* out, Vec4f* q);       // 0x00799320 (cdecl)
void ApplyPlanetCorrection(Vec3f* pos, cMoverTarget* obj);   // 0x00b444c0 (cdecl)

class cSurfaceMover {
public:
    virtual void vfn0();
    float GetSpeed();                             // 0x00b3dcd0
    void GetOrientation(Vec4f* out);              // 0x00b3f300 (ret 4)
    void Update(float dt);                        // 0x00b46660

    int mode;                                     // +4
    char pad0[0x14];
    Vec3f vel;                                    // +0x1c
    Vec3f angVel;                                 // +0x28
    char onSurface;                               // +0x34
    char pad2;
    char active;                                  // +0x36
    char pad3;
    char pad4[8];
    cMoverTarget* obj;                            // +0x40
};

// @ 0x00b46660
void cSurfaceMover::Update(float dt)
{
    if (!(1.5258789e-05f < GetSpeed()))
        return;
    if (!active)
        return;
    switch (mode) {
    case 0:
        if (vel.x != g_ZeroVec.x || vel.y != g_ZeroVec.y || vel.z != g_ZeroVec.z) {
            Vec3f* pv = &vel;
            obj->SetVelocityDir(pv);
            obj->SetAngularDir(&angVel);
            Vec4f q;
            GetOrientation(&q);
            Vec4f w = { angVel.x, angVel.y, angVel.z, 0.0f };
            Vec4f tmp;
            Vec4f* d = QuatDelta(&tmp, &w, &q);
            q.x = (d->x * 0.5f) * dt + q.x;
            q.y = q.y + (d->y * 0.5f) * dt;
            q.z = q.z + (d->z * 0.5f) * dt;
            q.w = q.w + (d->w * 0.5f) * dt;
            Vec4f tmp2;
            Vec4f* n = QuatNormalize(&tmp2, &q);
            q.x = n->x; q.y = n->y; q.z = n->z; q.w = n->w;
            if (obj->GetRotateFactor() == 0.0f)
                obj->SetOrientation(&q);
            Vec3f* p = obj->GetPosition();
            Vec3f tgt;
            tgt.x = pv->x * dt + p->x;
            tgt.y = pv->y * dt + p->y;
            tgt.z = pv->z * dt + p->z;
            ApplyPlanetCorrection(&tgt, obj);
        }
        break;
    case 1: {
        Vec3f* pv = &vel;
        if (pv->x != g_ZeroVec.x || pv->y != g_ZeroVec.y || pv->z != g_ZeroVec.z) {
            cPlanetModel* planet = PlanetModel();
            float scale = planet->GetScale();
            if (onSurface) {
                Vec3f t1, n1, t2;
                planet->ProjectToTangent(&t1, obj->GetPosition());
                Normalize(&n1, &t1);
                Vec3f* p = Normalize(&t2, obj->GetPosition());
                float px = p->x * scale, py = p->y * scale, pz = p->z * scale;
                float step = ((-n1.z * pz + -n1.y * py) + -n1.x * px) * dt;
                float step2 = step * step;
                if (Dot3(pv) < step2) {
                    pv->x = g_ZeroVec.x;
                    vel.y = g_ZeroVec.y;
                    vel.z = g_ZeroVec.z;
                    angVel.x = g_ZeroVec.x;
                    angVel.y = g_ZeroVec.y;
                    angVel.z = g_ZeroVec.z;
                    active = 0;
                } else {
                    Vec3f t3;
                    Vec3f* nv = Normalize(&t3, pv);
                    float nx = -nv->x, ny = -nv->y, nz = -nv->z;
                    pv->x = pv->x + nx * step;
                    vel.y = ny * step + vel.y;
                    vel.z = nz * step + vel.z;
                }
            } else {
                float len = VectorLength(obj->GetPosition());
                if (len > 1.5258789e-05f) {
                    Vec3f* p = obj->GetPosition();
                    float inv = 1.0f / len;
                    pv->x = ((inv * p->x) * scale) * dt + pv->x;
                    vel.y = ((p->y * inv) * scale) * dt + vel.y;
                    vel.z = ((p->z * inv) * scale) * dt + vel.z;
                } else {
                    onSurface = 1;
                }
            }
            Vec4f q;
            GetOrientation(&q);
            Vec4f w = { angVel.x, angVel.y, angVel.z, 0.0f };
            Vec4f tmp;
            Vec4f* d = QuatDelta(&tmp, &w, &q);
            q.x = (d->x * 0.5f) * dt + q.x;
            q.y = q.y + (d->y * 0.5f) * dt;
            q.z = q.z + (d->z * 0.5f) * dt;
            q.w = q.w + (d->w * 0.5f) * dt;
            Vec4f tmp2;
            Vec4f* n = QuatNormalize(&tmp2, &q);
            q.x = n->x; q.y = n->y; q.z = n->z; q.w = n->w;
            obj->SetOrientation(&q);
            Vec3f* p = obj->GetPosition();
            Vec3f tgt;
            tgt.x = pv->x * dt + p->x;
            tgt.y = vel.y * dt + p->y;
            tgt.z = vel.z * dt + p->z;
            Vec3f surf;
            obj->SetPosition(planet->DirectionToSurfacePosition(&surf, &tgt));
            cMoverTarget* o = obj;
            Vec4f ori;
            o->SetOrientation(planet->OrientationAt(&ori, o->GetPosition(), o->GetUp()));
            obj->flags &= 0xfffffffe;
            if (!onSurface) {
                Vec3f* pos = obj->GetPosition();
                float wh = planet->GetWaterHeight();
                float rad = planet->GetRadiusAt(pos);
                float* m = &wh;
                if (!(wh > rad)) m = &rad;
                onSurface = (float)fabs(*m - VectorLength(pos)) < 1.5258789e-05f;
            }
        }
        break;
    }
    }
}
