// Baker (bake queue / "baker" cheat) teardown, the BakerCommand cheat's
// destructor and the ArgScript option parser's destructor.
// This module was built WITHOUT optimization and without C++ EH unwinding:
// compile with /Od /Ob1 /MD /Gy /TP.
//
// /Od notes: an inline function that the compiler starts to expand but then
// gives up on (e.g. one containing a loop, or too deep) still reserves its
// locals in the caller's frame, so frame sizes depend on the exact shape of
// the inline helpers (EASTL containers, smart pointers) of the original headers.

// ---------------------------------------------------------------------------
// EASTL pieces (string, vector) as used by the ArgScript option parser.
// ---------------------------------------------------------------------------
namespace eastl {
    struct allocator {
        inline void deallocate(void* p, unsigned int) { delete[] (char*)p; }
        unsigned int mFlags;
    };

    template <typename T>
    struct basic_string {
        T* mpBegin;
        T* mpEnd;
        T* mpCapacity;
        allocator mAllocator;

        inline ~basic_string() { DeallocateSelf(); }
        inline void DeallocateSelf() {
            if ((mpCapacity - mpBegin) > 1)
                DoFree(mpBegin, (unsigned int)(mpCapacity - mpBegin));
        }
        inline void DoFree(T* p, unsigned int n) {
            if (p)
                mAllocator.deallocate(p, n * sizeof(T));
        }
    };
    typedef basic_string<char> string;

    // Allocator whose blocks carry a header word in front of the payload.
    struct array_allocator {
        inline void deallocate(void* p, unsigned int) {
            if (((int*)p)[-1])
                delete[] (char*)p;
        }
        unsigned int mFlags;
        unsigned int mFlags2;
    };

    template <typename T>
    inline void destruct(T* first, T* last) {
        for (; first < last; ++first)
            first->~T();
    }

    template <typename T>
    struct VectorBase {
        T* mpBegin;
        T* mpEnd;
        T* mpCapacity;
        array_allocator mAllocator;

        inline ~VectorBase() {
            if (mpBegin)
                mAllocator.deallocate(mpBegin, (mpCapacity - mpBegin) * sizeof(T));
        }
    };

    template <typename T>
    struct vector : VectorBase<T> {
        inline ~vector() { destruct(this->mpBegin, this->mpEnd); }
    };
}

// ---------------------------------------------------------------------------
// ArgScript command / option parser
// ---------------------------------------------------------------------------
namespace ArgScript {
    struct OptionArg {                  // 0x20
        unsigned int mType;
        eastl::string mName;
        unsigned int mData[3];
    };

    struct Option {                     // 0x38
        eastl::string mName;
        eastl::string mDescription;
        eastl::vector<OptionArg> mArgs;
        unsigned int mFlags;
    };

    struct Flag {                       // 0x18
        eastl::string mName;
        unsigned int mData[2];
    };

    // Lookup table built from the option list (destructor 0x00837fa0, /O2 module).
    struct OptionIndex {
        ~OptionIndex();
        unsigned int mData[17];
    };

    class OptionParser {
    public:
        OptionParser(int mode);                                  // 0x0083a9f0
        void AddOptions(const char* description, ...);           // 0x0083bcd0
        void PrintUsage(const char* name, void* stream);         // 0x0083a2f0

        eastl::string mName;             // +0x00
        eastl::string mDescription;      // +0x10
        eastl::string mUsage;            // +0x20
        eastl::vector<OptionArg> mArgs;  // +0x30
        eastl::vector<Option> mOptions;  // +0x44
        eastl::vector<Flag> mFlags;      // +0x58
        unsigned int mFlagMask[2];       // +0x6c
        OptionIndex mIndex;              // +0x74
        eastl::string mLastError;        // +0xb8
    };

    class ICommand {
    public:
        ICommand();
        virtual ~ICommand();                     // 0x0083c750
        virtual void ParseLine(void* line);
        unsigned int mField4;
        unsigned int mField8;
        unsigned int mFieldC;
    };
}

class BakerCommand : public ArgScript::ICommand {
public:
    BakerCommand(void* pBaker);
    virtual ~BakerCommand() {}
    virtual void ParseLine(void* line);
    void Description(void* stream);

    void* mpBaker;                      // +0x10
    ArgScript::OptionParser mOptions;   // +0x14
    const char* mKeyFilter;             // +0xdc
    int mLimit;                         // +0xe0
    bool mProcessQueue;                 // +0xe4
    int mFilterGroup;                   // +0xe8
    int mFilterInstance;                // +0xec
};

