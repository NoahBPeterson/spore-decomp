// Play-mode photo browser, part 2 (0x00632780..0x00633552): saving / loading photo files,
// the delete / move flows, the photo-type map, shutdown and deactivation.
// Compiled /O2 /MD /Gy /TP /GS- (no EH frames).

#include <intrin.h>
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedDecrement)

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int size_t;

extern "C" void* memcpy(void*, const void*, size_t);
void* operator new(size_t, const char*, int, int, int, int);
void operator delete(void*, const char*, int, int, int, int);
inline void* operator new(size_t, void* p) { return p; }
inline void operator delete(void*, void*) {}

void EASTL_allocator_deallocate(void* p);   // 0x00f47380

struct IRefCount {
    virtual int AddRef();
    virtual int Release();
};

// ---- strings -------------------------------------------------------------
extern wchar_t sEmptyWStr[];   // 0x01667bac, the shared empty string
struct wstring16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    uint32_t mAlloc;
    wstring16() : mpBegin(sEmptyWStr), mpEnd(sEmptyWStr), mpCapacity(sEmptyWStr + 1) {}
    wstring16(const wstring16& o);              // 0x0056e2d0
    struct NoInit {};
    wstring16(NoInit) {}
    ~wstring16() {
        if (mpCapacity - mpBegin > 1 && mpBegin)
            EASTL_allocator_deallocate(mpBegin);
    }
};
void WStr_Format(wstring16* out, const wchar_t* fmt, ...);   // 0x0041e050

// ---- UI --------------------------------------------------------------------
struct cSPPlayModeUI {
    void SetUIGroupVisible(uint32_t id, bool v);
    void SetEditorUIGroupVisible(uint32_t id, bool v);
    void SetEditorUIEnabled(uint32_t id, bool v);
};

// ---- jobs ------------------------------------------------------------------
struct cJob {
    int ContinueJob();      // 0x0068f970
    void Cancel(int);
    void AddRef();
    void Release();
};
template <class T> struct AutoRef {
    T* mpObject;
    AutoRef() : mpObject(0) {}
};

struct RefCountVBase {
    virtual void Dtor_();
    virtual int AddRef();
    virtual int Release();
    int mRefCount;
    RefCountVBase() : mRefCount(0) {}
};

struct cPlayModePhoto : RefCountVBase {
    uint32_t key8;            // +0x08
    uint32_t keyC;            // +0x0c
    uint32_t raster10;        // +0x10
    uint32_t raster14;        // +0x14
    uint32_t raster18;        // +0x18
    uint32_t photo_guid;      // +0x1c
    wstring16 mName;          // +0x20
    AutoRef<cJob> writeJob;   // +0x30
    AutoRef<cJob> loadJob;    // +0x34
    uint8_t bIsSelected;      // +0x38
    uint8_t bIsLoaded;        // +0x39
    cPlayModePhoto() : raster10(0), raster14(0), raster18(0) {}
};
extern uint32_t gPhotoTypeKeyInstance;   // 0x01523310

