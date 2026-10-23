// flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
// Slice s00b74f80: the Simulator::cObstacle notify path (0xb74f80), the
// eastl-style hashtable helpers around it, and the merge-sort / vector
// insertion helpers that share the translation unit.

#include <math.h>

void operator delete(void*);

// ---------------------------------------------------------------- types
struct V3 { float x, y, z; };

typedef char (__cdecl *CmpV3)(V3*, V3*);

// The record's 0x70/0x78 member: a wrapper around an object whose vtable
// carries the 0x16c entry.
struct Inner { void** vptr; };
struct Wrapper { Inner* impl; };
typedef void (__thiscall *Fn16c)(void* self, void* owner, int a);
typedef void (__thiscall *Fn0)(void* self);

struct Stream { void** vptr; };
typedef void* (__thiscall *Fn20)(void* self);
typedef void* (__thiscall *Fn18)(void* self);
typedef void (__thiscall *Fn1c)(void* self);

typedef void (__thiscall *FnSub4)(void* self);

// ---------------------------------------------------------------- globals
extern char g_1687ad0;                 // 0x1687ad0
extern float g_1687ad4;                // 0x1687ad4
extern float g_1687ad8;                // 0x1687ad8
extern float g_1687adc;                // 0x1687adc
extern float g_1485720;                // 0x1485720 (1.0f)
extern float g_13eb960;                // 0x13eb960 (0.01f)
extern char g_16880f0;                 // 0x16880f0 matrix literal
extern char g_13ebb38;                 // 0x13ebb38 allocator file string

// ---------------------------------------------------------------- callees
struct Mat3 { void Assign(const void* m); };                               // 0x41cb40
void* __stdcall FUN_00b3d3b0(unsigned key, int a, int b);                  // 0xb3d3b0
int __fastcall FUN_00b2a690(void* p);                                      // 0xb2a690
void __stdcall FUN_00a887b0(int a, float f);                               // 0xa887b0
void* __cdecl EAAllocate(unsigned size, const char* name, int a, int b,
                         const char* file, int line);                      // 0xf473a0
unsigned __cdecl FUN_005939d0(unsigned a0, unsigned a1, unsigned b0,
                              unsigned b1, char flag);                     // 0x5939d0
void __cdecl FUN_00ae2ed0(void* stream, void* rec);                        // 0xae2ed0
void __cdecl ReadInt32(void* obj, void* out, int n, int flag);             // 0x93a780
void __cdecl FUN_00b74c50(V3* a, V3* b, CmpV3 cmp);                        // 0xb74c50
void __cdecl FUN_00b74cc0(V3* a, V3* b, CmpV3 cmp);                        // 0xb74cc0
void __cdecl FUN_00b737d0(V3* first, int top, int len, int pos, V3 value,
                          CmpV3 cmp);                                      // 0xb737d0
void __cdecl FUN_00b74d60(int* base, int i, int n, int idx, int value,
                          V3 pos);                                          // 0xb74d60
char* __cdecl FUN_00b73780(char* first, char* last, char* dst);            // 0xb73780
char* __cdecl FUN_00b739f0(char* first, char* last, char* dst);            // 0xb739f0
void __cdecl FUN_00b73890(void** out, char* first, char* last, char* dst,
                          char* at);                                       // 0xb73890
void __cdecl FUN_00b738e0(char* dst, unsigned n, const void* src);         // 0xb738e0
void __cdecl FUN_00cc8b50(void* first, void* last, void* dst);             // 0xcc8b50
void __cdecl FUN_00edba80(void* first, void* last, void* dst);             // 0xedba80
void __cdecl FUN_00898580(void* first, void* last, const void* value);     // 0x898580
void __cdecl FUN_00921440(int* out, int a, int b, int c);                  // 0x921440

// ---------------------------------------------------------------- classes
struct Hashtable2 {
    int* Find(int* out, unsigned* key);                                    // 0xb746a0
};

