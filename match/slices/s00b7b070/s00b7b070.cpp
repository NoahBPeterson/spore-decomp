// flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast
// Slice s00b7b070 -- the giant Simulator ambience/obstacle manager that the neighbouring
// slices s00b794e0 / s00b7a4a0 also touch (vtables 0x14650cc +0, 0x14650e8 +4, 0x14650c8 +8,
// base vtable 0x13eb394; the cGonzagoSubsystem subobject sits at +4).  No dev-PDB name
// survives for these five functions, so members are reached by raw byte offset.
#include "types.h"
#include <math.h>

typedef unsigned int  uint32;
typedef unsigned char uint8;

// ---------------------------------------------------------------- globals
extern float  DAT_01485720;                                   // 1.0f
extern float  DAT_013ec480;                                   // 0.2f
extern float  DAT_013ec4b8;                                   // 1e-08f
extern float  DAT_013ef480;                                   // forced ambience value
extern uint8  DAT_01687ad0;                                   // force-ambience flag
extern float  DAT_01687ad4, DAT_01687ad8, DAT_01687adc;       // origin
extern char   DAT_0156b478[];                                 // cVarListSerializer name
extern char   DAT_013eb394[];                                 // base vtable
extern char   DAT_014650cc[], DAT_014650e8[], DAT_014650c8[]; // manager vtables

// ---------------------------------------------------------------- external callees
// Every external entry point is declared with its original address in the identifier and in a
// trailing comment; tools/difftest/resolve.py binds call relocations on either.
void  FUN_00f47380(void* p);                                          // 0x00f47380  operator delete
void* __cdecl FUN_00b3d350(void);                                     // 0x00b3d350  SP::PlanetModel
void* __cdecl FUN_00b3d4d0(void);                                     // 0x00b3d4d0  current game context
void* __cdecl FUN_0067dd10(void);                                     // 0x0067dd10  SP::App
void* __cdecl FUN_00720250(void* first, void* last, void* result);    // 0x00720250  eastl do_copy
void  __cdecl FUN_00571db0(int h, int a, int b, int c, int d);        // 0x00571db0  EA::Messaging::RemoveHandler

// external thiscall entry points (object pointer goes in ecx, hence members)
struct Ext {
    float* FUN_00b81630(float* out, const float* in);      // 0x00b81630  planet-space transform
    void   FUN_007c3d30(float* a, float* b, float* c, float* d);  // 0x007c3d30  cViewer::GetCameraLocationInfo
    void   FUN_00b7a4a0(float* a, float* b, float r, void* vec, int flag);   // 0x00b7a4a0
    char   FUN_00b72b60(void* a, float* b, float c, void* d, uint32 e, float* f, char* g);  // 0x00b72b60
    void*  FUN_00645ed0(void** out, const void* key);      // 0x00645ed0  hashtable::find
    float* FUN_00b76400(const void* key);                  // 0x00b76400  hashtable insert
    void   FUN_00b76e00(int a, float b);                   // 0x00b76e00
    void   FUN_00b7a710();                                 // 0x00b7a710
    void   FUN_00b77aa0();                                 // 0x00b77aa0
    void   FUN_00692f90(void* obj, const void* name, int hash);  // 0x00692f90  cVarListSerializer ctor
    char   FUN_00693e10(void* arg);                        // 0x00693e10  cVarListSerializer::Serialize
    void   FUN_00750310();                                 // 0x00750310
    void   FUN_00b73070(uint32 a, uint32 b);               // 0x00b73070
    void   FUN_005f3680(uint32 a, uint32 b);               // 0x005f3680  eastl DoDestroyValues
    void   FUN_00b75bf0(uint32 a, uint32 b);               // 0x00b75bf0
    void   FUN_00b75b80(uint32 a, uint32 b);               // 0x00b75b80
    void   FUN_00b759b0(uint32 a, uint32 b);               // 0x00b759b0
    void   FUN_00a24480(uint32 a, uint32 b);               // 0x00a24480
    void   FUN_00a1b6c0(uint32 a, uint32 b);               // 0x00a1b6c0  hashtable::DoFreeNodes
    void   FUN_00ae6970();                                 // 0x00ae6970  ~vector<AutoRefCount<cStarRecord>>
    void   FUN_00b5b9a0();                                 // 0x00b5b9a0  ~cGonzagoSubsystem
};

