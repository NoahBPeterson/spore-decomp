// Slice s00e1df10 -- the Sporepedia search dialog (message handling, shutdown, palette/feed
// setup) plus the 12-byte ref-counted key/value pair container algorithms (copy, assign,
// swap, insertion sort, heap sift-up/sift-down/push/pop).
//
// Pair element (0xc bytes): { uint32 mKey; uint8 mFlag; uint8 pad[3]; RefObj* mpObj; }
// RefObj vtable: +0 = dtor, +4 = AddRef, +8 = Release.
//
// Dialog layout used here: +0x08 embedded cSPUILayout, +0x10/+0x14 two ids, +0x18 avatar
// window, +0x40 cSPPalette, +0x44 palette category/model, +0x48 FeedList, +0x4c sub-object,
// +0xbc media, +0xd4 uint32, +0xe0 uint32, +0xe4 uint16.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <string.h>
#include <stddef.h>

extern "C" void* __cdecl operator_new_(unsigned size, const char* name, int, int, const char* file, int line); // 0x00f473a0
extern "C" void __cdecl operator_delete__(void*);         // 0x00f47380

// ---------------------------------------------------------------------------------------
// shared object interfaces
// ---------------------------------------------------------------------------------------
struct RefObj {
    virtual void dtor();                                   // +0x00
    virtual void AddRef();                                 // +0x04
    virtual void Release();                                // +0x08
};

struct IWindow {
    virtual void v00();                                    // +0x00
    virtual void v01();                                    // +0x04
    virtual void v02();                                    // +0x08
    virtual IWindow* QueryInterface(uint32_t id);          // +0x0c
    virtual void v04();                                    // +0x10
    virtual void v05();                                    // +0x14
    virtual void v06();                                    // +0x18
    virtual uint32_t GetID();                              // +0x1c
};
struct IWindowFull {
    virtual void v00(); virtual void v01(); virtual void v02();
    virtual IWindowFull* QueryInterface(uint32_t id);      // +0x0c
    virtual void v04(); virtual void v05(); virtual void v06();
    virtual uint32_t GetID();                              // +0x1c
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20();
    virtual void* GetValue();                              // +0x54
    virtual void v22(); virtual void v23();
    virtual void SetValue(uint32_t v, int flag);           // +0x60
    virtual void v25(); virtual void v26(); virtual void v27(); virtual void v28();
    virtual void v29(); virtual void v30();
    virtual void SetChecked(int a, bool b);                // +0x7c
};

struct MsgServer {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual void Send(void* listener, uint32_t msg, int param); // +0x2c
};
MsgServer* __cdecl GetMessageServer();                    // 0x0067dcc0

struct Layout {
    IWindow* FindWindowByID(uint32_t id, bool recurse);   // 0x008105b0
    bool IsVisible();                                     // 0x00810070
};
struct FeedList {
    void Shutdown();                                      // 0x006628d0
    void SetVisible(bool v);                              // 0x00662920
    void SetThing(void* p);                               // 0x00663350
};
struct PaletteCat;
struct Palette {
    void Shutdown();                                      // 0x005c5c20
    PaletteCat* GetCategory(int i);                       // 0x005c5de0
    bool Init(const void* key, uint32_t type, int a, int b, int c, int d, int e); // 0x005c6340
};
struct PaletteCat {
    virtual void v00();
    virtual void AddRef();                                // +0x04
    virtual void Release();                               // +0x08
    uint32_t mPad[0x1b];                                  // +0x0c..+0x73
    uint32_t mE0;                                         // +0x74
};

void __cdecl EndModal(void* w, int a, int b);             // 0x00809c50
void __cdecl StringCtor(void* out, uint32_t id);          // 0x004010a0
void __cdecl StringCtor2(void* out, uint32_t id);         // 0x005ecf80
struct Str16 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    void RangeInitialize(const wchar_t* s);               // 0x00579a90
};
bool __cdecl CheckString(Str16* s);                       // 0x00e1de60
void* __cdecl NounManager();                              // 0x00b3d300
void* __cdecl GetPlayerTribe(void* nm);                   // 0x00bfc5f0
uint16_t __cdecl TribeNameId(void* tribe);                // 0x00c8e9f0

