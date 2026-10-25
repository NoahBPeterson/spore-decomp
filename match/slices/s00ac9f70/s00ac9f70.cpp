// Slice s00ac9f70: gameplay serialization / EASTL range helpers.
#include <string.h>
#include <xmmintrin.h>
#define FSQRT(v) _mm_cvtss_f32(_mm_sqrt_ss(_mm_set_ss(v)))

typedef unsigned int uint;
typedef unsigned char uchar;

static void* vc(void* obj, int off) { return ((void**)*(void**)obj)[off / 4]; }

void* __cdecl operator_new(size_t, const char*, int, int, const char*, int);
void  __cdecl operator_delete(void*);
void  __cdecl FUN_00f47380(void* p);            // 0x00f47380 free
void  __cdecl FUN_00829110(void* a, void* b, void* c, void* d, void* e);
struct VecObj {                       // EASTL vector header {begin, end, capacity}
  void FUN_00b93c60(uint n, void* p); // 0x00b93c60
};
struct SortValue {                       // 3-float heap sort key
    float x, y, z;
    char FUN_00ac0730(void* a, void* b); // 0x00ac0730 distance compare (thiscall, ret 8)
};
void  __cdecl FUN_00ac93c0(void* arr, void* arg2, int holeIndex, void* arg5, SortValue value); // 0x00ac93c0
void  __fastcall FUN_00d5ccf0(void* self, int, void* p);          // 0x00d5ccf0 (thiscall, ret 4)
void  __cdecl FUN_00d576d0(void* p);
void  __fastcall FUN_00d5f780(void* self, int, void* p);          // 0x00d5f780 (thiscall, ret 4)
void* __fastcall FUN_00c8e820(void* self, int, void* p);          // 0x00c8e820 (thiscall, ret 4)
void* __cdecl SP_GetSpeciesProfile(void* p);
void  __fastcall FUN_00c96e80(void* self, int, void* p);          // 0x00c96e80 (thiscall, ret 4)
unsigned __cdecl FUN_00b5b800(void);                              // 0x00b5b800 current game mode
void* __fastcall FUN_00c0bbd0(void* self, int);                   // 0x00c0bbd0
void  __fastcall FUN_00645ed0(void* self, int, void* out, void* in);  // 0x00645ed0 (thiscall, ret 8)
void  __fastcall FUN_01068380(void* self, int, void* a, void* b);     // 0x01068380 (thiscall, ret 8)
extern "C" float DAT_0140f334;                                    // 0x0140f334
void  __cdecl FUN_0093aa70(void* a, void* b, int c, int d);
void  __cdecl FUN_0093a780(void* a, void* b, int c, int d);
void  __fastcall FUN_00ae6970(void* p);
extern "C" char  DAT_015d8b54;
extern "C" char  DAT_015d8b56;
extern "C" char  DAT_015d8b59;

// ---- wide-string serialize helpers (shared by the three FUN_00acab* fns) ---
struct cWideString {
    unsigned short* mpBegin;
    unsigned short* mpEnd;
    unsigned short* mpCapacityEnd;
    cWideString* FUN_0056e2d0(const cWideString* src); // 0x0056e2d0 copy-ctor (thiscall, ret 4)
};
cWideString* FUN_0093c5a0(cWideString* out, const char* src, int len); // 0x0093c5a0
cWideString* FUN_0093c6d0(cWideString* out, const cWideString* src);   // 0x0093c6d0
void  __cdecl FUN_00694fc0(cWideString* out, const void* value);       // 0x00694fc0
void  __cdecl FUN_00695010(cWideString* out, const void* value);       // 0x00695010
void  __cdecl FUN_00694c10(cWideString* out, const void* value);       // 0x00694c10
extern "C" unsigned short DAT_01667bac[];                              // 0x01667bac L""
extern "C" unsigned short DAT_013f36bc[];                              // 0x013f36bc L"type"
#define WSTR_FREE(s) do { \
    if ((((unsigned)((char*)(s).mpCapacityEnd - (char*)(s).mpBegin) & ~1u) > 2) && (s).mpBegin) \
        FUN_00f47380((s).mpBegin); \
} while (0)
#define WSTR_FREE_CMDLINE(s) do { \
    if (((char*)(s).mpCapacityEnd - (char*)(s).mpBegin) > 1 && (s).mpBegin) \
        FUN_00f47380((s).mpBegin); \
} while (0)
#define WSTR_SET_EMPTY_ODD(s) do { \
    (s).mpBegin = DAT_01667bac; (s).mpEnd = DAT_01667bac; \
    (s).mpCapacityEnd = (unsigned short*)0x01667bad; \
} while (0)

