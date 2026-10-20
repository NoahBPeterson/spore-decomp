// Slice s00a63dd0 - EA::Audio::Eapd (EA's embedded Pure Data):
//   * the tail of the "EAPd/AssetManager" family whose head lives in slice
//     s00a62ec0: the asset-file loader/parser, its intrusive helper nodes and
//     the hash-bucket / intrusive-list helpers the manager and its child
//     objects are built on,
//   * the small EAPd "class holder" wrappers that hand out shared method
//     tables (0xa643b0 / 0xa64400 / 0xa645c0 / 0xa646a0 ...),
//   * the hash map used for EAPd objects (0xa64ad0 / 0xa64b70 / 0xa64be0 /
//     0xa64c50 / 0xa64cf0).
// Flags: /O2 /MD /Gy /EHsc /TP /GS- /arch:SSE /fp:fast
#include "s00a63dd0.h"

namespace EA { namespace Audio { namespace Eapd {

// ===========================================================================
// @ 0x00a63dd0  EapdAssetManager::Load
// ===========================================================================
bool EapdAssetManager::Load(const char* data, unsigned size, PgSymbol* out)
{
    (void)data; (void)size; (void)out;
    return false;
}

// ===========================================================================
// @ 0x00a64280  EapdAssetManager::ReleaseEntryNode
// ===========================================================================
void EapdAssetManager::ReleaseEntryNode(AssetEntry* node)
{
    char* inner = (char*)node + 0x10;
    ((MapDestroyFace*)inner)->Destroy(*(void**)(inner + 0xc));
    *(void**)(inner + 0x18) = (void*)0x1403934;
    void** vtbl = *(void***)this;
    ((void (__thiscall*)(void*, void*))vtbl[3])(this, node);
}

// ===========================================================================
// @ 0x00a642f0  EapdAssetManager::ReleaseNodeAt34
// ===========================================================================
bool EapdAssetManager::ReleaseNodeAt34(uint32_t key)
{
    bool ok = false;
    char* tree = (char*)this + 0x34;
    void* found;
    ((RBTreeFindFace*)tree)->Find(&found, &key);
    char* val = (char*)found;
    if ((char*)this + 0x38 != val) {
        int* ref = *(int**)(val + 0x14);
        --*ref;
        if (*ref == 0) {
            char* cur = *(char**)((char*)this + 0x3c);
            while (cur != (char*)this + 0x38) {
                if (*(void**)(cur + 0x14) == ref) {
                    --*(int*)(tree + 0x14);
                    void* nx = RBTreeIncrement(cur);
                    RBTreeErase(cur, tree + 4);
                    void** alloc = *(void***)(tree + 0x18);
                    ((void (__thiscall*)(void*, void*))alloc[3])(tree + 0x18, cur);
                    cur = (char*)nx;
                } else {
                    cur = (char*)RBTreeIncrement(cur);
                }
            }
            ((EapdAssetManager*)((char*)this + 4))->ReleaseEntryNode((AssetEntry*)ref);
        }
        ok = true;
    }
    return ok;
}

// ===========================================================================
// @ 0x00a64390  EapdAssetManager::FreeSlot
// ===========================================================================
void* EapdAssetManager::FreeSlot(void* a1, void* a2, void* a3)
{
    return ((AllocFace*)((char*)this + 0x10))->DestroyHelper(0x1c, a1, a2, a3);
}

// ===========================================================================
// @ 0x00a643b0  EapdAssetManager::NewEntryNode
// ===========================================================================
AssetEntry* EapdAssetManager::NewEntryNode(void* a1, void* a2)
{
    AssetEntry* n = (AssetEntry*)((void* (__thiscall*)(void*, unsigned))
        ((*(void***)((char*)this + 0xc))[2]))((char*)this + 0xc, 0x1c);
    if (n != 0) {
        n->mpLink1 = 0;
        n->mpLink0 = 0;
        n->mpFieldC = a1;
        n->mpField8 = a2;
        char* head = (char*)this + 0x4c;
        n->mpLink1 = *(void**)(head + 4);
        n->mpLink0 = head;
        *(void**)(head + 4) = n;
        *(void**)(*(void**)((char*)n + 4)) = n;
    }
    return n;
}

// ===========================================================================
// @ 0x00a64400  EapdAssetManager::AllocFromPool
// ===========================================================================
void* EapdAssetManager::AllocFromPool(void* a1)
{
    (void)a1;
    void* n = *(void**)((char*)this + 0x28);
    if (n) {
        *(void**)((char*)this + 0x28) = *(void**)n;
    } else {
        n = ((void* (__thiscall*)(void*, unsigned))
             ((*(void***)((char*)this + 0x10))[2]))((char*)this + 0x10,
                                                     *(unsigned*)((char*)this + 0x1c));
    }
    if (n) {
        ++*(int*)((char*)this + 0x2c);
        unsigned c = *(unsigned*)((char*)this + 0x2c);
        if (c > *(unsigned*)((char*)this + 0x30))
            *(unsigned*)((char*)this + 0x30) = c;
    }
    return n;
}

// ===========================================================================
// @ 0x00a64470  SlotCtor
// ===========================================================================
AssetSlot* AssetSlot::Ctor()
{
    char* s = (char*)this;
    *(void**)(s + 8) = (void*)gTag15544b4;
    *(void**)(s + 0) = (void*)0x1454fac;
    *(void**)(s + 4) = 0;
    *(void**)(s + 0x14) = 0;
    *(void**)(s + 0x10) = (void*)0x1454fac;
    *(void**)(s + 0x18) = (void*)0x145562c;
    *(void**)(s + 0x20) = 0;
    *(void**)(s + 0x1c) = (void*)0x1454fac;
    *(void**)(s + 0x24) = (void*)0x145562c;
    *(void**)(s + 0x28) = 0;
    *(void**)(s + 0x2c) = 0;
    *(void**)(s + 0x30) = 0;
    *(void**)(s + 0x34) = 0;
    *(void**)(s + 0x38) = 0;
    *(void**)(s + 0x3c) = 0;
    *(void**)(s + 0xc) = (void*)0x14556c0;
    *(void**)(s + 0x40) = 0;
    *(void**)(s + 0x48) = s + 0x44;
    *(void**)(s + 0x44) = s + 0x44;
    *(void**)(s + 0x50) = s + 0x4c;
    *(void**)(s + 0x4c) = s + 0x4c;
    return this;
}

// ===========================================================================
// @ 0x00a644e0  SlotFree
// ===========================================================================
void AssetSlot::Free(void* node)
{
    char* n = (char*)node;
    void* prev = *(void**)(n + 4);
    void* next = *(void**)n;
    *(void**)prev = next;
    *(void**)((char*)next + 4) = prev;
    *(void**)n = 0;
    *(void**)(n + 4) = 0;
    char* alloc = (char*)this + 0xc;
    void** vtbl = *(void***)alloc;
    ((void (__thiscall*)(void*, void*))vtbl[3])(alloc, node);
}

// ===========================================================================
// @ 0x00a64510  EapdAssetManager::DetachList
// ===========================================================================
void EapdAssetManager::DetachList(void* key, void* list)
{
    char* head = (char*)list;
    char* cur = *(char**)head;
    if (cur != head) {
        do {
            char* node = cur;
            cur = *(char**)cur;
            if (*(void**)(node + 0xc) == key) {
                void* prev = *(void**)(node + 4);
                void* nx = *(void**)node;
                *(void**)prev = nx;
                *(void**)((char*)nx + 4) = prev;
                *(void**)node = 0;
                *(void**)(node + 4) = 0;
                char* alloc = (char*)this + 0xc;
                void** vtbl = *(void***)alloc;
                ((void (__thiscall*)(void*, void*))vtbl[3])(alloc, node);
            }
        } while (cur != head);
    }
}

// ===========================================================================
// @ 0x00a64560  EapdAssetManager::FreeAll
// ===========================================================================
bool EapdAssetManager::FreeAll()
{
    char* sent = (char*)this + 0x4c;
    char* cur = *(char**)sent;
    char seen = 0;
    if (cur != sent) {
        char* alloc = (char*)this + 0xc;
        seen = 1;
        do {
            char* next = *(char**)cur;
            char* prev = *(char**)(cur + 4);
            *(char**)prev = next;
            *(char**)(next + 4) = prev;
            *(void**)cur = 0;
            *(void**)(cur + 4) = 0;
            void** vtbl = *(void***)alloc;
            ((void (__thiscall*)(void*, void*))vtbl[3])(alloc, cur);
            cur = next;
        } while (cur != sent);
    }
    return !seen;
}

// ===========================================================================
// @ 0x00a645c0  EapdAssetManager::RearrangeLists
// ===========================================================================
void EapdAssetManager::RearrangeLists()
{
    char* a44 = (char*)this + 0x44;
    char* a4c = (char*)this + 0x4c;
    void* d4c = *(void**)a4c;
    void* d44 = *(void**)a44;
    void* e4c = *(void**)(a4c + 4);
    void* e44 = *(void**)(a44 + 4);
    *(void**)a44 = d4c;
    *(void**)(a44 + 4) = e4c;
    *(void**)a4c = d44;
    *(void**)(a4c + 4) = e44;

    if (*(void**)a44 == a4c) {
        *(void**)(a44 + 4) = a44;
        *(void**)a44 = a44;
    } else {
        void* p = *(void**)(a44 + 4);
        *(void**)p = a44;
        void* q = *(void**)a44;
        *(void**)((char*)q + 4) = a44;
    }
    if (*(void**)a4c == a44) {
        *(void**)(a4c + 4) = a4c;
        *(void**)a4c = a4c;
    } else {
        void* p = *(void**)(a4c + 4);
        *(void**)p = a4c;
        void* q = *(void**)a4c;
        *(void**)((char*)q + 4) = a4c;
    }

    void* cur = *(void**)a44;
    while (cur != a44) {
        void* next = *(void**)cur;
        int r = ((int (__thiscall*)(void*))*(void**)((char*)cur + 8))(cur);
        if (r == 0) {
            void* v = *(void**)((char*)cur + 4);
            *(void**)v = next;
            *(void**)((char*)next + 4) = v;
            *(void**)cur = 0;
            *(void**)((char*)cur + 4) = 0;
            char* alloc = (char*)this + 0xc;
            void** vtbl = *(void***)alloc;
            ((void (__thiscall*)(void*, void*))vtbl[3])(alloc, cur);
        } else {
            void* link = (char*)cur + 4;
            void* tail = *(void**)(a4c + 4);
            *(void**)link = tail;
            *(void**)cur = a4c;
            *(void**)(a4c + 4) = cur;
            *(void**)tail = cur;
        }
        cur = next;
    }
}

// ===========================================================================
// @ 0x00a646a0  EapdAssetManager::ClearLists
// ===========================================================================
__declspec(noinline) void EapdAssetManager::ClearLists(void* a1)
{
    DetachList(a1, (char*)this + 0x44);
    DetachList(a1, (char*)this + 0x4c);
}

// ===========================================================================
// @ 0x00a646d0  ThrowHelper
// ===========================================================================
void ThrowHelper(void* p)
{
    (void)p;
    ((void (__cdecl*)(void*))uThrowTarget)((void*)0x13f5b98);
}

// ===========================================================================
// @ 0x00a646f0  IterHelper::MakeEntryIter
// ===========================================================================
void* IterHelper::MakeEntryIter(void* entry)
{
    void* self = this;
    *(void**)self = *(void**)((char*)entry + 0x34);
    *(void**)((char*)self + 4) = entry;
    return self;
}

// ===========================================================================
// @ 0x00a64710  EapdAssetManager::ResetAndClear
// ===========================================================================
__declspec(noinline) void EapdAssetManager::ResetAndClear()
{
    void* sys = SystemGetAssetManager();
    ((EapdAssetManager*)sys)->ClearLists(this);
}

// ===========================================================================
// @ 0x00a64730  EapdAssetManager::PushNode
// ===========================================================================
bool EapdAssetManager::PushNode(void* node)
{
    bool ok = false;
    if (*(void**)((char*)node + 0x34) == *(void**)this) {
        *(void**)((char*)node + 0x40) = *(void**)((char*)this + 4);
        *(void**)((char*)this + 4) = node;
        ok = true;
    }
    return ok;
}

// ===========================================================================
// @ 0x00a64750  EapdAssetManager::RemoveNode
// ===========================================================================
bool EapdAssetManager::RemoveNode(void* node)
{
    bool ok = false;
    if (node) {
        char* head = *(char**)((char*)this + 4);
        if (head == node) {
            *(void**)((char*)this + 4) = *(void**)(head + 0x40);
            ok = true;
        } else {
            char* cur = *(char**)(head + 0x40);
            if (cur) {
                char* prev = head;
                do {
                    if (cur == node) {
                        *(void**)(prev + 0x40) = *(void**)(cur + 0x40);
                        ok = true;
                        break;
                    }
                    prev = cur;
                    cur = *(char**)(cur + 0x40);
                } while (cur);
            }
        }
    }
    return ok;
}

// ===========================================================================
// @ 0x00a647b0  SendFloatToAll
// ===========================================================================
int SendFloatToAll(void* atom)
{
    char* a = (char*)atom;
    char* base = *(char**)(a + 0xc);
    float f = atom_getfloat(a + 0x10);
    void* n = *(void**)(base + 4);
    while (n) {
        void* c = *(void**)((char*)n + 0x28);
        ++gDepth167545c;
        if (gDepth167545c < 1000) {
            void* e = *(void**)((char*)c + 8);
            while (e) {
                outlet_float_(*(void**)((char*)e + 4), f);
                e = *(void**)e;
            }
        }
        --gDepth167545c;
        n = *(void**)((char*)n + 0x40);
    }
    return 0;
}

// ===========================================================================
// @ 0x00a64820  SendSymbolToAll
// ===========================================================================
int SendSymbolToAll(void* atom)
{
    char* a = (char*)atom;
    char* base = *(char**)(a + 0xc);
    PgSymbol sym;
    atom_getsymbol(&sym, a + 0x10);
    void* n = *(void**)(base + 4);
    while (n) {
        void* c = *(void**)((char*)n + 0x28);
        outlet_list_(c, (void*)sym.mHash, (void*)sym.mpName);
        n = *(void**)((char*)n + 0x40);
    }
    return 0;
}

// ===========================================================================
// @ 0x00a64870  SendSymbolList
// ===========================================================================
int SendSymbolList(void* atom)
{
    void* n = *(void**)((char*)(*(void**)((char*)atom + 0xc)) + 4);
    while (n) {
        outlet_symbol_(*(void**)((char*)n + 0x28));
        n = *(void**)((char*)n + 0x40);
    }
    return 0;
}

// ===========================================================================
// @ 0x00a648a0  EapdAssetManager::MakeFloatHandler
// ===========================================================================
bool EapdAssetManager::MakeFloatHandler(float f)
{
    bool ok = false;
    if (*(int*)this == 0) {
        void* sys = SystemGetAssetManager();
        AssetEntry* e = ((EapdAssetManager*)sys)->NewEntryNode(this, (void*)0xa647b0);
        if (e) {
            e->mKind10 = 1;
            e->mFloat14 = f;
            ok = true;
        }
    }
    return ok;
}

// ===========================================================================
// @ 0x00a648f0  EapdAssetManager::MakeSymbolHandler
// ===========================================================================
bool EapdAssetManager::MakeSymbolHandler(const char* s)
{
    bool ok = false;
    if (*(int*)this == 1) {
        PgSymbol sym;
        gensym(&sym, s);
        void* sys = SystemGetAssetManager();
        AssetEntry* e = ((EapdAssetManager*)sys)->NewEntryNode(this, (void*)0xa64820);
        if (e) {
            e->mKind10 = 2;
            *(unsigned*)&e->mFloat14 = sym.mHash;
            e->mpField18 = (void*)sym.mpName;
            ok = true;
        }
    }
    return ok;
}

// ===========================================================================
// @ 0x00a64950  EapdAssetManager::MakeListHandler
// ===========================================================================
bool EapdAssetManager::MakeListHandler(void)
{
    bool ok = false;
    if (*(int*)this == 2) {
        void* sys = SystemGetAssetManager();
        void* e = ((EapdAssetManager*)sys)->NewEntryNode(this, (void*)0xa64870);
        if (e)
            ok = true;
    }
    return ok;
}

// ===========================================================================
// @ 0x00a649b0  EapdAssetManager::GetTwoWords
// ===========================================================================
void* EapdAssetManager::GetTwoWords(void* out)
{
    char* p = *(char**)((char*)this + 0x70);
    void* a = *(void**)(p + 0x64);
    void* b = *(void**)(p + 0x68);
    *(void**)out = a;
    *(void**)((char*)out + 4) = b;
    return out;
}


// ===========================================================================
// @ 0x00a649d0  EapdAssetManager::RealizeDollar
// ===========================================================================
void* EapdAssetManager::RealizeDollar(void* out)
{
    void* g = *(void**)((char*)this + 0x70);
    canvas_realizedollar2(out, g);
    return out;
}

// ===========================================================================
// @ 0x00a64a10  PauseCanvas
// ===========================================================================
int PauseCanvas(void* entry)
{
    float f = *(float*)((char*)entry + 0x14);
    void* c = *(void**)((char*)entry + 0xc);
    canvas_pause_(*(void**)((char*)c + 0x70), f);
    return 0;
}

// ===========================================================================
// @ 0x00a64a50  EapdAssetManager::DisposeArray
// ===========================================================================
void EapdAssetManager::DisposeArray(void** arr, unsigned n)
{
    for (unsigned i = 0; i < n; ++i) {
        char* node = (char*)arr[i];
        if (node) {
            char* alloc = (char*)this + 0x1c;
            while (node) {
                char* cur = node;
                node = *(char**)(node + 0xc);
                void** vtbl = *(void***)alloc;
                ((void (__thiscall*)(void*, void*))vtbl[3])(alloc, cur);
            }
        }
        arr[i] = 0;
    }
}

// ===========================================================================
// @ 0x00a64aa0  EapdAssetManager::MakeFloatHandler2
// ===========================================================================
void EapdAssetManager::MakeFloatHandler2(uint8_t v)
{
    void* sys = SystemGetAssetManager();
    AssetEntry* e = ((EapdAssetManager*)sys)->NewEntryNode((void*)this, (void*)0xa64a10);
    e->mKind10 = 1;
    e->mFloat14 = (float)v;
}

// ===========================================================================
// @ 0x00a64ad0  HashMapResize
// ===========================================================================
void ObjectHashMap::Resize(unsigned newCount)
{
    unsigned oldCount = mNumBuckets08;
    unsigned* oldBuckets = (unsigned*)mpBuckets04;
    void* alloc = (char*)this + 0x1c;
    void** vtbl = *(void***)alloc;
    void* fn = vtbl[2];
    unsigned* nb = (unsigned*)((void* (__thiscall*)(void*, unsigned))fn)(alloc, newCount * 4 + 4);
    memset_f(nb, 0, newCount * 4);
    nb[newCount] = 0xffffffff;
    unsigned i = 0;
    unsigned* newb = nb;
    if (oldCount > 0) {
        do {
            unsigned* n = (unsigned*)oldBuckets[i];
            if (n) {
                unsigned* b = newb;
                do {
                    unsigned h = *n % newCount;
                    unsigned* next = (unsigned*)((char*)n + 0xc);
                    unsigned* node = n;
                    mpBuckets04 = 0;
                    oldBuckets[i] = (unsigned)*(unsigned**)((char*)n + 0xc);
                    node = n;
                    unsigned* slot = b + h;
                    *(unsigned**)((char*)n + 0xc) = (unsigned*)*slot;
                    *slot = (unsigned)n;
                    n = (unsigned*)oldBuckets[i];
                } while (n);
            }
            ++i;
        } while (i < oldCount);
    }
    if (oldCount > 1) {
        void** a2 = *(void***)((char*)this + 0x1c);
        void* f2 = a2[3];
        ((void (__thiscall*)(void*, void*))f2)((char*)this + 0x1c, oldBuckets);
    }
    mpBuckets04 = nb;
    mNumBuckets08 = newCount;
}

// ===========================================================================
// @ 0x00a64b70  HashMapDtor
// ===========================================================================
void ObjectHashMap::Dtor()
{
    ((EapdAssetManager*)this)->DisposeArray((void**)mpBuckets04, mNumBuckets08);
    mSize0c = 0;
    if (mNumBuckets08 > 1) {
        void** a = *(void***)((char*)this + 0x1c);
        void* f = a[3];
        ((void (__thiscall*)(void*, void*))f)((char*)this + 0x1c, mpBuckets04);
    }
    *(void**)((char*)this + 0x1c) = (void*)0x1403934;
}

// ===========================================================================
// @ 0x00a64be0  HashMapErase
// ===========================================================================
unsigned ObjectHashMap::Erase(uint32_t* key)
{
    unsigned before = mSize0c;
    unsigned idx = *key % mNumBuckets08;
    unsigned** bucket = (unsigned**)((char*)mpBuckets04 + idx * 4);
    if (*bucket) {
        unsigned* cur = *bucket;
        while (*cur != *key) {
            bucket = (unsigned**)((char*)cur + 0xc);
            cur = *bucket;
            if (!cur)
                break;
        }
        while (*bucket) {
            unsigned* node = *bucket;
            if (*node != *key)
                break;
            *bucket = *(unsigned**)((char*)node + 0xc);
            void** a = *(void***)((char*)this + 0x1c);
            void* f = a[3];
            ((void (__thiscall*)(void*, void*))f)((char*)this + 0x1c, node);
            --mSize0c;
        }
    }
    return before - mSize0c;
}

// ===========================================================================
// @ 0x00a64c50  HashMapClear
// ===========================================================================
void ObjectHashMap::DisposeArray2(void** arr, unsigned n)
{
    for (unsigned i = 0; i < n; ++i) {
        char* node = (char*)arr[i];
        if (node) {
            char* alloc = (char*)this + 0x1c;
            while (node) {
                char* cur = node;
                node = *(char**)(node + 0xc);
                ((EapdAssetManager*)(cur + 4))->ResetAndClear();
                void** vtbl = *(void***)alloc;
                ((void (__thiscall*)(void*, void*))vtbl[3])(alloc, cur);
            }
        }
        arr[i] = 0;
    }
}

// ===========================================================================
// @ 0x00a64cb0  Instance::GetGroup
// ===========================================================================
void* ObjectHashMap::GetGroup(PgSymbol sym)
{
    char* cont = (char*)this + 0xc;
    void* r = 0;
    void* found[2];
    ((HashFace*)cont)->Find(found, &sym);
    unsigned idx = *(unsigned*)(cont + 8);
    void** b = *(void***)(cont + 4);
    if (b[idx] != found[0])
        r = *(void**)((char*)found[0] + 8);
    return r;
}

// ===========================================================================
// @ 0x00a64cf0  ObjectHashMap::Insert
// ===========================================================================
void* ObjectHashMap::Insert(void* out, void* node, void* bucketPtr)
{
    void* first = *(void**)((char*)node + 0xc);
    *(void**)((char*)out + 4) = bucketPtr;
    *(void**)out = first;
    while (*(void**)out == 0) {
        void* p = (char*)*(void**)((char*)out + 4) + 4;
        *(void**)((char*)out + 4) = p;
        *(void**)out = *(void**)p;
    }
    void* c = *(void**)bucketPtr;
    if (c == node) {
        *(void**)bucketPtr = *(void**)((char*)c + 0xc);
    } else {
        void* a = *(void**)((char*)c + 0xc);
        while (a != node) {
            c = a;
            a = *(void**)((char*)c + 0xc);
        }
        *(void**)((char*)c + 0xc) = *(void**)((char*)a + 0xc);
    }
    ((EapdAssetManager*)((char*)node + 4))->ResetAndClear();
    void** a2 = *(void***)((char*)this + 0x1c);
    void* f = a2[3];
    ((void (__thiscall*)(void*, void*))f)((char*)this + 0x1c, node);
    --mSize0c;
    return out;
}

}}}
