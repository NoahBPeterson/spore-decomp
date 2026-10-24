// src/game/SPEditors/SPPlayModePhotoBrowser.cpp -- migrated from slice(s) s00633560, s00632780, s00631810, s00630750, s0062f6e0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPPlayModePhotoBrowser.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPPlayModePhotoBrowser.h"
#include "EA/Audio/FactoryBinarySampleData.h"
#include "SP/cJobManager.h"
#include "SP/cSPPlayModeBGInfo.h"
#include "SP/cSPPlayModeBGMgr.h"
#include "SP/cSPPlayModeUI.h"
#include <intrin.h>
#include <string.h>
#include "EA/IO/FileStream.h"
#include "SP/cPlayModePhoto.h"
#include "SP/cJob.h"
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedDecrement, _rotl)

// ---- items of slice s0062f6e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* operator new(size_t, const char*, int, int, int, int);
inline void* operator new(size_t, void* p) { return p; }
struct IRefCount {
    virtual int AddRef();
    virtual int Release();
};
template <class T> struct AutoRef {
    T* mpObject;
    AutoRef() : mpObject(0) {}
    AutoRef(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRef(const AutoRef& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRef() { if (mpObject) mpObject->Release(); }
};
template <class T> struct SPVec {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    SPVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~SPVec();
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    T* erase(T* first, T* last);
    T* insert(T* pos, const T& v);
    void DoInsertValueEnd(T* pos, const T& v);
};
struct cSPPlayModeUI {
    void* FindPlayModeUIWindow(uint32_t id);
    void* FindEditorUIWindow(uint32_t id);
    void SetUIGroupVisible(uint32_t id, bool v);
    void SetEditorUIGroupVisible(uint32_t id, bool v);
    void SetEditorUIEnabled(uint32_t id, bool v);
    void SetEnabled(uint32_t id, bool v);
    void ToggleUIGroup(uint32_t id, bool v);
};
struct cJob {
    int ContinueJob();         // 0x0068f970
    void Cancel(int);          // 0x00692400
    void AddRef();             // 0x0068f950
    void Release();            // 0x00690120
};
struct cPlayModePhoto {
    virtual void d0();
    virtual int AddRef();
    virtual int Release();
    uint32_t pad[0x30 / 4 - 1];
    AutoRef<cJob> writeJob;    // +0x30 (retail layout; PDB has it at the same place)
    AutoRef<cJob> loadJob;     // +0x34
    uint8_t bIsSelected;       // +0x38
    uint8_t bIsLoaded;         // +0x39
};
struct UIImage : IRefCount {
    uint32_t pad[4];
    UIImage(void* raster);                   // 0x008333b0
    int GetWidth();                          // 0x008332a0
    int GetHeight();                         // 0x008332d0
};
struct UIImageView {
    UIImageView(UIImage* img, int w, int h, float u0, float v0, float u1, float v1, int flag); // 0x009579f0
};
void FUN_00957c20(UIImage* img, int v);
struct cSPPlayModePhotoBrowser {
    virtual void v0();
    SPVec<AutoRef<cPlayModePhoto> > mPhotos;   // +0x04
    uint32_t pad0[2];
    uint32_t mCurrentFirstPhotoIndex;          // +0x18
    uint32_t mCurrentSelectedPhotoIndex;       // +0x1c
    uint32_t pad1;
    cSPPlayModeUI* mUI;                        // +0x24
    uint32_t pad2[(0x54 - 0x28) / 4];
    uint32_t mMode;                            // +0x54
    uint32_t pad3[(0xe8c - 0x58) / 4];
    void* mAsyncHandle;                        // +0xe8c

    void EnterMoveMode();
    void EnterDeleteMode();
    void ExitDeleteMode();
    void ExitMoveMode();
    uint8_t IsSendPhotoWinVisible();
    cPlayModePhoto* GetPhotoAt(uint32_t idx, bool relative);
    void SelectAll(bool v);
    static UIImageView* __stdcall GetImageFromRaster(void* raster);
    cPlayModePhoto* FindPhotoByGuid(uint32_t guid);
    void ReleaseAsyncHandle();
    cJob* CancelAllPendingLoadJobs();
    int IsPhotosWriting();
    bool AnyWriteJobActive();
    void UpdatePageButtons(int unused);
};
struct HeaderReader {
    uint32_t pad[5];
    HeaderReader();            // 0x0087cde0
    ~HeaderReader();           // 0x0087d070
    bool Open(void* p);        // 0x0087ce00
    bool Get(int kind, uint32_t* count);   // 0x0087d0b0
    int Item(int idx);         // 0x0087ced0
};
struct PhotoGuid { uint32_t pad[7]; uint32_t guid; };
struct JobHandle { uint32_t pad[2]; uint32_t a; uint32_t b; uint8_t pad2[0x39 - 0x10]; uint8_t flag; };
struct Registry {
    virtual void r0(); virtual void r1(); virtual void r2(); virtual void r3();
    virtual void r4(); virtual void r5(); virtual void r6(); virtual void r7();
    virtual volatile long* Lookup(uint32_t b, uint32_t a, int z);   // +0x20
};
Registry* FUN_0067dd60();
struct JobRef {
    cJob* mpObject;
    JobRef& operator=(const JobRef& rhs);
};
const wchar_t* FindFirstOfW(const wchar_t* b, const wchar_t* e, const wchar_t* s, const wchar_t* se); // 0x00455f50
int CompareW(const wchar_t* b1, const wchar_t* e1, const wchar_t* b2, const wchar_t* e2);           // 0x005e9260
struct wstring16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    uint32_t mpCap;
    uint32_t find_first_of(const wchar_t* p, uint32_t position) const;
    int compare(uint32_t pos, uint32_t n, const wchar_t* p) const;
};
static inline uint32_t CharStrlen(const wchar_t* p)
{
    const wchar_t* pEnd = p;
    while (*pEnd)
        ++pEnd;
    return (uint32_t)(pEnd - p);
}
template <class T> static inline const T& min_alt(const T& a, const T& b) { return (a < b) ? a : b; }
struct LocaleMsgBase {
    virtual ~LocaleMsgBase() {}
};
struct LocaleMsg : LocaleMsgBase {
    uint32_t mSlots[0x2c / 4 - 1 + 1];   // placeholder up to +0x30 (slots are 8 bytes apiece from +8)
    ~LocaleMsg();
};
// ---- items of slice s0062f6e0 end

// ---- items of slice s00630750 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* __cdecl EA_Allocate(unsigned size, const char* name, int a, int b, const char* file, int line);
extern "C" void  __cdecl EA_Free(void*);
extern void* gVt13fe518;    // 0x13fe518
extern void* gVt13fe528;    // 0x13fe528
extern void* gVt13ec458;    // 0x13ec458
extern "C" void __cdecl RBTreeInsert(void* node, void* pos, void* root, char b);
struct WStr {
  short* begin; short* end; short* cap;
  void AllocateSelf(int n);
  void Append(const short* first, const short* last);
};
struct Job { void GetStatus(); };
struct Ent24 { int f0, f4, f8, fc, f10, f14, f18, f1c, f20; };
// ---- items of slice s00630750 end

// ---- items of slice s00631810 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void __cdecl CALLEE_memcpy_11e0744(void* dst, const void* src, unsigned n);
struct PhotoVecGrow {
  void FUN_005c8480(void* pos, void** value);   // thiscall @ 0x5c8480, ecx = vector
};
extern void __fastcall ExitDeleteMode(void*);
extern void __fastcall ExitMoveMode(void*);
typedef void (__thiscall *TF0)(void*);
// ---- items of slice s00631810 end


// ---- items of slice s00632780 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t sEmptyWStr[];   // 0x01667bac, the shared empty string
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedDecrement)
extern "C" void* memcpy(void*, const void*, size_t);
void EASTL_allocator_deallocate(void* p);   // 0x00f47380
struct wstring16_s0063_2780 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAlloc;
    wstring16_s0063_2780() : mpBegin(sEmptyWStr), mpEnd(sEmptyWStr), mpCapacity(sEmptyWStr + 1) {}
    wstring16_s0063_2780(const wstring16_s0063_2780& o);              // 0x0056e2d0
    struct NoInit {};
    wstring16_s0063_2780(NoInit) {}
    ~wstring16_s0063_2780() {
        if (mpCapacity - mpBegin > 1 && mpBegin)
            EASTL_allocator_deallocate(mpBegin);
    }
};
void WStr_Format(wstring16_s0063_2780* out, const wchar_t* fmt, ...);   // 0x0041e050
struct cSPPlayModeUI_s0063_2780 {
    void SetUIGroupVisible(uint32_t id, bool v);  // 0x00635760 (cSPPlayModeUI::SetUIGroupVisible)
    void SetEditorUIGroupVisible(uint32_t id, bool v);  // 0x00635790 (cSPPlayModeUI::SetEditorUIGroupVisible)
    void SetEditorUIEnabled(uint32_t id, bool v);  // 0x00634f20 (cSPPlayModeUI::SetEditorUIEnabled)
};
template <class T> struct AutoRef_s0063_2780 {
    T* mpObject;
    AutoRef_s0063_2780() : mpObject(0) {}
};
struct RefCountVBase {
    virtual void Dtor_();
    virtual int AddRef();
    virtual int Release();
    int mRefCount;
    RefCountVBase() : mRefCount(0) {}
};
struct cPlayModePhoto_s0063_2780 : RefCountVBase {
    uint32_t key8;            // +0x08
    uint32_t keyC;            // +0x0c
    uint32_t raster10;        // +0x10
    uint32_t raster14;        // +0x14
    uint32_t raster18;        // +0x18
    uint32_t photo_guid;      // +0x1c
    wstring16_s0063_2780 mName;          // +0x20
    AutoRef_s0063_2780<cJob> writeJob;   // +0x30
    AutoRef_s0063_2780<cJob> loadJob;    // +0x34
    uint8_t bIsSelected;      // +0x38
    uint8_t bIsLoaded;        // +0x39
    cPlayModePhoto_s0063_2780() : raster10(0), raster14(0), raster18(0) {}
};
extern uint32_t gPhotoTypeKeyInstance;   // 0x01523310
struct SaveArea {
    virtual int s00(); virtual int s01(); virtual int s02(); virtual int s03(); virtual int s04();
    virtual int s05(); virtual int s06(); virtual int s07(); virtual int s08(); virtual int s09();
    virtual const wchar_t* GetPath(wstring16_s0063_2780* name);   // +0x28
    virtual int s0b(); virtual int s0c(); virtual int s0d(); virtual int s0e(); virtual int s0f();
    virtual int s10(); virtual int s11(); virtual int s12(); virtual int s13(); virtual int s14();
    virtual int s15(); virtual int s16(); virtual int s17(); virtual int s18(); virtual int s19();
    virtual void WriteFile(const wchar_t* path, void* data);   // +0x68
};
SaveArea* GetSaveArea(uint32_t id);    // 0x006b1f90
void OperatorPlus(wstring16_s0063_2780* result, const wchar_t* rhs);   // 0x006309e0
struct FileStream : RefCountVBase {
    uint32_t pad[0x22c / 4 - 3];
    FileStream(int flags);   // 0x00931da0
};
struct IFileStream : RefCountVBase {
    virtual void v3(); virtual void v4(); virtual void v5(); virtual void Close();   // +0x18
    virtual void v7(); virtual void v8(); virtual void v9(); virtual void va(); virtual void vb();
    virtual void vc(); virtual void vd(); virtual void ve();
    virtual void SetPath(const wchar_t* p);   // +0x3c
    virtual void v10(); virtual void v11(); virtual void v12();
    virtual bool Open(int a, int b, int c, int d);   // +0x4c
};
struct HeaderInfo { uint32_t pad[4]; uint32_t width; uint32_t height; uint32_t bpp; };
struct HeaderReader_s0063_2780 {
    uint32_t pad[5];
    HeaderReader_s0063_2780();                         // 0x0087cde0
    ~HeaderReader_s0063_2780();                        // 0x0087d070
    bool Open(void* p);                     // 0x0087ce00
    bool Get(int kind, uint32_t* count);    // 0x0087d0b0
    HeaderInfo* Item(int idx);              // 0x0087ced0
    void Free(void* p);                     // 0x0087cef0 (gfree)
    bool Read(HeaderInfo* info, void* dst, uint32_t n);   // 0x0087cf00
};
struct IMessageServer {
    virtual int m00(); virtual int m01(); virtual int m02(); virtual int m03(); virtual int m04();
    virtual int m05(); virtual int m06(); virtual int m07(); virtual int m08(); virtual int m09();
    virtual int m0a();
    virtual void AddListener(void* handler, uint32_t msgId, int priority);   // +0x2c
};
IMessageServer* MessageServer();   // 0x0067dcc0
struct IRegistry {
    virtual int r00(); virtual int r01(); virtual int r02(); virtual int r03(); virtual int r04();
    virtual int r05(); virtual int r06(); virtual int r07();
    virtual volatile long* Lookup(uint32_t b, uint32_t a, int z);   // +0x20
    virtual int r09(); virtual int r0a(); virtual int r0b(); virtual int r0c();
    virtual void Commit(void* res);   // +0x34
    virtual int r0e();
    virtual void* Acquire(void* a, void* b, uint32_t w, uint32_t h, int, int, int, int);   // +0x3c
};
IRegistry* FUN_0067dd60_s0063_2780();
struct IResourceManager {
    virtual int a00(); virtual int a01(); virtual int a02(); virtual int a03(); virtual int a04();
    virtual int a05(); virtual int a06(); virtual int a07(); virtual int a08(); virtual int a09();
    virtual int a0a(); virtual int a0b(); virtual int a0c(); virtual int a0d(); virtual int a0e();
    virtual int a0f(); virtual int a10(); virtual int a11(); virtual int a12(); virtual int a13();
    virtual int a14(); virtual int a15(); virtual int a16(); virtual int a17(); virtual int a18();
    virtual int a19(); virtual int a1a(); virtual int a1b(); virtual int a1c(); virtual int a1d();
    virtual int a1e();
    virtual void GetPathForKey(const void* key, wstring16_s0063_2780* out);   // +0x7c
};
IResourceManager* GetResourceManager();   // 0x008de1a0
struct ResourceKey { uint32_t instance, type, group; };
template <class T> struct PtrVec {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void DoInsertValue(T* pos, const T& v);   // 0x00630b30
    void push_back(const T& v) {
        if (mpEnd < mpCapacity)
            ::new (mpEnd++) T(v);
        else
            DoInsertValue(mpEnd, v);
    }
    T* erase(T* first, T* last) {
        memcpy(first, last, (char*)mpEnd - (char*)last);
        mpEnd -= (last - first);
        return first;
    }
};
struct PhotoTypeInfo {
    uint32_t bits;
    uint32_t key[3];
};
struct RBNode;
struct RBAnchor {
    RBNode* mpNodeRight;
    RBNode* mpNodeLeft;
    RBNode* mpNodeParent;
    uint8_t mColor;
};
struct RBNode : RBAnchor {
    uint32_t key;
    PhotoTypeInfo value;
};
struct PhotoTypePair {              // value_type: key + its info, 20 bytes
    uint32_t key;
    PhotoTypeInfo info;
};
struct InsertUniqueTag {            // the trailing by-value integral_constant<bool,1>
    uint8_t mValue;
};
// A non-POD iterator: a class with a destructor is returned through a hidden pointer (retail
// passes the out slot as the first stack argument for both find and DoInsertKey).
struct PhotoTypeMapIterator {
    RBNode* mpNode;
    PhotoTypeMapIterator() : mpNode(0) {}
    PhotoTypeMapIterator(const PhotoTypeMapIterator& o) : mpNode(o.mpNode) {}
    ~PhotoTypeMapIterator() {}
};

