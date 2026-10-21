// Slice s00f69a30 -- SPTerrain/SPTerrainEditor.obj  (cTerrainEditor init + brush/quad draw helpers)
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern "C" long __cdecl _InterlockedExchangeAdd(volatile long* p, long v);
#pragma intrinsic(_InterlockedExchangeAdd)

struct Vec3 { float x, y, z; Vec3() {} Vec3(float a, float b, float c) : x(a), y(b), z(c) {} };
struct Vec4 { float x, y, z, w; Vec4() {} Vec4(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {} };
struct Vec2 { float x, y; Vec2() {} Vec2(float a, float b) : x(a), y(b) {} };

// ---- globals --------------------------------------------------------------------------------
extern const float C_1485720;    // 0x01485720  = 1.0f
extern const float C_148f63c;    // 0x0148f63c  = 0.017453292f
extern const u8    T_148f624[];  // 0x0148f624  ping id table (6 dwords)
extern const u32   D_148f614;    // 0x0148f614  AutoHandler id array
extern u8          g_16c998c[];  // 0x016c998c
extern u8          g_16c9858[];  // 0x016c9858
extern float       g_16c9824[11];
extern u32         g_16c9898;
extern float       g_16c990c;
extern float       g_16c9910;
extern float       g_16c9914;
extern void*       g_015b0e40;   // 0x015b0e40

// ---- externs --------------------------------------------------------------------------------
void* __cdecl FUN_00f672f0(const char* fmt, int w, int h, int flags);           // 0x00f672f0
void* __cdecl FUN_0067dda0();                                                   // 0x0067dda0
void* __cdecl FUN_0067dd60();                                                   // 0x0067dd60
void* __cdecl FUN_0067dcc0();                                                   // 0x0067dcc0
void* __cdecl FUN_0067de30();                                                   // 0x0067de30
void* __cdecl FUN_0067dd10();                                                   // 0x0067dd10
void  __cdecl FUN_00777ae0(int slot, const void* data, int zero);               // 0x00777ae0
void* __cdecl GetShaderTable();                                                 // 0x00f48a60
void  __cdecl FUN_00f959f0(void* table, int a);                                 // 0x00f959f0
void  __cdecl RemoveHandler(void* h, u32 a, u32 b, u32 c, u32 d);               // 0x00571db0
void  __cdecl operator_delete(void* p);                                         // 0x00f47380
void  __cdecl FillSpriteTexture(void* buf, u32 bytes, int offset);              // 0x011f0440
typedef void (__thiscall *tfn1)(void*, void*);
typedef void (__thiscall *tfnf)(void*, float);
typedef void (__thiscall *tfnv)(void*);
void  Matrix3_Assign();                                                         // 0x0041cb40
void  cXform_PreRotateX();                                                      // 0x005a2d90
void  cXform_RotateY();                                                         // 0x006b9050
void  cTransform_PreRotateY();                                                  // 0x004099b0
void  Basis3_Build();                                                           // 0x006b9440
void  __cdecl FUN_011ef750(void* self, int a, void* out);                       // 0x011ef750
void  __cdecl FUN_011e0744(void* self, const void* data, int n);                // 0x011e0744
void  __cdecl FUN_011ef880(void* self);                                         // 0x011ef880
void* __cdecl FUN_00fc2c10(void* self, int a, int b);                           // 0x00fc2c10
void  __cdecl FUN_00fc2830(void* self);                                         // 0x00fc2830

// ---- interfaces -----------------------------------------------------------------------------
#define V(n) virtual void v##n();
struct IVP {
    V(0) V(1) V(2) V(3)
    virtual void* CreateRasterID(void* out, int w, int h, int fmt, int a, u32 id, int b); // +0x10
    V(5) V(6)
    virtual void* GetRaster(u32 pageID, u32 allocID);                        // +0x1c
    V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15) V(16)
    virtual void  Remap(u32 pageID, u32 allocID, const char* name);          // +0x48
};
struct IResolver {
    V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13) V(14)
    virtual void* CreateTexture(u32 id, void* r, int w, int h, int a, int b, int c, int d); // +0x3c
};
struct IBatch {
    V(0)
    virtual bool BigAlloc(void** out, int stride, int count, const int* desc, int verts, int one); // +0x04
    virtual bool Alloc(void** out, int stride, int count, int zero);         // +0x08
    virtual bool Apply(u32 shader, void* arg);                               // +0x0c
    virtual void Flush();                                                    // +0x10
};
struct IBinding { u32 w[4]; };
struct ShaderIds { u32 pad; u32 id; };

