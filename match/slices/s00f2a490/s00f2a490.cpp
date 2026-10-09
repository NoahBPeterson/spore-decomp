// Building-data container helpers (eastl vector< cBuildingData >, stride 0x38)
// plus the tutorial command-list builder.  /O2.
//
// Flags: /O2 /MD /Gy /TP

typedef unsigned int   uint32_t;
typedef unsigned int   uint;
typedef unsigned char  uint8_t;

struct Sub { void assign(Sub* other); };          // 0x00473500
struct Elem34 { float f; int d[12]; };            // 0x34
struct BuildData { char d[0x38]; };               // 0x38
struct WideVec { char d[0x20]; };                 // 0x20

// ---------------------------------------------------------------------------
// 0x00f2a490  copy_backward of 0x34-byte elements
// ---------------------------------------------------------------------------
// @ 0x00f2a490
Elem34* FUN_00f2a490(Elem34* first, Elem34* last, Elem34* out)
{
    if (last != first) {
        do {
            --last;
            --out;
            *out = *last;
        } while (last != first);
    }
    return out;
}

// ---------------------------------------------------------------------------
// 0x00f2a510  property lookup
// ---------------------------------------------------------------------------
extern void* EA_ConvertToString16(void*, int, int);   // 0x0093c5a0
extern void  FUN_00f28b30_();                          // unused
extern void  eastl_wstring_ctor(void*);               // 0x0056e2d0
extern void  operator_delete(void*);                  // 0x00f47380
extern int   FUN_005954f0(int*, void*, void*, void*); // 0x005954f0
extern int   FUN_00ae5530(int*, void*, int, void*);   // 0x00ae5530

// @ 0x00f2a510
uint8_t FUN_00f2a510(int* a, int b, int* c)
{
    wchar_t buf[10];
    if (c == 0)
        return 1;
    if ((c[4] & c[5]) == -1 && *c == 0)
        return 1;
    wchar_t* p = (wchar_t*)buf;
    bool empty;
    if (b == 0) {
        buf[0] = 0;
        p = buf;
        empty = true;
    } else {
        p = (wchar_t*)EA_ConvertToString16(buf, b, -1);
        empty = false;
    }
    eastl_wstring_ctor(p);
    (void)empty;
    char ok = (*(int(__thiscall**)(int*, wchar_t*))(*a))(a, p);
    bool r;
    if ((c[4] & c[5]) == -1)
        r = ok ? (FUN_00ae5530(a, 0, b, 0), true) : false;
    else
        r = ok ? (FUN_005954f0(a, 0, c + 4, 0) != 0) : false;
    if (!r)
        return 0;
    return (*(int(__thiscall**)(int*, wchar_t*))(*(int*)a + 4))(a, p) != 0;
}

// ---------------------------------------------------------------------------
// 0x00f2a6a0  build tutorial command list
// ---------------------------------------------------------------------------
typedef int(__thiscall* PushFn)(void*, int*);
extern void FUN_00c06c30();        // 0x00c06c30
inline void push8(void* vec, int* rec)
{
    uint32_t* p = (uint32_t*)vec;
    if (p[1] < p[2]) {
        uint32_t* q = (uint32_t*)p[1];
        p[1] = (uint32_t)(q + 8);
        if (q)
            for (int i = 0; i < 8; ++i)
                q[i] = rec[i];
    } else {
        FUN_00c06c30();
    }
}
extern void FUN_00c06c30();        // 0x00c06c30
extern int  FUN_00ec6e70(int);     // 0x00ec6e70
extern int  FUN_00c072b0(int*);    // 0x00c072b0
extern int  ScenarioTutorials_GetActive();

