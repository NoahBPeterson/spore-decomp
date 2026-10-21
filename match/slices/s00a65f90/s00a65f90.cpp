// Slice s00a65f90 (batch gold3, slice 77).  Region 0x00a65f90-0x00a6709c.
// EA::Audio::Eapd (EA's embedded Pure Data): the InstanceManager / SymbolManager
// lifecycle, the symbol + binding hashtables and the EAPd SystemOverflow arena.
// Callees: FixedPool::Init (0xa53210), the EASTL hashtable find/equal_range
// helpers, the pd outlet/bang entry points, 0x921340 (log2).
#include "s00a65f90.h"

// ===========================================================================
// InstanceManager
// ===========================================================================

// @ 0xa65f90
bool InstanceManager::Init(uint32_t size, uint32_t a2, uint32_t a3)
{
    ((FixedPool*)((char*)this + 8))->Init(0x78, size, (void*)a2, (void*)a3);
    PdInletRelease((char*)this + 0x3c, (void*)size, (void*)a2, (void*)a3);
    PdOutletInit((char*)this + 0x90, (void*)size, (void*)a2, (void*)a3);
    return true;
}

// @ 0xa65fe0
bool InstanceManager::FlushAll()
{
    Hashtable& h = mBindings;
    HashNode* node = *h.mpBucketArray;
    if (!node) {
        HashNode** b = h.mpBucketArray + 1;
        while (!*b)
            ++b;
        node = *b;
    }
    while (node != h.mpBucketArray[h.mnBucketCount]) {
        PdSymRelease(this, node->mKey);
        node = *h.mpBucketArray;
        if (!node) {
            HashNode** b = h.mpBucketArray + 1;
            while (!*b)
                ++b;
            node = *b;
        }
    }
    return true;
}

// @ 0xa66070
void* InstanceManager::InsertParam(void* out, uint32_t* key)
{
    Hashtable& h = mBindings;
    HashFind it = HashTableFind(&h, key);
    if (it.mpNode == h.mpBucketArray[h.mnBucketCount]) {
        uint32_t local[6];
        local[0] = *key;
        local[1] = 0;
        local[2] = 0;
        local[3] = 0;
        local[4] = 0;
        local[5] = 0;
        PdPatchInsert(&it, local, (void*)0);
    }
    (void)out;
    return (char*)it.mpNode + 4;
}

// @ 0xa66300
uint32_t InstanceManager::AddInstance(uint32_t glist)
{
    uint32_t id = mCurId;
    mCurId2 = id;
    ++mCurId;
    void* a = &mAllocA;
    void* obj = ((void* (__thiscall*)(void*, uint32_t))(*(void***)a)[2])(a, 0x78);
    if (obj)
        (void)glist;
    return id;
}

// @ 0xa66170
CursorValue* CursorTable::InsertIfAbsent(const CursorValue* value)
{
    CursorIter it = FindNode(value);
    if (it.mpNode != mpBucketArray[mnBucketCount])
        return (CursorValue*)((char*)it.mpNode + 8);
    CursorValue pair = *value;
    InsertResult res;
    Insert(&res, &pair, false);
    return (CursorValue*)((char*)res.mpNode + 8);
}

// @ 0xa663e0
void CursorRegistry::RemoveAllFor(void* key, int unused)
{
    CursorLink* node = (CursorLink*)mCursors.InsertIfAbsent((const CursorValue*)&key);
    while (node->mpNext != node)
        ((InstanceReleaser*)this)->Remove(*(int*)((char*)node->mpValue + 8));
    (void)unused;
}

// @ 0xa665f0
Hashtable* Hashtable::Construct(void* name)
{
    mnBucketCount = 0;
    mnElementCount = 0;
    mfMaxLoadFactor = 1.0f;
    mnGrowthFactor = 2;
    mnNextResize = 0;
    PdClassResize(&mAlloc, (uint32_t)name);
    mnElementCount = 0;
    mnNextResize = 0;
    mnBucketCount = 1;
    mpBucketArray = (HashNode**)0x154df28;
    return this;
}

// @ 0xa66670
InstanceManager::~InstanceManager()
{
    HashtableDtor90((char*)this + 0x90);
    mSymbols.Destruct();
    mField38 = (void*)0x1403934;
    ((FixedPool*)((char*)this + 8))->~FixedPool();
}

