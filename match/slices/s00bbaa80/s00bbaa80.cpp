// match/slices/s00bbaa80/s00bbaa80.cpp
// Object file: SPStarManager/SPStarSearch.obj (VS2008 SP1).
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /Isrc/game/include
//
// cStarManager star-search helpers: the star/planet key index table, the
// measure/merge group passes over the star-record grid, the star record
// allocation helpers and the grid reset.  Local stub structs carry the retail
// field offsets the disassembly shows.

#include "types.h"

#pragma warning(disable: 4100)

// ---------------------------------------------------------------------------
// unnamed callees (address in the comment)
// ---------------------------------------------------------------------------
void* GetManager();                                    // 0x67dcd0 EA::ResourceMan::GetManager
void* FUN_00b3d2a0();                                  // 0xb3d2a0 SP::StarManager
void  FUN_00b8dd60(void* self, void* out);             // 0xb8dd60 (thiscall)
void  FUN_00b8dde0(void* self, void* key3);            // 0xb8dde0 (thiscall, ret 8)
void* FUN_00f48a80();                                  // 0xf48a80
void  FUN_00ba8010(void* self, void* out, int x);      // 0xba8010 (thiscall, ret 8)
void  FUN_00ba6660(void* star);                        // 0xba6660
void* EAAllocate(unsigned size, const char* pool, int a, int b, int c, int d); // 0xf473a0
void  __cdecl operator_delete(void* p);                // 0xf47380
void  __cdecl FUN_00454cb0(void*, void*);              // 0x454cb0 eastl::basic_string<char>::assign
int   __cdecl FUN_00472fe0(void*, const char*, ...);   // 0x472fe0 eastl::basic_string<char>::sprintf
void* __cdecl FUN_0093c570(void* out, void* self, int* x); // 0x93c570 EA::ConvertToString8
void* __cdecl FUN_00618890(void* out, void* rhs);      // 0x618890 eastl::operator+
int   __cdecl qsort(void*, unsigned, unsigned, int(__cdecl*)(const void*, const void*));

// The star key-index map: EASTL vector of 8-byte {key, value} records.
struct StarIndex {
    int   mCount;   // +0x08
    int*  mData;    // +0x0c
    void Remove(int* a, int* b);   // 0xbbb060
};
void FUN_00bbb060(StarIndex* self, int* a, int* b);    // 0xbbb060

// ---------------------------------------------------------------------------
// cStarManager -> SP::cStarRecord (0xbb9e00 reads retail +0x58 and passes
// param_1+0x60 as the 3rd sprintf argument, matching the PDB name field).
// ---------------------------------------------------------------------------
struct cStarRecord {
    char       pad_0000[0x08];
    uint32_t   fields_08;   // +0x08
    uint32_t   fields_0c;   // +0x0c
    uint32_t   fields_10;   // +0x10
    uint32_t   fields_14;   // +0x14
    uint32_t   fields_18;   // +0x18
    uint32_t   fields_1c;   // +0x1c
    uint32_t   fields_20;   // +0x20
    uint32_t   fields_24;   // +0x24
    uint32_t   fields_28;   // +0x28
    uint32_t   fields_2c;   // +0x2c
    char       pad_0030[0x30];
    uint32_t   key_60;      // +0x60
    uint32_t   key_64;      // +0x64
    uint32_t   key_68;      // +0x68
};

struct cStarManager {
    char      pad_0000[0x58];
    cStarRecord* mStar;         // +0x58
    uint32_t  mFlags;           // +0x5c
    uint32_t  unk_60;           // +0x60
    uint32_t  unk_64;           // +0x64
    uint32_t  unk_68;           // +0x68
    char      pad_006c[0x84 - 0x6c];
    cStarRecord** mGrid;        // +0x84 grid vector begin
    uint32_t  pad_0088;
    char      pad_008c[0xac - 0x8c];
    uint8_t   mMeasureFlag;     // +0xac

    bool Measure(cStarRecord* key);
    void SetStar(cStarRecord* key);
};

