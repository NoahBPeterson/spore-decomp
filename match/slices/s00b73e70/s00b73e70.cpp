// Slice s00b73e70: the Simulator module around Simulator::cObstacle (0xb73e70-0xb74f79):
// the obstacle/agent manager methods, its eastl hashtable helpers and the
// heap-sort sift helpers that share the translation unit.
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "types.h"

// ---------------------------------------------------------------- callees
void __stdcall FUN_00a887b0(int a, float f);      // 0xa887b0
void* SP_NounManager(int id);                      // 0xb3d300
void* SP_cGameNounManager_CreateNoun(void* m, int id);  // 0xb20c60
void* __cdecl EAAllocate(int a, const char* b, int c, int d, int e, int f); // 0xf473a0
void __stdcall FUN_00c3e240(float f);              // 0xc3e240
void* SP_GonzagoModelWorld();                      // 0xb3d520
void* __fastcall FUN_00b90410(void* self);         // 0xb90410  (GetSpeciesFromID)
void* __fastcall FUN_00b8f860(void* self);         // 0xb8f860
void* __stdcall FUN_00b3d440(void* a, void* b, void* c); // 0xb3d440
void* __fastcall FUN_00b03320(void* self);         // 0xb03320
void __stdcall FUN_00b74860(int* out, int* key);   // 0xb74860
extern "C" unsigned long long __allshl(unsigned lo, unsigned hi, int sh); // 0x011e06e0
struct Vec3 { float x, y, z; };
void __stdcall FUN_00b737d0(int begin, int i, int n, int idx, Vec3 v, void* cmp);
void __stdcall FUN_00b73920(int a, void* b, int c, void* d, Vec3 v);
bool __stdcall WriteUint32(void* stream, const void* p, int n, int flag);   // 0x93aa70
void __stdcall FUN_00ae2e40(void* a, int b);                                // 0xae2e40
void* __stdcall FUN_00b3d420_p(void* a);                                    // 0xb3d420
void* __stdcall FUN_00b3d440_0();                                            // 0xb3d440 (0 args)
void __stdcall FUN_00b3d440_2(void* out, void* a);                          // 0xb3d440 (2 args)
void* __stdcall FUN_00b3d440_3(void* a, void* b, void* c);                  // 0xb3d440 (3 args)
void* __fastcall FUN_00b04c20_3(void* a, void* b, void* c);                 // 0xb04c20
void* __fastcall FUN_00e5c780(void* self);                                  // 0xe5c780
unsigned int __fastcall FUN_00b058f0(void* self);                           // 0xb058f0
extern int g_156b470;
extern int g_156b424;
void* SP_ModelManager();                                                    // 0x67dd80
void __stdcall FUN_00571d40(void* a);                                       // 0x571d40
void __stdcall FUN_00571d20(void* a);                                       // 0x571d20
void __stdcall FUN_00478db0(void* a);                                       // 0x478db0
struct Vec3f { float x, y, z; };
struct HierGrid {
    char pad0[0x24];
    void* mBegin;      // +0x24
    void* mEnd;        // +0x28
    bool Shutdown();                                        // 0x704060
    bool Init(const Vec3f& v, float f, int a, int b);        // 0x704260
};
void* SP_GetActiveTerrainSphere();                          // 0xf48aa0

// __thiscall callees are modelled as member functions of dummy classes so that
// a direct call carries the right convention (this in ecx, ret N).
struct C74860 { void __thiscall Find(int* out, int* key); };          // 0xb74860
struct C72f10 { void* __thiscall Find(void* node, int* key, unsigned int hash); }; // 0xb72f10

// The obstacle record's node allocators live on the record itself (this in ecx,
// one pointer argument on the stack, ret 4).
struct Simulator_cObstacle;
struct Node3View {
    int f0;                  // +0x00 (doubles as the free-list link)
    int f4;                  // +0x04
    int f8;                  // +0x08 (sub-object with a vtable)
    int fC;                  // +0x0c
    int f10;                 // +0x10
};
struct Node2View {
    int f0;                  // +0x00 (doubles as the free-list link)
    int f4;                  // +0x04 (sub-object with a vtable)
    int f8;                  // +0x08
};
struct Simulator_cObstacle {
    void* AllocNode3(int* src);   // 0xb74b60
    void* AllocNode2(int* src);   // 0xb74bc0
};

