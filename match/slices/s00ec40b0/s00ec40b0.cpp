// Slice s00ec40b0 -- Spore UI: Sporepedia timeline card / asset view + the introsort + binary-heap
// template family it instantiates over 8-byte {Key,Value} pairs.
//
// Everything here is EA/Spore game code (not Havok). No PDB symbols survive for this VA range, so the
// names below are reconstructed from the string literals ("Sporepedia", "Simulator"), the vtable stores
// and the Ghidra/EA-slice conventions. The original was built with MSVC 2005-era /O2 /MD /arch:SSE.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

typedef unsigned char  uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int   uint32_t;
typedef unsigned int   uintptr_t;
typedef int            int32_t;

typedef int            hkBool;

// --------------------------------------------------------------------------------------- opaque bits
struct hkWorld; struct hkCollisionDispatcher; struct hkEntity; struct hkSimulationIsland;
struct hkAgentNnEntry; struct hkConstraintInstance;
class cImportExport; class Controller;

// cSPUILayout is a real Spore class; only the members this slice touches are declared.
class cSPUILayout
{
public:
    static void Init(void* self, const void* key, int a, unsigned int b);
    static void* FindWindowByID(void* self, unsigned int id, int a);
    static void Shutdown(void* self, int a);
};
namespace EA { namespace ResourceMan { struct Key_; } namespace Messaging { void RemoveHandler(); } }
namespace SP { namespace Thumbnail { class cImportExport; } namespace Achievements { class Controller; } }

// EAAllocate(size, tag, a,b,c,d) -- 0x00f473a0; operator_new is the game's tagged allocator.
extern "C" void* EAAllocate(unsigned int size, const char* tag, int, int, int, int);   // 0x00f473a0
extern "C" void  FUN_0066b050(void* p);                                                 // 0x0066b050
extern "C" void* FUN_00ef19f0();                                                        // 0x00ef19f0
extern "C" void  FUN_00b3d410(int a, void* b, int c);                                   // 0x00b3d410
extern "C" void  FUN_00e3e350(int a, void* b, int c);                                   // 0x00e3e350
extern "C" void* SP_MessageServer();                                                    // 0x0067dcc0
extern "C" void  UI_CalloutMessageBox(void* self, const char* text);                    // 0x00809db0
extern "C" void  FUN_00f2b3d0();                                                        // 0x00f2b3d0
void  FUN_00ec4e50_move(void* dst, const void* src, unsigned int n);                     // memmove-equivalent
void  FUN_00f2b340();                                                                    // 0x00f2b340
extern "C" void* FUN_005f7930();                                                        // 0x005f7930
extern "C" void* FUN_00675250(unsigned int key, int a = 0);                             // 0x00675250
extern "C" void  EA_ResourceMan_GetManager_v();                                         // (thunk used via vtable)
extern "C" void* EA_ResourceMan_GetManager();                                           // 0x00e2.. (manager getter)

void operator_delete_(void* p) { ::operator delete(p); }

// --------------------------------------------------------------------------------- heap/introsort ABI
// All the sort templates below operate on arrays of 8-byte records {uint32_t key; uint32_t value;}
// compared by (value, key) ascending -- the cut/copy sort family instantiated for EA::ResourceMan::Key_.

namespace SPUIHelpers
{
    void* CenterWindowInRect();                                     // 0x.. CenterWindowInRect
    void  BeginModal(void* window, int a, int b);                   // 0x.. BeginModal
    void  EndModal(void* window);                                   // 0x.. EndModal
}

// (cSPUILayout members declared above.)

namespace EA { namespace Stopwatch { void* Stopwatch(void* self, int a, int b); } }

