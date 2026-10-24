// Slice s01046160 -- a Spore "material/property assignment" view helper class:
// its ctor/dtor, a per-frame property pump that walks the game-data view list,
// and two larger routines that build colour/vertex data and pick the best
// matching candidate from a renderable list.
//
//  0x01046160  cPropView::Pump_01046160            (ret 4)
//  0x010463b0  cPropView::Pump_010463b0            (ret 4)
//  0x010468f0  cPropView::Pump_010468f0            (ret 4)
//  0x01046e40  cPropView::cPropView                (ret)
//  0x01046eb0  cPropView::~cPropView               (ret)
//  0x01046f30  cPropView::Fill_01046f30            (ret 4)
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-  (MSVC 2008 SP1).
#include "types.h"
#include <math.h>
#include <string.h>

typedef unsigned int uint32_t;

// ---- raw callees -----------------------------------------------------------
void*  __cdecl FUN_01002bd0();                                        // 0x01002bd0
void*  __cdecl FUN_00a1ad60(void* a);                                 // 0x00a1ad60
void*  __cdecl FUN_00ffbe50();                                        // 0x00ffbe50
float  __cdecl FUN_00ffbfd0(void* a);                                 // 0x00ffbfd0
void*  __cdecl FUN_01021240(void* a, void* b);                        // 0x01021240
void*  __cdecl FUN_005c65e0(void* a);                                 // 0x005c65e0
void*  __cdecl FUN_00b3d2a0(void* a);                                 // 0x00b3d2a0
void*  __cdecl FUN_00bb1080(void* a);                                 // 0x00bb1080
bool   __cdecl FUN_01044bf0(void* a, void* b);                        // 0x01044bf0
void*  __cdecl FUN_0067ddd0();                                        // 0x0067ddd0
void*  __cdecl FUN_01045200(void* a, void* b, void* c);               // 0x01045200
void   __cdecl FUN_01045490(void* a, void* b, void* c, void* d);      // 0x01045490
void   __cdecl FUN_00f47380(void* p);                                 // 0x00f47380 (free)
void*  __cdecl FUN_00feb0f0(void* a);                                 // 0x00feb0f0
void*  __cdecl FUN_0067dd50();                                        // 0x0067dd50
void   __cdecl FUN_01045b90(void* a, int b, int c);                   // 0x01045b90
void   __cdecl FUN_01045a60(void* a, void* b, int c);                 // 0x01045a60
void*  __cdecl FUN_00996460(void* a);                                 // 0x00996460
void*  __cdecl FUN_0093a780(void* a, void* b, int c, int d);          // 0x0093a780
void   __cdecl FUN_00692f90(void* a, void* b, int c, int d);          // 0x00692f90
void   __cdecl FUN_00693e10(void* a, void* b);                        // 0x00693e10
void   __cdecl FUN_00ca09f0(void* a, int b);                          // 0x00ca09f0

// 010463b0
bool   __cdecl FUN_00bb9af0(void* a, int b);                          // 0x00bb9af0
void*  __cdecl FUN_01045120(void* a, void* b, void* c);               // 0x01045120
void*  __cdecl FUN_00ba6f20(void* a);                                 // 0x00ba6f20
void   __cdecl FUN_004e0880(void* a, int b);                          // 0x004e0880
void   __cdecl FUN_00455660(void* a, void* b, void* c);               // 0x00455660

// 010468f0
void*  __cdecl FUN_00feb9f0();                                        // 0x00feb9f0
bool   __cdecl FUN_00fecbf0(void* a);                                 // 0x00fecbf0
void*  __cdecl FUN_00b3d2c0();                                        // 0x00b3d2c0
void*  __cdecl FUN_00b3d300();                                        // 0x00b3d300
void*  __cdecl FUN_00f67d90(void* a);                                 // 0x00f67d90
void*  __cdecl FUN_01021090();                                        // 0x01021090
bool   __cdecl FUN_00c7a710(void* a, void* b);                        // 0x00c7a710
bool   __cdecl FUN_00d01f20(void* a, void* b, void* c);               // 0x00d01f20
void*  __cdecl FUN_00ba9370(void* a);                                 // 0x00ba9370
bool   __cdecl FUN_00c75d70(void* a, void* b, void* c);               // 0x00c75d70
void*  __cdecl FUN_00c308d0(void* a);                                 // 0x00c308d0
void*  __cdecl FUN_00bba790(void* a);                                 // 0x00bba790
int    __cdecl FUN_00b8dab0(void* a);                                 // 0x00b8dab0
bool   __cdecl FUN_00fee3d0(void* a, void* b, void* c);               // 0x00fee3d0
float  __cdecl FUN_010434c0(void* a, void* b);                        // 0x010434c0
bool   __cdecl FUN_00bba870(void* a, int b);                          // 0x00bba870
void*  __cdecl FUN_00921580(void* a);                                 // 0x00921580

