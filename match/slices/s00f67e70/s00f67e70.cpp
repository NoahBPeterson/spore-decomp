// Slice s00f67e70 -- SPTerrain/SPTerrainEditor.obj  (terrain-editor render helpers + TessellateBrush)
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

struct Vec3 { float x, y, z; Vec3() {} Vec3(float a, float b, float c) : x(a), y(b), z(c) {} };
struct V4 { float x, y, z, w; V4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {} };

namespace SP {

// ---- cViewer (SPEngine/SPGraphicsViewer.obj) ------------------------------------------------
class cViewer { public:
    cViewer* FUN_007c3f70();                                  // 0x007c3f70
    bool     Init(bool flag);                                 // 0x007c4dd0
    void     SetA(float v);                                   // 0x007c4ba0
    void     SetB(float v);                                   // 0x007c4bc0
    void     ViewportRectArgs(int x, int y, int w, int h);    // 0x007c5310
    void     SetC(float a, float b);                          // 0x007c4b00
    void     SetRasterDirect(void* r);                        // 0x007c3cb0
    void     Clear(u32 flags);                                // 0x007c3cc0
    void     SetRaster(const void* r, bool flag);             // 0x007c4be0
    bool     Update();                                        // 0x007c4fd0
    void     Finish();                                        // 0x007c3c10
};

} // namespace SP

// ---- Raster ---------------------------------------------------------------------------------
struct Raster { u32 pad[3]; u16 width; u16 height; u8 depth; u8 pad2[3]; };
struct RasterDesc { u32 v0, v1; };

// ---- global object with a vtable method at slot 30 (+0x78) ----------------------------------
#define DUMMY_V(n) virtual void v##n();
struct GlobalObj {
    DUMMY_V(0)  DUMMY_V(1)  DUMMY_V(2)  DUMMY_V(3)  DUMMY_V(4)  DUMMY_V(5)
    DUMMY_V(6)  DUMMY_V(7)  DUMMY_V(8)  DUMMY_V(9)  DUMMY_V(10) DUMMY_V(11)
    DUMMY_V(12) DUMMY_V(13) DUMMY_V(14) DUMMY_V(15) DUMMY_V(16) DUMMY_V(17)
    DUMMY_V(18) DUMMY_V(19) DUMMY_V(20) DUMMY_V(21) DUMMY_V(22) DUMMY_V(23)
    DUMMY_V(24) DUMMY_V(25) DUMMY_V(26) DUMMY_V(27) DUMMY_V(28) DUMMY_V(29)
    virtual void Send(void* a, int b, void* c);               // +0x78 (slot 30)
};
GlobalObj* __cdecl FUN_0067dd50();                            // 0x0067dd50

struct IResolver {
    DUMMY_V(0)  DUMMY_V(1)  DUMMY_V(2)  DUMMY_V(3)  DUMMY_V(4)  DUMMY_V(5)
    DUMMY_V(6)  DUMMY_V(7)  DUMMY_V(8)  DUMMY_V(9)  DUMMY_V(10) DUMMY_V(11) DUMMY_V(12)
    virtual void Resolve(void* handle);                       // +0x34 (slot 13)
};
IResolver* __cdecl FUN_0067dd60();                            // 0x0067dd60
#undef DUMMY_V

// ---- shader table ---------------------------------------------------------------------------
struct ShaderIds { u32 pad; u32 id; };
struct ShaderTable {
    char       pad00[0x0c];
    ShaderIds* table[0x10];                                   // +0x0c (indexed by id)
    ShaderIds* s4c;                                           // +0x4c
};
ShaderTable* __cdecl GetShaderTable();                        // 0x00f48a60

// ---- batch interfaces -----------------------------------------------------------------------
struct IBatch {
    virtual void v0();
    virtual bool BigAlloc(void** out, int stride, int count, const int* desc, int verts, int one); // +0x04
    virtual bool Alloc(void** out, int stride, int count, int zero);                               // +0x08
    virtual bool Apply(u32 shader, void* arg);                                                     // +0x0c
    virtual void Flush();                                                                          // +0x10
};

