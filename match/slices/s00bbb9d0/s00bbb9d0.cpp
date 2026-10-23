// Slice s00bbb9d0 - star-grid measure-list passes and terraforming resource-key
// helpers from SporeApp.exe (VS2008 SP1).
//
// The first block (0x00bbb9d0 .. 0x00bbc300) continues the star/planet key grid
// of slice s00bbaa80 (SPStarManager/SPStarSearch.obj): the four measure-list
// sift passes, the free-record iterator, the record allocation with its three
// edge insertions, and the grow pass.  The rest is the terraforming/planet
// resource-key group (SP::TerraformingManager and friends).

#include "types.h"

#pragma warning(disable: 4100)

// ---------------------------------------------------------------------------
// callees (address in the comment)
// ---------------------------------------------------------------------------
bool StarGridSlotCmp1(void* self, unsigned slot, int* a, int* b);   // 0xbbb000
void StarIndex_Remove(void* unused, int* a, int* b, void* self);    // 0xbbb060
void StarGridSiftDownEq1(void* self, int slot, int index, char doCmp);  // 0xbbb600
void StarGridSiftUpEq0(void* self, int slot, int index, char doCmp);    // 0xbbb710
void StarGridResolveEq1(void* self, int slot, int index, char doCmp);   // 0xbbb820
void StarGridResolveEq0(void* self, int slot, int index, char doCmp);   // 0xbbb900
int  StarGridAllocRecord(int* self, int key, const float* pa, const float* pb, int key2);

struct PlanetRecord;
extern "C" {
    int*  GetActivePlanet2();          // 0x8414c0
    PlanetRecord* GetActivePlanet();   // 0x1021260
    PlanetRecord* GetActivePlanetRecord();  // 0x10212a0
    int   GetUniverseContext();        // 0x1021080
    int   TerraDistClass(float a, float b);         // 0xfc2080
    int   GetSetting9();               // 0x401090
    uint32_t g_dw168a488;              // 0x168a488 empty-key sentinel
    uint32_t g_dw168a48c;              // 0x168a48c
    uint32_t g_dw168a490;              // 0x168a490
}

struct SpeciesProfile {
    int  EmblemType();                 // 0xb8f860
    uint32_t field_608;                // +0x608
};

// The object whose +0x64 field the terraform-zero helper clears (thiscall).
struct TerraObj {
    void ZeroField(PlanetRecord* key, float v);   // 0xbbc370
};

// Receiver whose 0x8414c0 accessor yields the active planet record.
struct PlanetAccessor {
    int* FUN_008414c0();               // 0x8414c0
};

// The object holding the six resource-key words at +0x7c..+0x90 (thiscall).
struct KeySink {
    void Store3(int a, int b, int c);             // 0xbbc410
    void Store3B(int a, int b, int c);            // 0xbbc460
    void __fastcall StoreEmpty();                 // 0xbbc4a0
};

struct DrawObj {
    void  Flush(unsigned flags);       // 0xb2a750
    void  FUN_00b2bbe0();              // 0xb2bbe0
};
DrawObj* GetDrawObj();                 // 0xb3d3b0

struct CityObj {
    int GetNumBuildings();             // 0xff0870
    int GetNumTurrets();               // 0xff0760
};

struct PlanetRecord {
    uint8_t  pad_0000[0xb0];
    float    unk_b0;                   // +0xb0
    float    unk_b4;                   // +0xb4
    uint32_t unk_b8;                   // +0xb8
    int      p_bc;                     // +0xbc  (species id array begin)
    int      p_c0;                     // +0xc0  (species id array end)
    uint8_t  pad_c4[0xc];
    int      p_d0;                     // +0xd0  (profile array begin)
    int      p_d4;                     // +0xd4  (profile array end)
    float GetField64();                // 0xc71d30
    void  SetField64(float v);         // 0xc71da0
};

struct PlanetCellMgr {
    void FUN_00c745d0(int one, void* key);   // 0xc745d0
};
PlanetCellMgr* GetPlanetCellManager();       // 0x1021260

