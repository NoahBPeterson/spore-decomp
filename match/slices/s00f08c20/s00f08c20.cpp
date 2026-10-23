// Slice s00f08c20 - Spore "scenario task list" UI helpers (the panel set driven by the
// g_16c7d90 / g_16c7d94 / g_16c7d98 UI state blocks, plus the EASTL hashtable primitives the
// task-entry lists are built on).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE /fp:fast (slice s00f07c90, same module).
//
// The window interface and the UI state block are copied from the neighbouring slice
// s00f07c90 (same class); the hashtable helpers 0xf09090/0xf09170/0xf092b0 are the
// EASTL clear/erase/insert primitives reproduced here so the call sites of 0xf094d0 /
// 0xf09580 / 0xf096c0 / 0xf09c90 come out right.
#include "types.h"
#include <math.h>

typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;

// ---------------------------------------------------------------------------
// UTFWin window interface: vtable slots by byte offset (matches slice s00f07c90).
// ---------------------------------------------------------------------------
struct IWin {
    virtual void w00();
    virtual void AddRef();                    // 0x04
    virtual void Release();                   // 0x08
    virtual void w0c();
    virtual void w10();
    virtual void w14();
    virtual void w18();
    virtual void w1c();
    virtual void w20();
    virtual void w24();
    virtual void w28();
    virtual void w2c();
    virtual void w30();
    virtual float* GetArea();                 // 0x34
    virtual float* GetRect();                 // 0x38
    virtual void w3c();
    virtual void w40();
    virtual void w44();
    virtual IWin* GetActiveWindow(int a);     // 0x48
    virtual void w4c();
    virtual void w50();
    virtual void w54();
    virtual void w58();
    virtual void w5c();
    virtual void w60();
    virtual void SetPos(float x, float y);    // 0x64
    virtual void w68();
    virtual void w6c();
    virtual void w70();
    virtual void w74();
    virtual void w78();
    virtual void SetFlags(int a, int b);      // 0x7c
    virtual void w80();
    virtual void w84();
    virtual void w88();
    virtual void w8c();
    virtual void w90();
    virtual void w94();
    virtual void w98();
    virtual void w9c();
    virtual void wa0();
    virtual void wa4();
    virtual void wa8();
    virtual void wac();
    virtual void wb0();
    virtual void wb4();
    virtual IWin* GetWindow(uint id);          // 0xb8
    virtual void IAddRef();                    // 0xbc
    virtual void IRelease();                   // 0xc0
    virtual void wc4();
    virtual void wc8();
    virtual void wcc();
    virtual void wd0();
    virtual void wd4();
    virtual void wd8(void* arg);               // 0xd8
    virtual void wdc();
    virtual void we0();
    virtual void we4();
    virtual void we8(void* p);
    virtual void wec();
    virtual void wf0();
    virtual void wf4();
    virtual char wf8(void* arg);               // 0xf8
    virtual void wfc();
    virtual void w100();
    virtual void w104(void* arg);              // 0x104
};

// cSPUILayout window manager (subset used here).
struct Layout {
    IWin* FindWindowByID(uint id, int recurse);          // 0xf105b0
    char  Init(const void* key, int b, uint c);          // 0xf120d0
    char  Init(const wchar_t* name, int b, int c, uint d);
    char  SetVisibility(int v);                          // 0xf10590
    char  Shutdown(int b);                               // 0xf11ad0
};

// SP::cString (0x14-byte EA string) and the wide-string assign helper.
struct CStr {
    char b[0x14];
    CStr& operator=(const CStr&);
};
struct WStr {
    void assign(int a, int b);                            // 0x423650
};

struct Animator {
    void ClearAll();                                      // 0xf07f8f00
};

// ---------------------------------------------------------------------------
// The 0x15ad538 / 0x15ad558 EASTL hashtable shape: +4 bucket array, +8 bucket
// count, +0xc element count, +0x10 node allocator.
// ---------------------------------------------------------------------------
struct NodeAlloc {
    void alloc(void* out, uint a, uint b, int c);         // 0xf0921440
};

