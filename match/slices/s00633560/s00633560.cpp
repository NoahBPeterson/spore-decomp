// SP::cSPPlayModePhotoBrowser helpers. Region 0x633560-0x63448f.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"
#include <string.h>
#include <intrin.h>
#pragma intrinsic(_InterlockedExchangeAdd)

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

// ---- jobs / allocators -----------------------------------------------------
void* operator new(size_t, const char*, int, int, int, int);   // 0x00f473a0
void  operator delete[](void*);                                // 0x00f47380

// ---- shared layouts (mirrors the s00632780 slice) ---------------------------
extern wchar_t g_1667bac[];                       // 0x01667bac shared empty string
extern wchar_t g_1667bae[];                       // 0x01667bae

struct wstring16 {
    wchar_t* mpBegin;                             // +0x00
    wchar_t* mpEnd;                               // +0x04
    wchar_t* mpCapacity;                          // +0x08
    uint32_t mAlloc;                              // +0x0c
    wstring16() : mpBegin(g_1667bac), mpEnd(g_1667bac), mpCapacity(g_1667bae) {}
    ~wstring16() {
        if (mpBegin && mpCapacity - mpBegin > 1)
            operator delete[](mpBegin);
    }
};

struct ResourceKey { uint32_t instance, type, group; };

// ---- cSPPlayModeUI ---------------------------------------------------------
struct cSPPlayModeUI {
    void* FindEditorUIWindow(uint32_t id);                     // 0x00634e40
    void* FindPlayModeUIWindow(uint32_t id);                   // 0x00634dc0
    void  ShowToolTip(uint32_t id, uint32_t a, uint32_t b, void* tip, float* p);  // 0x00635040
    void  RemoveTooltip(uint32_t id, void* p);                 // 0x00635290
    void  SetUIGroupVisible(uint32_t id, int v);               // 0x00635760
    void  SetEnabled(uint32_t id, int v);                      // 0x00634ef0
};

struct cJob {
    int  ContinueJob();                                        // 0x0068f970
    int  AddRef();                                             // 0x0068f950
    int  Release();                                            // 0x00690120
    int  GetStatus();                                          // 0x006909b0
};

// ---- browser thiscall entry points (reached through a PMB* view) -----------
struct PMB {
    void DeleteOne();                   // 0x00632c60
    void DeleteAll();                   // 0x00632ba0
    void MoveOne();                     // 0x00632ce0
    void MoveAll();                     // 0x00632c00
    int  PhotoCountChanged();           // 0x00631b30
    void ShowImageThumbnail();          // 0x00633cc0
    void UpdatePhotoCountText();        // 0x00630d10
    void DeletePhoto(int idx, int b);   // 0x006320d0
    void ShowSendEmailWindow();         // 0x00630f20
    void* IsPhotosWriting();            // 0x00630470
    void ClearLoadedPhotos();           // 0x00632b00
    void ClearPhotoList();              // 0x00634030
    void CapturePixels(void* stream, int idx, uint32_t arg3);          // 0x00633440
    bool LoadPhotoByKey(const ResourceKey* key);                       // 0x006332c0
    void* FindPhotoByGuid(uint32_t guid);                              // 0x00630360
    bool CopyPixelsToRaster(int idx, uint32_t p, uint32_t group);      // 0x006329b0
    void AddPhoto(int guid, int arg);                                  // 0x00632900
    void PushLoaded(uint32_t guid);                                    // 0x00632ab0
    void GetPhotoDir(int guid, wstring16* out);                        // 0x00631e50
};

// cPlayModePhoto: refcounted, 0x3c bytes.
struct cPlayModePhoto {
    void* vptr;             // +0x00
    int   mRefCount;        // +0x04
    uint32_t keyType;       // +0x08
    uint32_t keyInstance;   // +0x0c
    ResourceKey fullKey;    // +0x10  fullScreenThumbnail.key (instance/type/group)
    uint32_t photo_guid;    // +0x1c
    uint32_t name20;        // +0x20
    uint32_t name24;        // +0x24
    uint32_t name28;        // +0x28
    uint32_t name2c;        // +0x2c
    cJob*  writeJob;        // +0x30
    cJob*  loadJob;         // +0x34
    uint8_t bIsSelected;    // +0x38
    uint8_t bIsLoaded;      // +0x39
};

typedef cPlayModePhoto* PhotoPtr;
template <class T> struct AutoRef { T* mpObject; AutoRef() : mpObject(0) {} };

struct PhotoVec {                       // PtrVec<AutoRef<cPlayModePhoto>>
    PhotoPtr* mpBegin;                  // +0x00
    PhotoPtr* mpEnd;                    // +0x04
    PhotoPtr* mpCapacity;               // +0x08
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    void PushBack(void* pos, void* pv); // 0x005c8480
};

