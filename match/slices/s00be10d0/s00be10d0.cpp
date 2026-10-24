// Slice s00be10d0 (gold7): SP planet-noun controller cluster.
//
// Eight retail functions of one class (`ecx` = this unless noted).  The object is a game noun
// that owns:
//   * an eastl::vector<AutoRefCount<ILogReporter>> log (bookkeeping header inlined at +0x1e0,
//     the erase-region begin/end pair at +0x1f4),
//   * three SPVector<AutoRefCount> lists  (+0x308, +0x340, +0x354),
//   * a 3-float position at +0x32c,
//   * a RefVec2 (0xc-byte elements) at +0x55c,
//   * an eastl::rbtree<int, pair<const int, string>> at +0x570,
//   * an ILogReporter* at +0x590,
//   * eastl::map<uint,uint> instances at +0x5a0 (map1), +0x5bc (map2), +0x5d8 (map3),
//   * an SP::cSPTimer at +0x5f8.
// Offsets recovered from the retail disassembly are named in the struct; only fields actually
// read or written are named.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-
#include "types.h"
#include <string.h>
#include <stddef.h>

typedef unsigned int        u32;
typedef unsigned char       u8;
typedef unsigned short      u16;
typedef          int        i32;
typedef          float      f32;
typedef unsigned __int64    u64;
typedef          __int64    i64;

// ---------------------------------------------------------------- object dispatch helpers
typedef void* (__thiscall* tc0_t)(void*);
typedef void* (__thiscall* tc1_t)(void*, void*);
static inline void* vt0(void* p, int slot) { return ((tc0_t*)(*(void***)p))[slot](p); }
static inline void* vt1p(void* p, int slot, void* a) { return ((tc1_t*)(*(void***)p))[slot](p, a); }
static inline void  addref(void* p) { if (p) vt0(p, 0); }
static inline void  relref(void* p) { if (p) vt0(p, 1); }

