// Slice s00e998d0: SP::cSPUFOGfx — the UFO visual-effect controller and its
// per-effect "Update*Effect" entry points.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
//
// cSPUFOGfx holds one AutoRefCount<cIVisualEffect> per visual effect (an
// intrusive-refcounted handle: a single pointer, released through vtable slot
// +0x04). Every updater follows the same shape: gate on a flag, drop whatever
// instance is current, ask the effect manager (vtable slot +0x2c) to create a
// new one under a 32-bit id, then push a transform message into it.
//
// The layout below models the retail offsets read from the disassembly; the
// fields this slice does not touch are explicit padding.
#include "types.h"

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;
typedef short          i16;
typedef int            i32;

extern "C" double sqrt(double);

// ---------------------------------------------------------------- math types
struct Vector3 { float x, y, z; };
struct Matrix3 {
    u32 m[9];
    void Set(const void* src);       // @0x41cb40 Matrix3::Assign
};

// ------------------------------------------------------------- effect types
struct IEffect {                     // EA::Swarm::cIVisualEffect instance
    virtual void v00();
    virtual void Release();                  // 0x04
    virtual void Start(int flag);            // 0x08
    virtual void Stop(int flag);             // 0x0c
    virtual bool IsActive();                 // 0x10
    virtual void v14();                      // 0x14
    virtual void SetTransform(void* msg);    // 0x18
    virtual void v1c(); virtual void v20();
};

template <class T> struct AutoRefCount {     // intrusive ref-count handle
    T* mpObject;                             // +0x00
    void Clear();
};

// The release idiom of an AutoRefCount: keep the old pointer, null the slot,
// then call the instance's Release().  Defined out of line so the optimiser
// does not delete the guard when the caller has already proved the slot null.
template <class T> void AutoRefCount<T>::Clear()
{
    T* p = mpObject;
    if (p) {
        mpObject = 0;
        p->Release();
    }
}

struct XformMsg {                    // 0x38 bytes; ctor @0x434040
    u16 flags;                       // +0x00  |4 = has position, |2 = has matrix
    i16 count;                       // +0x02
    Vector3 pos;                     // +0x04
    u32 f10;                         // +0x10  (1.0f from the ctor)
    Matrix3 mat;                     // +0x14
    XformMsg();                      // defined out of slice @0x434040
};

struct EffectsMgr {                  // SP::EffectsManager (singleton)
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool CreateEffect(int key, int unused, IEffect** out);   // +0x2c
};
EffectsMgr* SP_EffectsManager();             // @0x67ddd0

// --------------------------------------------------------------- target types
struct cTransformSub {               // embedded spatial transform, at target+0x34
    virtual void t00(); virtual void t04(); virtual void t08(); virtual void t0c();
    virtual void t10(); virtual void t14(); virtual void t18(); virtual void t1c();
    virtual void t20(); virtual void t24(); virtual void t28();
    virtual Vector3* GetPosition();              // +0x2c
    virtual void*    GetOrientation();           // +0x30
    virtual void t34(); virtual void t38(); virtual void t3c();
    virtual void t40(); virtual void t44(); virtual void t48(); virtual void t4c();
    virtual void t50(); virtual void t54(); virtual void t58();
    virtual void     GetLocalPoint(Vector3* out); // +0x5c
};

struct cContactState {               // embedded collision state, at target+0x508
    u8 opaque[0x20c];
    u8 IsLatched();                  // @0xbfc480
    u8 IsConnected();                // @0xbfc600
};

struct cSpatialObj {                 // creature / flying-saucer spatial object
    u8            pad00[0x34];       // +0x000
    cTransformSub m_transform;       // +0x034
    u8            pad38[0x4d0];      // +0x038
    cContactState m_contact;         // +0x508  (0x20c bytes)
    i32           m_state714;        // +0x714  motion/UI state
    float         m_v718;            // +0x718  local position
    float         m_v71c;            // +0x71c
    float         m_v720;            // +0x720
    u8            pad724[0x28];      // +0x724
    u8            m_flag74c;         // +0x74c  "use city position"

