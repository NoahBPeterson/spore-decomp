// Slice s00c6d0f0 -- SP::cHerd::AddAvatarEggsInNest (0x00c6d0f0, 1730 bytes, thiscall, 1 stack arg).
//
// Lays out one egg per owned creature (plus one for the avatar) around a nest position, in a
// hexagonal "spiral": ring 1 holds 6 eggs, ring 2 holds 12, ... (cap grows by 6 per ring), each
// ring `spacing` metres further out.  Spacing is 1 unless the herd's species profile has a size
// vector, in which case it is |size| * c0b440(g) * d2e800(0).  The ring direction frame is built from
// two fixed quaternions (axis (1,0,0) and axis (0,1,0), both pi/2 rotated) applied to the nest
// position, then the surface orientation at the nest, then every egg gets a random world position
// 2..5 m around its spiral point and its own surface orientation facing that point.  The first egg
// (i == 0) belongs to the avatar (isAvatar flag, owner = avatar noun); the others are owned by the
// i-1'th entry of NounManager()->list.  Each created egg gets flag 0x4000 at +0x84 and byte
// +0xa5 = 1 and is registered through FUN_00b3d310()->FUN_00b45410(egg + 0x34).
//
// Callee conventions come from the call sites: FUN_0059aed0 is cdecl (out, v, q); PlanetModel()
// takes no argument (pushes before it belong to the thiscall that follows); FUN_00b3d310 returns a
// global and the push before it is the argument of the thiscall FUN_00b45410.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

namespace SP {

struct Vec3 { float x, y, z; };
struct Quat { float x, y, z, w; };

struct cSpeciesProfile {
    uint32_t pad[0x554 / 4];
    float mSize[3];                                    // +0x554
};

struct EggRegistry {
    void FUN_00b45410(void* p);                        // thiscall ret 4
};

struct cEgg {
    uint32_t pad[0x34 / 4];
    uint32_t m34[(0x84 - 0x34) / 4];
    uint32_t mFlags;                                   // +0x84
    uint8_t pad88[0xa5 - 0x88];
    uint8_t mB5;                                       // +0xa5
};

struct ObjList {
    void** mpBegin;
    void** mpEnd;
};

struct cGameNounManager {
    uint32_t pad[0x5c / 4];
    ObjList mList;                                     // +0x5c
    ObjList* GetList();                                // 0x00b1f9c0: lea eax,[ecx+0x5c]
    void* GetAvatar();                                 // 0x00b1fdb0
};

class cPlanetModel {
public:
    Quat* BuildSurfaceOrientation(Quat* out, const Vec3* pos, const Vec3* dir);      // 0x00b7f250 (ret 12)
    Vec3* MakeRandomWorldPosition(Vec3* out, const Vec3* center, float minR, float maxR);   // 0x00b81780
    Vec3* FUN_00b82970(Vec3* out, const Vec3* in, int flag);                          // ret 12
};

class cHerd {
public:
    virtual int AddRef();                              // +0x00
    virtual int Release();                             // +0x04
    char pad04[0xa4 - 4];
    cSpeciesProfile* mpSpeciesProfile;                 // +0xa4

    void AddAvatarEggsInNest(const Vec3* nestPos);
    cEgg* AddEggInNest(const Vec3* pos, const Quat* orient, bool isAvatar, int kind, void* owner);   // 0x00c6cf10 (ret 20)
};

}  // namespace SP

extern "C" {
    SP::cGameNounManager* __cdecl NounManager();       // 0x00b3d300
    SP::cPlanetModel*     __cdecl PlanetModel();       // 0x00b3d350
    SP::Vec3*             __cdecl FUN_0059aed0(SP::Vec3* out, const SP::Vec3* v, const SP::Quat* q);
    float                 __cdecl FUN_00c0b440(int g);
    float                 __cdecl FUN_00d2e800(int a);
    SP::EggRegistry*      __cdecl FUN_00b3d310();
}

extern int DAT_0169e370;                                // 0x0169e370
extern float DAT_015778b4;                                  // 0x015778b4
extern float DAT_015778b8, DAT_015778bc, DAT_015778c0;                   // 0x015778b8
extern float DAT_015778c4, DAT_015778c8, DAT_015778cc;                   // 0x015778c4
extern SP::Vec3 DAT_01693ea0;                                // 0x01693ea0
extern float DAT_01693eac;                              // 0x01693eac

using namespace SP;

