// Slice s00ba47b0 -- creature-mode / cursor-map helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

typedef unsigned int uint;

// ---------------------------------------------------------------- types
struct Vec4i { int a, b, c, d; };

// EASTL map node: next/prev links, payload at +8, mapped value pointer at +0x14.
struct MapNode {
    MapNode* next;                        // +0x00
    MapNode* prev;                        // +0x04
    char pad08[0xc];
    void* value;                          // +0x14
};

struct HashTable {
    char pad00[4];
    MapNode** buckets;                    // +0x04
    int bucketCount;                      // +0x08
    void Find(MapNode** out, uint* key);  // 0x00db4780
};

struct CursorProvider {
    char pad00[0xc];
    HashTable table;                      // +0x0c

    char* FindByField10(uint key, int match);
    char* FindFirst10(uint* key, int a, int b, int c);
    char* FindFirst24(uint* key, int a, int b, int c);
    char* FindByField24(uint key, int match);
    void UpdateEntry(uint key, int a, int b, int c, int d, int e, int f);
};

struct CModeObj {
    void Update(int* key);
    void Method(int a, uint b, void* c);
};

// Per-creature behavior state block addressed through creature+0x20.
struct StateBlock {
    int* Get(int* key);                   // 0x00ba39f0
};

// Goal-state container: begin/end/cap of 0xb0-byte elements.
struct GoalVec {
    char* begin;                          // +0x00
    char* end;                            // +0x04
    char* cap;                            // +0x08
    char pad0c[8];
    bool  flags14;                        // +0x14

    void Insert(char* pos, char* src);
    int* Emplace(char* pos, char* src);
    char* FindOrAdd(uint* key);
};

struct GoalVecOwner {
    char pad00[0x20];
    StateBlock state;                     // +0x20
    char pad28[0x18];
    void* GetSlot(int* key);              // at +0x40, 0x00ba3a80
};

struct Telemetry {
    void Reset(int);                      // 0x007ebb60
};

struct ResMgr { int* Get(); };
struct IntVector { void resize(uint); };
struct TimeMgr { unsigned __int64 Get(); };
struct CommRef { void* GetCommContext(); };
struct Obj94 { void* Get(); };

// Element payload copier (ECX = destination, stack arg = source).
struct VecElem {
    void CopyFrom(void* src);             // 0x00ba3ca0
};

// ---------------------------------------------------------------- globals
extern char DAT_01654c10;
extern char DAT_01654c01;
extern char DAT_01654c02;

// ---------------------------------------------------------------- callees
void* __cdecl SP_NounManager();                          // 0x00b3d300
int __cdecl FUN_00b21340(...);                              // 0x00b21340 (thiscall, 5 args)
void __cdecl FUN_00b93c60(...);                             // 0x00b93c60
void __cdecl FUN_00829110(...);                             // 0x00829110
void __cdecl FUN_00f47380(void* p);                      // 0x00f47380  operator delete
int __cdecl SP_GetCurrentGameMode();                     // 0x00b5b800
int __cdecl FUN_00ba3f90(int, int*, int);                // 0x00ba3f90
void* __cdecl FUN_00c0c1a0(void* self);                  // 0x00c0c1a0
char __cdecl FUN_00c0c0e0(void* self);                   // 0x00c0c0e0
uint __cdecl FUN_00ba4270(int);                          // 0x00ba4270
void __cdecl FUN_00ba4600(void* self);                   // 0x00ba4600
void __cdecl FUN_00ba4330(int);                          // 0x00ba4330
int __cdecl FUN_00ba4290(int, void*);                    // 0x00ba4290
char __cdecl FUN_00ba46f0(void* self, int);              // 0x00ba46f0
void __cdecl FUN_00ba3860(void* self);                   // 0x00ba3860
void __cdecl FUN_00ba5e10(void* self, int);              // 0x00ba5e10
void __cdecl FUN_00572660(void* self);                   // 0x00572660
void* __cdecl FUN_00675250(uint, int);                   // 0x00675250
void __cdecl AutoTest(void* self, uint, uint);           // 0x00675830
void* __cdecl FUN_00c04590(void* self);                  // 0x00c04590
int __cdecl FUN_00bca0c0(int, int, int, int);            // 0x00bca0c0
void* __cdecl FUN_00d37cb0();                            // 0x00d37cb0
void* __cdecl FUN_00cd3440();                            // 0x00cd3440
void* __cdecl COMInterfaceCast(void*);                   // 0x00ac8960
void* __cdecl FUN_0067de90(...);                         // 0x0067de90
void* __cdecl FUN_00ba2f90();                            // 0x00ba2f90
void __cdecl FUN_00ba2f20(void* self);                   // 0x00ba2f20
int __cdecl FUN_00c72540(void*, void*, void*, char);     // 0x00c72540
void __cdecl FUN_00ba3ca0(void*);                        // 0x00ba3ca0
void __cdecl FUN_00ba45a0(void*, void*, void*);          // 0x00ba45a0
void* __cdecl operator_new(int);                         // 0x00f473a0
void __cdecl FUN_00ba4430(void*);                        // 0x00ba4430
void* __cdecl FUN_00ba3ea0(void*, void*, void*);         // 0x00ba3ea0
void __cdecl FUN_00ba36f0(void*, void*, void*);          // 0x00ba36f0
void __cdecl FUN_00ba5350(int**, int*, int*, int, int, int); // 0x00ba5350
void __cdecl FUN_00ba53b0(int**, int*, int*, int, int, int); // 0x00ba53b0
void* __cdecl FUN_00ba4520(void*);                       // 0x00ba4520

