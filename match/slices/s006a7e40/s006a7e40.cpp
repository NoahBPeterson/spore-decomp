// Slice s006a7e40 — SP::cPropertyManager preload + EASTL property-hashtable helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

void* EASTL_allocator_allocate(uint32_t size, const char* name, int flags, int debugFlags, const char* file, int line);
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

// @ 0x006a7e40
// SP::cPropertyManager::PreloadPropertyLists
void cPropertyManager::PreloadPropertyLists()
{
    // TODO(partial): walks the resource manager's property-list resources, instantiates a
    // cPropertyList per instance, feeds it through cPropertyList::cPropertyList("Preloaded")
    // and cPropertyList::Load, then registers every resulting list via
    // FUN_006a1710/GetPropertyList.  The 4096-entry scratch vector and the EH/FUN_* cleanup
    // layout are not reproduced yet.
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
struct ValueMap1 {
    char     pad0[4];
    void**   mpBucketArray;    // +4
    uint32_t mnBucketCount;    // +8

    Iter1 find(const Key1* key);                 // out-of-line template instantiation
    void  makeDefault(const Key1* key, void* out, int flag);   // 0x006a3f40
    void  insertDefault(Iter1* out, const void* value, int flag); // 0x006a5c50

    int& operator[](const Key1* key);
};

// @ 0x006a8340
int& ValueMap1::operator[](const Key1* key)
{
    Iter1 it = find(key);
    if (it.mpNode != mpBucketArray[mnBucketCount])
        return *(int*)((char*)it.mpNode + 0x10);

    char temp[0x14];
    makeDefault(key, temp, 0);
    insertDefault(&it, temp, 0);
    // temp's embedded string is destroyed here (see original EH cleanup).
    return *(int*)((char*)it.mpNode + 0x10);
}

// eastl::hashtable<unsigned int, pair<const unsigned int, basic_string<wchar_t>>>::operator[]
struct Key2;
struct Iter2 {
    void* mpNode;   // +0
    Iter2() {}
    Iter2(const Iter2&) {}
};
struct ValueMap2 {
    char     pad0[4];
    void**   mpBucketArray;    // +4
    uint32_t mnBucketCount;    // +8

    Iter2 find(uint32_t key);                        // 0x00a3b2c0
    void  makeDefault(uint32_t key, void* out);      // 0x00b209f0
    void  insertDefault(Iter2* out, const void* value, uint32_t key); // 0x006a5d50

    uint16_t* operator[](uint32_t key);
};

// @ 0x006a8410
uint16_t* ValueMap2::operator[](uint32_t key)
{
    Iter2 it = find(key);
    if (it.mpNode != mpBucketArray[mnBucketCount])
        return (uint16_t*)((char*)it.mpNode + 4);

    char temp[0x18];
    makeDefault(key, temp);
    insertDefault(&it, temp, key & 0xffffff00);
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
