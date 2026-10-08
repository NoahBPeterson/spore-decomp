// Slice s00d53b50: pick / place a nearby noun on a ring around the avatar (0x00d53b50, 1.9 KB).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
//
// Place(target, outPos): every slot of the list at +0x20/+0x24 has an angle (+4); the slot's
// direction (the avatar's up-vector rotated by that angle about the avatar's position axis) is
// scored by |1 - dot(dir, direction to target)| into +8, the list is sorted by that score
// (eastl::sort with FUN_00d52c90), the first usable slot (angle inside the ring window while in
// the planet mode, farther from the avatar than the target) takes the target noun and the
// resulting point is projected onto the planet surface. Names are Claude-coined.
#include "types.h"
#include <math.h>

typedef unsigned int uint;

struct Vec3 { float x, y, z; };

// ---------------------------------------------------------------------------- stubs
struct NounSub {                                     // polymorphic member at Noun+0xc0
    virtual void s0();  virtual void s1();  virtual void s2();  virtual void s3();
    virtual void s4();  virtual void s5();  virtual void s6();  virtual void s7();
    virtual void s8();  virtual void s9();  virtual void s10();
    virtual const Vec3* GetPosition();               // +0x2c
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
    virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22();
    virtual void GetDirection(Vec3* out);            // +0x5c
    virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
    virtual void s28();
    virtual float GetRadius();                       // +0x74
};
struct Noun {
    virtual void AddRef();                           // +0
    virtual void Release();                          // +4
    char pad[0xc0 - 4];
    NounSub mSub;                                    // +0xc0
};
struct Entry {
    Noun* mpNoun;                                    // +0 (AutoRefCount<Noun>)
    float mAngle;                                    // +4
    float mScore;                                    // +8
};
struct NounMgr { Noun* GetAvatar(); };               // 0x00b1fdb0
NounMgr* NounManager();                              // 0x00b3d300
const void* GetCurrentGameMode();                    // 0x00b5b800
extern char gPlanetMode;                             // 0x01654c10
extern const float kRingRadius;                      // 0x01583d24
extern const float kOffsetBase;                      // 0x01582e04

struct PlanetModelT { Vec3* Project(Vec3* out, const Vec3* in); };   // 0x00b816f0 (ret 8)
PlanetModelT* PlanetModel();                         // 0x00b3d350
void FUN_00d99e20(const Vec3* pos, Vec3* res);       // cdecl

typedef char (__cdecl* Cmp)(Entry*, Entry*);
extern "C" char __cdecl F52c90(Entry*, Entry*);      // 0x00d52c90
void introsort(Entry** first, Entry** last, int depth, Cmp pred);    // 0x00d53940 (cdecl)
void insertion_sort(Entry** first, Entry** last, Cmp pred);          // 0x00b909f0 (cdecl)

static inline int Log2(int n) { int k = 0; while (n) { n >>= 1; ++k; } return k; }

static __forceinline void SortEntries(Entry** first, Entry** last, Cmp cmp)
{
    if (first != last) {
        int lg = Log2(last - first);
        introsort(first, last, lg * 2 - 2, cmp);
        if (last - first > 28) {
            insertion_sort(first, first + 28, cmp);
            for (Entry** p = first + 28; p != last; ++p) {       // unguarded insertion sort
                Entry* val = *p;
                float key = val->mScore;
                Entry** q = p;
                Entry** r = p;
                while (true) {
                    --r;
                    if ((*r)->mScore <= key) break;
                    *q = *r;
                    --q;
                }
                *q = val;
            }
        } else {
            insertion_sort(first, last, cmp);
        }
    }
}

// Rotate v about the unit axis n by angle (quaternion form).
static inline void RotateAxis(Vec3* u, const Vec3& n, float angle, const Vec3& v)
{
    float s = sinf(angle * 0.5f);
    float c = cosf(angle * 0.5f);
    float qx = s * n.x;
    float qy = n.y * s;
    float qz = n.z * s;
    u->x = (((qy * qx) - (c * qz)) * v.y + ((c * qy) + (qz * qx)) * v.z) * 2.0f
           + (1.0f - (qy * qy + qz * qz) * 2.0f) * v.x;
    u->y = (((qz * qy) - (c * qx)) * v.z + ((c * qz) + (qy * qx)) * v.x) * 2.0f
           + (1.0f - (qz * qz + qx * qx) * 2.0f) * v.y;
    u->z = (((qz * qx) - (c * qy)) * v.x + ((c * qx) + (qz * qy)) * v.y) * 2.0f
           + (1.0f - (qy * qy + qx * qx) * 2.0f) * v.z;
}

