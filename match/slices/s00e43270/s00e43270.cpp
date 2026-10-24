// Slice s00e43270: the Simulator "UITimeline" subsystem constructor @ 0x00e43830 (2512 bytes).
//
// Module flags: /O2 /MD /Gy /TP /arch:SSE (no /EHsc: the ctor has no EH frame although its
// members have destructors).
//
// The object is allocated by the simulator subsystem setup (0x00b615c0) as
// new("Simulator/SubSystem/UITimeline") of 0x708 bytes. It is a retail-only class (neither the
// 2008 dev PDB nor ModAPI has a layout of this size with these bases), so the member names below
// are descriptive and the layout is taken from the constructor's stores:
//   +0x000 interface vptr (pre-ctor vtable 0x013eb384)
//   +0x004 interface vptr (pre-ctor vtable 0x014426a0)
//   +0x008 SP::cGonzagoSubsystem (0x1c bytes, out-of-line ctor 0x00b5b960)
//   +0x024 SP::cStringTokenTranslator (8 bytes, out-of-line ctor 0x006b5870)
//   then plain fields, seven EASTL maps (rbtree, 0x1c bytes each), a fixed_vector of six
//   ref-counted pointers, Stopwatch/LimitStopwatch timers and nineteen EASTL string16s.
#include "../../include/types.h"
#include <new>

// Status: complete and behaviourally equivalent; same size (2512 bytes), same instruction multiset,
// same call order. Not byte-exact: the /O2 scheduler places a few stores/pushes differently
// (derived vptr stores, the 0x68/0x88 int/float interleave, Stopwatch arg pushes, `or ebp,-1`).

// ------------------------------------------------------------------ EA / EASTL pieces
namespace EA {
class Stopwatch { public:
    uint64_t mnStartTime;                  // +0x00
    uint64_t mnTotalElapsedTime;           // +0x08
    int mnUnits;                           // +0x10
    float mfStopwatchCyclesToUnitsCoefficient;  // +0x14
    Stopwatch(int units, bool bStartImmediately);  // 0x0093a560
};

class LimitStopwatch : public Stopwatch { public:
    uint64_t mnEndTime;                    // +0x18
    LimitStopwatch(int units, uint32_t nLimit = 0, bool bStartImmediately = false)
        : Stopwatch(units, false) { SetTimeLimit(nLimit, bStartImmediately); }
    void SetTimeLimit(uint32_t nLimit, bool bStartImmediately);  // 0x0093a480
};
}  // namespace EA

namespace eastl {
template <typename T> struct less { less() {} };

struct rbtree_node_base {
    rbtree_node_base* mpNodeRight;
    rbtree_node_base* mpNodeLeft;
    rbtree_node_base* mpNodeParent;
    char mColor;
};

// eastl::map<K,V> layout: rb_base::mCompare, mAnchor, mnSize, mAllocator (0x1c bytes).
template <typename K>
class rbtree { public:
    less<K> mCompare;                      // +0x00
    rbtree_node_base mAnchor;              // +0x04
    uint32_t mnSize;                       // +0x14
    uint32_t mAllocator;                   // +0x18 (EASTL allocator; nothing to construct)

    rbtree() : mAnchor(), mnSize(0) { reset(); }
    void reset() {
        mAnchor.mpNodeRight = &mAnchor;
        mAnchor.mpNodeLeft = &mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor = 0;
        mnSize = 0;
    }
};

extern wchar_t gEmptyString[];             // 0x01667bac

// eastl::basic_string<char16_t>: mpBegin, mpEnd, mpCapacity, allocator (0x10 bytes).
struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAllocator;
    string16() : mpBegin(&gEmptyString[0]), mpEnd(&gEmptyString[0]), mpCapacity(&gEmptyString[1]) {}
};
}  // namespace eastl