// ---------------------------------------------------------------- external helpers
void* SP_NounManager();                                              // 0xb3d300
void* SP_PlanetModel();                                             // 0xb3d350
void* SP_PendingObject();                                           // 0xb3d480 (-> [0x167eb3c])
void* FUN_00b25f40(int key);                                        // 0xb25f40 (nounMgr->GetNoun)
void* FUN_00b25fb0();                                               // 0xb25fb0 nounMgr->GetPlayerCivilization
void* FUN_00b20c60(u32 id);                                         // 0xb20c60 nounMgr->CreateNoun
void  FUN_00c41c60(void* a, void* b, int c);                        // 0xc41c60
// FUN_00ac8cd0 is __thiscall on the object returned by SP_PendingObject(): (this=obj, a, flag).
struct PendingObj { void ac8cd0(void* a, int b); };                 // 0xac8cd0
// cGameNounManager (as returned by SP_NounManager): members are __thiscall.
namespace SP {
struct cGameNounManager {
    void* GetNoun(int id);              // 0xb25f40
    void* CreateNoun(u32 id);           // 0xb20c60
};
}
// vtbl-bearing sub-object embedded in a noun (its first field is the vptr).
struct SubVObj { void* mpVtbl; };
typedef void* (__thiscall *MF0B)(void*);
typedef void  (__thiscall *MF0E)(void*, void*);
// A created noun: +0x34 is a vtbl-bearing sub-object, and it has a __thiscall
// method FUN_00bd2310(void* arg).
struct NounObj {
    char    pad00[0x34];
    SubVObj mSub34;
    void    FUN_00bd2310(void* arg);                                // 0xbd2310
};
// cSPTimer: 0x1c bytes; members are __thiscall.
struct cSPTimer {
    char pad[0x1c];
    void Restart();                                                 // 0xbc3130
    u64  GetElapsedTime();                                          // 0xbc3190
};
// Object returned by vtbl[3] of the noun's reporter; holds a back-pointer at +0x18.
struct HolderObj { char pad[0x18]; void* mpOwner; };
void* FUN_00b88590(void* model, const void* key);                   // 0xb88590 GetContinent
void  FUN_00be0730(void* refvec2);                                  // 0xbe0730
void* FUN_00be0790(void* tree, const void* key);                    // 0xbe0790
void  FUN_00ceed50(void* self, u32* out);                           // 0xceed50 (free; kept for other uses)
// FUN_00ceed50 is __thiscall on a global object at 0x169c255: (this, a, out).
struct Ceeder { void ceed50(void* a, u32* out); };                  // 0xceed50
#define kCeeder ((Ceeder*)0x169c255)
void* FUN_00edafd0(void* end, const void* tmp);                     // 0xedafd0
void* FUN_00b8d420(void* p);                                        // 0xb8d420
void  FUN_00b86650(void* a, void* b);                               // 0xb86650
void  FUN_00b866f0(void* a, void* b);                               // 0xb866f0
void* FUN_00bef950(void* out);                                      // 0xbef950 (profile from key)
void  FUN_00e3c7c0(void* a, u32 b);                                 // 0xe3c7c0
void* FUN_00bd9480(void* self, void* out);                          // 0xbd9480
void  FUN_00bd2310(void* noun, void* self);                         // 0xbd2310
void  FUN_00bdbbb0(void* self);                                     // 0xbdbbb0
void  FUN_00bc3130(void* timer);                                    // 0xbc3130 cSPTimer::Restart
u64   FUN_00bc3190(void* timer);                                    // 0xbc3190 cSPTimer::GetElapsedTime
void* FUN_00e39fb0(void* tree, const void* key);                    // 0xe39fb0 rbtree<int>::find
void* FUN_00921580(void* node);                                     // 0x921580 RBTreeIncrement
void* FUN_00436ce0(const void* a, void* out);                       // 0x436ce0 Vector3_Normalize
char  FUN_0041dd30(const void* a, const void* b);                   // 0x41dd30 Vector3_NotEqual
int   FUN_00bd92d0(void* noun);                                     // 0xbd92d0
extern const f32 kTickThreshold;                                    // 0x169cb60
// ---------------------------------------------------------------- eastl containers (retail layout)
struct rbNodeBase {
    void* mpNodeRight;                  // +0x00
    void* mpNodeLeft;                   // +0x04
    void* mpNodeParent;                 // +0x08
    char  mColor;                       // +0x0c
    char  pad[3];
};

// eastl::map<u32,u32> node (key@+0x10, value@+0x14)
struct IntMapNode {
    rbNodeBase link;                    // +0x00
    i32 mKey;                           // +0x10
    i32 mValue;                         // +0x14
};

// eastl::map<u32,u32>
struct IntTreeMap {
    char       pad0[4];                 // +0x00
    rbNodeBase mAnchor;                 // +0x04
    int        mnSize;                  // +0x14
    char       pad18[4];
    int& operator[](const int& k);      // 0x00643a40
};

// SPVector<AutoRefCount> (begin/end/cap of 4-byte pointers)
struct PtrVec {
    void** mpBegin;                     // +0x00
    void** mpEnd;                       // +0x04
    void** mpCapacity;                  // +0x08
    void   DoInsertPtr(void** position, void* const& value);     // 0xaea5d0
    void   erase(void** first, void** last);                     // 0xe25bd0
};

// RefVec2 element (0xc bytes)
struct RefVec2Elem {
    void* p0;                           // +0x00
    void* p4;                           // +0x04
    i32   f8;                           // +0x08
};
struct RefVec2 {
    RefVec2Elem* mpBegin;               // +0x00
    RefVec2Elem* mpEnd;                 // +0x04
    RefVec2Elem* mpCapacity;            // +0x08
};

struct Vec3 { f32 x, y, z; };
extern const Vec3 kOrigin;                                          // 0x168bd70 (.70/.74/.78)

// ---------------------------------------------------------------- the class
class cSPPlanetNoun {
public:
    char   pad00[0x6c];
    u8     mFlag6c;                     // +0x6c  dirty flag

