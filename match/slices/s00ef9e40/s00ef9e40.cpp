// Slice s00ef9e40 -- Simulator::cScenarioTutorials methods: rebuild of the step hashtables,
// message registration, app-preference read, and per-category / per-entry update helpers.
// Region flags: /O2 /MD /Gy /TP
#include "types.h"

// ---------------------------------------------------------------------------
// external helpers (masked relocations); thiscall callees modelled as stub members
// ---------------------------------------------------------------------------
extern "C" void* __cdecl SP_MessageServer();       // 0x0067dcc0
extern "C" void* __cdecl FUN_0067cac0();           // 0x0067cac0
#define SP_GetSomeMgr FUN_0067cac0
extern "C" void  __cdecl operator_delete_(void*);  // 0x00f47380

struct HashClear { void clear(void*, void*); };          // 0x0068fb70, ret 8
struct HashCtor  { void* ctor(int, int); };              // 0x00ef9950, ret 8
struct HashErase { void erase(void*, void*, void*, void*); }; // 0x00ef9a20, ret 0x10
struct CatUpdate { void f(int); };                       // 0x00ef7ec0, ret 4
struct EntryUpdate { void f(int); };                     // 0x00ef9af0, ret 4
struct InputFwd  { void f(int); };                       // 0x00ef8a10, ret 4
struct CatState  { unsigned f(int); };               // 0x00ef7330, ret 4
struct CatValid  { bool f(int); };                   // 0x00ef72d0, ret 4
struct Stopwatch { void SetTimeLimit(int, int); };       // 0x0093a480, ret 8
struct HashInsert { void insert(void*, void*); };        // 0x00ef8cc0, ret 8
struct HashFind  { void find(void*, void*); };           // 0x00a23ef0, ret 8
struct RefreshUI { void Refresh(); };                    // 0x00efbce0, ret 0
struct Mgr830    { void f(int); };                       // 0x0067c830, ret 4
extern "C" void __cdecl RefreshChecklist();              // 0x00efbce0 (call with this already in ecx)

// ---------------------------------------------------------------------------
// globals
// ---------------------------------------------------------------------------
extern void*    g_AppPreferences;      // 0x015fd91c
extern uint32_t g_msgNames[11];        // 0x0148b5d8
extern int      g_catTableA[];         // 0x0148b450 {lo,hi,hash,flag} x 0x10
extern int      g_catTableB[];         // 0x0148b510
extern uint8_t  g_16c7b50[2];          // 0x016c7b50

// ---------------------------------------------------------------------------
// cScenarioTutorials -- base at +0 is cContentValidationSummarizer.
// ---------------------------------------------------------------------------
struct cScenarioTutorials {
    char* self() { return (char*)this; }
    void Reset();                              // 0x00ef9e40
    void UpdateAll();                          // 0x00efa040
    void SetCategoryState(int category, char flag);   // 0x00efa0b0
    void HandleCategoryMessage(int category, int arg); // 0x00efa110
};

