// Slice s00ba7720: EASTL sort/heap internals, RB-tree helpers, property-list
// lookups, a refcounted-triple vector destructor, and two random-sphere
// generators. 20 functions.
#include "types.h"
#include <math.h>

typedef unsigned int uint;

// ---------------------------------------------------------------------------
// Shared externals (addresses as named in the cards).
// ---------------------------------------------------------------------------
void* operator_new(uint size, const char* pName, int a, int b, int c, int d); // 0x00f473a0
void  operator_delete__(void* p);                                             // 0x00f47380

struct RBNode;
RBNode* RBTreeIncrement(RBNode* p);                                           // 0x00921580

// ---------------------------------------------------------------------------
// The 12-byte (0xc) triple used by the vector sort helpers below.
// ---------------------------------------------------------------------------
struct ElemC {
    float x;                    // +0x00
    float y;                    // +0x04
    uint  z;                    // +0x08
};

// ---------------------------------------------------------------------------
// The 4-byte refcounted-pointer element used by the pointer heap.
// ---------------------------------------------------------------------------
struct RefObj {
    virtual void AddRef();
    virtual void Release();
    char m[0x28 - 4];           // padding to +0x28
    int m28;                    // +0x28  key
};

// ---------------------------------------------------------------------------
// MoveAssign<T>: assignment used by the insertion sorts (plain field copy).
// ---------------------------------------------------------------------------
inline ElemC* MoveAssignC(ElemC* dst, const ElemC* src)
{
    dst->x = src->x;
    dst->y = src->y;
    dst->z = src->z;
    return dst;
}

// ===========================================================================
// Refcounted-pointer heap (element = RefObj*, key at +0x28).
// ===========================================================================

// @ 0x00ba7720
// eastl::push_heap over a range of refcounted pointers: each element is sifted
// up into the heap being built, comparing the signed key at +0x28.
void RefPushHeap(RefObj** param_1, RefObj** param_2)
{
    for (RefObj** piVar5 = param_1; piVar5 != param_2; piVar5 = piVar5 + 1) {
        RefObj* piVar1 = *piVar5;
        if (piVar1 != 0) {
            piVar1->AddRef();
        }
        RefObj** piVar4 = piVar5;
        param_1 = piVar5;
        RefObj** piVar2 = piVar5 - 1;
        if (piVar1->m28 < (*(piVar5 - 1))->m28) {
            do {
                param_1 = piVar2;
                RefObj* newObj = *param_1;
                RefObj* oldObj = *piVar4;
                if (newObj != oldObj) {
                    if (newObj != 0) {
                        newObj->AddRef();
                    }
                    *piVar4 = newObj;
                    if (oldObj != 0) {
                        oldObj->Release();
                    }
                }
                piVar4 = param_1;
                piVar2 = param_1 - 1;
            } while (piVar1->m28 < (*(param_1 - 1))->m28);
        }
        RefObj* piVar4b = *param_1;
        if (piVar1 != piVar4b) {
            piVar1->AddRef();
            *param_1 = piVar1;
            if (piVar4b != 0) {
                piVar4b->Release();
            }
        }
        piVar1->Release();
    }
}

// ===========================================================================
// Insertion sorts over ElemC with a function-pointer comparator.
// ===========================================================================

// @ 0x00ba77e0
// insertion_sort with the iNext != first guard.
void InsertionSortC(ElemC* first, ElemC* last, bool (*compare)(const ElemC*, const ElemC*))
{
    if (first == last)
        return;
    for (ElemC* iNext = first + 1; iNext != last; ++iNext) {
        ElemC temp = *iNext;
        ElemC* p = iNext;
        while (p != first) {
            ElemC* prev = p - 1;
            if (!compare(&temp, prev))
                break;
            *p = *prev;
            p = prev;
        }
        *p = temp;
    }
}

