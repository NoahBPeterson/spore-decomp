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

struct PlanetModel { char pad[0x24]; ITerrain* mpTerrain; };
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
