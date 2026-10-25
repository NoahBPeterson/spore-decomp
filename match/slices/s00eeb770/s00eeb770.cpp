// slice s00eeb770 -- adviser / planet-surface helpers: a refcounted-list removal, two vector
// copies, a large message handler, and small surface-position accessors.
//
// Complex members use a `__thiscall` convention (ecx = this), matching the original code
// which passes `this` in ECX (e.g. the message handler at 0x00eeba40, whose `ecx` is a
// UI object whose own vtable sits 4 bytes before the field block it manipulates).
#include "types.h"

struct Vec3 { float x, y, z; };
struct Vec3i { int x, y, z; };

#include <math.h>  // sqrtf -> fsqrt under /Oi (implied by /O2)
#include <string.h>


struct Manager;
struct GlobalObj {
    char  pad0[0x18];
    void* f18;               // +0x18
    char  pad1[0x58];
    Manager* f74;            // +0x74
    char  pad2[0x5c];
    void* fd4;               // +0xd4  (scenario tutorial UI singleton)
};
extern GlobalObj* g_16c7aa4;

struct Manager {
    int   FUN_00f3be30();
    void* FUN_00f3d780(int a);
    void* FUN_00f3bcb0();
    void* FUN_00f3e8a0(int key);
};

extern int* g_016c7a24;
extern int  g_016c7a28;

// ===========================================================================
// @ 0x00eebf80   int -> [p+0x18] (tail call)
// ===========================================================================
struct XGet { int Get18(); };
int __cdecl f_00eebf80(XGet* p)
{
    if (p == 0)
        return 0;
    return p->Get18();
}

// ===========================================================================
// @ 0x00eebf90
// ===========================================================================
void* __cdecl FUN_005bf860(void* a, int b);
void  __cdecl FUN_005bf120(void* a, void* b, int c, int d);
void __cdecl f_00eebf90(int p1, int p2)
{
    FUN_005bf860((void*)p1, p2);
    FUN_005bf120((void*)(p1 + 8), (void*)p1, 0, 0);
}

// ===========================================================================
// @ 0x00eeb770   remove matching entries from a refcounted list
// ===========================================================================
struct ListEntry {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(int);
    char pad[0x28];
    char flag;               // +0x2c
};

struct VtObj32 {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(int); virtual void v7c(int, bool);
};

struct AudioObj {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual int  v20();
    virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual void v38(unsigned);
    virtual void v3c();
    virtual void v40(unsigned, unsigned);
    virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54();
    virtual void v58();
};

struct MsgObj {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10();
    virtual void v14(unsigned, int, int);
};

struct LayoutObj {
    void* FindWindowByID(unsigned int id, bool recursive);   // 0x008105b0
};

AudioObj* __cdecl GetSystemAT();                             // 0x00a206f0
MsgObj*   __cdecl GetMsgServer();                            // 0x0067dcc0

// copy [first,last) into out, dropping entries equal to *value (EA refcount-aware)
ListEntry** __cdecl FUN_00b6f4f0(ListEntry** first, ListEntry** last, ListEntry** out, ListEntry** value);
ListEntry** __cdecl FUN_006782c0(ListEntry** first, ListEntry** last, ListEntry** out);   // do_copy
void __cdecl FUN_00e26de0(void** first, void** last, void* cmp);                          // SortRecordsA

struct CCList {
    char pad0[0x14];
    VtObj32* f14;            // +0x14
    char pad1[0x0c];
    LayoutObj* layout;       // +0x24
    char pad2[0x14];
    ListEntry** begin;       // +0x3c
    ListEntry** end;         // +0x40
};