// ---- integer hash table (bucket free 0x00693230, insert 0x007c3990) --------
struct HTNode { int mKey; int mValue; HTNode* mpNext; };
struct HTPair { int mKey; int mValue; };
struct HTIter { HTNode* mpNode; void* mpBucket; char mbInserted; };
struct HashTable {
    int         mPad00;        // +0x00
    HTNode**    mpBuckets;     // +0x04
    int         mBucketCount;  // +0x08
    int         mCount;        // +0x0c
    void FUN_00693230(HTNode** buckets, int count);          // 0x00693230 (thiscall, ret 8)
    void FUN_007c3990(HTIter* out, const HTPair* pair, int hint); // 0x007c3990 (thiscall, ret 0xc)
};

struct GameCreature { void FUN_00aca360(void* other); };       // 0x00aca360 (thiscall, ret 4)

// @ 0x00ac9f70
void FUN_00ac9f70(void* obj, int param) {
    int base = param;
    int v = *(int*)(param + 0xc);
    void* r = ((void* (__thiscall*)(void*))vc(obj, 0x20))(obj);
    int val = v;
    void* w = ((void* (__thiscall*)(void*))vc(r, 0x18))(r);
    FUN_0093aa70(w, &val, 1, 0);
    int* buckets = *(int**)(base + 4);
    void* node = (void*)*buckets;
    int* pp = buckets;
    if (!node) {
        pp = buckets + 1;
        int t = buckets[1];
        while (t == 0) { pp++; t = *pp; }
        node = (void*)*pp;
    }
    void* end = (void*)buckets[*(int*)(base + 8)];
    while (node != end) {
        void* r2 = ((void* (__thiscall*)(void*))vc(obj, 0x20))(obj);
        int k = *(int*)node;
        int tmp = k;
        void* w2 = ((void* (__thiscall*)(void*))vc(r2, 0x18))(r2);
        FUN_0093aa70(w2, &tmp, 1, 0);
        ((void (__thiscall*)(void*))vc(obj, 0x1c))(obj);
        void* r3 = ((void* (__thiscall*)(void*))vc(obj, 0x20))(obj);
        tmp = *(int*)((char*)node + 4);
        void* w3 = ((void* (__thiscall*)(void*))vc(r3, 0x18))(r3);
        FUN_0093aa70(w3, &tmp, 1, 0);
        ((void (__thiscall*)(void*))vc(obj, 0x1c))(obj);
        node = (void*)*((int*)node + 2);
        while (node == 0) {
            pp = pp + 1;
            node = (void*)*pp;
        }
    }
    ((void (__thiscall*)(void*))vc(obj, 0x1c))(obj);
}

