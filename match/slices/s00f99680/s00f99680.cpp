// Slice s00f99680 -- SP::cTerrainSphere terrain-sphere VB/IB setup, editor view, control-map
// params, face-grid build and cloud type (0x00f99680 .. 0x00f9a590).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (movss/xorps/maxss/minss, x87 float copies, no EH frame)
#include "types.h"
#include <math.h>

void* __cdecl operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
void  __cdecl operator delete(void* p);                                                    // 0x00f47380

// ---- rdata float constants -------------------------------------------------------------
extern const float kOne;        // 0x01485720 == 1.0f
extern const float kEighth;     // 0x01486d94 == 0.125f
extern const float kNegEighth;  // 0x01490898 == -0.125f
extern const float kTwo;        // 0x01470f1c == 2.0f
extern const float kQuarter;    // 0x013f115c == 0.0625f
extern const float kHalf;       // 0x01471064 == 0.5f
extern const float kEps1;       // 0x013f11c8 == 1.0e-6f
extern const float kEps2;       // 0x014908cc == 2.0e-6f
extern const float kScale;      // 0x013ffd60 == 0.002f

// ---- RenderWare vertex / index buffers -------------------------------------------------
struct RVtxDesc {
    uint8_t pad0[0xf];
    uint8_t mStride;                // +0x0f
};
struct RVtxBuf {
    RVtxDesc* mpDesc;               // +0x00
    uint32_t  mUnused;              // +0x04
    uint32_t  mBase;                // +0x08
    uint32_t  mNumVerts;            // +0x0c
    void* D3D9Lock(uint32_t a, uint32_t b, uint32_t c);   // 0x011f3620 (ret 0xc)
    void* Unlock();                                       // 0x011f36a0
};
struct RIdxBuf {
    int   Lock(uint32_t a, void** out);                   // 0x011f4f20 (ret 8)
    void* Unlock(void** out);                             // 0x011f4fd0 (ret 4)
};
void* __cdecl GetVertexDescriptor(const char* name);      // 0x007c3af0
void* __cdecl CreateVertexBuffer(void* desc, int count, int a, int b);                 // 0x00762b70
void* __cdecl CreateIndexBuffer(void* desc, int a, int count, int b, int c, int d);    // 0x00762c60
extern void* g_vdStrt2f;        // 0x016c9e70
extern void* g_vdMain;          // 0x016c9e74
extern void* g_vdCombo;         // 0x016c9e78
extern RVtxBuf* g_vb;           // 0x016c9e3c
extern RIdxBuf* g_ib;           // 0x016c9e34
extern void* g_vbSkirt;         // 0x016c9e6c
extern char  g_idxDesc;         // 0x015d07b0

// ---- generic vtable helpers ------------------------------------------------------------
#define VIRT(n) virtual void v##n();

struct IRefObj32 {              // Release = slot 1, SetMode(int) = slot 3, Update() = slot 31
    virtual void AddRef();      // +0x00
    virtual void Release();     // +0x04
    VIRT(2)
    virtual void SetMode(int);  // +0x0c
    VIRT(4) VIRT(5) VIRT(6) VIRT(7) VIRT(8) VIRT(9) VIRT(10) VIRT(11) VIRT(12)
    VIRT(13) VIRT(14) VIRT(15) VIRT(16) VIRT(17) VIRT(18) VIRT(19) VIRT(20)
    VIRT(21) VIRT(22) VIRT(23) VIRT(24) VIRT(25) VIRT(26) VIRT(27) VIRT(28)
    VIRT(29) VIRT(30)
    virtual void Update();      // +0x7c
};

struct IEffects {               // Remove(int) = slot 20 (+0x50)
    VIRT(0) VIRT(1) VIRT(2) VIRT(3) VIRT(4) VIRT(5) VIRT(6) VIRT(7) VIRT(8)
    VIRT(9) VIRT(10) VIRT(11) VIRT(12) VIRT(13) VIRT(14) VIRT(15) VIRT(16)
    VIRT(17) VIRT(18) VIRT(19)
    virtual void Remove(int);   // +0x50
};
IEffects* __cdecl EffectsManager();          // 0x0067ddd0

