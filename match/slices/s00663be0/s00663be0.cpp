// Slice s00663be0: SP::cSPUIFeedListCategory (feed-category filter), the cSPUIFeedListItem
// comparator/heap helpers and the intrusive refcounted-pointer sort primitives around it.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-.
#include "types.h"

struct IWindow;

extern "C" int __cdecl _wcsicmp(const wchar_t*, const wchar_t*);

// =============================================================================
// SP::cSPUIFeedListItem
// =============================================================================
struct FeedItem {
    virtual int  AddRef();       // +0x00
    virtual int  Release();      // +0x04
    char     pad08[8];
    void*    m0c;                // +0x0c
    int      m10;                // +0x10
    bool     m14;                // +0x14
    char     pad15[3];
    wchar_t* mName;              // +0x18
    char     pad1c[0xc4 - 0x1c];
    int      mGroup;             // +0xc4
    char     padc8[0x134 - 0xc8];
    int      m134;               // +0x134
    char     pad138[0x17c - 0x138];
    int      m17c;               // +0x17c
    char     pad180[0x188 - 0x180];
    int      m188;               // +0x188
    void FUN_00667690(int v);    // 0x00667690
    void FUN_00668550(int v);    // 0x00668550
    void FUN_00666590(float* r); // 0x00666590
    void FUN_00666680(int v);    // 0x00666680
};

