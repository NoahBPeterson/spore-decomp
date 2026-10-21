// SporeApp.exe frozen batch "gold4" — slice s00d99ff0 (11 functions)
// Creature social/interaction predicates and helpers.
#include "types.h"

typedef unsigned int uint;
typedef unsigned int uintptr_t;

extern "C" float sqrtf(float);

// ---------------------------------------------------------------- externals
void  operator_delete_arr(void* p);                    // 0x00f47380
void* FUN_00f3e8a0(int nounID);                        // 0x00f3e8a0
void* FUN_00ac80d0(void* obj, int type);               // 0x00ac80d0
void* CastCreature(void* obj);                         // 0x00ae66f0
void  FUN_00c41ec0(void* self);                        // 0x00c41ec0
void  FUN_0059aed0(void* dst, const void* src, int a); // 0x0059aed0
void  FUN_00b3d240(void);                              // 0x00b3d240
void  FUN_00b3d3c0(void);                              // 0x00b3d3c0
void  FUN_00b3d350(void);                              // 0x00b3d350
void  FUN_00b3d4c0(void* a, void* b, void* c);         // 0x00b3d4c0
void* FUN_00b3d4c0_ret(void* a, void* b, void* c);     // 0x00b3d4c0
void  FUN_00b35bf0(void* self);                        // 0x00b35bf0
void  FUN_00b79c30(void);                              // 0x00b79c30
void  FUN_00ba3f90(void);                              // 0x00ba3f90
void  FUN_00b815a0(void);                              // 0x00b815a0
void  FUN_00b7e390(void);                              // 0x00b7e390
void  FUN_00bc96a0(void);                              // 0x00bc96a0
void  FUN_00bc98f0(void);                              // 0x00bc98f0
int   FUN_00c0e6a0(void* a);                           // 0x00c0e6a0
int   FUN_00ba3f90_ret();                              // 0x00ba3f90
struct Socialable { int GetSocialGoal(); };            // 0x00c0e6a0
struct GoalBlob  { int Query(); };                     // 0x00ba3f90
void  FUN_00b3d240(void);                              // 0x00b3d240 (fwd)
void  FUN_00b3d240_ref(void* a, void* b, void* c, void* d);  // 0x00b3d240
void  FUN_00b35bf0(void* self);                        // 0x00b35bf0 (fwd)
void  FUN_00c897e0(void);                              // 0x00c897e0
void  FUN_00c0e6a0(void);                              // 0x00c0e6a0
void  FUN_0059c190(void);                              // 0x0059c190
void  FUN_0041cb40(void);                              // 0x0041cb40
void  FUN_004ff6d0(void);                              // 0x004ff6d0
void  FUN_006989d0(void);                              // 0x006989d0
int   FUN_00d999d0(void* p);                           // 0x00d999d0
void  FUN_00af9ff0(void);                              // 0x00af9ff0
void  FUN_00b1fdb0(void);                              // 0x00b1fdb0
void  FUN_00b3d300(void);                              // 0x00b3d300
void  FUN_0067dd10(void);                              // 0x0067dd10
void  FUN_007c3d30(void);                              // 0x007c3d30

extern "C" {
extern float DAT_0169f2f4;    // 0x0169f2f4
extern float DAT_0169f2a4;    // 0x0169f2a4
extern float DAT_0169f2a8;    // 0x0169f2a8
extern float DAT_0169f2ac;    // 0x0169f2ac
extern float DAT_0169f300;    // 0x0169f300
extern float DAT_01485720;    // 0x01485720 (1.0f)
extern float DAT_01471064;    // 0x01471064 (0.5f)
extern void* DAT_016c7aa4;    // 0x016c7aa4
}

// ---------------------------------------------------------------- vtable helpers
template <class T, int Off, class A, class B>
static inline void vcallA2(T* p, A a, B b) {
    typedef void (T::*PMF)(A, B);
    void* fn = ((void**)*(void***)p)[Off / 4];
    PMF f; *(void**)&f = fn;
    (p->*f)(a, b);
}
template <class T, int Off>
static inline void vcallv(T* p) {
    typedef void (T::*PMF)();
    void* fn = ((void**)*(void***)p)[Off / 4];
    PMF f; *(void**)&f = fn;
    (p->*f)();
}
template <class T, int Off>
static inline bool vcallBool(T* p) {
    typedef bool (T::*PMF)();
    void* fn = ((void**)*(void***)p)[Off / 4];
    PMF f; *(void**)&f = fn;
    return (p->*f)();
}