struct HashTbl {
    void*      f00;          // +0x00
    IWin**     buckets;      // +0x04
    uint       bucketCount;  // +0x08
    uint       size;         // +0x0c
    NodeAlloc  na;           // +0x10

    void  find(void* out, const void* key);               // 0xf0645ed0 / 0xf0685f30
    void  insert(void* retval, const void* value, uint unused);   // 0x00f092b0
    void  insertOther(void* out, void* value, int flag);  // 0x00f091f0
    void  rehash(uint n);                                 // 0x00ad8020
    void  clearBuckets(IWin** buckets, uint n);           // 0x00f09090
    void  clearBuckets2(IWin** buckets, uint n);          // 0x0093dc70 (other slice)
    void* erase(void* out, void* node, void* bucketPtr);  // 0x00f09170
    int*  FindOrInsertTextStyle(int* key);                // 0x00f09bf0
    int   TaskGroupLookup(int* key);                      // 0x00f09c90
};

// ---------------------------------------------------------------------------
// UI state blocks.
// ---------------------------------------------------------------------------
struct RecDB;
struct Ctx;

struct Entry { IWin* win; int idx; int savedA; int savedB; };   // 0x10 bytes

struct UIState {
    Layout* layout;               // +0x00
    Ctx*    ctx;                  // +0x04
    char*   owner;                // +0x08
    int     mode;                 // +0x0c
    Entry   entries[5];           // +0x10 .. +0x60
    IWin*   field60;              // +0x60
    int     field64;              // +0x64
    int     f68;                  // +0x68
    int     f6c;                  // +0x6c
    int     field70;              // +0x70
    IWin*   listWin;              // +0x74
    float   cursorX;              // +0x78
    float   cursorY;              // +0x7c
    void*   tool;                 // +0x80
};

extern UIState* g_16c7d90;        // 0x16c7d90
extern UIState* g_16c7d94;        // 0x16c7d94
extern UIState* g_16c7d98;        // 0x16c7d98
extern UIState* g_16c7d88;        // 0x16c7d88

struct Global7aa4 { char pad[0x14]; void* ui14; char pad2[0x60]; void* day78; };
extern Global7aa4* g_16c7aa4;     // 0x16c7aa4

// Per-panel slot array 0x16c7df0 .. 0x16c7f30 (10 slots of 0x20 bytes).
struct PBEntry {
    Layout* layout;               // +0x00
    IWin*   win;                  // +0x04
    float   startTime;            // +0x08
    int     record;               // +0x0c
    char    active;               // +0x10
    char    pad11[3];
    int     day;                  // +0x14
    float   height;               // +0x18
    int     sel;                  // +0x1c
};
extern PBEntry g_pbEntries[10];   // 0x16c7df0
extern char    g_animator;        // 0x16c7f30 (cSPUIAnimator)

extern HashTbl g_hash538;         // 0x15ad538
extern HashTbl g_hash558;         // 0x15ad558

// ---------------------------------------------------------------------------
// External functions.
// ---------------------------------------------------------------------------
extern "C" void* EAAllocate(uint size, const char* name, int a, int b, uint allocator, int line);
extern "C" void  OperatorDelete(void* p);                                  // ??
extern "C" void* SP_WindowManager();                                       // 0x67caa0
extern "C" char  FUN_008053b0();                                           // IsSomething
extern "C" char  CreditsTabInit(int a, uint id, void** out);               // 0x805310
extern "C" void  FUN_00f07c10(int* base, void* ctx, int idx, void* a5, void* a6);
extern "C" void* FUN_00f07ae0(int* a, int* b, int* c, void* d);
extern "C" void  FUN_00f090e0(int* a, int* b, void* c);
extern "C" void  FUN_00f09120(int* a, int* b, void* c);
extern "C" void  FUN_00ad8020();                                           // (unused placeholder)
extern "C" void  FUN_00b18530();
extern "C" void  FUN_00f19e70(int a, void* out, void* out2);
extern "C" void* FUN_00ae6760(int a);
extern "C" void* FUN_00b6d160(int a, int b);
extern "C" void  FUN_00de5df0(void* out, void* a, uint b);
extern "C" void  FUN_006b5430(void* dst, ...);
extern "C" void  ReadProgressTuning();                                     // 0xf07c90

