// Slice s00559050: Editor ObjectTemplateDB / property-list destructor helpers.
// Unoptimized /Od module.
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

// ---------------------------------------------------------------------------
// Opaque helper types.  Only their size and the addresses of the entry points
// they expose matter here; the containers are otherwise byte blobs.
// ---------------------------------------------------------------------------

struct Alloc { char mTag; };   // allocator tag; the collection ctors ignore it

// eastl::VectorBase<ResourceKey> - 0xc bytes.
struct VectorBaseRK {
    uint32_t mBegin;      // +0x00
    uint32_t mEnd;        // +0x04
    uint32_t mCapacity;   // +0x08
    void Destroy();       // 0x005156b0
};

// 0x18-byte eastl vector_set.
struct VSet {
    void* mBegin;         // +0x00
    void* mEnd;           // +0x04
    void* mCapacity;      // +0x08
    void* mp0c;           // +0x0c
    void* mp10;           // +0x10
    void* mp14;           // +0x14
    void Init(const Alloc& a);   // 0x00540470
};

// 0x14-byte eastl vector_set (shorter instantiation, same initialiser).
struct VSet14 {
    void* mBegin;         // +0x00
    void* mEnd;           // +0x04
    void* mCapacity;      // +0x08
    void* mp0c;           // +0x0c
    void* mp10;           // +0x10
    void Init(const Alloc& a);   // 0x00540470
};

// eastl::rbtree<Key16> - 0x1c bytes.
struct RBTreeKey16 {
    void* mAnchor00;      // +0x00
    void* mAnchor04;      // +0x04
    void* mAnchor08;      // +0x08
    void* mp0c;           // +0x0c
    void* mAnchor10;      // +0x10
    void* mAnchor14;      // +0x14
    void* mAnchor18;      // +0x18
    void Init(const Alloc& a);   // 0x004b5980
};

// 0x1c-byte sub-block of Big (a small list head).
struct BigBlock { void* mWords[7]; };

// 0x58-byte fixed-size container.
struct Big {
    BigBlock mHead;       // +0x00
    BigBlock mMid;        // +0x1c
    void*    mTail[8];    // +0x38
    void Init();          // 0x00570870
};

// 4-byte linear-congruential RNG.
struct RandomLC {
    uint32_t mState;      // +0x00
    void SetSeed(int seed);      // 0x00936090
};

struct Vector3 {
    float x, y, z;
    void SetZero();       // 0x0056dec0
};

// A polymorphic object header: the vtable pointer lives at +0x00.
struct RefObj { void** mpVtbl; };

typedef void (__thiscall *VoidThunk)(void*);
typedef int  (__thiscall *IntThunk)(void*);

// ---------------------------------------------------------------------------
// vtable objects
// ---------------------------------------------------------------------------
extern void* vtbl_PropBaseA22[];             // 0x013ebcdc
extern void* vtbl_ITracerBase[];             // 0x013eb938
extern void* vtbl_cILayer[];                 // 0x013f1ab0
extern void* vtbl_PaintSystem[];             // 0x013eb394
extern void* vtbl_cListenerBase[];           // 0x013eb384
extern void* vtbl_hkReferencedObject[];      // 0x013ef094
extern void* vtbl_Editor_ObjectTemplateDB[]; // 0x013f4578
extern void* vtbl_ObjectTemplateDB_04a[];    // 0x013f4544
extern void* vtbl_ObjectTemplateDB_00[];     // 0x013f44b8
extern void* vtbl_ObjectTemplateDB_04b[];    // 0x013f4480
extern void* vtbl_ObjectTemplateDB_08[];     // 0x013f4470
extern void* vtbl_ObjectTemplateDB_0c[];     // 0x013f446c

// ---------------------------------------------------------------------------
// externals and free callees
// ---------------------------------------------------------------------------
extern void* g_015e3f00;                     // 0x015e3f00