// ---- globals ---------------------------------------------------------------
extern float g_13eb1bc;      // 0x013eb1bc
extern float g_1488874;      // 0x01488874
extern float g_1499dac;      // 0x01499dac
extern float g_1465544;      // 0x01465544

// ---- vtable slot helper ----------------------------------------------------
#define VF(o, off)  (*(void**)(*(char**)(o) + (off)))

// ---- small POD helpers -----------------------------------------------------
struct V3 { float x, y, z; };

struct VecPtr {                 // std::vector<ptr> header (12 bytes)
    void** mFirst;
    void** mLast;
    void** mEnd;
};

struct PropReq {                // stack request descriptor
    uint32_t mField00;
    uint32_t mField04;
    uint32_t mField08;
    float    mField0c;
    float    mField10;
    float    mField14;
    uint32_t mField18;
};

struct PropReq2 {               // larger stack request descriptor (010463b0)
    uint32_t mField00;
    uint32_t mField04;
    uint32_t mField08;
    float    mField0c;
    float    mField10;
    float    mField14;
    uint32_t mField18;
    uint32_t mField1c;
    uint8_t  mField20;
    uint8_t  mPad21[3];
};

// opaque item type whose tail fields are touched by the pumps
struct cMatItem {
    uint8_t  mPad00[0x70];
    void*    mpField70;         // +0x70
    uint8_t  mPad74[0x38];
    uint8_t  mFieldAc;          // +0xac
};

// reference-counted handle used inside the material/binding walkers
struct cHandle {
    void*    mpObj;             // +0x00
    uint32_t mField04;          // +0x04
    uint32_t mField08;          // +0x08
    uint32_t mField0c;          // +0x0c
    uint8_t  mField10;          // +0x10
    uint8_t  mPad11[3];
};

// ---- the sub-object at +0x20 ----------------------------------------------
struct cSub1 {
    uint32_t mData[10];         // +0x00 .. +0x27
    uint8_t  mPad28[4];         // +0x28 .. +0x2b
    void Init(int a);           // 0x00ca09f0
    void Destroy();             // 0x00996460
    void Zero() { for (int i = 0; i < 10; ++i) mData[i] = 0; }
};

// large stack scratch used by Fill_01046f30 (its first member receives the
// value produced by FUN_0093a780; the remainder is unreferenced padding).
struct cFillLocal {
    V3       mValue;            // +0x0000
    uint8_t  mPad[0x0a18 - 12]; // +0x000c
};

// ---- intrusive list at +0x5c ----------------------------------------------
struct cIntList {
    void*    mpNext;            // +0x00
    void*    mpHead;            // +0x04
    uint32_t mCount;            // +0x08
    union {
        uint32_t mFlag32;       // +0x0c
        uint8_t  mFlagByte;     // +0x0c
    };
    uint32_t mSize;             // +0x10
};

// ---- intrusive list node (touched at +0x18 by ~cPropView) ------------------
struct cNode {
    uint8_t  mPad00[0x18];
    void*    mpField18;         // +0x18
};

// ---- node walked by the container iterators --------------------------------
struct cListNode {
    uint8_t  mPad00[0x10];
    void*    mpField10;         // +0x10
};

// ---- game-data root and its view list --------------------------------------
struct cGameRoot {
    uint8_t  mPad00[0x30];
    void*    mpField30;         // +0x30 -> cViewList*
};
struct cViewList {
    uint8_t  mPad00[0x90];
    uint32_t mField90;          // +0x90
    void*    mpEnd;             // +0x94 (sentinel)
    void*    mpCur;             // +0x98
};