    u8   HasFlag(int id);            // @0xc38990
    void SetFlag(int id, int value); // @0xc389c0
};

struct cViewer {                     // SP::cViewer
    void GetCameraLocationInfo(Vector3* pos, Vector3* dir, int a, int b); // @0x7c3d30
};

// --------------------------------------------------------------- globals
extern Vector3 g_camDefault;         // @0x16c6350
extern Vector3 g_spawnOffset;        // @0x16c6934
extern Matrix3 g_baseRotation;       // @0x16c6910
extern Vector3 g_upAxis;             // @0x15a8b08
extern float   g_distEpsilon;        // @0x15a8b4c
extern float   g_normEpsilon;        // @0x13ec4b8

// --------------------------------------------------------------- externs
int     SP_GetUniverseContext();                                   // @0x1021080
void*   SP_App();                                                  // @0x67dd10
void*   SP_PlanetModel(void* in);                                  // @0xb3d350
void*   SP_PlanetModel(void* out, void* in);                       // @0xb3d350
void    SP_FUN_b81630(void* self, void* out, void* in);            // @0xb81630
char    SP_FUN_b7e3e0(void* in);                                   // @0xb7e3e0
float   SP_VectorLength(void* in);                                 // @0x40ae50
void    SP_Vector3_Normalize(Vector3* dest, Vector3* src);         // @0x436ce0
Vector3* SP_normalized_safe(Vector3* out, Vector3* in);            // @0x449c20
Matrix3 SP_Matrix3FromFacingAndUp(const void* facing, const void* up); // @0x69b440
Matrix3 SP_Matrix3FromQuaternion(const void* quat);                    // @0x59c190
int     SP_FNVHash(const char* str, u32 seed, int mode);           // @0x932e80
void*   SP_GetUFOSimulator();                                      // @0xffbe50
float   SP_GetMaxTravelDistance(void* self);                       // @0xffbfc0
float   SP_GetMaxZ(void* self);                                    // @0xffbfd0
void*   SP_IsArchived();                                           // @0x1021240
Vector3* SP_GetCities(void* self);                                 // @0x5c65e0
int     SP_FUN_1046fc0(int id);                                    // @0x1046fc0
char    SP_FUN_10449e0(int value);                                 // @0x10449e0
void    SP_FUN_e99280(void* obj, void* msg);                       // @0xe99280

// --------------------------------------------------------------- controller
struct cSPUFOGfx {
    u8      pad00[0x0c];                 // +0x000
    void*   m_pObj0c;                    // +0x00c render subject
    u8      pad10[0x68];                 // +0x010
    u8      m_flag78;                    // +0x078 effects-enabled flag
    u8      pad79[0x0b];                 // +0x079
    AutoRefCount<IEffect> m_84;          // +0x084 shadow
    AutoRefCount<IEffect> m_88;          // +0x088 spare-phase A
    AutoRefCount<IEffect> m_8c;          // +0x08c spare-phase B
    u8      pad90[0x0c];                 // +0x090
    AutoRefCount<IEffect> m_9c;          // +0x09c AOE repair
    AutoRefCount<IEffect> m_a0;          // +0x0a0 rally call
    AutoRefCount<IEffect> m_a4;          // +0x0a4 shield
    AutoRefCount<IEffect> m_a8;          // +0x0a8 cloak
    AutoRefCount<IEffect> m_ac;          // +0x0ac unlock notice
    u8      padB0[0x04];                 // +0x0b0
    AutoRefCount<IEffect> m_b4;          // +0x0b4
    u8      padB8[0x04];                 // +0x0b8
    AutoRefCount<IEffect> m_bc;          // +0x0bc re-entry streak

