// Slice s0097e1f0 -- EA::UTFWinControls::ImageCursorProvider dtor/ctor,
// eastl fixed_hash_map ctor, UI::InflateEffect / BiStateEffect (UTFWin effects),
// ProportionalLayout / SimpleLayout factories.
// (0x97e1f0 .. 0x97f130, 27 functions)
//
// Module flags: /O2 /MD /Gy /TP /GS- /arch:SSE /fp:fast  (UTFWin region; the
// effect functions mix x87 arithmetic with movss stores, see notes).

#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// unnamed retail callees / globals (address in the comment)
// ---------------------------------------------------------------------------
extern "C" {
    int    __cdecl FUN_009512c0();                                                 // 0x009512c0
    void*  __cdecl FUN_009512d0(int size, int align, const char* type, int grp);   // 0x009512d0
    void   __cdecl Del_00f47380(void* p);                                          // 0x00f47380  ??3@YAXPAX@Z
    void*  __cdecl Alloc_00921340(unsigned n);                                     // 0x00921340
}
void __fastcall FadeEffect_ctor(void* self);        // 0x00963db0
void __fastcall Sub_b380(void* self);               // 0x0096b380  ?Sub_b380@@YIXPAUWinDialog@@@Z
void __fastcall CursorWindow_ctor(void* self);      // 0x0097dad0  ?CursorWindow_ctor@@YAXPAX@Z
bool __fastcall WinDialog_DoMessage(void* self, void* unused, int* msg);   // 0x0096c430  __thiscall ret 4

#define VT(o, i) ((*(void***)(o))[i])
#define VCALL0(R, o, i)        (((R(__thiscall*)(void*))VT(o, i))(o))
#define VCALL1(R, o, i, A, a)  (((R(__thiscall*)(void*, A))VT(o, i))(o, a))
#define VCALL2(R, o, i, A, a, B, b) (((R(__thiscall*)(void*, A, B))VT(o, i))(o, a, b))

// ---------------------------------------------------------------------------
// stub types
// ---------------------------------------------------------------------------
struct IRef {                                   // ref-counted object: slot0 AddRef, slot1 Release
    virtual int AddRef() throw();
    virtual int Release() throw();
};

struct HNode;
struct CursorWindow;

struct WinRef {                                 // EA::AutoRefCount<CursorWindow>
    CursorWindow* mpObject;                     // +0
    WinRef() throw() : mpObject(0) {}
};

struct FixedPoolDesc {                          // fixed_pool_base + params, 5 dwords
    void*     mpHead;      // +0
    uintptr_t mpData;      // +4
    uintptr_t mpEnd;       // +8
    unsigned  mnNodeSize;  // +0xc
    uintptr_t mpBuckets;   // +0x10
    void init(void* p, unsigned size, unsigned nodeSize, unsigned align, int flag);  // 0x00921260
};

struct PolicyCalc { unsigned NextCount(unsigned n); };   // 0x009213c0

struct FixedHashTable {                         // eastl::hashtable<...ImageCursor...>
    int       pad0;                             // +0
    HNode**   mpBucketArray;                    // +4
    unsigned  mnBucketCount;                    // +8
    unsigned  mnElementCount;                   // +0xc
    unsigned  mPolicy[3];                       // +0x10 prime_rehash_policy (two floats + mask)
    HNode*    mpFreeList;                       // +0x1c
    int       pad20;                            // +0x20
    void*     mpPoolBegin;                      // +0x24
    void*     mpPoolEnd;                        // +0x28
    unsigned  mnNodeSize;                       // +0x2c
    void**    mpInlineBuckets;                  // +0x30
    void*     mInlineBuckets[65];               // +0x34
    char      mNodeBuffer[0x500];               // +0x138

    void DoFreeNodes(HNode** buckets, unsigned n);  // 0x0097e030
    void DoRehash(unsigned n);                      // 0x0097dc30
};

struct FixedMap : FixedHashTable {              // eastl::fixed_hash_map<unsigned,ImageCursor,64,64,1,...>
    struct HashT {};
    struct PredT {};
    FixedMap(const HashT& a, const PredT& b);   // 0x0097e2b0
    void HashtableInit(void* buckets, HashT h0, PredT* pb,
                       HashT* pa0, HashT h1, HashT* pa1, FixedPoolDesc* pool);
                                                 // 0x0097dcd0 (thiscall, 7 args)
};

