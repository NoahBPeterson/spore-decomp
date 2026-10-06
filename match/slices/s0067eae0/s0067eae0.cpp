// Slice s0067eae0: SP::cCheatManager / anonymous-namespace cheat commands (0x0067eae0-0x0067f9b0).
// /O2 with SSE, EH enabled for the placement-new/set-insert helpers.
#include "../../include/types.h"

static inline void** VT(void* p) { return *(void***)p; }

extern "C" __declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
extern "C" void* __cdecl FUN_00921580(void*);      // eastl::RBTreeIncrement
extern "C" void  __cdecl FUN_009216a0(void*, void*, void*, int);  // eastl::RBTreeInsert

// ===========================================================================
// @ 0x0067EC70  anonymous::cCheatHistoryCommand::Execute
// ===========================================================================
struct Arguments {
    void* MainArguments(void** out, int a, int b);   // EA::ArgScript::cArguments::MainArguments
};
struct CheatManager;
struct Cmd_ec70 {
    char pad0[4];
    void* p4;        // +0x04
    char pad8[8];
    CheatManager* p10;   // +0x10
    void Execute(void* args);
};
struct CheatManager {
    char pad0[0x4c];
    void* setEnd;    // +0x4c
    void* setRoot;   // +0x50
    void ActivateConsole(unsigned code);
};

void Cmd_ec70::Execute(void* args)
{
    void* r = ((Arguments*)args)->MainArguments(&args, 0, 1);
    unsigned v = 0x32;
    if ((int)args > 0)
        v = ((unsigned (__thiscall*)(void*, void*))VT(*(void**)p4)[0x9c / 4])
                (*(void**)p4, *(void**)r);
    p10->ActivateConsole(v);
}

// ===========================================================================
// @ 0x0067ECB0  anonymous::cCheatListCommand::Execute
// ===========================================================================
struct Cmd_ecb0 {
    char pad0[0x10];
    CheatManager* p10;   // +0x10
    void Execute(void* args);
};

void Cmd_ecb0::Execute(void* args)
{
    ((Arguments*)args)->MainArguments(&args, 0, 0);
    char* base = (char*)p10;
    for (void* n = *(void**)(base + 0x50); n != base + 0x4c;
         n = FUN_00921580(n)) {
        void* o = *(void**)((char*)n + 0x10);
        ((void (__thiscall*)(void*))VT(o)[0x18 / 4])(o);
    }
}

// ===========================================================================
// @ 0x0067EF60  command string setter (thiscall, ret 8)
// ===========================================================================
struct EString {
    void assign(const char* first, const char* last);
    char* c_str();
};
struct Parser {
    void Set(const char* s);   // FUN_0067e7b0
};
struct Cmd_ef60 {
    char pad0[0xc];
    Parser* p0c;    // +0x0c
    EString str10;  // +0x10
    bool Execute(const char* s, int len);
};

bool Cmd_ef60::Execute(const char* s, int len)
{
    if (s[len] == 0) {
        p0c->Set(s);
        return true;
    }
    str10.assign(s, s + len);
    p0c->Set(*(char**)&str10);
    return true;
}

// ===========================================================================
// @ 0x0067F640  vector push_back (element at +4/+8)
// ===========================================================================
extern "C" void __cdecl FUN_00690b80(void*, void*);
struct Cmd_f640 {
    char pad0[4];
    void* begin;   // +0x04
    void* end;     // +0x08
    void push_back(void** v);
    void grow(void* at, void* v);   // FUN_00690b80
};

void Cmd_f640::push_back(void** v)
{
    void* p = begin;
    if (p < end) {
        begin = (char*)p + 4;
        if (p) {
            *(void**)p = *v;
            return;
        }
    } else {
        grow(p, v);
    }
}
// ===========================================================================
// Shared EASTL shapes for the cCheatManager methods (retail layout, not the 2008 PDB's)
//   cCheatManager: +0 vptr, +4 vptr2, +8 refcount,
//                  +0x0c  StrTree mNames   (string -> AutoRefCount<cICommand>)
//                  +0x28  StrTree mTree2   (string -> ...)
//                  +0x44  AutoRefCount<cIParser> mParser
//                  +0x48  RefSet mConsoles (set<AutoRefCount<cICheatConsole>>)
// ===========================================================================
#include <intrin.h>
#define TC0(R, p, off)            ((R(__thiscall*)(void*))VT(p)[(off) / 4])(p)
#define TC1(R, p, off, A, a)      ((R(__thiscall*)(void*, A))VT(p)[(off) / 4])(p, a)
#define TC2(R, p, off, A, a, B, b) ((R(__thiscall*)(void*, A, B))VT(p)[(off) / 4])(p, a, b)
#define TC3(R, p, off, A, a, B, b, C, c) ((R(__thiscall*)(void*, A, B, C))VT(p)[(off) / 4])(p, a, b, c)