struct SpeciesMgr {
    void* FUN_00b3d420(void* key);           // 0xb3d420
    SpeciesProfile* FUN_00b90410(void* id);  // 0xb90410
};
SpeciesMgr* GetSpeciesManager();             // 0x1021260

SpeciesProfile* GetSpeciesProfile(uint32_t key);   // 0x4df550

struct PlanetObj {
    void FUN_00c80680(int one, void* key);   // 0xc80680
};

// ===========================================================================
// @ 0x00bbb9d0
// Grid pass: move the record at (index, slot) down its own measure list, then
// fix up the records it passed.
// ===========================================================================
void StarGridSiftList(const int* self, int slot, int index, char doCmp)
{
    const int* s = self;
    const short* list = (const short*)s[9 + slot];
    const short* a = (const short*)(s[5] + index * 0x14);

    const short* e = list + (int)a[4 + slot] * 4;   // +0x08 + slot*2
    const short* prev = e - 4;

    while (prev >= list) {
        const float prevm = *(const float*)(prev + 2);
        const float em = *(const float*)(e + 2);
        if (!(em < prevm))
            return;

        if (*prev != (short)-2) {
            const short* other = (const short*)s[5] + prev[1] * 10;

            if (*prev == 1) {
                if (doCmp != 0 && StarGridSlotCmp1((void*)self, slot, (int*)a, (int*)other)
                    && s[2] != s[0]) {
                    int x = *(const int*)a;
                    int y = *(const int*)other;
                    int lo, hi;
                    if (x < y) { lo = x; hi = y; } else { lo = y; hi = x; }
                    int* dst = (int*)(s[3] + s[2] * 8);
                    dst[0] = lo;
                    dst[1] = hi;
                    ((int*)s)[2] = s[2] + 1;
                }
                *(short*)((const char*)other + 0x0e + slot * 2) += 1;
            } else {
                *(short*)((const char*)other + 0x08 + slot * 2) += 1;
            }
        }

        *(short*)((const char*)a + 0x08 + slot * 2) -= 1;

        int t0 = *(const int*)e;
        int t1 = *(const int*)(e + 2);
        *(int*)e = *(const int*)prev;
        *(int*)(e + 2) = *(const int*)(prev + 2);
        *(int*)prev = t0;
        *(int*)(prev + 2) = t1;

        e -= 4;
        prev -= 4;
    }
}

// ===========================================================================
// @ 0x00bbbaf0
// Grid pass: move the record at (index, slot) up its own measure list.
// ===========================================================================
void StarGridSiftListUp(const int* self, int slot, int index, char doCmp)
{
    const int* s = self;
    const short* list = (const short*)s[9 + slot];
    const short* end = list + s[8] * 4;
    const short* a = (const short*)(s[5] + index * 0x14);

    const short* e = list + (int)a[7 + slot] * 4;   // +0x0e + slot*2

    while (e + 4 < end && *(const float*)(e + 6) < *(const float*)(e + 2)) {
        const short* p = e + 4;

        if (*p != (short)-2) {
            const short* other = (const short*)s[5] + p[1] * 10;

            if (*p == 0) {
                if (doCmp != 0 && StarGridSlotCmp1((void*)self, slot, (int*)a, (int*)other)
                    && s[2] != s[0]) {
                    int x = *(const int*)a;
                    int y = *(const int*)other;
                    int lo, hi;
                    if (x < y) { lo = x; hi = y; } else { lo = y; hi = x; }
                    int* dst = (int*)(s[3] + s[2] * 8);
                    dst[0] = lo;
                    dst[1] = hi;
                    ((int*)s)[2] = s[2] + 1;
                }
                *(short*)((const char*)other + 0x08 + slot * 2) -= 1;
            } else {
                *(short*)((const char*)other + 0x0e + slot * 2) -= 1;
            }
        }

        *(short*)((const char*)a + 0x0e + slot * 2) += 1;

        int t0 = *(const int*)e;
        int t1 = *(const int*)(e + 2);
        *(int*)e = *(const int*)p;
        *(int*)(e + 2) = *(const int*)(p + 2);
        *(int*)p = t0;
        *(int*)(p + 2) = t1;

        e += 4;
    }
}