// ---- red-black tree (eastl::map<uint, pair<bitset<3>, Key>>) ----------------
struct RBNode;
struct RBAnchor { RBNode* right; RBNode* left; RBNode* parent; uint8_t color; };
struct RBNode : RBAnchor { uint32_t key; uint32_t value[5]; };
struct RBTreeHead {                     // 0x1c bytes
    uint32_t mCompare;                  // +0x00
    RBAnchor mAnchor;                   // +0x04
    uint32_t mnSize;                    // +0x14
    uint32_t mAllocator;                // +0x18
    void DoNuke(RBNode* n);             // 0x009a9600
};
// thiscall stub removed: the map reset in these functions is eastl DoNukeSubtree

struct PixEntry {                       // 0x24 bytes
    uint8_t* mpBegin;                   // +0x00
    uint8_t* mpEnd;                     // +0x04
    uint8_t* mpCapacity;                // +0x08
    uint32_t mAlloc;                    // +0x0c
    uint32_t pad10;                     // +0x10
    uint32_t width;                     // +0x14
    uint32_t height;                    // +0x18
    uint32_t bytes;                     // +0x1c
    uint32_t guid;                      // +0x20
};

// ---- the browser -----------------------------------------------------------
struct CapArg;
struct cSPPlayModePhotoBrowser {        // 0xec0 bytes
    void*    vptr;                             // +0x000
    PhotoVec mPhotos;                          // +0x004
    uint32_t pad10;                            // +0x010
    uint32_t pad14;                            // +0x014
    uint32_t mCurrentFirstPhotoIndex;          // +0x018
    uint32_t mCurrentSelectedPhotoIndex;       // +0x01c
    uint8_t  mbPhotosLoaded;                   // +0x020
    cSPPlayModeUI* mUI;                        // +0x024
    uint32_t pad28[10];                        // +0x028..0x050
    uint32_t mWatermarkPixels;                 // +0x050
    uint32_t pad54[5];                         // +0x054..0x068
    RBTreeHead mPhotoTypeMap;                  // +0x068
    PixEntry mPix[99];                         // +0x084..0xe70
    uint32_t mPixelBufCount;                   // +0x0e70
    uint32_t mBrowserMode;                     // +0x0e74
    PhotoVec mLoaded;                          // +0x0e78..0xE84
    uint32_t mPadE84;                          // +0x0e84
    uint32_t mPadE88;                          // +0x0e88
    void*    mAsyncHandle;                     // +0x0e8c
    AutoRef<void> mTooltip[5];                 // +0x0e90..+0x0ea4
    uint32_t mPhotoCount;                      // +0x0ea4
    uint32_t mDeactivateCount;                 // +0x0ea8
    uint32_t mLoadedCount[5];                  // +0x0eac..+0x0ec0

    void Init(cSPPlayModeUI* ui);                                    // 0x006339e0
    void ShowThumbnailAsync(const ResourceKey* key, uint32_t guid,
                            int slotIdx, void* win, uint8_t flag);   // 0x00633ac0
    void ShowImageThumbnail();                                       // 0x00633cc0
    bool CapturePhotoFromMessage(CapArg* arg);                       // 0x00633560
    bool Activate(uint32_t msgId, void* arg);                        // 0x00634140
    void SetSelectedPhoto(unsigned idx);                             // 0x00634380
};

// ---- engine entry points (address-annotated) -------------------------------
extern "C" void* __cdecl FUN_0067dd60(void);       // 0x0067dd60 resource registry
extern "C" void* __cdecl FUN_006b1f90(int id);     // 0x006b1f90 SaveArea::Get
extern "C" void* __cdecl FUN_0067dcc0(void);       // 0x0067dcc0 MessageServer
extern "C" void  __cdecl FUN_006309e0(wstring16* out, const void* path);       // 0x006309e0 operator+
extern "C" void  __cdecl FUN_0041e050(wstring16* out, const wchar_t* fmt, ...); // 0x0041e050 format
extern "C" void* __cdecl FUN_00f473a0(int n, const char* name, int a, int b, int c, int d); // 0x00f473a0 operator new
extern "C" void  __cdecl FUN_00f47380(void* p);    // 0x00f47380 operator delete[]
extern "C" void* __cdecl FUN_00921580(void* node); // 0x00921580 RBTreeIncrement
extern "C" void  __cdecl FUN_00921880(void* node, void* anchor);  // 0x00921880 RBTreeErase
extern "C" void* __cdecl FUN_00633890(void);       // 0x00633890 job callback
extern "C" void  __cdecl FUN_008068d0(void* win, void* img, int a);    // 0x008068d0 SetWindowImage
extern "C" char  __cdecl FUN_00807bb0(void* win, void* p, int a);      // 0x00807bb0 SetWindowImage
extern "C" void* __cdecl FUN_006300d0(void* raster);                   // 0x006300d0 GetImageFromRaster
extern "C" void* __cdecl FUN_009512c0(void);       // 0x009512c0 (returns a name pointer)
extern "C" void* __cdecl FUN_009512d0(int size, int align, const char* name, void* a); // 0x009512d0
extern "C" void* __cdecl FUN_0068f4d0(void);       // 0x0068f4d0

