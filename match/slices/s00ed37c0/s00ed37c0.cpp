// Slice s00ed37c0 -- Scenario "cast" palette panel: Setup (0x00ed3c00) plus the
// record-map / message-listener helpers (0x00ed37c0 .. 0x00ed4200).
// Module flags: /O2 /MD /Gy /TP
#include "types.h"

// ---------------------------------------------------------------- vtable helpers
// Raw virtual call through slot N of an object whose vtable is not declared here.
template <int N> inline void VCall(void* p)
{
    ((void(__thiscall*)(void*))(*(void***)p)[N])(p);
}
template <int N, class R> inline R VCall1(void* p, unsigned a)
{
    return ((R(__thiscall*)(void*, unsigned))(*(void***)p)[N])(p, a);
}

// Generic intrusive pointer assignment as the original code spelled it inline:
// AddRef the new value (slot A), store, Release the old one (slot R).
template <int A, int R, class T> inline void AssignRef(T*& dst, T* v)
{
    T* old = dst;
    if (v != old) {
        if (v) VCall<A>(v);
        dst = v;
        if (old) VCall<R>(old);
    }
}

inline void* operator new(size_t, void* p) { return p; }
inline void operator delete(void*, void*) {}

inline const int& MaxRef(const int& a, const int& b) { return b < a ? a : b; }

// ---------------------------------------------------------------- stub types
struct Any { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); };

// Palette item entry stored in the 0x5c / 0x70 vectors (20 bytes).
struct PalEntry {
    Any* item;   // +0  (AddRef slot 1, Release slot 2)
    Any* pal;    // +4  (AddRef slot 2, Release slot 3)
    int  cat;    // +8
    int  row;    // +0xc
    int  idx;    // +0x10
    PalEntry() : item(0), pal(0) {}
    ~PalEntry()
    {
        if (pal)  VCall<3>(pal);
        if (item) VCall<2>(item);
    }
};

struct PalVec {
    PalEntry* mpBegin;
    PalEntry* mpEnd;
    PalEntry* mpCapacity;
    int       alloc;
    int       pad;
    void DoInsertValue(PalEntry* pos, const PalEntry& v);   // 0x00ed2d00 (thiscall, ret 8)
    __forceinline void push_back()
    {
        if (mpEnd < mpCapacity) {
            ::new (mpEnd++) PalEntry();
        } else {
            DoInsertValue(mpEnd, PalEntry());
        }
    }
};

void* __cdecl operator new(size_t, const char*, int, int, int, int);   // 0x00f473a0

struct Layout { Any* GetWorldMainWindow(unsigned id); };               // 0x00810620
Layout* __cdecl GetLayoutManager();                                    // 0x00805070

struct Row {                         // element of Category::rows (+0x34/+0x38 = item pointers)
    char  pad[0x34];
    void** itemsBegin;
    void** itemsEnd;
    void* GetItem(int i);            // 0x005cae30
};
struct RowCell { Row* row; int pad; };

struct Category : Any {              // cSPPalette
    char    pad4[0x84];
    RowCell* rowsBegin;              // +0x88
    RowCell* rowsEnd;                // +0x8c
    bool Init(const void* key, int a, int b, int c, int d, int e, int f);   // 0x005c6340 (ret 0x1c)
    void AddRowLike(int src);        // 0x005c50b0
    Row* GetRow(int i);              // 0x005c2e50
};

struct PaletteUI : Any {             // cSPPaletteUI (0x6c)
    PaletteUI();                     // 0x005cb3b0
    char  pad4[0x30];
    Category** catBegin;             // +0x34
    Category** catEnd;               // +0x38
    void Init(Category* pal, Any* mainWin, int a, Any* b);   // 0x005cb5a0 (ret 0x10)
    void SetVisible(int v);          // 0x005ca900 (ret 4)
    int  FindCategoryIndex();        // 0x005ca9c0
    Category* GetCategory(int i);    // 0x005cae30
    uint32_t tail[12];
};

