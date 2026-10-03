// Slice s004035d0: a small module compiled WITHOUT optimization and WITHOUT C++ EH:
//   /Od /Ob1 /MD /Gy /TP /arch:SSE    (no /EHsc: array member destruction is an inline
//   countdown loop instead of `eh vector destructor iterator`, and destructors have no
//   EH frame; /arch:SSE: float stores are movss).
//
// Contents: two plain constructors, a large multiply-inherited system object's
// destructor and AddRef, a deferred-callback batch flush, and the out-of-line
// destructor of an 8-element member array.
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

// ---------------------------------------------------------------------------
// 0x38-byte settings block: id, flag, pointer vector, three {index, min, max} ranges.
// ---------------------------------------------------------------------------
struct PtrVector {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;
    PtrVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
};

struct RangeSettings {
    int mID;
    bool mbEnabled;
    PtrVector mItems;
    int mIndex0; float mMin0; float mMax0;
    int mIndex1; float mMin1; float mMax1;
    int mIndex2; float mMin2; float mMax2;
    RangeSettings();
};

// @ 0x004035d0
RangeSettings::RangeSettings()
    : mID(0), mbEnabled(false), mItems(),
      mIndex0(0), mMin0(0.0f), mMax0(0.0f),
      mIndex1(0), mMin1(0.0f), mMax1(0.0f),
      mIndex2(0), mMin2(0.0f), mMax2(0.0f) {}

// ---------------------------------------------------------------------------
// Resource key (instance id, type/group halves) and a record built around it.
// ---------------------------------------------------------------------------
struct ResourceKey {
    uint32_t mInstanceID;
    uint16_t mTypeLo;
    uint16_t mTypeHi;
    ResourceKey(uint32_t instanceID = 0x2ea8fb98, uint16_t typeLo = 0, uint16_t typeHi = 4)
        : mInstanceID(instanceID), mTypeLo(typeLo), mTypeHi(typeHi) {}
};

struct RawPtr {
    void* mpObject;
    RawPtr() : mpObject(0) {}
};

struct KeyedRecord {
    void* mpOwner;
    void* mpData;
    void* mpExtra;
    ResourceKey mKey;
    RawPtr mRef14, mRef18, mRef1C, mRef20;
    RawPtr mSlots[3];
    KeyedRecord();
};

// @ 0x004036e0
KeyedRecord::KeyedRecord() : mpOwner(0), mpData(0), mpExtra(0) {}

// ---------------------------------------------------------------------------
// Deferred batch: hands every queued item to a target's virtual Apply() once.
// ---------------------------------------------------------------------------
struct BatchTarget {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool Apply(uint32_t context, uint32_t item, uint32_t userData);  // slot 0x2C
};

inline bool ApplyAll(BatchTarget* target, uint32_t context, uint32_t* items, uint32_t count,
                     uint32_t userData) {
    bool ok = true;
    for (uint32_t i = 0; i < count; i++)
        if (!target->Apply(context, items[i], userData))
            ok = false;
    return ok;
}

struct PendingBatch {
    BatchTarget* mpTarget;
    uint32_t mContext;
    uint32_t* mpItems;
    uint32_t mnCount;
    uint32_t mUserData;

    bool Flush();
    ~PendingBatch() { if (mpTarget) Flush(); }
};

// @ 0x004039f0
bool PendingBatch::Flush() {
    bool result = false;
    if (mpTarget) {
        BatchTarget* target = mpTarget;
        mpTarget = 0;
        result = ApplyAll(target, mContext, mpItems, mnCount, mUserData);
    }
    return result;
}

// ---------------------------------------------------------------------------
// Smart pointers and members of the big system object.
// ---------------------------------------------------------------------------
struct IVirtualRefCounted { virtual int AddRef(); virtual int Release(); };

template <class T> struct intrusive_ptr {
    T* mpObject;
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
};

namespace Resource { struct ThreadedObject { int Release(); }; }
struct RefObject690 { int Release(); };   // released via 0x00690120

struct DefaultRefCounted {
    virtual ~DefaultRefCounted() {}
    int mnRefCount;
    int AddRef() { return mnRefCount++ + 1; }
    int Release();
};

// Members whose destructors are out of line elsewhere.  Some wrappers declare unused
// locals: stand-ins for dead /Od stack slots the original destructor reserves.
struct Member10Base { uint32_t d[8]; ~Member10Base(); };                        // 0x0041fac0
struct Member10 : Member10Base { ~Member10() { uint32_t unused0, unused1; } };
struct Member30Base { uint32_t d[8]; ~Member30Base(); };                        // 0x004e0f20
struct Member30 : Member30Base { ~Member30() { uint32_t unused0, unused1; } };
struct Member50Base { uint32_t d[9]; ~Member50Base(); };                        // 0x00928dc0
struct Member50 : Member50Base { ~Member50() { uint32_t unused0, unused1; } };
struct Member90Base { uint32_t d[5]; ~Member90Base(); };                        // 0x00540520
struct Member90 : Member90Base { ~Member90() { uint32_t unused; } };
struct MemberA4Base { uint32_t d[6]; ~MemberA4Base(); };                        // 0x004e1bf0
struct MemberA4 : MemberA4Base { ~MemberA4() { uint32_t unused; } };

struct Slot2C { uint32_t d[11]; ~Slot2C(); };                                   // 0x004200b0
struct SlotArray8 {
    Slot2C mSlots[8];
    ~SlotArray8();
};

struct Member228Base { uint32_t d[13]; ~Member228Base(); };                     // 0x00401f20
struct Member228 : Member228Base { ~Member228() { uint32_t unused0, unused1; } };
struct Member68 { uint32_t d[26]; ~Member68(); };                               // 0x004020e0
struct Member330 { uint32_t d[(0x1168 - 0x330) / 4]; ~Member330(); };          // 0x00417fe0
struct Entry20 { uint32_t d[8]; ~Entry20(); };                                  // 0x005534b0

struct SystemInterface : IVirtualRefCounted {};
struct SystemListener { virtual ~SystemListener() {} };

struct GameSystem : SystemInterface, SystemListener, DefaultRefCounted {
    Member10 m10;
    Member30 m30;
    Member50 m50;
    intrusive_ptr<IVirtualRefCounted> m74, m78, m7C;
    intrusive_ptr<RefObject690> m80;
    intrusive_ptr<Resource::ThreadedObject> m84;
    intrusive_ptr<DefaultRefCounted> m88, m8C;
    Member90 m90;
    MemberA4 mA4;
    intrusive_ptr<DefaultRefCounted> mBC;
    uint32_t mC0, mC4;
    SlotArray8 mC8;
    Member228 m228;
    Member68 m25C;
    uint32_t m2C4;
    Member68 m2C8;
    Member330 m330;
    PendingBatch mPending;
    intrusive_ptr<IVirtualRefCounted> m117C;
    uint32_t m1180;
    Entry20 mEntries[6];

    virtual int AddRef();
    ~GameSystem();
};

// @ 0x004036a0
int GameSystem::AddRef() { return DefaultRefCounted::AddRef(); }

// @ 0x004037b0
GameSystem::~GameSystem() { uint32_t unused0, unused1, unused2; }

// @ 0x00403aa0
SlotArray8::~SlotArray8() {}