// virtual interfaces walked by the per-frame pass
struct VtApp {                       // SP::App
    virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4();
    virtual void p5(); virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9();
    virtual void q0(); virtual void q1(); virtual void q2(); virtual void q3(); virtual void q4();
    virtual void q5(); virtual void q6(); virtual void q7(); virtual void q8(); virtual void q9();
    virtual void* FUN_00000050();    // slot 20 (+0x50)
};
struct VtHost {                      // SP::App::something
    virtual void r0(); virtual void r1(); virtual void r2(); virtual void r3();
    virtual void r4(); virtual void r5(); virtual void r6();
    virtual void* FUN_0000001c();    // slot 7 (+0x1c)
};

// the 0x18-byte sample-point entry the per-frame pass walks (6 floats)
struct Vec18 { float v[6]; };

// The fixed vector the sample pass fills: begin/end, two allocator bookkeeping dwords, then the
// 0x100-element storage 0xb7a4a0 appends to.  The word just below `buf` is the storage-ownership
// slot the teardown checks (`begin[-1]`), so it must be modelled and cleared.
struct SampleVec {
    void**  begin;
    void**  end;
    void**  cap;
    void*   spare0;
    void*   spare1;
    void*   buf[0x100];
};

struct Mgr {
    void  Sample(float* camPos, float* entry);
    void  Update(int a, float b);
    char  SerializeIt(void* arg);
    void  Destroy();
    void  UpdatePooled(int a, int b);
};

// The inline-buffer release epilogue every container teardown in Destroy() repeats: hand the
// storage back to the container's own teardown, clear the end slot, then release the storage
// unless it is the container's own inline buffer (in which case push it on the free list).
#define RELEASE(C, FN) \
    do { \
        uint32* blk_; \
        ((Ext*)(C))->FN(*(uint32*)((char*)(C) + 4), *(uint32*)((char*)(C) + 8)); \
        blk_ = *(uint32**)((char*)(C) + 4); \
        *(uint32*)((char*)(C) + 0xc) = 0; \
        if (*(uint32*)((char*)(C) + 8) > 1 && blk_ != *(uint32**)((char*)(C) + 0x30)) { \
            if (blk_ < *(uint32**)((char*)(C) + 0x24) || *(uint32**)((char*)(C) + 0x28) <= blk_) { \
                FUN_00f47380(blk_); \
            } else { \
                *blk_ = *(uint32*)((char*)(C) + 0x1c); \
                *(uint32*)((char*)(C) + 0x1c) = (uint32)blk_; \
            } \
        } \
    } while (0)