struct IManager67 {             // Update(int) = slot 31 (+0x7c)
    VIRT(0) VIRT(1) VIRT(2) VIRT(3) VIRT(4) VIRT(5) VIRT(6) VIRT(7) VIRT(8)
    VIRT(9) VIRT(10) VIRT(11) VIRT(12) VIRT(13) VIRT(14) VIRT(15) VIRT(16)
    VIRT(17) VIRT(18) VIRT(19) VIRT(20) VIRT(21) VIRT(22) VIRT(23) VIRT(24)
    VIRT(25) VIRT(26) VIRT(27) VIRT(28) VIRT(29) VIRT(30)
    virtual void Update(int);   // +0x7c
};
IManager67* __cdecl GetManager67();          // 0x0067dd50

// ---- terrain map set / planet / state manager ------------------------------------------
struct cTerrainMapSet {
    float GetHeightAt(const float* pos);     // 0x00f927c0 (ret 4)
};
struct cPlanetData {
    uint8_t pad0[0x34];
    float f34;                               // +0x34
    float f38;                               // +0x38
    float f3c;                               // +0x3c
};
struct cTerrainStateMgr {
    uint8_t pad0[0x5b0];
    void* mpProps;                           // +0x5b0
};

// ---- property objects ------------------------------------------------------------------
struct Property {
    void*    mpData;                         // +0x00
    uint32_t pad4[3];                        // +0x04
    uint8_t  mFlags;                         // +0x10
    uint8_t  pad11;
    uint16_t mType;                          // +0x12
    int* GetInt();                           // 0x0041e990
};
extern float g_propDefault;                  // 0x015d1168

// UpdateControlMapParams: slot 0, HasProperty at +0x1c, GetProperty at +0x28, Release at +4.
struct IPropListA {
    VIRT(0)
    virtual void Release();                  // +0x04
    VIRT(2) VIRT(3) VIRT(4) VIRT(5) VIRT(6)
    virtual bool HasProperty(uint32_t id);              // +0x1c
    VIRT(8) VIRT(9)
    virtual Property* GetProperty(uint32_t id);         // +0x28
};
// SetCloudType: GetProperty(id,&out) at +0x24.
struct IPropListB {
    VIRT(0) VIRT(1) VIRT(2) VIRT(3) VIRT(4) VIRT(5) VIRT(6) VIRT(7) VIRT(8)
    virtual bool GetProperty(uint32_t id, Property** out);   // +0x24
};

struct cWeatherManager {                     // only the two cloud-type setters are used here
    void SetCloudTypeA(int v);               // 0x00fc2f10
    void SetCloudTypeB(int v);               // 0x00fc2f30
};

// ---- property-value extraction (inlined at every call site) ----------------------------
static __forceinline const float* PropPtr(Property* pr)
{
    uint16_t t = pr->mType;
    if (t == 0xd || t == 0x10) {
        if (pr->mFlags & 0x30)
            return (const float*)pr->mpData;       // value object holds a pointer
        return (const float*)((t != 0) ? (void*)pr : (void*)0);
    }
    return &g_propDefault;
}

// ---- editor / viewer -------------------------------------------------------------------
struct cViewer {                             // 0x174 bytes
    uint32_t mPad[0x174 / 4];
    cViewer();                               // 0x007c3f70
    void Init(int arg);                      // 0x007c4dd0
    void Shutdown();                         // 0x007c3ba0
    void Destroy();                          // 0x007c4000
    void SetViewScale(float w, float h);     // 0x007c4b00 (ret 8)
    void SetNear(float f);                   // 0x007c4ba0 (ret 4)
    void SetFar(float f);                    // 0x007c4bc0 (ret 4)
};
struct cEditor {                             // the in-game terrain editor singleton
    bool IsActive();                         // 0x00f699b0
};
void* __cdecl TerrainEditor();               // 0x00f48a70

// ---- job -------------------------------------------------------------------------------
struct cJob {
    int Cancel(int a);                       // 0x00692400 (ret 4)
    int Release();                           // 0x00690120
};
struct cDirectPropertyList {
    bool GetDescription(uint32_t id);        // 0x006a25a0 (ret 4)
};
extern cDirectPropertyList* g_AppProperties;  // 0x015fd918

