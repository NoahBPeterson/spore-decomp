// cViewer methods and rw resource/arena helpers, 0x007c4be0-0x007c5a40.
// Reconstructed from the retail disassembly + Ghidra decompile.
// Members/offsets follow the 2008 dev PDB cViewer / rw::graphics::Camera layouts.

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// ---- rw::graphics::Camera (size 0x98; PDB says 0xa0) ----
struct D3DVIEWPORT9 { u32 X, Y, Width, Height; float MinZ, MaxZ; };

struct rwCamera {
    float m_transform[16];       // +0x00  Matrix44Affine
    void* m_raster[4];           // +0x40
    void* m_zbuffer;             // +0x50
    float m_viewOffset[2];       // +0x54
    float m_viewWindow[2];       // +0x5c
    float m_recipViewWindow[2];  // +0x64
    int   m_projectionType;      // +0x6c
    float m_nearPlane;           // +0x70
    float m_farPlane;            // +0x74
    D3DVIEWPORT9 m_viewport;     // +0x78
    void* m_window;              // +0x90
    u32   m_stencilClear;        // +0x94

    void  AssignTo(void* out);        // 0x7779e0
    int   Check();                    // 0x11f3f20
    void  SetTexture(void* t);        // 0x7c3b70
    void  SetSize(int x, int y, int w, int h);  // 0x76d7d0
    void  GetViewport(void* out);     // 0x7c4010
};

// ---- SP::cViewer (size 0x174) ----
struct cViewer {
    float mCameraToWorld[16];    // +0x00
    float mWorldToCamera[16];    // +0x40
    float mCameraToClip[16];     // +0x80
    float mWorldToClip[16];      // +0xc0
    float mClipToWorld[16];      // +0x100
    u8    mClearColor[16];       // +0x140
    int   mRenderType;           // +0x150
    int   mRenderTypeVariation;  // +0x154
    void* mShaderDataRT;         // +0x158
    float mMaterialLODs[4];      // +0x15c
    bool  mTileRender;           // +0x16c
    u8    pad16d[3];
    rwCamera* mCamera;           // +0x170

    void UpdateTransforms();                 // 0x7c4940 (extern)
    void SetViewportRect(u16* r);            // 0x7c4a60 (extern)
    void SetAspect(float a);                 // 0x7c4b50 (extern)
    int  BuildTransforms();                  // 0x7c43e0 (extern)

    void SetRaster(int* handle, bool setViewport);
    void SetCameraToWorld(float* m);
    void SetBasis(void* basis);
    void SetCameraToWorldFromBasis(float* p);
    bool Init(bool windowed);
    bool Update();
    bool Copy(cViewer* src, bool a, bool b);
    void CopyFrom(cViewer* src);
    void SetViewportRectArgs(u16 x, u16 y, u16 w, u16 h);
    void SetViewAngle(float a);
    void SetViewAngleY(float a);
    void SetViewWindow(float x, float y);
};

// ---- renderer singleton (global DAT_015fd8d4) ----
struct Renderer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual int  v18(int a, int b);
    virtual void v1c();
    virtual void v20(int* out, int a, int b);
};
extern Renderer* GetRenderer();          // 0x67dda0

struct Basis3 { void Build(void* owner); };  // 0x6b9440
extern void* FUN_00761380();                 // default raster factory / init
extern float g_identityMatrix[16];           // 0x1635fa0
extern void* g_defaultCameraRaster;          // 0x15d0838
extern void* g_defaultZBufferRaster;         // 0x15d083c
extern float g_tanScaleA;                    // 0x153c7a8
extern float g_tanScaleB;                    // 0x1401c04
extern float g_one;                          // 0x1485720
extern float g_aspectEps;                    // 0x153c98c
extern u8    g_forceAspect;                  // 0x153c988
extern float g_defaultFov;                   // 0x1410350

struct cShaderDataRenderType { u8 mType; u8 pad[3]; int mVariation; };