// ===========================================================================
// @ 0x00bbbc10
// Grid pass: merge a freeing measure entry into the creating list.
// ===========================================================================
void StarGridFreePass(const int* self, int slot, int index, char doCmp)
{
    const int* s = self;
    const short* list = (const short*)s[9 + slot];
    const short* end = list + s[8] * 4;
    const short* a = (const short*)(s[5] + index * 0x14);

    const short* e = list + (int)a[4 + slot] * 4;   // +0x08 + slot*2

    while (e + 4 < end && *(const float*)(e + 2) > *(const float*)(e + 6)) {
        const short* p = e + 4;

        if (*p != (short)-2) {
            const short* other = (const short*)s[5] + p[1] * 10;

            if (*p == 1) {
                if (doCmp != 0 && StarGridSlotCmp1((void*)self, slot, (int*)a, (int*)other))
                    StarIndex_Remove((void*)self, (int*)a, (int*)other, 0);
                *(short*)((const char*)other + 0x0e + slot * 2) -= 1;
            } else {
                *(short*)((const char*)other + 0x08 + slot * 2) -= 1;
            }
        }

        *(short*)((const char*)a + 0x08 + slot * 2) += 1;

        int t0 = *(const int*)e;
        int t1 = *(const int*)(e + 2);
        *(int*)e = *(const int*)p;
        *(int*)(e + 2) = *(const int*)(p + 2);
        *(int*)p = t0;
        *(int*)(p + 2) = t1;

        e += 4;
    }
}

// ===========================================================================
// @ 0x00bbbcf0
// Grid pass: merge a creating measure entry into the freeing list.
// ===========================================================================
void StarGridCreatePass(const int* self, int slot, int index, char doCmp)
{
    const int* s = self;
    const short* list = (const short*)s[9 + slot];
    const short* a = (const short*)(s[5] + index * 0x14);

    const short* e = list + (int)a[7 + slot] * 4;   // +0x0e + slot*2
    const short* prev = e - 4;

    while (prev >= list) {
        if (*(const float*)(prev + 2) <= *(const float*)(e + 2))
            return;

        if (*e != (short)-2) {
            const short* other = (const short*)s[5] + e[1] * 10;

            if (*e == 0) {
                if (doCmp != 0 && StarGridSlotCmp1((void*)self, slot, (int*)a, (int*)other))
                    StarIndex_Remove((void*)self, (int*)a, (int*)other, 0);
                *(short*)((const char*)other + 0x08 + slot * 2) += 1;
            } else {
                *(short*)((const char*)other + 0x0e + slot * 2) += 1;
            }
        }

        *(short*)((const char*)a + 0x0e + slot * 2) -= 1;

        int t0 = *(const int*)e;
        int t1 = *(const int*)(e + 2);
        *(int*)e = *(const int*)prev;
        *(int*)(e + 2) = *(const int*)(prev + 2);
        *(int*)prev = t0;
        *(int*)(prev + 2) = t1;

        e -= 4;
        prev -= 4;
    }
}

// ===========================================================================
// @ 0x00bbbe20
// Free-record iterator: returns the next free slot record, or 0.
// ===========================================================================
void* StarGridNextFree(const int* self, int* pos)
{
    int n = self[2];
    --n;
    const int* p = (*pos < n) ? pos : &n;
    int idx = *p;
    *pos = idx;
    if (idx < 0)
        return 0;
    *pos = idx - 1;
    return (void*)(self[3] + idx * 8);
}

