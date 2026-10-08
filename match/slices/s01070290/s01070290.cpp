// Slice s01070290 -- cSPUISpace tool-button / property-list initialisation (0x01070290).
// Module flags: /O2 /MD /Gy /TP (no /EHsc; stack realigned with "and esp,-8")
#include "types.h"

inline void* operator new(size_t, void* p) { return p; }
inline void operator delete(void*, void*) {}
void* __cdecl operator new(size_t, const char*, int, int, int, int);   // 0x00f473a0

// ---------------------------------------------------------------- vtable helpers
template <int N, class R> inline R VCall0(void* p)
{ return ((R(__thiscall*)(void*))(*(void***)p)[N])(p); }
template <int N, class R, class A> inline R VCall1(void* p, A a)
{ return ((R(__thiscall*)(void*, A))(*(void***)p)[N])(p, a); }
template <int N, class R, class A, class B> inline R VCall2(void* p, A a, B b)
{ return ((R(__thiscall*)(void*, A, B))(*(void***)p)[N])(p, a, b); }

template <int N, class R, class A, class B, class C> inline R VCall3(void* p, A a, B b, C c)
{ return ((R(__thiscall*)(void*, A, B, C))(*(void***)p)[N])(p, a, b, c); }

struct Obj { char pad[4]; };
struct Key;        // opaque virtual object; every call goes through VCall*

template <int A, int R> __forceinline void AssignRef(Obj*& dst, Obj* v)
{
    Obj* old = dst;
    if (v != old) {
        if (v) VCall0<A, void>(v);
        dst = v;
        if (old) VCall0<R, void>(old);
    }
}

// ---------------------------------------------------------------- stub types
struct Key { unsigned a, b, c; };                    // 12-byte resource key
typedef bool (__thiscall *InitFn)(void*, void*, Key);  // vtable slot 7: Init(buffer, key)
#define INIT_CALL(o, buf, key) (((InitFn)(*(void***)(o))[7])((o), (buf), (key)))
extern Key      g_15b92ac;                           // 0x015b92ac
extern unsigned g_15b910c;                           // 0x015b910c
extern Key      g_15b942c;                           // 0x015b942c
extern Key      g_15b9438;                           // 0x015b9438

struct Property {
    char pad[0x12];
    unsigned short type;                             // +0x12
    unsigned* GetUInt();                             // 0x0041ea00
    bool*     GetBool();                             // 0x0041e920
};

// Owning pointer to a property list (AddRef slot 0 / Release slot 1). operator& resets, like
// the out-parameter smart pointers of the original.
struct RcPtr {
    Obj* p;
    RcPtr() : p(0) {}
    ~RcPtr() { if (p) VCall0<1, void>(p); }
    Obj** operator&()
    {
        Obj* t = *(Obj* volatile*)&p;
        if (t) { p = 0; VCall0<1, void>(t); }
        return &p;
    }
};

struct PropManager {
    // vtable slot 11 (+0x2c)
    bool GetList(unsigned id, unsigned group, Obj** out)
    { return VCall3<11, bool, unsigned, unsigned, Obj**>(this, id, group, out); }
};
PropManager* __cdecl PropertyManager();             // 0x0067de30

bool __cdecl GetPropArray(Obj* list, unsigned id, int* count, Key** arr);       // 0x006a0ae0
inline bool GetProp(Obj* list, unsigned id, Property** out)
{ return VCall2<9, bool, unsigned, Property**>(list, id, out); }                // vtable slot 9 (+0x24)

struct cString {
    char pad[0x1c];
    cString();                                       // 0x006b5060
    ~cString();                                      // 0x006b5240
    const wchar_t* GetText();                        // 0x006b55c0
};
bool __cdecl GetPropertyAsText(Obj* list, unsigned id, cString* out);           // 0x006a1360
void __cdecl SetTooltipText(Obj* window, const wchar_t* text, int a, int b);    // 0x00806de0

struct GlobalUI {
    Obj* FindWindowByID(unsigned id);                // 0x00e012b0 (ret 4)
    void* GetBuffer();                               // 0x0093b6c0
};

struct SpaceGame { Obj* GetPlayerInventory(); };    // 0x00a1ad60
SpaceGame* __cdecl SpaceGameGet();                   // 0x01002bd0

struct Dialog : Obj {                                // cConnectionDialog-like panel, 0x18 bytes
    char pad[0x14];
    Dialog();                                        // 0x00810000
    void Init(const Key* k, int a, int b);           // 0x008120d0 (ret 0xc)
};
struct ToolObjA : Obj { char pad[0x13c]; ToolObjA(); };   // 0x0106da70 (0x140)
struct ToolObjB : Obj { char pad[0x15c]; ToolObjB(); };   // 0x0106e2d0 (0x160)

struct MapResult { void* it; bool ok; };
struct MapEntry {
    unsigned key;
    Obj*     val;
    MapEntry(unsigned k, Obj* v) : key(k), val(v) { if (v) VCall0<0, void>(v); }
    ~MapEntry() { if (val) VCall0<1, void>(val); }
};
struct ObjMap { char pad[0x20]; void Insert(MapResult* r, const MapEntry* e, bool b); };        // 0x00ad9090 (ret 0xc)
struct UIntSet { char pad[0x18]; void Insert(MapResult* r, const unsigned* v); };               // 0x00554020 (ret 8)