// eastl hashtables used by the obstacle manager: two-key and three-key variants.
struct Hashtable2 {
    int mPad;                 // +0x00
    int* mBegin;              // +0x04
    int mCount;               // +0x08
    void Find(int* out, unsigned int* key);   // 0xb746a0
};
struct Hashtable3 {
    void Find(int* out, unsigned int* key);   // 0xb74740
    void* FindNode(void* node, int* key, unsigned int hash);  // 0xb72f10
};


// The object hung off a manager's +0x78 slot: a small wrapper whose first word is
// the implementing object (vtable at +0).  Its slots 0x16c/0x170 take the wrapper
// back as their first argument.
struct Inner { void** vptr; };            // first word is the vtable pointer
struct Wrapper { Inner* impl; };          // what +0x78 points at
typedef void (__thiscall *Fn16c)(void* self, void* owner, int a);
typedef void (__thiscall *Fn170)(void* self, void* owner, bool a);

// The 0x1688114 static descriptor block and its one-shot init flag.
struct C74860;   // fwd
extern unsigned int g_168814c;   // init flag (bit 0)
extern float g_1687ad4, g_1687ad8, g_1687adc;
extern char g_1687ad0;
extern float g_1485720;
struct Mat3 { void Assign(const void* src); };  // 0x41cb40 __thiscall

struct DescBlock {
    short f0;            // +0x00
    short f2;            // +0x02
    float f4;            // +0x04  (0x1688118)
    float f8;            // +0x08  (0x168811c)
    float fc;            // +0x0c  (0x1688120)
    float f10;           // +0x10  (0x1688124)
};
extern DescBlock g_desc;         // 0x1688114
extern Mat3 g_mtx;               // 0x1688128
extern char g_matrix_src[];      // 0x16880f0

// ======================================================================
// @ 0x00b74590
void __stdcall FUN_00b74590(int self)
{
    Wrapper* pw = *(Wrapper**)(self + 0x78);
    if (pw != 0) {
        Inner* in = pw->impl;
        ((Fn16c)in->vptr[0x16c / 4])(in, pw, 0);
        pw = *(Wrapper**)(self + 0x78);
        if (pw != 0) {
            *(int*)(self + 0x78) = 0;
            if (*(int*)((char*)pw + 0x40) > 1) {
                *(int*)((char*)pw + 0x40) -= 1;
                return;
            }
            in = pw->impl;
            ((Fn170)in->vptr[0x170 / 4])(in, pw,
                ((unsigned int)*(int*)((char*)pw + 4) >> 0x1f) != 0);
        }
    }
}

// ======================================================================
// @ 0x00b73e70
void* __fastcall FUN_00b73e70(int self)
{
    int mode = *(int*)(self + 0x88);
    int* result = 0;
    if (mode >= 0) {
        if (mode <= 3) {
            if (*(int*)(self + 0x58) != 0)
                result = (int*)(*(int*)(self + 0x5c) * 0x4c + *(int*)(self + 0x58));
        } else if (mode == 4) {
            if (*(int*)(self + 0x70) != 0)
                result = (int*)(*(int*)(self + 0x70) + 8);
        }
    }
    if (result != 0)
        return result;
    if ((g_168814c & 1) == 0) {
        g_168814c |= 1;
        g_desc.f4 = g_1687ad4;
        g_desc.f8 = g_1687ad8;
        g_desc.fc = g_1687adc;
        g_desc.f2 = 0;
        g_desc.f0 = 0;
        g_desc.f10 = g_1485720;
        g_mtx.Assign(g_matrix_src);
    }
    return &g_desc;
}

