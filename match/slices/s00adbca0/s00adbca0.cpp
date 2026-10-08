// Slice s00adbca0: FUN_00adbca0, "where does this attached effect/object go": resolves the
// pose of the object named by the config (pos, orientation, three scales) from either a
// registered holder (found1) or the config's defaults, applies the config's offset
// (rotated by the orientation), and clamps to the planet surface.
//
// Retail layouts; offsets verified against the asm.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (movss, x87 call results; no EH frame).
#include "types.h"

extern "C" double __cdecl sqrt(double);
#pragma intrinsic(sqrt)

struct Vector3 { float x, y, z; };
struct Quat { float x, y, z, w; Quat() {} Quat(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {} };
struct Box { float minX, minY, minZ, maxX, maxY, maxZ; };

struct Matrix3 {
    float m[9];
    Matrix3(const Matrix3& o);                       // 0x0041cb40
};

extern Vector3 g_DefaultPos1;                        // 0x0167a548
extern Vector3 g_DefaultPos2;                        // 0x0167a5a4
extern Matrix3 g_DefaultRot;                         // 0x0167a5b0
extern float   g_One;                                // 0x01485720 (1.0f)

struct Transform {
    uint16_t flags;
    uint16_t mod;
    Vector3  pos;
    float    scale;
    Matrix3  rot;
    Transform() : flags(0), mod(0), pos(g_DefaultPos2), scale(1.0f), rot(g_DefaultRot) {}
};

// Object found by id; vtable slots as used here.
class IPose {
public:
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void s20(); virtual void s24(); virtual void s28();
    virtual const Vector3* GetPosition();            // 0x2c
    virtual const Quat*    GetOrientation();         // 0x30
    virtual void s34(); virtual void s38(); virtual void s3c(); virtual void s40();
    virtual void s44(); virtual void s48(); virtual void s4c(); virtual void s50();
    virtual void s54(); virtual void s58(); virtual void s5c(); virtual void s60();
    virtual void s64();
    virtual const Box* GetBounds();                  // 0x68
    virtual void s6c();
    virtual float GetScaleB();                       // 0x70
    virtual float GetScaleA();                       // 0x74
    virtual void s78(); virtual void s7c(); virtual void s80(); virtual void s84();
    virtual void s88(); virtual void s8c(); virtual void s90(); virtual void s94();
    virtual void s98(); virtual void s9c(); virtual void sa0(); virtual void sa4();
    virtual void sa8(); virtual void sac(); virtual void sb0(); virtual void sb4();
    virtual void sb8(); virtual void sbc();
    virtual void Release();                          // 0xc0
};

class IPoseSource {
public:
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14(); virtual void s18(); virtual void s1c();
    virtual void GetTransform(Transform* out);       // 0x20
};

// Pose holder filled by Owner::Lookup (0x30 bytes).
struct Holder {
    Vector3 pos;
    Quat    rot;
    float   sc[4];
    IPose*  obj;
    Holder() : pos(g_DefaultPos1), rot(Quat(0.0f, 0.0f, 0.0f, 0.0f)), obj(0)
    {
        sc[0] = sc[1] = sc[2] = sc[3] = g_One;
    }
    ~Holder() { if (obj) obj->Release(); }
    Vector3* ad7b90(Vector3* out);                   // 0x00ad7b90
};

struct Cfg {
    uint32_t pad00[4];
    uint32_t id;               // +0x10
    Vector3  ofs;              // +0x14
    Vector3  ofs2;             // +0x20
    uint8_t  pad2c[3];
    bool     scaleXY;          // +0x2f
    bool     useB;             // +0x30
    bool     useC;             // +0x31
    uint8_t  pad32[2];
    uint32_t id2;              // +0x34
    int      mode;             // +0x38
    uint32_t pad3c[(0x80 - 0x3c) / 4];
    Vector3  defPos;           // +0x80
};

struct TerrainMapSet {
    uint32_t pad00[0x34 / 4];
    float radius;              // +0x34
    float maxHeight;           // +0x38
    float waterHeight;         // +0x3c
    float GetHeightAt(const Vector3* p);             // 0x00f927c0
};
class TerrainProvider {
public:
    virtual void s00(); virtual void s04(); virtual void s08();
    virtual TerrainMapSet* GetMapSet();              // 0xc
};
struct PlanetMdl {
    uint32_t pad00[0x24 / 4];
    TerrainProvider* terrain;  // +0x24
    bool     IsPositionBelowSurface(const Vector3* p);                  // 0x00b81f90
    Vector3* b81630(Vector3* out, const Vector3* p);                    // 0x00b81630
    Vector3* b82b40(Vector3* out, const Vector3* p, int k);             // 0x00b82b40
};
PlanetMdl* PlanetModel();                            // 0x00b3d350
int  GetUniverseContext();                           // 0x01021080
bool IsInvalidQuat(const Quat* q);                   // 0x00ad7170 (cdecl)
Matrix3* QuatToMatrix(Matrix3* out, const Quat* q);  // 0x004a9b40 (cdecl)
Quat* QuaternionFromMatrix33(Quat* out, const Matrix3* m, float k);     // 0x00472b80 (cdecl)

class Placer {
public:
    uint32_t pad00[0x16c / 4];
    Cfg*     cfg;                                    // +0x16c

