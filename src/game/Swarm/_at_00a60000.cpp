// src/game/Swarm/_at_00a60000.cpp -- migrated from slice(s) s00a6dfc0 by tools/migrate/rewrite.py
// Object file: Swarm/_at_00a60000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/ArgScript/cArguments.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  MakeCaseInsensitive(void* s);                              // 0x8409b0
extern "C" void* EAAllocate(unsigned size, const char* a, int b, int c, const char* file, int line); // 0xf473a0
extern "C" void  operator_delete__(void* p);                                // 0xf47380
extern "C" int   v005f7870r(const void* a, const void* b, int n);           // 0x5f7870 returns the ordering
extern "C" void* v009215c0(void* node);                                     // 0x9215c0 RBTreeDecrement
extern "C" bool  v00812210(void* a, void* b);                              // 0x812210 key compare
extern "C" void* v00898b80(void* out, void* a, void* b, void* c, void* d);  // 0x898b80 uninitialized_copy
extern "C" void* v00abced0(void* a, void* b, void* c);                      // 0xabced0 copy_backward
extern "C" void* v00a177f0(void* a, void* b, const void* v);                // 0xa177f0 fill
extern "C" void* v006e5760(void* a, unsigned n, const void* v);             // 0x6e5760 uninitialized_fill_n
extern "C" void* v00a11310(const void* a, const void* b, void* c);          // 0xa11310 memmove
extern "C" void* v007e2ea0(void* out, void* ht);                            // 0x7e2ea0 hashtable find
extern "C" void  v00a6e570(void* out, void* node, void* key, int side);     // 0xa6e570 map insert-node
extern const char  kEaStlName[];    // 0x13f2150 "EASTL"
extern const char  kEaAllocFile[];  // 0x13ebb38 EASTL allocator.h
extern const float kOne;            // 0x1485720 1.0f
extern const float gFloatA;         // 0x1676a0c
extern const float gFloatB;         // 0x1676a10
extern const float gFloatC;         // 0x1676a14
#include <string.h>

// ---- items of slice s00a6dfc0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void  MakeCaseInsensitive(void* s);                              // 0x8409b0
extern "C" void* EAAllocate(unsigned size, const char* a, int b, int c, const char* file, int line); // 0xf473a0
extern "C" void  operator_delete__(void* p);                                // 0xf47380
extern "C" int   v005f7870r(const void* a, const void* b, int n);           // 0x5f7870 returns the ordering
extern "C" void* v009215c0(void* node);                                     // 0x9215c0 RBTreeDecrement
extern "C" bool  v00812210(void* a, void* b);                              // 0x812210 key compare
extern "C" void* v00898b80(void* out, void* a, void* b, void* c, void* d);  // 0x898b80 uninitialized_copy
extern "C" void* v00abced0(void* a, void* b, void* c);                      // 0xabced0 copy_backward
extern "C" void* v00a177f0(void* a, void* b, const void* v);                // 0xa177f0 fill
extern "C" void* v006e5760(void* a, unsigned n, const void* v);             // 0x6e5760 uninitialized_fill_n
extern "C" void* v00a11310(const void* a, const void* b, void* c);          // 0xa11310 memmove
extern "C" void* v007e2ea0(void* out, void* ht);                            // 0x7e2ea0 hashtable find
extern "C" void  v00a6e570(void* out, void* node, void* key, int side);     // 0xa6e570 map insert-node
extern const char  kEaStlName[];    // 0x13f2150 "EASTL"
extern const char  kEaAllocFile[];  // 0x13ebb38 EASTL allocator.h
extern const float kOne;            // 0x1485720 1.0f
extern const float gFloatA;         // 0x1676a0c
extern const float gFloatB;         // 0x1676a10
extern const float gFloatC;         // 0x1676a14
namespace EA {
namespace Swarm {
struct EString {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    void* mpAlloc;      // +0x0c
    void assign(const char* first, const char* last);   // 0x00454cb0
};
}
}
namespace EA {
namespace Swarm {
struct DrawInfoTarget;
}
}
namespace EA {
namespace Swarm {
class cEffectsParser { public:
    char      _pad00[0x10];
    unsigned  mFlags;               // +0x10
    char      _pad14[0x0c];
    void*     mpColl;               // +0x20
    char      _pad24[0x20];
    int       m44;                  // +0x44
    char      _pad48[0x30];
    int       m78;                  // +0x78
    char      _pad7c[0x10];
    void*     mpSaveColl;           // +0x8c
    char      _pad90[0x28];
    char      mEditors[0x13 * 0x20]; // +0xb8
    char      mName[0x10];          // +0x3c4