// @ 0xa66780
void InstanceManager::Construct(void* a, void* b)
{
    mpObj = a;
    mAllocA.mpVtbl = (void*)0x1454fac;
    mAllocA.mA = 0;
    mAllocA.mpName = "EAPd/InstanceManager";
    mAllocB.mpVtbl = (void*)0x1454fac;
    mAllocB.mA = 0;
    mAllocB.mpName = "EAPd/InstanceManager";
    mField20 = 0;
    mField24 = 0;
    mField28 = 0;
    mField2c = 0;
    mField30 = 0;
    mField34 = 0;
    mpVtbl4 = (void*)0x14556c0;
    mField38 = b;
    PdPatchMapInit((char*)this + 0x3c, "EAPd/PatchMap");
    PdInstanceMapInit((char*)this + 0x90, "EAPd/InstanceMap");
    mCurId = 0;
    mCurId2 = 0xffffffff;
}

// @ 0xa66c60
void EapdRec::GetC4(uint32_t* a, uint32_t* b, uint32_t* c)
{
    *a = mC4;
    *b = m70;
    *c = m28;
}

// @ 0xa66c90
void EapdRec::GetC8(uint32_t* a, uint32_t* b, uint32_t* c)
{
    *a = mC8;
    *b = m74;
    *c = m28;
}

// ===========================================================================
// EapdSystemOverflow
// ===========================================================================

// @ 0xa66830
EapdSystemOverflow::~EapdSystemOverflow()
{
    mpVtbl = (void*)&vtbl_EAPd_SystemOverflow;
    if (mpArena) {
        void* a = &mpAlloc;
        ((void (__thiscall*)(void*, void*))(*(void***)a)[3])(a, mpArena);
    }
    mField10 = 0x1403934;
    mpAlloc = (void*)0x1403934;
    mpVtbl = (void*)0x1403934;
}

// @ 0xa66890
bool EapdSystemOverflow::Init(uint32_t size, uint32_t a3, uint32_t a4)
{
    if (mpArena) {
        void* a = &mpAlloc;
        ((void (__thiscall*)(void*, void*))(*(void***)a)[3])(a, mpArena);
        mpArena = 0;
    }
    mField08 = *(uint32_t*)(a3 + 4);
    mField14 = *(uint32_t*)(a4 + 4);
    void* p = ((void* (__thiscall*)(void*, uint32_t))(*(void***)&mpAlloc)[2])(&mpAlloc, size);
    mpArena = p;
    mpCursor = p;
    mpLimit = (char*)p + size;
    mUsed = 0;
    return p != 0;
}

// @ 0xa66900
void* EapdSystemOverflow::Alloc(uint32_t n)
{
    char* cur = (char*)mpCursor;
    void* r = cur;
    if ((uint32_t)cur + n <= (uint32_t)mpLimit)
        mpCursor = cur + n;
    else
        r = ((void* (__thiscall*)(void*, uint32_t))(*(void***)((char*)this + 0x10))[2])((char*)this + 0x10, n);
    if (r)
        mUsed += n;
    return r;
}

// @ 0xa66930
void EapdSystemOverflow::Free(void* p)
{
    if ((uint32_t)p >= (uint32_t)mpArena && (uint32_t)p < (uint32_t)mpLimit)
        return;
    void* a = (char*)this + 0x10;
    ((void (__thiscall*)(void*, void*))(*(void***)a)[3])(a, p);
}

// ===========================================================================
// SymbolManager
// ===========================================================================

// @ 0xa66970
uint32_t EapdHashString(const char* s)
{
    uint32_t h = 0x811c9dc5;
    uint32_t c = (uint8_t)*s;
    while (c != 0) {
        ++s;
        h = h * 0x1000193 ^ (uint32_t)tolower((int)c);
        c = (uint8_t)*s;
    }
    return h;
}