// ======================================================================
// @ 0x00b74ef0
void __stdcall FUN_00b74ef0(int self)
{
    FUN_00b74590(self);
    *(volatile unsigned int*)(self + 0x34) &= 0xfffffffe;
    int c = *(int*)(self + 0x54);
    if (c != 0) {
        FUN_00a887b0(*(int*)(self + 0x5c), c ? 1.0f : 0.0f);
        return;
    }
    Wrapper* pw = *(Wrapper**)(self + 0x70);
    if (pw != 0) {
        *(unsigned int*)((char*)pw + 4) |= 1;
        pw = *(Wrapper**)(self + 0x70);
        Inner* in = pw->impl;
        ((Fn16c)in->vptr[0x16c / 4])(in, pw, 1);
    }
}

// The obstacle manager record: a big object whose +0x56c0 sub-object is a
// two-key eastl hashtable.
struct ObstacleMgr {
    int Lookup(unsigned int* key);   // 0xb74f40
    int FindById(unsigned int* a, int b, int id);  // 0xb74e90
};

// ======================================================================
// @ 0x00b74f40 ObstacleMgr::Lookup
int ObstacleMgr::Lookup(unsigned int* key)
{
    int local[2];
    Hashtable2* ht = (Hashtable2*)((char*)this + 0x56c0);
    ht->Find(&local[0], key);
    if (local[0] != ht->mBegin[ht->mCount])
        return local[0] + 0xc;
    return 0;
}

// ======================================================================
// @ 0x00b749c0
void FUN_00b749c0(float* a, float* b, float x, float y, float z)
{
    while (a != b) {
        float dx = a[0] - x;
        float s = dx * dx;
        float dy = a[1] - y;
        s += dy * dy;
        float dz = a[2] - z;
        s += dz * dz;
        if (0.01f > s) break;
        a += 6;
    }
}

// ======================================================================
// @ 0x00b74c20
void FUN_00b74c20(float* a, float* b, float* c)
{
    for (; a != b; a += 3) {
        if (a != 0) {
            a[0] = c[0];
            a[1] = c[1];
            a[2] = c[2];
        }
    }
}

// ======================================================================
// @ 0x00b74b60 Simulator::cObstacle::AllocNode3
void* Simulator_cObstacle::AllocNode3(int* src)
{
    Node3View* node = *(Node3View**)((char*)this + 0x1c);
    if (node != 0) {
        *(int**)((char*)this + 0x1c) = (int*)node->f0;
    } else {
        node = (Node3View*)EAAllocate(*(int*)((char*)this + 0x2c), "Simulator", 0, 0, 0x13ebb38, 0xd1);
    }
    if (node != 0) {
        node->f0 = src[0];
        node->f4 = src[1];
        node->f8 = src[2];
        int* p = (int*)node->f8;
        if (p != 0) {
            (*(void(__thiscall**)(int*))*p)(p);
        }
    }
    node->f10 = 0;
    return node;
}

// ======================================================================
// @ 0x00b74bc0 Simulator::cObstacle::AllocNode2
void* Simulator_cObstacle::AllocNode2(int* src)
{
    Node2View* node = *(Node2View**)((char*)this + 0x1c);
    if (node != 0) {
        *(int**)((char*)this + 0x1c) = (int*)node->f0;
    } else {
        node = (Node2View*)EAAllocate(*(int*)((char*)this + 0x2c), "Simulator", 0, 0, 0x13ebb38, 0xd1);
    }
    if (node != 0) {
        node->f0 = src[0];
        node->f4 = src[1];
        int* p = (int*)node->f4;
        if (p != 0) {
            (*(void(__thiscall**)(int*))*p)(p);
        }
    }
    node->f8 = 0;
    return node;
}

