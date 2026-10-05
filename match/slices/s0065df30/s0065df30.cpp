// Slice s0065df30: SP::cSPUIFeedEdit grid population / layout helpers plus the
// eastl::vector<AssetInfo> insert cluster.
// UI module: /O2 /MD /Gy /TP /arch:SSE2 (no /EHsc).
#include "types.h"
#include <string.h>

typedef void(__thiscall* FnP)(void*);
typedef void(__thiscall* FnP2)(void*, int, int);
typedef void(__thiscall* FnPi)(void*, int);
typedef void(__thiscall* FnPv)(void*, void*);
typedef void*(__thiscall* FnRetP)(void*);
typedef int(__thiscall* FnRetI)(void*);

static inline void* Vslot(void* o, int off) { return ((void**)(*(void**)o))[off / 4]; }

extern "C" void* EASTL_allocator_allocate(unsigned int size, const char* tag, int a, int b, const char* file, int line);
extern "C" void  EASTL_allocator_deallocate(void* p);
extern "C" void  SPUIHelpers_SetWindowAreaToParent(void* win);
extern "C" char  FUN_009979f0(void* win, uint32_t id);
extern "C" void* CopyImpl(void* first, void* last, void* dest);
extern const wchar_t* g_kFrameName;  // 0x1526954

extern void* g_vt_13fff58;
extern void* g_vt_13fff48;
extern void* g_vt_13ec458;

// ---------------------------------------------------------------------------
// vector<AssetInfo> element type and the EASTL template helpers (relocations).
// ---------------------------------------------------------------------------
struct AssetInfo { uint64_t mnAssetID; uint32_t mnType; void* mpImage; };

struct AssetVec {
    AssetInfo* begin;
    AssetInfo* end;
    AssetInfo* cap;
    AssetInfo* DoInsertValue(AssetInfo* pos, AssetInfo* value);      // 0065df30
    AssetInfo* erase(AssetInfo* first, AssetInfo* last);
    void push_back();                                                // 0065e6d0
};

extern "C" AssetInfo* UninitCopy(AssetInfo* first, AssetInfo* last, AssetInfo* dest); // 0x65cdc0
extern "C" AssetInfo* UninitMove(AssetInfo* first, AssetInfo* last, AssetInfo* dest); // 0x65ce10
extern "C" void  AssignRange(AssetInfo* first, AssetInfo* last, AssetInfo* dest);     // 0x65c750
extern "C" void  DestroyRange(AssetInfo* p);                                          // 0x65cd70

// @ 0x0065df30
__declspec(noinline) AssetInfo* AssetVec::DoInsertValue(AssetInfo* position, AssetInfo* value) {
    if (end != cap) {
        if (position <= value && value < end) value = value + 1;
        if (end != 0) {
            end->mnAssetID = end[-1].mnAssetID;
            end->mnType = end[-1].mnType;
            end->mpImage = end[-1].mpImage;
            if (end->mpImage) (*(FnP)Vslot(end->mpImage, 0))(end->mpImage);
        }
        UninitMove(position, end - 1, end);
        DestroyRange(position);
        end = end + 1;
        return position;
    }
    int n = (int)(end - begin);
    int nc = (n == 0) ? 1 : n * 2;
    AssetInfo* buf = 0;
    if (nc != 0)
        buf = (AssetInfo*)EASTL_allocator_allocate((unsigned)(nc << 4), "Editor", 0, 0,
                                                   (const char*)0x13ebb38, 0xd1);
    if (buf) {
        AssetInfo* p = UninitCopy(begin, position, buf);
        AssignRange(begin, position, buf);
        if (p) {
            *p = *value;
            if (p->mpImage) (*(FnP)Vslot(p->mpImage, 0))(p->mpImage);
        }
        AssetInfo* p2 = UninitCopy(position, end, p + 1);
        AssignRange(position, end, p + 1);
        if (begin && (begin[-1].mnAssetID != 0)) EASTL_allocator_deallocate(begin);
        begin = buf;
        end = p2;
        cap = buf + nc;
    }
    return position;
}

// ---------------------------------------------------------------------------
// scalar helpers / other classes.
// ---------------------------------------------------------------------------
struct cSPUILayout { void* FindWindowByID(uint32_t id, int recursive); };
struct cXHTMLFrameSet {
    void* GetFrame(const wchar_t* name);
    bool  FUN_009979f0(void* win, uint32_t id);
    void  FUN_00997140();
};
struct TextSlot { void Assign(void* p); };