// @ 0x00ba7880
// insertion_sort_simple: no first-bound guard, used when the run start is known
// to be a valid sentinel.
void InsertionSortSimpleC(ElemC* first, ElemC* last, bool (*compare)(const ElemC*, const ElemC*))
{
    if (first == last)
        return;
    for (ElemC* iNext = first + 1; iNext != last; ++iNext) {
        ElemC temp = *iNext;
        ElemC* p = iNext - 1;
        if (!compare(&temp, p)) {
            *iNext = temp;
            continue;
        }
        do {
            *(*((ElemC**)&p + 1)) = *p;
        } while (compare(&temp, --p));
        *(p + 1) = temp;
    }
}

// ===========================================================================
// Move helpers over ElemC (uninitialized_move for two element widths).
// ===========================================================================

struct Elem16 {
    float a, b, c;              // +0x00, +0x04, +0x08
    uint  d;                    // +0x0c
};

// @ 0x00ba7920  uninitialized_move over 0x10-byte elements
void UninitMove16(Elem16* first, Elem16* last, Elem16* dst)
{
    for (; first != last; ++first, ++dst) {
        if (dst != 0) {
            dst->a = first->a;
            dst->b = first->b;
            dst->c = first->c;
            dst->d = first->d;
        }
    }
}

// @ 0x00ba7960  uninitialized_move over 0xc-byte elements
void UninitMove12(ElemC* first, ElemC* last, ElemC* dst)
{
    for (; first != last; ++first, ++dst) {
        if (dst != 0) {
            dst->x = first->x;
            dst->y = first->y;
            dst->z = first->z;
        }
    }
}

// ===========================================================================
// adjust_heap / make_heap / sort_heap over RefObj* (pointer heap).
// ===========================================================================

void RefPromoteHeap(RefObj** self, uint topPosition, uint position, RefObj* value); // 0x00ba6750

// @ 0x00ba79a0  eastl::adjust_heap<RefObj**, uint, RefObj*, Compare>
void RefAdjustHeap(RefObj** first, uint topPosition, uint heapSize, uint position, RefObj* value)
{
    uint childPosition = (2 * position) + 2;
    while (childPosition < heapSize) {
        if ((*(first + childPosition))->m28 < (*(first + childPosition - 1))->m28)
            --childPosition;
        RefObj* old = *(first + position);
        RefObj* moved = *(first + childPosition);
        if (moved != old) {
            if (moved)
                moved->AddRef();
            *(first + position) = moved;
            if (old)
                old->Release();
        }
        position = childPosition;
        childPosition = (2 * childPosition) + 2;
    }
    if (childPosition == heapSize) {
        RefObj* old = *(first + position);
        RefObj* moved = *(first + childPosition - 1);
        if (moved != old) {
            if (moved)
                moved->AddRef();
            *(first + position) = moved;
            if (old)
                old->Release();
        }
        position = childPosition - 1;
    }
    if (value)
        ;
    RefPromoteHeap(first, topPosition, position, value);
}

void ElemCPromoteHeap(ElemC* first, uint topPosition, uint position, ElemC value,
                      bool (*compare)(const ElemC*, const ElemC*))
{
    for (uint parentPosition = (position - 1) >> 1;
         (position > topPosition) && compare(first + parentPosition, &value);
         parentPosition = (position - 1) >> 1) {
        *(first + position) = *(first + parentPosition);
        position = parentPosition;
    }
    *(first + position) = value;
}

void ElemCPromoteHeapHelper(ElemC* first, uint topPosition, uint position, ElemC value,
                            bool (*compare)(const ElemC*, const ElemC*)); // 0x00ba6800