// ---- misc singletons -------------------------------------------------------
struct SaveArea {
    virtual int s00(); virtual int s01(); virtual int s02(); virtual int s03(); virtual int s04();
    virtual int s05(); virtual int s06(); virtual int s07(); virtual int s08(); virtual int s09();
    virtual const wchar_t* GetPath(wstring16* name);   // +0x28
    virtual int s0b(); virtual int s0c(); virtual int s0d(); virtual int s0e(); virtual int s0f();
    virtual int s10(); virtual int s11(); virtual int s12(); virtual int s13(); virtual int s14();
    virtual int s15(); virtual int s16(); virtual int s17(); virtual int s18(); virtual int s19();
    virtual void WriteFile(const wchar_t* path, void* data);   // +0x68
};
SaveArea* GetSaveArea(uint32_t id);    // 0x006b1f90
void OperatorPlus(wstring16* result, const wchar_t* rhs);   // 0x006309e0

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
struct HeaderReader {
    uint32_t pad[5];
    HeaderReader();                         // 0x0087cde0
    ~HeaderReader();                        // 0x0087d070
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
IRegistry* FUN_0067dd60();

struct IResourceManager {
    virtual int a00(); virtual int a01(); virtual int a02(); virtual int a03(); virtual int a04();
    virtual int a05(); virtual int a06(); virtual int a07(); virtual int a08(); virtual int a09();
    virtual int a0a(); virtual int a0b(); virtual int a0c(); virtual int a0d(); virtual int a0e();
    virtual int a0f(); virtual int a10(); virtual int a11(); virtual int a12(); virtual int a13();
    virtual int a14(); virtual int a15(); virtual int a16(); virtual int a17(); virtual int a18();
    virtual int a19(); virtual int a1a(); virtual int a1b(); virtual int a1c(); virtual int a1d();
    virtual int a1e();
    virtual void GetPathForKey(const void* key, wstring16* out);   // +0x7c
};
IResourceManager* GetResourceManager();   // 0x008de1a0

struct ResourceKey { uint32_t instance, type, group; };

// ---- lock-free pointer vector helpers ---------------------------------------
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

// ---- red-black tree (eastl::map<uint, pair<bitset<3>, Key>>) ----------------
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
struct PhotoTypeMap {
    uint32_t mCompare;
    RBAnchor mAnchor;
    uint32_t mnSize;
    void DoNuke(RBNode* n);                                   // 0x009a9600
    RBNode* find(const uint32_t& key);
    PhotoTypeInfo& operator[](const uint32_t& key);
    RBNode* DoInsertKey(RBNode* hint, uint32_t key, PhotoTypeInfo v);
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

// ---------------------------------------------------------------------------
// the browser
// ---------------------------------------------------------------------------
struct cSPPlayModePhotoBrowser {
    virtual void v0();
    PtrVec<AutoRef<cPlayModePhoto> > mPhotos;     // +0x04
    uint32_t pad0[2];
    uint32_t mCurrentFirstPhotoIndex;             // +0x18
    uint32_t mCurrentSelectedPhotoIndex;          // +0x1c
    uint8_t mbPhotosLoaded;                       // +0x20
    cSPPlayModeUI* mUI;                           // +0x24
    uint32_t pad1[(0x68 - 0x28) / 4];
    PhotoTypeMap mPhotoTypeMap;                   // +0x68
    uint32_t pad2;
    PixEntry mPix[99];                            // +0x84
    uint32_t pad2b[2];
    PtrVec<cPlayModePhoto*> mLoaded;              // +0xe78
    uint32_t pad3[2];
    void* mAsyncHandle;                           // +0xe8c
    AutoRef<IRefCount> mTooltip[5];               // +0xe90
    uint32_t mPhotoCount;                         // +0xea4
    uint32_t mDeactivateCount;                    // +0xea8

    // from the previous slice
    void SelectAll(bool v);
    void ExitDeleteMode();
    void ExitMoveMode();
    cPlayModePhoto* FindPhotoByGuid(uint32_t guid);
    void ReleaseAsyncHandle();
    cJob* CancelAllPendingLoadJobs();
    cJob* IsPhotosWriting();
    int GetHeaderInfo(void* stream, int kind);

    // this slice
    bool CheckGuidAndType(wstring16 a, uint32_t u, int kind, wstring16 b);
    void AddPhoto(uint32_t guid, int kind);
    bool CopyPixelsToRaster(int idx, uint32_t a, uint32_t b);
    void PushLoaded(uint32_t guid);
    void ClearLoadedPhotos();
    void DeleteAll();
    void MoveAll();
    void DeleteOne();
    void MoveOne();
    bool SaveThumbnail(void* data);
    bool ResetPhotoMap();
    void Shutdown();
    void Deactivate();
    void SetToLastPage();
    bool LoadPhotoThumb(uint32_t idx);
    bool MarkPhotoTypeForGuid(uint32_t guid, int kind, ResourceKey key);
    bool LoadPhotoByKey(const ResourceKey* key);
    void CapturePixels(int idx, void* stream, uint32_t arg3);