void __fastcall f_00eeb770(CCList* c, int dummy, int param_2, char param_3)
{
    (void)dummy;
    if (c->begin != c->end) {
        ListEntry** it = c->begin;
        do {
            ListEntry* e = *it;
            ListEntry* tmp = e;
            e->v24(param_2);
            if (e->flag == 0) {
                ++it;
            } else {
                e->v20();
                ListEntry** p = c->begin;
                while (p != c->end) {
                    if (*p == e) {
                        p = FUN_00b6f4f0(p + 1, c->end, p, &tmp);
                        break;
                    }
                    ++p;
                }
                if (p + 1 < c->end)
                    FUN_006782c0(p + 1, c->end, p);
                c->end = c->end - 1;
                ListEntry* last = *c->end;
                if (last != 0)
                    last->v04();
                AudioObj* a = GetSystemAT();
                int u = 0;
                if (a != 0)
                    u = a->v20();
                AudioObj* b = GetSystemAT();
                if (b != 0) {
                    b->v38(0x03475365);
                    b->v40(0x03475381, 0x956eae88);
                    b->v40(0x03475385, (unsigned)u);
                    b->v58();
                }
                if (param_3 != 0) {
                    MsgObj* m = GetMsgServer();
                    m->v14(0xd69290d7, 0, 0);
                }
            }
        } while (it != c->end);
    }
    FUN_00e26de0((void**)c->begin, (void**)c->end, (void*)0x00eea760);
    if (c->layout != 0 && c->layout->FindWindowByID(0xf68ddb49u, 1) != 0) {
        unsigned n = (unsigned)(c->end - c->begin);
        VtObj32* w = (VtObj32*)c->layout->FindWindowByID(0xf68ddb49u, 1);
        if (w != 0)
            w->v7c(2, n < 0x19);
    }
    if (c->f14 != 0) {
        unsigned n = (unsigned)(c->end - c->begin);
        c->f14->v78(n < 0x19 ? 0x07e4330b : 0x07e4330c);
    }
}

// ===========================================================================
// @ 0x00eeb920   copy list contents into two output vectors (__thiscall, ecx = list)
// ===========================================================================
struct FloatVec {
    float* begin;            // +0x00
    float* end;              // +0x04
    float* cap;              // +0x08
};

struct Vec3Vec {
    Vec3* begin;             // +0x00
    Vec3* end;               // +0x04
    Vec3* cap;               // +0x08
};

void* __cdecl FUN_004b5ad0(void* slot, const Vec3* v);       // SpVector<Vector3>::DoInsertValue
void* __cdecl FUN_00455660(void* slot, const float* v);      // SpVector<float>::DoInsertValue

void __fastcall f_00eeb920(CCList* c, int dummy, FloatVec* out1, Vec3Vec* out2)
{
    (void)dummy;
    if (out1 == 0 || out2 == 0)
        return;

    FUN_00e26de0((void**)c->begin, (void**)c->end, (void*)0x00eea760);

    {
        float* b = out1->begin;
        float* e = out1->end;
        volatile int zero = 0;
        memcpy(b, e, (size_t)zero);                    // inlined erase keeps the zero-size copy
        int d = ((int)((char*)e - (char*)b) >> 2) << 2;
        out1->end = (float*)((char*)e - d);            // erase(begin, end)
    }
    {
        char* b = (char*)out2->begin;
        char* e = (char*)out2->end;
        int d = (int)(e - b) / 12 * 12;
        out2->end = (Vec3*)(e - d);                   // erase(begin, end)
    }

    ListEntry** it = c->begin;
    while (it != c->end) {
        ListEntry* e = *it;
        float v = *(float*)((char*)e + 0x30);
        if (out1->end < out1->cap) {
            float* d = out1->end;
            out1->end = d + 1;
            if (d != 0)
                *d = v;
        } else {
            FUN_00455660(out1->end, &v);
        }
        Vec3 v3;
        v3.x = *(float*)((char*)e + 0x34);
        v3.y = *(float*)((char*)e + 0x38);
        v3.z = *(float*)((char*)e + 0x3c);
        if (out2->end < out2->cap) {
            Vec3* d = out2->end;
            out2->end = d + 1;
            if (d != 0) {
                d->x = v3.x; d->y = v3.y; d->z = v3.z;
            }
        } else {
            FUN_004b5ad0(out2->end, &v3);
        }
        ++it;
    }
}