void* __cdecl operator new(unsigned int, const char*, int, int, const char*, int) throw();
inline void* __cdecl operator new(unsigned int, void* p) { return p; }
inline void __cdecl operator delete(void*, void*) {}
void __cdecl operator delete(void*) throw();
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
#pragma intrinsic(memcpy)

#define EA_ALLOC_H "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

struct NodeHdr { NodeHdr* right; NodeHdr* left; NodeHdr* parent; char color; char pad[3]; };

extern "C" NodeHdr* __cdecl RBTreeIncrement(NodeHdr*);                       // 0x921580
extern "C" NodeHdr* __cdecl RBTreeDecrement(NodeHdr*);                       // 0x9215c0
extern "C" void __cdecl RBTreeInsert(NodeHdr* node, NodeHdr* parent, NodeHdr* anchor, int left);  // 0x9216a0
extern "C" void __cdecl RBTreeErase(NodeHdr* node, NodeHdr* anchor);         // 0x921880
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char*, const char*);

struct ICmdRef {   // EA::ArgScript::cICommand: slot 3 AddRef, slot 4 Release
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual void AddRef(); virtual void Release();
};
struct IRef {      // SP::cICheatConsole: slot 0 AddRef, slot 1 Release
    virtual void AddRef(); virtual void Release();
};

struct EAlloc { EAlloc() {} };
// eastl::basic_string<char, eastl::allocator>
struct EStr {
    char* b; char* e; char* c; int al;
    EStr() : b(0), e(0), c(0) {}
    EStr(const char* first, const char* last, const EAlloc& al_ = EAlloc());   // @0x5e96a0
    __forceinline EStr(const char* s)
    {
        const char* q = s;
        while (*q++) ;
        const char* send = q - 1;
        unsigned n = (unsigned)(send - s);
        unsigned cap = n + 1;
        if (cap > 1) {
            b = (char*)operator new(cap, "App", 0, 0, EA_ALLOC_H, 0xd1);
            c = b + cap;
        } else {
            b = (char*)0x1667bac;
            c = (char*)0x1667bad;
        }
        memcpy(b, s, n);
        e = b + (send - s);
        *e = 0;
    }
    ~EStr() { if (c - b > 1 && b) operator delete(b); }
    void AllocateSelf(unsigned n);   // @0x475ab0 (RangeInitialize shape)
};

// pair<const string, AutoRefCount<cICommand>>
struct PairB {
    EStr k;
    ICmdRef* v;
    PairB(const EStr& key, ICmdRef* const& val);   // @0x67ee60
    PairB(const PairB& o);                            // @0x67e900
    ~PairB();                                         // @0x67e830
};

struct CmdRef { ICmdRef* p; ~CmdRef() { if (p) p->Release(); } };
struct PairBInl { EStr k; CmdRef v; };   // same layout as PairB, with the dtor inline
struct Node : NodeHdr { PairB v; };   // 0x24 bytes

struct InsResult { NodeHdr* it; bool ok; };

struct StrTree {
    int al;
    NodeHdr a;       // anchor: right = rightmost, left = leftmost, parent = root
    int count;
    int ext;
    Node* NewNodeFromKey(const EStr* k);     // @0x67e890
    Node* NewNodeFromPair(const PairB* v);      // @0x67eef0
    void InsertKey(InsResult* out, const EStr* key, char flag);     // @0x67f0c0
    void InsertPair(InsResult* out, const PairB* v, char flag);        // @0x67f260
    void InsertAt(NodeHdr** out, NodeHdr* at, const PairB* v, char flag);  // @0x67f1f0
    NodeHdr** InsertHint(NodeHdr** out, NodeHdr* pos, const PairB* v, int unused4);  // @0x67f790
    NodeHdr** find(NodeHdr** out, const EStr& key) throw();   // @0x923ac0
    void NukeSub(Node* n);                                // @0x67f670
    void Nuke2(NodeHdr* root);                            // @0xe84940
};
struct NamesTree : StrTree { ~NamesTree() { NukeSub((Node*)a.parent); } };
struct Tree2 : StrTree { ~Tree2() { Nuke2(a.parent); } };
struct ParserRef {   // EA::AutoRefCount<cIParser>
    void* p;
    ~ParserRef() { if (p) ((void (__thiscall*)(void*))(*(void***)p)[1])(p); }
};