struct CastPanel : Any { uint32_t pad[15]; CastPanel(); };                    // 0x005c5e30 (0x40)
struct ToolObj : Any { uint32_t pad[51]; ToolObj(); };                        // 0x00eccaf0 (0xd0)
struct Obj34 : Any {                                        // 0x005c64e0 (0x34)
    uint32_t pad[12];
    Obj34();
};
struct Obj34Fields {
    void* vt;
    int   rc;
    Any*  doc;       // +8 (refcounted, rc at +4, deleting dtor slot 0)
    int   pad0c;
    Any*  f10;       // +0x10 (release slot 1)
    Any*  f14;       // +0x14 (AddRef 0 / Release 1)
    unsigned short w18;
    char  pad1a[0x17];
    char  b31;
};
struct DocRC { void* vt; int rc; };
struct ItemUI : Any { uint32_t pad[8]; ItemUI(Any* item); };                 // 0x00ece870 (0x24)
struct AvatarUI : Any {
    uint32_t pad[14];
    AvatarUI();            // 0x00ed0ab0
    void Setup(int a);     // 0x00ed1880
};

struct MsgServer { void Register(void* listener, unsigned id); };   // vtable slot 9

MsgServer* __cdecl MessageServer();                          // 0x0067dcc0

struct CallbackBase {                                        // EA::CallbackSystem::Callback
    char pad[0x20];
    CallbackBase(int a, int b, int c, int d, int e, int f, int g);   // 0x00929e70 (ret 0x1c)
    void Set(void* fn, void* obj, int flag);                 // 0x00929da0 (ret 0xc)
    virtual ~CallbackBase();
};
class Scn;
struct ScnCallback : CallbackBase {
    Scn*  owner;     // +0x24
    void* fn;        // +0x28
    int   extra;     // +0x2c
    ScnCallback(Scn* o) : CallbackBase(0, 0, 0x16, 0, 2, 0, 0)
    {
        fn = (void*)0x00ed33f0;
        extra = 0;
        owner = o;
        Set((void*)0x00ed1cf0, this, 0);
    }
    virtual ~ScnCallback() {}
};

struct Globals { char pad[0x74]; struct Sub* sub; };
struct Sub { char pad[0x10]; char* db; char pad2[0xbc]; Any* doc; };
extern Globals* g_16c7aa4;                                   // 0x016c7aa4

struct ResKey { unsigned instance, type, group; };

// ---------------------------------------------------------------- scenario record map
// The scenario "record" container is a sorted vector of 0x27e8-byte elements; the
// element's sort key lives at +0x20.  The map header mirrors a std::vector header
// (begin/end/capacity/alloc) plus a flags byte at +0x14.
struct Record   { char pad[0x27e8]; };
struct RecordMap {
    Record* mpBegin;         // +0x00
    Record* mpEnd;           // +0x04
    Record* mpCapacity;      // +0x08
    int     allocA;          // +0x0c
    int     allocB;          // +0x10
    uint8_t flags;           // +0x14
    Record* Find(int* key);  // 0x00ed37c0 (find-or-insert; returns &record->f8)
};

// callees shared with the record-map / palette code (SLICE s00ed2600).
extern "C" {
    void* __stdcall FUN_00ed1f00(void* tab, int key);            // 0x00ed1f00 (find by key)
    int   __cdecl   FUN_00ed29b0(Record* a, Record* b, int* key, int flag);  // 0x00ed29b0 (lower_bound)
    Record* __cdecl FUN_00ed3740(RecordMap* self, Record* pos, int* key);    // 0x00ed3740 (insert)
    void  __cdecl   FUN_00ed3120(void* self, void* item, int one);           // 0x00ed3120 (select)
}
Record* __cdecl FUN_00f2d260(Record* p);                         // 0x00f2d260 (construct element)
char*   __cdecl FUN_00dff1a0(char* dst, char* src);              // 0x00dff1a0 (copy-construct)
void    __cdecl FUN_00dfce90(void* p);                           // 0x00dfce90 (destroy element)
int     __cdecl FUN_00eece20(int key);                           // 0x00eece20 (key -> icon)
void*   __cdecl FUN_00ed1f70(void* tab, int key);                // 0x00ed1f70 (insert into vec)
Record* __cdecl FUN_00ed1ec0(RecordMap* self);                   // 0x00ed1ec0


