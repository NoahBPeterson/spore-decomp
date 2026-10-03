// Editor block-loading module (BlockLoader update tick and the editor block-data
// owner's constructor). Built WITHOUT optimization and without C++ EH:
// compile with /Od /Ob1 /MD /Gy /TP (no /EHsc: locals with destructors get no EH frame).
//
// Neither function is byte-exact yet: instruction streams match, but the original
// frames contain dead stack slots (compiler temporaries) not reproduced here, so
// frame offsets differ. See nonmatching.txt.

template <class T> class intrusive_ptr {
public:
    intrusive_ptr() : mpObject(0) {}
    ~intrusive_ptr() { if (mpObject) mpObject->Release(); }
    intrusive_ptr& operator=(T* pObject) {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
    T* get() const { return mpObject; }
    T* operator->() const { return mpObject; }
    operator T*() const { return mpObject; }
    T** GetAddress();       // 0x0041d870
    T** AsOutParam() { return GetAddress(); }
    T* mpObject;
};

template <class T> class vector {
public:
    bool empty() const;     // 0x00526430
    void push_back(const T& v); // 0x004b54b0
    T& back() { return *(mpEnd - 1); }
    void pop_back() { --mpEnd; }
    int size() const { return (int)(mpEnd - mpBegin); }
    T& operator[](int i) { return mpBegin[i]; }
    T* begin() { return mpBegin; }
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    unsigned int mAllocator[2];
};

class Object {
public:
    virtual int AddRef();
    virtual int Release();
};

class Result : public Object {};

class Slot : public Object {
public:
    virtual void v2(); virtual void v3();
    virtual bool IsFinished();                      // +0x10
    virtual bool GetResult(Result** ppResult);      // +0x14
};

class Editor : public Object {
public:
    int GetMode();          // 0x0068f970
    bool IsPlayMode() {
        switch (GetMode()) {
        case 7:
        case 8:
            return true;
        default:
            return false;
        }
    }
    bool IsEditing() { return ((1 << GetMode()) & 0x3c) != 0; }
    void Refresh();         // 0x006909b0
};

struct BlockRequest { unsigned int a, b, c; };

class Item : public Object {
public:
    unsigned char mFlags;
    bool IsHidden() const { return (mFlags & 1) != 0; }
};

class IFactory {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void Create(BlockRequest* req, Slot** ppSlot, Result** ppResult,
                        int a, int b, int c, int d, int e);       // +0x10
};
IFactory* GetFactory();     // 0x0067dcd0

class IItemManager {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13();
    virtual void Process(Item* item, Editor* editor);               // +0x38
};
IItemManager* GetItemManager();  // 0x0067dd60

class IUndoManager {
public:
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
    virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void BeginBatch();   // +0x20
    virtual void EndBatch();     // +0x24
};
IUndoManager* GetUndoManager();  // 0x0068f4d0

void PostMessage(int id, Result* result);     // 0x006ac0a0
Result* CombineResults(intrusive_ptr<Result>* results);   // 0x00421eb0

inline bool IsPlayMode(int mode) { return mode >= 7 && mode <= 8; }

class BlockLoader {
public:
    void Update();
    void ApplyResult(Result* result, bool flag);    // 0x00402470
    void Finish();                                  // 0x00402b30

    unsigned int mVTable;
    unsigned int mField4;
    unsigned int mField8;
    intrusive_ptr<Editor> mpEditor;                 // +0x0c
    vector<BlockRequest> mRequests;                 // +0x10
    vector<intrusive_ptr<Result> > mResults;        // +0x24
    vector<intrusive_ptr<Item> > mItems;                           // +0x38
    intrusive_ptr<Slot> mSlots[6];                  // +0x4c
    bool mbApplyResults;                            // +0x64
    bool mbApplyFlag;                               // +0x65
};

// @ 0x00402cc0
void BlockLoader::Update()
{
    if (!mpEditor || mpEditor->IsPlayMode() || mpEditor->IsEditing())
        return;
    {
        int idleSlots = 0;
        for (int i = 0; i < 6; i++) {
            if (mSlots[i]) {
                intrusive_ptr<Result> result;
                if (mSlots[i]->IsFinished()) {
                    if (mSlots[i]->GetResult(result.AsOutParam())) {
                        PostMessage(9, result);
                        mResults.push_back(result);
                    }
                    mSlots[i] = 0;
                }
            }
            while (!mSlots[i] && !mRequests.empty()) {
                BlockRequest request = mRequests.back();
                mRequests.pop_back();
                intrusive_ptr<Result> result;
                GetFactory()->Create(&request, mSlots[i].AsOutParam(), result.AsOutParam(), 0, 0, 0, 0, 0);
                if (result) {
                    PostMessage(9, result);
                    mResults.push_back(result);
                    mSlots[i] = 0;
                }
            }
            if (!mSlots[i])
                idleSlots++;
        }
        if (idleSlots == 6) {
            if (mbApplyResults) {
                mbApplyResults = false;
                intrusive_ptr<Result> combined;
                if (!mResults.empty())
                    combined = CombineResults(mResults.begin());
                if (combined)
                    ApplyResult(combined, mbApplyFlag);
                else
                    Finish();
            } else {
                GetUndoManager()->BeginBatch();
                int i = 0;
                for (int count = mItems.size(); i < count; i++) {
                    if (!mItems[i]->IsHidden())
                        GetItemManager()->Process(mItems[i], mpEditor);
                }
                mpEditor->Refresh();
                GetUndoManager()->EndBatch();
            }
        }
    }
}

// ===========================================================================
struct DefaultAlloc { DefaultAlloc() {} };

struct Container20 {                      // 0x20 bytes, ctor 0x005640f0
    Container20(const DefaultAlloc& a = DefaultAlloc());
    unsigned int mData[8];
};

struct BlockDataCache {                   // 0x24 bytes, ctor 0x00928cd0
    BlockDataCache(int a, int b, void* (*f1)(), void* (*f2)(), const char* name);
    unsigned int mData[9];
};
void* BlockAlloc();
void* BlockFree();

template <class T> struct RefPtr {
    RefPtr() : mpObject(0) {}
    T* mpObject;
};

struct PtrVector {
    PtrVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    unsigned int mAllocator[2];
};

struct PtrVector2 {
    PtrVector2() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;
    unsigned int mAllocator[3];
};

struct Slot2C {
    Slot2C(const DefaultAlloc& a = DefaultAlloc());
    unsigned int mData[11];
};
struct SlotArray {
    SlotArray() {}
    Slot2C mSlots[8];
};

struct Obj30 { Obj30(); unsigned int d[12]; };
struct Obj68 { Obj68(); unsigned int d[26]; };
struct ObjBig { ObjBig(); unsigned int d[(0x1100 - 0x330) / 4]; };
struct Obj38 { Obj38(); unsigned int d[14]; };
struct Obj18 { Obj18(int n, int flags); unsigned int d[6]; };

struct Range5 {
    Range5() : a(0), b(0), c(0), d(0), e(0) {}
    unsigned int a, b, c, d, e;
};

class IRefCounted { public: virtual int AddRef(); };
class IBaseB0 { public: virtual void f0(); };
class IBaseB : public IBaseB0 { public: virtual void f0(); };
class IBaseC { public: IBaseC() : mField(0) {} virtual void g0(); unsigned int mField; };

class EditorBlockData : public IRefCounted, public IBaseB, public IBaseC {
public:
    EditorBlockData();
    virtual int AddRef();
    virtual void f0();
    virtual void g0();

    Container20 mContainer10;      // +0x10
    Container20 mContainer30;      // +0x30
    BlockDataCache mCache;         // +0x50
    RefPtr<void> mRef74;
    RefPtr<void> mRef78;
    RefPtr<void> mRef7C;
    RefPtr<void> mRef80;
    RefPtr<void> mRef84;
    RefPtr<void> mRef88;
    RefPtr<void> mRef8C;
    PtrVector mVector90;           // +0x90
    PtrVector2 mVectorA4;          // +0xa4
    RefPtr<void> mRefBC;
    bool mFlagC0;
    int mFieldC4;
    SlotArray mSlots;              // +0xc8
    Obj30 mObj228;
    bool mFlag258;
    bool mFlag259;
    Obj68 mObj25C;
    bool mFlag2C4;
    Obj68 mObj2C8;
    ObjBig mObj330;
    Obj38 mObj1100;
    Obj18 mObj1138;
    Obj18 mObj1150;
    Range5 mRange1168;
    RefPtr<void> mRef117C;
    bool mFlag1180;
    Container20 mContainers[6];    // +0x1184
};

// @ 0x00403240
EditorBlockData::EditorBlockData()
    : mCache(0, -1, BlockAlloc, BlockFree, "Editor/BlockData"),
      mFlagC0(true), mFieldC4(0), mFlag258(false), mFlag259(false), mFlag2C4(false),
      mObj1138(5, 0), mObj1150(5, 0), mFlag1180(false)
{
}