struct Tbl {
    void Reset(int a, int b);                                              // 0xb73070
    int Insert3(int* out, const void* in, int flag);                        // 0xb748e0
};

struct Rec {
    void FUN_00b73f30(float f, int iv);                                    // 0xb73f30
};

struct Mgr {
    void Notify(int rec, float dt, int unused);
    void FUN_00b74590(int rec);                                            // 0xb74590
    unsigned char FUN_00b74400(int rec);                                   // 0xb74400
};

struct T51b0 {
    bool Query(int* out, unsigned key0, unsigned key1, unsigned cmp, char flag);
};

struct Pool {
    void FUN_00921440(int* out, int a, int b, int c);                      // 0x921440
};

struct T5240 {
    unsigned* Insert(unsigned* out, unsigned* key, int flag);
    int* AllocNode3(unsigned* key);                                        // 0xb74b60
    void DoFreeNodes(int p);                                               // 0xc76610
};

struct T5820 {
    T5820* Init();
};

struct T5890 {
    int* GetOrInsert(unsigned* key);
    int* FindKey(int* out, int* key);                                      // 0xb74860
    int Insert3(int* out, const void* in, int flag);                        // 0xb748e0
};

struct T5910 {
    int* Unlink(int* out, int* node, int* bucket);
};

struct T59b0 {
    void FreeTable(int* buckets, unsigned n);
};

struct E18 { float f0, f1, f2, f3; char c; int i; };

struct T5a30 {
    void Insert(E18* pos, E18* value);
};

struct E16 { float x, y, z; char c; char pad[3]; };

struct T5dc0 {
    void Insert(char* at, unsigned n, const void* value);
};

// ======================================================================
// 0xb74f80  manager notify
// ======================================================================
// @ 0x00b74f80 Notify
void Mgr::Notify(int rec_, float dt, int unused)
{
    char* rec = (char*)rec_;
    if (rec == 0)
        return;

    char bl = (dt != g_1485720) ? 1 : 0;

    unsigned key;
    switch (*(int*)(rec + 0x88)) {
    case 0:  key = 0x3a8be428; break;
    case 1:  key = 0x29c388a;  break;
    case 2:  key = 0x6d60a1cc; break;
    default: key = 0;          break;
    }

    int iv = FUN_00b2a690(FUN_00b3d3b0(key, *(int*)(rec + 0x50),
                                       *(int*)(rec + 0x5c)));
    char dl = g_1687ad0;

    if (*(int*)(rec + 0x78) != 0) {
        if (*(float*)(rec + 0x68) == g_1485720 || (dl == 0 && iv != 0)) {
            FUN_00b74590(rec_);
            float saved = *(float*)(rec + 0x68);
            if (iv == 0) {
                *(unsigned*)(rec + 0x34) &= ~1u;
                if (*(int*)(rec + 0x54) != 0) {
                    FUN_00a887b0(*(int*)(rec + 0x5c), 1.0f);
                } else {
                    Wrapper* pw = *(Wrapper**)(rec + 0x70);
                    if (pw != 0) {
                        *(unsigned*)((char*)pw + 4) |= 1u;
                        ((Fn16c)((Inner*)pw->impl)->vptr[0x16c / 4])
                            (pw->impl, pw, 1);
                    }
                }
            }
            ((Rec*)rec)->FUN_00b73f30(saved, iv);
        }
    } else if (bl) {
        if (dl != 0 || iv == 0) {
            int type = *(int*)(rec + 0x88);
            if (type == 4 || type == 3) {
                *(unsigned*)(rec + 0x34) |= 1u;
                if (*(int*)(rec + 0x54) != 0) {
                    FUN_00a887b0(*(int*)(rec + 0x5c), 0.0f);
                } else {
                    Wrapper* pw = *(Wrapper**)(rec + 0x70);
                    if (pw != 0) {
                        *(unsigned*)((char*)pw + 4) &= ~1u;
                        ((Fn16c)((Inner*)pw->impl)->vptr[0x16c / 4])
                            (pw->impl, pw, 0);
                    }
                }
            } else if (FUN_00b74400(rec_) == 0) {
                *(unsigned*)(rec + 0x34) &= ~1u;
                if (*(int*)(rec + 0x54) != 0) {
                    FUN_00a887b0(*(int*)(rec + 0x5c), 1.0f);
                } else {
                    Wrapper* pw = *(Wrapper**)(rec + 0x70);
                    if (pw != 0) {
                        *(unsigned*)((char*)pw + 4) |= 1u;
                        ((Fn16c)((Inner*)pw->impl)->vptr[0x16c / 4])
                            (pw->impl, pw, 1);
                    }
                }
            }
            ((Rec*)rec)->FUN_00b73f30(*(float*)(rec + 0x68), iv);
        }
    }

    if (g_1687ad0 == 0) {
        dt = (dt - *(float*)(rec + 0x68))
             * *(float*)((char*)this + 0x5488)
             + *(float*)(rec + 0x68);
        if (fabsf(dt - g_1485720) < g_13eb960)
            dt = g_1485720;
    }

    if (*(float*)(rec + 0x68) != dt)
        ((Rec*)rec)->FUN_00b73f30(dt, iv);
}