class Scn {
public:
    char       pad0[8];
    char       listener[0x1c];        // +8 .. message listener sub-object
    MsgServer* server;                // +0x24
    void*      lstn;                  // +0x28
    const void* lstnName;             // +0x2c
    int        lstnFlag;              // +0x30
    int        lstnZero;              // +0x34
    Any*       mainWin;               // +0x38
    CastPanel* castPanel;             // +0x3c
    PaletteUI* paletteUI;             // +0x40
    int        pad44[2];
    AvatarUI*  avatarUI;              // +0x4c
    Any*       tool;                  // +0x50
    int        pad54;
    ScnCallback* callback;            // +0x58
    PalVec     vecA;                  // +0x5c
    PalVec     vecB;                  // +0x70

    void Finish();                    // 0x00ed3a00
    void SelectCategory(Category* cat, int one);   // 0x00ed3120 (ret 8)
    bool Setup();                     // 0x00ed3c00
};

extern const unsigned kMsgIds[];   // 0x01489bb4 (message id table)

// ---------------------------------------------------------------- message-view callees
MsgServer* __cdecl MessageServer();                              // 0x0067dcc0 (already above)
Any*  __cdecl FUN_00ed1d20(Any* mainWin);                        // 0x00ed1d20 (mainWin -> palette UI)
int   __cdecl FUN_00f46450(int key);                             // 0x00f46450
int   __cdecl FUN_00f43af0(int key);                             // 0x00f43af0
Any*  __cdecl FUN_00f3e8a0(void* db, int key);                   // 0x00f3e8a0 (key -> node)
void  __cdecl FUN_00f40370(void* node);                          // 0x00f40370 (ScenarioNode clear+propagate)
int   __cdecl FUN_00f42580(int key);                             // 0x00f42580
void  __cdecl FUN_00f427c0(void* node);                          // 0x00f427c0
void  __cdecl FUN_00f45970(void* node);                          // 0x00f45970
void  __cdecl FUN_00f45a80(void* node);                          // 0x00f45a80
void  __cdecl FUN_00f455e0(void* node, int key);                 // 0x00f455e0
void* __cdecl FUN_00f00790(void* self, int key);                 // 0x00f00790 (ApplyPlacement)
int   __cdecl GetAllocator(void* obj);                           // 0x007f54d0 (__thiscall obj->GetAllocator)
bool  __cdecl FUN_00ecdb80(void* obj);                           // 0x00ecdb80
void* __cdecl FUN_00ed21f0(void* p);                             // 0x00ed21f0
void* __cdecl FUN_00ed21d0(void* p);                             // 0x00ed21d0
void  __cdecl FUN_00ed2600(void* self, void* a, int b);          // 0x00ed2600
void  __cdecl FUN_00ed3350(void* self, int key);                 // 0x00ed3350
void  __cdecl FUN_00ed33a0(void* self, int key);                 // 0x00ed33a0
void  __cdecl FUN_00ed2410(void* self, void* a, void* b, void* c); // 0x00ed2410
void  __cdecl FUN_00ece300(void* item);                          // 0x00ece300
void* __cdecl FUN_01137690(Any* p);                              // 0x01137690
void  __cdecl FUN_00eef810(void* out, void* a, int b, int c);    // 0x00eef810
void  __cdecl FUN_00dfed90(void* dst, void* src);                // 0x00dfed90
void* __cdecl FUN_00ecdbb0(void* p);                             // 0x00ecdbb0

// ---------------------------------------------------------------- message-view layouts
// The scenario panel listener is entered by the message server with `ecx` pointing
// at its listener sub-object.  ProcessMessage's `this` sits 8 bytes into that
// sub-object, so the helpers are reached with `ecx = this - 8`.  Modelling the two
// views explicitly keeps every field access named.
struct ScnRecBody {                 // helper view (ecx == ProcessMessage this - 8)
    char   pad5c[0x5c];
    PalVec palVecA;                 // +0x5c (== ProcessMessage +0x54)
    PalVec palVecB;                 // +0x70 (== ProcessMessage +0x68)
    void Finish();                  // 0x00ed3a00
    void RemoveIcon(int key);       // 0x00ed38a0
    void ClearTwo(int key);         // 0x00ed3920
    void DeselectTwo(int key);      // 0x00ed39a0
    void ChooseSubCategory(void* sub, int key);  // 0x00ed3b20
};

