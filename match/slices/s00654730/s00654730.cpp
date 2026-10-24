// slice s00654730: SP::cSPUIAssetGrid focus/scroll/filter update methods (UI
// module, /O2 /MD /Gy /TP /arch:SSE /fp:fast, no /EHsc).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <new>

extern "C" void* AssetBrowser();                       // 0x00401030
extern "C" void* FUN_0065f810(int);                    // 0x0065f810  (vector<0x34-byte item>)
extern "C" void  FUN_00659340(void*);                  // 0x00659340
extern "C" void* FUN_0066a800(int);                    // 0x0066a800
extern "C" void  FUN_0066b0c0(void*);                  // 0x0066b0c0
extern "C" void  FUN_00653ee0(void*, void*, void*);    // 0x00653ee0
extern "C" void  FUN_00650470(void*);                  // 0x00650470
extern "C" char  FUN_00666420(void*);                  // 0x00666420
extern "C" void  cTribeTool_GetTutorialToolPrice(void*, int, int);  // 0x004e1c30
extern "C" void  Stopwatch_GetElapsedTime(void*, void*);  // 0x0093a5e0
extern "C" void  SPUIHelpers_UpdateMouseFocus(int);    // 0x00804f50

struct U8Vec {
    unsigned* mpBegin;
    unsigned* mpEnd;
    unsigned* mpCapacity;
};

// @ 0x00654730  SP::cSPUIAssetGrid::SetFeedFilter-like update (PARTIAL skeleton:
// the 1477-byte body drives many UI sub-widgets).
void FUN_00654730(void* self, void* filter) {
    char* s = (char*)self;
    *(int*)(s + 0x1b4) = 0;
    void* old = *(void**)(s + 0x19c);
    if (filter != old) {
        if (filter)
            (*(void(__thiscall**)(void*))((char*)*(void**)filter))(filter);
        *(void**)(s + 0x19c) = filter;
        if (old)
            (*(void(__thiscall**)(void*))((char*)*(void**)old + 4))(old);
    }
    s[0x1e4] = 0;
    s[0x1e5] = 0;
    void* p = *(void**)(s + 0x1c0);
    if (p) {
        *(void**)(s + 0x1c0) = 0;
        (*(void(__thiscall**)(void*))((char*)*(void**)p + 4))(p);
    }
    *(int*)(s + 0x1c4) = 0;
    *(int*)(s + 0x1c8) = 0;
    *(int*)(s + 0x1cc) = 0;
    if (filter && FUN_00666420(filter)) {
        void* w0 = *(void**)(s + 0x28);
        (*(void(__thiscall**)(void*, int, int))((char*)*(void**)w0 + 0x7c))(w0, 1, 1);
        void* w1 = *(void**)(s + 0x48);
        (*(void(__thiscall**)(void*, int, int))((char*)*(void**)w1 + 0x7c))(w1, 1, 1);
    }
}

// @ 0x00654d00  SP::cSPUIAssetGrid::Reset/Refresh
void FUN_00654d00(void* self) {
    char* s = (char*)self;
    s[0x1e8] = 0;
    void* p = *(void**)(s + 0xfc);
    if (p) {
        void* q = *(void**)((char*)p + 0x10);
        if (q)
            FUN_00659340(q);
        *(void**)(s + 0xfc) = 0;
    }
    void* item = FUN_0066a800(*(int*)(s + 0x1a0));
    s[0x100] = 0;
    if (item) {
        (*(void(__thiscall**)(void*))((char*)*(void**)item + 4))(item);
        U8Vec vec;
        vec.mpBegin = 0; vec.mpEnd = 0; vec.mpCapacity = 0;
        if (*(void**)(s + 0xe0)) {
            void* list = FUN_0065f810(0);
            char* begin = *(char**)list;
            char* end = *(char**)((char*)list + 4);
            while (begin != end) {
                unsigned v = *(unsigned*)begin;
                if (vec.mpEnd < vec.mpCapacity) {
                    *vec.mpEnd++ = v;
                } else {
                    // vector<unsigned>::DoInsertValue(&vec, &v): grow
                    unsigned n = (unsigned)(vec.mpEnd - vec.mpBegin);
                    unsigned cap = n ? n * 2 : 1;
                    unsigned* nd = (unsigned*)::operator new(cap * 4);
                    for (unsigned i = 0; i < n; ++i) nd[i] = vec.mpBegin[i];
                    nd[n] = v;
                    if (vec.mpBegin) ::operator delete(vec.mpBegin);
                    vec.mpBegin = nd;
                    vec.mpEnd = nd + n + 1;
                    vec.mpCapacity = nd + cap;
                }
                begin += 0x34;
            }
        }
        FUN_0066b0c0(&vec);
        FUN_00653ee0(*(void**)(s + 0xe8), *(void**)(s + 0xec), item);
        if (vec.mpBegin && ((unsigned*)vec.mpBegin)[-1])
            ::operator delete(vec.mpBegin);
    }
    FUN_00650470(self);
    *(int*)(s + 0x198) = 1;
    if (item)
        (*(void(__thiscall**)(void*))((char*)*(void**)item + 8))(item);
}