struct ImageCursorProvider {                    // EA::UTFWinControls::ImageCursorProvider
    void*    mVptr;                             // +0
    void*    mSerVptr;                          // +4
    int      mRefCount;                         // +8
    FixedMap mCursorMap;                        // +0xc .. +0x644
    char     mMapPad[0x118];                    // +0x644 .. +0x75c
    WinRef   mpCursorWindow;                    // +0x75c
    ~ImageCursorProvider();                     // 0x0097e1f0
    ImageCursorProvider();                      // 0x0097e380
};

// ---------------------------------------------------------------------------
// @ 0x0097e1f0  EA::UTFWinControls::ImageCursorProvider::~ImageCursorProvider
// ---------------------------------------------------------------------------
ImageCursorProvider::~ImageCursorProvider()
{
    CursorWindow* p;

    *(void**)this = (void*)0x014433b8;
    *(void**)((char*)this + 4) = (void*)0x014433a0;
    p = mpCursorWindow.mpObject;
    if (p != 0) {
        mpCursorWindow.mpObject = 0;
        VCALL0(void, p, 1);
    }
    p = mpCursorWindow.mpObject;
    if (p != 0) {
        VCALL0(void, p, 1);
    }
    mCursorMap.DoFreeNodes(mCursorMap.mpBucketArray, mCursorMap.mnBucketCount);
    mCursorMap.mnElementCount = 0;
    if (mCursorMap.mnBucketCount > 1 && mCursorMap.mpBucketArray != (HNode**)mCursorMap.mpInlineBuckets) {
        HNode** buckets = mCursorMap.mpBucketArray;
        if (buckets >= (HNode**)mCursorMap.mpPoolBegin && buckets < (HNode**)mCursorMap.mpPoolEnd) {
            *(HNode**)buckets = mCursorMap.mpFreeList;
            mCursorMap.mpFreeList = (HNode*)buckets;
        } else {
            Del_00f47380(buckets);
        }
    }
    *(void**)this = (void*)0x013eb938;
    *(void**)((char*)this + 4) = (void*)0x013eb938;
}

// @ 0x0097e2b0  eastl::fixed_hash_map<...>::fixed_hash_map
FixedMap::FixedMap(const HashT& a, const PredT& b)
{
    FixedPoolDesc pool;
    void* end;
    void* buckets;
    unsigned need;

    pool.mpHead = 0;
    pool.init(&mNodeBuffer[0], 0x500, 0x14, 4, 0);
    end = &mNodeBuffer[0x500];
    pool.mpData = (uintptr_t)&mNodeBuffer[0];
    pool.mpEnd = (uintptr_t)end;
    pool.mnNodeSize = 0x14;
    pool.mpBuckets = (uintptr_t)&mInlineBuckets[0];
    buckets = Alloc_00921340(0x40);
    HashtableInit(buckets, a, (PredT*)&b, (HashT*)&a, a, (HashT*)&a, &pool);
    mPolicy[0] = 0x461c4000;
    mPolicy[1] = 0x40000000;
    mPolicy[2] = 0;
    mnElementCount = 0;
    need = ((PolicyCalc*)(void*)&mPolicy[0])->NextCount(0);
    if (mnBucketCount < need)
        DoRehash(need);
}

// @ 0x0097e380  EA::UTFWinControls::ImageCursorProvider::ImageCursorProvider
ImageCursorProvider::ImageCursorProvider() : mCursorMap(FixedMap::HashT(), FixedMap::PredT())
{
    CursorWindow* p;
    CursorWindow* old;
    int grp;

    *(void**)((char*)this + 4) = (void*)0x013fa72c;
    *(void**)this = (void*)0x014433b8;
    *(void**)((char*)this + 4) = (void*)0x014433a0;
    mRefCount = 0;
    mpCursorWindow.mpObject = 0;
    grp = FUN_009512c0();
    p = (CursorWindow*)FUN_009512d0(0x218, 4, (const char*)0x014433d4, grp);
    if (p != 0) {
        CursorWindow_ctor(p);
    } else {
        p = 0;
    }
    old = mpCursorWindow.mpObject;
    if (p != old) {
        if (p != 0)
            VCALL0(void, p, 0);
        mpCursorWindow.mpObject = p;
        if (old != 0)
            VCALL0(void, old, 1);
    }
}

