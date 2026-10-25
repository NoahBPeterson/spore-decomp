// src/game/SPGonzago/SPAppData.cpp -- migrated from slice(s) s00e4ba40, s00e4aa60, s00e39ab0, s00453250 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPAppData.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <math.h>
#include <string.h>
#include <new>
#include <xmmintrin.h>
#include "cSPUILayout.h"
#include "SP/cStarManager.h"
#include "SP/cTerrainSphere.h"
#include <stddef.h>
#include "EA/IO/FileStream.h"
#include "SP/cEditorResource.h"
#include "EA/ResourceMan/Manager.h"
#include "SP/cTypeDef.h"
#include <intrin.h>
#include "EA/ResourceMan/FactoryBinary.h"

// ---- items of slice s00453250 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(float ax, float ay, float az) : x(ax), y(ay), z(az) {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
    void Set(float ax, float ay, float az) { x = ax; y = ay; z = az; }
};
struct Matrix33 {
    Vector3 xAxis, yAxis, zAxis;
    Matrix33(float a, float b, float c, float d, float e, float f, float g, float h, float i)
    { xAxis.Set(a, b, c); yAxis.Set(d, e, f); zAxis.Set(g, h, i); }
};
// ---- items of slice s00453250 end

// ---- items of slice s00e39ab0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IntRbNode {
    IntRbNode* mpLeft;         // +0x00
    IntRbNode* mpRight;        // +0x04
    IntRbNode* mpParent;       // +0x08
    uint32_t   mColor;         // +0x0c
    int32_t    mKey;           // +0x10
};
struct IntRbTree {
    uint32_t  mnSize;          // +0x00
    IntRbNode mAnchor;         // +0x04
    void find(IntRbNode** ppResult, const int32_t* pKey);
};
// ---- items of slice s00e39ab0 end