extern "C" void* EANew(int size, const char* name, int, int, int, int);  // 0xf473a0
extern "C" float tanf(float);                                            // CRT
extern "C" void  DrawShader(int cmd, void* data, int changed);           // 0x777ae0
extern "C" void  FUN_00777ae0(int cmd, void* data, int changed);
extern "C" void  FUN_011f38f0(int a, void* b);                           // 0x11f38f0

// ===========================================================================
// @ 0x007c4be0
__declspec(noinline) void cViewer::SetRaster(int* handle, bool setViewport) {
    Renderer* r = GetRenderer();
    int v = r->v18(handle[0], handle[1]);
    mCamera->m_raster[0] = (void*)v;
    if (setViewport) {
        int rect[4];
        Renderer* r2 = GetRenderer();
        r2->v20(rect, handle[0], handle[1]);
        SetViewportRect((u16*)rect);
    }
}

// ===========================================================================
// @ 0x007c4c40
__declspec(noinline) void cViewer::SetCameraToWorld(float* m) {
    for (int i = 0; i < 16; i++) mCameraToWorld[i] = m[i];
    rwCamera* cam = mCamera;
    float* d = cam->m_transform;
    // SIMD 3x3 transpose with sign flip on row 0 (see disassembly).
    d[0] = -m[0]; d[1] = -m[1]; d[2] = -m[2]; d[3] = -m[0];
    d[4] =  m[8]; d[5] =  m[9]; d[6] =  m[10]; d[7] =  m[8];
    d[8] =  m[4]; d[9] =  m[5]; d[10] = m[6]; d[11] = m[4];
    d[12] = m[12]; d[13] = m[13]; d[14] = m[14]; d[15] = m[12];
    UpdateTransforms();
}

// ===========================================================================
// @ 0x007c4d00
__declspec(noinline) void cViewer::SetBasis(void* basis) {
    ((Basis3*)basis)->Build(this);
    SetCameraToWorld(mCameraToWorld);
}

// ===========================================================================
// @ 0x007c4d20
__declspec(noinline) void cViewer::SetCameraToWorldFromBasis(float* p) {
    float m[16];
    m[0] = -p[0]; m[1] = -p[1]; m[2] = -p[2]; m[3] = 0.0f;
    m[4] =  p[8]; m[5] =  p[9]; m[6] =  p[10]; m[7] = 0.0f;
    m[8] =  p[4]; m[9] =  p[5]; m[10] = p[6]; m[11] = 0.0f;
    m[12] = p[12]; m[13] = p[13]; m[14] = p[14]; m[15] = 1.0f;
    SetCameraToWorld(m);
}

// ===========================================================================
// @ 0x007c4dd0
__declspec(noinline) bool cViewer::Init(bool windowed) {
    if (mCamera != 0) return false;
    mCamera = (rwCamera*)FUN_00761380();
    if (mCamera == 0) return false;
    if (mShaderDataRT == 0) {
        mShaderDataRT = EANew(8, "Graphics", 0, 0, 0, 0);
        ((int*)mShaderDataRT)[1] = -1;
        *(u8*)mShaderDataRT = 0xff;
    }

    rwCamera* cam = mCamera;
    cam->m_nearPlane = 1.0f;
    cam->m_farPlane = 1000.0f;

    rwCamera* def = (rwCamera*)g_defaultCameraRaster;
    u16 w = *(u16*)((char*)def + 0x0c);
    u16 h = *(u16*)((char*)def + 0x0e);
    cam->m_viewport.X = 0;
    cam->m_viewport.Y = 0;
    cam->m_viewport.Width = w;
    cam->m_viewport.Height = h;
    cam->m_viewport.MinZ = 0.0f;
    cam->m_viewport.MaxZ = 1.0f;

    float* d = cam->m_transform;
    d[0]=1.0f; d[1]=0; d[2]=0; d[3]=0;
    d[4]=0; d[5]=1.0f; d[6]=0; d[7]=0;
    d[8]=0; d[9]=0; d[10]=1.0f; d[11]=0;
    d[12]=0; d[13]=0; d[14]=0; d[15]=0;

    for (int i = 0; i < 16; i++) mCameraToWorld[i] = g_identityMatrix[i];

    cam->m_raster[0] = g_defaultCameraRaster;
    cam->m_zbuffer   = g_defaultZBufferRaster;

    if (!windowed) {
        cam->m_projectionType = 1;
        float t = tanf(g_tanScaleA * g_tanScaleB * g_defaultFov);
        cam->m_viewWindow[1] = t;
        float a = ((float)w / (float)h) * t;
        cam->m_viewWindow[0] = a;
        cam->m_recipViewWindow[0] = 1.0f / a;
        cam->m_recipViewWindow[1] = 1.0f / t;
    } else {
        cam->m_projectionType = 2;
        cam->m_viewWindow[0] = 1.0f;
        cam->m_viewWindow[1] = 1.0f;
        cam->m_recipViewWindow[1] = 1.0f;
        cam->m_recipViewWindow[0] = 1.0f;
    }
    UpdateTransforms();
    return true;
}