// ---- geometry rects --------------------------------------------------------------------
struct Rect {
    float left, top, right, bottom;
};
struct float3 {
    float x, y, z;
};

// ---- the terrain sphere ----------------------------------------------------------------
struct cTerrainSphere {
    // vtable: 3=GetMapSet, 4=end-flush, 6=push vertex, 7=push normal, 12=query,
    //         15=begin, 19=?, 20=begin-strip, 25=index, 31=end
    VIRT(0) VIRT(1) VIRT(2)
    virtual cTerrainMapSet* GetMapSet();     // +0x0c
    virtual void v04();                      // +0x10
    VIRT(5)
    virtual void v06(const float3* v);       // +0x18
    virtual void v07(const float3* n);       // +0x1c
    VIRT(8) VIRT(9) VIRT(10) VIRT(11)
    virtual bool v12();                      // +0x30
    VIRT(13) VIRT(14)
    virtual bool v15(int a);                 // +0x3c
    VIRT(16) VIRT(17) VIRT(18)
    virtual bool v19(int a);                 // +0x4c
    virtual void v20(int a);                 // +0x50
    VIRT(21) VIRT(22) VIRT(23) VIRT(24)
    virtual void v25(int a, int b);          // +0x64
    VIRT(26) VIRT(27) VIRT(28) VIRT(29) VIRT(30)
    virtual void v31();                      // +0x7c

    uint32_t mPad04;                         // +0x04
    uint32_t mPad08;                         // +0x08
    IRefObj32* mpEditor;                     // +0x0c
    int      mEd10;                          // +0x10
    int      mEd14;                          // +0x14
    int      mEd18;                          // +0x18
    int      mEd1C;                          // +0x1c
    cViewer* mpViewer;                       // +0x20
    uint8_t  mEditorOn;                      // +0x24
    uint8_t  mPad25[3];                      // +0x25
    IPropListB* mpConfig28;                  // +0x28
    cPlanetData* mpPlanet;                   // +0x2c
    uint8_t  mPad30[0x1d4 - 0x30];
    int      mDim;                           // +0x1d4
    uint8_t  mPad1d8[0x20c - 0x1d8];
    cTerrainStateMgr* mpStateMgr;            // +0x20c
    cWeatherManager*  mpWeather;             // +0x210
    uint8_t  mPad214[0x34c - 0x214];
    float    mPropA;                         // +0x34c
    float    mPropB;                         // +0x350
    float    mPropC;                         // +0x354
    float    mPropD;                         // +0x358
    float    mPropE;                         // +0x35c
    uint8_t  mPad360[0x36c - 0x360];
    int      mFaceBase;                      // +0x36c
    uint8_t  mFlag370;                       // +0x370
    uint8_t  mPad371[3];                     // +0x371
    Rect     mRects[24];                     // +0x374 (4 groups x 6 rects)
    uint8_t  mFlag4F4;                       // +0x4f4
    uint8_t  mPad4f5[0x894 - 0x4f5];
    cJob*    mpJob894;                       // +0x894
    uint8_t  mPad898[0x8a4 - 0x898];
    int      mJobId8a4;                      // +0x8a4
    uint8_t  mPad8a8[0x8d8 - 0x8a8];
    IRefObj32* mpP8d8;                       // +0x8d8
    IRefObj32* mpP8dc;                       // +0x8dc
    IRefObj32* mpP8e0;                       // +0x8e0

    void InitializeVBInfoArray();            // 0x00f99680
    void EditorTeardown();                   // 0x00f998f0
    void JobTeardown();                      // 0x00f99980
    bool IsEditorReady();                    // 0x00f999e0
    void MarkFaceDirty(int face, const float* rect);   // 0x00f99ac0 (ret 8)
    void FUN_00f99ba0(int face);             // 0x00f99ba0 (ret 4)
    void UpdateControlMapParams();           // 0x00f99d20
    void FUN_00f99f20(IRefObj32* p, int a, int b, int* v);  // 0x00f99f20 (ret 0x10)
    void FUN_00f99ff0();                     // 0x00f99ff0
    void FUN_00f9a040(cTerrainSphere* p, void* arg1, float step, bool useHeight);  // 0x00f9a040 (ret 0x10)
    void SetCloudType();                     // 0x00f9a590
};

