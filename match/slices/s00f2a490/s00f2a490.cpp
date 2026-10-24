// Building-data container helpers (eastl vector< cBuildingData >, stride 0x38)
// plus the tutorial command-list builder.  /O2.
//
// Flags: /O2 /MD /Gy /TP

typedef unsigned int   uint32_t;
typedef unsigned int   uint;
typedef unsigned char  uint8_t;

struct Sub { void assign(Sub* other); };          // 0x00473500
struct Elem34 { float f; int d[12]; };            // 0x34
struct BuildData {                                 // 0x38, scalar fields (no /GS buffer)
    int  f00, f04, f08, f0c;
    int  f10, f14, f18;
    bool f1c;
    bool pad1d, pad1e, pad1f;
    bool f20;
    bool pad21, pad22, pad23;
    int  f24, f28, f2c;
    int  f30, f34;
};
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
// eastl::basic_string<wchar_t> layout: {begin, end, capacity}.
struct WStr {
    wchar_t* b;
    wchar_t* e;
    wchar_t* c;
    void CopyCtor(const WStr* src);            // 0x0056e2d0
};

extern wchar_t gEmptyString16[];               // 0x01667bac eastl::gEmptyString16

extern "C" {
void* __cdecl FUN_0093c5a0(WStr* out, int name, int n);                              // 0x0093c5a0 EA::ConvertToString16
void  __cdecl FUN_00f47380(void* p);                                                 // 0x00f47380 operator delete
char  __cdecl FUN_00ae5530(int* a, const char* name, void* key, const wchar_t* cls); // 0x00ae5530 write Key
char  __cdecl FUN_005954f0(int* a, const char* id, void* val, const wchar_t* type);  // 0x005954f0 write int64
}

// @ 0x00f2a510
bool FUN_00f2a510(int* a, int b, int* c)
{
    if (c == 0)
        return 1;
    if ((c[4] & c[5]) == -1 && *c == 0)
        return 1;

    WStr N;
    if (b == 0) {
        N.b = gEmptyString16;
        N.e = gEmptyString16;
        N.c = gEmptyString16 + 1;
    } else {
        FUN_0093c5a0(&N, b, -1);
    }

    WStr C;
    C.CopyCtor(&N);

    if ((((char*)N.c - (char*)N.b) & ~1) > 2 && N.b)
        FUN_00f47380(N.b);

    const wchar_t* str = (C.b == C.e) ? L"asset" : C.b;
    char ok = ((char(__thiscall*)(int*, const wchar_t*))(*(void***)a)[0])(a, str);

    if ((c[4] & c[5]) == -1)
        ok = ok ? (FUN_00ae5530(a, "key", c, L"EA::ResourceMan::Key") != 0) : 0;
    else
        ok = ok ? (FUN_005954f0(a, "ID", c + 4, L"uint64_t") != 0) : 0;

    char result = 0;
    if (ok)
        result = ((char(__thiscall*)(int*, const wchar_t*))(*(void***)a)[1])(a, str) != 0;

    if ((((char*)C.c - (char*)C.b) & ~1) > 2 && C.b)
        FUN_00f47380(C.b);
    return result;
}

// ---------------------------------------------------------------------------
// 0x00f2a6a0  build tutorial command list
// ---------------------------------------------------------------------------
extern int FUN_00ec6e70(int);     // 0x00ec6e70

struct Rec { int d[8]; };         // 0x20

struct RecVec {
    Rec* mpBegin;   // +0
    Rec* mpEnd;     // +4
    Rec* mpCap;     // +8
    void erase(Rec* first, Rec* last);        // 0x00899420
    void push_back(const Rec& v);             // 0x00c072b0
    Rec* insert(Rec* pos, const Rec* v);      // 0x00c06c30
};

inline void push8(RecVec* v, Rec* rec)
{
    if (v->mpEnd < v->mpCap) {
        Rec* q = v->mpEnd;
        v->mpEnd = q + 1;
        if (q)
            *q = *rec;
    } else {
        v->insert(v->mpEnd, rec);
    }
}

struct TutCmds { void Build_00f2a6a0(); TutCmds* Build_00f2aac0(); };