extern "C" void* SP_NounManager();                                         // 0xb3d300
extern "C" void* FUN_00ad7380(int a);
extern "C" uint  FNV1_String8(const char* s, uint h, int a);               // 0x932e80
extern "C" void* cConnectionDialog_ctor(void* mem);                        // cConnectionDialog::ctor
extern "C" void* interface_cast_CreatureAnimal(int a);                     // 0xac8960
extern "C" void* interface_cast_Building(int a);                           // 0xb67720

// Other interface classes reached through thiscall helpers.
struct NounMgr     { int GetAvatar(); };              // 0xb1fdb0
struct GameData    { int Get(); };                    // 0xb18530
struct RecOwner    { void slot(void* a, void* b, int c); };   // 0xde5df0
struct Day78       { void slot(int a, void* rec, void* flag); }; // 0xf19e70

extern "C" char g_eastlAllocator;    // 0x13ebb38 (EASTL allocator instance)
extern char     g_15ad578;           // 0x15ad578

// ---------------------------------------------------------------------------
// Rank used by the task-list ordering (2 = first, 9 = second, anything else = third).
// ---------------------------------------------------------------------------
static int TaskRank(int kind)
{
    if (kind == 2)
        return 0;
    return (kind != 9) + 1;
}

// ---------------------------------------------------------------------------
// Is the "scenario entry" window currently on screen?
// ---------------------------------------------------------------------------
// @ 0x00f08c20
char IsScenarioEntryOpen()
{
    if (g_16c7d90 == g_16c7d98)
        return 0;
    UIState* st = g_16c7d90;
    void* holder = *(void**)((char*)g_16c7aa4->ui14 + 0x18);
    IWin* win = st->layout->FindWindowByID(0x73e6ba0, 1);
    if (FUN_008053b0())
        return 0;
    if (win) {
        IWin* wm = (IWin*)SP_WindowManager();
        IWin* cur = wm->GetActiveWindow(0);
        if (win == cur)
            return 0;
        if (win->wf8(cur))
            return 0;
    }
    IWin* w2 = *(IWin**)((char*)holder + 0x20);
    if (w2 == 0)
        return 1;
    IWin* wm2 = (IWin*)SP_WindowManager();
    IWin* cur2 = wm2->GetActiveWindow(0);
    if (w2 != cur2 && !w2->wf8(cur2))
        return 1;
    return 0;
}

// ---------------------------------------------------------------------------
// Copy a task record into a freshly allocated 0xc-byte node (AddRef the payload).
// ---------------------------------------------------------------------------
// @ 0x00f08cc0
IWin** __stdcall TaskNodeAlloc(int* src)
{
    IWin** p = (IWin**)EAAllocate(0xc, "Simulator", 0, 0, (uint)&g_eastlAllocator, 0xd1);
    if (p) {
        IWin* r = (IWin*)*src;
        p[0] = r;
        if (r)
            r->IAddRef();
        p[1] = (IWin*)(intptr_t)src[1];
    }
    p[2] = 0;
    return p;
}

// ---------------------------------------------------------------------------
// Sift one element down the task heap.
// ---------------------------------------------------------------------------
// @ 0x00f08d10
void SiftDownTaskHeap(int* base, void* ctx, int end, int idx, void* a5, void* a6)
{
    int child;
    for (;;) {
        int twoIdx = idx * 2;
        child = twoIdx + 2;
        if (end <= child)
            break;
        int up = *(int*)(base[child] + 0x24);
        int dn = *(int*)(base[child - 1] + 0x24);
        if (TaskRank(up) <= TaskRank(dn))
            child = twoIdx + 1;
        base[idx] = base[child];
        idx = child;
    }
    if (child == end) {
        base[idx] = base[child - 1];
        idx = child - 1;
    }
    FUN_00f07c10(base, ctx, idx, a5, a6);
}