// ======================================================================
// 0xb751b0  query hashtable entry
// ======================================================================
// @ 0x00b751b0 Query
bool T51b0::Query(int* out, unsigned key0, unsigned key1, unsigned cmp,
                  char flag)
{
    Hashtable2* ht = flag != 0
        ? (Hashtable2*)((char*)this + 0x38)
        : (Hashtable2*)((char*)this + 0x2094);

    int local[4];
    int* p = ht->Find(local, &key0);
    out[0] = p[0];
    out[1] = p[1];
    out[2] = p[2];
    out[3] = p[3];

    unsigned r = FUN_005939d0((unsigned)out[0], (unsigned)out[1],
                              (unsigned)out[2], (unsigned)out[3], flag);
    return r != 0 && r == cmp;
}

// ======================================================================
// 0xb75240  insert into the pooled hashtable
// ======================================================================
// @ 0x00b75240 Insert
unsigned* T5240::Insert(unsigned* out, unsigned* key, int flag)
{
    int res[2];
    ((Pool*)((char*)this + 0x10))->FUN_00921440(res, *(int*)((char*)this + 8),
                                                *(int*)((char*)this + 0xc), 1);
    if (*(char*)res != 0)
        ((T5240*)this)->DoFreeNodes(res[1]);

    unsigned idx = key[0] % *(unsigned*)((char*)this + 8);
    int* node = ((T5240*)this)->AllocNode3(key);
    int** mBegin = *(int***)((char*)this + 4);
    int* head = mBegin[idx];

    if (head != 0) {
        unsigned k0 = key[0];
        unsigned k1 = key[1];
        int* cur = head;
        do {
            if ((unsigned)cur[0] == k0 && (unsigned)cur[1] == k1) {
                node[4] = cur[4];
                cur[4] = (int)node;
                goto done;
            }
            cur = (int*)cur[4];
        } while (cur != 0);
    }

    node[4] = (int)head;
    mBegin[idx] = node;

done:
    ++*(unsigned*)((char*)this + 0xc);
    out[0] = (unsigned)node;
    out[1] = (unsigned)((char*)mBegin + idx * 4);
    return out;
}

