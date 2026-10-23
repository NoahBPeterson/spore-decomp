// Slice s00f1ae10 - UI scenario play progress bar family.
// /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"
#include <intrin.h>

typedef unsigned int uint;
typedef unsigned short wchar16;

struct Vec3 { float x, y, z; };
struct VP {
    float x, y, z, f;
    VP() {}
    VP(float a, float b, float c, float d) : x(a), y(b), z(c), f(d) {}
};   // {position, scalar} pushed by value

// ---- engine bits -----------------------------------------------------------
struct WString {
    wchar16* mpBegin;
    wchar16* mpEnd;
    wchar16* mpCap;
    void assign(const wchar16* first, const wchar16* last);   // 0x00423650
};

struct CString {
    uint pad[5];
    CString();                                                // 0x006b5060
    CString(uint a, uint b, const wchar16* c);                // 0x006b5770
    ~CString();                                               // 0x006b5240
    bool Load(uint a, uint b, int c);                         // 0x006b54b0
    const wchar16* GetText();                                 // 0x006b55c0
};

// generic vtable accessors (vtable slot index = byte offset / 4)
typedef void* (__thiscall* PFnQI)(void*, uint);
typedef Vec3* (__thiscall* PFnPos)(void*);
typedef float (__thiscall* PFnF)(void*);
typedef void  (__thiscall* PFnSet)(void*, int);
typedef void  (__thiscall* PFnVoid)(void*);
typedef void  (__thiscall* PFnSpawn)(void*, uint, Vec3*, Vec3*, int, int, float);

inline void*  QI(void* p, uint id) { return ((PFnQI)((void**)*(void**)p)[3])(p, id); }   // +0x0c
inline Vec3*  Pos(void* p)         { return ((PFnPos)((void**)*(void**)p)[0x0b])(p); }  // +0x2c
inline float  Scalar(void* p)      { return ((PFnF)((void**)*(void**)p)[0x1d])(p); }     // +0x74
inline void   SetX(void* p, int v) { ((PFnSet)((void**)*(void**)p)[0x12])(p, v); }       // +0x48

struct Ctr {                       // avatar / mission / interactable object
    void** vtbl;                   // +0x00
    char   pad04[0x18];
    int    f1c;                    // +0x1c
    char   pad20[4];
    int    f24;                    // +0x24
};

// ---- progress bar element / owner -----------------------------------------
struct Sub8 {
    void Set(const int& v);                            // 0x00b2b5b0
};

struct PBEl {
    char disabled;      // +0x00
    char flag1;         // +0x01
    char pad02[2];
    int  count;         // +0x04
    char sub8[0x1c];    // +0x08
    int  type;          // +0x24
    int  id;            // +0x28
    int  aux;           // +0x2c
    int  threshold;     // +0x30
    char flag34;        // +0x34
    char pad35[0x1ac - 0x35];
};

struct PtrVec {
    void** mpBegin;
    void** mpEnd;
    void** mpCap;
};

struct PB;

struct SMgr {                       // scenario manager, *g_16c7aa4->+0x74
    char  pad00[0x10];
    void* f10;                      // +0x10
    char  pad14[4];
    char  f14;                      // +0x14

    void* Find(int id);             // 0x00f3be60
    void* Lookup(int id);           // 0x00f3e8a0
    void* Sub(void* out);           // 0x00f3bcb0
    char  Match(void* obj, void* key, int cookie, void* rec);   // 0x00f3e6d0
    void  Collect(int q, PtrVec* out);                          // 0x00f40d00
};

struct GBlock {                     // *0x016c7aa4
    char  pad00[0x6c];
    void* f6c;                      // +0x6c
    char  pad70[4];
    SMgr* f74;                      // +0x74
    char  pad78[4];
    void* f7c;                      // +0x7c
    char  pad80[0xcc - 0x80];
    int   fcc;                      // +0xcc
    int   fd0;                      // +0xd0
};

extern GBlock* g_16c7aa4;
extern Vec3    g_16c826c;