// SP::App  (vtable slots 0x50 = 20, 0x1c = 7 on the returned object, 0x38 = 14)
struct AppResult { V(0) V(1) V(2) V(3) V(4) V(5) V(6) virtual void* Sub(); }; // +0x1c
struct IApp {
    V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9)
    V(10) V(11) V(12) V(13)
    virtual u32 Kind();            // +0x38
    V(15) V(16) V(17) V(18) V(19)
    virtual AppResult* Views();    // +0x50
};
struct IServer {
    V(0) V(1) V(2) V(3) V(4)
    virtual void Post(u32 id, void* a, int b);   // +0x14
};
struct ITerrainSphere {
    V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7) V(8) V(9) V(10) V(11) V(12) V(13)
    V(14) V(15) V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23) V(24) V(25)
    V(26) V(27) V(28) V(29) V(30) V(31) V(32) V(33) V(34) V(35) V(36) V(37)
    V(38)
    virtual void SetProp(void* s, int zero);     // +0x9c (slot 39)
};
#undef V

struct RectT { float l, t, r, b; };
struct RectId { u32 pageID; u32 allocID; };
struct RasterLike { u32 pad0[3]; u16 width; u16 height; u8 depth; u8 pad2[3]; };

// ---- the terrain editor ---------------------------------------------------------------------
struct cTerrainEditor {
    char       pad0[0x08];            // +0x00 vfptr(s)
    void*      mpServer;              // +0x08
    void*      mpHandler;             // +0x0c
    void*      mpIdArray;             // +0x10
    u32        mnIdArrayCount;        // +0x14
    u32        mnPriority;            // +0x18
    void*      mRTTCamera;            // +0x1c
    RasterLike* mHeightRasterArray[6];// +0x20
    RectId     mHeightRectIDArray[6]; // +0x38
    RasterLike* mHeightRTPingRaster;  // +0x68
    RectId     mHeightRTPingRectID;   // +0x6c
    void*      mTextureType;          // +0x74
    u8         mGPUDirtyFace[6];      // +0x78
    char       pad7e[2];
    RectT      mCPUDirtyRect[6];      // +0x80
    RectT      mBrushDirtyRect[6];    // +0xe0
    char       pad140[0x158 - 0x140];
    u8         mTempBuffer0;          // +0x158
    u8         pad159[3];
    float      mTempBufferF;          // +0x15c
    char       pad160[4];
    float      mMaxTimePerRenderJob;  // +0x164
    void*      mUploadHeightMapTexture; // +0x168
    RectId     mTempExtractRectID[2]; // +0x16c
    RasterLike* mTempExtractTexture;  // +0x17c
    char       pad180[0x198 - 0x180];
    RasterLike* mTileRaster[2];       // +0x198
    int        mTileIndex;            // +0x1a0
    char       pad1a4[0x1c8 - 0x1a4];
    void*      mpSphere;              // +0x1c8 (AutoRefCount target)
    char       pad1cc[4];
    float      mRange[4];             // +0x1d0
    float      mMat[8];               // +0x1e0
    IBatch*    mBatch;                // +0x200
    IBatch*    mBatch2;               // +0x204
    IBatch*    mBatch3;               // +0x208

    void Init();                                                      // 0x00f69a30
    u32  HandleMessage(u32 id, void* p);                              // 0x00f69e50
    bool ReadTile(int face, const int* rect, float elapsed);          // 0x00f69f50
    bool DrawBrushLayer(u32 param);                                   // 0x00f6a3a0
    void Construct();                                                 // 0x00f6a4b0
    void Destroy();                                                   // 0x00f6a5d0
    void DrawBrush(u32 a, u32 b, void* p, void* q, u32 c);            // 0x00f6a6a0
    void SetBrushShaderData(void* p, int q);                          // 0x00f6a710
    void TextureMapQuadRTT(u32 a1, u32 a2, int a3, void* a4, u32 a5, void* a6, u32 a7); // 0x00f6a8d0