    void UpdateShadow();
    void UpdateSpacePhase(void* unused);
    void UpdateAOERepairEffect(cSpatialObj* obj);
    void UpdateRallyCallEffect(cSpatialObj* obj);
    void UpdateE9A1F0(cSpatialObj* obj);
    void UpdateShieldEffect(cSpatialObj* obj);
    void UpdateE9A470(cSpatialObj* obj);
    void UpdateCloakEffect(cSpatialObj* obj);
    void UpdateE9A6A0(cSpatialObj* obj);
};

#define DROP_EFFECT(ref)                                        \
    do {                                                        \
        if ((ref).mpObject) {                                   \
            IEffect* _drop = (ref).mpObject;                    \
            (ref).mpObject = 0;                                 \
            _drop->Release();                                   \
        }                                                       \
    } while (0)

// @ 0x00e998d0
void cSPUFOGfx::UpdateShadow()
{
    cSpatialObj* uni = 0;
    if (m_pObj0c != 0)
        uni = (cSpatialObj*)(*(void* (__thiscall**)(void*, i32))(*(void***)m_pObj0c)[0xb8 / 4])(m_pObj0c, (i32)0xb033b403);

    if (SP_GetUniverseContext() != 0) {
        if (m_84.mpObject) m_84.mpObject->Stop(1);
        return;
    }

    void* app     = SP_App();
    void* app2    = (*(void* (__thiscall**)(void*))(*(void***)app)[0x50 / 4])(app);
    cViewer* view = (cViewer*)(*(void* (__thiscall**)(void*))(*(void***)app2)[0x1c / 4])(app2);

    Vector3 camPos = g_camDefault;
    Vector3 camDir = g_camDefault;
    if (view != 0)
        view->GetCameraLocationInfo(&camPos, &camDir, 0, 0);

    cTransformSub* xf = &uni->m_transform;
    Vector3* p0 = xf->GetPosition();
    float facing = p0->z * camPos.z + p0->y * camPos.y + p0->x * camPos.x;
    if (facing < 0.0f || m_flag78 == 0) {
        if (m_84.mpObject) m_84.mpObject->Stop(1);
        return;
    }

    Vector3 surface;
    SP_PlanetModel(&surface, p0);
    SP_FUN_b81630(&surface, &surface, p0);

    if (SP_GetUniverseContext() == 0) {
        SP_PlanetModel(p0);
        if (SP_FUN_b7e3e0(p0) != 0) {
            float dist = SP_VectorLength(p0) -
                         (float)sqrt(surface.x * surface.x + surface.y * surface.y +
                                     surface.z * surface.z);
            if (dist < g_distEpsilon) {
                if (!m_84.mpObject->IsActive())
                    m_84.mpObject->Start(0);

                Vector3 edge;
                xf->GetLocalPoint(&edge);
                Vector3* p1 = xf->GetPosition();
                Vector3 dir;
                SP_Vector3_Normalize(&dir, p1);

                Vector3 normal;
                SP_PlanetModel(&normal, &dir);
                SP_FUN_b81630(&normal, &normal, &dir);

                Vector3 tangent, up;
                tangent.x = edge.y * dir.z - edge.z * dir.y;
                tangent.y = edge.z * dir.x - edge.x * dir.z;
                tangent.z = edge.x * dir.y - edge.y * dir.x;
                Vector3* nt = SP_normalized_safe(&tangent, &tangent);
                up.x = nt->y * dir.z - nt->z * dir.y;
                up.y = nt->z * dir.x - nt->x * dir.z;
                up.z = nt->x * dir.y - nt->y * dir.x;
                SP_normalized_safe(&up, &up);

                XformMsg msg;
                msg.pos = *p1;
                msg.flags |= 4; msg.count += 1;
                Matrix3 basis = SP_Matrix3FromFacingAndUp(&dir, &up);
                msg.mat = basis;
                msg.flags |= 2; msg.count += 1;
                m_84.mpObject->SetTransform(&msg);
                return;
            }
        }
    }

    if (m_84.mpObject->IsActive())
        m_84.mpObject->Stop(0);
}

