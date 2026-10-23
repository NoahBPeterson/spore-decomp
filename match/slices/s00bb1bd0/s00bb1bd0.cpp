// match/slices/s00bb1bd0/s00bb1bd0.cpp
// Object file: SPStarManager.obj (VS2008 SP1).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Star-record / empire bookkeeping helpers: the star manager's per-tick empire
// assignment, the abduct / target query helpers, and the eastl
// vector<EA::AutoRefCount<SP::cStarRecord>> insert instantiations.

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

// ---- globals (address in comment) -------------------------------------------
extern float g_1470f1c;   // 0x1470f1c 2.0f
extern float g_13eb1bc;   // 0x13eb1bc -1.0f
extern float g_1465e90;   // 0x1465e90 20.0f
extern float g_1465ea8;   // 0x1465ea8 3.0f
extern float g_13eb960;   // 0x13eb960 0.01f
extern float g_156c51c;   // 0x156c51c
extern int   g_15b46d0[]; // 0x15b46d0 bit-index table
extern char  g_1601760[]; // 0x1601760 EA::Random RNG
extern char  g_168965c[]; // 0x168965c criteria position
extern char  g_13ebb38[]; // 0x13ebb38 allocator tag

// ---- external callees (free functions) --------------------------------------
int   __stdcall FUN_00b3d430(int t);                           // 0xb3d430 TerraformingManager
int   __fastcall FUN_00bbc670(int t);                          // 0xbbc670
int   __cdecl    FUN_00b3d2a0();                               // 0xb3d2a0 SP_StarManager
void* __fastcall FUN_005c65e0(void* civ);                      // 0x5c65e0 GetCities -> civ+0x3c
void  __cdecl    FUN_00f47380(void* p);                        // 0xf47380 operator delete
void* __cdecl    FUN_00f473a0(u32 n, const char* name, int a, int b,
                              const char* file, int line);      // 0xf473a0 EAAllocate
void* __cdecl    FUN_011e0744(void* dst, void* src, int bytes); // 0x11e0744 eastl move
void  __cdecl    FUN_006782c0(void* first, void* last, void* dst); // 0x6782c0 eastl do_copy
int   __cdecl    FUN_00c8b450(int x);                          // 0xc8b450 IsGasStarType
char  __cdecl    FUN_00fefe70(int item);                       // 0xfefe70
int   __cdecl    FUN_004010a0();                               // 0x4010a0
void  __cdecl    FUN_00423650(void* a, void* b);               // 0x423650 WString_Assign
int   __cdecl    FUN_00b96130(void* a, void* b, void* rng);    // 0xb96130
void  __cdecl    FUN_00ba61b0(int a, void* b);                 // 0xba61b0
int   __fastcall FUN_00a68fb0(void* rng, int n);               // 0xa68fb0 RandomUint32Uniform
int*  __fastcall FUN_00e5c780(int this_, void* a, void* b);    // 0xe5c780 rbtree find
int*  __fastcall FUN_005ecf80(int this_, int key, void* out);  // 0x5ecf80 map find
void  __fastcall FUN_00ae6970(void* v);                        // 0xae6970 vector dtor
void  __cdecl    FUN_006a1250(int owner, int key, int* out);   // 0x6a1250 GetPropertyAsKey

// element operations on the 20-byte star-record element
struct E20 { unsigned char raw[0x14]; };
void  __fastcall FUN_00ba95a0(E20* dst, E20* src);   // 0xba95a0 copy-construct
void  __fastcall FUN_00ba9960(E20* dst, int n, E20* src); // 0xba9960 fill-construct
void  __fastcall FUN_00ba98b0(E20* dst, void* a, void* b, void* c); // 0xba98b0
void  __cdecl    FUN_00baa8f0(E20* first, E20* last, E20* dLast);   // 0xbaa8f0 move_backward
void  __fastcall FUN_00babe40(E20* a, E20* b, E20* c);              // 0xbabe40 assign
void  __fastcall FUN_01011cc0(E20* dst, E20* src);                  // 0x1011cc0 assign

// ---- stub object types ------------------------------------------------------
struct IRef {
    virtual int  AddRef();
    virtual void Release();
};

struct Empire {
    void FUN_00c341a0(int item);   // 0xc341a0 AddStar
};

struct Prop {
    int*   FUN_0041e990();         // 0x41e990 GetInt
    float* FUN_0041ea70();         // 0x41ea70 GetFloat
};