// ---- vector<float> (12-byte header) ----------------------------------------
struct VecF32 { float* mFirst; float* mLast; float* mEnd; };

// allocator header immediately preceding a vector buffer
struct cVecHdr { uint32_t mPool; };

// ---- generic container (begin/end) -----------------------------------------
struct cContainer { void** mFirst; void** mLast; };

// ---- the owning view class -------------------------------------------------
class cPropView {
public:
    cPropView();                                        // 0x01046e40
    ~cPropView();                                       // 0x01046eb0
    void Pump_01046160(uint32_t key);                   // 0x01046160
    void Pump_010463b0(uint32_t key);                   // 0x010463b0
    void Pump_010468f0(uint32_t key);                   // 0x010468f0
    void Fill_01046f30(void* arg);                      // 0x01046f30
    void Bind(void* cand, uint32_t key, uint32_t propKey);

    uint8_t   mFlag0;           // +0x00
    uint8_t   mFlag1;           // +0x01
    uint8_t   mPad02[2];        // +0x02
    void*     mArray[7];        // +0x04 .. +0x1f
    cSub1     mSub1;            // +0x20
    float     mField4c;         // +0x4c
    uint32_t  mField50;         // +0x50
    void*     mpField54;        // +0x54
    uint8_t   mPad58[4];        // +0x58
    cIntList  mList;            // +0x5c
    uint32_t  mField70;         // +0x70
    uint32_t  mField74;         // +0x74
};

// ===========================================================================
// 0x01046e40 -- constructor
// ===========================================================================
// @ 0x01046e40
cPropView::cPropView()
{
    uint32_t* q = mSub1.mData;

    mFlag0 = 0;
    mFlag1 = 0;

    q[0] = 0; q[1] = 0; q[2] = 0; q[3] = 0; q[4] = 0;
    q[5] = 0; q[6] = 0; q[7] = 0; q[8] = 0; q[9] = 0;

    mSub1.Init(0);

    mField4c = g_1465544;
    mField50 = 1;
    mpField54 = 0;

    cIntList* p = &mList;
    memset(&p->mpHead, 0, 0x0c);

    p->mpHead = p;
    p->mpNext = p;
    p->mCount = 0;
    p->mFlagByte = 0;
    p->mSize = 0;
}

// ===========================================================================
// 0x01046eb0 -- destructor / teardown
// ===========================================================================
// @ 0x01046eb0
cPropView::~cPropView()
{
    void* a = FUN_0067dd50();
    ((void(__thiscall*)(void*, int))VF(a, 0x50))(a, 0x17);

    ((void(__thiscall*)(void*))FUN_00feb0f0)((void*)0x016e0688);

    ((void(__thiscall*)(void*, int, int))FUN_01045b90)(this, 2, 0);

    if (mpField54 != 0) {
        ((void(__thiscall*)(void*, int))VF(mpField54, 0x0c))(mpField54, 0);

        if (mpField54 != 0) {
            void* p = mpField54;
            mpField54 = 0;
            ((void(__thiscall*)(void*))VF(p, 4))(p);
        }
    }

    while (mList.mSize != 0) {
        void* h = mList.mpHead;
        ((void(__thiscall*)(void*, void*, int))FUN_01045a60)
            (this, ((cNode*)h)->mpField18, 1);
    }

    ((void(__thiscall*)(void*))FUN_00996460)(&mSub1);
}

// ===========================================================================
// 0x01046f30 -- fill 7 array slots from the given object
// ===========================================================================
// @ 0x01046f30
void cPropView::Fill_01046f30(void* arg)
{
    ((void(__thiscall*)(void*, int, int))FUN_01045b90)(this, 4, 0);
    ((void(__thiscall*)(void*))FUN_00996460)(&mSub1);

    cFillLocal local;

    for (int i = 0; i < 7; ++i) {
        void* p = ((void*(__thiscall*)(void*))VF(arg, 0x20))(arg);
        void* q = ((void*(__thiscall*)(void*))VF(p, 0x18))(p);
        FUN_0093a780(q, &local.mValue, 1, 0);
        mArray[i] = *(void**)&local.mValue;
    }

    ((void(__thiscall*)(void*, void*, int, int))FUN_00692f90)
        (&local.mValue.y, this, 0x015b85a0, 0x01a80d26);
    ((void(__thiscall*)(void*, void*))FUN_00693e10)(&local.mValue.y, arg);
}