// @ 0x00aca0c0
// Heap "sift-down": walk the hole towards the leaves of a binary heap stored in arr[0..n),
// always descending into the *farther* of the two children (value.FUN_00ac0730 compare),
// moving each displaced element up, then re-insert `value` at the resting hole via 0x00ac93c0.
// arg5 is a reference-counted handle (vfn0 = addref, vfn4 = release) that is threaded through
// the repair call and released as the tail call.
void __cdecl FUN_00aca0c0(void** arr, void* arg2, int n, int holeIndex, void* arg5, SortValue value) {
    int child = 2 * holeIndex + 2;
    if (child < n) {
        do {
            void* left  = arr[child - 1] ? (void*)((char*)arr[child - 1] + 0x120) : 0;
            void* right = arr[child]     ? (void*)((char*)arr[child]     + 0x120) : 0;
            if (value.FUN_00ac0730(right, left)) --child;
            void* moved = arr[child];
            void* old   = arr[holeIndex];
            if (moved != old) {
                if (moved) ((void (__thiscall*)(void*))vc(moved, 0))(moved);
                arr[holeIndex] = moved;
                if (old) ((void (__thiscall*)(void*))vc(old, 4))(old);
            }
            holeIndex = child;
            child = 2 * child + 2;
        } while (child < n);
        if (child == n) {                       // lone left child
            void* moved = arr[child - 1];
            void* old   = arr[holeIndex];
            if (moved != old) {
                if (moved) ((void (__thiscall*)(void*))vc(moved, 0))(moved);
                arr[holeIndex] = moved;
                if (old) ((void (__thiscall*)(void*))vc(old, 4))(old);
            }
            holeIndex = child - 1;
        }
    }
    if (arg5) ((void (__thiscall*)(void*))vc(arg5, 0))(arg5);
    FUN_00ac93c0(arr, arg2, holeIndex, arg5, value);
    if (arg5) ((void (__thiscall*)(void*))vc(arg5, 4))(arg5);
}

// @ 0x00aca1f0  lower_bound over 0x20-byte elements; returns the resulting iterator
int* FUN_00aca1f0(int* begin, int* end, int* key) {
    int n = (int)((char*)end - (char*)begin) >> 5;
    if (n > 0) {
        do {
            int h = n >> 1;
            if (begin[h * 8] < *key) {
                begin = begin + h * 8 + 8;
                h = n + (-1 - h);
            }
            n = h;
        } while (n > 0);
    }
    return begin;
}

// @ 0x00aca2f0
int FUN_00aca2f0(uchar* p, uchar* end, int out) {
    for (; p != end; p += 0x20) {
        *(void**)(p + 4) = (void*)0x145a164;
        uchar* b = *(uchar**)(p + 0xc);
        uchar* e2 = *(uchar**)(p + 0x10);
        for (; b < e2; b += 0xc) {
            void* o = *(void**)b;
            ((void (__thiscall*)(void*, int))vc(o, 0))(o, 0);
        }
        uchar* base = *(uchar**)(p + 0xc);
        if (base && *(int*)(base - 4) != 0)
            operator_delete(base);
        out += 0x20;
    }
    return out;
}