void* FUN_00564f20(void* p);                                    // 0x00564f20
int   FUN_0055cb50(void* self, void* params, int flags);        // 0x0055cb50
void  FUN_00f47380(void* p);                                    // 0x00f47380  operator delete

void  __fastcall FUN_00564580(void* self, int /*edx*/);                     // 0x00564580
void  __fastcall FUN_00564470(void* self, int /*edx*/);                     // 0x00564470
void  __fastcall FUN_005646b0(void* self, int /*edx*/);                     // 0x005646b0
void  __fastcall FUN_00553fb0(void* self, int /*edx*/);                     // 0x00553fb0
void  __fastcall FUN_00548400(void* self, int /*edx*/);                     // 0x00548400
void  __fastcall FUN_00426c70(void* self, int /*edx*/);                     // 0x00426c70
void  __fastcall FUN_00567070(void* self, int /*edx*/);                     // 0x00567070
void  __fastcall FUN_00566da0(void* self, int /*edx*/, void* a, void* b);   // 0x00566da0
void  __fastcall FUN_00566ce0(void* self, int /*edx*/, void* a);            // 0x00566ce0
void  __fastcall FUN_00566ad0(void* self, int /*edx*/, void* a);            // 0x00566ad0
void  __fastcall FUN_004e8a30(void* self, int /*edx*/, void* a);            // 0x004e8a30
int   __fastcall FUN_0068f950(void* self, int /*edx*/);                     // 0x0068f950  cJob::AddRef
int   __fastcall FUN_00690120(void* self, int /*edx*/);                     // 0x00690120  cJob::Release

