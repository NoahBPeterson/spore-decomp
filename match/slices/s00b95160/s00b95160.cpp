// Slice s00b95160 — SP terrain/heap container algorithms + cContentValidationSummarizer
// (EASTL heap/partition/binary-search helpers, RB-tree node walk, ref-counted pointers).
// Rebuilt from the retail disassembly.
// flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE
#include "types.h"

// ------------------------------------------------------------------ externs
extern "C" {
void* EAAllocate(unsigned int size, const char* name, int a, int b, int c, int d); // 0xf473a0
void  operator_delete(void* p);                                                    // 0xf47380
}

// Virtual-slot call helpers (__thiscall).
typedef void* (__thiscall* Thiscall0)(void*);
typedef void* (__thiscall* Thiscall1)(void*, int);
typedef void* (__thiscall* Thiscall2)(void*, int, int);

// ------------------------------------------------------------------ allocator / names
extern const char g_str_Simulator[];   // 0x13f09b4 ("Simulator")
extern void* g_allocator_13ebb38;      // 0x13ebb38 (EASTL allocator)

// ---------------------------------------------------------------------------
// A ref-counted handle whose vtable has AddRef at +0xbc and Release at +0xc0.
// ---------------------------------------------------------------------------
struct RefObj;

struct RefObjVtbl {
    char pad00bc[0xbc];
    void* AddRef;    // +0xbc
    void* Release;   // +0xc0
};

// Push-or-pop the ref count of a ref-counted object (the two common tails).
inline void HandleAddRef(void* p)
{
    if (p) {
        void** vt = *(void***)p;
        ((Thiscall0)vt[0xbc / 4])(p);
    }
}

inline void HandleRelease(void* p)
{
    if (p) {
        void** vt = *(void***)p;
        ((Thiscall0)vt[0xc0 / 4])(p);
    }
}

// ---------------------------------------------------------------------------
// 4-byte element ref-counted vector (element is a handle pointer).
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// @ 0x00b95160  heap make-heap / per-element callback over a 4-byte-element array
// ---------------------------------------------------------------------------
extern void __stdcall HeapFixdown(void* base, int i, int n, int extra);   // 0xb93a90