// ===========================================================================
// @ 0x00bbbe60
// Publish one record measure pair into the two coordinate measure lists and
// run the four sift passes, or (when the record is part of a group) write the
// record's bounding pair straight into the created/freeing lists.
// ===========================================================================
void StarGridInsertMeasure(const int* self, int index, const float* pa, const float* pb)
{
    const int* s = self;
    const short* rec = (const short*)(s[5] + index * 0x10);

    if ((*(const uint16_t*)((const char*)rec + 0x0c) & 0x8000u) != 0) {
        *(float*)(s[12] + 4 + ((int)*(const short*)((const char*)rec + 0x08) & 0x7fff) * 8)
            = pa[0];
        *(float*)(s[12] + 4 + ((int)*(const short*)((const char*)rec + 0x0c) & 0x7fff) * 8)
            = pb[0];
        *(float*)(s[13] + 4 + ((int)*(const short*)((const char*)rec + 0x0a) & 0x7fff) * 8)
            = pa[1];
        *(float*)(s[13] + 4 + ((int)*(const short*)((const char*)rec + 0x0e) & 0x7fff) * 8)
            = pb[1];
    } else {
        const short* pk = (const short*)((const char*)rec + 0x0c);
        const int* const* listBase = (const int* const*)(s + 9);
        for (int k = 0; k < 2; ++k, ++listBase, ++pk) {
            const char* list = (const char*)*listBase;
            float* e0 = (float*)(list + pk[-2] * 8);
            float* e1 = (float*)(list + pk[0] * 8);

            if (pa[k] < e0[1]) {
                e0[1] = pa[k];
                StarGridSiftDownEq1((void*)self, k, index, 0);
            }
            if (pb[k] > e1[1]) {
                e1[1] = pb[k];
                StarGridSiftUpEq0((void*)self, k, index, 0);
            }
            if (pa[k] > e0[1]) {
                e0[1] = pa[k];
                StarGridResolveEq1((void*)self, k, index, 0);
            }
            if (pb[k] < e1[1]) {
                e1[1] = pb[k];
                StarGridResolveEq0((void*)self, k, index, 0);
            }
        }
    }
}

// ===========================================================================
// @ 0x00bbbfe0
// Allocate one 0x14-byte record, build its three measure pairs and insert it.
// Returns the allocated record index.
// ===========================================================================
int StarGridAllocRecord(int* self, int key, const float* pa, const float* pb, int key2)
{
    int* s = self;
    int idx;
    if (s[4] == s[6]) {
        idx = s[4];
        s[6] = s[6] + 1;
        s[4] = idx + 1;
    } else {
        idx = s[7];
        s[7] = *(int*)(s[5] + idx * 0x14);
        s[4] = s[4] + 1;
    }

    int* rec = (int*)(s[5] + idx * 0x14);
    rec[1] = key2;
    rec[0] = key;

    int j = s[8] + 0;
    int j1 = s[8] + 1;

    for (int k = 0; k < 3; ++k) {
        float* m = (float*)s[9 + k];
        *(short*)((char*)m + j * 8 + 0) = 0;
        *(short*)((char*)m + j * 8 + 2) = (short)idx;
        m[j * 2 + 1] = pa[k];

        *(short*)((char*)m + j1 * 8 + 2) = (short)idx;
        *(short*)((char*)m + j1 * 8 + 0) = 1;
        m[j1 * 2 + 1] = pb[k];

        *(short*)((char*)rec + 0x0c + k * 2) = (short)(j1 | 0x8000);
        *(short*)((char*)rec + 0x08 + k * 2) = (short)(j | 0x8000);

        char last = (k == 2) ? 1 : 0;
        StarGridSiftList(self, k, idx, last);
        StarGridCreatePass(self, k, idx, last);
    }

    s[8] = s[8] + 2;
    return idx;
}

