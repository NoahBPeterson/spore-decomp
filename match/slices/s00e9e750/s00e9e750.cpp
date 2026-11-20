// s00e9e750.cpp -- SP::Audio::cAmbienceLayerManager constructor (retail 0x00e9e750).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// The class is the one reconstructed in match/slices/s00e9e290 (its destructor
// 0x00e9e3a0 and Shutdown live there).  Retail's sequence is a normal
// compiler-generated constructor: base subobject constructors first, then the
// three derived vftable stores, then the member initialisers in declaration
// order (with the two ResponseCurve constructors at +0xec/+0x450 expanded in
// place).  The base layout is
//
//   +0x00  primary base (vftable only; its constructor is novtable, the
//          most-derived constructor installs the derived vftable there)
//   +0x04  cListenerBase            (vftable)
//   +0x08  IEventModifier           (vftable + one int at +0x0c)
//
// which is exactly the store order [4], [8], [0xc], [0], [4], [8] in retail.
#include "types.h"
#include <intrin.h>

typedef unsigned int uint;
typedef unsigned char u8;

// ---------------------------------------------------------------------------
// Base subobjects.
// ---------------------------------------------------------------------------
struct __declspec(novtable) AmbPrimaryBase {
    virtual void p0();
    virtual void p1();
};

struct AmbListenerBase {
    virtual void l0();
    virtual void l1();
};

struct AmbEventModifier {
    virtual void e0();
    int  mZero;                         // +0x0c in the complete object
    AmbEventModifier() : mZero(0) {}
};

// ---------------------------------------------------------------------------
// Member types.
// ---------------------------------------------------------------------------
// eastl ResponseCurve (0x364 bytes); its default constructor is 0x00a1aa50.
struct RespCurve {
    void* mBegin;                       // +0x00  inline buffer / heap block
    void* pad04[3];
    void* mCap;                         // +0x10
    u8    pad14[0x364 - 0x14];
    RespCurve();                        // 0x00a1aa50 (declared only)
};

// eastl::map<int, Tag> (rbtree).  The map starts at +0x80; its anchor node
// (rbtree_node_base) is the first thing the tree initialises, at +0x84.
// `mAnchor()` value-initialises the 16-byte node, which is where retail's
// three null stores through eax (and the separate `xor ecx,ecx`) come from;
// reset() then installs the sentinels through the map's own this pointer.
struct RBNodeBase {
    RBNodeBase* mpNodeRight;            // +0x00
    RBNodeBase* mpNodeLeft;             // +0x04
    RBNodeBase* mpNodeParent;           // +0x08
    char        mColor;                 // +0x0c (kRBTreeColorRed == 0)
};

struct EmptyAlloc {};

class TagMap {
public:
    uint32_t   mUnk00;                  // +0x00 (part of the map, untouched)
    RBNodeBase mAnchor;                 // +0x04
    uint32_t   mnSize;                  // +0x14
    EmptyAlloc mAllocator;              // +0x18 (empty, no store)

    TagMap();
    void reset();
};

inline TagMap::TagMap() : mAnchor(), mnSize(0) {
    reset();
}

inline void TagMap::reset() {
    mAnchor.mpNodeRight  = &mAnchor;
    mAnchor.mpNodeLeft   = &mAnchor;
    mAnchor.mpNodeParent = 0;
    mAnchor.mColor       = 0;           // kRBTreeColorRed
    mnSize               = 0;
}

extern char eastl_gEmptyString16[];     // 0x01667bac

// eastl fixed_string default buffer (begin/end/capacity).
struct FixedStr {
    char* mBegin;                       // +0x00
    char* mEnd;                         // +0x04
    char* mCap;                         // +0x08

    FixedStr() {
        mBegin = eastl_gEmptyString16;
        mEnd = eastl_gEmptyString16;
        mCap = eastl_gEmptyString16 + 1;
    }
};

// The +0xd8..+0xeb curve-parameter block.  Retail evaluates the shared curve
// constant once, before the +0xdc store, and writes that one register to both
// scalars, so the block assigns a local in that order rather than using two
// separate member initialisers.
extern const float g_ambCurveConst;     // 0x01473c70

struct AmbCurveParams {
    float    mD8;                       // +0x00 (0xd8)
    uint32_t mDC;                       // +0x04 (0xdc)
    float    mE0;                       // +0x08 (0xe0)
    float    mE4;                       // +0x0c (0xe4)
    uint32_t mE8;                       // +0x10 (0xe8)

    AmbCurveParams();
};

inline AmbCurveParams::AmbCurveParams() {
    mD8 = 0.0f;
    float c = g_ambCurveConst;
    mDC = 0;
    mE0 = c;
    mE4 = c;
    mE8 = 0;
}