// Ref-counted object held by the fixed_vector below (slot +0x04 = Release, slot +0x24 = the
// stop/flush hook called by Reset).
struct RefObject {
    virtual void Slot00();                 // +0x00
    virtual void Release();                // +0x04
    virtual void Slot08();
    virtual void Slot0c();
    virtual void Slot10();
    virtual void Slot14();
    virtual void Slot18();
    virtual void Slot1c();
    virtual void Slot20();
    virtual void Slot24();                 // +0x24
};

// Object held by the +0x184 vector and by +0x1c8; released through vtable slot +0x04.
struct cTimelineTrack {
    virtual void Slot00();                 // +0x00
    virtual void Release();                // +0x04
    void Flush();                          // 0x00e48f60 (thiscall, no arguments)
};

// eastl::vector<cTimelineTrack*>: begin/end/capacity at +0x184/+0x188/+0x18c.
struct TraceVector {
    cTimelineTrack** mpBegin;              // +0x00
    cTimelineTrack** mpEnd;                // +0x04
    cTimelineTrack** mpCapacity;           // +0x08
    int size() const { return (int)(mpEnd - mpBegin); }
    void erase(cTimelineTrack** first, cTimelineTrack** last);   // 0x00e25bd0 (thiscall, pops 8)
};

// eastl CopyImpl::do_copy(srcFirst, srcLast, dest) -> end of dest (0x006782c0, cdecl).
RefObject** DoCopyRefPtrs(RefObject** srcFirst, RefObject** srcLast, RefObject** dest);

// eastl::fixed_vector<intrusive_ptr<RefObject>, 6, true> (0x30 bytes).
struct fixed_vector_allocator {
    uint32_t mOverflowAllocator;           // +0x00
    void* mpPoolBegin;                     // +0x04
    fixed_vector_allocator(void* pNodeBuffer) : mpPoolBegin(pNodeBuffer) {}
};

struct RefPtrFixedVector6 {
    RefObject** mpBegin;                   // +0x00
    RefObject** mpEnd;                     // +0x04
    RefObject** mpCapacity;                // +0x08
    fixed_vector_allocator mAllocator;     // +0x0c
    uint32_t mPad14;                       // +0x14
    RefObject* mBuffer[6];                 // +0x18

    // vector::DoInsertValues(position, n, value) instance @ 0x00cbc200
    void DoInsertValues(RefObject** position, uint32_t n, RefObject* const& value);
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void resize(uint32_t n) {
        RefObject* value = 0;
        if (n > size())
            DoInsertValues(mpEnd, n - size(), value);
        else
            mpEnd = mpBegin + n;
    }
    // eastl::vector::erase(first, last): shift the tail down, release the tail slots, fix the end.
    void erase(RefObject** first, RefObject** last) {
        RefObject** pCursor = DoCopyRefPtrs(last, mpEnd, first);
        while (pCursor < mpEnd) {
            RefObject* pOld = *pCursor;
            if (pOld != 0)
                pOld->Release();
            ++pCursor;
        }
        mpEnd -= (last - first);
    }
    void clear() { erase(mpBegin, mpEnd); }

    explicit RefPtrFixedVector6(uint32_t n) : mAllocator(&mBuffer[0]) {
        mpBegin = mpEnd = &mBuffer[0];
        mpCapacity = mpBegin + 6;
        resize(n);
    }
};

struct Vector4 {
    float x, y, z, w;
    Vector4(const Vector4& v) : x(v.x), y(v.y), z(v.z), w(v.w) {}
};
extern const Vector4 kTimelineColorDefault;  // 0x015a5880 = (1, 1, 1, 0)

struct TimelineStaticInfo;                   // 0x0154df28 (static object)
extern TimelineStaticInfo gTimelineStaticInfo;

extern const float kTimelineF_0_5;           // 0x01471064 = 0.5
extern const float kTimelineF_8;             // 0x013eeda0 = 8.0
extern const float kTimelineF_0_25;          // 0x013eb8a0 = 0.25
extern const float kTimelineF_5;             // 0x01481c9c = 5.0
extern const float kTimelineF_0_3;           // 0x01481cd0 = 0.3
extern const float kTimelineF_1;             // 0x01485720 = 1.0
extern const float kTimelineF_2;             // 0x01470f1c = 2.0