struct AvMgr {
    Ctr* GetAvatar();               // 0x00b1fdb0
};
extern "C" AvMgr* SPNounManager();  // 0x00b3d300

// ---- misc engine entry points ---------------------------------------------
extern "C" void* FUN_00b3d240();                              // 0x00b3d240
extern "C" void  FUN_00e16a70(void*, int);                    // 0x00e16a70
extern "C" void  FUN_00e133b0(void*, int, int);               // 0x00e133b0
extern "C" void  FUN_00e13b50(void*, int, int);               // 0x00e13b50
extern "C" void  FUN_00f0e6c0(void*);                         // 0x00f0e6c0
extern "C" void  FUN_00f19530(void*);                         // 0x00f19530
extern "C" uint  ResourceKeyToIcon(void*);                    // 0x00eece20
extern "C" void  FUN_00eeea50(void*);                         // 0x00eeea50
extern "C" int   FUN_00efc520();                              // 0x00efc520
extern "C" void* FUN_00b18e00(void*);                         // 0x00b18e00
extern "C" void  FUN_00c8ad30(void*, uint, int);              // 0x00c8ad30
extern "C" void* AchievementsController(uint, int);           // 0x00675250
struct Achievements { void AutoTest(); };                     // 0x00676e90

struct ObjName {
    const wchar16* Text();          // 0x00f26360
    void Do(void*);                 // 0x00f28b80
};

struct AudioSys {
    int  V20();                     // +0x20
    void V38(uint);                 // +0x38
    void V40(uint, int);            // +0x40
    void V58();                     // +0x58
};
typedef int  (__thiscall* PFnV20)(void*);
typedef void (__thiscall* PFnV38)(void*, uint);
typedef void (__thiscall* PFnV40)(void*, uint, int);
typedef void (__thiscall* PFnV58)(void*);
inline int  Audio20(void* p)          { return ((PFnV20)((void**)*(void**)p)[8])(p); }   // +0x20
inline void Audio38(void* p, uint a)  { ((PFnV38)((void**)*(void**)p)[0x0e])(p, a); }    // +0x38
inline void Audio40(void* p, uint a, int b) { ((PFnV40)((void**)*(void**)p)[0x10])(p, a, b); } // +0x40
inline void Audio58(void* p)          { ((PFnV58)((void**)*(void**)p)[0x16])(p); }       // +0x58

extern "C" void* EA_Audio_GetSystemAT();                      // 0x00a206f0
extern "C" void* EAAllocate(uint, const char*, int, int, int, int); // 0x00f473a0
extern "C" void* MessageServer();                             // 0x0067dcc0

struct Msg {
    void V04();                     // +0x04
    void V08();                     // +0x08
};

struct MsgServer {
    void Post(int id, void* msg, int b);   // +0x14
};

// assign a NUL terminated wide string range (eastl::basic_string::assign(p, p+len))
static int Len16(const wchar16* p)
{
    const wchar16* q = p;
    while (*q) ++q;
    return (int)(q - p);
}

static void AssignStr(WString& w, const wchar16* p)
{
    w.assign(p, p + Len16(p));
}