struct ScnRec {                     // ProcessMessage view (this == ScnRecBody + 8)
    char   pad00[0x38];
    Any*   mainWin;                 // +0x38
    PalVec palVec0;                 // +0x54 (== ScnRecBody +0x4c)
    PalVec palVec1;                 // +0x68 (== ScnRecBody +0x60)
    char   pad7c[0x1e24];
    bool   ProcessMessage(unsigned id, Any* arg);   // 0x00ed4200
};

// cSPPaletteUI view used by ProcessMessage (vtable-driven).
struct PaletteCtrl {
    void** vt;
    int   GetCurrentCategoryIndex();          // 0x005ca9c0 (slot)
    void* GetSubCategory(int i);              // 0x005cae30
};

// @ 0x00ed3c00 -- Scn::Setup
bool Scn::Setup()
{
    AssignRef<0, 1>(mainWin, GetLayoutManager()->GetWorldMainWindow(0x08d0f4fb));

    castPanel = new ("Simulator/Scenario/CastPanel", 0, 0, 0, 0) CastPanel();
    VCall<1>(castPanel);
    paletteUI = new ("Simulator/Scenario/CastPanelUI", 0, 0, 0, 0) PaletteUI();
    VCall<0>(paletteUI);

    Category* pal;
    {
        Any* sub = castPanel ? (Any*)((char*)castPanel + 8) : 0;
        pal = sub ? VCall1<3, Category*>(sub, 0x12dca0ea) : 0;
    }
    ResKey key;
    key.type     = 0x00b1b104;
    key.group    = 0x406b6a00;
    key.instance = 0xb4;
    if (pal->Init(&key, -1, 0, 0, 0, 0, 0)) {
        ToolObj* t = new ("Editor", 0, 0, 0, 0) ToolObj();
        AssignRef<0, 1>(tool, (Any*)t);
        VCall<7>(tool);

        PaletteUI* ui = paletteUI ? VCall1<3, PaletteUI*>(paletteUI, 0x52deed23) : 0;

        Obj34Fields* o = (Obj34Fields*)new ("Editor", 0, 0, 0, 0) Obj34();
        if (o) VCall<1>(o);

        DocRC* doc = (DocRC*)g_16c7aa4->sub->doc;
        DocRC* old = (DocRC*)o->doc;
        if (doc != old) {
            if (doc) doc->rc = doc->rc + 1;
            o->doc = (Any*)doc;
            if (old) {
                int n = old->rc - 1;
                old->rc = n;
                if (n == 0) {
                    old->rc = 1;
                    ((void(__thiscall*)(void*, int))(*(void***)old)[0])(old, 1);
                }
            }
        }
        if (o->f10) {
            Any* p = o->f10;
            o->f10 = 0;
            VCall<1>(p);
        }
        o->w18 = 0x268a;
        o->b31 = 1;
        AssignRef<0, 1>(o->f14, tool);
        ui->Init(pal, mainWin, 0, (Any*)o);
        ui->SetVisible(1);
        VCall<2>(o);
    }

    PaletteUI* ui2 = paletteUI ? VCall1<3, PaletteUI*>(paletteUI, 0x52deed23) : 0;
    for (int i = 0; i < (ui2->catEnd - ui2->catBegin); ++i) {
        Category* cat = ui2->GetCategory(i);
        PalVec* vec;
        int limit;
        if (i < 7) {
            limit = 6;
            vec = &vecA;
        } else if (i == 7) {
            limit = 0x30;
            vec = &vecB;
        } else {
            continue;
        }
        if ((cat->rowsEnd - cat->rowsBegin) < limit) {
            int last = 0;
            for (int k = 0; ; ++k) {
                int cur = (int)(cat->rowsEnd - cat->rowsBegin);
                if (k >= MaxRef(limit, cur)) break;
                if (k < (int)(cat->rowsEnd - cat->rowsBegin)) {
                    last = k;
                } else {
                    cat->AddRowLike(last);
                }
            }
        }
        for (int r = 0; r < (cat->rowsEnd - cat->rowsBegin); ++r) {
            Row* row = cat->GetRow(r);
            for (int j = 0; j < (row->itemsEnd - row->itemsBegin); ++j) {
                void* it = row->GetItem(j);
                Any* data = it ? VCall1<3, Any*>((char*)it + 0xc, 0x0722de52) : 0;
                ItemUI* iu = new ("UI/cSPScenarioPaletteItemUIBase", 0, 0, 0, 0) ItemUI(data);
                ((void(__thiscall*)(void*, int))(*(void***)iu)[9])(iu, i);

                vec->push_back();
                PalEntry& e = vec->mpEnd[-1];
                AssignRef<1, 2>(e.item, (Any*)iu);
                AssignRef<2, 3>(e.pal, (Any*)cat);
                e.cat = i;
                e.idx = j;
                e.row = r;
            }
        }
    }

    SelectCategory(ui2->GetCategory(ui2->FindCategoryIndex()), 1);

    callback = new ("Simulator/Scenario/CastPanel", 0, 0, 0, 0) ScnCallback(this);

    AvatarUI* av = new ("Simulator/Scenario/AvatarUI", 0, 0, 0, 0) AvatarUI();
    AssignRef<1, 2>(avatarUI, av);
    avatarUI->Setup(0);
    Finish();

    void* l = listener;
    server = MessageServer();
    lstn = l;
    lstnName = kMsgIds;
    lstnFlag = 1;
    lstnZero = 0;
    if (server && l)
        ((void(__thiscall*)(void*, void*, unsigned))(*(void***)server)[9])(server, l, 0x030c11c7);
    return true;
}

