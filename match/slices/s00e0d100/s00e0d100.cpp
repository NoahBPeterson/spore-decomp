// Slice s00e0d100: cSPUIMinimapWin camera-arrow drawing (MSVC 2008 SP1, /O2 /arch:SSE [/fp:fast]).
// Retail offsets differ from the 2008 PDB; raw offsets are used.
#include <math.h>

struct Vec3 { float x, y, z; };
struct Vec2 { float x, y; };

struct Image { char pad[0x1c]; int mW; int mH; };

struct Vertex2D {                       // 0x14 bytes
    float x, y;
    unsigned int color;
    float u, v;
};

struct Target2D {                       // returned by RenderContext::Begin2D
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20();
    virtual void DrawQuads(Vertex2D* v, int count, Image* img);          // +0x54, ret 0xc
};

struct RenderContext {
    Target2D* Begin2D(int);             // 0x95bc10
    void End2D();                       // 0x95bb20
};

struct MapSet;
struct ITerrain {
    virtual int AddRef();
    virtual int Release();
    virtual void* GetPropertyList();
    virtual MapSet* GetTerrainMapSet();                                  // +0xc
};

struct PlanetModel {
    char pad[0x24]; ITerrain* mpTerrain;
    Vec3* DirectionToSurfacePosition(const Vec3* pDir, Vec3* pOut);     // 0xb815a0 (thiscall ret 8)
};
PlanetModel* GetPlanetModel();                                           // 0xb3d350 (SP::PlanetModel)
extern "C" unsigned int GetCurrentGameMode();                            // 0xb5b800 (SP::GetCurrentGameMode)
// terrain-map-set projection to texture UV (cdecl, returns its out pointer)
extern "C" Vec2* ProjectToUV(Vec2* out, MapSet* ms, const Vec3* pos, const Vec3* a, const Vec3* b, float scale, int flag); // 0x00e0b580

struct MinimapWin {
    char pad0[0x23c];
    int mW;                             // +0x23c
    int mH;                             // +0x240
    char pad1[0x250 - 0x244];
    Image* mpImage;                     // +0x250
    char pad2[0x304 - 0x254];
    Vec3 mCenter;                       // +0x304
    Vec3 mUp;                           // +0x310
    char pad3[0x338 - 0x31c];
    Vec3 mAxisA;                        // +0x338
    Vec3 mAxisB;                        // +0x344
    float mScale;                       // +0x350

    bool ProjectCenter(const Vec3* pos, Vec2* out, int flag);           // 0xe0bcb0 (thiscall ret 0xc)
    float RemapX(float x, float y);                                      // 0xe0aa80 (thiscall ret 8, float in ST0)
    bool DrawCameraArrow(RenderContext* ctx, int unused);
};

// pick the candidate among x-1, x, x+1 that is nearest to ref (map wraps horizontally)
static __forceinline float WrapNearest(float x, float ref) {
    float c = x - 1.0f;
    if (fabs(x - ref) <= fabs(c - ref)) {
        c = x;
        if (fabs((x + 1.0f) - ref) < fabs(x - ref)) c = x + 1.0f;
    }
    return c;
}

