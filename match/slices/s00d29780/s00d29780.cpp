// Slice s00d29780: FUN_00d29ca0 (0x00D29CA0, 2170 bytes, __thiscall, plain ret).
// Creature-camera occluder fade: tests whether the camera anchor can see the avatar (a cheap
// line test, else a swept-volume test), eases the global fade factor up/down, moves the smoothed
// anchor, and then fades the materials of every occluding object found by the sweep: objects found
// now fade towards 0.1 and are remembered in the camera's set, objects that are no longer
// occluding fade back to 1.1 and are dropped from the set once they reach 1.0.
// Built /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (MSVC 2008 SP1).
#include <math.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

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
    virtual void s27(); virtual void s28();
    virtual float GetScale74();                   // slot 29 (+0x74): float returned in st(0)
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

struct cOccluderSet;
bool LineTest(const void* ctx, const Vec3* scale, cOccluderSet* out);  // 0x00d29780 (cdecl)
bool SweepTest(cSweepVolume* vol, int flag);                           // 0x00d29610 (cdecl)

// ---- occluder set (eastl::set<AutoRefCount<cOccluder>>) -------------------------------------------
struct cOccluder;
struct cPropValue {
    union {
        char* mpData;                             // +0x00 (heap buffer when mFlags & 0x30)
        char  mInline[0x10];                      // +0x00 (inline buffer otherwise)
    };
    u8  mFlags;                                   // +0x10
    u8  mPad11;                                   // +0x11
    u16 mType;                                    // +0x12
};
struct cPropHolder {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8();
    virtual bool Query(u32 key, cPropValue** out); // slot 9 (+0x24)
};
struct cMaterialFade {
    u32 pad0;
    u32 mFlags;                                   // +4  (bit 1 = fading)
    char pad8[0x58 - 8];
    float mAlpha;                                 // +0x58
    char pad5c[0x90 - 0x5c];
    cPropHolder* mp90;                            // +0x90
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
struct RBNodeBase {                               // eastl rbtree_node_base, 0x10 bytes
    RBNodeBase* right;                            // +0x00
    RBNodeBase* left;                             // +0x04
    RBNodeBase* parent;                           // +0x08
    u32 color;                                    // +0x0c
};
struct RBNode : RBNodeBase {
    cOccluder* value;                             // +0x10
};
RBNode* RBTreeIncrement(RBNode* n);               // 0x00921580 (cdecl)
void RBTreeErase(RBNode* n, RBNode* anchor);      // 0x00921880 (cdecl)
struct RBTree {
    RBNodeBase mAnchor;                           // +0x00 header node (its value slot is the size)
    int mnSize;                                   // +0x10
    void DoNukeSubtree(RBNodeBase* n);            // 0x00cbae20
    __forceinline RBNode* begin() { return (RBNode*)mAnchor.left; }
    __forceinline RBNode* end() { return (RBNode*)&mAnchor; }
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
    void Insert(void* out, const void* key, int color); // 0x00cbae70 (ret 0xc)
    __forceinline RBNode* begin() { return mTree.begin(); }
    __forceinline RBNode* end() { return mTree.end(); }
    __forceinline RBNode* find(cOccluder* key)
    {
        RBNode* cand = mTree.end();
        for (RBNode* n = (RBNode*)mTree.mAnchor.parent; n; ) {
            if (n->value < key) {
                n = (RBNode*)n->right;
            } else {
                cand = n;
                n = (RBNode*)n->left;
            }
        }
        if (cand == mTree.end() || key < cand->value)
            return mTree.end();
        return cand;
    }
};
bool FindOccluders(const void* ctx, const Vec3* scale, cOccluderSet* out); // 0x00d299f0 (cdecl)

// ---- spatial query used by the occluder tests ------------------------------------------------------
struct SpVecAllocHeader {
    int mnCapacity;                               // +0x00
};
struct AutoRefVec {                               // eastl::vector<EA::AutoRefCount<cOccluder> >
    void** mpBegin;                               // +0x00
    void** mpEnd;                                 // +0x04
    void** mpCap;                                 // +0x08
    void Destroy();                               // 0x00ad92d0 (out of line)
};
struct cHandlerProvider {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14();
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
    virtual bool GetHandlers(const void* src, const void* query, AutoRefVec* out, int count); // slot 19 (+0x4c)
};
cHandlerProvider* GetHandlerProvider();           // 0x00b3d240
bool IsLiveHandler(void* h);                      // 0x00d20e70

// ---- creature-camera debug print --------------------------------------------------------------------
extern u8  gDebugEnabled;                         // 0x0169de84
extern Vec3 gDebugPos;                            // 0x0169deb0
extern u8  gDebugMatrixSrc[];                     // 0x0169df20
extern char gEmptyString16[];                     // 0x01667bac
extern const char gDebugFormat[];                 // 0x0147a400
struct cSPMatrix3 {
    float mData[9];                               // 3x3, 0x24 bytes
    void Assign(const void* src);                 // 0x0041cb40 (ret 4)
};
struct cDebugDrawable {
    void Draw(const void* desc);                  // 0x007c40f0 (ret 4)
};
struct EastlString {
    char* mpBegin;                                // +0x00
    char* mpEnd;                                  // +0x04
    char* mpCapacity;                             // +0x08
    u32   mPad0c;                                 // +0x0c (class is 0x10 bytes)
    __forceinline EastlString() {
        mpBegin = gEmptyString16;
        mpEnd = gEmptyString16;
        mpCapacity = gEmptyString16 + 1;
    }
    ~EastlString() {
        if (mpCapacity - mpBegin > 1 && mpBegin)
            operator delete(mpBegin);
    }
    void sprintf(const char* fmt, ...);           // 0x00472fe0
};
struct DebugDesc {
    u16 mType;                                    // +0x00
    u16 mFlags;                                   // +0x02
    Vec3 mPos;                                    // +0x04
    float mRadius;                                // +0x10
};

extern const float kPowBase;      // 0x01447a10 (double 0.1f)

class cCreatureCamera {
public:
    void UpdateOccluderFade();    // 0x00d29ca0
    void PrintDebug(void* obj);   // 0x00d2a520 (ret 4)

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

