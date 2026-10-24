// Slice s00e4aa60: SP editor-side helpers - the wide-string search map lookup, the
// arg-script value converter, the resource type-table walkers, resource creation and the
// catalog/asset helpers.
//
// The type-table walkers recurse through `this`, so they are members of a walker class;
// the retail recursion reloads `this` from its spill slot, which the /O2 codegen here
// reproduces.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"
#include <intrin.h>

inline void* operator new(uint32_t, void* p) { return p; }

// ---------------------------------------------------------------------------
// Externals (retail addresses in comments; call targets are masked during comparison)
// ---------------------------------------------------------------------------
extern "C" void* __cdecl operator_new(uint32_t size, const char* tag, int a, int b, const char* file, int line); // 0x00f473a0
extern "C" void __cdecl operator_delete_array(void* p);                                                          // 0x00f47380

extern char szNameSimulator[];   // 0x013f09b4 "Simulator"
extern char szNameEastl[];       // 0x013f2150 "EASTL"
extern char szAllocatorFile[];   // 0x013ebb38 ".../EASTL/allocator.h"
extern char szCatalogTxt[];      // 0x015a5c20 catalog file name
extern char szCellGame[];        // 0x015a5c1c
extern char szDataDir[];         // data dir name used by the .cel scan

extern wchar_t gEmptyString16[]; // 0x01667bac

extern void* GetManager();       // 0x0067dcd0  EA::ResourceMan::GetManager
extern void* MessageServer();    // 0x0067dcc0  SP::MessageServer
extern void* GetDataDir(void*);  // 0x00688cb0  SP::GetDataDir

uint32_t FNV1_String16(const wchar_t* pText, uint32_t hash, uint32_t flags); // 0x00932f30
uint32_t FNVHash(const wchar_t* pText, uint32_t hash, uint32_t flags);       // 0x00932e80

int ParseEnum(const char* pText, int* pOut);                                 // 0x00840bb0
void* Matrix3FromEulerXYZ(void* pOut, const void* pEuler);                   // 0x005f4e80

// resource type table record walkers
int FUN_00e4a8a0(int type);                                                  // 0x00e4a8a0
bool FUN_00e4a910(int type);                                                 // 0x00e4a910
bool FUN_00e4a960(int type);                                                 // 0x00e4a960
int FUN_00e82420(int handle, int flags);                                     // 0x00e82420

// resource helper functions
bool FUN_008dde50(void* pThis, void* p1, void* p2, void* p3, void* p4);      // 0x008dde50
bool FUN_008ddf70(void* pThis, void* p1, void* p2, void* p3, void* p4);      // 0x008ddf70
void* SP_LockedAlloc(void* pPool, void* a, void* b, void* c, void* d, int size); // 0x009289f0
void FUN_006acfe0(void* pKey, void* pRes);                                   // 0x006acfe0
void FUN_006ad050(void* pRes);                                               // 0x006ad050

// eastl helpers
void* RBTreeIncrement(void* pNode);                                          // 0x00921580
void RBTreeInsert(void* pNew, void* pParent, void* pHeader, int side);        // 0x009216a0

// io helpers
void FilePathCtor(void* pFilePath, const wchar_t* pPath);                    // 0x00930f60
const wchar_t* FilePathGetExtension(void* pFilePath);                        // 0x00930c10
int64_t FUN_00932130(const wchar_t* pPath, int type);                        // 0x00932130
int wcsncmp(const wchar_t* pA, const wchar_t* pB, uint32_t n);
wchar_t* wcsncpy(wchar_t* pDst, const wchar_t* pSrc, uint32_t n);
struct FileStream {
    char mStorage[0x228];
    FileStream(const wchar_t* pPath);                       // 0x00931da0 (ret 4)
    void SetPath16(const wchar_t* pPath);                   // 0x00931810
    bool Open(int a, int b, int c, int d);                  // 0x009318f0
    bool Close();                                           // 0x00931a70
    ~FileStream();                                          // 0x00931e70
    void WriteString(const char* pText, int len, int n);    // 0x0093abd0
};
void* DirectoryFindFirst(const wchar_t* pPath, const wchar_t* pMask, int a, int b); // 0x0092e730
void DirectoryFindFinish(void* pHandle);                                     // 0x0092e9b0

// ---------------------------------------------------------------------------
// eastl strings
// ---------------------------------------------------------------------------
struct string16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    string16() : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {}
    ~string16()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
    }
    void DoFree(wchar_t* p, uint32_t n)
    {
        if (p)
            operator_delete_array(p);
    }
    const wchar_t* c_str() const { return mpBegin; }
    void sprintf(const wchar_t* fmt, ...);   // 0x0041e050
};

