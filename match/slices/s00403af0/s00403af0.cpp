// Slice s00403af0: the baker/skinner system's Initialize() plus three small helpers.
// The whole module is built WITHOUT optimization and without C++ EH:
//   /Od /Ob1 /MD /Gy /TP   (no /EHsc: Initialize has destructible locals but no EH frame)
//
// /Od notes learned here (on top of s004ce770's):
//  - Stack frame = [named locals, ordered by a NAME hash per function] then three temp
//    regions: statement temporaries (class temps, new-results, return value), inline-expansion
//    slots (params bound to non-trivial args, inline locals, inline scalar returns), and
//    call-result temps (virtual-call `this` values, operator-> results).
//  - Inline functions returning a call result (AsOutParam, HashString) force all args of the
//    enclosing call to be pre-evaluated into temps (right-to-left), then pushed.
//  - `x++ + 1` (not `++x`) reproduces the temp-then-store AddRef pattern.
void* operator new[](unsigned int size, const char* pName, int flags, unsigned int debugFlags,
                     const char* pFile, int line);
void* operator new(unsigned int size, const char* pName, int flags, unsigned int debugFlags,
                   const char* pFile, int line);
void EASTL_allocator_deallocate(void* p);
unsigned int FNVHash(const char* s, unsigned int seed, int lowercase);
inline unsigned int HashString(const char* s) { return FNVHash(s, 0x811c9dc5, 1); }

// ---------------------------------------------------------------------------
template <class T> struct intrusive_ptr {
    T* mpObject;
    intrusive_ptr() : mpObject(0) {}
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
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
    T* operator->() const { return mpObject; }
    T* get() const { return mpObject; }
    intrusive_ptr& ReleaseRef();   // out of line: releases and nulls, returns *this
    T** AsOutParam() { return &ReleaseRef().mpObject; }
};

void AddListeners(struct IMessageManager* pManager, struct IMessageListener* pListener,
                  const unsigned int* pIDs, unsigned int count);

struct ResourceKey {
    unsigned int instanceID;
    unsigned int typeID;
    unsigned int groupID;
};

// ---------------------------------------------------------------------------
struct IObject {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
};

struct IWindowGroup : IObject {
    virtual void v08(); virtual void v0c(); virtual void v10();
    virtual IWindowGroup* FindWindowByID(unsigned int id, int a, int b);
    virtual void v018(); virtual void v01c(); virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c(); virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c(); virtual void v040(); virtual void v044(); virtual void v048(); virtual void v04c(); virtual void v050(); virtual void v054(); virtual void v058(); virtual void v05c(); virtual void v060(); virtual void v064(); virtual void v068(); virtual void v06c(); virtual void v070(); virtual void v074(); virtual void v078(); virtual void v07c(); virtual void v080(); virtual void v084(); virtual void v088(); virtual void v08c(); virtual void v090(); virtual void v094(); virtual void v098(); virtual void v09c(); virtual void v0a0(); virtual void v0a4(); virtual void v0a8(); virtual void v0ac(); virtual void v0b0(); virtual void v0b4(); virtual void v0b8(); virtual void v0bc(); virtual void v0c0(); virtual void v0c4(); virtual void v0c8(); virtual void v0cc(); virtual void v0d0(); virtual void v0d4(); virtual void v0d8(); virtual void v0dc(); virtual void v0e0(); virtual void v0e4(); virtual void v0e8(); virtual void v0ec(); virtual void v0f0(); virtual void v0f4(); virtual void v0f8(); virtual void v0fc(); virtual void v100(); virtual void v104(); virtual void v108(); virtual void v10c(); virtual void v110(); virtual void v114(); virtual void v118(); virtual void v11c(); virtual void v120();
    // 0x124
    virtual void SetFlag(int flag, int a, int b);
    virtual void v128(); virtual void v12c(); virtual void v130();
    virtual void SetVisible(bool visible);
};

struct IWindowManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual IWindowGroup* FindWindowByID(unsigned int id, int a, int b);
};
IWindowManager* WindowManager();  // 0x0067DD80

struct DefaultRefCounted {
    void* vtable;
    int mnRefCount;
    int AddRef() { return mnRefCount++ + 1; }
    int Release();
};

struct cBlockData : DefaultRefCounted {
    unsigned int pad[10];
    cBlockData();
};
struct cBakeQueue : DefaultRefCounted {
    unsigned int pad[36];
    cBakeQueue(float scale);
};

struct IMessageListener { virtual void v00(); };
struct IMessageManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20();
    virtual void AddListener(IMessageListener* listener, unsigned int messageID);
};