// @ 0xa669b0
uint32_t SymbolManager::HashCall(uint32_t a)
{
    return mHashFunction((const char*)a);
}
// @ 0xa669d0
bool FixedHashtableAllocator::InitTables(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
{
    if (mpBucketBuffer) {
        void* v = mInitAllocator.mpVtbl;
        ((void (__thiscall*)(void*, void*))(*(void***)&mInitAllocator)[3])(&mInitAllocator, mpBucketBuffer);
        mpBucketBuffer = 0;
        (void)v;
    }
    float f = (float)a;
    if ((int)a < 0)
        f += 4294967296.0f;
    uint32_t nb = (uint32_t)(long long)(f * 1.3333334f);
    mnBucketCount = nb;
    if (nb < 3) {
        mnBucketCount = 3;
    } else {
        mnBucketCount = EapdPrimeBelow(nb) + 1;
    }
    if ((mnBucketCount << 2) == 0xc)
        return Init(0xc, a + 1, (void*)b, (void*)c);
    if (!Init(0xc, a, (void*)b, (void*)c))
        return false;
    void* p = ((void* (__thiscall*)(void*, uint32_t))(*(void***)&mInitAllocator)[2])(&mInitAllocator, mnBucketCount * 4);
    mpBucketBuffer = p;
    (void)d;
    return p != 0;
}

// @ 0xa66b40
void Hashtable::Rehash(uint32_t n)
{
    HashNode** arr = (HashNode**)EapdPrimeBelow(n);
    for (uint32_t i = 0; i < mnBucketCount; ++i) {
        HashNode* node = mpBucketArray[i];
        while (node) {
            uint32_t key = node->mKey;
            mpBucketArray[i] = node->mpNext;
            node->mpNext = arr[key % n];
            arr[key % n] = node;
            node = mpBucketArray[i];
        }
    }
    HashNode* old = (HashNode*)mpBucketArray;
    if (mnBucketCount > 1 && old != (HashNode*)mAlloc.mpBucketBuffer) {
        --mAlloc.mnCurrentSize;
        if ((uint8_t*)old < (uint8_t*)mAlloc.mpPoolBegin ||
            (uint8_t*)old >= (uint8_t*)mAlloc.mpPoolEnd) {
            void* v = &mAlloc.mOverflowAllocator;
            ((void (__thiscall*)(void*, void*))(*(void***)v)[3])(v, old);
        } else {
            *(void**)old = mAlloc.mpHead;
            mAlloc.mpHead = old;
        }
    }
    mpBucketArray = arr;
    mnBucketCount = n;
}

// @ 0xa66bf0
void EapdClearBucketsRaw(Hashtable* self, HashNode** arr, uint32_t n)
{
    for (uint32_t i = 0; i < n; ++i) {
        HashNode* node = arr[i];
        while (node) {
            HashNode* next = node->mpNext;
            if (node != (HashNode*)self->mAlloc.mpBucketBuffer) {
                --self->mAlloc.mnCurrentSize;
                if ((uint8_t*)node < (uint8_t*)self->mAlloc.mpPoolBegin ||
                    (uint8_t*)node >= (uint8_t*)self->mAlloc.mpPoolEnd) {
                    void* v = &self->mAlloc.mOverflowAllocator;
                    ((void (__thiscall*)(void*, void*))(*(void***)v)[3])(v, node);
                } else {
                    *(void**)node = self->mAlloc.mpHead;
                    self->mAlloc.mpHead = node;
                }
            }
            node = next;
        }
        arr[i] = 0;
    }
}

// @ 0xa66e30
bool SymbolManager::Unbind(uint32_t key, void* value)
{
    Hashtable& h = mBindings;
    HashIter it = HashTableEqualRange(&h, &key);
    while (it.mpNode != it.mpEnd) {
        if (it.mpNode->mValue == value) {
            HashIter dummy;
            dummy.mpNode = it.mpNode;
            dummy.mpBucket = it.mpBucket;
            dummy.mpEnd = it.mpNode;
            h.erase(dummy);
            return true;
        }
        it.mpNode = it.mpNode->mpNext;
        while (!it.mpNode)
            it.mpNode = *++it.mpBucket;
    }
    return false;
}

// @ 0xa66ec0
void* SymbolManager::BindX(uint32_t key, uint32_t b)
{
    Hashtable& h = mBindings;
    HashIter it = HashTableEqualRange(&h, &key);
    if (it.mpNode == it.mpEnd)
        return 0;
    void* r = it.mpNode->mValue;
    if (it.mpNode->mpNext == 0) {
        while (!*++it.mpBucket)
            ;
    }
    (void)b;
    return r;
}

// @ 0xa66f10
void* SymbolManager::FindByClass(uint32_t key, void* a2, void* a3)
{
    Hashtable& h = mBindings;
    HashIter t = HashTableEqualRange(&h, &key);
    HashNode*  node   = t.mpNode;
    HashNode** bucket = t.mpBucket;
    HashNode*  end    = t.mpEnd;
    void* found = 0;
    while (node != end) {
        void* val = node->mValue;
        HashNode* next = node->mpNext;
        if (*(void**)val == a3)
            found = val;
        node = next;
        while (!node)
            node = *++bucket;
    }
    (void)a2;
    return found;
}

// @ 0xa66f70
void SymbolManager::SendBang(uint32_t key, uint32_t a2)
{
    Hashtable& h = mBindings;
    HashIter t = HashTableEqualRange(&h, &key);
    HashNode*  node   = t.mpNode;
    HashNode** bucket = t.mpBucket;
    HashNode*  end    = t.mpEnd;
    while (node != end) {
        OutletBang(node->mValue);
        node = node->mpNext;
        while (!node)
            node = *++bucket;
    }
    (void)a2;
}

// @ 0xa66fd0
void SymbolManager::SendFloat(uint32_t key, uint32_t a2, float f)
{
    Hashtable& h = mBindings;
    HashIter t = HashTableEqualRange(&h, &key);
    HashNode*  node   = t.mpNode;
    HashNode** bucket = t.mpBucket;
    HashNode*  end    = t.mpEnd;
    while (node != end) {
        OutletFloat(node->mValue, f);
        node = node->mpNext;
        while (!node)
            node = *++bucket;
    }
    (void)a2;
}

// @ 0xa67040
void SymbolManager::SendSymbol(uint32_t key, void* a2, void* a3)
{
    Hashtable& h = mBindings;
    HashIter t = HashTableEqualRange(&h, &key);
    HashNode*  node   = t.mpNode;
    HashNode** bucket = t.mpBucket;
    HashNode*  end    = t.mpEnd;
    while (node != end) {
        OutletSymbol(node->mValue, a2);
        node = node->mpNext;
        while (!node)
            node = *++bucket;
    }
    (void)a3;
}

// @ 0xa66d60
void SymbolManager::ClearClasses()
{
    Hashtable& h = mSymbols;
    HashNode* node = *h.mpBucketArray;
    HashNode** bucket = h.mpBucketArray;
    if (!node) {
        bucket = h.mpBucketArray + 1;
        while (!*bucket)
            ++bucket;
        node = *bucket;
    }
    HashNode* end = h.mpBucketArray[h.mnBucketCount];
    for (; node != end; ) {
        mHashFunction((const char*)node->mValue);
        HashIter it;
        it.mpNode = node;
        it.mpBucket = bucket;
        it.mpEnd = node;
        HashIter r = h.erase(it);
        node = r.mpNode;
        bucket = r.mpBucket;
    }
}

// @ 0xa66de0
bool SymbolManager::FindSym(uint32_t key, t_symbol* out)
{
    Hashtable* h = &mSymbols;
    bool found = false;
    HashFind t = HashTableFind(h, &key);
    if (h->mpBucketArray[h->mnBucketCount] != t.mpNode) {
        out->mpName = (const char*)t.mpNode->mValue;
        out->mHash = key;
        found = true;
    }
    return found;
}

// @ 0xa66cc0
HashIter Hashtable::erase(HashIter it)
{
    HashNode* p = it.mpEnd;
    HashNode* node = it.mpNode;
    HashNode** bucket = it.mpBucket;
    HashIter out;
    out.mpNode = node->mpNext;
    out.mpBucket = bucket;
    if (!out.mpNode) {
        do {
            ++out.mpBucket;
            out.mpNode = *out.mpBucket;
        } while (!out.mpNode);
    }
    HashNode* head = *bucket;
    if (head == node) {
        *bucket = head->mpNext;
    } else {
        HashNode* prev = head;
        while (prev->mpNext != node)
            prev = prev->mpNext;
        prev->mpNext = node->mpNext;
    }
    if (p != (HashNode*)mAlloc.mpBucketBuffer) {
        --mAlloc.mnCurrentSize;
        if ((uint8_t*)p >= (uint8_t*)mAlloc.mpPoolBegin && (uint8_t*)p < (uint8_t*)mAlloc.mpPoolEnd) {
            *(void**)p = mAlloc.mpHead;
            mAlloc.mpHead = p;
        } else {
            void* v = &mAlloc.mOverflowAllocator;
            ((void (__thiscall*)(void*, void*))(*(void***)v)[3])(v, p);
        }
    }
    --mnElementCount;
    return out;
}

// @ 0xa66410
void CursorRegistry::RemoveCurrentClass(CursorValue value)
{
    uint32_t saved = mnCurId;
    CursorListHead local;
    local.mpNext = (CursorNode*)&local;
    local.mpPrev = (CursorNode*)&local;

    CursorListHead* head = (CursorListHead*)mCursors.InsertIfAbsent(&value);

    // Swap the per-key list with the local head, then repair both ends.
    CursorNode* hn = head->mpNext;
    CursorNode* hp = head->mpPrev;
    CursorNode* ln = local.mpNext;
    CursorNode* lp = local.mpPrev;
    head->mpNext = ln;
    head->mpPrev = lp;
    local.mpNext = hn;
    local.mpPrev = hp;

    if (local.mpNext == (CursorNode*)head) {
        local.mpNext = (CursorNode*)&local;
        local.mpPrev = (CursorNode*)&local;
    } else {
        local.mpPrev->mpNext = (CursorNode*)&local;
        local.mpNext->mpPrev = (CursorNode*)&local;
    }

    if (head->mpNext == (CursorNode*)&local) {
        head->mpNext = (CursorNode*)head;
        head->mpPrev = (CursorNode*)head;
    } else {
        head->mpPrev->mpNext = (CursorNode*)head;
        head->mpNext->mpPrev = (CursorNode*)head;
    }

    while (local.mpPrev != (CursorNode*)&local) {
        uint32_t id = local.mpNext->mnId;
        ((InstanceReleaser*)this)->Remove((int)id);
        mnCurId = id;
        mnCurId2 = 0xFFFFFFFFu;
        ((InstanceResetter*)this)->Reset(value.mKey, (uint32_t)value.mValue, 0, 0);
    }

    mnCurId = saved;
}

// @ 0xa66550
void Hashtable::Destruct()
{
    ClearBuckets(mpBucketArray, mnBucketCount);
    HashNode* p = (HashNode*)mpBucketArray;
    mnElementCount = 0;
    if (mnBucketCount > 1 && p != (HashNode*)mAlloc.mpBucketBuffer) {
        --mAlloc.mnCurrentSize;
        if ((uint8_t*)p < (uint8_t*)mAlloc.mpPoolBegin ||
            (uint8_t*)p >= (uint8_t*)mAlloc.mpPoolEnd) {
            void* v = &mAlloc.mOverflowAllocator;
            ((void (__thiscall*)(void*, void*))(*(void***)v)[3])(v, p);
        } else {
            *(void**)p = mAlloc.mpHead;
            mAlloc.mpHead = p;
        }
    }
    mAlloc.DestroyAllocator();
}

// @ 0xa660e0
void Hashtable::ClearBuckets(HashNode** arr, uint32_t n)
{
    for (uint32_t i = 0; i < n; ++i) {
        HashNode* node = arr[i];
        while (node) {
            HashNode* next = node->mpNext;
            HashNode* chain = (HashNode*)node->mValue;
            while (chain != (HashNode*)((char*)node + 8)) {
                HashNode* c2 = (HashNode*)chain->mKey;
                *(void**)((char*)chain + 4) = 0;
                *(void**)chain = 0;
                chain = c2;
            }
            *(void**)((char*)node + 0xc) = 0;
            *(void**)((char*)node + 8) = 0;
            if (node != (HashNode*)mAlloc.mpBucketBuffer) {
                --mAlloc.mnCurrentSize;
                if ((uint8_t*)node < (uint8_t*)mAlloc.mpPoolBegin ||
                    (uint8_t*)node >= (uint8_t*)mAlloc.mpPoolEnd) {
                    void* a = &mAlloc.mOverflowAllocator;
                    ((void (__thiscall*)(void*, void*))(*(void***)a)[3])(a, node);
                } else {
                    *(void**)node = mAlloc.mpHead;
                    mAlloc.mpHead = node;
                }
            }
            node = next;
        }
        arr[i] = 0;
    }
}