// ===========================================================================
// @ 0x00bbc0f0
// Publish the measure pair of the record at (slot, index) into each of the
// three coordinate lists, running the four sift passes with the group flag on.
// ===========================================================================
void StarGridInsertRow(int* self, int slot, const float* pa, const float* pb)
{
    int* s = self;
    const short* pk = (const short*)(s[5] + slot * 0x14) + 7;  // a + 0x0e
    const int* const* listBase = (const int* const*)(s + 9);

    for (int k = 0; k < 3; ++k, ++listBase, ++pk) {
        const char* list = (const char*)*listBase;
        float* e0 = (float*)(list + pk[-3] * 8);
        float* e1 = (float*)(list + pk[0] * 8);

        if (pa[k] < e0[1]) {
            e0[1] = pa[k];
            StarGridSiftList(self, k, slot, 1);
        }
        if (pb[k] > e1[1]) {
            e1[1] = pb[k];
            StarGridSiftListUp(self, k, slot, 1);
        }
        if (pa[k] > e0[1]) {
            e0[1] = pa[k];
            StarGridFreePass(self, k, slot, 1);
        }
        if (pb[k] < e1[1]) {
            e1[1] = pb[k];
            StarGridCreatePass(self, k, slot, 1);
        }
    }
}

// ===========================================================================
// @ 0x00bbc300
// Record allocation wrapper (no measure pair pointer).
// ===========================================================================
void StarGridAllocRecord2(int* self, int key, const float* pa, const float* pb)
{
    StarGridAllocRecord(self, key, pa, pb, 0);
}

// ===========================================================================
// @ 0x00bbc320
// Tail-call thunk onto the row-insert pass.
// ===========================================================================
void StarGridRowThunk(int* self, int slot, const float* pa, const float* pb)
{
    StarGridInsertRow(self, slot, pa, pb);
}

// ===========================================================================
// @ 0x00bbc340
// Add a float to the active planet's +0x1fd4 accumulator.
// ===========================================================================
void __stdcall TerraAccum1(void* self, float v)
{
    int* p = ((PlanetAccessor*)self)->FUN_008414c0();
    if (p != 0)
        *(float*)((char*)p + 0x1fd4) += v;
}

// ===========================================================================
// @ 0x00bbc370
// Zero the +0x64 field of the object in ecx when the active planet is the one
// passed in and no universe context is live.
// ===========================================================================
void TerraObj::ZeroField(PlanetRecord* key, float v)
{
    if (v != 0.0f && key == GetActivePlanet()
        && GetUniverseContext() == 0) {
        float cur = key->GetField64();
        key->SetField64(cur + v);
        *(int*)((char*)this + 0x64) = 0;
    }
}
// ===========================================================================
// @ 0x00bbc3c0
// Add a float to the active planet's +0x1fd8 accumulator.
// ===========================================================================
void __stdcall TerraAccum2(void* self, float v)
{
    int* p = ((PlanetAccessor*)self)->FUN_008414c0();
    if (p != 0)
        *(float*)((char*)p + 0x1fd8) += v;
}

// ===========================================================================
// @ 0x00bbc400
// Flush the debug-draw singleton's category 0xf.
// ===========================================================================
void TerraFlushDbg()
{
    GetDrawObj()->Flush(0xf);
}

// ===========================================================================
// @ 0x00bbc410
// Store three caller keys then the shared empty key.
// ===========================================================================
// ===========================================================================
// @ 0x00bbc410
// Store three caller keys then the shared empty key.
// ===========================================================================
void KeySink::Store3(int a, int b, int c)
{
    char* s = (char*)this;
    *(int*)(s + 0x7c) = a;
    *(int*)(s + 0x80) = b;
    *(int*)(s + 0x84) = c;
    *(int*)(s + 0x88) = g_dw168a488;
    *(int*)(s + 0x8c) = g_dw168a48c;
    *(int*)(s + 0x90) = g_dw168a490;
}