struct DlgBase {
    void teardown();                                      // 0x00e18810
    void reset();                                         // 0x00e18a30
};
struct SubObj {
    void init();                                          // 0x00e0a5c0
};
struct PaletteCtor {
    RefObj* ctor();                                       // 0x005c5e30
    RefObj* ctor2();                                      // 0x005c64e0
};

// ---------------------------------------------------------------------------------------
// 12-byte pair container
// ---------------------------------------------------------------------------------------
static inline void assignObj(RefObj*& dst, RefObj* src);

struct Pair {
    uint32_t mKey;                                        // +0x00
    uint8_t  mFlag;                                       // +0x04
    uint8_t  mPad[3];
    RefObj*  mpObj;                                       // +0x08
    void assignFrom(const Pair& src) {
        mKey = src.mKey;
        mFlag = src.mFlag;
        assignObj(mpObj, src.mpObj);
    }
};
typedef char chk_pair[(sizeof(Pair) == 0xc) ? 1 : -1];

static inline void assignObj(RefObj*& dst, RefObj* src)
{
    RefObj* old = dst;
    if (src != old) {
        if (src)
            src->AddRef();
        dst = src;
        if (old)
            old->Release();
    }
}

static inline void assignObjLazy(RefObj*& dst, RefObj* src)
{
    if (dst != src) {
        if (src)
            src->AddRef();
        RefObj* old = dst;
        dst = src;
        if (old)
            old->Release();
    }
}

// copy-construct a range (does not release the destination)
// @ 0x00e1e240
Pair* __cdecl pairCopyConstruct(Pair* first, Pair* last, Pair* out)      // 0x00e1e240
{
    while (first != last) {
        if (out) {
            out->mKey = first->mKey;
            out->mFlag = first->mFlag;
            RefObj* o = first->mpObj;
            out->mpObj = o;
            if (o)
                o->AddRef();
        }
        ++first;
        ++out;
    }
    return out;
}

// assign a range (add-ref new, release old)
// @ 0x00e1e390
Pair* __cdecl pairAssign(Pair* first, Pair* last, Pair* out)             // 0x00e1e390
{
    while (first != last) {
        out->assignFrom(*first);
        ++first;
        ++out;
    }
    return out;
}

// assign a range backwards
// @ 0x00e1e3f0
Pair* __cdecl pairAssignBackward(Pair* first, Pair* last, Pair* out)     // 0x00e1e3f0
{
    while (last != first) {
        --last;
        --out;
        out->assignFrom(*last);
    }
    return out;
}

// swap two elements
// @ 0x00e1e450
void __cdecl pairSwap(Pair* a, Pair* b)                                  // 0x00e1e450
{
    Pair tmp;
    tmp.mKey = a->mKey;
    tmp.mFlag = a->mFlag;
    tmp.mpObj = a->mpObj;
    if (tmp.mpObj)
        tmp.mpObj->AddRef();

    RefObj* oldA = a->mpObj;
    RefObj* newA = b->mpObj;
    a->mKey = b->mKey;
    a->mFlag = b->mFlag;
    if (newA != oldA) {
        if (newA)
            newA->AddRef();
        a->mpObj = newA;
        if (oldA)
            oldA->Release();
    }

    RefObj* oldB = b->mpObj;
    b->mKey = tmp.mKey;
    b->mFlag = tmp.mFlag;
    if (tmp.mpObj != oldB) {
        if (tmp.mpObj)
            tmp.mpObj->AddRef();
        b->mpObj = tmp.mpObj;
        if (oldB)
            oldB->Release();
    }

    if (tmp.mpObj)
        tmp.mpObj->Release();
}

// sift a hole up the heap
// @ 0x00e1e2d0
void __cdecl pairSiftUp(Pair* base, int top, int hole, uint32_t key, uint8_t flag, RefObj* obj) // 0x00e1e2d0
{
    int parent = (hole - 1) >> 1;
    while (hole > top && base[parent].mKey < key) {
        base[hole].mKey = base[parent].mKey;
        base[hole].mFlag = base[parent].mFlag;
        assignObjLazy(base[hole].mpObj, base[parent].mpObj);
        hole = parent;
        parent = (parent - 1) >> 1;
    }
    base[hole].mKey = key;
    base[hole].mFlag = flag;
    assignObjLazy(base[hole].mpObj, obj);
    if (obj)
        obj->Release();
}