// @ 0x00d99ff0
bool FUN_00d99ff0(void* obj)
{
    void* p;
    int   tag;
    if (obj == 0) goto fail;
    p = (void*)((void*(*)(void*, int))(*(void***)obj)[0xb8 / 4])(obj, 0x17f243b);
    if (p == 0) goto fail;
    tag = (int)((void*(*)(void*))(*(void***)p)[0x20 / 4])(p);

    if (tag > 0x2c9cc91) {
        if (tag > 0x3ed8573) {
            if (tag == 0x52aa6122) return true;
            goto fail;
        }
        if (tag == 0x3ed8573) return true;
        if (tag == 0x2e72cae) return true;
        if (tag != 0x3a2511e) goto fail;
        {
            void* r = (void*)((void*(*)(void*, int))(*(void***)p)[0xb8 / 4])(p, 0x3a2511e);
            if (*(int*)((char*)r + 0x108) == 0) goto fail;
        }
        return true;
    }
    if (tag == 0x2c9cc91) return true;
    if (tag > 0x18c88e4) {
        if (tag == 0x18eb45e || tag == 0x18eb4b7) {
            if (((uint)(uintptr_t)obj & 1) == 0) return true;
            {
                char* c = (char*)CastCreature(obj);
                if (c[0x137] == 0) return true;
                if (c[0xb5e] != 0) return true;
                void* vt = (char*)c + 0xc0;
                FUN_00c41ec0(vt);
                if (*(int*)((char*)vt + 0x5c) == 0) return false;
                return ((bool(*)(void*))(*(void***)vt)[0xf8 / 4])(vt);
            }
        }
        goto fail;
    }
    if (tag == 0x18c88e4) {
        void* r = (void*)((void*(*)(void*, int))(*(void***)p)[0xb8 / 4])(p, 0x18c88e4);
        int v = *(int*)((char*)r + 0x228);
        if (v == 0x5b9a06e) return false;
        return v == 0x5d97f762;
    }
    if (tag == 0x18c431c) return true;
    if (tag == 0x18c84a9) goto fail;
    goto fail;

fail:
    return *(uint8_t*)((char*)obj + 0x71) == 0;
}

// @ 0x00d9a110
bool FUN_00d9a110(void* ea, void* param)
{
    float* pmax = (float*)ea;
    float* pf = *(float**)param;
    int    n = (int)(*(int*)((char*)param + 4) - (int)pf) / 12;
    float* other = *(float**)ea;
    int    i;
    if (n <= 0) return false;
    for (i = 0; i < n; ++i) {
        if (pf[0] != other[0]) return true;
        if (pf[1] != other[1]) return true;
        if (pf[2] != other[2]) return true;
        pf += 3;
        other += 3;
    }
    (void)pmax;
    return false;
}

// @ 0x00d9a190
int FUN_00d9a190(void* ecxObj, float* eaxPt)
{
    float* pf = *(float**)ecxObj;
    int    n = (*(int*)((char*)ecxObj + 4) - (int)pf) / 12;
    float  dx = pf[0] - eaxPt[0];
    float  dy = pf[1] - eaxPt[1];
    float  dz = pf[2] - eaxPt[2];
    float  best = dx * dx + dy * dy + dz * dz;
    best = sqrtf(best);
    int    bi = 0;
    int    i;
    if (n <= 1) return bi;
    for (i = 1; i < n; ++i) {
        float* q = pf + i * 3;
        float ax = q[0] - eaxPt[0];
        float ay = q[1] - eaxPt[1];
        float az = q[2] - eaxPt[2];
        float d = ax * ax + ay * ay + az * az;
        d = sqrtf(d);
        if (d < best) {
            bi = i;
            best = d;
        }
    }
    return bi;
}

// @ 0x00d9a290
void FUN_00d9a290(int a1, void* a2, void* a3, int* a4)
{
    int noun;
    int off;
    char* rec;
    int v;
    if (a2 == 0 || a1 == 0) return;
    *a4 = a1;
    noun = (int)FUN_00f3e8a0(*(int*)a2);
    off = a1 * 0x4e0;
    rec = (char*)(*(int*)(noun + 0x70) + off);
    v = *(int*)(rec + 0x4b8);
    if (!((v == 6) || (v == 4) || (rec[0x4c8] != 0))) return;
    if (!FUN_00d9a110(0, (void*)(*(int*)((char*)a2 + 0x28) + a1 * 0x34 + 0x1c))) return;
    a4[1] = FUN_00d9a190((char*)a2 + 0x28 + a1 * 0x34 - 0x18 + 0x1c, (float*)a3);
    {
        int noun2 = (int)FUN_00f3e8a0(*(int*)a2);
        if (*(int*)(*(int*)(noun2 + 0x70) + off - 0x28) == 6 &&
            *(int*)(rec + 0x4b8) == 4) {
            a4[3] = *(int*)a3;
            a4[4] = *(int*)((char*)a3 + 4);
            a4[5] = *(int*)((char*)a3 + 8);
        }
    }
}