// @ 0x004043F0
// Registers the listener for each message ID in a table.
void AddListeners(IMessageManager* pManager, IMessageListener* pListener, const unsigned int* pIDs,
                  unsigned int count)
{
    for (unsigned int i = 0; i < count; i++)
        pManager->AddListener(pListener, pIDs[i]);
}
IMessageManager* MessageManager();  // 0x0067DCC0

struct MessageRegistration {
    IMessageManager* mpManager;
    IMessageListener* mpListener;
    const unsigned int* mpIDs;
    unsigned int mnCount;
    int mbRegistered;
    void Init(IMessageManager* pManager, IMessageListener* pListener, const unsigned int* pIDs, unsigned int count) {
        mpManager = pManager;
        mpListener = pListener;
        mpIDs = pIDs;
        mnCount = count;
        mbRegistered = 0;
        if (pManager && pListener && mpIDs)
            AddListeners(pManager, pListener, pIDs, count);
    }
};
extern const unsigned int kMessageIDs[13];  // 0x0150C008

struct BakerCommand { BakerCommand(void* owner); unsigned int pad[60]; };
void Function_0067de20();

struct KeyAllocator { KeyAllocator() {} };
template <class T> inline void destruct(T* first, T* last) { for (; first < last; ++first) first->~T(); }
template <class T> inline void destruct(T** first, T** last) {}
template <class T> struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    KeyAllocator mAllocator;
    unsigned int mPad;
    VectorBase(const KeyAllocator& a);
    ~VectorBase();
};
template <class T> struct vector : VectorBase<T> {
    vector(const KeyAllocator& a) : VectorBase<T>(a) {}
    ~vector() { destruct(mpBegin, mpEnd); }
    void reserve(unsigned int n);
    unsigned int size() const { return (unsigned int)(mpEnd - mpBegin); }
    T& operator[](unsigned int n) { return mpBegin[n]; }
};

struct IStream {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28();
    virtual int GetSize();
    virtual void Read(void* buf, int n);
};
struct IResourceRecord {
    virtual void v00(); virtual int AddRef(); virtual int Release(); virtual void v0c(); virtual void v10();
    virtual void v14();
    virtual IStream* GetStream();
};
struct IDatabase {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30();
    virtual bool OpenRecord(const ResourceKey& key, IResourceRecord** ppRecord, int a, int b, int c, int d);
    virtual void v38();
    virtual void CloseRecord(IResourceRecord* pRecord);
};

namespace Skinner {
class PaintSystem {
public:
    virtual ~PaintSystem() {}
    virtual bool IsEqual(const PaintSystem& other) const = 0;
    static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
};
class IdPaintSystem : public PaintSystem {
public:
    IdPaintSystem(unsigned int id) : mId(id) {}
    virtual bool IsEqual(const PaintSystem& other) const;
    unsigned int mId;
};

// @ 0x00404460
bool IdPaintSystem::IsEqual(const PaintSystem& other) const
{
    return static_cast<const IdPaintSystem&>(other).mId == mId;
}
}

// @ 0x00404430
// Skinner::PaintSystem's scalar deleting destructor (??_G), emitted with the vtable;
// IdPaintSystem's identical one was folded into it by the linker.

struct IResourceManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void FindRecords(vector<ResourceKey>* keys, const Skinner::PaintSystem& filter, vector<IDatabase*>* dbs);
};
IResourceManager* ResourceManager();  // 0x0067DCD0

struct BufferPool { void* Alloc(int size, int flags); };
struct BufferMap { void*& operator[](const unsigned __int64& key); };

struct PropertyID {
    unsigned int mIndex : 8;
    unsigned int mGroup : 8;
    unsigned int mType : 8;
    unsigned int mUnused : 6;
    unsigned int mKind : 2;
    PropertyID(int type, int group) {
        *(unsigned int*)this = 0;
        mKind = 1;
        mType = type;
        mGroup = group;
    }
};

struct IPropList : IObject {};
struct IPropManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20(); virtual void v24();
    virtual void v28();
    virtual bool GetPropertyListImpl(unsigned int name, PropertyID id, IPropList** ppList);

};
IPropManager* PropManager();  // 0x0067DE30
bool GetPropertyKeys(IPropList* list, unsigned int id, int* count, ResourceKey** keys);
bool GetPropertyFloats(IPropList* list, unsigned int id, int* count, float** values);

struct FloatMap { float& operator[](const ResourceKey& key); unsigned int pad[8]; };