// sift the hole down then up
// @ 0x00e1e8c0
void __cdecl pairSiftDown(Pair* base, int, int len, int hole,
                          uint32_t key, uint8_t flag, RefObj* obj, int) // 0x00e1e8c0
{
    int child;
    for (;;) {
        child = hole * 2 + 2;
        if (len <= child)
            break;
        if (base[child].mKey < base[child - 1].mKey)
            child -= 1;
        base[hole].mKey = base[child].mKey;
        base[hole].mFlag = base[child].mFlag;
        assignObj(base[hole].mpObj, base[child].mpObj);
        hole = child;
    }
    if (child == len) {
        base[hole].mKey = base[child - 1].mKey;
        base[hole].mFlag = base[child - 1].mFlag;
        assignObj(base[hole].mpObj, base[child - 1].mpObj);
        hole = child - 1;
    }
    pairSiftUp(base, 0, hole, key, flag, obj);
}

// insertion sort
// @ 0x00e1e6d0
void __cdecl pairInsertionSort(Pair* first, Pair* last)                  // 0x00e1e6d0
{
    if (first == last)
        return;
    Pair* i = first + 1;
    if (i == last)
        return;
    do {
        uint32_t key = i->mKey;
        uint8_t flag = i->mFlag;
        RefObj* obj = i->mpObj;
        if (obj)
            obj->AddRef();
        Pair* hole = i;
        while (hole != first && key < hole[-1].mKey) {
            hole->mKey = hole[-1].mKey;
            hole->mFlag = hole[-1].mFlag;
            assignObj(hole->mpObj, hole[-1].mpObj);
            --hole;
        }
        hole->mKey = key;
        hole->mFlag = flag;
        assignObj(hole->mpObj, obj);
        if (obj)
            obj->Release();
        ++i;
    } while (i != last);
}

// make-heap: sift every element up into place
// @ 0x00e1e7d0
void __cdecl pairMakeHeap(Pair* first, Pair* last)                       // 0x00e1e7d0
{
    if (first == last)
        return;
    for (Pair* i = first + 1; i != last; ++i) {
        uint32_t key = i->mKey;
        uint8_t flag = i->mFlag;
        RefObj* obj = i->mpObj;
        if (obj)
            obj->AddRef();
        Pair* hole = i;
        while (hole != first && key < hole[-1].mKey) {
            hole->mKey = hole[-1].mKey;
            hole->mFlag = hole[-1].mFlag;
            assignObj(hole->mpObj, hole[-1].mpObj);
            --hole;
        }
        hole->mKey = key;
        hole->mFlag = flag;
        assignObj(hole->mpObj, obj);
        if (obj)
            obj->Release();
    }
}

// pop the heap root to the back, restore the heap
// @ 0x00e1e9e0
void __cdecl pairPopHeap(Pair* first, Pair* last, int)                   // 0x00e1e9e0
{
    uint32_t key = last[-1].mKey;
    uint8_t flag = last[-1].mFlag;
    RefObj* obj = last[-1].mpObj;
    if (obj)
        obj->AddRef();

    last[-1].mKey = first->mKey;
    last[-1].mFlag = first->mFlag;
    assignObj(last[-1].mpObj, first->mpObj);

    int hole = (int)(last - first) - 1;
    pairSiftUp(first, 0, hole, key, flag, obj);
    if (obj)
        obj->Release();
}

// ---------------------------------------------------------------------------------------
// the dialog
// ---------------------------------------------------------------------------------------
struct SearchDlg {
    uint32_t mPad00[2];                                   // +0x00
    uint8_t  mLayout[0x08];                               // +0x08 embedded cSPUILayout
    uint32_t mId10;                                       // +0x10
    uint32_t mId14;                                       // +0x14
    void*    mpAvatar;                                    // +0x18
    uint32_t mPad1C[9];                                   // +0x1c
    Palette* mpPalette;                                   // +0x40
    void*    mpModel;                                     // +0x44
    FeedList* mpFeed;                                     // +0x48
    uint8_t  mSub4C[0x70];                                // +0x4c sub-object
    void*    mpMedia;                                     // +0xbc
    uint32_t mPadC0[5];                                   // +0xc0
    uint32_t mD4;                                         // +0xd4
    uint32_t mD8[2];                                      // +0xd8
    uint32_t mE0;                                         // +0xe0
    uint16_t mE4;                                         // +0xe4