// @ 0x00aca360
// Creature interaction dispatcher (thiscall, arg = the other creature, ret 4).
// Two "interaction tags" returned by other->vfn0x20():
//   0x18eb45e - unlink other's handle from the visible list at this+0xe0, then range-check.
//   0x18eb4b7 - unless the current game mode is 0x1654c02, look for a matching creature in
//               this->m_a8..this->m_ac (0x18 stride) and trigger the in-range action.
// Range check = x87 sqrt of the squared XZ/Y distance between the two 0xc0/0x120 position
// sub-objects, compared against a radius field pulled from vfn0x6c() (+0x25c).
void GameCreature::FUN_00aca360(void* other) {
    uchar* self = (uchar*)this;
    unsigned tag = ((unsigned (__thiscall*)(void*))vc(other, 0x20))(other);

    if (tag == 0x18eb45e) {
        // ---- path A (0xaca52e): release other's handle from the list at this+0xe0 ----
        uchar* list = self + 0xe0;
        int handle = *(int*)((uchar*)other + 0x24);
        void* at = 0;
        FUN_00645ed0(list, 0, &at, &handle);
        if (at) {
            void** begin = *(void***)(list + 4);
            int size = *(int*)(list + 8);
            if (at != begin[size]) {
                if (--*(int*)((uchar*)at + 4) <= 0)
                    FUN_01068380(list, 0, at, at);
            }
        }
    } else if (tag == 0x18eb4b7) {
        if (FUN_00b5b800() == 0x1654c02) return;

        uchar* mgr = *(uchar**)(self + 0xa4);
        uchar* c = mgr ? *(uchar**)(mgr + 0xaf0) : 0;
        if (c) {
            float* p1 = (float*)((void* (__thiscall*)(void*))vc(c + 0x120, 0x2c))(c + 0x120);
            float* p2 = (float*)((void* (__thiscall*)(void*))vc((uchar*)other + 0xc0, 0x2c))((uchar*)other + 0xc0);
            float dx = p2[0] - p1[0], dy = p2[1] - p1[1], dz = p2[2] - p1[2];
            float d = FSQRT(dx * dx + dy * dy + dz * dz);
            uchar* rf = (uchar*)((void* (__thiscall*)(void*))vc(c, 0x6c))(c);
            if (d > *(float*)(rf + 0x25c) + DAT_0140f334) {
                FUN_00d5ccf0(mgr, 0, other);
                return;
            }
        }

        uchar* it  = *(uchar**)(self + 0xa8);
        uchar* end = *(uchar**)(self + 0xac);
        while (it != end) {
            void* o = *(void**)it;
            if (o) {
                void* a = FUN_00c8e820(o, 0, 0);
                void* b = FUN_00c0bbd0(other, 0);
                if (a == b) {
                    float* p1 = (float*)((void* (__thiscall*)(void*))vc((uchar*)o + 0x120, 0x2c))((uchar*)o + 0x120);
                    float* p2 = (float*)((void* (__thiscall*)(void*))vc((uchar*)other + 0xc0, 0x2c))((uchar*)other + 0xc0);
                    float dx = p2[0] - p1[0], dy = p2[1] - p1[1], dz = p2[2] - p1[2];
                    float d = FSQRT(dx * dx + dy * dy + dz * dz);
                    float r = ((float (__thiscall*)(void*))vc(o, 0x60))(o);
                    if (2.0f * r >= d) {
                        float* p = (float*)((void* (__thiscall*)(void*))vc((uchar*)other + 0xc0, 0x2c))((uchar*)other + 0xc0);
                        ((void (__thiscall*)(void*, int, void*, int, void*))*(void**)((uchar*)other + 0xe8))(other, 0, o, 1, p);
                        FUN_00c96e80(o, 0, other);
                        return;
                    }
                }
            }
            it += 0x18;
        }
        FUN_00d576d0(other);
        return;
    } else {
        return;
    }

    // ---- common range check reached from path A (0xaca57e) ----
    uchar* mgr = *(uchar**)(self + 0xa4);
    uchar* c = mgr ? *(uchar**)(mgr + 0xaf0) : 0;
    if (!c) return;
    if (((char (__thiscall*)(void*))vc(c, 0x2c))(c)) return;
    float* p1 = (float*)((void* (__thiscall*)(void*))vc(c + 0x120, 0x2c))(c + 0x120);
    float* p2 = (float*)((void* (__thiscall*)(void*))vc((uchar*)other + 0xc0, 0x2c))((uchar*)other + 0xc0);
    float dx = p2[0] - p1[0], dy = p2[1] - p1[1], dz = p2[2] - p1[2];
    float d = FSQRT(dx * dx + dy * dy + dz * dz);
    uchar* rf = (uchar*)((void* (__thiscall*)(void*))vc(c, 0x6c))(c);
    if (d > *(float*)(rf + 0x25c))
        FUN_00d5f780(mgr, 0, other);
}

// @ 0x00aca620
// Deserialize an integer hash map: clear the bucket array, read the entry count from the
// serializer, then read `count` (key, value) pairs (each followed by a 0x1c vcall) and insert
// them. The final 0x1c vcall terminates the sequence. On a duplicate key the existing node's
// value is overwritten.
void __cdecl FUN_00aca620(void* obj, HashTable* ht) {
    ht->FUN_00693230(ht->mpBuckets, ht->mBucketCount);
    ht->mCount = 0;
    int count = 0;
    void* sub = ((void* (__thiscall*)(void*))vc(obj, 0x20))(obj);
    void* rdr = ((void* (__thiscall*)(void*))vc(sub, 0x18))(sub);
    FUN_0093a780(rdr, &count, 1, 0);
    for (int i = 0; i < count; ++i) {
        int key = 0;
        void* ks = ((void* (__thiscall*)(void*))vc(obj, 0x20))(obj);
        void* kr = ((void* (__thiscall*)(void*))vc(ks, 0x18))(ks);
        FUN_0093a780(kr, &key, 1, 0);
        ((void (__thiscall*)(void*))vc(obj, 0x1c))(obj);

        int value = 0;
        void* vs = ((void* (__thiscall*)(void*))vc(obj, 0x20))(obj);
        void* vr = ((void* (__thiscall*)(void*))vc(vs, 0x18))(vs);
        FUN_0093a780(vr, &value, 1, 0);
        ((void (__thiscall*)(void*))vc(obj, 0x1c))(obj);

        HTPair pair;
        pair.mKey = key;
        pair.mValue = value;
        HTIter out;
        ht->FUN_007c3990(&out, &pair, 0);
        if (!out.mbInserted) out.mpNode->mValue = value;
    }
    ((void (__thiscall*)(void*))vc(obj, 0x1c))(obj);
}