extern "C" uint64_t __cdecl _aulldiv(uint64_t, uint64_t); // 0x011e0970
void* __cdecl SP_GameTimeManager();                      // 0x00b3d380
unsigned __int64 __cdecl FUN_00b316c0(void* self);       // 0x00b316c0
void* __cdecl FUN_00c71e30(void* self);                  // 0x00c71e30
void* __cdecl GetCommContext(void* self);                // 0x00ce6950
void __cdecl FUN_00b3d4c0(void*);                        // 0x00b3d4c0
void __cdecl FUN_00b3d4f0(void*);                        // 0x00b3d4f0
void __cdecl FUN_00e30d20(void*);                        // 0x00e30d20
void __cdecl FUN_00675370();                             // 0x00675370
char __cdecl FUN_00675e80(uint);                         // 0x00675e80
void __cdecl FUN_00675770();                             // 0x00675770
void* __cdecl FUN_00607a60();                            // 0x00607a60
void* __cdecl SP_GetActivePlanet();                      // 0x00b3d240
void* __cdecl FUN_00c0bc00();                            // 0x00c0bc00
char __cdecl SetSpeciesAsScanned(void* planet);          // 0x00b3d520
void* __cdecl SP_GetTerrainSphere(void* mgr);            // 0x00c3b0f0

// ---------------------------------------------------------------- 0x00ba47b0
// @ 0x00BA47B0
void CModeObj::Update(int* key) {
    void* self = this;
    StateBlock* sb = (StateBlock*)((char*)self + 0x20);
    int* st = sb->Get(key);
    *(int*)((char*)st + 8) = 0;
    void* mgr = SP_NounManager();
    Vec4i* vec = (Vec4i*)FUN_00b21340();
    int* base = (int*)vec->a;
    FUN_00b93c60();
    int* out;
    FUN_00829110();
    int* p = (int*)vec->a;
    int* q = base;
    int* end = (int*)vec->b;
    for (; q != end; q++) {
        int* obj = (int*)*q;
        if (obj[0x2ca] == key[0] && obj[0x2cb] == key[1] && obj[0x2cc] == key[2])
            obj[0x2d6] &= 0xffffff7f;
    }
    for (; p < end; p++) {
        int* obj = (int*)*p;
        if (obj)
            ((void(__thiscall*)(void*))((void**)*obj)[1])(obj);
    }
    if (base && base[-1])
        FUN_00f47380(base);
}

