// s00c1f580 -- SP::cSPCreatureBase's constructor and teardown together with
// the small EASTL-style container helpers and factory forwarders that are laid
// out next to them in the retail image.
//
// Reconstructed from the retail disassembly only
// (work/match/scratch_s00c1f580_cards.txt).  The dev-PDB headers under
// src/game/include/SP do NOT describe this build, so every offset below was
// read off the observed code instead of a header.
//
//   0x00c1f580  cCreatureDataBlock::FUN_00c1f580   thiscall, 2 args (ret 8)
//   0x00c1f650  cCurvePointVector::PushBackDefault thiscall
//   0x00c1f6d0  cUIntVector::insert                thiscall, 3 args (ret 0x10)
//   0x00c1f8d0  SP::cSPCreatureBase::cSPCreatureBase  thiscall (1415 bytes)
//   0x00c1fe80  cSPCreatureBase::FUN_00c1fe80      thiscall
//   0x00c1ffb0  cCreaturePart::FUN_00c1ffb0        thiscall, 1 arg (ret 4)
//   0x00c201a0  cCreatureFactory::FUN_00c201a0     thiscall, 3 args (ret 0xc)
//   0x00c20210  cCreatureFactory::FUN_00c20210     thiscall, 2 args (ret 8)

#include <new>

typedef unsigned int uint;

struct Vector3 {
    float x;
    float y;
    float z;
};

// ---------------------------------------------------------------------------
// A small ref-counted interface.  Its "release" entry point lives in vtable
// slot 0xc0, which is all cCurvePoint's destructor needs to reach.
// ---------------------------------------------------------------------------
class cReleaseable {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5c();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6c();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void v7c();
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8c();
    virtual void v90();
    virtual void v94();
    virtual void v98();
    virtual void v9c();
    virtual void va0();
    virtual void va4();
    virtual void va8();
    virtual void vac();
    virtual void vb0();
    virtual void vb4();
    virtual void vb8();
    virtual void vbc();
    virtual void vc0();
};

// ---------------------------------------------------------------------------
// cCurvePoint -- 0x24-byte element of the curve vector kept at creature+0xbc0.
// Its default constructor leaves +0x14 untouched (the retail constructor only
// stores 0xffffffff at +0x00 and zeroes +0x04/+0x08/+0x0c/+0x10/+0x18/+0x1c
// /+0x20).
// ---------------------------------------------------------------------------
struct cCurvePoint {
    int          mIndex;      // +0x00
    int          mField04;    // +0x04
    int          mField08;    // +0x08
    int          mField0c;    // +0x0c
    int          mField10;    // +0x10
    int          mField14;    // +0x14   (deliberately not initialized)
    union {
        unsigned char mByte18;   // +0x18  low byte: "initialised" flag
        float         mField18;  // +0x18  full slot: sampled curve limit
    };
    int          mField1c;    // +0x1c
    cReleaseable* mpRef20;    // +0x20

    cCurvePoint()
        : mIndex(-1), mField04(0), mField08(0), mField0c(0), mField10(0),
          mByte18(0), mField1c(0), mpRef20(0) {
    }
    ~cCurvePoint() {
        if (mpRef20 != 0) {
            mpRef20->vc0();
        }
    }
};

// ---------------------------------------------------------------------------
// The vector of cCurvePoint used by the creature (creature+0xbc0) and the
// caller-visible tail hooks.  Layout matches the retail one: begin/end/capacity
// followed by the pointer of the in-place (fixed) buffer.
// ---------------------------------------------------------------------------
class cCurvePointVector {
public:
    cCurvePoint* mpBegin;    // +0x00
    cCurvePoint* mpEnd;      // +0x04
    cCurvePoint* mpCapacity; // +0x08
    void*        mpFixed;    // +0x0c

    void  PushBackDefault();                                          // 0x00c1f650
    void  InsertValue(cCurvePoint* pos, const cCurvePoint* value);    // 0x00c1b990
    cCurvePoint* erase(cCurvePoint* first, cCurvePoint* last);        // 0x00ac4570
    void* FUN_00c144b0(void* a, void* b);                             // 0x00c144b0
    void  fn(void* a, void* b, void* c, int count);                   // 0x00b96360
};

// ---------------------------------------------------------------------------
// The curve object handed out by cSampleC0::FUN_00c41ec0 (0x00c41ec0).  It
// starts with the SpVector<cCurvePoint> itself and carries the sampled point
// plus a small flag word behind it.
// ---------------------------------------------------------------------------
class cCurveHolder : public cCurvePointVector {
public:
    int     mField10;    // +0x10
    Vector3 mPoint14;    // +0x14
    char    mPad20[0x38];// +0x20
    int     mField58;    // +0x58
    int     mField5c;    // +0x5c
    void  FUN_00c199e0(int value);   // 0x00c199e0
};

// ---------------------------------------------------------------------------
// Small sample object returned by cSampleC0::FUN_00c421f0 (0x00c421f0); the
// teardown reads its +0x0c float as a curve limit.
// ---------------------------------------------------------------------------
class cSampleRef {
public:
    char  mPad00[0x0c];
    float mField0c;      // +0x0c
};

// ---------------------------------------------------------------------------
// The global SpVector<Vector3> used to collect highlight anchors (in-place
// capacity, so push_back only calls out when the buffer is full).
// ---------------------------------------------------------------------------
class cVector3Vector {
public:
    Vector3* mpBegin;    // +0x00
    Vector3* mpEnd;      // +0x04
    Vector3* mpCapacity; // +0x08

    void DoInsertValue(Vector3* position, const Vector3* value);  // 0x004b5ad0

    void push_back(const Vector3& value) {
        Vector3* slot = mpEnd;
        if (slot < mpCapacity) {
            mpEnd = slot + 1;
            if (slot != 0) {
                *slot = value;
            }
        } else {
            DoInsertValue(slot, &value);
        }
    }
};