// @ 0x00f2a6a0
void TutCmds::Build_00f2a6a0()
{
    char* self = (char*)this;
    RecVec* v = (RecVec*)(self + 0x4cc);
    Rec rec;

    v->erase(v->mpBegin, v->mpEnd);

    bool flag = *(int*)(self + 0x4b8) == 1;
    int mode = *(int*)(self + 0x4ac);
    rec.d[6] = -1;
    rec.d[7] = -1;

    if (mode == 1) {
        rec.d[0] = 2; rec.d[1] = 0; rec.d[2] = -1; rec.d[3] = 9;
        rec.d[4] = -1; rec.d[5] = -1;
        v->push_back(rec);
    } else if (mode == 2 || mode == 4 || mode == 5) {
        rec.d[0] = 2; rec.d[1] = 0; rec.d[2] = -1; rec.d[3] = 0;
        rec.d[4] = 0; rec.d[5] = -1; rec.d[6] = -1; rec.d[7] = -1;
        push8(v, &rec);

        if (mode != 2) {
            rec.d[0] = 0; rec.d[1] = -1; rec.d[2] = -1; rec.d[3] = 0;
            if (flag)
                rec.d[3] = 5;
            if (mode == 4)
                rec.d[3] = 8;
            int kind = *(int*)(self + 0x4a8);
            if (kind != 1 && kind != 0) {
                for (unsigned i = 1; i < 5; ++i) {
                    if (i != (unsigned)(kind - 1) && FUN_00ec6e70(i)) {
                        rec.d[4] = 1;
                        rec.d[5] = i;
                        v->push_back(rec);
                    }
                }
                rec.d[4] = 0;
                rec.d[5] = -1;
                v->push_back(rec);
            } else {
                rec.d[4] = 0;
                rec.d[5] = -1;
                v->push_back(rec);
            }
        }
    }

    rec.d[0] = 0; rec.d[1] = -1; rec.d[2] = -1;
    if (mode == 2 || mode == 1) {
        rec.d[3] = 0xb; rec.d[4] = -1; rec.d[5] = -1;
        push8(v, &rec);
    }
    rec.d[3] = 0xc; rec.d[4] = 0; rec.d[5] = -1;
    push8(v, &rec);
    if (*(int*)(self + 0x4b0) == 2) {
        rec.d[4] = -1; rec.d[5] = -1;
        rec.d[3] = 3; rec.d[2] = -1; rec.d[1] = -1; rec.d[0] = 0;
        push8(v, &rec);
    } else if (*(int*)(self + 0x4b0) == 3) {
        rec.d[4] = 2; rec.d[5] = *(int*)(self + 0x4bc);
        rec.d[3] = 3; rec.d[2] = -1; rec.d[1] = -1; rec.d[0] = 0;
        push8(v, &rec);
    }
    if (*(int*)(self + 0x4b4) == 2) {
        rec.d[3] = 4; rec.d[4] = 0; rec.d[5] = -1; rec.d[6] = 0; rec.d[7] = -1;
    } else if (*(int*)(self + 0x4b0) == 3) {
        rec.d[3] = 3; rec.d[4] = 2; rec.d[5] = *(int*)(self + 0x4bc);
        rec.d[6] = 2; rec.d[7] = *(int*)(self + 0x4c0);
    } else {
        goto tail;
    }
    rec.d[2] = -1; rec.d[1] = -1; rec.d[0] = 0;
    push8(v, &rec);
tail:
    rec.d[4] = -1; rec.d[5] = -1; rec.d[6] = -1; rec.d[7] = -1;
    rec.d[0] = 0; rec.d[1] = -1; rec.d[2] = -1;
    switch (*(int*)(self + 0x4b8)) {
    case 1:  rec.d[3] = 1; break;
    case 4:  rec.d[3] = 2; break;
    case 5:  rec.d[3] = 7; rec.d[4] = 2; rec.d[5] = *(int*)(self + 0x4c4); break;
    case 6:  rec.d[3] = 10; break;
    default: rec.d[3] = 6; rec.d[4] = -1; rec.d[5] = -1; break;
    }
    push8(v, &rec);
}