// ======================================================================
// @ 0x00b74370
void* __fastcall FUN_00b74370(int self)
{
    void* result;
    if (((*(int*)(self + 0x40f4) - *(int*)(self + 0x40f0)) >> 2) != 0) {
        int* top = *(int**)(*(int*)(self + 0x40f4) - 4);
        result = 0;
        if (top != 0) {
            (*(void(__thiscall**)(int*))*top)(top);
            result = top;
        }
        *(int*)(self + 0x40f4) -= 4;
        int* slot = *(int**)(self + 0x40f4);
        if (*slot != 0)
            (*(void(__thiscall**)(int*))(*slot + 4))(slot);
    } else {
        void* m = SP_NounManager(0x3ed8573);
        result = SP_cGameNounManager_CreateNoun(m, 0x3ed8573);
        if (result == 0) return 0;
        (*(void(__thiscall**)(void*))*(int*)result)(result);
    }
    if (result != 0)
        (*(void(__thiscall**)(void*))(*(int*)result + 4))(result);
    return result;
}

// ======================================================================
// @ 0x00b746a0
void Hashtable2::Find(int* out, unsigned int* key)
{
    int* bucket = (int*)(*(int*)((char*)this + 4) + (*key % *(unsigned int*)((char*)this + 8)) * 4);
    unsigned int* node = (unsigned int*)*bucket;
    if (node != 0) {
        do {
            if (key[0] == node[0] && key[1] == node[1]) {
                unsigned int* nx = (unsigned int*)node[4];
                while (nx != 0 && key[0] == nx[0] && key[1] == nx[1])
                    nx = (unsigned int*)nx[4];
                int* slot = bucket;
                if (nx == 0) {
                    slot = bucket + 1;
                    while (*slot == 0) slot++;
                    nx = (unsigned int*)*slot;
                }
                out[1] = (int)bucket;
                out[0] = (int)node;
                out[2] = (int)nx;
                out[3] = (int)slot;
                return;
            }
            node = (unsigned int*)node[4];
        } while (node != 0);
    }
    int* endb = (int*)(*(int*)((char*)this + 4) + *(int*)((char*)this + 8) * 4);
    out[0] = *endb;
    out[1] = (int)endb;
    out[2] = *endb;
    out[3] = (int)endb;
}
// ======================================================================
// @ 0x00b74740 Hashtable3::Find
void Hashtable3::Find(int* out, unsigned int* key)
{
    unsigned int k2 = key[2];
    unsigned int h = key[0] ^ k2;
    unsigned int bi = h % *(unsigned int*)((char*)this + 8);
    int* bucket = (int*)(*(int*)((char*)this + 4) + bi * 4);
    void* node = FindNode((void*)*bucket, (int*)key, h);
    if (node != 0) {
        unsigned int* p = *(unsigned int**)((char*)node + 0xc70);
        while (p != 0 && *key == p[0] && key[1] == p[1] && k2 == p[2])
            p = *(unsigned int**)((char*)p + 0x31c);
        int* slot = bucket;
        if (p == 0) {
            slot = bucket + 1;
            while (*slot == 0) slot++;
            p = (unsigned int*)*slot;
        }
        out[0] = (int)node;
        out[1] = (int)bucket;
        out[2] = (int)p;
        out[3] = (int)slot;
        return;
    }
    int* endb = (int*)(*(int*)((char*)this + 4) + *(int*)((char*)this + 8) * 4);
    int v = *endb;
    out[0] = v;
    out[1] = (int)endb;
    out[2] = v;
    out[3] = (int)endb;
}

// ======================================================================
// @ 0x00b74e90 ObstacleMgr::FindById
struct Iter2 {
    int* cur;        // +0x00
    int* bucket;     // +0x04
    int* end;        // +0x08
    int* endBucket;  // +0x0c
};
int ObstacleMgr::FindById(unsigned int* a, int b, int id)
{
    Iter2 it;
    Hashtable2* ht = (Hashtable2*)((char*)this + 0x38);
    ht->Find((int*)&it, (unsigned int*)&a);
    int* cur = it.cur;
    int* end = it.end;
    int* bucket = it.bucket;
    while (cur != end) {
        if (*(int*)(*(int*)((char*)cur + 8) + 0x5c) == id)
            return *(int*)((char*)cur + 8);
        cur = *(int**)((char*)cur + 0x10);
        while (cur == 0) {
            bucket++;
            cur = (int*)*bucket;
        }
    }
    return 0;
}