namespace Editor {

// element refcount-style increment (field at this+0x10)
class cCounterHolder {
public:
    uint32_t pad[3];
    uint32_t mCount;
    int Increment();
};
// @ 0x00559500
int cCounterHolder::Increment() {
    uint32_t* v33 = (uint32_t*)((char*)this + 0xc);
    int len = (int)v33[1] + 1;
    v33[1] = v33[1] + 1;
    return len;
}

namespace W1G2_58 {

// 4-byte polymorphic base subobject: its constructor just rewrites the vtable.
struct c5594e0 {
    void* mpVtbl;         // +0x00
    c5594e0();            // @ 0x005594e0
};

// @ 0x005594e0
c5594e0::c5594e0()
{
    mpVtbl = &vtbl_ITracerBase;
    mpVtbl = &vtbl_cILayer;
}

// Shared layout of Editor::W1G2_58::cObjectTemplateDB and SP::cSPObjectTemplateDB.
// The two vtables at +0x00/+0x04 belong to the two c5594e0 subobjects.
struct ObjectTemplateDBLayout {
    c5594e0       mBase00;        // +0x00
    c5594e0       mBase04;        // +0x04
    void*         mpVtbl08;       // +0x08
    void*         mpVtbl0c;       // +0x0c
    void*         mp10;           // +0x10
    VSet14        mSet14;         // +0x14
    VSet          mSet28;         // +0x28
    uint8_t       mByte40;        // +0x40
    uint8_t       mPad41[3];      // +0x41
    void*         mp44;           // +0x44
    RBTreeKey16   mTree48;        // +0x48
    VSet          mSet64;         // +0x64
    VSet          mSet7c;         // +0x7c
    VSet          mSet94;         // +0x94
    VSet          mSetAc;         // +0xac
    VSet          mSetC4;         // +0xc4
    VSet          mSetDc;         // +0xdc
    RBTreeKey16   mTreeF4;        // +0xf4
    RBTreeKey16   mTree110;       // +0x110
    VSet          mSet12c;        // +0x12c
    VSet          mSet144;        // +0x144
    VSet          mSet15c;        // +0x15c
    Big           mBig174;        // +0x174
    RandomLC      mRand1cc;       // +0x1cc
    uint8_t       mByte1d0;       // +0x1d0
    uint8_t       mPad1d1[3];     // +0x1d1
    Vector3       mVec1d4;        // +0x1d4
    uint8_t       mPad1e0[0xc];   // +0x1e0
    RBTreeKey16   mTree1ec;       // +0x1ec
    RBTreeKey16   mTree208;       // +0x208
    void*         mp224;          // +0x224
    VSet          mSet228;        // +0x228
    VSet          mSet240;        // +0x240
    VSet14        mSet258;        // +0x258
    void*         mp26c;          // +0x26c
};

// Editor::ObjectTemplateDB.
class cObjectTemplateDB : public ObjectTemplateDBLayout {
public:
    cObjectTemplateDB();          // @ 0x00559110
};

// @ 0x00559110
cObjectTemplateDB::cObjectTemplateDB()
{
    Alloc alloc;
    // The two c5594e0 subobjects are default-constructed by the base layout; retail
    // then overwrites their vtable pointers with the derived-class ones.
    mBase00.mpVtbl = &vtbl_Editor_ObjectTemplateDB;
    mBase04.mpVtbl = &vtbl_ObjectTemplateDB_04a;
    mpVtbl08 = &vtbl_PaintSystem;
    mpVtbl08 = &vtbl_cListenerBase;
    mpVtbl0c = &vtbl_hkReferencedObject;
    mp10 = 0;
    mBase00.mpVtbl = &vtbl_ObjectTemplateDB_00;
    mBase04.mpVtbl = &vtbl_ObjectTemplateDB_04b;
    mpVtbl08 = &vtbl_ObjectTemplateDB_08;
    mpVtbl0c = &vtbl_ObjectTemplateDB_0c;
    mSet14.Init(alloc);
    mSet28.Init(alloc);
    mByte40 = 0;
    mp44 = 0;
    if (mp44 != 0)
        FUN_0068f950(mp44, 0);
    mTree48.Init(alloc);
    mSet64.Init(alloc);
    mSet7c.Init(alloc);
    mSet94.Init(alloc);
    mSetAc.Init(alloc);
    mSetC4.Init(alloc);
    mSetDc.Init(alloc);
    mTreeF4.Init(alloc);
    mTree110.Init(alloc);
    mSet12c.Init(alloc);
    mSet144.Init(alloc);
    mSet15c.Init(alloc);
    mBig174.Init();
    mRand1cc.SetSeed(-1);
    mByte1d0 = 0;
    mVec1d4.SetZero();
    mTree1ec.Init(alloc);
    mTree208.Init(alloc);
    mp224 = 0;
    if (mp224 != 0)
        ((VoidThunk)((RefObj*)mp224)->mpVtbl[1])(mp224);
    mSet228.Init(alloc);
    mSet240.Init(alloc);
    mSet258.Init(alloc);
    mp26c = 0;
    if (mp26c != 0)
        ((VoidThunk)((RefObj*)mp26c)->mpVtbl[1])(mp26c);
}

// scalar deleting destructor for cPropertyList / cEditorResource
class c559050 {
public:
    void*         mpVtbl;         // +0x00
    uint32_t      mPad04[5];      // +0x04
    VectorBaseRK  mVec18;         // +0x18
    void* Dtor(uint32_t flags);   // @ 0x00559050
};

// @ 0x00559050
void* c559050::Dtor(uint32_t flags)
{
    VectorBaseRK* vec = &mVec18;
    // Retail walks the element range at 0xc stride; ResourceKey's destructor is trivial,
    // so the loop body is empty (the storage release happens in the vector destructor).
    for (uint32_t it = vec->mBegin; it < vec->mEnd; it += 0xc) {
    }
    vec->Destroy();
    mpVtbl = &vtbl_PropBaseA22;
    mpVtbl = &vtbl_ITracerBase;
    if ((flags & 1) != 0)
        FUN_00f47380(this);
    return this;
}

// small virtual-call helper
class c5590c0 {
public:
    uint32_t mUnused;             // +0x00
    char sub(void* obj, void* key, int a, int b);   // @ 0x005590c0
};

// @ 0x005590c0
char c5590c0::sub(void* obj, void* key, int a, int b)
{
    (void)a; (void)b;
    void* p = FUN_00564f20(key);
    if (p != 0)
    {
        int v = ((IntThunk)((RefObj*)obj)->mpVtbl[6])(obj);
        return (char)FUN_0055cb50((void*)v, (char*)p + 0x18, 0);
    }
    return 0;
}

} // namespace W1G2_58
} // namespace Editor