// 0x18-byte helper object at +0x560 (+0x0 is not initialised by the constructor).
struct TimelineSub560 {
    uint32_t m00;                            // +0x00
    TimelineStaticInfo* mpInfo;              // +0x04
    uint32_t mCount;                         // +0x08
    uint32_t m0c;                            // +0x0c
    float mf10, mf14;                        // +0x10
    TimelineSub560() : mf10(kTimelineF_1), mf14(kTimelineF_2) {
        mCount = 1;
        mpInfo = &gTimelineStaticInfo;
        m0c = 0;
    }
};

// ------------------------------------------------------------------ bases
struct ITimelineIfc0 {                       // vptr at +0
    virtual void Ifc0Slot0();
    virtual void Ifc0Slot1() = 0;
};
struct ITimelineIfc1 {                       // vptr at +4
    virtual void Ifc1Slot0() = 0;
    virtual void Ifc1Slot1() = 0;
    virtual void Ifc1Slot2();
};

namespace SP {
class cIGonzagoSubsystem { public: virtual void GonzagoSlot0(); };
struct RefCountTemplateInt { virtual void RefSlot0(); int mnRefCount; };
class cGonzagoSubsystem : public cIGonzagoSubsystem, public RefCountTemplateInt { public:
    int mPreModeTransitionState;
    int mPostModeTransitionState;
    int mCurrentTransition;
    int mCurrentTransitionPhase;
    cGonzagoSubsystem();                     // 0x00b5b960
};
class cStringTokenTranslator { public:
    virtual void TokenSlot0();
    int mnRefCount;
    cStringTokenTranslator();                // 0x006b5870
};
}  // namespace SP