// @ 0x00e99c50
void cSPUFOGfx::UpdateSpacePhase(void* /*unused*/)
{
    cSpatialObj* uni = 0;
    if (m_pObj0c != 0)
        uni = (cSpatialObj*)(*(void* (__thiscall**)(void*, i32))(*(void***)m_pObj0c)[0xb8 / 4])(m_pObj0c, (i32)0xb033b403);

    if (uni->m_state714 == 0 && SP_GetUniverseContext() == 2) {
        bool entering = SP_FUN_10449e0(SP_FUN_1046fc0(5));
        if (!entering) entering = SP_FUN_10449e0(SP_FUN_1046fc0(0));
        if (!entering) entering = SP_FUN_10449e0(SP_FUN_1046fc0(1));
        if (!entering) entering = SP_FUN_10449e0(SP_FUN_1046fc0(4));
        if (!entering) entering = SP_FUN_10449e0(SP_FUN_1046fc0(2));
        if (!entering) entering = SP_FUN_10449e0(SP_FUN_1046fc0(3));
        if (entering) {
            if (!m_88.mpObject->IsActive() && m_flag78 != 0)
                m_88.mpObject->Start(0);
            (*(void (__thiscall**)(void*))(*(void***)this)[0x2c / 4])(this);

            XformMsg msg;
            msg.pos = g_spawnOffset;
            msg.f10 = 0x3f800000;
            msg.mat.Set(&g_baseRotation);
            if (uni->m_flag74c == 0) {
                msg.pos.x = uni->m_v718;
                msg.pos.y = uni->m_v71c;
                msg.pos.z = uni->m_v720;
            } else {
                Vector3* city = SP_GetCities(SP_IsArchived());
                msg.pos = *city;
            }
            msg.flags |= 4; msg.count += 1;

            Vector3 fwd;
            float proj = (-uni->m_v71c) * g_upAxis.y +
                         (-uni->m_v720) * g_upAxis.z +
                         (-uni->m_v718) * g_upAxis.x;
            fwd.z = -uni->m_v720 - proj * g_upAxis.z;
            fwd.y = -uni->m_v71c - proj * g_upAxis.y;
            fwd.x = -uni->m_v718 - proj * g_upAxis.x;
            float inv = 1.0f / (float)sqrt(fwd.x * fwd.x + fwd.y * fwd.y +
                                           fwd.z * fwd.z + g_normEpsilon);
            fwd.x *= inv; fwd.y *= inv; fwd.z *= inv;
            Matrix3 basis = SP_Matrix3FromFacingAndUp(&fwd, &g_upAxis);
            msg.mat = basis;
            msg.flags |= 2; msg.count += 1;

            void* sim = SP_GetUFOSimulator();
            msg.f10 = (u32)(float)SP_GetMaxTravelDistance(sim);
            msg.count += 1;
            m_88.mpObject->SetTransform(&msg);

            if (!m_8c.mpObject->IsActive() && m_flag78 != 0)
                m_8c.mpObject->Start(0);
            void* sim2 = SP_GetUFOSimulator();
            msg.f10 = (u32)(float)SP_GetMaxZ(sim2);
            msg.count += 1;
            m_8c.mpObject->SetTransform(&msg);
            return;
        }
    }

    m_88.mpObject->Stop(1);
    m_8c.mpObject->Stop(1);
}