    char   pad6d[0xb3];
    SubVObj mSub120;                    // +0x120 vtbl-bearing sub-object
    char   pad124[0xb4];

    i32    mnLogA;                      // +0x1d8
    i32    mnLogB;                      // +0x1dc
    void*  mpA1e0;                      // +0x1e0
    void*  mpA1e4;                      // +0x1e4
    char   pad1e8[0x0c];
    PtrVec mLogVec1f4;                  // +0x1f4 (erase target; begin@+0x1f4, end@+0x1f8)
    char   pad200[0x0c];
    f32    mf20c;                       // +0x20c
    f32    mf210;                       // +0x210
    i32    mn214;                       // +0x214

    char   pad218[0xf0];
    PtrVec mVec308;                     // +0x308
    char   pad314[0x18];
    Vec3   mPos32c;                     // +0x32c
    char   pad338[0x08];
    PtrVec mVec340;                     // +0x340
    char   pad34c[0x08];
    PtrVec mVec354;                     // +0x354
    char   pad360[0x1fc];
    RefVec2 mRefVec55c;                 // +0x55c
    char   pad568[0x08];

    IntTreeMap mTree570;                // +0x570 rbtree<int,pair<const int,string>> (anchor @ +0x574)
    char   pad58c[0x04];
    void*  mpLog590;                    // +0x590 ILogReporter*
    char   pad594[0x0c];
    IntTreeMap map1;                    // +0x5a0 (mnSize @ +0x5b4)
    IntTreeMap map2;                    // +0x5bc
    IntTreeMap map3;                    // +0x5d8
    char   pad5f4[0x04];
    cSPTimer mTimer5f8;                 // +0x5f8
    char   pad614[0x38];
    i32    mn64c;                       // +0x64c

    void ResetLog();                                            // 0x00be10d0
    void SetLog(void* r);                                       // 0x00be1150
    void Tick1();                                               // 0x00be11f0
    int  Activate(cSPPlanetNoun* other, int flag);              // 0x00be1340
    void OnNoun(int id);                                        // 0x00be1820
    void* FUN_00bd92d0(void* noun);                             // 0xbd92d0
    void PushVec308(void* r);                                   // 0x00be1e80
    void PushVec340(void* r, int flag);                         // 0x00be1ef0
    void* MakeNoun();                                           // 0x00be1fb0
};

#define CHECK_OFFSET(T, m, off) \
    typedef char SBE_CHK_##m[(offsetof(T, m) == (off)) ? 1 : -1]

CHECK_OFFSET(cSPPlanetNoun, mFlag6c, 0x6c);
CHECK_OFFSET(cSPPlanetNoun, mSub120, 0x120);
CHECK_OFFSET(cSPPlanetNoun, mnLogA, 0x1d8);
CHECK_OFFSET(cSPPlanetNoun, mnLogB, 0x1dc);
CHECK_OFFSET(cSPPlanetNoun, mpA1e0, 0x1e0);
CHECK_OFFSET(cSPPlanetNoun, mpA1e4, 0x1e4);
CHECK_OFFSET(cSPPlanetNoun, mLogVec1f4, 0x1f4);
CHECK_OFFSET(cSPPlanetNoun, mf20c, 0x20c);
CHECK_OFFSET(cSPPlanetNoun, mf210, 0x210);
CHECK_OFFSET(cSPPlanetNoun, mn214, 0x214);
CHECK_OFFSET(cSPPlanetNoun, mVec308, 0x308);
CHECK_OFFSET(cSPPlanetNoun, mPos32c, 0x32c);
CHECK_OFFSET(cSPPlanetNoun, mVec340, 0x340);
CHECK_OFFSET(cSPPlanetNoun, mVec354, 0x354);
CHECK_OFFSET(cSPPlanetNoun, mRefVec55c, 0x55c);
CHECK_OFFSET(cSPPlanetNoun, mTree570, 0x570);
CHECK_OFFSET(cSPPlanetNoun, mpLog590, 0x590);
CHECK_OFFSET(cSPPlanetNoun, map1, 0x5a0);
CHECK_OFFSET(cSPPlanetNoun, map2, 0x5bc);
CHECK_OFFSET(cSPPlanetNoun, map3, 0x5d8);
CHECK_OFFSET(cSPPlanetNoun, mTimer5f8, 0x5f8);
CHECK_OFFSET(cSPPlanetNoun, mn64c, 0x64c);

