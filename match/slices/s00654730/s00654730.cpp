// slice s00654730: SP::cSPUIAssetGrid focus/scroll/filter update methods (UI
// module, /O2 /MD /Gy /TP /arch:SSE /fp:fast, no /EHsc).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <new>
#include <intrin.h>

extern "C" __declspec(dllimport) int __stdcall QueryPerformanceCounter(long long* out);   // kernel32
// The engine's one-argument global operator new (used by the entry-vector growth).
void* operator new(unsigned int size);   // 0x00f47380

extern "C" void* AssetBrowser();                       // 0x00401030
extern "C" void* FUN_0065f810(int);                    // 0x0065f810  (vector<0x34-byte item>)
extern "C" void  FUN_00659340(void*);                  // 0x00659340
extern "C" void* FUN_0066a800(int);                    // 0x0066a800
extern "C" void  FUN_0066b0c0(void*);                  // 0x0066b0c0
extern "C" void  FUN_00653ee0(void*, void*, void*);    // 0x00653ee0
extern "C" void  FUN_00650470(void*);                  // 0x00650470
extern "C" char  FUN_00666420(void*);                  // 0x00666420
extern "C" int   cTribeTool_GetTutorialToolPrice(void*, int, int);  // 0x004e1c30
extern "C" void  Stopwatch_GetElapsedTime(void*, void*);  // 0x0093a5e0
extern "C" void  SPUIHelpers_UpdateMouseFocus(int);    // 0x00804f50
extern "C" void* RBTreeIncrement(void* node);          // 0x00921580
extern "C" void  FUN_0064f890(void* dst, void* end, void* src);  // 0x0064f890 (cdecl)
extern "C" void  FUN_00652b00(void* vecEnd, char* node);  // 0x00652b00 (cdecl)
extern "C" bool  FUN_00668be0(void* item, void* str);     // 0x00668be0 (cdecl)
extern "C" void  FUN_0064ecc0();                          // 0x0064ecc0 (cdecl)
extern "C" void  FUN_006524a0();                          // 0x006524a0 (cdecl)
extern "C" void  FUN_00654490(int n);                     // 0x00654490 (cdecl)
extern "C" void  FUN_0064f3b0(void* out, void* src);      // 0x0064f3b0 (cdecl, ctor-into-slot)
extern "C" void  FUN_006535b0(void* vecEnd, void* src);   // 0x006535b0 (cdecl)
extern "C" void* FUN_006462b0(void* browser, void* item); // 0x006462b0 (thiscall)
// cSPUIAssetGrid tail updates.
struct AssetGridTail {
    void UpdateScrolling(int flag);   // 0x0064fa20
    void UpdateAll();                 // 0x0064ecc0
    void UpdateScrollRegion();        // 0x006524a0
};

// cSPUIAssetGrid / cSPUIAssetBrowser helper members (thiscall; ecx = receiver).
struct U8Vec;
struct GridHelper {
    void Reset0x644040(void* arg);   // 0x00644040
    bool IsEmpty(void);              // 0x00642910
    void Release0x64e7a0();          // 0x0064e7a0
    void Clear();                    // 0x006543a0
    void MergeEntries(void* begin, void* end, void* src);  // 0x006545d0 (cdecl)
    void Update0x650470();           // 0x00650470
    void Collect0x659340();          // 0x00659340
    void* FeedItems(void* flag);     // 0x0065f810
    bool IsKnownID();                // 0x00666420
};
// eastl::vector<SP::cSPAssetGridEntry, sp_vector_allocator> (at this+0xe8).
struct EntryVec {
    void* mpBegin;                   // +0
    void* mpEnd;                     // +4
    void  InsertAt(void* pos, void* value, void* out);   // 0x00653de0 (thiscall)
    void* Erase(void* it);                                // 0x006534c0 (thiscall)
};
// cSPAssetGridEntry ctor helpers (thiscall on the vector at this+0xe8).
struct GridEntries {
    void* mpBegin;                   // +0
    void* mpEnd;                     // +4
    void* mpCapacity;                // +8
    void* ConstructInto(void* slot, void* src);   // 0x0064f3b0
    void* DoInsertValue(void* slot, void* src);   // 0x006535b0
    void  InsertEntry(void* pos, int count);      // 0x00652b00
    void  Reserve(int n);                         // 0x00654490
};
struct StopwatchHelper {
    long long GetElapsedTime();      // 0x0093a5e0
    void Restart();                  // 0x00571e80
};