// ===========================================================================
// 0x01046160 -- property pump
// ===========================================================================
// @ 0x01046160
void cPropView::Pump_01046160(uint32_t key)
{
    void* w = FUN_01002bd0();
    void* g = ((void*(__thiscall*)(void*))FUN_00a1ad60)(w);
    if (g == 0)
        return;
    if (!((bool(__thiscall*)(void*, uint32_t))VF(g, 0x74))(g, 0x016e01a8u))
        return;

    VecPtr  vec;                                       // esp+0x2c
    PropReq req;                                       // esp+0x58
    vec.mFirst = 0;
    vec.mLast  = 0;
    vec.mEnd   = 0;
    req.mField04 = 0x3f;
    req.mField08 = 0;
    req.mField10 = g_13eb1bc;
    req.mField14 = g_13eb1bc;
    req.mField18 = 0;
    req.mField00 = 4;
    req.mField0c = g_13eb1bc;
    req.mField10 = ((float(__thiscall*)(void*))FUN_00ffbfd0)(FUN_00ffbe50());

    void* r = FUN_01021240(&req, &vec);
    void* s = ((void*(__thiscall*)(void*))FUN_005c65e0)(r);
    void* t = FUN_00b3d2a0(s);
    ((void(__thiscall*)(void*))FUN_00bb1080)(t);

    void** it  = vec.mFirst;
    void** end = vec.mLast;
    if (it == end)
        goto done;

    for (; it != end; ++it) {
        void*     obj = *it;
        cMatItem* mi  = (cMatItem*)obj;
        cHandle   h;

        mField74++;
        h.mpObj    = 0;
        h.mField04 = mField74;
        h.mField08 = key;
        h.mField0c = 1;
        h.mField10 = 0;

        if (key != 0x166521a5 && key != 0x70930c64 && key != 0xc3f6ca28) {
            if (((bool(__thiscall*)(void*, void*))FUN_01044bf0)(this, obj))
                goto keep;
            if (h.mpObj != 0) {
                void* p = h.mpObj;
                ((void(__thiscall*)(void*))VF(p, 4))(p);
            }
            continue;
        }

    keep:
        h.mField10 |= 2;
        void* d = FUN_0067ddd0();
        if (h.mpObj != 0) {
            void* p = h.mpObj;
            h.mpObj = 0;
            ((void(__thiscall*)(void*))VF(p, 4))(p);
        }
        bool ok = ((bool(__thiscall*)(void*, uint32_t, int, void*))VF(d, 0x2c))
                      (d, 0x28684c04u, 0, &h);
        if (!ok) {
            if (h.mpObj != 0) {
                void* p = h.mpObj;
                ((void(__thiscall*)(void*))VF(p, 4))(p);
            }
            continue;
        }
        {
            void* p = h.mpObj;
            ((void(__thiscall*)(void*, int))VF(p, 8))(p, 0);
        }
        FUN_01045200(this, &h, mi->mpField70);
        {
            cHandle h2 = h;
            if (h2.mpObj != 0) {
                void* p = h2.mpObj;
                ((void(__thiscall*)(void*))VF(p, 0))(p);
            }
        }
        FUN_01045490(&mPad58, &h, &h, 0);
        if (h.mpObj != 0) {
            void* p = h.mpObj;
            ((void(__thiscall*)(void*))VF(p, 4))(p);
        }
    }

done:
    {
        void** b = vec.mFirst;
        void** e = vec.mLast;
        while (b < e) {
            void* p = *b;
            if (p != 0)
                ((void(__thiscall*)(void*))VF(p, 4))(p);
            ++b;
        }
        if (vec.mFirst != 0 && ((cVecHdr*)vec.mFirst - 1)->mPool != 0)
            FUN_00f47380(vec.mFirst);
    }
}