namespace {
__forceinline Quat AxisAngle(float ax, float ay, float az, float angle)
{
    float half = angle * 0.5f;
    float s = (float)sin(half);
    float c = (float)cos(half);
    Quat q;
    q.x = ax * s; q.y = ay * s; q.z = az * s; q.w = c;
    return q;
}

// q1 * q2
__forceinline Quat Mul(const Quat& a, const Quat& b)
{
    Quat r;
    float cx = b.z * a.y - b.y * a.z;
    float cy = a.z * b.x - b.z * a.x;
    float cz = b.y * a.x - a.y * b.x;
    r.x = (a.w * b.x + b.w * a.x) + cx;
    r.y = (b.y * a.w + b.w * a.y) + cy;
    r.z = (b.z * a.w + b.w * a.z) + cz;
    r.w = b.w * a.w - ((b.x * a.x + b.z * a.z) + b.y * a.y);
    return r;
}
}

// @ 0x00c6d0f0
void cHerd::AddAvatarEggsInNest(const Vec3* nestPos)
{
    ObjList* list = NounManager()->GetList();
    int count = (int)(list->mpEnd - list->mpBegin) + 1;
    int i = 0;
    float spacing = 1.0f;
    if (cSpeciesProfile* prof = mpSpeciesProfile) {
        float len = sqrtf((prof->mSize[0] * prof->mSize[0] + prof->mSize[1] * prof->mSize[1]) + prof->mSize[2] * prof->mSize[2]);
        float k = FUN_00c0b440(DAT_0169e370);
        spacing = FUN_00d2e800(0) * k * len;
    }

    Quat q1 = AxisAngle(DAT_015778b8, DAT_015778bc, DAT_015778c0, DAT_015778b4);
    Quat q2 = AxisAngle(DAT_015778c4, DAT_015778c8, DAT_015778cc, DAT_015778b4);
    Quat q = Mul(q1, q2);

    Vec3 rtmp;
    Vec3 rotated = *FUN_0059aed0(&rtmp, nestPos, &q);
    Quat surf;
    PlanetModel()->BuildSurfaceOrientation(&surf, nestPos, &rotated);
    Vec3 atmp;
    Vec3 axis = *FUN_0059aed0(&atmp, &DAT_01693ea0, &surf);
    float inv = 1.0f / sqrtf(axis.y * axis.y + (axis.z * axis.z + axis.x * axis.x));
    float rx = inv * axis.x, ry = axis.y * inv, rz = axis.z * inv;

    float pinv = 1.0f / sqrtf((nestPos->x * nestPos->x + nestPos->y * nestPos->y) + nestPos->z * nestPos->z);
    float px = pinv * nestPos->x, py = nestPos->y * pinv, pz = pinv * nestPos->z;

    int ring = 1;
    int idx = 0;
    int cap = 6;
    for (; i < count; ++i) {
        Vec3 pos = *nestPos;
        bool isAvatar = false;
        if (i > 0) {
            if (idx >= cap) {
                ++ring;
                cap += 6;
                idx = 0;
            }
            float dist = (float)ring * spacing;
            double h = (double)idx * DAT_01693eac / cap * 0.5;
            float s = (float)sin(h);
            float c = (float)cos(h);
            ++idx;
            float X = s * px, Y = py * s, Z = pz * s, W = c;
            float YY = Y * Y;
            float XY = Y * X;
            float ZY = Z * Y;
            float WY = W * Y;
            pos.x = (((WY + Z * X) * rz + (XY - W * Z) * ry) * 2.0f + (1.0f - (Z * Z + YY) * 2.0f) * rx) * dist + pos.x;
            pos.y = (((W * Z + XY) * rx + (ZY - W * X) * rz) * 2.0f + (1.0f - (Z * Z + X * X) * 2.0f) * ry) * dist + pos.y;
            pos.z = (((W * X + ZY) * ry + (Z * X - WY) * rx) * 2.0f + (1.0f - (X * X + YY) * 2.0f) * rz) * dist + pos.z;
        }
        cPlanetModel* pm = PlanetModel();
        Vec3 tmp;
        Vec3* rnd = pm->MakeRandomWorldPosition(&tmp, &pos, 2.0f, 5.0f);
        Vec3 dir;
        dir.x = rnd->x - pos.x; dir.y = rnd->y - pos.y; dir.z = rnd->z - pos.z;
        Quat orient;
        pm->BuildSurfaceOrientation(&orient, &pos, &dir);
        void* owner;
        if (i == 0) {
            owner = NounManager()->GetAvatar();
            isAvatar = true;
        } else {
            owner = list->mpBegin[i - 1];
        }
        Vec3 surfPos;
        PlanetModel()->FUN_00b82970(&surfPos, &pos, 0);
        cEgg* egg = AddEggInNest(&surfPos, &orient, isAvatar, 5, owner);
        egg->mFlags |= 0x4000;
        egg->mB5 = 1;
        FUN_00b3d310()->FUN_00b45410(&egg->m34[0]);
    }
}
