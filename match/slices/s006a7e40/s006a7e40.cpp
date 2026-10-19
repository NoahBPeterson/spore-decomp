// Slice s006a7e40 — SP::cPropertyManager preload + EASTL property-hashtable helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

void* EASTL_allocator_allocate(uint32_t size, const char* name, int flags, int debugFlags, const char* file, int line); // 0x00f473a0
void  EASTL_allocator_deallocate(void* p);   // 0x00f47380

#define APP_ALLOCATOR_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

// ===========================================================================
// SP::cPropertyManager::PreloadPropertyLists
// ===========================================================================

// Minimal receiver view: the retail cPropertyManager derives from several interfaces and
// carries a resource-manager pointer plus the preloaded-list vector around +0x1c0.
struct cPropertyManager {
    char    pad00[0x1c0];
    char**  mpPreloadedBegin;   // +0x1c0 (approximate)

    void PreloadPropertyLists();
};

// Out-of-line helpers of the preload pipeline (real retail VAs).  The resource-manager / record
// interaction is virtual (vtable slots), so those are modelled with __thiscall function-pointer
// calls at the documented slot offsets; the free calls below are direct and annotated.
struct RecQuery;                 // resource-record query object returned by FUN_006abf00
struct Key128 {                  // 0x14-byte record key used by the walk
    void*  mVtbl;                // +0x00  0x013eb898
    int    mField4;              // +0x04  -1
    int    mField8;              // +0x08  -1
    int    mFieldC;              // +0x0c  0x00b1b104
    int    mField10;             // +0x10  -1
};

struct Manager;                  // EA::ResourceMan::Manager
Manager* GetResManager();                                   // 0x0067dcd0
RecQuery* QueryResourceRecords();                           // 0x006abf00
void*     GetAllocator();                                   // 0x00925cb0 (default allocator)
void*     operator_newx(uint32_t, const char*, int, int, int, int); // 0x00f473a0
void      operator_deletex(void*);                          // 0x00f47380
void*     PropertyListCtor(void* self, const char* name);   // 0x006a1b90
void      RegisterPropertyList(void* list);                 // 0x006ad010
void*     MapFindKey(void* map, const Key128* key);         // 0x0041cd60
void      MapInsertValue(void* vec, void* pos, const void* val); // 0x00690c90
void*     MapFindRef(void* map, const void* ref, void* out); // 0x0041fb20
void*     VariantToSubItem();                               // 0x006bb640
void      SetPropertyListParent(void* list, void* parent);// 0x006a1710

// __thiscall vtable-slot helpers (slot offsets in bytes).
typedef char (__thiscall *Fn_vt_ret_char)(void*);
typedef char (__thiscall *Fn_vt_char_i)(void*, int);
typedef char (__thiscall *Fn_vt_char_item)(void*, const void*, int);
typedef void (__thiscall *Fn_vt_vec_key)(void*, void* vec, void* key);
typedef char (__thiscall *Fn_vt_char_pp)(void*, void* a, void* b, void* out);
typedef void (__thiscall *Fn_vt_void_void)(void*, void*);

static char VtCall_c_i(void* obj, int slot, int arg)
{
    return (*(Fn_vt_char_i*)(*(char***)obj + slot / 4))(obj, arg);
}
static void VtCall_vec_key(void* obj, int slot, void* vec, void* key)
{
    (*(Fn_vt_vec_key*)(*(char***)obj + slot / 4))(obj, vec, key);
}
static char VtCall_c_item(void* obj, int slot, const void* item, int arg)
{
    return (*(Fn_vt_char_item*)(*(char***)obj + slot / 4))(obj, item, arg);
}
static char VtCall_c_pp(void* obj, int slot, void* a, void* b, void* out)
{
    return (*(Fn_vt_char_pp*)(*(char***)obj + slot / 4))(obj, a, b, out);
}
static void VtCall_v(void* obj, int slot)
{
    (*(Fn_vt_void_void*)(*(char***)obj + slot / 4))(obj, 0);
}
static char VtCall_c(void* obj, int slot)
{
    return (*(Fn_vt_ret_char)(*(char***)obj + slot / 4))(obj);
}