// ------------------------------------------------------------------ the class
class cUITimelineSubsystem
    : public ITimelineIfc0, public ITimelineIfc1, public SP::cGonzagoSubsystem,
      public SP::cStringTokenTranslator {
public:
    cUITimelineSubsystem();
    void Reset();                            // 0x00e43280
    virtual void Ifc0Slot0();
    virtual void Ifc0Slot1();
    virtual void Ifc1Slot0();
    virtual void Ifc1Slot1();
    virtual void Ifc1Slot2();
    virtual void GonzagoSlot0();
    virtual void RefSlot0();
    virtual void TokenSlot0();

    uint32_t m02c, m030, m034, m038, m03c, m040, m044, m048, m04c, m050, m054, m058, m05c,
        m060, m064;                          // +0x02c
    uint32_t m068, m06c, m070, m074;         // +0x068
    uint32_t m078[4];                        // +0x078 (not initialised)
    float m088, m08c, m090, m094, m098, m09c, m0a0, m0a4;  // +0x088
    uint32_t m0a8;                           // +0x0a8
    EA::Stopwatch mStopwatch0b0;             // +0x0b0
    eastl::rbtree<uint32_t> mMap0c8;         // +0x0c8
    eastl::rbtree<uint32_t> mMap0e4;         // +0x0e4
    eastl::rbtree<uint32_t> mMap100;         // +0x100
    eastl::rbtree<uint32_t> mMap11c;         // +0x11c
    eastl::rbtree<uint32_t> mMap138;         // +0x138
    eastl::rbtree<uint32_t> mMap154;         // +0x154
    uint32_t m170, m174, m178;               // +0x170
    uint32_t m17c, m180;                     // +0x17c (not initialised)
    uint32_t m184, m188, m18c;               // +0x184
    uint32_t m190, m194;                     // +0x190 (not initialised)
    RefPtrFixedVector6 mRefVec198;           // +0x198
    uint32_t m1c8, m1cc, m1d0, m1d4, m1d8, m1dc, m1e0, m1e4;  // +0x1c8
    Vector4 mColor1e8, mColor1f8, mColor208, mColor218, mColor228, mColor238;  // +0x1e8
    bool m248, m249;                         // +0x248
    float m24c;                              // +0x24c
    eastl::rbtree<uint32_t> mMap250;         // +0x250
    bool m26c, m26d;                         // +0x26c
    float m270, m274, m278;                  // +0x270
    bool m27c;                               // +0x27c
    uint32_t m280, m284, m288;               // +0x280
    float m28c, m290;                        // +0x28c
    uint32_t m294, m298, m29c, m2a0, m2a4, m2a8, m2ac, m2b0, m2b4, m2b8, m2bc, m2c0, m2c4,
        m2c8, m2cc, m2d0, m2d4, m2d8, m2dc, m2e0;  // +0x294
    uint32_t m2e4[7];                        // +0x2e4 (not initialised)
    int m300, m304;                          // +0x300
    uint32_t m308, m30c, m310, m314, m318, m31c, m320, m324, m328;  // +0x308
    int m32c;                                // +0x32c
    uint32_t m330, m334, m338, m33c, m340, m344, m348, m34c;  // +0x330
    EA::LimitStopwatch mLimitStopwatch350;   // +0x350
    bool m370, m371;                         // +0x370
    uint32_t m374, m378, m37c, m380, m384, m388, m38c, m390, m394, m398, m39c, m3a0, m3a4,
        m3a8, m3ac, m3b0, m3b4, m3b8, m3bc, m3c0, m3c4, m3c8, m3cc, m3d0, m3d4, m3d8, m3dc,
        m3e0, m3e4, m3e8, m3ec, m3f0;        // +0x374
    EA::Stopwatch mStopwatch3f8;             // +0x3f8
    float m410;                              // +0x410
    EA::Stopwatch mStopwatch418;             // +0x418
    float m430;                              // +0x430
    EA::Stopwatch mStopwatch438;             // +0x438
    float m450;                              // +0x450
    bool m454;                               // +0x454
    uint32_t m458;                           // +0x458
    int m45c;                                // +0x45c
    uint32_t m460, m464, m468;               // +0x460
    uint32_t m46c, m470;                     // +0x46c (not initialised)
    uint32_t m474, m478, m47c;               // +0x474
    uint32_t m480, m484;                     // +0x480 (not initialised)
    uint32_t m488;                           // +0x488
    bool m48c;                               // +0x48c
    uint32_t m490;                           // +0x490
    float m494, m498;                        // +0x494
    bool m49c;                               // +0x49c
    uint32_t m4a0;                           // +0x4a0
    EA::Stopwatch mStopwatch4a8;             // +0x4a8
    float m4c0;                              // +0x4c0
    EA::Stopwatch mStopwatch4c8;             // +0x4c8
    float m4e0, m4e4;                        // +0x4e0
    bool m4e8;                               // +0x4e8
    EA::Stopwatch mStopwatch4f0;             // +0x4f0
    bool m508;                               // +0x508
    EA::Stopwatch mStopwatch510;             // +0x510
    bool m528;                               // +0x528
    EA::Stopwatch mStopwatch530;             // +0x530
    EA::Stopwatch mStopwatch548;             // +0x548
    TimelineSub560 mSub560;                  // +0x560
    uint32_t m578;                           // +0x578
    uint32_t m57c;                           // +0x57c (not initialised)
    uint32_t m580, m584, m588, m58c, m590, m594, m598, m59c, m5a0, m5a4, m5a8, m5ac, m5b0,
        m5b4, m5b8, m5bc, m5c0, m5c4, m5c8, m5cc, m5d0;  // +0x580
    eastl::string16 mStr5d4, mStr5e4, mStr5f4, mStr604, mStr614, mStr624, mStr634, mStr644,
        mStr654, mStr664, mStr674, mStr684, mStr694, mStr6a4, mStr6b4, mStr6c4, mStr6d4,
        mStr6e4, mStr6f4;                    // +0x5d4
};

