// s00bb5d80 -- SP cStarManager / cAppModeEditorBase gameplay helpers.
//
// Reconstructed from the disassembly in work/match/scratch_s00bb5d80_cards.txt.
// MSVC 2008 SP1, /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- /Isrc/game/include
// (same module as the neighbouring slices s00bb4f30 / s00bb6a30).
//
// The class family is SP::cStarManager (fields from s00bb4f30: the star-record
// grid at +0xc8 whose rows are 0x14-byte eastl vectors of AutoRefCount<cStarRecord>).
//
// Outcome: all seven functions are reconstructed in full and the TU compiles.
// 00bb6700 is byte-exact (manifest.txt); the other six are non-exact and are
// booked in nonmatching.txt.  Retail callees are __thiscall members (ecx =
// cStarManager / cStarRecord) with callee cleanup; FUN_00bb1bd0/FUN_00bb1b80
// are __stdcall.
#include "types.h"
#include <new>
#include <stddef.h>

typedef unsigned int  uint;
typedef unsigned char uchar;

// ---- shared types (mirroring the neighbouring slice s00bb4f30) --------------
struct Vector3 { float x, y, z; };

struct RefObj {
    virtual int  AddRef();
    virtual int  Release();
};

struct cStarRecord : RefObj {
    uchar   pad04[0x38];
    Vector3 mPosition;      // +0x3c
    uchar   pad48[0x14];
    uint    mFlags;         // +0x5c
    uchar   pad60[0x10];
    uint    mID;            // +0x70

    const Vector3& GetPosition();               // 0x005c65e0
    uint   GetFlags();                          // 0x00c87040
    void   FUN_00bb9ab0(Vector3* pos);          // 0x00bb9ab0 (thiscall, ret 4)
    void   FUN_00bb9ad0(int v);                 // 0x00bb9ad0 (thiscall, ret 4)
    void   FUN_00bb9b00(uint mask, int on);     // 0x00bb9b00 (thiscall, ret 8)
    void*  FUN_00bbaa60(int v);                 // 0x00bbaa60 (thiscall, ret 4)
    void   SetRootWindowId(uint id);            // 0x00c87bc0 (thiscall, ret 4)
};
cStarRecord* cStarRecord_ctor(cStarRecord* self);   // 0x00bba130

