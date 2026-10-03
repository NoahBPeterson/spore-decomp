// Slice s004057b0: one large per-frame update of a record-streaming system object.
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE (no /EHsc: the KeyedRecord locals have no EH frame).
// Levers found while matching:
//  - /Od lays out inline-expansion slots in body order with the inline's spilled `this`
//    last; dead slots in the original are reproduced with unused locals.
//  - rdtsc comes from inline asm (high half stored first), not __rdtsc().
//  - ThreadedObject::AddRef is _InterlockedIncrement (address computed before the 1).
//  - pack(4) on the system class: MSVC otherwise pads the vfptr to 8 (uint64 members).
#include "types.h"

// ---------------------------------------------------------------------------
// Win32 bits
// ---------------------------------------------------------------------------
union LARGE_INTEGER {
    struct { uint32_t LowPart; int32_t HighPart; } u;
    int64_t QuadPart;
};
extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(LARGE_INTEGER* lpCount);
extern "C" long _InterlockedIncrement(long volatile* addend);
#pragma intrinsic(_InterlockedIncrement)

// ---------------------------------------------------------------------------
// EA::StdC::Stopwatch (start, accumulated, units)
// ---------------------------------------------------------------------------
// rdtsc into a 64-bit local, high half first.
#define EA_READ_CPU_CYCLE(t) __asm { rdtsc } __asm { mov dword ptr [t + 4], edx } __asm { mov dword ptr [t], eax }
inline uint64_t GetStopwatchCycle() {
    LARGE_INTEGER li;
    QueryPerformanceCounter(&li);
    return li.QuadPart;
}

struct Stopwatch {
    enum { kUnitsCPUCycles = 1 };
    uint64_t mnStartTime;
    uint64_t mnTotalElapsedTime;
    int mnUnits;
    float mfCoefficient;

    void Start() {
        if (!mnStartTime) {
            if (mnUnits == kUnitsCPUCycles) {
                uint64_t nCycle;
                EA_READ_CPU_CYCLE(nCycle);
                mnStartTime = nCycle;
            } else
                mnStartTime = GetStopwatchCycle();
        }
    }
    void Restart() {
        if (mnUnits == kUnitsCPUCycles) {
            uint64_t nCycle;
            EA_READ_CPU_CYCLE(nCycle);
            mnStartTime = nCycle;
        } else
            mnStartTime = GetStopwatchCycle();
        mnTotalElapsedTime = 0;
    }
    void Reset() {
        mnStartTime = 0;
        mnTotalElapsedTime = 0;
    }
    void Stop();                                    // 0x0093a2e0
};

// ---------------------------------------------------------------------------
// Ref-counted object types and intrusive pointers
// ---------------------------------------------------------------------------
struct DefaultRefCounted {
    virtual ~DefaultRefCounted() {}
    int mnRefCount;
    int AddRef() { return mnRefCount++ + 1; }
    int Release();                                  // 0x00453540
};

// 12-byte resource key (instance, type, group).
struct InstanceID {
    uint32_t mValue;
};

struct ResourceKey {
    InstanceID mInstanceID;
    uint32_t mTypeID;
    uint32_t mGroupID;
    ResourceKey() : mInstanceID(), mTypeID(0), mGroupID(0) {}
    bool operator==(const ResourceKey& o) const {
        return mInstanceID.mValue == o.mInstanceID.mValue && mTypeID == o.mTypeID && mGroupID == o.mGroupID;
    }
    bool operator!=(const ResourceKey& o) const {
        return mInstanceID.mValue != o.mInstanceID.mValue || mTypeID != o.mTypeID || mGroupID != o.mGroupID;
    }
};

// 8-byte name/flags pair stored after the key.
struct RecordTag {
    uint32_t mNameID;
    uint16_t mFlags;
    uint16_t mExtra;
    RecordTag(uint32_t nameID, uint16_t flags, uint16_t extra)
        : mNameID(nameID), mFlags(flags), mExtra(extra) {}
};

struct StreamTarget : DefaultRefCounted {
    uint32_t m08;
    ResourceKey mKey;                               // +0x0C
    char pad18[0x6B - 0x18];
    bool mbCancelled;                               // +0x6B
    bool mbFinished;                                // +0x6C
};