// ======================================================================
// 0xb753b0  deserialize the obstacle graph
// ======================================================================
// @ 0x00b753b0 f_00b753b0
void f_00b753b0(void* stream, Tbl* table)
{
    table->Reset(*(int*)((char*)table + 4), *(int*)((char*)table + 8));
    *(int*)((char*)table + 0xc) = 0;

    void* obj = ((Fn20)((Stream*)stream)->vptr[0x20 / 4])(stream);
    void* ser = ((Fn18)(*(void***)obj)[0x18 / 4])(obj);

    int count = 0;
    ReadInt32(ser, &count, 1, 0);

    for (unsigned i = 0; i < (unsigned)count; ++i) {
        V3 b; b.x = 0; b.y = 0; b.z = 0;
        V3 a; a.x = 0; a.y = 0; a.z = 0;
        FUN_00ae2ed0(stream, &b);
        ((Fn1c)((Stream*)stream)->vptr[0x1c / 4])(stream);
        FUN_00ae2ed0(stream, &a);
        ((Fn1c)((Stream*)stream)->vptr[0x1c / 4])(stream);

        V3 in[2];
        in[0] = b;
        in[1] = a;

        int out[3];
        table->Insert3(out, in, 0);
        if (*(char*)(out + 2) == 0) {
            int* node = (int*)out[0];
            *(float*)((char*)node + 0xc) = a.x;
            *(float*)((char*)node + 0x10) = a.y;
            *(float*)((char*)node + 0x14) = a.z;
        }
    }

    ((Fn1c)((Stream*)stream)->vptr[0x1c / 4])(stream);
}

// ======================================================================
// 0xb754d0  insertion sort over a range
// ======================================================================
// @ 0x00b754d0 f_00b754d0
void f_00b754d0(V3* begin, V3* last, V3* end, CmpV3 cmp)
{
    FUN_00b74c50(begin, last, cmp);
    for (V3* p = last; p < end; ++p) {
        if (cmp(p, begin)) {
            V3 v = *p;
            *p = *begin;
            FUN_00b737d0(begin, 0, (int)(last - begin), 0, v, cmp);
        }
    }
    FUN_00b74cc0(begin, last, cmp);
}

// ======================================================================
// 0xb75570  merge two sorted runs
// ======================================================================
// @ 0x00b75570 f_00b75570
void f_00b75570(V3* p1, V3* end1, V3* p2, V3* end2, V3* dst, CmpV3 cmp)
{
    while (p1 != end1 && p2 != end2) {
        if (cmp(p2, p1)) {
            *dst = *p2;
            ++p2;
        } else {
            *dst = *p1;
            ++p1;
        }
        ++dst;
    }
    while (p1 != end1) {
        *dst = *p1;
        ++p1;
        ++dst;
    }
    while (p2 != end2) {
        *dst = *p2;
        ++p2;
        ++dst;
    }
}

// ======================================================================
// 0xb75620  quickselect on pointers, distance to a pivot
// ======================================================================
// @ 0x00b75620 f_00b75620
void f_00b75620(int** first, int** last, int* pivot, float x, float y, float z)
{
    for (;;) {
        int* v;
        for (;;) {
            v = *first;
            float dv = (y - *(float*)((char*)v + 0x3c))
                     * (y - *(float*)((char*)v + 0x3c))
                     + (z - *(float*)((char*)v + 0x40))
                     * (z - *(float*)((char*)v + 0x40))
                     + (x - *(float*)((char*)v + 0x38))
                     * (x - *(float*)((char*)v + 0x38));
            float dp = (y - *(float*)((char*)pivot + 0x3c))
                     * (y - *(float*)((char*)pivot + 0x3c))
                     + (z - *(float*)((char*)pivot + 0x40))
                     * (z - *(float*)((char*)pivot + 0x40))
                     + (x - *(float*)((char*)pivot + 0x38))
                     * (x - *(float*)((char*)pivot + 0x38));
            if (dp <= dv)
                break;
            ++first;
        }

        float dp = (y - *(float*)((char*)pivot + 0x3c))
                 * (y - *(float*)((char*)pivot + 0x3c))
                 + (z - *(float*)((char*)pivot + 0x40))
                 * (z - *(float*)((char*)pivot + 0x40))
                 + (x - *(float*)((char*)pivot + 0x38))
                 * (x - *(float*)((char*)pivot + 0x38));
        int* w;
        float dw;
        do {
            w = *--last;
            dw = (y - *(float*)((char*)w + 0x3c))
               * (y - *(float*)((char*)w + 0x3c))
               + (z - *(float*)((char*)w + 0x40))
               * (z - *(float*)((char*)w + 0x40))
               + (x - *(float*)((char*)w + 0x38))
               * (x - *(float*)((char*)w + 0x38));
        } while (dw > dp);

        if (first >= last)
            break;
        *first = *last;
        *last = v;
        ++first;
    }
}

