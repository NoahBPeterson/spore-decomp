// Slice s00d29780: FUN_00d29ca0 (0x00D29CA0, 2170 bytes, __thiscall, plain ret).
// Creature-camera occluder fade: tests whether the camera anchor can see the avatar (a cheap
// line test, else a swept-volume test), eases the global fade factor up/down, moves the smoothed
// anchor, and then fades the materials of every occluding object found by the sweep: objects found
// now fade towards 0.1 and are remembered in the camera's set, objects that are no longer
// occluding fade back to 1.1 and are dropped from the set once they reach 1.0.
// Built /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (MSVC 2008 SP1).
#include <math.h>

typedef unsigned char u8;
typedef unsigned int  u32;

// 3-vector; the user copy ctor gives the movss copy flavour of the original, the implicit assignment
// stays a dword copy.
struct Vec3 {
    float x, y, z;
    Vec3() {}
    Vec3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    __forceinline Vec3(const Vec3& v) : x(v.x), y(v.y), z(v.z) {}
};
struct Quat { float x, y, z, w; };

Vec3* RotateByQuat(Vec3* out, const Vec3* v, const Quat* q);    // 0x0059aed0 (cdecl)

void operator delete(void*);

// ---- globals ------------------------------------------------------------------------------------
extern Vec3  gCameraForward;     // 0x0169df44
extern float gFade;              // 0x0169df6c (0 = fully faded out .. 1 = opaque)

// ---- avatar --------------------------------------------------------------------------------------
struct cAvatarComp {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10();
    virtual const Vec3* GetPosition();            // slot 11 (+0x2c)
    virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15(); virtual void s16();
    virtual void s17(); virtual void s18(); virtual void s19(); virtual void s20(); virtual void s21();
    virtual void s22(); virtual void s23(); virtual void s24(); virtual void s25();
    virtual const float* GetBounds();             // slot 26 (+0x68): [2] = min y, [5] = max y
};
struct cAvatar {
    char pad[0xc0];
    cAvatarComp mComp;                            // +0xc0
};
struct cGameNounManager {
    cAvatar* GetAvatar();                         // 0x00b1fdb0
};
cGameNounManager* NounManager();                  // 0x00b3d300

// ---- application / sweep volume --------------------------------------------------------------------
struct cAppSub {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6();
    virtual u32 GetKey();                         // slot 7 (+0x1c)
};
struct cApp {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual cAppSub* GetSub();                    // slot 20 (+0x50)
};
cApp* App();                                      // 0x0067dd10

// Convex sweep volume built from the camera anchor and the view direction (size 0xd8).
struct cSweepVolume {
    Vec3 mStart;                                  // +0x00
    Vec3 mDir;                                    // +0x0c
    Vec3 mAxis;                                   // +0x18  (mStart normalised)
    Vec3 mSide;                                   // +0x24  (normalised mAxis x mDir)
    char pad30[0x0c];
    Vec3 mEnd;                                    // +0x3c  (mStart + mDir)
    int* mpData;                                  // +0x48  (array begin; points at the inline buffer at +0x60)
    char pad4c[0xd8 - 0x4c];
    cSweepVolume(u32 key);                        // 0x00b16dc0
    __forceinline ~cSweepVolume() { if (mpData && mpData[-1]) operator delete(mpData); }
};

bool LineTest(const Vec3* from, const Vec3* dir, int flag);            // 0x00d29780 (cdecl)
bool SweepTest(cSweepVolume* vol, int flag);                           // 0x00d29610 (cdecl)