struct PhotoTypeMap {
    uint32_t mCompare;
    RBAnchor mAnchor;
    uint32_t mnSize;
    void DoNuke(RBNode* n);                                   // 0x009a9600
    PhotoTypeMapIterator find(const uint32_t& key);
    PhotoTypeInfo& operator[](const uint32_t& key);
    PhotoTypeMapIterator DoInsertKey(RBNode* hint, const PhotoTypePair& value, InsertUniqueTag tag);
    void clear() {
        DoNuke(mAnchor.mpNodeParent);
        mAnchor.mpNodeRight = (RBNode*)&mAnchor;
        mAnchor.mpNodeLeft = (RBNode*)&mAnchor;
        mAnchor.mpNodeParent = 0;
        mAnchor.mColor = 0;
        mnSize = 0;
    }
};
struct PixEntry;
struct PixEntry {
    uint8_t* mpBegin;
    uint8_t* mpEnd;
    uint8_t* mpCapacity;
    uint32_t mAlloc;
    uint8_t* erase(uint8_t* first, uint8_t* last) {
        memcpy(first, last, (char*)mpEnd - (char*)last);
        mpEnd -= (last - first);
        return first;
    }
    uint32_t pad;
    uint32_t width;      // +0x14 (browser +0x98 for entry 0)
    uint32_t height;     // +0x18
    uint32_t bytes;      // +0x1c
    uint32_t extra;      // +0x20
    void resize(uint32_t n);   // 0x004c0410
};
struct PixView {   // an entry viewed at its absolute offset (0x84) from a base that is "this + idx * 0x24"
    uint32_t pad[0x84 / 4];
    PixEntry e;
};
struct cSPPlayModePhotoBrowser_s0063_2780 {
    virtual void v0();
    PtrVec<AutoRef_s0063_2780<cPlayModePhoto_s0063_2780> > mPhotos;     // +0x04
    uint32_t pad0[2];
    uint32_t mCurrentFirstPhotoIndex;             // +0x18
    uint32_t mCurrentSelectedPhotoIndex;          // +0x1c
    uint8_t mbPhotosLoaded;                       // +0x20
    cSPPlayModeUI_s0063_2780* mUI;                           // +0x24
    uint32_t pad1[(0x68 - 0x28) / 4];
    PhotoTypeMap mPhotoTypeMap;                   // +0x68
    uint32_t pad2;
    PixEntry mPix[99];                            // +0x84
    uint32_t pad2b[2];
    PtrVec<cPlayModePhoto_s0063_2780*> mLoaded;              // +0xe78
    uint32_t pad3[2];
    void* mAsyncHandle;                           // +0xe8c
    AutoRef_s0063_2780<IRefCount> mTooltip[5];               // +0xe90
    uint32_t mPhotoCount;                         // +0xea4
    uint32_t mDeactivateCount;                    // +0xea8