// The 4096-entry inline scratch vector used to collect property lists during the walk.
struct ScratchVec {
    void* mpBegin;      // +0x00
    void* mpEnd;        // +0x04
    void* mpCapacity;   // +0x08
    void* mpInline;     // +0x0c
    void* mBuf[4096];   // +0x10 inline storage
};

// @ 0x006a7e40
// SP::cPropertyManager::PreloadPropertyLists
void cPropertyManager::PreloadPropertyLists()
{
    Manager* mgr = GetResManager();
    RecQuery* query = QueryResourceRecords();

    Key128 key;
    key.mVtbl   = (void*)0x013eb898;
    key.mField4 = -1;
    key.mField8 = -1;
    key.mFieldC = 0x00b1b104;
    key.mField10 = -1;

    GetAllocator();
    // A hash set with an inline sentinel; the resource manager enumerates every record into it.
    char  set[0x10];                       // +0x00 head/self links (sentinel list)
    *(void**)(set + 0) = set;
    *(void**)(set + 4) = 0;
    *(void**)(set + 8) = set;
    VtCall_v(mgr, 0x5c);                   // mgr->EnumerateRecords(&set, 0)

    ScratchVec scratch;
    scratch.mpBegin    = scratch.mBuf;
    scratch.mpEnd      = scratch.mBuf;
    scratch.mpCapacity = (char*)set;       // approximate upper bound slot
    scratch.mpInline   = scratch.mBuf;

    // ---- first pass: build cPropertyList objects for every matching sub-item ----
    for (void** node = *(void***)set; node != (void**)set; node = (void**)*node) {
        void* rec = node[2];
        if (rec != 0 && VtCall_c_i(rec, 0x0c, 0x226a1de) != 0)
            continue;

        // sub-item vector {begin,end,cap} of 0xc-byte entries
        void* sub[3] = { 0, 0, 0 };
        VtCall_vec_key(rec, 0x0c, sub, set + 0x28);
        int count = (int)(((char*)sub[1] - (char*)sub[0]) / 0xc);

        for (int i = 0; i < count; ++i) {
            char* item = (char*)sub[0] + i * 0xc;
            char* p0 = *(char**)(item + 0);
            char* p1 = *(char**)(item + 4);
            char* p2 = *(char**)(item + 8);

            void* list = 0;
            if (VtCall_c_pp(rec, 0x18, &p0, 0, 0) == 0) {
                void* subItem = 0;
                if (VtCall_c_pp(rec, 0x1c, &p0, 0, 0) != 0) {   // slot 0x1c: create variant
                    list = operator_newx(0x38, "App/PropertyList/Preload", 0, 0, 0, 0);
                    if (list != 0)
                        list = PropertyListCtor(list, "Preloaded");
                    if (list != 0)
                        VtCall_v(list, 0x00);                       // list->vtable[0]() : AddRef
                    ((void**)list)[2] = p0;
                    ((void**)list)[3] = p1;
                    ((void**)list)[4] = p2;
                    subItem = p2;
                    if (VtCall_c(list, 0x3c) != 0) {                // list->AddProperty(...)
                        RegisterPropertyList(list);
                        void* slot = MapFindKey(set + 0x28, &key);
                        void* old = *(void**)slot;
                        if (list != old) {
                            VtCall_v(list, 0x00);                   // AddRef new
                            *(void**)slot = list;
                            if (old != 0)
                                VtCall_v(old, 0x04);                // Release old
                        }
                        if (VtCall_c_i(list, 0x1c, 0x00b2cccb) != 0) {
                            if (scratch.mpEnd < (void*)scratch.mpCapacity)
                                *(void**)scratch.mpEnd = list, scratch.mpEnd = (char*)scratch.mpEnd + 4;
                            else
                                MapInsertValue(scratch.mpBegin, scratch.mpEnd, &list);
                        }
                    }
                }
                if (list != 0)
                    VtCall_v(list, 0x04);                           // Release
            }
        }

        if (sub[0] != 0 && *(int*)((char*)sub[0] - 4) != 0)
            operator_deletex(sub[0]);
    }

    // ---- second pass: attach the parent property list for every collected list ----
    int ncollected = (int)(((char*)scratch.mpEnd - (char*)scratch.mpBegin) >> 2);
    for (int i = 0; i < ncollected; ++i) {
        void* list = ((void**)scratch.mpBegin)[i];
        char* subItem = (char*)VtCall_c_i(list, 0x28, 0x00b2cccb);

        // Decode the sub-item's key: a short type tag at +0x12 selects the representation.
        short tag = *(short*)(subItem + 0x12);
        char* keyPtr;
        if (tag == 0x20 || tag == 0x10) {
            if ((subItem[0x10] & 0x30) == 0)
                keyPtr = (tag != 0) ? subItem : 0;
            else
                keyPtr = *(char**)subItem;
        } else {
            keyPtr = (char*)VariantToSubItem();
        }

        Key128 ref;
        ref.mVtbl   = *(void**)(keyPtr + 0);
        ref.mField4 = *(int*)(keyPtr + 4);
        ref.mField8 = *(int*)(keyPtr + 8);
        if (ref.mField8 == 0)
            ref.mField8 = *(int*)((char*)list + 0x10);
        ref.mFieldC = 0;
        ref.mField10 = 0;

        void* found = 0;
        MapFindRef(set + 0x28, &ref, &found);
        if (found == 0) {
            void* parent = 0;
            if (VtCall_c_pp(list, 0x2c, ref.mVtbl, (void*)ref.mField4, &parent) != 0)
                SetPropertyListParent(list, 0);
        } else {
            SetPropertyListParent(list, *(void**)((char*)found + 8));
        }
    }

    if (scratch.mpBegin != 0 && scratch.mpBegin != (void*)scratch.mBuf)
        operator_deletex(scratch.mpBegin);

    // ---- release the enumerated record set ----
    for (void** node = *(void***)set; node != (void**)set; ) {
        void** next = (void**)*node;
        VtCall_v((void*)node, 0x0c);
        *(void**)set = next;
        node = next;
    }
}