// thiscall helpers modelled as members (ecx = the object shown in the comment)
struct FileStream {
    void* ctor(const char* name);                  // 0x00931da0
};
struct JobCtx {
    void Submit(void* job);                        // 0x0068f9b0
    int  GetStatus();                              // 0x006909b0
};
struct TooltipProc {
    void* ctor(const wchar_t* group, uint32_t id, const wchar_t* text, float* p,
               uint32_t a, void* vtbl, uint32_t b);    // 0x00835e30
};

extern uint32_t g_1523310;              // 0x01523310 photo-type key instance

// ---- capture-argument model ------------------------------------------------
struct CapObj {
    uint32_t f00, f04, f08;   // +0x00
    ResourceKey key;          // +0x0c
    uint32_t guid;            // +0x18
    uint32_t f1c, f20;        // +0x1c, +0x20
    uint8_t  flag24;          // +0x24
    uint32_t target;          // +0x28
    uint32_t kind;            // +0x2c
};
struct CapArg { uint32_t f0, f4; CapObj* pObj; };   // pObj at +8

typedef void (__thiscall *VFnV)(void*);
typedef int  (__thiscall *VFnI)(void*);
typedef int  (__thiscall *VFnArg)(void*, int);
typedef void (__thiscall *VFnPP)(void*, void*);
typedef void (__thiscall *VFnSS)(void*, void*, void*);
typedef void (__thiscall *VFnS)(void*, const wstring16*);
typedef int  (__thiscall *VFn4I)(void*, int, int, int);
typedef void* (__thiscall *VFn4P)(void*, int, int, int);
typedef int  (__thiscall *VFn4I4)(void*, int, int, int, int);
typedef const void* (__thiscall *VFnPath)(void*, wstring16*);
typedef void (__thiscall *VFnKeyPath)(void*, const ResourceKey*, wstring16*);
typedef void (__thiscall *VFn4)(void*, void*, void*, int);
typedef void (__thiscall *VFn4A)(void*, void*, void*, int, int);
typedef void (__thiscall *VFnPPP)(void*, void*, void*, void*);

static inline void* VSLOT(void* obj, int byteOffset) {
    return ((void**)*(void**)obj)[byteOffset / 4];
}
static void WStrFree(wstring16& s) {
    if (s.mpBegin && s.mpCapacity - s.mpBegin > 1)
        FUN_00f47380(s.mpBegin);
}

struct Vec3 { void* b; void* e; void* c; };

void __fastcall FUN_00633ea0(void* self);   // 0x00633ea0 UpdateViewerImage

// ===========================================================================
// 0x00633560: CapturePhotoFromMessage
// ===========================================================================
// @ 0x00633560
bool cSPPlayModePhotoBrowser::CapturePhotoFromMessage(CapArg* arg)
{
    void* self = this;
    CapObj* o = arg->pObj;
    ResourceKey key;                       // +0x18 on the frame
    key.instance = o->key.instance;
    key.type     = o->key.type;
    key.group    = o->key.group;
    uint32_t loc18 = o->guid;
    uint32_t loc1c = o->f1c;
    uint32_t loc20 = o->f20;
    (void)loc1c; (void)loc20;
    uint8_t  flag   = o->flag24;
    uint32_t target = o->target;
    uint32_t kind   = o->kind;

    void* rmgr = FUN_0067dd60();
    void* sa   = FUN_006b1f90(0x11ac196);

    wstring16 path;                        // +0x28
    ((VFnKeyPath)VSLOT(rmgr, 0x7c))(rmgr, &key, &path);          // GetPathForKey
    const void* p = ((VFnPath)VSLOT(sa, 0x28))(sa, &path);       // GetPath
    wstring16 full;                        // +0x40
    FUN_006309e0(&full, p);                // operator+

    void* fs = FUN_00f473a0(0x22c, "Editor", 0, 0, 0, 0);
    if (fs != 0) {
        fs = ((FileStream*)fs)->ctor(0);
        if (fs != 0)
            ((VFnV)VSLOT(fs, 0x04))(fs);
    }
    ((VFnS)VSLOT(fs, 0x3c))(fs, &full);                          // SetPath
    bool opened = ((VFn4I4)VSLOT(fs, 0x4c))(fs, 1, 6, 1, 0) != 0; // Open
    if (opened)
        ((PMB*)self)->CapturePixels(fs, (int)loc1c, loc18);

    void* ms = FUN_0067dcc0();
    if (ms != 0 && target != 0) {
        void* msg = FUN_00f473a0(0x38, "Editor", 0, 0, 0, 0);
        if (msg != 0) {
            *(uint32_t*)((char*)msg + 0x28) = 0;
            *(void**)msg = (void*)0x13eb90c;         // vtbl_UI::BehaviorMessage
            *(uint32_t*)((char*)msg + 4) = 0;
            *(uint32_t*)((char*)msg + 0x30) = 0;
            *(void**)msg = (void*)0x13fe50c;
            ((VFnV)VSLOT(msg, 0x04))(msg);
        }
        uint32_t* m = (uint32_t*)msg;
        m[2] = loc1c;
        m[4] = (flag != 0);
        m[6] = loc20;
        m[8] = kind;
        ((VFn4A)VSLOT(ms, 0x18))(ms, (void*)target, msg, 0, 0);
        ((VFnV)VSLOT(msg, 0x08))(msg);
    }
    ((VFnV)VSLOT(fs, 0x08))(fs);

    WStrFree(full);
    WStrFree(path);
    return true;
}