// ===========================================================================
// @ 0x00bbaa80  cStarManager::Measure(cStarRecord*) : __thiscall, ret 4
//
// Compares the manager's cached star measurement against a candidate record:
// on a mismatch it builds two 12-byte keys, formats a diagnostic string and
// refreshes the cached star.
// ===========================================================================
bool cStarManager::Measure(cStarRecord* key)
{
    if (mMeasureFlag == 0)
        return true;

    FUN_00ba6660(mStar);

    cStarRecord* cur = *mGrid;
    if (cur == 0 || *(char*)((char*)cur + 0x130) == 0)
        return true;

    int cached;
    FUN_00b8dd60(this, &cached);
    int measured = (int)key;
    bool equal = (cached == measured);
    if (equal)
        return equal;

    // string stub (EASTL basic_string<wchar_t> built from the shared empty
    // buffer at 0x01667bac); the byte layout is 3 pointers, matching retail.
    struct WStr {
        uint32_t mpBegin;
        uint32_t mpEnd;
        uint32_t mpCap;
    };
    WStr a;
    a.mpBegin = 0x01667bac; a.mpEnd = 0x01667bac; a.mpCap = 0x01667bae;

    void* mgr = GetManager();
    (*(void(__thiscall**)(void*, int*, WStr*))(*(uint32_t**)mgr + 0x1f))(mgr, &cached, &a);

    int vals[3];
    vals[0] = measured;
    FUN_00f48a80();
    void* mgr2 = GetManager();
    (*(void(__thiscall**)(void*, int*, WStr*))(*(uint32_t**)mgr2 + 0x1f))(mgr2, &vals[1], &a);

    void* out;
    FUN_00b3d2a0();
    FUN_00ba8010(this, &out, measured);

    struct WStr8 {
        uint32_t mpBegin;
        uint32_t mpEnd;
        uint32_t mpCap;
    };
    WStr8 s;
    {
        // basic_string<char> pool buffer; the literal is the format string.
        char fmt[] = " failed consistency check (0x%08x - 0x%08x)!\n";
        s.mpBegin = (uint32_t)(int)" failed consistency check (0x%08x - 0x%08x)!\n";
        s.mpEnd = s.mpBegin + sizeof(fmt) - 1;
        s.mpCap = s.mpBegin + sizeof(fmt);
    }
    FUN_00472fe0(&s, " failed consistency check (0x%08x - 0x%08x)!\n", measured, cached);

    // EA::ConvertToString8 + eastl::operator+ build the reported string.
    struct WStr16 { uint32_t a, b, c; };
    WStr16 wide;
    wide.a = measured; wide.b = cached; wide.c = 0;
    char* conv = (char*)FUN_0093c570(&wide, (char*)this + 0x60, (int*)&s);
    operator_delete(0);
    operator_delete(0);
    FUN_00454cb0(conv, *(void**)(conv + 4));

    // refresh the cached star with the freshly measured value
    void* out2;
    FUN_00b3d2a0();
    FUN_00ba8010(this, &out2, measured);

    operator_delete(0);
    return equal;
}

// ===========================================================================
// @ 0x00bbac80  cStarManager::SetStar(cStarRecord*) : __thiscall, ret 8
// ===========================================================================
void cStarManager::SetStar(cStarRecord* key)
{
    if (key == mStar)
        return;

    if (mMeasureFlag != 0 && ((mFlags >> 0xf) & 1) == 0) {
        FUN_00ba6660(mStar);
        cStarRecord* cur = *mGrid;
        void* out;
        FUN_00b3d2a0();
        FUN_00ba8010(this, &out, (int)key);
        FUN_00b8dde0(cur, &out);
    }
    mStar = key;
}

// ===========================================================================
// @ 0x00bbace0  int __cdecl(const void*, const void*) : qsort comparator
// ===========================================================================
int __cdecl StarSortCmp(const void* a, const void* b)
{
    float fa = *(const float*)((const char*)a + 4);
    float fb = *(const float*)((const char*)b + 4);
    if (fb > fa)
        return -1;
    return 1;
}

// ===========================================================================
// @ 0x00bbad00  star grid row destroy (2 sub-vectors)
// ===========================================================================
void StarGridRow2(uint32_t* self)
{
    uint32_t* p = self + 9;
    int n = 2;
    do {
        operator_delete((void*)*p);
        ++p;
        --n;
    } while (n != 0);
    operator_delete((void*)self[5]);
    operator_delete((void*)self[3]);
    operator_delete(self);
}