// ===========================================================================
// ===========================================================================
// 0x010463b0 -- property pump (matrix / colour variant)
// ===========================================================================
static void PushF32(VecF32* v, float f)                 // vector<float> push_back
{
    if (v->mFirst < v->mLast)
        *v->mFirst++ = f;
    else
        FUN_00455660(v, v->mFirst, &f);
}

// @ 0x010463b0
void cPropView::Pump_010463b0(uint32_t key)
{
    void* w = FUN_01002bd0();
    void* g = ((void*(__thiscall*)(void*))FUN_00a1ad60)(w);
    if (g == 0)
        return;
    if (!((bool(__thiscall*)(void*, uint32_t))VF(g, 0x74))(g, 0x016e01a8u))
        return;

    VecPtr   vec;                                      // esp+0x64
    PropReq2 req;                                      // esp+0x90
    vec.mFirst = 0;
    vec.mLast  = 0;
    vec.mEnd   = 0;
    req.mField04 = 0x3f;
    req.mField08 = 0;
    req.mField10 = g_13eb1bc;
    req.mField14 = g_13eb1bc;
    req.mField18 = 0;
    req.mField00 = 4;
    req.mField0c = g_13eb1bc;
    req.mField10 = ((float(__thiscall*)(void*))FUN_00ffbfd0)(FUN_00ffbe50());

    void* r = FUN_01021240(&req, &vec);
    void* s = ((void*(__thiscall*)(void*))FUN_005c65e0)(r);
    void* t = FUN_00b3d2a0(s);
    ((void(__thiscall*)(void*))FUN_00bb1080)(t);

    void** it  = vec.mFirst;
    void** end = vec.mLast;
    if (it == end)
        goto done;

    for (; it != end; ++it) {
        cMatItem* mi = (cMatItem*)*it;
        if (!((bool(__thiscall*)(void*, int))FUN_00bb9af0)(mi, 0x10000))
            continue;

        cHandle h;
        mField74++;
        h.mpObj    = 0;
        h.mField04 = mField74;
        h.mField08 = key;
        h.mField0c = 1;
        h.mField10 = 0;

        if (key != 0x166521a5u && key != 0x70930c64u && key != 0xc3f6ca28u) {
            if (!((bool(__thiscall*)(void*, void*))FUN_01044bf0)(this, mi)) {
                if (h.mpObj != 0) {
                    void* p = h.mpObj;
                    ((void(__thiscall*)(void*))VF(p, 4))(p);
                }
                continue;
            }
        }

        h.mField10 |= 2;
        void* d = FUN_0067ddd0();
        if (h.mpObj != 0) {
            void* p = h.mpObj;
            h.mpObj = 0;
            ((void(__thiscall*)(void*))VF(p, 4))(p);
        }
        if (!((bool(__thiscall*)(void*, uint32_t, int, void*))VF(d, 0x2c))
                 (d, 0x4ac5fb61u, 0, &h)) {
            if (h.mpObj != 0) {
                void* p = h.mpObj;
                ((void(__thiscall*)(void*))VF(p, 4))(p);
            }
            continue;
        }
        {
            void* p = h.mpObj;
            ((void(__thiscall*)(void*, int))VF(p, 8))(p, 0);
        }
        FUN_01045200(this, &h, mi->mpField70);
        {
            cHandle hi = h;
            if (hi.mpObj != 0) {
                void* p = hi.mpObj;
                ((void(__thiscall*)(void*))VF(p, 0))(p);
            }
        }

        void* sel = FUN_01045120(this, h.mpObj, mi->mpField70);
        if (sel != 0) {
            float* ca = (float*)((void*(__thiscall*)(void*))FUN_005c65e0)(mi);
            float* cb = (float*)((void*(__thiscall*)(void*))FUN_005c65e0)
                            (((void*(__thiscall*)(void*))FUN_00ba6f20)(FUN_00b3d2a0(mi)));

            VecF32 tmp;
            tmp.mFirst = 0;
            tmp.mLast  = 0;
            tmp.mEnd   = 0;
            FUN_004e0880(&tmp, 0x1c5);

            V3 va;
            va.x = ca[0]; va.y = ca[1]; va.z = ca[2];
            V3 vb;
            vb.x = cb[0]; vb.y = cb[1]; vb.z = cb[2];

            float dx = vb.x - va.x;
            float dy = vb.y - va.y;
            float dz = vb.z - va.z;
            float len = 1.0f / (float)sqrt((double)(dx * dx + dy * dy + dz * dz));
            V3 n;
            n.x = dx * len * g_1488874;
            n.y = dy * len * g_1488874;
            n.z = dz * len * g_1488874;

            PushF32(&tmp, va.x);
            PushF32(&tmp, va.y);
            PushF32(&tmp, va.z);
            PushF32(&tmp, n.x);
            PushF32(&tmp, n.y);
            PushF32(&tmp, n.z);
            PushF32(&tmp, va.x);
            PushF32(&tmp, va.y);
            PushF32(&tmp, va.z);

            float* pd = (float*)FUN_00b3d2a0(mi);
            PushF32(&tmp, pd[0]);
            PushF32(&tmp, pd[1]);
            PushF32(&tmp, pd[2]);

            int nverts = (int)(tmp.mFirst - (float*)tmp.mFirst) + 4;
            ((void(__thiscall*)(void*, float*, int, int))VF(h.mpObj, 0x44))
                (h.mpObj, (float*)tmp.mFirst, nverts, 0);
            FUN_00f47380((float*)tmp.mFirst);
        }

        if (h.mpObj != 0) {
            void* p = h.mpObj;
            ((void(__thiscall*)(void*))VF(p, 4))(p);
        }
    }

done:
    {
        void** b = vec.mFirst;
        void** e = vec.mLast;
        while (b < e) {
            void* p = *b;
            if (p != 0)
                ((void(__thiscall*)(void*))VF(p, 4))(p);
            ++b;
        }
        if (vec.mFirst != 0 && ((cVecHdr*)vec.mFirst - 1)->mPool != 0)
            FUN_00f47380(vec.mFirst);
    }
}