// ---- progress bar ---------------------------------------------------------
class PB {
public:
    void  Add(PBEl* e, void* a, void* b);            // 0x00f1ae10
    void  Event(void* a, void* ev);                  // 0x00f1aff0
    void  Release(void* a, void* ev);                // 0x00f1b180
    void  Unlink(void* a, void* b, int c);           // 0x00f1b260
    char  TryAdd(void* a);                           // 0x00f1b2f0
    void  SetKind(int a);                            // 0x00f1b360
    void  PlaySound(int a, int b);                   // 0x00f1b370
    void  RefreshAll();                              // 0x00f1b450
    void  RemoveByType(void* a);                     // 0x00f1b590
    void  SetText(int kind);                         // 0x00f1b640
    void  SetMode(int a, PBEl* ev, int kind);        // 0x00f1b730
    Ctr*  FindNearest(void* a, int q, void* excl);   // 0x00f1b820
    void  GetNameA(WString* out);                    // 0x00f1b9b0
    void  GetNameB(WString* out);                    // 0x00f1ba00
    void  GetInfo(int idx, WString* out);            // 0x00f1ba50
    void  GetNameC(int i, WString* out);             // 0x00f1bcb0
    void  GetNameD(int i, WString* out);             // 0x00f1bcd0
    void  Setup(VP a, VP b, PBEl* e);                // 0x00f19940
    void  Remove(PBEl* e, void* p);                  // 0x00f19ac0
    void  Apply(int a, int b);                       // 0x00f198f0
    int   ByIndex(void* p);                          // 0x00f19840
    char  FUN_00f1a070(void* p);                     // 0x00f1a070
    void  FUN_00f1a120(PBEl* e, void* p);            // 0x00f1a120
    bool  FUN_00f1a7a0(int a, void* p);              // 0x00f1a7a0
    void  FUN_00f1a7f0(void* p);                     // 0x00f1a7f0
    void  FUN_00f1aae0(int a);                       // 0x00f1aae0
    int   EachChild(int id, int b);                  // 0x00f19660

    char    pad00[4];
    int     f04;            // +0x04
    char    pad08[0x54 - 0x08];
    WString ws54;           // +0x54
    char    pad60[4];
    PBEl*   begin;          // +0x64
    PBEl*   end;            // +0x68
    char    pad6c[0x90 - 0x6c];
    int     state;          // +0x90
    char    pad94[0xb0 - 0x94];
    int     f_b0;           // +0xb0
    char    padb4[4];
    int     f_b8;           // +0xb8
    char    padbc[0xec - 0xbc];
    char    f_ec;           // +0xec
};

// @ 0x00f1ae10
void PB::Add(PBEl* e, void* a, void* b)
{
    if (state != 3) return;
    if (e->disabled) return;
    if (!a) {
        Ctr* av = SPNounManager()->GetAvatar();
        a = av ? (void*)((char*)av + 0xc0) : 0;
    }
    Vec3 pa = *Pos(a);
    float ta = Scalar(a);
    Vec3 pb;
    float tb;
    if (b) {
        pb = *Pos(b);
        tb = Scalar(b);
    } else {
        pb = g_16c826c;
        tb = 0.0f;
    }
    ++e->count;
    int th = e->threshold;
    if (e->type == 7 && e->flag34) {
        void* o = FUN_00b3d240();
        ((PFnSpawn)((void**)*(void**)o)[0x17])(o, 0x7b11813, &pa, &g_16c826c, -1, -1, ta);
    }
    if (e->count >= th) {
        Setup(VP(pb.x, pb.y, pb.z, tb), VP(pa.x, pa.y, pa.z, ta), e);
        return;
    }
    if (f_ec) return;
    char* c = (char*)g_16c7aa4->f6c;
    void* card = *(void**)(c + 0x148);
    if (card) {
        FUN_00e16a70(card, 0);
        if (*(char*)((char*)card + 0x10) == 0)
            FUN_00e13b50(card, 0, 0);
        else
            FUN_00e133b0(card, 0, 0);
    }
    FUN_00f0e6c0(g_16c7aa4->f6c);
}

// @ 0x00f1aff0
void PB::Event(void* a, void* ev)
{
    if (state == 3) {
        Ctr* av = SPNounManager()->GetAvatar();
        if (a == (void*)av) {
            int id = ((Ctr*)ev)->f1c;
            if (id != -1) {
                for (PBEl* e = begin; e != end; ++e) {
                    if (e->type == 8 && e->id == id) {
                        if (!e->disabled)
                            Add(e, QI(ev, 0x1186577), 0);
                        else
                            ++e->count;
                    }
                    if (e->type == 9 && e->id == id && !e->disabled) {
                        void* card = *(void**)((char*)g_16c7aa4->f6c + 0x148);
                        if (card) {
                            FUN_00e16a70(card, 0);
                            if (*(char*)((char*)card + 0x10) == 0)
                                FUN_00e13b50(card, 0, 0);
                            else
                                FUN_00e133b0(card, 0, 0);
                        }
                    }
                }
            }
        } else {
            int ia = ((Ctr*)a)->f1c;
            int ib = ((Ctr*)ev)->f1c;
            if (ia != -1 && ib != -1) {
                for (PBEl* e = begin; e != end; ++e) {
                    if (e->type == 9 && e->id == ib && (e->aux == ia || e->aux == -1)) {
                        if (!e->disabled)
                            Add(e, FUN_00b18e00(ev), 0);
                        else
                            ++e->count;
                    }
                }
            }
        }
    }
    if (ev) {
        void* p = QI(ev, 0x1186577);
        if (p) FUN_00c8ad30(p, 0x7b0f76d, 1);
    }
}