class cRingPlacer {
public:
    char pad00[0x20];
    Entry** mpBegin;                                 // +0x20
    Entry** mpEnd;                                   // +0x24

    Entry* Place(Noun* target, Vec3* outPos);
};

// @ 0x00d53b50
Entry* cRingPlacer::Place(Noun* target, Vec3* outPos)
{
    NounSub* av = (NounSub*)((char*)NounManager()->GetAvatar() + 0xc0);
    const Vec3* p = av->GetPosition();
    float px = p->x;
    float invLen = 1.0f / sqrtf((px * px + p->y * p->y) + p->z * p->z + 1e-8f);
    Vec3 n;
    n.x = px * invLen;
    n.y = p->y * invLen;
    n.z = p->z * invLen;
    Vec3 v;
    av->GetDirection(&v);

    const Vec3* ap = av->GetPosition();
    NounSub* tsub = &target->mSub;
    const Vec3* tp = tsub->GetPosition();
    float dy = tp->y - ap->y;
    float dz = tp->z - ap->z;
    float dx = tp->x - ap->x;
    float distSq = (dz * dz + dy * dy) + dx * dx;
    float invD = 1.0f / sqrtf(distSq + 1e-8f);
    Vec3 t;
    t.x = invD * dx;
    t.y = dy * invD;
    t.z = dz * invD;
    float dnx = t.x, dny = t.y, dnz = t.z;

    Entry* found = 0;
    Entry** end = mpEnd;
    for (Entry** it = mpBegin; it != end; ++it) {
        Entry* e = *it;
        RotateAxis(&t, n, e->mAngle, v);
        e->mScore = fabsf(1.0f - ((t.x * dnx + t.z * dnz) + t.y * dny));
        if (e->mpNoun == target) found = e;
    }

    SortEntries(mpBegin, mpEnd, F52c90);

    bool planet = (GetCurrentGameMode() == &gPlanetMode);
    Entry** cursor = mpBegin;
    Entry* chosen = 0;
    float ring = kRingRadius;
    for (; cursor != end; ++cursor) {
        chosen = *cursor;
        if (planet) {
            float a = chosen->mAngle;
            if (ring * 0.5f > a) continue;
            if (a > ring * 1.5f) continue;
        }
        Noun* cur = chosen->mpNoun;
        if (cur && cur != target) {
            const Vec3* a1 = av->GetPosition();
            const Vec3* t1 = cur->mSub.GetPosition();
            float ey = t1->y - a1->y;
            float ez = t1->z - a1->z;
            float ex = t1->x - a1->x;
            float thr = distSq + 1.0f;
            if (!(((ez * ez + ey * ey) + ex * ex) > thr)) continue;
        }
        if (found) {
            Noun* t = found->mpNoun;
            if (t) { found->mpNoun = 0; t->Release(); }
        }
        break;
    }
    if (cursor == end) return 0;

    Noun* old = chosen->mpNoun;
    if (old != target) {
        target->AddRef();
        chosen->mpNoun = target;
        if (old) old->Release();
    }
    RotateAxis(&t, n, chosen->mAngle, v);
    float k1 = kOffsetBase + 1.0f;
    float rt = tsub->GetRadius();
    float ra = av->GetRadius();
    float r = (ra + rt) + k1;
    Vec3 off;
    off.x = t.x * r;
    off.y = t.y * r;
    off.z = t.z * r;
    const Vec3* pa = av->GetPosition();
    t.x = off.x + pa->x;
    t.z = pa->z + off.z;
    t.y = pa->y + off.y;
    Vec3* proj = PlanetModel()->Project(&off, &t);
    *outPos = *proj;
    FUN_00d99e20(tsub->GetPosition(), outPos);
    return chosen;
}