// @ 0x00e0d2e0  cSPUIMinimapWin (camera arrow draw)
bool MinimapWin::DrawCameraArrow(RenderContext* ctx, int unused) {
    const Vec3* pc = &mCenter;
    if ((pc->x * pc->x + pc->y * pc->y) + pc->z * pc->z <= 0.1f) return true;
    if ((mUp.x * mUp.x + mUp.y * mUp.y) + mUp.z * mUp.z <= 0.9f) return true;

    Target2D* tgt = ctx->Begin2D(0);
    Vertex2D v[4];
    v[0].x = 0.0f; v[0].y = 0.0f; v[0].color = 0xffffffff; v[0].u = 0.0f; v[0].v = 0.0f;
    v[1].color = 0xffffffff; v[1].u = 1.0f; v[1].v = 0.0f;
    v[2].color = 0xffffffff; v[2].u = 1.0f; v[2].v = 1.0f;
    v[3].color = 0xffffffff; v[3].u = 0.0f; v[3].v = 1.0f;

    Vec2 p;
    ProjectCenter(pc, &p, 0);

    float dx, dy;                       // (uninitialised in the original when there is no terrain)
    PlanetModel* pm = GetPlanetModel();
    ITerrain* ter = pm ? pm->mpTerrain : 0;
    if (ter) {
        Vec2 t0, t1, t2;
        Vec2 tmp;
        t0 = *ProjectToUV(&tmp, ter->GetTerrainMapSet(), pc, &mAxisA, &mAxisB, mScale, 0);
        Vec3 q;
        q.x = mUp.x * 0.3f + pc->x;
        q.y = pc->y + mUp.y * 0.3f;
        q.z = pc->z + mUp.z * 0.3f;
        t1 = *ProjectToUV(&tmp, ter->GetTerrainMapSet(), &q, &mAxisA, &mAxisB, mScale, 0);
        Vec3 r;
        r.x = pc->x - mUp.x * 0.3f;
        r.y = pc->y - mUp.y * 0.3f;
        r.z = pc->z - mUp.z * 0.3f;
        t2 = *ProjectToUV(&tmp, ter->GetTerrainMapSet(), &r, &mAxisA, &mAxisB, mScale, 0);

        float rx, ry;
        unsigned int mode = GetCurrentGameMode();
        bool plain = true;
        if (mode == 0x1654c05 || mode == 0x1654c04) {
            t1.x = WrapNearest(t1.x, t0.x);
            t2.x = WrapNearest(t2.x, t0.x);
            float d1 = sqrt((t1.x - t0.x) * (t1.x - t0.x) + (t1.y - t0.y) * (t1.y - t0.y));
            float d2 = sqrt((t0.x - t2.x) * (t0.x - t2.x) + (t0.y - t2.y) * (t0.y - t2.y));
            if (!(d1 < d2)) {
                float mx = t0.x * 2.0f;
                float my = t0.y * 2.0f - t2.y;
                float cy = my;
                if (cy <= 0.0f) cy = 0.0f;
                if (0.999f <= cy) cy = 0.999f;
                float yy = (float)mH * cy;
                ry = my * (float)mH;
                rx = RemapX((float)mW * (mx - t2.x), yy);
                plain = false;
            }
        }
        if (plain) {
            ry = (float)mH * t1.y;
            rx = RemapX((float)mW * t1.x, ry);
        }
        dy = ry - p.y;
        dx = rx - p.x;
    }
    Image* img = mpImage;
    float nx = -dx;
    float s1 = ((float)img->mH / sqrt(dx * dx + dy * dy)) * 0.4f;
    float A = dx * s1, B = dy * s1;
    float s2 = ((float)img->mW / sqrt(nx * nx + dy * dy)) * 0.4f;
    float P = dy * s2, Q = nx * s2;
    v[0].x = (p.x + A) - P;  v[0].y = (B + p.y) - Q;
    v[1].x = (P + p.x) + A;  v[1].y = (Q + B) + p.y;
    v[2].x = ((p.x - A) + P); v[2].y = Q + (p.y - B);
    v[3].x = ((p.x - A) - P); v[3].y = (p.y - B) - Q;
    tgt->DrawQuads(v, 1, img);
    ctx->End2D();
    return true;
}

// ===========================================================================
// Minimap feedback icons (retail offsets differ from the 2008 PDB).
// ===========================================================================

typedef unsigned char uint8_t;
typedef int int32_t;
typedef unsigned int uint32_t;

struct IMinimapIcon;                     // icon / window object drawn on the minimap