// ======================================================================
// @ 0x00b7b070  ambience sample-point pass over one 0x18-byte candidate object
// ======================================================================
void Mgr::Sample(float* camPos, float* entry)
{
    char* self = (char*)this;
    float tmp[3], tgt[3], startP[3], camP[3], endP[3];
    float dx, dy, dz, scale, radius2, len, inv, f8;
    float value, curValue;
    float* p;
    void*  pm;
    uint32 flags, mask;
    char   forced, adjust;
    SampleVec v;

    v.spare0 = 0;   // allocator bookkeeping above the inline storage
    v.spare1 = 0;   // ... and the ownership word the teardown reads as begin[-1]
    pm = FUN_00b3d350();
    p = entry;
    if (pm != 0) {
        p = ((Ext*)pm)->FUN_00b81630(tmp, entry);
    }
    endP[0] = p[0];
    endP[1] = p[1];
    endP[2] = p[2];
    scale   = entry[3];
    mask    = *(uint32*)((char*)entry + 0x14);
    dx = endP[0] - camPos[0];
    dy = endP[1] - camPos[1];
    dz = endP[2] - camPos[2];
    flags = ((uint8*)entry)[0x10];
    startP[0] = dx;
    startP[1] = dy;
    startP[2] = dz;
    p = camPos;
    if (pm != 0) {
        p = ((Ext*)pm)->FUN_00b81630(camP, camPos);
    }
    tgt[0] = p[0];
    tgt[1] = p[1];
    tgt[2] = p[2];
    {
        float f9 = endP[0] - tgt[0];
        float f6 = endP[1] - tgt[1];
        float f7 = endP[2] - tgt[2];
        radius2 = *(float*)(self + 0x54a0) * *(float*)(self + 0x54a0);
        v.begin = v.buf;
        inv = 1.0f / sqrtf((f6 * f6 + (f7 * f7 + f9 * f9)) + DAT_013ec4b8);
        f8 = *(float*)(self + 0x5480);
        len = sqrtf((dy + DAT_013ec4b8) * (dy + DAT_013ec4b8) +
                    ((dx + DAT_013ec4b8) * (dx + DAT_013ec4b8) +
                     (dz + DAT_013ec4b8) * (dz + DAT_013ec4b8)));
        dx = endP[0];
        dy = endP[1];
        dz = endP[2];
        if (0.0f < f8) {
            dx = ((inv * f9) * scale) * f8 + endP[0];
            dz = ((f7 * inv) * scale) * f8 + endP[2];
            dy = ((f6 * inv) * scale) * f8 + endP[1];
        }
        f8 = f8 * scale + len;
        camP[0] = dx;
        camP[1] = dy;
        camP[2] = dz;
        v.end = v.begin;
        p = ((Ext*)pm)->FUN_00b81630(startP, endP);
        endP[0] = p[0];
        endP[1] = p[1];
        endP[2] = p[2];
        ((Ext*)this)->FUN_00b7a4a0(endP, camP, *(float*)(self + 0x5480) * scale, &v, 0);
        {
            void* ctx = FUN_00b3d4d0();
            forced = 0;
            if (*(int*)((char*)ctx + 0x2c) == 1 || *(int*)((char*)ctx + 0x2c) == 2) {
                ctx = FUN_00b3d4d0();
                forced = 1;
                if (*(char*)((char*)ctx + 0x2a) == 0) {
                    forced = 0;
                }
            }
        }
        {
            float** it = (float**)v.begin;
            while (it != (float**)v.end) {
                float* obj = *it;
                if ((mask & (1u << (*(uint32*)((char*)obj + 0x88) & 0x1f))) != 0) {
                    float cur = *obj;
                    value = 1.0f;
                    curValue = 0.0f;
                    adjust = 0;
                    if (((Ext*)this)->FUN_00b72b60(entry, startP, *(float*)(self + 0x5480) * scale,
                                                   obj, flags, &curValue, &adjust) != 0) {
                        if (forced == 0) {
                            float a, b;
                            if (adjust == 0) {
                                float ddx = tgt[0] - *(float*)((char*)obj + 0x38);
                                float ddy = tgt[1] - *(float*)((char*)obj + 0x3c);
                                float ddz = tgt[2] - *(float*)((char*)obj + 0x40);
                                if (((ddz * ddz + ddy * ddy) + ddx * ddx) <= radius2) {
                                    a = *(float*)(self + 0x549c) * *(float*)(self + 0x5484);
                                    b = 1.0f;
                                } else {
                                    a = *(float*)(self + 0x5484);
                                    b = curValue;
                                }
                            } else {
                                a = *(float*)(self + 0x5484);
                                b = curValue;
                            }
                            value = (a - 1.0f) * b + 1.0f;
                        } else {
                            value = 0.0f;
                        }
                        if (DAT_01687ad0 != 0) {
                            value = 0.99f;
                        }
                    }
                    if (*(float*)((char*)obj + 0x7c) != 0.0f && *(int*)((char*)obj + 0x78) != 0) {
                        void*  node = 0;
                        void*  key  = (void*)obj;
                        float* slot;
                        node = ((Ext*)(self + 0x49e0))->FUN_00645ed0(&node, &key);
                        if (node == *(void**)(*(int*)(self + 0x49e4) + *(int*)(self + 0x49e8) * 4)) {
                            slot = ((Ext*)(self + 0x49e0))->FUN_00b76400(&key);
                            *slot = value;
                        } else {
                            float* nv = &value;
                            float* ex = (float*)((char*)node + 4);
                            if (!(value < *ex)) {
                                nv = ex;
                            }
                            *ex = *nv;
                        }
                    }
                    (void)cur;
                }
                it = it + 1;
            }
        }
    }
    if (v.begin != 0 && *(int*)((char*)v.begin - 4) != 0) {
        FUN_00f47380(v.begin);
    }
}