// ---------------------------------------------------------------------------
// Lay out the five task panels of a state block and hook up the list window.
// ---------------------------------------------------------------------------
// @ 0x00f08db0
void SetupTaskPanels(UIState* st, int owner)
{
    IWin* win = st->layout->FindWindowByID(0xceff0000, 1);
    for (int i = 0; i < 5; i++) {
        IWin* w = 0;
        CreditsTabInit(owner, 0xcefa1000, (void**)&w);
        float* area = w->GetArea();
        float h = area[3] - area[1];
        win->wd8(w);
        w->SetPos(0.0f, (float)i * h);
        st->entries[i].win = w;
        st->entries[i].idx = i;
        if (w)
            w->AddRef();
    }
    IWin* list = 0;
    CreditsTabInit(owner, 0xcefa1000, (void**)&list);
    win->wd8(list);
    st->field60 = list;
    st->field64 = -1;
    list->SetFlags(1, 0);
    IWin* lw = st->layout->FindWindowByID(0x7de6958, 1);
    lw->w104(&g_15ad578);
    if (list)
        list->AddRef();
}

// ---------------------------------------------------------------------------
// Create the marker-text dialog pair (g_16c7d94 / g_16c7d98) and initialise them.
// ---------------------------------------------------------------------------
// @ 0x00f08ef0
void CreateMarkerTextDialogs()
{
    UIState* a = (UIState*)EAAllocate(0x88, "UI/marker_text_dialog", 0, 0, 0, 0);
    if (a)
        a->layout = 0;
    else
        a = 0;
    void* p = *(void**)((char*)g_16c7aa4->ui14 + 0x18);
    IWin* nu = *(IWin**)((char*)p + 0x10);
    IWin* old = (IWin*)a->layout;
    g_16c7d94 = a;
    if (nu != old) {
        if (nu)
            nu->AddRef();
        a->layout = (Layout*)nu;
        if (old)
            old->Release();
    }

    struct { uint h; uint k1; uint k2; } key;
    key.h  = FNV1_String8("ScenarioChatterEntry", 0x811c9dc5, 1);
    key.k1 = 0x510a95b;
    key.k2 = 0x40464100;
    SetupTaskPanels(g_16c7d94, (int)&key);

    if ((g_16c7d98 = (UIState*)EAAllocate(0x88, "UI/marker_text_dialog", 0, 0, 0, 0)) != 0)
        g_16c7d98->layout = 0;

    void* mem = (void*)EAAllocate(0x18, "Simulator/marker_text_dialog/UI", 0, 0, 0, 0);
    IWin* dlg = mem ? (IWin*)cConnectionDialog_ctor(mem) : 0;
    IWin* oldB = (IWin*)g_16c7d98->layout;
    if (dlg != oldB) {
        if (dlg)
            dlg->AddRef();
        g_16c7d98->layout = (Layout*)dlg;
        if (oldB)
            oldB->Release();
    }

    struct { uint h; uint k1; uint k2; } key2;
    key2.h  = FNV1_String8("ScenarioEditModeTextDialog3", 0x811c9dc5, 1);
    key2.k1 = 0x510a95b;
    key2.k2 = 0x40464100;
    g_16c7d98->layout->Init(&key2, 1, 0x8c509d6c);
    g_16c7d98->layout->SetVisibility(0);

    struct { uint h; uint k1; uint k2; } key3;
    key3.h  = FNV1_String8("ScenarioTalkGoalEntry", 0x811c9dc5, 1);
    key3.k1 = 0x510a95b;
    key3.k2 = 0x40464100;
    SetupTaskPanels(g_16c7d98, (int)&key3);
}