struct PtrVec {
    const char** b; const char** e; const char** c;
    ~PtrVec() { if (b && ((int*)b)[-1] != 0) operator delete(b); }
    void grow(const char** at, const char** v);     // @0x690b80
};

struct ConsoleRef {   // EA::AutoRefCount<cICheatConsole>
    IRef* p;
    ConsoleRef(IRef* x) : p(x) { if (p) p->AddRef(); }
    ~ConsoleRef() { if (p) p->Release(); }
};
struct SetNode : NodeHdr { IRef* v; };
struct RefSet {
    int al;
    NodeHdr a;
    int count;
    int ext;
    void Nuke(NodeHdr* root);                                          // @0xeb6280
    ~RefSet() { Nuke(a.parent); }
    void Insert(InsResult* out, const ConsoleRef* v, char flag);       // @0x68a140
    NodeHdr** Find(NodeHdr** out, const ConsoleRef* key);              // @0xe5c780
};

struct ScriptErr { const char* msg; };

extern "C" void* __cdecl CreateParser();                 // EA::ArgScript::CreateParser
extern "C" void* __cdecl EA_Trace_GetServer();           // 0x9234c0
extern "C" void* __cdecl SP_MessageServer();             // 0x67dcc0
extern "C" const char* __cdecl Tokenize(const char* s, const char** end, const char* delims);   // 0x840890
extern "C" bool __cdecl WildcardMatch(const char*, const char*, int);   // EA::Text::WildcardMatch
extern "C" void __cdecl Output(void*, const char*, ...);                // EA::ArgScript::Output

struct AppCheatHandler { char pad[0x20]; AppCheatHandler(struct CheatMgr*); };            // @0x67e9a0
struct AppCheatConsole { char pad[0x28]; AppCheatConsole(const char*, struct CheatMgr*); };  // @0x67e100

extern char g_vt_1401b78[], g_vt_1401b74[], g_vt_13ef094[], g_vt_13eb938[];

struct B0 { virtual ~B0() {} };
struct B4 { virtual ~B4() {} };
struct CheatMgr : B0, B4 {
    int refcount;
    NamesTree mNames;         // +0x0c
    Tree2 mTree2;             // +0x28
    ParserRef mParser;        // +0x44
    RefSet mConsoles;         // +0x48
    virtual ~CheatMgr();                        // @0x67f910
    bool Init();                                // @0x67ed00
    bool RunCheat(const char* cmd);             // @0x67efc0
    bool Shutdown();                            // @0x67f390
    void* FindCommand(const char* name);        // @0x67f470
    void InsertConsole(IRef* c);                // @0x67f540
    void RemoveConsole(IRef* c);                // @0x67f5c0
    int  FindMatches(const char* pat, PtrVec* out);   // @0x67f710
    void RemoveCommand(const char* name);       // @0x67f9b0
    void AddBuiltInCheats();                    // @0x67e480
    void Print(const char* s);                  // @0x67e7b0
};

// ===========================================================================
// @ 0x0067EAE0  anonymous::cCheatHelpCommand::Execute
// ===========================================================================
struct HelpArgs {
    char** MainArguments(int* argc, int a, int b);   // EA::ArgScript::cArguments::MainArguments
    bool HasFlag(const char* name);                  // cArguments::HasFlag
};
struct Cmd_eae0 {
    char pad0[4];
    void* p4;        // +0x04 output sink
    char pad8[8];
    void* p10;       // +0x10 cheat manager (virtual interface)
    void Execute(HelpArgs* args);
};