// The star-record element type: all of its methods take the extra argument on
// the stack (plain __thiscall), which is what keeps the pushes in place.
struct StarRec {
    int   FUN_00bb9ae0();          // 0xbb9ae0
    char  FUN_00bb9af0(int v);     // 0xbb9af0
    void  FUN_00bb9ad0(int v);     // 0xbb9ad0
    void  FUN_00bb9b00(int a, int b); // 0xbb9b00
    void  FUN_00bb9b90(void* p);   // 0xbb9b90
    void  FUN_00bb9c10(int v);     // 0xbb9c10
    int   FUN_00b1fdb0();          // 0xb1fdb0 GetAvatar
    int*  FUN_00bba790();          // 0xbba790
    int   FUN_00bbaa60(int v);     // 0xbbaa60
    int   FUN_00801920();          // 0x801920 cSPGameDataUFO::AddRef
};

// The criteria block fed to the star-search helpers.
struct Crit {
    int   m0;
    int   m4;
    int   m8;
    float mC;
    float m10;
    float m14;
    int   m18;
};

// A 3-pointer eastl vector of 4-byte elements.
struct PtrVec {
    void* mpBegin;
    void* mpEnd;
    void* mpCap;
};

// The star manager / game-data object (this of the per-tick helpers).
struct SM {
    char  pad000[0xc8];
    int   mC8;                        // +0xc8 vector-of-vectors base
    int   mCC;                        // +0xcc
    char  pad0d0[0xdc - 0xd0];
    int   mDC;                        // +0xdc AutoRefCount vector base
    int   mE0;                        // +0xe0
    char  pad0e4[0x118 - 0xe4];
    int   m118;                       // +0x118
    int   m11C;                       // +0x11c
    char  pad120[0x148 - 0x120];
    int   m148;                       // +0x148
    char  pad14c[0x1a0 - 0x14c];
    int   m1A0;                       // +0x1a0 property owner
    char  pad1a4[0x1d4 - 0x1a4];
    int   m1D4;                       // +0x1d4
    int   m1D8;                       // +0x1d8

    int  FUN_00bb1340(int item);                    // 0xbb1340
    void FUN_00bb1080(void* pos, void* crit, void* out);  // 0xbb1080
    void* FUN_00bb0e90(void* pos, void* crit);      // 0xbb0e90
    void FUN_00bae9b0(int item);                    // 0xbae9b0
    void FUN_00bbac80(int a, int b);                // 0xbbac80 SetStar
    void FUN_00a16a30(int a);                       // 0xa16a30 SetMessageServer
    void FUN_00a16a90(int a);                       // 0xa16a90
    void FUN_00ba64a0(void* a, void* b, int c);     // 0xba64a0
    void FUN_00baf630(int a, int b);                // 0xbaf630

    void FUN_00bb2070();
    void FUN_00bb23e0();
    void FUN_00bb2610();
    char FUN_00bb21b0(void* civ, float f);
    bool FUN_00bb2330(void* item, char flag);
    bool FUN_00bb24d0(void* civ);
    void FUN_00bb28c0(void* pos);
};

// An eastl vector of 20-byte elements.
struct E20Vec {
    E20* mpBegin;
    E20* mpEnd;
    E20* mpCap;
    void FUN_00bb1bd0(E20* position, int n, E20* value);
    void FUN_00bb1df0(E20* position, E20* value);
};