// @ 0x00ef9e40
void cScenarioTutorials::Reset()
{
    char* self = (char*)this;
    *(uint16_t*)(self + 0x38) = 0;
    *(uint8_t*)(self + 0x3a) = 0;
    char* step = self + 0x4a8;
    int n = 2;
    do {
        unsigned char tmp[0x14c];
        ((HashCtor*)tmp)->ctor(0, 0);
        ((HashClear*)step)->clear(*(void**)(step + 4), *(void**)(step + 8));
        *(int*)(step + 0xc) = 0;
        ((HashErase*)step)->erase(0, 0, 0, 0);
        ((HashClear*)0)->clear(0, 0);
        if (*(uint32_t*)(step + 0x38) > 1 && *(void**)(step + 0x34) != 0) {
            void* q = *(void**)(step + 0x34);
            if ((char*)q < *(char**)(step + 0x54) || (char*)q >= *(char**)(step + 0x58))
                operator_delete_(q);
        }
        step += 0x14c;
        n -= 1;
    } while (n != 0);

    void* ms = SP_MessageServer();
    *(void**)(self + 0x48) = ms;
    *(void**)(self + 0x4c) = self;
    *(void**)(self + 0x50) = g_msgNames;
    *(int*)(self + 0x54) = 0xb;
    *(int*)(self + 0x58) = 0;
    if (ms != 0 && self != 0) {
        unsigned i = 0;
        do {
            void** vt = *(void***)ms;
            void (__thiscall *f)(void*, void*, int) = (void(__thiscall*)(void*, void*, int))vt[0x24 / 4];
            f(ms, self, g_msgNames[i / 4]);
            i += 4;
        } while (i < 0x2c);
    }
    void* prefs = g_AppPreferences;
    int v0 = 0, v1 = 0;
    if (prefs != 0) {
        void** vt = *(void***)prefs;
        int (__thiscall *getprop)(void*, int, void*) = (int(__thiscall*)(void*, int, void*))vt[0x24 / 4];
        if (getprop(prefs, 0x7abf095, &v0) != 0) {
            // property value
        }
        getprop(prefs, 0x7abf09d, &v1);
    }
    int i = 0;
    do {
        int cnt = (&v0)[i];
        g_16c7b50[i] = (cnt != 0);
        if (cnt > 0) {
            unsigned char local = 0;
            int k = 0;
            do {
                ((HashInsert*)self)->insert(&local, 0);
                k++;
            } while (k < cnt);
        }
        i++;
    } while (i < 2);
}

// @ 0x00efa040
void cScenarioTutorials::UpdateAll()
{
    char* self = (char*)this;
    int idx = *(int*)(self + 0x30);
    if (idx == -1)
        return;
    int sel = *(int*)(self + 0x34);
    int* p;
    if (sel == 0) {
        p = (int*)((char*)g_catTableA + idx * 0x10);
    } else if (sel == 1) {
        p = (int*)((char*)g_catTableB + idx * 0x10);
    }
    int i = 0;
    do {
        ((CatUpdate*)self)->f(i);
        i++;
    } while (i != 0xad);
    int e = p[0];
    if (e <= p[1]) {
        do {
            ((EntryUpdate*)self)->f(e);
            e++;
        } while (e <= p[1]);
    }
}

// @ 0x00efa0b0
void cScenarioTutorials::SetCategoryState(int category, char flag)
{
    char* self = (char*)this;
    ((InputFwd*)self)->f(category);
    ((CatUpdate*)self)->f(category);
    unsigned state = ((CatState*)self)->f(category);
    if (state > 0) {
        ((Stopwatch*)(self + 0x10))->SetTimeLimit(state, 1);
        *(uint8_t*)(self + 0x3b) = 1;
    }
    ((EntryUpdate*)self)->f(category);
    if (((CatValid*)self)->f(category) && *(int*)(self + 0x30) != -1 && flag != 0) {
        RefreshChecklist();
    }
}

// @ 0x00efa110
void cScenarioTutorials::HandleCategoryMessage(int category, int arg)
{
    char* self = (char*)this;
    int local;
    int k = category;
    ((HashFind*)(self + 0x5c))->find(&local, &k);
    if (local == *(int*)(*(int*)(self + 0x60) + *(int*)(self + 0x64) * 4)) {
        ((InputFwd*)self)->f(category);
        ((CatUpdate*)self)->f(category);
        unsigned state = ((CatState*)self)->f(category);
        if (state > 0) {
            ((Stopwatch*)(self + 0x10))->SetTimeLimit(state, 1);
            *(uint8_t*)(self + 0x3b) = 1;
        }
        ((EntryUpdate*)self)->f(category);
    }
    if (*(uint8_t*)(self + 0x40) == 0) {
        ((Mgr830*)SP_GetSomeMgr())->f(arg);
    }
}