    void Refresh();                                                   // 0x00f67da0
    void InitViewer();                                                // 0x00f67e70
    bool BuildBrush(void* faces, u32 flipIdx, u32 a3, u32 a4);        // 0x00f68070
    void UpdateRange(void* p);                                        // 0x00f684c0
    bool DrawUnitQuad(int idx, u32 a, u32 b);                         // 0x00f68650
    void DrawRaster(int idx, u32 a, void* handle, u32 b);             // 0x00f68c80
    bool TextureMapQuad(u32 a, u32 b, u32 c, void* p, u32 d, void* e);// 0x00f68d50
    void PairResize(int size);                                        // 0x00f67360 (this = container)
    void PairClear();                                                 // 0x00f674c0
    void ApplyRaster(int idx, void* p);                               // 0x00f67810
};

// @ 0x00f69a30
void cTerrainEditor::Init()
{
    mHeightRasterArray[0] = (RasterLike*)FUN_00f672f0("V3FC4BT2F", 0x100, 0, 0);
    mHeightRasterArray[1] = (RasterLike*)FUN_00f672f0("V4FN4FC4BT2F", 0xc00, 0x400, 0);
    mHeightRasterArray[2] = (RasterLike*)FUN_00f672f0("V4FN3FC4BT4FT4FT4FT4FT4F", 0x10, 0, 0);
    mMaxTimePerRenderJob = 100.0f;

    IApp* pm = (IApp*)FUN_0067de30();
    void** ppv = &mpSphere;
    void* old = *ppv;
    if (old) {
        *ppv = 0;
        (*(void(__thiscall**)(void*, int))(*(void**)old))(old, 4);
    }
    (*(void(__thiscall**)(void*, u32, u32, void**))(*(void**)pm))(pm, 0x5f848353, 0x243ad2b, ppv);

    IServer* server = (IServer*)FUN_0067dcc0();
    mpServer = server;
    mpHandler = this;
    mpIdArray = (void*)&D_148f614;
    mnIdArrayCount = 4;
    mnPriority = 0;
    if (server) {
        u32 i = 0;
        do {
            u32 id = *(const u32*)((const char*)&D_148f614 + i);
            (*(void(__thiscall**)(void*, cTerrainEditor*, u32))(*(void**)server))(server, this, id);
            i += 4;
        } while (i < 0x10);
    }

    mTempBuffer0 = 0;
    mTempBufferF = 0.0f;

    for (int i = 0; i < 6; ++i)
        mGPUDirtyFace[i] = 0;
    *(u32*)&mGPUDirtyFace[4] = 0;

    const float z = 0.0f;
    for (int i = 0; i < 6; ++i) {
        mCPUDirtyRect[i].l = z;
        mCPUDirtyRect[i].t = z;
        mCPUDirtyRect[i].r = z;
        mCPUDirtyRect[i].b = z;
    }
    *(u32*)&mTextureType = 0;
    for (int i = 0; i < 6; ++i) {
        mBrushDirtyRect[i].l = z;
        mBrushDirtyRect[i].t = z;
        mBrushDirtyRect[i].r = z;
        mBrushDirtyRect[i].b = z;
    }

    IVP* vp = (IVP*)FUN_0067dda0();
    RectId* dst = mHeightRectIDArray;
    RasterLike** rasters = mHeightRasterArray;
    const u32* ids = (const u32*)&T_148f624;
    do {
        u32 tmp[2];
        u32* r = (u32*)vp->CreateRasterID(tmp, 0x200, 0x200, 0x15, 0, *ids, 0);
        u32 allocID = r[1];
        u32 pageID = r[0];
        vp->Remap(r[0], allocID, "TerrainHeightRasters");
        if (allocID != 0xffffffff) {
            *rasters = (RasterLike*)vp->GetRaster(pageID, allocID);
            dst->pageID = pageID;
            dst->allocID = allocID;
        }
        ++dst;
        ++rasters;
        ++ids;
    } while ((int)ids < 0x148f63c);

    IResolver* res = (IResolver*)FUN_0067dd60();
    RasterLike* tex = (RasterLike*)res->CreateTexture(0xc88d71ef, g_015b0e40, 0x200, 0x200, 1, 8, 0x51, 0);
    RasterLike* oldTex = mTempExtractTexture;
    if (tex != oldTex) {
        if (tex) {
            void** rc = (void**)tex;
            _InterlockedExchangeAdd((volatile long*)&rc[2], 1);
        }
        mTempExtractTexture = tex;
        if (oldTex) {
            void** rc = (void**)oldTex;
            long n = _InterlockedExchangeAdd((volatile long*)&rc[2], -1);
            if (n < 1) {
                _InterlockedExchangeAdd((volatile long*)&rc[2], 1);
            }
        }
    }

    u32 tmp2[2];
    u32* r2 = (u32*)vp->CreateRasterID(tmp2, 0x200, 0x200, 0x15, 0, 0x3356f173, 0);
    u32 pageID = r2[0];
    u32 allocID = r2[1];
    vp->Remap(pageID, allocID, "TerrainPing");
    if (allocID != 0xffffffff) {
        mHeightRTPingRaster = (RasterLike*)vp->GetRaster(pageID, allocID);
        mHeightRTPingRectID.pageID = pageID;
        mHeightRTPingRectID.allocID = allocID;
    }

    ((cTerrainEditor*)((char*)this + 0x180))->PairResize(0x40);
    ((cTerrainEditor*)((char*)this + 0x1a4))->PairResize(0x20);
    InitViewer();
}