// ===========================================================================
// @ 0x007c4fd0
__declspec(noinline) bool cViewer::Update() {
    rwCamera* cam = mCamera;
    if (cam->m_raster[0] == 0) return false;

    float aspect = (float)cam->m_viewport.Width / (float)cam->m_viewport.Height;
    float cur = cam->m_viewWindow[0] / cam->m_viewWindow[1];
    float diff = cur - aspect;
    if (diff < 0) diff = -diff;
    if (diff > g_aspectEps && g_forceAspect != 0 && mTileRender)
        SetAspect(aspect);

    if (!mCamera->Check()) return false;
    BuildTransforms();

    cShaderDataRenderType* sd = (cShaderDataRenderType*)mShaderDataRT;
    int changed;
    if (sd->mVariation == mRenderType) {
        changed = (u8)sd->mType == (u8)mRenderTypeVariation ? 0 : 1;
    } else {
        changed = 1;
    }
    sd->mVariation = mRenderType;
    sd->mType = (u8)mRenderTypeVariation;
    DrawShader(0x201, sd, changed);
    return true;
}

// ===========================================================================
// @ 0x007c50b0
__declspec(noinline) bool cViewer::Copy(cViewer* src, bool copyZBuffer, bool keepRaster) {
    if (this == src) return true;
    if (src == 0 || src->mCamera == 0 || mCamera == 0) return false;

    rwCamera* sc = src->mCamera;
    mTileRender = src->mTileRender;
    mRenderTypeVariation = src->mRenderTypeVariation;
    mRenderType = src->mRenderType;
    mCamera->m_projectionType = sc->m_projectionType;
    mCamera->m_nearPlane = sc->m_nearPlane;
    mCamera->m_farPlane  = sc->m_farPlane;
    mCamera->m_viewOffset[0] = sc->m_viewOffset[0];
    mCamera->m_viewOffset[1] = sc->m_viewOffset[1];

    char local[0x40];
    sc->AssignTo(local);
    mCamera->SetTexture(local);

    for (int i = 0; i < 16; i++) mCameraToWorld[i] = src->mCameraToWorld[i];
    mCamera->m_raster[0] = sc->m_raster[0];
    if (!copyZBuffer)
        mCamera->m_zbuffer = sc->m_zbuffer;
    if (!keepRaster && sc->m_raster[1] != 0)
        FUN_011f38f0(1, sc->m_raster[1]);

    int r[4];
    sc->GetViewport(r);
    mCamera->SetSize(r[0], r[1], r[2] - r[0], r[3] - r[1]);

    float vx = sc->m_viewWindow[0];
    float vy = sc->m_viewWindow[1];
    rwCamera* dc = mCamera;
    dc->m_viewWindow[0] = vx;
    dc->m_viewWindow[1] = vy;
    dc->m_recipViewWindow[0] = 1.0f / vx;
    dc->m_recipViewWindow[1] = 1.0f / vy;
    UpdateTransforms();
    return true;
}