// ---------------------------------------------------------------- 0x00ba48b0
// @ 0x00BA48B0
void CModeObj::Method(int a, uint b, void* c) {
    void* self = this;
    int st = FUN_00ba3f90(b, (int*)c, 0);
    void* mode = (void*)SP_GetCurrentGameMode();
    if (mode == &DAT_01654c10) {
        if (c) {
            if (((char(__thiscall*)(void*))((void**)*(void**)c)[0xb])(c))
                return;
            if (*((char*)c + 0xb5e))
                return;
        }
        if (a != 3)
            return;
        int nx = st == 3 ? 6 : st;
        if (!c)
            return;
        if (nx == st)
            return;
        FUN_00572660(c);
        int* slot = (int*)((GoalVecOwner*)self)->GetSlot((int*)&a);
        *slot = nx;
        if (!a)
            return;
        ((void(__thiscall*)(void*))((void**)*(void**)a)[1])((void*)a);
        return;
    }
    uint flag2 = 0;
    uint flag3 = 0;
    if (c) {
        if (((char(__thiscall*)(void*))((void**)*(void**)c)[0x34])(c)) {
            if (a != 4)
                return;
            int* st2 = ((StateBlock*)((char*)self + 0x20))->Get((int*)&b);
            *st2 = st;
            FUN_00ba5e10(c, 7);
            return;
        }
        if (!FUN_00c0c1a0(c))
            return;
    }
    int nx = st;
    switch (a) {
    case 0:
        ((CModeObj*)self)->Update((int*)&b);
        if (!c)
            goto def;
        if (FUN_00c0c0e0(c) && (void*)SP_GetCurrentGameMode() == &DAT_01654c01) {
            AutoTest((void*)FUN_00675250(0x343100cc, 1), 0x343100cc, 1);
        }
        {
            int* st2 = ((StateBlock*)((char*)self + 0x20))->Get((int*)&b);
            st2[3]++;
            void* cm = FUN_00c0c1a0(c);
            if ((uint)st2[3] < *(uint*)((char*)cm + 0x400)) {
                void* cm2 = FUN_00c0c1a0(c);
                if (*(uint*)((char*)cm2 + 0x3fc) <= (uint)st2[3] &&
                    (FUN_00ba4270(b) > 1 || (nx = 1, st == 5)))
                    goto lab_b07;
            } else {
                FUN_00ba4600(c);
                flag3 = 1;
                nx = 5;
            }
            goto lab_b0c;
        }
    case 1:
        ((CModeObj*)self)->Update((int*)&b);
        if (FUN_00ba4270(b) > 1 || st == 5)
            goto lab_b86;
        nx = 2;
        break;
    case 2:
        ((CModeObj*)self)->Update((int*)&b);
        if (st != 4 && st != 6)
            goto def;
        nx = 3;
        break;
    case 3: {
        void* animal = COMInterfaceCast(c);
        if (animal) {
            void* s = FUN_00c04590(animal);
            *((char*)s + 0x85) = 0;
        }
        int r = FUN_00bca0c0(2, 1, 0, 0);
        if (st == 5 && r == -1)
            break;
        FUN_00ba4330(b);
        nx = FUN_00ba4290(b, c);
        flag2 = 1;
        break;
    }
    case 4:
        goto case4;
    case 5: {
        int* st2 = ((StateBlock*)((char*)self + 0x20))->Get((int*)&b);
        st2[3]++;
        void* cm = FUN_00c0c1a0(c);
        if (*(uint*)((char*)cm + 0x400) <= (uint)st2[3]) {
            FUN_00ba4600(c);
            flag3 = 1;
        }
        ((CModeObj*)self)->Update((int*)&b);
lab_b07:
        nx = 5;
lab_b0c: {
        void* animal = COMInterfaceCast(c);
        if (animal) {
            void* s = FUN_00c04590(animal);
            *((char*)s + 0x85) = 0;
        }
        break;
        }
    }
    case 6:
        ((CModeObj*)self)->Update((int*)&b);
        if (st == 5)
            goto def;
        nx = 2;
        break;
    case 7:
        ((CModeObj*)self)->Update((int*)&b);
lab_b86:
        nx = 5;
        break;
    default:
        goto def;
    }
    if (nx != st) {
        FUN_00ba46f0(c, nx == 6);
        if ((char)flag2)
            FUN_00ba3860(c);
case4:
        if (nx == 3) {
            int* st2 = ((StateBlock*)((char*)self + 0x20))->Get((int*)&b);
            st2[3] = 0;
        } else if (nx == 4) {
            int* st2 = ((StateBlock*)((char*)self + 0x20))->Get((int*)&b);
            st2[1]++;
        }
        {
            int* st2 = ((StateBlock*)((char*)self + 0x20))->Get((int*)&b);
            *st2 = nx;
            if (c && (char)flag3 == 0)
                FUN_00ba5e10(c, 5);
        }
    }
def:
    mode = (void*)SP_GetCurrentGameMode();
    if (mode == &DAT_01654c01) {
        void* p = FUN_00d37cb0();
        ((void(__thiscall*)(void*, int))((void**)*(void**)p)[0xa])(p, 0);
    } else if (mode == &DAT_01654c02) {
        void* p = FUN_00cd3440();
        ((void(__thiscall*)(void*, int))((void**)*(void**)p)[0xa])(p, 0);
        return;
    }
}

