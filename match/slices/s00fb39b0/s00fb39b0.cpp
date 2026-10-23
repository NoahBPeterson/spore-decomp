// match/slices/s00fb39b0/s00fb39b0.cpp
// Slice s00fb39b0 -- Spore terrain decal / terrain-record container helpers
// (SporeApp.exe 0x00fb39b0..0x00fb43ae).
//
//  00fb39b0  FUN_00fb39b0   vector<SP::TerrainRecord>(e=200)::insert  (grow path + shift-insert)
//  00fb3e20  FUN_00fb3e20   clear the +0x154 16-byte-element vector, free the +0x94 pool block
//  00fb3f10  SP::cTerrainSphereQuad::RebuildDecalIndices
//  00fb4340  FUN_00fb4340   dtor: dec 0x016d664c, free +0x1a0 / +0x18c / +0x154
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-
#include "types.h"

extern "C" void  __cdecl operator_delete(void*);                                            // 0x00f47380
extern "C" void* __cdecl EAAllocate(unsigned, const char*, int, int, const char*, unsigned); // 0x00f473a0
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);                              // 0x011e0744
extern "C" int   __cdecl atexit(void (*)());                                                // 0x011e07ef

int             DAT_016d664c;               // 0x016d664c
unsigned        DAT_016d66c0;               // 0x016d66c0  "static-init done" flag
unsigned short* DAT_016d66ac;               // 0x016d66ac  vector<unsigned short>::begin
unsigned short* DAT_016d66b0;               // 0x016d66b0  vector<unsigned short>::end
unsigned short* DAT_016d66b4;               // 0x016d66b4  vector<unsigned short>::cap
char            DAT_015d07b0;               // 0x015d07b0  index-buffer pool

// ---------------------------------------------------------------------------
// Terrain record: four 0x30-byte sub-blocks (9 floats, int, 2 floats), then a
// trailing int and byte, padded out to 200 bytes.
// ---------------------------------------------------------------------------
struct TerrainSub { float f[9]; int key; float g[2]; };      // 0x30
struct TerrainRecord {
    TerrainSub    sub[4];                                   // 0x00..0xbf
    int           tail;                                     // 0xc0
    unsigned char flag;                                     // 0xc4
    unsigned char pad[3];
};                                                          // 0xc8 == 200

extern "C" int  __cdecl FUN_00fb2e70(int srcBegin, int srcEnd, int dst);                        // 0x00fb2e70
extern "C" void __cdecl FUN_00fb2ca0(int dst, int n, const void* value, int cap);               // 0x00fb2ca0
extern "C" void __cdecl FUN_00fb2ac0(void* cap, int pos, int begin, int end, int capv);         // 0x00fb2ac0
extern "C" void __cdecl FUN_00fb05b0(int pos, int end, const void* value);                      // 0x00fb05b0
extern "C" void __cdecl FUN_00faf100(int a, int b, int c);                                      // 0x00faf100

// Stub for the vector object (begin/end/cap) so the insert below is emitted __thiscall.
struct TerrainVecStub {
    int* begin;
    int* end;
    int* cap;
    void FUN_00fb39b0(int pos, unsigned n, const TerrainRecord* value);
};