// @ 0x00e99f90
void cSPUFOGfx::UpdateAOERepairEffect(cSpatialObj* obj)
{
    if (obj == 0)
        return;

    if (obj->HasFlag(2)) {
        obj->SetFlag(2, 0);
        i32 key = obj->m_state714 != 0 ? (i32)(0xa0018993 + 0xb8438bce)
                                       : (i32)0xa0018993;
        DROP_EFFECT(m_9c);
        EffectsMgr* mgr = SP_EffectsManager();
        DROP_EFFECT(m_9c);
        mgr->CreateEffect(key, 0, &m_9c.mpObject);
        if (m_9c.mpObject)
            m_9c.mpObject->Start(0);
    }

    if (m_9c.mpObject) {
        if (m_9c.mpObject->IsActive()) {
            XformMsg msg;
            Vector3* p = obj->m_transform.GetPosition();
            msg.pos = *p;
            msg.flags |= 4; msg.count += 1;
            m_9c.mpObject->SetTransform(&msg);
            return;
        }
        DROP_EFFECT(m_9c);
    }
}

// @ 0x00e9a0c0
void cSPUFOGfx::UpdateRallyCallEffect(cSpatialObj* obj)
{
    if (obj == 0)
        return;

    if (obj->HasFlag(3)) {
        obj->SetFlag(3, 0);
        i32 key = obj->m_state714 != 0 ? (i32)(0x2c860712 + 0xf3ab5d75)
                                       : (i32)0x2c860712;
        DROP_EFFECT(m_a0);
        EffectsMgr* mgr = SP_EffectsManager();
        DROP_EFFECT(m_a0);
        mgr->CreateEffect(key, 0, &m_a0.mpObject);
        if (m_a0.mpObject)
            m_a0.mpObject->Start(0);
    }

    if (m_a0.mpObject) {
        if (m_a0.mpObject->IsActive()) {
            XformMsg msg;
            Vector3* p = obj->m_transform.GetPosition();
            msg.pos = *p;
            msg.flags |= 4; msg.count += 1;
            m_a0.mpObject->SetTransform(&msg);
            return;
        }
        DROP_EFFECT(m_a0);
    }
}

// @ 0x00e9a1f0
void cSPUFOGfx::UpdateE9A1F0(cSpatialObj* obj)
{
    if (obj == 0)
        return;

    int key = 0;
    if (obj->HasFlag(7)) {
        obj->SetFlag(7, 0);
        key = SP_FNVHash("UI_unlock_space_rare", 0x811c9dc5, 1);
    } else if (obj->HasFlag(5)) {
        obj->SetFlag(5, 0);
        key = SP_FNVHash("UI_unlock_space_tool", 0x811c9dc5, 1);
    } else if (obj->HasFlag(6)) {
        obj->SetFlag(6, 0);
    }

    if (key != 0) {
        EffectsMgr* mgr = SP_EffectsManager();
        DROP_EFFECT(m_ac);
        mgr->CreateEffect(key, 0, &m_ac.mpObject);
        if (m_ac.mpObject) {
            XformMsg msg;
            SP_FUN_e99280(obj, &msg);
            m_ac.mpObject->SetTransform(&msg);
            m_ac.mpObject->Start(0);
        }
    }

    if (m_ac.mpObject) {
        if (m_ac.mpObject->IsActive()) {
            XformMsg msg;
            SP_FUN_e99280(obj, &msg);
            m_ac.mpObject->SetTransform(&msg);
            return;
        }
        DROP_EFFECT(m_ac);
    }
}

// @ 0x00e9a360
void cSPUFOGfx::UpdateShieldEffect(cSpatialObj* obj)
{
    if (obj == 0)
        return;

    if (!obj->m_contact.IsLatched() || obj->m_state714 == 1) {
        if (m_a4.mpObject) {
            m_a4.mpObject->Stop(0);
            DROP_EFFECT(m_a4);
        }
    } else if (m_a4.mpObject == 0) {
        // An AutoRefCount::Clear() here, not the DROP_EFFECT macro: the macro
        // would be folded away (the guard already implies the slot is null).
        m_a4.Clear();
        EffectsMgr* mgr = SP_EffectsManager();
        m_a4.Clear();
        mgr->CreateEffect((i32)0xdc08f952, 0, &m_a4.mpObject);
        if (m_a4.mpObject)
            m_a4.mpObject->Start(0);
    }

    if (m_a4.mpObject) {
        if (m_a4.mpObject->IsActive()) {
            XformMsg msg;
            Vector3* p = obj->m_transform.GetPosition();
            msg.pos = *p;
            msg.flags |= 4; msg.count += 1;
            m_a4.mpObject->SetTransform(&msg);
        }
    }
}