// ---------------------------------------------------------------------------
// Free a bucket array: every chain node releases its payload and is deleted.
// ---------------------------------------------------------------------------
// @ 0x00f09090
void HashTbl::clearBuckets(IWin** buckets, uint n)
{
    for (uint i = 0; i < n; i++) {
        IWin** e = (IWin**)buckets[i];
        while (e) {
            IWin** cur = e;
            IWin* r = e[0];
            e = (IWin**)cur[2];
            if (r)
                r->IRelease();
            OperatorDelete(cur);
        }
        buckets[i] = 0;
    }
}

// ---------------------------------------------------------------------------
// Erase one node from a 0x15ad538-style container and delete it.
// ---------------------------------------------------------------------------
// @ 0x00f09170
void* HashTbl::erase(void* out, void* node, void* bucketPtr)
{
    int* o = (int*)out;
    int v = *(int*)((char*)node + 8);
    o[1] = (int)bucketPtr;
    o[0] = v;
    while (v == 0) {
        o[1] += 4;
        v = *(int*)o[1];
        o[0] = v;
    }
    int* p = *(int**)bucketPtr;
    if (p == (int*)node) {
        *(int*)bucketPtr = p[2];
    } else {
        int* q = (int*)p[2];
        while (q != (int*)node) {
            p = q;
            q = (int*)q[2];
        }
        p[2] = q[2];
    }
    IWin* r = *(IWin**)node;
    if (r)
        r->IRelease();
    OperatorDelete(node);
    size--;
    return out;
}

// ---------------------------------------------------------------------------
// Insert a node into the 0x15ad538-style container (EASTL hashtable insert).
// ---------------------------------------------------------------------------
// @ 0x00f092b0
void HashTbl::insert(void* retval, const void* value, uint unused)
{
    uint k = *(uint*)value;
    uint idx = k % bucketCount;
    uint* slot = (uint*)((char*)buckets + idx * 4);
    void* node = (void*)*slot;
    while (node) {
        if (k == *(uint*)node)
            break;
        node = *(void**)((char*)node + 0xc);
    }
    if (node == 0) {
        char local8[4];
        uint local4;
        na.alloc(&local8, bucketCount, size, 1);
        void* n = EAAllocate(0x10, "Simulator", 0, 0, (uint)&g_eastlAllocator, 0xd1);
        if (n) {
            *(uint*)n = *(uint*)value;
            *((uint*)n + 1) = *((uint*)value + 1);
            *((uint*)n + 2) = *((uint*)value + 2);
        }
        *(void**)((char*)n + 0xc) = 0;
        if (local8[0]) {
            idx = k % local4;
            rehash(local4);
        }
        *(void**)((char*)n + 0xc) = *(void**)((char*)buckets + idx * 4);
        *(void**)((char*)buckets + idx * 4) = n;
        size++;
        *(void**)retval = n;
        *((char*)retval + 8) = 1;
        *((void**)retval + 1) = (char*)buckets + idx * 4;
        return;
    }
    *(void**)retval = node;
    *((char*)retval + 8) = 0;
    *((void**)retval + 1) = slot;
}

// ---------------------------------------------------------------------------
// Partition the task list around `pivot` (better rank first).
// ---------------------------------------------------------------------------
// @ 0x00f093a0
int* PartitionTasks(int* first, int* last, int* pivot, void* ctx)
{
    for (;;) {
        int v = *first;
        while (TaskRank(*(int*)(*first + 0x24)) <= TaskRank(*(int*)(*pivot + 0x24)))
            first++;
        do {
            last--;
        } while (TaskRank(*(int*)(*pivot + 0x24)) <= TaskRank(*(int*)(*last + 0x24)));
        if (first >= last)
            return first;
        *first = *last;
        *last = v;
        first++;
    }
}

