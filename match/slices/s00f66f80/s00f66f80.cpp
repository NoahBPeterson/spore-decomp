// Slice s00f66f80 -- 19 functions of the Terrain/TerrainDraw + terrain temp-extract module.
//   00f66f80  lock a vertex buffer + build an index buffer (thiscall, ret 0x18)
//   00f67070  unlock / dispatch a terrain draw batch (thiscall, ret 8)
//   00f67290  advance a batch's cursor counters
//   00f672b0  destroy a batch (dtor + virtual free)
//   00f672f0  allocate a TerrainDraw object (0x34, "Terrain/TerrainDraw")
//   00f67360  build the TerrainTempExtract0/1..2/3 render targets
//   00f674c0  release those render targets
//   00f67540/7560  set/clear an explicit depth value at +0x158/+0x15c
//   00f67580  write a face's LOD byte
//   00f675b0  compute a UV rect from a terrain-extract struct
//   00f676f0  LOD selection from a range rect
//   00f67770  choose the terrain shader/pass id
//   00f67810  draw one terrain face through a viewer raster
//   00f678d0  fetch the current depth value
//   00f67900/79b0  merge a rect into a per-slot bounding rect
//   00f67aa0  project a direction into the terrain sprite atlas
//   00f67da0  clear the six terrain sprite sub-rasters
// Module flags: /O2 /MD /Gy /EHsc /TP.
#include "types.h"
#include <math.h>