// =====================================================================================================
// 0x00EC40B0 -- Sporepedia message registrar: allocate six tiny 3-slot messages and hand each to
// FUN_0066b050, which stores them in the Sporepedia messaging table.
// =====================================================================================================
// @ 0x00ec40b0
extern "C" void* FUN_00ec40b0()
{
    // Each block is {vptr, refcount, payload}; the vptr is the class's scalar-deleting-destructor table.
    struct Blk { void* vptr; void* refcount; uint32_t payload; };
    void* r = 0;

    Blk* a = (Blk*)EAAllocate(8, "Sporepedia", 0, 0, 0, 0);
    if (a) { a->refcount = 0; a->vptr = (void*)0x01489008; }
    FUN_0066b050(a);

    Blk* b = (Blk*)EAAllocate(8, "Sporepedia", 0, 0, 0, 0);
    if (b) { b->refcount = 0; b->vptr = (void*)0x01489028; }
    FUN_0066b050(b);

    for (uint32_t i = 0; i < 4; ++i)
    {
        Blk* c = (Blk*)EAAllocate(0xc, "Sporepedia", 0, 0, 0, 0);
        if (c) { c->refcount = 0; c->vptr = (void*)0x01489048;
                 c->payload = (i == 0) ? 0x190e18aa : (i == 1) ? 0x35c95bc4
                            : (i == 2) ? 0x11576eea : 0x5bd7a6a4; }
        FUN_0066b050(c);
        r = c;
    }
    (void)r;
    return r;
}

// =====================================================================================================
// UI::TimelineSporepediaCardData -- Sporepedia card window (size 0x8c).
//   +0x00 vptr  +0x10 vptr  +0x14 vptr  +0x18 ..  +0x78..0x7c flags  +0x80 int  +0x84 int  +0x88 int
// =====================================================================================================
namespace UI
{
    class TimelineSporepediaCardData
    {
    public:
        TimelineSporepediaCardData();
    };
    void TimelineSporepediaCardData_ctor(void* self);   // 0x00642100 (base ctor)
}

// @ 0x00ec41e0
void FUN_00642100(void*);            // base ctor at 0x00642100
UI::TimelineSporepediaCardData* UI_TimelineSporepediaCardData_ctor(UI::TimelineSporepediaCardData* self)
{
    void* p = self;
    FUN_00642100(p);

    uint8_t* b = (uint8_t*)p;
    b[0x78] = 0; b[0x79] = 0; b[0x7a] = 0; b[0x7b] = 0; b[0x7c] = 0;

    void** w = (void**)p;
    w[0x00 / 4] = (void*)0x01489090;
    w[0x10 / 4] = (void*)0x0148907c;
    w[0x14 / 4] = (void*)0x0148906c;

    *(int*)(b + 0x84) = 0x7fffffff;
    *(int*)(b + 0x88) = 0x7fffffff;
    *(int*)(b + 0x80) = -1;
    return self;
}

// @ 0x00ec42f0
void __fastcall UI_TimelineSporepediaCardData_sendMessage(void* self, int /*unused*/, uint32_t /*unused2*/)
{
    int* srv = (int*)SP_MessageServer();
    int* vt  = (int*)*srv;
    typedef void (*Fn)(void*, unsigned int, unsigned int, unsigned int);
    ((Fn)vt[0x14 / 4])(srv, 0xcc0bf725, *(unsigned int*)((char*)self + 0x80), 0);
}

// =====================================================================================================
// 0x00EC4330 -- set a 3-dword "card id" through the global card store and reset the view's state.
// =====================================================================================================
// @ 0x00ec4330
void FUN_00ec4330(void* self, uint32_t* id)
{
    uint32_t* slot = (uint32_t*)FUN_00ef19f0();
    slot[0] = id[0];
    slot[1] = id[1];
    slot[2] = id[2];
    slot[9]  = 1;
    slot[10] = 0;
    *(uint8_t*)((char*)self + 0x24) = 0;
    FUN_00b3d410(1, (void*)0x01654c10, 1);
    FUN_00e3e350(1, (void*)0x01654c10, 1);
    *(uint32_t*)((char*)self + 0x28) = 10;
}

// =====================================================================================================
// 0x00EC4380 -- pick the callout text for a card state (3 bools) and show it.
// =====================================================================================================
// @ 0x00ec4380
void FUN_00ec4380(void* self, char sel, char alt, char warn)
{
    void* box = (char*)self + 0x10;
    if (!sel)
    {
        *(uint32_t*)((char*)self + 0x90) = 3;
        if (warn) { UI_CalloutMessageBox(box, (const char*)0x015abc7c); return; }
        UI_CalloutMessageBox(box, (const char*)0x015abc70);
        return;
    }
    if (alt)
    {
        *(uint32_t*)((char*)self + 0x90) = 1;
        if (warn) { UI_CalloutMessageBox(box, (const char*)0x015abc4c); return; }
        UI_CalloutMessageBox(box, (const char*)0x015abc40);
        return;
    }
    *(uint32_t*)((char*)self + 0x90) = 2;
    if (warn) { UI_CalloutMessageBox(box, (const char*)0x015abc64); return; }
    UI_CalloutMessageBox(box, (const char*)0x015abc58);
}