    long long EffectsMapID(const char* s);                          // 00a6e600
    long long MapFindA(const char* s);                              // 00a6eaf0
    long long MapFindB(const char* s, int idx);                     // 00a6eb60
    long long MapFindC(const char* s, int idx);                     // 00a6ebd0
    long long LookupRes(int idx, const char* s);                    // 00a6ec40
    void      ParseDrawInfoOptions(void* args, void* obj, DrawInfoTarget* t); // 00a6ed80
    int       GetInheritedA(int a, int depth, void* c);             // 00a6f090
    int       GetInheritedB(int a, int depth, void* c);             // 00a6f0d0
};
}
}
namespace EA {
namespace Swarm {
struct DrawInfoTarget {
    int      m00;               // +0x00
    int      m04;               // +0x04
    char     m08;               // +0x08
    char     mType;             // +0x09 (0xf = text; else decal)
    char     mFlags;            // +0x0a
    char     mBuffer;           // +0x0b
    short    mLayer;            // +0x0c
    char     _pad0e[2];
    float    mSortOffset;       // +0x10
    char     _pad14[4];
    unsigned mResA;             // +0x18
    unsigned mResB;             // +0x1c
};
}
}
namespace EA {
namespace Swarm {
struct Matrix3 {
    float m[12];
    void Assign(const float* src);      // 0x0041cb40
};
}
}
namespace EA {
namespace Swarm {
extern const float gMatIdent[12];       // 0x1676ab8 identity matrix block
}
}
namespace EA {
namespace Swarm {
struct VecBase {
    char*  mpBegin;         // +0x00
    char*  mpEnd;           // +0x04
    char*  mpCapacity;      // +0x08
    char*  Append(void* first, void* last);          // 0xa6d8c0
    void   FixTail(char* p);                         // 0x7e2be0
};
}
}
namespace EA {
namespace Swarm {
class cEffectsManager { public:
    char      _pad00[0x2c];
    void**    mpCollBegin;          // +0x2c (vector of ICollection*)
    void**    mpCollEnd;            // +0x30
    void**    mpCollCapacity;       // +0x34
    char      _pad38[0x224 - 0x38];
    void*     mpHashF0;             // +0x224
    void**    mpBuckets;            // +0x228 (HashTable.mpBucketArray)
    int       mnBucketCount;        // +0x22c
    int       mnElementCount;       // +0x230
    void      FUN_00a6dfc0(void* vec);      // 00a6dfc0
    bool      FUN_00a6e050(void* p);        // 00a6e050
    void      FUN_00a6e320(VecBase* vec, void* b, void* c);  // 00a6e320
    void      FUN_00a6e3e0(VecBase* vec, void* b);           // 00a6e3e0
    void*     FUN_00a6e4b0();                                // 00a6e4b0
};
}
}
// ---- items of slice s00a6dfc0 end

// @ 0x00a6e4b0
namespace EA { namespace Swarm {
void* cEffectsManager::FUN_00a6e4b0()
{
    char* esi = (char*)this;
    *(int*)(esi + 0) = 0x40;
    int zc = 0;
    int zb = 0;
    *(int*)(esi + 4) = zb;
    *(short*)(esi + 0x0a) = (short)zc;
    int za = 0;
    *(short*)(esi + 0x08) = (short)za;
    *(float*)(esi + 0x0c) = gFloatA;
    *(float*)(esi + 0x10) = gFloatB;
    *(float*)(esi + 0x14) = gFloatC;
    *(float*)(esi + 0x18) = kOne;
    ((Matrix3*)(esi + 0x1c))->Assign(gMatIdent);
    float one = kOne;
    *(char*)(esi + 0x40) = (char)zb;
    *(char*)(esi + 0x41) = (char)zb;
    *(int*)(esi + 0x44) = zb;
    *(int*)(esi + 0x48) = zb;
    *(int*)(esi + 0x4c) = zb;
    int za2 = 0;
    int zd = 0;
    *(short*)(esi + 0x7a) = (short)za2;
    *(int*)(esi + 0x70) = zb;
    *(int*)(esi + 0x74) = zb;
    *(float*)(esi + 0x58) = one;
    *(float*)(esi + 0x5c) = one;
    *(float*)(esi + 0x60) = one;
    *(float*)(esi + 0x64) = one;
    *(float*)(esi + 0x68) = one;
    *(float*)(esi + 0x6c) = one;
    *(short*)(esi + 0x78) = (short)zd;
    *(float*)(esi + 0x7c) = one;
    *(int*)(esi + 0x80) = -1;
    return esi;
}
}}  // namespace EA::Swarm

// @ 0x00a6e6e0
namespace EA { namespace Swarm {
void FUN_00a6e6e0(void* self, void* out, int* key)
{
    char* ebx = (char*)self;
    char* puVar8 = ebx + 4;
    char bVar9 = 1;
    if (*(void**)(ebx + 0xc) != 0) {
        int iVar1 = *key;
        int iVar6 = key[1] - iVar1;
        int local_4 = iVar6;
        char* puVar4 = *(char**)(ebx + 0xc);
        for (;;) {
            puVar8 = puVar4;
            int iVar7 = *(int*)(puVar8 + 0x14) - *(int*)(puVar8 + 0x10);
            int local_8 = iVar7;
            int* piVar5 = &local_8;
            if (iVar6 <= iVar7)
                piVar5 = &local_4;
            int cmp = v005f7870r((void*)iVar1, *(void**)(puVar8 + 0x10), *piVar5);
            if (cmp == 0) {
                if (iVar6 < iVar7)
                    cmp = -1;
                else
                    cmp = (iVar7 < iVar6);
            }
            bVar9 = cmp < 0;
            puVar4 = bVar9 ? *(char**)(puVar8 + 4) : *(char**)puVar8;
            if (puVar4 == 0)
                break;
        }
    }
    char* puVar4 = puVar8;
    if (bVar9) {
        if (puVar8 == *(char**)(ebx + 8))
            goto do_insert;
        puVar4 = (char*)v009215c0(puVar8);
    }
    if (v00812210(puVar4 + 0x10, key)) {
    do_insert:
        v00a6e570(&key, puVar8, key, 0);
        *(int*)out = (int)key;
        *((char*)out + 4) = 1;
        return;
    }
    *(int*)out = (int)puVar4;
    *((char*)out + 4) = 0;
}
}}  // namespace EA::Swarm