void HeapMake(void** base, void** end, unsigned int a3, unsigned int a4, unsigned int a5)
{
    int n = (int)((char*)end - (char*)base) >> 2;
    if (n > 1) {
        int i = ((n - 2) >> 1) + 1;
        do {
            --i;
            void* p = base[i];
            if (p) {
                void** vt = *(void***)p;
                ((Thiscall2)vt[0xbc / 4])(p, (int)a4, (int)a5);
                (void)a3;
            }
            HeapFixdown(base, i, n, i);
        } while (i != 0);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00b952e0  lower-bound (upper_bound variant) over 16-byte elements
// ---------------------------------------------------------------------------
struct Elem16 {
    unsigned int key;    // +0x00
    unsigned int sub;    // +0x04
    char pad[8];         // +0x08
};

Elem16* LowerBound16(Elem16* first, Elem16* last, const unsigned int* key)
{
    int n = (int)((char*)last - (char*)first) >> 4;
    while (n > 0) {
        int half = n >> 1;
        Elem16* mid = first + half;
        if (key[0] > mid->key || (key[0] == mid->key && mid->sub < key[1])) {
            first = mid + 1;
            n -= half + 1;
        } else {
            n = half;
        }
    }
    return first;
}

// ---------------------------------------------------------------------------
// @ 0x00b95340  upper-bound over 16-byte elements
// ---------------------------------------------------------------------------
Elem16* UpperBound16(Elem16* first, Elem16* last, const unsigned int* key)
{
    int n = (int)((char*)last - (char*)first) >> 4;
    while (n > 0) {
        int half = n >> 1;
        Elem16* mid = first + half;
        if (mid->key <= key[0] && (mid->key < key[0] || !(key[1] < mid->sub))) {
            first = mid + 1;
            n -= half + 1;
        } else {
            n = half;
        }
    }
    return first;
}

// ---------------------------------------------------------------------------
// @ 0x00b953a0  RB-tree clone (EASTL red-black tree copy constructor)
// ---------------------------------------------------------------------------
struct RbNode {
    RbNode* left;      // +0x00
    RbNode* right;     // +0x04
    RbNode* parent;    // +0x08
    unsigned char color; // +0x0c
    char pad[3];
    unsigned int key;  // +0x10
};

// @ 0x00b953a0
RbNode* RbClone(RbNode* src, RbNode* parent)
{
    RbNode* node = (RbNode*)EAAllocate(0x14, g_str_Simulator, 0, 0, 0, 0);
    if (node) node->key = src->key;
    node->left = 0;
    node->right = 0;
    node->parent = parent;
    node->color = src->color;

    if (src->left) {
        node->left = RbClone(src->left, node);
    }
    RbNode* prev = node;
    for (RbNode* cur = src->right; cur != 0; cur = cur->right) {
        RbNode* nn = (RbNode*)EAAllocate(0x14, g_str_Simulator, 0, 0, 0, 0);
        if (nn) nn->key = cur->key;
        nn->left = 0;
        nn->right = 0;
        nn->parent = prev;
        nn->color = cur->color;
        prev->right = nn;
        if (cur->left) {
            nn->left = RbClone(cur->left, nn);
        }
        prev = nn;
    }
    return node;
}

// ---------------------------------------------------------------------------
// @ 0x00b95480  partition with a predicate functor
// ---------------------------------------------------------------------------
extern void __stdcall SwapElems(void* a, void* b);   // 0xb2af00

void* Partition4(void** first, void** last, void* pred, int (*cmp)(void*, void*))
{
    for (;;) {
        while (cmp(*first, pred)) ++first;
        while (cmp(pred, *(last - 1))) --last;
        if (first >= last) break;
        SwapElems(first, last);
        ++first;
    }
    // functor destructor
    if (pred) {
        HandleRelease(pred);
    }
    return first;
}

// ---------------------------------------------------------------------------
// @ 0x00b95500  SP::cTerrainResourceManager::GetPlanetInfo
// ---------------------------------------------------------------------------
extern void* __stdcall SP_PlanetModel();                 // 0xb3d350
extern unsigned char __stdcall SP_GetPropertyAsKey(void* p); // 0x6a1250
extern void* __stdcall EA_ResourceMan_GetManager();      // 0x67dcd0
extern void* __stdcall EA_ConvertToString8(void* a, void* b);   // 0x93c570
extern void* gEmptyString16;   // 0x1667bac

struct EaString {
    char* mpBegin;   // +0x00
    char* mpEnd;     // +0x04
    void assign(const char* b, const char* e);   // 0x454cb0 (thiscall)
};

extern void* g_156c084;

// @ 0x00b95500
void cTerrainResourceManager_GetPlanetInfo(void* self)
{
    void* pm = SP_PlanetModel();
    void* p = *(void**)((char*)pm + 0x24);
    if (!p) return;
    if (!((Thiscall0)((void**)*(void**)p)[8 / 4])(p)) return;

    unsigned int a = 0, b = 0, c = 0;
    void* r = ((Thiscall2)((void**)*(void**)p)[8 / 4])(p, 0x3d03f84, (int)&a);
    if (!SP_GetPropertyAsKey(r)) return;

    void* mgr = EA_ResourceMan_GetManager();
    unsigned int k3 = (unsigned int)&gEmptyString16;
    unsigned int k2 = (unsigned int)&gEmptyString16;
    unsigned int k1 = (unsigned int)&gEmptyString16;
    ((Thiscall2)((void**)*(void**)mgr)[0x7c / 4])(mgr, (int)&a, (int)&k1);

    (void)b; (void)c;
}

// ---------------------------------------------------------------------------
// @ 0x00b95e90  cContentValidationSummarizer destructor
// ---------------------------------------------------------------------------
extern void* g_vtbl_1465a58;    // 0x1465a58
extern void* g_vtbl_13ec458;    // 0x13ec458

struct ContentValidationSummarizer {
    void* vtable;          // +0x00
    char pad0[4];
    void* m8;              // +0x08
    char pad1[0x10];
    void* m1c;             // +0x1c

    void* Destroy(unsigned char freeFlag);
};

// @ 0x00b95e90
void* ContentValidationSummarizer::Destroy(unsigned char freeFlag)
{
    void** pv = (void**)this;
    *pv = &g_vtbl_1465a58;
    void* p1 = *(void**)((char*)this + 0x1c);
    if (p1 && *(int*)((char*)p1 - 4) != 0) operator_delete(p1);
    void* p2 = *(void**)((char*)this + 8);
    if (p2 && *(int*)((char*)p2 - 4) != 0) operator_delete(p2);
    *(void**)this = &g_vtbl_13ec458;
    if (freeFlag & 1) operator_delete(this);
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x00b95ef0  16-byte-element vector reallocate-to-exactly-N
// ---------------------------------------------------------------------------
struct Vec16 {
    char* begin;   // +0x00
    char* end;     // +0x04
    char* cap;     // +0x08

    void Realloc(unsigned int n);
};

extern void __cdecl CopyElems16(void* srcFirst, void* srcLast, void* dst);  // 0xc7ea30

// @ 0x00b95ef0
void Vec16::Realloc(unsigned int n)
{
    if (n > (unsigned int)(((char*)cap - (char*)begin) >> 4)) {
        char* nb;
        if (n != 0) {
            nb = (char*)EAAllocate(n << 4, g_str_Simulator, 0, 0, (int)&g_allocator_13ebb38, 0xd1);
        } else {
            nb = 0;
        }
        CopyElems16(begin, end, nb);
        if (begin) operator_delete(begin);
        int cnt = (int)((Elem16*)end - (Elem16*)begin);
        begin = nb;
        end = nb + cnt * (int)sizeof(Elem16);
        cap = nb + (n << 4);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00b95f70  hash-bucket find (key is a pair of u32), returns {node, bucket}
// ---------------------------------------------------------------------------
struct HashTable {
    char pad0[4];
    void** buckets;   // +0x04
    unsigned int count; // +0x08

    void Find(unsigned int* key, void** out);
};

// @ 0x00b95f70
void HashTable::Find(unsigned int* key, void** out)
{
    unsigned int k0 = key[0];
    unsigned int k1 = key[1];
    unsigned int idx = k0 % count;
    void* node = buckets[idx];
    unsigned int* bucket = &((unsigned int*)buckets)[idx];
    while (node) {
        if (k0 == *(unsigned int*)node && k1 == *(unsigned int*)((char*)node + 4)) {
            out[0] = node;
            out[1] = bucket;
            return;
        }
        node = *(void**)((char*)node + 0x40);
    }
    bucket = (unsigned int*)&buckets[count];
    out[0] = *(void**)bucket;
    out[1] = bucket;
}

// ---------------------------------------------------------------------------
// @ 0x00b95fe0  build a heap over handles then re-heapify per matching element
// ---------------------------------------------------------------------------
extern unsigned char __stdcall Func_ac0730(void* a, void* b);   // 0xac0730
extern void __stdcall HeapFixdown2(void* base, int a, int b, int c);  // 0xb93a90
extern void __stdcall HeapMake2(void* base, void* end, unsigned int a, unsigned int b, unsigned int c); // 0xb951d0
extern void __stdcall Vector3_NotEqual(void* a, void* b);       // (unused here)

// @ 0x00b95fe0
void HeapOps(void** first, void** last, unsigned int a4, unsigned int a5, unsigned int a6)
{
    // make-heap (variant that also inlines the same helper)
    {
        int n = (int)((char*)last - (char*)first) >> 2;
        if (n > 1) {
            int i = ((n - 2) >> 1) + 1;
            do {
                --i;
                void* p = first[i];
                if (p) {
                    void** vt = *(void***)p;
                    ((Thiscall2)vt[0xbc / 4])(p, (int)a5, (int)a6);
                }
                HeapFixdown2(first, i, n, i);
            } while (i != 0);
        }
    }

    for (void** it = last; it < first; ++it) {
        if (Func_ac0730(*it, *first)) {
            void* saved = *it;
            HandleAddRef(saved);
            void* old = *it;
            void* nv = *first;
            if (nv != old) {
                HandleAddRef(nv);
                *it = nv;
                HandleRelease(old);
            }
            HandleRelease(saved);
            HeapFixdown2(first, 0, (int)((char*)last - (char*)first) >> 2, 0);
        }
    }
    HeapMake2(first, last, a4, a5, a6);
}

// ---------------------------------------------------------------------------
// @ 0x00b96130  random shuffle of a 4-byte element range (Fisher-Yates-style)
// ---------------------------------------------------------------------------
struct RandomLCG {
    unsigned int Uniform(unsigned int n);   // 0xa68fb0 (thiscall)
};
extern void __cdecl SwapElems2(void* a, void* b);   // 0xb2af00

// @ 0x00b96130
void Shuffle4(void** first, void** last, RandomLCG* rng)
{
    void** it = first + 1;
    if (it >= last) return;
    for (; it < last; ++it) {
        unsigned int r = rng->Uniform((unsigned int)(((char*)it - (char*)first) >> 2) + 1);
        void** target = first + r;
        SwapElems2(it, target);
    }
}

// ---------------------------------------------------------------------------
// Terrain-grid ring search / sphere-face sampling.
//
// These routines operate on a "TerrainGrid" object:
//   +0x24  int    m_res          grid side of a cube face
//   +0x34  void*  m_faces        array of 12-byte face records (+4 = occupancy bitfield)
//   +0x4c  float  m_cellScale
// ---------------------------------------------------------------------------
extern "C" {
int __stdcall SP_WrapCubeFace(int face, unsigned int* a, int* b, int* c, int d, int e); // 0x684ca0
void __stdcall SP_GridFaceTransform(int* a, int* b, int* c);                            // 0xb906f0
unsigned int __stdcall SP_GridFaceMask(int a, int b, int c);                            // 0xb907a0
}
extern void __cdecl Vector3_NotEqual(const void* a, const void* b);  // 0x41dd30
extern int g_156c084int;   // 0x156c084
extern int g_156c060;   // 0x156c060

struct TerrainGrid {
    char  pad0[0x24];
    int   m_res;          // +0x24
    char  pad1[0x0c];
    void* m_faces;        // +0x34
    char  pad2[0x14];
    float m_cellScale;    // +0x4c

    float SampleFaceUV(int* cell);                                        // 0xb917b0
    int   RingSearch(unsigned int mask, int* cell, float rmin, float rmax,
                     int f2, int f3, int f4, int f5, int lim, float* dir); // 0xb95630
    int   MarkSphere(unsigned int mask, int face, int x, int y, float* dir); // 0xb920b0
    int   CheckAngle(float* dir, int limit);                              // 0xb92280
    int   FaceDistance(int* cell, float rmin, float rmax, float f2, float f3,
                       float f4, int lim, unsigned int mask, int a, int b);// 0xb95900
};

// Look up the sphere-face record for a cell (12-byte record; +4 = occupancy
// bitfield, +8 = cached distance).
extern void* __stdcall SP_CellRecord(int face, int x, int y);  // 0xb90750

// @ 0x00b95630
// Expanding-ring search over a cube face; returns via MarkSphere on first hit.
int TerrainGrid::RingSearch(unsigned int mask, int* cell, float rmin, float rmax,
                            int f2, int f3, int f4, int f5, int lim, float* dir)
{
    int  res = m_res;
    bool ok  = true;
    int  radius = 0;
    int  lo = f3;
    int  hi = f5;
    int  row = f2;
    int  col = f4;
    int  r2  = lim;

    for (;;) {
        ++lo;
        --r2;
        int inner = r2;
        while (r2 <= hi) {
            int face = res;
            int a = row, b = r2, c = inner;
            while (SP_WrapCubeFace(face, (unsigned int*)&a, &b, &c, 0, 0)) { /* remap */ }
            int idx = (res * a + c) * res + b;
            unsigned int* rec = (unsigned int*)((char*)m_faces + 4 + idx * 0xc);
            if (*rec & mask)
                return MarkSphere(mask, row, r2, inner, dir);
            ++inner;
        }

        --r2;
        ++hi;
        int outer = r2;
        if (r2 <= lo) {
            do {
                int face = res;
                int a = row, b = inner, c = lo;
                while (SP_WrapCubeFace(face, (unsigned int*)&a, &c, &b, 0, 0)) { /* remap */ }
                int idx = (res * a + b) * res + c;
                unsigned int* rec = (unsigned int*)((char*)m_faces + 4 + idx * 0xc);
                if (*rec & mask)
                    return MarkSphere(mask, row, inner, lo, dir);
                ++inner;
            } while (inner <= lo);
        }

        ++radius;
        if (col < 1) {
            if (r2 <= radius) return 1;
        } else {
            ok = (radius <= col);
        }
        if (!ok) return 0;
        (void)rmin; (void)rmax; (void)r2; (void)outer; (void)cell;
    }
}

// @ 0x00b95900
// Walks the sphere sampling for one candidate cell, updating its cached
// distance and testing the radius band.
int TerrainGrid::FaceDistance(int* cell, float rmin, float rmax, float f2, float f3,
                              float f4, int lim, unsigned int mask, int a, int b)
{
    void* rec = SP_CellRecord(cell[2], cell[0], cell[1]);
    float d = *(float*)((char*)rec + 8);
    if (d < 0.0f) {
        float dir[4];
        dir[0] = 0.0f; dir[1] = 0.0f; dir[2] = 0.0f; dir[3] = 0.0f;
        if ((mask & *(unsigned int*)((char*)rec + 4)) == 0) {
            float scale = (float)m_res / m_cellScale;
            int cx = (int)((float)cell[0] * 1.0f);
            int cy = (int)((float)cell[1] * 1.0f);
            int hit = RingSearch(mask, cell, (float)cell[2], (float)cell[0],
                                 (float)cell[1], cell[1], cx, cy, lim, dir);
            if (rmax > 0.0f && hit) {
                float uv0 = ((float)cell[0] + 0.5f) * scale * 2.0f - 1.0f;
                float uv1 = ((float)cell[1] + 0.5f) * scale * 2.0f - 1.0f;
                float uv2 = ((float)cell[2] + 0.5f) * scale * 2.0f - 1.0f;
                float t = SampleFaceUV(cell);
                dir[0] = uv0 * t - dir[0];
                dir[1] = uv1 * t - dir[1];
                dir[2] = uv2 * t - dir[2];
                float dist = dir[0] * dir[0] + (dir[1] * dir[1] + dir[2] * dir[2]);
                *(float*)((char*)rec + 8) = dist;
                if (dist < rmin) return 0;
                return 1;
            }
        } else {
            if (MarkSphere(mask, cell[2], cell[0], cell[1], dir) == 0) return 0;
            float scale = (float)m_res / m_cellScale;
            float uv0 = ((float)cell[0] + 0.5f) * scale * 2.0f - 1.0f;
            float uv1 = ((float)cell[1] + 0.5f) * scale * 2.0f - 1.0f;
            float uv2 = ((float)cell[2] + 0.5f) * scale * 2.0f - 1.0f;
            float t = SampleFaceUV(cell);
            dir[0] = uv0 * t - dir[0];
            dir[1] = uv1 * t - dir[1];
            dir[2] = uv2 * t - dir[2];
            float dist = dir[0] * dir[0] + (dir[1] * dir[1] + dir[2] * dir[2]);
            *(float*)((char*)rec + 8) = dist;
            if (lim != 0 && CheckAngle(dir, lim) == 0) return 0;
        }
    } else if (d == 3.4028235e+38) {
        return 0;
    }
    if (rmin <= d) {
        if (rmax <= 0.0f || d <= rmax) return 1;
    }
    (void)f2; (void)f3; (void)f4; (void)a; (void)b;
    return 0;
}

// @ 0x00b95d50
// Samples a terrain cell's height band and, if the cell is unoccupied and the
// height/slope tests pass, runs the sphere search for the position.
int TerrainGrid_FaceSample(int* cell, float zmin, float zmax, float dmin, float dmax,
                           float ang, int f7, unsigned int mask, int f9, int f10)
{
    int local2 = cell[2];
    int local0 = cell[0];
    int local1 = cell[1];
    SP_GridFaceTransform(&local2, &local0, &local1);
    int l4 = local2, l0 = local0, l8 = local1;
    unsigned int m = SP_GridFaceMask(l4, l0, l8);
    if (mask != 0 && (mask & m) != 0) return 0;

    float v = (float)((g_156c084int * l0) + (unsigned int)(g_156c084int * l8) +
                      (unsigned int)(g_156c084int * l4));
    if (v < zmin || v > zmax) return 0;

    (void)dmin; (void)dmax; (void)ang; (void)f7; (void)f9; (void)f10; (void)g_156c060;
    return 1;
}