// Minimal UTFWin IWindow: only slot 0x104 is named.
struct IWindow {
    virtual void m00(); virtual void m01(); virtual void m02(); virtual void m03();
    virtual void m04(); virtual void m05(); virtual void m06(); virtual void m07();
    virtual void m08(); virtual void m09(); virtual void m10(); virtual void m11();
    virtual void m12(); virtual void m13(); virtual void m14(); virtual void m15();
    virtual void m16(); virtual void m17(); virtual void m18(); virtual void m19();
    virtual void m20(); virtual void m21(); virtual void m22(); virtual void m23();
    virtual void m24(); virtual void m25(); virtual void m26(); virtual void m27();
    virtual void m28(); virtual void m29(); virtual void m30(); virtual void m31();
    virtual void m32(); virtual void m33(); virtual void m34(); virtual void m35();
    virtual void m36(); virtual void m37(); virtual void m38(); virtual void m39();
    virtual void m40(); virtual void m41(); virtual void m42(); virtual void m43();
    virtual void m44(); virtual void m45(); virtual void m46(); virtual void m47();
    virtual void m48(); virtual void m49(); virtual void m50(); virtual void m51();
    virtual void m52(); virtual void m53(); virtual void m54(); virtual void m55();
    virtual void m56(); virtual void m57(); virtual void m58(); virtual void m59();
    virtual void m60(); virtual void m61(); virtual void m62(); virtual void m63();
    virtual void m64();
    virtual void Slot104(void*);   // 0x104
};
struct HashtableU64 { int count; int* erase(int* out, int* node, int* bucket); };

struct VecPtr {
    void* begin; void* end; void* cap;
    void* erase(void* first, void* last);
};
struct HashSet {
    char pad[0xc];
    int  count;
    void DoFreeNodes(void* a, void* b);
};

struct cSPUIFeedEditAssetView {
    void* vt; void* vt4; void* vt8;      // 0x00
    void* mpLayout;                        // 0x0c
    void* mpParentWin;                     // 0x10
    void* mpRootWin;                       // 0x14
    void* mpButtonWin;                     // 0x18
    void* mpAssetWin;                      // 0x1c
    void* mpBackdropWin;                   // 0x20
    void* mpGlowWin;                       // 0x24
    void* mpEmptyWin;                      // 0x28
    void* mpImage;                         // 0x2c
    int   mnMode;                          // 0x30
    int   pad34;                           // 0x34
    uint64_t mnAssetID;                    // 0x38
    uint32_t mnIndex;                      // 0x40
    uint32_t mTickMask;                    // 0x44
    float mfBlinkStart;                    // 0x48
    void ClearAsset();                     // 0065d050
};

extern "C" void* HashFind64(uint64_t* out, uint64_t* key);      // 0x553510
extern "C" void  HashEraseR(uint64_t* a, uint64_t* key, int f);  // 0x553750

// ---------------------------------------------------------------------------
// SP::cSPUIFeedEdit (retail layout).
// ---------------------------------------------------------------------------
struct cSPUIFeedEdit {
    void* vt;                          // 0x00
    char  pad04[0x10];                 // 0x04
    cSPUILayout* mpLayout;             // 0x14
    char  mFrameSet[0x48];             // 0x18
    char  pad60[0x1c];                 // 0x60
    void* mpWin7c;                     // 0x7c
    void* mpWin80;                     // 0x80
    void* mpWin84;                     // 0x84
    void* mpWin88;                     // 0x88
    int   m8c;                         // 0x8c
    char  mbIsLoaded;                  // 0x90
    char  pad91[3];
    float mfAssetViewWidth;            // 0x94
    float mfAssetViewHeight;           // 0x98
    uint32_t mnAssetColCount;          // 0x9c
    uint32_t mnAssetRowCount;          // 0xa0
    uint32_t mnCurPage;                // 0xa4
    uint32_t mnNumPages;               // 0xa8
    int32_t  mnSelectedIndex;          // 0xac
    void* mViewBegin;                  // 0xb0
    void* mViewEnd;                    // 0xb4
    void* mViewCap;                    // 0xb8
    char  padbc[8];                    // 0xbc
    AssetVec mAssetList;               // 0xc4
    char  padcc[8];                    // 0xcc
    HashSet mNewAssets;                // 0xd8
    HashSet mDeleteAssets;             // 0xf8
    HashSet mExistingAssets;           // 0x118
    char  pad138[0x11];                // 0x138..0x148
    char  mbTransactionActive;         // 0x149
    char  mbNameSet;                   // 0x14a