// ======================================================================
// 0xb75750  heap make
// ======================================================================
// @ 0x00b75750 f_00b75750
void f_00b75750(int* begin, int* end, V3 pos)
{
    int n = (int)(end - begin);
    if (n < 2)
        return;
    int i = ((n - 2) >> 1) + 1;
    do {
        --i;
        FUN_00b74d60(begin, i, n, i, begin[i], pos);
    } while (i != 0);
}

// ======================================================================
// 0xb757b0  heap sort
// ======================================================================
// @ 0x00b757b0 f_00b757b0
void f_00b757b0(int* begin, int* end, V3 pos)
{
    int n = (int)(end - begin);
    if (n <= 1)
        return;
    int* p = end - 1;
    do {
        int v = *p;
        *p = *begin;
        FUN_00b74d60(begin, 0, n - 1, 0, v, pos);
        --p;
        n = (int)((char*)p - (char*)begin) / 4 + 1;
    } while (n > 1);
}

// ======================================================================
// 0xb75820  constructor
// ======================================================================
// @ 0x00b75820 Init
T5820* T5820::Init()
{
    *(short*)((char*)this + 0) = 0;
    *(short*)((char*)this + 2) = 0;
    *(float*)((char*)this + 4) = g_1687ad4;
    *(float*)((char*)this + 8) = g_1687ad8;
    *(float*)((char*)this + 0xc) = g_1687adc;
    *(float*)((char*)this + 0x10) = g_1485720;
    ((Mat3*)((char*)this + 0x14))->Assign(&g_16880f0);

    char* p = (char*)this + 0x64;
    *(char**)((char*)this + 0x4c) = p;
    *(char**)((char*)this + 0x50) = p;
    *(char**)((char*)this + 0x54) = p + 0xc00;
    *(int*)((char*)this + 0x60) = 0;
    return this;
}

// ======================================================================
// 0xb75890  find or insert a key
// ======================================================================
// @ 0x00b75890 GetOrInsert
int* T5890::GetOrInsert(unsigned* key)
{
    int local[4];
    ((T5890*)this)->FindKey(local, (int*)key);
    if (local[0] == *(int*)(*(int*)((char*)this + 4)
                            + *(int*)((char*)this + 8) * 4)) {
        int in[6];
        in[0] = (int)key[0];
        in[1] = (int)key[1];
        in[2] = (int)key[2];
        in[3] = 0;
        in[4] = 0;
        in[5] = 0;
        ((T5890*)this)->Insert3(local, in, 0);
    }
    return (int*)(local[0] + 0xc);
}

// ======================================================================
// 0xb75910  unlink a node from its bucket
// ======================================================================
// @ 0x00b75910 Unlink
int* T5910::Unlink(int* out, int* node, int* bucket)
{
    out[1] = (int)bucket;
    out[0] = node[4];
    while (out[0] == 0) {
        out[1] += 4;
        out[0] = *(int*)out[1];
    }

    int* cur = *(int**)bucket;
    if (cur == node) {
        *(int**)bucket = (int*)cur[4];
    } else {
        int* a = (int*)cur[4];
        while (a != node) {
            cur = a;
            a = (int*)a[4];
        }
        cur[4] = a[4];
    }

    if (node[2] != 0) {
        void** vt = *(void***)node[2];
        ((FnSub4)vt[1])((void*)node[2]);
    }

    if (node != *(int**)((char*)this + 0x30)) {
        int* lo = *(int**)((char*)this + 0x24);
        int* hi = *(int**)((char*)this + 0x28);
        if (node >= lo && node < hi) {
            *node = *(int*)((char*)this + 0x1c);
            *(int**)((char*)this + 0x1c) = node;
            --*(int*)((char*)this + 0xc);
            return out;
        }
        operator delete(node);
    }
    --*(int*)((char*)this + 0xc);
    return out;
}