// @ 0x00f1b180
void PB::Release(void* a, void* ev)
{
    if (state == 3 && a) {
        void* ag = QI(a, 0xd0036e08);
        if (ag) {
            Ctr* av = SPNounManager()->GetAvatar();
            if (ag == (void*)av) {
                int id = ((Ctr*)ev)->f1c;
                if (id != -1) {
                    for (PBEl* e = begin; e != end; ++e) {
                        if (e->type == 8 && e->id == id) {
                            if (e->count == 1) {
                                if (e->flag1) Remove(e, (char*)ag + 0xc0);
                            } else {
                                --e->count;
                            }
                        }
                        if (e->type == 9 && e->id == id && !e->disabled)
                            Apply(0, 1);
                    }
                }
            }
        }
    }
    if (FUN_00f1a7a0(8, ev)) FUN_00f19530(ev);
}

// @ 0x00f1b260
void PB::Unlink(void* a, void* b, int)
{
    if (state != 3) return;
    int ia = ((Ctr*)a)->f1c;
    int ib = ((Ctr*)b)->f1c;
    for (PBEl* e = begin; e != end; ++e) {
        switch (e->type) {
        case 6:
            if ((e->id == ia && e->aux == ib) || (e->id == ib && e->aux == ia)) {
                if (!e->disabled) Add(e, 0, 0);
                e->flag1 = 0;
            }
            break;
        case 8:
            if (e->id == ib) e->flag1 = 0;
            break;
        }
    }
}

// @ 0x00f1b2f0
char PB::TryAdd(void* a)
{
    char r = 0;
    if (state == 3) {
        int id = ((Ctr*)a)->f1c;
        if (id != -1 && FUN_00f1a070(a)) {
            for (PBEl* e = begin; e != end; ++e) {
                if (!e->disabled && e->type == 2 && id == e->id) {
                    r = 1;
                    FUN_00f1a120(e, a);
                    break;
                }
            }
        }
    }
    return r;
}

// @ 0x00f1b360
void PB::SetKind(int a)
{
    FUN_00f1a7a0(2, (void*)a);
}

// @ 0x00f1b370
void PB::PlaySound(int, int b)
{
    void* au = EA_Audio_GetSystemAT();
    int v = 0;
    if (au) v = Audio20(au);
    au = EA_Audio_GetSystemAT();
    if (au) {
        Audio38(au, 0x3475365);
        Audio40(au, 0x3475381, 0xe76c9b4f);
        Audio40(au, 0x3475385, v);
        Audio58(au);
    }
    char* m = (char*)EAAllocate(0x40, "App", 0, 0, 0, 0);
    if (m) {
        *(int*)(m + 0x30) = 0;
        *(int*)m = 0x13eb90c;
        _InterlockedExchange((volatile long*)(m + 4), 0);
        *(int*)m = 0x13eb844;
        *(int*)(m + 0x38) = 0;
        ((Msg*)m)->V04();
    }
    *(int*)(m + 0x30) = f04;
    *(int*)(m + 8) = b;
    void* ms = MessageServer();
    ((MsgServer*)ms)->Post(*(int*)(m + 0x30), m, 0);
    ((Msg*)m)->V08();
}