// ===========================================================================
// 0x010468f0 -- property pump (candidate selection)
// ===========================================================================
// shared binding helper: record the candidate and emit the property-assign call.
void cPropView::Bind(void* candv, uint32_t key, uint32_t propKey)
{
    cMatItem* cand = (cMatItem*)candv;
    void*     p70  = cand->mpField70;
    cHandle   h;

    mField74++;
    h.mpObj    = 0;
    h.mField04 = mField74;
    h.mField08 = key;
    h.mField0c = 1;
    h.mField10 = 0;

    if (key != 0x166521a5u && key != 0x70930c64u && key != 0xc3f6ca28u) {
        if (!((bool(__thiscall*)(void*, void*))FUN_01044bf0)(this, cand)) {
            if (h.mpObj != 0) {
                void* p = h.mpObj;
                ((void(__thiscall*)(void*))VF(p, 4))(p);
            }
            return;
        }
    }

    h.mField10 |= 2;
    void* d = FUN_0067ddd0();
    if (h.mpObj != 0) {
        void* p = h.mpObj;
        h.mpObj = 0;
        ((void(__thiscall*)(void*))VF(p, 4))(p);
    }

    if (((bool(__thiscall*)(void*, uint32_t, int, void*))VF(d, 0x2c))(d, propKey, 0, &h)) {
        {
            void* p = h.mpObj;
            ((void(__thiscall*)(void*, int))VF(p, 8))(p, 0);
        }
        FUN_01045200(this, &h, p70);
        {
            cHandle copy;
            copy.mpObj    = p70;
            copy.mField04 = h.mField04;
            copy.mField08 = h.mField08;
            copy.mField0c = h.mField0c;
            copy.mField10 = h.mField10;
            if (h.mpObj != 0) {
                void* q = h.mpObj;
                ((void(__thiscall*)(void*))VF(q, 0))(q);
            }
            FUN_01045490(&mPad58, &copy, &h, 0);
        }
    }

    if (h.mpObj != 0) {
        void* p = h.mpObj;
        ((void(__thiscall*)(void*))VF(p, 4))(p);
    }
}