cUITimelineSubsystem::cUITimelineSubsystem()
    : m02c(0), m030(0), m034(0), m038(0), m03c(0), m040(0), m044(0), m048(0), m04c(0),
      m050(0), m054(0), m058(0), m05c(0), m060(0), m064(0),
      m068(0), m06c(0), m070(0), m074(0),
      m088(0.0f), m08c(0.0f), m090(0.0f), m094(0.0f), m098(0.0f), m09c(0.0f), m0a0(0.0f),
      m0a4(0.0f), m0a8(0),
      mStopwatch0b0(4, false),
      m170(0), m174(0), m178(0), m184(0), m188(0), m18c(0),
      mRefVec198(6),
      m1c8(0), m1cc(0), m1d0(0), m1d4(0), m1d8(0), m1dc(0), m1e0(0), m1e4(0),
      mColor1e8(kTimelineColorDefault), mColor1f8(kTimelineColorDefault),
      mColor208(kTimelineColorDefault), mColor218(kTimelineColorDefault),
      mColor228(kTimelineColorDefault), mColor238(kTimelineColorDefault),
      m248(false), m249(false), m24c(0.0f),
      m26c(false), m26d(false), m270(0.0f), m274(0.0f), m278(0.0f), m27c(false),
      m280(0), m284(0), m288(0), m28c(0.0f), m290(0.0f),
      m294(0), m298(0), m29c(0), m2a0(0), m2a4(0), m2a8(0), m2ac(0), m2b0(0), m2b4(0),
      m2b8(0), m2bc(0), m2c0(0), m2c4(0), m2c8(0), m2cc(0), m2d0(0), m2d4(0), m2d8(0),
      m2dc(0), m2e0(0),
      m300(-1), m304(-1),
      m308(0), m30c(0), m310(0), m314(0), m318(0), m31c(0), m320(0), m324(0), m328(0),
      m32c(-1),
      m330(0), m334(0), m338(0), m33c(0), m340(0), m344(0), m348(0), m34c(0),
      mLimitStopwatch350(4),
      m370(false), m371(false),
      m374(0), m378(0), m37c(0), m380(0), m384(0), m388(0), m38c(0), m390(0), m394(0),
      m398(0), m39c(0), m3a0(0), m3a4(0), m3a8(0), m3ac(0), m3b0(0), m3b4(0), m3b8(0),
      m3bc(0), m3c0(0), m3c4(0), m3c8(0), m3cc(0), m3d0(0), m3d4(0), m3d8(0), m3dc(0),
      m3e0(0), m3e4(0), m3e8(0), m3ec(0), m3f0(0),
      mStopwatch3f8(5, false), m410(kTimelineF_0_5),
      mStopwatch418(5, false), m430(kTimelineF_8),
      mStopwatch438(5, false), m450(kTimelineF_0_25),
      m454(false), m458(0), m45c(-1), m460(0), m464(0), m468(0),
      m474(0), m478(0), m47c(0), m488(0), m48c(false), m490(0),
      m494(0.0f), m498(0.0f), m49c(false), m4a0(0),
      mStopwatch4a8(5, false), m4c0(0.0f),
      mStopwatch4c8(5, false), m4e0(kTimelineF_5), m4e4(kTimelineF_0_3), m4e8(false),
      mStopwatch4f0(5, false), m508(false),
      mStopwatch510(5, false), m528(false),
      mStopwatch530(5, false),
      mStopwatch548(5, false),
      m578(0),
      m580(0), m584(0), m588(0), m58c(0), m590(0), m594(0), m598(0), m59c(0), m5a0(0),
      m5a4(0), m5a8(0), m5ac(0), m5b0(0), m5b4(0), m5b8(0), m5bc(0), m5c0(0), m5c4(0),
      m5c8(0), m5cc(0), m5d0(0) {
}

// ------------------------------------------------------------------ page interface
// The timeline page (SP::cSPPalettePageUI) whose Update (0x00e423a0) is forwarded to.
struct cSPPalettePageUI {
    void Update(uint32_t deltaMs);         // 0x00e423a0 (thiscall, pops 4)
};