// ===========================================================================
// @ 0x00bbad50  star grid row destroy (3 sub-vectors)
// ===========================================================================
void StarGridRow3(uint32_t* self)
{
    uint32_t* p = self + 9;
    int n = 3;
    do {
        operator_delete((void*)*p);
        ++p;
        --n;
    } while (n != 0);
    operator_delete((void*)self[5]);
    operator_delete((void*)self[3]);
    operator_delete(self);
}

// ===========================================================================
// @ 0x00bbada0  merge two sorted star/planet key lists into an output array
// ===========================================================================
int StarGridMerge(void* self, int* src, int srcCount, int* sorted, int sortedCount,
                  int* outRecs, int slot)
{
    qsort(sorted, sortedCount, 8, StarSortCmp);

    struct Rec { short word_0; short idx; float measure; };
    uint32_t* write = (uint32_t*)((char*)self + 0x5c);
    uint32_t* listEnd = (uint32_t*)((char*)self + 0x88);
    int* listCur = (int*)((char*)self + 0x60);

    Rec* a = (Rec*)src;
    Rec* b = (Rec*)sorted;
    int si = 0, ti = 0;
    int na = 0, nb = 0;
    int count = 0;
    int oi = 0;

    for (;;) {
        while (na != nb) {
            if (si == srcCount)
                break;
            if (a->word_0 == (short)-2) { ++si; ++a; continue; }
            if (si == srcCount) break;
            if (a->word_0 == (short)-2) { ++si; ++a; continue; }
            if (b->measure > a->measure) break;
            goto ADJUST_A;
        }

        if (si == srcCount) {
            if (ti == sortedCount) return count;
            if (b->word_0 == (short)-2) {
                ++ti;
                ++b;
                continue;
            }
        } else {
            if (a->word_0 == (short)-2) { ++si; ++a; continue; }
            if (ti != sortedCount) {
                if (b->word_0 == (short)-2) { ++ti; ++b; continue; }
                if (b->measure <= a->measure) goto ADJUST_A;
            }
            if (oi == count) {
                ++oi; ++ti; ++si; ++b; ++a;
                continue;
            }
            *write = *(uint32_t*)a;
            write[1] = ((uint32_t*)a)[1];
            ++oi; write += 2; ++ti; ++a;
            goto TAIL;
        }

    ADJUST_A:
        if (oi == count && oi < srcCount) {
            ++oi;
            if (a->word_0 != (short)-2) {
                ++nb;
                *listCur = *(int*)a;
                listCur[1] = ((int*)a)[1];
                listCur += 2;
            }
            ++a;
        }
        ++na;
        *write = *(uint32_t*)b;
        write[1] = ((uint32_t*)b)[1];
        ++ti; write += 2; ++b;
        goto TAIL;

    TAIL:
        {
            Rec* last = (Rec*)(write - 2);
            int base = *((int*)((char*)self + 0x14));
            base += last->idx * 16;
            int idx = oi - 1;
            if (last->word_0 == 0)
                *(short*)(base + 8 + slot * 2) = (short)idx;
            else
                *(short*)(base + 0xc + slot * 2) = (short)idx;
            ++count;
        }
    }
}

// ===========================================================================
// @ 0x00bbafa0  compare two star/planet measures at slot index 0
// ===========================================================================
bool StarGridSlotCmp0(void* self, unsigned slot, int* a, int* b)
{
    if (a[1] == b[1] && a[1] != 0)
        return false;

    short* pb = (short*)b;
    short* pa = (short*)a;
    for (unsigned i = 0; i < 2; ++i) {
        (void)self;
        if (i == slot)
            continue;
        if (!(pb[4 + i] <= pa[6 + i] && pa[4 + i] <= pb[6 + i]))
            return false;
    }
    return true;
}
// ===========================================================================
// @ 0x00bbb000  compare two star/planet measures at slot index 1
// ===========================================================================
bool StarGridSlotCmp1(void* self, unsigned slot, int* a, int* b)
{
    if (a[1] == b[1] && a[1] != 0)
        return false;

    short* pb = (short*)b;
    short* pa = (short*)a;
    for (unsigned i = 0; i < 3; ++i) {
        (void)self;
        if (i == slot)
            continue;
        if (!(pb[4 + i] <= pa[6 + i] && pa[4 + i] <= pb[6 + i]))
            return false;
    }
    return true;
}
// ===========================================================================
// @ 0x00bbb060  star index table remove(pair)
// ===========================================================================
void StarIndex_Remove(int* a, int* b)
{
    int lo = *a;
    int hi = *b;
    if (lo >= hi) { int t = lo; lo = hi; hi = t; }

    StarIndex* self = (StarIndex*)0;
    int n = self->mCount;
    if (n <= 0)
        return;

    int* p = self->mData;
    int i = 0;
    while (p[0] != lo || p[1] != hi) {
        ++i;
        p += 2;
        if (i >= n)
            return;
    }
    --n;
    self->mCount = n;
    p[0] = self->mData[n * 2];
    p[1] = self->mData[n * 2 + 1];
    self->mData[n * 2] = -1;
}