    void UnloadLayout();               // 0065e0a0
    bool Populate();                   // 0065e110
    bool RemoveAsset(int a, int b);    // 0065e570
    void ResetPanel();                 // 0065e720
    void LoadLayout();                 // 0065e8d0
    void UpdateStrings();              // 0065cb90
    void UpdateEnabledState();         // 0065cae0
    void UpdateGrid();                 // 0065d260
    void UpdateButtons();              // 0065cc50
    bool SetPage(unsigned int page);
    int  GetAssetIndex(int a, int b);  // 0065ccd0
};

// @ 0x0065e0a0
void cSPUIFeedEdit::UnloadLayout() {
    char* p = (char*)this;
    if (!*(char*)(p + 0x90)) return;
    void* a = *(void**)(p + 0x80);
    if (a) { *(void**)(p + 0x80) = 0; (*(FnP)Vslot(a, 4))(a); }
    void* b = *(void**)(p + 0x88);
    if (b) { *(void**)(p + 0x88) = 0; (*(FnP)Vslot(b, 4))(b); }
    ((VecPtr*)(p + 0xb0))->erase(*(void**)(p + 0xb0), *(void**)(p + 0xb4));
    ((cXHTMLFrameSet*)(p + 0x18))->FUN_00997140();
    *(char*)(p + 0x90) = 0;
}

// @ 0x0065e110
bool cSPUIFeedEdit::Populate() {
    char* p = (char*)this;
    ((VecPtr*)(p + 0xb0))->erase(*(void**)(p + 0xb0), *(void**)(p + 0xb4));

    cSPUIFeedEditAssetView* view =
        (cSPUIFeedEditAssetView*)EASTL_allocator_allocate(0x50, "Sporepedia", 0, 0, 0, 0);
    if (view) {
        view->vt4 = &g_vt_13ec458; view->vt8 = 0;
        view->vt = &g_vt_13fff58;  view->vt4 = &g_vt_13fff48;
        view->mpLayout = 0; view->mpParentWin = 0; view->mpRootWin = 0;
        view->mpButtonWin = 0; view->mpAssetWin = 0; view->mpBackdropWin = 0;
        view->mpGlowWin = 0; view->mpEmptyWin = 0; view->mpImage = 0;
        view->mnMode = 0; view->mnAssetID = (uint64_t)-1;
        view->mnIndex = 0xffffffff; view->mTickMask = 0xffffffff; view->mfBlinkStart = 0.0f;
    }
    if (!view) return false;

    (*(FnP)Vslot(view, 0))(view);
    int nViews = (*(int*)(p + 0xb4) - *(int*)(p + 0xb0)) >> 2;
    char c = (*(char(__thiscall*)(void*, uint32_t, int))Vslot(view, 0x1c))(view, *(uint32_t*)(p + 0x88), nViews);
    if (!c) { (*(FnP)Vslot(view, 4))(view); return false; }

    void* root = view->mpRootWin;
    if (root == 0) { (*(FnP)Vslot(view, 4))(view); return false; }
    float* r = (*(float*(__thiscall*)(void*))Vslot(root, 0x38))(root);
    *(float*)(p + 0x94) = r[2] - r[0];
    float* r2 = (*(float*(__thiscall*)(void*))Vslot(root, 0x38))(root);
    *(float*)(p + 0x98) = r2[3] - r2[1];
    float* pr = (*(float*(__thiscall*)(void*))Vslot(*(void**)(p + 0x88), 0x38))(*(void**)(p + 0x88));
    float w = pr[2] - pr[0];
    float* pr2 = (*(float*(__thiscall*)(void*))Vslot(*(void**)(p + 0x88), 0x38))(*(void**)(p + 0x88));
    float h = pr2[3] - pr2[1];
    int cols = (int)(w / *(float*)(p + 0x94));
    *(int*)(p + 0x9c) = cols;
    int rows = (int)(h / *(float*)(p + 0x98));
    *(int*)(p + 0xa0) = rows;
    float fx = (w - (float)cols * *(float*)(p + 0x94)) * 0.5f;
    float fy = (h - (float)rows * *(float*)(p + 0x98)) * 0.5f;
    (*(void(__thiscall*)(void*, float, float))Vslot(root, 0x64))(root, fx, fy);

    int idx = 0;
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            cSPUIFeedEditAssetView* v =
                (cSPUIFeedEditAssetView*)EASTL_allocator_allocate(0x50, "Sporepedia", 0, 0, 0, 0);
            if (v) { v->mpImage = 0; v->mnAssetID = (uint64_t)-1; v->mnIndex = 0xffffffff; v->mTickMask = 0xffffffff; v->mfBlinkStart = 0.0f; }
            if (idx != 0 && v == 0) {
                ((VecPtr*)(p + 0xb0))->erase(*(void**)(p + 0xb0), *(void**)(p + 0xb4));
                return false;
            }
            float px = (float)col * *(float*)(p + 0x94) + fx;
            float py = (float)row * *(float*)(p + 0x98) + fy;
            if (v->mpRootWin)
                (*(void(__thiscall*)(void*, float, float))Vslot(v->mpRootWin, 0x64))(v->mpRootWin, px, py);
            VecPtr* list = (VecPtr*)(p + 0xb0);
            if (list->end < list->cap) {
                void** slot = (void**)list->end;
                list->end = (char*)list->end + 4;
                if (slot) { *slot = v; (*(FnP)Vslot(v, 0))(v); }
            }
            ++idx;
        }
    }
    void** it = (void**)*(void**)(p + 0xb0);
    void** end = (void**)*(void**)(p + 0xb4);
    for (; it != end; ++it)
        (*(void(__thiscall*)(void*, uint32_t))Vslot(*(void**)(p + 0x88), 0xe8))(*(void**)(p + 0x88), ((cSPUIFeedEditAssetView*)*it)->mnIndex);
    return true;
}