// ---- occluder set (eastl::set<AutoRefCount<cOccluder>>) -------------------------------------------
struct cOccluder;
struct cMaterialFade {
    u32 pad0;
    u32 mFlags;                                   // +4  (bit 1 = fading)
    char pad8[0x58 - 8];
    float mAlpha;                                 // +0x58
};
struct cOccluder {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
    virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23(); virtual void s24();
    virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28(); virtual void s29();
    virtual void s30(); virtual void s31(); virtual void s32(); virtual void s33(); virtual void s34();
    virtual void s35(); virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
    virtual void s40(); virtual void s41(); virtual void s42();
    virtual cMaterialFade* GetMaterial();         // slot 43 (+0xac)
    virtual void s44(); virtual void s45(); virtual void s46();
    virtual void AddRef();                        // slot 47 (+0xbc)
    virtual void Release();                       // slot 48 (+0xc0)
};
struct RBNode {
    RBNode* right;                                // +0
    RBNode* left;                                 // +4
    RBNode* parent;                               // +8
    u32 color;                                    // +0xc
    cOccluder* value;                             // +0x10
};
RBNode* RBTreeIncrement(RBNode* n);               // 0x00921580 (cdecl)
void RBTreeErase(RBNode* n, RBNode* anchor);      // 0x00921880 (cdecl)
struct RBTree {
    RBNode mAnchor;                               // +0x00 (value slot unused)
    int mnSize;
    void DoNukeSubtree(RBNode* n);                // 0x00cbae20
};
struct cOccluderSet {
    u32 mAllocator;                               // +0
    RBTree mTree;                                 // +4
    __forceinline cOccluderSet() {
        mTree.mAnchor.right = 0; mTree.mAnchor.left = 0; mTree.mAnchor.parent = 0; mTree.mAnchor.color = 0;
        mTree.mnSize = 0;
        mTree.mAnchor.right = &mTree.mAnchor; mTree.mAnchor.left = &mTree.mAnchor;
        mTree.mAnchor.parent = 0; mTree.mAnchor.color = 0; mTree.mnSize = 0;
    }
    __forceinline ~cOccluderSet() { mTree.DoNukeSubtree(mTree.mAnchor.parent); }
    void insert(RBNode* first, RBNode* last);     // 0x00d28e10 (ret 8)
    __forceinline RBNode* begin() { return mTree.mAnchor.left; }
    __forceinline RBNode* end() { return &mTree.mAnchor; }
    __forceinline RBNode* find(cOccluder* key)
    {
        RBNode* cand = &mTree.mAnchor;
        for (RBNode* n = mTree.mAnchor.parent; n; ) {
            if (n->value < key) {
                n = n->right;
            } else {
                cand = n;
                n = n->left;
            }
        }
        if (cand == &mTree.mAnchor || key < cand->value)
            return &mTree.mAnchor;
        return cand;
    }
};
bool FindOccluders(const Vec3* from, const Vec3* dir, cOccluderSet* out);   // 0x00d299f0 (cdecl)

extern const float kPowBase;      // 0x01447a10 (double 0.1f)

class cCreatureCamera {
public:
    void UpdateOccluderFade();    // 0x00d29ca0

    char pad0[0x1c];
    float mDt;                    // +0x1c
    char pad1[0xc4 - 0x20];
    Vec3 mOffset;                 // +0xc4
    char pad2[0x13c - 0xd0];
    Vec3 mAnchor;                 // +0x13c
    char pad3[0x154 - 0x148];
    Quat mOrientation;            // +0x154
    bool mbFading;                // +0x164
    char pad4[0x168 - 0x165];
    Vec3 mSmoothAnchor;           // +0x168
    char pad5[0x318 - 0x174];
    cOccluderSet mFaded;          // +0x318
};

// The module's SSE clamp helper (maxss/minss).
__forceinline float Clamp(float x, float lo, float hi)
{
    __asm {
        movss xmm0, x
        maxss xmm0, lo
        minss xmm0, hi
        movss x, xmm0
    }
    return x;
}