// ===========================================================================
// @ 0x00bbc460
// Store the shared empty key then three caller keys.
// ===========================================================================
void KeySink::Store3B(int a, int b, int c)
{
    char* s = (char*)this;
    *(int*)(s + 0x7c) = g_dw168a488;
    *(int*)(s + 0x80) = g_dw168a48c;
    *(int*)(s + 0x88) = a;
    *(int*)(s + 0x84) = g_dw168a490;
    *(int*)(s + 0x8c) = b;
    *(int*)(s + 0x90) = c;
}
// ===========================================================================
// @ 0x00bbc4a0
// Store the shared empty key into both key slots.
// ===========================================================================
void __fastcall KeySink::StoreEmpty()
{
    char* s = (char*)this;
    *(int*)(s + 0x7c) = g_dw168a488;
    *(int*)(s + 0x80) = g_dw168a48c;
    *(int*)(s + 0x84) = g_dw168a490;
    *(int*)(s + 0x88) = g_dw168a488;
    *(int*)(s + 0x8c) = g_dw168a48c;
    *(int*)(s + 0x90) = g_dw168a490;
}

// ===========================================================================
// @ 0x00bbc540
// Publish the two stored keys to the active planet's cargo slots and pick the
// debug-draw category from the species' emblem type.
// ===========================================================================
void __stdcall CargoSlotsUpdate(int* k, void* planetArg)
{
    if (k[0] == (int)g_dw168a488 && k[1] == (int)g_dw168a48c && k[2] == (int)g_dw168a490)
        return;

    void* planet = planetArg;
    if (planet == 0)
        planet = GetActivePlanet();

    ((PlanetCellMgr*)planet)->FUN_00c745d0(1, k);

    int* p2 = GetActivePlanet2();
    if (p2 != 0)
        ((PlanetObj*)p2)->FUN_00c80680(1, k);

    if (planet != GetActivePlanet())
        return;

    GetDrawObj()->FUN_00b2bbe0();
    void* sp = GetSpeciesManager()->FUN_00b3d420(k);
    SpeciesProfile* prof = GetSpeciesManager()->FUN_00b90410(sp);
    if (prof == 0)
        return;

    unsigned cat = prof->EmblemType();
    if (cat == 0x29c388a) {
        GetDrawObj()->Flush(2);
    } else if (cat == 0x3a8be428) {
        GetDrawObj()->Flush(4);
    } else if (cat == 0x6d60a1cc) {
        GetDrawObj()->Flush(1);
    } else {
        GetDrawObj()->Flush(0);
    }
}

// ===========================================================================
// @ 0x00bbc630
// Compare the total building count (buildings + turrets) of two cities.
// ===========================================================================
bool CityLessBuildings(void* a, void* b)
{
    int x = ((CityObj*)a)->GetNumBuildings() + ((CityObj*)a)->GetNumTurrets();
    int y = ((CityObj*)b)->GetNumBuildings() + ((CityObj*)b)->GetNumTurrets();
    return x < y;
}

// ===========================================================================
// @ 0x00bbc670
// Planet record terraform distance getter.
// ===========================================================================
int __stdcall PlanetTerraformDist(void* rec)
{
    PlanetRecord* r = (PlanetRecord*)rec;
    if (r == 0)
        r = GetActivePlanetRecord();
    return TerraDistClass(r->unk_b0, r->unk_b4);
}

// ===========================================================================
// @ 0x00bbc6a0
// True when `value` is at least the planet record's terraform distance.
// ===========================================================================
bool __stdcall PlanetTerraformAtLeast(int value, void* rec)
{
    PlanetRecord* r = (PlanetRecord*)rec;
    if (r == 0) {
        r = GetActivePlanetRecord();
        if (r == 0)
            r = GetActivePlanetRecord();
    }
    int dist = TerraDistClass(r->unk_b0, r->unk_b4);
    return dist >= value;
}

// ===========================================================================
// @ 0x00bbc700
// Select the record pointer with the lowest key in [first, last).
// ===========================================================================
bool RecordKeyLess(void* a, void* b);      // 0xac0730

void** RecordMinSelect(void** first, void** last)
{
    void** best = first;
    if (first != last) {
        void** it = first;
        while (it = it + 1, it != last) {
            void* ka = *best ? (char*)*best + 0x34 : 0;
            void* kb = *it ? (char*)*it + 0x34 : 0;
            if (RecordKeyLess(kb, ka))
                best = it;
        }
    }
    return best;
}