// ---------------------------------------------------------------------------
// 0x00f2aac0  initialise the tutorial-command object (size 0x234)
// ---------------------------------------------------------------------------
// @ 0x00f2aac0
TutCmds* TutCmds::Build_00f2aac0()
{
    char* self = (char*)this;
    *(volatile int*)(self + 0x00) = -1;
    *(volatile float*)(self + 0x04) = 0.0f;
    *(volatile float*)(self + 0x08) = 0.0f;
    *(volatile float*)(self + 0x0c) = 0.0f;
    *(volatile float*)(self + 0x10) = 0.0f;
    *(volatile float*)(self + 0x14) = 0.0f;
    *(volatile float*)(self + 0x18) = 0.0f;
    *(volatile float*)(self + 0x1c) = 1.0f;
    *(volatile float*)(self + 0x20) = 1.0f;
    *(volatile float*)(self + 0x24) = 0.5f;
    *(volatile char**)(self + 0x28) = self + 0x40;
    *(volatile char**)(self + 0x2c) = self + 0x40;
    *(volatile char**)(self + 0x30) = self + 0x1e0;
    *(volatile int*)(self + 0x3c) = 0;
    *(volatile float*)(self + 0x1e0) = 1.0f;
    *(volatile float*)(self + 0x1e4) = 1.0f;
    *(volatile float*)(self + 0x1e8) = 0.0f;
    *(volatile float*)(self + 0x1ec) = 0.0f;
    *(volatile float*)(self + 0x1f0) = 0.0f;
    *(volatile float*)(self + 0x1f4) = 0.0f;
    *(volatile float*)(self + 0x1f8) = 0.0f;
    *(volatile float*)(self + 0x1fc) = 0.0f;
    *(volatile float*)(self + 0x200) = 1.0f;
    *(volatile float*)(self + 0x204) = 1.0f;
    *(volatile uint8_t*)(self + 0x208) = 0;
    *(volatile uint8_t*)(self + 0x209) = 0;
    *(volatile int*)(self + 0x20c) = 0;
    *(volatile int*)(self + 0x210) = 0;
    *(volatile int*)(self + 0x214) = 0;
    *(volatile float*)(self + 0x220) = 0.0f;
    *(volatile int*)(self + 0x224) = 0;
    *(volatile int*)(self + 0x228) = -1;
    *(volatile int*)(self + 0x22c) = -1;
    *(volatile int*)(self + 0x230) = -1;
    return this;
}

// ---------------------------------------------------------------------------
// 0x00f2ac30
// ---------------------------------------------------------------------------
// @ 0x00f2ac30
__declspec(noinline) bool FUN_00f2ac30(void* self, int* a, int b)
{
    (void)self; (void)a; (void)b;
    return 0;
}

// ---------------------------------------------------------------------------
// 0x00f2ada0  resize vector<BuildData> (stride 0x38)
// ---------------------------------------------------------------------------
struct Vec38 {
    BuildData* mpBegin;
    BuildData* mpEnd;
    BuildData* mpCapacity;
    void resize(uint32_t n);
    void insert(BuildData* pos, uint32_t count, BuildData* val);   // 0x00f28e40
    BuildData* erase(BuildData* first, BuildData* last);           // 0x00f28dd0
};