// The +0x08-side interface of the page host: its `this` sits 8 bytes past the cSPPalettePageUI
// base, so the shim below calls the page with this - 8. (Vtable-slot adjustor shim.)
struct cTimelinePageHost {
    void Update(uint32_t arg0, uint32_t arg1);
};

// @ 0x00e43270
void cTimelinePageHost::Update(uint32_t arg0, uint32_t)
{
    cSPPalettePageUI* page = (cSPPalettePageUI*)((char*)this - 8);
    page->Update(arg0);
}

// Sink object kept at +0x5c: virtual slot +0x7c takes two ints.
struct TimelineHintSink {
    void Notify(int a, int b) {
        uint32_t* pVtable = *(uint32_t**)this;
        typedef void (__thiscall* Fn)(TimelineHintSink*, int, int);
        ((Fn)pVtable[0x7c / 4])(this, a, b);
    }
};

// Six 0xc-byte entries at +0x29c (three 32-bit fields each).
struct TimelineEntry {
    uint32_t m00, m04, m08;
};

// @ 0x00e43280
void cUITimelineSubsystem::Reset()
{
    m284 = 0;
    m28c = 0.0f;
    m290 = 0.0f;
    m294 = 0;

    if (m0a8 != 0) {
        cTimelineTrack* pOld = (cTimelineTrack*)(void*)m0a8;
        m0a8 = 0;
        pOld->Release();
    }
    if (m1c8 != 0)
        ((cTimelineTrack*)(void*)m1c8)->Flush();
    if (m1c8 != 0) {
        cTimelineTrack* pOld = (cTimelineTrack*)(void*)m1c8;
        m1c8 = 0;
        pOld->Release();
    }

    TraceVector* tracks = (TraceVector*)&m184;
    int nTracks = tracks->size();
    for (int i = 0; i < nTracks; ++i)
        tracks->mpBegin[i]->Flush();
    tracks->erase(tracks->mpBegin, tracks->mpEnd);

    TimelineEntry* entries = (TimelineEntry*)&m29c;
    for (int i = 0; i < 6; ++i) {
        entries[i].m00 = 0;
        entries[i].m04 = 0;
        entries[i].m08 = 0;
    }

    for (int i = 0; i < 6; ++i) {
        RefObject* pSlot = mRefVec198.mpBegin[i];
        if (pSlot != 0)
            pSlot->Slot24();
    }

    // fixed_vector::clear() followed by fixed_vector::resize(6), both inlined.
    mRefVec198.clear();
    if (mRefVec198.size() < 6) {
        RefObject* value = 0;
        mRefVec198.DoInsertValues(mRefVec198.mpEnd, 6 - mRefVec198.size(), value);
    } else {
        mRefVec198.erase(mRefVec198.mpBegin + 6, mRefVec198.mpEnd);
    }

    if (m05c != 0)
        ((TimelineHintSink*)(void*)m05c)->Notify(2, 0);

    if (m030 != 0) {
        m300 = -1;
        m304 = -1;
        m308 = 0;
        m30c = 0;
        m310 = 0;
        m314 = 0;
        m318 = 0;
        m31c = 0;
        m320 = 0;
        m324 = 0;
        m328 = 0;
        m32c = -1;
    }
}

// ------------------------------------------------------------------ key collection
// EA::ResourceMan::Key (0xc bytes).
struct ResourceKey {
    uint32_t mTypeID;                      // +0x00
    uint32_t mInstanceID;                  // +0x04
    uint32_t mGroupID;                     // +0x08
};

void SortKeys(ResourceKey* first, ResourceKey* last);              // 0x004f6b70 (eastl::sort)
ResourceKey* UniqueKeys(ResourceKey* first, ResourceKey* last);    // 0x004f6830 (eastl::unique)