// ===========================================================================
// Get-or-create accessors for two eastl hashtables
// ===========================================================================

// eastl::hashtable<basic_string<char>, pair<const string, AutoRefCount<cExprFunction>>>::operator[]
struct Key1;
struct Iter1 {
    void* mpNode;   // +0
    Iter1() {}
    Iter1(const Iter1&) {}
};

// Temporary value slot built by makeDefault: the pair's embedded string is released when the
// temporary dies (the original's EH cleanup: cap-begin > 1 byte and a non-null heap pointer).
struct StrTmpC {
    void* mpBegin; void* mpEnd; void* mpCap;
    void* mPad1; void* mPad2;
    ~StrTmpC() {
        if ((char*)mpCap - (char*)mpBegin > 1 && mpBegin)
            EASTL_allocator_deallocate(mpBegin);
    }
};

struct ValueMap1 {
    char     pad0[4];
    void**   mpBucketArray;    // +4
    uint32_t mnBucketCount;    // +8

    Iter1 find(const Key1* key);                 // out-of-line template instantiation
    void* makeDefault(const Key1* key, void* out, int flag);   // 0x006a3f40
    void  insertDefault(Iter1* out, const void* value, int flag); // 0x006a5c50

    int& operator[](const Key1* key);
};

// @ 0x006a8340
int& ValueMap1::operator[](const Key1* key)
{
    Iter1 it = find(key);
    if (it.mpNode != mpBucketArray[mnBucketCount])
        return *(int*)((char*)it.mpNode + 0x10);

    StrTmpC temp;
    void* v = makeDefault(key, &temp, 0);
    insertDefault(&it, v, 0);
    return *(int*)((char*)it.mpNode + 0x10);
}