// @ 0x00f2a6a0
void FUN_00f2a6a0(char* self)
{
    int rec[8];
    int v = *(int*)(self + 0x4ac);
    if (v == 1 || v == 2 || v == 3) {
        rec[0] = 1;
        rec[1] = -1;
        rec[2] = -1;
        rec[3] = (v == 1) ? 5 : 0;
        if (*(int*)(self + 0x4ac) == 4)
            rec[3] = 8;
        int kind = *(int*)(self + 0x4a8);
        if (kind != 1 && kind != 0) {
            for (unsigned i = 1; i < 5; ++i) {
                if (i != (unsigned)(kind - 1) && FUN_00ec6e70(i)) {
                    rec[4] = 1;
                    rec[5] = i;
                    FUN_00c072b0(rec);
                }
            }
            rec[4] = 0;
        } else {
            rec[4] = 0;
            rec[5] = -1;
            FUN_00c072b0(rec);
        }
    }
    rec[0] = 0; rec[1] = -1; rec[2] = -1;
    if (*(int*)(self + 0x4ac) == 2 || *(int*)(self + 0x4ac) == 1) {
        rec[3] = 0xb; rec[4] = -1; rec[5] = -1;
        push8(self + 0x4d0, rec);
    }
    rec[3] = 0xc; rec[4] = 0; rec[5] = -1;
    push8(self + 0x4d0, rec);
    if (*(int*)(self + 0x4b0) == 2) {
        rec[4] = -1; rec[5] = -1;
        rec[3] = 3; rec[2] = -1; rec[1] = -1; rec[0] = 0;
        push8(self + 0x4d0, rec);
    } else if (*(int*)(self + 0x4b0) == 3) {
        rec[4] = 2; rec[5] = *(int*)(self + 0x4bc);
        rec[3] = 3; rec[2] = -1; rec[1] = -1; rec[0] = 0;
        push8(self + 0x4d0, rec);
    }
    if (*(int*)(self + 0x4b4) == 2) {
        rec[3] = 4; rec[4] = 0; rec[5] = -1; rec[6] = 0; rec[7] = -1;
    } else if (*(int*)(self + 0x4b0) == 3) {
        rec[3] = 3; rec[4] = 2; rec[5] = *(int*)(self + 0x4bc);
        rec[6] = 2; rec[7] = *(int*)(self + 0x4c0);
    } else {
        goto tail;
    }
    rec[2] = -1; rec[1] = -1; rec[0] = 0;
    push8(self + 0x4d0, rec);
tail:
    rec[4] = -1; rec[5] = -1; rec[6] = -1; rec[7] = -1;
    rec[0] = 0; rec[1] = -1; rec[2] = -1;
    switch (*(int*)(self + 0x4b8)) {
    case 1:  rec[3] = 1; break;
    case 4:  rec[3] = 2; break;
    case 5:  rec[3] = 7; rec[4] = 2; rec[5] = *(int*)(self + 0x4c4); break;
    case 6:  rec[3] = 10; break;
    default: rec[3] = 6; rec[4] = -1; rec[5] = -1; break;
    }
    push8(self + 0x4d0, rec);
}

// ---------------------------------------------------------------------------
// 0x00f2aac0
// ---------------------------------------------------------------------------
extern int FUN_00f08850(int, int);

// @ 0x00f2aac0
void FUN_00f2aac0(char* self)
{
    int rec[8];
    rec[0] = 0; rec[1] = -1; rec[2] = -1;
    if (*(int*)(self + 0x4ac) == 4) {
        rec[3] = 8; rec[4] = 0; rec[5] = -1;
    } else {
        rec[3] = 0xc; rec[4] = 0; rec[5] = -1;
    }
    push8(self + 0x4d0, rec);
}