// ===========================================================================
// @ 0x00bbb0e0  grid table reset
// ===========================================================================
void StarGridResetFields(uint32_t* self)
{
    self[0x2c / 4] = 0;
    self[0x20 / 4] = 0;
    self[0x08 / 4] = 0;
    self[0x10 / 4] = 0;
    self[0x18 / 4] = 0;
}

// ===========================================================================
// @ 0x00bbb110  count getter
// ===========================================================================
int StarGridCount(uint32_t* self)
{
    return (int)self[2] - 1;
}

// ===========================================================================
// @ 0x00bbb120  grid insert: one record at a free slot plus four edge entries
// ===========================================================================
void StarGridInsert(void* p, int a2, float* pa, float* pb, int a5)
{
    uint32_t* self = (uint32_t*)p;
    uint32_t slot;

    if (self[4] == self[6]) {
        self[6] = self[6] + 1;
        slot = self[4];
        self[4] = slot + 1;
    } else {
        slot = self[7];
        uint32_t next = *(uint32_t*)(slot * 16 + self[5]);
        self[4] = self[4] + 1;
        self[7] = next;
    }

    uint32_t* rec = (uint32_t*)(slot * 16 + self[5]);
    rec[0] = a2;
    rec[1] = a5;

    uint32_t base = self[0xb];
    uint32_t m = self[0xc];
    int i0 = (int)slot;
    int i1 = i0 + 1;

    *(short*)(m + i0 * 8 + 0) = 0;
    *(short*)(m + i0 * 8 + 2) = (short)slot;
    *(float*)(m + i0 * 8 + 4) = *pa;
    *(short*)(m + i0 * 8 + 0xa) = (short)slot;
    *(short*)(m + i1 * 8 + 0) = 1;
    *(float*)(m + i1 * 8 + 4) = *pb;

    uint32_t e0 = slot | 0xffff8000u;
    *(uint16_t*)(rec + 2) = (uint16_t)e0;
    uint32_t e1 = (uint32_t)i1 | 0xffff8000u;
    *(uint16_t*)(rec + 3) = (uint16_t)e1;

    uint32_t base2 = self[0xd];
    *(short*)(base2 + i0 * 8 + 0) = 0;
    *(short*)(base2 + i0 * 8 + 2) = (short)slot;
    *(float*)(base2 + i0 * 8 + 4) = pa[1];
    *(short*)(base2 + i1 * 8 + 0) = 1;
    *(short*)(base2 + i1 * 8 + 2) = (short)slot;
    *(float*)(base2 + i1 * 8 + 4) = pb[1];

    *(uint16_t*)((char*)rec + 10) = (uint16_t)e0;
    *(uint16_t*)((char*)rec + 14) = (uint16_t)e1;

    self[0xb] = self[0xb] + 2;
}