// @ 0x00f69e50
u32 cTerrainEditor::HandleMessage(u32 id, void* p)
{
    if (id > 0x12d74a2) {
        if (id == 0x24e5e7f) {
            void* t = GetShaderTable();
            FUN_00f959f0(t, *(u8*)p);
            return 1;
        }
        return 0;
    }
    if (id == 0x12d74a2) {
        if (!mTextureType)
            return 1;
        void* s;
        if (p == 0 || (s = *(void**)((char*)p + 8)) == 0) {
            void* app = (void*)FUN_0067dd10();
            void** avt = *(void***)app;
            void* ar = ((void*(__thiscall*)(void*))avt[0x50 / 4])(app);
            void** rvt = *(void***)ar;
            s = ((void*(__thiscall*)(void*))rvt[0x1c / 4])(ar);
        }
        void* app2 = (void*)FUN_0067dd10();
        void** a2vt = *(void***)app2;
        u32 k = ((u32(__thiscall*)(void*))a2vt[0x38 / 4])(app2);
        if (k == 0x9ac9c2) {
            void* ts = mTextureType;
            void** tvt = *(void***)ts;
            ((void(__thiscall*)(void*, void*, int))tvt[0x9c / 4])(ts, s, 0);
            return 1;
        }
        void* ms = (void*)FUN_0067dcc0();
        void** mvt = *(void***)ms;
        ((void(__thiscall*)(void*, u32, void*, int))mvt[0x14 / 4])(ms, 0x1b537e5, p, 0);
        return 1;
    }
    switch (id) {
    case 0x1216ec2:
        Refresh();
        return 1;
    case 0x1216ec4:
        if (mTextureType)
            *(void**)((char*)mTextureType + 0x1cc) = *(void**)((char*)p + 8);
        return 1;
    default:
        break;
    }
    return 0;
}