// ---------------------------------------------------------------------------
// BiStateEffect / effect helpers
// ---------------------------------------------------------------------------
struct Sink33 {                                  // 3x4-ish matrix sink at 0x95ea30 (ret 4)
    void Apply(float* v);                        // 0x0095ea30
};

struct BiStateEffect {                           // UI::InflateEffect / GlideEffect base region
    void* mVptr;                                 // +0
    void* mSerVptr;                              // +4
    int   mRefCount;                             // +8
    void* mVptr12;                               // +0xc
    char  pad[0x64 - 0x10];
    float mValue;                                // +0x64
    void func88h(int unused, Sink33* sink, float t);   // 0x0097e5e0, thiscall ret 0xc
};

// @ 0x0097e5e0  UTFWin::BiStateEffect::func88h  (mix float -> clamped mix)
void BiStateEffect::func88h(int unused, Sink33* sink, float t)
{
    float v;
    float vec[3];

    v = (mValue - 1.0f) * t + 1.0f;
    if (fabsf(v) < 0.03f) {
        v = 0.03f;
    } else if (fabsf(1.0f - v) < 0.03f) {
        v = 1.0f;
    }
    vec[0] = v;
    vec[1] = v;
    vec[2] = 1.0f;
    sink->Apply(vec);
}

struct InflateEffect {                           // UI::InflateEffect : FadeEffect
    void* mVptr;                                 // +0
    void* mSerVptr;                              // +4
    int   mRefCount;                             // +8
    void* mVptr12;                               // +0xc
    char  pad[0x60 - 0x10];
    void* mVptr60;                               // +0x60
    float mValue;                                // +0x64
    InflateEffect();                             // 0x0097e690
};

// factory objects: CreateInstance is __thiscall(factory, unused, group) -> ret 8
struct BasicFactory_Inflate { void* CreateInstance(int unused, int grp); };
struct BasicFactory_Prop    { void* CreateInstance(int unused, int grp); };
struct BasicFactory_Simple  { void* CreateInstance(int unused, int grp); };

// @ 0x0097e690  UI::InflateEffect::InflateEffect
InflateEffect::InflateEffect()
{
    FadeEffect_ctor(this);
    const float one = *(const float*)0x01485720;
    *(void* volatile*)((char*)this + 0x60) = (void*)0x014426a0;
    *(void**)this = (void*)0x014434d0;
    *(void**)((char*)this + 4) = (void*)0x014434b8;
    *(void**)((char*)this + 0xc) = (void*)0x0144347c;
    *(void**)((char*)this + 0x60) = (void*)0x014435a0;
    mValue = one;
}

// @ 0x0097e710  EA::UTFWinControls::BasicFactory_InflateEffect::CreateInstance
extern const float g_kOne;                       // 0x01485720
void* BasicFactory_Inflate::CreateInstance(int unused, int grp)
{
    char* p;

    if (grp == 0)
        grp = FUN_009512c0();
    p = (char*)FUN_009512d0(0xb8, 8, (const char*)0x014435bc, grp);
    if (p != 0) {
        FadeEffect_ctor(p);
        float one = g_kOne;
        *(void* volatile*)(p + 0x60) = (void*)0x014426a0;
        *(void**)p = (void*)0x014434d0;
        *(void**)(p + 4) = (void*)0x014434b8;
        *(void**)(p + 0xc) = (void*)0x0144347c;
        *(void**)(p + 0x60) = (void*)0x014435a0;
        *(float*)(p + 0x64) = one;
        return p;
    }
    return 0;
}
// ---------------------------------------------------------------------------
// UiNodeShapes: the vtables used by the shape/area helpers below
// ---------------------------------------------------------------------------
struct INode {                                   // object reached via a window's slot 4
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual INode* Slot4();                      // +0x10
    char pad_;
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual void v9(); virtual void v10(); virtual void v11(); virtual void v12();
    virtual void v13();
    virtual const float* GetArea();              // +0x38
};

struct Sink14 {                                  // object at holder+0xc, slot 5 (0x14)
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4();
    virtual void Apply(const float* area, float* rect);   // +0x14
};