    // from the previous slice
    void SelectAll(bool v);  // 0x00630090 (cSPPlayModePhotoBrowser::SelectAll)
    void ExitDeleteMode();  // 0x006301a0 (cSPPlayModePhotoBrowser::ExitDeleteMode)
    void ExitMoveMode();  // 0x00630280 (cSPPlayModePhotoBrowser::ExitMoveMode)
    cPlayModePhoto_s0063_2780* FindPhotoByGuid(uint32_t guid);  // 0x00630360 (cSPPlayModePhotoBrowser::FindPhotoByGuid)
    void ReleaseAsyncHandle();  // 0x006303a0 (cSPPlayModePhotoBrowser::ReleaseAsyncHandle)
    cJob* CancelAllPendingLoadJobs();  // 0x00630410 (cSPPlayModePhotoBrowser::CancelAllPendingLoadJobs)
    cJob* IsPhotosWriting();  // 0x00630470 (cSPPlayModePhotoBrowser::IsPhotosWriting)
    int GetHeaderInfo(void* stream, int kind);  // 0x0062fee0 (cSPPlayModePhotoBrowser::GetHeaderInfo)

    // this slice
    bool CheckGuidAndType(wstring16_s0063_2780 a, uint32_t u, int kind, wstring16_s0063_2780 b);  // 0x00632780 (cSPPlayModePhotoBrowser::CheckGuidAndType)
    void AddPhoto(uint32_t guid, int kind);  // 0x00632900 (cSPPlayModePhotoBrowser::AddPhoto)
    bool CopyPixelsToRaster(int idx, uint32_t a, uint32_t b);  // 0x006329b0 (cSPPlayModePhotoBrowser::CopyPixelsToRaster)
    void PushLoaded(uint32_t guid);  // 0x00632ab0 (cSPPlayModePhotoBrowser::PushLoaded)
    void ClearLoadedPhotos();  // 0x00632b00 (cSPPlayModePhotoBrowser::ClearLoadedPhotos)
    void DeleteAll();  // 0x00632ba0 (cSPPlayModePhotoBrowser::DeleteAll)
    void MoveAll();  // 0x00632c00 (cSPPlayModePhotoBrowser::MoveAll)
    void DeleteOne();  // 0x00632c60 (cSPPlayModePhotoBrowser::DeleteOne)
    void MoveOne();  // 0x00632ce0 (cSPPlayModePhotoBrowser::MoveOne)
    bool SaveThumbnail(void* data);  // 0x00632d60 (cSPPlayModePhotoBrowser::SaveThumbnail)
    bool ResetPhotoMap();  // 0x00632e40 (cSPPlayModePhotoBrowser::ResetPhotoMap)
    void Shutdown();  // 0x00632f30 (cSPPlayModePhotoBrowser::Shutdown)
    void Deactivate();  // 0x00632fe0 (cSPPlayModePhotoBrowser::Deactivate)
    void SetToLastPage();  // 0x00633080 (cSPPlayModePhotoBrowser::SetToLastPage)
    bool LoadPhotoThumb(uint32_t idx);  // 0x006330b0 (cSPPlayModePhotoBrowser::LoadPhotoThumb)
    bool MarkPhotoTypeForGuid(uint32_t guid, int kind, ResourceKey key);  // 0x00633230 (cSPPlayModePhotoBrowser::MarkPhotoTypeForGuid)
    bool LoadPhotoByKey(const ResourceKey* key);  // 0x006332c0 (cSPPlayModePhotoBrowser::LoadPhotoByKey)
    void CapturePixels(void* stream, int idx, uint32_t arg3);  // 0x00633440 (cSPPlayModePhotoBrowser::CapturePixels)