// ======================================================================
// @ 0x00b74c50
void FUN_00b74c50(char* begin, char* end, void* cmp)
{
    int n = (int)(end - begin) / 0xc;
    if (n >= 2) {
        int i = ((n - 2) >> 1) + 1;
        int* p = (int*)(begin + 8 + i * 0xc);
        do {
            i--;
            FUN_00b737d0((int)begin, i, n, i, *(Vec3*)&p[-5], cmp);
            p -= 3;
        } while (i != 0);
    }
}

// ======================================================================
// @ 0x00b74cc0
void FUN_00b74cc0(char* begin, char* end, void* cmp)
{
    int n = (int)(end - begin) / 0xc;
    if (n > 1) {
        int* p = (int*)(end - 0xc);
        do {
            int a = p[0], b = p[1], c = p[2];
            p[0] = *(int*)begin;
            p[1] = *(int*)(begin + 4);
            p[2] = *(int*)(begin + 8);
            FUN_00b737d0((int)begin, 0, n - 1, 0, *(Vec3*)&a, cmp);
            p -= 3;
            n = (int)((char*)p - begin) / 0xc;
        } while (n > 1);
    }
}

// ======================================================================
// @ 0x00b74a60
void FUN_00b74a60(int* m, int* it)
{
    int* a = (*(int*(__thiscall**)(int*))(*(int*)m + 0x20))(m);
    int* ser = (int*)(*(int*(__thiscall**)(int*, int))(*(int*)a + 0x18))(a, it[3]);
    WriteUint32(ser, &it[3], 1, 0);
    int* bucket = (int*)it[1];
    int* node = (int*)*bucket;
    int* slot = bucket;
    if (node == 0) {
        slot = bucket + 1;
        while (*slot == 0) slot++;
        node = (int*)*slot;
    }
    int* end = (int*)(bucket[it[2]]);
    while (node != end) {
        FUN_00ae2e40(m, (int)node);
        (*(void(__thiscall**)(int*))(*(int*)m + 0x1c))(m);
        FUN_00ae2e40(m, (int)node + 0xc);
        (*(void(__thiscall**)(int*))(*(int*)m + 0x1c))(m);
        node = *(int**)((char*)node + 0x18);
        if (node == 0) {
            do { slot++; node = (int*)*slot; } while (node == 0);
        }
    }
    (*(void(__thiscall**)(int*))(*(int*)m + 0x1c))(m);
}

// ======================================================================
// @ 0x00b74d60
void FUN_00b74d60(int* base, void* b, int n, int i, void* cmp, float x, float y, float z)
{
    int c = i * 2 + 2;
    if (c < n) {
        do {
            int* n1 = (int*)(base[c]);
            float dz1 = z - *(float*)((char*)n1 + 0x40);
            float dx1 = x - *(float*)((char*)n1 + 0x38);
            float dy1 = y - *(float*)((char*)n1 + 0x3c);
            int* n2 = (int*)(base[c - 1]);
            float dy2 = y - *(float*)((char*)n2 + 0x3c);
            float dx2 = x - *(float*)((char*)n2 + 0x38);
            float dz2 = z - *(float*)((char*)n2 + 0x40);
            float d1 = dz1 * dz1 + dx1 * dx1 + dy1 * dy1;
            float d2 = dz2 * dz2 + dy2 * dy2 + dx2 * dx2;
            c = (d2 > d1) ? c : (i * 2 + 1);
            base[i] = base[c];
            i = c;
            c = i * 2 + 2;
        } while (c < n);
    }
    if (c == n) {
        base[i] = base[c - 1];
        i = c - 1;
    }
    Vec3 v; v.x = x; v.y = y; v.z = z;
    FUN_00b73920((int)base, b, i, cmp, v);
}