// @ 0x00a6e7e0
namespace EA { namespace Swarm {
void FUN_00a6e7e0(void* self, char* dst, unsigned count, void* val)
{
    char* esiSelf = (char*)self;
    char* pBegin = *(char**)esiSelf;
    char* pEnd = *(char**)(esiSelf + 4);
    unsigned capacity = (unsigned)((*(char**)(esiSelf + 8) - pEnd) / 0xc);
    if (capacity >= count) {
        if (count == 0)
            return;
        int local_c = *(int*)val;
        char* oldEnd = pEnd;
        int local_8 = ((int*)val)[1];
        int local_4 = ((int*)val)[2];
        unsigned have = (unsigned)((pEnd - dst) / 0xc);
        if (count < have) {
            unsigned n = count * 0xc;
            char* src = oldEnd - count * 0xc;
            v00898b80(&val, src, oldEnd, oldEnd, dst);
            v00abced0(dst, src, oldEnd);
            *(int*)(esiSelf + 4) += n;
            v00a177f0(dst, dst + n, &local_c);
            return;
        }
        unsigned extra = count - have;
        v006e5760(oldEnd, extra, &local_c);
        *(int*)(esiSelf + 4) += extra * 0xc;
        v00898b80(&dst, dst, oldEnd, *(void**)(esiSelf + 4), dst);
        *(int*)(esiSelf + 4) += have * 0xc;
        v00a177f0(dst, oldEnd, &local_c);
        return;
    }
    unsigned oldCount = (unsigned)((pEnd - pBegin) / 0xc);
    unsigned cap2 = oldCount * 2;
    if (oldCount == 0)
        cap2 = 1;
    unsigned need = oldCount + count;
    if (need > cap2)
        cap2 = need;
    void* newBuf;
    if (cap2 == 0)
        newBuf = 0;
    else
        newBuf = EAAllocate(cap2 * 0xc, kEaStlName, 0, 0, kEaAllocFile, 0xd1);
    char* mid = (char*)v00a11310(pBegin, dst, newBuf);
    v006e5760(mid, count, val);
    char* fin = (char*)v00a11310(dst, pEnd, mid + count * 0xc);
    if (pBegin != 0 && *(int*)(pBegin - 4) != 0)
        operator_delete__(pBegin);
    *(char**)esiSelf = (char*)newBuf;
    *(char**)(esiSelf + 4) = fin;
    *(char**)(esiSelf + 8) = (char*)newBuf + cap2 * 0xc;
}
}}  // namespace EA::Swarm

// @ 0x00a6eaf0
namespace EA { namespace Swarm {
long long cEffectsParser::MapFindA(const char* s)
{
    void* self = this;
    char* edi = (char*)self;
    char* p = (char*)s;
    char* q = p + 1;
    do { } while (*p++ != 0);
    int len = (int)(p - q);
    char* esi = edi + 0x3c4;
    ((EString*)esi)->assign(s, s + len);
    MakeCaseInsensitive(esi);
    void* local_8[2];
    char* tbl = edi + 0x24;
    v007e2ea0(local_8, tbl);
    int ecx = *(int*)(tbl + 8);
    int edx = *(int*)(tbl + 4);
    long long r = *(int*)((char*)local_8[0] + 0x10);
    if ((int)local_8[0] == *(int*)(edx + ecx * 4))
        r = -1;
    return r;
}
}}  // namespace EA::Swarm

// @ 0x00a6eb60
namespace EA { namespace Swarm {
long long cEffectsParser::MapFindB(const char* s, int idx)
{
    void* self = this;
    char* edi = (char*)self;
    char* esi = edi + 0x3c4;
    const char* p = s;
    do { } while (*p++ != 0);
    ((EString*)esi)->assign(s, p - 1);
    MakeCaseInsensitive(esi);
    char* tbl = *(char**)(edi + 0x44) + idx * 0x20;
    void* local_8[2];
    v007e2ea0(local_8, tbl);
    int ecx = *(int*)(tbl + 8);
    int edx = *(int*)(tbl + 4);
    if ((int)local_8[0] == *(int*)(edx + ecx * 4))
        return -1;
    return *(int*)((char*)local_8[0] + 0x10);
}
}}  // namespace EA::Swarm