// @ 0x0065e570
bool cSPUIFeedEdit::RemoveAsset(int a, int b) {
    char* p = (char*)this;
    uint32_t idx = GetAssetIndex(a, b);
    uint32_t count = (uint32_t)((*(int*)(p + 0xc8) - *(int*)(p + 0xc4)) >> 4);
    if (idx >= count) return false;

    int bucket = *(int*)(*(int*)(p + 0xdc) + *(int*)(p + 0xe0) * 4);
    uint64_t key = (uint64_t)(uint32_t)a | ((uint64_t)(uint32_t)b << 32);
    uint64_t local = 0;
    void* r = HashFind64(&local, &key);
    if (*(int*)r != bucket) {
        local &= 0xffffff00ULL;
        HashEraseR(&local, &key, 0);
    }
    AssetInfo* first = (AssetInfo*)(*(int*)(p + 0xc4) + (idx << 4));
    AssetInfo* e = (AssetInfo*)*(void**)(p + 0xc8);
    if (first + 1 < e) CopyImpl(first + 1, e, first);
    *(int*)(p + 0xc8) -= 0x10;
    AssetInfo* lastp = (AssetInfo*)*(void**)(p + 0xc8);
    if (lastp->mpImage) (*(FnP)Vslot(lastp->mpImage, 4))(lastp->mpImage);
    UpdateEnabledState();
    uint32_t n = (uint32_t)((*(int*)(p + 0xc8) - *(int*)(p + 0xc4)) >> 4);
    uint32_t per = (uint32_t)((*(int*)(p + 0xb4) - *(int*)(p + 0xb0)) >> 2);
    uint32_t pages = n / per;
    *(uint32_t*)(p + 0xa8) = pages;
    if (pages * per != n) *(uint32_t*)(p + 0xa8) = pages + 1;
    UpdateButtons();
    UpdateGrid();
    UpdateStrings();
    return true;
}

// @ 0x0065e6d0  eastl::vector<AssetInfo>::push_back() (no-argument)
void AssetVec::push_back() {
    AssetInfo* e = end;
    if (e < cap) {
        end = e + 1;
        if (e) e->mpImage = 0;
        return;
    }
    AssetInfo tmp;
    tmp.mpImage = 0;
    DoInsertValue(e, &tmp);
    void* x = *(void* volatile*)&tmp.mpImage;
    if (x) (*(FnP)Vslot(x, 4))(x);
}