// eastl::vector<ResourceKey, eastl::sp_vector_allocator>.
struct KeyVector {
    ResourceKey* mpBegin;                  // +0x00
    ResourceKey* mpEnd;                    // +0x04
    ResourceKey* mpCapacity;               // +0x08
    int size() const { return (int)(mpEnd - mpBegin); }
    ResourceKey* end() const { return mpEnd; }
    void reserve(int n);                   // 0x0041e4d0 (thiscall, pops 4)
    void DoInsertKey(ResourceKey* position, const ResourceKey& key);   // 0x004e3e10
    void push_back(const ResourceKey& key) {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) ResourceKey(key);
        else
            DoInsertKey(mpEnd, key);
    }
    void erase(ResourceKey* first, ResourceKey* last);
};

void KeyVector::erase(ResourceKey* first, ResourceKey* last)
{
    ResourceKey* pOldEnd = mpEnd;
    ResourceKey* pTarget = first;
    for (ResourceKey* pSource = last; pSource != pOldEnd; ++pSource)
        *pTarget++ = *pSource;
    ResourceKey* pNewEnd = pTarget;
    for (ResourceKey* pIt = pNewEnd; pIt != mpEnd; ++pIt) {
        // ResourceKey is a POD: nothing to destroy.
    }
    mpEnd -= (last - first);
}

struct cSpeciesProfile {
    uint8_t mPad00[0x504];                 // +0x000
    ResourceKey mModelKey;                 // +0x504
};

// One entry of the noun manager's game-data vector.
struct cGameNoun {
    uint8_t mPad00[0xa4];                  // +0x000
    cSpeciesProfile* mpProfile;            // +0x0a4
    bool HasProperty(uint32_t propertyID);              // 0x00bf2cb0 (thiscall, pops 4)
    ResourceKey* GetModelTypeKey(uint32_t propertyID);  // 0x00bf9770 (thiscall, pops 4)
};

// The game-data vector of a noun type: eastl::vector with the SP allocator as a base class, so the
// 4-byte allocator comes first and begin/end/capacity land at +4/+8/+0xc.
struct SpVectorAllocatorBase {
    void* mpAllocator;                     // +0x00
};
struct GameDataVector : SpVectorAllocatorBase {
    cGameNoun** mpBegin;                   // +0x04
    cGameNoun** mpEnd;                     // +0x08
    cGameNoun** mpCapacity;                // +0x0c
    int count() const { return (int)(mpEnd - mpBegin); }
};

struct cTerrainSphere {
    uint8_t mPad00[0x1168];                // +0x0000
    ResourceKey mKey1168;                  // +0x1168
};

class cGameNounManager {
public:
    SpVectorAllocatorBase* GetGameDataVector(void* p0, void* p1, void* p2, void* p3, void* p4);  // 0x00b21340
    cTerrainSphere* GetCurrentTerrainSphere();             // 0x00f67d90 (thiscall)
};
cGameNounManager* NounManager();                           // 0x00b3d300

// 0x00e48f60-free helper objects used by the collectors.
struct cKeyCollector { void FUN_00acc800(); };             // 0x00acc800 (thiscall, no arguments)
cKeyCollector* __stdcall FUN_00b3d480(KeyVector* keys);    // 0x00b3d480 (callee pops its argument)

class cSPEditorSpeciesManager {
public:
    cSpeciesProfile* GetAvatarProfile();                   // 0x004df420 (thiscall)
};
cSPEditorSpeciesManager* GetSpeciesManager();              // 0x00401090 (cdecl)

// 0x01021260 returns the active planet (null when the player has none yet).
void* GetActivePlanet();

class cSimSingleton {
public:
    uint8_t mData[0x100];                  // +0x000 (0x100-byte singleton)
    cSimSingleton();                       // 0x00cc5a70
    void FUN_00cc5bc0(KeyVector* keys);    // 0x00cc5bc0 (thiscall, pops 4)
};
extern cSimSingleton* gSimSingleton;       // 0x0169b054

void* operator new(unsigned int size, const char* name, int a, int b, int c, int d);  // 0x00f473a0