namespace SP {

// Spore's own view of the same object template database.
class cSPObjectTemplateDB : public Editor::W1G2_58::ObjectTemplateDBLayout {
public:
    ~cSPObjectTemplateDB();       // @ 0x00559590
};

// @ 0x00559590
cSPObjectTemplateDB::~cSPObjectTemplateDB()
{
    mBase00.mpVtbl = &vtbl_ObjectTemplateDB_00;
    mBase04.mpVtbl = &vtbl_ObjectTemplateDB_04b;
    mpVtbl08 = &vtbl_ObjectTemplateDB_08;
    mpVtbl0c = &vtbl_ObjectTemplateDB_0c;
    g_015e3f00 = 0;

    if (mp26c != 0)
        ((VoidThunk)((RefObj*)mp26c)->mpVtbl[2])(mp26c);

    FUN_00566da0(&mSet258, 0, mSet258.mBegin, mSet258.mEnd);
    FUN_00567070(&mSet258, 0);
    FUN_00564580(&mSet240, 0);
    FUN_00553fb0(&mSet228, 0);

    if (mp224 != 0)
        ((VoidThunk)((RefObj*)mp224)->mpVtbl[2])(mp224);

    FUN_00566ce0(&mTree208, 0, mTree208.mp0c);
    FUN_00566ce0(&mTree1ec, 0, mTree1ec.mp0c);
    FUN_00564580(&mVec1d4, 0);
    FUN_00564580(&mBig174.mTail[0], 0);
    FUN_00564470(&mBig174.mMid, 0);
    FUN_00564470(&mBig174.mHead, 0);
    FUN_00553fb0(&mSet15c, 0);
    FUN_00553fb0(&mSet144, 0);
    FUN_00553fb0(&mSet12c, 0);
    FUN_00566ad0(&mTree110, 0, mTree110.mp0c);
    FUN_00566ad0(&mTreeF4, 0, mTreeF4.mp0c);
    FUN_00564580(&mSetDc, 0);
    FUN_00564580(&mSetC4, 0);

    for (char* it = (char*)mSetAc.mBegin; it < (char*)mSetAc.mEnd; it += 8) {
    }
    FUN_00426c70(&mSetAc, 0);

    for (char* it = (char*)mSet94.mBegin; it < (char*)mSet94.mEnd; it += 4) {
    }
    FUN_00548400(&mSet94, 0);

    for (char* it = (char*)mSet7c.mBegin; it < (char*)mSet7c.mEnd; it += 4) {
    }
    FUN_00548400(&mSet7c, 0);

    for (char* it = (char*)mSet64.mBegin; it < (char*)mSet64.mEnd; it += 4) {
    }
    FUN_00548400(&mSet64, 0);

    FUN_004e8a30(&mTree48, 0, mTree48.mp0c);

    if (mp44 != 0)
        FUN_00690120(mp44, 0);

    for (char* it = (char*)mSet28.mBegin; it < (char*)mSet28.mEnd; it += 4) {
    }
    FUN_00548400(&mSet28, 0);
    FUN_005646b0(&mSet14, 0);

    mpVtbl0c = &vtbl_hkReferencedObject;
    mpVtbl08 = &vtbl_PaintSystem;
    mBase04.mpVtbl = &vtbl_ITracerBase;
    mBase00.mpVtbl = &vtbl_ITracerBase;
}

} // namespace SP