// The constructor (0x00404500, matched in slice s00404480) is repeated here so
// that this translation unit emits BakerCommand's vtable, and with it the
// inline destructor's two out-of-line pieces:
// @ 0x00405000  BakerCommand::`scalar deleting destructor' (??_GBakerCommand@@UAEPAXI@Z)
// @ 0x00405050  ArgScript::OptionParser::~OptionParser, implicit (??1OptionParser@ArgScript@@QAE@XZ)
BakerCommand::BakerCommand(void* pBaker)
    : mpBaker(pBaker), mOptions(1)
{
    mOptions.AddOptions("Baker system management.",
        "-bake^ [<keyFilter:cstring>]", 0, &mKeyFilter,
            "bake given buildings/vehicles/creatures/etc., switch to model viewer unless noSwitch is specified",
        "-toData^", 6,
            "after baking, promote baked resources to Data, ready for checking in as shipped content",
        "-show^", 0xb, "show result of baking in the model viewer",
        "-force^", 8, "force the baker to perform a full bake, ignoring existing resources on disk",
        "-hires^", 0xe, "bake with high lod model present",
        "-flush^", 1, "flush resman after each bake",
        "-rtts^", 2, "show rtt list after each bake",
        "-limit <n:int>", &mLimit, "bake at most n models",
        "-describeBlocks^", 3,
            "dump text descriptions for all rigblocks to basePath or UserData/Debug/BlockDescriptions.",
        "-filter^ <group:int> <instance:int>", 4, &mFilterGroup, &mFilterInstance,
            "filter by manifest list for describeBlocks cheat",
        "-processQueue^ <bool>", 5, &mProcessQueue, "enable or disable processing of queued items",
        "-dumpProfs^", 7, "dump timing information for bakes completed",
        "-fastDevMode^", 0xc, "enable 'fast' mode until game restart (extremely low quality)",
        0);
}

// ---------------------------------------------------------------------------
// Smart pointers
// ---------------------------------------------------------------------------
template <typename T>
class intrusive_ptr {
public:
    T* mpObject;

    intrusive_ptr() : mpObject(0) {}
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }

    intrusive_ptr& operator=(const intrusive_ptr& ip) { return operator=(ip.mpObject); }
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

// Reference counted base. Release (0x00453540) and intrusive_ptr's
// operator=(const intrusive_ptr&) for it (0x004e4350) are inline but too big
// for the /Ob1 inliner, so they stay out of line.
class DefaultRefCounted {
public:
    virtual ~DefaultRefCounted();

    int AddRef() {
        int count = mnRefCount + 1;
        mnRefCount = mnRefCount + 1;
        return count;
    }
    int Release() {
        int count = mnRefCount - 1;
        mnRefCount = mnRefCount - 1;
        if (count)
            return count;
        mnRefCount = 1;
        delete this;
        return 0;
    }
    void Unload();                      // 0x0055bee0

    int mnRefCount;
};

class BakeJob {
public:
    int AddRef();                       // 0x0068f950
    int Release();                      // 0x00690120
    void Cancel(int reason);            // 0x00692400
};

class IVirtualRefCounted {
public:
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};

// ---------------------------------------------------------------------------
// One bake request (0x30 bytes).
// ---------------------------------------------------------------------------
struct ResourceID {
    ResourceID() : mInstance(0), mGroup(0), mType(0) {}
    unsigned int mInstance;
    unsigned int mGroup;
    unsigned int mType;
};

struct BakeFormat {
    BakeFormat() : mTypeID(0x2ea8fb98), mLod(0), mFlags(4) {}
    unsigned int mTypeID;
    unsigned short mLod;
    unsigned short mFlags;
};

// Constructor (0x004036e0), destructor (0x00401f20) and assignment
// (0x00405440) are all compiler-generated.
struct BakeEntry {
    ResourceID mKey;                               // +0x00
    BakeFormat mFormat;                            // +0x0c
    intrusive_ptr<DefaultRefCounted> mpModel;                         // +0x14
    intrusive_ptr<DefaultRefCounted> mpRig;                         // +0x18
    intrusive_ptr<BakeJob> mpJob;                  // +0x1c
    intrusive_ptr<IVirtualRefCounted> mpTarget;    // +0x20
    intrusive_ptr<IVirtualRefCounted> mpOutputs[3]; // +0x24
};

// @ 0x00405440  BakeEntry::operator= (implicit)
void AssignBakeEntry(BakeEntry& dst, const BakeEntry& src) { dst = src; }

// ---------------------------------------------------------------------------
// Baker
// ---------------------------------------------------------------------------
class ICheatManager {
public:
    static ICheatManager* Get();                   // 0x0067de20
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void RemoveCheat(const char* name);    // +0x1c
};

class IMessageManager {
public:
    static IMessageManager* Get();                 // 0x0067dd80
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void RemoveListener(unsigned int messageID);  // +0x18
};

struct KeyList {
    void* mpVTable;
    unsigned int mpBegin;
    unsigned int mpEnd;
    unsigned int mnCount;
    void Erase(unsigned int first, unsigned int last);   // 0x004e3590
    inline void clear() {
        Erase(mpBegin, mpEnd);
        mnCount = 0;
    }
};