extern cVector3Vector gVec168e81c;      // 0x0168e81c

// ---------------------------------------------------------------------------
// A 4-byte-element vector with an inline (fixed) buffer.  "mpFixed" is the
// in-place buffer that operator delete must never be handed.
// ---------------------------------------------------------------------------
class cUIntVector {
public:
    uint* mpBegin;    // +0x00
    uint* mpEnd;      // +0x04
    uint* mpCapacity; // +0x08
    uint* mpFixed;    // +0x10

    void insert(void* position, const uint* first, const uint* last, uint); // 0x00c1f6d0
};

extern "C" void* __cdecl operator_new_fun_00f473a0(uint size, const char* name, int a3, int a4, const char* file, int line);
extern "C" void* __cdecl operator_new(uint size);
extern "C" void  __cdecl operator_delete_array(void* p);
extern "C" void  __cdecl FUN_00bc4030(void* a, const void* b, const void* c);
extern "C" void  __cdecl FUN_00c16090(void* a, void* b, void* c);
extern "C" void* __cdecl memcpy(void* dst, const void* src, uint count);
extern "C" void* __cdecl memmove(void* dst, const void* src, uint count);

// ---------------------------------------------------------------------------
// Fixed-size block allocator local used while bootstrapping a creature data
// block.
// ---------------------------------------------------------------------------
class eastl_fixed_pool_base {
public:
    void*   mpHead;    // +0x00
    void*   mpField04; // +0x04
    void*   mpField08; // +0x08
    void*   mpField0c; // +0x0c
    int     mCount10;  // +0x10
    void*   mpField14; // +0x14

    void init(void* pBegin, int size, int align, int count, int flag); // 0x00921260
    uint FUN_009213c0(void* value);                                    // 0x009213c0
};

extern "C" void* __cdecl FUN_00921340(int which);

// A two-float range.  The retail code builds it in a stack temporary and then
// copies both dwords out, which is what MSVC emits for a small struct
// assignment.
struct cRange {
    float mMin;   // +0x00
    float mMax;   // +0x04

    cRange() {}
    cRange(float min, float max) : mMin(min), mMax(max) {}
};

// ---------------------------------------------------------------------------
// The pooled data block hung off every creature at offset 0xcc8 / 0xd68.
// ---------------------------------------------------------------------------
class cCreatureDataBlock {
public:
    int          mPad00[2];      // +0x00
    uint         mCount08;       // +0x08
    void*        mpField0c;      // +0x0c
    cRange       mRange10;       // +0x10
    int          mField18;       // +0x18
    char         mPad1c[0x18];   // +0x1c
    int          mpField34;      // +0x34
    char         mPad38[0x14];   // +0x38
    char         mBuffer4c[0x30]; // +0x4c
    char         mPad7c[4];      // +0x7c

    cCreatureDataBlock* FUN_00c1f580(void* param2, void* param3);   // 0x00c1f580
    void FUN_00b5d220(uint n);                                  // 0x00b5d220
    void FUN_00c142a0(void* a1, void* a2, void* a3, void* a4, void* a5,
                      void* a6, void* a7);                      // 0x00c142a0
};

// ---------------------------------------------------------------------------
// Base of the creature: gives the object its first vtable and the secondary
// vtable slot that the constructor re-initializes at +0x04.
// ---------------------------------------------------------------------------
class cGameData {
public:
    cGameData();
    // The primary vtable; slot 0x00..0xbc.  Slot 0xbc is the one the retail
    // teardown calls through "this".
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34();
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual void v44();
    virtual void v48();
    virtual void v4c();
    virtual void v50();
    virtual void v54();
    virtual void v58();
    virtual void v5c();
    virtual void v60();
    virtual void v64();
    virtual void v68();
    virtual void v6c();
    virtual void v70();
    virtual void v74();
    virtual void v78();
    virtual void v7c();
    virtual void v80();
    virtual void v84();
    virtual void v88();
    virtual void v8c();
    virtual void v90();
    virtual void v94();
    virtual void v98();
    virtual void v9c();
    virtual void va0();
    virtual void va4();
    virtual void va8();
    virtual void vac();
    virtual void vb0();
    virtual void vb4();
    virtual void vb8();
    virtual void vbc();
    void* mpSecondaryVtbl;   // +0x04
};

// ---------------------------------------------------------------------------
// The singleton property bag the constructor queries for the creature's
// health/combat numbers.
// ---------------------------------------------------------------------------
class cPropertyBag {
public:
    int FUN_00c14350();     // 0x00c14350
};

extern "C" uint          __cdecl FNVHash(const char* name, uint start, int flag); // 0x00932e80
extern "C" float         __cdecl SP_GetPropertyT_float(uint hashA, int zero, uint hashB, float fallback); // 0x00bcea30
extern "C" cPropertyBag* __cdecl FUN_00b3d310();                  // 0x00b3d310
extern "C" void          __cdecl FUN_00c0b5e0(void* p);          // 0x00c0b5e0
extern "C" void          __cdecl FUN_00c0d3a0(void* p);           // 0x00c0d3a0
extern "C" void*         __cdecl FUN_00c0ff80(void* a, void* b, void* c); // 0x00c0ff80
extern "C" void          __cdecl FUN_00572020(void* p, int flag); // 0x00572020
extern "C" void          __cdecl FUN_00c29b00(void* p);           // 0x00c29b00

// Globals read or written by this slice.
extern wchar_t gEmptyString16[];        // 0x01667bac (eastl's empty 16-bit string)
extern float   gField13f1cac;           // 0x013f1cac
extern float   gHKRealOne;              // 0x01485720
extern float   gField13ec5b4;           // 0x013ec5b4
extern float   gVecBe0;                 // 0x0168d910
extern float   gVecBe4;                 // 0x0168d914
extern float   gVecBe8;                 // 0x0168d918
extern int     gField15716d4;           // 0x015716d4
extern int     gField15716d8;           // 0x015716d8
extern int     gField15716dc;           // 0x015716dc
extern int     gField15716e0;           // 0x015716e0
extern int     gField15716e4;           // 0x015716e4