// @ 0x00f69f50
bool cTerrainEditor::ReadTile(int face, const int* rect, float elapsed)
{
    void* st = GetShaderTable();
    u32 shader = *(u32*)(*(char**)((char*)st + 0x50) + 4);
    void* out;
    if (!mBatch->Alloc(&out, 0x18, 4, 0))
        return false;

    int* verts = (int*)out;
    // original: operator_new__(0x60) then writes 0x60 bytes; contract small.
    verts[0x14 / 4] = 0;
    RasterLike* raster = mHeightRasterArray[face];
    u16 w = raster->width;
    u16 h = raster->height;
    u8 depth = raster->depth;

    float fw = (float)w;
    float fh = (float)h;
    float zero = 0.0f;
    float n = -zero / fw;
    float one = C_1485720;
    float o = one - zero / fw;
    *(float*)((char*)verts + 0x00) = n;
    *(float*)((char*)verts + 0x04) = n;
    *(float*)((char*)verts + 0x08) = zero;
    *(float*)((char*)verts + 0x18) = o;
    *(float*)((char*)verts + 0x1c) = n;
    *(float*)((char*)verts + 0x20) = zero;
    *(float*)((char*)verts + 0x30) = n;
    *(float*)((char*)verts + 0x34) = o;
    *(float*)((char*)verts + 0x38) = zero;
    *(float*)((char*)verts + 0x48) = o;
    *(float*)((char*)verts + 0x4c) = o;

    float u0 = (float)rect[0] / fw;
    float v0 = (float)rect[1] / fh;
    float u1 = (float)rect[2] / fw;
    float v1 = (float)rect[3] / fh;
    *(float*)((char*)verts + 0x10) = u0;
    *(float*)((char*)verts + 0x14) = v1;
    *(float*)((char*)verts + 0x28) = u1;
    *(float*)((char*)verts + 0x2c) = v1;
    *(float*)((char*)verts + 0x40) = u0;
    *(float*)((char*)verts + 0x44) = v0;
    *(float*)((char*)verts + 0x58) = u1;
    *(float*)((char*)verts + 0x5c) = v0;

    FUN_00777ae0(0x201, 0, 0);

    int idx = mTileIndex;
    float* rp = (float*)((char*)this + 0x180 + idx * 8);
    Vec2 rs(rp[0], rp[1]);
    (*(void(__thiscall**)(void*, Vec2*, int))(*(void**)((char*)this + 0x1c)))(mRTTCamera, &rs, 1);
    // Viewer::SetRaster(mRTTCamera, &rs, 1) then Update()
    bool ok = (*(bool(__thiscall**)(void*))(*(void**)((char*)this + 0x1c)))(mRTTCamera);
    if (ok) {
        int* handle = (int*)mTileRaster[idx];
        FUN_00fc2c10(&out, 0, (int)handle);   // RasterState::Construct
        if (!mBatch->Apply(shader, 0)) {
            FUN_00fc2830(&out);
            return false;
        }
        mBatch->Flush();
        (*(void(__thiscall**)(void*))(*(void**)((char*)this + 0x1c)))(mRTTCamera);
        FUN_00fc2830(&out);
    }

    void* buf = (void*)mTileRaster[idx];
    FillSpriteTexture(buf, (u32)(depth >> 3) << 12, 0);

    void* hm = (*(void*(__thiscall**)(void*))(*(void**)((char*)this + 0x74)))((char*)this + 0x74);
    int* hd = *(int**)((char*)hm + 8);
    int side = hd[2];
    int iVar2 = hd[4] + side * side * idx * 2;
    u16* dst = (u16*)iVar2;   // (see below)
    (void)dst;

    int row = 0;
    u32 yoff = 0;
    do {
        u32* src = (u32*)mTileRaster[mTileIndex];
        int x = 0;
        do {
            if (rect[0] + x < (int)w && rect[1] + row < (int)h)
                ((u16*)(size_t)(hd[4] + (side * side * idx * 2)))[((rect[1] + row) * w + rect[0] + x)] =
                    (u16)(*(u32*)((char*)src + ((yoff + x) * 4)) >> 8);
            x += 4;
        } while (x < 0x40);
        ++row;
        yoff += 0x40;
    } while (yoff < 0x1000);

    mTileIndex = 1 - mTileIndex;
    return true;
}

// @ 0x00f6a3a0
bool cTerrainEditor::DrawBrushLayer(u32 param)
{
    if (!mTextureType)
        return false;
    ITerrainSphere* ts = (ITerrainSphere*)mTextureType;
    void* hm = (*(void*(__thiscall**)(ITerrainSphere*))(*(void**)ts))(ts);
    hm = *(void**)((char*)hm + 8);
    int* hd = (int*)hm;
    int side = hd[2];
    for (int i = 0; i < 6; ++i) {
        if (!mGPUDirtyFace[i])
            continue;
        void* sphere = mTextureType;
        u32* idxbuf = *(u32**)((char*)sphere + 0);   // [mTextureType+?]
        int* src = (int*)(side * side * i * 2 + hd[4]);
        u32 handle = (u32)idxbuf;
        (void)handle; (void)src; (void)param;
    }
    return true;
}