// ===========================================================================
// 0x00633760: FindValidPhotos
// ===========================================================================
// @ 0x00633760
uint32_t __fastcall FUN_00633760(void* self)
{
    char* s = (char*)self;
    void* sa = FUN_006b1f90(0x11ac196);
    uint32_t ctx[5];
    uint32_t r = ((VFnArg)VSLOT(sa, 0x5c))(sa, 0x13f8f14);
    ctx[0] = 0x13eb898;
    ctx[1] = 0xffffffff;
    ctx[2] = 0x11ac196;
    ctx[3] = r;
    ctx[4] = 0xffffffff;
    Vec3 arr;
    arr.b = arr.e = arr.c = 0;
    ((VFnSS)VSLOT(sa, 0x30))(sa, (void*)&arr, (void*)&ctx[0]);
    for (char* it = (char*)arr.b; it != (char*)arr.e; it += 0xc) {
        ResourceKey tmp;
        tmp.instance = *(uint32_t*)(it + 0);
        tmp.type     = *(uint32_t*)(it + 4);
        tmp.group    = *(uint32_t*)(it + 8);
        ((PMB*)self)->LoadPhotoByKey(&tmp);
    }

    RBNode* anchor = (RBNode*)(s + 0x6c);
    RBNode* n = *(RBNode**)(s + 0x70);
    while (n != anchor) {
        uint32_t bits = n->value[0];
        if ((bits & 1) != 0 && ((bits >> 1) & 1) != 0) {
            n = (RBNode*)FUN_00921580(n);
        } else {
            --*(uint32_t*)(s + 0x7c);
            RBNode* next = (RBNode*)FUN_00921580(n);
            FUN_00921880(n, anchor);
            FUN_00f47380(n);
            n = next;
        }
    }
    uint32_t cnt = *(uint32_t*)(s + 0x7c);
    if (arr.b != 0 && ((int*)(arr.b))[-1] != 0)
        FUN_00f47380(arr.b);
    return cnt;
}

// ===========================================================================
// 0x006338a0: ResetPhotoCounts (private helper)
// ===========================================================================
// @ 0x006338a0
void __fastcall FUN_006338a0(void* self)
{
    cSPPlayModePhotoBrowser* b = (cSPPlayModePhotoBrowser*)self;
    FUN_00633760(self);
    char* s = (char*)self;
    RBNode* anchor = (RBNode*)(s + 0x6c);
    RBNode* n = *(RBNode**)(s + 0x70);
    uint32_t count = 0;
    while (n != anchor) {
        if (count >= 0x63)
            return;
        cPlayModePhoto* ph = (cPlayModePhoto*)FUN_00f473a0(0x3c, "Editor", 0, 0, 0, 0);
        if (ph != 0) {
            ph->mRefCount = 0;
            ph->vptr = (void*)0x13fe518;
            ph->fullKey.instance = 0;
            ph->fullKey.type = 0;
            ph->fullKey.group = 0;
            ph->name20 = (uint32_t)(uintptr_t)g_1667bac;
            ph->name24 = (uint32_t)(uintptr_t)g_1667bac;
            ph->name28 = (uint32_t)(uintptr_t)g_1667bae;
            ph->writeJob = 0;
            ph->loadJob = 0;
        }
        ph->photo_guid = n->key;
        ph->fullKey.instance = n->value[1];
        ph->fullKey.type = n->value[2];
        ph->fullKey.group = n->value[3];
        ph->bIsSelected = 0;
        if (ph->writeJob != 0) {
            cJob* j = ph->writeJob;
            ph->writeJob = 0;
            j->Release();
        }
        if (ph->loadJob != 0) {
            cJob* j = ph->loadJob;
            ph->loadJob = 0;
            j->Release();
        }
        ph->bIsLoaded = 0;
        ((VFnV)VSLOT(ph, 0x04))(ph);
        // push into mPhotos (PtrVec<AutoRef>) with the lock-free inline path
        PhotoPtr* end = b->mPhotos.mpEnd;
        if (end < b->mPhotos.mpCapacity) {
            b->mPhotos.mpEnd = end + 1;
            *end = ph;
            ((VFnV)VSLOT(ph, 0x04))(ph);
        } else {
            b->mPhotos.PushBack(end, &ph);
        }
        if (ph != 0)
            ((VFnV)VSLOT(ph, 0x08))(ph);
        n = (RBNode*)FUN_00921580(n);
        ++count;
    }
}