class cBehaviorTreeData {
public:
    // Class-specific allocation: the retail constructor passes the size, an
    // allocation name and four zeroed debug/alignment parameters.
    static void* operator new(size_t size,
                              const char* name = "Simulator/cBehaviorTreeData",
                              int flags = 0, unsigned align = 0,
                              const char* file = 0, int line = 0);
    cBehaviorTreeData();          // 0x00bcb2a0
    virtual void bt0();
    void FUN_00bcb3d0();          // 0x00bcb3d0
};

class cFieldB48 {
public:
    void FUN_00bc9fe0();   // 0x00bc9fe0
};

// ---------------------------------------------------------------------------
// cBundle34 / cMotion58 / cSampleC0 / cInteractionTarget / cCombatant /
// cField670 / cGonzagoTimer -- the creature's embedded sub-objects, each with
// its own vtable.  Only the members touched by this slice are named; the
// remaining space is explicit padding so every named member lands on the
// offset the retail code uses.
// ---------------------------------------------------------------------------
class cBundle34 {
public:
    cBundle34();
    virtual void b00();
    void FUN_00cee7e0();    // 0x00cee7e0
    char mPad04[0x20];      // +0x04 -> 0x24
};

class cMotion58 {
public:
    cMotion58();
    virtual void m00();
    void FUN_00abf710();    // 0x00abf710
    char mPad04[0x64];      // +0x04 -> 0x68
};

class cSampleC0 {
public:
    cSampleC0();
    virtual void sc00();
    cCurveHolder* FUN_00c41ec0();     // 0x00c41ec0
    cSampleRef*   FUN_00c421f0();     // 0x00c421f0
    void FUN_00c421b0(int value);  // 0x00c421b0

    char  mPad04[0x4c];      // +0x04
    int   mFlags50;          // +0x50   (bit 0x200 = "armed")
    int   mField54;          // +0x54
    char  mPad58[0x7c];      // +0x58
    void* mpVtblD4;          // +0xd4   (secondary vtable slot)
    int   mFieldD8;          // +0xd8
    int   mFieldDc;          // +0xdc
    char  mPadE0[0x104];     // +0xe0
    float mField1e4;         // +0x1e4
    int   mField1e8;         // +0x1e8
    int   mField1ec;         // +0x1ec
    int   mField1f0;         // +0x1f0
    char  mPad1f4[0x2dc];    // +0x1f4 -> 0x4d0
};

class cInteractionTarget {
public:
    cInteractionTarget();
    virtual void it00();
    void FUN_00ac0450();    // 0x00ac0450
    char mPad04[0x14];      // +0x04 -> 0x18
};

class cCombatant {
public:
    cCombatant();
    virtual void cb00();

    char  mPad04[0x28];      // +0x04
    float mHealth2c;         // +0x2c   (creature health)
    int   mField30;          // +0x30
    int   mField34;          // +0x34
    float mCombat38;         // +0x38   (combat strength)
    char  mPad3c[0x8c];      // +0x3c -> 0xc8
};

class cGonzagoTimer {
public:
    cGonzagoTimer();
    virtual void gt00();
    void FUN_00bc3170();     // 0x00bc3170

    char  mPad04[0x1c];      // +0x04
    float mField20;          // +0x20
    int   mField24;          // +0x24
    float mField28;          // +0x28
    float mField2c;          // +0x2c   (100.0f)
};

class cField670 {
public:
    cField670();
    virtual void f670();

    char          mPad04[0x49c];   // +0x04
    unsigned char mByte4a0;        // +0x4a0
    char          mPad4a1[7];      // +0x4a1
    unsigned char mByte4a8;        // +0x4a8
    char          mPad4a9[7];      // +0x4a9
    int           mField4b0;       // +0x4b0
    int           mField4b4;       // +0x4b4
    int           mField4b8;       // +0x4b8
    int           mField4bc;       // +0x4bc
    int           mField4c0;       // +0x4c0
    int           mField4c4;       // +0x4c4
    wchar_t*      mpStr4c8;        // +0x4c8   (empty wide string)
    wchar_t*      mpStr4cc;        // +0x4cc
    wchar_t*      mpStr4d0;        // +0x4d0
    int           mField4d4;       // +0x4d4
    cFieldB48*    mpField4d8;      // +0x4d8
    cBehaviorTreeData* mpTree4dc;  // +0x4dc
    cReleaseable* mpField4e0;      // +0x4e0
    int           mField4e4;       // +0x4e4
    int           mField4e8;       // +0x4e8
    unsigned char mBytes4ec[8];    // +0x4ec
    unsigned char mByte4f4;        // +0x4f4
    unsigned char mBytes4f5[3];    // +0x4f5
    unsigned char mByte4f8;        // +0x4f8
    unsigned char mByte4f9;        // +0x4f9
    char          mPad4fa[2];      // +0x4fa
    void*         mpField4fc;      // +0x4fc
    int           mField500;       // +0x500
    int           mField504;       // +0x504
    char          mPad508[4];      // +0x508
    float         mField50c;       // +0x50c
    float         mField510;       // +0x510
    float         mField514;       // +0x514
    int           mField518;       // +0x518
    int           mField51c;       // +0x51c -> 0x520
};

// ---------------------------------------------------------------------------
// SP::cSPCreatureBase -- the game's creature object (size is a little under
// 0xfb8).  The retail constructor also re-stores nine multiple-inheritance
// vtable slots (+0x00, +0x04, +0x34, +0x58, +0xc0, +0x194, +0x590, +0x5a8,
// +0x670); those fixups belong to base classes that cannot be expressed from
// this single-inheritance declaration.
// ---------------------------------------------------------------------------
class cSPCreatureBase : public cGameData {
public:
    cSPCreatureBase();
    ~cSPCreatureBase();