// ---- items of slice s00e4aa60 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl operator_new(uint32_t size, const char* tag, int a, int b, const char* file, int line); // 0x00f473a0
extern "C" void __cdecl operator_delete_array(void* p);                                                          // 0x00f47380
extern char szNameSimulator[];   // 0x013f09b4 "Simulator"
extern char szCatalogTxt[];      // 0x015a5c20 catalog file name
extern char szCellGame[];        // 0x015a5c1c
extern char szDataDir[];         // data dir name used by the .cel scan
extern wchar_t gEmptyString16[]; // 0x01667bac
extern void* GetManager();       // 0x0067dcd0  EA::ResourceMan::GetManager
extern void* GetDataDir(void*);  // 0x00688cb0  SP::GetDataDir
uint32_t FNV1_String16(const wchar_t* pText, uint32_t hash, uint32_t flags); // 0x00932f30
int ParseEnum(const char* pText, int* pOut);                                 // 0x00840bb0
void* Matrix3FromEulerXYZ(void* pOut, const void* pEuler);                   // 0x005f4e80
int FUN_00e4a8a0(int type);                                                  // 0x00e4a8a0
bool FUN_00e4a910(int type);                                                 // 0x00e4a910
bool FUN_00e4a960(int type);                                                 // 0x00e4a960
int FUN_00e82420(int handle, int flags);                                     // 0x00e82420
void FUN_006acfe0(void* pKey, void* pRes);                                   // 0x006acfe0
void FUN_006ad050(void* pRes);                                               // 0x006ad050
void* RBTreeIncrement(void* pNode);                                          // 0x00921580
void FilePathCtor(void* pFilePath, const wchar_t* pPath);                    // 0x00930f60
const wchar_t* FilePathGetExtension(void* pFilePath);                        // 0x00930c10
int64_t FUN_00932130(const wchar_t* pPath, int type);                        // 0x00932130
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
struct cArgScript {
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
Vec3 gVec3Result;    // 0x016ad0a8
Vec2 gVec2Result;    // 0x016ad0a0
Mat3 gMat3Result;    // 0x016ad0b4
struct IRecStream {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void v20();
    virtual int32_t v24(int32_t flags);                        // +0x24
virtual void v28();
virtual void v2c();
virtual void v30();
virtual void v34();
    virtual void v38(uint32_t value, int32_t size);            // +0x38
};
struct cFieldWalker {
    void OffsetInstances(void* pArg1, char* pBase, cTypeDef* pType);                          // 0x00e4ace0
    void AdjustPointers(void* pDelta, char* pBase, cTypeDef* pType);                          // 0x00e4add0
    void ReadRecords(IRecStream* pStream, char* pBase, cTypeDef* pType);                      // 0x00e4ae80
};
struct ISimulatorObject {
virtual void v00();
virtual void v04();
    virtual void v08(int flags);    // +0x08
};
struct IIdentifiable {
virtual void v00();
virtual void v04();
virtual void v08();
    virtual void* GetObject(uint32_t id);   // +0x0c
virtual void v10();
virtual void v14();
virtual void v18();
    virtual void v1c();                     // +0x1c
};
struct IEditorObject {
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
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
virtual void v00();
virtual void v04();
virtual void v08();
virtual void v0c();
virtual void v10();
virtual void v14();
virtual void v18();
virtual void v1c();
    virtual void v20(void* pRes, uint32_t a, uint32_t b, void* pContext, uint32_t c);  // +0x20
};
struct cResourceWriteLock {
    void* mResource[32];      // +0x00
    int32_t mNumResources;    // +0x80
    void Release();           // 0x00e4b170
};
struct sFileInfoData {
    wchar_t mName[0x100];     // +0x000
    wchar_t mType[0x100];     // +0x200
    wchar_t mExt[0x100];      // +0x400
    uint32_t mTime;           // +0x600
};
struct FilePath {
    char pad[0x180];
};
struct cResManager {
    char pad[0x240];
    cResManager* Construct();                                    // 0x0092f960
    bool Init();                                                 // 0x008de220
    void SetCallback(void (*pFn)(const wchar_t*, uint32_t, uint32_t, uint32_t, uint32_t), void* pArg); // 0x0092f5d0
    void SetFlags(int32_t flags);                                // 0x0092fa90
    void SetArg(void* pArg);                                     // 0x0092fa50
    void Finish();                                               // 0x0092faf0
};
struct IReleaseManager {
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
    virtual void ReleaseHandle(uint32_t a, IIdentifiable* pResource, int32_t priority);  // +0x50
};
struct ISearchObject {
    virtual void Destroy(int32_t mode);   // +0x00
    virtual void v04();
    void Shutdown();                      // 0x0092f5f0
    void Cleanup();                       // 0x0092f9e0
};
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
// ---- items of slice s00e4aa60 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
void SP_sFileChange(const wchar_t* pPath, uint32_t p2, uint32_t p3, uint32_t p4, uint32_t p5);  // 0x00e4b5f0 (stays in the slice: not this object's)

// ---- items of slice s00e4ba40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern char g_allocName[];   // 0x013ebb38  allocation category string
extern char g_allocSim[];    // 0x013f09b4  "Simulator"
extern char g_allocEASTL[];  // 0x013f2150  ".../EASTL/allocator.h"
extern char g_emptyStr[];    // 0x01667bac  ?gEmptyString16@eastl@@3PA_WA  (shared empty)
extern char g_emptyStr1[];   // 0x01667bad  &g_emptyStr + 1
extern char g_fmtPctS[];     // 0x013fc850
extern void** g_appDataBegin;   // 0x016ad100
extern void** g_appDataEnd;     // 0x016ad104
extern void** g_appDataCap;     // 0x016ad108
extern char g_zero2[];    // 0x016ad068
extern char g_zero9[];    // 0x016ad174
extern char g_def3v[];    // 0x016ad070  default 3-vector
typedef unsigned int   uint;
typedef unsigned char  u8;
typedef unsigned short u16;
void* EAAllocate(uint size, const char* cat, int a, int b, const char* file, int line); // 0x00f473a0
void  memcpy_(void* d, const void* s, uint n);   // 0x011e0744
void  memset_(void* d, int v, uint n);           // 0x011e073e
uint  FNVHash(const void* s, uint seed, int mode); // 0x00932e80
void  DoInsertCell(void* at, void* v);           // 0x00a80dd0  SimpleVector<CellData*>::DoInsertValue
void* NewMapNode(void* map, void* pos, int key); // 0x00b1c3e0  map<int,string>::node alloc/insert
int   atoi_(const char* s);                      // 0x011e0e4e
char* strchr_(const char* s, int c);             // 0x011e0f2c
void  FUN_00e82280(void);                        // 0x00e82280
void  FUN_00e82490(void);                        // 0x00e82490
void* ZoneObjectNew(int size, const char* name, int a, int b, int c, int d); // 0x00926020
void  FUN_00e4b390(void* h);                     // 0x00e4b390  SP::sFileInfo
void* FUN_00b1c220(void);                        // 0x00b1c220  map<string,int>::operator[]
void  FUN_00e4a8a0(void);                        // 0x00e4a8a0
void* FUN_009289f0(uint a, uint b, uint c, uint d, uint e, uint f); // 0x009289f0  cSPMemPool::LockedAlloc
struct EaString {
    char* mpBegin_00;    // +0x00
    char* mpEnd_04;      // +0x04
    char* mpCap_08;      // +0x08
    void  sprintf_(const char* fmt, ...);       // 0x00472fe0
    void  assign(const void* first, const void* last); // 0x00454cb0
    void  SetEmpty(void) { mpBegin_00 = g_emptyStr; mpEnd_04 = g_emptyStr; mpCap_08 = g_emptyStr1; }
    // free the owned buffer when it is not the shared empty sentinel
    void  FreeIfOwned(void) {
        if (mpCap_08 - mpBegin_00 > 1 && mpBegin_00 != 0)
            operator_delete_array(mpBegin_00);
    }
};
struct EaStringW {                     // eastl::basic_string<wchar_t>
    u16* mpBegin_00;
    u16* mpEnd_04;
    u16* mpCap_08;
    void  sprintf_w(const u16* fmt, ...);       // 0x0041e050  WStr_Format
    void  FreeIfOwned(void) {
        if (mpEnd_04 - mpBegin_00 > 2 && mpBegin_00 != 0)
            operator_delete_array(mpBegin_00);
    }
};
struct MapBase {                        // rbtree map initialised at +4
    uint mData_00[7];               // +0x00 .. +0x1b
    void  init(uint a, uint b);         // 0x00b72080
    void* find(uint key);               // 0x00b721d0
};
struct MapStrInt {                      // eastl::map<eastl::string,int>
    void*    mpvptr_00;                 // +0x00
    void*    mAnchorL_04;               // +0x04
    void*    mAnchorR_08;               // +0x08
    void*    mRoot_0c;                  // +0x0c  anchor.parent
    u8       mColor_10;                 // +0x10
    u8       mPad_11[3];                // +0x11
    int      mnSize_14;                 // +0x14
    uint     mPad_18;                   // +0x18
    int*  at(const EaString* key);          // 0x00b1c220  operator[]
    void* find(void** out, const void* key); // 0x00b20930  ?Find@MapStrFind
    void  NukeSubtree(void* root);          // 0x00e84940  DoNukeSubtree
};
struct SimpleVec {                      // SimpleVector<void*> (begin/end/capacity)
    void** mpBegin_00;                  // +0x00
    void** mpEnd_04;                    // +0x04
    void** mpCap_08;                    // +0x08
    void   clear(void);                 // 0x00743b50  ?VecClear@cModelWorld
};
struct cSPAppDataGlobals_s00e4_ba40 {
    void*      mpResource_00;           // +0x00
    MapBase    mMap_04;                 // +0x04
    void*      mpParser_20;             // +0x20
    void*      mpArg_24;                // +0x24
    MapStrInt  mFieldMap_28;            // +0x28
    uint   mPad_44;                 // +0x44
    SimpleVec  mPoolList_48;            // +0x48
    uint   mTail_54;
};
extern cSPAppDataGlobals_s00e4_ba40* gspAppDataGlobals_s00e4_ba40;   // 0x016ad060
struct TypeDesc;
struct FieldRec {                       // 0x28-byte field descriptor inside a TypeDesc
    uint mHash_00;                  // +0x00
    uint mNameHash_04;              // +0x04
    int      mOffset_08;                // +0x08  sentinel -1 terminates the list
    uint mFlags_0c;                 // +0x0c
    uint mPad_10[2];                // +0x10
    uint mPad_18[4];                // +0x18
};
struct TypeDesc {
    uint  mId_00;                   // +0x00
    FieldRec* mpFields_04;              // +0x04
    uint  mPad_08[2];               // +0x08
};
struct Ctx {
    uint  mPad_00[4];               // +0x00
    TypeDesc* mpType_10;                // +0x10
    uint  mPad_14[9];               // +0x14
};
struct CtxVec {
    void** mpBegin_00;
    void** mpEnd_04;
    void** mpCap_08;
    void   DoInsertValue(void** pEnd, void* const& v);  // 0x00a80dd0  SimpleVector::DoInsertValue
};
struct cResourceWriteLock_s00e4_ba40 {
    void* mpHandle_00;                  // +0x00
    void  Release(void);                // 0x00e4b170
};
struct cMyMagicCommand_s00e4_ba40 {
    void*  mpVptr_00;                   // +0x00
    void** mpVecBegin_04;               // +0x04
    void** mpVecEnd_08;                 // +0x08
    void** mpVecCap_0c;                 // +0x0c
    uint mPad_10[3];                // +0x10 .. +0x1b
    cResourceWriteLock_s00e4_ba40 mLock_1c;        // +0x1c
    uint mPad_20[31];               // +0x20 .. +0x9b
    uint mFlag_9c;                  // +0x9c
    cMyMagicCommand_s00e4_ba40* Command(void* field);   // 0x00e4ba40
    void* Destroy(uint flags);               // 0x00e4bad0  scalar deleting dtor
    void  Execute(void* args);               // 0x00e4c730
};
struct FileStream_s00e4_ba40 {
    char  mData_00[0x154];
    void  ctor(const char* a);          // 0x00931da0
    void  SetPath16(const u16* p);      // 0x00931810
    char  Open(uint a, uint b, uint c, uint d); // 0x009318f0
    void  AddRef(void);                 // 0x009317b0
    void  Close(void);                  // 0x00931a70
    void  dtor(void);                   // 0x00931e70
};
struct StreamBuffer {
    char mData_00[0x140];
    void ctor(void* owner, uint a, uint b);  // 0x0093b530
    void dtor(void);                         // 0x0093b5a0
};
uint ReadLine(void* sb, char* buf, uint n);  // 0x0093a8b0
void* FindFirst(const void* dir, const u16* pat, uint a, uint b);  // 0x0092e730
void* FindNext(void* h, uint a);                                   // 0x0092e8e0
void  FindFinish(void* h);                                         // 0x0092e9b0
int   wcscmp_(const u16* a, const u16* b);
struct FieldDefArg {
    uint  mPad_00[3];
    uint  mFieldOff_0c;       // +0x0c  element size / field offset
    uint  mType_10;           // +0x10  data type id
};
struct FieldDefFull {
    uint mPad_00[3];
    uint mPad_0c;
    uint mType_10;
    uint mPad_14;
    uint mPad_18;
    uint mPad_1c;
    uint mFlags_20;
};
uint MainArguments(void* args, int* count, int a, int b);       // 0x00838020
uint OptionArguments(void* args, const char* name, int* count, int a, int b); // 0x00838130
void* sStringToData(void* s, void* fd);                         // 0x00e4aad0
void* sAssetCreate(void* a, void* b, void* c);      // 0x00e4b730
void* CreateParser(void);                          // 0x008408d0
void* MessageServer(void);                         // 0x0067dcc0
// ---- items of slice s00e4ba40 end

// @ 0x00453920
namespace rw { namespace math { namespace fpu {
Matrix33 Matrix33FromEulerXYZ(const Vector3& e)
{
    // Local names chosen for the /Od slot order (od_names fit 14; y/z still swap, see nonmatching.txt); roles in the comments.
    float v8 = e.x;                       // x
    float t2 = sinf(v8), elem = cosf(v8);   // sx, cx
    float n6 = e.y;                       // y
    float s = sinf(n6), mid = cosf(n6);   // sy, cy
    float t33 = e.z;                       // z
    float n5 = sinf(t33), p1 = cosf(t33);   // sz, cz
    float n17 = elem * p1;              // cx*cz
    float p9 = elem * n5;              // cx*sz
    float owner = t2 * p1;              // sx*cz
    float t23 = t2 * n5;              // sx*sz
    float p40[9];                          // the nine elements
    p40[0] = mid * p1; p40[1] = mid * n5; p40[2] = -s;
    p40[3] = s * owner - p9; p40[4] = s * t23 + n17; p40[5] = mid * t2;
    p40[6] = s * n17 + t23; p40[7] = s * p9 - owner; p40[8] = mid * elem;
    return Matrix33(p40[0], p40[1], p40[2], p40[3], p40[4], p40[5], p40[6], p40[7], p40[8]);
}
}}}  // namespace rw::math::fpu

// @ 0x00e39fb0
void IntRbTree::find(IntRbNode** ppResult, const int32_t* pKey)
{
    IntRbNode* pNode = mAnchor.mpParent;
    IntRbNode* pEnd = &mAnchor;
    IntRbNode* pResult = pEnd;
    while (pNode) {
        if (pNode->mKey < *pKey) {
            pNode = pNode->mpLeft;
        } else {
            pResult = pNode;
            pNode = pNode->mpRight;
        }
    }
    if (pResult != pEnd && !(*pKey < pResult->mKey)) {
        *ppResult = pResult;
        return;
    }
    *ppResult = pEnd;
}

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

// @ 0x00e4ba40
cMyMagicCommand_s00e4_ba40* cMyMagicCommand_s00e4_ba40::Command(void* field)
{
    Ctx* top = (Ctx*)this->mpVecEnd_08[-1];
    FieldRec* rec = top->mpType_10->mpFields_04;
    uint hash = FNVHash(field, 0x811c9dc5, 1);
    FieldRec* found = 0;
    if (rec->mOffset_08 != -1) {
        for (;;) {
            if (rec->mNameHash_04 == hash) { found = rec; break; }
            rec = (FieldRec*)((char*)rec + 0x28);
            if (rec->mOffset_08 == -1) { found = 0; break; }
        }
    }
    if (found == 0) return 0;
    CtxVec* v = (CtxVec*)((char*)this + 4);
    if (v->mpEnd_04 < v->mpCap_08) {
        void** e = v->mpEnd_04;
        v->mpEnd_04 = e + 1;
        if (e) *e = found;
    } else {
        v->DoInsertValue(v->mpEnd_04, found);
    }
    return this;
}

// @ 0x00e4bad0
void* cMyMagicCommand_s00e4_ba40::Destroy(uint flags)
{
    this->mpVptr_00 = (void*)0x148256c;
    this->mLock_1c.Release();
    void* buf = this->mpVecBegin_04;
    if (buf != 0 && *(int*)((char*)buf - 4) != 0)
        operator_delete_array(buf);
    if (flags & 1)
        operator_delete_array(this);
    return this;
}

// @ 0x00e4bb10
void FUN_00e4bb10(void)
{
    void** begin = g_appDataBegin;
    void** end = g_appDataEnd;
    if (begin != end) {
        do {
            void* obj = *begin;
            void** b = *(void***)((char*)obj + 4);
            while (b != *(void***)((char*)obj + 8)) {
                operator_delete_array(*b);
                ++b;
            }
            *(uint*)((char*)obj + 0x9c) = 0;
            (*(void(__thiscall**)(void*, int))(*(int*)obj + 0x20))(obj, 1);
            ++begin;
            end = g_appDataEnd;
        } while (begin != end);
        begin = g_appDataBegin;
    }
    memcpy_(begin, end, 0);
    int n = (int)(end - begin);
    g_appDataEnd = end - n;
}

// @ 0x00e4bc70
void FUN_00e4bc70(void)
{
    cSPAppDataGlobals_s00e4_ba40* g = gspAppDataGlobals_s00e4_ba40;
    MapStrInt* map = &g->mFieldMap_28;
    map->NukeSubtree(map->mRoot_0c);
    map->mAnchorR_08 = &map->mAnchorL_04;
    map->mAnchorL_04 = &map->mAnchorL_04;
    map->mRoot_0c    = 0;
    map->mColor_10   = 0;
    map->mnSize_14   = 0;
}

// @ 0x00e4bca0
void FUN_00e4bca0(void* param_1, void* param_2)
{
    cMyMagicCommand_s00e4_ba40* cmd = (cMyMagicCommand_s00e4_ba40*)EAAllocate(0xa0, g_allocSim, 0, 0, 0, 0);
    if (cmd != 0) {
        cmd->mpVptr_00     = (void*)0x148256c;
        cmd->mpVecBegin_04 = 0;
        cmd->mpVecEnd_08   = 0;
        cmd->mpVecCap_0c   = 0;
        cmd->mFlag_9c      = 0;
    } else {
        cmd = 0;
    }
    void* item = EAAllocate(0x28, g_allocSim, 0, 0, 0, 0);
    *(void**)((char*)item + 0x10) = param_2;
    *(uint*)((char*)item + 0x14) = 0;
    *(uint*)((char*)item + 0x08) = 0;
    void** end = cmd->mpVecEnd_08;
    if (end < cmd->mpVecCap_0c) {
        cmd->mpVecEnd_08 = end + 1;
        if (end) *end = item;
    } else {
        DoInsertCell(&cmd->mpVecEnd_08, &item);
    }
    (*(void(__thiscall**)(void*, void*, void*))(*(int*)param_1 + 0x14))(param_1, *(void**)param_2, cmd);
    if (g_appDataEnd < g_appDataCap) {
        void** slot = g_appDataEnd;
        g_appDataEnd = slot + 1;
        if (slot) *slot = cmd;
    } else {
        DoInsertCell(&g_appDataEnd, &cmd);
        g_appDataEnd = g_appDataEnd;
    }
}

// @ 0x00e4bd70
void FUN_00e4bd70(void)
{
    void* p = *(void**)0x16ad064;
    while (p != 0) {
        void** list = *(void***)0x16ad060;
        FUN_00e4bca0(list[8], p);
        p = *(void**)((char*)p + 0x28);
    }
}

// @ 0x00e4bda0
int* MapStrInt::at(const EaString* key)
{
    void** head = &this->mAnchorL_04;
    void** pos  = head;
    void** root = this->mRoot_0c ? (void**)this->mRoot_0c : 0;
    (void)root;
    u8* node = (u8*)this->mRoot_0c;
    int k = *(int*)key;
    while (node) {
        if (*(int*)(node + 0x10) < k) {
            node = *(u8**)node;
        } else {
            pos = (void**)node;
            node = *(u8**)(node + 4);
        }
    }
    if (pos == head || k < *(int*)((char*)pos + 0x10)) {
        EaString tmp;
        tmp.SetEmpty();
        void* v = FUN_00b1c220();
        (void)v;
        u8* n = (u8*)NewMapNode(this, pos, k);
        pos = (void**)n;
    }
    return (int*)((char*)pos + 0x14);
}

// @ 0x00e4be50
void* FUN_00e4be50(const char* s)
{
    if (s == 0) return 0;
    uint hash = FNVHash(s, 0x811c9dc5, 1);
    const char* p = s;
    const char* q = s + 1;
    do { char c = *p; ++p; } while (*(p - 1) != 0);
    uint len = (uint)(p - q);
    char* dst;
    if (len + 1 > 1) {
        dst = (char*)EAAllocate(len + 1, g_allocEASTL, 0, 0, g_allocName, 0xd1);
    } else {
        dst = g_emptyStr;
    }
    memcpy_(dst, s, len);
    char* endp = dst + len;
    *endp = 0;
    EaString key;
    key.mpBegin_00 = dst;
    key.mpEnd_04 = endp;
    key.mpCap_08 = 0;
    int* slot = gspAppDataGlobals_s00e4_ba40->mFieldMap_28.at(&key);
    (void)hash;
    if (slot != (int*)((char*)&g_emptyStr)) {
        // assign the key into the map node's string
        ((EaString*)((char*)slot))->assign(dst, endp);
    }
    if (len + 1 > 1 && dst != 0) operator_delete_array(dst);
    return (void*)hash;
}

// @ 0x00e4bf30
const char* DebugNameFromSPID(int spid)
{
    if (spid == 0) {
        memcpy_((void*)0x16acf60, "<null key>", 0xc);
    }
    void* out;
    void* found = gspAppDataGlobals_s00e4_ba40->mFieldMap_28.find(&out, &spid);
    if (*(void**)found == (void*)((char*)gspAppDataGlobals_s00e4_ba40 + 0x2c)) {
        memcpy_((void*)0x16acf60, "<unknown key>", 0xe);
        return (const char*)0x16acf60;
    }
    EaString* v = (EaString*)gspAppDataGlobals_s00e4_ba40->mFieldMap_28.at((const EaString*)&spid);
    char* src = v->mpBegin_00;
    char* dst = (char*)0x16acf60;
    char c;
    do { c = *src; *dst++ = c; ++src; } while (c != 0);
    return (const char*)0x16acf60;
}

// @ 0x00e4bff0
void FUN_00e4bff0(const char* key, int value)
{
    struct { EaString s; uint pad_0c; } frame;
    EaString& s = frame.s;
    s.SetEmpty();
    s.sprintf_(g_fmtPctS, key);
    int* slot = gspAppDataGlobals_s00e4_ba40->mFieldMap_28.at(&s);
    *slot = value;
    s.FreeIfOwned();
}

// @ 0x00e4c060
char SP_sAppDataCompile(void* layout, void* arg)
{
    cSPAppDataGlobals_s00e4_ba40* g = gspAppDataGlobals_s00e4_ba40;
    void* parser = g->mpParser_20;
    (*(void(__thiscall**)(void*, int))(*(int*)parser + 0x10))(parser, 0);
    EaString s;
    s.SetEmpty();
    s.sprintf_("%S%S", (char*)layout + 0x200, (void*)0);
    g->mpArg_24 = arg;
    char ok = (*(char(__thiscall**)(void*, const char*))(*(int*)parser + 0x48))(parser, g_emptyStr);
    g->mpArg_24 = 0;
    if (!ok) {
        s.FreeIfOwned();
        return 0;
    }
    FUN_00e4bff0((char*)layout + 0x200, *(int*)((char*)layout + 0x600));
    s.FreeIfOwned();
    return 1;
}

// @ 0x00e4c130
void SP_sReadAppDataResource(const char* dir, int threshold)
{
    EaStringW path;
    path.mpBegin_00 = (u16*)g_emptyStr;
    path.mpEnd_04   = (u16*)g_emptyStr;
    path.mpCap_08   = (u16*)0x1667bae;
    path.sprintf_w((const u16*)L"%s%s", dir, *(void**)0x15a5c20);

    FileStream_s00e4_ba40 fs;
    fs.ctor(0);
    fs.SetPath16(path.mpBegin_00);
    fs.Open(1, 4, 1, 0);
    fs.AddRef();
    StreamBuffer sb;
    sb.ctor(&fs, 0x2000, 0);
    char line[0x100];
    uint n = ReadLine(&sb, line, 0x100);
    if (n < 0xfffffffe && atoi_(line) < threshold) {
        fs.Close();
        sb.dtor();
        fs.dtor();
    } else {
        n = ReadLine(&sb, line, 0x100);
        while (n < 0xfffffffe) {
            EaString fld;
            fld.SetEmpty();
            char* sp = strchr_(line, 0x20);
            if (sp) {
                fld.assign(line, sp);
                int v = atoi_(sp);
                int* slot = gspAppDataGlobals_s00e4_ba40->mFieldMap_28.at(&fld);
                *slot = v;
            }
            fld.FreeIfOwned();
            n = ReadLine(&sb, line, 0x100);
        }
        fs.Close();
        sb.dtor();
        fs.dtor();
    }
    path.FreeIfOwned();
}

// @ 0x00e4c330
char FUN_00e4c330(void* obj)
{
    FUN_00e82280();
    void* node = gspAppDataGlobals_s00e4_ba40->mMap_04.find(*(uint*)((char*)obj + 0x60c));
    if (node) {
        SP_sAppDataCompile((char*)obj + 8, *(void**)((char*)node + 0xc));
    }
    return 1;
}

// @ 0x00e4c370
char SP_sIsUpToDate(void* obj)
{
    EaString key;
    key.SetEmpty();
    key.sprintf_(g_fmtPctS, (char*)obj + 0x200);
    void* out;
    void* node = gspAppDataGlobals_s00e4_ba40->mFieldMap_28.find(&out, &key);
    uint stamp;
    if (*(void**)node == (void*)((char*)gspAppDataGlobals_s00e4_ba40 + 0x2c)) {
        key.FreeIfOwned();
        return 0;
    }
    int* v = gspAppDataGlobals_s00e4_ba40->mFieldMap_28.at(&key);
    stamp = (uint)*v;
    if (*(uint*)((char*)obj + 0x600) > stamp) {
        key.FreeIfOwned();
        return 1;
    }
    key.FreeIfOwned();
    return 0;
}

// @ 0x00e4c440
void SP_sCellResourceCompileAll(const char* dir, void* arg)
{
    void* h = FindFirst(dir, (const u16*)L"*.cel", 0, 0);
    if (h == 0) return;
    char more = 1;
    while (more) {
        if (*(u8*)((char*)h + 0x208) == 0) {
            u16 ext[0x102];
            FUN_00e4b390(h);
            if (wcscmp_((const u16*)((char*)h + 0x20a), (const u16*)L".cel") == 0) {
                if (!SP_sIsUpToDate(h)) {
                    SP_sAppDataCompile((char*)h + 8, arg);
                }
            }
        }
        more = FindNext(h, 0) != 0;
    }
    FindFinish(h);
}

// @ 0x00e4c520
void SP_sAppendData(void* objBase, void* value, FieldDefArg* fd)
{
    char* dst = (char*)objBase + fd->mFieldOff_0c;
    switch (fd->mType_10) {
    case 0: case 4:
        return;
    case 1:
        *(void**)dst = value; return;
    case 2:
        *(void**)dst = value; return;
    case 5:
        *(uint*)dst = (uint)value; return;
    case 6:
        *(u8*)dst = value != 0; return;
    case 3:
        if (value == 0) { *(uint*)dst = 0; return; }
        *(void**)dst = FUN_00e4be50((const char*)value); return;
    case 7:
        *(void**)dst = FUN_00e4be50((const char*)value); return;
    case 8:
        if (value != 0) { ((uint*)dst)[0] = ((uint*)value)[0]; ((uint*)dst)[1] = ((uint*)value)[1]; ((uint*)dst)[2] = ((uint*)value)[2]; return; }
        memcpy_(dst, g_def3v, 12); return;
    case 9:
        memcpy_(dst, value ? value : g_zero9, 0x24); return;
    case 10:
        if (value != 0) { FUN_00e4a8a0(); return; }
        *(u16*)dst = 0; return;
    case 11:
        if (value != 0) { ((uint*)dst)[0] = ((uint*)value)[0]; ((uint*)dst)[1] = ((uint*)value)[1]; return; }
        memcpy_(dst, g_zero2, 8); return;
    default:
        if (value == 0) { memset_(dst, 0, fd->mFieldOff_0c); return; }
        memcpy_(dst, value, fd->mFieldOff_0c); return;
    }
}

// @ 0x00e4c670
void SP_sParseField(FieldDefFull* fd, void* args, void* out)
{
    uint flags = fd->mFlags_20;
    void* value = (void*)*(uint*)((char*)fd + 0x1c);
    if ((flags & 8) == 0 && args != 0) {
        int count = -1;
        uint ok;
        if ((flags & 2) != 0 && (flags & 4) == 0) {
            if (*(uint*)((char*)fd + 0x10) == 6) {
                ok = OptionArguments(args, (const char*)*(uint*)fd, &count, 0, 1);
                if (ok == 0) goto append;
                if (count != 0) {
                    if ((int)count > *(int*)((char*)fd + 0x18))
                        value = sStringToData((void*)*(uint*)(ok + *(int*)((char*)fd + 0x18) * 4), fd);
                } else {
                    SP_sAppendData(out, (void*)1, (FieldDefArg*)fd);
                    return;
                }
            } else {
                ok = OptionArguments(args, (const char*)*(uint*)fd, &count, 0, 0x7fffffff);
                if (ok != 0 && count > *(int*)((char*)fd + 0x18))
                    value = sStringToData((void*)*(uint*)(ok + *(int*)((char*)fd + 0x18) * 4), fd);
            }
        } else {
            ok = MainArguments(args, &count, 0, 0x7fffffff);
            if (ok != 0 && count > *(int*)((char*)fd + 0x18))
                value = sStringToData((void*)*(uint*)(ok + *(int*)((char*)fd + 0x18) * 4), fd);
        }
    }
append:
    SP_sAppendData(out, value, (FieldDefArg*)fd);
}

// @ 0x00e4c730
void cMyMagicCommand_s00e4_ba40::Execute(void* args)
{
    u8* ctx = (u8*)this->mpVecEnd_08[-1];
    uint type = *(uint*)(ctx + 0x10);
    uint typeId = type;
    if ((int)type < 0xc) {
        SP_sParseField((FieldDefFull*)ctx, args, (void*)*(uint*)((char*)this + 0x18));
        *(uint*)((char*)this + 8) -= 4;
        return;
    }
    if ((*(u8*)(type + 0x10) & 1) != 0) {
        int local;
        MainArguments(args, &local, 1, 0x7fffffff);
        *(void**)((char*)this + 0x18) = sAssetCreate((void*)*(uint*)&local, (void*)type, (char*)this + 0x1c);
    }
    void* dst;
    if (*(uint*)(ctx + 0x14) == 4) {
        FUN_00e4a8a0();
        uint size = 0;
        uint* cnt = (uint*)(*(uint*)(ctx + 0xc) + *(uint*)((char*)this + 0x18));
        uint* base = (uint*)(*(uint*)(ctx + 8) + *(uint*)((char*)this + 0x18));
        if (*cnt == 0) {
            void* p = (void*)FUN_009289f0(size, 0, 0, 0, 0, 0);
            *base = (uint)p;
            cSPAppDataGlobals_s00e4_ba40* g = gspAppDataGlobals_s00e4_ba40;
            void** slot = g->mPoolList_48.mpEnd_04;
            if (slot < g->mPoolList_48.mpCap_08) {
                g->mPoolList_48.mpEnd_04 = slot + 1;
                if (slot) *slot = p;
            } else {
                DoInsertCell(&g->mPoolList_48.mpEnd_04, &p);
            }
            dst = p;
        } else {
            dst = (void*)((char*)*base + *cnt * size);
        }
        memset_(dst, 0, size);
        *cnt += 1;
        type = typeId;
    } else {
        dst = (void*)(*(uint*)(ctx + 8) + *(uint*)((char*)this + 0x18));
    }
    u8* f = (u8*)*(uint*)(type + 4);
    char appended = 0;
    if (*(int*)(f + 8) != -1) {
        uint off = 0;
        do {
            if ((*(uint*)(f + 0x20) & 4) == 0) {
                SP_sParseField((FieldDefFull*)f, args, dst);
            } else {
                if ((*(uint*)(f + 0x20) & 2) != 0)
                    SP_sAppendData(dst, (void*)*(uint*)(f + 0x1c), (FieldDefArg*)f);
                appended = 1;
            }
            off += 0x28;
            f = (u8*)(*(uint*)(type + 4) + off);
        } while (*(int*)(f + 8) != -1);
        if (appended) {
            void* p = gspAppDataGlobals_s00e4_ba40->mpParser_20;
            (*(void(__thiscall**)(void*, void*))(*(int*)p + 0x8c))(p, this);
            return;
        }
    }
    *(uint*)((char*)this + 8) -= 4;
}

// @ 0x00e4c8c0
void FUN_00e4c8c0(void)
{
    cSPAppDataGlobals_s00e4_ba40* g = (cSPAppDataGlobals_s00e4_ba40*)EAAllocate(0x58, g_allocSim, 0, 0, 0, 0);
    if (g != 0) {
        g->mPoolList_48.clear();
        g->mFieldMap_28.mAnchorL_04 = &g->mFieldMap_28.mAnchorL_04;
        g->mFieldMap_28.mAnchorR_08 = &g->mFieldMap_28.mAnchorL_04;
        g->mFieldMap_28.mRoot_0c   = 0;
        g->mFieldMap_28.mColor_10  = 0;
        g->mFieldMap_28.mnSize_14  = 0;
        g->mPad_44 = 0;
        g->mPoolList_48.mpBegin_00 = 0;
        g->mPoolList_48.mpEnd_04   = 0;
        g->mPoolList_48.mpCap_08   = 0;
    } else {
        g = 0;
    }
    gspAppDataGlobals_s00e4_ba40 = g;
    g->mpParser_20 = 0;
    (void)ZoneObjectNew(8, "App", 0, 0, 0, 0);
    void* ps = CreateParser();
    g->mpParser_20 = ps;
    (*(void(__thiscall**)(void*))(*(int*)ps))(ps);
    (*(void(__thiscall**)(void*))(*(int*)ps + 8))(ps);
    (*(void(__thiscall**)(void*, int))(*(int*)ps + 0x10))(ps, 0);
    FUN_00e4bd70();
    void* ms = MessageServer();
    (*(void(__thiscall**)(void*, void*, int, int, int))(*(int*)ms + 0x28))(ms, (void*)FUN_00e4c330, 0, 0x4a4e97f, 0);
    FUN_00e82490();
}