struct IMinimapIcon {                    // vtable slots used by this slice
    virtual void s00();                  // +0x00
    virtual void s04();                  // +0x04
    virtual void s08();                  // +0x08
    virtual void s0c();                  // +0x0c
    virtual IMinimapIcon* s10();         // +0x10 parent
    virtual void s14();                  // +0x14
    virtual void s18();                  // +0x18
    virtual void s1c();                  // +0x1c
    virtual void s20();                  // +0x20
    virtual void s24();                  // +0x24
    virtual bool s28();                  // +0x28 is-visible
    virtual void s2c();                  // +0x2c
    virtual void s30();                  // +0x30
    virtual void s34();                  // +0x34
    virtual const float* s38();          // +0x38 quad (4 floats)
    virtual void s3c();                  // +0x3c
    virtual void s40();                  // +0x40
    virtual void s44();                  // +0x44
    virtual void s48();                  // +0x48
    virtual void s4c();                  // +0x4c
    virtual void s50();                  // +0x50
    virtual void s54();                  // +0x54
    virtual void s58();                  // +0x58
    virtual void s5c();                  // +0x5c
    virtual void s60();                  // +0x60
    virtual void s64();                  // +0x64
    virtual void s68();                  // +0x68
    virtual void s6c(float* pQuad);      // +0x6c set quad
    virtual void s70();                  // +0x70
    virtual void s74();                  // +0x74
    virtual void s78();                  // +0x78
    virtual void s7c(int a, int b);      // +0x7c set visible
    virtual void s80();                  // +0x80
    virtual void s84();                  // +0x84
    virtual void s88();                  // +0x88
    virtual void s8c();                  // +0x8c
    virtual void s90();                  // +0x90
    virtual void s94();                  // +0x94
    virtual void s98();                  // +0x98
    virtual void s9c();                  // +0x9c
    virtual void sa0();                  // +0xa0
    virtual void sa4();                  // +0xa4
    virtual void sa8();                  // +0xa8
    virtual void sac();                  // +0xac
    virtual void sb0();                  // +0xb0
    virtual void sb4();                  // +0xb4
    virtual void sb8();                  // +0xb8
    virtual void sbc();                  // +0xbc
    virtual void sc0(Vec2 size, float* pOut);   // +0xc0
    virtual void sc4();                  // +0xc4
    virtual void sc8();                  // +0xc8
    virtual void scc();                  // +0xcc
    virtual void sd0();                  // +0xd0
    virtual void sd4();                  // +0xd4
    virtual void sd8();                  // +0xd8
    virtual void sdc();                  // +0xdc
    virtual void se0(IMinimapIcon* pIcon);      // +0xe0 detach parent
    virtual void se4();                  // +0xe4
    virtual void se8();                  // +0xe8
    virtual void sec(IMinimapIcon* pIcon);      // +0xec attach
    virtual IMinimapIcon* sf0(uint32_t id, int flag);   // +0xf0 lookup icon by id
};

struct IDirectionProvider {              // subobject holding the surface direction
    virtual void d00();                  // +0x00
    virtual void d04();                  // +0x04
    virtual void d08();                  // +0x08
    virtual void d0c();                  // +0x0c
    virtual void d10();                  // +0x10
    virtual void d14();                  // +0x14
    virtual void d18();                  // +0x18
    virtual void d1c();                  // +0x1c
    virtual void d20();                  // +0x20
    virtual void d24();                  // +0x24
    virtual void d28();                  // +0x28
    virtual const Vec3* GetDirection();  // +0x2c
};

struct IMinimapTargetA {                 // feedback target, direction subobject at +0x34
    virtual void a00();                  // +0x00
    virtual void a04();                  // +0x04
    virtual void a08();                  // +0x08
    virtual void* Find(uint32_t id);     // +0x0c
    char pad_010[0x24];                  // +0x10
    IDirectionProvider mDirection;       // +0x34
};

struct IMinimapTargetB {                 // feedback target, direction subobject at +0xc0
    virtual void b00();                  // +0x00
    virtual void b04();                  // +0x04
    virtual void b08();                  // +0x08
    virtual void* Find(uint32_t id);     // +0x0c
    char pad_010[0xb0];                  // +0x10
    IDirectionProvider mDirection;       // +0xc0
};

struct IMinimapTargetC {                 // feedback target exposing its event mode
    virtual void c00();                  // +0x00
    virtual void c04();                  // +0x04
    virtual void c08();                  // +0x08
    virtual void* Find(uint32_t id);     // +0x0c
    virtual void c10();                  // +0x10
    virtual void c14();                  // +0x14
    virtual void c18();                  // +0x18
    virtual void c1c();                  // +0x1c
    virtual void* GetMode();             // +0x20
};