// ---------------------------------------------------------------- 0x00ba4c70
// @ 0x00BA4C70
void GoalVec::Insert(char* pos, char* src) {
    GoalVec* self = this;
    char* end = self->end;
    if (end != self->cap) {
        if (pos <= src && src < end)
            src += 0xb0;
        if (end) {
            *(int*)end = *(int*)(end - 0xb0);
            FUN_00ba3ca0(end - 0xa8);
        }
        FUN_00ba45a0(pos, self->end - 0xb0, self->end);
        *(int*)pos = *(int*)src;
        FUN_00ba4430(src + 8);
        self->end += 0xb0;
        return;
    }
    int n = (end - self->begin) / 0xb0;
    if (n == 0)
        n = 1;
    else
        n *= 2;
    char* mem = 0;
    if (n)
        mem = (char*)operator_new(n * 0xb0);
    char* begin = self->begin;
    char* mid = (char*)FUN_00ba3ea0(begin, pos, mem);
    FUN_00ba36f0(begin, pos, mem);
    if (mid) {
        *(int*)mid = *(int*)src;
        FUN_00ba3ca0(src + 8);
    }
    char* oldEnd = self->end;
    char* last = (char*)FUN_00ba3ea0(pos, oldEnd, mid + 0xb0);
    FUN_00ba36f0(pos, oldEnd, mid + 0xb0);
    if (self->begin)
        FUN_00f47380(self->begin);
    self->begin = mem;
    self->end = last;
    self->cap = mem + n * 0xb0;
}

// ---------------------------------------------------------------- 0x00ba4de0
// @ 0x00BA4DE0
int* GoalVec::Emplace(char* pos, char* src) {
    GoalVec* self = this;
    int idx = (pos - self->begin) / 0xb0;
    char* end = self->end;
    if (pos == end && end != self->cap) {
        self->end = end + 0xb0;
        if (end) {
            *(int*)end = *(int*)src;
            ((VecElem*)(end + 8))->CopyFrom(src + 8);
            return (int*)(self->begin + idx * 0xb0);
        }
    } else {
        self->Insert(pos, src);
    }
    return (int*)(self->begin + idx * 0xb0);
}

// ---------------------------------------------------------------- 0x00ba4e60
// @ 0x00BA4E60
char* GoalVec::FindOrAdd(uint* key) {
    GoalVec* self = this;
    MapNode* end = (MapNode*)self->end;
    MapNode* found = (MapNode*)FUN_00c72540(self->begin, end, key, self->flags14);
    if (found == end || *key < *(uint*)found) {
        char* tmp = (char*)FUN_00ba2f90();
        uint k = *key;
        FUN_00ba3ca0(tmp);
        end = (MapNode*)self->end;
        MapNode* lo = (found == end || *(uint*)found <= k) ? found : (MapNode*)self->begin;
        MapNode* hi = (found == end || *(uint*)found <= k) ? end : found;
        found = (MapNode*)FUN_00c72540(lo, hi, &k, self->flags14);
        if (found == end || k < *(uint*)found)
            found = (MapNode*)self->Emplace((char*)found, (char*)&k);
        FUN_00ba2f20(tmp);
        FUN_00ba2f20(tmp + 0xc0);
    }
    return (char*)found + 8;
}