#define VGETID(p) ((int(__thiscall*)(void*))((void**)*(void***)(p))[0x4c / 4])((void*)(p))

// ================================================================================
// @ 0x00be10d0
void cSPPlanetNoun::ResetLog()
{
    mnLogA = 0;
    mnLogB = -1;
    void* end = mpA1e4;
    void* begin = mpA1e0;
    memcpy(begin, end, 0);                       // retail: size = (char*)end - (char*)end == 0
    mpA1e4 = (char*)end - ((char*)end - (char*)begin);
    mLogVec1f4.erase(mLogVec1f4.mpBegin, mLogVec1f4.mpEnd);
    mf20c = 0.0f;
    mf210 = 0.0f;
    mn214 = 0;
}

// ================================================================================
// @ 0x00be1150
void cSPPlanetNoun::SetLog(void* r)
{
    void* old = mpLog590;
    if (r != old) {
        addref(r);
        mpLog590 = r;
        relref(old);
    }
    if (r != 0) {
        if (map1.mnSize == 0) {
            int id = VGETID(mpLog590);
            int v = mn64c;
            map1[id] = v;
            ((PendingObj*)SP_PendingObject())->ac8cd0(this, 1);
        }
        int v = VGETID(mpLog590);
        ((void(__thiscall*)(cSPPlanetNoun*, int))((void**)*(void***)this)[0x48 / 4])(this, v);
    }
}

// ================================================================================
// @ 0x00be11f0
void cSPPlanetNoun::Tick1()
{
    u64 t = mTimer5f8.GetElapsedTime();
    double elapsed = (double)t;
    if (!(elapsed > (double)kTickThreshold))
        return;
    mTimer5f8.Restart();
    int base = VGETID(mpLog590);
    IntMapNode* anchor = (IntMapNode*)&map1.mAnchor;     // +0x5a4
    for (IntMapNode* node = (IntMapNode*)map1.mAnchor.mpNodeLeft; node != anchor;
         node = (IntMapNode*)FUN_00921580(node)) {
        int key = node->mKey;
        int* val = &node->mValue;
        if (key != base && *val >= 1) {
            void* nobj = ((SP::cGameNounManager*)SP_NounManager())->GetNoun(key);
            if (nobj == 0) {
                map1[base] += *val;
                *val = 0;
            } else {
                u32 out = 0;
                kCeeder->ceed50(this, &out);
                if ((int)out > 0) {
                    int take = (int)out;
                    if (take > *val)
                        take = *val;
                    map1[base] += take;
                    map3[key] += take;
                    *val -= take;
                    ((PendingObj*)SP_PendingObject())->ac8cd0(this, 0);
                }
            }
        }
    }
}

// ================================================================================
// @ 0x00be1e80
void cSPPlanetNoun::PushVec308(void* r)
{
    if (r == 0)
        return;
    addref(r);
    PtrVec& v = mVec308;
    void** end = v.mpEnd;
    if (end < v.mpCapacity) {
        v.mpEnd = end + 1;
        if (end != 0) {
            *end = r;
            addref(r);
        }
    } else {
        void* tmp = r;
        v.DoInsertPtr(end, tmp);
        r = tmp;
    }
    relref(r);
}