// ---
// @ 0x00fb39b0
// ---
// vector<TerrainRecord>(element size 200)::insert(pos, n, value): realloc-and-splice when the
// spare capacity is short, otherwise the classic three-way shift / fill.
void TerrainVecStub::FUN_00fb39b0(int pos, unsigned n, const TerrainRecord* value)
{
    int* self = (int*)this;
    TerrainRecord tmp;
    int newBuf;
    int p1;
    int p2;
    int oldEnd;
    unsigned have;
    unsigned spare;
    unsigned newCap;
    unsigned cap;

    spare = (unsigned)((self[2] - self[1]) / 200);
    if (spare >= n) {
        if (n == 0) {
            return;
        }

        tmp = *value;

        oldEnd = self[1];
        have = (unsigned)((oldEnd - pos) / 200);
        if (have > n) {
            p1 = oldEnd - (int)(n * 200);
            FUN_00fb2ac0(&cap, p1, oldEnd, oldEnd, (int)cap);
            self[1] = self[1] + (int)(n * 200);
            FUN_00faf100(pos, p1, oldEnd);
            FUN_00fb05b0(pos, pos + (int)(n * 200), &tmp);
        } else {
            FUN_00fb2ca0(oldEnd, (int)(n - have), &tmp, (int)cap);
            self[1] = self[1] + (int)((n - have) * 200);
            FUN_00fb2ac0(&cap, pos, oldEnd, self[1], (int)cap);
            self[1] = self[1] + (int)(have * 200);
            FUN_00fb05b0(pos, oldEnd, &tmp);
        }
        return;
    }

    have = (unsigned)((self[1] - self[0]) / 200);
    newCap = have * 2;
    if (have == 0) {
        newCap = 1;
    }
    cap = have + n;
    if (cap < newCap) {
        cap = newCap;
    }
    if (cap == 0) {
        newBuf = 0;
    } else {
        newBuf = (int)EAAllocate(cap * 200, "Simulator", 0, 0,
                                 "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                                 0xd1);
    }
    p1 = FUN_00fb2e70(self[0], pos, newBuf);
    FUN_00fb2ca0(p1, (int)n, value, (int)cap);
    p2 = FUN_00fb2e70(pos, self[1], (int)(n * 200 + p1));
    if (self[0] != 0 && *(int*)(self[0] - 4) != 0) {
        operator_delete((void*)self[0]);
    }
    self[0] = newBuf;
    self[1] = p2;
    self[2] = (int)(cap * 200 + newBuf);
}

// ---------------------------------------------------------------------------
extern "C" void __cdecl   FUN_00762a30(int);                       // 0x00762a30
extern "C" void __fastcall FUN_00fb5090(void* self);               // 0x00fb5090

// 16-byte trivially-copyable element of the +0x154 vector; +4 holds an owned object.
struct Elem16 { int a; int b; int c; int d; };

// ---
// @ 0x00fb3e20
// ---
// Clear the vector of 16-byte elements at +0x154 (releasing each element's +4 pointer object),
// rewind its end, free the +0x170 block and hand the +0x94 pool block back to the allocator's
// free list.
extern "C" void __fastcall FUN_00fb3e20(int self)
{
    int n;

    if (*(int*)(self + 8) != 0) {
        FUN_00fb5090((void*)self);
    }

    n = (*(int*)(self + 0x158) - *(int*)(self + 0x154)) >> 4;
    if (n > 0) {
        int i = n;
        int off = 0;
        do {
            int p = *(int*)(off + *(int*)(self + 0x154) + 4);
            if (p != 0) {
                FUN_00762a30(p);
                *(int*)(off + *(int*)(self + 0x154) + 4) = 0;
            }
            off += 0x10;
            i--;
        } while (i != 0);
    }

    // eastl vector::erase(begin(), end()): the move source collapses onto end(), so the copy loop
    // is empty and only mLast rewinds by (count * -sizeof(T)).
    {
        Elem16* dst = (Elem16*)*(int*)(self + 0x154);
        Elem16* src = (Elem16*)*(int*)(self + 0x158);
        Elem16* end = (Elem16*)*(int*)(self + 0x158);
        while (src != end) {
            *dst = *src;
            ++src;
            ++dst;
        }
        *(int*)(self + 0x158) = *(int*)(self + 0x158) +
            ((*(int*)(self + 0x158) - *(int*)(self + 0x154)) >> 4) * -16;
    }

    {
        int p = *(int*)(self + 0x170);
        if (p != 0) {
            operator_delete((void*)p);
            *(int*)(self + 0x170) = 0;
        }
    }

    {
        int p = *(int*)(self + 0x94);
        if (p != 0) {
            int* pool = *(int**)(*(int*)self + 0xa4c);
            *(int*)(*(int*)((char*)pool + 4) + 8) = p;
            *(int*)(p + 8) = 0;
            *(int*)(p + 0xc) = *(int*)((char*)pool + 4);
            (*(int*)((char*)pool + 8))--;
            *(int*)((char*)pool + 4) = p;
        }
    }
    *(int*)(self + 0x94) = 0;
}

// ---------------------------------------------------------------------------
// The global index vector's out-of-line grow helper and the upload plumbing.
// ---------------------------------------------------------------------------
struct UShortVec {
    unsigned short* begin;
    unsigned short* end;
    unsigned short* cap;
    void grow(unsigned short* pos, const unsigned short* value);       // 0x006f5bc0
};

struct IndexBuffer {
    void* Lock(unsigned int level, void* locked);                      // 0x011f4f20
    void  Unlock(void* locked);                                        // 0x011f4fd0
};

extern "C" void  __cdecl FUN_013c9d50(void);                                                    // 0x013c9d50
extern "C" int   __cdecl FUN_00762c60(void* pool, unsigned a, unsigned b, int c, int d, int e); // 0x00762c60

namespace SP {

struct cTerrainSphereDecal {
    char GetBBoxForFace(int face, float* out);                     // 0x00fad140
};

struct cTerrainSphereQuad {
    char  pad0[0x18];
    int   mChunkRes;                                               // 0x18
    int   mFace;                                                   // 0x1c
    char  pad1[0x38];                                              // 0x20..0x57
    float field58;                                                 // 0x58
    float field5c;                                                 // 0x5c
    float field60;                                                 // 0x60

    unsigned char RebuildDecalIndices(unsigned int* param_2);
};

}

// ---
// @ 0x00fb3f10
// ---
// Walk the (mChunkRes+1)^2 parameter lattice, bbox-cull every cell against the face's bounding
// box and emit the four/two triangle corner indices of each surviving cell into the global index
// vector, then upload the finished list into the decal's index buffer.
unsigned char __thiscall SP::cTerrainSphereQuad::RebuildDecalIndices(unsigned int* param_2)
{
    int   chunk  = mChunkRes;
    int   stride = chunk + 3;
    float bbox[4];
    int   iRow;
    int   iCol;
    int   base;

    if (((SP::cTerrainSphereDecal*)*param_2)->GetBBoxForFace(mFace, bbox) == 0) {
        return 0;
    }

    if ((DAT_016d66c0 & 1) == 0) {
        DAT_016d66c0 = DAT_016d66c0 | 1;
        DAT_016d66ac = 0;
        DAT_016d66b0 = 0;
        DAT_016d66b4 = 0;
        atexit(FUN_013c9d50);
    }

    {
        UShortVec* vec = (UShortVec*)&DAT_016d66ac;
        unsigned short* first = vec->begin;
        unsigned short* last  = vec->end;
        if (first != last) {
            unsigned short* d = first;
            for (unsigned short* s = last; s != vec->end; ++s, ++d) {
                *d = *s;
            }
            vec->end = (unsigned short*)((int)vec->end - (int)(last - first) * 2);
        }
    }

    if (chunk + 1 > 1) {
        base = stride;
        for (iRow = 1; iRow < chunk + 1; iRow++) {
            for (iCol = 1; iCol < chunk + 1; iCol++) {
                float res   = (float)chunk;
                float morph = field60;
                float a = ((float)(iCol - 1) / res) * morph + field58;
                float b = ((float)(iRow - 1) / res) * morph + field5c;

                if (bbox[0] < morph / res + a && a < bbox[2] &&
                    bbox[1] < morph / res + b && b < bbox[3]) {
                    unsigned int v0 = (unsigned int)(base + iCol);
                    unsigned int v1 = v0 + 1;
                    UShortVec* vec = (UShortVec*)&DAT_016d66ac;
                    unsigned short v;

                    v = (unsigned short)v1;
                    if (vec->end < vec->cap) {
                        unsigned short* p = vec->end;
                        vec->end = vec->end + 1;
                        if (p != 0) *p = v;
                    } else {
                        vec->grow(vec->end, &v);
                    }

                    v = (unsigned short)(stride + v0 + 1);
                    if (vec->end < vec->cap) {
                        unsigned short* p = vec->end;
                        vec->end = vec->end + 1;
                        if (p != 0) *p = v;
                    } else {
                        vec->grow(vec->end, &v);
                    }

                    v = (unsigned short)(stride + v0);
                    if (vec->end < vec->cap) {
                        unsigned short* p = vec->end;
                        vec->end = vec->end + 1;
                        if (p != 0) *p = v;
                    } else {
                        vec->grow(vec->end, &v);
                    }

                    v = (unsigned short)(stride + v0);
                    if (vec->end < vec->cap) {
                        unsigned short* p = vec->end;
                        vec->end = vec->end + 1;
                        if (p != 0) *p = v;
                    } else {
                        vec->grow(vec->end, &v);
                    }

                    v = (unsigned short)v0;
                    if (vec->end < vec->cap) {
                        unsigned short* p = vec->end;
                        vec->end = vec->end + 1;
                        if (p != 0) *p = v;
                    } else {
                        vec->grow(vec->end, &v);
                    }

                    v = (unsigned short)v1;
                    if (vec->end < vec->cap) {
                        unsigned short* p = vec->end;
                        vec->end = vec->end + 1;
                        if (p != 0) *p = v;
                    } else {
                        vec->grow(vec->end, &v);
                    }
                }
            }
            base += stride;
        }
    }

    if ((unsigned short*)DAT_016d66ac != DAT_016d66b0) {
        int idxBuf = (int)param_2[1];
        unsigned count = (unsigned)((int)DAT_016d66b0 - (int)DAT_016d66ac) >> 1;

        if (idxBuf != 0 && *(int*)(idxBuf + 8) != (int)count) {
            FUN_00762a30(idxBuf);
            param_2[1] = 0;
        }
        if (param_2[1] == 0) {
            param_2[1] = (unsigned int)FUN_00762c60(&DAT_015d07b0, count / 3, count, 8, 4, 0);
        }
        {
            int locked[3];
            if (((IndexBuffer*)param_2[1])->Lock(2, locked) == 0) {
                return 0;
            }
            memcpy((void*)locked[0], DAT_016d66ac,
                   (unsigned)((int)DAT_016d66b0 - (int)DAT_016d66ac) >> 1 << 1);
            ((IndexBuffer*)param_2[1])->Unlock(locked);
            return 1;
        }
    }

    if (param_2[1] != 0) {
        FUN_00762a30((int)param_2[1]);
        param_2[1] = 0;
    }
    return 1;
}

// ---------------------------------------------------------------------------
struct MemManager { void FUN_00fa2620(int a, int b); };            // 0x00fa2620

// ---
// @ 0x00fb4340
// ---
// Destructor: drop the global instance count and release the three owned buffers (each guarded
// by the allocator's 4-byte size prefix at -4).
extern "C" void __fastcall FUN_00fb4340(int self)
{
    void* p;

    DAT_016d664c = DAT_016d664c - 1;

    p = *(void**)(self + 0x1a0);
    if (p != 0 && *(int*)((char*)p - 4) != 0) {
        operator_delete(p);
    }

    ((MemManager*)(self + 0x18c))->FUN_00fa2620(*(int*)(self + 0x18c), *(int*)(self + 0x190));

    p = *(void**)(self + 0x18c);
    if (p != 0 && *(int*)((char*)p - 4) != 0) {
        operator_delete(p);
    }

    p = *(void**)(self + 0x154);
    if (p != 0 && *(int*)((char*)p - 4) != 0) {
        operator_delete(p);
    }
}