// =====================================================================================================
// introsort / binary-heap templates over 8-byte {key,value} records, ordered by (value,key) ascending.
// =====================================================================================================
struct Rec { uint32_t key; uint32_t value; };

static inline bool less_rec(const Rec& a, const Rec& b)
{
    return a.value < b.value || (a.value == b.value && a.key < b.key);
}

// @ 0x00ec4430  -- find(first,last,val): returns matching record pointer or last
Rec* FUN_00ec4430(Rec* first, Rec* last, const Rec* val)
{
    const uint32_t k = val->key;
    const uint32_t v = val->value;
    while (first != last)
    {
        if (first->key == k && first->value == v)
            return first;
        ++first;
    }
    return first;
}

// @ 0x00ec4460
bool FUN_00ec4460(const Rec* a, const Rec* b, const Rec* c)
{
    while (true)
    {
        if (a == b)
            return true;
        if (a->key != c->key || a->value != c->value)
            return false;
        ++a; ++c;
    }
}

// @ 0x00ec44a0  -- insertion sort
void FUN_00ec44a0(Rec* first, Rec* last)
{
    if (first == last) return;
    for (Rec* cur = first + 1; cur != last; ++cur)
    {
        Rec v = *cur;
        Rec* p = cur;
        while (p != first)
        {
            Rec* prev = p - 1;
            if (less_rec(*prev, v)) break;
            *p = *prev;
            --p;
        }
        *p = v;
    }
}

// @ 0x00ec4500  -- backwards insertion sort
void FUN_00ec4500(Rec* first, Rec* last)
{
    for (Rec* cur = first; cur != last; ++cur)
    {
        Rec v = *cur;
        Rec* p = cur - 1;
        while (p >= first && less_rec(v, *p))
        {
            *(p + 1) = *p;
            --p;
        }
        *(p + 1) = v;
    }
}

// @ 0x00ec4570  -- median-of-three (EASTL median(a,b,c,comp))
Rec* FUN_00ec4570(Rec* a, Rec* b, Rec* c)
{
    if (less_rec(*a, *b))
    {
        if (less_rec(*b, *c)) return b;
        if (less_rec(*a, *c)) return c;
        return a;
    }
    if (less_rec(*a, *c)) return a;
    if (less_rec(*b, *c)) return c;
    return b;
}

// @ 0x00ec45f0  -- push_heap on [root, hole)
void FUN_00ec45f0(Rec* base, int root, int hole, uint32_t key, uint32_t value)
{
    while (hole > root)
    {
        int parent = (hole - 1) >> 1;
        const Rec& pv = base[parent];
        if (pv.value > value || (pv.value == value && pv.key >= key)) break;
        base[hole] = pv;
        hole = parent;
    }
    base[hole].key = key;
    base[hole].value = value;
}

// @ 0x00ec4650
void FUN_00ec4650(void* self)
{
    int* srv = (int*)SP_MessageServer();
    void* ctx = (self == 0) ? 0 : (char*)self + 8;
    *(int**)((char*)self + 0x94)  = srv;
    *(void**)((char*)self + 0x98) = ctx;
    *(void**)((char*)self + 0x9c) = (void*)0x0148918c;
    *(uint32_t*)((char*)self + 0xa0) = 10;
    *(uint32_t*)((char*)self + 0xa4) = 0;

    if (srv != 0 && ctx != 0)
    {
        int* vt = (int*)*srv;
        typedef void (*Fn)(void*, void*, void*);
        for (uint32_t off = 0; off < 0x28; off += 4)
            ((Fn)vt[0x24 / 4])(srv, *(void**)((char*)0x0148918c + off), ctx);
    }
}