// @ 0x00f1b450
void PB::RefreshAll()
{
    SMgr* mgr = g_16c7aa4->f74;
    char* coll = (char*)mgr->f10;
    char* it = *(char**)(coll + 0x2bf4);
    char* endIt = *(char**)(coll + 0x2bf8);
    while (it != endIt) {
        int obj = *(int*)it;
        int v = ByIndex((void*)obj);
        PtrVec vec;
        vec.mpBegin = 0;
        vec.mpEnd = 0;
        vec.mpCap = 0;
        mgr->Collect(obj, &vec);
        int n = (int)(vec.mpEnd - vec.mpBegin);
        for (int i = 0; i < n; ++i) {
            void* x = 0;
            if (vec.mpBegin[i] == 0 ||
                (x = QI(vec.mpBegin[i], 0xd0036e08)) == 0 ||
                ((*(uint*)((char*)x + 0xb58) >> 8) & 1) == 0)
                SetX(vec.mpBegin[i], v);
            FUN_00f1a7f0(vec.mpBegin[i]);
        }
        for (void** p = vec.mpBegin; p < vec.mpEnd; ++p) {
            if (*p) ((PFnVoid)((void**)*(void**)*p)[1])(*p);
        }
        if (vec.mpBegin && vec.mpBegin[-1] != 0)
            ::operator delete(vec.mpBegin);
        it += 0x27e8;
    }
    Ctr* av = SPNounManager()->GetAvatar();
    SetX(av, 1);
}

// @ 0x00f1b590
void PB::RemoveByType(void* a)
{
    if (state == 3) {
        int id = ((Ctr*)a)->f1c;
        if (id != -1) {
            for (PBEl* e = begin; e != end; ++e) {
                if (e->id == id && e->type == 5) {
                    Remove(e, QI(a, 0x1186577));
                    int t = ((Ctr*)a)->f24;
                    ((Sub8*)e->sub8)->Set(t);
                }
            }
        }
        if (*(char*)((char*)g_16c7aa4->f74 + 0x14) == 0) {
            int st = g_16c7aa4->fd0;
            if (st && st == 2) {
                Achievements* c = (Achievements*)AchievementsController(0xb57b9d12, 1);
                c->AutoTest();
            }
        }
    }
}

// @ 0x00f1b640
void PB::SetText(int kind)
{
    f_b0 = kind;
    CString s;
    switch (kind) {
    case 0:
        s.Load(0x21851ebe, 0x796cee4, 0);
        AssignStr(ws54, s.GetText());
        break;
    case 1:
        s.Load(0x21851ebe, 0x796cfdd, 0);
        AssignStr(ws54, s.GetText());
        break;
    case 4:
        s.Load(0x21851ebe, 0x7c50b5f, 0);
        AssignStr(ws54, s.GetText());
        break;
    }
}

// @ 0x00f1b730
void PB::SetMode(int a, PBEl* ev, int kind)
{
    char* w = (char*)g_16c7aa4->f7c;
    if (w) *(int*)(w + 0xc) = a;
    CString s;
    switch (kind) {
    case 0:
        s.Load(0x21851ebe, 0x796cee4, 0);
        break;
    case 1:
        s.Load(0x21851ebe, 0x796cfdd, 0);
        break;
    case 2: {
        int t = ev->type;
        uint id;
        if (t == 10)
            id = 0x796cfe1;
        else if (t == 11)
            id = 0x796cfe5;
        else
            id = 0x796d59a;
        s.Load(0x21851ebe, id, 0);
        break;
    }
    case 3:
        s.Load(0x21851ebe, 0x796d599, 0);
        break;
    }
    AssignStr(ws54, s.GetText());
    f_b0 = kind;
    FUN_00f1aae0(6);
}