struct IMinimapView {                    // current minimap view
    virtual void v00();                  // +0x00
    virtual void v04();                  // +0x04
    virtual void v08();                  // +0x08
    virtual void v0c();                  // +0x0c
    virtual void v10();                  // +0x10
    virtual void v14();                  // +0x14
    virtual void v18();                  // +0x18
    virtual float GetAngle();            // +0x1c
    virtual void* GetMode();             // +0x20
};

struct IWindowManager {                  // SP::WindowManager()
    virtual void w00();                  // +0x00
    virtual void w04();                  // +0x04
    virtual void w08();                  // +0x08
    virtual void w0c();                  // +0x0c
    virtual void w10();                  // +0x10
    virtual void w14();                  // +0x14
    virtual void w18();                  // +0x18
    virtual void w1c();                  // +0x1c
    virtual void w20();                  // +0x20
    virtual void w24();                  // +0x24
    virtual void w28();                  // +0x28
    virtual void w2c();                  // +0x2c
    virtual void w30();                  // +0x30
    virtual void w34();                  // +0x34
    virtual void w38();                  // +0x38
    virtual void w3c();                  // +0x3c
    virtual void w40();                  // +0x40
    virtual void w44();                  // +0x44
    virtual IMinimapView* GetView(int which);   // +0x48
};

struct IAppAccess {                      // SP::App()
    virtual void a00();                  // +0x00
    virtual void a04();                  // +0x04
    virtual void a08();                  // +0x08
    virtual void a0c();                  // +0x0c
    virtual void a10();                  // +0x10
    virtual void a14();                  // +0x14
    virtual void a18();                  // +0x18
    virtual void a1c();                  // +0x1c
    virtual void a20();                  // +0x20
    virtual void a24();                  // +0x24
    virtual void a28();                  // +0x28
    virtual void a2c();                  // +0x2c
    virtual void a30();                  // +0x30
    virtual void a34();                  // +0x34
    virtual void* GetModeTag();          // +0x38
};

struct IMapSetProjection {               // ITerrain slot +0x0c is variadic (0 or 4 args)
    virtual void p00();                  // +0x00
    virtual void p04();                  // +0x04
    virtual void p08();                  // +0x08
    virtual Vec2* Project(Vec2* pUV, const Vec3* pA, const Vec3* pB, float scale);  // +0x0c
};

struct MinimapEventNode;                 // eastl rbtree node (event id + feedback event)

struct MinimapEventTree {                // eastl::rbtree keyed by the event id
    uint32_t          mSize;             // +0x00 (not touched here)
    MinimapEventNode* mpRoot;            // +0x04 anchor: parent (end iterator)
    MinimapEventNode* mpBegin;           // +0x08 anchor: leftmost node
    MinimapEventNode* mpEnd;             // +0x0c anchor: rightmost node
    uint32_t          mColor;            // +0x10 anchor: colour
    MinimapEventNode* find(MinimapEventNode** pFound, const void* pKey);  // 0x00e5c780
};

struct cFeedbackEvent;                   // feedback event payload (only referenced here)

struct AutoRefCountEvent {               // EA::AutoRefCount<cFeedbackEvent> (4 bytes)
    cFeedbackEvent* mpEvent;             // +0x00
};

struct MinimapEventNode {
    MinimapEventNode* mpParent;          // +0x00
    MinimapEventNode* mpLeft;            // +0x04
    MinimapEventNode* mpRight;           // +0x08
    uint32_t          mColor;            // +0x0c
    uint32_t          mKey;              // +0x10
    AutoRefCountEvent mEvent;            // +0x14
    Vec3              mPos;              // +0x18 direction of the event on the surface
    uint32_t          mFlags;            // +0x24
    IMinimapTargetA*  mpTarget;          // +0x28
    float             mTime;             // +0x2c
    uint32_t          mState;            // +0x30
};