// ---------------------------------------------------------------------------
// Insertion pass: move better-ranked records to the front of the list.
// ---------------------------------------------------------------------------
// @ 0x00f09430
void ReorderTasks(int* base, int* first, int* last, void* ctx)
{
    FUN_00f090e0(base, first, ctx);
    for (int* it = first; it < last; it++) {
        int v = *it;
        if (TaskRank(*(int*)(v + 0x24)) <= TaskRank(*(int*)(*base + 0x24))) {
            *it = *base;
            SiftDownTaskHeap(base, 0, (int)((char*)first - (char*)base) >> 2, 0, (void*)v, ctx);
        }
    }
    FUN_00f09120(base, first, ctx);
}

// ---------------------------------------------------------------------------
// Tear the whole scenario panel system down (progress panel variant, animator).
// ---------------------------------------------------------------------------
// @ 0x00f094d0
void ShutdownTaskPanels()
{
    UIState* st = g_16c7d88;
    if (st) {
        IWin* w = (IWin*)st->layout;
        if (w)
            w->IRelease();
        OperatorDelete(st);
        g_16c7d88 = 0;
    }
    g_hash538.clearBuckets(g_hash538.buckets, g_hash538.bucketCount);
    g_hash538.size = 0;
    ((Animator*)&g_animator)->ClearAll();
    for (PBEntry* e = &g_pbEntries[0]; e < (PBEntry*)&g_animator; e++) {
        if (e->layout) {
            e->layout->Shutdown(1);
            if (e->layout) {
                IWin* L = (IWin*)e->layout;
                e->layout = 0;
                L->Release();
            }
        }
        IWin* w = e->win;
        if (w) {
            e->win = 0;
            w->IRelease();
        }
        e->sel = 0;
    }
}

// ---------------------------------------------------------------------------
// Build the object-bubble layout and its ten panel slots.
// ---------------------------------------------------------------------------
// @ 0x00f09580
void CreateBubblePanels()
{
    ReadProgressTuning();
    UIState* st = (UIState*)EAAllocate(8, "UI/ObjectBubbleLayout", 0, 0, 0, 0);
    if (st)
        st->layout = 0;
    else
        st = 0;
    IWin* w = (IWin*)st->layout;
    g_16c7d88 = st;
    if (w) {
        st->layout = 0;
        w->IRelease();
    }
    st->ctx = 0;
    g_hash538.clearBuckets(g_hash538.buckets, g_hash538.bucketCount);
    g_hash538.size = 0;
    ((Animator*)&g_animator)->ClearAll();
    for (PBEntry* e = &g_pbEntries[0]; e < (PBEntry*)&g_animator; e++) {
        void* mem = (void*)EAAllocate(0x18, "UI/ObjectBubbleLayout", 0, 0, 0, 0);
        IWin* dlg = mem ? (IWin*)cConnectionDialog_ctor(mem) : 0;
        IWin* old = (IWin*)e->layout;
        if (dlg != old) {
            if (dlg)
                dlg->AddRef();
            e->layout = (Layout*)dlg;
            if (old)
                old->Release();
        }
        e->layout->Init(L"SpeechBubble", 0x40464100, 1, 0x3f608b3e);
        e->layout->SetVisibility(0);
        IWin* w2 = e->win;
        if (w2) {
            e->win = 0;
            w2->IRelease();
        }
        e->startTime = 0.0f;
        e->sel = 0;
        IWin* lw = e->layout->FindWindowByID(0x7392dd8, 1);
        float* area = lw->GetRect();
        e->height = area[3] - area[1];
    }
}

// ---------------------------------------------------------------------------
// Tear the bubble panels down.
// ---------------------------------------------------------------------------
// @ 0x00f096c0
void ShutdownBubblePanels()
{
    UIState* st = g_16c7d88;
    IWin* w = (IWin*)st->layout;
    if (w) {
        st->layout = 0;
        w->IRelease();
    }
    st->ctx = 0;
    g_hash558.clearBuckets2(g_hash558.buckets, g_hash558.bucketCount);
    g_hash558.size = 0;
    g_hash538.clearBuckets(g_hash538.buckets, g_hash538.bucketCount);
    g_hash538.size = 0;
    ((Animator*)&g_animator)->ClearAll();
    for (PBEntry* e = &g_pbEntries[0]; e < (PBEntry*)&g_animator; e++) {
        if (e->layout)
            e->layout->SetVisibility(0);
        IWin* w2 = e->win;
        if (w2) {
            e->win = 0;
            w2->IRelease();
        }
        e->sel = 0;
        e->startTime = 0.0f;
    }
}