// ================================================================ s00ed37c0 additions

struct FillEntry { int f0, f4, f8; };
struct EditorRect { int a0, a4, a8, ac; };
struct Rect3 { int a, b, c; };

void __cdecl FUN_00540520(void* p);                      // 0x00540520
void __cdecl FUN_00929e70(void* p);                      // (unused)

namespace UI {
    void __cdecl ToggleHint(void* checklist, int hi, int lo);   // 0x00efbbe0
    void __cdecl ApplyPlacement(void* self, int alloc);         // 0x00f00790
}

// Scn::Finish forwards to the message-view body (the two views alias; the member
// is a convenience so the pre-existing Setup() call site stays valid).
void Scn::Finish()
{
    ((ScnRecBody*)(void*)this)->Finish();
}

// @ 0x00ed37c0 -- RecordMap::Find (find-or-insert the record keyed by *key;
// returns &record->f8, which the callers use as the record's payload pointer).
Record* RecordMap::Find(int* key)
{
    Record* end = mpEnd;
    Record* pos = (Record*)FUN_00ed29b0(mpBegin, end, key, flags);
    if (pos != end && *key >= *(int*)pos)
        return (Record*)((char*)pos + 8);

    Record tmp;
    FUN_00f2d260(&tmp);
    *(int*)((char*)&tmp + 0x20) = *key;
    FUN_00dff1a0((char*)&tmp + 4, (char*)key + 4);

    int k = *(int*)((char*)&tmp + 0x20);
    end = mpEnd;
    if (pos == end || *(int*)pos <= k) {
        pos = mpEnd;
    } else {
        pos = mpBegin;
    }
    pos = FUN_00ed3740(this, pos, (int*)((char*)&tmp + 0x20));
    if (pos == end || k < *(int*)pos) {
        pos = (Record*)((char*)FUN_00ed3740(this, pos, (int*)((char*)&tmp + 0x20)));
    }
    FUN_00dfce90((char*)&tmp + 4);
    FUN_00dfce90(&tmp);
    return (Record*)((char*)pos + 8);
}