// @ 0x00e9a470
void cSPUFOGfx::UpdateE9A470(cSpatialObj* obj)
{
    if (obj == 0)
        return;

    if (obj->m_contact.IsConnected()) {
        if (m_bc.mpObject == 0) {
            EffectsMgr* mgr = SP_EffectsManager();
            DROP_EFFECT(m_bc);
            mgr->CreateEffect((i32)0x46cca23c, 0, &m_bc.mpObject);
            if (m_bc.mpObject)
                m_bc.mpObject->Start(0);
        }
    } else if (m_bc.mpObject) {
        m_bc.mpObject->Stop(0);
        DROP_EFFECT(m_bc);
    }

    if (m_bc.mpObject) {
        if (m_bc.mpObject->IsActive()) {
            XformMsg msg;
            Vector3* p = obj->m_transform.GetPosition();
            msg.pos = *p;
            msg.flags |= 4; msg.count += 1;

            void* q = obj->m_transform.GetOrientation();
            Matrix3 basis = SP_Matrix3FromQuaternion(q);
            msg.mat = basis;
            msg.flags |= 2; msg.count += 1;
            m_bc.mpObject->SetTransform(&msg);
        }
    }
}

// @ 0x00e9a590
void cSPUFOGfx::UpdateCloakEffect(cSpatialObj* obj)
{
    if (obj == 0)
        return;

    if (!obj->HasFlag(1) && obj->m_state714 != 5) {
        if (m_a8.mpObject) {
            m_a8.mpObject->Stop(0);
            DROP_EFFECT(m_a8);
        }
    } else if (m_a8.mpObject == 0) {
        // AutoRefCount::Clear() rather than DROP_EFFECT; see UpdateShieldEffect.
        m_a8.Clear();
        EffectsMgr* mgr = SP_EffectsManager();
        m_a8.Clear();
        mgr->CreateEffect((i32)0xaa0ddbdf, 0, &m_a8.mpObject);
        if (m_a8.mpObject)
            m_a8.mpObject->Start(0);
    }

    if (m_a8.mpObject) {
        if (m_a8.mpObject->IsActive()) {
            XformMsg msg;
            Vector3* p = obj->m_transform.GetPosition();
            msg.pos = *p;
            msg.flags |= 4; msg.count += 1;
            m_a8.mpObject->SetTransform(&msg);
        }
    }
}

// @ 0x00e9a6a0
void cSPUFOGfx::UpdateE9A6A0(cSpatialObj* obj)
{
    if (obj == 0)
        return;

    if (obj->HasFlag(8)) {
        obj->SetFlag(8, 0);
        EffectsMgr* mgr = SP_EffectsManager();
        DROP_EFFECT(m_b4);
        mgr->CreateEffect((i32)0x4338a32d, 0, &m_b4.mpObject);
        if (m_b4.mpObject) {
            XformMsg msg;
            SP_FUN_e99280(obj, &msg);
            m_b4.mpObject->SetTransform(&msg);
            m_b4.mpObject->Start(0);
        }
    }

    if (m_b4.mpObject) {
        if (m_b4.mpObject->IsActive()) {
            XformMsg msg;
            Vector3* p = obj->m_transform.GetPosition();
            msg.pos = *p;
            msg.flags |= 4; msg.count += 1;
            m_b4.mpObject->SetTransform(&msg);
            return;
        }
        DROP_EFFECT(m_b4);
    }
}