// @ 0x00aca730
void FUN_00aca730(void* obj, int* vec) {
    void* r = ((void* (__thiscall*)(void*))vc(obj, 0x20))(obj);
    int n = (vec[1] - vec[0]) >> 2;
    void* w = ((void* (__thiscall*)(void*))vc(r, 0x18))(r);
    FUN_0093aa70(w, &n, 1, 0);
    int* b = (int*)vec[0];
    int* e = (int*)vec[1];
    for (; b != e; b++) {
        uint v = 0;
        if (*b) v = ((uint (__thiscall*)(void*, int))vc((void*)*b, 0xc))((void*)*b, 0x179c807);
        ((void (__thiscall*)(void*, uint))vc(obj, 0x2c))(obj, v);
    }
    ((void (__thiscall*)(void*))vc(obj, 0x1c))(obj);
}

// @ 0x00aca7b0
void __stdcall FUN_00aca7b0(uchar* p, uchar* end) {
    if (p < end) {
        uint n = (((uint)(end - p) - 1) >> 5) + 1;
        do {
            *(void**)(p + 4) = (void*)0x145a164;
            uchar* b = *(uchar**)(p + 0xc);
            uchar* e2 = *(uchar**)(p + 0x10);
            for (; b < e2; b += 0xc) {
                void* o = *(void**)b;
                ((void (__thiscall*)(void*, int))vc(o, 0))(o, 0);
            }
            uchar* base = *(uchar**)(p + 0xc);
            if (base && *(int*)(base - 4) != 0)
                operator_delete(base);
            p += 0x20;
        } while (--n);
    }
}

// @ 0x00aca820
void __stdcall FUN_00aca820(int* p, int* end) {
    for (; p < end; p += 6) {
        int* e2 = (int*)p[2];
        for (int* it = (int*)p[1]; it < e2; it++) {
            void* o = (void*)*it;
            if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
        }
        int b = p[1];
        if (b && *(int*)(b - 4) != 0) operator_delete((void*)b);
        void* o = (void*)*p;
        if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
    }
}

// @ 0x00aca970
struct VecCopyStub { int* FUN_00aca970(int* src); };
int* VecCopyStub::FUN_00aca970(int* src) {
    int* obj = (int*)this;
    void* o = *(void**)src;
    *obj = (int)o;
    if (o) ((void (__thiscall*)(void*))vc(o, 0))(o);
    ((VecObj*)((char*)this + 4))->FUN_00b93c60((src[2] - src[1]) >> 2, src + 4);
    int* ret = 0;
    FUN_00829110(&ret, (void*)src[1], (void*)src[2], (void*)obj[1], (void*)src);
    obj[2] = (int)ret;
    return obj;
}