// @ 0x00f2ada0
void Vec38::resize(uint32_t n)
{
    uint32_t have = (uint32_t)(mpEnd - mpBegin);
    if (have < n) {
        BuildData tmp;
        tmp.f00 = 0;  tmp.f04 = 0;  tmp.f08 = 0;  tmp.f0c = 0;
        tmp.f10 = -1; tmp.f14 = -1; tmp.f18 = -1;
        tmp.f1c = 0;
        tmp.f20 = 0;
        tmp.f24 = 0;  tmp.f28 = 0;  tmp.f2c = 0;
        tmp.f30 = -1; tmp.f34 = -1;
        insert(mpEnd, n - have, &tmp);
    } else {
        erase(mpBegin + n, mpEnd);
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
    Vec38* v = (Vec38*)vec;
    v->erase(v->mpBegin, v->mpEnd);
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

struct IntVec {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    void reserve(int n);                                       // 0x00d01790
    void DoInsertKey4(uint32_t* pos, const uint32_t& value);   // 0x00b96600
};

// @ 0x00f2af60
void FUN_00f2af60(int vec, int key, int* count, int arg4, char arg5)
{
    if ((*count <= 0 || arg5 == 0) && FUN_00f27990(key, arg4)) {
        if (vec) {
            IntVec* v = (IntVec*)vec;
            uint32_t* end = v->mpEnd;
            if (end < v->mpCapacity) {
                v->mpEnd = end + 1;
                if (end) {
                    *end = (uint32_t)key;
                    ++*count;
                    return;
                }
            } else {
                uint32_t value = (uint32_t)key;
                v->DoInsertKey4(end, value);
            }
        }
        ++*count;
    }
}

// ---------------------------------------------------------------------------
// 0x00f2afc0  ordered insert
// ---------------------------------------------------------------------------
extern int* FUN_00f27fc0(int, int, int*, int);   // 0x00f27fc0

struct Elem18 { int d[6]; };                      // 0x18
struct Vec18 {
    Elem18* insert(Elem18* pos, const Elem18& val);    // 0x00f2a3a0
};

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
            pos = (int*)FUN_00f27fc0((int)mpBegin, (int)key, (int*)val, mFlag);
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
    ((Vec18*)this)->insert((Elem18*)pos, *(const Elem18*)val);
}

// ---------------------------------------------------------------------------
// 0x00f2b040  collect matching building data
// ---------------------------------------------------------------------------
extern bool FUN_00f259b0(void*, int*);       // 0x00f259b0

struct BigObj {
    char pad0[0x130];
    int  mKey130;            // +0x130
    char pad1[0x44];
    BuildData* begin178;     // +0x178
    BuildData* end17c;       // +0x17c
    char pad2[0x2a74];
    char* begin2bf4;         // +0x2bf4
    char* end2bf8;           // +0x2bf8
    int collect(int vec, int key, int arg4);
    bool check();            // 0x00f2b340
};

// @ 0x00f2b040
int BigObj::collect(int vec, int key, int arg4)
{
    int count = 0;
    if (vec)
        ((IntVec*)vec)->reserve((int)((end2bf8 - begin2bf4) / 0x27e8) * 3 +
                                (int)((char*)end17c - (char*)begin178) / 0x38 + 1);
    FUN_00f2af60(vec, (int)&mKey130, &count, key, (char)arg4);
    int* p = (int*)begin178;
    while (p != (int*)end17c) {
        if ((count < 1 || (char)arg4 == 0) && FUN_00f27990((int)p, key)) {
            if (vec) {
                IntVec* v = (IntVec*)vec;
                uint32_t* e = v->mpEnd;
                if (e < v->mpCapacity) {
                    v->mpEnd = e + 1;
                    if (e) *e = (uint32_t)(int)p;
                } else {
                    uint32_t value = (uint32_t)(int)p;
                    v->DoInsertKey4(e, value);
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
                        IntVec* v = (IntVec*)vec;
                        uint32_t* q = v->mpEnd;
                        if (q < v->mpCapacity) {
                            v->mpEnd = q + 1;
                            if (q) *q = (uint32_t)(int)(e - 0x50);
                        } else {
                            uint32_t value = (uint32_t)(int)(e - 0x50);
                            v->DoInsertKey4(q, value);
                        }
                    }
                    ++count;
                }
            }
            if (count < 1 || (char)arg4 == 0) {
                if (FUN_00f27990((int)(e - 0x28), key)) {
                    if (vec) {
                        IntVec* v = (IntVec*)vec;
                        uint32_t* q = v->mpEnd;
                        if (q < v->mpCapacity) {
                            v->mpEnd = q + 1;
                            if (q) *q = (uint32_t)(int)(e - 0x28);
                        } else {
                            uint32_t value = (uint32_t)(int)(e - 0x28);
                            v->DoInsertKey4(q, value);
                        }
                    }
                    ++count;
                }
            }
            int cc = count;
            if (count < 1 || (char)arg4 == 0) {
                if (FUN_00f27990((int)e, key)) {
                    if (vec) {
                        IntVec* v = (IntVec*)vec;
                        uint32_t* q = v->mpEnd;
                        if (q < v->mpCapacity) {
                            v->mpEnd = q + 1;
                            if (q) *q = (uint32_t)(int)e;
                        } else {
                            uint32_t value = (uint32_t)(int)e;
                            v->DoInsertKey4(q, value);
                        }
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
    char pad2[0x2a74];
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
bool BigObj::check()
{
    int* vec[3] = { 0, 0, 0 };
    collect((int)vec, 0x30f0f, 0);
    int* p = vec[0];
    uint32_t n = (uint32_t)(vec[1] - vec[0]);
    bool ok = true;
    for (uint32_t i = 0; i < n; ++i) {
        int e = p[i];
        if (!FUN_00f2ac30((void*)e, (int*)(e + 0x10), 0)) {
            if (!FUN_00f259b0((void*)e, (int*)(e + 0xc)))
                ok = false;
        }
    }
    if (p && ((int*)p)[-1] != 0)
        FUN_00f47380((void*)p);
    return ok;
}