// ======================================================================
// @ 0x00b73f30
void __fastcall FUN_00b73f30(int self, float f, int arg)
{
    *(float*)(self + 0x68) = f;
    if (arg == 0) {
        if (*(int*)(self + 0x78) != 0 && g_1687ad0 == 0) {
            *(float*)(*(int*)(self + 0x78) + 0x58) = f;
            *(unsigned int*)(*(int*)(self + 0x78) + 4) |= 2;
        }
    } else if (*(int*)(arg + 0x10) != 0) {
        if (g_1687ad0 == 0) {
            FUN_00c3e240(f);
        } else if (f == 1.0f) {
            FUN_00c3e240(1.0f);
        } else {
            FUN_00c3e240(0.0f);
        }
    }
    if ((*(unsigned char*)(self + 0x34) & 1) == 0 && *(int*)(self + 0x54) != 0)
        FUN_00a887b0(*(int*)(self + 0x5c), 1.0f);

    if (*(int*)(self + 0x88) != 3 && *(int*)(self + 0x88) != 4) {
        void* p = FUN_00b3d420_p((void*)(self + 0x7c));
        void* sp = FUN_00b90410(p);
        if (sp != 0) sp = FUN_00b8f860(sp);
        else sp = 0;
        void* obj = FUN_00b3d440_3(sp, *(void**)(self + 0x50), *(void**)(self + 0x5c));
        void* esi = FUN_00b03320(obj);
        if (esi != 0) {
            void* pa;
            FUN_00b3d440_2(&pa, (char*)esi + 0x1c8);
            FUN_00e5c780((char*)FUN_00b3d440_0() + 0x8080);
            if (pa != (void*)((char*)FUN_00b3d440_0() + 0x8084)) {
                void* ebx = FUN_00b04c20_3(*(void**)((char*)esi + 0x4c),
                                           *(void**)((char*)esi + 0x50),
                                           *(void**)((char*)esi + 0x54));
                unsigned int i = 0;
                unsigned int n = FUN_00b058f0(esi);
                if ((char*)pa + 0x18 != 0) {
                    for (; ebx != 0 && i < n; i++) {
                        if (*(int*)((char*)pa + 0x18 + 0x14) != 0) {
                            unsigned long long m = __allshl(1, 0, (int)i);
                            if (((unsigned int)m & *(unsigned int*)((char*)ebx + 0x48)) ||
                                ((unsigned int)(m >> 32) & *(unsigned int*)((char*)ebx + 0x4c))) {
                                float v;
                                if (g_1687ad0 == 0) v = *(float*)(self + 0x68);
                                else { v = 1.0f; if (*(float*)(self + 0x68) != 1.0f) v = 0.0f; }
                                FUN_00a887b0(*(int*)(*(int*)((char*)esi + 0x19c) + i * 4), v);
                            }
                        }
                    }
                }
            }
        }
    }
}


