// Slice s00d239a0: F_d239a0, camera/avatar facing update. Works out the camera "up-projected" facing
// axis from the avatar locomotion object, stores it in the global camera state (0x169e370), and
// either snaps the camera goal (nearly parallel case) or rotates the camera forward vector by an
// angle limited to +-1.553343 rad (acos of the clamped dot product).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>
#include <xmmintrin.h>

namespace SP {

#define VFUNC(obj, off) ((*(void***)(obj))[(off) / 4])

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
__declspec(align(16)) struct Quat { float x, y, z, w; };

Vector3* __cdecl normalized_safe(Vector3* out, const Vector3* in);          // 0x00449c20
Vector3* __cdecl F_59aed0(Vector3* out, const Vector3* v, const Quat* q);   // 0x0059aed0 rotate v by q
Quat* __cdecl F_59b060(Quat* out, const Vector3* axis, float angle);        // 0x0059b060 axis-angle quaternion
Quat* __cdecl F_c64ad0(Quat* out, const Quat* q);                           // 0x00c64ad0 normalise quaternion
__declspec(align(16)) struct Tmp { float f[4]; };
#define TV(t) ((Vector3*)&(t))
#define TQ(t) ((Quat*)&(t))

struct cLocomotiveObject {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual Vector3* F_2c();                       // 0x2c
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58();
    virtual Vector3* F_5c(Vector3* out);           // 0x5c
};
struct cCreatureAnimal {
    char pad0[0xc0];
    cLocomotiveObject mLoco;                       // +0xc0
    char padc4[0xb5e - 0xc4];
    bool mbDead;                                   // +0xb5e
};
struct cGameNounManager { cCreatureAnimal* GetAvatar(); };   // 0x00b1fdb0
struct cGameInputManager {
    bool IsKeyDown(int key) { return ((bool(__thiscall*)(void*, int))VFUNC(this, 0x18))(this, key); }
};

struct cCreatureModeInputStrategy {
    bool UpdateAvatarGoal(bool a, bool b);         // 0x00d31a70
    char pad0[0x54];
    bool mbEnabled;                                // +0x54
};
template<class T> struct Ref {
    T* mp;
    T* get() const { return mp; }
};
struct cCreatureModeStrategy {
    static cCreatureModeStrategy* Instance();      // 0x00d38840
    char pad0[0x64];
    Ref<cCreatureModeInputStrategy> mpInput;       // +0x64
};
struct Other { char pad0[0x68]; cCreatureModeInputStrategy* mpStrat; };
extern Other* g_other;                             // 0x016c7aa4

struct CamState {
    char pad0[0xf];
    uint8_t b0f;
    char pad1[1];
    uint8_t b11;
    char pad2[6];
    Vector3 v18;                                   // +0x18
};
CamState* F_d2e340();                              // returns &g_cam (0x169e370)

cGameNounManager* NounManager();                   // 0x00b3d300
cGameInputManager* GameInputManager();             // 0x00b3d250
uint32_t GetCurrentGameMode();                     // 0x00b5b800
extern const Vector3 g_c;                          // 0x0169df44

struct Ctl {
    char pad0[0x38];
    float f38, f3c, f40;                           // +0x38
    char pad1[4];
    Vector3 v48;                                   // +0x48
    char pad2[0x60 - 0x54];
    Quat q60;                                      // +0x60
    char pad3[0x114 - 0x70];
    Vector3 v114;                                  // +0x114
    void F_d239a0();
};

// @ 0x00d239a0
void Ctl::F_d239a0()
{
    cGameInputManager* input = GameInputManager();
    cCreatureAnimal* av = NounManager()->GetAvatar();
    bool enabled = false;
    if (GetCurrentGameMode() == 0x1654c05) {
        enabled = true;
    } else {
        cCreatureModeInputStrategy* s;
        if (cCreatureModeStrategy::Instance()->mpInput.get())
            s = cCreatureModeStrategy::Instance()->mpInput.get();
        else
            s = g_other->mpStrat;
        if (s) enabled = s->mbEnabled;
    }
    if (av && !av->mbDead && input && enabled) {
        Vector3 w;
        Vector3 a = *F_59aed0(&w, &g_c, &q60);
        Vector3* n = normalized_safe(&w, &v48);
        float d = (a.y * n->y + a.z * n->z) + a.x * n->x;
        float tx = a.x - d * n->x, ty = a.y - d * n->y, tz = a.z - d * n->z;
        w.x = tx; w.y = ty; w.z = tz;
        normalized_safe(&a, &w);

        Tmp U, V, W;
        if (input->IsKeyDown(2)) {
            Vector3* g = av->mLoco.F_5c(TV(U));
            w.x = -g->x; w.y = -g->y; w.z = -g->z;
            Vector3* m = normalized_safe(TV(V), &v114);
            float d2 = (w.y * m->y + w.z * m->z) + w.x * m->x;
            w.x = w.x - d2 * m->x;
            w.y = w.y - d2 * m->y;
            w.z = w.z - d2 * m->z;
            w = *normalized_safe(TV(W), &w);
        } else {
            Vector3* m = normalized_safe(TV(W), &v114);
            Vector3* g = av->mLoco.F_5c(TV(V));
            float d2 = (m->x * g->x + m->y * g->y) + m->z * g->z;
            float tx2 = g->x - d2 * m->x, ty2 = g->y - d2 * m->y, tz2 = g->z - d2 * m->z;
            w.x = tx2; w.y = ty2; w.z = tz2;
            w = *normalized_safe(TV(U), &w);
        }
        CamState* cam = F_d2e340();
        cam->v18 = w;
        cam = F_d2e340();
        float c = (cam->v18.y * a.y + cam->v18.z * a.z) + cam->v18.x * a.x;
        if (input->IsKeyDown(2)) c = c * -1.0f;
        if (c < 0.99f) {
            float lo = -1.0f, hi = 1.0f;
            float clv = c;
            __asm {
                movss xmm0, clv
                maxss xmm0, lo
                minss xmm0, hi
                movss clv, xmm0
            }
            float ang = fabsf(acosf(clv));
            float lo2 = -1.553343f, hi2 = 1.553343f;
            __asm {
                movss xmm0, ang
                maxss xmm0, lo2
                minss xmm0, hi2
                movss ang, xmm0
            }
            float ang2 = ang;
            Vector3* r = F_59aed0(TV(W), &g_c, &q60);
            Vector3& e = w;
            e.x = r->y * v48.z - r->z * v48.y;
            e.y = r->z * v48.x - r->x * v48.z;
            e.z = r->x * v48.y - r->y * v48.x;
            cam = F_d2e340();
            float s = (cam->v18.z * e.z + cam->v18.y * e.y) + cam->v18.x * e.x;
            if (0.0f > s) ang2 = ang * -1.0f;
            if (input->IsKeyDown(2)) ang2 = ang2 * -1.0f;
            Quat* q = F_c64ad0(TQ(V), F_59b060(TQ(U), normalized_safe(TV(W), av->mLoco.F_2c()), ang2));
            Vector3* rv = F_59aed0(TV(W), &F_d2e340()->v18, q);
            F_d2e340()->v18 = *rv;
            Vector3* nn = normalized_safe(TV(W), &F_d2e340()->v18);
            Vector3 nc = *nn;
            F_d2e340()->v18 = nc;
            F_d2e340()->b11 = 1;
            F_d2e340()->b0f = 1;
            cCreatureModeInputStrategy* p = cCreatureModeStrategy::Instance()->mpInput.get();
            if (p && p->mbEnabled)
                p->UpdateAvatarGoal(false, true);
        } else {
            float f = 1.0f - c;
            Vector3* m = normalized_safe(TV(W), &v114);
            Vector3* g = av->mLoco.F_5c(TV(V));
            float cx = m->z * g->y - m->y * g->z;
            float cy = m->x * g->z - g->x * m->z;
            float cz = g->x * m->y - m->x * g->y;
            float s2 = (cy * a.y + cz * a.z) + cx * a.x;
            if (s2 > 0.0f) f = f * -1.0f;
            f38 = a.x; f3c = a.y; f40 = a.z;
            *(float*)((char*)this + 0x174) = f;
            *(float*)((char*)this + 0xf8) = f;
            *((uint8_t*)this + 0x2b2) = 0;
            *(int*)((char*)this + 0x1ec) = 1;
        }
    }
}

}  // namespace SP