// ===========================================================================
// 0x006339e0: Init
// ===========================================================================
// @ 0x006339e0
void cSPPlayModePhotoBrowser::Init(cSPPlayModeUI* ui)
{
    mUI = ui;
    mCurrentSelectedPhotoIndex = 0xffffffff;
    mWatermarkPixels = 0;
    FUN_006338a0(this);
    float local8 = 5.0f;
    float local4 = -15.0f;
    AutoRef<void>* slot = mTooltip;
    int n = 5;
    int i = 0;
    do {
        void* mem = FUN_009512d0(0x68, 4, "UI/Tooltip", FUN_009512c0());
        void* tip = 0;
        if (mem != 0)
            tip = ((TooltipProc*)mem)->ctor(L"Tooltips", 0x3754e6c, L"***PLACEHOLDER***",
                                            &local8, 0, (void*)0x13fe4c4, 0);
        void* cur = slot->mpObject;
        if (tip != cur) {
            if (tip != 0)
                ((VFnV)VSLOT(tip, 0x00))(tip);
            slot->mpObject = tip;
            if (cur != 0)
                ((VFnV)VSLOT(cur, 0x04))(cur);
        }
        mLoadedCount[i] = 0;
        slot++;
        ++i;
    } while (--n);
    mDeactivateCount = 0;
}

// ===========================================================================
// 0x00633ac0: ShowThumbnailAsync
// ===========================================================================
// @ 0x00633ac0
void cSPPlayModePhotoBrowser::ShowThumbnailAsync(
    const ResourceKey* key, uint32_t guid, int slotIdx, void* win, uint8_t flag)
{
    wstring16 path;
    if (key->instance == 0 && key->group == 0 && key->type == 0) {
        ((PMB*)this)->GetPhotoDir((int)guid, &path);
        wstring16 full;
        FUN_0041e050(&full, L"CRE_%s-%08x_sml.jpg", path.mpBegin, guid);
        void* sa = FUN_006b1f90(0x11ac196);
        ((VFnSS)VSLOT(sa, 0x68))(sa, full.mpBegin, (void*)key);
        WStrFree(full);
    }
    // job object
    void* job = FUN_00f473a0(0x30, "Editor", 0, 0, 0, 0);
    uint32_t* j = 0;
    if (job != 0) {
        j = (uint32_t*)job;
        j[0] = 0x13f1ab0;
        j[1] = 0x13ef094;
        j[2] = 0;
        j[0] = 0x14906ec;
        j[1] = 0x14188c0;
        j[3] = 0; j[4] = 0; j[5] = 0; j[6] = 0; j[7] = 0; j[8] = 0;
        j[10] = 0; j[11] = 0;
        ((uint8_t*)j)[0x24] = 0;
        ((VFnV)VSLOT(j, 0x00))(j);
    }
    j[3] = key->instance;
    j[4] = key->type;
    j[5] = key->group;
    j[6] = guid;
    j[7] = (uint32_t)slotIdx;
    j[8] = (uint32_t)win;
    ((uint8_t*)j)[0x24] = flag;
    j[10] = 0x476e786;
    j[11] = mDeactivateCount;

    void* mgr = FUN_0068f4d0();
    void* ctx = 0;
    ((VFnPP)VSLOT(mgr, 0x10))(mgr, &ctx);
    *(void**)((char*)ctx + 0x00) = (void*)&FUN_00633890;
    *(void**)((char*)ctx + 0x04) = this;
    *(uint32_t*)((char*)ctx + 0x18) = 4;
    ((JobCtx*)ctx)->Submit(j);
    ((JobCtx*)ctx)->GetStatus();

    void* ph = ((PMB*)this)->FindPhotoByGuid(guid);
    cJob* old = *(cJob**)((char*)ph + 0x34);
    cJob* nu  = (cJob*)ctx;
    if (nu != old) {
        if (nu != 0)
            nu->AddRef();
        *(cJob**)((char*)ph + 0x34) = nu;
        if (old != 0)
            old->Release();
    }
    ++mWatermarkPixels;
    if (nu != 0)
        nu->Release();
    ((VFnV)VSLOT(j, 0x04))(j);
    WStrFree(path);
}