// ======================================================================
// 0xb759b0  free every node in a bucket table
// ======================================================================
// @ 0x00b759b0 FreeTable
void T59b0::FreeTable(int* buckets, unsigned n)
{
    for (unsigned i = 0; i < n; ++i) {
        int* p = *(int**)((char*)buckets + i * 4);
        while (p != 0) {
            int* node = p;
            p = (int*)node[4];
            int* sub = (int*)node[2];
            if (sub != 0) {
                void** vt = *(void***)sub;
                ((FnSub4)vt[1])(sub);
            }
            if (node != *(int**)((char*)this + 0x30)) {
                int* lo = *(int**)((char*)this + 0x24);
                int* hi = *(int**)((char*)this + 0x28);
                if (node >= lo && node < hi) {
                    *node = *(int*)((char*)this + 0x1c);
                    *(int**)((char*)this + 0x1c) = node;
                } else {
                    operator delete(node);
                }
            }
        }
        *(int**)((char*)buckets + i * 4) = 0;
    }
}

// ======================================================================
// 0xb75a30  vector insert (0x18-byte elements)
// ======================================================================
// @ 0x00b75a30 Insert
void T5a30::Insert(E18* pos, E18* value)
{
    E18* mEnd = *(E18**)((char*)this + 4);
    E18* mCapEnd = *(E18**)((char*)this + 8);
    E18* mBegin = *(E18**)((char*)this + 0);

    if (mEnd != mCapEnd) {
        if (value >= pos && value < mEnd)
            ++value;
        if (mEnd != 0)
            *mEnd = mEnd[-1];
        FUN_00cc8b50(pos, mEnd - 1, mEnd);
        *pos = *value;
        *(E18**)((char*)this + 4) = mEnd + 1;
        return;
    }

    unsigned n = (unsigned)((char*)mEnd - (char*)mBegin) / 0x18;
    unsigned cap2 = n != 0 ? n * 2 : 1;
    if (n == 0)
        cap2 = 1;
    unsigned size = cap2 != 0 ? cap2 : 0;

    E18* nb = size != 0
        ? (E18*)EAAllocate(size * 0x18, "Simulator", 0, 0, &g_13ebb38, 0xd1)
        : 0;

    E18* mid = (E18*)FUN_00b73780((char*)mBegin, (char*)pos, (char*)nb);
    if (mid != 0)
        *mid = *value;
    E18* dst = (E18*)FUN_00b73780((char*)pos, (char*)mEnd,
                                  (char*)(mid != 0 ? mid + 1 : mid));
    if (mBegin != 0 && *(int*)((char*)mBegin - 4) != 0)
        operator delete(mBegin);

    *(E18**)((char*)this + 4) = dst;
    *(E18**)((char*)this + 0) = nb;
    *(E18**)((char*)this + 8) = (E18*)((char*)nb + size * 0x18);
}

// ======================================================================
// 0xb75b80  free the 0xc70-chained nodes
// ======================================================================
// @ 0x00b75b80 f_00b75b80
void __stdcall f_00b75b80(int** buckets, unsigned n)
{
    for (unsigned i = 0; i < n; ++i) {
        int* p = buckets[i];
        while (p != 0) {
            int* node = p;
            p = *(int**)((char*)node + 0xc70);
            int* sub = *(int**)((char*)node + 0x58);
            if (sub != 0 && *(int*)((char*)sub - 4) != 0)
                operator delete(sub);
            operator delete(node);
        }
        buckets[i] = 0;
    }
}

// ======================================================================
// 0xb75bf0  free the 0xc68-chained nodes
// ======================================================================
// @ 0x00b75bf0 f_00b75bf0
void __stdcall f_00b75bf0(int** buckets, unsigned n)
{
    for (unsigned i = 0; i < n; ++i) {
        int* p = buckets[i];
        while (p != 0) {
            int* node = p;
            p = *(int**)((char*)node + 0xc68);
            int* sub = *(int**)((char*)node + 0x50);
            if (sub != 0 && *(int*)((char*)sub - 4) != 0)
                operator delete(sub);
            operator delete(node);
        }
        buckets[i] = 0;
    }
}