// ===========================================================================
// @ 0x00bbb210  grid erase: clear the four edges and free the slot
// ===========================================================================
void StarGridErase(uint32_t* self, int slot)
{
    uint32_t off = (uint32_t)slot * 16;
    uint32_t* rec = (uint32_t*)(self[5] + off);

    uint16_t i0 = *(uint16_t*)((char*)rec + 0xc);
    uint16_t i1 = *(uint16_t*)((char*)rec + 8);
    uint16_t i2 = *(uint16_t*)((char*)rec + 0xe);
    uint16_t i3 = *(uint16_t*)((char*)rec + 0xa);

    if (i0 & 0x8000u)
        *(uint16_t*)((char*)self[0xc] + (i0 & 0x7fffu) * 8) = 0xfffe;
    else
        *(uint16_t*)((char*)self[9] + (unsigned)(int)(short)i0 * 8) = 0xfffe;

    if (i1 & 0x8000u)
        *(uint16_t*)((char*)self[0xc] + (i1 & 0x7fffu) * 8) = 0xfffe;
    else
        *(uint16_t*)((char*)self[9] + (unsigned)(int)(short)i1 * 8) = 0xfffe;

    if (i2 & 0x8000u)
        *(uint16_t*)((char*)self[0xa] + (i2 & 0x7fffu) * 8) = 0xfffe;
    else
        *(uint16_t*)((char*)self[0xd] + (unsigned)(int)(short)i2 * 8) = 0xfffe;

    if (i3 & 0x8000u)
        *(uint16_t*)((char*)self[0xa] + (i3 & 0x7fffu) * 8) = 0xfffe;
    else
        *(uint16_t*)((char*)self[0xd] + (unsigned)(int)(short)i3 * 8) = 0xfffe;

    rec[0] = self[7];
    rec[1] = 0xffffffffu;
    self[4] = self[4] - 1;
    self[7] = (uint32_t)slot;
}

// ===========================================================================
// @ 0x00bbb2e0  grid measure pass: merge every measure list, collect groups
// ===========================================================================
void StarGridMeasure(void* p)
{
    uint32_t* self = (uint32_t*)p;
    int i = 0;
    int r = 0;
    do {
        r = StarGridMerge(self, (int*)self[9 + i], (int)self[8], (int*)self[9 + i + 3],
                          (int)self[0xb], (int*)self[0xc], i);
        ++i;
    } while (i < 2);

    self[8] = (uint32_t)r;
    self[0xb] = 0;
    int j = 0;
    self[2] = 0;

    if ((int)self[8] <= 0)
        return;

    int active[1024];
    int nactive = 0;
    for (int k = 0; k < (int)self[8]; ++k) {
        short* rec = (short*)(self[9] + k * 8);
        int* a = (int*)(self[5] + rec[1] * 16);
        if (rec[0] == 0) {
            for (int m = 0; m < nactive; ++m) {
                int* b = (int*)(self[5] + active[m] * 16);
                if (StarGridSlotCmp0(self, 0, a, b) && self[2] != self[0]) {
                    int x = *a;
                    int y = *b;
                    int lo = (x < y) ? x : y;
                    int hi = (x < y) ? y : x;
                    int* dst = (int*)(self[3]) + self[2] * 2;
                    dst[0] = lo;
                    dst[1] = hi;
                    self[2] = self[2] + 1;
                }
            }
            active[nactive] = rec[1];
            ++nactive;
        } else {
            for (int m = 0; m < nactive; ++m) {
                if (active[m] == rec[1]) {
                    active[m] = active[nactive - 1];
                    --nactive;
                    break;
                }
            }
        }
    }
}

// ===========================================================================
// @ 0x00bbb400  star-grid table allocation (2 sub-vectors)
// ===========================================================================
uint32_t* StarGridAlloc2(uint32_t pool, uint32_t n)
{
    uint32_t* g = (uint32_t*)EAAllocate(0x38, "Simulator", 0, 0, 0, 0);
    g[0] = n;
    g[0xb] = 0;
    g[8] = 0;
    g[2] = 0;
    g[4] = 0;
    g[6] = 0;
    g[1] = pool;

    g[3] = (uint32_t)(int)EAAllocate(n * 8, "Simulator", 0, 0, 0, 0);
    g[5] = (uint32_t)(int)EAAllocate(pool * 0x10, "Simulator", 0, 0, 0, 0);

    uint32_t* p = g + 0xc;
    int k = 2;
    do {
        p[-3] = (uint32_t)(int)EAAllocate(pool * 16, "Simulator", 0, 0, 0, 0);
        p[0] = (uint32_t)(int)EAAllocate(pool * 16, "Simulator", 0, 0, 0, 0);
        ++p;
        --k;
    } while (k != 0);

    return g;
}