// ===========================================================================
// @ 0x00eec580   indexed lookup
// ===========================================================================
int __cdecl f_00eec580(int p)
{
    if (p <= 0)
        return 0;
    int n = g_016c7a28;
    while (p > n) {
        p = n;
        if (p <= 0)
            return 0;
    }
    return g_016c7a24[p - 1];
}

// ===========================================================================
// @ 0x00eec540
// ===========================================================================
void __cdecl f_00eec540(int p)
{
    int n = g_016c7a28;
    for (int i = 0; i < n; ++i) {
        if (g_016c7a24[i] > p)
            break;
    }
}

// ===========================================================================
// @ 0x00eec3d0   Vec3i by value (sret)
// ===========================================================================
Vec3i __cdecl f_00eec3d0(int* in)
{
    Vec3i out;
    out.x = 0; out.y = 0; out.z = 0;
    if (in != 0) {
        if (*in == -2) {
            Vec3i* p = (Vec3i*)g_16c7aa4->f74->FUN_00f3bcb0();
            out.x = p->x; out.y = p->y; out.z = p->z;
            return out;
        }
        Vec3i* p = (Vec3i*)g_16c7aa4->f74->FUN_00f3e8a0(*in);
        if (p != 0) {
            out.x = p->x; out.y = p->y; out.z = p->z;
        }
    }
    return out;
}

// ===========================================================================
// @ 0x00eec0d0
// ===========================================================================
void __cdecl f_00eec0d0(int p)
{
    Manager* m = g_16c7aa4->f74;
    m->FUN_00f3d780(p);
}

// ---- surface position / radius at 0x00eec0f0 ----
struct PlanetObj {
    void  DirectionToSurfacePosition(float* out, float* dir);     // 0x00b815a0
    float GetRadiusAt(float* dir);                                // 0x00b7ef70
    float FUN_00b7e500();                                         // 0x00b7e500
    float GetWaterHeight();                                       // 0x00b7e390
};
PlanetObj* __cdecl SP_PlanetModel();                              // 0x00b3d350

// RayHitResult: hit flag at +0, hit position at +0x10 (0x30 bytes total).
struct __declspec(align(16)) RayHitResult {
    int   hit;          // 0x00
    int   r04;          // 0x04
    int   r08;          // 0x08
    int   r0c;          // 0x0c
    float px;           // 0x10
    float py;           // 0x14
    float pz;           // 0x18
    int   r1c;          // 0x1c
    int   rz[4];        // 0x20
};
void __cdecl FUN_00b65b10(float* a, void* ctx, int c, int d, int e, RayHitResult* out);

extern void* g_0167ecd0;                 // ray-query context object (value at 0x0167ecd0)
extern float g_13ec478;                  // == 0.05f

// @ 0x00eec0f0
#pragma float_control(precise, off)
float __cdecl f_00eec0f0(float* dir, char a2, int* out, char a4)
{
    PlanetObj* pm = SP_PlanetModel();

    if (a2 == 0) {
        *out = 2;
        return pm->GetRadiusAt(dir);
    }

    Vec3 pos;
    pm->DirectionToSurfacePosition(&pos.x, dir);

    float dist = 0.0f;
    float flag = 0.0f;
    float f1 = pos.z * pos.z + (pos.x * pos.x + pos.y * pos.y);
    float f2 = (float)sqrt((double)f1);

    Vec3 v;
    if (a4 == 0) {
        v.x = dir[0];
        v.y = dir[1];
        v.z = dir[2];
        flag = g_13ec478;
        dist = f2 - (float)sqrt((double)(v.x * v.x + (dir[1] * dir[1] + dir[2] * dir[2])));
    } else {
        v.x = pos.x;
        v.y = pos.y;
        v.z = pos.z;
        float r = pm->FUN_00b7e500();
        dist = 0.0f;
        flag = r - f2;
    }

    RayHitResult res;
    res.rz[0] = res.rz[1] = res.rz[2] = res.rz[3] = 0;
    FUN_00b65b10(&v.x, g_0167ecd0, 0, 1, 6, &res);
    if (res.hit != 0) {
        float f3 = (res.py * res.py + res.pz * res.pz) + res.px * res.px;
        if (f1 < f3) {
            *out = res.hit;
            return (float)sqrt((double)f3);
        }
    }
    *out = 2;
    return f2;
}

