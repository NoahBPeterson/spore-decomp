#include <intrin.h>
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedDecrement, _rotl)
// Play-mode UI module (0x0062F6E0..0x006306F0): the background-picker manager
// (SP::cSPPlayModeBGMgr) and the photo-browser helpers (SP::cSPPlayModePhotoBrowser).
// Compiled /O2 /MD /Gy.

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int size_t;

void* operator new(size_t, const char*, int, int, int, int);
inline void* operator new(size_t, void* p) { return p; }
inline void operator delete(void*, void*) {}
void operator delete(void*, const char*, int, int, int, int);

// ---------------------------------------------------------------------------
// shared helpers
// ---------------------------------------------------------------------------
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

struct RefCountVBase {
    virtual void Dtor_();
    virtual int AddRef();
    virtual int Release();
    int mRefCount;
    RefCountVBase() : mRefCount(0) {}
};
struct cSPPlayModeBGInfo : RefCountVBase {
    uint32_t mEntryEffectID;
    uint32_t mThumbNailID;
    uint32_t mOrderNumber;
    uint32_t mLightingID;
    cSPPlayModeBGInfo() {}
};

struct UIWindow {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
    virtual void v05(); virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
    virtual bool v0A();
    virtual void v0B(); virtual void v0C(); virtual void v0D(); virtual void v0E(); virtual void v0F();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v1A(); virtual void v1B(); virtual void v1C(); virtual void v1D(); virtual void v1E();
    virtual void SetVisible(bool visible, bool animate);
};

struct Effect {
    int f0045b210();
    void f0045b150();
    void f0045ae10(int);
};
Effect* __stdcall GetEffect(uint32_t id);   // FUN_00401050

struct ResourceKey { uint32_t instance, type, group; };

struct PropertyList;
struct Property {
    uint16_t pad[9];
    uint16_t type;   // +0x12
    int* GetInt();
};
struct PropertyList : IRefCount {
    virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6();
    virtual void s7(); virtual void s8();
    virtual bool GetProperty(uint32_t id, Property** out);   // vtbl +0x24
};
struct PropertyManager_ {
    virtual int a0(); virtual int a1(); virtual int a2(); virtual int a3(); virtual int a4();
    virtual int a5(); virtual int a6(); virtual int a7();
    virtual void GetPropertyList(uint32_t instance, uint32_t group, AutoRef<PropertyList>* out); // +0x20 (unused here)
    virtual void a9(); virtual void a10();
    virtual void GetPropertyListEx(uint32_t instance, uint32_t group, AutoRef<PropertyList>* out); // +0x2c
};
PropertyManager_* PropertyManager();   // 0x0067de30
void GetPropertyAsKeyInstance(PropertyList* props, uint32_t id, uint32_t* out);  // cdecl

struct KeyFilterBase {
    virtual void v0();
    int a;
    uint32_t b;
    uint32_t c;
    int d;
    KeyFilterBase() {}
    ~KeyFilterBase() {}
};
struct KeyFilter : KeyFilterBase {
    KeyFilter(uint32_t group) { a = -1; b = group | 0x40607000; c = 0xb1b104; d = -1; }
};

struct KeyArray {
    ResourceKey* mpBegin;
    ResourceKey* mpEnd;
    ResourceKey* mpCap;
    uint32_t mAlloc[2];
    KeyArray() : mpBegin(0), mpEnd(0), mpCap(0) {}
    ~KeyArray() {
        if (mpBegin && ((int*)mpBegin)[-1] != 0) EASTL_allocator_deallocate(mpBegin);
    }
    static void EASTL_allocator_deallocate(void*);
};

struct ResourceManager_ {
    virtual int a0(); virtual int a1(); virtual int a2(); virtual int a3(); virtual int a4();
    virtual int a5(); virtual int a6(); virtual int a7(); virtual int a8(); virtual int a9();
    virtual int a10(); virtual int a11(); virtual int a12(); virtual int a13();
    virtual void GetKeys(KeyArray* out, KeyFilterBase* filter, int flag);   // +0x38
};
ResourceManager_* GetResourceManager();   // 0x008de1a0