// ===========================================================================
// @ 0x00bbc760
// Insertion sort of record pointers with a caller-supplied compare callback.
// ===========================================================================
void RecordInsertionSort(void** first, void** last, bool (__cdecl* cmp)(void*, void*))
{
    for (; first != last; first = first + 1) {
        void* v = *first;
        void** dst = first;
        void** src = first;
        while (cmp(v, src[-1])) {
            *dst = src[-1];
            dst = dst - 1;
            src = src - 1;
        }
        *dst = v;
    }
}

// ===========================================================================
// @ 0x00bbc7c0
// Median-of-three record pointer selection with a caller compare callback.
// ===========================================================================
void** RecordMedian3(void** a, void** b, void** c, bool (__cdecl* cmp)(void*, void*))
{
    if (cmp(*a, *b)) {
        if (cmp(*b, *c))
            return b;
        if (cmp(*a, *c))
            return c;
        return a;
    }
    if (cmp(*a, *c))
        return a;
    if (cmp(*b, *c))
        return c;
    return b;
}

// ===========================================================================
// @ 0x00bbc840
// Number of records held in the this object's two vector pairs.
// ===========================================================================
int __fastcall TerraVectorCount(void* self)
{
    char* s = (char*)self;
    int a = (*(int*)(s + 0x358) - *(int*)(s + 0x354)) >> 2;
    int b = (*(int*)(s + 0x344) - *(int*)(s + 0x340)) >> 2;
    return a + b;
}

// ===========================================================================
// @ 0x00bbc870
// Resource key at the `n`-th planet-record entry whose species has the given
// emblem-type code, or the shared empty key.
// ===========================================================================
SpeciesMgr* FUN_00b3d420();      // 0xb3d420

void __stdcall fn_bbc870(int* out, int n, int code, void* rec)
{
    int found = 0;
    int idx = 0;

    PlanetRecord* r = (PlanetRecord*)rec;
    if (r == 0)
        r = GetActivePlanetRecord();

    SpeciesMgr* mgr = FUN_00b3d420();

    int count = (r->p_c0 - r->p_bc) / 0xc;
    int off = 0;
    idx = 0;
    if (count > 0) {
        do {
            int* entry = (int*)(r->p_bc + off);
            SpeciesProfile* prof = mgr->FUN_00b90410(entry);
            if (prof != 0) {
                if (prof->EmblemType() == code) {
                    ++found;
                    if (found == n) {
                        out[0] = entry[0];
                        out[1] = entry[1];
                        out[2] = entry[2];
                        return;
                    }
                }
            }
            ++idx;
            off += 0xc;
        } while (idx < count);
    }

    int k0 = (int)g_dw168a488;
    int k1 = (int)g_dw168a48c;
    int k2 = (int)g_dw168a490;
    out[0] = k0;
    out[1] = k1;
    out[2] = k2;
}

// ===========================================================================
// @ 0x00bbc950
// Resource key at the k-th planet-record entry whose species profile has no
// emblem, or the shared empty key.
// ===========================================================================
void __stdcall fn_bbc950(int* out, int a, int b, void* rec)
{
    int idx = 0;
    int found = 0;

    PlanetRecord* r = (PlanetRecord*)rec;
    if (r == 0)
        r = GetActivePlanetRecord();

    GetSetting9();

    int count = (int)((r->p_d4 - r->p_d0) / 0xc);
    int target = a * 2 - 1 + b;
    int off = 0;
    if (count > 0) {
        do {
            SpeciesProfile* prof = (SpeciesProfile*)GetSpeciesProfile(r->p_d0 + off);
            if (prof != 0) {
                if (prof->field_608 == 0)
                    ++found;
                if (found == target) {
                    int* src = (int*)(r->p_d0 + off);
                    out[0] = src[0];
                    out[1] = src[1];
                    out[2] = src[2];
                    return;
                }
            }
            ++idx;
            off += 0xc;
        } while (idx < count);
    }

    out[0] = g_dw168a488;
    out[1] = g_dw168a48c;
    out[2] = g_dw168a490;
}