void Cmd_eae0::Execute(HelpArgs* args)
{
    int argc;
    char** r = args->MainArguments(&argc, 0, 1);
    const char* key = argc > 0 ? *r : "*";
    PtrVec list = {0, 0, 0};
    int n = ((int (__thiscall*)(void*, const char*, PtrVec*))VT(p10)[0x2c / 4])(p10, key, &list);
    if (list.e - list.b == 0) {
        Output(p4, "command not found\n");
    } else {
        int mode = 0;
        if (n == 1) mode = n;
        if (args->HasFlag("full")) mode = 1;
        if (args->HasFlag("html")) mode = 2;
        int count = (int)(list.e - list.b);
        for (int i = 0; i < count; ++i) {
            void* cmd = TC1(void*, p10, 0x28, const char*, list.b[i]);
            const char* desc = TC1(const char*, cmd, 4, int, mode);
            if (!desc) {
                desc = TC1(const char*, cmd, 4, int, 1);
                if (!desc)
                    desc = TC1(const char*, cmd, 4, int, 0);
            }
            if (mode == 0) {
                if (!desc) desc = "no description";
                Output(p4, "%-20s: %s\n", list.b[i], desc);
            } else {
                if (!desc) desc = "no description";
                Output(p4, "%-20s\n%s\n", list.b[i], desc);
            }
        }
    }
}

// ===========================================================================
// @ 0x0067ED00  SP::cCheatManager::Init
// ===========================================================================
bool CheatMgr::Init()
{
    if (mParser.p)
        return false;
    void* np = CreateParser();
    void* old = mParser.p;
    if (np != old) {                      // AutoRefCount assignment
        if (np) TC0(void, np, 0);
        mParser.p = np;
        if (old) TC0(void, old, 4);
    }
    TC0(void, mParser.p, 8);
    AddBuiltInCheats();
    AppCheatHandler* h = new("App/CheatManager", 0, 0, 0, 0) AppCheatHandler(this);
    TC1(void, mParser.p, 0xbc, AppCheatHandler*, h);
    TC0(void, mParser.p, 0x30);
    void* tr = EA_Trace_GetServer();
    if (tr) {
        AppCheatConsole* c = new("App/CheatManager", 0, 0, 0, 0) AppCheatConsole("AppConsole", this);
        TC1(void, tr, 0x1c, AppCheatConsole*, c);
        TC3(void, tr, 0x30, const char*, "AppConsole", int, 0, int, 100);
        TC3(void, tr, 0x30, const char*, "AppConsole", const char*, "Console", int, 1);
    }
    return true;
}

// ===========================================================================
// @ 0x0067EE60  pair<string, AutoRefCount<cICommand>>(const string& key, const AutoRefCount& v)
// ===========================================================================
PairB::PairB(const EStr& key, ICmdRef* const& val)
{
    const char* s = key.b;
    const char* e = key.e;
    unsigned n = (unsigned)(e - s);
    k.AllocateSelf(n + 1);
    char* d = k.b;
    memcpy(d, s, n);
    k.e = d + n;
    *k.e = 0;
    v = val;
    if (v) v->AddRef();
}

// ===========================================================================
// @ 0x0067EEF0  rbtree node allocation from a value (EASTL allocator.h:0xd1)
// ===========================================================================
Node* StrTree::NewNodeFromPair(const PairB* val)
{
    Node* n = (Node*)operator new(0x24, "App", 0, 0, EA_ALLOC_H, 0xd1);
    ::new((void*)&n->v) PairB(*val);
    return n;
}

// ===========================================================================
// @ 0x0067EFC0  SP::cCheatManager::RunCheat
// ===========================================================================
bool CheatMgr::RunCheat(const char* cmd)
{
    bool ok = false;
    if (mParser.p) {
        try {
            TC1(void, mParser.p, 0x40, const char*, cmd);
            ok = true;
            const char* tok = Tokenize(cmd, &cmd, " \t\n\r\x0b\x0c");
            NodeHdr* it;
            bool hit = *mTree2.find(&it, EStr(tok, cmd)) != &mTree2.a;
            if (hit) {
                void* ms = SP_MessageServer();
                if (ms)
                    TC3(void, ms, 0x14, int, 0x4bef1e3, int, 0, int, 0);
            }
        } catch (ScriptErr& e) {
            Print(e.msg);
            Print("\n");
        }
    }
    return ok;
}