struct string8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    string8() : mpBegin((char*)gEmptyString16), mpEnd((char*)gEmptyString16), mpCapacity((char*)gEmptyString16 + 1) {}
    ~string8()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (uint32_t)(mpCapacity - mpBegin));
    }
    void DoFree(char* p, uint32_t n)
    {
        if (p)
            operator_delete_array(p);
    }
    const char* c_str() const { return mpBegin; }
    void sprintf(const char* fmt, ...);      // 0x00472fe0
};

// ---------------------------------------------------------------------------
// SP app-data globals (0x016ad060 points at this block)
// ---------------------------------------------------------------------------
struct cMapNode {
    cMapNode* mpRight;    // +0x00
    cMapNode* mpLeft;     // +0x04
    cMapNode* mpParent;   // +0x08
    int32_t mColor;       // +0x0c
};

struct cVarNode {
    cMapNode mHeader;     // +0x00
    string8 mName;        // +0x10
    uint32_t mUnk1c;      // +0x1c
    int32_t mValue;       // +0x20
};

struct cVarMap {
    uint32_t mUnk0;       // +0x00
    cMapNode mAnchor;     // +0x04
    uint32_t mnSize;      // +0x14
    uint32_t mAllocator;  // +0x18
    cMapNode* begin() const { return mAnchor.mpLeft; }
    cMapNode* end() const { return (cMapNode*)&mAnchor; }
};

// The wide-string -> entry search map living at globals+4.
struct cSearchMap {
    int32_t GetPriority();          // 0x00e31100
    void* Find(void* pKey);         // 0x00b72230
    void Remove(void* pKey);        // 0x00b72260
};

struct cEntryNode {
    void* mpKey;          // +0x00
    uint32_t mHash;       // +0x04
    void* mpObject;       // +0x08
    void* mpResource;     // +0x0c
};

struct Vec2 { float x; float y; };
struct Vec3 { float x; float y; float z; };
struct Mat3 { float m[9]; };

// The arg-script value converter interface.
struct cArgScript {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(); virtual void v54(); virtual void v58(); virtual void v5c();
    virtual void v60(); virtual void v64(); virtual void v68(); virtual void v6c();
    virtual void v70(); virtual void v74(); virtual void v78(); virtual void v7c();
    virtual void v80(); virtual void v84(); virtual void v88(); virtual void v8c();
    virtual void v90();
    virtual bool ToBool(const void* pValue);                    // +0x94
    virtual float ToFloat(const void* pValue);                  // +0x98
    virtual int32_t ToInt(const void* pValue);                  // +0x9c
    virtual void vA0();
    virtual Vec2* ToVec2(Vec2* pOut, const void* pValue);       // +0xa4
    virtual Vec3* ToVec3(Vec3* pOut, const void* pValue);       // +0xa8
};

struct cSPAppDataGlobals {
    uint32_t mUnk00;              // +0x00
    cSearchMap mSearch;           // +0x04
    uint32_t mPad[6];             // +0x08..+0x20
    cArgScript* mpArgScript;      // +0x20
    uint32_t mUnk24;              // +0x24
    cVarMap mVarMap;              // +0x28
};

extern cSPAppDataGlobals* gspAppDataGlobals;   // 0x016ad060

// Resource type table: a linked list of type defs and the field records of each type.
struct cTypeRecord {
    uint32_t mUnk00;      // +0x00
    uint32_t mUnk04;      // +0x04
    int32_t mOffset;      // +0x08  (-1 terminates the record array)
    int32_t mCountOffset; // +0x0c
    int32_t mType;        // +0x10
    int32_t mFlags;       // +0x14
    uint32_t mPad[4];     // +0x18..+0x28
};

struct cTypeDef {
    uint32_t mUnk00;              // +0x00
    cTypeRecord* mpRecords;       // +0x04
    int32_t mId;                  // +0x08
    uint32_t mUnk0c;              // +0x0c
    uint32_t mUnk10;              // +0x10
    uint32_t mUnk14;              // +0x14
    uint32_t mUnk18;              // +0x18
    void (*mpfn1c)(void*);        // +0x1c
    void (*mpfn20)(void*);        // +0x20
    uint32_t mPad24;              // +0x24
    cTypeDef* mpNext;             // +0x28
};

extern cTypeDef* gspTypes;   // 0x016ad064  head of the type-def list

