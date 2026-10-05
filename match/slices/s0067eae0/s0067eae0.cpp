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
// @ 0x0067EEF0  placement-new helper (EH)
// ===========================================================================
extern "C" void* __cdecl EASTL_alloc24(unsigned int, const char*, int, int, const char*, int);
extern "C" void  __cdecl FUN_0067e900(void*);   // construct at +0x10

void* alloc_67eef0(int arg)
{
    void* mem = EASTL_alloc24(0x24, "App", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
    if (!mem)
        return 0;
    FUN_0067e900((char*)mem + 0x10);
    return mem;
}

// ===========================================================================
// @ 0x0067F1F0  rbtree insert wrapper
// ===========================================================================
struct RBTree_1f0 {
    char pad0[4];
    void* head;    // +0x04
    char pad8[0xc];
    int count;     // +0x14
    void insert(void** out, void* at, void** value, char flag);
};

void RBTree_1f0::insert(void** out, void* at, void** value, char flag)
{
    int less = 0;
    if (!flag && at != (char*)this + 4) {
        if (_stricmp((char*)*value, *(char**)((char*)at + 0x10)) >= 0)
            less = 1;
    }
    void* node = alloc_67eef0((int)value);
    FUN_009216a0(node, at, (char*)this + 4, less);
    count += 1;
    *out = node;
}
// ---- additional externs for the remaining SP::cCheatManager methods ----
extern char g_HM_1401510v[];
extern char g_HM_13ec458v[];
extern char g_HM_13eb938v[];
extern char g_HM_1401b74[];
extern "C" void* __cdecl EASTL_deallocate_(void*);
extern "C" void* __cdecl RBTreeIncrement(void*);
extern "C" void* __cdecl RBTreeDecrement(void*);
extern "C" void* __cdecl CreateParser();
extern "C" void  __cdecl AddBuiltInCheats(void*);
extern "C" void* __cdecl EA_Trace_GetServer();
extern "C" void* __cdecl RBTreeDecrement(void*);
extern "C" void* __cdecl RBTreeErase(void*, void*);
extern "C" void  __cdecl DoNukeSubtree(void*);
extern "C" int   __cdecl WildcardMatch(const char*, const char*, int);
extern "C" int   __cdecl HasFlag(void*, const char*);
extern "C" void  __cdecl Output(void*, const char*, ...);
extern "C" void  __cdecl FUN_00eb6280(void*);

// ===========================================================================
// @ 0x0067EAE0  anonymous::cCheatHelpCommand::Execute (partial)
// ===========================================================================
struct Cmd_eae0 {
    char pad0[4];
    void* p4;        // +0x04 output sink
    char pad8[8];
    void* p10;       // +0x10 cheat manager
    void Execute(void* args);
};

void Cmd_eae0::Execute(void* args)
{
    void* r = ((Arguments*)args)->MainArguments(&args, 0, 1);
    const char* key = (int)args > 0 ? *(const char**)r : "";
    void* list[3] = {0, 0, 0};
    int n = ((int (__thiscall*)(void*, const char*, void**))VT(p10)[0x2c / 4])(p10, key, list);
    int count = (int)((char*)list[1] - (char*)list[0]) >> 2;
    if (count == 0) {
        Output(p4, "command not found\n");
    } else {
        int mode = n == 1 ? 1 : 0;
        if (HasFlag(args, "full")) mode = 1;
        if (HasFlag(args, "html")) mode = 2;
        for (int i = 0; i < count; ++i) {
            void* cmd = ((void* (__thiscall*)(void*, const char*))VT(p10)[0x28 / 4])
                            (p10, ((const char**)list[0])[i]);
            const char* desc = ((const char* (__thiscall*)(void*, int))VT(cmd)[1])(cmd, mode);
            if (!desc && !(desc = ((const char* (__thiscall*)(void*, int))VT(cmd)[1])(cmd, 1)))
                desc = ((const char* (__thiscall*)(void*, int))VT(cmd)[1])(cmd, 0);
            if (!desc) desc = "no description";
            if (mode == 0)
                Output(p4, "%-20s: %s\n", ((const char**)list[0])[i], desc);
            else
                Output(p4, "%-20s\n%s\n", ((const char**)list[0])[i], desc);
        }
    }
    if (list[0] && *((int*)list[0] - 1) != 0)
        EASTL_deallocate_(list[0]);
}

// ===========================================================================
// @ 0x0067ED00  SP::cCheatManager::Init (partial)
// ===========================================================================
struct CheatManager2 {
    char pad0[0x28];
    void* mpParser;   // +0x28
    char pad2c[0x18];
    void* p44;        // +0x44
    char pad48[0x50];
    void* p98;        // +0x98
    char pad9c[0x100];
    void* p19c;
    void* p1a0;
    void* p1a4;
    void* p1a8;
    unsigned char b1ac;
    void* p1b0;
    void* p1b4;
    int Init();
};

int CheatManager2::Init()
{
    if (mpParser) return 0;
    void* parser = CreateParser();
    mpParser = parser;
    ((void (__thiscall*)(void*))VT(parser)[2])(parser);
    AddBuiltInCheats(this);
    void* cm = EASTL_alloc24(0x20, "App/CheatManager", 0, 0, 0, 0);
    ((void (__thiscall*)(void*, void*))VT(mpParser)[0xbc / 4])(mpParser, cm);
    ((void (__thiscall*)(void*))VT(mpParser)[0x30 / 4])(mpParser);
    void* tr = EA_Trace_GetServer();
    if (tr) {
        void* cm2 = EASTL_alloc24(0x28, "App/CheatManager", 0, 0, 0, 0);
        ((void (__thiscall*)(void*, void*))VT(tr)[0x1c / 4])(tr, cm2);
        ((void (__thiscall*)(void*, const char*, int, int))VT(tr)[0x30 / 4])(tr, "AppConsole", 0, 100);
        ((void (__thiscall*)(void*, const char*, const char*, int))VT(tr)[0x30 / 4])(tr, "AppConsole", "Console", 1);
    }
    return 1;
}

// ===========================================================================
// @ 0x0067EE60  string + AutoRefCount constructor (partial)
// ===========================================================================
struct Str3 { char* begin; char* end; char* cap; };

Str3* ctor_67ee60(Str3* self, void* src, int** ref)
{
    self->begin = self->end = self->cap = 0;
    char* s = *(char**)src;
    char* e = *((char**)src + 1);
    unsigned n = (unsigned)(e - s);
    self->begin = (char*)EASTL_alloc24(n + 1, 0, 0, 0, 0, 0);
    char* d = self->begin;
    for (unsigned i = 0; i < n; ++i) d[i] = s[i];
    self->end = d + n;
    self->cap = d + n + 1;
    *self->end = 0;
    int* obj = *ref;
    *(int**)((char*)self + 0x10) = obj;
    if (obj) ((void (__thiscall*)(void*))VT(obj)[3])(obj);
    return self;
}

// ===========================================================================
// @ 0x0067EFC0  SP::cCheatManager::RunCheat (partial)
// ===========================================================================
int run_67efc0(CheatManager2* self, const char* name)
{
    unsigned char ok = 0;
    if (self->p44) {
        ((void (__thiscall*)(void*, const char*))VT(self->p44)[0x40 / 4])(self->p44, name);
        ok = 1;
    }
    return ok;
}

// ===========================================================================
// @ 0x0067F0C0 / 0x0067F260  rbtree find-or-insert (partial)
// ===========================================================================
struct RBNode { RBNode* left; RBNode* right; RBNode* parent; char color; char pad; char* key; char pad2[4]; };
struct RBMap {
    char pad0[4];
    RBNode* head;   // +0x04
    RBNode* tail;   // +0x08
    RBNode* root;   // +0x0c
    char pad10[4];
    int count;      // +0x14
    void find_or_insert(void** out, char** key, char flag);
    void find_or_insert2(void** out, char** key, char flag);
};

void RBMap::find_or_insert(void** out, char** key, char flag)
{
    (void)flag;
    RBNode* parent = head;
    RBNode* n = root;
    int less = 1;
    while (n) {
        int c = _stricmp(*key, n->key);
        less = c < 0;
        parent = n;
        n = less ? n->right : n->left;
    }
    (void)parent;
    void* node = alloc_67eef0((int)key);
    count += 1;
    *out = node;
    *((unsigned char*)out + 4) = 1;
}

void RBMap::find_or_insert2(void** out, char** key, char flag)
{
    find_or_insert(out, key, flag);
}

// ===========================================================================
// @ 0x0067F390  release console/file stream (partial)
// ===========================================================================
int release_67f390(void** self)
{
    if (!self[0x11]) return 0;
    void* tr = EA_Trace_GetServer();
    (void)tr;
    ((void (__thiscall*)(void*))VT((void*)self[0x11])[3])((void*)self[0x11]);
    self[0x11] = 0;
    FUN_00eb6280((void*)self[0x15]);
    self[0x14] = (void*)&self[0x13];
    self[0x15] = 0;
    self[0x17] = 0;
    *(void**)self[0x13] = (void*)&self[0x13];
    return 1;
}

// ===========================================================================
// @ 0x0067F470  string intern (partial)
// ===========================================================================
int intern_67f470(CheatManager2* self, const char* s)
{
    unsigned n = 0;
    while (s[n]) ++n;
    char* key = (char*)EASTL_alloc24(n + 1, 0, 0, 0, 0, 0);
    for (unsigned i = 0; i < n; ++i) key[i] = s[i];
    key[n] = 0;
    (void)self;
    EASTL_deallocate_(key);
    return 0;
}

void erase_67f9b0(CheatManager2* self, char* s)
{
    if (self->p44)
        ((void (__thiscall*)(void*, char*))VT(self->p44)[0x18 / 4])(self->p44, s);
    intern_67f470(self, s);
}

// ===========================================================================
// @ 0x0067F5C0  find-and-erase (partial)
// ===========================================================================
void erase_67f5c0(int* self, int* key)
{
    if (key) ((void (__thiscall*)(void*))VT((void*)key)[0])((void*)key);
    if (key) ((void (__thiscall*)(void*))VT((void*)key)[1])((void*)key);
    (void)self;
}

// ===========================================================================
// @ 0x0067F670  recursive subtree delete (partial)
// ===========================================================================
void delete_subtree_67f670(RBNode* n)
{
    while (n) {
        delete_subtree_67f670(n->left);
        RBNode* next = n->right;
        void* sub = *(void**)((char*)n + 0x20);
        if (sub) ((void (__thiscall*)(void*))VT(sub)[4])(sub);
        char* p = *(char**)((char*)n + 0x10);
        if ((int)(*(int*)((char*)n + 0x18) - (int)p) > 1 && p)
            EASTL_deallocate_(p);
        EASTL_deallocate_(n);
        n = next;
    }
}

// ===========================================================================
// @ 0x0067F710  wildcard match loop (partial)
// ===========================================================================
int search_67f710(int self, const char* pattern, int* results)
{
    int count = 0;
    for (int n = *(int*)(self + 0x14); n != self + 0x10; n = (int)RBTreeIncrement((void*)n)) {
        if (WildcardMatch(*(const char**)(n + 0x10), pattern, 0)) {
            int* end = (int*)(results + 1);
            int val = *(int*)(n + 0x10);
            if (*end < *(int*)(results + 2)) {
                *(int*)*end = val;
                *end += 4;
            } else {
                FUN_00690b80((void*)*end, &val);
            }
            count++;
        }
    }
    return count;
}

// ===========================================================================
// @ 0x0067F790  rbtree insert (partial)
// ===========================================================================
void* insert_67f790(int self, void** out, int* at, char** key)
{
    (void)self; (void)out; (void)at; (void)key;
    return 0;
}

// ===========================================================================
// @ 0x0067F910  App::CheatManager destructor (partial)
// ===========================================================================
struct AppCheat {
    void** vt; void* vt2;
    char pad8[0x2c];
    void* p34;
    void* p38;
    char pad3c[0x2c];
    void* p68;
    void* p6c;
    void* p70;
    void* p74;
    char pad78[0x1c];
    int* p94;
    char pad98[0x14];
    void* pB4;
    void dtor();
};

void AppCheat::dtor()
{
    vt = (void**)g_HM_1401510v;
    vt2 = (void*)g_HM_1401b74;
    FUN_00eb6280(p94);
    if (pB4) ((void (__thiscall*)(void*))VT(pB4)[1])(pB4);
    DoNukeSubtree(*(void**)((char*)&p34 + 4));
    delete_subtree_67f670((RBNode*)p68);
    vt2 = (void*)g_HM_13ec458v;
    vt = (void**)g_HM_13eb938v;
}

// ===========================================================================
// @ 0x0067F540  set insert with AutoRefCount (EH, partial)
// ===========================================================================
extern "C" void __cdecl FUN_0068a140(void*, void*, void*);
struct Set548 {
    char pad0[0x48];
    void insert(int* obj);
};
void Set548::insert(int* obj)
{
    if (obj) ((void (__thiscall*)(void*))VT((void*)obj)[0])((void*)obj);
    int* local = obj;
    char buf[12];
    FUN_0068a140(buf, &local, 0);
    if (obj) ((void (__thiscall*)(void*))VT((void*)obj)[1])((void*)obj);
}