    Layout* layout() { return (Layout*)mLayout; }

    uint32_t handle(uint32_t* msg, int arg2);             // 0x00e1df10
    uint32_t getD4(int unused);                           // 0x00e1e100
    void shutdown();                                      // 0x00e1e120
    void hideFeed();                                      // 0x00e1e1f0
    void setThing(void* p);                               // 0x00e1e210
    void setupPalette(void* key, uint32_t a, uint32_t b, uint32_t c, uint32_t d); // 0x00e1e500
};
typedef char chk_dlg_offsets[
    (offsetof(SearchDlg, mpPalette) == 0x40 &&
     offsetof(SearchDlg, mpFeed) == 0x48 &&
     offsetof(SearchDlg, mpMedia) == 0xbc &&
     offsetof(SearchDlg, mD4) == 0xd4 &&
     offsetof(SearchDlg, mE0) == 0xe0) ? 1 : -1];

// @ 0x00e1df10
uint32_t SearchDlg::handle(uint32_t* msg, int arg2)
{
    IWindow* w = layout()->FindWindowByID(0x7d4c266, 1);
    uint32_t kind = msg[2];
    if (kind == 0x287259f6) {
        uint32_t sub = (*(uint32_t(__thiscall**)(void))**(void***)msg)();
        if (sub == 0x7d4de46) {
            EndModal(w, 1, 1);
            return 0;
        }
        if (sub != 0x5a725b4)
            return 0;
        Str16 range;
        range.mpBegin = 0;
        range.mpEnd = 0;
        range.mpCapacity = 0;
        StringCtor(&range, 0x51aa76bb);
        StringCtor2(&range, 0x51aa76bb);
        IWindow* listW = layout()->FindWindowByID(0x7d4c4be, 1);
        if (listW) {
            IWindowFull* list = (IWindowFull*)listW->QueryInterface(0xcf428691);
            if (list) {
                list->SetValue((uint32_t)(uintptr_t)range.mpBegin, 0);
                IWindowFull* check = (IWindowFull*)layout()->FindWindowByID(0x7d4de46, 1);
                if (check)
                    check->SetChecked(2, range.mpBegin != range.mpEnd);
            }
        }
        if ((int)(((char*)range.mpCapacity - (char*)range.mpBegin) & 0xfffffffe) > 2 && range.mpBegin)
            operator_delete__(range.mpBegin);
        return 0;
    }
    if (kind != 0x9b1552d8)
        return 0;
    uint32_t sub = (*(uint32_t(__thiscall**)(void))**(void***)msg)();
    if (sub != 0x7d4c4be)
        return 0;
    IWindow* listW = layout()->FindWindowByID(0x7d4c4be, 1);
    IWindowFull* list = listW ? (IWindowFull*)listW->QueryInterface(0xcf428691) : 0;
    wchar_t* text = (wchar_t*)list->GetValue();
    Str16 s;
    s.mpBegin = 0;
    s.mpEnd = 0;
    s.mpCapacity = 0;
    s.RangeInitialize(text);
    bool ok = CheckString(&s);
    wchar_t* lo = s.mpBegin;
    if (ok)
        list->SetValue((uint32_t)(uintptr_t)lo, 0);
    IWindowFull* check = (IWindowFull*)layout()->FindWindowByID(0x7d4de46, 1);
    if (check)
        check->SetChecked(2, lo != s.mpEnd);
    if ((int)(((char*)s.mpCapacity - (char*)lo) & 0xfffffffe) > 2 && lo)
        operator_delete__(lo);
    return 0;
}

// @ 0x00e1e100
uint32_t SearchDlg::getD4(int)
{
    return mD4;
}