// ---------------------------------------------------------------------------
// 0x00f2ac30
// ---------------------------------------------------------------------------
// @ 0x00f2ac30
int FUN_00f2ac30(void* self, int* a, int b, int c)
{
    (void)self; (void)a; (void)b; (void)c;
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00f2ada0  resize vector<BuildData> (stride 0x38)
// ---------------------------------------------------------------------------
extern BuildData* FUN_00f28dd0();   // eastl vector erase
extern void FUN_00f28e40();         // 0x00f28e40

struct Vec38 { BuildData* mpBegin; BuildData* mpEnd; BuildData* mpCapacity; void resize(uint32_t n); };

// @ 0x00f2ada0
void Vec38::resize(uint32_t n)
{
    uint32_t have = (uint32_t)(mpEnd - mpBegin) / 0x38;
    if (have < n) {
        BuildData tmp;
        for (uint32_t i = 0; i < sizeof(BuildData); ++i)
            ((char*)&tmp)[i] = 0;
        *(int*)((char*)&tmp + 0x10) = -1;
        *(int*)((char*)&tmp + 0x14) = -1;
        *(int*)((char*)&tmp + 0x18) = -1;
        *(int*)((char*)&tmp + 0x2c) = -1;
        *(int*)((char*)&tmp + 0x30) = -1;
        FUN_00f28e40();
    } else {
        FUN_00f28dd0();
    }
}

// ---------------------------------------------------------------------------
// 0x00f2ae60  load building-data list
// ---------------------------------------------------------------------------
extern void EA_IO_ReadInt32(void*, int*, int, int);  // 0x0093a780
extern void FUN_00f28280(int);                       // 0x00f28280
extern void FUN_00f257f0(void*);                     // 0x00f257f0
extern void FUN_00f29030(void*, void*);              // 0x00f29030

// @ 0x00f2ae60
void FUN_00f2ae60(char* self, int* vec)
{
    FUN_00f28dd0();
    int n = 0;
    int* io = (int*)(*(int(__thiscall**)(char*))(*(int*)self + 0x20))(self);
    void* stream = (void*)(*(int(__thiscall**)(int*))(*(int*)io + 0x18))(io);
    EA_IO_ReadInt32(stream, &n, 1, 0);
    FUN_00f28280(n);
    if (n) {
        for (int i = 0; i < n; ++i) {
            char rec[0x38];
            for (int k = 0; k < 0x38; ++k) rec[k] = 0;
            *(int*)(rec + 0x10) = -1;
            *(int*)(rec + 0x14) = -1;
            *(int*)(rec + 0x18) = -1;
            *(int*)(rec + 0x2c) = -1;
            *(int*)(rec + 0x30) = -1;
            FUN_00f257f0(self);
            BuildData* p = (BuildData*)vec[1];
            if (p < (BuildData*)vec[2]) {
                vec[1] = (int)(p + 1);
                if (p)
                    for (int k = 0; k < 0x38; ++k) ((char*)p)[k] = rec[k];
            } else {
                FUN_00f29030(p, rec);
            }
        }
    }
    (*(int(__thiscall**)(char*))(*(int*)self + 0x1c))(self);
}

// ---------------------------------------------------------------------------
// 0x00f2af60  push-if-match
// ---------------------------------------------------------------------------
extern bool FUN_00f27990(int, int);      // 0x00f27990
extern void FUN_00b96600();              // 0x00b96600

// @ 0x00f2af60
void FUN_00f2af60(int vec, int key, int* count, int arg4, char arg5)
{
    if ((*count <= 0 || arg5 == 0) && FUN_00f27990(key, arg4)) {
        if (vec) {
            int* end = *(int**)(vec + 4);
            if (end < *(int**)(vec + 8)) {
                *(int**)(vec + 4) = end + 1;
                if (end) {
                    *end = key;
                    ++*count;
                    return;
                }
            } else {
                int v = key;
                FUN_00b96600();
                (void)v;
            }
        }
        ++*count;
    }
}

// ---------------------------------------------------------------------------
// 0x00f2afc0  ordered insert
// ---------------------------------------------------------------------------
extern int* FUN_00f27fc0(int, int, int*, int);   // 0x00f27fc0
extern void FUN_00f2a3a0(void*, void*);           // 0x00f2a3a0

struct TreeLike {
    int* mpBegin;   // +0
    int* mpEnd;     // +4
    char pad[0xc];
    uint8_t mFlag;  // +0x14
    void insert(uint* key, uint* val);
};

// @ 0x00f2afc0
void TreeLike::insert(uint* key, uint* val)
{
    int* end = mpEnd;
    int* pos;
    if (key != (uint*)end) {
        bool less = *val < *key;
        if (*val == *key && (less = val[2] < key[2], val[2] == key[2]))
            less = val[1] < key[1];
        if (less) {
            pos = (int*)FUN_00f27fc0((int)mpBegin, (int)end, (int*)val, mFlag);
            goto check;
        }
    }
    pos = (int*)FUN_00f27fc0((int)key, (int)end, (int*)val, mFlag);
check:
    if (pos != end) {
        bool less = *val < *(uint*)pos;
        if (*val == *(uint*)pos && (less = val[2] < ((uint*)pos)[2], val[2] == ((uint*)pos)[2]))
            less = val[1] < ((uint*)pos)[1];
        if (!less)
            return;
    }
    FUN_00f2a3a0(pos, val);
}

// ---------------------------------------------------------------------------
// 0x00f2b040  collect matching building data
// ---------------------------------------------------------------------------
extern void FUN_00d01790(int);   // 0x00d01790
extern int  FUN_00f259b0();       // 0x00f259b0

struct BigObj {
    char pad0[0x130];
    int  mKey130;            // +0x130
    char pad1[0x48];
    BuildData* begin178;     // +0x178
    BuildData* end17c;       // +0x17c
    char pad2[0x2674];
    char* begin2bf4;         // +0x2bf4
    char* end2bf8;           // +0x2bf8
    int collect(int vec, int key, int arg4);
};

// @ 0x00f2b040
int BigObj::collect(int vec, int key, int arg4)
{
    int count = 0;
    if (vec)
        FUN_00d01790((int)((end2bf8 - begin2bf4) / 0x27e8) * 3 +
                     (int)((char*)end17c - (char*)begin178) / 0x38 + 1);
    FUN_00f2af60(vec, (int)&mKey130, &count, key, (char)arg4);
    int* p = (int*)begin178;
    while (p != (int*)end17c) {
        if ((count < 1 || (char)arg4 == 0) && FUN_00f27990((int)p, key)) {
            if (vec) {
                int* e = *(int**)(vec + 4);
                if (e < *(int**)(vec + 8)) {
                    *(int**)(vec + 4) = e + 1;
                    if (e) *e = (int)p;
                } else {
                    FUN_00b96600();
                }
            }
            ++count;
        }
        p = (int*)((char*)p + 0x38);
    }
    char* b = begin2bf4;
    if (b != end2bf8) {
        char* e = b + 0x58;
        do {
            if (count < 1 || (char)arg4 == 0) {
                if (FUN_00f27990((int)(e - 0x50), key)) {
                    if (vec) {
                        int* q = *(int**)(vec + 4);
                        if (q < *(int**)(vec + 8)) { *(int**)(vec + 4) = q + 1; if (q) *q = (int)(e - 0x50); }
                        else FUN_00b96600();
                    }
                    ++count;
                }
            }
            if (count < 1 || (char)arg4 == 0) {
                if (FUN_00f27990((int)(e - 0x28), key)) {
                    if (vec) {
                        int* q = *(int**)(vec + 4);
                        if (q < *(int**)(vec + 8)) { *(int**)(vec + 4) = q + 1; if (q) *q = (int)(e - 0x28); }
                        else FUN_00b96600();
                    }
                    ++count;
                }
            }
            int cc = count;
            if (count < 1 || (char)arg4 == 0) {
                if (FUN_00f27990((int)e, key)) {
                    if (vec) {
                        int* q = *(int**)(vec + 4);
                        if (q < *(int**)(vec + 8)) { *(int**)(vec + 4) = q + 1; if (q) *q = (int)e; }
                        else FUN_00b96600();
                    }
                    ++cc;
                    count = cc;
                }
            }
            b += 0x27e8;
            e += 0x27e8;
        } while (b != end2bf8);
        return count;
    }
    return count;
}

// ---------------------------------------------------------------------------
// 0x00f2b270  does anything match?
// ---------------------------------------------------------------------------
struct MatchObj {
    char pad0[0x130];
    char pad1[0x48];
    char* begin178;   // +0x178
    char* end17c;     // +0x17c
    char pad2[0x2674];
    char* begin2bf4;  // +0x2bf4
    char* end2bf8;    // +0x2bf8
    bool any(void* key);
};

// @ 0x00f2b270
bool MatchObj::any(void* key)
{
    char r = FUN_00f27990((int)this + 0x130, (int)key) ? 1 : 0;
    char* p = begin178;
    while (p != end17c) {
        if (r < 1 && FUN_00f27990((int)p, (int)key))
            ++r;
        p += 0x38;
    }
    char* q = begin2bf4;
    if (q != end2bf8) {
        char* e = q + 0x58;
        do {
            if (r < 1) {
                if (FUN_00f27990((int)(e - 0x50), (int)key)) ++r;
                if (r < 1) {
                    if (FUN_00f27990((int)(e - 0x28), (int)key)) ++r;
                    if (r < 1 && FUN_00f27990((int)e, (int)key)) ++r;
                }
            }
            q += 0x27e8;
            e += 0x27e8;
        } while (q != end2bf8);
    }
    return r != 0;
}

// ---------------------------------------------------------------------------
// 0x00f2b340  check all collected entries
// ---------------------------------------------------------------------------
// @ 0x00f2b340
bool FUN_00f2b340(BigObj* self)
{
    int begin = 0, end = 0, cap = 0;
    self->collect((int)&begin, 0x30f0f, 0);
    int* p = &begin;
    int n = end - begin;
    n >>= 2;
    bool ok = true;
    for (int i = 0; i < n; ++i) {
        int e = p[i];
        if (!FUN_00f2ac30((void*)e, (int*)(e + 0x10), 0, 0)) {
            if (!FUN_00f259b0())
                ok = false;
        }
    }
    if (begin && ((int*)(begin))[-1] != 0)
        operator_delete((void*)begin);
    return ok;
}
extern int FUN_00f259b0();   // 0x00f259b0