// eastl::hashtable<unsigned int, pair<const unsigned int, basic_string<wchar_t>>>::operator[]
struct Key2;
struct Iter2 {
    void* mpNode;   // +0
    Iter2() {}
    Iter2(const Iter2&) {}
};

struct StrTmpW {
    void* mpBegin; void* mpEnd; void* mpCap;
    void* mPad1; void* mPad2;
    ~StrTmpW() {
        if ((char*)mpCap - (char*)mpBegin > 1 && mpBegin)
            EASTL_allocator_deallocate(mpBegin);
    }
};

struct ValueMap2 {
    char     pad0[4];
    void**   mpBucketArray;    // +4
    uint32_t mnBucketCount;    // +8

    Iter2 find(uint32_t key);                        // 0x00a3b2c0
    void* makeDefault(uint32_t key, void* out);      // 0x00b209f0
    void  insertDefault(Iter2* out, const void* value, uint32_t key); // 0x006a5d50

    uint16_t* operator[](uint32_t key);
};

// @ 0x006a8410
uint16_t* ValueMap2::operator[](uint32_t key)
{
    Iter2 it = find(key);
    if (it.mpNode != mpBucketArray[mnBucketCount])
        return (uint16_t*)((char*)it.mpNode + 4);

    StrTmpW temp;
    void* v = makeDefault(key, &temp);
    insertDefault(&it, v, key & 0xffffff00);
    return (uint16_t*)((char*)it.mpNode + 4);
}

// ===========================================================================
// eastl::vector<element(0x18)>::reserve  (retail instance)
// ===========================================================================

void relocateA(void* first, void* last, void* dest);
void relocateB(void* first, void* last, void* dest);

struct PVec {
    char* mpBegin;      // +0
    char* mpEnd;        // +4
    char* mpCapacity;   // +8

    void reserve(uint32_t n);
};

// @ 0x006a84f0
void PVec::reserve(uint32_t n)
{
    if (n <= (uint32_t)((mpCapacity - mpBegin) / 0x18))
        return;

    char* pNewData = n ? (char*)EASTL_allocator_allocate(n * 0x18, "App", 0, 0, APP_ALLOCATOR_FILE, 0xd1) : 0;
    char* pEnd   = mpEnd;
    char* pBegin = mpBegin;
    relocateA(pBegin, pEnd, pNewData);
    relocateB(pBegin, pEnd, pNewData);
    if (mpBegin)
        EASTL_allocator_deallocate(mpBegin);

    uint32_t nPrevSize = (uint32_t)((mpEnd - mpBegin) / 0x18);
    mpBegin    = pNewData;
    mpEnd      = pNewData + nPrevSize * 0x18;
    mpCapacity = pNewData + n * 0x18;
}

// ===========================================================================
// eastl::hashtable<basic_string<char>, pair<const string, unsigned int>>::DoFreeNodes
// ===========================================================================

struct Str16 { void* mpBegin; void* mpEnd; void* mpCapacity; void* mAllocator; };
struct Node  { Str16 mValue; uint32_t mSecond; Node* mpNext; };

struct HTable {
    // @ 0x006a85b0
    void DoFreeNodes(Node** pBucketArray, uint32_t n);
};

void HTable::DoFreeNodes(Node** pBucketArray, uint32_t n)
{
    for (uint32_t i = 0; i < n; ++i) {
        Node* p = pBucketArray[i];
        while (p) {
            Node* pNode = p;
            p = p->mpNext;
            if ((int)((char*)pNode->mValue.mpCapacity - (char*)pNode->mValue.mpBegin) > 1 && pNode->mValue.mpBegin)
                EASTL_allocator_deallocate(pNode->mValue.mpBegin);
            EASTL_allocator_deallocate(pNode);
        }
        pBucketArray[i] = 0;
    }
}