// ================================================================================
// @ 0x00be1ef0
void cSPPlanetNoun::PushVec340(void* r, int flag)
{
    void* tmp = r;
    if (r != 0)
        addref(r);
    void** end = mVec340.mpEnd;
    if (end < mVec340.mpCapacity) {
        mVec340.mpEnd = end + 1;
        if (end != 0) {
            *end = r;
            if (r == 0)
                goto done;
            addref(r);
        }
    } else {
        mVec340.DoInsertPtr(end, tmp);
        tmp = r;
    }
    relref(tmp);
done:
    mFlag6c = 1;
    if (r != 0) {
        HolderObj* holder = (HolderObj*)(void*)vt1p(r, 3, (void*)0x135b1e8);
        if (holder != 0) {
            void* old = holder->mpOwner;
            if (old != this) {
                addref(this);
                holder->mpOwner = this;
                if (old != 0)
                    relref(old);
            }
        }
    }
    if (flag == 0)
        FUN_00bdbbb0(this);
}

// ================================================================================
// @ 0x00be1fb0
void* cSPPlanetNoun::MakeNoun()
{
    void* n = ((SP::cGameNounManager*)SP_NounManager())->CreateNoun(0x436f342);
    if (n == 0)
        return 0;
    void* esi = ((void*(__thiscall*)(void*, u32))((void**)*(void***)n)[0x0c / 4])(n, 0x436f315);
    if (esi != 0) {
        void* tmp = esi;
        addref(esi);
        void** end = mVec354.mpEnd;
        if (end < mVec354.mpCapacity) {
            mVec354.mpEnd = end + 1;
            if (end != 0) {
                *end = esi;
                addref(esi);
            }
        } else {
            mVec354.DoInsertPtr(end, tmp);
            tmp = tmp;
        }
        relref(tmp);
        ((NounObj*)esi)->FUN_00bd2310(this);
        NounObj* obj = (NounObj*)esi;
        SubVObj* sub34 = &obj->mSub34;
        void* sub34vt = sub34->mpVtbl;
        void* r = ((MF0B)((void**)mSub120.mpVtbl)[0x2c / 4])(&mSub120);
        ((MF0E)((void**)sub34vt)[0x38 / 4])(sub34, r);
    }
    return esi;
}

// ================================================================================
// @ 0x00be1820
void cSPPlanetNoun::OnNoun(int id)
{
    void* n = ((SP::cGameNounManager*)SP_NounManager())->GetNoun(id);
    if (n == 0)
        return;
    void* d = this->FUN_00bd92d0(n);
    if (d == 0)
        return;
    Activate((cSPPlanetNoun*)d, 0);
}