struct Binding {
    u32 w[4];
    void Init(u32 shader, int index, u32 value);              // 0x00fc2c10
    void Done();                                              // 0x00fc2830
};

// ---- terrain brush face ---------------------------------------------------------------------
struct FaceVertex { float f0, y, z, f0c, f10, f14, f18; };   // 0x1c
struct FaceOrIdx { int count; int* data; };                  // the original keeps a raw union here
struct Face { int count; FaceVertex v[16]; };                // 0x1c4
struct FaceVec { Face* mpBegin; Face* mpEnd; };

// ---- externs --------------------------------------------------------------------------------
extern "C" void* __cdecl memset(void* dst, int val, unsigned int n);        // 0x011e073e
extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int n);
extern "C" void  __cdecl VecInsert(void* self, const void* data, int n);    // 0x011e0744
void* __cdecl EAAllocate(u32 size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
void __cdecl FUN_00777ae0(int slot, const void* data, int zero);            // 0x00777ae0
int  __stdcall FUN_00f67770(u32 a, int* b);                                 // 0x00f67770
char __stdcall FUN_00f6779a(int zone, float* out);                         // 0x00f6779a
inline int zip(u32 zone)
{
    float f[8];
    FUN_00f6779a((int)zone, f);
    f[7] = 0.0f;
    return *(int*)&f[0];
}

extern const float C_13f9428;   // 0x013f9428
extern const float C_13f6d90;   // 0x013f6d90   (= 100000.0f)
extern const float C_1473c70;   // 0x01473c70   (= 10.0f)
extern const float C_1485720;   // 0x01485720   (= 1.0f)
extern const float C_13eb1bc;   // 0x013eb1bc   (= -1.0f)
extern const float C_148f6cc;   // 0x0148f6cc   (= 0.001953125f)
extern const float C_1470f1c;   // 0x01470f1c   (= 2.0f)
extern const float C_1471064;   // 0x01471064   (= 0.5f)
extern const u8    T_148f608[]; // 0x0148f608 texture-axis table
extern void*       g_gate;      // 0x015b0e48 self-referencing sentinel

namespace SP {

u32 __cdecl ColorRGBToU32(const float* rgb);                  // 0x00458a40

// ---- the terrain editor object (layout taken from the slice's own accesses) ------------------
class cTerrainEditor { public:
    char       pad0[0x1c];
    cViewer*   mViewer;        // +0x1c
    Raster*    mRaster0;       // +0x20
    char       pad24[0x38 - 0x24];
    RasterDesc mRasterDesc[6]; // +0x38: six 8-byte raster descriptors
    u32        mHandle68;      // +0x68
    char       pad6c[0x80 - 0x6c];
    float      mDirty[24];     // +0x80
    char       padE0[0x164 - 0xe0];
    float      mF164;          // +0x164
    char       pad168[0x1d0 - 0x168];
    float      mRange[4];      // +0x1d0
    float      mMat[8];        // +0x1e0
    IBatch*    mBatch;         // +0x200
    IBatch*    mBatch2;        // +0x204

    void Refresh();                                                 // 0x00f67da0
    void B0(u32 a, u32 b, float* out);                              // 0x00f675b0
    void Init();                                                    // 0x00f67e70
    void Enable(int unused);                                        // 0x00f67ff0
    bool BuildBrush(FaceVec* faces, u32 flipIdx, u32 a3, u32 a4);   // 0x00f68070
    void UpdateRange(int* p);                                       // 0x00f684c0
    bool DrawUnitQuad(int idx, u32 a, u32 b);                       // 0x00f68650
    static void __stdcall TessellateBrush(void* out, void* vec, const float* in, int count,
                                          int strips, int limit, int unused); // 0x00f687f0
    void DrawRaster(int idx, u32 a, int* handle, u32 b);            // 0x00f68c80
};

// @ 0x00f67e70
void cTerrainEditor::Init()
{
    if (mRaster0 == 0)
        return;

    cViewer* v = (cViewer*)EAAllocate(0x174, "Terrain/TerrainEditor/cViewer", 0, 0, 0, 0);
    mViewer = (v != 0) ? v->FUN_007c3f70() : 0;
    mViewer->Init(true);
    Raster* r = mRaster0;
    mViewer->SetA(C_13f9428);
    mViewer->SetB(C_13f6d90);
    mViewer->ViewportRectArgs(0, 0, r->width, r->height);
    mViewer->SetC(0.5f, 0.5f);
    mViewer->SetRasterDirect(r);
    mViewer->Clear(0);
    Refresh();

    const float zero = 0.0f;
    mDirty[0] = zero;  mDirty[1] = zero;  mDirty[2] = zero;  mDirty[3] = zero;
    mDirty[4] = zero;  mDirty[5] = zero;  mDirty[6] = zero;  mDirty[7] = zero;
    mDirty[8] = zero;  mDirty[9] = zero;  mDirty[10] = zero; mDirty[11] = zero;
    mDirty[12] = zero; mDirty[13] = zero; mDirty[14] = zero; mDirty[15] = zero;
    mDirty[16] = zero; mDirty[17] = zero; mDirty[18] = zero; mDirty[19] = zero;
    mDirty[20] = zero; mDirty[21] = zero; mDirty[22] = zero; mDirty[23] = zero;
}

struct MsgBlk { u32 a; u32 b; u8 c; u8 pad[3]; u32 d[8]; };   // 0x2c

// @ 0x00f67ff0
void cTerrainEditor::Enable(int unused)
{
    (void)unused;
    if (g_gate == (void*)&g_gate)
        return;
    mF164 = C_1473c70;
    void* self = (char*)this + 4;
    GlobalObj* o = FUN_0067dd50();
    MsgBlk blk;
    blk.a = 1;
    blk.b = 0;
    blk.c = 1;
    for (int i = 0; i < 8; ++i)
        blk.d[i] = 0;
    o->Send(self, 0, &blk);
}

// The original keeps the vertex-count / index-array pair in one stack slot (a union).
struct FaceOrIdxSentinel { int count; int* beg; };

// @ 0x00f68070
bool cTerrainEditor::BuildBrush(FaceVec* faces, u32 flipIdx, u32 a3, u32 a4)
{
    union { int* idx; int count; } nVertexIdx;
    nVertexIdx.idx = 0;
    int n0 = 0, n2 = 0, total = 0;
    int idxData = 0;
    int* unused26 = 0;
    const int n = (int)(((char*)faces->mpEnd - (char*)faces->mpBegin) / 0x1c4);
    int rest[2];
    rest[0] = 0;
    rest[1] = 0;
    if (n >= 2) {
        Face* f = faces->mpBegin;
        int iters = ((n - 2) >> 1) + 1;
        nVertexIdx.count = iters * 2;
        do {
            rest[0] += f->count;
            n0 += f->count * 3 - 6;
            rest[1] += f[1].count;
            n2 += f[1].count * 3 - 6;
            f += 2;
        } while (--iters);
    }
    const u32 nVi = (u32)nVertexIdx.count;
    if (nVi < (u32)n) {
        idxData = ((FaceOrIdx*)faces->mpBegin)[nVi].count;
        total = idxData * 3 - 6;
    }
    n0 += n2;
    n0 += total;
    void* out = 0;
    if (!mBatch2->BigAlloc(&out, 0x2c, rest[0] + rest[1] + idxData, (const int*)&nVertexIdx, n0, 1))
        return false;

    const float one = C_1485720;
    const float eps = C_148f6cc;
    const float two = C_1470f1c;
    const float half = C_1471064;
    const u8* te = &T_148f608[(flipIdx >> 1) * 4];
    float arr[3];
    arr[0] = (flipIdx & 1) ? C_13eb1bc : one;
    arr[2] = arr[0];
    arr[1] = 1.0f;
    float t0 = arr[te[0]];
    float t1 = arr[te[1]];
    float t2 = arr[te[2]];

    float tb[4];
    B0(a3, a4, tb);

    u32 written = 0;
    u32 fi = 0;
    for (; fi < (u32)(((char*)faces->mpEnd - (char*)faces->mpBegin) / 0x1c4); ++fi) {
        int vi = 0;
        if (faces->mpBegin[fi].count > 0) {
            char* vo = (char*)out + written * 0x2c;
            do {
                FaceVertex* fv = &faces->mpBegin[fi].v[vi];
                float px = fv->y * eps;
                float py = 1.0f - fv->z * eps;
                *(float*)(vo + 0x00) = px;
                *(float*)(vo + 0x04) = py;
                *(float*)(vo + 0x08) = 1.0f;
                *(float*)(vo + 0x0c) = 1.0f;
                arr[0] = *(float*)(vo + 0x00);
                arr[1] = 1.0f - *(float*)(vo + 0x04);
                float r1 = arr[te[1]];
                float r0 = arr[te[0]];
                *(float*)(vo + 0x24) = fv->f10;
                float r2 = arr[te[2]];
                *(float*)(vo + 0x28) = fv->f14;
                tb[0] = fv->f18;
                *(float*)(vo + 0x10) = tb[0];
                *(float*)(vo + 0x14) = tb[1];
                *(float*)(vo + 0x18) = tb[2];
                *(float*)(vo + 0x1c) = tb[3];
                float rgb[3];
                rgb[0] = ((r0 * two - one) * t0) * half + half;
                rgb[1] = ((r1 * two - one) * t1) * half + half;
                rgb[2] = ((r2 * two - one) * t2) * half + half;
                *(u32*)(vo + 0x20) = ColorRGBToU32(rgb);
                ++written;
                vo += 0x2c;
                arr[2] = 1.0f;
            } while (++vi < faces->mpBegin[fi].count);
        }
    }

    u16* pidx = (u16*)idxData;
    u32 cursor = 0;
    u32 base = 0;
    u32 fc = 0;
    for (; fc < (u32)(((char*)faces->mpEnd - (char*)faces->mpBegin) / 0x1c4); ++fc) {
        int k = 0;
        int n3 = faces->mpBegin[fc].count - 2;
        if (n3 > 0) {
            do {
                pidx[cursor] = (u16)base;
                pidx[cursor + 1] = (u16)(base + k + 1);
                pidx[cursor + 2] = (u16)(base + k + 2);
                ++k;
                cursor += 3;
            } while (k < n3);
        }
        base += faces->mpBegin[fc].count;
    }
    return true;
}

// @ 0x00f684c0
void cTerrainEditor::UpdateRange(int* p)
{
    float* f = mRange;
    f[0] = -2.0f;
    f[1] = -1.0f;
    f[2] = 1.0f;
    f[3] = 2.0f;

    int mode = p[0x30 / 4];
    if (mode == 1) {
        f[0] = -2.0f;
        f[1] = -1.0f;
        if (p[0x3c / 4] == 1)
            f[2] = *(float*)((char*)p + 0x40);
        else
            f[2] = *(float*)((char*)p + 0x34);
        f[3] = *(float*)((char*)p + 0x34);
    } else if (mode == 2) {
        f[0] = *(float*)((char*)p + 0x34);
        if (p[0x3c / 4] == 1)
            f[1] = *(float*)((char*)p + 0x40);
        else
            f[1] = *(float*)((char*)p + 0x34);
        f[2] = 1.0f;
        f[3] = 2.0f;
    } else if (mode == 3) {
        f[0] = *(float*)((char*)p + 0x34);
        f[1] = *(float*)((char*)p + 0x34);
        f[2] = *(float*)((char*)p + 0x38);
        f[3] = *(float*)((char*)p + 0x38);
        if (p[0x3c / 4] == 1) {
            f[0] = *(float*)((char*)p + 0x40);
            f[3] = *(float*)((char*)p + 0x44);
        }
    }

    f[2] = f[2] + 0.0078125f;
    f[3] = f[3] + 0.0078125f;

    float dx = f[1] - f[0];
    float dy = f[3] - f[2];
    float sx = dx > 0.0f ? 1.0f / dx : 0.0f;
    float sy = dy > 0.0f ? -1.0f / dy : 0.0f;

    f[4] = sx;
    f[5] = 0.0f;
    f[6] = sy;
    f[7] = 0.0f;
    f[8] = f[0] * sx;
    f[9] = -1.0f;
    f[10] = f[2] * sy - 1.0f;
    f[11] = 0.0f;

    FUN_00777ae0(0x24a, f, 0);
}

struct QuadVert { Vec3 v; float pad[3]; };                    // 0x18

// @ 0x00f68650
bool cTerrainEditor::DrawUnitQuad(int idx, u32 a, u32 b)
{
    u32 shader = GetShaderTable()->s4c->id;

    void* out = 0;
    if (!mBatch->Alloc(&out, 0x18, 4, 0))
        return false;

    memset(out, 0, 0x60);
    *(Vec3*)((char*)out + 0x00) = Vec3(0.0f, 0.0f, 0.0f);
    *(Vec3*)((char*)out + 0x18) = Vec3(1.0f, 0.0f, 0.0f);
    *(Vec3*)((char*)out + 0x30) = Vec3(0.0f, 1.0f, 0.0f);
    *(Vec3*)((char*)out + 0x48) = Vec3(1.0f, 1.0f, 0.0f);
    FUN_00777ae0(0x201, 0, 0);

    mViewer->SetRaster(&mRasterDesc[idx], true);
    if (!mViewer->Update())
        return true;

    Binding bind;
    bind.Init(shader, 0, a);
    if (!mBatch->Apply(shader, (void*)b)) {
        bind.Done();
        return false;
    }
    mBatch->Flush();
    mViewer->Finish();
    bind.Done();
    return true;
}

// @ 0x00f687f0
void __stdcall cTerrainEditor::TessellateBrush(void* out, void* vec, const float* in, int count,
                                     int strips, int limit, int unused)
{
    (void)unused;
    const float eps = 0.001953125f;

    int written = 0;
    if (count >= 4) {
        const float* src = in + 3;
        int iters = ((count - 4) >> 2) + 1;
        written = iters * 4;
        float* dst = (float*)out;
        do {
            dst[0x00] = src[-3] * eps;
            dst[0x01] = 1.0f - src[-2] * eps;
            dst[0x02] = 1.0f;
            dst[0x03] = 1.0f;
            dst[0x0b] = src[0] * eps;
            dst[0x0c] = 1.0f - src[1] * eps;
            dst[0x0d] = 1.0f;
            dst[0x0e] = 1.0f;
            dst[0x16] = src[3] * eps;
            dst[0x17] = 1.0f - src[4] * eps;
            dst[0x18] = 1.0f;
            dst[0x19] = 1.0f;
            dst[0x21] = src[6] * eps;
            dst[0x22] = 1.0f - src[7] * eps;
            dst[0x23] = 1.0f;
            dst[0x24] = 1.0f;
            dst += 0x2c;
            src += 12;
            --iters;
        } while (iters);
    }
    if (written < count) {
        const float* src = in + written * 3;
        int n = count - written;
        float* dst = (float*)out + written * 0xb;
        written += n;
        do {
            dst[0] = src[0] * eps;
            dst[1] = 1.0f - src[1] * eps;
            dst[2] = 1.0f;
            dst[3] = 1.0f;
            dst += 0xb;
            src += 3;
            --n;
        } while (n);
    }

    u16 idxbuf[2046];
    int cursor = 0;
    int k = 0;
    int n2 = count - 2;
    if (n2 > 0) {
        do {
            idxbuf[cursor] = 0;
            idxbuf[cursor + 1] = (u16)(k + 1);
            idxbuf[cursor + 2] = (u16)(k + 2);
            ++k;
            cursor += 3;
        } while (k < n2);
    }

    int start = 0;
    while (strips > 0) {
        int newStrips = (cursor - start) / 3;
        int top = cursor;
        if (written + newStrips * 3 <= limit && (u32)(cursor + newStrips * 12) < 0x801 && newStrips > 0) {
            float* dst = (float*)out + written * 0xb;
            u16* ip = idxbuf + start + 2;
            int cnt = newStrips;
            do {
                u16 i0 = ip[-2];
                u16 i1 = ip[-1];
                u16 i2 = ip[0];
                int m = written;
                const float* v0 = (const float*)((char*)out + i0 * 0x2c);
                const float* v1 = (const float*)((char*)out + i1 * 0x2c);
                const float* v2 = (const float*)((char*)out + i2 * 0x2c);
                dst[0x00] = (v1[0] + v0[0]) * 0.5f;
                dst[0x01] = (v1[1] + v0[1]) * 0.5f;
                dst[0x02] = (v1[2] + v0[2]) * 0.5f;
                dst[0x03] = (v1[3] + v0[3]) * 0.5f;
                ++written;
                dst[0x0b] = (v1[0] + v2[0]) * 0.5f;
                dst[0x0c] = (v1[1] + v2[1]) * 0.5f;
                dst[0x0d] = (v1[2] + v2[2]) * 0.5f;
                dst[0x0e] = (v1[3] + v2[3]) * 0.5f;
                ++written;
                dst[0x16] = (v2[0] + v0[0]) * 0.5f;
                dst[0x17] = (v2[1] + v0[1]) * 0.5f;
                dst[0x18] = (v2[2] + v0[2]) * 0.5f;
                dst[0x19] = (v2[3] + v0[3]) * 0.5f;
                ++written;
                idxbuf[cursor] = i0;
                idxbuf[cursor + 1] = (u16)m;
                idxbuf[cursor + 2] = (u16)(m + 2);
                idxbuf[cursor + 3] = i1;
                idxbuf[cursor + 4] = (u16)(m + 1);
                idxbuf[cursor + 5] = (u16)m;
                idxbuf[cursor + 6] = i2;
                idxbuf[cursor + 7] = (u16)(m + 2);
                idxbuf[cursor + 8] = (u16)(m + 1);
                idxbuf[cursor + 9] = (u16)m;
                idxbuf[cursor + 10] = (u16)(m + 1);
                idxbuf[cursor + 11] = (u16)(m + 2);
                dst += 0x21;
                cursor += 12;
                ip += 3;
            } while (--cnt);
        }
        start = top;
        --strips;
    }

    VecInsert(vec, idxbuf + start, (cursor - start) * 2);
}

// @ 0x00f68c80
void cTerrainEditor::DrawRaster(int idx, u32 a, int* handle, u32 b)
{
    int sh = FUN_00f67770(a, handle);
    u32 shader = GetShaderTable()->table[sh]->id;
    Binding b0;
    b0.Init(shader, 0, mHandle68);

    void* h = (void*)*handle;
    u32 resolved;
    if (h != 0) {
        if ((*(u8*)((char*)h + 4) & 1) == 0)
            FUN_0067dd60()->Resolve(h);
        resolved = *(u32*)h;
    } else {
        resolved = 0;
    }

    Binding b1;
    b1.Init(shader, 1, resolved);

    mViewer->SetRaster(&mRasterDesc[idx], true);
    if (mViewer->Update()) {
        mBatch2->Apply(shader, (void*)b);
        mBatch2->Flush();
        mViewer->Finish();
    }
    b1.Done();
    b0.Done();
}
} // namespace SP