// ===========================================================================
// @ 0x00eec2b0   scaled surface direction
// ===========================================================================
void __cdecl f_00eec2b0(float* out, float* dir, int a3, int* flag, int a5)
{
    float h = f_00eec0f0(dir, (char)a3, flag, (char)a5);
    PlanetObj* pm = SP_PlanetModel();
    float wh = pm->GetWaterHeight();
    float hh;
    if (wh > h) {
        *flag = 4;
        hh = wh;
    } else {
        hh = h;
    }
    float x = dir[0];
    float inv = (float)(1.0 / sqrt((double)x * x + (double)dir[1] * dir[1] + (double)dir[2] * dir[2]));
    float xi = (float)(x * inv);
    float yi = (float)(dir[1] * inv);
    float zi = (float)(dir[2] * inv);
    out[0] = (float)(xi * hh);
    out[1] = (float)(yi * hh);
    out[2] = (float)(zi * hh);
}

// ===========================================================================
// @ 0x00eec370
// ===========================================================================
#pragma float_control(precise, off)
float __cdecl f_00eec370(float* dir, int a2, int a3)
{
    float local[3];
    f_00eec2b0(local, dir, a2, (int*)a3, 1);
    float d1 = (float)sqrt((double)(dir[0] * dir[0] + dir[1] * dir[1] + dir[2] * dir[2]));
    float s = (local[0] * local[0] + local[1] * local[1]) + local[2] * local[2];
    return d1 - (float)sqrt((double)s);
}

// ===========================================================================
// @ 0x00eec440   orient/scale a direction from a physics object
// ===========================================================================
struct PhysObj {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual int  QueryInterface(unsigned id);                    // v0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90(); virtual void v94(); virtual void v98(); virtual void v9c();
    virtual void va0(); virtual void va4(); virtual void va8(); virtual void vac();
    virtual void vb0(); virtual void vb4();
    virtual int  vB8(unsigned id);
};

struct BodyObj {
    bool FUN_00f25680();                                       // body validity check
};
struct SurfObj {
    void FUN_00c9ff40(void* v, void* a, void* b);              // surface query -> two floats
};
void* __cdecl SP_normalized_safe(void* out, float* v);

void __cdecl f_00eec440(int* param_1)
{
    void* a = g_16c7aa4->f74->FUN_00f3d780((int)param_1);
    if (a == 0)
        return;
    PhysObj* obj = (PhysObj*)a;
    if (obj->QueryInterface(0x01186577) == 0)
        return;
    void* body = g_16c7aa4->f74->FUN_00f3e8a0(*param_1);
    if (body == 0)
        return;
    if (!((BodyObj*)body)->FUN_00f25680())
        return;
    int r = obj->vB8(0x0137e8e0);
    if (r == 0)
        return;

    float tmp[2];
    ((SurfObj*)(void*)r)->FUN_00c9ff40((float*)param_1 + 1, &tmp[0], &tmp[1]);
    float norm[3];
    float* dir = (float*)SP_normalized_safe(norm, (float*)param_1 + 1);
    float scale = tmp[0];
    float sx = dir[0] * scale;
    float sy = dir[1] * scale;
    float sz = dir[2] * scale;
    ((float*)param_1)[1] = sx;
    ((float*)param_1)[2] = sy;
    ((float*)param_1)[3] = sz;
    ((float*)param_1)[0x88] = tmp[1];
}

// ===========================================================================
// @ 0x00eebfc0   vector reserve + key find
// ===========================================================================
extern void* g_016c7a58;                                     // vector allocator
bool __cdecl FUN_006a0ae0(void* param_1, void* alloc, int* outCount, void** outData);