// ================================================================================
// @ 0x00be1340
int cSPPlanetNoun::Activate(cSPPlanetNoun* other, int flag)
{
    VGETID(mpLog590);
    int otherId = VGETID(other->mpLog590);
    int* found = (int*)FUN_00e39fb0(&mTree570, &otherId);
    if (*(void**)found == (void*)&mTree570.mAnchor) {
        float* slot = (float*)FUN_00be0790(&mTree570, &otherId);
        *slot = 0.0f;
    }
    if (SP_PlanetModel() != 0 && flag == 0) {
        Vec3 pa, pb;
        Vec3* r = (Vec3*)((void*(__thiscall*)(cSPPlanetNoun*, Vec3*))((void**)*(void***)this)[0x58 / 4])(this, &pa);
        int ca = (int)FUN_00b88590(SP_PlanetModel(), r);
        Vec3* r2 = (Vec3*)((void*(__thiscall*)(cSPPlanetNoun*, Vec3*))((void**)*(void***)other)[0x58 / 4])(other, &pb);
        int cb = (int)FUN_00b88590(SP_PlanetModel(), r2);
        if (ca != cb) {
            Vec3 va = mPos32c;                    // a-side position (fStack_30/2c/28)
            Vec3 vb = other->mPos32c;             // b-side position (fStack_3c/38/34)
            if ((va.x == kOrigin.x && va.y == kOrigin.y && va.z == kOrigin.z) ||
                FUN_0041dd30(&vb, &kOrigin) == 0) {
                flag = 2;
            } else {
                Vec3 na, nb;
                Vec3* pf = (Vec3*)FUN_00bd9480(this, &na);
                na.x = mPos32c.x - pf->x;
                na.y = mPos32c.y - pf->y;
                na.z = mPos32c.z - pf->z;
                Vec3* nn = (Vec3*)FUN_00436ce0(&na, &nb);
                va.x = nn->x * 15.0f + va.x;
                va.y = nn->y * 15.0f + va.y;
                va.z = nn->z * 15.0f + va.z;
                Vec3* qf = (Vec3*)FUN_00bd9480(other, &nb);
                na.x = other->mPos32c.x - qf->x;
                na.y = other->mPos32c.y - qf->y;
                na.z = other->mPos32c.z - qf->z;
                Vec3* qn = (Vec3*)FUN_00436ce0(&na, &nb);
                vb.x = qn->x * 15.0f + vb.x;
                vb.y = qn->y * 15.0f + vb.y;
                vb.z = qn->z * 15.0f + vb.z;
                int ia = (int)FUN_00b88590(SP_PlanetModel(), &va);
                int ib = (int)FUN_00b88590(SP_PlanetModel(), &vb);
                flag = (ia != ib) + 1;
            }
        }
    }
    void* obj = 0;
    if (flag == 0) {
        void* n = FUN_00b20c60(0x2b8a4e7);
        if (n != 0) {
            void* x = ((void*(__thiscall*)(void*, u32))((void**)*(void***)n)[0x0c / 4])(n, 0x2bca14b);
            obj = x;
            if (x != 0)
                FUN_00c41c60(this, other, 1);
        }
    }
    FUN_00be0730(&mRefVec55c);
    RefVec2Elem* endA = mRefVec55c.mpEnd;
    {
        RefVec2Elem* slotA = endA - 1;
        void* old = slotA->p0;
        if (slotA->p0 != (void*)this) {
            addref(this);
            slotA->p0 = this;
            relref(old);
        }
        void* old2 = slotA->p4;
        if (obj != old2) {
            addref(obj);
            slotA->p4 = obj;
            relref(old2);
        }
        slotA->f8 = flag;
    }
    FUN_00be0730(&other->mRefVec55c);
    RefVec2Elem* endB = other->mRefVec55c.mpEnd;
    {
        RefVec2Elem* slotB = endB - 1;
        void* old = slotB->p0;
        if (slotB->p0 != (void*)this) {
            addref(this);
            slotB->p0 = this;
            relref(old);
        }
        void* old2 = slotB->p4;
        if (obj != old2) {
            addref(obj);
            slotB->p4 = obj;
            relref(old2);
        }
        slotB->f8 = flag;
    }
    if (SP_PlanetModel() != 0) {
        if (flag == 0)
            FUN_00b8d420(endA[-1].p4);
        else if (flag == 1)
            FUN_00b86650(this, other);
        else if (flag == 2)
            FUN_00b866f0(this, other);
    }
    char a = *(char*)(*(int*)((char*)this + 0x590) + 0x89);
    int ol = *(int*)((char*)other + 0x590);
    void* k1; void* k2;
    if (a == 0) {
        if (*(char*)(ol + 0x89) == 0)
            return flag;
        k1 = *(void**)((char*)this + 0x590 + 0x40);
        k2 = *(void**)((char*)FUN_00b25fb0() + 0x40);
    } else {
        if (*(char*)(ol + 0x89) == 0) {
            k1 = *(void**)(ol + 0x40);
            k2 = *(void**)((char*)FUN_00b25fb0() + 0x40);
        } else {
            return flag;
        }
    }    {
        Vec3 zero = { 0.0f, 0.0f, 0.0f };
        void* key;
        FUN_00bef950(&zero);
        void* p = FUN_00bef950(&zero);
        void* civ = FUN_00b25fb0();
        FUN_00e3c7c0((void*)0x3f5a88f8, (u32)p);
    }
    (void)k1; (void)k2; (void)obj;
    return flag;
}