struct Blob56 { unsigned int d[14]; Blob56(); };
struct SortEntry { unsigned int a, b, c; };
struct SortLess {};
void SortEntries(SortEntry* first, SortEntry* last, SortLess compare);
extern SortEntry kSortTable[];  // 0x0150C050
extern int kSortTableCount;      // 0x013EC430
inline void sort(SortEntry* first, SortEntry* last, SortLess compare) { SortEntries(first, last, compare); }

struct Base0 { virtual void v00(); };
class cBaker : public Base0, public IMessageListener {
public:
    virtual void v04(); virtual void v08(); virtual void v0c(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1c();
    virtual bool Initialize();
    void Reset(int);          // 0x00411890
    void LoadSettings();      // 0x004124b0

    unsigned int pad08[(0x30 - 0x08) / 4];
    BufferMap mBuffers;       // 0x30
    unsigned int pad34[(0x50 - 0x34) / 4];
    BufferPool mPool;         // 0x50
    unsigned int pad54[(0x74 - 0x54) / 4];
    intrusive_ptr<IWindowGroup> mpWindow;      // 0x74
    intrusive_ptr<IWindowGroup> mpProgress;    // 0x78
    unsigned int pad7c[(0x88 - 0x7c) / 4];
    intrusive_ptr<cBlockData> mpBlockData;     // 0x88
    intrusive_ptr<cBakeQueue> mpQueue;         // 0x8c
    unsigned int pad90[(0xb8 - 0x90) / 4];
    bool mbBaking;                             // 0xb8
    unsigned int padbc[(0x1100 - 0xbc) / 4];
    Blob56 mSettings;                          // 0x1100
    unsigned int pad1138[(0x1168 - 0x1138) / 4];
    MessageRegistration mMessages;             // 0x1168
    unsigned int pad117c[(0x1184 - 0x117c) / 4];
    FloatMap mGeomInfo[6];                     // 0x1184
};

// @ 0x00403AF0
// virtual slot 8 of the vtable at 0x013EB2F0
bool cBaker::Initialize()
{
    SortEntry* pTable = kSortTable;
    sort(pTable, pTable + kSortTableCount, SortLess());

    mSettings = Blob56();

    mpWindow = WindowManager()->FindWindowByID(0x227d899, 0, 0);
    mpWindow->SetFlag(1, 0, 0);
    mpWindow->SetVisible(true);
    mpProgress = WindowManager()->FindWindowByID(0x227d89a, 0, 0);
    mpProgress->SetVisible(false);

    mpBlockData = new("Editor", 0, 0, 0, 0) cBlockData();
    mpQueue = new("Editor", 0, 0, 0, 0) cBakeQueue(1.0f);

    mMessages.Init(MessageManager(), this, kMessageIDs, 13);
    Reset(0);
    new("Editor", 0, 0, 0, 0) BakerCommand(this);
    Function_0067de20();

    vector<ResourceKey> keys((KeyAllocator()));
    vector<IDatabase*> dbList((KeyAllocator()));
    keys.reserve(0x800);
    ResourceManager()->FindRecords(&keys, Skinner::IdPaintSystem(0x5caa5e28), &dbList);

    for (int i = 0, n = (int)keys.size(); i < n; i++) {
        ResourceKey key = keys[i];
        IDatabase* pDB = dbList[i];
        intrusive_ptr<IResourceRecord> pRecord;
        if (pDB) {
            if (pDB->OpenRecord(key, pRecord.AsOutParam(), 1, 6, 1, 0)) {
                IStream* pStream = pRecord->GetStream();
                int size = pStream->GetSize();
                if (size >= 0x24 && size < 100000) {
                    void* pData = mPool.Alloc(size, 1);
                    pStream->Read(pData, size);
                    unsigned __int64 fullID = key.instanceID | ((unsigned __int64)key.groupID << 32);
                    mBuffers[fullID] = pData;
                }
                pDB->CloseRecord(pRecord.get());
            }
        }
    }

    mbBaking = false;
    LoadSettings();

    for (int i = 0; i < 6; i++) {
        int type = i + 'a';
        intrusive_ptr<IPropList> pList;
        if (PropManager()->GetPropertyListImpl(HashString("GeomInfo"), PropertyID(type, 1), pList.AsOutParam())) {
            int keyCount;
            ResourceKey* pKeyList;
            int valueCount;
            float* pValues;
            if (GetPropertyKeys(pList.get(), 0x66f235b, &keyCount, &pKeyList) &&
                GetPropertyFloats(pList.get(), 0x66f235c, &valueCount, &pValues) &&
                keyCount == valueCount) {
                for (int j = 0; j < keyCount; j++)
                    mGeomInfo[i][pKeyList[j]] = pValues[j];
            }
        }
    }
    return true;
}