// @ 0x00ed38a0 -- ScnRecBody::RemoveIcon(key): look the key up in palVecA; when it
// is not present, map it to an icon id and insert that, then run the icon's
// virtual hand-off and select the record.
void ScnRecBody::RemoveIcon(int key)
{
    if (key == -1)
        return;

    RecordMap* map = (RecordMap*)(g_16c7aa4->sub->db + 0x2bf4);
    Record* rec = map->Find(&key);

    PalEntry* e = (PalEntry*)FUN_00ed1f00(&palVecA, key);
    if (!e) {
        int icon = FUN_00eece20((int)rec);
        e = (PalEntry*)FUN_00ed1f70(&palVecA, icon);
        if (!e)
            return;
        void* obj = e->item;
        ((void(__thiscall*)(void*, int))(*(void***)obj)[0x1c / 4])(obj, key);
    }
    FUN_00ed3120(this, e->pal, 1);
}

// @ 0x00ed3920 -- ScnRecBody::ClearTwo(key): clear the key from both palVecA and
// palVecB, running each found entry's virtual clear and deselecting its record.
void ScnRecBody::ClearTwo(int key)
{
    RecordMap* map = (RecordMap*)(g_16c7aa4->sub->db + 0x2bf4);
    map->Find(&key);

    PalEntry* e = (PalEntry*)FUN_00ed1f00(&palVecA, key);
    if (e) {
        void* obj = e->item;
        ((void(__thiscall*)(void*))(*(void***)obj)[0x20 / 4])(obj);
        FUN_00ed3120(this, e->pal, 1);
    }

    e = (PalEntry*)FUN_00ed1f00(&palVecB, key);
    if (e) {
        void* obj = e->item;
        ((void(__thiscall*)(void*))(*(void***)obj)[0x20 / 4])(obj);
        FUN_00ed3120(this, e->pal, 1);
    }
}

// @ 0x00ed39a0 -- ScnRecBody::DeselectTwo(key): resolve the key in both vectors and
// run each found entry's virtual deselect.
void ScnRecBody::DeselectTwo(int key)
{
    RecordMap* map = (RecordMap*)(g_16c7aa4->sub->db + 0x2bf4);
    map->Find(&key);

    PalEntry* e = (PalEntry*)FUN_00ed1f00(&palVecA, key);
    if (e) {
        void* obj = e->item;
        ((void(__thiscall*)(void*))(*(void***)obj)[0x14 / 4])(obj);
    }

    e = (PalEntry*)FUN_00ed1f00(&palVecB, key);
    if (e) {
        void* obj = e->item;
        ((void(__thiscall*)(void*))(*(void***)obj)[0x14 / 4])(obj);
    }
}

// @ 0x00ed3a00 -- ScnRecBody::Finish(): refresh the record container, walk every
// record once invoking RemoveIcon, then walk the second (0x238-stride) container
// and re-select the entries whose allocator id is still live.
void ScnRecBody::Finish()
{
    FUN_00ed1ec0((RecordMap*)(g_16c7aa4->sub->db + 0x2bf4));

    char* db  = g_16c7aa4->sub->db;
    Record* b = *(Record**)&db[0x2bf4];
    Record* e = *(Record**)&db[0x2bf8];
    for (; b != e; b = (Record*)((char*)b + 0x27e8))
        RemoveIcon(*(int*)b);

    db = g_16c7aa4->sub->db;
    unsigned count = *(unsigned*)&db[0x2c24];
    char* catBegin;
    if (count < 0x3fffffff)
        catBegin = *(char**)&db[0x2c10] + count * 0x238;
    else
        catBegin = *(char**)&db[0x2c14];
    char* catEnd = *(char**)&db[0x2c14];

    for (;;) {
        if (catEnd == catBegin)
            return;
        int key = *(int*)(catBegin + 4);
        if (key != -2) {
            char* vEnd = *(char**)&db[0x2c00];   // unused
            (void)vEnd;
            // scan palVecB for a matching allocator id
            char* vb = (char*)palVecB.mpBegin;
            char* ve = (char*)palVecB.mpEnd;
            bool found = false;
            for (char* p = vb; p < ve; p += 0x14) {
                if (GetAllocator(*(void**)p) == key) { found = true; break; }
            }
            if (!found) {
                for (char* p = vb; p < ve; p += 0x14) {
                    if (FUN_00ecdb80(*(void**)p)) {
                        void* obj = *(void**)p;
                        ((void(__thiscall*)(void*, int))(*(void***)obj)[0x1c / 4])(obj, key);
                        FUN_00ed3120(this, *(void**)(p + 4), 1);
                        break;
                    }
                }
            }
        }
        do {
            unsigned f = *(unsigned*)catBegin;
            catBegin += 0x238;
            if ((f >> 0x1e) & 1)
                break;
        } while ((int)*(unsigned*)catBegin < 0);
    }
}