// ----------------------------------------------------------------------------------------
// @ 0x00f99680
void cTerrainSphere::InitializeVBInfoArray()
{
    bool hasDesc = g_AppProperties->GetDescription(0x563886e);
    g_vdStrt2f = GetVertexDescriptor("STRT2F");
    g_vdMain = GetVertexDescriptor(hasDesc ? "V4BC4B" : "V4B");
    g_vdCombo = GetVertexDescriptor(hasDesc ? "V4BC4BSTRT2F" : "V4BSTRT2F");

    int dim = mDim;
    int n = dim + 3;
    int idxCount = 6 * dim * dim;

    RVtxBuf* vb = (RVtxBuf*)CreateVertexBuffer(g_vdStrt2f, n * n, 0, 0);
    g_vb = vb;
    uint8_t stride = vb->mpDesc->mStride;
    float* verts = (float*)vb->D3D9Lock(2, stride * vb->mBase, stride * vb->mNumVerts);
    g_vb = verts ? vb : 0;
    if (g_vb) {
        float inv = kOne / (float)dim;
        float lo = inv * kNegEighth;
        float hi = inv * kEighth + kOne;
        for (int i = 0; i < n; i++) {
            float tv = (float)(i - 1) / (float)dim;
            tv = tv < lo ? lo : tv;
            tv = tv > hi ? hi : tv;
            for (int j = 0; j < n; j++) {
                float tu = (float)(j - 1) / (float)dim;
                tu = tu < lo ? lo : tu;
                tu = tu > hi ? hi : tu;
                verts[0] = tu;
                verts[1] = tv;
                verts = (float*)((char*)verts + stride);
            }
        }
        g_vb->Unlock();
    }

    g_ib = (RIdxBuf*)CreateIndexBuffer(&g_idxDesc, 1, idxCount, 8, 4, 0);
    void* lock = 0;
    if (g_ib->Lock(2, &lock)) {
        uint16_t* p = (uint16_t*)lock;
        for (int i = 1; i <= dim; i++) {
            int base = (uint16_t)(i + n);
            for (int k = 0; k < dim; k++) {
                p[0] = (uint16_t)(base + 1);
                p[1] = (uint16_t)(base + n + 1);
                p[2] = (uint16_t)(base + n);
                p[3] = (uint16_t)(base + n);
                p[4] = (uint16_t)(base);
                p[5] = (uint16_t)(base + 1);
                p += 6;
                base += n;
            }
        }
        g_ib->Unlock(&lock);
    }

    g_vbSkirt = CreateVertexBuffer(g_vdStrt2f, 3, 0, 0);
}

// @ 0x00f998f0
void cTerrainSphere::EditorTeardown()
{
    if (mpP8e0) mpP8e0->SetMode(0);
    mpP8d8->SetMode(2);
    EffectsManager()->Remove(0xd0a45522);
    if (mpP8d8) {
        IRefObj32* p = mpP8d8;
        mpP8d8 = 0;
        p->Release();
    }
    if (mpP8dc) mpP8dc->Update();
    if (mpP8dc) {
        IRefObj32* p = mpP8dc;
        mpP8dc = 0;
        p->Release();
    }
}

// @ 0x00f99980
void cTerrainSphere::JobTeardown()
{
    if (mJobId8a4 != -1)
        GetManager67()->Update(mJobId8a4);
    mJobId8a4 = -1;
    if (mpJob894) {
        mpJob894->Cancel(1);
        if (mpJob894) {
            cJob* j = mpJob894;
            mpJob894 = 0;
            j->Release();
        }
    }
}