// ===========================================================================
// 0x00633cc0: ShowImageThumbnail
// ===========================================================================
// @ 0x00633cc0
void cSPPlayModePhotoBrowser::ShowImageThumbnail()
{
    void* job = ((PMB*)this)->IsPhotosWriting();
    if (job != 0) {
        while (((cJob*)job)->ContinueJob() == 4) {
        }
    }
    AutoRef<void>* slot = mTooltip;
    const uint32_t ids[5] = { 0x3eab260, 0x3f15ea8, 0x3f15ef8, 0x3f6c0e8, 0x3f6c188 };
    for (uint32_t i = 0; i < 5; ++i, ++slot) {
        void* win = mUI->FindPlayModeUIWindow(ids[i]);
        if (win == 0)
            continue;
        uint32_t idx = mCurrentFirstPhotoIndex + i;
        if (idx < mPhotos.size()) {
            cPlayModePhoto* ph = mPhotos.mpBegin[idx];
            if (ph != 0) {
                mUI->ShowToolTip(ids[i], 0x583897c,
                                 (uint32_t)(uintptr_t)L"*ClickToEmail*",
                                 slot->mpObject, 0);
                if (ph->bIsLoaded == 0) {
                    mLoadedCount[i] = ph->photo_guid;
                    ShowThumbnailAsync(&ph->fullKey, ph->photo_guid, (int)i, win, 0);
                } else {
                    void* rmgr = FUN_0067dd60();
                    void* ras = ((VFn4P)VSLOT(rmgr, 0x20))(rmgr, ph->keyInstance,
                                                           g_1523310, 0);
                    void* rmgr2 = FUN_0067dd60();
                    ((VFnPP)VSLOT(rmgr2, 0x68))(rmgr2, ras);
                    void* img = FUN_006300d0(ras);
                    if (img != 0)
                        ((VFnV)VSLOT(img, 0x00))(img);
                    FUN_008068d0(win, img, 0);
                    if (img != 0)
                        ((VFnV)VSLOT(img, 0x04))(img);
                }
                continue;
            }
        }
        // empty slot: clear the loaded-guid marker, blank the window, drop tooltip
        mLoadedCount[i] = 0;
        FUN_008068d0(win, 0, 0);
        mUI->RemoveTooltip(ids[i], slot->mpObject);
    }
}

// ===========================================================================
// helpers for the nonmatching tail (kept from the previous wave)
// ===========================================================================
typedef void (__thiscall *TF0)(void*);
typedef void (__thiscall *TF1)(void*, int);
typedef void (__thiscall *TF2)(void*, void*, int);
typedef void (__thiscall *TF3)(void*, int, int, int);

// @ 0x00633f90
void __fastcall FUN_00633f90(void* self) {
  char* s = (char*)self;
  int tag = 0;
  switch (*(int*)(s + 0xe74)) {
    case 0: tag = 0x447a553; ((PMB*)s)->DeleteOne(); break;
    case 1: tag = 0x4479851; ((PMB*)s)->DeleteAll(); break;
    case 2: tag = 0x447a54c; ((PMB*)s)->MoveOne(); break;
    case 3: tag = 0x4479848; ((PMB*)s)->MoveAll(); break;
  }
  int c = ((PMB*)s)->PhotoCountChanged();
  *(int*)(s + 0xea4) = c;
  ((PMB*)s)->ShowImageThumbnail();
  ((PMB*)s)->UpdatePhotoCountText();
  FUN_00633ea0(s);
  void* m = FUN_0067dcc0();
  if (m != 0 && tag != 0) {
    ((TF3)(*(void**)(*(char**)m + 0x14)))(m, tag, 0, 0);
  }
}