// @ 0x00e1e120
void SearchDlg::shutdown()
{
    GetMessageServer()->Send(this ? (void*)((char*)this + 0xc) : 0, 0x5bf34455, 0xffffd8f1);
    GetMessageServer()->Send(this ? (void*)((char*)this + 0xc) : 0, 0x1e8c9e0, 0xffffd8f1);
    ((SubObj*)mSub4C)->init();
    if (mpMedia) {
        (*(void (__thiscall**)(void*))((*(void***)mpMedia)[9]))(mpMedia);   // +0x24
        void* m = mpMedia;
        if (m) {
            mpMedia = 0;
            (*(void (__thiscall**)(void*))((*(void***)m)[1]))(m);           // +0x04
        }
    }
    if (mpFeed) {
        mpFeed->Shutdown();
        FeedList* f = mpFeed;
        if (f) {
            mpFeed = 0;
            (*(void (__thiscall**)(void*))((*(void***)f)[1]))(f);
        }
    }
    if (mpPalette) {
        mpPalette->Shutdown();
        Palette* p = mpPalette;
        if (p) {
            mpPalette = 0;
            (*(void (__thiscall**)(void*))((*(void***)p)[2]))(p);           // +0x08
        }
    }
    ((DlgBase*)this)->teardown();
}

// @ 0x00e1e1f0
void SearchDlg::hideFeed()
{
    if (mpFeed)
        mpFeed->SetVisible(0);
    ((DlgBase*)this)->reset();
}

// @ 0x00e1e210
void SearchDlg::setThing(void* p)
{
    if (mpFeed) {
        Layout* l = (Layout*)mpAvatar;
        if (l->IsVisible())
            mpFeed->SetThing(p);
    }
}

// @ 0x00e1e500
void SearchDlg::setupPalette(void* key, uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    if (!key)
        return;

    RefObj* pal = 0;
    void* mem = operator_new_(0x40, (const char*)0x013f6b3c, 0, 0, 0, 0);
    if (mem)
        pal = ((PaletteCtor*)mem)->ctor();
    if (pal != (RefObj*)mpPalette) {
        if (pal)
            pal->AddRef();
        Palette* old = mpPalette;
        mpPalette = (Palette*)pal;
        if (old)
            (*(void (__thiscall**)(void*))((*(void***)old)[2]))(old);
    }
    if (!mpPalette->Init(key, c, 0, 0, 0, 0, 0)) {
        Palette* p = mpPalette;
        if (p) {
            mpPalette = 0;
            (*(void (__thiscall**)(void*))((*(void***)p)[2]))(p);
        }
        return;
    }

    PaletteCat* cat = mpPalette->GetCategory(0);
    if (cat) {
        cat->AddRef();
        mE0 = cat->mE0;
    }

    RefObj* model = 0;
    void* mem2 = operator_new_(0x34, (const char*)0x013f6b3c, 0, 0, 0, 0);
    if (mem2)
        model = ((PaletteCtor*)mem2)->ctor2();
    if (model != (RefObj*)mpModel) {
        if (model)
            model->AddRef();
        void* old = mpModel;
        mpModel = model;
        if (old)
            (*(void (__thiscall**)(void*))((*(void***)old)[2]))(old);
    }

    if (mId10 == 0x1654c02 && mId14 == 0x6722bd6) {
        void* nm = NounManager();
        void* tribe = GetPlayerTribe(nm);
        if (tribe) {
            void* m = mpModel;
            void* nm2 = NounManager();
            void* tribe2 = GetPlayerTribe(nm2);
            *(uint16_t*)((char*)m + 0x18) = TribeNameId(tribe2);
            goto tail;
        }
    }
    *(uint16_t*)((char*)mpModel + 0x18) = mE4;

tail:
    {
        uint8_t* m = (uint8_t*)mpModel;
        RefObj* r = *(RefObj**)(m + 8);
        if (r) {
            *(void**)(m + 8) = 0;
            if (--*(int*)((char*)r + 4) == 0) {
                *(int*)((char*)r + 4) = 1;
                (*(void (__thiscall**)(void*, int))**(void***)r)(r, 1);
            }
        }
        RefObj* q = *(RefObj**)(m + 0xc);
        if (q) {
            *(void**)(m + 0xc) = 0;
            q->Release();
        }
        *(uint32_t*)(m + 0x2c) = c;
        *(uint32_t*)(m + 0x1c) = 0;
        *(uint32_t*)(m + 0x20) = d;
    }
    if (cat)
        cat->Release();
}