struct Vec3 { float x, y, z; };

struct ICamInfo {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual Vec3* GetPos();      // 0x2c
    virtual Vec3* GetForward();  // 0x30
};

struct AvatarObj {
    uint8_t pad000[0xc0];
    ICamInfo* mCam;              // +0xc0
};
struct NounMgr {
    void* GetAvatar();           // 0x00b1fdb0
};
struct AppObj {};

NounMgr*  SP_NounManager();                       // 0x00b3d300
AvatarObj* NounMgr_GetAvatar(NounMgr* m);         // 0x00b1fdb0
AppObj*   SP_App();                               // 0x0067dd10
void      Viewer_GetCameraLocationInfo(void* viewer, Vec3* out, int, int, int); // 0x007c3d30
Vec3*     FUN_0059aed0(Vec3* dst, const float* src, void* a);                  // 0x0059aed0

// @ 0x00d9a360
bool FUN_00d9a360(Vec3* io, Vec3* out)
{
    AvatarObj* avatar = NounMgr_GetAvatar(SP_NounManager());
    void* app = (void*)SP_App();
    void* viewer = (void*)((void*(*)(void*))(*(void***)app)[0x50 / 4])(app);
    viewer = (void*)((void*(*)(void*))(*(void***)viewer)[0x1c / 4])(viewer);
    if (viewer == 0 || avatar == 0) return false;

    Viewer_GetCameraLocationInfo(viewer, io, 0, 0, 0);

    ICamInfo* cam = avatar->mCam;
    Vec3* pos = cam->GetPos();
    float dx = pos->x - io->x;
    float dy = pos->y - io->y;
    float dz = pos->z - io->z;
    float* fwd = (float*)cam->GetForward();

    Vec3 tmp;
    float* r = (float*)FUN_0059aed0(&tmp, &DAT_0169f2f4, (void*)fwd);
    (void)r;
    float nx = r[0], ny = r[1], nz = r[2];
    float d = nz * dz + nx * dx + ny * dy;
    out->x = dx - d * nx;
    out->y = dy - ny * d;
    out->z = dz - nz * d;
    return true;
}

// @ 0x00d9a4a0
void FUN_00d9a4a0(void* a1, void* a2, void* obj, Vec3* out)
{
    // Reference point = half-extent centre of the object's bounds (slot 0x6c),
    // optionally re-projected through the action-circle / selection transform.
    Vec3  half;
    char* o = (char*)obj;
    float* b = (float*)((void*(*)(void*, Vec3*))(*(void***)o)[0x6c / 4])(o, &half);
    float cx = (b[0] + b[3]) * DAT_01471064;
    float cy = (b[1] + b[4]) * DAT_01471064;
    float cz = (b[2] + b[5]) * DAT_01471064;
    out->x = cx;
    out->y = cy;
    out->z = cz;

    if ((*(uint8_t*)(o + 0x50) & 0x10) == 0) {
        char* circle = (char*)a2 + 0xc0;
        bool ok = true;
        if (!((bool(*)(void*))(*(void***)circle)[0x58 / 4])(circle)) {
            if (!((bool(*)(void*))(*(void***)o)[0x48 / 4])(o)) {
                if (!((bool(*)(void*))(*(void***)circle)[0x48 / 4])(circle)) {
                    ok = false;
                }
            }
        }
        if (ok) {
            Vec3  ref;
            float* r = (float*)((void*(*)(void*, Vec3*))(*(void***)circle)[0x6c / 4])(circle, &ref);
            ref.x = out->x;
            ref.y = out->y;
            ref.z = (r[5] + r[2]) * DAT_01471064;
            FUN_00b3d240_ref(o, &ref, b, out);
            FUN_00b35bf0(r);
        }
    }
    (void)a1; (void)cx;
}