// @ 0x00f1b820
Ctr* PB::FindNearest(void* a, int q, void* excl)
{
    Ctr* best = 0;
    Ctr* av = SPNounManager()->GetAvatar();
    if (!av) return best;
    SMgr* mgr = g_16c7aa4->f74;
    PtrVec vec;
    vec.mpBegin = 0;
    vec.mpEnd = 0;
    vec.mpCap = 0;
    mgr->Collect(q, &vec);
    float bestd = 3.402823466e+38F;
    for (int i = 0; i < (int)(vec.mpEnd - vec.mpBegin); ++i) {
        void* p = vec.mpBegin[i];
        if (mgr->Match(p, (char*)a + 0x24, f_b8, a) && p != excl) {
            Vec3* p1 = Pos(p ? QI(p, 0x1186577) : 0);
            Vec3* p2 = Pos((char*)av + 0xc0);
            float d = (p2->z - p1->z) * (p2->z - p1->z) +
                      (p2->y - p1->y) * (p2->y - p1->y) +
                      (p2->x - p1->x) * (p2->x - p1->x);
            if (d < bestd) {
                bestd = d;
                best = (Ctr*)p;
            }
        }
    }
    for (void** pp = vec.mpBegin; pp < vec.mpEnd; ++pp)
        if (*pp) ((PFnVoid)((void**)*(void**)*pp)[1])(*pp);
    if (vec.mpBegin && vec.mpBegin[-1] != 0)
        ::operator delete(vec.mpBegin);
    return best;
}

// @ 0x00f1b9b0
void PB::GetNameA(WString* out)
{
    char* o = (char*)g_16c7aa4->f74->Find(f_b8);
    if (o) AssignStr(*out, ((ObjName*)o)->Text());
}

// @ 0x00f1ba00
void PB::GetNameB(WString* out)
{
    char* o = (char*)g_16c7aa4->f74->Find(f_b8);
    if (o) AssignStr(*out, ((ObjName*)(o + 0x3c))->Text());
}

// @ 0x00f1ba50
void PB::GetInfo(int idx, WString* out)
{
    char* w = (char*)g_16c7aa4->f7c;
    if (!w) return;
    *(int*)(w + 0xc) = idx;
    PBEl* e = (PBEl*)((char*)begin + idx * 0x1ac);
    int type = e->type;
    CString s;
    void* mission = g_16c7aa4->f74->Lookup(e->id);
    if (e->id == -2 || !mission) goto defpath;
    switch (ResourceKeyToIcon(mission)) {
    case 0xb10e526f:
    case 0xd37c1045:
    case 0x5b3d1d0d:
        s.Load(0x21851ebe, ((const uint*)0x148c204)[type], 0);
        break;
    case 0xcf56099a:
    case 0x6031c03a:
        s.Load(0x21851ebe, ((const uint*)0x148c234)[type], 0);
        break;
    default:
    defpath:
        s.Load(0x21851ebe, ((const uint*)0x148c1d4)[type], 0);
        if (type == 2) {
            if (mission) {
                int t;
                if (g_16c7aa4->fcc == 2) t = f_b8;
                else t = FUN_00efc520();
                t = t * 0x4e0 + *(int*)((char*)mission + 0x70);
                if (t && *(char*)(t + 2))
                    s.Load(0x21851ebe, 0x7b55060, 0);
            }
            goto done;
        }
        break;
    }
    if (type == 9 && !e->disabled && !EachChild(e->id, 0))
        s.Load(0x21851ebe, 0x79e8291, 0);
done:
    AssignStr(*out, s.GetText());
}

struct FreeName {
    void Name(int id, WString* out);
};

// @ 0x00f1bc00
void FreeName::Name(int id, WString* out)
{
    if (id == -2) {
        void* x = ((SMgr*)g_16c7aa4->f74)->Sub(out);
        FUN_00eeea50(x);
        return;
    }
    if (id != -1) {
        char* o = (char*)g_16c7aa4->f74->Lookup(id);
        if (o) {
            ((ObjName*)o)->Do(out);
            return;
        }
    }
    CString s(0x21851ebe, 0x7968de4, 0);
    AssignStr(*out, s.GetText());
}

// @ 0x00f1bcb0
void PB::GetNameC(int i, WString* out)
{
    ((FreeName*)this)->Name(((PBEl*)((char*)begin + i * 0x1ac))->id, out);
}

// @ 0x00f1bcd0
void PB::GetNameD(int i, WString* out)
{
    ((FreeName*)this)->Name(((PBEl*)((char*)begin + i * 0x1ac))->aux, out);
}