template <class T> struct AutoRefCount {
    T* mpObject;
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    AutoRefCount(const AutoRefCount& x) : mpObject(x.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
};

struct sp_vector_allocator { uint mData[2]; };
inline void SpFree(void* p) { if (((uint*)p)[-1] != 0) operator delete[](p); }

typedef AutoRefCount<cStarRecord> StarRef;

// eastl::vector<AutoRefCount<cStarRecord>, sp_vector_allocator> -- 0x14 bytes.
struct StarVector {
    StarRef* mpBegin;
    StarRef* mpEnd;
    StarRef* mpCapacity;
    sp_vector_allocator mAllocator;

    StarVector() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~StarVector()
    {
        for (StarRef* p = mpBegin; p < mpEnd; ++p) p->~StarRef();
        if (mpBegin) SpFree(mpBegin);
    }
    void DoInsertValue(StarRef* pos, const StarRef& v);      // 0x00aea5d0 (ret 8)
    void push_back(const StarRef& v)
    {
        if (mpEnd < mpCapacity) ::new ((void*)mpEnd++) StarRef(v);
        else DoInsertValue(mpEnd, v);
    }
    void resize(uint n);                                     // 0x00bb6740
};

// eastl::vector<Vector3> -- 0xc-byte elements (civ city positions).
struct Vec3Vec {
    Vector3* mpBegin;
    Vector3* mpEnd;
    Vector3* mpCapacity;
    sp_vector_allocator mAllocator;
    Vec3Vec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void DoInsertValue(Vector3* pos, const Vector3& v);      // 0x004b5ad0
    void push_back(const Vector3& v)
    {
        if (mpEnd < mpCapacity) *mpEnd++ = v;
        else DoInsertValue(mpEnd, v);
    }
};

// A 0x14-byte element (one star-record grid row) and a vector of them; the
// vector itself also carries the 2-dword eastl allocator (0x14 bytes total).
struct Row14 { uint d[5]; };
struct VecRows {
    Row14* mpBegin;
    Row14* mpEnd;
    Row14* mpCapacity;
    sp_vector_allocator mAllocator;
    VecRows() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~VecRows();                                              // 0x00ae6970
    void resize(uint n);                                     // 0x00bb6740
};

// ---- allocator / operators -------------------------------------------------
void* operator new(size_t, const char* name, int flags, unsigned dbg, const char* file, int line);
void  operator delete[](void* p);                            // 0x00f47380
void* EAAllocate(uint size, const char* name, int a, int b, int c, int d);  // 0x00f473a0

// ---- EA random singleton ---------------------------------------------------
struct EALCG {
    double RandomDoubleUniform();                            // 0x009360d0
    uint   RandomUint32Uniform(uint n);                      // 0x00a68fb0
};

// ---- free callees ----------------------------------------------------------
void* ObjectTemplateDB();                                    // 0x0067cb40
void* SP_GetSaveArea(uint id);                               // 0x006b1f90
void* MessageServer();                                       // 0x0067dcc0
void* GetManager();                                          // 0x0067dcd0
void* FUN_00f48a80();                                        // 0x00f48a80
void  FUN_004010a0();                                        // 0x004010a0
char  FUN_00c8b520(int mode);                                // 0x00c8b520
void  FUN_00b3d360();                                        // 0x00b3d360
void  FUN_00b7dec0();                                        // 0x00b7dec0
void  FUN_00c34140(void* node);                              // 0x00c34140
void  FUN_00a16a90(int v);                                   // 0x00a16a90
void  FUN_00bbac80(cStarRecord* rec, int v);                 // 0x00bbac80
void  FUN_00ba8340(void* a, void* b);                        // 0x00ba8340
void  FUN_00c77a00(int v);                                   // 0x00c77a00
void* FUN_00baa8b0(void* a, void* b, void* c);               // 0x00baa8b0
void  FUN_00bb14a0(void* self, StarVector* out);             // 0x00bb14a0
void  FUN_00bb1df0(void* self, StarVector* out);             // 0x00bb1df0
void  __stdcall FUN_00bb1bd0(void* end, uint n, VecRows& tmp);  // 0x00bb1bd0
void  __stdcall FUN_00bb1b80(void* first, void* last);       // 0x00bb1b80

// eastl string-ish 3-dword local.
struct EString3 { wchar_t* mpBegin; wchar_t* mpEnd; wchar_t* mpCap; };
void RangeInitialize(EString3* self, const wchar_t* s);      // 0x00579a90
bool RemoveDirectoryRecursive(const wchar_t* dir, int force); // 0x00932890
bool CreateDirectoryPath(const wchar_t* dir);                // 0x00932960

// ---- vtable helper ---------------------------------------------------------
struct IVtbl { void* slot[0x40]; };
#define VSLOT(o, off) (((IVtbl*)*(void**)(o))->slot[(off) / 4])

// ---- globals ---------------------------------------------------------------
extern uint  g_1689650;      // 0x01689650
extern uchar g_1689648;      // 0x01689648
extern uint  g_156c518;      // 0x0156c518
extern uint  g_156c508;      // 0x0156c508
extern float g_13eb960;      // 0x013eb960  (0.01f)
extern uint  g_1601760;      // 0x01601760  (EA random LCG singleton)

// ---------------------------------------------------------------------------
// cStarManager
// ---------------------------------------------------------------------------
struct cStarManager {
    // thiscall helpers (ecx = this).
    void FUN_00ba7100(Vector3* pos, int* out1, int* out2);   // 0x00ba7100
    char FUN_00bb9af0(cStarRecord* rec, int v);              // 0x00bb9af0
    void FUN_00ba8830(cStarRecord* rec);                     // 0x00ba8830
    cStarRecord* FUN_00bb3c70();                             // 0x00bb3c70
    char FUN_00bb2330(cStarRecord* rec, int v);              // 0x00bb2330
    cStarRecord* FUN_00bb3800(int v);                        // 0x00bb3800
    void FUN_00bb23e0();                                     // 0x00bb23e0
    void FUN_00bac620(int v);                                // 0x00bac620
    void FUN_00bb4ba0();                                     // 0x00bb4ba0
    void FUN_00bb59b0(void* a, int b);                       // 0x00bb59b0
    void FUN_00bb6700(cStarRecord* rec, int arg2);           // 0x00bb6700
    void FUN_00bac150();                                     // 0x00bac150
    void FUN_00b96130(void* a, void* b, void* rnd);          // 0x00b96130
};

// raw field accessors (avoid modelling every offset).
#define F(sm, off) (*(uint*)((char*)(sm) + (off)))
#define P(sm, off) (*(void**)((char*)(sm) + (off)))
#define PV(sm, off) (*(void***)((char*)(sm) + (off)))

// ---------------------------------------------------------------------------
// 0x00bb5d80 -- populate a grid cell with a new cStarRecord per input element.
// ---------------------------------------------------------------------------
struct StarInput { int count; int pad; char* items; };  // [0]=count, [2]=items

// @ 0x00bb5d80
bool __cdecl FUN_00bb5d80(uint unused, StarInput* p, int mode)
{
    (void)unused;
    int count = p->count;
    char* items = p->items;
    if (count <= 0) { g_1689650 += count; return true; }

    cStarManager* sm = ((cStarManager* (__cdecl*)())0x00b3d2a0)();
    FUN_004010a0();
    float rr = *(float*)((char*)sm + 0x1bc) * *(float*)((char*)sm + 0x1bc);
    char flag = FUN_00c8b520(mode);
    float scale = (float)*(int*)((char*)sm + 0x1c4) * g_13eb960;

    char* ebx = items + 0xc;
    int rem = count;
    do {
        Vector3 pos;
        pos.x = *(float*)(ebx - 8);
        pos.y = *(float*)(ebx - 4);
        pos.z = *(float*)(ebx);
        int outA, outB;
        sm->FUN_00ba7100(&pos, &outB, &outA);

        cStarRecord* rec = (cStarRecord*)EAAllocate(0xb0, "Simulator/cStarRecord", 0, 0, 0, 0);
        rec = rec ? cStarRecord_ctor(rec) : 0;

        rec->FUN_00bb9ab0(&pos);
        rec->SetRootWindowId((uint)mode);

        if (flag != 0) {
            if (scale > ((EALCG*)0x1601760)->RandomDoubleUniform()) rec->FUN_00bb9b00(0x1000, 1);
        }

        if (mode == 2) {
            StarRef local(rec);
            ((StarVector*)((char*)sm + 0x104))->push_back(local);
        } else if (flag != 0) {
            rec->FUN_00bb9ad0(1);
            float d2 = pos.x * pos.x + pos.y * pos.y + pos.z * pos.z;
            if (d2 > rr) rec->FUN_00bb9ad0((int)sm->FUN_00bb3800(1));
        }

        // append to the grid row (outA*0x40 + outB) and set the record id.
        StarVector* row = (StarVector*)((char*)P(sm, 0xc8) + (outA * 0x40 + outB) * 0x14);
        int cnt = (int)((char*)row->mpEnd - (char*)row->mpBegin) >> 2;
        int oA2, oB2;
        sm->FUN_00ba7100(&pos, &oB2, &oA2);
        rec->mID = ((uint)(oA2 * 0x40 + oB2) << 12) + (uint)cnt;
        row->push_back(StarRef(rec));

        ebx += 0x4c;
    } while (--rem);

    g_1689650 += (uint)count;
    return true;
}

// ---------------------------------------------------------------------------
// 0x00bb6040 -- rebuild the civ/star tables for the current galaxy.
// ---------------------------------------------------------------------------
// @ 0x00bb6040
void __fastcall FUN_00bb6040(cStarManager* self)
{
    self->FUN_00bb23e0();
    if (P(self, 0xa0) == P(self, 0xa4)) self->FUN_00bac620(0);
    if (P(self, 0xa0) != P(self, 0xa4)) {
        Vec3Vec civs;
        int missing = 0;
        uint n = (uint)((char*)P(self, 0xe0) - (char*)P(self, 0xdc)) >> 2;
        for (uint i = 0; i < n; ++i) {
            cStarRecord* civ = (cStarRecord*)PV(self, 0xdc)[i];
            const Vector3* c = ((const Vector3* (__cdecl*)(void*))0x005c65e0)(civ);
            civs.push_back(*c);
            if (!self->FUN_00bb9af0(civ, 2)) ++missing;
        }
        int have = (int)((char*)P(self, 0xf4) - (char*)P(self, 0xf0)) >> 2;
        int total = have + missing;
        if (total < (int)g_156c518) {
            int room = (int)g_156c508 - missing;
            if (room > 0) {
                if (room > (int)g_156c518 - total) room = (int)g_156c518 - total;
                self->FUN_00b96130(P(self, 0x118), P(self, 0x11c), &g_1601760);
                bool changed = false;
                for (int k = 0; k < room; ++k) {
                    cStarRecord* rec = 0;
                    int idx = 0;
                    while ((uint)idx < ((char*)P(self, 0x11c) - (char*)P(self, 0x118)) >> 2) {
                        rec = (cStarRecord*)PV(self, 0x118)[idx];
                        ++idx;
                        if (!self->FUN_00bb2330(rec, 0)) { rec = 0; continue; }
                        if (rec != 0) break;
                    }
                    if (g_1689648 == 0 && rec == 0) rec = self->FUN_00bb3c70();
                    if (rec != 0) {
                        rec->FUN_00bb9ad0(0);
                        rec->FUN_00bb9b00(1, 1);
                        FUN_00a16a90(-1);
                        if (P(self, 0xa0) == P(self, 0xa4)) self->FUN_00bac620(0);
                        if (P(self, 0xa0) != P(self, 0xa4)) {
                            uint r = ((EALCG*)0x1601760)->RandomUint32Uniform(
                                (uint)((char*)P(self, 0xa4) - (char*)P(self, 0xa0)) >> 2);
                            FUN_00bbac80((cStarRecord*)PV(self, 0xa0)[r], 0);
                            PV(self, 0xa0)[r] = PV(self, 0xa4)[-1];
                            P(self, 0xa4) = (char*)P(self, 0xa4) - 4;
                        }
                        civs.push_back(rec->GetPosition());
                        self->FUN_00ba8830(rec);
                        changed = true;
                    }
                }
                if (P(self, 0xa0) == P(self, 0xa4)) self->FUN_00bac620(0);
                if (changed && *(uchar*)((char*)self + 0x64) == 0) {
                    self->FUN_00bb4ba0();
                    void* ms = MessageServer();
                    ((void (__fastcall*)(void*, int, int, int, int))VSLOT(ms, 0x18))(ms, 0, 0, 0, 0x62d91c2);
                }
            }
        }
    }
}

// ---------------------------------------------------------------------------
// 0x00bb6390 -- tear the manager's container members down (dtor body).
// ---------------------------------------------------------------------------
// @ 0x00bb6390
void __fastcall FUN_00bb6390(cStarManager* self)
{
    FUN_00b3d360();
    FUN_00b7dec0();
    for (void* it = P(self, 0x158); it != (char*)self + 0x154;
         it = ((void* (__cdecl*)(void*))0x00921580)(it)) {
        FUN_00c34140(*(void**)((char*)it + 0x14));
    }
    ((void (__fastcall*)(void*, int))0x00d0c930)((char*)self + 0x154, 0);
    P(self, 0x154) = (char*)self + 0x154;
    P(self, 0x158) = (char*)self + 0x154;
    F(self, 0x15c) = 0;
    *(uchar*)((char*)self + 0x160) = 0;
    F(self, 0x164) = 0;

    {
        void* e = P(self, 0x54);
        void* b = P(self, 0x50);
        ((void (__cdecl*)(void*, void*, int))0x011e0744)(b, e, 0);
        P(self, 0x54) = (char*)e + ((int)((char*)e - (char*)b) >> 2) * -4;
    }

    for (void* nd = P(self, 0x2c); nd != 0; ) {
        void* next = *(void**)((char*)nd + 4);
        ((void (__fastcall*)(void*, int))0x009a9600)(nd, 0);
        operator delete[](nd);
        nd = next;
    }
    P(self, 0x24) = (char*)self + 0x24;
    P(self, 0x28) = (char*)self + 0x24;
    F(self, 0x2c) = 0;
    *(uchar*)((char*)self + 0x30) = 0;
    F(self, 0x34) = 0;

    ((void (__cdecl*)(void*, void*))0x00e25bd0)(P(self, 0xdc), P(self, 0xe0));

    ((void (__fastcall*)(void*, int))0x00d0c930)((char*)self + 0x12c, 0);
    P(self, 0x12c) = (char*)self + 0x12c;
    P(self, 0x130) = (char*)self + 0x12c;
    F(self, 0x134) = 0;
    *(uchar*)((char*)self + 0x138) = 0;
    F(self, 0x13c) = 0;
    ((void (__cdecl*)(void*, void*))0x00e25bd0)(P(self, 0xf0), P(self, 0xf4));
    ((void (__cdecl*)(void*, void*))0x00e25bd0)(P(self, 0x104), P(self, 0x108));
    ((void (__cdecl*)(void*, void*))0x00e25bd0)(P(self, 0x118), P(self, 0x11c));

    for (void* nd = P(self, 0x190); nd != 0; ) {
        void* next = *(void**)((char*)nd + 4);
        ((void (__fastcall*)(void*, int))0x009a9600)(nd, 0);
        operator delete[](nd);
        nd = next;
    }
    P(self, 0x184) = (char*)self + 0x184;
    P(self, 0x188) = (char*)self + 0x184;
    F(self, 0x18c) = 0;
    *(uchar*)((char*)self + 0x190) = 0;
    F(self, 0x194) = 0;

    self->FUN_00bac150();

    {
        char* end = (char*)P(self, 0xcc);
        char* beg = (char*)P(self, 0xc8);
        while (beg != end) {
            ((void (__fastcall*)(void*, char*))0x01011cc0)(self, beg);
            beg += 0x14;
        }
        FUN_00ba8340(beg, end);
    }

    void* r224 = P(self, 0x224);
    if (r224) {
        ((void (__fastcall*)(void*, int))VSLOT(r224, 0x1c))(r224, 0);
        void* rm = GetManager();
        ((void (__fastcall*)(void*, int, void*, int))VSLOT(rm, 0x50))(rm, 0, r224, 1000);
        ((void (__fastcall*)(void*, int))VSLOT(r224, 0x8))(r224, 0);
        if (r224) { P(self, 0x224) = 0; ((void (__fastcall*)(void*, int))VSLOT(r224, 0x4))(r224, 0); }
    }
    void* r228 = P(self, 0x228);
    if (r228) {
        ((void (__fastcall*)(void*, int))VSLOT(r228, 0x1c))(r228, 0);
        void* rm = GetManager();
        ((void (__fastcall*)(void*, int, void*, int))VSLOT(rm, 0x50))(rm, 0, r228, 1000);
        ((void (__fastcall*)(void*, int))VSLOT(r228, 0x8))(r228, 0);
        if (r228) { P(self, 0x228) = 0; ((void (__fastcall*)(void*, int))VSLOT(r228, 0x4))(r228, 0); }
    }
    void* g = FUN_00f48a80();
    ((void (__fastcall*)(void*, int))VSLOT(g, 0x1c))(g, 0);
}

// ---------------------------------------------------------------------------
// 0x00bb6650 -- SP::cAppModeEditorBase::Redo
// ---------------------------------------------------------------------------
// @ 0x00bb6650
bool __fastcall cAppModeEditorBase_Redo(cStarManager* self)
{
    void* db = ObjectTemplateDB();
    ((void (__fastcall*)(void*, int))VSLOT(db, 0x68))(db, 0);
    FUN_00bb6390(self);
    void* sa = SP_GetSaveArea(0x04729a47);
    void* name = ((void* (__fastcall*)(void*, int))VSLOT(sa, 0x28))(sa, 0);
    EString3 tmp;
    RangeInitialize(&tmp, (const wchar_t*)name);
    bool ok = false;
    if (RemoveDirectoryRecursive(tmp.mpBegin, 1)) {
        if (CreateDirectoryPath(tmp.mpBegin)) ok = true;
    }
    if ((((char*)tmp.mpEnd - (char*)tmp.mpBegin) & ~1u) > 2 && tmp.mpBegin)
        operator delete[](tmp.mpBegin);
    return ok;
}

// ---------------------------------------------------------------------------
// 0x00bb6700 -- activate/select a planet record.
// ---------------------------------------------------------------------------
// @ 0x00bb6700
void cStarManager::FUN_00bb6700(cStarRecord* rec, int arg2)
{
    if (*(uchar*)((char*)rec + 0xac) == 0)
        FUN_00ba8830(rec);
    void* v = rec->FUN_00bbaa60(0);
    FUN_00bb59b0(v, arg2);
}

// ---------------------------------------------------------------------------
// 0x00bb6740 -- VecRows::resize(uint).
// ---------------------------------------------------------------------------
// @ 0x00bb6740
void VecRows::resize(uint n)
{
    if (n > (uint)(mpEnd - mpBegin)) {
        VecRows tmp;
        FUN_00bb1bd0(mpEnd, n - (uint)(mpEnd - mpBegin), tmp);
    } else {
        FUN_00bb1b80(mpBegin + n, mpEnd);
    }
}

// ---------------------------------------------------------------------------
// 0x00bb67d0 -- deserialize a list of star-record rows.
// ---------------------------------------------------------------------------
// @ 0x00bb67d0
void __cdecl FUN_00bb67d0(cStarManager* self, StarVector* rows)
{
    StarRef* beg = rows->mpBegin;
    StarRef* end = rows->mpEnd;
    void* r = FUN_00baa8b0(end, end, beg);
    FUN_00ba8340(r, rows->mpEnd);
    int delta = (int)((char*)end - (char*)beg) / 0x14;
    rows->mpEnd = (StarRef*)((char*)rows->mpEnd - delta * 0x14);

    int count = 0;
    void* io = ((void* (__fastcall*)(void*, int))VSLOT(self, 0x20))(self, 0);
    void* rd = ((void* (__fastcall*)(void*, int))VSLOT(io, 0x18))(io, 0);
    ((void (__cdecl*)(void*, int*, int, int))0x0093a780)(rd, &count, 1, 0);
    FUN_00c77a00(count);

    for (int i = 0; i < count; ++i) {
        StarVector tmp;
        FUN_00bb14a0(self, &tmp);
        if (rows->mpEnd < rows->mpCapacity) {
            void** slot = (void**)rows->mpEnd;
            rows->mpEnd = (StarRef*)(slot + 5);
            if (slot) {
                int n2 = (int)((char*)tmp.mpEnd - (char*)tmp.mpBegin) >> 2;
                void* mem = n2 ? EAAllocate((uint)(n2 * 4), "Simulator", 0, 0, 0, 0) : 0;
                slot[0] = mem;
                slot[1] = mem;
                slot[2] = (char*)mem + n2 * 4;
            }
        } else {
            FUN_00bb1df0(self, &tmp);
        }
        for (StarRef* p = tmp.mpBegin; p < tmp.mpEnd; ++p)
            if (p->mpObject) p->mpObject->Release();
        if (tmp.mpBegin && ((uint*)tmp.mpBegin)[-1] != 0) operator delete[](tmp.mpBegin);
    }
    ((void (__fastcall*)(void*, int))VSLOT(self, 0x1c))(self, 0);
}