// =============================================================================
// EA::AutoRefCount<SP::cSPUIFeedListItem>  (one pointer, copy = AddRef)
// =============================================================================
struct AutoRefCountT {
    FeedItem* mpObject;
    AutoRefCountT() : mpObject(0) {}
    AutoRefCountT(const AutoRefCountT& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCountT() { if (mpObject) mpObject->Release(); }
    AutoRefCountT& operator=(const AutoRefCountT& o) {
        if (o.mpObject != mpObject) {
            if (o.mpObject) o.mpObject->AddRef();
            FeedItem* old = mpObject;
            mpObject = o.mpObject;
            if (old) old->Release();
        }
        return *this;
    }
    FeedItem* operator->() const { return mpObject; }
    operator FeedItem*() const { return mpObject; }
};

// =============================================================================
// SP::AlphabeticalFeedSort
// =============================================================================
struct AlphabeticalFeedSort {
    bool operator()(const FeedItem* a, const FeedItem* b) const {
        if (a && b) {
            if (a->mGroup == b->mGroup) {
                if (a->mName && b->mName)
                    return _wcsicmp(a->mName, b->mName) < 0;
                return false;
            }
            return a->mGroup < b->mGroup;
        }
        return false;
    }
};

// =============================================================================
// EASTL heap primitives (out-of-line so adjust_heap emits a real call)
// =============================================================================
template <typename T, typename Compare>
__declspec(noinline) void promote_heap(T* first, int topPosition, int position, const T& value) {
    Compare compare;
    for (int parentPosition = (position - 1) >> 1;
         (position > topPosition) && compare(first[parentPosition], value);
         parentPosition = (position - 1) >> 1) {
        first[position] = first[parentPosition];
        position = parentPosition;
    }
    first[position] = value;
}

template <typename T, typename Compare>
void adjust_heap(T* first, int topPosition, int heapSize, int position, const T& value) {
    Compare compare;
    int childPosition = (2 * position) + 2;
    for (; childPosition < heapSize; childPosition = (2 * childPosition) + 2) {
        if (compare(first[childPosition], first[childPosition - 1]))
            --childPosition;
        first[position] = first[childPosition];
        position = childPosition;
    }
    if (childPosition == heapSize) {
        first[position] = first[childPosition - 1];
        position = childPosition - 1;
    }
    promote_heap<T, Compare>(first, topPosition, position, value);
}

// =============================================================================
// UTFWin IWindow: slots used by this slice (offsets in comments).
// =============================================================================
struct IWindow {
    virtual void      v00();                          // 0x00
    virtual int       Release();                      // 0x04
    virtual void      v02();                          // 0x08
    virtual IWindow*  FindWindow(uint32_t id);        // 0x0c
    virtual IWindow*  v04();                          // 0x10
    virtual void      v05();                          // 0x14
    virtual void      v06();                          // 0x18
    virtual void      v07();                          // 0x1c
    virtual void      v08();                          // 0x20
    virtual void      v09();                          // 0x24
    virtual void      SetStateFlag(int, bool);        // 0x28
    virtual void      v11();                          // 0x2c
    virtual void      v12();                          // 0x30
    virtual float*    GetArea();                      // 0x34
    virtual float*    GetRect();                      // 0x38
    virtual void      v15();                          // 0x3c
    virtual void      v16();                          // 0x40
    virtual void      v17();                          // 0x44
    virtual void*     v18(int);                       // 0x48
    virtual void      v19();                          // 0x4c
    virtual void      v20();                          // 0x50
    virtual void      v21();                          // 0x54
    virtual void      v22();                          // 0x58
    virtual void      v23();                          // 0x5c
    virtual void      SetArea(float*);                // 0x60
    virtual void      v25();                          // 0x64
    virtual void      v26();                          // 0x68
    virtual void      v27(void*);                     // 0x6c
    virtual void      v28();                          // 0x70
    virtual void      v29();                          // 0x74
    virtual void      v30();                          // 0x78
    virtual void      SetFlag(int, bool);             // 0x7c
    virtual void      v32();                          // 0x80
    virtual void      v33();                          // 0x84
    virtual void      v34();                          // 0x88
    virtual void      v35();                          // 0x8c
    virtual void      v36();                          // 0x90
    virtual void      v37();                          // 0x94
    virtual void      v38();                          // 0x98
    virtual void      v39();                          // 0x9c
    virtual void      v40();                          // 0xa0
    virtual void      v41();                          // 0xa4
    virtual void      v42();                          // 0xa8
    virtual void      v43();                          // 0xac
    virtual void      v44();                          // 0xb0
    virtual void      v45();                          // 0xb4
    virtual void      v46();                          // 0xb8
    virtual void      v47();                          // 0xbc
    virtual void      v48();                          // 0xc0
    virtual void      v49();                          // 0xc4
    virtual void      v50();                          // 0xc8
    virtual void      v51();                          // 0xcc
    virtual void      v52();                          // 0xd0
    virtual void      v53();                          // 0xd4
    virtual void      v54();                          // 0xd8
    virtual void      v55();                          // 0xdc
    virtual void      v56();                          // 0xe0
    virtual void      v57();                          // 0xe4
    virtual void      v58();                          // 0xe8
    virtual void      v59();                          // 0xec
    virtual void      v60();                          // 0xf0
    virtual void      v61();                          // 0xf4
    virtual void      v62();                          // 0xf8
    virtual void      v63();                          // 0xfc
    virtual void      v64();                          // 0x100
    virtual void      v65();                          // 0x104
    virtual void      AttachProc(void*);              // 0x108
};

struct AudioAT {
    virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3();
    virtual void a4(); virtual void a5(); virtual void a6(); virtual void a7();
    virtual void* Slot20();                           // 0x20
};

struct cSPUILayout {
    virtual void s0();
    virtual void s1();
    virtual int  Release();                           // 0x08
    void Shutdown(bool);                              // 0x00811ad0
    char pad[0x18 - 4];
};

struct WindowManager {
    virtual void w00(); virtual void w01(); virtual void w02(); virtual void w03();
    virtual void w04(int a, void* b, void* c, int d); // 0x10
    virtual void w05(); virtual void w06(); virtual void w07(); virtual void w08();
    virtual void w09(); virtual void w10(); virtual void w11(); virtual void w12();
    virtual void w13(); virtual void w14(); virtual void w15(); virtual void w16();
    virtual void w17();
    virtual void* w18(int v);                         // 0x48
};

// -----------------------------------------------------------------------------
// external callees
// -----------------------------------------------------------------------------
void  __cdecl EA_RemoveHandler(void* h, uint32_t a, uint32_t b, uint32_t c, uint32_t d); // 0x00571db0
struct D4Obj { void FUN_00829d30(); };
void  __stdcall FUN_008294c0(void* p, int v);                 // 0x008294c0
bool  __cdecl FUN_00805150(void* a, void* b);                 // 0x00805150
bool  __cdecl StartBanMode(uint32_t id);                      // 0x008d2fb0
struct PredObj { bool FUN_00a98020(); };
void* __cdecl SP_WindowManager();                             // 0x0067caa0
void* __cdecl SP_GetSystemAT();                               // 0x00a206f0
void  __cdecl SP_KillSetiEffects(uint32_t id, void* at);      // 0x00435ed0
void* __cdecl FUN_005c2570(void* p);                          // 0x005c2570 interface_cast
void  __cdecl FUN_00662b00(void* p);                          // 0x00662b00
void  __cdecl FUN_00c37480(void* p);                          // 0x00c37480 (float thiscall)

extern uint32_t g_fp1;   // 0x01486110
extern uint32_t g_fp2;   // 0x013f4fd0
extern uint32_t g_fp3;   // 0x013f9ea0
extern uint32_t g_fp4;   // 0x01485720
extern uint32_t g_fp5;   // 0x01485548

// =============================================================================
// SP::cSPUIFeedListCategory
// =============================================================================
struct cSPUIFeedListCategory {
    char      pad00[0x10];
    bool      m10;            // +0x10
    char      pad11[3];
    bool      m14;            // +0x14
    bool      m15;            // +0x15
    char      pad16[0x12];
    float     m28, m2c, m30, m34;   // +0x28 Rect
    float     m38, m3c, m40, m44;   // +0x38 Rect
    char      pad48[0x10];
    float     m58;            // +0x58
    float     m5c;            // +0x5c
    void*     m60;            // +0x60
    cSPUILayout* m64;         // +0x64
    char      pad68[4];
    void*     m6c;            // +0x6c
    IWindow*  m70;            // +0x70
    IWindow*  m74;            // +0x74
    IWindow*  m78;            // +0x78
    IWindow*  m7c;            // +0x7c
    IWindow*  m80;            // +0x80
    IWindow*  m84;            // +0x84
    FeedItem** m88;           // +0x88 vector begin
    FeedItem** m8c;           // +0x8c vector end
    char      pad90[8];
    bool      m98;            // +0x98
    char      pad99[3];
    bool      m9c;            // +0x9c
    char      pad9d[0x1f];
    void*     mbc;            // +0xbc
    uint32_t  mc0, mc4, mc8, mcc;   // +0xc0..0xcc
    char      padD0[4];
    void*     md4;            // +0xd4