    // external members
    bool FUN_00631810(HeaderInfo* hdr, uint32_t u, int kind, wstring16_s0063_2780 s);
    void FUN_00631df0(cPlayModePhoto_s0063_2780* p);
    void GetPhotoDir(uint32_t guid, wstring16_s0063_2780* out);                 // 0x00631e50
    bool FUN_006312f0(void* a, void* b, void* c, wstring16_s0063_2780 s);
    uint32_t PhotoCountChanged();                                    // 0x00631b30
};
void FUN_00632660();
void FUN_006326f0();
struct Surface {
    int Lock(int mode, int z, void** out);     // 0x011ef750
    void Unlock(void** out);                    // 0x011ef880
};
struct ImageRes {
    Surface* surface;
    uint32_t flags;
};
    void* operator new(unsigned int, char*, int, int, int, int); // 0x00f473a0
// ---- items of slice s00632780 end

// @ 0x0062fda0
void SP::cSPPlayModePhotoBrowser::EnterMoveMode()
{
    mMode = 1;
    mUI->ToggleUIGroup(0x3a8ede4, true);
    mUI->ToggleUIGroup(0x3eab260, true);
    mUI->ToggleUIGroup(0x3f15ea8, true);
    mUI->ToggleUIGroup(0x3f15ef8, true);
    mUI->ToggleUIGroup(0x3f6c0e8, true);
    mUI->ToggleUIGroup(0x3f6c188, true);
    mUI->ToggleUIGroup(0x3f6c1b4, true);
    mUI->SetUIGroupVisible(0x410cf00, false);
    mUI->SetUIGroupVisible(0x41a30c0, false);
}






// @ 0x0062fe40
void SP::cSPPlayModePhotoBrowser::EnterDeleteMode()
{
    mMode = 2;
    mUI->ToggleUIGroup(0x3a8ede4, true);
    mUI->ToggleUIGroup(0x3eab260, true);
    mUI->ToggleUIGroup(0x3f15ea8, true);
    mUI->ToggleUIGroup(0x3f15ef8, true);
    mUI->ToggleUIGroup(0x3f6c0e8, true);
    mUI->ToggleUIGroup(0x3f6c188, true);
    mUI->ToggleUIGroup(0x3f6c1b4, true);
    mUI->SetUIGroupVisible(0x41a30c0, false);
    mUI->SetUIGroupVisible(0x410cf00, false);
}






// @ 0x0062fee0
int __stdcall GetHeaderInfo(void* data, int kind)
{
    HeaderReader r;
    uint32_t count;
    bool ok = data && r.Open(data);
    switch (kind) {
    case 0x417b3a7:
        if (!ok || !r.Get(4, &count))
            return 0;
        break;
    case 0x417b3bc:
        if (!ok || !r.Get(2, &count))
            return 0;
        break;
    default:
        if (!ok)
            return 0;
    }
    if (count > 0)
        return r.Item(0);
    return 0;
}






// @ 0x00630090
void SP::cSPPlayModePhotoBrowser::SelectAll(bool v)
{
    for (uint32_t i = 0; i < mPhotos.size(); ++i) {
        SP::cPlayModePhoto* p;
        if (i < mPhotos.size())
            p = mPhotos.mpBegin[i].mpObject;
        else
            p = 0;
        p->bIsSelected = v;
    }
}






// @ 0x006300d0
UIImageView* __stdcall cSPPlayModePhotoBrowser::GetImageFromRaster(void* raster)
{
    if (raster) {
        void* mem = operator new(sizeof(UIImage), "UI", 0, 0, 0, 0);
        if (mem) {
            UIImage* img = new (mem) UIImage(raster);
            if (img) {
                img->AddRef();
                FUN_00957c20(img, 1);
                int w = img->GetWidth();
                int h = img->GetHeight();
                void* mem2 = operator new(0x2c, "UI", 0, 0, 0, 0);
                UIImageView* r;
                if (mem2)
                    r = new (mem2) UIImageView(img, w, h, 0.0f, 0.0f, 1.0f, 1.0f, 0);
                else
                    r = 0;
                img->Release();
                return r;
            }
        }
    }
    return 0;
}






// @ 0x006301a0
void SP::cSPPlayModePhotoBrowser::ExitDeleteMode()
{
    mMode = 0;
    if (mPhotos.size() != 0) {
        mUI->SetUIGroupVisible(0x410cf00, true);
        mUI->SetUIGroupVisible(0x41a30c0, true);
        mUI->SetUIGroupVisible(0x4463e78, true);
        mUI->SetEditorUIGroupVisible(0x447c040, true);
        mUI->SetEditorUIGroupVisible(0x447c4e8, true);
        mUI->SetEditorUIEnabled(0x3f67720, true);
    }
    mUI->ToggleUIGroup(0x3a8ede4, false);
    mUI->ToggleUIGroup(0x3eab260, false);
    mUI->ToggleUIGroup(0x3f15ea8, false);
    mUI->ToggleUIGroup(0x3f15ef8, false);
    mUI->ToggleUIGroup(0x3f6c0e8, false);
    mUI->ToggleUIGroup(0x3f6c188, false);
    mUI->ToggleUIGroup(0x3f6c1b4, false);
}






// @ 0x00630280
void SP::cSPPlayModePhotoBrowser::ExitMoveMode()
{
    mMode = 0;
    if (mPhotos.size() != 0) {
        mUI->SetUIGroupVisible(0x41a30c0, true);
        mUI->SetUIGroupVisible(0x410cf00, true);
        mUI->SetUIGroupVisible(0x4463e78, true);
        mUI->SetEditorUIGroupVisible(0x447c040, true);
        mUI->SetEditorUIGroupVisible(0x447c4e8, true);
        mUI->SetEditorUIEnabled(0x3f67720, true);
    }
    mUI->ToggleUIGroup(0x3a8ede4, false);
    mUI->ToggleUIGroup(0x3eab260, false);
    mUI->ToggleUIGroup(0x3f15ea8, false);
    mUI->ToggleUIGroup(0x3f15ef8, false);
    mUI->ToggleUIGroup(0x3f6c0e8, false);
    mUI->ToggleUIGroup(0x3f6c188, false);
    mUI->ToggleUIGroup(0x3f6c1b4, false);
}






// @ 0x00630360
cPlayModePhoto* cSPPlayModePhotoBrowser::FindPhotoByGuid(uint32_t guid)
{
    uint32_t n = mPhotos.size();
    cPlayModePhoto* result = 0;
    uint32_t i = 0;
    if (n > 0) {
        AutoRef<cPlayModePhoto>* b = mPhotos.mpBegin;
        AutoRef<cPlayModePhoto>* p = b;
        for (; i < n; ++i, ++p) {
            if (((PhotoGuid*)p->mpObject)->guid == guid)
                return b[i].mpObject;
        }
    }
    return result;
}






// @ 0x006303a0
void cSPPlayModePhotoBrowser::ReleaseAsyncHandle()
{
    JobHandle* h = (JobHandle*)mAsyncHandle;
    if (h) {
        volatile long* counter = FUN_0067dd60()->Lookup(h->b, h->a, 0) + 2;
        _InterlockedDecrement(counter);
        if (_InterlockedExchangeAdd(counter, 0) < 1)
            _InterlockedExchangeAdd(counter, 1);
        else
            _InterlockedExchangeAdd(counter, 0);
        h->flag = 0;
        mAsyncHandle = 0;
    }
}






// @ 0x00630410
cJob* cSPPlayModePhotoBrowser::CancelAllPendingLoadJobs()
{
    cJob* found = 0;
    for (uint32_t i = 0; i < mPhotos.size(); ++i) {
        cJob* j = mPhotos.mpBegin[i].mpObject->writeJob.mpObject;
        if (j) {
            int r = j->ContinueJob();
            if (r != 4) {
                if (r != 7)
                    j->Cancel(0);
            } else {
                found = j;
            }
        }
    }
    return found;
}