// ===========================================================================
// @ 0x007c5240
__declspec(noinline) void cViewer::CopyFrom(cViewer* src) {
    if (this == src) return;
    mTileRender = src->mTileRender;
    {
        float* s = src->mCamera->m_transform;
        float* d = mCamera->m_transform;
        for (int i = 0; i < 16; i++) d[i] = s[i];
    }
    for (int i = 0; i < 16; i++) mCameraToWorld[i] = src->mCameraToWorld[i];
    mCamera->m_nearPlane = src->mCamera->m_nearPlane;
    mCamera->m_farPlane  = src->mCamera->m_farPlane;
    float vx = src->mCamera->m_viewWindow[0];
    float vy = src->mCamera->m_viewWindow[1];
    rwCamera* d = mCamera;
    d->m_viewWindow[0] = vx;
    d->m_viewWindow[1] = vy;
    d->m_recipViewWindow[0] = 1.0f / vx;
    d->m_recipViewWindow[1] = 1.0f / vy;
    UpdateTransforms();
}

// ===========================================================================
// @ 0x007c5310
__declspec(noinline) void cViewer::SetViewportRectArgs(u16 x, u16 y, u16 w, u16 h) {
    struct Rect { int left, top, right, bottom; };
    Rect r;
    r.left = x;
    r.top = y;
    r.right = x + w;
    r.bottom = y + h;
    SetViewportRect((u16*)&r);
}

// ===========================================================================
// @ 0x007c5350
__declspec(noinline) void cViewer::SetViewAngle(float a) {
    rwCamera* cam = mCamera;
    cam->m_projectionType = 1;
    float ratio = cam->m_viewWindow[0] / cam->m_viewWindow[1];
    float t = tanf(g_tanScaleA * g_tanScaleB * a);
    if (ratio != 1.0f) t *= 0.75f;
    float w = ratio * t;
    cam->m_viewWindow[0] = w;
    cam->m_viewWindow[1] = t;
    cam->m_recipViewWindow[0] = 1.0f / w;
    cam->m_recipViewWindow[1] = 1.0f / t;
    UpdateTransforms();
}

// ===========================================================================
// @ 0x007c53d0
__declspec(noinline) void cViewer::SetViewAngleY(float a) {
    rwCamera* cam = mCamera;
    cam->m_projectionType = 1;
    float ratio = cam->m_viewWindow[0] / cam->m_viewWindow[1];
    float t = tanf(g_tanScaleA * g_tanScaleB * a);
    float w = ratio * t;
    cam->m_viewWindow[0] = w;
    cam->m_recipViewWindow[0] = 1.0f / w;
    cam->m_recipViewWindow[1] = 1.0f / t;
    cam->m_viewWindow[1] = t;
    UpdateTransforms();
}

// ===========================================================================
// @ 0x007c5440
__declspec(noinline) void cViewer::SetViewWindow(float x, float y) {
    mCamera->m_projectionType = 2;
    rwCamera* cam = mCamera;
    cam->m_viewWindow[0] = x;
    cam->m_viewWindow[1] = y;
    cam->m_recipViewWindow[0] = 1.0f / x;
    cam->m_recipViewWindow[1] = 1.0f / y;
    UpdateTransforms();
}

// ===========================================================================
// ---- rw arena / resource helpers ----
struct rwArena {
    char pad[0x40];
    int ObjectToId(int id);   // 0x11e3c30
    int IdToObject(int id);   // 0x11e2300
};
struct ArenaInner { rwArena* m_arena; };            // first dword is arena
struct ResMgr1 { char pad[0x80]; ArenaInner* m_inner; };
struct ResourceHolder { char pad[0x1c]; ResMgr1* m_mgr; };
struct rwArray { char pad[0x14]; int m_count; float* Get(int i); };

extern "C" void* ArenaTypeRegGetType(int type);   // 0x11e22c0
extern "C" void* OpNewArray(void* p, int a, int b); // 0x11e073e

// @ 0x007c5490
void* AllocArray(void* self) {
    return OpNewArray(*(void**)((char*)self + 8), 0, *(int*)((char*)self + 0xc) * 4);
}

// @ 0x007c54b0
void* ResolveOne(void* obj, ResourceHolder* holder) {
    int* p = (int*)((char*)obj + 0x3c);
    if (*p == 0) {
        *p = -1;
        return holder;
    }
    *p = holder->m_mgr->m_inner->m_arena->ObjectToId(*p);
    return holder;
}