struct cMinimapOverlay {                 // cSPUIMinimapWin (retail layout)
    char             pad_000[4];         // +0x000
    IMinimapIcon     mWindow;            // +0x004 polymorphic window subobject
    char             pad_008[0x230];     // +0x008
    uint8_t          mIconsHidden;       // +0x238
    char             pad_239[3];         // +0x239
    int32_t          mW;                 // +0x23c
    int32_t          mH;                 // +0x240
    char             pad_244[0xc];       // +0x244
    Image*           mpImage;            // +0x250
    char             pad_254[0xc8];      // +0x254
    MinimapEventTree mEvents;            // +0x31c
    char             pad_330[8];         // +0x330
    Vec3             mAxisA;             // +0x338
    Vec3             mAxisB;             // +0x344
    float            mScale;             // +0x350
    char             pad_354[0x638];     // +0x354
    IMinimapIcon*    mpIcon;             // +0x98c

    void DrawIcon(void* pWindow, float angle, void* pOwner);                  // 0x00e0d100
    bool ProjectEvent(const Vec2* pMapPos, Vec3* pOut);                       // 0x00e0de40
    AutoRefCountEvent* FindEvent(uint32_t key);                               // 0x00e0df30
    uint32_t OnTick();                                                        // 0x00e0d940

    float AngleFromPoint(float x, float y);                                   // 0x00e0a9e0
    void ComputeIconPositionFromMinimapCoords(const void* pPos, IMinimapIcon* pIcon, int flag);  // 0xe0bf40
    bool ProjectCenter(const Vec3* pPos, Vec2* pOut, int flag);               // 0xe0bcb0
    void RefreshEffects(const void* pData, uint32_t a, uint32_t b, int c);    // 0xe0b990
};

// ---- helpers and globals --------------------------------------------------
extern "C" Vec3* ExpandCoord(Vec3* pOut, const Vec2* pUV);               // 0x00e0cea0 (returns pOut)
extern "C" void HideWindowIcon(void* pWindow);                           // 0x00806fc0
extern "C" void SetWindowQuad(void* pWindow, const float* pQuad);        // 0x00808230
extern "C" void SetWindowScale(void* pWindow, float scale);              // 0x00808210
extern "C" void AnchorWindowToWindow(IMinimapIcon* pAnchor, void* pWindow, int flags, int z);   // 0x00807340
extern "C" float GetElapsedSeconds();                                    // 0x00805080
extern "C" MinimapEventNode* RBTreeIncrement(MinimapEventNode* pNode);   // 0x00921580
extern "C" IWindowManager* WindowManager();                              // 0x0067caa0
extern "C" IAppAccess* GetApp();                                         // 0x0067dd10
extern "C" void* EventAction(IMinimapTargetC* pTarget, const void* pEventId);   // 0x00ac80d0
extern "C" void PlayEvent(void* pHandle, float a, float b, int tag);     // 0x00b69aa0

struct Stopwatch { __int64 GetElapsed(); };                              // 0x0093a3a0
extern Stopwatch g_minimapStopwatch;                                     // 0x016a2028
extern uint32_t g_swLo, g_swHi;                                          // 0x016a2028 / 0x016a202c
extern uint8_t  g_fxEnabled;                                             // 0x016a1fa0
extern float    g_fxThreshold;                                           // 0x015a4cb8
extern float    g_fxScale;                                               // 0x016a203c
extern uint32_t g_fxA, g_fxB;                                            // 0x016a1f9c / 0x016a1f98
extern uint8_t  g_fxData[];                                              // 0x016a2040
extern float    g_lastDirX, g_lastDirY, g_lastDirZ;                      // 0x016a1fa4 / a8 / ac

extern float    g_iconRadius;                                            // 0x015a4be8
extern float    g_iconRadiusAlt;                                         // 0x015a4bec
extern float    g_iconAngleOffset;                                       // 0x015a4bfc
extern float    g_iconScale;                                             // 0x015a4be4
extern const uint32_t g_minimapModeRotating;                             // 0x01654c10