// ===========================================================================
// @ 0x00bbb500  star-grid table allocation (3 sub-vectors)
// ===========================================================================
uint32_t* StarGridAlloc3(uint32_t pool, uint32_t n)
{
    uint32_t* g = (uint32_t*)EAAllocate(0x40, "Simulator", 0, 0, 0, 0);
    g[0] = n;
    g[0xc] = 0;
    g[8] = 0;
    g[2] = 0;
    g[4] = 0;
    g[6] = 0;
    g[1] = pool;

    g[3] = (uint32_t)(int)EAAllocate(n * 8, "Simulator", 0, 0, 0, 0);
    g[5] = (uint32_t)(int)EAAllocate(pool * 0x14, "Simulator", 0, 0, 0, 0);

    uint32_t* p = g + 0xd;
    int k = 3;
    do {
        p[-4] = (uint32_t)(int)EAAllocate(pool * 16, "Simulator", 0, 0, 0, 0);
        p[0] = (uint32_t)(int)EAAllocate(pool * 16, "Simulator", 0, 0, 0, 0);
        ++p;
        --k;
    } while (k != 0);

    return g;
}

// ===========================================================================
// @ 0x00bbb600  grid pass: swap a record down its own measure list
// ===========================================================================
void StarGridSiftDownEq1(uint32_t* self, int slot, int index, char doCmp)
{
    uint32_t* a = (uint32_t*)(self[5] + index * 16);
    uint32_t* list = (uint32_t*)self[9 + slot];
    uint32_t* e = list + (int)(short)*(uint16_t*)((char*)a + 8 + slot * 2) * 2;
    uint32_t* prev = e - 2;

    if (prev < list)
        return;

    do {
        uint32_t* cur = e;
        if (!(*(float*)(cur + 1) < *(float*)(prev + 1)))
            return;

        uint16_t tag = *(uint16_t*)prev;
        if (tag != 0xfffeu) {
            uint32_t* other = (uint32_t*)(self[5] + (int)(short)*(uint16_t*)((char*)prev + 2) * 16);
            if (tag == 1) {
                if (doCmp &&
                    StarGridSlotCmp0(self, slot, (int*)a, (int*)other) &&
                    self[2] != self[0]) {
                    int x = (int)a[0];
                    int y = (int)other[0];
                    int lo = (x < y) ? x : y;
                    int hi = (x < y) ? y : x;
                    int* dst = (int*)(self[3] + self[2] * 8);
                    dst[0] = lo;
                    dst[1] = hi;
                    self[2] = self[2] + 1;
                }
                *(uint16_t*)((char*)other + 0xc + slot * 2) =
                    *(uint16_t*)((char*)other + 0xc + slot * 2) + 1;
            } else {
                *(uint16_t*)((char*)other + 8 + slot * 2) =
                    *(uint16_t*)((char*)other + 8 + slot * 2) + 1;
            }
        }

        *(uint16_t*)((char*)a + 8 + slot * 2) =
            *(uint16_t*)((char*)a + 8 + slot * 2) - 1;

        uint32_t t0 = cur[0], t1 = cur[1];
        cur[0] = prev[0]; cur[1] = prev[1];
        prev[0] = t0; prev[1] = t1;

        e -= 2;
        prev -= 2;
    } while (prev >= list);
}

// ===========================================================================
// @ 0x00bbb710  grid pass: swap a record up its own measure list
// ===========================================================================
void StarGridSiftUpEq0(uint32_t* self, int slot, int index, char doCmp)
{
    uint32_t count = self[8];
    uint32_t* a = (uint32_t*)(self[5] + index * 16);
    uint32_t* list = (uint32_t*)self[9 + slot];
    uint32_t* start = list + (int)(short)*(uint16_t*)((char*)a + 0xc + slot * 2) * 2;
    uint32_t* end = list + count * 2;

    uint32_t* e = start;
    for (uint32_t* p = start + 2; p < end; p += 2, e += 2) {
        if (!(*(float*)(p + 1) < *(float*)(e + 1)))
            return;

        uint16_t tag = *(uint16_t*)p;
        if (tag != 0xfffeu) {
            uint32_t* other = (uint32_t*)(self[5] + (int)(short)*(uint16_t*)((char*)p + 2) * 16);
            if (tag == 0) {
                if (doCmp &&
                    StarGridSlotCmp0(self, slot, (int*)a, (int*)other) &&
                    self[2] != self[0]) {
                    int x = (int)a[0];
                    int y = (int)other[0];
                    int lo = (x < y) ? x : y;
                    int hi = (x < y) ? y : x;
                    int* dst = (int*)(self[3] + self[2] * 8);
                    dst[0] = lo;
                    dst[1] = hi;
                    self[2] = self[2] + 1;
                }
                *(uint16_t*)((char*)other + 8 + slot * 2) =
                    *(uint16_t*)((char*)other + 8 + slot * 2) - 1;
            } else {
                *(uint16_t*)((char*)other + 0xc + slot * 2) =
                    *(uint16_t*)((char*)other + 0xc + slot * 2) - 1;
            }
        }

        *(uint16_t*)((char*)a + 0xc + slot * 2) =
            *(uint16_t*)((char*)a + 0xc + slot * 2) + 1;

        uint32_t t0 = e[0], t1 = e[1];
        e[0] = p[0]; e[1] = p[1];
        p[0] = t0; p[1] = t1;
    }
}