// @ 0x00f999e0
bool cTerrainSphere::IsEditorReady()
{
    if (!((cEditor*)TerrainEditor())->IsActive())
        return false;
    if (v19(7))
        return false;
    if (mFlag370 != 0)
        return false;
    if (!v12())
        return false;
    if (!mFlag4F4)
        return false;
    for (int i = 0; i < 6; i++) {
        const Rect& a = mRects[i];
        if (a.left != a.right && a.top != a.bottom) return false;
        const Rect& b = mRects[6 + i];
        if (b.left != b.right && b.top != b.bottom) return false;
        const Rect& c = mRects[12 + i];
        if (c.left != c.right && c.top != c.bottom) return false;
        const Rect& d = mRects[18 + i];
        if (d.left != d.right && d.top != d.bottom) return false;
    }
    return true;
}

// @ 0x00f99ac0
void cTerrainSphere::MarkFaceDirty(int face, const float* rect)
{
    Rect& r = mRects[6 + face - 6 * mFaceBase];
    if (r.left != r.right && r.top != r.bottom) {
        r.left   = r.left   < rect[0] ? r.left   : rect[0];
        r.top    = r.top    < rect[1] ? r.top    : rect[1];
        r.right  = r.right  > rect[2] ? r.right  : rect[2];
        r.bottom = r.bottom > rect[3] ? r.bottom : rect[3];
    } else {
        r.left   = rect[0];
        r.top    = rect[1];
        r.right  = rect[2];
        r.bottom = rect[3];
    }
}

// @ 0x00f99ba0
void cTerrainSphere::FUN_00f99ba0(int face)
{
    if (face < 0) {
        Rect* base = (Rect*)((char*)this - 6 * mFaceBase * 0x10 + 0x3d4);
        for (int k = 0; k < 6; k++) {
            base[k].left   = 0.0f;
            base[k].top    = 0.0f;
            base[k].right  = kOne;
            base[k].bottom = kOne;
        }
    } else {
        Rect& r = mRects[6 + face - 6 * mFaceBase];
        r.left   = 0.0f;
        r.top    = 0.0f;
        r.right  = kOne;
        r.bottom = kOne;
    }
}

// @ 0x00f99d20
void cTerrainSphere::UpdateControlMapParams()
{
    IPropListA* p = (IPropListA*)mpStateMgr->mpProps;
    if (p) p->v0();
    if (p->HasProperty(0xaf5d98bd))
        mPropA = *PropPtr(p->GetProperty(0xaf5d98bd));
    if (p->HasProperty(0xbc2b0f4a))
        mPropB = *PropPtr(p->GetProperty(0xbc2b0f4a));
    if (p->HasProperty(0x931d52b2))
        mPropC = *PropPtr(p->GetProperty(0x931d52b2));
    if (p->HasProperty(0x93cab73f))
        mPropD = *PropPtr(p->GetProperty(0x93cab73f));
    if (p->HasProperty(0x1a2b977))
        mPropE = *PropPtr(p->GetProperty(0x1a2b977));
    p->Release();
}

// @ 0x00f99f20
void cTerrainSphere::FUN_00f99f20(IRefObj32* p, int a, int b, int* v)
{
    if (mEditorOn) return;
    IRefObj32* old = mpEditor;
    if (p != old) {
        if (p) p->AddRef();
        mpEditor = p;
        if (old) old->Release();
    }
    mEd10 = a;
    mEd14 = b;
    mEd18 = v[0];
    mEd1C = v[1];
    mpViewer = new("Graphics", 0, 0, 0, 0) cViewer;
    mpViewer->Init(1);
    mpViewer->SetViewScale(kHalf, kHalf);
    mpViewer->SetNear(1.0f);
    mpViewer->SetFar(kTwo);
    mEditorOn = 1;
}

// @ 0x00f99ff0
void cTerrainSphere::FUN_00f99ff0()
{
    if (!mEditorOn) return;
    if (mpViewer) {
        mpViewer->Shutdown();
        cViewer* v = mpViewer;
        if (v) {
            v->Destroy();
            operator delete(v);
        }
        mpViewer = 0;
    }
    if (mpEditor) {
        IRefObj32* p = mpEditor;
        mpEditor = 0;
        p->Release();
    }
    mEditorOn = 0;
}