// ---------------------------------------------------------------------------
// cSPPlayModeBGMgr
// ---------------------------------------------------------------------------
struct cSPPlayModeBGMgr {
    virtual void v0();
    SPVec<AutoRef<cSPPlayModeBGInfo> > mBG;      // +0x04
    uint32_t pad0[2];                             // +0x10
    uint32_t mCurrThumbnailNum;                   // +0x18
    uint32_t mCurrBkgEffectID;                    // +0x1c
    uint32_t mLastBkgEffectID;                    // +0x20
    uint32_t pad1;                                // +0x24
    uint32_t mEntryEffectID;                      // +0x28
    uint32_t mChanging;                           // +0x2c
    uint8_t  mUI;                                 // +0x30
    cSPPlayModeUI* mUIPtr;                        // +0x34
    uint32_t mPageCount;                          // +0x38
    uint32_t mLightingWorld;                      // +0x3c
    uint32_t mbChangeInitiated;                   // +0x40
    uint8_t  mb44;                                // +0x44

    __declspec(noinline) void ShowBGThumbnails();
    bool HandleButton(uint32_t id);
    void Shutdown();
    __declspec(noinline) void LoadBackground(const ResourceKey* key);
    void LoadAllBGInfoFromGroup(uint8_t group);
    void Init(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint8_t e);
    void SetBGHilite(uint32_t id);
    void UpdateBGCountText();
    void UpdateBGHilite();
    void FUN_0062f610();
};

void FUN_008068d0(void* win, void* image, int z);
void FUN_00807840(uint32_t a, uint32_t b, uint32_t c, AutoRef<IRefCount>* out, int d, int e, int f);

// @ 0x0062f6e0
void cSPPlayModeBGMgr::ShowBGThumbnails()
{
    uint32_t ids[4] = { 0x445b018, 0x445b318, 0x445b340, 0x445b388 };
    uint32_t i = 0;
    do {
        if (i >= mBG.size())
            break;
        uint32_t idx = i + mPageCount * 4;
        void* win = mUIPtr->FindPlayModeUIWindow(ids[i]);
        if (idx >= mBG.size()) {
            FUN_008068d0(win, 0, 0);
        } else {
            AutoRef<IRefCount> img;
            FUN_00807840(0x2f7d0004, 0x100d977c, mBG.mpBegin[idx].mpObject->mThumbNailID, &img, 0, -1, -1);
            FUN_008068d0(win, img.mpObject, 0);
        }
        ++i;
    } while (i < 4);
    for (i = mBG.size(); i < 4; ++i) {
        UIWindow* w = (UIWindow*)mUIPtr->FindPlayModeUIWindow(ids[i]);
        if (w)
            w->SetVisible(true, false);
    }
}

// @ 0x0062f7f0
bool cSPPlayModeBGMgr::HandleButton(uint32_t id)
{
    bool result = false;
    uint32_t base = mPageCount * 4;
    uint32_t target;
    switch (id) {
    case 0x445b018:
        if (mCurrBkgEffectID == base)
            return result;
        if (mBG.size() <= base)
            return result;
        mCurrBkgEffectID = base;
        goto hilite;
    case 0x445b318: target = base + 1; break;
    case 0x445b340: target = base + 2; break;
    case 0x445b388: target = base + 3; break;
    case 0x47ed5b8:
        if (mPageCount > 0) {
            mPageCount = mPageCount - 1;
            UpdateBGCountText();
            ShowBGThumbnails();
            UpdateBGHilite();
            result = true;
        }
        return result;
    case 0x47ed640:
        if (mPageCount < mLightingWorld) {
            mPageCount = mPageCount + 1;
            UpdateBGCountText();
            ShowBGThumbnails();
            UpdateBGHilite();
            result = true;
        }
        return result;
    default:
        return result;
    }
    if (mCurrBkgEffectID == target)
        return result;
    if (mBG.size() <= target)
        return result;
    mCurrBkgEffectID = target;
hilite:
    result = true;
    SetBGHilite(id);
    FUN_0062f610();
    return result;
}

// @ 0x0062f8c0 / 0x0062f8e0: constructor / destructor of a small vtable + vector holder
struct SharedLibList {
    virtual void v0();
    SPVec<AutoRef<IRefCount> > mLibs;
    SharedLibList();
    ~SharedLibList();
};

// @ 0x0062f8c0
SharedLibList::SharedLibList() {}