// Is `dir` (from `from`) free of occluders?  Cheap line test first, then the swept-volume test.
static __forceinline bool CanSee(const Vec3* pFrom, const Vec3& dir)
{
    if (LineTest(pFrom, &dir, 0))
        return true;
    cSweepVolume vol(App()->GetSub()->GetKey());
    Vec3 a = *pFrom;
    float inv = 1.0f / sqrtf(a.x * a.x + a.y * a.y + a.z * a.z + 1e-8f);
    vol.mStart = *pFrom;
    vol.mDir = dir;
    Vec3 an(a.x * inv, a.y * inv, a.z * inv);
    float cx = an.z * dir.y - an.y * dir.z;
    float cy = dir.z * an.x - an.z * dir.x;
    float cz = an.y * dir.x - dir.y * an.x;
    vol.mAxis = an;
    float inv2 = 1.0f / sqrtf(cx * cx + cz * cz + cy * cy + 1e-8f);
    vol.mEnd.x = a.x + dir.x;
    vol.mEnd.y = a.y + dir.y;
    vol.mEnd.z = a.z + dir.z;
    vol.mSide = Vec3(cx * inv2, cy * inv2, cz * inv2);
    return SweepTest(&vol, 0);
}

// @ 0x00D29CA0
void cCreatureCamera::UpdateOccluderFade()
{
    cAvatar* avatar = NounManager()->GetAvatar();
    if (!avatar)
        return;

    Vec3 tmp;
    Vec3 dir = *RotateByQuat(&tmp, &gCameraForward, &mOrientation);

    bool visible = CanSee(&mAnchor, dir);
    const Vec3* from = mbFading ? &mSmoothAnchor : &mAnchor;
    if (!visible) {
        gFade = Clamp(mDt + gFade, 0.0f, 1.0f);
    } else if (gFade > 0.0f) {
        if (!CanSee(from, dir))
            goto skip;
        gFade = Clamp(gFade - mDt * 3.0f, 0.0f, 1.0f);
    }
skip:
    mbFading = gFade < 1.0f;
    if (gFade < 1.0f) {
        cAvatarComp* comp = &avatar->mComp;
        const float* bounds = comp->GetBounds();
        float h = (bounds[5] - bounds[2]) * 0.7f;
        float ox = mOffset.x * h, oy = mOffset.y * h, oz = mOffset.z * h;
        const Vec3* pos = comp->GetPosition();
        float tx = pos->x + ox, ty = pos->y + oy, tz = pos->z + oz;
        float t = gFade;
        mSmoothAnchor.x = (mAnchor.x - tx) * t + tx;
        mSmoothAnchor.y = (mAnchor.y - ty) * t + ty;
        mSmoothAnchor.z = (mAnchor.z - tz) * t + tz;
    }

    cOccluderSet found;
    if (FindOccluders(from, &dir, &found) && found.begin() != found.end()) {
        for (RBNode* n = found.begin(); n != found.end(); n = RBTreeIncrement(n)) {
            cMaterialFade* m = n->value->GetMaterial();
            if (m) {
                m->mFlags |= 2;
                float old = m->mAlpha;
                m->mAlpha = (1.0f - (float)pow((double)kPowBase, (double)(mDt * 15.0f))) * (0.1f - old) + old;
            }
        }
    }

    RBNode* it = mFaded.mTree.mAnchor.left;
    while (it != &mFaded.mTree.mAnchor) {
        cOccluder* o = it->value;
        cMaterialFade* m = o->GetMaterial();
        if (m) {
            o->AddRef();
            bool notFound = found.find(o) == found.end();
            o->Release();
            if (notFound) {
                float old = m->mAlpha;
                float a = (1.0f - (float)pow((double)kPowBase, (double)(mDt * 15.0f))) * (1.1f - old) + old;
                m->mAlpha = a;
                if (!(a < 1.0f)) {
                    m->mAlpha = 1.0f;
                    m->mFlags &= ~2u;
                    --mFaded.mTree.mnSize;
                    RBNode* next = RBTreeIncrement(it);
                    RBTreeErase(it, &mFaded.mTree.mAnchor);
                    if (it->value)
                        it->value->Release();
                    operator delete(it);
                    it = next;
                    continue;
                }
            }
        }
        it = RBTreeIncrement(it);
    }

    mFaded.insert(found.begin(), found.end());
}