    void  FUN_00c1fe80();                       // 0x00c1fe80
    void  FUN_00c19940(int value);              // 0x00c19940
    void  FUN_00c13340();                       // 0x00c13340
    float ce80(int a, int b);                   // 0x00c0ce80  (?ce80@CCB@@QAEMHH@Z)
    void  cff0(int value);                       // 0x00c0cff0  (?cff0@CCB@@QAEXH@Z)

    char               mPad08[0x2c];   // +0x08
    cBundle34          mBundle34;      // +0x34
    cMotion58          mMotion58;      // +0x58
    cSampleC0          mSampleC0;      // +0xc0
    cInteractionTarget mTarget590;     // +0x590
    cCombatant         mCombatant5a8;  // +0x5a8
    cField670          mField670;      // +0x670
    cGonzagoTimer      mTimerB90;      // +0xb90
    cCurvePointVector  mCurvesBc0;     // +0xbc0
    char               mPadBd0[0x10];  // +0xbd0
    float              mFieldBe0;      // +0xbe0
    float              mFieldBe4;      // +0xbe4
    float              mFieldBe8;      // +0xbe8
    int                mFieldBec;      // +0xbec
    int                mFieldBf0;      // +0xbf0
    int                mFieldBf4;      // +0xbf4
    int                mFieldBf8;      // +0xbf8
    int                mFieldBfc;      // +0xbfc
    int                mFieldC00;      // +0xc00
    int                mFieldC04;      // +0xc04
    int                mFieldC08;      // +0xc08
    int                mFieldC0c;      // +0xc0c
    char               mPadC10[0x18];  // +0xc10
    uint*              mpFixedBegin;   // +0xc28
    uint*              mpFixedEnd;     // +0xc2c
    uint*              mpFixedCapacity;// +0xc30
    char               mPadC34[8];     // +0xc34
    int                mFieldC3c;      // +0xc3c
    char               mFixedBuffer[0x80]; // +0xc40
    void*              mpFieldCc0;     // +0xcc0
    void*              mpFieldCc4;     // +0xcc4
    cCreatureDataBlock mBlockCc8;      // +0xcc8
    cCreatureDataBlock mBlockD68;      // +0xd68
    void*              mpFieldE08;     // +0xe08
    void*              mpFieldE0c;     // +0xe0c
    void*              mpFieldE10;     // +0xe10
    int                mFieldE14;      // +0xe14
    int                mFieldE18;      // +0xe18
    int                mFieldE1c;      // +0xe1c
    char               mPadE20[4];     // +0xe20
    int                mFieldE24;      // +0xe24
    int                mFieldE28;      // +0xe28
    int                mFieldE2c;      // +0xe2c
    char               mPadE30[8];     // +0xe30
    unsigned char      mByteE38;       // +0xe38
    char               mPadE39[3];     // +0xe39
    int                mFieldE3c;      // +0xe3c
    cCurvePointVector  mCurvesE40;     // +0xe40
    char               mPadE4c[8];     // +0xe4c
    int                mFieldE54;      // +0xe54
    float              mFieldE58;      // +0xe58
    float              mFieldE5c;      // +0xe5c
    unsigned char      mBytesE60[4];   // +0xe60
    int                mFieldE64;      // +0xe64
    unsigned char      mByteE68;       // +0xe68
    char               mPadE69[3];     // +0xe69
    int                mFieldE6c;      // +0xe6c
    int                mFieldE70;      // +0xe70
    int                mFieldE74;      // +0xe74
    unsigned char      mByteE78;       // +0xe78
    char               mPadE79[3];     // +0xe79
    cReleaseable*      mpFieldE7c;     // +0xe7c
    int                mFieldE80;      // +0xe80
    int                mFieldE84;      // +0xe84
    int                mFieldE88;      // +0xe88
    int                mFieldE8c;      // +0xe8c
    int                mFieldE90;      // +0xe90
    float              mFieldE94;      // +0xe94
    int                mFieldE98;      // +0xe98
    int                mFieldE9c;      // +0xe9c
    int                mFieldEa0;      // +0xea0
    char               mPadEa4[8];     // +0xea4
    int                mFieldEac;      // +0xeac
    char               mPadEb0[4];     // +0xeb0
    int                mFieldEb4;      // +0xeb4
    char               mPadEb8[0x20];  // +0xeb8
    int                mFieldEd8;      // +0xed8
    int                mFieldEdc;      // +0xedc
    int                mFieldEe0;      // +0xee0
    char               mPadEe4[4];     // +0xee4
    int                mFieldEe8;      // +0xee8
    char               mPadEec[0x20];  // +0xeec
    int                mFieldF0c;      // +0xf0c
    int                mFieldF10;      // +0xf10
    int                mFieldF14;      // +0xf14
    char               mPadF18[4];     // +0xf18
    int                mFieldF1c;      // +0xf1c
    char               mPadF20[0x20];  // +0xf20
    int                mFieldF40;      // +0xf40
    int                mFieldF44;      // +0xf44
    int                mFieldF48;      // +0xf48
    char               mPadF4c[4];     // +0xf4c
    int                mFieldF50;      // +0xf50
    char               mPadF54[0x20];  // +0xf54
    int                mFieldF74;      // +0xf74
    int                mFieldF78;      // +0xf78
    int                mFieldF7c;      // +0xf7c
    int                mFieldF80;      // +0xf80
    void*              mpFieldF84;     // +0xf84
    void*              mpFieldF88;     // +0xf88
    int                mFieldF8c;      // +0xf8c
    unsigned char      mByteF90;       // +0xf90
    char               mPadF91[3];     // +0xf91
    int                mFieldF94;      // +0xf94
    int                mFieldF98;      // +0xf98
    int                mFieldF9c;      // +0xf9c
    int                mFieldFa0;      // +0xfa0
    int                mFieldFa4;      // +0xfa4
    float              mFieldFa8;      // +0xfa8
    float              mFieldFac;      // +0xfac
    float              mFieldFb0;      // +0xfb0
    float              mFieldFb4;      // +0xfb4
    int                mFieldFb8;      // +0xfb8
};