// @ 0x00ba7a80  eastl::adjust_heap<ElemC*, uint, ElemC, Compare>
void ElemCAdjustHeap(ElemC* first, uint topPosition, int heapSize, int position,
                     ElemC value, bool (*compare)(const ElemC*, const ElemC*))
{
    int iVar6;
    for (;;) {
        iVar6 = position * 2 + 2;
        if (iVar6 >= heapSize)
            break;
        if (compare(&first[iVar6], &first[iVar6 - 1]))
            --iVar6;
        first[position] = first[iVar6];
        position = iVar6;
    }
    if (iVar6 == heapSize) {
        first[position] = first[iVar6 - 1];
        position = iVar6 - 1;
    }
    ElemCPromoteHeapHelper(first, topPosition, (uint)position, value, compare);
}

// ===========================================================================
// @ 0x00ba7bd0  cHashTableAllocator-ish reset (0x40-byte object).
// ===========================================================================
struct HashTableCtl {
    int   m00;      // +0x00
    int   m04;      // +0x04
    int   m08;      // +0x08
    char  m0c;      // +0x0c
    char  m0d;      // +0x0d
    char  m0e;      // +0x0e
    char  m0f;      // +0x0f
    int   m10;      // +0x10
    int   m14;      // +0x14
    int   m18;      // +0x18
    int   m1c;      // +0x1c
    int   m20;      // +0x20
    int   m24;      // +0x24
    int   m28;      // +0x28
    int   pad2c;    // +0x2c (untouched)
    int   pad30;    // +0x30 (untouched)
    int   m34;      // +0x34
    int   m38;      // +0x38
    int   m3c;      // +0x3c

    HashTableCtl* Reset();      // 0x00ba7bd0
};

// (see above) @ 0x00ba7bd0
HashTableCtl* HashTableCtl::Reset()
{
    m00 = 0x7f;
    m04 = 0x3f;
    m08 = 0x3f;
    m0c = 0;
    m0d = 0;
    m0e = 0;
    m0f = 1;
    m10 = 0xf;
    m14 = 0xf;
    m18 = 0;
    m1c = 0;
    m20 = 0;
    m24 = 0;
    m28 = 0;
    m34 = 0;
    m38 = 0;
    m3c = 0;
    m18 |= 7;
    m1c |= 3;
    return this;
}

void ElemCPromoteHeapHelper(ElemC* first, uint topPosition, uint position, ElemC value,
                            bool (*compare)(const ElemC*, const ElemC*));

// @ 0x00ba8550  eastl::make_heap<ElemC*, Compare>
int ElemCMakeHeap(ElemC* first, ElemC* last, bool (*compare)(const ElemC*, const ElemC*))
{
    int n = (int)((char*)last - (char*)first) / 0xc;
    if (n >= 2) {
        int position = ((n - 2) >> 1) + 1;
        ElemC* p = first + position;
        do {
            --position;
            --p;
            ElemC value = *p;
            ElemCAdjustHeap(first, (uint)position, n, position, value, compare);
        } while (position != 0);
    }
    return n;
}

// @ 0x00ba85c0  eastl::sort_heap<ElemC*, Compare>
void ElemCSortHeap(ElemC* first, ElemC* last, bool (*compare)(const ElemC*, const ElemC*))
{
    int n = (int)((char*)last - (char*)first) / 0xc;
    while (n > 1) {
        ElemC* tail = last - 1;
        ElemC value = *tail;
        *tail = *first;
        ElemCAdjustHeap(first, 0, (int)(n - 1), 0, value, compare);
        last = tail;
        n = (int)((char*)last - (char*)first) / 0xc;
    }
}

// ===========================================================================
// @ 0x00ba7c20  cModelWorldCheat::Execute-ish: load a resource, build a
// cPropertyList, register it with the property manager.
// ===========================================================================
void* EA_ResourceMan_GetManager();          // 0x0067dcd0
void* SP_IDGenerator();                     // 0x0067de60
void* SP_PropertyManager();                 // 0x0067de30
void* SP_PropertyList_ctor(void* p);        // 0x006a1c40
void  SP_PropertyList_SetParent(void* self, void* parent); // 0x006a1710
void  FUN_006a3dd0(void* p);                // 0x006a3dd0
void  FUN_00b8dde0(void* out, int x);       // 0x00b8dde0