// @ 0x00f9a040
void cTerrainSphere::FUN_00f9a040(cTerrainSphere* p, void* arg1, float step, bool useHeight)
{
    float negStep = -step;
    float scale = step * kTwo * kQuarter;

    p->v2();                 // (slot 3) no-arg begin on the geometry object
    p->v15((int)(size_t)arg1);
    p->v19(0);

    for (int face = 0; face < 6; face++) {
        float coord[3];
        int A, B, C;
        switch (face) {
        case 1:  coord[0] = step;    coord[1] = negStep; coord[2] = negStep; A = 1; B = 0; C = 2; break;
        case 2:  coord[0] = negStep; coord[1] = negStep; coord[2] = step;    A = 0; B = 2; C = 1; break;
        case 3:  coord[0] = negStep; coord[1] = negStep; coord[2] = negStep; A = 2; B = 0; C = 1; break;
        case 4:  coord[0] = negStep; coord[1] = step;    coord[2] = negStep; A = 0; B = 1; C = 2; break;
        case 5:  coord[0] = negStep; coord[1] = negStep; coord[2] = negStep; A = 0; B = 1; C = 2; break;
        default: coord[0] = negStep; coord[1] = negStep; coord[2] = negStep; A = 0; B = 2; C = 1; break;
        }

        float perm[3];
        for (int i = 0; i <= 16; i++) {
            float tv = (float)i * scale + coord[A];
            if (i == 0) {
                tv = tv + kEps1;
                perm[A] = tv;
            } else if (i == 16) {
                tv = tv - kEps2;
                perm[A] = tv;
            } else {
                perm[A] = tv;
            }
            perm[B] = coord[B];
            for (int j = 0; j <= 16; j++) {
                float tz = (float)j * scale + coord[C];
                if (j == 0) {
                    tz = tz + kEps1;
                    perm[C] = tz;
                } else if (j == 16) {
                    tz = tz - kEps2;
                    perm[C] = tz;
                } else {
                    perm[C] = tz;
                }
                float len = sqrtf(perm[0] * perm[0] + perm[1] * perm[1] + perm[2] * perm[2]);
                float inv = kOne / len;
                float3 n;
                n.x = perm[0] * inv;
                n.y = perm[1] * inv;
                n.z = perm[2] * inv;
                float3 pos;
                if (useHeight) {
                    float h = GetMapSet()->GetHeightAt(&n.x);
                    float base = mpPlanet->f3c * mpPlanet->f38 + mpPlanet->f34;
                    float d = (base > h) ? base : h;
                    float s = d * step * kScale;
                    pos.x = n.x * s;
                    pos.y = n.y * s;
                    pos.z = n.z * s;
                } else {
                    pos.x = n.x * step;
                    pos.y = n.y * step;
                    pos.z = n.z * step;
                }
                p->v06(&pos);
                p->v07(&n);
            }
        }

        int vbase = face * 0x121 + 1;
        for (int ii = 0; ii < 0x10; ii++) {
            int idx = vbase;
            for (int jj = 0; jj < 0x10; jj++) {
                p->v20(4);
                if (face == 0 || face == 4) {
                    p->v25(3, idx + 0x10);
                    p->v25(3, idx - 1);
                    p->v25(3, idx);
                    p->v25(3, idx);
                    p->v25(3, idx + 0x11);
                    p->v25(3, idx);
                } else {
                    p->v25(3, idx);
                    p->v25(3, idx - 1);
                    p->v25(3, idx + 0x10);
                    p->v25(3, idx + 0x10);
                    p->v25(3, idx + 0x11);
                    p->v25(3, idx + 0x10);
                }
                p->v31();
                idx++;
            }
            vbase += 0x11;
        }
    }
    p->v04();
}

// @ 0x00f9a590
void cTerrainSphere::SetCloudType()
{
    IPropListB* p = mpConfig28;
    if (p) {
        Property* prop;
        if (p->GetProperty(0x3b4de49, &prop)) {
            if (prop->mType == 9) {
                int n = *prop->GetInt();
                mpWeather->SetCloudTypeA(n);
            }
        }
    }
    p = mpConfig28;
    if (p) {
        Property* prop;
        if (p->GetProperty(0x60a0a5c, &prop)) {
            if (prop->mType == 9) {
                int* v = prop->GetInt();
                mpWeather->SetCloudTypeB(*v);
            }
        }
    }
}