struct GridEntry {
    char pad[0x18];
    float mPosition;   // +0x18
};

struct ItemSizeProvider {
    virtual void V00();
    virtual void V04();
    virtual void V08();
    virtual void V0c();
    virtual void V10();
    virtual void V14();
    virtual void V18();
    virtual void V1c();
    virtual void V20();
    virtual void V24();
    virtual void V28();
    virtual void V2c();
    virtual void V30();
    virtual void V34();
    virtual void V38();
    virtual void V3c();
    virtual int GetSize();   // +0x40
};

struct GridSource {
    char pad[0x20];
    ItemSizeProvider* mSizeProvider;   // +0x20
};

struct cSPUIAssetGrid {
    char pad108[0x108];
    float mItemWidth;         // +0x108
    char pad10c[0x1c];
    float mViewWidth;         // +0x128
    char pad12c[0x54];
    float mScroll;            // +0x180
    char pad184[4];
    float mMaxScroll;         // +0x188
    GridSource* mGridSource;  // +0x18c
    bool mFocusFlag;          // +0x190
    char pad191[0x55];
    bool mNeedsRebuild;       // +0x1e6
    char pad1e7[1];
    bool mNeedsReset;         // +0x1e8
    void* Find(uint32_t id);  // 0x006505d0
    void Rebuild();           // 0x006553b0
    void Refresh();           // 0x00654d00
    void ScrollTo(void* item); // 0x00654e20
};

// @ 0x00654e20  SP::cSPUIAssetGrid::ScrollTo(item)
void cSPUIAssetGrid::ScrollTo(void* item) {
    if (!item)
        return;
    if (mNeedsRebuild)
        Rebuild();
    if (mNeedsReset)
        Refresh();
    GridEntry* found = (GridEntry*)Find((uint32_t)(uintptr_t)item);
    if (!found)
        return;
    float itemPos = found->mPosition;
    float cur = mScroll;
    int size = mGridSource->mSizeProvider->GetSize();
    float limit = ((float)size + cur) - mViewWidth;
    if (limit < cur)
        limit = cur;
    if (cur <= itemPos) {
        if (limit < mItemWidth + itemPos)
            mScroll = (mItemWidth + itemPos - (float)size) + mViewWidth;
    } else {
        mScroll = itemPos;
    }
    float v = mScroll;
    if (v <= 0.0f)
        v = 0.0f;
    if (mMaxScroll <= v)
        v = mMaxScroll;
    mScroll = v;
    mFocusFlag = true;
    SPUIHelpers_UpdateMouseFocus(1);
}

// @ 0x00654f50  SP::cSPUIAssetGrid::OnSelect/commit (PARTIAL skeleton: 1117-byte
// body with tutorial-timer / selection propagation).
void FUN_00654f50(void* self, void* a, int b) {
    char* s = (char*)self;
    if (s[0x1e4]) {
        s[0x1e5] = 0;
        void* p = *(void**)(s + 0x1c0);
        (void)p; (void)a; (void)b;
    } else {
        AssetBrowser();
        AssetBrowser();
        AssetBrowser();
        Stopwatch_GetElapsedTime(s + 0x168, 0);
    }
}