// @ 0x00e0d100  cSPUIMinimapWin::DrawIcon
void cMinimapOverlay::DrawIcon(void* pWindow, float angle, void* pOwner)
{
    if (!mpIcon) return;
    if (angle == 0.0f) {
        HideWindowIcon(pWindow);
    } else {
        void* pMode = GetApp()->GetModeTag();
        ComputeIconPositionFromMinimapCoords(pOwner, mpIcon, 0);
        mWindow.sec(mpIcon);
        const float* pQuad = mpIcon->s38();
        float quad[4];
        quad[0] = pQuad[0];
        quad[1] = pQuad[1];
        quad[2] = pQuad[2];
        quad[3] = pQuad[3];
        float s = sinf(angle);
        float c = cosf(angle);
        float r = ((uint32_t)pMode == (uint32_t)&g_minimapModeRotating) ? g_iconRadiusAlt : g_iconRadius;
        quad[0] = quad[0] - r * c;
        quad[1] = quad[1] - r * s;
        quad[2] = quad[2] - r * c;
        quad[3] = quad[3] - r * s;
        mpIcon->s6c(quad);
        AnchorWindowToWindow(mpIcon, pWindow, 0x300, 0);
        angle = angle - g_iconAngleOffset;
        float q2[4] = { 0.0f, 0.0f, 1.0f, angle };
        SetWindowQuad(mpIcon, q2);
        if ((uint32_t)pMode != (uint32_t)&g_minimapModeRotating)
            SetWindowScale(pWindow, g_iconScale);
    }
    mpIcon->s7c(1, angle != 0.0f);
}

// @ 0x00e0de40  cSPUIMinimapWin::ProjectEvent
bool cMinimapOverlay::ProjectEvent(const Vec2* pMapPos, Vec3* pOut)
{
    PlanetModel* pm = GetPlanetModel();
    ITerrain* ter;
    if (pm) ter = pm->mpTerrain;
    else    ter = 0;
    if (!ter || !ter->GetTerrainMapSet()) return false;

    float angle = AngleFromPoint(pMapPos->x, pMapPos->y);
    Vec2 uv;
    uv.x = angle / mW;
    uv.y = pMapPos->y / (float)mH;

    Vec2* pUV = ((IMapSetProjection*)ter)->Project(&uv, &mAxisA, &mAxisB, mScale);
    Vec3 local;
    Vec3* pLocal = ExpandCoord(&local, pUV);
    *pOut = *pLocal;

    Vec3* pSurface = pm->DirectionToSurfacePosition(&local, pOut);
    *pOut = *pSurface;
    return true;
}

// @ 0x00e0df30  cSPUIMinimapWin::FindEvent
AutoRefCountEvent* cMinimapOverlay::FindEvent(uint32_t key)
{
    MinimapEventNode* pFound;
    mEvents.find(&pFound, &key);
    if (pFound != (MinimapEventNode*)&mEvents.mpRoot)
        return &pFound->mEvent;
    return 0;
}