// @ 0x007c54f0
void ResolveOneToObject(void* obj, int unused, ResMgr1* mgr) {
    int* p = (int*)((char*)obj + 0x3c);
    if (*p == -1) {
        *p = 0;
        return;
    }
    *p = mgr->m_inner->m_arena->IdToObject(*p);
}

// @ 0x007c5520
int ResolveAllOne(void* obj, int unused, ResMgr1* mgr) {
    int* p = (int*)((char*)obj + 0x3c);
    if (*p == -1) {
        *p = 0;
        return 1;
    }
    *p = mgr->m_inner->m_arena->IdToObject(*p);
    return 1;
}

// @ 0x007c5560
void* ResolveMany(void* a, ResourceHolder* holder) {
    int n = *(int*)((char*)a + 4);
    for (int i = 0; i < n; i++) {
        int* e = (int*)(*(void**)a);
        int id = e[i * 2 + 1];
        int r = (id == 0) ? -1 : holder->m_mgr->m_inner->m_arena->ObjectToId(id);
        ((int*)*(void**)a)[i * 2 + 1] = r;
    }
    if (*(void**)a == 0) {
        *(int*)a = -1;
        return holder;
    }
    *(int*)a = holder->m_mgr->m_inner->m_arena->ObjectToId(*(int*)a);
    return holder;
}

// @ 0x007c55d0
void ResolveManyToObject(void* a, int unused, ResMgr1* mgr) {
    int x = (*(int*)a == -1) ? 0 : mgr->m_inner->m_arena->IdToObject(*(int*)a);
    *(int*)a = x;
    int n = *(int*)((char*)a + 4);
    for (int i = 0; i < n; i++) {
        int* e = (int*)(*(void**)a);
        int id = e[i * 2 + 1];
        int r = (id == -1) ? 0 : mgr->m_inner->m_arena->IdToObject(id);
        ((int*)*(void**)a)[i * 2 + 1] = r;
    }
}

// @ 0x007c5630
int ResolveManyToObject2(void* a, int unused, ResMgr1* mgr) {
    int x = (*(int*)a == -1) ? 0 : mgr->m_inner->m_arena->IdToObject(*(int*)a);
    *(int*)a = x;
    int n = *(int*)((char*)a + 4);
    for (int i = 0; i < n; i++) {
        int* e = (int*)(*(void**)a);
        int id = e[i * 2 + 1];
        int r = (id == -1) ? 0 : mgr->m_inner->m_arena->IdToObject(id);
        ((int*)*(void**)a)[i * 2 + 1] = r;
    }
    return 1;
}

// @ 0x007c56a0
int SerializeArray(int out, int* src) {
    if (out == 0) out = src[2];
    rwArray* arr = (rwArray*)src[0];
    u32 n = (u32)arr->m_count;
    for (u32 i = 0; i < n; i++)
        ((float*)out)[i] = *arr->Get((int)i);
    return 1;
}

// @ 0x007c56e0
void RegFF0000C() {
    void* t = ArenaTypeRegGetType(0xff0000);
    if (t) *(void**)((char*)t + 0xc) = (void*)&ResolveAllOne;
}

// @ 0x007c5700
void RegFF0000() {
    void* t = ArenaTypeRegGetType(0xff0000);
    if (t) {
        *(void**)((char*)t + 4) = (void*)&ResolveOne;
        *(void**)((char*)t + 8) = (void*)&ResolveOneToObject;
    }
}

// @ 0x007c5720
void RegFF0001C() {
    void* t = ArenaTypeRegGetType(0xff0001);
    if (t) *(void**)((char*)t + 0xc) = (void*)&ResolveManyToObject2;
}

// @ 0x007c5740
void RegFF0001() {
    void* t = ArenaTypeRegGetType(0xff0001);
    if (t) {
        *(void**)((char*)t + 4) = (void*)&ResolveMany;
        *(void**)((char*)t + 8) = (void*)&ResolveManyToObject;
    }
}