struct LoadHandle {
    int AddRef();                                   // 0x0068f950
    int Release();                                  // 0x00690120
    int GetState();                                 // 0x0068f970
    void Activate();                                // 0x006909b0
    bool IsLoaded() {
        switch (GetState()) {
        case 7:
        case 8:
            return true;
        default:
            return false;
        }
    }
};

namespace Resource {
struct ThreadedObject {
    void* vtable;
    long mnRefCount;
    // The unused locals stand in for three dead /Od stack slots the original reserves here.
    int AddRef() { uint32_t unused0, unused1, unused2; return _InterlockedIncrement(&mnRefCount); }
    int Release();                                  // 0x00404f90
};
}

template <class T> struct intrusive_ptr {
    T* mpObject;
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    intrusive_ptr& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject)
                pObject->AddRef();
            mpObject = pObject;
            if (pTemp)
                pTemp->Release();
        }
        return *this;
    }
};

// Out-of-line instantiation used for KeyedRecord::mpTarget.
struct TargetPtr {
    StreamTarget* mpObject;
    StreamTarget* operator->() const { return mpObject; }
    operator StreamTarget*() const { return mpObject; }
    TargetPtr& operator=(StreamTarget* pObject);    // 0x0041cc60
};

struct IVirtualRefCounted { virtual int AddRef(); virtual int Release(); };

// 0x30-byte streaming record.
struct KeyedRecord {
    ResourceKey mKey;                               // +0x00
    RecordTag mTag;                                 // +0x0C
    intrusive_ptr<DefaultRefCounted> mpOwner;       // +0x14
    TargetPtr mpTarget;                             // +0x18
    intrusive_ptr<LoadHandle> mpHandle;             // +0x1C
    IVirtualRefCounted* mpListener;                 // +0x20
    IVirtualRefCounted* mpSlots[3];                 // +0x24

    KeyedRecord();                                  // 0x004036e0
    KeyedRecord(const KeyedRecord& x);              // 0x004063d0
    ~KeyedRecord();                                 // 0x00401f20
    KeyedRecord& operator=(const KeyedRecord& x);   // 0x00405440
};

struct RecordQueue {
    uint32_t d[(0x228 - 0xC8) / 4];
    int size();                                     // 0x00420480
    void push_back(const KeyedRecord& r, bool b);   // 0x004204f0
    bool empty();                                   // 0x00420510
    void pop_front();                               // 0x00420560
    KeyedRecord* front();                           // 0x004205b0
};

struct RecordTracker {
    uint32_t d[0x68 / 4];
    void Set(const KeyedRecord& r, bool hasTarget); // 0x004029f0
    void* IsActive();                               // 0x00402a90
    KeyedRecord* Get();                             // 0x00402ab0
    bool IsDone();                                  // 0x00402ac0
    void Clear();                                   // 0x00402b30
    void Update();                                  // 0x00402cc0
};

struct Manager { void Release(StreamTarget* p); };  // 0x00522800
Manager* GetManager();                              // 0x00401080

// pack(4): the vfptr would otherwise be padded to 8 bytes (Stopwatch holds uint64s).
#pragma pack(push, 4)
class StreamingSystem {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual bool HandleRecord(KeyedRecord& rec, bool deferred);   // slot 0x1C

    void Update();
    // Inline helpers; their unused locals stand in for dead /Od stack slots (8 and 3 dwords)
    // that the original reserves at these points.  __forceinline: /Ob1 refuses this one otherwise.
    __forceinline void RequeueCurrent() {
        uint32_t unused0, unused1, unused2, unused3, unused4, unused5, unused6, unused7;
        mQueue.push_back(mCurrent, false);
        mbAborted = true;
        Finish(false);
    }
    void FinishCancelled() {
        uint32_t unused0, unused1, unused2;
        Finish(true);
    }
    void Finish(bool b);                            // 0x00411890
    void Cancel();                                  // 0x00411e50
    bool TryResume();                               // 0x00406570