// @ 0x00ed3b20 -- ScnRecBody::ChooseSubCategory(sub, key): a scenario sub-category
// was chosen on `sub`; register/erase the icon accordingly and refresh the node.
void ScnRecBody::ChooseSubCategory(void* sub, int key)
{
    char* db = g_16c7aa4->sub->db;
    Sub* node = g_16c7aa4->sub;
    int alloc = GetAllocator(sub);
    if (alloc == -1) {
        int n = FUN_00f46450(key);
        ((void(__thiscall*)(void*, int))(*(void***)sub)[0x1c / 4])(sub, n);
        RemoveIcon(n);
    } else if (alloc == -2) {
        FUN_00f42580(key);
        db[0x14c] = 0;
        ((void(__thiscall*)(void*))(*(void***)sub)[0x14 / 4])(sub);
        FUN_00f40370(node);
        FUN_00f427c0(node);
    } else {
        FUN_00f43af0(alloc);
        Any* rec = FUN_00f3e8a0(db, alloc);
        *((char*)rec + 0x1c) = 0;
        ((void(__thiscall*)(void*))(*(void***)sub)[0x14 / 4])(sub);
        DeselectTwo(alloc);
        FUN_00f40370(node);
        FUN_00f427c0(node);
    }
    MsgServer* m = MessageServer();
    ((void(__thiscall*)(MsgServer*, unsigned, void*, void*))(*(void***)m)[5])(m, 0x07a12a49, 0, 0);
}