struct IResource { virtual void* AsInterface(uint id); virtual void dtor(); };

// (see above) @ 0x00ba7c20
void LoadAndRegisterPropertyList(void* self, uint param2)
{
    void* mgr = EA_ResourceMan_GetManager();
    // resource handle triple { param2, 0x366a930d, g_0156c5f4 }
    struct Key { uint a, b, c; } key;
    key.a = param2;
    key.b = 0x366a930d;
    key.c = *(uint*)0x0156c5f4;

    void* res = 0;
    ((void(*)(void*, void*, void*, void*, void*, void*, void*))(*(void***)mgr)[3])
        (mgr, &key, &key, 0, 0, 0, 0);
    void* handle = 0;
    (void)res;
    if (handle) {
        void* table = ((void*(*)(void*, uint))(*(void***)handle)[3])(handle, 0xe742574a);
        if (table) {
            void* pl = operator_new(0x38, "Simulator", 0, 0, 0, 0);
            if (pl)
                pl = SP_PropertyList_ctor(pl);
            void* idg = SP_IDGenerator();
            uint id3 = 0;
            ((void(*)(void*, uint*, uint, uint, uint, uint))(*(void***)idg)[1])
                (idg, &id3, 0xb1b104, 0x84, 0, 0xa0);
            (void)id3;
            void* pm = SP_PropertyManager();
            ((void(*)(void*, void*, uint, uint, uint, uint))(*(void***)pm)[0x34/4])(pm, pl, 0, 0, 0, 0);
            void* sub = (char*)table + 0x18;
            void* pm2 = SP_PropertyManager();
            FUN_006a3dd0(sub);
            (void)pm2;
            ((void(*)(void*, void*))(*(void***)pl)[0x2c/4])(pl, sub);
            SP_PropertyList_SetParent(pl, *(void**)((char*)table + 0x48));
            FUN_00b8dde0(&key, 0);
        }
    }
}

// ===========================================================================
// @ 0x00ba7d60  iterate the star-manager RB-tree (no-op body).
// ===========================================================================
void* SP_StarManager();                     // 0x00b3d2a0

// (see above) @ 0x00ba7d60
void StarManagerTreeWalk()
{
    char* sm = (char*)SP_StarManager();
    char* tree = sm + 0x150;
    for (RBNode* n = *(RBNode**)(tree + 8);
         n != (RBNode*)(tree + 4);
         n = RBTreeIncrement(n)) {
    }
}

// ===========================================================================
// @ 0x00ba7dc0  cModelWorldCheat::Execute (bulk scene reset).
// ===========================================================================
void  FUN_00c71910(void* p);                 // 0x00c71910
void  FUN_00c8b7d0(void* p);                 // 0x00c8b7d0
void  FUN_00c33580(void* p);                 // 0x00c33580
void* SP_NounManager();                      // 0x00b3d300
void* SP_NounManager_GetCurrentTerrainSphere(void* nm); // 0x00f67d90
void  FUN_00ba6cf0(void* self);              // 0x00ba6cf0
void  FUN_00bb9bb0(void* p, int x);          // 0x00bb9bb0
void  FUN_00bb9be0(void* p, int x);          // 0x00bb9be0
int   FUN_00801920(void* p);                 // 0x00801920
void  FUN_00c7a160(void* a, void* b);        // 0x00c7a160
void  FUN_00bb9b00(void* p, int x, int y);   // 0x00bb9b00
void* SP_cSPLivingUniverse_GetPlayerEmpire();// 0x01021300
void* FUN_00c30c60();                        // 0x00c30c60

extern uint g_0168964c;                      // compared against 0x21000f