// ---------------------------------------------------------------------------
// Introspective task sort (quicksort with a depth counter).
// ---------------------------------------------------------------------------
// @ 0x00f09770
void SortTasks(int* first, int* last, int depth, void* ctx)
{
    while ((int)(((char*)last - (char*)first) & 0xfffffffc) > 0x70) {
        if (depth <= 0)
            break;
        int* mid = (int*)FUN_00f07ae0(first,
                                      first + (((int)((char*)last - (char*)first) >> 2) / 2),
                                      last - 1, ctx);
        int* cut = PartitionTasks(first, last, mid, ctx);
        depth--;
        SortTasks(cut, last, depth, ctx);
        last = cut;
    }
    if (depth == 0)
        ReorderTasks(first, last, last, ctx);
}

// ---------------------------------------------------------------------------
// Copy a run of 0x44-byte task records forwards.
// ---------------------------------------------------------------------------
// @ 0x00f09800
void CopyTaskRange(char* dst, char* end, char* src)
{
    if (dst != end) {
        char* s = src + 4;
        char* d = dst + 0x18;
        do {
            *(int*)dst = *(int*)src;
            *(CStr*)(d - 0x14) = *(CStr*)s;
            if (s + 0x14 != d)
                ((WStr*)d)->assign(*(int*)(s + 0x14), *(int*)(s + 0x18));
            *(int*)(d + 0x10) = *(int*)(s + 0x24);
            *(int*)(d + 0x14) = *(int*)(s + 0x28);
            if (s + 0x2c != d + 0x18)
                ((WStr*)(d + 0x18))->assign(*(int*)(s + 0x2c), *(int*)(s + 0x30));
            *(int*)(d + 0x28) = *(int*)(src + 0x40);
            dst += 0x44;
            d += 0x44;
        } while (dst != end);
    }
}

// ---------------------------------------------------------------------------
// Copy a run of 0x44-byte task records backwards.
// ---------------------------------------------------------------------------
// @ 0x00f09880
char* CopyTaskRangeBack(char* first, char* last, char* dst)
{
    if (last != first) {
        do {
            last -= 0x44;
            dst  -= 0x44;
            *(int*)dst = *(int*)last;
            *(CStr*)(dst + 4) = *(CStr*)(last + 4);
            if (last + 0x18 != dst + 0x18)
                ((WStr*)(dst + 0x18))->assign(*(int*)(last + 0x18), *(int*)(last + 0x1c));
            *(int*)(dst + 0x28) = *(int*)(last + 0x28);
            *(int*)(dst + 0x2c) = *(int*)(last + 0x2c);
            if (last + 0x30 != dst + 0x30)
                ((WStr*)(dst + 0x30))->assign(*(int*)(last + 0x30), *(int*)(last + 0x34));
            *(int*)(dst + 0x40) = *(int*)(last + 0x40);
        } while (last != first);
    }
    return dst;
}

// ---------------------------------------------------------------------------
// Attach a task record to the HUD list.
// ---------------------------------------------------------------------------
// @ 0x00f09910
void AttachTaskRecord(int a, int b, uint rec)
{
    int local;
    int buf[3];
    FUN_00b6d160(a, b);
    if (rec != 0) {
        local = ((GameData*)a)->Get();
        ((RecOwner*)rec)->slot(buf, &local, (int)(rec & 0xffffff00));
    }
}