// ===========================================================================
// @ 0x00bbb820  grid pass: merge a freeing slot into the freeing list
// ===========================================================================
void StarGridResolveEq1(uint32_t* self, int slot, int index, char doCmp)
{
    uint32_t count = self[8];
    uint32_t* all = (uint32_t*)self[9 + slot];
    int* a = (int*)(self[5] + index * 16);
    uint32_t* e = all + count * 2;
    uint32_t* list = all + (int)(short)*(uint16_t*)((char*)a + 8 + slot * 2) * 2;

    for (uint32_t* p = list + 2; p < e; p += 2, list += 2) {
        if (!(*(float*)(p + 1) < *(float*)(list + 1)))
            return;

        uint16_t tag = *(uint16_t*)p;
        if (tag != 0xfffeu) {
            int* other = (int*)(self[5] + (int)(short)*(uint16_t*)((char*)p + 2) * 16);
            if (tag == 1) {
                if (doCmp && StarGridSlotCmp0(self, slot, a, other))
                    StarIndex_Remove(a, other);
                *(uint16_t*)((char*)other + 0xc + slot * 2) =
                    *(uint16_t*)((char*)other + 0xc + slot * 2) - 1;
            } else {
                *(uint16_t*)((char*)other + 8 + slot * 2) =
                    *(uint16_t*)((char*)other + 8 + slot * 2) - 1;
            }
        }

        *(uint16_t*)((char*)a + 8 + slot * 2) =
            *(uint16_t*)((char*)a + 8 + slot * 2) + 1;

        uint32_t t0 = list[0], t1 = list[1];
        list[0] = p[0]; list[1] = p[1];
        p[0] = t0; p[1] = t1;
    }
}

// ===========================================================================
// @ 0x00bbb900  grid pass: merge a freeing slot into the creating list
// ===========================================================================
void StarGridResolveEq0(uint32_t* self, int slot, int index, char doCmp)
{
    uint32_t* a = (uint32_t*)(self[5] + index * 16);
    uint32_t* list = (uint32_t*)self[9 + slot];
    uint32_t* e = list + (int)(short)*(uint16_t*)((char*)a + 0xc + slot * 2) * 2;
    uint32_t* prev = e - 2;

    if (prev < list)
        return;

    do {
        uint32_t* cur = e;
        if (!(*(float*)(cur + 1) < *(float*)(prev + 1)))
            return;

        uint16_t tag = *(uint16_t*)cur;
        if (tag != 0xfffeu) {
            int* other = (int*)(self[5] + (int)(short)*(uint16_t*)((char*)cur + 2) * 16);
            if (tag == 0) {
                if (doCmp && StarGridSlotCmp0(self, slot, (int*)a, other))
                    StarIndex_Remove((int*)a, other);
                *(uint16_t*)((char*)other + 8 + slot * 2) =
                    *(uint16_t*)((char*)other + 8 + slot * 2) + 1;
            } else {
                *(uint16_t*)((char*)other + 0xc + slot * 2) =
                    *(uint16_t*)((char*)other + 0xc + slot * 2) + 1;
            }
        }

        *(uint16_t*)((char*)a + 0xc + slot * 2) =
            *(uint16_t*)((char*)a + 0xc + slot * 2) - 1;

        uint32_t t0 = cur[0], t1 = cur[1];
        cur[0] = prev[0]; cur[1] = prev[1];
        prev[0] = t0; prev[1] = t1;

        e -= 2;
        prev -= 2;
    } while (prev >= list);
}