// @ 0x00630470
int cSPPlayModePhotoBrowser::IsPhotosWriting()
{
    for (uint32_t i = 0; i < mPhotos.size(); ++i) {
        cJob* j = mPhotos.mpBegin[i].mpObject->loadJob.mpObject;
        if (j) {
            int r = j->ContinueJob();
            if (r == 4 || r != 7)
                j->Cancel(0);
            AutoRef<cJob>* slot = &mPhotos.mpBegin[i].mpObject->loadJob;
            cJob* old = slot->mpObject;
            if (old) {
                slot->mpObject = 0;
                old->Release();
            }
        }
    }
    return 0;
}






// @ 0x006304e0
bool cSPPlayModePhotoBrowser::AnyWriteJobActive()
{
    bool any = false;
    for (uint32_t i = 0; i < mPhotos.size(); ++i) {
        cJob* j = mPhotos.mpBegin[i].mpObject->writeJob.mpObject;
        if (j) {
            switch (j->ContinueJob()) {
            case 3:
                any = true;
                break;
            case 4:
                any = true;
                break;
            case 7:
                break;
            default:
                j->Cancel(0);
            }
        }
    }
    return any;
}






// @ 0x00630540
JobRef& JobRef::operator=(const JobRef& rhs)
{
    cJob* p = rhs.mpObject;
    cJob* old = mpObject;
    if (p != old) {
        if (p)
            p->AddRef();
        mpObject = p;
        if (old)
            old->Release();
    }
    return *this;
}






// @ 0x00630580
void cSPPlayModePhotoBrowser::UpdatePageButtons(int unused)
{
    if (mUI) {
        uint32_t lastPage = 0;
        if (mPhotos.size() > 0)
            lastPage = (mPhotos.size() - 1) / 5;
        uint32_t page = mCurrentFirstPhotoIndex / 5;
        mUI->SetEnabled(0x3f42804, page > 0);
        mUI->SetEnabled(0x3f42784, page < lastPage);
        mUI->SetEditorUIEnabled(0x447b980, mCurrentSelectedPhotoIndex > 0);
        mUI->SetEditorUIEnabled(0x447b968, mCurrentSelectedPhotoIndex < mPhotos.size() - 1);
    }
}






// @ 0x00630630
uint32_t wstring16::find_first_of(const wchar_t* p, uint32_t position) const
{
    const uint32_t n = CharStrlen(p);
    const wchar_t* const pEnd = mpEnd;
    const wchar_t* const pStart = mpBegin;
    if (position < (uint32_t)(pEnd - pStart)) {
        const wchar_t* const pBegin = FindFirstOfW(pStart + position, pEnd, p, p + n);
        if (pBegin != pEnd)
            return (uint32_t)(pBegin - pStart);
    }
    return (uint32_t)-1;
}






// @ 0x00630690
int wstring16::compare(uint32_t pos, uint32_t n, const wchar_t* p) const
{
    uint32_t len = (uint32_t)(mpEnd - mpBegin) - pos;
    return CompareW(mpBegin + pos, mpBegin + pos + min_alt(len, n), p, p + CharStrlen(p));
}






// @ 0x006306f0
LocaleMsg::~LocaleMsg()
{
    uint32_t mask = 1;
    IRefCount** slot = (IRefCount**)this + 2;
    for (int n = 32; n; --n) {
        if ((((uint32_t*)this)[0x30 / 4] & mask) && *slot)
            (*slot)->Release();
        slot += 2;
        mask = _rotl(mask, 1);
    }
}






// @ 0x00630750
void* __fastcall FUN_00630750(void* self, short* /*unused edx arg*/, short* first, short* last, int /*unused*/)
{
  // Retail ignores the edx argument and reads its [first,last) pair from the
  // two stack parameters ([esp+4] and [esp+8]), popping three stack dwords.
  WStr* s = (WStr*)self;
  s->begin = 0; s->end = 0; s->cap = 0;
  int n = ((char*)last - (char*)first) >> 1;
  s->AllocateSelf(n + 1);
  short* dst = s->begin;
  memcpy(dst, first, n * 2);
  short* e = dst + n;
  s->end = e;
  *e = 0;
  return self;
}





