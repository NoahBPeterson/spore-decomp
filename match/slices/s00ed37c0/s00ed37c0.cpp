// Slice s00ed37c0 -- Scenario "cast" palette panel setup (0x00ed3c00).
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
struct Sub { char pad[0xd0]; Any* doc; };
extern Globals* g_16c7aa4;                                   // 0x016c7aa4

struct ResKey { unsigned instance, type, group; };

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