struct LinearAllocator {
    void* mpVTable;
    unsigned int mpBegin;
    unsigned int mpEnd;
    unsigned int mpCurrent;
    unsigned int mpLast;
    void FreeTo(unsigned int p);                   // 0x00928c40
    inline void Reset(unsigned int p) {
        if (p > mpBegin && p < mpEnd) {
            mpCurrent = 0;
            mpLast = mpCurrent;
        } else
            FreeTo(p);
    }
};

class IBakeTarget {
public:
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool Process(unsigned int context, unsigned int item, unsigned int flags);  // +0x2c

    inline bool ProcessAll(unsigned int context, const unsigned int* items, unsigned int count,
                           unsigned int flags) {
        bool ok = true;
        for (unsigned int i = 0; i < count; i++) {
            if (!Process(context, items[i], flags))
                ok = false;
        }
        return ok;
    }
};

// Pending batch (Flush = 0x004039f0).
struct BakeBatch {
    IBakeTarget* mpTarget;
    unsigned int mContext;
    unsigned int* mpItems;
    unsigned int mnCount;
    unsigned int mFlags;

    inline bool Flush() {
        bool result = false;
        if (mpTarget) {
            IBakeTarget* target = mpTarget;
            mpTarget = 0;
            result = target->ProcessAll(mContext, mpItems, mnCount, mFlags);
        }
        return result;
    }
};

struct BakeQueue {
    void Clear();                                  // 0x00402b30
    unsigned int mData[26];
};

// Map of queued bake requests: an outer cursor wrapping a node iterator.
struct BakeMap {
    struct node_iterator {                         // 0x14
        void* mpNode;
        unsigned int mData[4];

        BakeEntry* operator->() const;             // 0x005658b0
        bool operator==(const node_iterator& x) const { return mpNode == x.mpNode; }
    };

    struct iterator {                              // 0x1c
        void* mpList;
        node_iterator mIt;
        void* mpListEnd;

        iterator& operator++();                    // 0x00421f00
        BakeEntry* operator->() const { return mIt.operator->(); }
        BakeEntry& operator*() const { return *mIt.operator->(); }
        bool operator==(const iterator& x) const {
            return mpList == x.mpList && (mpList == mpListEnd || mIt == x.mIt);
        }
        bool operator!=(const iterator& x) const { return !(*this == x); }
    };

    iterator begin();                              // 0x00420200
    iterator end();                                // 0x00420350
    void clear();                                  // 0x00420440
    unsigned int mData[0x58];
};

class Baker {
public:
    void CancelAll();
    void Shutdown();

    unsigned int mPad00[12];
    KeyList mBakedKeys;                            // +0x30
    unsigned int mPad40[4];
    LinearAllocator mArena;                        // +0x50
    unsigned int mPad64[4];
    intrusive_ptr<IVirtualRefCounted> mpWindow;    // +0x74
    intrusive_ptr<IVirtualRefCounted> mpLayout;    // +0x78
    unsigned int mPad7c[3];
    intrusive_ptr<DefaultRefCounted> mpModelRes;   // +0x88
    intrusive_ptr<DefaultRefCounted> mpRigRes;     // +0x8c
    unsigned int mPad90[14];
    BakeMap mQueued;                               // +0xc8
    BakeEntry mCurrent;                            // +0x228
    unsigned char mPad258;
    bool mbBaking;                                 // +0x259
    unsigned char mPad25a[2];
    BakeQueue mPending;                            // +0x25c
    bool mbProcessQueue;                           // +0x2c4
    unsigned char mPad2c5[3];
    BakeQueue mDeferred;                           // +0x2c8
    unsigned int mPad334[(0x1168 - 0x334) / 4];
    BakeBatch mBatch;                              // +0x1168
};

// @ 0x004051e0
void Baker::CancelAll()
{
    mPending.Clear();
    mDeferred.Clear();
    mbProcessQueue = false;

    if (mCurrent.mpJob.get())
        mCurrent.mpJob->Cancel(0);
    if (mCurrent.mpModel.get())
        mCurrent.mpModel->Unload();
    mCurrent = BakeEntry();
    mbBaking = false;

    for (BakeMap::iterator it = mQueued.begin(); it != mQueued.end(); ++it) {
        if (it->mpJob.get())
            it->mpJob->Cancel(0);
        if (it->mpModel.get())
            it->mpModel->Unload();
        *it = BakeEntry();
    }
    mQueued.clear();
}

// @ 0x004055b0
void Baker::Shutdown()
{
    ICheatManager::Get()->RemoveCheat("baker");
    mpWindow = 0;
    mpLayout = 0;
    IMessageManager::Get()->RemoveListener(0x227d899);
    IMessageManager::Get()->RemoveListener(0x227d89a);
    mpModelRes = 0;
    mpRigRes = 0;
    mBatch.Flush();
    mArena.Reset(0);
    mBakedKeys.clear();
}