    // external members
    bool FUN_00631810(HeaderInfo* hdr, uint32_t u, int kind, wstring16 s);
    void FUN_00631df0(cPlayModePhoto* p);
    void GetPhotoDir(uint32_t guid, wstring16* out);                 // 0x00631e50
    bool FUN_006312f0(void* a, void* b, void* c, wstring16 s);
    uint32_t PhotoCountChanged();                                    // 0x00631b30
};
void FUN_00632660();
void FUN_006326f0();

// @ 0x00632780
bool cSPPlayModePhotoBrowser::CheckGuidAndType(wstring16 a, uint32_t u, int kind, wstring16 b)
{
    wstring16 path((wstring16::NoInit()));
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
                HeaderReader r;
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
void cSPPlayModePhotoBrowser::AddPhoto(uint32_t guid, int kind)
{
    bool created = false;
    cPlayModePhoto* p = FindPhotoByGuid(guid);
    if (!p) {
        void* mem = operator new(0x3c, "Editor", 0, 0, 0, 0);
        if (mem)
            p = new (mem) cPlayModePhoto();
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

struct Surface {
    int Lock(int mode, int z, void** out);     // 0x011ef750
    void Unlock(void** out);                    // 0x011ef880
};
struct ImageRes {
    Surface* surface;
    uint32_t flags;
};

// @ 0x006329b0
bool cSPPlayModePhotoBrowser::CopyPixelsToRaster(int idx, uint32_t a, uint32_t b)
{
    PixEntry* e = &((PixView*)((char*)this + idx * 0x24))->e;
    if (e->width == 0 || e->height == 0)
        return false;
    ImageRes* res = (ImageRes*)FUN_0067dd60()->Acquire((void*)a, (void*)b, e->width, e->height, 1, 8, 0x15, 8);
    if (!res)
        return false;
    if (!(res->flags & 1))
        FUN_0067dd60()->Commit(res);
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
void cSPPlayModePhotoBrowser::PushLoaded(uint32_t guid)
{
    cPlayModePhoto* p = FindPhotoByGuid(guid);
    mLoaded.push_back(p);
}

// @ 0x00632b00
void cSPPlayModePhotoBrowser::ClearLoadedPhotos()
{
    for (cPlayModePhoto** it = mLoaded.mpBegin; it != mLoaded.mpEnd; ++it) {
        cPlayModePhoto* p = *it;
        struct JobHandle { uint32_t pad[2]; uint32_t a; uint32_t b; };
        JobHandle* h = (JobHandle*)p;
        volatile long* counter = FUN_0067dd60()->Lookup(h->b, h->a, 0) + 2;
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
void cSPPlayModePhotoBrowser::DeleteAll()
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
void cSPPlayModePhotoBrowser::MoveAll()
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
void cSPPlayModePhotoBrowser::DeleteOne()
{
    mUI->SetUIGroupVisible(0x4463e78, false);
    mUI->SetEditorUIGroupVisible(0x447c040, false);
    mUI->SetEditorUIGroupVisible(0x447c4e8, false);
    mUI->SetEditorUIEnabled(0x3f67720, false);
    SelectAll(false);
    if (mCurrentSelectedPhotoIndex < mPhotos.size()) {
        cPlayModePhoto* p = mPhotos.mpBegin[mCurrentSelectedPhotoIndex].mpObject;
        if (p) {
            p->bIsSelected = 1;
            FUN_00632660();
            ExitDeleteMode();
            ReleaseAsyncHandle();
        }
    }
}

// @ 0x00632ce0
void cSPPlayModePhotoBrowser::MoveOne()
{
    mUI->SetUIGroupVisible(0x4463e78, false);
    mUI->SetEditorUIGroupVisible(0x447c040, false);
    mUI->SetEditorUIGroupVisible(0x447c4e8, false);
    mUI->SetEditorUIEnabled(0x3f67720, false);
    SelectAll(false);
    if (mCurrentSelectedPhotoIndex < mPhotos.size()) {
        cPlayModePhoto* p = mPhotos.mpBegin[mCurrentSelectedPhotoIndex].mpObject;
        if (p) {
            p->bIsSelected = 1;
            FUN_006326f0();
            ExitMoveMode();
            ReleaseAsyncHandle();
        }
    }
}

// @ 0x00632d60
bool cSPPlayModePhotoBrowser::SaveThumbnail(void* data)
{
    wstring16 fileName;
    cPlayModePhoto* p;
    if (mCurrentSelectedPhotoIndex < mPhotos.size())
        p = mPhotos.mpBegin[mCurrentSelectedPhotoIndex].mpObject;
    else
        p = 0;
    if (!p)
        return false;
    wstring16 dirName;
    GetPhotoDir(p->photo_guid, &dirName);
    WStr_Format(&fileName, L"CRE_%s-%08x_sml.jpg", dirName.mpBegin, p->photo_guid);
    GetSaveArea(0x11ac196)->WriteFile(fileName.mpBegin, data);
    return true;
}

// @ 0x00632e40
bool cSPPlayModePhotoBrowser::ResetPhotoMap()
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
        PhotoTypeInfo empty;
        empty.bits = 0;
        empty.key[0] = 0;
        empty.key[1] = 0;
        empty.key[2] = 0;
        pLowerBound = DoInsertKey(pLowerBound, key, empty);
    }
    return pLowerBound->value;
}

// @ 0x00632f30
void cSPPlayModePhotoBrowser::Shutdown()
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
        AutoRef<cPlayModePhoto>* slot = &mPhotos.mpBegin[i];
        cPlayModePhoto* p = slot->mpObject;
        if (p) {
            slot->mpObject = 0;
            p->Release();
        }
    }
    AutoRef<IRefCount>* t = mTooltip;
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
void cSPPlayModePhotoBrowser::Deactivate()
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
void cSPPlayModePhotoBrowser::SetToLastPage()
{
    uint32_t old = mCurrentFirstPhotoIndex;
    mCurrentFirstPhotoIndex = ((mPhotos.size() - 1) / 5) * 5;
    if (mCurrentFirstPhotoIndex != old)
        ClearLoadedPhotos();
}

// @ 0x006330b0
bool cSPPlayModePhotoBrowser::LoadPhotoThumb(uint32_t idx)
{
    bool result = false;
    if (idx < mPhotos.size()) {
        cPlayModePhoto* ph = mPhotos.mpBegin[idx].mpObject;
        if (ph) {
            wstring16 dirName;
            GetPhotoDir(ph->photo_guid, &dirName);
            wstring16 fileName;
            WStr_Format(&fileName, L"CRE_%s-%08x_sml.jpg", dirName.mpBegin, ph->photo_guid);
            uint32_t outA;
            uint32_t outB;
            uint32_t outC;
            wstring16 tmp;
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
bool cSPPlayModePhotoBrowser::MarkPhotoTypeForGuid(uint32_t guid, int kind, ResourceKey key)
{
    uint32_t bits = 0;
    ResourceKey k = { 0, 0, 0 };
    RBNode* it = mPhotoTypeMap.find(guid);
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
bool cSPPlayModePhotoBrowser::LoadPhotoByKey(const ResourceKey* key)
{
    wstring16 s1;
    uint32_t outA = 0;
    uint32_t outB = (uint32_t)-1;
    wstring16 s2;
    GetResourceManager()->GetPathForKey(key, &s2);
    wstring16 s3(s2);
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
void cSPPlayModePhotoBrowser::CapturePixels(int idx, void* stream, uint32_t arg3)
{
    PixEntry* e = &((PixView*)((char*)this + idx * 0x24))->e;
    if (stream) {
        HeaderReader r;
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