// ---------------------------------------------------------------------------
// SP::Audio::cAmbienceLayerManager -- layout as established by s00e9e290.
// ---------------------------------------------------------------------------
class cAmbienceLayerManager : public AmbPrimaryBase, public AmbListenerBase, public AmbEventModifier {
public:
    uint32_t  m10;                      // +0x10
    uint32_t  m14;                      // +0x14
    uint32_t  m18;                      // +0x18
    uint32_t  m1c;                      // +0x1c
    uint32_t  m20;                      // +0x20
    uint32_t  m24;                      // +0x24
    uint32_t  m28;                      // +0x28
    uint32_t  m2c;                      // +0x2c
    uint32_t  m30;                      // +0x30
    uint32_t  m34;                      // +0x34
    u8        pad38[8];                 // +0x38..+0x3f (not touched here)
    void*     mViewIdxBegin;            // +0x40
    int32_t   mViewIdxEnd;              // +0x44
    int32_t   mViewIdxCap;              // +0x48
    u8        pad4c[8];                 // +0x4c..+0x53
    void*     mViewTagsBegin;           // +0x54
    int32_t   mViewTagsEnd;             // +0x58
    int32_t   mViewTagsCap;             // +0x5c
    u8        pad60[8];                 // +0x60..+0x67
    void*     mDynTagsBegin;            // +0x68
    int32_t   mDynTagsEnd;              // +0x6c
    int32_t   mDynTagsCap;              // +0x70
    u8        pad74[0xc];               // +0x74..+0x7f
    TagMap    mIdToTagMap;              // +0x80..+0x9b
    float     mOriginX;                 // +0x9c
    float     mOriginY;                 // +0xa0
    float     mOriginZ;                 // +0xa4
    float     mRadius;                  // +0xa8
    u8        mbSphereChanged;          // +0xac
    u8        padad[3];
    void*     mpB0;                     // +0xb0
    void*     mpB4;                     // +0xb4
    void*     mpB8;                     // +0xb8
    u8        padbc[8];                 // +0xbc..+0xc3 (initialised by a sub-object)
    void*     mpC4;                     // +0xc4
    uint32_t  mC8;                      // +0xc8
    uint32_t  mCC;                      // +0xcc
    u8        padd0[8];                 // +0xd0..+0xd7
    AmbCurveParams mCurveParams;        // +0xd8..+0xeb
    RespCurve mCurveA;                  // +0xec
    RespCurve mCurveB;                  // +0x450
    float     mFreq;                    // +0x7b4
    u8        mb7b8;                    // +0x7b8
    u8        pad7b9[3];
    FixedStr  mStr;                     // +0x7bc
    uint32_t  mPad7c8;                  // +0x7c8 (not touched here)
    uint32_t  mFlags;                   // +0x7cc
    uint32_t  m7d0;                     // +0x7d0

    cAmbienceLayerManager();            // 0x00e9e750
};

typedef char sizeof_check_cAmbienceLayerManager[(sizeof(cAmbienceLayerManager) == 0x7d4) ? 1 : -1];

// ---------------------------------------------------------------------------
// Values loaded from the game's constant data (masked relocations in the check).
// ---------------------------------------------------------------------------
extern float g_ambOriginX;              // 0x016c6964
extern float g_ambOriginY;              // 0x016c6968
extern float g_ambOriginZ;              // 0x016c696c
extern const float g_ambCurveConst;     // 0x01473c70
extern float g_ambFreqConst;            // 0x01470f1c

// ===========================================================================
// 0x00e9e750 - SP::Audio::cAmbienceLayerManager::cAmbienceLayerManager
// ===========================================================================
// @ 0x00e9e750
cAmbienceLayerManager::cAmbienceLayerManager()
    : m10(0),
      m14(0),
      m18(0),
      m1c(0),
      m20(0),
      m24(0),
      m28(0),
      m2c(0),
      m30(0),
      m34(0),
      mViewIdxBegin(0),
      mViewIdxEnd(0),
      mViewIdxCap(0),
      mViewTagsBegin(0),
      mViewTagsEnd(0),
      mViewTagsCap(0),
      mDynTagsBegin(0),
      mDynTagsEnd(0),
      mDynTagsCap(0),
      mIdToTagMap(),
      mOriginX(g_ambOriginX),
      mOriginY(g_ambOriginY),
      mOriginZ(g_ambOriginZ),
      mRadius(0.0f),
      mbSphereChanged(0),
      mpB0(0),
      mpB4(0),
      mpB8(0),
      mpC4(0),
      mC8(0),
      mCC(0),
      mCurveParams(),
      mCurveA(),
      mCurveB(),
      mFreq(g_ambFreqConst),
      mb7b8(0),
      mStr(),
      mFlags(0),
      m7d0(0) {}