    bool FUN_00663be0(void* msg);
    void FUN_00663e50();
    void FUN_00663ef0(int param);
    void FUN_00664390(float a, float b, float c, float d);
    void FUN_00664440();
    void FUN_00664480(bool expanded);
    void FUN_006644e0(bool b);
    bool FUN_00664550(bool b);
    void FUN_00664580(bool b);
    FeedItem* FUN_00664610(uint32_t idx);
    FeedItem* FUN_00664640(int id);
    FeedItem* FUN_00664680(int id);
    FeedItem* FUN_006646c0(int id);
    bool FUN_00664a60(uint32_t id, void* msg);
};

// =============================================================================
// @ 0x00663be0
// =============================================================================
bool cSPUIFeedListCategory::FUN_00663be0(void* msg) {
    int type = *(int*)((char*)msg + 8);
    if (type > 0x1c) goto case287259f6;
    if (type == 0x1c) goto case1c;
    if (type == 9) goto case9;
    if (type != 0x1b) goto def;
    {
        if (*(int*)((char*)msg + 0xc) != 1) goto def;
        if (mcc) goto def;
        void* q = *(void**)((char*)msg + 0x18);
        if (!FUN_00805150(m70, q)) goto def;
        bool b1 = StartBanMode(0x3e8);
        bool b2 = StartBanMode(0x3ea);
        bool b3 = StartBanMode(0x3e9);
        if (b1 || b2 || b3) goto def;
        mcc = 1;
        return false;
    }
case9:
    {
        uint32_t v = *(uint32_t*)((char*)msg + 4);
        if (v != (uint32_t)m78 && v != (uint32_t)m7c && v != (uint32_t)m80) goto def;
        WindowManager* wm = (WindowManager*)SP_WindowManager();
        wm->w04((int)m6c, m64, msg, 0);
        return false;
    }
case1c:
    {
        if (*(int*)((char*)msg + 0xc) != 1) goto def;
        if (!mcc) goto def;
        WindowManager* wm = (WindowManager*)SP_WindowManager();
        void* r = wm->w18(1);
        void* q = *(void**)((char*)msg + 0x18);
        if (!FUN_00805150(m70, q)) goto def;
        if (FUN_00805150(m70, r)) goto def;
        mcc = 0;
        return false;
    }
case287259f6:
    if (type != 0x287259f6) goto def;
    {
        int sub = *(int*)((char*)msg + 0xc);
        if (sub == (int)0xb3c6efc2) goto sub_b3;
        if (sub == (int)0xb48e2560) goto sub_b4;
        goto def;
    }
sub_b3:
    {
        bool nv = (m98 == 0);
        m98 = nv;
        void* at = SP_GetSystemAT();
        void* r = at ? ((AudioAT*)at)->Slot20() : 0;
        uint32_t id = nv ? 0xea0588f8u : 0x2dd00402u + 0xea0588f8u;
        SP_KillSetiEffects(id, r);
        if (m7c) {
            IWindow* b = (IWindow*)FUN_005c2570(&m7c);
            b->SetStateFlag(4, nv);
        }
        goto tail;
    }
sub_b4:
    {
        bool nv = (m98 == 0);
        m98 = nv;
        void* at = SP_GetSystemAT();
        void* r = at ? ((AudioAT*)at)->Slot20() : 0;
        uint32_t id = nv ? 0xea0588f8u : 0x2dd00402u + 0xea0588f8u;
        SP_KillSetiEffects(id, r);
        if (m7c) {
            IWindow* b = (IWindow*)FUN_005c2570(&m7c);
            b->SetStateFlag(4, nv);
        }
        goto tail;
    }
tail:
    if (m5c) FUN_00662b00((char*)this - 4);
    return true;
def:
    return false;
}

// =============================================================================
// @ 0x00663e50
// =============================================================================
void cSPUIFeedListCategory::FUN_00663e50() {
    if (md4) {
        ((D4Obj*)md4)->FUN_00829d30();
        void* p = md4;
        if (p) { md4 = 0; ((cSPUILayout*)p)->Release(); }
    }
    if (m70) {
        void* self = (char*)this + 4;
        m70->AttachProc(self);
    }
    if (m64) {
        m64->Shutdown(true);
        cSPUILayout* p = m64;
        if (p) { m64 = 0; p->Release(); }
    }
    if (mbc) {
        void* h = mbc;
        uint32_t a = mc0, b = mc4, c = mc8, d = mcc;
        mbc = 0;
        EA_RemoveHandler(h, a, b, c, d);
    }
}

// =============================================================================
// @ 0x00663ef0  (large layout sweep; see partial.txt)
// =============================================================================
void cSPUIFeedListCategory::FUN_00663ef0(int param) {
    if (!m7c) return;
    float* p = m7c->GetRect();
    float span = p[2] - p[0];
    float total = m58 + *(float*)&g_fp1;
    int n = (int)((m8c - m88));
    for (int i = 0; i < n; ++i) {
        FeedItem* it = m88[i];
        it->FUN_00668550(param);
        float h = 0.0f;
        (void)h;
        float r[4];
        (void)span;
        it->FUN_00666590(r);
    }
    m5c = total + *(float*)&g_fp1;
    m7c->SetFlag(1, m9c);
    (void)span;
}

// =============================================================================
// @ 0x00664390
// =============================================================================
void cSPUIFeedListCategory::FUN_00664390(float a, float b, float c, float d) {
    struct D4 { char pad0[9]; bool f9; bool fa; };
    D4* d4 = (D4*)md4;
    if (d4 && (d4->f9 || d4->fa)) {
        FUN_008294c0((char*)this + 0x48, 1);
    } else if (m74) {
        float r[4] = {0.0f, 0.0f, 0.0f, 0.0f};
        m74->SetArea(r);
        float* p = m74->GetRect();
        m38 = p[0];
        m3c = p[1];
        m40 = p[2];
        m44 = p[3];
    }
    m28 = a;
    m2c = b;
    m30 = c;
    m34 = d;
}

// =============================================================================
// @ 0x00664440
// =============================================================================
void cSPUIFeedListCategory::FUN_00664440() {
    int n = (int)((m8c - m88));
    for (int i = 0; i < n; ++i)
        m88[i]->FUN_00667690(1);
}

// =============================================================================
// @ 0x00664480
// =============================================================================
void cSPUIFeedListCategory::FUN_00664480(bool expanded) {
    if (expanded == m9c) return;
    m9c = expanded;
    IWindow* btn = m80 ? m80->FindWindow(0x8ed27e7a) : 0;
    ((IWindow*)btn)->SetStateFlag(4, m9c);
    if (m60) FUN_00662b00(this);
}

// =============================================================================
// @ 0x006644e0
// =============================================================================
void cSPUIFeedListCategory::FUN_006644e0(bool b) {
    if (m78) m78->SetFlag(1, b);
    if (m80) {
        m80->SetFlag(1, b);
        float v;
        if (b) {
            float* p = m80->GetArea();
            v = p[3] - p[1];
        } else {
            v = 0.0f;
        }
        m58 = v;
    }
    if (m84) m84->SetFlag(1, b);
}

// =============================================================================
// @ 0x00664550
// =============================================================================
bool cSPUIFeedListCategory::FUN_00664550(bool b) {
    if (!b) return m14;
    if (m14 && m60 && ((PredObj*)m60)->FUN_00a98020()) return true;
    return false;
}

// =============================================================================
// @ 0x00664580
// =============================================================================
void cSPUIFeedListCategory::FUN_00664580(bool b) {
    m15 = b;
    if (m70) m70->SetFlag(2, m15);
    if (m78) m78->SetFlag(2, m15);
    if (m7c) m7c->SetFlag(2, m15);
    if (m80) m80->SetFlag(2, m15);
    if (m84) m84->SetFlag(2, m15);
}

// =============================================================================
// @ 0x00664610
// =============================================================================
FeedItem* cSPUIFeedListCategory::FUN_00664610(uint32_t idx) {
    FeedItem* result = 0;
    if (idx < (uint32_t)((m8c - m88)))
        result = m88[idx];
    return result;
}

// =============================================================================
// @ 0x00664640 / 0x00664680 / 0x006646c0
// =============================================================================
FeedItem* cSPUIFeedListCategory::FUN_00664640(int id) {
    int n = (int)(m8c - m88);
    int i = 0;
    FeedItem** p = m88;
    if (n > 0) {
        do {
        FeedItem* e = *p;
        if (e && e->m17c == id) return e;
            ++i; ++p;
        } while (i < n);
    }
    return 0;
}

FeedItem* cSPUIFeedListCategory::FUN_00664680(int id) {
    int n = (int)(m8c - m88);
    int i = 0;
    FeedItem** p = m88;
    if (n > 0) {
        do {
        FeedItem* e = *p;
        if (e && e->m134 == id) return e;
            ++i; ++p;
        } while (i < n);
    }
    return 0;
}

FeedItem* cSPUIFeedListCategory::FUN_006646c0(int id) {
    int n = (int)(m8c - m88);
    int i = 0;
    FeedItem** p = m88;
    if (n > 0) {
        do {
        FeedItem* e = *p;
        if (e && e->m188 == id) return e;
            ++i; ++p;
        } while (i < n);
    }
    return 0;
}

// =============================================================================
// @ 0x00664a60
// =============================================================================
bool cSPUIFeedListCategory::FUN_00664a60(uint32_t id, void* msg) {
    if (id != 0xb3d53f95) return false;
    if (!msg) return false;
    FeedItem* target = *(FeedItem**)((char*)msg + 0x10);
    if (!target) {
        if (*(unsigned char*)((char*)msg + 0x14) != 0)
            target = FUN_00664680(*(int*)((char*)msg + 0xc));
        else
            target = FUN_00664640(*(int*)((char*)msg + 0xc));
        if (!target) return false;
    }
    FeedItem** it = m88;
    FeedItem** end = m8c;
    for (; it != end; ++it)
        if (*it == target) break;
    if (it != end) FUN_00664480(true);
    return false;
}

// =============================================================================
// @ 0x00664700 / 0x00664800 : intrusive array insertion-sort primitives.
// =============================================================================
static void AssignRef(AutoRefCountT& slot, FeedItem* p) {
    if (p != slot.mpObject) {
        if (p) p->AddRef();
        FeedItem* old = slot.mpObject;
        slot.mpObject = p;
        if (old) old->Release();
    }
}

// @ 0x00664700
void __cdecl FUN_00664700(AutoRefCountT* first, AutoRefCountT* last) {
    if (first == last) return;
    AutoRefCountT* i = first + 1;
    if (i == last) return;
    do {
        FeedItem* value = i->mpObject;
        if (value) value->AddRef();
        AutoRefCountT* j = i;
        while (j != first) {
            FeedItem* prev = (j - 1)->mpObject;
            if (!value || !prev) break;
            if (value->mGroup == prev->mGroup) {
                if (!value->mName || !prev->mName) break;
                if (_wcsicmp(value->mName, prev->mName) >= 0) break;
            } else if (!(prev->mGroup < value->mGroup)) {
                break;
            }
            AssignRef(*j, prev);
            --j;
        }
        AssignRef(*j, value);
        if (value) value->Release();
        ++i;
    } while (i != last);
}

// @ 0x00664800
void __cdecl FUN_00664800(AutoRefCountT* first, AutoRefCountT* last) {
    if (first == last) return;
    AutoRefCountT* i = first;
    do {
        FeedItem* value = i->mpObject;
        if (value) value->AddRef();
        AutoRefCountT* j = i;
        while (j != first) {
            FeedItem* prev = (j - 1)->mpObject;
            if (!value || !prev) break;
            if (value->mGroup == prev->mGroup) {
                if (!value->mName || !prev->mName) break;
                if (_wcsicmp(value->mName, prev->mName) >= 0) break;
            } else if (!(prev->mGroup < value->mGroup)) {
                break;
            }
            AssignRef(*j, prev);
            --j;
        }
        AssignRef(*j, value);
        if (value) value->Release();
        ++i;
    } while (i != last);
}

// =============================================================================
// explicit instantiations: promote_heap / adjust_heap
// =============================================================================
template void promote_heap<AutoRefCountT, AlphabeticalFeedSort>(
    AutoRefCountT*, int, int, const AutoRefCountT&);
template void adjust_heap<AutoRefCountT, AlphabeticalFeedSort>(
    AutoRefCountT*, int, int, int, const AutoRefCountT&);