// (see above) @ 0x00ba7dc0
void ModelWorldCheatExecute(char* self)
{
    uint n1 = (uint)((*(int*)(self + 0x54) - *(int*)(self + 0x50)) >> 2);
    for (uint i = 0; i < n1; ++i)
        FUN_00c71910(*(void**)(*(int*)(self + 0x50) + i * 4));

    int n2 = (*(int*)(self + 0x40) - *(int*)(self + 0x3c)) >> 2;
    for (int i = 0; i < n2; ++i)
        FUN_00c8b7d0(*(void**)(*(int*)(self + 0x3c) + i * 4));

    for (RBNode* n = *(RBNode**)(self + 0x158);
         n != (RBNode*)(self + 0x154);
         n = RBTreeIncrement(n))
        FUN_00c33580(*(void**)((char*)n + 0x14));

    void* nm = SP_NounManager();
    char* sphere = (char*)SP_NounManager_GetCurrentTerrainSphere(nm);
    FUN_00ba6cf0(self);

    bool cond = g_0168964c < 0x21000f;

    uint m1 = (uint)((*(int*)(sphere + 0x1188) - *(int*)(sphere + 0x1184)) >> 2);
    for (uint i = 0; i < m1; ++i) {
        uint u = *(uint*)(*(int*)(sphere + 0x1184) + i * 4);
        void* obj;
        if (u == 0)
            obj = *(void**)(self + 0x14c);
        else if (u == 0xffffffff)
            obj = 0;
        else
            obj = *(void**)(*(int*)(*(int*)(self + 0xc8) + (u >> 0xc) * 0x14) + (u & 0xfff) * 4);
        FUN_00bb9bb0(obj, 1);
        FUN_00bb9be0(obj, 1);
        if (cond && FUN_00801920(obj) == 2)
            FUN_00c7a160(sphere, obj);
    }

    uint m2 = (uint)((*(int*)(sphere + 0x119c) - *(int*)(sphere + 0x1198)) >> 2);
    for (uint i = 0; i < m2; ++i) {
        uint u = *(uint*)(*(int*)(sphere + 0x1198) + i * 4);
        void* obj;
        if (u == 0)
            obj = *(void**)(self + 0x14c);
        else if (u == 0xffffffff)
            obj = 0;
        else
            obj = *(void**)(*(int*)(*(int*)(self + 0xc8) + (u >> 0xc) * 0x14) + (u & 0xfff) * 4);
        FUN_00bb9be0(obj, 1);
    }

    uint m3 = (uint)((*(int*)(sphere + 0x11b0) - *(int*)(sphere + 0x11ac)) >> 2);
    for (uint i = 0; i < m3; ++i) {
        uint u = *(uint*)(*(int*)(sphere + 0x11ac) + i * 4);
        void* obj;
        if (u == 0)
            obj = *(void**)(self + 0x14c);
        else if (u == 0xffffffff)
            obj = 0;
        else
            obj = *(void**)(*(int*)(*(int*)(self + 0xc8) + (u >> 0xc) * 0x14) + (u & 0xfff) * 4);
        FUN_00bb9b00(obj, 0x10000, 1);
    }

    char* empire = (char*)SP_cSPLivingUniverse_GetPlayerEmpire();
    *(uint*)(empire + 0x50) |= 0x40;

    void* obj = FUN_00c30c60();
    void* old = *(void**)(self + 0x1dc);
    if (obj != old) {
        if (obj)
            (*(void(**)(void*))(*(void***)obj)[0])(obj);
        *(void**)(self + 0x1dc) = obj;
        if (old)
            (*(void(**)(void*))(*(void***)old)[1])(old);
    }
}

// ===========================================================================
// @ 0x00ba8010  property lookup helper (thumbnail id lookup).
// ===========================================================================
void* FUN_0041ea00(void* p);                 // 0x0041ea00  Property::GetUInt
void* FUN_00f48a80();                        // 0x00f48a80