bool __cdecl f_00eebfc0(int param_1, int* param_2)
{
    bool found = false;
    int cnt;
    void* data;
    if (FUN_006a0ae0((void*)param_1, g_016c7a58, &cnt, &data)) {
        int n = cnt;
        int* p = (int*)data;
        for (int i = 0; i < n; i++) {
            if (found)
                break;
            if (p[0] == param_2[0] && p[1] == param_2[1] && p[2] == param_2[2])
                found = true;
            else
                found = false;
            p += 3;
        }
    }
    return found;
}

// ---- large adviser message handler (__thiscall, ecx = UI object) at 0x00eeba40 ----
struct Batch2D;

struct RenderCtx {
    void* Begin2D(void* mode);                               // 0x0095bc10
    void  End2D();                                           // 0x0095bb20
};

struct FrameObj {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c(void* f10, float f30, float f34, float f38, float f3c, void* a);
    virtual void v20(); virtual void v24();
    virtual void v28(int);
    char  pad04[0x14];
    void* f18;               // +0x18
};
struct WinTextFace {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void* v38();
};
struct WindowMgr {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void* v54(int); virtual void v58(int, void*); virtual void v5c(int, void*);
};
struct WinMgr {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void* v54(int); virtual void v58(int, void*); virtual void v5c(int, void*);
};

// The UI object's *own* vtable pointer precedes the first field the handler touches, so the
// handler's `this` (ecx) points 4 bytes past that vtable.  Modelling a small leading vtable
// (slots used at +0x18 and +0x1c of the object = slots after the pointer) lets us call
// `self->v18` / `self->v1c` through the interface object instead of raw vtable math.
struct _vtab { virtual void* v(int a, int b); };
struct Adviser {
    _vtab  vt;               // +0x00 (vtable pointer)
    int    f04;              // +0x04
    char   pad08[0x08];
    WinTextFace* f10;        // +0x10  (skin text face)
    int    f14;              // +0x14
    char   pad18[0x20];
    void*  f38;              // +0x38  (vector begin)
    char   pad3c[0x10];
    void*  f4c;              // +0x4c
    float  f54;              // +0x54
};

void  __cdecl FUN_00eeacc0(void* self, void* batch);
void* __cdecl FUN_00eea8b0(void* self, int a);
bool  __cdecl FUN_008d3200(int a, int b);
void* __cdecl FUN_00f473a0(unsigned size, const char* type, int a, int b, int c, int d); // ??2@YAPAXIPBDHHHH@Z
void* __cdecl FUN_00ee9be0(void* p);
void  __cdecl FUN_572660(FrameObj** out, FrameObj* p);
void  __cdecl FUN_00e1c7f0(void* self, FrameObj** p);
void  __cdecl FUN_00f33bf0(int self);
void  __cdecl FUN_00ee9e90(void* self, void* a, int b);
void  __cdecl FUN_00eea860(void* self, int a);
void  __cdecl FUN_00ed1350(int a, int b);
void  __cdecl FUN_00efbbe0(void* self, int a, int b);
void  __cdecl FUN_00eeab90(void* self, float* out, float v);
void  __cdecl FUN_00f32410(int self);
void  __cdecl FUN_00f34560(void* self);
void  __cdecl FUN_00f31ec0(void* self);
void  __cdecl FUN_00540520(FloatVec* p);
void  __cdecl FUN_004e1bf0(Vec3Vec* p);
void  __cdecl FUN_00f344e0(void* a, void* b);
void  __cdecl FUN_00eea2f0(void* self, void* a, void* b);
void  __cdecl FUN_00eeaf00(void* self, int a);
void  __cdecl FUN_00ee9f10(void* self, void* a, void* b);
void  __cdecl RecordEvent2(unsigned a, unsigned b);
void* __cdecl SP_WindowManager();                            // 0x0067caa0
MsgObj* __cdecl SP_MessageServer();                          // 0x0067dcc0

extern float g_13eb1bc;                                      // == -1.0f
extern float g_13eeda0;                                      // == 8.0f

struct HelperCalls {
    void* FUN_00eea8b0(int a);                                 // __thiscall, ret 4
    void  FUN_00ee9f10(void* a, void* b);                      // __thiscall, ret 8
    void  FUN_00eeaf00(int a);                                 // __thiscall, ret 4
};