    bool Lookup(uint32_t id, Holder* h);             // 0x00adb2a0
    bool LookupSource(uint32_t id, IPoseSource** out);   // 0x00adb1b0
    void GetPose(Vector3* outPos, Quat* outRot, float* outA, float* outB, float* outC);   // 0x00adbca0
};

void Placer::GetPose(Vector3* outPos, Quat* outRot, float* outA, float* outB, float* outC)
{
    Holder h1;
    IPoseSource* src;
    bool found1 = Lookup(cfg->id, &h1);
    bool haveSrc = LookupSource(cfg->id, &src);
    Holder h2;
    bool found2 = false;
    if (cfg->id2 != 0)
        found2 = Lookup(cfg->id2, &h2);

    Vector3 tmp;
    if (found1) {
        const Vector3* p = h1.obj ? h1.obj->GetPosition() : &h1.pos;
        *outPos = *p;
        const Quat* q = h1.obj ? h1.obj->GetOrientation() : &h1.rot;
        *outRot = *q;
        *outA = h1.obj ? h1.obj->GetScaleA() : h1.sc[0];
        *outB = h1.obj ? h1.obj->GetScaleB() : h1.sc[1];
        if (h1.obj) {
            const Box* b = h1.obj->GetBounds();
            *outC = b->maxZ - b->minZ;
        } else {
            *outC = h1.sc[3];
        }
        if (found2) {
            *outA = h2.obj ? h2.obj->GetScaleA() : h2.sc[0];
            *outB = h2.obj ? h2.obj->GetScaleB() : h2.sc[1];
        }
        if (cfg->mode == 1) {
            *outPos = *h1.ad7b90(&tmp);
        } else if (cfg->mode == 2) {
            float x = outPos->x, y = outPos->y, z = outPos->z;
            float inv = (float)(1.0 / sqrt(z * z + x * x + y * y));
            tmp.x = inv * x;
            tmp.y = inv * y;
            tmp.z = z * inv;
            TerrainMapSet* ts = PlanetModel()->terrain->GetMapSet();
            float h = ts->GetHeightAt(outPos);
            float r = ts->waterHeight * ts->maxHeight + ts->radius;
            const float& m = (r < h) ? h : r;
            outPos->x = tmp.x * m;
            outPos->y = tmp.y * m;
            outPos->z = tmp.z * m;
        }
        if (cfg->mode != 2 && GetUniverseContext() == 0) {
            if (PlanetModel()->IsPositionBelowSurface(outPos))
                *outPos = *PlanetModel()->b81630(&tmp, outPos);
        }
    } else if (!haveSrc) {
        *outPos = cfg->defPos;
        Quat q(0.0f, 0.0f, 0.0f, 1.0f);
        *outRot = q;
    } else {
        PlanetMdl* pm = PlanetModel();
        Transform xf;
        src->GetTransform(&xf);
        *outPos = xf.pos;
        Quat qtmp;
        *outRot = *QuaternionFromMatrix33(&qtmp, &xf.rot, 0.0f);
        if (cfg->mode == 2 && pm && pm->terrain)
            *outPos = *pm->b82b40(&tmp, outPos, 0);
    }

    Cfg* c = cfg;
    float ox = c->ofs.x, oy = c->ofs.y, oz = c->ofs.z;
    if (c->scaleXY) {
        ox = *outA * ox;
        oy = *outA * oy;
    }
    if (c->useB && c->useC) {
        float b = *outB, cc = *outC;
        oz = ((b > cc) ? b : cc) * oz;
    } else if (c->useB) {
        oz = *outB * oz;
    } else if (c->useC) {
        oz = *outC * oz;
    }
    ox = c->ofs2.x + ox;
    oy = c->ofs2.y + oy;
    oz = c->ofs2.z + oz;
    if (!IsInvalidQuat(outRot)) {
        float mbuf[9];
        const float* M = QuatToMatrix((Matrix3*)mbuf, outRot)->m;
        outPos->y = outPos->y + ((M[7] * oz + M[4] * oy) + M[1] * ox);
        outPos->x = outPos->x + ((M[6] * oz + M[3] * oy) + M[0] * ox);
        outPos->z = outPos->z + ((M[8] * oz + M[5] * oy) + M[2] * ox);
    } else {
        outPos->x = outPos->x + ox;
        outPos->y = outPos->y + oy;
        outPos->z = outPos->z + oz;
    }
}
