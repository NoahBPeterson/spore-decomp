// s00d425f0: sUpdateMinimap(float dt) (0x00d425f0). Per-frame update of the avatar's minimap icons:
// re-centers the map when the avatar moved far enough, rebuilds the icon set for the nearby
// herd/tribe objects every 2.5 s, and adds one queued extra icon per second.
// Flags /O2 /MD /Gy /TP /arch:SSE /fp:fast (no EH frame), like the neighbouring s00d41a70.
#include "types.h"

#include <math.h>

extern "C" void* __cdecl memmove(void* dst, const void* src, unsigned int n);   // 0x011e0744

struct Vec3 { float x, y, z; };

// cvtss2si (round to nearest) as in the original's asm helper
static inline int RoundToInt(float v)
{
    int r;
    __asm {
        cvtss2si eax, v
        mov r, eax
    }
    return r;
}

// ---------------------------------------------------------------- reference-counted helpers
class RefObject {
public:
    virtual int AddRef();
    virtual int Release();
};
struct RefPtr {
    RefObject* p;
    RefPtr() : p(0) {}
    ~RefPtr() { if (p) p->Release(); }
    void Assign(RefObject* n)
    {
        RefObject* old = p;
        if (n != old) {
            n->AddRef();
            p = n;
            if (old) old->Release();
        }
    }
};

struct cIconInfo {                    // size 0x24
    uint32_t mColor;                  // +0x00
    Vec3 mPos;                        // +0x04
    uint32_t mFlags;                  // +0x10
    RefPtr mpObject;                  // +0x14
    float mTimeout;                   // +0x18
    uint32_t mAnimState;              // +0x1c
    uint32_t m20;                     // +0x20
};

// ---------------------------------------------------------------- objects with a spatial subobject
class cSpatialObject {
public:
    virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
    virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
    virtual void s08(); virtual void s09(); virtual void s0a();
    virtual const Vec3* GetPosition();            // +0x2c
    virtual void s0c(); virtual void s0d(); virtual void s0e(); virtual void s0f();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
    virtual void s14(); virtual void s15();
    virtual bool IsHidden();                      // +0x58
    virtual uint32_t GetV5c(Vec3* out);           // +0x5c
};

struct cOwner {                       // herd / tribe record (the avatar's, and entries' +0x128)
    char pad0[0xa4];
    int mProfile;                     // +0xa4
    char pad1[0x120 - 0xa8];
    int mRangeMin;                    // +0x120
    int mRangeMax;                    // +0x124
    char pad2[0x160 - 0x128];
    void* mpLead;                     // +0x160
    char pad3[0x190 - 0x164];
    uint8_t mFlag190;                 // +0x190
    uint8_t mFlag191;                 // +0x191
};

class cMiniObj : public RefObject {   // entry of the game-data vector; sub-object at +0x34
public:
    char pad4[0x34 - 4];
    cSpatialObject mSub;              // +0x34 (a polymorphic subobject)
    char pad38[0xa9 - 0x38];
    uint8_t mFlagA9;                  // +0xa9
    char padaa[0x124 - 0xaa];
    uint32_t mFlags124;               // +0x124
    cOwner* mpOwner;                  // +0x128
};

struct cSpeciesData { char pad[0x4ec]; float mR, mG, mB; };                 // +0x4ec

struct cAvatarInfo;
class cCreatureMain {
public:
    virtual void v00();
    char pad4[0xc0 - 4];
};
class cAvatar : public cCreatureMain {
public:
    cSpatialObject mSub;              // +0xc0
    char padc4[0xb20 - 0xc4 - 0x00];
    cSpeciesData* mpSpecies;          // +0xb20
    cOwner* GetInfo();                // 0x00c04590
};

class cMinimapWin {
public:
    const Vec3* GetOrigin();                                          // 0x00e0acf0
    void SetCenter(const Vec3* pos);                                  // 0x00e0c1f0
    void SetZoom(float z);                                            // 0x00e0c2a0
    cIconInfo* FindIcon(cMiniObj* o);                                 // 0x00e0df30
    bool UpdateIcon(void* id, const Vec3* pos, int sel);              // 0x00e0df70
    void SetIconColor(const Vec3* pos, uint32_t v);                   // 0x00e0c490
    void Clear(int what);                                             // 0x00e0fb90
    void SetMode(int m);                                              // 0x00e0ad00
    void UpdateMapTexture();                                          // 0x00e0e1a0
    void RemoveIcon(void* id, int removeWindow, int flags);           // 0x00e0f9c0
    void AddIcon(void* id, const cIconInfo* info, int a, int b);      // 0x00e10580
};
extern cMinimapWin* g_minimap;                                        // 0x0169e3e4
extern int g_169e370;                                                 // 0x0169e370

// ---------------------------------------------------------------- managers
struct cPropList;
struct cStrategy { char pad[0xb4]; cPropList* mpProps; };
extern cStrategy* g_strategy;                                         // 0x0169e294
extern float __cdecl GetPropertyT_float(cPropList* p, uint32_t id, float def);   // 0x004e1c70