// @ 0x00ec46c0
char FUN_00ec46c0(void* self)
{
    if (*(int*)((char*)self + 0x18) == 0 || *(int*)(*(int*)((char*)self + 0x18) + 8) == 0)
        return 0;

    int* mgr = (int*)EA_ResourceMan_GetManager();
    int* obj = (int*)((int(*)(void*, void*))((int*)*mgr)[0x58 / 4])(mgr, (char*)*(int*)((char*)self + 0x18) + 8);
    if (obj == 0) return 0;

    if ((((unsigned int(*)(void*))((int*)*obj)[0x20 / 4])(obj) & 2) != 0)
    {
        FUN_00f2b3d0();
        FUN_00f2b340();
        int* mgr2 = (int*)EA_ResourceMan_GetManager();
        char r = (char)((int(*)(void*, void*, void*, void*, void*, void*))((int*)*mgr2)[0x20 / 4])(
                     mgr2, *(void**)((char*)self + 0x18), 0, obj, 0, 0);
        SP::Thumbnail::cImportExport* ie = (SP::Thumbnail::cImportExport*)FUN_005f7930();
        if (ie == 0) return 0;
        typedef void (*UpdFn)(void*, void*);
        ((UpdFn)(*(void***)ie)[1])(ie, (char*)*(int*)((char*)self + 0x18) + 8);
        return r;
    }
    return 0;
}

// @ 0x00ec4750
void FUN_00ec4750(void* self)
{
    if (*(int*)((char*)self + 0x1c) != 1 && *(int*)((char*)self + 0x1c) != 2)
        return;

    unsigned int key[3] = { 0x2d3d4971u, 0x0510a95bu, 0x40464100u };
    void* win = 0;
    void* mem = EAAllocate(0x18, "Simulator", 0, 0, 0, 0);
    if (mem) win = SPUIHelpers::CenterWindowInRect();

    void* old = *(void**)((char*)self + 0x74);
    if (win != old)
    {
        if (win) ((void(*)(void*))(*(void***)win)[1])(win);
        *(void**)((char*)self + 0x74) = win;
        if (old) ((void(*)(void*))(*(void***)old)[2])(old);
    }

    cSPUILayout::Init(*(void**)((char*)self + 0x74), key, 0, 0x5b598f7u);
    void* w1 = cSPUILayout::FindWindowByID(*(void**)((char*)self + 0x74), 0x75e0a00u, 1);
    void* w2 = cSPUILayout::FindWindowByID(*(void**)((char*)self + 0x74), 0x75e0a58u, 1);

    if (*(int*)((char*)self + 0x1c) == 1)
    {
        if (w1) ((void(*)(void*, int, int))(*(void***)w1)[0x7c / 4])(w1, 1, 1);
        if (!w2) goto done;
        if (w2) ((void(*)(void*, int, int))(*(void***)w2)[0x7c / 4])(w2, 1, 0);
    }
    else
    {
        if (*(int*)((char*)self + 0x1c) != 2) goto done;
        if (w1) ((void(*)(void*, int, int))(*(void***)w1)[0x7c / 4])(w1, 1, 0);
        if (!w2) goto done;
        ((void(*)(void*, int, int))(*(void***)w2)[0x7c / 4])(w2, 1, 1);
    }
done:
    {
        void* w3 = cSPUILayout::FindWindowByID(*(void**)((char*)self + 0x74), 0x7299020u, 1);
        if (w3 == 0)
        {
            cSPUILayout::Shutdown(*(void**)((char*)self + 0x74), 1);
            void* lay = *(void**)((char*)self + 0x74);
            if (lay)
            {
                *(void**)((char*)self + 0x74) = 0;
                ((void(*)(void*))(*(void***)lay)[2])(lay);
            }
        }
        else
        {
            ((void(*)(void*, void*))(*(void***)w3)[0x104 / 4])(w3, (char*)self + 0xc);
            SPUIHelpers::BeginModal(w3, 0, 1);
        }
    }
    int* srv = (int*)SP_MessageServer();
    typedef void (*Fn)(void*, unsigned int, unsigned int, unsigned int);
    ((Fn)((int*)*srv)[0x14 / 4])(srv, 0xcc0bf725u, 10, 0);
}

// @ 0x00ec48c0
int FUN_00ec48c0(int* a, int* b)
{
    if ((((b[1] - *b) ^ (a[1] - *a)) & 0xfffffff8u) == 0)
    {
        if (FUN_00ec4460((Rec*)*a, (Rec*)a[1], (Rec*)*b))
            return 0;
    }
    return 1;
}