// ===========================================================================
// @ 0x0067F0C0  StrTree::InsertKey (find-or-insert by key string)
// ===========================================================================
void StrTree::InsertKey(InsResult* out, const EStr* key, char)
{
    NodeHdr* parent = &a;
    NodeHdr* n = a.parent;
    bool less = true;
    while (n) {
        less = _stricmp(key->b, ((Node*)n)->v.k.b) < 0;
        parent = n;
        n = less ? n->left : n->right;
    }
    NodeHdr* pos = parent;
    if (less) {
        if (parent == a.left) {
            int left;
            if (parent != &a && _stricmp(key->b, ((Node*)parent)->v.k.b) >= 0) left = 1; else left = 0;
            Node* nn = NewNodeFromKey(key);
            RBTreeInsert(nn, parent, &a, left);
            count += 1;
            out->it = nn;
            out->ok = true;
            return;
        }
        parent = RBTreeDecrement(parent);
    }
    if (_stricmp(((Node*)parent)->v.k.b, key->b) < 0) {
        int left;
        if (pos != &a && _stricmp(key->b, ((Node*)pos)->v.k.b) >= 0) left = 1; else left = 0;
        Node* nn = NewNodeFromKey(key);
        RBTreeInsert(nn, pos, &a, left);
        count += 1;
        out->it = nn;
        out->ok = true;
        return;
    }
    out->it = parent;
    out->ok = false;
}

// ===========================================================================
// @ 0x0067F1F0  StrTree::InsertAt (insert with parent hint)
// ===========================================================================
void StrTree::InsertAt(NodeHdr** out, NodeHdr* at, const PairB* val, char flag)
{
    int left;
    if (!flag && at != &a && _stricmp(val->k.b, ((Node*)at)->v.k.b) >= 0) left = 1; else left = 0;
    Node* nn = NewNodeFromPair(val);
    RBTreeInsert(nn, at, &a, left);
    count += 1;
    *out = nn;
}

// ===========================================================================
// @ 0x0067F260  StrTree::InsertPair (find-or-insert by value)
// ===========================================================================
void StrTree::InsertPair(InsResult* out, const PairB* val, char)
{
    NodeHdr* parent = &a;
    NodeHdr* n = a.parent;
    bool less = true;
    while (n) {
        less = _stricmp(val->k.b, ((Node*)n)->v.k.b) < 0;
        parent = n;
        n = less ? n->left : n->right;
    }
    NodeHdr* pos = parent;
    if (less) {
        if (parent == a.left) {
            int left;
            if (parent != &a && _stricmp(val->k.b, ((Node*)parent)->v.k.b) >= 0) left = 1; else left = 0;
            Node* nn = NewNodeFromPair(val);
            RBTreeInsert(nn, parent, &a, left);
            count += 1;
            out->it = nn;
            out->ok = true;
            return;
        }
        parent = RBTreeDecrement(parent);
    }
    if (_stricmp(((Node*)parent)->v.k.b, val->k.b) < 0) {
        int left;
        if (pos != &a && _stricmp(val->k.b, ((Node*)pos)->v.k.b) >= 0) left = 1; else left = 0;
        Node* nn = NewNodeFromPair(val);
        RBTreeInsert(nn, pos, &a, left);
        count += 1;
        out->it = nn;
        out->ok = true;
        return;
    }
    out->it = parent;
    out->ok = false;
}

// ===========================================================================
// @ 0x0067F390  SP::cCheatManager::Shutdown (release console + parser + consoles)
// ===========================================================================
bool CheatMgr::Shutdown()
{
    if (!mParser.p)
        return false;
    void* tr = EA_Trace_GetServer();
    if (tr) {
        IRef* c = 0;
        if (TC2(bool, tr, 0x2c, const char*, "AppConsole", IRef**, &c))
            TC1(void, tr, 0x20, IRef*, c);
        if (c) c->Release();
    }
    TC0(void, mParser.p, 0xc);
    void* p = mParser.p;
    if (p) {
        mParser.p = 0;
        TC0(void, p, 4);
    }
    mConsoles.Nuke(mConsoles.a.parent);
    mConsoles.a.left = &mConsoles.a;
    mConsoles.a.parent = 0;
    mConsoles.a.color = 0;
    mConsoles.count = 0;
    mConsoles.a.right = &mConsoles.a;
    return true;
}

// ===========================================================================
// @ 0x0067F470  SP::cCheatManager::FindCommand
// ===========================================================================
void* CheatMgr::FindCommand(const char* name)
{
    EStr key(name);
    NodeHdr* it;
    mNames.find(&it, key);
    if (it != &mNames.a)
        return ((Node*)it)->v.v;
    return 0;
}