// @ 0x006307a0
void __fastcall FUN_006307a0(void* self, int* out, int* pos, unsigned* val, char flag)
{
  char* s = (char*)self;
  char b;
  if (flag == 0 && pos != (int*)(s + 4) && *val >= *(unsigned*)((char*)pos + 0x10))
    b = 1;
  else
    b = 0;
  char* node = (char*)EA_Allocate(0x24, "Editor", 0, 0,
                                  "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
  if (node + 0x10 != 0) {
    *(unsigned*)(node + 0x10) = val[0];
    *(unsigned*)(node + 0x14) = val[1];
    *(unsigned*)(node + 0x18) = val[2];
    *(unsigned*)(node + 0x1c) = val[3];
    *(unsigned*)(node + 0x20) = val[4];
  }
  RBTreeInsert(node, pos, s + 4, b);
  ++*(int*)(s + 0x14);
  *out = (int)node;
}





// @ 0x006308d0
void* __fastcall FUN_006308d0(void* self, char flag)
{
  char* s = (char*)self;
  *(void**)s = (void*)&gVt13fe518;
  {
    void* p = *(void**)(s + 0x34);
    if (p != 0) ((Job*)p)->GetStatus();
  }
  {
    void* p = *(void**)(s + 0x30);
    if (p != 0) ((Job*)p)->GetStatus();
  }
  {
    void* p = *(void**)(s + 0x20);
    unsigned n = (*(unsigned*)(s + 0x28) - (unsigned)p) & 0xfffffffe;
    if (n > 2 && p != 0) EA_Free(p);
  }
  *(void**)s = (void*)&gVt13ec458;
  if (flag & 1) EA_Free(s);
  return self;
}





// @ 0x00630930
void __fastcall FUN_00630930(void* self)
{ (void)self; }





// @ 0x006309e0
void* __cdecl FUN_006309e0(void* out, const short* lhs, const WStr* rhs)
{
  const short* p = lhs;
  while (*p) ++p;
  int n = (int)(p - lhs);
  int len = (int)(rhs->end - rhs->begin) >> 1;
  WStr* o = (WStr*)out;
  o->begin = 0; o->end = 0; o->cap = 0;
  int total = len + n;
  o->AllocateSelf(total + 1);
  *o->end = 0;
  o->Append(lhs, lhs + n);
  o->Append(rhs->begin, rhs->end);
  return out;
}





// @ 0x00630a50
void __fastcall FUN_00630a50(void* self)
{
  // Build the reusable sub-object pointer first and recover the base from it;
  // this keeps the object base in eax, so the void return still leaves eax =
  // self like the retail function does.
  char* p = (char*)self;
  p += 0x6c;
  char* a = p - 0x6c;
  *(void**)a = (void*)&gVt13fe528;
  *(int*)(a + 4) = 0;
  *(int*)(a + 8) = 0;
  *(int*)(a + 0xc) = 0;
  *(int*)(a + 0x18) = 0;
  *(unsigned char*)(a + 0x20) = 0;
  *(int*)(a + 0x28) = 0;
  *(int*)(a + 0x2c) = 0;
  *(int*)(a + 0x30) = 0;
  *(int*)(a + 0x50) = 0;
  *(int*)(a + 0x54) = 0;
  *(int*)(p + 4) = 0;
  *(int*)(p + 8) = 0;
  *(int*)(p + 0xc) = 0;
  *(void**)p = (void*)p;
  *(int*)(a + 0x70) = (int)p;
  *(int*)(a + 0x74) = 0;
  *(unsigned char*)(a + 0x78) = 0;
  *(int*)(a + 0x7c) = 0;
  p = a + 0x84;
  for (int i = 0x62; i >= 0; --i) {
    *(int*)(p + 0x00) = 0;
    *(int*)(p + 0x04) = 0;
    *(int*)(p + 0x08) = 0;
    *(int*)(p + 0x14) = 0;
    *(int*)(p + 0x18) = 0;
    *(int*)(p + 0x1c) = 0;
    *(int*)(p + 0x20) = 0;
    p += 0x24;
  }
  *(int*)(a + 0xe70) = 0;
  *(int*)(a + 0xe74) = 4;
  *(int*)(a + 0xe78) = 0;
  *(int*)(a + 0xe7c) = 0;
  *(int*)(a + 0xe80) = 0;
  *(int*)(a + 0xe8c) = 0;
  *(int*)(a + 0xe90) = 0;
  *(int*)(a + 0xe94) = 0;
  *(int*)(a + 0xe98) = 0;
  *(int*)(a + 0xe9c) = 0;
  *(int*)(a + 0xea0) = 0;
  *(int*)(a + 0xea8) = 0;
}





// @ 0x00630b30
void __fastcall FUN_00630b30(void* self, int* pos, int* val)
{
  int* v = (int*)self;
  int* end = (int*)v[1];
  if (end != (int*)v[2]) {
    int* src = val;
    if (val >= pos && val < end) src = val + 1;
    if (end != 0) *end = end[-1];
    unsigned n = (unsigned)((char*)(v[1] - 1) - (char*)pos);
    memmove((char*)v[1] - ((int)n >> 2) * 4, pos, n);
    *pos = *src;
    v[1] += 1;
    return;
  }
  int cap = (int)((char*)end - (char*)v[0]) >> 2;
  if (cap == 0) cap = 1; else cap *= 2;
  int* dst;
  if (cap == 0) dst = 0;
  else dst = (int*)EA_Allocate(cap * 4, "Editor", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
  unsigned n1 = (unsigned)((char*)pos - (char*)v[0]);
  int* p = (int*)((char*)dst + ((int)n1 >> 2) * 4);
  if (p != 0) *p = *val;
  int* oldEnd = (int*)v[1];
  memmove(p + 1, pos, (char*)oldEnd - (char*)pos);
  if (v[0] != 0 && *(int*)((char*)v[0] - 4) != 0) EA_Free((void*)v[0]);
  v[0] = (int)dst;
  v[1] = (int)((char*)p + 4 + (((char*)oldEnd - (char*)pos) >> 2) * 4);
  v[2] = (int)((char*)dst + cap * 4);
}





// @ 0x00630d10
void __fastcall FUN_00630d10(void* self)
{ (void)self; }





// @ 0x00630f20
void __fastcall FUN_00630f20(void* self)
{ (void)self; }





// @ 0x006312f0
void __fastcall FUN_006312f0(void* self)
{ (void)self; }





// @ 0x00631810
void __fastcall FUN_00631810(void* self)
{ (void)self; }

// @ 0x00631a10
void __fastcall FUN_00631a10(void* self)
{ (void)self; }

// @ 0x00631b30
void __fastcall FUN_00631b30(void* self)
{ (void)self; }

// @ 0x00631dc0
void __fastcall FUN_00631dc0(void* self)
{
  int* s = (int*)self;
  void* end = (void*)s[1];
  void* beg = (void*)s[0];
  CALLEE_memcpy_11e0744(beg, end, 0);
  s[1] += (int)beg - (int)end;
}

// @ 0x00631df0
// 4-dword vector header; the grow helper at 0x5c8480 receives the +0x4 sub-object in ecx and
// the old end plus the value slot on the stack (ret 8).
struct PhotoVec {
  void* mOwner;   // +0x0
  void* mBegin;   // +0x4
  void* mEnd;     // +0x8
  void* mCap;     // +0xc
};

void __fastcall FUN_00631df0(void* self, void* /*edx_unused*/, void* p)
{
  PhotoVec* v = (PhotoVec*)self;
  void* obj = p;
  if (obj != 0) ((TF0)(*(void**)(*(char**)obj + 4)))(obj);
  if (v->mEnd < v->mCap) {
    unsigned int* end = (unsigned int*)v->mEnd;
    v->mEnd = end + 1;
    if (end != 0) {
      *end = (unsigned int)obj;
      if (obj != 0) ((TF0)(*(void**)(*(char**)obj + 4)))(obj);
    }
  } else {
    ((PhotoVecGrow*)&v->mBegin)->FUN_005c8480(v->mEnd, &obj);
  }
  if (obj != 0) ((TF0)(*(void**)(*(char**)obj + 8)))(obj);
}

// @ 0x00631e50
void __fastcall FUN_00631e50(void* self)
{ (void)self; }

// @ 0x006320d0
__declspec(noinline) void __fastcall FUN_006320d0(void*, int, int)
{}

// @ 0x00632320
void __fastcall FUN_00632320(void* self, int)
{ (void)self; }

// @ 0x00632660
void __fastcall FUN_00632660(void* self)
{
  int* s = (int*)self;
  int n = (s[2] - s[1]) >> 2;
  for (int i = n - 1; i >= 0; --i) {
    void* p;
    if (i < ((s[2] - s[1]) >> 2)) p = *(void**)(s[1] + i * 4);
    else p = 0;
    if (*(unsigned char*)((char*)p + 0x38)) FUN_006320d0(self, i, 1);
  }
  for (unsigned i = 0; i < (unsigned)((s[2] - s[1]) >> 2); ++i) {
    void* p;
    if (i < (unsigned)((s[2] - s[1]) >> 2)) p = *(void**)(s[1] + i * 4);
    else p = 0;
    *(unsigned char*)((char*)p + 0x38) = 0;
  }
  ExitDeleteMode(self);
}

// @ 0x006326f0
void __fastcall FUN_006326f0(void* self)
{
  int* s = (int*)self;
  int n = (s[2] - s[1]) >> 2;
  for (int i = n - 1; i >= 0; --i) {
    void* p;
    if (i < ((s[2] - s[1]) >> 2)) p = *(void**)(s[1] + i * 4);
    else p = 0;
    if (*(unsigned char*)((char*)p + 0x38)) FUN_00632320(self, i);
  }
  for (unsigned i = 0; i < (unsigned)((s[2] - s[1]) >> 2); ++i) {
    void* p;
    if (i < (unsigned)((s[2] - s[1]) >> 2)) p = *(void**)(s[1] + i * 4);
    else p = 0;
    *(unsigned char*)((char*)p + 0x38) = 0;
  }
  ExitMoveMode(self);
}

// @ 0x00632780
bool cSPPlayModePhotoBrowser_s0063_2780::CheckGuidAndType(wstring16_s0063_2780 a, uint32_t u, int kind, wstring16_s0063_2780 b)
{
    wstring16_s0063_2780 path((wstring16_s0063_2780::NoInit()));
    OperatorPlus(&path, GetSaveArea(0x11ac196)->GetPath(&a));
    bool ok = false;
    FileStream* mem = (FileStream*)operator new(0x22c, "Editor", 0, 0, 0, 0);
    if (mem) {
        IFileStream* fs = (IFileStream*)new (mem) FileStream(0);
        if (fs) {
            fs->AddRef();
            fs->SetPath(path.mpBegin);
            bool opened = fs->Open(1, 6, 1, 0);
            HeaderInfo* hdr = (HeaderInfo*)GetHeaderInfo(fs, kind);
            if (opened && hdr && FUN_00631810(hdr, u, kind, b))
                ok = true;
            else
                ok = false;
            if (hdr) {
                HeaderReader_s0063_2780 r;
                r.Open(fs);
                r.Free(hdr);
            }
            fs->Close();
            fs->Release();
        }
    }
    return ok;
}



// @ 0x00632900
void cSPPlayModePhotoBrowser_s0063_2780::AddPhoto(uint32_t guid, int kind)
{
    bool created = false;
    cPlayModePhoto_s0063_2780* p = FindPhotoByGuid(guid);
    if (!p) {
        void* mem = operator new(0x3c, "Editor", 0, 0, 0, 0);
        if (mem)
            p = new (mem) cPlayModePhoto_s0063_2780();
        else
            p = 0;
        created = true;
    }
    p->photo_guid = guid;
    p->bIsSelected = 0;
    cJob* old = p->writeJob.mpObject;
    if (old) {
        p->writeJob.mpObject = 0;
        old->Release();
    }
    p->bIsLoaded = 1;
    if (kind == 0x417b3bc) {
        p->keyC = guid;
        p->key8 = gPhotoTypeKeyInstance;
    }
    if (created)
        FUN_00631df0(p);
}



// @ 0x006329b0
bool cSPPlayModePhotoBrowser_s0063_2780::CopyPixelsToRaster(int idx, uint32_t a, uint32_t b)
{
    PixEntry* e = &((PixView*)((char*)this + idx * 0x24))->e;
    if (e->width == 0 || e->height == 0)
        return false;
    ImageRes* res = (ImageRes*)FUN_0067dd60_s0063_2780()->Acquire((void*)a, (void*)b, e->width, e->height, 1, 8, 0x15, 8);
    if (!res)
        return false;
    if (!(res->flags & 1))
        FUN_0067dd60_s0063_2780()->Commit(res);
    Surface* s = res->surface;
    if (!s)
        return false;
    void* pixels;
    if (s->Lock(2, 0, &pixels)) {
        memcpy(pixels, e->mpBegin, e->bytes);
        s->Unlock(&pixels);
    }
    e->erase(e->mpBegin, e->mpEnd);
    return true;
}



// @ 0x00632ab0
void cSPPlayModePhotoBrowser_s0063_2780::PushLoaded(uint32_t guid)
{
    cPlayModePhoto_s0063_2780* p = FindPhotoByGuid(guid);
    mLoaded.push_back(p);
}



// @ 0x00632b00
void cSPPlayModePhotoBrowser_s0063_2780::ClearLoadedPhotos()
{
    for (cPlayModePhoto_s0063_2780** it = mLoaded.mpBegin; it != mLoaded.mpEnd; ++it) {
        cPlayModePhoto_s0063_2780* p = *it;
        struct JobHandle { uint32_t pad[2]; uint32_t a; uint32_t b; };
        JobHandle* h = (JobHandle*)p;
        volatile long* counter = FUN_0067dd60_s0063_2780()->Lookup(h->b, h->a, 0) + 2;
        _InterlockedDecrement(counter);
        if (_InterlockedExchangeAdd(counter, 0) < 1)
            _InterlockedExchangeAdd(counter, 1);
        else
            _InterlockedExchangeAdd(counter, 0);
        p->bIsLoaded = 0;
    }
    mLoaded.erase(mLoaded.mpBegin, mLoaded.mpEnd);
}



// @ 0x00632ba0
void cSPPlayModePhotoBrowser_s0063_2780::DeleteAll()
{
    mUI->SetUIGroupVisible(0x4463e78, false);
    mUI->SetEditorUIGroupVisible(0x447c040, false);
    mUI->SetEditorUIGroupVisible(0x447c4e8, false);
    mUI->SetEditorUIEnabled(0x3f67720, false);
    SelectAll(true);
    FUN_00632660();
    ExitDeleteMode();
    ClearLoadedPhotos();
}



// @ 0x00632c00
void cSPPlayModePhotoBrowser_s0063_2780::MoveAll()
{
    mUI->SetUIGroupVisible(0x4463e78, false);
    mUI->SetEditorUIGroupVisible(0x447c040, false);
    mUI->SetEditorUIGroupVisible(0x447c4e8, false);
    mUI->SetEditorUIEnabled(0x3f67720, false);
    SelectAll(true);
    FUN_006326f0();
    ExitMoveMode();
    ClearLoadedPhotos();
}



// @ 0x00632c60
void cSPPlayModePhotoBrowser_s0063_2780::DeleteOne()
{
    mUI->SetUIGroupVisible(0x4463e78, false);
    mUI->SetEditorUIGroupVisible(0x447c040, false);
    mUI->SetEditorUIGroupVisible(0x447c4e8, false);
    mUI->SetEditorUIEnabled(0x3f67720, false);
    SelectAll(false);
    if (mCurrentSelectedPhotoIndex < mPhotos.size()) {
        cPlayModePhoto_s0063_2780* p = mPhotos.mpBegin[mCurrentSelectedPhotoIndex].mpObject;
        if (p) {
            p->bIsSelected = 1;
            FUN_00632660();
            ExitDeleteMode();
            ReleaseAsyncHandle();
        }
    }
}



// @ 0x00632ce0
void cSPPlayModePhotoBrowser_s0063_2780::MoveOne()
{
    mUI->SetUIGroupVisible(0x4463e78, false);
    mUI->SetEditorUIGroupVisible(0x447c040, false);
    mUI->SetEditorUIGroupVisible(0x447c4e8, false);
    mUI->SetEditorUIEnabled(0x3f67720, false);
    SelectAll(false);
    if (mCurrentSelectedPhotoIndex < mPhotos.size()) {
        cPlayModePhoto_s0063_2780* p = mPhotos.mpBegin[mCurrentSelectedPhotoIndex].mpObject;
        if (p) {
            p->bIsSelected = 1;
            FUN_006326f0();
            ExitMoveMode();
            ReleaseAsyncHandle();
        }
    }
}



// @ 0x00632d60
bool cSPPlayModePhotoBrowser_s0063_2780::SaveThumbnail(void* data)
{
    wstring16_s0063_2780 fileName;
    cPlayModePhoto_s0063_2780* p;
    if (mCurrentSelectedPhotoIndex < mPhotos.size())
        p = mPhotos.mpBegin[mCurrentSelectedPhotoIndex].mpObject;
    else
        p = 0;
    if (!p)
        return false;
    wstring16_s0063_2780 dirName;
    GetPhotoDir(p->photo_guid, &dirName);
    WStr_Format(&fileName, L"CRE_%s-%08x_sml.jpg", dirName.mpBegin, p->photo_guid);
    GetSaveArea(0x11ac196)->WriteFile(fileName.mpBegin, data);
    return true;
}



// @ 0x00632e40
bool cSPPlayModePhotoBrowser_s0063_2780::ResetPhotoMap()
{
    mPhotoTypeMap.clear();
    uint32_t n = PhotoCountChanged();
    if (n != mPhotoCount) {
        mPhotoCount = n;
        return true;
    }
    return false;
}



// @ 0x00632e90
PhotoTypeInfo& PhotoTypeMap::operator[](const uint32_t& key)
{
    RBNode* pLowerBound = (RBNode*)&mAnchor;
    RBNode* pCurrent = mAnchor.mpNodeParent;
    while (pCurrent) {
        if (!(pCurrent->key < key)) {
            pLowerBound = pCurrent;
            pCurrent = pCurrent->mpNodeLeft;
        } else {
            pCurrent = pCurrent->mpNodeRight;
        }
    }
    if (pLowerBound == (RBNode*)&mAnchor || key < pLowerBound->key) {
        PhotoTypePair entry;
        entry.key = key;
        entry.info.bits = 0;
        entry.info.key[0] = 0;
        entry.info.key[1] = 0;
        entry.info.key[2] = 0;
        PhotoTypeMapIterator it = DoInsertKey(pLowerBound, entry, InsertUniqueTag());
        pLowerBound = it.mpNode;
    }
    return pLowerBound->value;
}



// @ 0x00632f30
void cSPPlayModePhotoBrowser_s0063_2780::Shutdown()
{
    mbPhotosLoaded = 0;
    cJob* job = CancelAllPendingLoadJobs();
    if (job) {
        while (job->ContinueJob() == 4) {
        }
    }
    job = IsPhotosWriting();
    if (job) {
        while (job->ContinueJob() == 4) {
        }
    }
    ClearLoadedPhotos();
    ReleaseAsyncHandle();
    for (uint32_t i = 0; i < mPhotos.size(); ++i) {
        AutoRef_s0063_2780<cPlayModePhoto_s0063_2780>* slot = &mPhotos.mpBegin[i];
        cPlayModePhoto_s0063_2780* p = slot->mpObject;
        if (p) {
            slot->mpObject = 0;
            p->Release();
        }
    }
    AutoRef_s0063_2780<IRefCount>* t = mTooltip;
    int n = 5;
    do {
        IRefCount* p = t->mpObject;
        if (p) {
            t->mpObject = 0;
            p->Release();
        }
        t++;
    } while (--n);
}



// @ 0x00632fe0
void cSPPlayModePhotoBrowser_s0063_2780::Deactivate()
{
    IMessageServer* ms = MessageServer();
    if (ms) {
        ms->AddListener(this, 0x4235e47, 0xffffd8f1);
        ms->AddListener(this, 0x476e786, 0xffffd8f1);
        ms->AddListener(this, 0x41a218d, 0xffffd8f1);
        ms->AddListener(this, 0x4755bcf, 0xffffd8f1);
    }
    cJob* job = IsPhotosWriting();
    if (job) {
        while (job->ContinueJob() == 4) {
        }
    }
    ClearLoadedPhotos();
    ReleaseAsyncHandle();
    ++mDeactivateCount;
}



// @ 0x00633080
void cSPPlayModePhotoBrowser_s0063_2780::SetToLastPage()
{
    uint32_t old = mCurrentFirstPhotoIndex;
    mCurrentFirstPhotoIndex = ((mPhotos.size() - 1) / 5) * 5;
    if (mCurrentFirstPhotoIndex != old)
        ClearLoadedPhotos();
}



// @ 0x006330b0
bool cSPPlayModePhotoBrowser_s0063_2780::LoadPhotoThumb(uint32_t idx)
{
    bool result = false;
    if (idx < mPhotos.size()) {
        cPlayModePhoto_s0063_2780* ph = mPhotos.mpBegin[idx].mpObject;
        if (ph) {
            wstring16_s0063_2780 dirName;
            GetPhotoDir(ph->photo_guid, &dirName);
            wstring16_s0063_2780 fileName;
            WStr_Format(&fileName, L"CRE_%s-%08x_sml.jpg", dirName.mpBegin, ph->photo_guid);
            uint32_t outA;
            uint32_t outB;
            uint32_t outC;
            wstring16_s0063_2780 tmp;
            bool ok = FUN_006312f0(&outA, &outB, &outC, tmp);
            GetSaveArea(0x11ac196);
            if (ok) {
                if (CheckGuidAndType(tmp, outB, outC, fileName))
                    ok = true;
                else
                    ok = false;
            } else {
                ok = false;
            }
            result = ok;
        }
    }
    return result;
}



// @ 0x00633230
bool cSPPlayModePhotoBrowser_s0063_2780::MarkPhotoTypeForGuid(uint32_t guid, int kind, ResourceKey key)
{
    uint32_t bits = 0;
    ResourceKey k = { 0, 0, 0 };
    PhotoTypeMapIterator found = mPhotoTypeMap.find(guid);
    RBNode* it = found.mpNode;
    if (it != (RBNode*)&mPhotoTypeMap.mAnchor) {
        bits = it->value.bits;
        k.instance = it->value.key[0];
        k.type = it->value.key[1];
        k.group = it->value.key[2];
    }
    switch (kind) {
    case 0x417b3a7:
        bits |= 1;
        break;
    case 0x417b3bc:
        k = key;
        bits |= 2;
        break;
    }
    PhotoTypeInfo& slot = mPhotoTypeMap[guid];
    slot.bits = bits;
    slot.key[0] = k.instance;
    slot.key[1] = k.type;
    slot.key[2] = k.group;
    return true;
}



// @ 0x006332c0
bool cSPPlayModePhotoBrowser_s0063_2780::LoadPhotoByKey(const ResourceKey* key)
{
    wstring16_s0063_2780 s1;
    uint32_t outA = 0;
    uint32_t outB = (uint32_t)-1;
    wstring16_s0063_2780 s2;
    GetResourceManager()->GetPathForKey(key, &s2);
    wstring16_s0063_2780 s3(s2);
    bool ok = FUN_006312f0(&outA, &outB, &s1, s3);
    GetSaveArea(0x11ac196);
    if (ok) {
        if (CheckGuidAndType(s2, outA, outB, s1)) {
            if (MarkPhotoTypeForGuid(outA, outB, *key))
                ok = true;
            else
                ok = false;
        } else {
            ok = false;
        }
    }
    return ok;
}



// @ 0x00633440
void cSPPlayModePhotoBrowser_s0063_2780::CapturePixels(void* stream, int idx, uint32_t arg3)
{
    PixEntry* e = &((PixView*)((char*)this + idx * 0x24))->e;
    if (stream) {
        HeaderReader_s0063_2780 r;
        r.Open(stream);
        uint32_t count;
        if (r.Get(2, &count) && count > 0) {
            HeaderInfo* info = r.Item(0);
            if (info) {
                if (info->bpp == 0x18 || info->bpp == 0x20) {
                    uint32_t h = info->height;
                    uint32_t w = info->width;
                    int bytesPerPixel = (int)(info->bpp + ((int)info->bpp >> 31 & 7)) >> 3;
                    uint32_t total = bytesPerPixel * w * h;
                    e->resize(total);
                    uint32_t zero = 0;
                    if (!r.Read(info, e->mpBegin, bytesPerPixel * h))
                        total = zero;
                    r.Free(info);
                    e->bytes = total;
                    e->width = h;
                    e->height = w;
                    e->extra = arg3;
                }
            }
        }
    }
}



// @ 0x00633560
void __fastcall FUN_00633560(void* self)
{ (void)self; }


// @ 0x00633760
void __fastcall FUN_00633760(void* self)
{ (void)self; }


// @ 0x006338a0
void __fastcall FUN_006338a0(void* self)
{ (void)self; }


// @ 0x006339e0
void __fastcall FUN_006339e0(void* self)
{ (void)self; }


// @ 0x00633ac0
void __fastcall FUN_00633ac0(void* self)
{ (void)self; }


// @ 0x00633cc0
void __fastcall FUN_00633cc0(void* self)
{ (void)self; }


// @ 0x00634140
void __fastcall FUN_00634140(void* self)
{ (void)self; }