// ======================================================================
// @ 0x00b7b590  per-frame driver: refresh the camera sample points
// ======================================================================
void Mgr::Update(int a, float b)
{
    char* self = (char*)this;
    if (*(int*)(self + 0x4908) != *(int*)(self + 0x490c)) {
        void* app  = FUN_0067dd10();
        void* host = ((VtApp*)app)->FUN_00000050();
        void* view = ((VtHost*)host)->FUN_0000001c();
        if (view != 0) {
            float cam[3] = { DAT_01687ad4, DAT_01687ad8, DAT_01687adc };
            float v1[3]  = { DAT_01687ad4, DAT_01687ad8, DAT_01687adc };
            float v2[3]  = { DAT_01687ad4, DAT_01687ad8, DAT_01687adc };
            float v3[3]  = { DAT_01687ad4, DAT_01687ad8, DAT_01687adc };
            float* p;
            float* e;
            ((Ext*)view)->FUN_007c3d30(cam, v1, v2, v3);
            p = *(float**)(self + 0x4908);
            e = *(float**)(self + 0x490c);
            if (p != e) {
                do {
                    if (((p[0] != DAT_01687ad4) || (p[1] != DAT_01687ad8) || (p[2] != DAT_01687adc))
                        && (p[3] != 0.0f)) {
                        ((Mgr*)this)->Sample(cam, p);
                    }
                    p += 6;
                } while (p != *(float**)(self + 0x490c));
            }
            ((Ext*)self)->FUN_00b76e00(a, b);
        }
        {
            Vec18* begin = (Vec18*)*(uint32*)(self + 0x4908);
            Vec18* end   = (Vec18*)*(uint32*)(self + 0x490c);
            FUN_00720250(end, end, begin);
            *(Vec18**)(self + 0x490c) += -(end - begin);
        }
    }
}

// ======================================================================
// @ 0x00b7b710  cVarListSerializer bridge (the serializer's `this` is manager - 4)
// ======================================================================
struct Serializer {
    char body[0xa14];
};

// @ 0x00b7b710
char Mgr::SerializeIt(void* arg)
{
    char* mgr = (char*)this - 4;
    Serializer ser;
    char  r;
    ((Ext*)&ser)->FUN_00692f90(mgr, DAT_0156b478, 0x1a80d26);
    r = ((Ext*)&ser)->FUN_00693e10(arg);
    if ((*(uint8*)((char*)this + 0x1c) & 4) != 0) {
        ((Ext*)mgr)->FUN_00b7a710();
    } else {
        ((Ext*)mgr)->FUN_00b77aa0();
    }
    return r;
}

// ======================================================================
// @ 0x00b7b780  manager destructor
// ======================================================================
void Mgr::Destroy()
{
    char* self = (char*)this;
    uint32 v;
    uint32 bv;

    v = *(uint32*)(self + 0x55a4);
    *(void**)self        = (void*)DAT_014650cc;
    *(void**)(self + 4)  = (void*)DAT_014650e8;
    *(void**)(self + 8)  = (void*)DAT_014650c8;
    if (v != 0) {
        ((Ext*)v)->FUN_00750310();
        FUN_00f47380((void*)v);
    }
    RELEASE(self + 0x56c0, FUN_00b73070);

    ((Ext*)(self + 0x55a8))->FUN_005f3680(*(uint32*)(self + 0x55a8), *(uint32*)(self + 0x55ac));
    bv = *(uint32*)(self + 0x55a8);
    if (bv != 0 && *(int*)(bv - 4) != 0) {
        FUN_00f47380((void*)bv);
    }
    ((Ext*)(self + 0x5508))->FUN_005f3680(*(uint32*)(self + 0x5508), *(uint32*)(self + 0x550c));
    bv = *(uint32*)(self + 0x5508);
    if (bv != 0 && *(int*)(bv - 4) != 0) {
        FUN_00f47380((void*)bv);
    }
    RELEASE(self + 0x54e8, FUN_00b75bf0);
    RELEASE(self + 0x54c8, FUN_00b75bf0);
    RELEASE(self + 0x54a8, FUN_00b75b80);
    RELEASE(self + 0x4f30, FUN_00a24480);
    RELEASE(self + 0x49e0, FUN_00a1b6c0);

    bv = *(uint32*)(self + 0x4908);
    if (bv != 0 && *(int*)(bv - 4) != 0) {
        FUN_00f47380((void*)bv);
    }
    ((Ext*)(self + 0x40f0))->FUN_00ae6970();
    RELEASE(self + 0x2094, FUN_00b759b0);
    RELEASE(self + 0x38, FUN_00b759b0);

    v = *(uint32*)(self + 0x24);
    if (v != 0) {
        *(uint32*)(self + 0x24) = 0;
        FUN_00571db0(v, *(int*)(self + 0x28), *(int*)(self + 0x2c), *(int*)(self + 0x30),
                     *(int*)(self + 0x34));
    }
    ((Ext*)(self + 4))->FUN_00b5b9a0();
    *(void**)self = (void*)DAT_013eb394;
}

// ======================================================================
// @ 0x00b7ba50  pooled-object update (INCOMPLETE -- see partial.txt)
// ======================================================================
void Mgr::UpdatePooled(int a, int b)
{
    (void)this;
    (void)a;
    (void)b;
}