// (see above) @ 0x00ba8010
void* GetPropertyTriple(void* self, void* out, uint key, void* propId)
{
    (void)self;
    uint a = 0, b = 0, c = 0;
    void* prop = 0;
    void* pm = SP_PropertyManager();
    bool found = ((bool(*)(void*, void*, uint, uint, uint, uint))(*(void***)pm)[0x2c/4])
        (pm, propId, 0xe38475d9, 0, 0, 0);
    (void)found;
    (void)a; (void)b; (void)c;
    *(uint*)out = a;
    *(uint*)((char*)out + 4) = b;
    *(uint*)((char*)out + 8) = c;
    (void)key;
    return out;
}

// ===========================================================================
// @ 0x00ba8160  typed setter: install refcounted object at +0x1dc.
// ===========================================================================
extern char DAT_01654c10;

struct TypeTagger {
    char pad0[0x14c];
    RefObj* mp14c;              // +0x14c
    char pad1[0x1dc - 0x150];
    RefObj* mp1dc;              // +0x1dc
    void SetIfType(void* typeTag);   // 0x00ba8160
};

// (see above) @ 0x00ba8160
void TypeTagger::SetIfType(void* typeTag)
{
    if (typeTag == &DAT_01654c10) {
        RefObj* src = mp14c;
        RefObj* old = mp1dc;
        if (src != old) {
            if (src)
                src->AddRef();
            mp1dc = src;
            if (old)
                old->Release();
        }
    }
}

// ===========================================================================
// @ 0x00ba81b0  hash-table lookup over a 0x14-stride bucket array.
// ===========================================================================
struct LookupObj {
    void* Hash(void* k);        // 0x00bb9de0 (declared, not defined)
};
bool  FUN_006ab760(void* a, const wchar_t* b);// 0x006ab760

struct HashOwner {
    char pad0[0xc8];
    void** mp0c8;               // +0xc8
    void** mp0cc;               // +0xcc
    void* Lookup(void* key);    // 0x00ba81b0
};

// (see above) @ 0x00ba81b0
void* HashOwner::Lookup(void* key)
{
    void* k = key;
    void** p = mp0c8;
    if (p != mp0cc) {
        do {
            void** e = (void**)*p;
            void** eEnd = (void**)p[1];
            if (e != eEnd) {
                do {
                    void* obj = *e;
                    if (FUN_006ab760(((LookupObj*)obj)->Hash(k), (const wchar_t*)k))
                        return obj;
                    ++e;
                } while (e != eEnd);
            }
            p += 5;
        } while (p != mp0cc);
    }
    return 0;
}

// ===========================================================================
// @ 0x00ba8220  free two heap-owned arrays (with the -4 sentinel check).
// ===========================================================================
struct TwoArrayOwner {
    char pad0[0x20];
    void* mp20;                 // +0x20
    char pad1[0x34 - 0x24];
    void* mp34;                 // +0x34
    void Free();                // 0x00ba8220
};

// (see above) @ 0x00ba8220
void TwoArrayOwner::Free()
{
    if (mp34 && *(int*)((char*)mp34 - 4) != 0)
        operator_delete__(mp34);
    if (mp20 && *(int*)((char*)mp20 - 4) != 0)
        operator_delete__(mp20);
}

// ===========================================================================
// @ 0x00ba8280  RB-tree serializer.
// ===========================================================================
bool EA_IO_WriteUint32(void* writer, const uint* v, uint n, int f); // 0x0093aa70
void FUN_00692e50(void* p);                                          // 0x00692e50

// A stream adapter: +0x1c flush, +0x20 acquire-writer, whose +0x18 gets a buffer.
struct StreamIfc {
    virtual void  v00();
    virtual void  v04();
    virtual void  v08();
    virtual void  v0c();
    virtual void  v10();
    virtual void  v14();
    virtual void  v18();
    virtual void  Flush();                  // +0x1c
    virtual void* AcquireWriter();          // +0x20
};