    uint32_t pad04[(0x80 - 0x04) / 4];
    intrusive_ptr<LoadHandle> m80;
    intrusive_ptr<Resource::ThreadedObject> m84;
    uint32_t pad88[(0xBC - 0x88) / 4];
    intrusive_ptr<StreamTarget> mpPendingTarget;    // +0xBC
    bool mbEnabled;                                 // +0xC0
    uint32_t padC4;
    RecordQueue mQueue;                             // +0xC8
    KeyedRecord mCurrent;                           // +0x228
    bool mbAborted;                                 // +0x258
    bool mbActive;                                  // +0x259
    RecordTracker mTracker;                         // +0x25C
    bool mbTransitioning;                           // +0x2C4
    RecordTracker mPreload;                         // +0x2C8
    uint32_t pad330[(0x1100 - 0x330) / 4];
    int mnQueued;                                   // +0x1100
    bool mbBusy;                                    // +0x1104
    ResourceKey mLastKey;                           // +0x1108
    uint32_t pad1114[(0x1138 - 0x1114) / 4];
    Stopwatch mTransitionTimer;                     // +0x1138
    Stopwatch mActiveTimer;                         // +0x1150
};
#pragma pack(pop)

// @ 0x004057b0
void StreamingSystem::Update() {
    ResourceKey readyKey;

    mnQueued = mQueue.size() + (mbActive || mbTransitioning);
    mbBusy = mbActive || mbTransitioning;
    mLastKey = mCurrent.mKey;

    if (mpPendingTarget) {
        if (mpPendingTarget->mbFinished || mpPendingTarget->mbCancelled) {
            mbAborted = true;
            if (mCurrent.mpTarget == mpPendingTarget)
                Finish(false);
            mpPendingTarget = 0;
        } else if (!mbActive) {
            if (mbTransitioning)
                RequeueCurrent();
            mCurrent = KeyedRecord();
            mCurrent.mKey = mpPendingTarget->mKey;
            mCurrent.mTag = RecordTag(0x2ea8fb98, 0, 0);
            mCurrent.mpTarget = mpPendingTarget.mpObject;
            mbActive = true;
            GetManager()->Release(mCurrent.mpTarget);
        }
    }

    if (mbActive && mCurrent.mpHandle && mCurrent.mpHandle->IsLoaded()) {
        readyKey = mCurrent.mKey;
        Finish(false);
    }
    if (mbActive && mCurrent.mpTarget && mCurrent.mpTarget->mbFinished) {
        Cancel();
        Finish(false);
    }
    if (mbActive && mCurrent.mpTarget && mCurrent.mpTarget->mbCancelled)
        FinishCancelled();

    while (!mbActive && !mbTransitioning && !mQueue.empty() && mbEnabled) {
        KeyedRecord rec(*mQueue.front());
        mQueue.pop_front();
        if (!HandleRecord(rec, (rec.mTag.mFlags & 0x100) != 0) || (rec.mTag.mFlags & 0x20)) {
            mCurrent = rec;
            bool hasTarget = mCurrent.mpTarget != 0;
            mTracker.Set(mCurrent, hasTarget);
            mbTransitioning = true;
            if (mCurrent.mpTarget && mCurrent.mKey == readyKey) {
                mTransitionTimer.Start();
                mActiveTimer.Stop();
            } else {
                mTransitionTimer.Restart();
                mActiveTimer.Reset();
            }
            break;
        }
    }

    if (mPreload.IsActive()) {
        if (mQueue.empty() || mQueue.front()->mKey != mPreload.Get()->mKey)
            mPreload.Clear();
    }
    if (!mPreload.IsActive() && !mbTransitioning && !mQueue.empty() && mbEnabled)
        mPreload.Set(*mQueue.front(), mQueue.front()->mpTarget != 0);

    mTracker.Update();
    mPreload.Update();

    if (mbTransitioning && mTracker.IsDone()) {
        mTransitionTimer.Stop();
        mActiveTimer.Start();
        mbTransitioning = false;
        mbActive = true;
        if (mCurrent.mpHandle)
            mCurrent.mpHandle->Activate();
        else if (mCurrent.mpTarget)
            GetManager()->Release(mCurrent.mpTarget);
        else if (mCurrent.mpOwner && !TryResume())
            Finish(false);
    }

    if (m80 && m80->IsLoaded()) {
        m80 = 0;
        m84 = 0;
    }
}