// ---------------------------------------------------------------------------
// Dispatch one task record to its HUD string by record kind.
// ---------------------------------------------------------------------------
// @ 0x00f09960
void TaskHudAction(int a, int rec, uint id, char flag)
{
    switch (*(int*)(rec + 0x24)) {
    case 1:
        AttachTaskRecord(a, 0x7c377ad, id);
        return;
    case 2:
        ((Day78*)g_16c7aa4->day78)->slot(a, &rec, &flag);
        if (flag) {
            AttachTaskRecord(a, 0x75de461, id);
            return;
        }
        if ((char)rec) {
            AttachTaskRecord(a, 0x75f3ea8, id);
            return;
        }
        break;
    case 3:
        if (flag) {
            AttachTaskRecord(a, 0x7c377a1, id);
            return;
        }
        break;
    case 4:
        AttachTaskRecord(a, 0x7c37790, id);
        return;
    case 5:
        if (flag) {
            AttachTaskRecord(a, 0x7c377b6, id);
            return;
        }
        break;
    case 6:
        AttachTaskRecord(a, 0x7c377a9, id);
        return;
    case 7: {
        int v1 = (int)interface_cast_CreatureAnimal(a);
        int v2 = (int)FUN_00ae6760(a);
        int v3 = (int)interface_cast_Building(a);
        if (flag && (v1 || v2 || v3)) {
            AttachTaskRecord(a, 0x7c37799, id);
            return;
        }
        break;
    }
    case 8:
        AttachTaskRecord(a, 0x7c377b1, id);
        return;
    case 9: {
        int t = (int)FUN_00ad7380(a);
        int av = ((NounMgr*)SP_NounManager())->GetAvatar();
        int avp = av ? av + 0xc0 : 0;
        if (t && avp) {
            int tp = *(int*)(t + 0x108) ? *(int*)(t + 0x108) + 0xc0 : 0;
            if (tp == avp)
                return;
        }
        if (*(int*)(a + 0x1c) == *(int*)(rec + 0x28)) {
            AttachTaskRecord(a, 0x7c377a5, id);
            return;
        }
        if (*(int*)(a + 0x1c) == *(int*)(rec + 0x2c)) {
            AttachTaskRecord(a, 0x7c377a6, id);
            return;
        }
        break;
    }
    case 10:
        if (*(int*)(a + 0x1c) == *(int*)(rec + 0x28)) {
            AttachTaskRecord(a, 0x7c37793, id);
            return;
        }
        if (*(int*)(a + 0x1c) == *(int*)(rec + 0x2c)) {
            AttachTaskRecord(a, 0x7c37794, id);
            return;
        }
        break;
    case 11:
        AttachTaskRecord(a, 0x7c3779d, id);
        break;
    default:
        break;
    }
}

// ---------------------------------------------------------------------------
// Look up (or insert) a text-style entry in the style-manager hashtable.
// ---------------------------------------------------------------------------
// @ 0x00f09bf0
int* HashTbl::FindOrInsertTextStyle(int* key)
{
    int it[3];
    find(it, key);
    if (it[0] != *(int*)((char*)buckets + bucketCount * 4))
        return (int*)(it[0] + 4);
    int* node = (int*)*key;
    if (node)
        ((IWin*)node)->IAddRef();
    it[0] = (int)node;
    it[1] = 0;
    int out[3];
    insertOther(out, it, 0);
    if (node)
        ((IWin*)node)->IRelease();
    return (int*)(out[0] + 4);
}

// ---------------------------------------------------------------------------
// Look up (or insert) a group in the 0x15ad538-style container.
// ---------------------------------------------------------------------------
// @ 0x00f09c90
int HashTbl::TaskGroupLookup(int* key)
{
    int local[6];
    find(local, key);
    if (local[0] == *(int*)((char*)buckets + bucketCount * 4)) {
        local[0] = *key;
        local[1] = 0;
        local[2] = 0;
        insert(local + 3, local, (uint)key & 0xffffff00);
        local[0] = local[3];
    }
    return local[0] + 4;
}