// @ 0x00f6a4b0
void cTerrainEditor::Construct()
{
    char* t = (char*)this;
    *(u32*)(t + 0x04) = 0x013f1ab0;
    *(u32*)(t + 0x00) = 0x0148f704;
    *(u32*)(t + 0x04) = 0x0148f6f4;
    *(u32*)(t + 0x08) = 0;
    *(u32*)(t + 0x0c) = 0;
    *(u32*)(t + 0x10) = 0;
    *(u32*)(t + 0x14) = 0;
    *(u32*)(t + 0x18) = 0;
    *(u32*)(t + 0x1c) = 0;
    *(u32*)(t + 0x38) = 0xffffffff;
    *(u32*)(t + 0x3c) = 0xffffffff;
    *(u32*)(t + 0x40) = 0xffffffff;
    *(u32*)(t + 0x44) = 0xffffffff;
    *(u32*)(t + 0x48) = 0xffffffff;
    *(u32*)(t + 0x4c) = 0xffffffff;
    *(u32*)(t + 0x50) = 0xffffffff;
    *(u32*)(t + 0x54) = 0xffffffff;
    *(u32*)(t + 0x58) = 0xffffffff;
    *(u32*)(t + 0x5c) = 0xffffffff;
    *(u32*)(t + 0x60) = 0xffffffff;
    *(u32*)(t + 0x64) = 0xffffffff;
    *(u32*)(t + 0x68) = 0;
    *(u32*)(t + 0x6c) = 0xffffffff;
    *(u32*)(t + 0x70) = 0xffffffff;
    *(u32*)(t + 0x74) = 0;
    *(u32*)(t + 0x168) = 0;
    *(u32*)(t + 0x16c) = 0;
    *(u32*)(t + 0x170) = 0;
    *(u32*)(t + 0x17c) = 0;
    *(u32*)(t + 0x180) = 0;
    *(u32*)(t + 0x184) = 0;
    *(u32*)(t + 0x188) = 0;
    *(u32*)(t + 0x18c) = 0;
    *(u32*)(t + 0x190) = 0;
    *(u32*)(t + 0x194) = 0;
    *(u32*)(t + 0x198) = 0;
    *(u32*)(t + 0x19c) = 0;
    *(u32*)(t + 0x1a0) = 0;
    *(u32*)(t + 0x1a4) = 0;
    *(u32*)(t + 0x1a8) = 0;
    *(u32*)(t + 0x1ac) = 0;
    *(u32*)(t + 0x1b0) = 0;
    *(u32*)(t + 0x1b4) = 0;
    *(u32*)(t + 0x1b8) = 0;
    *(u32*)(t + 0x1bc) = 0;
    *(u32*)(t + 0x1c0) = 0;
    *(u32*)(t + 0x1c4) = 0;
    *(u32*)(t + 0x1c8) = 0;
    *(u8*)(t + 0x1cc) = 0;
    *(u8*)(t + 0x1cd) = 0;
    *(u8*)(t + 0x1ce) = 0;
    *(u32*)(t + 0x200) = 0;
    *(u32*)(t + 0x204) = 0;
    *(u32*)(t + 0x208) = 0;
}

// @ 0x00f6a5d0
void cTerrainEditor::Destroy()
{
    *(void**)((char*)this + 0) = (void*)0x0148f704;
    *(void**)((char*)this + 4) = (void*)0x0148f6f4;
    void* p = *(void**)((char*)this + 0x1c8);
    if (p) {
        void** vt = *(void***)p;
        ((void(__thiscall*)(void*))vt[1])(p);
    }
    ((cTerrainEditor*)((char*)this + 0x1a4))->PairClear();
    ((cTerrainEditor*)((char*)this + 0x180))->PairClear();
    {
        u32 r = *(u32*)((char*)this + 0x17c);
        if (r) {
            volatile long* c = (volatile long*)(r + 8);
            _InterlockedExchangeAdd(c, -1);
            if (_InterlockedExchangeAdd(c, 0) < 1)
                _InterlockedExchangeAdd(c, 1);
            else
                _InterlockedExchangeAdd(c, 0);
        }
    }
    {
        void* b = *(void**)((char*)this + 0x168);
        if (b) {
            if (*(int*)((char*)b - 4) != 0)
                operator_delete((char*)b);
        }
    }
    {
        void* s = *(void**)((char*)this + 0x74);
        if (s) {
            void** vt = *(void***)s;
            ((void(__thiscall*)(void*))vt[1])(s);
        }
    }
    {
        void* h = *(void**)((char*)this + 0x08);
        if (h) {
            u32 c = *(u32*)((char*)this + 0x0c);
            u32 d = *(u32*)((char*)this + 0x10);
            u32 e = *(u32*)((char*)this + 0x14);
            u32 f = *(u32*)((char*)this + 0x18);
            *(u32*)((char*)this + 0x08) = 0;
            RemoveHandler(h, c, d, e, f);
        }
    }
    *(void**)((char*)this + 0) = (void*)0x013eb394;
    *(void**)((char*)this + 4) = (void*)0x013eb938;
}