struct UIntVec {
    unsigned* mpBegin; unsigned* mpEnd; unsigned* mpCapacity;
    void DoInsertValue(unsigned* pos, const unsigned& v);                       // 0x004558a0 (ret 8)
    inline void push_back(const unsigned& v)
    {
        if (mpEnd < mpCapacity) {
            if (mpEnd) *mpEnd = v;
            ++mpEnd;
        } else {
            DoInsertValue(mpEnd, v);
        }
    }
};

class Space {
public:
    char     pad0[0x224];
    GlobalUI* ui;             // +0x224
    char     pad228[0x10];
    Obj*     inventory;       // +0x238
    char     pad23c[4];
    UIntVec  tools;           // +0x240
    char     pad24c[8];
    Obj*     dialog;          // +0x254 (AddRef 1 / Release 2)
    char     pad258[4];
    ObjMap   objMap;          // +0x25c
    UIntSet  set27c;          // +0x27c
    Obj*     p294;            // +0x294
    Obj*     p298;            // +0x298
    Obj*     p29c;            // +0x29c

    void ToggleToolUI(unsigned id);                  // 0x0106e3e0 (ret 4)
    void Setup();                                    // 0x01070290
};

// @ 0x01070290
void Space::Setup()
{
    Obj* inv = SpaceGameGet()->GetPlayerInventory();
    Obj* inv2 = inv ? VCall1<3, Obj*, unsigned>(inv, 0x9073163b) : 0;
    AssignRef<0, 1>(inventory, inv2);

    Dialog* dlg = new ("UI", 0, 0, 0, 0) Dialog();
    AssignRef<1, 2>(dialog, (Obj*)dlg);
    ((Dialog*)dialog)->Init(&g_15b92ac, 0, 0x05b598fa);

    RcPtr list;
    PropManager* pm = PropertyManager();
    if (pm->GetList(0x22631cd0, 0x30608f0c, &list)) {
        int  count;
        Key* arr;
        if (GetPropArray(list.p, 0x98f1dfd8, &count, &arr)) {
            for (int i = 0; i < count; ++i) {
                RcPtr item;
                PropManager* pm2 = PropertyManager();
                if (pm2->GetList(arr[i].a, 0x30608f0c, &item)) {
                    Property* p1;
                    if (item.p && GetProp(item.p, 0x8f92bac3, &p1) && p1->type == 10) {
                        Obj* w = ui->FindWindowByID(*p1->GetUInt());
                        cString s;
                        if (w && GetPropertyAsText(item.p, 0x3068d95d, &s))
                            SetTooltipText(w, s.GetText(), -1, 1);
                    }
                    Property* p2;
                    if (item.p && GetProp(item.p, 0x7704db6f, &p2) && p2->type == 10) {
                        unsigned u = *p2->GetUInt();
                        tools.push_back(u);
                        Property* p3;
                        if (item.p && GetProp(item.p, 0x68f99898, &p3) && p3->type == 1 && *p3->GetBool()) {
                            MapResult r;
                            set27c.Insert(&r, &u);
                        }
                        int  count2;
                        Key* arr2;
                        if (GetPropArray(item.p, 0xf01ecafb, &count2, &arr2)) {
                            for (int j = 0; j < count2; ++j) {
                                Obj* o = (Obj*)new ("UI", 0, 0, 0, 0) ToolObjA();
                                VCall0<0, void>(o);
                                if (INIT_CALL(o, ui->GetBuffer(), arr2[j])) {
                                    MapResult r;
                                    MapEntry e(u, o);
                                    objMap.Insert(&r, &e, false);
                                    if (g_15b910c == arr2[j].a) {
                                        AssignRef<0, 1>(p294, o);
                                        Obj* t = p294;
                                        VCall1<12, void, int>(t, VCall0<34, int>(inventory));
                                    }
                                }
                                VCall0<1, void>(o);
                            }
                        }
                    }
                }
            }
        }
    }

    // the two preview/effect helpers
    {
        ToolObjA* d = new ("UI", 0, 0, 0, 0) ToolObjA();
        if (d) {
            *(unsigned*)d = 0x0149c33c;
            ((unsigned*)d)[1] = 0x0149c2d0;
            ((unsigned*)d)[3] = 0x0149c334;
        }
        AssignRef<0, 1>(p298, (Obj*)d);
        Obj* t = p298;
        if (INIT_CALL(t, ui->GetBuffer(), g_15b942c))
            VCall0<9, void>(p298);
        else if (p298) {
            Obj* q = p298;
            p298 = 0;
            VCall0<1, void>(q);
        }
    }
    {
        ToolObjB* d = new ("UI", 0, 0, 0, 0) ToolObjB();
        AssignRef<0, 1>(p29c, (Obj*)d);
        Obj* t = p29c;
        if (INIT_CALL(t, ui->GetBuffer(), g_15b9438))
            VCall0<9, void>(p29c);
        else if (p29c) {
            Obj* q = p29c;
            p29c = 0;
            VCall0<1, void>(q);
        }
    }
    ToggleToolUI(*tools.mpBegin);
}