// ---------------------------------------------------------------- 0x00ba4f30
// @ 0x00BA4F30
int __cdecl FUN_00ba4f30(int* obj) {
    SP_GetActivePlanet();
    if (obj) {
        void* p = (void*)((int(__thiscall*)(void*, uint))((void**)*obj)[3])(obj, 0xd0036e08);
        if (p) {
            void* s = FUN_00c04590(p);
            if (s && *(int*)((char*)s + 0x160))
                *(uint*)(*(int*)((char*)s + 0x160) + 0x124) |= 1;
        }
    }
    void* planet = FUN_00c0bc00();
    char scanned = SetSpeciesAsScanned(planet);
    if (scanned)
        return 0;
    void* mode = (void*)SP_GetCurrentGameMode();
    if (mode == &DAT_01654c10)
        return 0;
    char c = (char)((int(__thiscall*)(void*))((void**)*(void**)((char*)obj + 0xc0))[0x16])((char*)obj + 0xc0);
    int st = FUN_00ba3f90((int)obj, obj, 0);
    void* terr = SP_GetTerrainSphere(SP_NounManager());
    ((GoalVec*)&st)->FindOrAdd((uint*)&terr);
    void* p2 = FUN_00c0bc00();
    char* f = (char*)FUN_00ba4520(p2);
    *f = 1;
    void* p3 = FUN_00c0bc00();
    FUN_00b3d4c0(p3);
    int state = FUN_00ba3f90((int)p3, obj, 0);
    void* mode2 = (void*)SP_GetCurrentGameMode();
    if (mode2 == &DAT_01654c10) {
        ((void(__thiscall*)(void*))((void**)*obj)[0xb])(obj);
    } else {
        char d = (char)((int(__thiscall*)(void*))((void**)*obj)[0x34])(obj);
        if (d == 0) {
            if (FUN_00c0c1a0(p3)) {
                if (state == 3) {
                    int* s = ((StateBlock*)((char*)obj + 0x20))->Get((int*)&p3);
                    s[3] = 0;
                } else if (state == 4) {
                    int* s = ((StateBlock*)((char*)obj + 0x20))->Get((int*)&p3);
                    s[1]++;
                }
                int* s = ((StateBlock*)((char*)obj + 0x20))->Get((int*)&p3);
                *s = state;
                FUN_00ba5e10(obj, 5);
                void* mode3 = (void*)SP_GetCurrentGameMode();
                if (mode3 == &DAT_01654c01) {
                    void* q = FUN_00d37cb0();
                    ((void(__thiscall*)(void*, int))((void**)*(void**)q)[0xa])(q, 0);
                } else if (mode3 == &DAT_01654c02) {
                    void* q = FUN_00cd3440();
                    ((void(__thiscall*)(void*, int))((void**)*(void**)q)[0xa])(q, 0);
                }
            }
        } else {
            int* s = ((StateBlock*)((char*)obj + 0x20))->Get((int*)&p3);
            *s = state;
            FUN_00ba5e10(obj, 7);
        }
    }
    char e = (char)((int(__thiscall*)(void*))((void**)*(void**)((char*)obj + 0xc0))[0x16])((char*)obj + 0xc0);
    FUN_00ba5e10(obj, (e ? 6 : 0) + 1);
    FUN_00b3d4f0(p3);
    FUN_00e30d20(p3);
    void* mode4 = (void*)SP_GetCurrentGameMode();
    if (mode4 == &DAT_01654c01) {
        FUN_00675250(0xd35d68dd, 1);
        FUN_00675370();
        if (!FUN_00675e80(0xd35d68dd)) {
            void* q = FUN_00c0bc00();
            uint val = *(uint*)q;
            // hashtable insert not reconstructed
            (void)val;
        } else {
            FUN_00675770();
        }
    }
    return 1;
}

// ---------------------------------------------------------------- 0x00ba51f0
// @ 0x00BA51F0
void __cdecl FUN_00ba51f0() {
    Telemetry* t = (Telemetry*)FUN_0067de90();
    for (int i = 7; i <= 0xb; i++)
        t->Reset(i);
}

// ---------------------------------------------------------------- 0x00ba5220
// @ 0x00BA5220
int __cdecl FUN_00ba5220() {
    int mode = SP_GetCurrentGameMode();
    switch (mode) {
    case 0x1654c00: return 7;
    case 0x1654c01: return 8;
    case 0x1654c02: return 9;
    case 0x1654c04: return 10;
    case 0x1654c05: return 11;
    default:        return 11;
    }
}

// ---------------------------------------------------------------- 0x00ba5270
// @ 0x00BA5270
int* __cdecl FUN_00ba5270(int obj, uint arg) {
    if (obj == 0)
        return 0;
    void* res = FUN_0067de90(FUN_00ba5220(), 0);
    int* vec = (int*)((ResMgr*)res)->Get();
    if (vec == 0)
        return 0;
    ((IntVector*)vec)->resize(0xc);
    void* gt = SP_GameTimeManager();
    unsigned __int64 t = ((TimeMgr*)gt)->Get();
    int* p = (int*)vec[3];
    p[0] = (int)(t / 1000);
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[4] = arg;
    p[5] = (int)((CommRef*)(obj + 0x13c))->GetCommContext();
    p[6] = 5;
    void* x = ((Obj94*)(void*)obj)->Get();
    p[7] = x ? *(int*)((char*)x + 0x10) : 0xff576f79;
    p[8] = 0;
    p[9] = ((int(__thiscall*)(void*))((void**)*(void**)(obj + 0xd4))[0x13])((void*)(obj + 0xd4));
    p[10] = 0xf4c9dc5a;
    return vec;
}