// ---------------------------------------------------------------------------
// The object whose "this" the retail code reaches as creature+0x194: it is the
// part/attachment controller.  this-0xd4 is the creature's +0xc0 sub-object
// and this-0x194 is the creature itself.
// ---------------------------------------------------------------------------
class cCreaturePart {
public:
    void FUN_00c1ffb0(char enable);   // 0x00c1ffb0

    char    mPad00[0xd4];  // +0x00
    Vector3 mAnchorD4;     // +0xd4   (first point appended to the anchor vector)
    Vector3 mAnchorE0;     // +0xe0   (second point)
    char    mPadEc[0xb0];  // +0xec
    int     mField19c;     // +0x19c   (state bits, bit 2 = "disabled")
    char    mPad1a0[0x88c];// +0x1a0
    Vector3* mpCurveBeginA2c; // +0xa2c   (creature's +0xbc0)
    Vector3* mpCurveEndA30;   // +0xa30   (creature's +0xbc4)
    char    mPadA34[0x3d4];   // +0xa34
    int     mFieldE08;     // +0xe08   (creature's +0xf9c)
};

// ---------------------------------------------------------------------------
// Forwarders used by the spawn path.
// ---------------------------------------------------------------------------
class cCreatureFactory {
public:
    void* FUN_00c14e70(void* arg);                  // 0x00c14e70
    void  FUN_00c17350(void* arg, int zero);        // 0x00c17350
    void* FUN_00c1d120(void* a, void* b);           // 0x00c1d120
    void* FUN_00c201a0(char flag, void* a, void* b); // 0x00c201a0
    void  FUN_00c20210(void* a, void* b);           // 0x00c20210
};

class cFactoryObject {
public:
    virtual void o00();
    virtual void o04();
    virtual void o08(void* arg);
    virtual void o0c();
    virtual bool o10();
};

// ---------------------------------------------------------------------------
// @ 0x00c20210
// Tiny forwarder: the spawn helper called with an explicit pre-built argument,
// which simply passes the same handle down as both "factory" and "context".
// ---------------------------------------------------------------------------
void cCreatureFactory::FUN_00c20210(void* param1, void* param2)
{
    FUN_00c201a0((char)param1, param2, param2);
}