// @ 0x0065e720
void cSPUIFeedEdit::ResetPanel() {
    char* p = (char*)this;
    mAssetList.erase(mAssetList.begin, mAssetList.end);
    mNewAssets.DoFreeNodes(*(void**)(p + 0xdc), *(void**)(p + 0xe0)); mNewAssets.count = 0;
    mDeleteAssets.DoFreeNodes(*(void**)(p + 0xfc), *(void**)(p + 0x100)); mDeleteAssets.count = 0;
    mExistingAssets.DoFreeNodes(*(void**)(p + 0x11c), *(void**)(p + 0x120)); mExistingAssets.count = 0;

    void** it = (void**)*(void**)(p + 0xb0);
    void** end = (void**)*(void**)(p + 0xb4);
    for (; it != end; ++it) ((cSPUIFeedEditAssetView*)*it)->ClearAsset();

    *(int*)(p + 0xac) = -1;
    SetPage(0);
    *(int*)(p + 0xa4) = 0;

    void* w = *(void**)(p + 0x80);
    void* r = (*(void*(__thiscall*)(void*, uint32_t, int))Vslot(w, 0xf0))(w, 0x58b5d5b, 1);
    if (r) {
        void* q = (*(void*(__thiscall*)(void*, uint32_t))Vslot(r, 0xc))(r, 0xcf428691);
        if (q) {
            (*(void(__thiscall*)(void*, void*, int))Vslot(q, 0x60))(q, (void*)0x13ec468, 0);
            void* q2 = (*(void*(__thiscall*)(void*))Vslot(q, 0x10))(q);
            (*(void(__thiscall*)(void*, int, int))Vslot(q2, 0x7c))(q2, 2, 1);
        }
    }
    w = *(void**)(p + 0x80);
    r = (*(void*(__thiscall*)(void*, uint32_t, int))Vslot(w, 0xf0))(w, 0x58b5d76, 1);
    if (r) {
        void* q = (*(void*(__thiscall*)(void*, uint32_t))Vslot(r, 0xc))(r, 0xcf428691);
        if (q) (*(void(__thiscall*)(void*, void*, int))Vslot(q, 0x60))(q, (void*)0x13ec468, 0);
    }
    *(uint32_t*)(p + 0x8c) = 0;
    *(char*)(p + 0x149) = 0;
    *(char*)(p + 0x14a) = 0;

    uint32_t n = (uint32_t)((*(int*)(p + 0xc8) - *(int*)(p + 0xc4)) >> 4);
    uint32_t per = (uint32_t)((*(int*)(p + 0xb4) - *(int*)(p + 0xb0)) >> 2);
    uint32_t pages = n / per;
    *(uint32_t*)(p + 0xa8) = pages;
    if (pages * per != n) *(uint32_t*)(p + 0xa8) = pages + 1;
    UpdateButtons();
    UpdateStrings();
    UpdateEnabledState();
}

// @ 0x0065e8d0
void cSPUIFeedEdit::LoadLayout() {
    char* p = (char*)this;
    if (*(char*)(p + 0x90)) return;

    {
        void* nw = mpLayout->FindWindowByID(0x58cdf30, 1);
        void* old = *(void**)(p + 0x80);
        if (nw != old) {
            if (nw) (*(FnP)Vslot(nw, 0))(nw);
            *(void**)(p + 0x80) = nw;
            if (old) (*(FnP)Vslot(old, 4))(old);
        }
    }
    void* win = *(void**)(p + 0x80);
    if (win) {
        ((IWindow*)win)->Slot104(p + 8);
        SPUIHelpers_SetWindowAreaToParent(*(void**)(p + 0x80));

        void* nw = mpLayout->FindWindowByID(0x58b6a40, 1);
        void* old = *(void**)(p + 0x88);
        if (nw != old) {
            if (nw) (*(FnP)Vslot(nw, 0))(nw);
            *(void**)(p + 0x88) = nw;
            if (old) (*(FnP)Vslot(old, 4))(old);
        }

        Populate();
        UpdateStrings();
        UpdateEnabledState();

        if (((cXHTMLFrameSet*)(p + 0x18))->FUN_009979f0(*(void**)(p + 0x80), 0x58b69d0)) {
            void* fr = ((cXHTMLFrameSet*)(p + 0x18))->GetFrame(g_kFrameName);
            fr = fr ? (char*)fr + 4 : 0;
            ((TextSlot*)(p + 0x84))->Assign(fr);
        }
        *(char*)(p + 0x90) = 1;
    }
}