// @ 0x00ec4900  -- adjust_heap
void FUN_00ec4900(Rec* base, int root, int len, int hole, uint32_t key, uint32_t value)
{
    int child = hole * 2 + 2;
    while (child < len)
    {
        if (less_rec(base[child], base[child - 1]))
            --child;
        base[hole] = base[child];
        hole = child;
        child = hole * 2 + 2;
    }
    if (child == len)
    {
        base[hole] = base[len - 1];
        hole = child - 1;
    }
    FUN_00ec45f0(base, root, hole, key, value);
}

// @ 0x00ec4980
void FUN_00ec4980(void* self)
{
    void** p = (void**)self;
    p[0] = (void*)0x014891f4;
    p[2] = (void*)0x014891ec;
    p[3] = (void*)0x014891d0;
    p[4] = (void*)0x014891c4;
    p[5] = (void*)0x014891b4;

    int h = (int)p[0x25];
    if (h != 0)
    {
        p[0x25] = 0;
        EA::Messaging::RemoveHandler();
    }
    if ((int*)p[0x1d] != 0)
        ((void(*)(void*))(*(void***)p[0x1d])[2])(p[0x1d]);

    int v;
    v = (int)p[0x18]; if (v != 0 && *(int*)(v - 4) != 0) operator_delete_((void*)v);
    v = (int)p[0x13]; if (v != 0 && *(int*)(v - 4) != 0) operator_delete_((void*)v);
    v = (int)p[0xd];  if (v != 0 && *(int*)(v - 4) != 0) operator_delete_((void*)v);
    if ((int*)p[6] != 0)
        ((void(*)(void*))(*(void***)p[6])[1])(p[6]);

    p[3] = (void*)0x01489180;   // vtbl_Editor::cEditorResource
    p[2] = (void*)0x0148918c;   // vtbl_Skinner::PaintSystem
    p[0] = (void*)0x014891f4;   // vtbl_Simulator::cContentValidationSummarizer
}

// @ 0x00ec4ac0  -- lower_bound over 8-byte records
void* FUN_00ec4ac0(void* first, void* last, const void* val)
{
    int len = (int)((char*)last - (char*)first) >> 3;
    if (len > 0)
    {
        const uint32_t vv = ((const Rec*)val)->value;
        const uint32_t vk = ((const Rec*)val)->key;
        do
        {
            int half = len >> 1;
            Rec* mid = (Rec*)first + half;
            if (mid->value < vv || (mid->value == vv && mid->key < vk))
            {
                first = mid + 1;
                len -= half + 1;
            }
            else
            {
                len = half;
            }
        } while (len > 0);
    }
    return first;
}

// @ 0x00ec4b10  -- make_heap
void FUN_00ec4b10(void* first, void* last)
{
    int n = (int)((char*)last - (char*)first) >> 3;
    if (n < 2) return;
    for (int parent = (n - 2) / 2; parent >= 0; --parent)
    {
        Rec v = ((Rec*)first)[parent];
        FUN_00ec4900((Rec*)first, parent, n, parent, v.key, v.value);
    }
}

// @ 0x00ec4b50  -- sort_heap
void FUN_00ec4b50(Rec* first, Rec* last)
{
    int n = (int)(last - first);
    if (n < 2) return;
    Rec* end = last - 1;
    while (true)
    {
        Rec v = *end;
        *end = *first;
        FUN_00ec4900(first, 0, n - 1, 0, v.key, v.value);
        --end;
        n = (int)(end - first) + 1;
        if (n < 2) break;
    }
}

// @ 0x00ec4bb0
void* FUN_00ec4bb0(void* self)
{
    void** p = (void**)self;
    p[1] = 0;
    p[2] = (void*)0x0148918c;
    p[3] = (void*)0x01489180;
    p[5] = (void*)0x0148917c;
    p[0] = (void*)0x014891f4;
    p[2] = (void*)0x014891ec;
    p[3] = (void*)0x014891d0;
    p[4] = (void*)0x014891c4;
    p[5] = (void*)0x014891b4;
    p[6] = 0;
    p[7] = 0;
    p[8] = 0;
    *(uint8_t*)(p + 9) = 0;
    p[10] = 0;
    p[0xb] = 0;
    *(uint8_t*)(p + 0xc) = 0;
    p[0xd] = 0;
    p[0xe] = 0;
    p[0xf] = 0;
    p[0x12] = 0;
    p[0x13] = 0;
    p[0x14] = 0;
    p[0x15] = 0;
    p[0x18] = 0;
    p[0x19] = 0;
    p[0x1a] = 0;
    p[0x1d] = 0;
    EA::Stopwatch::Stopwatch(p + 0x1e, 4, 0);
    p[0x24] = 0;
    p[0x25] = 0;
    p[0x26] = 0;
    p[0x27] = 0;
    p[0x28] = 0;
    p[0x29] = 0;
    return self;
}