// @ 0x00634030
void __fastcall FUN_00634030(void* self) {
  char* s = (char*)self;
  cSPPlayModePhotoBrowser* b = (cSPPlayModePhotoBrowser*)self;
  RBTreeHead* map = &b->mPhotoTypeMap;
  map->DoNuke(*(RBNode**)(s + 0x74));
  RBNode* anchor = (RBNode*)&map->mAnchor;
  map->mAnchor.left = anchor;
  map->mAnchor.parent = 0;
  map->mAnchor.color = 0;
  map->mnSize = 0;
  map->mAnchor.right = anchor;
  for (int i = (int)b->mPhotos.size() - 1; i >= 0; --i)
    ((PMB*)b)->DeletePhoto(i, 0);
  FUN_006338a0(s);
  b->mCurrentFirstPhotoIndex = 0;
  b->ShowImageThumbnail();
  ((PMB*)b)->UpdatePhotoCountText();
  if (b->mPhotos.size() == 0)
    b->mUI->SetUIGroupVisible(0x4463e78, 0);
  else
    b->mUI->SetUIGroupVisible(0x4463e78, 1);
}

// @ 0x006340c0
bool __fastcall FUN_006340c0(void* self) {
  char* s = (char*)self;
  void* m = FUN_0067dcc0();
  if (m != 0) {
    ((TF2)(*(void**)(*(char**)m + 0x24)))(m, self, 0x4235e47);
    ((TF2)(*(void**)(*(char**)m + 0x24)))(m, self, 0x476e786);
    ((TF2)(*(void**)(*(char**)m + 0x24)))(m, self, 0x41a218d);
    ((TF2)(*(void**)(*(char**)m + 0x24)))(m, self, 0x4755bcf);
  }
  int c = ((PMB*)s)->PhotoCountChanged();
  *(int*)(s + 0xea4) = c;
  ((PMB*)s)->UpdatePhotoCountText();
  *(int*)(s + 0x18) = 0;
  ((PMB*)s)->ShowImageThumbnail();
  ((PMB*)s)->UpdatePhotoCountText();
  return true;
}

// @ 0x00634380
void cSPPlayModePhotoBrowser::SetSelectedPhoto(unsigned idx) {
  RBTreeHead* map = &mPhotoTypeMap;
  map->DoNuke(*(RBNode**)((char*)this + 0x74));
  RBNode* anchor = (RBNode*)&map->mAnchor;
  map->mAnchor.right = anchor;
  map->mAnchor.left = anchor;
  map->mAnchor.parent = 0;
  map->mAnchor.color = 0;
  map->mnSize = 0;
  unsigned c = (unsigned)((PMB*)this)->PhotoCountChanged();
  if (c != mPhotoCount) {
    mPhotoCount = c;
    FUN_00634030(this);
  }
  if (idx < mPhotos.size()) {
    mCurrentSelectedPhotoIndex = idx;
    ((PMB*)this)->ShowSendEmailWindow();
  }
}

// @ 0x006343f0
void __fastcall FUN_006343f0(void* self) {
  cSPPlayModePhotoBrowser* b = (cSPPlayModePhotoBrowser*)self;
  void* job = ((PMB*)b)->IsPhotosWriting();
  if (job != 0) {
    while (((cJob*)job)->ContinueJob() == 4) {
    }
  }
  RBTreeHead* map = &b->mPhotoTypeMap;
  map->DoNuke(*(RBNode**)((char*)b + 0x74));
  RBNode* anchor = (RBNode*)&map->mAnchor;
  map->mAnchor.right = anchor;
  map->mAnchor.left = anchor;
  map->mAnchor.parent = 0;
  map->mAnchor.color = 0;
  map->mnSize = 0;
  unsigned c = (unsigned)((PMB*)b)->PhotoCountChanged();
  if (c != b->mPhotoCount) {
    b->mPhotoCount = c;
    FUN_00634030(self);
  }
  unsigned cnt = b->mPhotos.size();
  unsigned idx = b->mCurrentFirstPhotoIndex;
  unsigned nidx = idx + 5;
  b->mCurrentFirstPhotoIndex = nidx;
  if (nidx < cnt) {
    ((PMB*)b)->ClearLoadedPhotos();
    b->ShowImageThumbnail();
    ((PMB*)b)->UpdatePhotoCountText();
  } else {
    b->mCurrentFirstPhotoIndex = idx;
    b->ShowImageThumbnail();
    ((PMB*)b)->UpdatePhotoCountText();
  }
}