struct cGameDataResult { uint32_t pad0; void** mpBegin; void** mpEnd; };
typedef void* (__cdecl* GameDataFn)();
extern void* __cdecl FUN_00cd7d10();
extern void* __cdecl FUN_00d3d420();
extern void* __cdecl FUN_00bbf9b0();
extern void* __cdecl FUN_00b1e500();
struct cGameNounManager {
    cAvatar* GetAvatar();                                             // 0x00b1fdb0
    cGameDataResult* GetGameDataVector(GameDataFn a, GameDataFn b, GameDataFn c, GameDataFn d, uint32_t typeID);   // 0x00b21340
};
extern cGameNounManager* __cdecl NounManager();                       // 0x00b3d300

struct cProfile;
struct cSpeciesManager { cProfile* GetAvatarProfile(); };             // 0x004df420
extern cSpeciesManager* __cdecl FUN_00401090();                       // 0x00401090

struct cHerd;
extern cOwner* __cdecl GetDesiredAvatarHerd(int which);               // 0x00d40b40

struct cPlanetModel {
    float GetRadius();                                                // 0x00b7e4d0
    int GetContinent(uint32_t key);                                   // 0x00b88590
};
extern cPlanetModel* __cdecl PlanetModel();                           // 0x00b3d350

struct cQuery { void Run(const Vec3* pos, float radius, void* out, int a, int b); };   // 0x00b09340
extern cQuery* __cdecl FUN_00b3d440();                                // 0x00b3d440
struct cInfoB { uint32_t GetKey(); };                                 // 0x00c6acc0

extern uint32_t __cdecl PackARGB(int a, int r, int g, int b);         // 0x0067ac80

// ---------------------------------------------------------------- the global candidate list
struct PtrVec {
    void** mpBegin;                   // 0x01583354
    void** mpEnd;                     // 0x01583358
    void** mpCap;                     // 0x0158335c
    void Reserve(uint32_t n);                                         // 0x00d01790
    void DoInsert(void** pos, void* const* value);                    // 0x00b96600
};
extern PtrVec g_list;                                                 // 0x01583354
extern uint8_t g_flag;                                                // 0x01583344
extern uint8_t g_flag2;                                               // 0x01583345
extern float g_t1;                                                    // 0x01583348
extern float g_t2;                                                    // 0x0158334c
extern float g_t3;                                                    // 0x01583350

struct FixedPtrVec {                  // eastl::fixed_vector<void*, 8> on the stack
    void** mpBegin;
    void** mpEnd;
    void** mpCap;
    uint32_t mFlag;
    uint32_t mBuf[8];
};