// @ 0x00eeba40
bool __fastcall f_00eeba40(Adviser* self, int dummy, int arg1, int msg)
{
    (void)dummy;
    char* p = (char*)msg;
    unsigned id = *(unsigned*)(p + 8);

    if (id > 0x287259f6) {
        /* no case */
    } else if (id == 0x287259f6) {
        if (*(int*)(p + 0xc) == -0x97224b7) {
            ((HelperCalls*)((char*)self - 4))->FUN_00eeaf00(1);
            int u = 0;
            AudioObj* a = GetSystemAT();
            if (a != 0)
                u = a->v20();
            RecordEvent2(0xe76c9b4f, (unsigned)u);
        }
    } else {
        unsigned sel = id - 6;
        if (sel > 7)
            return false;

        switch (sel) {
        case 0:
            if (*(int*)(p + 0x18) == 1000) {
                void* e = ((HelperCalls*)((char*)self - 4))->FUN_00eea8b0(arg1);
                if (e != 0) {
                    unsigned n = (unsigned)((*(char**)((char*)self + 0x3c) - *(char**)((char*)self + 0x38)) / 4);
                    if (FUN_008d3200(0x12, 0x3ff) && n >= 0x19)
                        goto alt_case0;
                    FrameObj* w;
                    {
                        w = (FrameObj*)FUN_00f473a0(0x54, (const char*)0x013f6b3c, 0, 0, 0, 0);
                        if (w != 0)
                            w = (FrameObj*)FUN_00ee9be0(w);
                        else
                            w = 0;
                        w->v1c(self->f10, *(float*)((char*)e + 0x30), *(float*)((char*)e + 0x34),
                               *(float*)((char*)e + 0x38), *(float*)((char*)e + 0x3c), 0);
                        w->v28(1);
                        FrameObj* sp;
                        FUN_572660(&sp, w);
                        FUN_00e1c7f0((char*)self + 0x38, &sp);
                        if (sp != 0)
                            (*(void(**)(FrameObj*))((*(char**)sp) + 4))(sp);
                        WindowMgr* wm = (WindowMgr*)SP_WindowManager();
                        wm->v58(1, w->f18);
                        FUN_00f33bf0(self->f14);
                        FUN_00ee9e90((void*)w->f18, (void*)e, 1);
                        self->f54 = g_13eb1bc;
                    }
                    goto case0_tail;
alt_case0:
                    {
                        w = (FrameObj*)FUN_00f473a0(0x54, (const char*)0x013f6b3c, 0, 0, 0, 0);
                        if (w != 0)
                            w = (FrameObj*)FUN_00ee9be0(w);
                        else
                            w = 0;
                        void* q = (void*)self->f10->v38();
                        float t = *(float*)(p + 0x10) / ((*(float*)((char*)q + 0xc) - *(float*)((char*)q + 4)) - g_13eeda0);
                        float fv;
                        FUN_00eeab90(self, &fv, t);
                        w->v1c(self->f10, t, 0, 0, 0, 0);
                        w->v28(1);
                        FrameObj* sp;
                        FUN_572660(&sp, w);
                        FUN_00e1c7f0((char*)self + 0x38, &sp);
                        if (sp != 0)
                            (*(void(**)(FrameObj*))((*(char**)sp) + 4))(sp);
                        WindowMgr* wm = (WindowMgr*)SP_WindowManager();
                        wm->v58(1, w->f18);
                        FUN_00f33bf0(self->f14);
                        FUN_00ee9e90((void*)w->f18, (void*)e, 0);
                        self->f54 = *(float*)((char*)self->f4c + 0x30);
                    }
case0_tail:
                    FUN_00eea860(self, 0);
                    FUN_00ed1350(*(int*)(*(char**)((char*)self + 0x4c) + 0x14), 1);
                    return true;
                }
                if (arg1 == (int)self->f10) {
                    unsigned n = (unsigned)((*(char**)((char*)self + 0x3c) - *(char**)((char*)self + 0x38)) / 4);
                    if (n < 0x19) {
                        FrameObj* w;
                        w = (FrameObj*)FUN_00f473a0(0x54, (const char*)0x013f6b3c, 0, 0, 0, 0);
                        if (w != 0)
                            w = (FrameObj*)FUN_00ee9be0(w);
                        else
                            w = 0;
                        void* q = (void*)self->f10->v38();
                        float t = *(float*)(p + 0x10) / ((*(float*)((char*)q + 0xc) - *(float*)((char*)q + 4)) - g_13eeda0);
                        float fv;
                        FUN_00eeab90(self, &fv, t);
                        w->v1c(self->f10, t, 0, 0, 0, 0);
                        w->v28(1);
                        FrameObj* sp;
                        FUN_572660(&sp, w);
                        FUN_00e1c7f0((char*)self + 0x38, &sp);
                        if (sp != 0)
                            (*(void(**)(FrameObj*))((*(char**)sp) + 4))(sp);
                        WindowMgr* wm = (WindowMgr*)SP_WindowManager();
                        wm->v58(1, w->f18);
                        FUN_00f33bf0(self->f14);
                        FUN_00ee9e90((void*)w->f18, (void*)e, 0);
                        self->f54 = g_13eb1bc;
                        FUN_00eea860(self, 0);
                        FUN_00ed1350(*(int*)(*(char**)((char*)self + 0x4c) + 0x14), 1);
                        FUN_00efbbe0(g_16c7aa4->fd4, 0x94, 0x95);
                        return true;
                    }
                }
            }
            return false;
        case 1:
            if (*(int*)(p + 0x18) == 1000 && self->f4c != 0) {
                FUN_00eea2f0(self, (char*)self + 0x4c, (void*)msg);
                if (*(float*)((char*)self->f4c + 0x30) == self->f54) {
                    FUN_00f32410(self->f14);
                } else {
                    MsgObj* m = SP_MessageServer();
                    m->v14(0xd69290d8, 0, 0);
                    if (*(char*)((char*)self->f4c + 0x50) != 0) {
                        (*(void(**)(void*, int, int))((*(char**)self) + 0x18))(self, 0x14, 0);
                        FloatVec a; a.begin = 0; a.end = 0; a.cap = 0;
                        Vec3Vec b;  b.begin = 0; b.end = 0; b.cap = 0;
                        f_00eeb920((CCList*)self, 0, &a, &b);
                        FUN_00f344e0(self, (void*)((char*)self - 4));
                        MsgObj* m2 = SP_MessageServer();
                        m2->v14(0x07e1ea71, 0, 0);
                        FUN_00540520(&a);
                        FUN_004e1bf0(&b);
                    }
                    FUN_00f34560(self);
                    FUN_00f31ec0(self);
                }
                if (self->f4c != 0) {
                    (*(void(**)(void*))((*(char**)self->f4c) + 4))(self->f4c);
                    self->f4c = 0;
                }
                {
                    WindowMgr* wm1 = (WindowMgr*)SP_WindowManager();
                    WinMgr* wm2 = (WinMgr*)SP_WindowManager();
                    void* back = wm1->v54(1);
                    wm2->v5c(1, back);
                }
                FUN_00efbbe0(g_16c7aa4->fd4, 0x92, 0x93);
                return true;
            }
            return false;
        case 2:
            if (self->f4c != 0) {
                ((HelperCalls*)self->f4c)->FUN_00ee9f10((void*)arg1, (void*)msg);
                MsgObj* m = SP_MessageServer();
                m->v14(0xd69290d8, 0, 0);
                return true;
            }
            return false;
        case 4:
            if (*(int*)(p + 0xc) == 1)
                return true;
            return false;
        case 7:
            if (arg1 == self->f14) {
                RenderCtx* rc = *(RenderCtx**)(p + 0x18);
                void* b = rc->Begin2D(0);
                FUN_00eeacc0((void*)((char*)self - 4), b);
                rc->End2D();
                return true;
            }
            return false;
        default:
            return false;
        }
    }
    return false;
}