// @ 0x00ec4c80
void FUN_00ec4c80(void* self)
{
    if (*(void**)((char*)self + 0x74) != 0)
    {
        void* w = cSPUILayout::FindWindowByID(*(void**)((char*)self + 0x74), 0x7299020u, 1);
        SPUIHelpers::EndModal(w);
        cSPUILayout::Shutdown(*(void**)((char*)self + 0x74), 0);
        void* lay = *(void**)((char*)self + 0x74);
        if (lay)
        {
            *(void**)((char*)self + 0x74) = 0;
            ((void(*)(void*))(*(void***)lay)[2])(lay);
        }
    }
    int* srv = (int*)SP_MessageServer();
    typedef void (*Fn)(void*, unsigned int, void*, unsigned int);
    ((Fn)((int*)*srv)[0x14 / 4])(srv, 0xcc0bf724u, 0, 0);
}

// @ 0x00ec4d30  -- upper_bound over 8-byte records
void* FUN_00ec4d30(void* first, void* last, uint32_t* val)
{
    void* lb = FUN_00ec4ac0(first, last, val);
    if (lb == last) return last;
    if (!less_rec(*(Rec*)val, *(Rec*)lb)) return lb;
    return last;
}

// @ 0x00ec4d70  -- partition; returns the final first-pointer
Rec* FUN_00ec4d70(Rec* first, Rec* last, uint32_t key, uint32_t value)
{
    Rec val; val.key = key; val.value = value;
    while (true)
    {
        while (true)
        {
            if (!less_rec(*first, val)) break;   // first->value >= value
            ++first;
        }
        Rec* back = last - 1;
        while (back >= first)
        {
            if (back->value < value || (back->value == value && back->key <= key))
                break;
            --back;
        }
        if (back <= first)
            return first;
        Rec t = *first; *first = *back; *back = t;
        ++first;
        last = back;
    }
}

// @ 0x00ec4de0  -- partial_sort
void FUN_00ec4de0(Rec* first, Rec* middle, Rec* last)
{
    FUN_00ec4b10(first, middle);
    for (Rec* it = middle; it < last; ++it)
    {
        if (less_rec(*it, *first))
        {
            Rec v = *it;
            *it = *first;
            FUN_00ec4900(first, 0, (int)(middle - first), 0, v.key, v.value);
        }
    }
    FUN_00ec4b50(first, middle);
}

// @ 0x00ec4e50
void* FUN_00ec4e50(void* self, char* pos)
{
    char* src = pos + 8;
    char* end = *(char**)((char*)self + 4);
    if (src < end)
        FUN_00ec4e50_move(pos, src, (unsigned int)(end - src));
    *(char**)((char*)self + 4) = end - 8;
    return pos;
}

// @ 0x00ec4e80  -- introsort loop
void FUN_00ec4e80(Rec* first, Rec* last, int depth)
{
    while ((char*)last - (char*)first > 0xe0 && depth > 0)
    {
        Rec* pivot = FUN_00ec4570(first, first + ((last - first) / 2), last - 1);
        Rec* mid = FUN_00ec4d70(first, last, pivot->key, pivot->value);
        --depth;
        FUN_00ec4e80(mid, last, depth);
        last = mid;
    }
    if (depth == 0)
        FUN_00ec4de0(first, last, last);
}

// @ 0x00ec4f00  -- sort dispatcher
void FUN_00ec4f00(Rec* first, Rec* last)
{
    if (first == last) return;
    int n = (int)(last - first);
    int depth = 0;
    for (int t = n; t != 0; t >>= 1) ++depth;
    FUN_00ec4e80(first, last, depth * 2 - 2);
    if (n > 0x1c)
    {
        FUN_00ec44a0(first, first + 0x1c);   // 0xe0 bytes = 0x1c records
        FUN_00ec4500(first + 0x1c, last);
    }
    else
    {
        FUN_00ec44a0(first, last);
    }
}