// @ 0x00d425f0
void __cdecl sUpdateMinimap(float dt)
{
    cAvatar* avatar = NounManager()->GetAvatar();
    if (!avatar || !g_minimap) {
        return;
    }
    const Vec3* pos = avatar->mSub.GetPosition();
    float aggro = GetPropertyT_float(g_strategy->mpProps, 0xf7dc67f7, 100.0f);

    g_t1 = g_t1 - dt;
    bool flag = g_flag != 0;
    if (g_t1 <= 0.0f) {
        g_t1 = 5.0f;
        Vec3 v = *pos;
        float len = sqrtf((v.x * v.x + v.y * v.y) + v.z * v.z);
        if (len > 1.5258789e-05f) {
            float thr = (1.0f / len) * aggro;
            float inv = 1.0f / (len + 1.5258789e-05f);
            float dx = v.x * inv, dy = v.y * inv, dz = v.z * inv;
            const Vec3* o = g_minimap->GetOrigin();
            float ex = o->x - dx, ey = o->y - dy, ez = o->z - dz;
            if (thr * thr < (ez * ez + ey * ey) + ex * ex) {
                flag = true;
                g_minimap->SetCenter(pos);
                g_minimap->SetZoom(GetPropertyT_float(g_strategy->mpProps, 0xde67264f, 0.99f));
            }
        }
    }

    g_t2 = g_t2 - dt;
    if (g_t2 <= 0.0f || flag) {
        g_t2 = 2.5f;
        cProfile* profile = FUN_00401090()->GetAvatarProfile();
        cOwner* herd = GetDesiredAvatarHerd(0);
        float ratio = aggro / PlanetModel()->GetRadius();
        float range2 = ratio * ratio;
        const Vec3* cam = g_minimap->GetOrigin();
        cGameDataResult* list = NounManager()->GetGameDataVector(FUN_00cd7d10, FUN_00d3d420, FUN_00bbf9b0,
                                                                  FUN_00b1e500, 0x52aa6122);
        void** end = list->mpEnd;
        for (void** it = list->mpBegin; it != end; ++it) {
            cMiniObj* e = (cMiniObj*)*it;
            cOwner* owner = e->mpOwner;
            if (owner != avatar->GetInfo()) {
                cOwner* o2 = e->mpOwner;
                if (g_169e370 < o2->mRangeMin || g_169e370 > o2->mRangeMax) {
                    continue;
                }
            }
            cSpatialObject* sp = &e->mSub;
            const Vec3* p = sp->GetPosition();
            float px = p->x, py = p->y, pz = p->z;
            float n = 1.0f / sqrtf(((px * px + py * py) + pz * pz) + 1e-08f);
            float qx = px * n - cam->x, qy = py * n - cam->y, qz = pz * n - cam->z;
            float d2 = (qz * qz + qy * qy) + qx * qx;
            if (!(range2 > d2) && e->mpOwner != herd) {
                if (!e->mFlagA9 || sp->IsHidden()) {
                    g_minimap->RemoveIcon(e, 1, 0);
                    continue;
                }
            }
            uint32_t flags = (e->mFlags124 & 1) ? 0x20 : 0x80020;
            bool sel = false;
            cOwner* ow = e->mpOwner;
            if (ow->mFlag191 || ow->mProfile == (int)profile) {
                flags |= 0x200000;
            }
            if (ow->mFlag190) {
                flags |= 0x100000;
            }
            if (ow == herd || sp->IsHidden()) {
                flags |= 8;
                sel = e->mpOwner == herd;
            }
            cIconInfo* ic = g_minimap->FindIcon(e);
            if (ic && ic->mFlags == flags) {
                if (g_minimap->UpdateIcon(e, sp->GetPosition(), sel)) {
                    continue;
                }
            }
            g_minimap->RemoveIcon(e, 1, 0);
            cIconInfo info;
            info.mColor = 0;
            info.mPos.x = 0.0f;
            info.mPos.y = 0.0f;
            info.mPos.z = -1.0f;
            info.mFlags = flags;
            info.mTimeout = 0.0f;
            info.mAnimState = 0;
            info.m20 = 0;
            if (flags & 8) {
                if (e == herd->mpLead) {
                    cSpeciesData* sd = avatar->mpSpecies;
                    int r = RoundToInt(sd->mR * 255.0f);
                    int g = RoundToInt(sd->mG * 255.0f);
                    int b = RoundToInt(sd->mB * 255.0f);
                    info.mColor = PackARGB(0xff, r, g, b);
                } else {
                    info.mColor = 0x7f000000;
                }
            }
            if ((flags & 0x100000) && !(flags & 0x80000)) {
                info.mColor = 0xffff0000;
            }
            info.mPos = *sp->GetPosition();
            info.mpObject.Assign(e);
            g_minimap->AddIcon(e, &info, 0, sel);
        }
    }

    Vec3 tmp;
    g_minimap->SetIconColor(pos, avatar->mSub.GetV5c(&tmp));
    if (g_flag2 || flag) {
        g_flag2 = 0;
        g_minimap->Clear(0x8000);
        cPlanetModel* pm = PlanetModel();
        int cont = pm->GetContinent(((cInfoB*)avatar->GetInfo())->GetKey());
        FixedPtrVec found;
        found.mpBegin = (void**)found.mBuf;
        found.mpEnd = found.mpBegin;
        found.mpCap = (void**)(found.mBuf + 8);
        found.mFlag = 0;
        FUN_00b3d440()->Run(pos, aggro * 1.5f, &found, 1, 0);
        void** gb = g_list.mpBegin;
        void** ge = g_list.mpEnd;
        memmove(gb, ge, 0);
        g_list.mpEnd = g_list.mpEnd - (ge - gb);
        g_list.Reserve((uint32_t)(found.mpEnd - found.mpBegin));
        for (void** q = found.mpBegin; q != found.mpEnd; ++q) {
            if (pm->GetContinent((uint32_t)*q) == cont) {
                if (g_list.mpEnd < g_list.mpCap) {
                    void** slot = g_list.mpEnd;
                    g_list.mpEnd = slot + 1;
                    if (slot) {
                        *slot = *q;
                    }
                } else {
                    g_list.DoInsert(g_list.mpEnd, q);
                }
            }
        }
        void** lo = g_list.mpBegin;
        void** hi = g_list.mpEnd - 1;
        while (lo < hi) {
            void* t = *lo;
            *lo = *hi;
            *hi = t;
            ++lo;
            --hi;
        }
        if (found.mpBegin && found.mpBegin[-1]) {
            operator delete[](found.mpBegin);
        }
    }

    g_t3 = g_t3 - dt;
    if (g_t3 <= 0.0f) {
        g_t3 = 1.0f;
        for (unsigned int i = 0; i < 1; ++i) {
            if (g_list.mpBegin == g_list.mpEnd) {
                break;
            }
            float* item = (float*)g_list.mpEnd[-1];
            void* kind = *(void**)(item + 4);
            if (!g_minimap->UpdateIcon(kind, (const Vec3*)item, 0)) {
                cIconInfo info;
                info.mColor = 0;
                info.mPos.x = item[0];
                info.mPos.y = item[1];
                info.mPos.z = item[2];
                info.mFlags = 0x8000;
                info.mTimeout = 0.0f;
                info.mAnimState = 0;
                info.m20 = 0;
                g_minimap->AddIcon(kind, &info, 0, 0);
            }
            g_list.mpEnd = g_list.mpEnd - 1;
        }
    }
    if (flag) {
        g_flag = 0;
        g_minimap->SetMode(4);
        g_minimap->UpdateMapTexture();
    }
}