// ---------------------------------------------------------------------------
// 0x00e4aa60  find the search-map entry whose wide-string hash matches
// ---------------------------------------------------------------------------
// @ 0x00e4aa60
cEntryNode* FUN_00e4aa60(const wchar_t* pText)
{
    uint32_t hash = FNV1_String16(pText, 0x811c9dc5, 1);
    int32_t key = gspAppDataGlobals->mSearch.GetPriority();
    cEntryNode* pFound = (cEntryNode*)gspAppDataGlobals->mSearch.Find(&key);
    while (pFound) {
        if (pFound->mHash == hash)
            return pFound;
        pFound = (cEntryNode*)gspAppDataGlobals->mSearch.Find(&key);
    }
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00e4aad0  SP::sStringToData - convert an arg-script value to raw data
// ---------------------------------------------------------------------------
Vec3 gVec3Result;    // 0x016ad0a8
Vec2 gVec2Result;    // 0x016ad0a0
Mat3 gMat3Result;    // 0x016ad0b4

// @ 0x00e4aad0
uintptr_t SP_sStringToData(const void* pValue, const cTypeRecord* pRecord)
{
    switch (pRecord->mType) {
    case 1: {
        int32_t value = gspAppDataGlobals->mpArgScript->ToInt(pValue);
        return (uintptr_t)value;
    }
    case 2: {
        float value = gspAppDataGlobals->mpArgScript->ToFloat(pValue);
        return *(uint32_t*)&value;
    }
    case 5: {
        int32_t value = ParseEnum((const char*)pValue, (int*)((char*)pRecord + 0x24));
        return (uintptr_t)value;
    }
    case 6: {
        bool value = gspAppDataGlobals->mpArgScript->ToBool(pValue);
        return (uintptr_t)(int32_t)value;
    }
    case 8: {
        Vec3 tmp;
        const Vec3* pVec = gspAppDataGlobals->mpArgScript->ToVec3(&tmp, pValue);
        gVec3Result = *pVec;
        return (uintptr_t)&gVec3Result;
    }
    case 9: {
        Vec3 tmp;
        const Vec3* pVec = gspAppDataGlobals->mpArgScript->ToVec3(&tmp, pValue);
        Mat3 tmpMat;
        const Mat3* pMat = (const Mat3*)Matrix3FromEulerXYZ(&tmpMat, pVec);
        gMat3Result = *pMat;
        return (uintptr_t)&gMat3Result;
    }
    case 11: {
        Vec2 tmp;
        const Vec2* pVec = gspAppDataGlobals->mpArgScript->ToVec2(&tmp, pValue);
        gVec2Result = *pVec;
        return (uintptr_t)&gVec2Result;
    }
    case 3:
    case 7:
    case 10:
        break;
    }
    return (uintptr_t)pValue;
}

// ---------------------------------------------------------------------------
// 0x00e4ac90  count / collect the ids of the registered type defs
// ---------------------------------------------------------------------------
// @ 0x00e4ac90
uint32_t __stdcall FUN_00e4ac90(uint32_t* pOut, uint32_t max)
{
    uint32_t n = 0;
    cTypeDef* pType = gspTypes;
    if (!pOut) {
        if (pType) {
            do {
                pType = pType->mpNext;
                ++n;
            } while (pType);
        }
        return n;
    }
    for (; pType && n < max; ++n) {
        pOut[n] = (uint32_t)pType->mId;
        pType = pType->mpNext;
    }
    return n;
}

// Stream used while reading a resource: it hands out handles for nested arrays.
struct IRecStream {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual int32_t v24(int32_t flags);                        // +0x24
    virtual void v28(); virtual void v2c(); virtual void v30(); virtual void v34();
    virtual void v38(uint32_t value, int32_t size);            // +0x38
};

// The record walkers below are members so that the recursion passes `this` in ecx.
struct cFieldWalker {
    void OffsetInstances(void* pArg1, char* pBase, cTypeDef* pType);                          // 0x00e4ace0
    void AdjustPointers(void* pDelta, char* pBase, cTypeDef* pType);                          // 0x00e4add0
    void ReadRecords(IRecStream* pStream, char* pBase, cTypeDef* pType);                      // 0x00e4ae80
};

// @ 0x00e4ace0
void cFieldWalker::OffsetInstances(void* pArg1, char* pBase, cTypeDef* pType)
{
    cTypeRecord* pRecord = pType->mpRecords;
    if (pRecord->mOffset == -1)
        return;
    int32_t offset = 0;
    do {
        int32_t type = pRecord->mType;
        int32_t* pValue = (int32_t*)(pBase + pRecord->mOffset);
        if (type == 3) {
            if (*pValue)
                *pValue = FUN_00e82420(*pValue, pRecord->mFlags);
        } else if (pRecord->mFlags == 4) {
            if (type >= 0xc && FUN_00e4a910(type)) {
                int32_t value = *pValue;
                int32_t size = FUN_00e4a8a0(type);
                int32_t count = *(int32_t*)(pBase + pRecord->mCountOffset);
                if (count > 0) {
                    do {
                        OffsetInstances(pArg1, (char*)(uintptr_t)value, (cTypeDef*)(uintptr_t)type);
                        value += size;
                        --count;
                    } while (count != 0);
                }
            }
        } else {
            if (type >= 0xc && FUN_00e4a910(type))
                OffsetInstances(pArg1, (char*)pValue, (cTypeDef*)(uintptr_t)type);
        }
        offset += 0x28;
        pRecord = (cTypeRecord*)((char*)pType->mpRecords + offset);
    } while (pRecord->mOffset != -1);
}

// @ 0x00e4add0
void cFieldWalker::AdjustPointers(void* pDelta, char* pBase, cTypeDef* pType)
{
    cTypeRecord* pRecord = pType->mpRecords;
    if (pRecord->mOffset == -1)
        return;
    int32_t offset = 0;
    do {
        if (pRecord->mFlags == 4) {
            uint32_t value = *(uint32_t*)(pBase + pRecord->mOffset);
            if (value <= 0xffff) {
                value += (uint32_t)pDelta;
                *(uint32_t*)(pBase + pRecord->mOffset) = value;
                if (pRecord->mType >= 0xc && FUN_00e4a960(pRecord->mType)) {
                    int32_t size = FUN_00e4a8a0(pRecord->mType);
                    int32_t count = *(int32_t*)(pBase + pRecord->mCountOffset);
                    if (count > 0) {
                        do {
                            AdjustPointers(pDelta, (char*)(uintptr_t)value, (cTypeDef*)(uintptr_t)pRecord->mType);
                            value += size;
                            --count;
                        } while (count != 0);
                    }
                }
            }
        }
        offset += 0x28;
        pRecord = (cTypeRecord*)((char*)pType->mpRecords + offset);
    } while (pRecord->mOffset != -1);
}

// @ 0x00e4ae80
void cFieldWalker::ReadRecords(IRecStream* pStream, char* pBase, cTypeDef* pType)
{
    cTypeRecord* pRecord = pType->mpRecords;
    if (pRecord->mOffset == -1)
        return;
    int32_t offset = 0;
    do {
        if (pRecord->mFlags == 4) {
            int32_t size = FUN_00e4a8a0(pRecord->mType);
            int32_t count = *(int32_t*)(pBase + pRecord->mCountOffset);
            uint32_t value = *(uint32_t*)(pBase + pRecord->mOffset);
            if (value >= 0xffff) {
                int32_t handle = pStream->v24(0);
                pStream->v38(value, count * size);
                *(uint32_t*)(pBase + pRecord->mOffset) = (uint32_t)handle;
                if (pRecord->mType >= 0xc && FUN_00e4a960(pRecord->mType) && count > 0) {
                    do {
                        ReadRecords(pStream, (char*)(uintptr_t)value, (cTypeDef*)(uintptr_t)pRecord->mType);
                        value += size;
                        --count;
                    } while (count != 0);
                }
            }
        }
        offset += 0x28;
        pRecord = (cTypeRecord*)((char*)pType->mpRecords + offset);
    } while (pRecord->mOffset != -1);
}

// ---------------------------------------------------------------------------
// Editor resource objects
// ---------------------------------------------------------------------------
// A resource object pool entry: the property list ctor is out of line (0x008ddff0), the
// derived class then installs its own vtable and clears its owner slot.
struct cPropertyListBase {
    cPropertyListBase();       // 0x008ddff0
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c(uint32_t id);
    uint32_t mUnk04;           // +0x04
    uint32_t mUnk08;           // +0x08
    uint32_t mUnk0c;           // +0x0c
    uint32_t mUnk10;           // +0x10
    uint32_t mUnk14;           // +0x14
    uint32_t mUnk18;           // +0x18
};

struct cEditorResource : cPropertyListBase {
    cEditorResource() : mpOwner(0) {}
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c(uint32_t id);
    void* mpOwner;             // +0x1c
};

struct ISimulatorObject {
    virtual void v00(); virtual void v04();
    virtual void v08(int flags);    // +0x08
};

// The out stream that accepts the new resource.
struct IEditorStream {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20();
    virtual bool Process(uint32_t a, void* pResource, uint32_t b, uint32_t c);  // +0x24
    bool CreateResource(uint32_t param1, ISimulatorObject** ppOut, uint32_t param3, uint32_t param4);
};

// @ 0x00e4af90
bool IEditorStream::CreateResource(uint32_t param1, ISimulatorObject** ppOut, uint32_t param3, uint32_t param4)
{
    if (!ppOut)
        return false;
    cEditorResource* pResource = 0;
    void* pMem = operator_new(0x20, szNameSimulator, 0, 0, 0, 0);
    if (pMem) {
        pResource = new (pMem) cEditorResource;
    }
    *ppOut = (ISimulatorObject*)pResource;
    if (!pResource)
        return false;
    pResource->v00();
    if (param1) {
        if (!Process(param1, *ppOut, param3, param4)) {
            if (*ppOut)
                (*ppOut)->v08(1);
            return false;
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// 0x00e4b030  resource load hook: bind the type def to the loaded owner
// ---------------------------------------------------------------------------
struct IIdentifiable {
    virtual void v00(); virtual void v04(); virtual void v08();
    virtual void* GetObject(uint32_t id);   // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void v1c();                     // +0x1c
};

struct IEditorObject {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void* v18();                    // +0x18
    virtual void v1c();
    virtual void v20(uint32_t value);       // +0x20
    virtual void v24();
    virtual void v28(int a, int b);         // +0x28
};

struct cResourceOwner {
    char pad0[0x14];
    char* mData;           // +0x14
    void* mHandle;         // +0x18
    char* mpType;          // +0x1c (the type def slot written by the load hook)
};

struct cLoadHook : cFieldWalker {
    bool BeginLoad(void* p1, void* p2, uint32_t p3, uint32_t p4);                 // 0x008dde50
    bool EndLoad(void* p1, void* p2, uint32_t p3, uint32_t p4);                   // 0x008ddf70
    bool Load(void* p1, IIdentifiable* p2, uint32_t p3, uint32_t p4);              // 0x00e4b030
    bool LoadStream(IIdentifiable* p1, IEditorObject* p2, uint32_t p3, uint32_t p4); // 0x00e4b0c0
};

static cTypeDef* FindTypeById(int32_t id)
{
    for (cTypeDef* pType = gspTypes; pType; pType = pType->mpNext) {
        if (pType->mId == id)
            return pType;
    }
    return 0;
}

// @ 0x00e4b030
bool cLoadHook::Load(void* p1, IIdentifiable* p2, uint32_t p3, uint32_t p4)
{
    if (!BeginLoad(p1, p2, p3, p4))
        return false;
    for (cTypeDef* pType = gspTypes; pType; pType = pType->mpNext) {
        if ((uint32_t)pType->mId == p4) {
            cResourceOwner* pOwner;
            if (p2)
                pOwner = (cResourceOwner*)p2->GetObject(0x116d51e);
            else
                pOwner = 0;
            pOwner->mpType = (char*)pType;
            AdjustPointers(pOwner->mData, pOwner->mData, pType);
            OffsetInstances(pOwner->mData, pOwner->mData, pType);
            return true;
        }
    }
    return true;
}

// @ 0x00e4b0c0
bool cLoadHook::LoadStream(IIdentifiable* p1, IEditorObject* p2, uint32_t p3, uint32_t p4)
{
    cResourceOwner* pOwner;
    if (p1)
        pOwner = (cResourceOwner*)p1->GetObject(0x2269ed1);
    else
        pOwner = 0;
    IEditorObject* pObj = (IEditorObject*)p2->v18();
    pObj->v20((uint32_t)(uintptr_t)pOwner->mHandle);
    pObj->v28(0, 2);
    int32_t id = (int32_t)p4;
    cTypeDef* pType = gspTypes;
    while (pType && pType->mId != id)
        pType = pType->mpNext;
    ReadRecords((IRecStream*)pObj, pOwner->mData, pType);
    pObj->v28(0, 0);
    return EndLoad(p1, p2, p3, p4);
}

// ---------------------------------------------------------------------------
// 0x00e4b170  SP::cResourceWriteLock::Release
// ---------------------------------------------------------------------------
struct tRefCounted {
    virtual void v00();
    int32_t mRefCount;        // +0x04
    tRefCounted() { _InterlockedExchange((volatile long*)&mRefCount, 0); }
};

struct cCreationContext : tRefCounted {
    virtual void v00();
};

struct ResourceKeyInfo {
    uint32_t mInstance;       // +0x00
    uint32_t mType;           // +0x04
    uint32_t mGroup;          // +0x08
};

struct IResourceManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(void* pRes, uint32_t a, uint32_t b, void* pContext, uint32_t c);  // +0x20
};

struct cResourceWriteLock {
    void* mResource[32];      // +0x00
    int32_t mNumResources;    // +0x80
    void Release();           // 0x00e4b170
};

// @ 0x00e4b170
void cResourceWriteLock::Release()
{
    cCreationContext context;
    int32_t i = 0;
    if (mNumResources < 1) {
        mNumResources = 0;
        return;
    }
    do {
        void* pRes = mResource[i];
        ResourceKeyInfo key;
        key.mInstance = *(uint32_t*)((char*)pRes + 8);
        key.mType = *(uint32_t*)((char*)pRes + 0x0c);
        key.mGroup = *(uint32_t*)((char*)pRes + 0x10);
        FUN_006acfe0(&key, pRes);
        IResourceManager* pManager = (IResourceManager*)GetManager();
        pManager->v20(mResource[i], 0, gspAppDataGlobals->mUnk24, &context, 0);
        FUN_006ad050(mResource[i]);
        cTypeDef* pType;
        for (pType = gspTypes; pType; pType = pType->mpNext) {
            if ((uint32_t)pType->mId == key.mType)
                break;
        }
        if (pType->mpfn20) {
            cResourceOwner* pOwner = 0;
            if (mResource[i])
                pOwner = (cResourceOwner*)((IIdentifiable*)mResource[i])->GetObject(0x2269ed1);
            pType->mpfn20(pOwner->mData);
        }
        ((ISimulatorObject*)mResource[i])->v04();
        ++i;
    } while (i < mNumResources);
    mNumResources = 0;
}

// ---------------------------------------------------------------------------
// 0x00e4b280  eastl rbtree insert (map node with a key object)
// ---------------------------------------------------------------------------
struct KeyString {
    char pad[0x14];
    KeyString(const void* pSrc);      // 0x00b20b90
};

struct MapNode {
    MapNode* mpRight;         // +0x00
    MapNode* mpLeft;          // +0x04
    MapNode* mpParent;        // +0x08
    int32_t mColor;           // +0x0c
    KeyString mKey;           // +0x10
    uint32_t mPad24;          // +0x24
};

struct MapTree {
    uint32_t mUnk0;           // +0x00
    cMapNode mAnchor;         // +0x04
    int32_t mnSize;           // +0x14
    uint32_t mAllocator;      // +0x18
    void Insert(MapNode** ppOut, MapNode* pParent, const void* pKey, bool bRoot);  // 0x00e4b280
};

// @ 0x00e4b280
void MapTree::Insert(MapNode** ppOut, MapNode* pParent, const void* pKey, bool bRoot)
{
    int32_t side;
    if (!bRoot && pParent != (MapNode*)&mAnchor && *(const int32_t*)pKey >= *(int32_t*)((char*)pParent + 0x10))
        side = 1;
    else
        side = 0;
    MapNode* pNew = (MapNode*)operator_new(0x24, szNameEastl, 0, 0, szAllocatorFile, 0xd1);
    new (&pNew->mKey) KeyString(pKey);
    RBTreeInsert(pNew, pParent, (MapNode*)&mAnchor, side);
    ++mnSize;
    *ppOut = pNew;
}

// ---------------------------------------------------------------------------
// 0x00e4b390  SP::sFileInfo
// ---------------------------------------------------------------------------
struct sFileInfoData {
    wchar_t mName[0x100];     // +0x000
    wchar_t mType[0x100];     // +0x200
    wchar_t mExt[0x100];      // +0x400
    uint32_t mTime;           // +0x600
};

struct FilePath {
    char pad[0x180];
};

// @ 0x00e4b390
void SP_sFileInfo(sFileInfoData* pInfo, const wchar_t* pA, const wchar_t* pB)
{
    string16 path;
    path.sprintf(L"%s%s", pA, pB);
    wcsncpy(pInfo->mName, pA, 0xff);
    pInfo->mName[0xff] = 0;
    wcsncpy(pInfo->mType, pB, 0xff);
    pInfo->mType[0xff] = 0;
    FilePath filePath;
    FilePathCtor(&filePath, path.c_str());
    wcsncpy(pInfo->mExt, FilePathGetExtension(&filePath), 0xff);
    pInfo->mExt[0xff] = 0;
    pInfo->mTime = (uint32_t)FUN_00932130(path.c_str(), 2);
}

// ---------------------------------------------------------------------------
// 0x00e4b470  SP::sFormatCatalogLine
// ---------------------------------------------------------------------------
// @ 0x00e4b470
void __fastcall SP_sFormatCatalogLine(const wchar_t* pDir, int32_t version)
{
    string16 path;
    path.sprintf(L"%s%s", pDir, (const wchar_t*)szCatalogTxt);
    FileStream fs(0);
    fs.SetPath16(path.c_str());
    fs.Open(2, 2, 1, 0);
    string8 line;
    line.sprintf("%d version", version);
    fs.WriteString(line.mpBegin, (int)(line.mpEnd - line.mpBegin), 1);
    cVarMap* pMap = &gspAppDataGlobals->mVarMap;
    for (cMapNode* pNode = pMap->begin(); pNode != pMap->end(); pNode = (cMapNode*)RBTreeIncrement(pNode)) {
        cVarNode* pVar = (cVarNode*)pNode;
        string8 entry;
        entry.sprintf("%s %d", pVar->mName.c_str(), pVar->mValue);
        fs.WriteString(entry.mpBegin, (int)(entry.mpEnd - entry.mpBegin), 1);
    }
    fs.Close();
}

// ---------------------------------------------------------------------------
// 0x00e4b5f0  cell-file change notification
// ---------------------------------------------------------------------------
struct cFileChangeMessage {
    virtual void v00();
    virtual void v04();
    int32_t mRefCount;        // +0x04
    sFileInfoData mInfo;      // +0x08
    uint32_t mFlags;          // +0x60c
};

struct IMessageServer {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void Send(uint32_t id, void* pMessage, uint32_t a, uint32_t b);   // +0x18
};

// @ 0x00e4b5f0
void SP_sFileChange(const wchar_t* pPath, uint32_t p2, uint32_t p3, uint32_t p4, uint32_t p5)
{
    FilePath filePath;
    FilePathCtor(&filePath, pPath);
    if (wcsncmp(FilePathGetExtension(&filePath), L".cel", 4) != 0)
        return;
    cFileChangeMessage* pMsg = 0;
    void* pMem = operator_new(0x610, szNameSimulator, 0, 0, 0, 0);
    if (pMem) {
        pMsg = new (pMem) cFileChangeMessage;
    }
    (void)p2;
    (void)p3;
    (void)p4;
    SP_sFileInfo(&pMsg->mInfo, pPath, pPath);
    pMsg->mFlags = p5;
    IMessageServer* pServer = (IMessageServer*)MessageServer();
    pServer->Send(0x4a4e97f, pMsg, 0, 0);
}

// ---------------------------------------------------------------------------
// 0x00e4b6c0  create the resource manager
// ---------------------------------------------------------------------------
struct cResManager {
    char pad[0x240];
    cResManager* Construct();                                    // 0x0092f960
    bool Init();                                                 // 0x008de220
    void SetCallback(void (*pFn)(const wchar_t*, uint32_t, uint32_t, uint32_t, uint32_t), void* pArg); // 0x0092f5d0
    void SetFlags(int32_t flags);                                // 0x0092fa90
    void SetArg(void* pArg);                                     // 0x0092fa50
    void Finish();                                               // 0x0092faf0
};

// @ 0x00e4b6c0
cResManager* FUN_00e4b6c0(void* p1, void* p2)
{
    cResManager* pManager;
    void* pMem = operator_new(0x240, szNameSimulator, 0, 0, 0, 0);
    if (pMem) {
        pManager = ((cResManager*)pMem)->Construct();
    } else {
        pManager = 0;
    }
    pManager->Init();
    pManager->SetCallback(&SP_sFileChange, p2);
    pManager->SetFlags(8);
    pManager->SetArg(p1);
    pManager->Finish();
    return pManager;
}

// ---------------------------------------------------------------------------
// 0x00e4b730  SP::sAssetCreate
// ---------------------------------------------------------------------------
struct AssetKey {
    uint32_t mHash;           // +0x00
    uint32_t mType;           // +0x04
    uint32_t mGroup;          // +0x08
    uint32_t mSize;           // +0x0c
};

struct cAsset {
    uint32_t mpVtbl;          // +0x00
    uint32_t mUnk04;          // +0x04
    uint32_t mUnk08;          // +0x08
    uint32_t mUnk0c;          // +0x0c
    uint32_t mUnk10;          // +0x10
    void* mpData;             // +0x14
    uint32_t mSize;           // +0x18
    AssetKey* mpKey;          // +0x1c
};

struct cAssetArray {
    uint32_t mUnk[0x80];
    uint32_t mCount;          // +0x80
};

// @ 0x00e4b730
void* SP_sAssetCreate(const wchar_t* pName, uint32_t p2, uint32_t p3, uint32_t p4, AssetKey* pKey, cAssetArray* pArray)
{
    uint32_t hash = FNVHash(pName, 0x811c9dc5, 1);
    (void)p2;
    (void)p3;
    (void)p4;
    AssetKey key;
    key.mHash = 0;
    key.mType = hash;
    key.mGroup = pKey->mHash;
    string16 name;
    name.sprintf(L"%S.%S", pName, (const wchar_t*)pKey->mGroup);
    IResourceManager* pManager = (IResourceManager*)GetManager();
    ((void(__thiscall*)(void*, AssetKey*, const wchar_t*))((*(void***)pManager)[0x80 / 4]))(pManager, &key, name.c_str());
    cAsset* pAsset = 0;
    void* pMem = operator_new(0x20, szNameSimulator, 0, 0, 0, 0);
    if (pMem) {
        pAsset = new (pMem) cAsset;
    }
    pAsset->mUnk08 = key.mType;
    pAsset->mUnk0c = key.mGroup;
    pAsset->mUnk10 = key.mHash;
    pAsset->mSize = pKey->mSize;
    pAsset->mpData = SP_LockedAlloc(pAsset, 0, 0, 0, 0, (int)pKey->mSize);
    pAsset->mpKey = pKey;
    pArray->mUnk[pArray->mCount] = (uint32_t)(uintptr_t)pAsset;
    ++pArray->mCount;
    return pAsset->mpData;
}

// ---------------------------------------------------------------------------
// 0x00e4b870  does any .cel file exist in the data dir
// ---------------------------------------------------------------------------
// @ 0x00e4b870
bool FUN_00e4b870()
{
    string16 dir;
    dir.sprintf(L"%s%s", GetDataDir(szCellGame), (const wchar_t*)szDataDir);
    void* pFind = DirectoryFindFirst(dir.c_str(), L"*.cel", 0, 0);
    if (pFind) {
        DirectoryFindFinish(pFind);
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// 0x00e4b910  release a search entry's resource and object
// ---------------------------------------------------------------------------
struct IReleaseManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void ReleaseHandle(uint32_t a, IIdentifiable* pResource, int32_t priority);  // +0x50
};

// The search-map object owned by an entry: it is torn down through its own helpers.
struct ISearchObject {
    virtual void Destroy(int32_t mode);   // +0x00
    virtual void v04();
    void Shutdown();                      // 0x0092f5f0
    void Cleanup();                       // 0x0092f9e0
};

// @ 0x00e4b910
void FUN_00e4b910(const wchar_t* pText)
{
    cEntryNode* pEntry = FUN_00e4aa60(pText);
    if (FUN_00e4b870()) {
        IIdentifiable* pResource = (IIdentifiable*)pEntry->mpResource;
        pResource->v1c();
        IReleaseManager* pManager = (IReleaseManager*)GetManager();
        pManager->ReleaseHandle(0, pResource, 100);
        pEntry->mpResource = 0;
    }
    ISearchObject* pObject = (ISearchObject*)pEntry->mpObject;
    pObject->Shutdown();
    pObject->Cleanup();
    if (pObject)
        pObject->Destroy(1);
    gspAppDataGlobals->mSearch.Remove(pEntry->mpKey);
}

// ---------------------------------------------------------------------------
// 0x00e4b990  free a tree of resource descriptor nodes
// ---------------------------------------------------------------------------
struct cDescNode {
    cDescNode* mpLeft;        // +0x00
    cDescNode* mpRight;       // +0x04
    uint32_t mUnk08;          // +0x08
    uint32_t mUnk0c;          // +0x0c
    uint32_t mUnk10;          // +0x10
    char* mpName;             // +0x14
    char* mpNameEnd;          // +0x18
    char* mpNameCapacity;     // +0x1c
};

struct cDescTree {
    void Free(cDescNode* pNode);   // 0x00e4b990
};

// @ 0x00e4b990
void cDescTree::Free(cDescNode* pNode)
{
    while (pNode) {
        Free(pNode->mpLeft);
        cDescNode* pNext = pNode->mpRight;
        char* pName = pNode->mpName;
        if (pNode->mpNameCapacity - pName > 1) {
            if (pName)
                operator_delete_array(pName);
        }
        operator_delete_array(pNode);
        pNode = pNext;
    }
}

// ---------------------------------------------------------------------------
// 0x00e4b9f0  SP::cMyMagicCommand::OnEndBlock
// ---------------------------------------------------------------------------
struct cFieldDef {
    char pad[0x10];
    cTypeDef* mpType;         // +0x10
};

struct cMyMagicCommand {
    char pad0[0x04];
    cFieldDef** mpBegin;      // +0x04
    cFieldDef** mpEnd;        // +0x08
    uint32_t mUnk0c;          // +0x0c
    uint32_t mUnk10;          // +0x10
    uint32_t mUnk14;          // +0x14
    void* mpCallback;         // +0x18
    cResourceWriteLock mLock; // +0x1c
    void OnEndBlock(void* pArg);   // 0x00e4b9f0
};

// @ 0x00e4b9f0
void cMyMagicCommand::OnEndBlock(void* pArg)
{
    (void)pArg;
    if (((uint32_t)((char*)mpEnd - (char*)mpBegin) & 0xfffffffc) == 4) {
        cTypeDef* pType = mpEnd[-1]->mpType;
        if (pType->mpfn1c)
            pType->mpfn1c(mpCallback);
        if (pType->mpfn20)
            pType->mpfn20(mpCallback);
        mLock.Release();
        return;
    }
    --mpEnd;
}