// ======================================================================
// 0xb75c60  recursive merge sort
// ======================================================================
// @ 0x00b75c60 f_00b75c60
void f_00b75c60(V3* a, V3* b, V3* buf, CmpV3 cmp)
{
    int n = (int)(b - a);
    if (n <= 1)
        return;

    int mid = n / 2;
    V3* p1 = a + mid;

    if (mid > 1) {
        V3* q = a + mid / 2;
        f_00b75c60(a, q, buf, cmp);
        f_00b75c60(q, p1, buf + mid / 2, cmp);
        f_00b75570(a, q, q, a + mid, buf, cmp);
    } else {
        *buf = *a;
    }

    if (n - mid > 1) {
        V3* r = a + (mid + n) / 2;
        f_00b75c60(p1, r, buf + mid, cmp);
        f_00b75c60(r, b, buf + (mid + n) / 2, cmp);
        f_00b75570(p1, r, r, b, buf + mid, cmp);
    } else {
        buf[mid] = *p1;
    }

    f_00b75570(buf, buf + mid, buf + mid, buf + n, a, cmp);
}

// ======================================================================
// 0xb75dc0  vector insert (0x10-byte elements)
// ======================================================================
// @ 0x00b75dc0 Insert
void T5dc0::Insert(char* at, unsigned n, const void* value)
{
    char* mEnd = *(char**)((char*)this + 4);
    char* mCapEnd = *(char**)((char*)this + 8);
    char* mBegin = *(char**)((char*)this + 0);

    unsigned avail = (unsigned)(mCapEnd - mEnd) >> 4;
    if (n > avail) {
        unsigned n0 = (unsigned)(mEnd - mBegin) >> 4;
        unsigned cap2 = n0 != 0 ? n0 * 2 : 1;
        unsigned size = (n0 + n < cap2) ? cap2 : (n0 + n);
        char* nb = size != 0
            ? (char*)EAAllocate(size * 0x10, "Simulator", 0, 0, &g_13ebb38, 0xd1)
            : 0;
        char* mid = FUN_00b739f0(mBegin, at, nb);
        FUN_00b738e0(mid, n, value);
        char* dst = FUN_00b739f0(at, mEnd, mid + n * 0x10);
        if (mBegin != 0 && *(int*)(mBegin - 4) != 0)
            operator delete(mBegin);
        *(char**)((char*)this + 4) = dst;
        *(char**)((char*)this + 0) = nb;
        *(char**)((char*)this + 8) = nb + size * 0x10;
        return;
    }

    if (n == 0)
        return;

    E16 local;
    local.x = *(float*)value;
    local.y = *(float*)((char*)value + 4);
    local.z = *(float*)((char*)value + 8);
    local.c = *(char*)((char*)value + 0xc);

    unsigned elemsAfter = (unsigned)(mEnd - at) >> 4;

    if (n < elemsAfter) {
        char* dst = mEnd - n * 0x10;
        FUN_00b73890((void**)&value, dst, mEnd, mEnd, at);
        *(char**)((char*)this + 4) = mEnd + n * 0x10;
        FUN_00edba80(at, dst, mEnd + n * 0x10);
        FUN_00898580(at, at + n * 0x10, &local);
    } else {
        char* oldEnd = mEnd;
        FUN_00b738e0(mEnd, n - elemsAfter, &local);
        *(char**)((char*)this + 4) = mEnd + (n - elemsAfter) * 0x10;
        FUN_00b73890((void**)&at, at, oldEnd, mEnd + (n - elemsAfter) * 0x10,
                      at);
        *(char**)((char*)this + 4) = mEnd
            + (n - elemsAfter) * 0x10 + elemsAfter * 0x10;
        FUN_00898580(at, oldEnd, &local);
    }
}