    RBNode* it = mFaded.begin();
    while (it != mFaded.end()) {
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
                    RBTreeErase(it, mFaded.end());
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

// Cheap line test: build a small query volume in front of the avatar and let the handler provider fill
// `out` with everything it overlaps.  Returns true as soon as an occluder is found when `out` is null.
// @ 0x00d29780
bool LineTest(const void* ctx, const Vec3* scale, cOccluderSet* out)
{
    cAvatarComp* comp = &NounManager()->GetAvatar()->mComp;
    const Vec3* pos = comp->GetPosition();
    float inv = 1.0f / sqrtf(pos->x * pos->x + pos->y * pos->y + pos->z * pos->z + 1e-8f);
    Vec3 an(pos->x * inv, pos->y * inv, pos->z * inv);
    const float* bb = comp->GetBounds();
    float dh = bb[5] - bb[2];
    float s = comp->GetScale74();
    float h = dh * 0.7f;
    Vec3 sc(scale->x * s, scale->y * s, scale->z * s);
    Vec3 off(an.x * h, an.y * h, an.z * h);
    const Vec3* p = comp->GetPosition();
    Vec3 center(p->x + off.x - sc.x, p->y + off.y - sc.y, p->z + off.z - sc.z);

    AutoRefVec vec;
    vec.mpBegin = 0;
    vec.mpEnd = 0;
    vec.mpCap = 0;
    GetHandlerProvider()->GetHandlers(ctx, &center, &vec, 4);

    for (void** it = vec.mpBegin; it != vec.mpEnd; ++it) {
        cOccluder* o = (cOccluder*)*it;
        if (!IsLiveHandler(o))
            continue;
        if (out == 0) {
            vec.Destroy();
            return true;
        }
        void* key = o;
        if (o)
            o->AddRef();
        void* node[2];
        int color = 0;
        out->Insert(node, &key, color);
        if (o)
            o->Release();
    }

    bool result = false;
    if (out)
        result = out->mTree.mnSize != 0;
    for (void** r = vec.mpBegin; r < vec.mpEnd; ++r) {
        if (*r)
            ((cOccluder*)*r)->Release();
    }
    if (vec.mpBegin && ((SpVecAllocHeader*)vec.mpBegin - 1)->mnCapacity != 0)
        operator delete(vec.mpBegin);
    return result;
}

// Swept-volume variant: same query, but only occluders whose material carries a non-empty name property
// count as blockers.
// @ 0x00d299f0
bool FindOccluders(const void* ctx, const Vec3* scale, cOccluderSet* out)
{
    cAvatarComp* comp = &NounManager()->GetAvatar()->mComp;
    const Vec3* pos = comp->GetPosition();
    float inv = 1.0f / sqrtf(pos->x * pos->x + pos->y * pos->y + pos->z * pos->z + 1e-8f);
    Vec3 an(pos->x * inv, pos->y * inv, pos->z * inv);
    const float* bb = comp->GetBounds();
    float dh = bb[5] - bb[2];
    float s = comp->GetScale74();
    float h = dh * 0.7f;
    Vec3 sc(scale->x * s, scale->y * s, scale->z * s);
    Vec3 off(an.x * h, an.y * h, an.z * h);
    const Vec3* p = comp->GetPosition();
    Vec3 center(p->x + off.x - sc.x, p->y + off.y - sc.y, p->z + off.z - sc.z);

    AutoRefVec vec;
    vec.mpBegin = 0;
    vec.mpEnd = 0;
    vec.mpCap = 0;
    GetHandlerProvider()->GetHandlers(ctx, &center, &vec, 4);

    for (void** it = vec.mpBegin; it != vec.mpEnd; ++it) {
        cOccluder* o = (cOccluder*)*it;
        cMaterialFade* m = o->GetMaterial();
        if (!m)
            continue;
        cPropHolder* ph = m->mp90;
        if (!ph)
            continue;
        cPropValue* val = 0;
        if (!ph->Query(0x7c75761, &val))
            continue;
        if (val->mType != 1)
            continue;
        const char* str = (val->mFlags & 0x30) ? val->mpData : val->mInline;
        if (*str == 0)
            continue;
        if (out == 0) {
            vec.Destroy();
            return true;
        }
        void* key = o;
        o->AddRef();
        void* node[2];
        int color = 0;
        out->Insert(node, &key, color);
        o->Release();
    }

    bool result = false;
    if (out)
        result = out->mTree.mnSize != 0;
    for (void** r = vec.mpBegin; r < vec.mpEnd; ++r) {
        if (*r)
            ((cOccluder*)*r)->Release();
    }
    if (vec.mpBegin && ((SpVecAllocHeader*)vec.mpBegin - 1)->mnCapacity != 0)
        operator delete(vec.mpBegin);
    return result;
}

// Debug drawable for the creature camera: a point marker at the global debug position plus a text line.
// @ 0x00d2a520
void cCreatureCamera::PrintDebug(void* obj)
{
    if (!gDebugEnabled)
        return;
    if (!obj)
        return;

    DebugDesc desc;
    desc.mType = 0;
    desc.mFlags = 0;
    desc.mPos.x = gDebugPos.x;
    desc.mPos.y = gDebugPos.y;
    desc.mPos.z = gDebugPos.z;
    desc.mRadius = 1.0f;

    cSPMatrix3 mtx;
    mtx.Assign(gDebugMatrixSrc);

    ((cDebugDrawable*)obj)->Draw(&desc);

    EastlString str;
    str.sprintf(gDebugFormat, (double)desc.mPos.x, (double)desc.mPos.y, (double)desc.mPos.z);
}