// @ 0x010468f0
void cPropView::Pump_010468f0(uint32_t key)
{
    // ---- phase 1: scan the game-data view list for the best renderable ----
    void* a = FUN_00feb9f0();
    if (((bool(__thiscall*)(void*))FUN_00fecbf0)(a)) {
        void* ctx = FUN_00b3d2c0();
        void* e1  = ((void*(__thiscall*)(void*))FUN_00f67d90)(FUN_00b3d300());
        void* e2  = FUN_01021090();
        void* clr = ((void*(__thiscall*)(void*))FUN_005c65e0)
                        (((void*(__cdecl*)())FUN_01021240)());

        cGameRoot* root = (cGameRoot*)FUN_01002bd0();
        cViewList* list = (cViewList*)root->mpField30;
        void** it  = (void**)list->mpCur;
        void** end = &list->mpEnd;

        while (it != end) {
            cListNode* node = (cListNode*)it;
            void* item = node->mpField10;
            if (item != e2
                && ((bool(__thiscall*)(void*, void*))FUN_00c7a710)(e1, item)
                && !((bool(__thiscall*)(void*, void*, void*))FUN_00d01f20)(ctx, item, e2)) {
                void* o = ((void*(__thiscall*)(void*))FUN_00ba9370)(FUN_00b3d2a0(item));
                if (o != 0
                    && ((bool(__thiscall*)(void*, void*, void*))FUN_00c75d70)(e1, o, 0)) {
                    void*        tag = FUN_00feb9f0();
                    cContainer*  cnt = (cContainer*)FUN_00c308d0(o);
                    float        best = g_1499dac;
                    void*        bestObj = 0;

                    for (void** p = cnt->mFirst; p != cnt->mLast; ++p) {
                        cMatItem* cand = (cMatItem*)*p;
                        if (cand->mFieldAc == 0)
                            continue;
                        cContainer* lst = (cContainer*)FUN_00bba790(cand);
                        for (void** k = lst->mFirst; k != lst->mLast; ++k) {
                            void* sub = *k;
                            if (FUN_00b8dab0(sub) == 5
                                && ((bool(__thiscall*)(void*, void*, void*))FUN_00fee3d0)(tag, o, sub)) {
                                float f = ((float(__thiscall*)(void*, void*))FUN_010434c0)
                                              (((void*(__thiscall*)(void*))FUN_005c65e0)(cand), clr);
                                if (f > best) {
                                    best    = f;
                                    bestObj = cand;
                                }
                            }
                        }
                    }

                    if (bestObj != 0)
                        Bind(bestObj, key, 0x57dfe741u);
                }
            }
            it = (void**)FUN_00921580(it);
        }
    }

    // ---- phase 2: build the colour/vertex request and bind every renderable ----
    VecPtr  vec;                                       // esp+0x7c
    PropReq req;                                       // esp+0x90
    vec.mFirst = 0;
    vec.mLast  = 0;
    vec.mEnd   = 0;
    req.mField04 = 0x3f;
    req.mField08 = 0;
    req.mField10 = g_13eb1bc;
    req.mField14 = g_13eb1bc;
    req.mField18 = 0;
    req.mField00 = 0x1ff1;
    req.mField0c = g_13eb1bc;
    req.mField10 = ((float(__thiscall*)(void*))FUN_00ffbfd0)(FUN_00ffbe50());

    void* r = FUN_01021240(&req, &vec);
    void* s = ((void*(__thiscall*)(void*))FUN_005c65e0)(r);
    void* t = FUN_00b3d2a0(s);
    ((void(__thiscall*)(void*))FUN_00bb1080)(t);

    for (void** it = vec.mFirst; it != vec.mLast; ++it) {
        void* obj = *it;
        if (((bool(__thiscall*)(void*, int))FUN_00bba870)(obj, 1))
            Bind(obj, key, 0x7a10d0cdu);
    }

    // ---- cleanup ----
    {
        void** b = vec.mFirst;
        void** e = vec.mLast;
        while (b < e) {
            void* p = *b;
            if (p != 0)
                ((void(__thiscall*)(void*))VF(p, 4))(p);
            ++b;
        }
        if (vec.mFirst != 0 && ((cVecHdr*)vec.mFirst - 1)->mPool != 0)
            FUN_00f47380(vec.mFirst);
    }
}