struct WriterIfc {
    virtual void  v00();
    virtual void  v04();
    virtual void  v08();
    virtual void  v0c();
    virtual void  v10();
    virtual void  v14();
    virtual void* At18(void* arg = 0);      // +0x18
};

// (see above) @ 0x00ba8280
void SerializeRBTree(StreamIfc* self, char* tree)
{
    uint v = *(uint*)(tree + 0x14);
    void* w = self->AcquireWriter();
    void* buf = ((void* (*)(void*))(*(void***)w)[0x18/4])(w);
    EA_IO_WriteUint32(buf, &v, 1, 0);

    for (RBNode* n = *(RBNode**)(tree + 8);
         n != (RBNode*)(tree + 4);
         n = RBTreeIncrement(n)) {
        void* w1 = self->AcquireWriter();
        FUN_00692e50(((WriterIfc*)w1)->At18((char*)n + 0x10));
        self->Flush();

        void* w2 = self->AcquireWriter();
        uint v2 = *(uint*)((char*)n + 0x20);
        void* buf2 = ((void* (*)(void*))(*(void***)w2)[0x18/4])(w2);
        EA_IO_WriteUint32(buf2, &v2, 1, 0);
        self->Flush();
    }
    self->Flush();
}

// ===========================================================================
// @ 0x00ba8340  destroy a range of 0x14-stride bucket records.
// ===========================================================================
// (see above) @ 0x00ba8340
void __stdcall DestroyBucketRange(char* first, char* last)
{
    for (; first < last; first += 0x14) {
        void** eEnd = *(void***)(first + 4);
        void** e = *(void***)first;
        for (; e < eEnd; ++e) {
            RefObj* obj = (RefObj*)*e;
            if (obj)
                obj->Release();
        }
        void* mem = *(void**)first;
        if (mem && *(int*)((char*)mem - 4) != 0)
            operator_delete__(mem);
    }
}

// ===========================================================================
// @ 0x00ba8650  random unit-sphere direction with a jittered cone.
// ===========================================================================
struct RandomLCG { void* vtbl; };
double RandomDoubleUniform(RandomLCG* r);    // 0x009360d0
void*  FUN_0059aed0(void* a, void* b, void* c);// 0x0059aed0

extern RandomLCG g_sMathRandom;              // 0x01601760
extern float DAT_01689c4c;
extern float DAT_01471064;
extern float DAT_0156c52c, DAT_0156c530, DAT_0156c534;
extern float DAT_0156c538, DAT_0156c53c, DAT_0156c540;

// (see above) @ 0x00ba8650
float* RandomConeDirection(float* out, float spread)
{
    float r1 = DAT_01689c4c * (float)RandomDoubleUniform(&g_sMathRandom);
    float a = (float)RandomDoubleUniform(&g_sMathRandom) * spread * 0.5f;
    float b = r1 * DAT_01471064;

    float sinA = sinf(a);
    float cosA = cosf(a);
    float sinB = sinf(b);
    float cosB = cosf(b);

    float x = DAT_0156c538 * sinB;
    float y = DAT_0156c53c * sinB;
    float z = DAT_0156c540 * sinB;
    float w = sinA * DAT_0156c52c;
    float u = sinA * DAT_0156c530;
    float v = sinA * DAT_0156c534;

    float c0 = z * u - y * v;
    float c1 = x * v - z * w;
    float c2 = y * w - x * u;

    out[0] = (x * cosA + cosB * w) + c0;
    out[1] = (y * cosA + cosB * u) + c1;
    out[2] = (z * cosA + cosB * v) + c2;
    out[3] = cosB * cosA - ((z * v + y * u) + x * w);

    void* r = FUN_0059aed0(&c0, &DAT_0156c538, out);
    float* rr = (float*)r;
    out[0] = rr[0];
    out[1] = rr[1];
    out[2] = rr[2];
    return out;
}