// ===========================================================================
// 0x00633ea0: UpdateViewerImage
// ===========================================================================
// @ 0x00633ea0
void __fastcall FUN_00633ea0(void* self)
{
    cSPPlayModePhotoBrowser* b = (cSPPlayModePhotoBrowser*)self;
    void* win = b->mUI->FindEditorUIWindow(0x3ffb8cc);
    if (win == 0)
        return;
    uint32_t idx = b->mCurrentSelectedPhotoIndex;
    uint32_t zeros[3] = { 0, 0, 0 };
    if (idx >= b->mPhotos.size()) {
        FUN_00807bb0(win, zeros, 0);
        return;
    }
    cPlayModePhoto* ph = b->mPhotos.mpBegin[idx];
    if (ph == 0) {
        FUN_00807bb0(win, zeros, 0);
        return;
    }
    if (ph->bIsLoaded == 0) {
        b->ShowThumbnailAsync(&ph->fullKey, ph->photo_guid, 5, win, 1);
        return;
    }
    void* rmgr = FUN_0067dd60();
    void* ras = ((VFn4P)VSLOT(rmgr, 0x20))(rmgr, ph->keyInstance, ph->keyType, 0);
    void* rmgr2 = FUN_0067dd60();
    ((VFnPP)VSLOT(rmgr2, 0x68))(rmgr2, ras);
    void* img = FUN_006300d0(ras);
    if (img != 0)
        ((VFnV)VSLOT(img, 0x00))(img);
    FUN_008068d0(win, img, 0xffffffff);
    if (img != 0)
        ((VFnV)VSLOT(img, 0x04))(img);
}

// ===========================================================================
// 0x00634140: Activate
// ===========================================================================
// @ 0x00634140
bool cSPPlayModePhotoBrowser::Activate(uint32_t msgId, void* arg)
{
    cSPPlayModePhotoBrowser* b = this;
    if (msgId > 0x4755bcf) {
        if (msgId != 0x476e786)
            return false;
        goto msg476e786;
    }
    if (msgId == 0x4755bcf || msgId == 0x41a218d) {
        ++b->mPhotoCount;
        return false;
    }
    if (msgId != 0x4235e47)
        return false;
    {
        uint32_t n = b->mPixelBufCount;
        --b->mWatermarkPixels;
        b->mPixelBufCount = n + 1;
        uint32_t guid = b->mPix[n].guid;
        if (((PMB*)b)->CopyPixelsToRaster((int)n, guid, g_1523310)) {
            ((PMB*)b)->AddPhoto((int)guid, 0x417b3bc);
            ((PMB*)b)->UpdatePhotoCountText();
            b->ShowImageThumbnail();
        }
        if (b->mWatermarkPixels != 0)
            return true;
        b->mUI->SetUIGroupVisible(0x410cf00, 1);
        b->mUI->SetUIGroupVisible(0x41a30c0, 1);
        b->mUI->SetEnabled(0x3a8ede4, 1);
        return true;
    }

msg476e786:
    {
        uint32_t* a = (uint32_t*)arg;
        if (b->mDeactivateCount != a[0x20 / 4])
            return true;
        --b->mWatermarkPixels;
        bool bTenNonZero = (a[0x10 / 4] != 0);
        uint32_t out = a[0x18 / 4];
        uint32_t idx = a[0x08 / 4];
        uint32_t guid = b->mPix[idx].guid;
        bool already = false;
        if (!bTenNonZero && b->mLoadedCount[idx] != guid)
            return true;
        void* ph = ((PMB*)b)->FindPhotoByGuid(guid);
        if (ph != 0)
            already = (((cPlayModePhoto*)ph)->bIsLoaded != 0);
        if (!already) {
            if (!((PMB*)b)->CopyPixelsToRaster((int)idx, guid, g_1523310))
                goto done;
        }
        ((PMB*)b)->AddPhoto((int)guid, 0x417b3bc);
        ((PMB*)b)->UpdatePhotoCountText();
        {
            void* rmgr = FUN_0067dd60();
            void* ras = ((VFn4P)VSLOT(rmgr, 0x20))(rmgr, guid, g_1523310, 0);
            void* rmgr2 = FUN_0067dd60();
            ((VFnPP)VSLOT(rmgr2, 0x68))(rmgr2, ras);
            void* img = FUN_006300d0(ras);
            if (img != 0)
                ((VFnV)VSLOT(img, 0x00))(img);
            FUN_008068d0((void*)out, img, 0);
            if (!already) {
                _InterlockedExchangeAdd((volatile long*)((char*)ras + 8), 1);
                if (bTenNonZero)
                    b->mAsyncHandle = ((PMB*)b)->FindPhotoByGuid(guid);
                else
                    ((PMB*)b)->PushLoaded(guid);
            }
            if (img != 0)
                ((VFnV)VSLOT(img, 0x04))(img);
        }
    done:
        if (b->mWatermarkPixels == 0) {
            b->mUI->SetUIGroupVisible(0x410cf00, 1);
            b->mUI->SetUIGroupVisible(0x41a30c0, 1);
            b->mUI->SetEnabled(0x3a8ede4, 1);
        }
        return true;
    }
}