struct AreaHolder {                              // the `this` of 0x97e8a0
    virtual void v0(); virtual void v1(); virtual void v2();
    Sink14* GetSink() { return (Sink14*)*(void**)((char*)this + 0xc); }
};

// @ 0x0097e8a0  area transform helper (window slot4 -> GetArea -> sink slot5, then expand)
void __fastcall FUN_0097e8a0(AreaHolder* self, int unused, INode* node, float* rect)
{
    const float* area;
    float tmp[4];
    INode* inner;

    inner = node->Slot4();
    area = inner->GetArea();
    tmp[0] = area[0];
    tmp[1] = area[1];
    tmp[2] = area[2];
    tmp[3] = area[3];
    self->GetSink()->Apply(tmp, rect);
    if (rect[0] > rect[2])
        rect[2] = rect[0];
    if (rect[1] > rect[3])
        rect[3] = rect[1];
}

// flags byte lives at +4 of the layout object
struct LayoutFlags {
    void* mVptr;                                 // +0
    unsigned char mFlags;                        // +4
    char pad[3];
};

// @ 0x0097e920  layout area grow
void __fastcall Layout_Grow(LayoutFlags* self, int unused, float* a, float* b)
{
    if ((self->mFlags & 8) != 0) {
        b[2] = (a[2] - a[0]) + b[2];
        if ((self->mFlags & 4) == 0)
            b[0] = (a[2] - a[0]) + b[0];
    }
    if ((self->mFlags & 2) != 0) {
        b[3] = (a[3] - a[1]) + b[3];
        if ((self->mFlags & 1) == 0)
            b[1] = (a[3] - a[1]) + b[1];
    }
}

// @ 0x0097e990  layout area shrink
bool __fastcall Layout_Shrink(LayoutFlags* self, int unused, float* a, float* b)
{
    if ((self->mFlags & 8) != 0) {
        b[2] = b[2] - (a[2] - a[0]);
        if ((self->mFlags & 4) == 0)
            b[0] = b[0] - (a[2] - a[0]);
    }
    if ((self->mFlags & 2) != 0) {
        b[3] = b[3] - (a[3] - a[1]);
        if ((self->mFlags & 1) == 0)
            b[1] = b[1] - (a[3] - a[1]);
    }
    return true;
}

// @ 0x0097ea70  layout proportional scale (+)
void __fastcall Layout_ScaleUp(LayoutFlags* self, int unused, float* a, float* b)
{
    b[0] = (a[2] - a[0]) * *(float*)((char*)self + 4) + b[0];
    b[2] = (a[2] - a[0]) * *(float*)((char*)self + 0xc) + b[2];
    b[1] = (a[3] - a[1]) * *(float*)((char*)self + 8) + b[1];
    b[3] = (a[3] - a[1]) * *(float*)((char*)self + 0x10) + b[3];
}

// @ 0x0097eae0  layout proportional scale (-)
bool __fastcall Layout_ScaleDown(LayoutFlags* self, int unused, float* a, float* b)
{
    b[0] = b[0] - (a[2] - a[0]) * *(float*)((char*)self + 4);
    b[2] = b[2] - (a[2] - a[0]) * *(float*)((char*)self + 0xc);
    b[1] = b[1] - (a[3] - a[1]) * *(float*)((char*)self + 8);
    b[3] = b[3] - (a[3] - a[1]) * *(float*)((char*)self + 0x10);
    return true;
}

// @ 0x0097eb90  EA::UTFWinControls::BasicFactory_ProportionalLayout::CreateInstance
void* BasicFactory_Prop::CreateInstance(int unused, int grp)
{
    char* p;

    if (grp == 0)
        grp = FUN_009512c0();
    p = (char*)FUN_009512d0(0x20, 4, (const char*)0x01443780, grp);
    if (p != 0) {
    *(void* volatile*)(p + 4) = (void*)0x013fa72c;
    *(int*)(p + 8) = 0;
    *(void* volatile*)(p + 0xc) = (void*)0x014426a0;
    *(void**)p = (void*)0x014436f8;
    *(void**)(p + 4) = (void*)0x014436dc;
    *(void**)(p + 0xc) = (void*)0x014436c0;
    *(float*)(p + 0x1c) = 0.0f;
    *(float*)(p + 0x18) = 0.0f;
    *(float*)(p + 0x14) = 0.0f;
    *(float*)(p + 0x10) = 0.0f;
    return p;
    }
    return 0;
}