// 0x015a5a68: seven creature property ids queried by the civilization key collector.
const uint32_t gCreaturePropertyIDs[7] = {
    0x99e92f05, 0x4e3f7777, 0x47c10953, 0x72c49181, 0x2090a11b, 0xbc1041e6, 0xc15695da
};

// @ 0x00e434a0
void CollectSpeciesModelKeys(KeyVector* keys)
{
    cGameNounManager* pManager = NounManager();
    GameDataVector* nouns = static_cast<GameDataVector*>(pManager->GetGameDataVector(
        (void*)0x00cd7d10, (void*)0x00d3d420, (void*)0x00accc30, (void*)0x00b1e500, (void*)0x01be418e));
    keys->reserve(nouns->count() + keys->size());
    cSpeciesProfile* avatarProfile = GetSpeciesManager()->GetAvatarProfile();
    for (cGameNoun** pNoun = nouns->mpBegin, ** pNounEnd = nouns->mpEnd; pNoun != pNounEnd;
         ++pNoun) {
        cSpeciesProfile* profile = (*pNoun)->mpProfile;
        if (profile != 0 && profile != avatarProfile)
            keys->push_back(profile->mModelKey);
    }
    SortKeys(keys->mpBegin, keys->mpEnd);
    ResourceKey* pNewEnd = UniqueKeys(keys->mpBegin, keys->mpEnd);
    keys->erase(pNewEnd, keys->mpEnd);
}

// @ 0x00e435c0
void CollectAllSpeciesModelKeys(KeyVector* keys)
{
    cGameNounManager* pManager = NounManager();
    GameDataVector* nouns = static_cast<GameDataVector*>(pManager->GetGameDataVector(
        (void*)0x00cd7d10, (void*)0x00d3d420, (void*)0x00accc30, (void*)0x00b1e500, (void*)0x01be418e));
    keys->reserve(nouns->count() + keys->size());
    for (cGameNoun** pNoun = nouns->mpBegin, ** pNounEnd = nouns->mpEnd; pNoun != pNounEnd;
         ++pNoun) {
        cSpeciesProfile* profile = (*pNoun)->mpProfile;
        if (profile != 0)
            keys->push_back(profile->mModelKey);
    }
    if (gSimSingleton == 0)
        gSimSingleton = new ("Simulator/SimSingleton", 0, 0, 0, 0) cSimSingleton();
    gSimSingleton->FUN_00cc5bc0(keys);
    SortKeys(keys->mpBegin, keys->mpEnd);
    ResourceKey* pNewEnd = UniqueKeys(keys->mpBegin, keys->mpEnd);
    keys->erase(pNewEnd, keys->mpEnd);
}

// @ 0x00e43710
void CollectCivilizationModelKeys(KeyVector* keys)
{
    if (GetActivePlanet() == 0)
        return;
    FUN_00b3d480(keys)->FUN_00acc800();
    cGameNounManager* pManager = NounManager();
    GameDataVector* nouns = static_cast<GameDataVector*>(pManager->GetGameDataVector(
        (void*)0x00b21080, (void*)0x00d3d420, (void*)0x00b236c0, (void*)0x00b1e500, (void*)0x018c816a));
    if (nouns->mpBegin != nouns->mpEnd) {
        cGameNoun* pCiv = *nouns->mpBegin;
        for (uint32_t i = 0; i < 7; ++i) {
            if (pCiv->HasProperty(gCreaturePropertyIDs[i]))
                keys->push_back(*pCiv->GetModelTypeKey(gCreaturePropertyIDs[i]));
        }
    }
    cTerrainSphere* pSphere = NounManager()->GetCurrentTerrainSphere();
    keys->push_back(pSphere->mKey1168);
    SortKeys(keys->mpBegin, keys->mpEnd);
    ResourceKey* pNewEnd = UniqueKeys(keys->mpBegin, keys->mpEnd);
    keys->erase(pNewEnd, keys->mpEnd);
}