// @ 0x00f6a6a0
void cTerrainEditor::DrawBrush(u32 a1, u32 a2, void* a3, void* a4, u32 a5)
{
    if (!BuildBrush((void*)a1, a2, (u32)a3, (u32)a4))
        return;
    ApplyRaster((int)a2, (void*)a5);
    UpdateRange(a3);
    FUN_00777ae0(0x241, 0, 0);
    FUN_00777ae0(0x23c, 0, 0);
    DrawRaster((int)a2, (u32)a3, a4, a5);
}

// @ 0x00f6a710
void cTerrainEditor::SetBrushShaderData(void* p, int q)
{
    UpdateRange(p);
    void* out;
    if (*(u8*)((char*)q + 6)) {
        g_16c9898 |= 1;
        u8 m[0x10];
        *(u8*)((char*)m + 0x00) = 0;
        *(u8*)((char*)m + 0x01) = 0;
        float f;
        f = g_16c990c; *(float*)((char*)m + 0x00) = f;
        f = g_16c9910; *(float*)((char*)m + 0x04) = f;
        *(u8*)((char*)m + 0x02) = 0;
        *(u8*)((char*)m + 0x03) = 0;
        f = g_16c9914; *(float*)((char*)m + 0x08) = f;
        *(u8*)((char*)m + 0x0c) = 0;
        f = C_1485720; *(float*)((char*)m + 0x0c) = f;
        ((tfn1)Matrix3_Assign)((char*)m + 0x04, g_16c998c);
        float rx = *(float*)((char*)p + 0x20) * C_148f63c;
        ((tfnf)cXform_PreRotateX)(m, rx);
        float ry = *(float*)((char*)p + 0x24) * C_148f63c;
        ((tfnf)cXform_RotateY)(m, ry);
        float rz = *(float*)((char*)p + 0x28) * C_148f63c;
        ((tfnf)cTransform_PreRotateY)(m, rz);
        ((tfn1)Basis3_Build)(m, g_16c9858);
        out = g_16c9858;
    } else {
        out = 0;
    }
    FUN_00777ae0(0x241, out, 0);

    if (*(u8*)p) {
        g_16c9824[0] = *(float*)((char*)p + 4);
        g_16c9824[1] = *(float*)((char*)p + 0xc);
        g_16c9824[2] = *(float*)((char*)p + 0x1c);
        g_16c9824[3] = *(float*)((char*)p + 0x24);
        g_16c9824[4] = *(float*)((char*)p + 8);
        g_16c9824[5] = *(float*)((char*)p + 0x10);
        g_16c9824[6] = *(float*)((char*)p + 0x18);
        g_16c9824[7] = *(float*)((char*)p + 0x20);
        g_16c9824[8] = *(float*)((char*)p + 0x14);
        g_16c9824[9] = *(float*)((char*)p + 0x28);
        g_16c9824[10] = 0.001953125f;
        out = g_16c9824;
    } else {
        out = 0;
    }
    FUN_00777ae0(0x23c, out, 0);
}

// @ 0x00f6a8d0
void cTerrainEditor::TextureMapQuadRTT(u32 a1, u32 a2, int a3, void* a4, u32 a5, void* a6, u32 a7)
{
    if (!TextureMapQuad(a1, a2, (u32)a3, a4, a5, a6))
        return;
    ApplyRaster(a3, (void*)a7);
    SetBrushShaderData(a4, (int)a5);
    DrawRaster(a3, (u32)a4, (void*)a5, a7);
}