// ======================================================================
// @ 0x00b74400
unsigned char __stdcall FUN_00b74400(int self)
{
    int* world = (int*)SP_GonzagoModelWorld();
    unsigned char result = 0;
    if (world != 0) (*(void(__thiscall**)(int*))*world)(world);
    int id = *(int*)(self + 0x74);
    if (id == 0 || id == 0x2ebcd6a6) id = *(int*)(self + 0x6c);
    if (world != 0) {
        result = 0;
        if (id != 0 && id != 0x2ebcd6a6 && *(int*)(self + 0x58) != 0 &&
            *(int*)(self + 0x88) != 3 && *(int*)(self + 0x88) != 4 &&
            *(int*)(self + 0x78) == 0) {
            void* a = g_1687ad0 == 0 ? (void*)g_156b424 : (void*)g_156b470;
            int* obj = (int*)(*(int*(__thiscall**)(int*, int, void*, int))(*(int*)world + 0xc))(world, id, a, 0);
            if (obj != 0) {
                *(int*)((char*)obj + 0x58) = *(int*)(self + 0x68);
                *(unsigned int*)((char*)obj + 4) |= 2;
                *(int*)((char*)obj + 0x44) = 0;
                *(int*)((char*)obj + 0x48) = 0;
                int* mm = (int*)SP_ModelManager();
                unsigned int bit = (*(unsigned int(__thiscall**)(int*, int, int))(*(int*)mm + 0x28))(mm, 0x420b420, 0);
                if (bit < 0x40) {
                    *(unsigned int*)((char*)obj + 0x44 + (bit >> 5) * 4) |= 1u << (bit & 0x1f);
                }
                int* d = (int*)FUN_00b73e70(self);
                FUN_00571d40((char*)d + 4);
                FUN_00571d20((char*)d + 0x14);
                result = 1;
                *(int*)((char*)obj + 0x18) = *(int*)((char*)d + 0x10);
                *(short*)((char*)obj + 10) += 1;
                if ((*(unsigned char*)(self + 0x34) & 4) != 0) {
                    *(short*)((char*)obj + 10) += 1;
                    *(int*)((char*)obj + 0x18) = 0x3f800000;
                }
                FUN_00478db0(obj);
                *(unsigned int*)(self + 0x34) |= 1;
                if (*(int*)(self + 0x54) == 0) {
                    if (*(int*)(self + 0x70) != 0) {
                        *(unsigned int*)(*(int*)(self + 0x70) + 4) &= 0xfffffffe;
                        int* w2 = *(int**)(self + 0x70);
                        int* in = (int*)*w2;
                        ((Fn16c)((void**)in)[0x16c / 4])(in, w2, 0);
                    }
                } else {
                    FUN_00a887b0(*(int*)(self + 0x5c), 0.0f);
                }
            }
        }
        (*(void(__thiscall**)(int*))(*(int*)world + 4))(world);
    }
    return result;
}

// ======================================================================
// @ 0x00b74130
void __fastcall FUN_00b74130(int self)
{
    int* s1 = (int*)SP_GetActiveTerrainSphere();
    if (s1 == 0) return;
    int* s2 = (int*)(*(int*(__thiscall**)(int*))(*(int*)s1 + 0xc))(s1);
    if (s2 == 0) return;
    int* s3 = (int*)(*(int*(__thiscall**)(int*))(*(int*)s1 + 0xc))(s1);
    float size = *(float*)((char*)s3 + 0x38) * *(float*)((char*)s3 + 0x54)
               + *(float*)((char*)s3 + 0x34) + 50.0f;

    float x0 = g_1687ad4 - size, x1 = g_1687ad4 + size;
    float y0 = g_1687ad8 - size, y1 = g_1687ad8 + size;
    float z0 = g_1687adc - size, z1 = g_1687adc + size;

    float a0 = x1 - x0, a1 = y1 - y0, a2 = z1 - z0;
    float* p = &a1;
    if (a1 <= a0) p = &a0;
    if (*p <= a2 && a2 != *p) p = &a2;
    float fv = *p;

    HierGrid* g = *(HierGrid**)(self + 0x55a4);
    if (g->mBegin != g->mEnd) g->Shutdown();

    if (x0 <= x1) {
        float t = fv * 2.0f;
        float hi = t * 9.999999f;
        float lo = t * 0.01f;
        int i1 = (int)lo; if ((float)i1 < lo) i1++;
        int b1 = 0; for (int v = i1; v != 0; v >>= 1) b1++;
        int i2 = (int)hi; if ((float)i2 < hi) i2++;
        int b2 = 0; for (int v = i2; v != 0; v >>= 1) b2++;
        int iVar2 = 0;
        if (0 < b1 - 1) iVar2 = b1 - 1;
        int iVar5 = 7;
        if (b2 - 1 < 7) iVar5 = b2 - 1;
        if (iVar5 < iVar2) iVar5 = iVar2;
        Vec3f v; v.x = x0; v.y = y0; v.z = z0;
        g->Init(v, fv, iVar2, iVar5);
    }
}