// Generic ref-counted interface with the slots this slice touches.
struct IObj {
    virtual void d00(); virtual void d04(); virtual void d08();
    virtual void* Find(int tag);   // 0x0c
};
struct IObj2 {
    virtual void d00(); virtual void d04(); virtual void d08(); virtual void d0c();
    virtual void d10(); virtual void d14(); virtual void d18(); virtual void d1c();
    virtual void d20(); virtual void d24(); virtual void d28();
    virtual bool Query();          // 0x2c
};

// @ 0x00d9a9c0
bool FUN_00d9a9c0(void* a1, void* a2)
{
    char* p = (char*)a1;
    if (*(int*)(p + 0x64) == 0) return true;
    {
        void* inner = *(void**)(p + 0x64);
        if (inner != 0) {
            void* got = ((IObj*)inner)->Find(0x17f243b);
            if (got != 0) {
                if (((IObj2*)got)->Query()) return false;
                if (got == a2) return false;
            }
        }
    }
    {
        void* q = *(void**)(p + 0x90);
        if (q != 0 && *(int*)((char*)q + 8) == 0x2e81370) return false;
    }
    return true;
}

// @ 0x00d9aa20
void FUN_00d9aa20(void* self, void* a2)
{
    char* s = (char*)self;
    char  buf[0x2a0];
    (void)buf;
    (void)s;
    (void)a2;
}

// Behaviour-tree / animation driver sub-object living at creature+0xb4c; the
// engine calls it via `add ecx,8` then a __thiscall.
struct Playable {
    void* Play(int a, int b);              // 0x00bc96a0
    void  ClearAll(int a, int b);          // 0x00bc98f0
};
struct BehTreeOwner {
    uint8_t pad00[0x1d8];
    int     mAnimState;     // +0x1d8
};

// thiscall vtable-call helper (member-function-pointer form).
static inline Playable* PlayableOf(char* self) {
    return (Playable*)(*(char**)(self + 0xb4c) + 8);
}

// Creature with the virtual slots the slice touches.
struct Creature {
    virtual void d00(); virtual void d04(); virtual void d08(); virtual void d0c();
    virtual void d10(); virtual void d14(); virtual void d18(); virtual void d1c();
    virtual void d20(); virtual void d24(); virtual void d28(); virtual void d2c();
    virtual void d30(); virtual void d34(); virtual void d38(); virtual void d3c();
    virtual void d40(); virtual void d44(); virtual void d48(); virtual void d4c();
    virtual void d50(); virtual void d54(); virtual void d58(); virtual void d5c();
    virtual void d60(); virtual void d64(); virtual void d68(); virtual void d6c();
    virtual void d70(); virtual void d74(); virtual void d78(); virtual void d7c();
    virtual void d80(); virtual void d84(); virtual void d88(); virtual void d8c();
    virtual void d90(); virtual void d94(); virtual void d98(); virtual void d9c();
    virtual void da0(); virtual void da4(); virtual void da8(); virtual void dac();
    virtual void db0(); virtual void db4(); virtual void db8(); virtual void dbc();
    virtual void dc0(); virtual void dc4(); virtual void dc8(); virtual void dcc();
    virtual void dd0(); virtual bool SlotD4();
};

// @ 0x00d9ae60
float FUN_00d9ae60(char* self)
{
    void* r = ((Playable*)(*(char**)(self + 0xb4c) + 8))->Play(0, 0x80);
    if (r == 0 && *(int*)(*(char**)(self + 0xb4c) + 0x1d8) != 0x5218bb3) return 1.0f;
    return 0.0f;
}

// @ 0x00d9aea0
float FUN_00d9aea0(char* self, void* a2, uint flags)
{
    void* r = ((Playable*)(*(char**)(self + 0xb4c) + 8))->Play(0x10000, 0);
    int   mem = FUN_00d999d0(r);
    int   goal = ((Socialable*)self)->GetSocialGoal();
    if (goal == 0) return 0.0f;
    if ((flags & 0x4000000) != 0) return 1.0f;
    GoalBlob* gb = (GoalBlob*)FUN_00b3d4c0_ret(self + 0xb28, self, (void*)mem);
    if (gb->Query() == 5) {
        ((Playable*)(*(char**)(self + 0xb4c) + 8))->ClearAll(0x10000, 0);
        return 0.0f;
    }
    return 1.0f;
}
// @ 0x00d9af20
float FUN_00d9af20(char* self)
{
    void* r = ((Playable*)(*(char**)(self + 0xb4c) + 8))->Play(0x10000, 0);
    int   mem = FUN_00d999d0(r);
    if (mem == 0) return 0.0f;
    if (((Creature*)self)->SlotD4()) return 1.0f;
    return 0.0f;
}


