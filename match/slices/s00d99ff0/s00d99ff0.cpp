// SporeApp.exe frozen batch "gold4" — slice s00d99ff0 (11 functions)
// Creature social/interaction predicates and helpers.
#include "types.h"

typedef unsigned int uint;
typedef unsigned int uintptr_t;

extern "C" float sqrtf(float);

// ---------------------------------------------------------------- externals
void  operator_delete_arr(void* p);                    // 0x00f47380
struct DB {
    void* FUN_00f3e8a0(int nounID);                    // 0x00f3e8a0 (thiscall: self = *(DAT_016c7aa4+0x74))
};
void* FUN_00ac80d0(void* obj, int type);               // 0x00ac80d0
void* CastCreature(void* obj);                         // 0x00ae66f0
void  FUN_00c41ec0(void* self);                        // 0x00c41ec0
struct C41Obj { char* Method(); };                     // 0x00c41ec0 (__thiscall)
void  FUN_0059aed0(void* dst, const void* src, int a); // 0x0059aed0
void* FUN_00b3d240(...);                               // 0x00b3d240 (query builder)
void* FUN_00b3d3c0(...);                               // 0x00b3d3c0 (scan context getter)
void* FUN_00b3d350(...);                               // 0x00b3d350 (planet model / query context)
void* FUN_00b3d4c0(void);                              // 0x00b3d4c0 (argless global getter)
struct Query     { bool Run(); };                      // 0x00b35bf0
void  FUN_00b79c30(...);                               // 0x00b79c30 (list filter/append)
void  FUN_00ba3f90(void);                              // 0x00ba3f90 (__thiscall, ret 0xc)
void* FUN_00b815a0(...);                               // 0x00b815a0 (transform point)
float FUN_00b7e390(...);                               // 0x00b7e390 (distance/radius)
void  FUN_00bc96a0(void);                              // 0x00bc96a0
void  FUN_00bc98f0(void);                              // 0x00bc98f0
int   FUN_00c0e6a0(void* a);                           // 0x00c0e6a0
int   FUN_00ba3f90_ret();                              // 0x00ba3f90
struct Socialable { int GetSocialGoal(); };            // 0x00c0e6a0
struct GoalBlob  { int Query(float* goal, void* cre, void* mem); }; // 0x00ba3f90 (__thiscall, ret 0xc)
void  FUN_00b3d240_ref(void* a, void* b, void* c, void* d);  // 0x00b3d240
void  FUN_00c897e0(...);                               // 0x00c897e0
void  FUN_0059c190(...);                               // 0x0059c190
void  FUN_0041cb40(...);                               // 0x0041cb40 (matrix ctor)
void  FUN_004ff6d0(...);                               // 0x004ff6d0 (back-transform)
bool  FUN_006989d0(...);                               // 0x006989d0 (ray/segment test)
int   FUN_00d999d0(void* p);                           // 0x00d999d0
void* __fastcall FUN_00af9ff0(void* self, void* dummy, int i);  // 0x00af9ff0 (ret 4)
void  __fastcall FUN_00afa070(void* self, void* dummy, int kind); // 0x00afa070 (ret 4)
void* __fastcall FUN_00b81630(void* self, void* dummy, void* dst, void* src); // 0x00b81630 (ret 8)
void* FUN_00b1fdb0(void);                              // 0x00b1fdb0
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

// Virtual slots the interaction predicate walks: Find(tag) at +0xb8 and the
// tag/flag queries at +0x20 and +0xf8 are __thiscall.
typedef void* (__thiscall *PFN_Find)(void*, int);
typedef int   (__thiscall *PFN_Tag)(void*);
typedef bool  (__thiscall *PFN_Query)(void*);