// @ 0x0062f8e0
SharedLibList::~SharedLibList() {}

// @ 0x0062f920
void cSPPlayModeBGMgr::Shutdown()
{
    if (mBG.size() != 0) {
        uint32_t last = mLastBkgEffectID;
        cSPPlayModeBGInfo* info = mBG.mpBegin[0].mpObject;
        if (GetEffect(last)->f0045b210())
            GetEffect(mLastBkgEffectID)->f0045b150();
        if (!GetEffect(info->mEntryEffectID)->f0045b210()) {
            if (GetEffect(info->mEntryEffectID)->f0045b210())
                GetEffect(info->mEntryEffectID)->f0045ae10(1);
        }
        mLastBkgEffectID = info->mEntryEffectID;
        for (uint32_t i = 0; i < mBG.size(); ++i) {
            AutoRef<cSPPlayModeBGInfo>* slot = &mBG.mpBegin[i];
            cSPPlayModeBGInfo* p = slot->mpObject;
            if (p) {
                slot->mpObject = 0;
                p->Release();
            }
        }
        mBG.erase(mBG.mpBegin, mBG.mpEnd);
    }
}

// @ 0x0062f9f0
void cSPPlayModeBGMgr::LoadBackground(const ResourceKey* key)
{
    AutoRef<PropertyList> props;
    uint32_t entry = 0, thumb = 0, lighting = 0;
    Property* prop;
    uint32_t order = (uint32_t)-1;
    PropertyManager_* mgr = PropertyManager();
    if (props.mpObject) {
        PropertyList* t = props.mpObject;
        props.mpObject = 0;
        t->Release();
    }
    mgr->GetPropertyListEx(key->instance, key->group, &props);
    if (props.mpObject) {
        cSPPlayModeBGInfo* info = new ("Editor", 0, 0, 0, 0) cSPPlayModeBGInfo();
        AutoRef<cSPPlayModeBGInfo> ref(info);
        GetPropertyAsKeyInstance(props.mpObject, 0x3fd7424, &entry);
        GetPropertyAsKeyInstance(props.mpObject, 0x3febc27, &thumb);
        GetPropertyAsKeyInstance(props.mpObject, 0x56bf5d7, &lighting);
        if (props.mpObject && props.mpObject->GetProperty(0x40e7f66, &prop) && prop->type == 9)
            order = *prop->GetInt();
        info->mOrderNumber = order;
        info->mEntryEffectID = entry;
        info->mThumbNailID = thumb;
        info->mLightingID = lighting;
        SPVec<AutoRef<cSPPlayModeBGInfo> >* pv = &mBG;
        AutoRef<cSPPlayModeBGInfo>* end = pv->mpEnd;
        AutoRef<cSPPlayModeBGInfo>* it = pv->mpBegin;
        for (; it != end; ++it) {
            AutoRef<cSPPlayModeBGInfo> cur(*it);
            if (info->mOrderNumber < cur.mpObject->mOrderNumber) {
                pv->insert(it, ref);
                return;
            }
        }
        if (pv->mpEnd < pv->mpCapacity) {
            AutoRef<cSPPlayModeBGInfo>* slot = pv->mpEnd++;
            if (slot)
                new (slot) AutoRef<cSPPlayModeBGInfo>(ref);
        } else {
            pv->DoInsertValueEnd(pv->mpEnd, ref);
        }
    }
}

// @ 0x0062fbc0
void cSPPlayModeBGMgr::LoadAllBGInfoFromGroup(uint8_t group)
{
    ResourceManager_* rm = GetResourceManager();
    KeyArray keys;
    KeyFilter filter(group);
    ResourceKey copy;
    rm->GetKeys(&keys, &filter, 0);
    ResourceKey* end = keys.mpEnd;
    for (ResourceKey* k = keys.mpBegin; k != end; ++k) {
        copy = *k;
        LoadBackground(&copy);
    }
}