// @ 0x0097ec00  EA::UTFWinControls::BasicFactory_SimpleLayout::CreateInstance
void* BasicFactory_Simple::CreateInstance(int unused, int grp)
{
    char* p;

    if (grp == 0)
        grp = FUN_009512c0();
    p = (char*)FUN_009512d0(0x14, 4, (const char*)0x01443870, grp);
    if (p != 0) {
    *(void* volatile*)(p + 4) = (void*)0x013fa72c;
    *(int*)(p + 8) = 0;
    *(void* volatile*)(p + 0xc) = (void*)0x014426a0;
    *(void**)p = (void*)0x014437e8;
    *(void**)(p + 4) = (void*)0x014437cc;
    *(void**)(p + 0xc) = (void*)0x014437b0;
    *(unsigned char*)(p + 0x10) = 5;
    return p;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// WinMessageBox helpers (this == the IWinMessageBox sub-object at msgbox+0x338)
// ---------------------------------------------------------------------------
// WinMessageBox  (0x97ec90 .. 0x97efe0)
//
// SerUpdate / DoMessage are WinMessageBox members (this == the WinMessageBox).
// The remaining helpers are methods of the IWinMessageBox sub-object that lives
// at WinMessageBox+0x338, hence `this` is that sub-object and the dirty byte is
// written at `this - 0x128`.
// ---------------------------------------------------------------------------
struct MsgBoxSub {                               // IWinMessageBox sub-object
    void* mVptr;                                 // +0
    int   mType;                                 // +4
    void vt0();  void vt1();  void vt2();  void vt3();  void vt4();  void vt5();
    void vt6();  void vt7();  void vt8();  void vt9();  void vt10(); void vt11();
    void vt12(); void vt13(); void vt14(); void vt15(); void vt16(); void vt17();
    void vt18(); void vt19(); void vt20(); void vt21(); void vt22(); void vt23();
    void vt24(); void vt25(); void vt26(); void vt27(); void vt28(); void vt29();
    void vt30(); void vt31();
    void vt32();                                 // +0x80
    void vt33();                                 // +0x84
    void vt34();                                 // +0x88
    void SetType(int t);                         // 0x0097ed30, ret 4
    void Set8c(int v);                           // 0x0097ed60, ret 4
    void Set90(int v);                           // 0x0097ed80, ret 4
    void SetBorder0(float a, float b, float c, float d);   // 0x0097eda0, ret 0x10
    void SetBorder1(float a, float b, float c, float d);   // 0x0097ee10, ret 0x10
    void Set40(int v);                           // 0x0097ee50, ret 4
    void Set2c30(float a, float b);              // 0x0097ee70, ret 8
    void Set34(float v);                         // 0x0097ee90, ret 4
    void Set44(int v);                           // 0x0097eec0, ret 4
    void Set8(float v);                          // 0x0097eee0, ret 4
    void SetDrawable(IRef* p);                   // 0x0097efa0, ret 4
};

struct Msg {                                     // UTFWin::Message
    IRef*    source;                             // +0
    int      pad4;
    unsigned eventType;                          // +8
    unsigned subType;                            // +0xc
    int      pad10;
    int      id;                                 // +0x14
};

struct WinMessageBox {
    void*  mVptr;                                // +0
    void*  mSerVptr;                             // +4
    void*  mIWindowVptr;                         // +8
    char   pad0[0x34 - 0xc];
    void*  mInstanceId;                          // +0x34
    char   pad1[0x80 - 0x38];
    void*  mCommentBegin;                        // +0x80
    void*  mCommentEnd;                          // +0x84
    char   pad2[0x338 - 0x88];
    MsgBoxSub mSub;                              // +0x338
    char   pad3[0x40];                           // +0x340 .. +0x380
    IRef** mpButtonsBegin;                       // +0x380
    IRef** mpButtonsEnd;                         // +0x384

    void SerUpdate();                            // 0x0097ec90
    bool DoMessage(Msg* msg);                    // 0x0097efe0
};

// @ 0x0097ec90  EA::UTFWinControls::WinMessageBox::SerUpdate
void WinMessageBox::SerUpdate()
{
    MsgBoxSub* sub = &mSub;
    VCALL0(void, sub, 0x80 / 4);
    VCALL0(void, sub, 0x88 / 4);
    Sub_b380(this);
}

// @ 0x0097ed30  IWinMessageBox sub-object type setter
void MsgBoxSub::SetType(int t)
{
    if (mType != t) {
        mType = t;
        VCALL0(void, this, 0x80 / 4);
        VCALL0(void, this, 0x88 / 4);
    }
}

// @ 0x0097ed60
void MsgBoxSub::Set8c(int v) { *(int*)((char*)this + 0x8c) = v; *(unsigned char*)((char*)this - 0x128) = 1; }
// @ 0x0097ed80
void MsgBoxSub::Set90(int v) { *(int*)((char*)this + 0x90) = v; *(unsigned char*)((char*)this - 0x128) = 1; }
// @ 0x0097eda0
void MsgBoxSub::SetBorder0(float a, float b, float c, float d)
{ *(float*)((char*)this + 0xc) = a; *(float*)((char*)this + 0x10) = b; *(float*)((char*)this + 0x14) = c; *(float*)((char*)this + 0x18) = d; *(unsigned char*)((char*)this - 0x128) = 1; }
// @ 0x0097ee10
void MsgBoxSub::SetBorder1(float a, float b, float c, float d)
{ *(float*)((char*)this + 0x1c) = a; *(float*)((char*)this + 0x20) = b; *(float*)((char*)this + 0x24) = c; *(float*)((char*)this + 0x28) = d; *(unsigned char*)((char*)this - 0x128) = 1; }
// @ 0x0097ee50
void MsgBoxSub::Set40(int v) { *(int*)((char*)this + 0x40) = v; *(unsigned char*)((char*)this - 0x128) = 1; }
// @ 0x0097ee70
void MsgBoxSub::Set2c30(float a, float b)
{ *(float*)((char*)this + 0x2c) = a; *(float*)((char*)this + 0x30) = b; *(unsigned char*)((char*)this - 0x128) = 1; }
// @ 0x0097ee90
void MsgBoxSub::Set34(float v) { *(float*)((char*)this + 0x34) = v; *(unsigned char*)((char*)this - 0x128) = 1; }
// @ 0x0097eec0
void MsgBoxSub::Set44(int v) { *(int*)((char*)this + 0x44) = v; *(unsigned char*)((char*)this - 0x128) = 1; }
// @ 0x0097eee0
void MsgBoxSub::Set8(float v) { *(float*)((char*)this + 8) = v; *(unsigned char*)((char*)this - 0x128) = 1; }

// @ 0x0097efa0  WinMessageBox sub-object drawable setter (AutoRefCount field at +0x98)
void MsgBoxSub::SetDrawable(IRef* p)
{
    IRef* old = *(IRef**)((char*)this + 0x98);
    if (p != old) {
        if (p != 0)
            VCALL0(void, p, 0);
        *(IRef**)((char*)this + 0x98) = p;
        if (old != 0)
            VCALL0(void, old, 1);
    }
    *(unsigned char*)((char*)this - 0x128) = 1;
}

// @ 0x0097efe0  EA::UTFWinControls::WinMessageBox::DoMessage
bool WinMessageBox::DoMessage(Msg* msg)
{
    IRef** it;
    IRef* found;

    if (msg->eventType == 0x287259f6) {
        it = mpButtonsBegin;
        for (; it != mpButtonsEnd; ++it) {
            found = VCALL0(IRef*, *it, 0x10 / 4);        // button -> GetWindow()
            if (found != 0 && found == msg->source)
                goto found_it;
        }
        if (msg->subType == 0x4f0dd487) {
            if (mInstanceId != 0) {
                void* w = (char*)this + 4;
                if (VCALL1(bool, mInstanceId, 0x80 / 4, void*, w)) {
                    VCALL2(void, mInstanceId, 0x78 / 4, void*, w, int, 3);
                    return true;
                }
            }
            {
                struct { int pad0; int pad1; unsigned evt; void* text; int id; } local;
                local.evt = 0x8f4d1281;
                local.text = mCommentEnd ? mCommentEnd : mCommentBegin;
                local.id = 3;
                VCALL1(void, (char*)this + 4, 0x114 / 4, void*, &local);
            }
            return true;
        }
    }
    return WinDialog_DoMessage(this, 0, (int*)msg);

found_it:
    {
        void* w = (char*)this + 4;
        if (mInstanceId != 0) {
            if (VCALL1(bool, mInstanceId, 0x80 / 4, void*, w)) {
                unsigned id = VCALL0(unsigned, found, 0x1c / 4);
                VCALL2(void, mInstanceId, 0x78 / 4, void*, w, unsigned, id);
                return true;
            }
        }
        {
            struct { int pad0; int pad1; unsigned evt; void* text; int id; } local;
            local.evt = 0x8f4d1281;
            local.text = mCommentEnd ? mCommentEnd : mCommentBegin;
            local.id = (int)VCALL0(unsigned, found, 0x1c / 4);
            VCALL1(void, (char*)this + 4, 0x114 / 4, void*, &local);
        }
        return true;
    }
}

// ---------------------------------------------------------------------------
// WinGrid area computation (this == the WinGrid main object; the IWinGrid
// sub-object sits at this-0x20c)
// ---------------------------------------------------------------------------
struct WinGridBase {                             // the IWinGrid sub-object at grid-0x20c
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34();
    virtual void Slot35();                       // +0x8c
    virtual void v36();
    virtual void Slot37(float x, float y);       // +0x94
    virtual void Slot38(float* w, float* h);     // +0x98
    virtual void Slot39(float* x, float* y);     // +0x9c
};

struct GridScroll {                              // the scrolling-row object at grid+0x1c0
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void* Slot4();                       // +0x10  (4)
    virtual void v05(); virtual void v06();
    virtual void Slot7(int a);                   // +0x1c  (7)
    virtual void v08(); virtual void v09();
    virtual bool Slot26();                       // +0x28  (10)
    virtual void v11(); virtual void v12(); virtual void v13();
    virtual const float* GetArea();              // +0x38  (14)
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
    virtual void v19(); virtual void v20(); virtual void v21(); virtual void v22();
    virtual void v23(); virtual void v24(); virtual void v25();
    virtual void DrawRow(float x, float rowH);   // +0x68  (26)
};

struct WinGrid {                                 // the WinGrid main object (this)
    char  pad0[0x134];
    float mRowH;                                 // +0x134
    char  pad1[0x164 - 0x138];
    float mX;                                    // +0x164
    float mY;                                    // +0x168
    char  pad2[0x1c0 - 0x16c];
    GridScroll* mpScroll;                        // +0x1c0
    void UpdateArea();                           // 0x0097f130
};

// @ 0x0097f130  WinGrid::UpdateArea
void WinGrid::UpdateArea()
{
    WinGridBase* base = (WinGridBase*)((char*)this - 0x20c);
    float sw, sh, w, h;
    float limit;
    float x, y;
    float pos, height, drawX;
    GridScroll* row;
    const float* area;

    base->Slot35();
    base->Slot38(&sw, &sh);
    base->Slot39(&w, &h);
    limit = mRowH * 2.0f;
    x = mX;
    if (limit + mX < sw)
        x = sw;
    y = mY;
    if (limit + mY < sh)
        y = sh;

    if (mpScroll != 0) {
        row = (GridScroll*)mpScroll->Slot4();
        if (row->Slot26() & 1) {
            mpScroll->Slot7(0);
            row = (GridScroll*)mpScroll->Slot4();
            area = row->GetArea();
            pos = area[2] - area[0];
            row = (GridScroll*)mpScroll->Slot4();
            area = row->GetArea();
            height = area[3] - area[1];
            if (pos > x) {
                do {
                    if (pos <= height * 4.0f)
                        break;
                    if (pos > w) {
                        drawX = w;
                    } else {
                        drawX = pos - 10.0f;
                        if (x > pos - 10.0f)
                            drawX = x;
                    }
                    row = (GridScroll*)mpScroll->Slot4();
                    row->DrawRow(drawX, height);
                    mpScroll->Slot7(1);
                    row = (GridScroll*)mpScroll->Slot4();
                    area = row->GetArea();
                    height = area[3] - area[1];
                    pos = drawX;
                } while (pos > x);
            }
            y = (mRowH + height) + y;
            if (pos > x)
                x = pos;
        }
    }
    limit = mRowH * 2.0f;
    base->Slot37(limit + x, limit + y);
}