// @ 0x00ed4200 -- ScnRec::ProcessMessage(id, arg): the scenario cast-panel message
// handler.  Dispatches on the message id (a 32-bit hash) to the palette/category,
// record and sub-category actions.  Always returns false in al.
bool ScnRec::ProcessMessage(unsigned id, Any* arg)
{
    ScnRecBody* body = (ScnRecBody*)((char*)this - 8);

    if (id == 0x03150c27 || id == 0x044ef2b8) {
        PaletteCtrl* ui = (PaletteCtrl*)FUN_00ed1d20(mainWin);
        int catIndex = ui->GetCurrentCategoryIndex();
        if (id == 0x044ef2b8) {
            void* sub = ui->GetSubCategory(catIndex);
            void* w = *(void**)((char*)sub + 0x18);
            ((void(__thiscall*)(void*, unsigned, int))(*(void***)w)[0xf0 / 4])(w, 0x05d17546, 1);
            if (catIndex <= 5) {
                static const short kHint[6][2] = {
                    { 0x1a, 0x1b }, { 0x2c, 0x2d }, { 0x32, 0x33 },
                    { 0x40, 0x41 }, { 0x56, 0x57 }, { 0x5a, 0x43 },
                };
                void* u = *(void**)((char*)g_16c7aa4->sub->doc);
                (void)u;
                UI::ToggleHint(g_16c7aa4->sub->doc, kHint[catIndex][1], kHint[catIndex][0]);
            }
        }
        // walk both entry vectors and drop the entries of the current category
        for (int v = 0; v < 2; ++v) {
            PalVec* vec = (v == 0) ? &palVec0 : &palVec1;
            PalEntry* b = vec->mpBegin;
            PalEntry* e = vec->mpEnd;
            for (PalEntry* p = b; p < e; ++p) {
                Any* data = p->item ? VCall1<3, Any*>((char*)p->item + 8, 0x0722de52) : 0;
                if (p->cat == catIndex && data)
                    FUN_00ece300(data);
            }
        }
        Any* sub0 = (Any*)ui->GetSubCategory(ui->GetCurrentCategoryIndex());
        FUN_00ed3120((char*)this - 8, sub0, 0);
        return false;
    }

    switch (id) {
    case 0x030c11c7: {
        if (!FUN_00ed21f0((char*)mainWin + 0x10) || *((char*)mainWin + 0x44))
            return false;
        FillEntry tmp;
        tmp.f0 = tmp.f4 = tmp.f8 = 0;
        FUN_00eef810(&tmp, (char*)mainWin + 0x18, 0, 0);
        VCall<0>(&tmp);
        FUN_00540520(&tmp);
        return false;
    }
    case 0x072ab904: {
        if (!arg)
            return false;
        Any* x = (Any*)FUN_00ed21d0((char*)arg + 0x20);
        FUN_00ed2600((char*)this - 8, x, 0);
        return false;
    }
    case 0x072abb02: {
        if (!arg)
            return false;
        Any* x = (Any*)FUN_00ed21d0((char*)arg + 0x20);
        Any* y = (Any*)FUN_01137690(x);
        y = y ? VCall1<3, Any*>(y, 0x0722de52) : 0;
        int alloc = GetAllocator(y);
        if (*(int*)((char*)arg + 0x14) == 0 || alloc == -1)
            return false;
        UI::ApplyPlacement((void*)0x015ad328, alloc);
        return false;
    }
    case 0x072bdb11: {
        body->Finish();
        return false;
    }
    case 0x07311fe9: {
        FUN_00ed3350((char*)this - 8, (int)arg);
        return false;
    }
    case 0x07311ff7: {
        FUN_00ed33a0((char*)this - 8, (int)arg);
        return false;
    }
    case 0x07326686: {
        body->ClearTwo((int)arg);
        return false;
    }
    case 0x07395b639: {
        body->DeselectTwo((int)arg);
        return false;
    }
    case 0x073e7b71: {
        if (!arg)
            return false;
        Any* x = (Any*)FUN_00ed21d0((char*)arg + 0x20);
        Any* editor = (Any*)FUN_00ecdbb0(x);
        int srcAlloc = GetAllocator(x);
        FUN_00f45970(g_16c7aa4->sub);
        Any* slot = (Any*)FUN_00ecdbb0((char*)arg + 0x24);
        EditorRect r = VCall1<0, EditorRect>(slot, 0x0722de63);
        (void)editor; (void)srcAlloc; (void)r;
        return false;
    }
    case 0x07c7b9bb: {
        if (!arg)
            return false;
        Any* x = (Any*)((char*)arg + 0x20);
        x = x ? VCall1<3, Any*>(x, 0x0722de63) : 0;
        int alloc = GetAllocator(x);
        FUN_00f45970(g_16c7aa4->sub);
        Any* y = (Any*)((char*)arg + 0x24);
        y = y ? VCall1<3, Any*>(y, 0x0722de63) : 0;
        Rect3 rr = VCall1<0, Rect3>(y, 0);
        if (rr.a) {
            body->ChooseSubCategory(x, (int)&rr);
        }
        if (alloc == -1) {
            int z = GetAllocator(y);
            if (z != -2) {
                Any* dbl = (Any*)g_16c7aa4->sub->db;
                Any* p = FUN_00f3e8a0(dbl, GetAllocator(x));
                Any* q = FUN_00f3e8a0(dbl, GetAllocator(y));
                FUN_00dfed90((char*)p + 0x70, (char*)q + 0x70);
            }
        }
        FUN_00f45a80(g_16c7aa4->sub);
        return false;
    }
    case 0x08292e7f: {
        if (!arg)
            return false;
        FUN_00ed2410((char*)this - 8, *(void**)((char*)arg + 8),
                     *(void**)((char*)arg + 0x10), *(void**)((char*)arg + 0x18));
        return false;
    }
    default:
        break;
    }
    return false;
}