// @ 0x0062fc90
void cSPPlayModeBGMgr::Init(uint32_t a, uint32_t b, uint32_t c, uint32_t d, uint8_t e)
{
    mUIPtr = (cSPPlayModeUI*)a;
    mChanging = b;
    mLastBkgEffectID = b;
    mEntryEffectID = c;
    mCurrThumbnailNum = 0;
    mCurrBkgEffectID = 0;
    mUI = 0;
    mbChangeInitiated = d;
    LoadAllBGInfoFromGroup(e);
    mPageCount = 0;
    mLightingWorld = 0;
    if (mBG.size() > 0)
        mLightingWorld = (mBG.size() - 1) >> 2;
    if (mLightingWorld > 0)
        mUIPtr->SetUIGroupVisible(0x47ed4c0, true);
    else
        mUIPtr->SetUIGroupVisible(0x47ed4c0, false);
    UpdateBGCountText();
    ShowBGThumbnails();
    mUIPtr->SetUIGroupVisible(0x459b0f0, true);
    mUIPtr->SetUIGroupVisible(0x459b298, false);
    mUIPtr->SetUIGroupVisible(0x459b2d8, false);
    mUIPtr->SetUIGroupVisible(0x459b348, false);
    mb44 = 0;
}

// ---------------------------------------------------------------------------
// cSPPlayModePhotoBrowser
// ---------------------------------------------------------------------------
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
// the guid lives at +0x1c, so give a typed view of it
struct cPlayModePhotoG : cPlayModePhoto {};

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

// @ 0x0062fd60
uint8_t cSPPlayModePhotoBrowser::IsSendPhotoWinVisible()
{
    UIWindow* w = (UIWindow*)mUI->FindEditorUIWindow(0x3f67620);
    if (w) {
        uint8_t r = w->v0A();
        r &= 1;
        return r;
    }
    return false;
}

// @ 0x0062fda0
void cSPPlayModePhotoBrowser::EnterMoveMode()
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
void cSPPlayModePhotoBrowser::EnterDeleteMode()
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

// ---- GetHeaderInfo -------------------------------------------------------
struct HeaderReader {
    uint32_t pad[5];
    HeaderReader();            // 0x0087cde0
    ~HeaderReader();           // 0x0087d070
    bool Open(void* p);        // 0x0087ce00
    bool Get(int kind, uint32_t* count);   // 0x0087d0b0
    int Item(int idx);         // 0x0087ced0
};

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

// @ 0x0062ff90
const char* RFindFirstOf(const char* last, const char* first, const char* s, const char* sEnd)
{
    for (; last != first; --last)
        for (const char* p = s; p != sEnd; ++p)
            if (last[-1] == *p)
                return last;
    return first;
}

// @ 0x00630060
cPlayModePhoto* cSPPlayModePhotoBrowser::GetPhotoAt(uint32_t idx, bool relative)
{
    uint32_t i = relative ? mCurrentFirstPhotoIndex + idx : idx;
    if (i < mPhotos.size())
        return mPhotos.mpBegin[i].mpObject;
    return 0;
}

// @ 0x00630090
void cSPPlayModePhotoBrowser::SelectAll(bool v)
{
    for (uint32_t i = 0; i < mPhotos.size(); ++i) {
        cPlayModePhoto* p;
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
void cSPPlayModePhotoBrowser::ExitDeleteMode()
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
void cSPPlayModePhotoBrowser::ExitMoveMode()
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

struct PhotoGuid { uint32_t pad[7]; uint32_t guid; };

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
struct JobHandle { uint32_t pad[2]; uint32_t a; uint32_t b; uint8_t pad2[0x39 - 0x10]; uint8_t flag; };
struct Registry {
    virtual void r0(); virtual void r1(); virtual void r2(); virtual void r3();
    virtual void r4(); virtual void r5(); virtual void r6(); virtual void r7();
    virtual volatile long* Lookup(uint32_t b, uint32_t a, int z);   // +0x20
};
Registry* FUN_0067dd60();

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
struct JobRef {
    cJob* mpObject;
    JobRef& operator=(const JobRef& rhs);
};
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

// ---------------------------------------------------------------------------
// eastl::basic_string<wchar_t> members
// ---------------------------------------------------------------------------
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
struct LocaleMsgBase {
    virtual ~LocaleMsgBase() {}
};
struct LocaleMsg : LocaleMsgBase {
    uint32_t mSlots[0x2c / 4 - 1 + 1];   // placeholder up to +0x30 (slots are 8 bytes apiece from +8)
    ~LocaleMsg();
};
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