// ===========================================================================
// @ 0x0067F540  insert console into the consoles set
// ===========================================================================
void CheatMgr::InsertConsole(IRef* c)
{
    ConsoleRef k(c);
    InsResult r;
    mConsoles.Insert(&r, &k, 0);
}

// ===========================================================================
// @ 0x0067F5C0  find-and-erase console
// ===========================================================================
void CheatMgr::RemoveConsole(IRef* c)
{
    NodeHdr* it;
    {
        ConsoleRef k(c);
        mConsoles.Find(&it, &k);
    }
    if (it != &mConsoles.a) {
        mConsoles.count -= 1;
        RBTreeIncrement(it);
        RBTreeErase(it, &mConsoles.a);
        IRef* v = ((SetNode*)it)->v;
        if (v) v->Release();
        operator delete(it);
    }
}

// ===========================================================================
// @ 0x0067F670  StrTree::NukeSub (recursive subtree delete)
// ===========================================================================
void StrTree::NukeSub(Node* n)
{
    while (n) {
        NukeSub((Node*)n->right);
        Node* next = (Node*)n->left;
        ((PairBInl*)&n->v)->~PairBInl();
        operator delete(n);
        n = next;
    }
}

// ===========================================================================
// @ 0x0067F710  SP::cCheatManager::FindMatches (wildcard match over the names)
// ===========================================================================
int CheatMgr::FindMatches(const char* pat, PtrVec* out)
{
    int n = 0;
    for (NodeHdr* it = mNames.a.left; it != &mNames.a; it = RBTreeIncrement(it)) {
        const char* val;
        if (WildcardMatch(((Node*)it)->v.k.b, pat, 0)) {
            val = ((Node*)it)->v.k.b;
            const char** p = out->e;
            if (p < out->c) {
                out->e = p + 1;
                if (p) *p = val;
            } else {
                out->grow(p, &val);
            }
            n++;
        }
    }
    return n;
}

// ===========================================================================
// @ 0x0067F790  StrTree::InsertHint (insert with position hint)
// ===========================================================================
NodeHdr** StrTree::InsertHint(NodeHdr** out, NodeHdr* pos, const PairB* val, int)
{
    NodeHdr* anchor = &a;
    if (pos != a.right && pos != anchor) {
        NodeHdr* next = RBTreeIncrement(pos);
        if (_stricmp(((Node*)pos)->v.k.b, val->k.b) < 0 &&
            _stricmp(val->k.b, ((Node*)next)->v.k.b) < 0) {
            if (pos->right == 0) {
                InsertAt(out, pos, val, 0);
                return out;
            }
            Node* nn = NewNodeFromPair(val);
            RBTreeInsert(nn, next, anchor, 0);
            count += 1;
            *out = nn;
            return out;
        }
        InsResult r;
        InsertPair(&r, val, 0);
        *out = r.it;
        return out;
    }
    if (count != 0 && _stricmp(((Node*)a.right)->v.k.b, val->k.b) < 0) {
        NodeHdr* last = a.right;
        int left;
        if (last != anchor && _stricmp(val->k.b, ((Node*)last)->v.k.b) >= 0) left = 1; else left = 0;
        Node* nn = NewNodeFromPair(val);
        RBTreeInsert(nn, last, anchor, left);
        count += 1;
        *out = nn;
        return out;
    }
    InsResult r;
    InsertPair(&r, val, 0);
    *out = r.it;
    return out;
}

// ===========================================================================
// @ 0x0067F910  SP::cCheatManager::~cCheatManager
// ===========================================================================
CheatMgr::~CheatMgr()
{
}

// ===========================================================================
// @ 0x0067F9B0  SP::cCheatManager::RemoveCommand (parser + names map)
// ===========================================================================
void CheatMgr::RemoveCommand(const char* name)
{
    if (mParser.p) TC1(void, mParser.p, 0x18, const char*, name);
    NodeHdr* it;
    {
        EStr key(name);
        mNames.find(&it, key);
    }
    if (it != &mNames.a) {
        mNames.count -= 1;
        RBTreeIncrement(it);
        RBTreeErase(it, &mNames.a);
        ((Node*)it)->v.~PairB();
        operator delete(it);
    }
}