// @ 0x00e0d940  cSPUIMinimapWin::OnTick
uint32_t cMinimapOverlay::OnTick()
{
    if ((mWindow.s28() & 1) == 0)
        return 1;

    float now = GetElapsedSeconds();
    MinimapEventNode* pEnd = (MinimapEventNode*)&mEvents.mpRoot;
    for (MinimapEventNode* p = mEvents.mpBegin; p != pEnd; p = RBTreeIncrement(p)) {
        IMinimapIcon* pIcon = 0;
        uint32_t key = p->mKey;
        if (p->mFlags & 0x40103) {
            IMinimapIcon* pGroup = mWindow.sf0(key, 1);
            if (pGroup) {
                pIcon = pGroup->s10()->sf0(key + 1, 1);
                if (pIcon && !mIconsHidden) {
                    if (now > p->mTime) {
                        pIcon->s7c(1, 0);
                        if (now > p->mTime + 1.0f) {
                            pIcon->s10()->se0(pIcon);
                            pIcon = 0;
                            p->mState = 0;
                        }
                    } else if ((pIcon->s28() & 1) == 0) {
                        pIcon->s7c(1, 1);
                    }
                }
            }
        }

        if ((p->mFlags & 0x100) && p->mpTarget) {
            IMinimapTargetA* pTargetA = (IMinimapTargetA*)p->mpTarget->Find(0x137e8e0);
            if (pTargetA) {
                const Vec3* pDir = pTargetA->mDirection.GetDirection();
                float len2 = pDir->x * pDir->x + pDir->y * pDir->y + pDir->z * pDir->z + 1e-8f;
                float inv = 1.0f / sqrt((double)len2);
                p->mPos.x = pDir->x * inv;
                p->mPos.y = pDir->y * inv;
                p->mPos.z = pDir->z * inv;
                if (p->mPos.x != g_lastDirX || p->mPos.y != g_lastDirY || p->mPos.z != g_lastDirZ) {
                    Vec2 uv;
                    ProjectCenter(&p->mPos, &uv, 0);
                    IMinimapIcon* pFound = mWindow.sf0(key, 1);
                    if (pFound)
                        ComputeIconPositionFromMinimapCoords(&uv, pFound, 0);
                }
            }
        }

        if ((p->mFlags & 0x2000) && p->mpTarget) {
            IMinimapTargetB* pTargetB = (IMinimapTargetB*)p->mpTarget->Find(0x4f176642);
            if (pTargetB) {
                const Vec3* pDir = pTargetB->mDirection.GetDirection();
                float len2 = pDir->x * pDir->x + pDir->y * pDir->y + pDir->z * pDir->z + 1e-8f;
                float inv = 1.0f / sqrt((double)len2);
                p->mPos.x = pDir->x * inv;
                p->mPos.y = pDir->y * inv;
                p->mPos.z = pDir->z * inv;
                Vec2 uv;
                ProjectCenter(&p->mPos, &uv, 0);
                if (pIcon)
                    ComputeIconPositionFromMinimapCoords(&uv, pIcon, 0);
                IMinimapIcon* pFound = mWindow.sf0(key, 1);
                if (pFound)
                    ComputeIconPositionFromMinimapCoords(&uv, pFound, 0);
            }
        }
    }

    if (g_fxEnabled != 0) {
        if ((g_swLo == 0 && g_swHi == 0) ||
            (g_fxThreshold <= (float)(__int64)g_minimapStopwatch.GetElapsed() * g_fxScale))
            RefreshEffects(g_fxData, g_fxA, g_fxB, 1);
    }

    unsigned int mode = GetCurrentGameMode();
    if (mode != 0x1654c01 && mode != 0x1654c05 && mode != 0x1654c02)
        return 1;

    IMinimapView* pView = WindowManager()->GetView(1);
    if (!pView)
        return 1;

    float viewAngle = pView->GetAngle();
    MinimapEventNode* pFound;
    mEvents.find(&pFound, &viewAngle);
    if (pFound == pEnd)
        return 1;
    if (!pFound->mpTarget)
        return 1;

    IMinimapIcon* pFocus = mWindow.sf0(pFound->mKey, 1);
    if (!pFocus)
        return 1;

    const float* pQuad = pFocus->s38();
    float halfW = (pQuad[2] - pQuad[0]) * 0.5f;
    float halfH = (pQuad[3] - pQuad[1]) * 0.5f;
    Vec2 half;
    half.x = halfW;
    half.y = halfH;
    float size[2];
    pFocus->sc0(half, size);

    if (!pFound->mpTarget)
        return 1;
    IMinimapTargetC* pTargetC = (IMinimapTargetC*)pFound->mpTarget->Find(0x17f243b);
    if (!pTargetC)
        return 1;

    void* pEventMode = pTargetC->GetMode();
    void* pHandle;
    int tag;
    if ((uint32_t)pEventMode == 0x18c43e8) {
        pHandle = EventAction(pTargetC, (const void*)0x18c43e8);
        tag = 0;
    } else if ((uint32_t)pEventMode == 0x18c6d19) {
        pHandle = EventAction(pTargetC, (const void*)0x18c6d19);
        tag = 0x05b598f6;
    } else if ((uint32_t)pEventMode == 0x52aa6122) {
        if (mode != 0x1654c01)
            return 1;
        pHandle = EventAction(pTargetC, (const void*)0x52aa6122);
        tag = 0;
    } else {
        return 1;
    }
    PlayEvent(pHandle, size[0], size[1], tag);
    return 1;
}