// ---------------------------------------------------------------------------
// eastl::vector<E20>::insert(position, n, value)  -- thiscall, ret 0xc.
// @ 0x00bb1bd0
// ---------------------------------------------------------------------------
void E20Vec::FUN_00bb1bd0(E20* position, int n, E20* value) {
    if ((u32)((mpCap - mpEnd) / 0x14) < (u32)n) {
        int size = (int)((mpEnd - mpBegin) / 0x14);
        u32 newCap = (u32)(size * 2);
        if (size == 0) newCap = 1;
        u32 want = (u32)size + (u32)n;
        if (want < newCap) want = newCap;
        E20* nbuf = want ? (E20*)FUN_00f473a0(want * 0x14, "Simulator", 0, 0,
                          "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
        int off = (int)((char*)position - (char*)mpBegin);
        char* p = (char*)FUN_011e0744(nbuf, mpBegin, off);
        p += (off / 0x14) * 0x14;
        FUN_00ba9960((E20*)p, n, value);
        int tail = (int)((char*)mpEnd - (char*)position);
        char* r = (char*)FUN_011e0744(p + n * 0x14, position, tail);
        if (mpBegin && ((int*)mpBegin)[-1] != 0) FUN_00f47380(mpBegin);
        mpBegin = nbuf;
        mpEnd = (E20*)(r + (tail / 0x14) * 0x14);
        mpCap = (E20*)((char*)nbuf + want * 0x14);
    } else if (n != 0) {
        E20 tmp;
        FUN_00ba95a0(&tmp, value);
        int elemsAfter = (int)((mpEnd - position) / 0x14);
        if ((u32)n < (u32)elemsAfter) {
            E20* src = mpEnd - n;
            FUN_00ba98b0(&tmp, src, mpEnd, mpEnd);
            mpEnd += n;
            FUN_00baa8f0(position, src, mpEnd - n);
            FUN_00babe40(position, position + n, &tmp);
        } else {
            FUN_00ba9960(mpEnd, n - elemsAfter, &tmp);
            mpEnd += (n - elemsAfter);
            FUN_00ba98b0(&tmp, position, mpEnd, mpEnd);
            mpEnd += elemsAfter;
            FUN_00babe40(position, position + n, &tmp);
        }
    }
}

// ---------------------------------------------------------------------------
// eastl::vector<E20>::insert(position, value)  -- thiscall, ret 8.
// @ 0x00bb1df0
// ---------------------------------------------------------------------------
void E20Vec::FUN_00bb1df0(E20* position, E20* value) {
    if (mpEnd != mpCap) {
        E20* src = value;
        if (value >= position && value < mpEnd) src = value + 1;
        if (mpEnd) FUN_00ba95a0(mpEnd, mpEnd - 1);
        FUN_00baa8f0(position, mpEnd - 1, mpEnd);
        FUN_01011cc0(position, src);
        mpEnd += 1;
    } else {
        int size = (int)((mpEnd - mpBegin) / 0x14);
        if (size == 0) size = 1;
        else size = size * 2;
        E20* nbuf = size ? (E20*)FUN_00f473a0(size * 0x14, "Simulator", 0, 0,
                        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1) : 0;
        int off = (int)((char*)position - (char*)mpBegin);
        char* p = (char*)FUN_011e0744(nbuf, mpBegin, off);
        p += (off / 0x14) * 0x14;
        if (p) FUN_00ba95a0((E20*)p, value);
        E20* e2 = mpEnd;
        char* r = (char*)FUN_011e0744(p + 0x14, position, (int)((char*)e2 - (char*)position));
        if (mpBegin && ((int*)mpBegin)[-1] != 0) FUN_00f47380(mpBegin);
        mpEnd = (E20*)(r + ((int)((char*)e2 - (char*)position) / 0x14) * 0x14);
        mpBegin = nbuf;
        mpCap = (E20*)((char*)nbuf + size * 0x14);
    }
}

// ---------------------------------------------------------------------------
// Assign every star in the grid to its empire: pass 1 (type 5 + flag 4, or
// flag 2), pass 2 (type 5 only).
// @ 0x00bb2070
// ---------------------------------------------------------------------------
void SM::FUN_00bb2070() {
    int cnt = (*(int*)((char*)this + 0xcc) - *(int*)((char*)this + 0xc8)) / 0x14;
    if (cnt > 0) {
        int off = 0;
        do {
            int* v = (int*)(*(int*)((char*)this + 0xc8) + off);
            int i = 0;
            int c = (v[1] - v[0]) >> 2;
            if (c > 0) {
                do {
                    int u = *(int*)(v[0] + i * 4);
                    StarRec* r = (StarRec*)u;
                    if ((r->FUN_00bb9ae0() == 5 && r->FUN_00bb9af0(4)) ||
                        r->FUN_00bb9af0(2)) {
                        ((Empire*)FUN_00bb1340(u))->FUN_00c341a0(u);
                    }
                    i++;
                } while (i < c);
            }
            off += 0x14;
        } while (--cnt);
    }
    cnt = (*(int*)((char*)this + 0xcc) - *(int*)((char*)this + 0xc8)) / 0x14;
    if (cnt > 0) {
        int off = 0;
        do {
            int* v = (int*)(*(int*)((char*)this + 0xc8) + off);
            int i = 0;
            int c = (v[1] - v[0]) >> 2;
            if (c > 0) {
                do {
                    int u = *(int*)(v[0] + i * 4);
                    if (((StarRec*)u)->FUN_00bb9ae0() == 5) {
                        ((Empire*)FUN_00bb1340(u))->FUN_00c341a0(u);
                    }
                    i++;
                } while (i < c);
            }
            off += 0x14;
        } while (--cnt);
    }
}

// ---------------------------------------------------------------------------
// Pick a star for the civ's abduct target and flag it.
// @ 0x00bb21b0
// ---------------------------------------------------------------------------
char SM::FUN_00bb21b0(void* civ, float f) {
    Crit crit;
    PtrVec out;
    crit.m0 = 0x1ff0;
    crit.m4 = 0x3f;
    crit.m8 = 0;
    crit.mC = 0.0f;
    crit.m10 = f * g_1470f1c;
    crit.m14 = f;
    crit.m18 = 2;
    out.mpBegin = 0;
    out.mpEnd = 0;
    out.mpCap = 0;
    char ret = 0;
    void* cities = FUN_005c65e0(civ);
    FUN_00b3d2a0();
    ((SM*)FUN_00b3d2a0())->FUN_00bb1080(cities, &crit, &out);
    int n = (int)(((char*)out.mpEnd - (char*)out.mpBegin) >> 2);
    if (n > 0) {
        int i = 0;
        do {
            StarRec* item = (StarRec*)((int*)out.mpBegin)[i];
            if (item->FUN_00bb9ae0() == 1) {
                if (FUN_00c8b450(item->FUN_00801920()) == 0 &&
                    item->FUN_00bb9af0(2) == 0 &&
                    item->FUN_00bb9af0(1) == 0) {
                    int* p = *(int**)((char*)this + 0x118);
                    int* e = *(int**)((char*)this + 0x11c);
                    if (p != e) {
                        while (*p != (int)item) {
                            p++;
                            if (p == e) break;
                        }
                        if (p != e) goto next;
                    }
                    if (*(char*)((char*)item + 0xac) == 0)
                        FUN_00bae9b0((int)item);
                    if (FUN_00fefe70((int)item)) {
                        ret = 1;
                        item->FUN_00bb9c10(1);
                        item->FUN_00bb9b00(0x20000, 1);
                        break;
                    }
                }
            }
        next:
            i++;
        } while (i < n);
    }
    {
        void** p = (void**)out.mpBegin;
        if (out.mpBegin < out.mpEnd) {
            do {
                if (*p) ((IRef*)*p)->Release();
                p++;
            } while (p < (void**)out.mpEnd);
        }
        if (out.mpBegin && ((int*)out.mpBegin)[-1] != 0)
            FUN_00f47380(out.mpBegin);
    }
    return ret;
}

// ---------------------------------------------------------------------------
// Whether `item` is a valid abduct target.
// @ 0x00bb2330
// ---------------------------------------------------------------------------
bool SM::FUN_00bb2330(void* item, char flag) {
    StarRec* r = (StarRec*)item;
    bool b = true;
    if (r->FUN_00bb9ae0() > 1) b = false;
    if (flag == 0 && r->FUN_00bb9af0(1)) b = false;
    if (r->FUN_00b1fdb0() != -1) b = false;
    if ((int)item == *(int*)((char*)this + 0x148)) return false;
    if (b) {
        if (FUN_00bb21b0(item, g_156c51c) == 0) return false;
        if (*(char*)((char*)item + 0xac) != 0) {
            int* p = r->FUN_00bba790();
            if (((p[1] - p[0]) & 0xfffffffc) != 0x14) b = false;
            int t = r->FUN_00bbaa60(0);
            if (FUN_00bbc670(FUN_00b3d430(t)) != 3) return false;
        }
    }
    return b;
}

// ---------------------------------------------------------------------------
// Erase every invalid abduct target from the +0xdc vector.
// @ 0x00bb23e0
// ---------------------------------------------------------------------------
void SM::FUN_00bb23e0() {
    int* p = (int*)*(int*)((char*)this + 0xdc);
    if (p != (int*)*(int*)((char*)this + 0xe0)) {
        int* next = p + 1;
        do {
            StarRec* item = (StarRec*)*p;
            bool b = true;
            if (item->FUN_00bb9ae0() > 1) b = false;
            if (item->FUN_00b1fdb0() != -1) b = false;
            if ((int)item == *(int*)((char*)this + 0x148) || !b ||
                FUN_00bb21b0(item, g_156c51c) == 0) {
            erase:
                if (next < (int*)*(int*)((char*)this + 0xe0))
                    FUN_006782c0(next, (void*)*(int*)((char*)this + 0xe0), p);
                *(int*)((char*)this + 0xe0) -= 4;
                int last = *(int*)*(int*)((char*)this + 0xe0);
                if (last) ((IRef*)last)->Release();
            } else {
                if (*(char*)((char*)item + 0xac) != 0) {
                    int* q = item->FUN_00bba790();
                    if (((q[1] - q[0]) & 0xfffffffc) != 0x14) b = false;
                    int t = item->FUN_00bbaa60(0);
                    if (FUN_00bbc670(FUN_00b3d430(t)) != 3) goto erase;
                }
                if (!b) goto erase;
                p++;
                next++;
            }
        } while (p != (int*)*(int*)((char*)this + 0xe0));
    }
}

// ---------------------------------------------------------------------------
// True when the civ has a star for every bit (0..2) of the bit table.
// @ 0x00bb24d0
// ---------------------------------------------------------------------------
bool SM::FUN_00bb24d0(void* civ) {
    Crit crit;
    PtrVec out;
    crit.m0 = 0x1fff;
    crit.m4 = 0x20;
    crit.m8 = 0;
    crit.mC = g_13eb1bc;
    crit.m10 = g_1465e90;
    crit.m14 = g_1465ea8;
    crit.m18 = 0;
    out.mpBegin = 0;
    out.mpEnd = 0;
    out.mpCap = 0;
    void* cities = FUN_005c65e0(civ);
    FUN_00b3d2a0();
    ((SM*)FUN_00b3d2a0())->FUN_00bb1080(cities, &crit, &out);
    int n = (int)(((char*)out.mpEnd - (char*)out.mpBegin) >> 2);
    u32 bits = 0;
    u32 i = 0;
    while (i < (u32)n) {
        int avatar = ((StarRec*)((int*)out.mpBegin)[i])->FUN_00b1fdb0();
        int mgr = FUN_00b3d2a0();
        int item;
        if (avatar == -1) {
            item = 0;
        } else {
            int* hit = FUN_00e5c780(mgr + 0x150, &avatar, &avatar);
            if (*hit == mgr + 0x154) item = 0;
            else item = *(int*)(*hit + 0x14);
        }
        i++;
        bits |= 1u << g_15b46d0[*(int*)(item + 0x58)];
        if (bits == 7) break;
    }
    {
        void** p = (void**)out.mpBegin;
        if (out.mpBegin < out.mpEnd) {
            do {
                if (*p) ((IRef*)*p)->Release();
                p++;
            } while (p < (void**)out.mpEnd);
        }
        if (out.mpBegin && ((int*)out.mpBegin)[-1] != 0)
            FUN_00f47380(out.mpBegin);
    }
    return bits == 7;
}

// ---------------------------------------------------------------------------
// Spawn a random star of the right kind and wire it into the grid.
// @ 0x00bb2610
// ---------------------------------------------------------------------------
void SM::FUN_00bb2610() {
    int key1 = 0;
    if (*(int*)((char*)this + 0x1a0) != 0) {
        int tmp;
        int obj = *(int*)((char*)this + 0x1a0);
        if ((*(char(__thiscall*)(int, int, void*))((*(void***)obj)[9]))(obj, 0x195e031, &tmp) &&
            *(short*)(tmp + 0x12) == 9) {
            key1 = *((Prop*)tmp)->FUN_0041e990();
        }
    }
    float fVal = 0.0f;
    if (*(int*)((char*)this + 0x1a0) != 0) {
        int tmp;
        int obj = *(int*)((char*)this + 0x1a0);
        if ((*(char(__thiscall*)(int, int, void*))((*(void***)obj)[9]))(obj, 0x195e032, &tmp) &&
            *(short*)(tmp + 0x12) == 0xd) {
            fVal = *((Prop*)tmp)->FUN_0041ea70();
        }
    }
    m1D8 = m1D4 | 0x80000000;
    m1D4 = m1D4 + 1;
    int prop[3];
    prop[0] = 0;
    prop[1] = 0;
    prop[2] = 0;
    FUN_006a1250(*(int*)((char*)this + 0x1a0), 0x195e035, prop);
    float pos[3];
    pos[0] = 0.0f;
    pos[1] = 0.0f;
    pos[2] = 0.0f;
    Crit crit;
    crit.m0 = 0x1ff1;
    crit.m4 = 0x3f;
    crit.m8 = 0;
    crit.mC = g_13eb1bc;
    crit.m10 = g_13eb960;
    crit.m14 = g_1465e90;
    crit.m18 = 2;
    void* rec = FUN_00bb0e90(pos, &crit);
    if (rec == 0) return;
    FUN_00baf630(m1D8, (int)rec);
    StarRec* star = (StarRec*)rec;
    star->FUN_00bb9ad0(5);
    star->FUN_00bb9b90(prop);
    star->FUN_00bb9c10(1);
    Crit crit2;
    crit2.m0 = 0x1ff1;
    crit2.m4 = 0x3f;
    crit2.m8 = 0;
    crit2.mC = g_13eb960;
    crit2.m10 = g_1465e90;
    crit2.m14 = fVal;
    crit2.m18 = 2;
    PtrVec out;
    out.mpBegin = 0;
    out.mpEnd = 0;
    out.mpCap = 0;
    FUN_00bb1080(g_168965c, &crit2, &out);
    int* first = (int*)out.mpBegin;
    int* last = (int*)out.mpEnd;
    int  total = FUN_00b96130(first, last, g_1601760);
    int  cnt = (int)(((char*)last - (char*)first) >> 2);
    int  pick = (cnt < total) ? total : cnt;
    if (pick > 0) {
        do {
            int idx = FUN_00a68fb0(g_1601760, cnt);
            int item = first[idx];
            FUN_00a16a90(m1D8);
            StarRec* s2 = (StarRec*)item;
            s2->FUN_00bb9ad0(5);
            s2->FUN_00bb9b90(prop);
            s2->FUN_00bb9c10(1);
            if (idx != cnt - 1) {
                int* a = &first[cnt - 1];
                int* b = &first[idx];
                int  x = *a;
                int  y = *b;
                if (x != y) {
                    if (x) ((IRef*)x)->AddRef();
                    *b = x;
                    if (y) ((IRef*)y)->Release();
                }
            }
            last--;
            out.mpEnd = last;
            if (*last) ((IRef*)*last)->Release();
            pick--;
        } while (pick);
    }
    FUN_00ae6970(&out);
}

// ---------------------------------------------------------------------------
// Spawn a star at `pos`, name it and install it.
// @ 0x00bb28c0
// ---------------------------------------------------------------------------
void SM::FUN_00bb28c0(void* pos) {
    Crit crit;
    crit.m0 = 0x1ff1;
    crit.m4 = 0x3f;
    crit.m8 = 0;
    crit.mC = g_13eb1bc;
    crit.m10 = g_13eb1bc;
    crit.m14 = g_13eb1bc;
    crit.m18 = 0;
    void* starp = FUN_00bb0e90(pos, &crit);
    if (starp == 0) return;
    StarRec* star = (StarRec*)starp;
    int canvas = FUN_004010a0();
    star->FUN_00bb9ad0(0);
    PtrVec w;
    w.mpBegin = 0;
    w.mpEnd = 0;
    w.mpCap = 0;
    star->FUN_00bb9b90(&w);
    int* node = FUN_005ecf80(canvas, 0x7cab064c, &w);
    if (node != (int*)((char*)star + 0x60)) {
        FUN_00423650((void*)node[0], (void*)node[1]);
    }
    if ((((char*)w.mpEnd - (char*)w.mpBegin) & 0xfffffffe) > 2 && w.mpBegin)
        FUN_00f47380(w.mpBegin);
    FUN_00a16a30(0);
    FUN_00bbac80(0, 0);
    FUN_00a16a90(-1);
    *(char*)((char*)star + 0xac) = 0;
    star->FUN_00bb9c10(1);
    int obj = 0;
    FUN_00ba61b0(*(int*)((char*)star + 0x70) + ((u8)*(char*)((char*)star + 0xac) << 0x18), &obj);
    int* node2 = FUN_005ecf80(canvas, 0x7e1310a, &w);
    if (node2 != (int*)(obj + 0x18)) {
        FUN_00423650((void*)node2[0], (void*)node2[1]);
    }
    if ((((char*)w.mpEnd - (char*)w.mpBegin) & 0xfffffffe) > 2 && w.mpBegin)
        FUN_00f47380(w.mpBegin);
    *(int*)(obj + 0x2c) = 2;
    *(int*)(obj + 0x28) = 1;
    *(int*)(obj + 0x194) = 0;
    FUN_00ba64a0((void*)obj, star, 0);
    (*(char*)((char*)star + 0xac))++;
    ((IRef*)obj)->Release();
}