// @ 0x00acaab0
int* FUN_00acaab0(int* p, int* end, int* out) {
    if (p != end) {
        int* cur = out;
        do {
            if (cur) {
                void* o = (void*)*p;
                *cur = (int)o;
                if (o) ((void (__thiscall*)(void*))vc(o, 0))(o);
                int n = (p[2] - p[1]) >> 2;
                int mem = 0;
                if (n) mem = (int)operator_new(n * 4, "Simulator", 0, 0,
                    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
                cur[1] = mem;
                cur[2] = mem;
                cur[3] = mem + n * 4;
                int* r = 0;
                FUN_00829110(&r, (void*)p[1], (void*)p[2], (void*)mem, (void*)end);
                cur[2] = (int)r;
            }
            p += 6; cur += 6;
        } while (p != end);
        return cur;
    }
    return out;
}

// @ 0x00acab70
int FUN_00acab70(int* p, int* end, int out) {
    for (; p != end; p += 6) {
        int* e2 = (int*)p[2];
        for (int* it = (int*)p[1]; it < e2; it++) {
            void* o = (void*)*it;
            if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
        }
        int b = p[1];
        if (b && *(int*)(b - 4) != 0) operator_delete((void*)b);
        void* o = (void*)*p;
        if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
        out += 0x18;
    }
    return out;
}

// @ 0x00acabe0
// Serialize a named value that carries a float/vector key. Format the key into a wide
// command line, bail out (true) when it is empty, resolve the (optional) C-string file name
// to a wide string, make the wide copy of the command line, then run the save protocol:
//   vfn0(name)  -> [if gbTypeCheck] vfn8(L"type", pArg) -> vfn0C(typedName) -> vfn4(name)
// The empty-name case uses pArg as the name argument for vfn0/vfn4.
char FUN_00acabe0(void* pSave, const char* pFileName, const void* pValue, const void* pArg) {
    cWideString cmdLine;
    WSTR_SET_EMPTY_ODD(cmdLine);
    FUN_00694fc0(&cmdLine, pValue);

    char result = 1;
    if (cmdLine.mpBegin != cmdLine.mpEnd) {
        cWideString fileName;
        if (pFileName) {
            FUN_0093c5a0(&fileName, pFileName, -1);
        } else {
            fileName.mpBegin = DAT_01667bac;
            fileName.mpEnd = DAT_01667bac;
            fileName.mpCapacityEnd = DAT_01667bac + 1;
        }
        cWideString name;
        name.FUN_0056e2d0(&fileName);
        WSTR_FREE(fileName);

        cWideString typedName;
        FUN_0093c6d0(&typedName, &cmdLine);

        char ok;
        if (name.mpBegin == name.mpEnd) {
            ok = ((char (__thiscall*)(void*, const void*))vc(pSave, 0))(pSave, pArg);
        } else {
            ok = ((char (__thiscall*)(void*, const void*))vc(pSave, 0))(pSave, name.mpBegin);
            if (DAT_015d8b54 && ok)
                ok = ((char (__thiscall*)(void*, const void*, const void*))vc(pSave, 8))(pSave, DAT_013f36bc, pArg);
        }
        if (ok)
            ok = ((char (__thiscall*)(void*, const void*))vc(pSave, 0xc))(pSave, typedName.mpBegin);
        if (ok)
            ok = ((char (__thiscall*)(void*, const void*))vc(pSave, 4))(pSave,
                     name.mpBegin == name.mpEnd ? pArg : (const void*)name.mpBegin);
        result = ok ? 1 : 0;
        WSTR_FREE(typedName);
        WSTR_FREE(name);
    }
    WSTR_FREE_CMDLINE(cmdLine);
    return result;
}

// @ 0x00acadb0
// Same save protocol as 0x00acabe0 but the key is a single float and the type-check global is
// DAT_015d8b56.
char FUN_00acadb0(void* pSave, const char* pFileName, const void* pValue, const void* pArg) {
    cWideString cmdLine;
    WSTR_SET_EMPTY_ODD(cmdLine);
    FUN_00695010(&cmdLine, pValue);

    char result = 1;
    if (cmdLine.mpBegin != cmdLine.mpEnd) {
        cWideString fileName;
        if (pFileName) {
            FUN_0093c5a0(&fileName, pFileName, -1);
        } else {
            fileName.mpBegin = DAT_01667bac;
            fileName.mpEnd = DAT_01667bac;
            fileName.mpCapacityEnd = DAT_01667bac + 1;
        }
        cWideString name;
        name.FUN_0056e2d0(&fileName);
        WSTR_FREE(fileName);

        cWideString typedName;
        FUN_0093c6d0(&typedName, &cmdLine);

        char ok;
        if (name.mpBegin == name.mpEnd) {
            ok = ((char (__thiscall*)(void*, const void*))vc(pSave, 0))(pSave, pArg);
        } else {
            ok = ((char (__thiscall*)(void*, const void*))vc(pSave, 0))(pSave, name.mpBegin);
            if (DAT_015d8b56 && ok)
                ok = ((char (__thiscall*)(void*, const void*, const void*))vc(pSave, 8))(pSave, DAT_013f36bc, pArg);
        }
        if (ok)
            ok = ((char (__thiscall*)(void*, const void*))vc(pSave, 0xc))(pSave, typedName.mpBegin);
        if (ok)
            ok = ((char (__thiscall*)(void*, const void*))vc(pSave, 4))(pSave,
                     name.mpBegin == name.mpEnd ? pArg : (const void*)name.mpBegin);
        result = ok ? 1 : 0;
        WSTR_FREE(typedName);
        WSTR_FREE(name);
    }
    WSTR_FREE_CMDLINE(cmdLine);
    return result;
}

// @ 0x00acaf80
// Same save protocol as 0x00acabe0 but the key is a string and the type-check global is
// DAT_015d8b59.
char FUN_00acaf80(void* pSave, const char* pFileName, const void* pValue, const void* pArg) {
    cWideString cmdLine;
    WSTR_SET_EMPTY_ODD(cmdLine);
    FUN_00694c10(&cmdLine, pValue);

    char result = 1;
    if (cmdLine.mpBegin != cmdLine.mpEnd) {
        cWideString fileName;
        if (pFileName) {
            FUN_0093c5a0(&fileName, pFileName, -1);
        } else {
            fileName.mpBegin = DAT_01667bac;
            fileName.mpEnd = DAT_01667bac;
            fileName.mpCapacityEnd = DAT_01667bac + 1;
        }
        cWideString name;
        name.FUN_0056e2d0(&fileName);
        WSTR_FREE(fileName);

        cWideString typedName;
        FUN_0093c6d0(&typedName, &cmdLine);

        char ok;
        if (name.mpBegin == name.mpEnd) {
            ok = ((char (__thiscall*)(void*, const void*))vc(pSave, 0))(pSave, pArg);
        } else {
            ok = ((char (__thiscall*)(void*, const void*))vc(pSave, 0))(pSave, name.mpBegin);
            if (DAT_015d8b59 && ok)
                ok = ((char (__thiscall*)(void*, const void*, const void*))vc(pSave, 8))(pSave, DAT_013f36bc, pArg);
        }
        if (ok)
            ok = ((char (__thiscall*)(void*, const void*))vc(pSave, 0xc))(pSave, typedName.mpBegin);
        if (ok)
            ok = ((char (__thiscall*)(void*, const void*))vc(pSave, 4))(pSave,
                     name.mpBegin == name.mpEnd ? pArg : (const void*)name.mpBegin);
        result = ok ? 1 : 0;
        WSTR_FREE(typedName);
        WSTR_FREE(name);
    }
    WSTR_FREE_CMDLINE(cmdLine);
    return result;
}

// @ 0x00acb150
struct FourVecDtorStub { void* FUN_00acb150(uchar flags); };
void* FourVecDtorStub::FUN_00acb150(uchar flags) {
    void* self = this;
    *(void**)self = (void*)0x145a184;
    FUN_00ae6970((uchar*)self + 0x50);
    FUN_00ae6970((uchar*)self + 0x3c);
    FUN_00ae6970((uchar*)self + 0x28);
    FUN_00ae6970((uchar*)self + 0x14);
    if (flags & 1) operator_delete(self);
    return self;
}

// @ 0x00acb190
void __fastcall FUN_00acb190(void* self) {
    *(int*)((uchar*)self + 4) -= 0x18;
    uchar* v = *(uchar**)((uchar*)self + 4);
    FUN_00ae6970(v + 4);
    void* o = *(void**)v;
    if (o) ((void (__thiscall*)(void*))vc(o, 4))(o);
}