// @ 0x007c5760 (start not in the index; body lives in RegFF0001's range)
int ResolveFF0002(void* obj, int unused, ResMgr1* mgr) {
    *(void**)((char*)obj + 4) = (void*)&SerializeArray;
    int a = *(int*)((char*)obj + 8);
    *(int*)((char*)obj + 8) = (a == -1) ? 0 : mgr->m_inner->m_arena->IdToObject(a);
    int b = *(int*)((char*)obj + 0x10);
    if (b == -1) {
        *(int*)((char*)obj + 0x10) = 0;
        return 1;
    }
    *(int*)((char*)obj + 0x10) = mgr->m_inner->m_arena->IdToObject(b);
    return 1;
}

// @ 0x007c57c0
void RegFF0002C() {
    void* t = ArenaTypeRegGetType(0xff0002);
    if (t) *(void**)((char*)t + 0xc) = (void*)&ResolveFF0002;
}

// @ 0x007c57e0
int IsType1Or9(int p) {
    char c = *(char*)(p + 2);
    if (c == 1 || c == 9) return 1;
    return 0;
}

// @ 0x007c5800
int IsType9to11(int p) {
    char c = *(char*)(p + 2);
    if (c == 9 || c == 10 || c == 11) return 1;
    return 0;
}

// @ 0x007c5820
int CompareRows(int base, int count, int stride, int idx) {
    if (idx == count - 1) return 0;
    const char* a = (const char*)(base + idx * stride);
    const char* b = (const char*)(base + (idx + 1) * stride);
    int n = stride;
    while (n >= 4) {
        if (*(const int*)a != *(const int*)b) return 0;
        a += 4; b += 4; n -= 4;
    }
    if (n > 0) {
        if (a[0] != b[0]) return 0;
        if (n > 1 && a[1] != b[1]) return 0;
        if (n > 2 && a[2] != b[2]) return 0;
    }
    if (count > 1) return 1;
    if (idx < count - 2) {
        const char* c = (const char*)(base + (idx + 2) * stride);
        n = stride;
        while (n >= 4) {
            if (*(const int*)b != *(const int*)c) return 0;
            b += 4; c += 4; n -= 4;
        }
        if (n > 0) {
            if (b[0] != c[0]) return 0;
            if (n > 1 && b[1] != c[1]) return 0;
            if (n > 2 && b[2] != c[2]) return 0;
        }
    }
    return 1;
}

// @ 0x007c5920
u8 FindMatch(int base, int p2, int p3, int stride, int mode) {
    int n = p3 & 0xffff;
    int idx = p2 & 0xffff;
    u8 k = 2;
    if (idx == n - 1) return 1;
    if (idx == n - 2) return 2;
    if (mode == 1) {
        while (idx + 2 < n) {
            if (!CompareRows(base, p3 & 0xffff, stride & 0xffff, idx + k))
                return k;
            k++;
            if (k == 0x80) return 0x80;
        }
        return k;
    } else {
        while (idx + 2 < n) {
            if (CompareRows(base, p3 & 0xffff, stride & 0xffff, idx + k))
                return k;
            k++;
            if (k == 0x80) return 0x80;
        }
        return k;
    }
}

// ---- viewport/rect descriptor initializer ----
struct SomeDesc {
    u8 b0, b1, b2, b3;   // +0
    u16 w4;              // +4
    u16 w6;              // +6
    u8  b8;              // +8
    u8  b9;              // +9
    u16 wa;              // +a
    u16 wc;              // +c
    u16 we;              // +e
    u16 w10;             // +10
    u8  b12;             // +12
    u8  b13;             // +13
    u32 d14;             // +14
    u32 d18;             // +18
    u32 d1c;             // +1c
};

// @ 0x007c5a40
void InitDesc(SomeDesc* d, u32 p2, u16 p3, u16 p4, u8 p5) {
    d->w4 = 0;
    d->w6 = 0;
    d->wa = 0;
    d->wc = 0;
    d->we = p3;
    d->b0 = 0;
    d->b1 = 0;
    d->b2 = 0;
    d->b8 = 0;
    d->w10 = p4;
    d->d14 = 0;
    d->d18 = 0;
    d->b12 = p5;
    d->b13 = 0x20;
    d->d1c = p2;
}