// ---------------------------------------------------------------- 0x00ba5350
// @ 0x00BA5350
void __cdecl FUN_00ba5350_impl(int** out, int* begin, int* end, int a, int b, int c) {
    if (begin == end) {
        *out = begin;
        return;
    }
    while (begin != end) {
        int* node = (int*)begin[5];
        if (node[2] == a && node[1] == b && node[3] == c && node[9] == -1)
            break;
        begin = (int*)*begin;
    }
    *out = begin;
}

// ---------------------------------------------------------------- 0x00ba53b0
// @ 0x00BA53B0
void __cdecl FUN_00ba53b0_impl(int** out, int* begin, int* end, int a, int b, int c) {
    if (begin == end) {
        *out = begin;
        return;
    }
    while (begin != end) {
        int* node = (int*)begin[5];
        if (node[2] == a && node[1] == b && node[3] == c)
            break;
        begin = (int*)*begin;
    }
    *out = begin;
}

// ---------------------------------------------------------------- 0x00ba5410
// @ 0x00BA5410
char* CursorProvider::FindByField10(uint key, int match) {
    CursorProvider* self = this;
    MapNode* found[2];
    char* result = 0;
    HashTable* t = &self->table;
    t->Find(found, &key);
    MapNode** buckets = t->buckets;
    if (found[0] != buckets[t->bucketCount]) {
        MapNode* head = (MapNode*)((char*)found[0] + 4);
        for (MapNode* n = head->next; n != head; n = n->next) {
            if (*(int*)((char*)n->value + 0x10) == match) {
                if (n != head)
                    result = (char*)n + 8;
                break;
            }
        }
    }
    return result;
}

// ---------------------------------------------------------------- 0x00ba5470
// @ 0x00BA5470
char* CursorProvider::FindFirst10(uint* key, int a, int b, int c) {
    CursorProvider* self = this;
    MapNode* found[2];
    char* result = 0;
    HashTable* t = &self->table;
    t->Find(found, key);
    MapNode** buckets = t->buckets;
    if (found[0] != buckets[t->bucketCount]) {
        MapNode* head = (MapNode*)((char*)found[0] + 4);
        void* res;
        FUN_00ba5350_impl((int**)&res, (int*)head->next, (int*)head, a, b, c);
        if (res != head)
            result = (char*)res + 8;
    }
    return result;
}

// ---------------------------------------------------------------- 0x00ba54f0
// @ 0x00BA54F0
char* CursorProvider::FindFirst24(uint* key, int a, int b, int c) {
    CursorProvider* self = this;
    MapNode* found[2];
    char* result = 0;
    HashTable* t = &self->table;
    t->Find(found, key);
    MapNode** buckets = t->buckets;
    if (found[0] != buckets[t->bucketCount]) {
        MapNode* head = (MapNode*)((char*)found[0] + 4);
        void* res;
        FUN_00ba53b0_impl((int**)&res, (int*)head->next, (int*)head, a, b, c);
        if (res != head)
            result = (char*)res + 8;
    }
    return result;
}

// ---------------------------------------------------------------- 0x00ba5570
// @ 0x00BA5570
char* CursorProvider::FindByField24(uint key, int match) {
    CursorProvider* self = this;
    MapNode* found[2];
    char* result = 0;
    HashTable* t = &self->table;
    t->Find(found, &key);
    MapNode** buckets = t->buckets;
    if (found[0] != buckets[t->bucketCount]) {
        MapNode* head = (MapNode*)((char*)found[0] + 4);
        for (MapNode* n = head->next; n != head; n = n->next) {
            if (*(int*)((char*)n->value + 0x24) == match) {
                if (n != head)
                    result = (char*)n + 8;
                break;
            }
        }
    }
    return result;
}

// ---------------------------------------------------------------- 0x00ba55d0
// @ 0x00BA55D0
void CursorProvider::UpdateEntry(uint key, int a, int b, int c,
                                 int d, int e, int f) {
    CursorProvider* self = this;
    MapNode* found[2];
    HashTable* t = &self->table;
    t->Find(found, &key);
    MapNode** buckets = t->buckets;
    if (found[0] != buckets[t->bucketCount]) {
        MapNode* head = (MapNode*)((char*)found[0] + 4);
        for (MapNode* n = head->next; n != head; n = n->next) {
            int* v = (int*)n->value;
            if (v[2] == a && v[1] == b && v[3] == c) {
                v[1] = d;
                v[2] = e;
                v[3] = f;
            }
        }
    }
}