// ---- allocation / service ---------------------------------------------------
void* __cdecl EAAllocate(unsigned int size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
void  __cdecl operator_delete(void* p);                                                     // 0x00f47380
void* __cdecl TerrainManager();                                                             // 0x0067dda0

// RenderWare graphics entry points used by this module.
void* __cdecl RWVertexBufferD3D9Lock(void* self, unsigned pool, unsigned offset, unsigned size);  // 0x011f3620
void* __cdecl RWVertexBufferUnlock(void* self);                                                   // 0x011f36a0
void  __cdecl RWCompiledStateDispatch(void* cs);                                                  // 0x011ee580
void  __cdecl RWGlobalStateD3D9Sync();                                                            // 0x011f21a0
int   __cdecl RWVertexDescriptorAreEqual(void* a, void* b);                                       // 0x011f2e70
void  __cdecl FUN_011f2bc0(void* vd);                                                             // 0x011f2bc0
void  __cdecl RWFillSpriteTexture(void* dst, unsigned a, int b);                                  // 0x011f0440

// The terrain draw-batch object (0x34 bytes).  All offsets are raw because the layout is
// only partly known; a private helper macro keeps it readable.
struct TerrainDraw {
    void**  mpVtbl;      // +0x00
    void*   mpVb;        // +0x04
    void*   mpIb;        // +0x08
    void*   mpIb2;       // +0x0c
    void*   mpShader;    // +0x10
    int32_t mStart0;     // +0x14
    int32_t mCount0;     // +0x18
    int32_t mStart1;     // +0x1c
    int32_t mCount1;     // +0x20
    int32_t mBase0;      // +0x24
    int32_t mBase1;      // +0x28
    void*   mpParam;     // +0x2c
    int32_t mLockState;  // +0x30

    char BuildIndexed(unsigned* a, void* b, int vertCount, int c, int* d, int indexCount);  // 0x00f66f80
    int  Draw(void* compiledState, void* out);                                              // 0x00f67070
    void Advance();                                                                         // 0x00f67290
    void Init(void* a, void* b, void* c);                                                   // 0x00f66d20
    void Deinit();                                                                          // 0x00f66e70
};
void FUN_00f66d20(void* a, void* b, void* c);   // 0x00f66d20
void FUN_00f66e70(void* self);                  // 0x00f66e70

// @ 0x00f66f80
char TerrainDraw::BuildIndexed(unsigned* pa, void* pb, int vertCount, int pc, int* pd, int indexCount)
{
    int base = mCount0;
    unsigned pool = 10;
    if (mStart0 - base < vertCount) {
        pool = 6;
        base = 0;
    }
    *pa = 0;
    *pd = 0;

    unsigned char stride;
    {
        unsigned* vd = (unsigned*)mpVb;
        int n = vertCount;
        if (vertCount == 0)
            n = (int)vd[3];
        stride = *(unsigned char*)(*vd + 0xf);
        void* p = RWVertexBufferD3D9Lock(mpVb, pool, (vd[2] + base) * stride, stride * n);
        if (!p)
            return 0;
    }

    int vbase = mCount1;
    unsigned pool2 = 0x1000;
    if (mStart1 - vbase < indexCount) {
        pool2 = 0;
        vbase = 0;
    }
    int* ib = *(int**)mpIb2;
    int r = ((int(__thiscall*)(void*, int, int, void*, int*))ib[0x2c / 4])(ib, (*((int**)mpIb2))[1] * 2 + vbase * 2, indexCount, pa, pd); // LockIndex
    if (r < 0)
        return 0;

    mpParam = pb;
    mCount0 = pool2;
    mStart1 = base;
    mLockState = 1;
    *pd = (int)pa;
    mBase1 = vbase;
    mBase0 = indexCount;
    return 1;
}

// @ 0x00f67070
int TerrainDraw::Draw(void* compiledState, void* out)
{
    if (mLockState == 1) {
        RWVertexBufferUnlock(mpVb);
        if (mpIb) {
            void* o = *(void**)mpIb;
            ((void(__thiscall*)(void*))((void**)o)[0x30 / 4])(o);
        }
    }
    mLockState = 2;
    RWCompiledStateDispatch(compiledState);
    RWGlobalStateD3D9Sync();

    void** dev = *(void***)0x016f89d0;
    void* vd = mpShader;
    if (*(void**)0x016f65a0 == 0 || !RWVertexDescriptorAreEqual(*(void**)0x016f65a0, vd))
        *(unsigned*)0x016f9110 |= 0x100000;
    *(void**)0x016f65a0 = vd;
    FUN_011f2bc0(vd);

    ((void(__thiscall*)(void*, void*))((void**)(*(void**)0x016f6568))[0x14 / 4])(*(void**)0x016f6568, mpShader);
    *(unsigned*)0x016f9110 = 0;

    {
        unsigned* vb = (unsigned*)mpVb;
        int iVar5 = vb[1];
        unsigned stride = *(unsigned char*)(*vb + 0xf);
        if (*(int*)0x016f9138 != iVar5 || *(int*)0x016f913c != 0 || *(unsigned*)0x016f9140 != stride) {
            ((void(__thiscall*)(void*, int, int, int, unsigned))((void**)*dev)[0x190 / 4])(dev, 0, iVar5, 0, stride);
            *(int*)0x016f9138 = iVar5;
            *(int*)0x016f913c = 0;
            *(unsigned*)0x016f9140 = stride;
        }
    }
    {
        int i = 1;
        int* p = (int*)0x016f9144;
        do {
            if (*p != 0) {
                ((void(__thiscall*)(void*, int, int, int, int))((void**)*dev)[0x190 / 4])(dev, i, 0, 0, 0);
                p[0] = 0;
                p[1] = 0;
                p[2] = 0;
            }
            p += 3;
            ++i;
        } while ((int)p < 0x16f9168);
    }

    int* ib = (int*)mpIb2;
    if (ib == 0 && mpIb != 0) {
        if (mpIb != (void*)1)
            ib = 0;
        else
            ib = *(int**)0x016c9698;
    } else if (ib == 0) {
        ib = *(int**)0x016c969c;
    }
    {
        int obj = *ib;
        if (*(int*)0x016f8afc != obj) {
            ((void(__thiscall*)(void*, int))((void**)*dev)[0x1a0 / 4])(dev, obj);
            *(int*)0x016f8afc = obj;
        }
    }

    if (mpParam == (void*)0) {
        int n = mBase0;
        if (n == 0)
            n = mBase1;
        n -= 2;
        int v = mCount1 + ib[1];
        int r = ((int(__thiscall*)(void*, int, int, int, int, int, int))((void**)*dev)[0x148 / 4])(
            dev, 5, mStart1, 0, mBase1, v, n);
        if (r < 0) {
            ((void(__thiscall*)(void*))((void**)*mpVtbl)[0x10 / 4])(this);
            return 0;
        }
    } else if (mpParam == (void*)1) {
        int n = mBase0;
        if (n == 0)
            n = mBase1;
        n /= 3;
        int v = mCount1 + ib[1];
        int r = ((int(__thiscall*)(void*, int, int, int, int, int, int))((void**)*dev)[0x148 / 4])(
            dev, 4, mStart1, 0, mBase1, v, n);
        if (r < 0) {
            ((void(__thiscall*)(void*))((void**)*mpVtbl)[0x10 / 4])(this);
            return 0;
        }
    }

    if (out) {
        *((int*)out + 8) += mBase1;
        if (mBase0 != 0) {
            *((int*)out + 9) += mBase0;
            *((int*)out + 10) += 1;
            return 1;
        }
        *((int*)out + 9) += mBase1;
        *((int*)out + 10) += 1;
    }
    return 1;
}

// @ 0x00f67290
void TerrainDraw::Advance()
{
    char* p = (char*)this;
    *(int*)(p + 0x18) += *(int*)(p + 0x24);
    *(int*)(p + 0x20) += *(int*)(p + 0x28);
    *(int*)(p + 0x30) = 0;
}

// @ 0x00f672b0
void TerrainDrawDestroy(void* self)
{
    ((TerrainDraw*)self)->Deinit();
    if (self) {
        void** vt = *(void***)self;
        ((void(__thiscall*)(void*, int))vt[0])(self, 1);
    }
}

// @ 0x00f672f0
void* __cdecl AllocTerrainDraw(void* a, void* b, void* c)
{
    TerrainDraw* p = (TerrainDraw*)EAAllocate(0x34, "Terrain/TerrainDraw", 0, 0, 0, 0);
    TerrainDraw* r = 0;
    if (p) {
        p->mpVb = 0;
        p->mpIb = 0;
        p->mpIb2 = 0;
        p->mpShader = 0;
        p->mStart0 = 0;
        p->mCount0 = 0;
        p->mStart1 = 0;
        p->mCount1 = 0;
        p->mBase0 = 0;
        p->mBase1 = 0;
        p->mLockState = 0;
        p->mpVtbl = (void**)0x0148f598;
        p->mpParam = (void*)1;
        r = p;
    }
    ((TerrainDraw*)r)->Init(a, b, c);
    return r;
}

// ---- render targets for the terrain temp extraction -------------------------
void* __cdecl FUN_0067dda0_svc();  // same service singleton as TerrainManager

// The service's texture/resource factory vtable (offset 0x10 Create, 0x18 Make, 0x48 Name).
struct TexFactory {
    void** mpVtbl;
};

// A terrain temp-extract object (0x20 bytes + two extra slots).
struct TempExtract {
    void*   hA_handle;   // +0x00
    int32_t hA_id;       // +0x04
    void*   hB_handle;   // +0x08
    int32_t hB_id;       // +0x0c
    int32_t hA_tex;      // +0x10
    int32_t hB_tex;      // +0x14
    void*   buf0;        // +0x18
    void*   buf1;        // +0x1c

    char Build(int size);   // 0x00f67360
    void Destroy();         // 0x00f674c0
};

// @ 0x00f67360
// @ 0x00f67360
char TempExtract::Build(int size)
{
    unsigned texA, texB, nameA, nameB;
    if (size == 0x20) {
        texA = 0x860dfc11;
        nameA = 0x0148f660;   // "TerrainTempExtract0"
        texB = 0x860dfc10;
        nameB = 0x0148f64c;   // "TerrainTempExtract1"
    } else {
        texA = 0x860dfc13;
        nameA = 0x0148f688;   // "TerrainTempExtract2"
        texB = 0x860dfc12;
        nameB = 0x0148f674;   // "TerrainTempExtract3"
    }

    TexFactory* svc = (TexFactory*)TerrainManager();
    void** vt = svc->mpVtbl;

    unsigned out[2];
    ((void*(__thiscall*)(void*, unsigned*, int, int, int, int, int, int))vt[0x10 / 4])(
        svc, out, size, size, 0x15, 0, (int)texA, 0);
    hA_handle = (void*)out[0];
    hA_id = (int)out[1];
    ((void(__thiscall*)(void*, unsigned, unsigned, unsigned))vt[0x48 / 4])(svc, out[0], out[1], nameA);
    if (hA_id != -1)
        hA_tex = (int)((void*(__thiscall*)(void*, unsigned, int))vt[0x18 / 4])(svc, out[0], out[1]);

    buf0 = EAAllocate(size * size * 4, "Terrain/TerrainEditor/TempExtractBuffer0", 0, 0, 0, 0);

    ((void*(__thiscall*)(void*, unsigned*, int, int, int, int, int, int))vt[0x10 / 4])(
        svc, out, size, size, 0x15, 0, (int)texB, 0);
    hB_handle = (void*)out[0];
    hB_id = (int)out[1];
    ((void(__thiscall*)(void*, unsigned, unsigned, unsigned))vt[0x48 / 4])(svc, out[0], out[1], nameB);
    if (hB_id != -1)
        hB_tex = (int)((void*(__thiscall*)(void*, unsigned, int))vt[0x18 / 4])(svc, out[0], out[1]);

    buf1 = EAAllocate(size * size * 4, "Terrain/TerrainEditor/TempExtractBuffer1", 0, 0, 0, 0);
    return 1;
}

// @ 0x00f674c0
void TempExtract::Destroy()
{
    TexFactory* svc = (TexFactory*)TerrainManager();
    void** vt = svc->mpVtbl;
    if (hB_tex != 0) {
        ((void(__thiscall*)(void*, void*, int))vt[0x14 / 4])(svc, hB_handle, hB_id);
        hB_tex = 0;
        hB_handle = (void*)-1;
    }
    if (buf1) {
        operator_delete(buf1);
        buf1 = 0;
    }
    if (hA_tex != 0) {
        ((void(__thiscall*)(void*, void*, int))vt[0x14 / 4])(svc, hA_handle, hA_id);
        hA_tex = 0;
        hA_handle = (void*)-1;
    }
    if (buf0) {
        operator_delete(buf0);
        buf0 = 0;
    }
}

// ---- the terrain-face / sprite-atlas object ---------------------------------
extern float g_one_1485720;              // 0x01485720 = 1.0f
extern float g_half_1471064;             // 0x01471064 = 0.5f
extern float g_c_13eb1bc;                // 0x013eb1bc = -1.0f
extern float g_c_1470f1c;                // 0x01470f1c = 2.0f
extern float g_c_148f69c;                // 0x0148f69c = 1.0039062f (0x3f808081)
extern float g_c_1488874;                // 0x01488874 = 0.1f
extern float g_c_13fff7c;                // 0x013fff7c = 0.35f
extern float g_c_1485544;                // 0x01485544 = 0.75f
extern float g_c_1485378;                // 0x01485378 = 0.0f (compare base)
extern float g_c_148f6a0;                // 0x0148f6a0 = 1.5259022e-05f
extern float g_c_148f6a4;                // 0x0148f6a4
extern float g_c_148f6a8;                // 0x0148f6a8

void* __cdecl ShaderGet(unsigned a, unsigned b, unsigned c);        // 0x00777ae0
void* __cdecl TerrainEditorGet();                                   // 0x00f48a60
void  __cdecl RasterStateConstruct(void* dst, void* a, void* b, void* c);  // 0x00fc2c10
void  __cdecl RasterStateClear(void* self);                         // 0x00fc2830
int   __cdecl ViewerSetRaster(void* self, void* p, bool b);         // 0x007c4be0
char  __cdecl ViewerUpdate(void* self);                             // 0x007c4fd0
void  __cdecl ViewerEndDraw(void* self);                            // 0x007c3c10
void  __cdecl ViewerSetClearColor(void* self, const void* c);       // 0x007c3c20
void  __cdecl ViewerClear(void* self, unsigned flags);              // 0x007c3c50
struct DepthCtx { float Read(); };                                  // 0x00fd9400
void  __cdecl FUN_00fa3b30(void* self);                             // 0x00fa3b30
int*  __cdecl SP_CoordToIndex(int* out, int n, float* v);           // 0x00684bf0

// The terrain-face object (only the offsets this slice touches are named).
// The terrain-face object: only accessed through raw offsets, so it is opaque here.
struct Vec4 { float x, y, z, w; };

struct TerrainFace {
    char raw[0x300];
    void SetDepth(float d);        // 0x00f67540
    void ClearDepth();             // 0x00f67560
    void SetLodByte(int slot, unsigned char v);  // 0x00f67580
    void Draw(int slot, void* a3); // 0x00f67810
    float GetDepth();              // 0x00f678d0
    void MergeRectA(int slot, float* r);  // 0x00f67900
    void MergeRectB(int slot, float* r);  // 0x00f679b0
    float ProjectDir(float dx, float dy, float dz);  // 0x00f67aa0
    void ClearSprites();           // 0x00f67da0
};

// Simpler offsets used by the small methods.
struct FaceBuf {
    char pad000[0x74];
    void* mpRaster7c;        // +0x74
};

// @ 0x00f67540
void TerrainFace::SetDepth(float d)
{
    char* p = (char*)this;
    p[0x158] = 1;
    *(float*)(p + 0x15c) = d;
}

// @ 0x00f67560
void TerrainFace::ClearDepth()
{
    char* p = (char*)this;
    p[0x158] = 0;
    *(float*)(p + 0x15c) = 0.0f;
}

// @ 0x00f67580
void TerrainFace::SetLodByte(int slot, unsigned char v)
{
    char* p = (char*)this;
    if (slot < 0) {
        p[0x78] = (char)v;
        p[0x79] = (char)v;
        p[0x7a] = (char)v;
        p[0x7b] = (char)v;
        p[0x7c] = (char)v;
        p[0x7d] = (char)v;
        return;
    }
    p[0x78 + slot] = (char)v;
}

// @ 0x00f675b0
void FUN_00f675b0(char* self, char* info, float* out)
{
    int kind = *(int*)(info + 0xc);
    if (kind == 5 || kind == 6) {
        out[0] = *(float*)(info + 0x1c);
        out[1] = *(float*)(info + 0x10);
        float a = *(float*)(info + 0x14);
        if (a == *(float*)(info + 0x18)) {
            if (*(int*)(info + 0xc) == 5) {
                out[2] = a;
                out[3] = a + g_one_1485720;
            } else {
                out[3] = a;
                out[2] = a - g_one_1485720;
            }
            goto tail;
        }
        out[2] = a;
        out[3] = *(float*)(info + 0x18);
    } else {
        out[0] = *(float*)(info + 0x1c);
        if (kind == 3) {
            out[1] = 0.0f;
            out[2] = 0.0f;
            out[3] = *(float*)(info + 0x10);
        } else {
            out[1] = g_one_1485720;
            if (kind != 4) {
                out[2] = g_one_1485720;
                out[3] = 0.0f;
                if (*(int*)(info + 0xc) == 2)
                    out[1] = g_c_13eb1bc;
                else if (*(int*)(info + 0xc) == 1) {
                    out[2] = g_c_1470f1c;
                    out[3] = g_c_148f69c;
                }
                goto tail;
            }
            out[2] = *(float*)(info + 0x18);
            out[3] = *(float*)(info + 0x14);
        }
    }
tail:
    if (*self != 0) {
        int k = *(int*)(self + 0x2c);
        if (k == 6) {
            out[0] = g_one_1485720;
            out[2] = g_half_1471064;
            out[1] = g_one_1485720;
            return;
        }
        out[2] = g_one_1485720;
        if (k == 1) {
            out[0] = g_one_1485720;
            out[1] = g_one_1485720;
            return;
        }
        out[0] = 0.0f;
        out[1] = g_one_1485720;
    }
}

// @ 0x00f676f0
int __cdecl SelectLod(float* param_1)
{
    float a = param_1[2] - param_1[0];
    float b = param_1[3] - param_1[1];
    float* p = (a < b) ? &b : &a;
    float fVar1 = *p;
    if (fVar1 < g_c_1488874)
        return 0;
    if (fVar1 < g_c_13fff7c)
        return 1;
    if (fVar1 < g_c_1485544)
        return 2;
    return 3;
}

// @ 0x00f67770
int __stdcall FUN_00f67770(char* self, char* info)
{
    if (info[6] != 0) {
        if (*(int*)(info + 0xc) != 3 && *(int*)(info + 0xc) != 4)
            return 0x0e;
        return 0x0f;
    }
    if (*self != 0)
        return (self[1] != 0) + 5;
    int kind = *(int*)(info + 0xc);
    if (kind == 5)
        return kind + 0xd;
    if (kind == 6)
        return kind + 0xd;
    if (kind == 3 && info[4])
        return (info[5] != 0) + 3;
    if (kind == 3 || kind == 4)
        return 9;
    if (info[4] != 0)
        return (info[5] != 0) + 1;
    return 8;
}
// @ 0x00f67810
void TerrainFace::Draw(int slot, void* a3)
{
    char* p = (char*)this;
    unsigned raster[4];       // rw::graphics::RasterState on the stack (0x10 bytes)
    ShaderGet(0x201, 0, 0);
    void* e = TerrainEditorGet();
    void* u = *(void**)(*(char**)((char*)e + 0x28) + 4);
    RasterStateConstruct(raster, u, 0, *(void**)(p + 0x20 + slot * 4));
    ViewerSetRaster(*(void**)(p + 0x1c), p + 0x6c, true);
    char ok = ViewerUpdate(*(void**)(p + 0x1c));
    if (ok) {
        void* o = *(void**)(p + 0x204);
        void** vt = *(void***)o;
        ((void(__thiscall*)(void*, void*, void*))vt[0xc / 4])(o, u, a3);
        ViewerEndDraw(*(void**)(p + 0x1c));
    }
    RasterStateClear(raster);
}

// @ 0x00f678d0
float TerrainFace::GetDepth()
{
    char* p = (char*)this;
    if (p[0x158] != 0)
        return *(float*)(p + 0x15c);
    void* o = *(void**)(p + 0x74);
    if (!o)
        return g_half_1471064;
    void** vt = *(void***)o;
    void* r = ((void*(__thiscall*)(void*))vt[0x10 / 4])(o);
    return ((DepthCtx*)r)->Read();
}

// @ 0x00f67900
void TerrainFace::MergeRectA(int slot, float* r)
{
    Vec4* v = (Vec4*)((char*)this + ((slot + 8) << 4));
    if (v->x == v->z || v->y == v->w) {
        *v = *(Vec4*)r;
        return;
    }
    if (r[0] < v->x) v->x = r[0];
    if (r[1] < v->y) v->y = r[1];
    if (r[2] > v->z) v->z = r[2];
    if (r[3] > v->w) v->w = r[3];
}

// @ 0x00f679b0
void TerrainFace::MergeRectB(int slot, float* r)
{
    Vec4* v = (Vec4*)((char*)this + ((slot + 0xe) << 4));
    if (v->x == v->z || v->y == v->w) {
        *v = *(Vec4*)r;
        return;
    }
    if (r[0] < v->x) v->x = r[0];
    if (r[1] < v->y) v->y = r[1];
    if (r[2] > v->z) v->z = r[2];
    if (r[3] > v->w) v->w = r[3];
}

// @ 0x00f67aa0
float TerrainFace::ProjectDir(float dx, float dy, float dz)
{
    char* p = (char*)this;
    if (*(void**)(p + 0x20) == 0)
        return 0.0f;

    float invLen = 1.0f / sqrtf(dx * dx + dy * dy + dz * dz);
    float nx = dx * invLen;
    float ny = dy * invLen;
    float nz = dz * invLen;
    float ax = fabsf(nx);
    float ay = fabsf(ny);
    float az = fabsf(nz);

    float u, v;
    int face;
    if (az < ax || az < ay) {
        if (ay < ax) {
            u = (ny / nx + 1.0f) * 0.5f;
            v = (nz / ax + 1.0f) * 0.5f;
            face = (nx < 0.0f) ? 3 : 2;
        } else {
            u = (nz / ny + 1.0f) * 0.5f;
            v = (nx / ay + 1.0f) * 0.5f;
            face = (ny < 0.0f) ? 5 : 4;
        }
    } else {
        u = (nx / nz + 1.0f) * 0.5f;
        v = (ny / az + 1.0f) * 0.5f;
        face = (nz < 0.0f) ? 1 : 0;
    }

    int idx[2];
    SP_CoordToIndex(idx, 0x200, &u);

    unsigned* sprite = *(unsigned**)(p + 0x20 + face * 4);
    unsigned char c = *(unsigned char*)(sprite + 0x10 / 4);

    unsigned rect[8];
    rect[0] = 0x20;
    rect[1] = 0x20;
    rect[2] = *(unsigned*)&u;
    rect[3] = *(unsigned*)&v;
    rect[4] = (unsigned)(int)u + 1;
    rect[5] = (unsigned)(int)v + 1;
    rect[6] = 0;
    rect[7] = 0;
    (void)c;

    int slot = *(int*)(p + 0x1c4);
    void* tex = *(void**)(p + 0x1b4 + slot * 4);
    *(int*)(p + 0x1c4) = 1 - slot;

    void* a = *(void**)tex;
    void* b = *(void**)(sprite + 8);
    unsigned h1 = 0, h2 = 0;
    ((void(__thiscall*)(void*, int, unsigned*))((void**)*(void**)((char*)a + 8))[0x48 / 4])(*(void**)((char*)a + 8), 0, &h1);
    ((void(__thiscall*)(void*, int, unsigned*))((void**)*(void**)((char*)b + 8))[0x48 / 4])(*(void**)((char*)b + 8), 0, &h2);

    if (h1 != 0) {
        if (h2 != 0) {
            void* dev = *(void**)0x016f89d0;
            ((void(__thiscall*)(void*, unsigned, unsigned*, void*, unsigned*, int))((void**)*(void**)dev)[0x88 / 4])(
                dev, h2, rect, 0, &rect[4], 1);
            RWFillSpriteTexture(rect, h1 >> 3, 0);
        }
        ((void(__thiscall*)(void*, void*))((void**)*(void**)h1)[8 / 4])((void*)h1, (void*)h1);
    }
    if (h2 != 0)
        ((void(__thiscall*)(void*, void*))((void**)*(void**)h2)[8 / 4])((void*)h2, (void*)h2);

    return ((float)((rect[0] >> 8) & 0xffff) * g_c_148f6a0) * 2.0f - 1.0f;
}

// @ 0x00f67da0
void TerrainFace::ClearSprites()
{
    char* p = (char*)this;
    if (*(void**)(p + 0x20) == 0)
        return;
    if (*(void**)(p + 0x74) != 0)
        FUN_00fa3b30(*(void**)(p + 0x74));

    struct RGBA { float r, g, b, a; } col;
    col.r = g_c_148f6a8;
    col.g = g_c_148f6a4;
    col.b = 0.0f;
    col.a = 0.0f;

    int* raster = (int*)(p + 0x38);
    float* sprite = (float*)(p + 0x88);
    for (int i = 0; i < 6; ++i) {
        sprite[-2] = 0.0f;
        sprite[-1] = 0.0f;
        sprite[0] = g_one_1485720;
        sprite[1] = g_one_1485720;
        ViewerSetRaster(*(void**)(p + 0x1c), raster, true);
        if (ViewerUpdate(*(void**)(p + 0x1c))) {
            ViewerSetClearColor(*(void**)(p + 0x1c), &col);
            ViewerClear(*(void**)(p + 0x1c), 7);
            ViewerEndDraw(*(void**)(p + 0x1c));
        }
        sprite += 4;
        raster += 2;
    }
}