// ---------------------------------------------------------------------------
// @ 0x00c201a0
// Looks up the object already bound to "param3"; when it exists and reports
// itself as live the call is a no-op, otherwise the old binding is reset and a
// new object is created for "param2".  The flag selects between "reset only"
// and "reset and recreate".
// ---------------------------------------------------------------------------
void* cCreatureFactory::FUN_00c201a0(char flag, void* param2, void* param3)
{
    cFactoryObject* created;

    if (flag != 0) {
        cFactoryObject* found = (cFactoryObject*)FUN_00c14e70(param3);
        if (found != 0 && found->o10()) {
            return 0;
        }

        FUN_00c17350(param3, 0);

        created = (cFactoryObject*)FUN_00c1d120(param2, param3);
        if (created != 0) {
            created->o08(0);
        }
        return created;
    } else {
        FUN_00c17350(param3, 0);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00c1f650
// SpVector<cCurvePoint>::push_back() for a default (all-zero) element.  When
// the vector still has room the element is built in place, otherwise a
// temporary is built on the stack and handed to InsertValue, which reallocates.
// ---------------------------------------------------------------------------
void cCurvePointVector::PushBackDefault()
{
    cCurvePoint* p = mpEnd;

    if (p < mpCapacity) {
        mpEnd = p + 1;
        if (p != 0) {
            new (p) cCurvePoint;
        }
        return;
    }

    cCurvePoint value;
    InsertValue(p, &value);
}

// ---------------------------------------------------------------------------
// @ 0x00c1f6d0
// eastl-style vector<unsigned int>::insert(position, first, last) with the
// "fixed buffer" rule: the outgoing block is only handed to delete[] when it is
// not the vector's internal buffer.
// ---------------------------------------------------------------------------
void cUIntVector::insert(void* position, const uint* first, const uint* last, uint)
{
    if (first == last) {
        return;
    }

    uint* pEnd = mpEnd;
    const uint count = (uint)(last - first);

    if (count <= (uint)(mpCapacity - pEnd)) {
        // The run fits inside the existing block.
        const uint after = (uint)(pEnd - (uint*)position);

        if (after <= count) {
            // The run reaches past the old end: the input tail moves into the
            // free room, then the old tail slides up behind it.
            FUN_00bc4030((uint*)first + after, (uint*)last, pEnd);
            mpEnd = pEnd + (count - after);

            memmove(mpEnd, position, (uint)((char*)pEnd - (char*)position));
            mpEnd = mpEnd + after;

            FUN_00c16090((uint*)first, (uint*)first + after,
                         (uint*)position + after);
        } else {
            // The run fits entirely behind "position": shift the tail right
            // by "count" elements and drop the run into the gap.
            uint* pShift = pEnd - count;
            memcpy(pEnd, pShift, (uint)((char*)pEnd - (char*)pShift));
            mpEnd = pEnd + count;

            memmove((uint*)((char*)pEnd - ((char*)pShift - (char*)position)),
                    position, (uint)((char*)pShift - (char*)position));

            FUN_00bc4030((uint*)first, (uint*)last, position);
        }
        return;
    }

    // Grow: allocate a fresh block, splice the three pieces in, then free the
    // old block unless it is the in-place buffer.
    const uint size = (uint)(pEnd - mpBegin);
    uint newCapacity = size * 2;
    if (size == 0) {
        newCapacity = 1;
    }
    uint needed = size + count;
    if (needed < newCapacity) {
        needed = newCapacity;
    }

    uint* pNew = 0;
    if (needed != 0) {
        pNew = (uint*)operator_new_fun_00f473a0(
            needed * 4, "Simulator", 0, 0,
            "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\"
            "UTFKernel\\EASTL\\include\\EASTL/allocator.h",
            0xd1);
    }

    const uint headBytes = (uint)((char*)position - (char*)mpBegin);
    memcpy(pNew, mpBegin, headBytes);
    uint* pDst = (uint*)((char*)pNew + headBytes);

    for (const uint* src = first; src != last; ++src) {
        *pDst++ = *src;
    }

    const uint tailBytes = (uint)((char*)pEnd - (char*)position);
    memcpy(pDst, position, tailBytes);
    uint* pNewEnd = (uint*)((char*)pDst + tailBytes);

    if (mpBegin != 0 && mpBegin != mpFixed) {
        operator_delete_array(mpBegin);
    }

    mpEnd      = pNewEnd;
    mpBegin    = pNew;
    mpCapacity = (uint*)((char*)pNew + needed * 4);
}

// ---------------------------------------------------------------------------
// @ 0x00c1f580
// Bootstraps one of the creature's two pooled data blocks.  A fixed_pool is
// built over the block's own 0x30-byte embedded buffer, the block's pool
// descriptor is primed, the initial resource is requested, then the block's
// range is seeded and its used count clamped against the pool accounting.
// Returns the block (the constructor's "this").
// ---------------------------------------------------------------------------
cCreatureDataBlock* cCreatureDataBlock::FUN_00c1f580(void* param2, void* param3)
{
    eastl_fixed_pool_base pool;

    pool.mpHead = 0;
    pool.init(mBuffer4c, 0x30, 0xc, 4, 0);

    pool.mpField08 = mBuffer4c;
    pool.mpField0c = mPad7c;
    pool.mCount10  = 0xc;
    pool.mpField14 = &mpField34;

    void* resource = FUN_00921340(5);
    FUN_00c142a0(resource, param2, &param3, &param3, param3, &param3, &pool);

    mRange10 = cRange(10000.0f, 2.0f);
    mField18 = 0;

    uint used = pool.FUN_009213c0(mpField0c);
    if (mCount08 < used) {
        FUN_00b5d220(used);
    }

    return this;
}

// ---------------------------------------------------------------------------
// @ 0x00c1f8d0
// SP::cSPCreatureBase::cSPCreatureBase -- builds the creature: the base
// sub-objects, the two pooled data blocks, the two curve vectors, the
// behaviour tree and the health/combat numbers read out of the property bag.
//
// The retail image additionally re-stores nine multiple-inheritance vtable
// slots (+0x00, +0x04, +0x34, +0x58, +0xc0, +0x194, +0x590, +0x5a8, +0x670).
// Those fixups belong to base classes (the creature derives from cGameData,
// cLocomotiveObject, cInteractionAgent and a bundle container) that are not
// modelled here, so they are not reproduced.
// ---------------------------------------------------------------------------
cSPCreatureBase::cSPCreatureBase()
    : mBundle34()
    , mMotion58()
    , mSampleC0()
    , mTarget590()
    , mCombatant5a8()
    , mField670()
    , mTimerB90()
{
    // ---- behaviour-tree / path state (inside cField670) ------------------
    mField670.mByte4a0 = 0;                 // +0xb10
    mField670.mByte4a8 = 0;                 // +0xb18
    mField670.mField4b0 = 0;                // +0xb20
    mField670.mField4b4 = 0;                // +0xb24
    mField670.mField4b8 = 0;                // +0xb28
    mField670.mField4bc = 0;                // +0xb2c
    mField670.mField4c0 = 0;                // +0xb30
    mField670.mField4c4 = 1;                // +0xb34
    mField670.mpStr4c8 = gEmptyString16;         // +0xb38  (empty wide string)
    mField670.mpStr4cc = gEmptyString16;         // +0xb3c
    mField670.mpStr4d0 = gEmptyString16 + 1;     // +0xb40  (its terminator)
    mField670.mpField4d8 = 0;               // +0xb48
    mField670.mpTree4dc  = 0;               // +0xb4c
    mField670.mpField4e0 = 0;               // +0xb50
    mField670.mField4e4 = 0;                // +0xb54
    mField670.mField4e8 = 0;                // +0xb58
    mField670.mBytes4ec[0] = 0;             // +0xb5c  (four zeroed bools)
    mField670.mBytes4ec[1] = 0;
    mField670.mBytes4ec[2] = 0;
    mField670.mBytes4ec[3] = 0;
    mField670.mBytes4ec[4] = 0;
    mField670.mBytes4ec[5] = 0;
    mField670.mBytes4ec[6] = 0;
    mField670.mBytes4ec[7] = 0;             // +0xb63
    mField670.mByte4f4 = 1;                 // +0xb64
    mField670.mBytes4f5[0] = 0;             // +0xb65
    mField670.mBytes4f5[1] = 0;
    mField670.mBytes4f5[2] = 0;             // +0xb67
    mField670.mByte4f8 = 1;                 // +0xb68
    mField670.mByte4f9 = 0;                 // +0xb69
    mField670.mpField4fc = 0;               // +0xb6c
    mField670.mField500 = 0;                // +0xb70
    mField670.mField504 = 0;                // +0xb74
    mField670.mField50c = gHKRealOne;       // +0xb7c  (standard speed = 1)
    mField670.mField510 = 0.0f;             // +0xb80  (turn rate)
    mField670.mField514 = gField13f1cac;    // +0xb84
    mField670.mField518 = 5;                // +0xb88

    // ---- goal / timer block ----------------------------------------------
    mTimerB90.mField20 = 0.0f;              // +0xbb0
    mTimerB90.mField24 = 0;                 // +0xbb4
    mTimerB90.mField28 = 0.0f;              // +0xbb8
    mTimerB90.mField2c = 100.0f;            // +0xbbc  (v2 = (100,0,0))

    mFieldBe0 = gVecBe0;                    // +0xbe0  (goal.facing)
    mFieldBe4 = gVecBe4;                    // +0xbe4  (movementMode)
    mFieldBe8 = gVecBe8;                    // +0xbe8  (acceptableStopDistance)
    mFieldBec = 0;                          // +0xbec
    mFieldBf0 = 0;                          // +0xbf0
    mFieldBf4 = 0;                          // +0xbf4
    mFieldBf8 = 0;                          // +0xbf8
    mFieldBfc = 0;                          // +0xbfc
    mFieldC00 = 0;                          // +0xc00
    mFieldC04 = 0;                          // +0xc04
    mFieldC08 = 0;                          // +0xc08
    mFieldC0c = 0;                          // +0xc0c

    // ---- neighbour vector with an in-place buffer ------------------------
    mpFixedBegin    = (uint*)mFixedBuffer;                  // +0xc28
    mpFixedEnd      = (uint*)mFixedBuffer;                  // +0xc2c
    mpFixedCapacity = (uint*)(mFixedBuffer + 0x80);         // +0xc30
    mFieldC3c = 0;                                          // +0xc3c

    // ---- the two pooled data blocks --------------------------------------
    mpFieldCc0 = 0;                         // +0xcc0
    mpFieldCc4 = 0;                         // +0xcc4

    char scratch;                           // address-only, as in the image
    mBlockCc8.FUN_00c1f580(&scratch, &scratch);     // +0xcc8
    mBlockD68.FUN_00c1f580(&scratch, &scratch);     // +0xd68

    // ---- reference lists -------------------------------------------------
    mFieldE14 = 0;                          // +0xe14
    mFieldE18 = 0;                          // +0xe18
    mFieldE1c = 0;                          // +0xe1c
    mpFieldE0c = (void*)&mpFieldE0c;         // +0xe0c  (self-referential list head)
    mpFieldE10 = (void*)&mpFieldE0c;         // +0xe10
    mFieldE24 = 0;                          // +0xe24
    mFieldE28 = 0;                          // +0xe28
    mFieldE2c = 0;                          // +0xe2c
    mByteE38  = 0;                          // +0xe38
    mFieldE3c = -1;                         // +0xe3c
    mCurvesE40.mpBegin    = 0;              // +0xe40
    mCurvesE40.mpEnd      = 0;              // +0xe44
    mCurvesE40.mpCapacity = 0;              // +0xe48
    mFieldE54 = 0;                          // +0xe54
    mFieldE58 = gField13ec5b4;              // +0xe58
    mFieldE5c = gField13ec5b4;              // +0xe5c
    mBytesE60[0] = 0;                       // +0xe60
    mBytesE60[1] = 0;
    mBytesE60[2] = 0;
    mBytesE60[3] = 0;
    mFieldE64 = 0;                          // +0xe64
    mByteE68  = 0;                          // +0xe68
    mFieldE6c = 0;                          // +0xe6c
    mFieldE70 = -1;                         // +0xe70
    mFieldE74 = -1;                         // +0xe74
    mByteE78  = 0;                          // +0xe78
    mpFieldE7c = 0;                         // +0xe7c
    mFieldE80 = 0;                          // +0xe80
    mFieldE84 = 0;                          // +0xe84
    mFieldE88 = 0;                          // +0xe88
    mFieldE8c = -1;                         // +0xe8c
    mFieldE90 = -1;                         // +0xe90
    mFieldE94 = 0.0f;                       // +0xe94
    mFieldE98 = 0;                          // +0xe98
    mFieldE9c = 0;                          // +0xe9c
    mFieldEa0 = 0;                          // +0xea0
    mFieldEac = 0;                          // +0xeac
    mFieldEd8 = 0;                          // +0xed8
    mFieldEdc = 0;                          // +0xedc
    mFieldEe0 = 0;                          // +0xee0
    mFieldEe8 = 0;                          // +0xee8
    mFieldEb4 = 0;                          // +0xeb4
    mFieldF0c = 0;                          // +0xf0c
    mFieldF10 = 0;                          // +0xf10
    mFieldF14 = 0;                          // +0xf14
    mFieldF1c = 0;                          // +0xf1c
    mFieldF40 = 0;                          // +0xf40
    mFieldF44 = 0;                          // +0xf44
    mFieldF48 = 0;                          // +0xf48
    mFieldF50 = 0;                          // +0xf50
    mFieldF74 = 0;                          // +0xf74
    mFieldF78 = 0;                          // +0xf78
    mFieldF7c = 0;                          // +0xf7c
    mFieldF80 = gField15716d4;              // +0xf80
    mpFieldF84 = (void*)&mpFieldF84;         // +0xf84  (self-referential list head)
    mpFieldF88 = (void*)&mpFieldF84;         // +0xf88
    mFieldF8c = 0;                          // +0xf8c
    mByteF90  = 1;                          // +0xf90
    mFieldF94 = 0;                          // +0xf94
    mFieldF98 = 0;                          // +0xf98
    mFieldF9c = 0;                          // +0xf9c
    mFieldFa0 = 0;                          // +0xfa0
    mFieldFa4 = 0;                          // +0xfa4

    mSampleC0.mField1f0 = 0;                // +0x2b0
    mSampleC0.mField54  = 1;                // +0x114

    // ---- health / combat numbers out of the property bag -----------------
    uint hashHealth = FNVHash("StandardCreatureHealth", 0x811c9dc5, 1);
    uint hashCombat = FNVHash("Combat", 0x811c9dc5, 1);
    float property = SP_GetPropertyT_float(hashCombat, 0, hashHealth, 100.0f);
    mCombatant5a8.mHealth2c = property;     // +0x5d4
    mCombatant5a8.mCombat38 = property;     // +0x5e0

    gField15716d8 = 0;                      // +0x15716d8
    gField15716dc = -1;                     // +0x15716dc
    gField15716e0 = 0;                      // +0x15716e0
    gField15716e4 = 1;                      // +0x15716e4

    mFieldFa8 = 0.0f;                       // +0xfa8

    mFieldFac = ce80(1, 1);                 // +0xfac
    mFieldFb0 = ce80(2, 1);                 // +0xfb0
    mFieldFb4 = ce80(3, 1);                 // +0xfb4
    mSampleC0.mField1e4 = mFieldFb0;        // +0x2a4  (copy of the middle value)

    mField670.mField51c = 0;                // +0xb8c
    mTimerB90.FUN_00bc3170();

    cPropertyBag* bag = FUN_00b3d310();
    mSampleC0.FUN_00c421b0(bag->FUN_00c14350());

    mField670.mpTree4dc = new cBehaviorTreeData;    // +0xb4c

    FUN_00c0b5e0(this);

    mSampleC0.mFlags50 |= 0x200;            // +0x110
    mField670.mField4e8 &= 0xffff778f;      // +0xb58
}

// ---------------------------------------------------------------------------
// @ 0x00c1fe80
// Teardown half of the constructor: every sub-object is released, both curve
// vectors are emptied, the behaviour tree and the reference-counted members
// are dropped, then the creature is handed back to the spawner.
// ---------------------------------------------------------------------------
void cSPCreatureBase::FUN_00c1fe80()
{
    mMotion58.FUN_00abf710();
    mTarget590.FUN_00ac0450();
    mBundle34.FUN_00cee7e0();

    vbc();                                  // [this]+0xbc

    FUN_00c0d3a0(this);

    if (mField670.mpTree4dc != 0) {
        mField670.mpTree4dc->FUN_00bcb3d0();
    }
    if (mField670.mpField4d8 != 0) {
        mField670.mpField4d8->FUN_00bc9fe0();
    }

    mCurvesBc0.erase(mCurvesBc0.mpBegin, mCurvesBc0.mpEnd);

    if (mField670.mpField4e0 != 0) {
        cReleaseable* released = mField670.mpField4e0;
        mField670.mpField4e0 = 0;
        released->v04();
    }

    mField670.mField4e8 = 0;

    if (mField670.mpField4fc != 0) {
        FUN_00572020(mField670.mpField4fc, 0);
        mField670.mpField4fc = 0;
    }

    mFieldE3c = -1;
    FUN_00c13340();

    if (mpFieldE7c != 0) {
        cReleaseable* released = mpFieldE7c;
        mpFieldE7c = 0;
        released->v64();
    }

    mField670.mField504 = 0;
    FUN_00c19940(0);

    // The second curve vector is re-based: the tail is relocated and the end
    // pointer advanced by exactly the number of live elements.
    cCurvePoint* curveBegin = mCurvesE40.mpBegin;
    cCurvePoint* curveEnd   = mCurvesE40.mpEnd;
    void* relocated = FUN_00c0ff80(curveEnd, curveEnd, curveBegin);
    mCurvesE40.FUN_00c144b0(relocated, mCurvesE40.mpEnd);

    uint elements = (uint)((char*)curveEnd - (char*)curveBegin) / 0x24;
    mCurvesE40.mpEnd = (cCurvePoint*)((char*)mCurvesE40.mpEnd + elements * 0x24);

    FUN_00c29b00(this);
}

// ---------------------------------------------------------------------------
// @ 0x00c1ffb0
// Enables or disables the part/attachment controller.
//
// "this" is an interior pointer: the owning creature is this-0x194 and the
// sample sub-object used below (creature+0xc0) is this-0xd4.
//
//   enable != 0 : re-seed the part's curve from the creature's current curve
//                 point, clamp the sample count and feed it to the holder.
//                 With an empty source curve the call is skipped entirely.
//   enable == 0 : mark the part off and append its two anchor points to the
//                 global anchor vector.
// ---------------------------------------------------------------------------
void cCreaturePart::FUN_00c1ffb0(char enable)
{
    cSampleC0* samples = (cSampleC0*)((char*)this - 0xd4);
    cSPCreatureBase* owner = (cSPCreatureBase*)((char*)this - 0x194);

    if (enable != 0) {
        if (mpCurveBeginA2c == mpCurveEndA30) {
            return;
        }

        mField19c &= 0xfffffffb;

        cCurveHolder* holder = samples->FUN_00c41ec0();
        cSampleRef*   ref    = samples->FUN_00c421f0();
        float         limit  = ref->mField0c;

        holder->mPoint14 = *mpCurveBeginA2c;
        if (holder->mField5c == 0) {
            holder->mField5c = 1;
        }

        holder->erase(holder->mpBegin, holder->mpEnd);

        float count = (float)(int)((uint)((char*)mpCurveEndA30
                                         - (char*)mpCurveBeginA2c) / 0x24 - 1);
        float clamped = (count > 0.0f) ? count : 0.0f;
        holder->FUN_00c199e0((int)clamped);

        holder->fn(holder->mpEnd, (void*)((char*)mpCurveBeginA2c + 0x3c),
                   mpCurveEndA30, (int)clamped);

        if (holder->mpBegin != holder->mpEnd) {
            const float kOne = gHKRealOne;
            float value = (kOne > limit) ? kOne : limit;
            holder->mpEnd[-2].mField18 = value;
        }

        owner->cff0(mFieldE08);
        return;
    }

    // Switch the part off: record the disabled state and remember its anchors.
    mField19c = 8;
    gVec168e81c.push_back(mAnchorD4);
    gVec168e81c.push_back(mAnchorE0);
}