// @ 0x00ec4f70
void FUN_00ec4f70(void* self, char notify, int param)
{
    *(uint8_t*)((char*)self + 0x24) = 0;

    if (*(int*)((char*)self + 0x1c) == 1)
    {
        int* o = *(int**)((char*)self + 0x18);
        if (o) { *(void**)((char*)self + 0x18) = 0;
                 ((void(*)(void*))(*(void***)o)[1])(o); }
        *(uint32_t*)((char*)self + 0x1c) = 0;
        *(uint32_t*)((char*)self + 0x2c) = 6;
        char* b = *(char**)((char*)self + 0x38);
        char* e = *(char**)((char*)self + 0x34);
        *(char**)((char*)self + 0x38) = b + ((b - e) >> 3) * -8;
        if (*(void**)((char*)self + 0x74) != 0)
            FUN_00ec4c80(self);
        *(uint32_t*)((char*)self + 0x78) = 0;
        *(uint32_t*)((char*)self + 0x7c) = 0;
        *(uint32_t*)((char*)self + 0x80) = 0;
        *(uint32_t*)((char*)self + 0x84) = 0;
        if (param == 0) param = 1;
        *(int*)((char*)self + 0x20) = param;
        if (notify)
        {
            int* srv = (int*)SP_MessageServer();
            typedef void (*Fn)(void*, unsigned int, void*, unsigned int);
            ((Fn)((int*)*srv)[0x14 / 4])(srv, 0xcc0bf723u, &param, 0);
        }
    }
    else if (*(int*)((char*)self + 0x1c) == 2)
    {
        int o2 = *(int*)((char*)self + 0x18);
        uint32_t v0 = *(uint32_t*)(o2 + 8);
        uint32_t v1 = *(uint32_t*)(o2 + 0xc);
        uint32_t v2 = *(uint32_t*)(o2 + 0x10);
        int* o = *(int**)((char*)self + 0x18);
        if (o) { *(void**)((char*)self + 0x18) = 0;
                 ((void(*)(void*))(*(void***)o)[1])(o); }
        *(uint32_t*)((char*)self + 0x1c) = 0;
        *(uint32_t*)((char*)self + 0x48) = 5;

        char* e = *(char**)((char*)self + 0x50);
        char* b = *(char**)((char*)self + 0x4c);
        char* q = *(char**)((char*)self + 0x64);
        char* r = *(char**)((char*)self + 0x60);
        *(char**)((char*)self + 0x64) = q + ((q - r) >> 3) * -8;
        (void)e; (void)b;

        *(int*)((char*)self + 0x20) = param;
        if (notify)
        {
            uint32_t msg[4] = { 0, v0, v1, v2 };
            int* srv = (int*)SP_MessageServer();
            typedef void (*Fn)(void*, unsigned int, void*, unsigned int);
            ((Fn)((int*)*srv)[0x14 / 4])(srv, 0x068cd252u, msg, 0);
        }
        if (*(void**)((char*)self + 0x74) != 0)
            FUN_00ec4c80(self);
        *(uint32_t*)((char*)self + 0x78) = 0;
        *(uint32_t*)((char*)self + 0x7c) = 0;
        *(uint32_t*)((char*)self + 0x80) = 0;
        *(uint32_t*)((char*)self + 0x84) = 0;
    }
}

// @ 0x00ec5100
void FUN_00ec5100(void* self)
{
    int o = *(int*)((char*)self + 0x18);
    char flag = *(char*)((char*)self + 0x24);
    *(uint32_t*)((char*)self + 0x2c) = 6;

    uint32_t id[3] = { 0, 0, 0 };
    if (o != 0) { id[0] = *(uint32_t*)(o + 8); id[1] = *(uint32_t*)(o + 0xc); id[2] = *(uint32_t*)(o + 0x10); }

    FUN_00ec4f70(self, 1, 2);
    if (flag) FUN_00ec4330(self, id);
}

// @ 0x00ec5160
void FUN_00ec5160(void* self)
{
    *(uint32_t*)((char*)self + 0x48) = 5;
    FUN_00ec4f70(self, 0, 0);
    FUN_00675250(0x1881b6ecu);
    FUN_00675250(0x4a384f78u, 1);
}