// @ 0x00d99ff0
bool FUN_00d99ff0(void* obj, uint flags)
{
    void* p;
    int   tag;
    if (obj == 0) goto fail;
    p = ((PFN_Find)(*(void***)obj)[0xb8 / 4])(obj, 0x17f243b);
    if (p == 0) goto fail;
    tag = ((PFN_Tag)(*(void***)p)[0x20 / 4])(p);

    if (tag > 0x2c9cc91) {
        if (tag > 0x3ed8573) {
            if (tag == 0x52aa6122) return true;
            goto fail;
        }
        if (tag == 0x3ed8573) return true;
        if (tag == 0x2e72cae) return true;
        if (tag != 0x3a2511e) goto fail;
        {
            void* r = FUN_00ac80d0(p, tag);
            if (*(int*)((char*)r + 0x108) == 0) goto fail;
        }
        return true;
    }
    if (tag == 0x2c9cc91) return true;
    if (tag > 0x18c88e4) {
        if (tag == 0x18eb45e || tag == 0x18eb4b7) {
            if ((flags & 1) == 0) return true;
            {
                char* c = (char*)CastCreature(obj);
                if (c[0x137] == 0) return true;
                if (c[0xb5e] != 0) return true;
                void* vt = (char*)c + 0xc0;
                char* r = ((C41Obj*)vt)->Method();
                if (*(int*)(r + 0x5c) == 0) return false;
                if (((PFN_Query)(*(void***)vt)[0xf8 / 4])(vt)) return true;
            }
            return false;
        }
        goto fail;
    }
    if (tag == 0x18c88e4) {
        void* r = FUN_00ac80d0(p, tag);
        int v = *(int*)((char*)r + 0x228);
        if (v == 0x5b9a06e) return false;
        if (v != 0x5d97f762) return true;
        return false;
    }
    if (tag == 0x18c431c) return true;
    if (tag == 0x18c84a9) return true;
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
    if (a2 == 0) return;
    if (a1 == 0) return;
    *a4 = a1;
    noun = (int)((DB*)*(void**)((char*)DAT_016c7aa4 + 0x74))->FUN_00f3e8a0(*(int*)a2);
    off = a1 * 0x4e0;
    rec = (char*)(*(int*)(noun + 0x70) + off);
    v = *(int*)(rec + 0x4b8);
    if (!((v == 6) || (v == 4) || (rec[0x4c8] != 0))) return;
    if (!FUN_00d9a110((void*)(*(int*)((char*)a2 + 0x28) + a1 * 0x34 - 0x18),
                     (void*)(*(int*)((char*)a2 + 0x28) + a1 * 0x34 + 0x1c))) return;
    a4[1] = FUN_00d9a190((char*)a2 + 0x28 + a1 * 0x34 - 0x18 + 0x1c, (float*)a3);
    {
        int noun2 = (int)((DB*)*(void**)((char*)DAT_016c7aa4 + 0x74))->FUN_00f3e8a0(*(int*)a2);
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

struct Viewer { void __stdcall GetCameraLocationInfo(int, int, int, Vec3* out); }; // 0x007c3d30
typedef void* (__thiscall *PFN_NoArg)(void*);

NounMgr*  SP_NounManager();                       // 0x00b3d300
AppObj*   SP_App();                               // 0x0067dd10
Vec3*     FUN_0059aed0(Vec3* dst, const float* src, void* a);                  // 0x0059aed0

// @ 0x00d9a360
bool FUN_00d9a360(Vec3* io, Vec3* out)
{
    AvatarObj* avatar = (AvatarObj*)((NounMgr*)SP_NounManager())->GetAvatar();
    void* app = (void*)SP_App();
    void* viewer = ((PFN_NoArg)(*(void***)app)[0x50 / 4])(app);
    viewer = ((PFN_NoArg)(*(void***)viewer)[0x1c / 4])(viewer);
    if (viewer == 0 || avatar == 0) return false;

    ((Viewer*)viewer)->GetCameraLocationInfo(0, 0, 0, io);

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

typedef void* (__thiscall *PFN_Bounds)(void*, void*);   // vtable +0x6c: float* bounds
typedef bool  (__thiscall *PFN_Test)(void*);            // vtable +0x48/+0x58
typedef float (__thiscall *PFN_Float)(void*);           // vtable +0x74
struct TransformObj { void FUN_00c897e0(void* xf); };  // 0x00c897e0 LocalToWorld
struct Xf { void FUN_004ff6d0(Vec3* p); };             // 0x004ff6d0 BackTransform
void* FUN_00449c20(...);                                // 0x00449c20 normalized_safe

bool FUN_00d99ff0(void* obj, uint flags);
static bool scanVisitor(void* p, uint flags);
static Vec3 boundsCentre(void* obj)
{
    Vec3  scratch;
    float* b = (float*)((PFN_Bounds)(*(void***)obj)[0x6c / 4])(obj, &scratch);
    Vec3  c;
    c.x = (b[0] + b[3]) * DAT_01471064;
    c.y = (b[1] + b[4]) * DAT_01471064;
    c.z = (b[2] + b[5]) * DAT_01471064;
    return c;
}

// @ 0x00d9a4a0
Vec3* FUN_00d9a4a0(Vec3* out, void* a2, void* obj)
{
    // Reference point = half-extent centre of the object's bounds (slot 0x6c).
    char* o = (char*)obj;
    Vec3  c = boundsCentre(o);
    *out = c;

    // Selection/action-circle pass: when the object is not already selected, ask the
    // action circle (a2+0xc0) whether the point should be pulled to its surface.
    bool reprojected = false;
    if ((*(uint8_t*)(o + 0x50) & 0x10) == 0) {
        char* circle = (char*)a2 + 0xc0;
        bool ok = ((PFN_Test)(*(void***)circle)[0x58 / 4])(circle);
        if (!ok) ok = ((PFN_Test)(*(void***)o)[0x48 / 4])(o);
        if (!ok) ok = ((PFN_Test)(*(void***)circle)[0x48 / 4])(circle);
        if (ok) {
            Vec3  ref;
            Vec3* rb = (Vec3*)((PFN_Bounds)(*(void***)circle)[0x6c / 4])(circle, &ref);
            ref.x = out->x;
            ref.y = out->y;
            ref.z = (rb->z + *(float*)((char*)rb + 8)) * DAT_01471064;
            c = boundsCentre(o);
            void* q = FUN_00b3d240(o, &ref, &c, out);
            reprojected = ((Query*)q)->Run();
        }
    }

    // Projected path: build the object->world transform, back-transform both the
    // circle centre and the current point, then clip against the circle plane.
    if (((PFN_Test)(*(void***)o)[0x48 / 4])(o) && !reprojected) {
        float xf[0x20];
        // transform header: rotation rows at +0x18, translation at +0x04,
        // uniform scale at +0x4c (the original fills these from .rdata).
        for (int i = 0; i < 0x20; i++) xf[i] = 0.0f;
        ((float*)xf)[0x04] = 0.0f;
        ((float*)xf)[0x05] = DAT_0169f2a4;
        ((float*)xf)[0x06] = DAT_0169f2a8;
        ((float*)xf)[0x07] = DAT_0169f2ac;
        ((float*)xf)[0x08] = 1.0f;
        FUN_0041cb40(&((float*)xf)[0x18], &DAT_0169f300);
        ((TransformObj*)o)->FUN_00c897e0(xf);

        void* u = ((PFN_NoArg)(*(void***)o)[0x68 / 4])(o);
        Vec3  p1 = boundsCentre((char*)a2 + 0xc0);
        ((Xf*)xf)->FUN_004ff6d0(&p1);
        ((Xf*)xf)->FUN_004ff6d0(out);

        float t = 0.0f;
        if (FUN_006989d0(&p1, out, u, &t)) {
            out->x = (out->x - p1.x) * t + p1.x;
            out->y = (out->y - p1.y) * t + p1.y;
            out->z = (out->z - p1.z) * t + p1.z;
            if (((int*)xf)[0] & 2) {
                float x = out->x, y = out->y, z = out->z;
                out->x = ((float*)xf)[0x14] * z + ((float*)xf)[0x11] * y + ((float*)xf)[0x0e] * x;
                out->y = ((float*)xf)[0x15] * z + ((float*)xf)[0x12] * y + ((float*)xf)[0x0f] * x;
                out->z = ((float*)xf)[0x16] * z + ((float*)xf)[0x13] * y + ((float*)xf)[0x10] * x;
            }
            float s = ((float*)xf)[0x13];
            out->x = s * out->x + ((float*)xf)[0x01];
            out->y = s * out->y + ((float*)xf)[0x02];
            out->z = s * out->z + ((float*)xf)[0x03];
            return out;
        }

        // No clipping result: push the point out to the object radius along the
        // normalized direction from the circle centre.
        float r = ((PFN_Float)(*(void***)o)[0x74 / 4])(o);
        Vec3  centre = boundsCentre((char*)a2 + 0xc0);
        Vec3  d;
        d.x = centre.x - out->x;
        d.y = centre.y - out->y;
        d.z = centre.z - out->z;
        Vec3  tmp;
        float* n = (float*)FUN_00449c20(&tmp, &d);
        out->x = out->x + n[0] * r;
        out->y = out->y + n[1] * r;
        out->z = out->z + n[2] * r;
    }
    return out;
}

// Callback handed to the spatial query (original local label 00d9a960): accept a
// candidate while the interaction predicate says it is not the current target.
static bool scanVisitor(void* p, uint flags)
{
    char* o = (char*)p;
    if (*(int*)(o + 0x64) == 0) return false;
    void* q = *(void**)(o + 0x90);
    if (q != 0 && *(int*)((char*)q + 8) == 0x2e81370) return false;
    void* inner = *(void**)(o + 0x64);
    if (inner != 0) {
        void* got = ((PFN_Find)(*(void***)inner)[0x0c / 4])(inner, 0x1186577);
        if (got != 0) {
            if (FUN_00d99ff0(got, flags)) return false;
            return true;
        }
    }
    return false;
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

// Action-circle scan: gather nearby objects around self+0x14, optionally move each
// candidate position to the planet surface, then classify hits through the verb grid.
struct ScanRec {                 // candidate record produced by the query helpers
    uint8_t  mSkip;              // +0x00 non-zero = ignore
    uint8_t  pad01[0xb];
    float    mX, mY, mZ;         // +0x0c
};
struct ScanObj {
    uint8_t  pad00[0x38];
    float    mX, mY, mZ;         // +0x38
    float    mRadius;            // +0x44
    uint8_t  pad48[0x2f];
    uint8_t  mLocal;             // +0x77
};
typedef void  (__thiscall *PFN_QueryFn)(void*);         // vtable +0x48
// The sort helper takes six stack arguments and pops them itself (LTCG ABI), so
// it is modelled as a free __fastcall with an unused edx slot.
typedef void  (__fastcall *PFN_Sort)(void* self, void* dummy, Vec3* centre, float tag,
                                     void*** list, void* a5,
                                     bool (__cdecl *cb)(void*, uint), void* a7);
typedef float (__thiscall *PFN_Radius)(void*);          // vtable +0x74
typedef float*(__thiscall *PFN_Point)(void*);           // vtable +0x2c
typedef void  (__thiscall *PFN_Release)(void*);         // vtable +0xc0

void  __fastcall FUN_00b79c30(void* self, void* dummy, Vec3* centre, void* a,
                              int b, float c, void* d, void* e);   // 0x00b79c30 (ret 0x18)
void* __fastcall FUN_00b815a0(void* self, void* dummy, void* dst, float* p); // 0x00b815a0 (ret 8)

struct PM {
    float FUN_00b7e390();                       // 0x00b7e390 water height (thiscall)
};

// @ 0x00d9aa20
void FUN_00d9aa20(void* self)
{
    char*  s      = (char*)self;
    float  tag    = *(float*)(s + 0x0c);
    float  radius = *(float*)(s + 0x10);
    Vec3*  centre = (Vec3*)(s + 0x14);
    bool   torus  = *(uint8_t*)(s + 0x28) != 0;

    // Nearby-object list produced by the scan context, and the sorted candidate
    // vector produced by the query helper.  Both are EASTL vectors in the original.
    void*  nearStore[64];
    void** nearBegin = nearStore;
    void** nearEnd   = nearStore;
    void*  candStore[64];
    void** candBegin = candStore;
    void** candEnd   = candStore;

    // 0x00b3d3c0 returns the scan context (ecx); 0x00b79c30 filters by tag and
    // pops its six stack arguments itself (LTCG ABI).
    FUN_00b79c30(FUN_00b3d3c0(), 0, centre, &nearBegin, 0x1f, tag, 0, 0);

    void* sorter = FUN_00b3d240();
    // The query fills the sorted candidate vector using the interaction predicate
    // as its acceptance callback.
    ((PFN_Sort)(*(void***)sorter)[0x48 / 4])(sorter, 0, centre, tag,
                                             &candBegin, 0, scanVisitor, 0);

    float m[16];
    FUN_0059c190(m, s + 0x2c);
    PM* pm = (PM*)FUN_00b3d350();
    float water = pm->FUN_00b7e390();
    float waterSq = water * water;

    int n = 0;
    for (char* rec = (char*)FUN_00af9ff0(s, 0, 0); rec != 0;
         rec = (char*)FUN_00af9ff0(s, 0, n)) {
        n++;
        if (rec[0] != 0) continue;

        ScanRec* r = (ScanRec*)rec;
        float px = r->mX, py = r->mY, pz = r->mZ;

        if (torus) {
            // rotate the local offset by the quaternion matrix and add the origin
            float tx = centre->x + (m[6] * pz + m[3] * py + m[0] * px);
            float ty = centre->y + (m[7] * pz + m[4] * py + m[1] * px);
            float tz = centre->z + (m[8] * pz + m[5] * py + m[2] * px);
            Vec3  tmp;
            float* q = (float*)FUN_00b815a0(pm, 0, &tmp, &tx);
            px = q[0]; py = q[1]; pz = q[2];
        }

        if (!(waterSq < px * px + py * py + pz * pz)) {
            FUN_00afa070(rec, 0, 1);
            continue;
        }

        // first pass: nearby objects (bounds position + radius)
        for (void** it = nearBegin; it != nearEnd; ++it) {
            ScanObj* o = (ScanObj*)*it;
            float rad = o->mRadius + radius;
            float dx = px - o->mX, dy = py - o->mY, dz = pz - o->mZ;
            if (dx * dx + dy * dy + dz * dz < rad * rad)
                FUN_00afa070(rec, 0, 1);
        }

        // second pass: verb entries from the sorted list, with their own radius
        for (void** it = candBegin; it != candEnd; ++it) {
            ScanObj* o = (ScanObj*)*it;
            float v = ((PFN_Radius)(*(void***)o)[0x74 / 4])(o);
            float lim = v - radius;
            if (!(0.1f <= lim)) lim = 0.1f;
            float* q;
            if (o->mLocal) q = ((PFN_Point)(*(void***)o)[0x2c / 4])(o);
            else {
                Vec3 tmp;
                q = (float*)FUN_00b81630(pm, 0, &tmp,
                                         ((PFN_Point)(*(void***)o)[0x2c / 4])(o));
            }
            float dx = px - q[0], dy = py - q[1], dz = pz - q[2];
            if (dx * dx + dy * dy + dz * dz < (lim + radius) * (lim + radius))
                FUN_00afa070(rec, 0, 2);
        }
    }

    // release the sorted candidates
    for (void** it = candBegin; it != candEnd; ++it) {
        void* o = *it;
        if (o != 0) ((PFN_Release)(*(void***)o)[0xc0 / 4])(o);
    }
}

struct CreatureTail {
    uint8_t pad00[0xb28];
    Vec3    mCachedFlockGoal;      // +0xb28
};

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
float FUN_00d9aea0(char* self, void* a2, void* a3, uint flags)
{
    void* r = ((Playable*)(*(char**)(self + 0xb4c) + 8))->Play(0x10000, 0);
    int   mem = FUN_00d999d0(r);
    int   goal = ((Socialable*)self)->GetSocialGoal();
    if (goal == 0) return 0.0f;
    if ((flags & 0x4000000) != 0) return 1.0f;
    Vec3* pcVar3 = &((CreatureTail*)self)->mCachedFlockGoal;
    char* pcVar4 = self;
    int q = ((GoalBlob*)FUN_00b3d4c0())->Query((float*)pcVar3, pcVar4, (void*)mem);
    if (q == 5) {
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