struct U8Vec {
    unsigned* mpBegin;
    unsigned* mpEnd;
    unsigned* mpCapacity;
};

// The two target methods are __thiscall (ecx = the grid). Declared as members of an
// early struct so the receiver travels in ecx, matching retail.
struct AssetGrid {
    void UpdateAssets(void* filter, void* feedItem);  // 0x00654730
    void OnSelectCommit(void* item, void* filter);  // 0x00654f50
};

// @ 0x00654730  UpdateAssets  SP::cSPUIAssetGrid::UpdateAssets(FilterItem* filter, cSPUIFeedListItem* feedItem)
// Rebuilds the asset grid for a newly selected feed filter. Resets the load counter (+0x1b4),
// swaps the active filter (+0x19c) with AddRef/Release, clears the pending-selection state
// (+0x1e4/+0x1e5/+0x1c0) and the three scratch fields (+0x1c4/+0x1c8/+0x1cc), toggles the
// header/background widgets' visibility, releases the previous feed item (+0xfc), then walks
// the filter's sorted sub-item list (+0x4c) building grid entries (+0xe8) and finally updates
// scrolling/scroll-region and stamps the frame timer.
void AssetGrid::UpdateAssets(void* filter, void* feedItem) {
    void* self = this;
    char* s = (char*)self;

    // 0x1b4 = load counter
    *(int*)(s + 0x1b4) = 0;

    // --- swap the active filter (+0x19c) with AddRef/Release ---
    void* old = *(void**)(s + 0x19c);
    if (filter != old) {
        if (filter)
            (*(void(__thiscall**)(void*))((char*)*(void**)filter))(filter);
        *(void**)(s + 0x19c) = filter;
        if (old)
            (*(void(__thiscall**)(void*))((char*)*(void**)old + 4))(old);
    }

    // --- clear pending-selection state ---
    s[0x1e4] = 0;
    s[0x1e5] = 0;
    void* pend = *(void**)(s + 0x1c0);
    if (pend) {
        *(void**)(s + 0x1c0) = 0;
        (*(void(__thiscall**)(void*))((char*)*(void**)pend + 4))(pend);
    }
    *(int*)(s + 0x1c4) = 0;
    *(int*)(s + 0x1c8) = 0;
    *(int*)(s + 0x1cc) = 0;

    // --- primary widget (+0x28) and secondary (+0x48) visibility; header bar (+0x4c) ---
    void* curFilter = *(void**)(s + 0x19c);
    bool known = curFilter != 0 && ((GridHelper*)curFilter)->IsKnownID();
    if (known) {
        void* w0 = *(void**)(s + 0x28);
        (*(void(__thiscall**)(void*, int, int))((char*)*(void**)w0 + 0x7c))(w0, 1, 1);
        void* w1 = *(void**)(s + 0x48);
        (*(void(__thiscall**)(void*, int, int))((char*)*(void**)w1 + 0x7c))(w1, 1, 1);
    } else {
        void* w0 = *(void**)(s + 0x28);
        (*(void(__thiscall**)(void*, int, int))((char*)*(void**)w0 + 0x7c))(w0, 1, 0);
        void* w1 = *(void**)(s + 0x48);
        (*(void(__thiscall**)(void*, int, int))((char*)*(void**)w1 + 0x7c))(w1, 1, 0);
    }
    {
        void* w2 = *(void**)(s + 0x4c);
        (*(void(__thiscall**)(void*, int, int))((char*)*(void**)w2 + 0x7c))(w2, 1, known ? 1 : 0);
    }

    // --- feed-header widget (+0x5c): visible only when the stored filter + item are both live ---
    {
        void* w3 = *(void**)(s + 0x5c);
        if (w3) {
            int vis;
            if (curFilter == 0)
                vis = s[0x1b8];
            else
                vis = (s[0x1b8] && *((char*)curFilter + 0x16)) ? 1 : 0;
            (*(void(__thiscall**)(void*, int, int))((char*)*(void**)w3 + 0x7c))(w3, 1, vis);
        }
    }

    // --- release the previous feed item (+0xfc) and its sub-object at +0x10 ---
    {
        void* it = *(void**)(s + 0xfc);
        if (it) {
            void* sub = *(void**)((char*)it + 0x10);
            if (sub)
                ((GridHelper*)sub)->Collect0x659340();
            *(void**)(s + 0xfc) = 0;
        }
    }
    s[0x100] = 0;

    // --- if the header widget (+0x2c) and feedItem are both live, rebuild the entry vector ---
    if (*(void**)(s + 0x2c) != 0 && feedItem != 0) {
        ((GridHelper*)self)->Clear();
        void* f2 = *(void**)(s + 0x19c);
        bool want = (f2 == 0) ? (s[0x1b8] != 0)
                              : (s[0x1b8] != 0 && *((char*)f2 + 0x16) != 0);
        if (want) {
            GridEntries* vec = (GridEntries*)(s + 0xe8);
            if (vec->mpEnd < vec->mpCapacity) {
                void* slot = vec->mpEnd;
                vec->mpEnd = (char*)slot + 0x20;
                FUN_0064f3b0(slot, /*placeholder entry*/ 0);
            } else {
                FUN_006535b0(vec->mpEnd, 0);
            }
        }
        // second (empty) placeholder entry
        {
            GridEntries* vec = (GridEntries*)(s + 0xe8);
            if (vec->mpEnd < vec->mpCapacity) {
                void* slot = vec->mpEnd;
                vec->mpEnd = (char*)slot + 0x20;
                FUN_0064f3b0(slot, 0);
            } else {
                FUN_006535b0(vec->mpEnd, 0);
            }
        }
        {
            GridEntries* vec = (GridEntries*)(s + 0xe8);
            int count = (int)(((char*)vec->mpEnd - (char*)vec->mpBegin) >> 5);
            FUN_00652b00(vec->mpEnd, (char*)feedItem + 0x5c + count);
        }

        // --- merge the feed item's sorted sub-item list (+0x4c) into the entry vector ---
        char* subEnd = (char*)feedItem + 0x4c;
        char* node = *(char**)((char*)feedItem + 0x50);
        if (node != subEnd) {
            do {
                char* sub = *(char**)(node + 0x1c);   // the sub-object
                if ((*(char(__thiscall**)(char*))((char*)*(void**)sub + 0x2c))(sub)) {
                    void* browser = AssetBrowser();
                    void* entry = FUN_006462b0(browser, sub);
                    (*(void(__thiscall**)(void*))((char*)*(void**)entry))(entry);   // AddRef
                    {
                        // build a cSPAssetGridEntry from {sub keys, sub, entry} then insert
                        GridEntries* vec = (GridEntries*)(s + 0xe8);
                        if (vec->mpEnd < vec->mpCapacity) {
                            void* slot = vec->mpEnd;
                            vec->mpEnd = (char*)slot + 0x20;
                            FUN_0064f3b0(slot, 0);
                        } else {
                            FUN_006535b0(vec->mpEnd, 0);
                        }
                    }
                } else {
                    *(int*)(s + 0x1b4) += 1;
                }
                {
                    char* next = (char*)RBTreeIncrement(node);
                    char* stop = (char*)feedItem + 0x4c + 0x4c;
                    node = next;
                    if (node == stop) break;
                }
            } while (true);
        }

        // --- after the walk: reserve or arm the pending selection ---
        if (((GridHelper*)feedItem)->IsEmpty()) {
            FUN_00654490(-1);
        } else {
            s[0x1e4] = 1;
            void* oldPend = *(void**)(s + 0x1c0);
            if (feedItem != oldPend) {
                (*(void(__thiscall**)(void*))((char*)*(void**)feedItem))(feedItem);
                *(void**)(s + 0x1c0) = feedItem;
                if (oldPend)
                    (*(void(__thiscall**)(void*))((char*)*(void**)oldPend + 4))(oldPend);
            }
        }
    }

    // --- header message string (eastl::gEmptyString16 ...) then show on the feed-header sub-widget
    {
        void* headerWidget = *(void**)(s + 0x50);
        if (headerWidget && *(void**)(s + 0x19c) != 0) {
            if (FUN_00668be0(headerWidget, (void*)/*16-byte key*/ 0)) {
                void* w = *(void**)(s + 0x50);
                (*(void(__thiscall**)(void*, void*))((char*)*(void**)w + 0x80))(w, 0);
            }
        }
    }

    // --- tail updates ---
    s[0x1e6] = 1;
    s[0x1e7] = 1;
    ((AssetGridTail*)self)->UpdateScrolling(0);
    ((AssetGridTail*)self)->UpdateAll();
    ((GridHelper*)self)->Update0x650470();
    ((AssetGridTail*)self)->UpdateScrollRegion();

    *(int*)(s + 0x194) = 1;
    void* f = *(void**)(s + 0x19c);
    bool render;
    if (f == 0)
        render = (s[0x1b8] != 0) && (*(void**)(s + 0xe8) != *(void**)(s + 0xec));
    else
        render = (s[0x1b8] != 0) && (*((char*)f + 0x16) != 0);
    if (render && *(void**)(s + 0xe8) != *(void**)(s + 0xec) &&
        *(char*)(*(char**)(s + 0xe8) + 0x1c) != 0) {
        int pad = 5;
        void* ab = AssetBrowser();
        if (ab && ((int*)AssetBrowser())[6] != 0) {
            void* ab2 = AssetBrowser();
            pad = cTribeTool_GetTutorialToolPrice((void*)((int*)ab2)[6], 0x86cf5fc5, 5);
        }
        void* w = *(void**)(s + 0x5c);
        if (w) {
            char* e0 = *(char**)(s + 0xe8);
            (*(void(__thiscall**)(void*, float, float))((char*)*(void**)w + 0x64))(
                w, *(float*)(e0 + 0x14) + (float)pad, *(float*)(e0 + 0x18) + (float)pad);
            (*(void(__thiscall**)(void*, float, float))((char*)*(void**)w + 0x68))(
                w, *(float*)(s + 0x104) - (float)(pad * 2),
                   *(float*)(s + 0x108) - (float)(pad * 2));
        }
    }

    // --- frame timer stamp (+0x160 gate) ---
    {
        unsigned long long stamp;
        if (*(int*)(s + 0x160) == 1) {
            stamp = __rdtsc();
        } else {
            long long pc = 0;
            QueryPerformanceCounter(&pc);
            stamp = (unsigned long long)pc;
        }
        *(int*)(s + 0x150) = (int)(stamp & 0xffffffffu);
        *(int*)(s + 0x154) = (int)(stamp >> 32);
    }
    *(int*)(s + 0x158) = 0;
    *(int*)(s + 0x15c) = 0;
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

// @ 0x00654f50  OnSelectCommit  SP::cSPUIAssetGrid::OnSelectCommit(item, filter)
// Commits a feed-selection. If the pending "in-select" flag (this+0x1e4) is set, just swap the
// pending item at +0x1c0 and return. Otherwise gate on the tutorial timer: when the stopwatch at
// +0x168 has elapsed *past* the per-tool price, run the commit body; otherwise arm the pending
// swap (+0x1e5=1) and return early. The commit body releases +0x1c0, resets the item, and -- when
// the item's filter still matches +0x19c -- merges the item's sorted entry list (+0x4c) into the
// grid's own sorted entry vector (+0xe8/+0xec), dropping entries that fall out of order.
void AssetGrid::OnSelectCommit(void* item, void* filter) {
    void* self = this;
    char* s = (char*)self;

    if (s[0x1e4]) {
        s[0x1e5] = 0;
        void* old = *(void**)(s + 0x1c0);
        if (item != old) {
            if (item)
                (*(void(__thiscall**)(void*))((char*)*(void**)item))(item);
            *(void**)(s + 0x1c0) = item;
            if (old)
                (*(void(__thiscall**)(void*))((char*)*(void**)old + 4))(old);
        }
        return;
    }

    long long price = 2000;
    void* ab = AssetBrowser();
    if (ab && ((int*)AssetBrowser())[6] != 0) {
        void* ab2 = AssetBrowser();
        price = (long long)(int)(uintptr_t)cTribeTool_GetTutorialToolPrice((void*)((int*)ab2)[6], 0x1df98401, 2000);
    }
    unsigned long long elapsed = (unsigned long long)((StopwatchHelper*)(s + 0x168))->GetElapsedTime();
    if ((unsigned long long)price >= elapsed) {
        // stopwatch has NOT out-run the price: arm the pending swap and leave.
        s[0x1e5] = 1;
        void* old = *(void**)(s + 0x1c0);
        if (item != old) {
            if (item)
                (*(void(__thiscall**)(void*))((char*)*(void**)item))(item);
            *(void**)(s + 0x1c0) = item;
            if (old)
                (*(void(__thiscall**)(void*))((char*)*(void**)old + 4))(old);
        }
        return;
    }

    // Commit body.
    s[0x1e5] = 0;
    ((GridHelper*)self)->Release0x64e7a0();
    ((GridHelper*)item)->Reset0x644040(0);
    if (!((GridHelper*)item)->IsEmpty()) {
        s[0x1e5] = 1;
        *(void**)(s + 0x1c0) = item;   // AutoRefCount<IWinText>::operator=
    }
    if (filter == *(void**)(s + 0x19c) && item) {
        ((GridHelper*)self)->Release0x64e7a0();
        ((GridHelper*)self)->MergeEntries(*(void**)(s + 0xe8), *(void**)(s + 0xec), item);
        // Merge the item's sorted list (rbtree anchored at item+0x4c) into the grid's
        // entry vector at +0xe8. Each entry is 0x20 bytes; ordering compares the
        // 64-bit pair {[+0x10],[+0x14]} (then a third key at the tail).
        char* itemEnd = (char*)item + 0x4c;
        void* node = *(void**)((char*)item + 0x50);   // first node
        char* out = *(char**)(s + 0xe8);
        while (node != itemEnd) {
            void* cur = node;
            if (out == *(char**)(s + 0xec)) {
                // append: build a temporary entry then insert at end
                EntryVec* vec = (EntryVec*)(s + 0xe8);
                vec->InsertAt(out, cur, &out);
                node = RBTreeIncrement(node);
                continue;
            }
            // compare {cur[0x10],cur[0x14],cur[0x18]} against the queued out entry
            unsigned k0 = *(unsigned*)((char*)cur + 0x10);
            unsigned k1 = *(unsigned*)((char*)cur + 0x14);
            unsigned k2 = *(unsigned*)((char*)cur + 0x18);
            unsigned c0 = *(unsigned*)(out + 0);
            unsigned c1 = *(unsigned*)(out + 4);
            unsigned c2 = *(unsigned*)(out + 8);
            bool curLess = (k0 < c0) || (k0 == c0 && (k2 < c2 || (k2 == c2 && k1 < c1)));
            if (!curLess) {
                bool curMore = (k0 > c0) || (k0 == c0 && (k2 > c2 || (k2 == c2 && k1 > c1)));
                if (curMore) {
                    out += 0x20;
                    node = RBTreeIncrement(node);
                }
            } else {
                out += 0x20;
                node = RBTreeIncrement(node);
            }
        }
        // Drop trailing grid entries that no longer sort before the item's end.
        while (out != *(char**)(s + 0xec)) {
            EntryVec* vec = (EntryVec*)(s + 0xe8);
            out = (char*)vec->Erase(out);
            *(int*)(s + 0x198) = 1;
        }
    }

    s[0x1e6] = 1;
    s[0x1e7] = 0;
    ((GridHelper*)self)->Update0x650470();
    {
        float v = *(float*)(s + 0x180);
        if (v < 0.0f) v = 0.0f;
        if (*(float*)(s + 0x188) < v) v = *(float*)(s + 0x188);
        *(float*)(s + 0x180) = v;
    }
    ((StopwatchHelper*)(s + 0x168))->Restart();
}
