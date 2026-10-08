// Slice s00e3f970: 0x00E3F970, a layout/refresh method of a space-stage UI panel that owns a stack of
// entry widgets (names Claude-coined).
//
// What it does:
//   1. Clears the "seen" hash table at +0x560, then walks the global item list (service +0xc): for every
//      item not yet in the table it looks up its property list (group 0xe1d7164f), reads the boolean
//      property 0x94f79745, and (unless the item id is one of three excluded ids) creates an Entry
//      (0x10c bytes), initialises it either from the item iterator (e3f2a0, when the flag is set) or from
//      the panel's object map (e48f30), and collects it in a local vector.
//   2. Clears the panel's entry vector (+0x184), then walks the collected entries BACKWARDS: each entry's
//      two keys drive Interp::Run over the keyframe map (+0xc8), the entry is positioned (e46d80),
//      pushed on the panel's entry vector, and the running y cursor (5.0 start, +5.0 per entry) advances.
//   3. Makes the last entry the "current" one (+0xa8), updates the cursor field +0x28c, runs the
//      keyframes once more for the final key, refreshes (e3a8f0 / e3c000 / e3caa0), flags the entries that
//      come before the first entry with key 0xdbd1b537 and finally clamps the visible range (+0xa0/+0xa4).
//
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE (no /EHsc: ref-counted locals but no EH frame).
#include "types.h"

typedef unsigned int size_t;
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void operator delete[](void* p);
inline void* operator new(unsigned int, void* p) { return p; }

// ---------------------------------------------------------------------------------------
struct IRef {
    virtual void AddRef();
    virtual void Release();                                         // +4
};
template <class T> struct Ref {                                     // EA::AutoRefCount<T>
    T* mpObject;
    Ref() : mpObject(0) {}
    Ref(T* p) : mpObject(p) { if (p) p->AddRef(); }
    Ref(const Ref& o) : mpObject(o.mpObject) { if (mpObject) mpObject->AddRef(); }
    ~Ref() { if (mpObject) mpObject->Release(); }
    Ref& operator=(T* pObject)
    {
        if (pObject != mpObject) {
            T* const pTemp = mpObject;
            if (pObject) pObject->AddRef();
            mpObject = pObject;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};

// property system (see s00e3cf60)
struct Property {
    void*    mpValue;                                               // +0 (when flags & 0x30: pointer to value)
    char     pad4[0xc];
    uint8_t  mFlags;                                                // +0x10
    uint8_t  pad11;
    uint16_t mType;                                                 // +0x12
    char* GetBytes() { return (mFlags & 0x30) ? *(char**)this : (char*)this; }
};
struct PropertyList : IRef {
    virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6();
    virtual void s7(); virtual void s8();
    virtual bool GetProperty(uint32_t id, Property** out);          // +0x24
};
struct IPropManager {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28();
    virtual bool GetPropertyList(uint32_t instanceID, uint32_t groupID, PropertyList** dst);   // +0x2c
};
IPropManager* PropertyManager();                                    // 0x0067de30

// keyframed UI object (map<int, IObj*> values) -- see s00e3eca0
struct IObj : IRef {
    virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5(); virtual void s6();
    virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
    virtual void s12(); virtual void s13();
    virtual float* GetVec4();                                       // +0x38
    virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
    virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22();
    virtual void SetDepth(int d);                                   // +0x5c
    virtual void s24(); virtual void s25(); virtual void s26();
    virtual void SetVec4(float* v);                                 // +0x6c
    virtual void s28(); virtual void s29(); virtual void s30();
    virtual void SetFlags(int a, int b);                            // +0x7c
};
struct MapIntObj {                                                  // map<int, IObj*> at this+0xc8
    IObj*& operator[](const int& key);                              // 0x00e3ec20
};
struct MapRefObj {                                                  // map<Ref<IObj>, IObj*> at this+0xe4
    IObj*& operator[](const Ref<IObj>& key);                        // 0x00ceb2b0
};

struct Vec2 {
    float x, y;
    Vec2() {}
    Vec2(const Vec2& o) : x(o.x), y(o.y) {}
};

// panel entry widget (0x10c bytes)
struct Entry : IRef {
    char   pad4[0x1c - 4];
    IObj*  mpChild;                                                 // +0x1c
    char   pad20[0x68 - 0x20];
    int    mKey;                                                    // +0x68
    char   pad6c[4];
    float  mWidth;                                                  // +0x70
    float  mHeight;                                                 // +0x74
    char   pad78[0xa8 - 0x78];
    int    mA8;                                                     // +0xa8
    char   padac[0xe4 - 0xac];
    int    mKeyE4;                                                  // +0xe4
    char   pade8[0xf8 - 0xe8];
    float  mFloatF8;                                                // +0xf8
    char   padfc[0x108 - 0xfc];
    uint8_t mFlag108;                                               // +0x108
    uint8_t mFlag109;                                               // +0x109
    char    pad10a[0x10c - 0x10a];

    Entry();                                                        // 0x00e471e0 (ctor)
    void Init(MapIntObj* objs, void* item, int a, int b);           // 0x00e48f30
    void SetPosition(Vec2 pos, int a, Vec2 size, int b);            // 0x00e46d80
    void Fe47100(void* p);                                          // 0x00e47100
    int  GetA8();                                                   // 0x0098f940
};

// hash table of already-seen items (this+0x560)
struct HNode;
struct HIter {
    HNode*  mpNode;
    HNode** mpBucket;
    HIter(HNode* n, HNode** b) : mpNode(n), mpBucket(b) {}
    HIter(const HIter& o) : mpNode(o.mpNode), mpBucket(o.mpBucket) {}
    bool operator==(const HIter& o) const { return mpNode == o.mpNode; }
};
struct SeenTable {
    char     pad0[4];
    HNode**  mpBucketArray;                                         // +4
    uint32_t mnBucketCount;                                         // +8
    uint32_t mnElementCount;                                        // +0xc
    void DoFreeNodes(HNode** pNodeArray, uint32_t n);               // 0x00693230
    HIter find(const uint32_t& key);                                // 0x00645ed0
    HIter end() { return HIter(mpBucketArray[mnBucketCount], mpBucketArray + mnBucketCount); }
    void clear()
    {
        DoFreeNodes(mpBucketArray, mnBucketCount);
        mnElementCount = 0;
    }
};

// global item list (circular, payload at node+8)
struct ItemData {
    char      pad0[0xc];
    uint32_t* mpID;                                                 // +0xc
};
struct ListNode {
    ListNode* mpFirst;                                              // +0
    ListNode* mpNext;                                               // +4
    ItemData  mData;                                                // +8
};
struct ListIter {
    ListNode* mpNode;
    ListIter(ListNode* n) : mpNode(n) {}
    ListIter(const ListIter& o) : mpNode(o.mpNode) {}
};
struct ItemService {
    ListNode* GetItems(int kind);                                   // 0x007eb100
};
ItemService* GetItemService();                                      // 0x0067de90

// local vector of Ref<Entry> (sp_vector_allocator)
struct EntryVec {
    Ref<Entry>* mpBegin;
    Ref<Entry>* mpEnd;
    Ref<Entry>* mpCapacity;
    EntryVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~EntryVec()
    {
        for (Ref<Entry>* p = mpBegin; p < mpEnd; ++p)
            p->~Ref();
        if (mpBegin && ((int*)mpBegin)[-1])
            ::operator delete[]((void*)mpBegin);
    }
    void push_back(const Ref<Entry>& r);                            // 0x00e1c7f0
};
// panel's own entry vector (this+0x184)
struct PanelVec {
    Ref<Entry>* mpBegin;
    Ref<Entry>* mpEnd;
    Ref<Entry>* mpCapacity;
    void erase(Ref<Entry>* first, Ref<Entry>* last);                // 0x00e25bd0
    void DoInsertValue(Ref<Entry>* pos, const Ref<Entry>& r);       // 0x00aea5d0
    void push_back(const Ref<Entry>& r)
    {
        if (mpEnd < mpCapacity)
            ::new((void*)mpEnd++) Ref<Entry>(r);
        else
            DoInsertValue(mpEnd, r);
    }
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
};

extern float g_Vec2X;                                               // 0x016acc90
extern float g_Vec2Y;                                               // 0x016acc94

struct EntryPanel {
    char       pad0[0x98];
    float      mF98;
    float      mF9c;
    float      mFa0;
    float      mFa4;
    Ref<Entry> mpCurrent;                                           // +0xa8
    char       padac[0xc8 - 0xac];
    MapIntObj  mObjs;                                               // +0xc8
    char       padc9[0xe4 - 0xc9];
    MapRefObj  mObjRefs;                                            // +0xe4
    char       pade5[0x184 - 0xe5];
    PanelVec   mEntries;                                            // +0x184
    char       pad190[0x1dc - 0x190];
    char       mField1dc;                                           // +0x1dc
    char       pad1dd[0x28c - 0x1dd];
    float      mF28c;
    char       pad290[4];
    int        mSelectedKey;                                        // +0x294
    char       pad298[0x560 - 0x298];
    SeenTable  mSeen;                                               // +0x560

    float Run(float acc, int key, int end);                         // 0x00e3ee30
    void  Fe3f2a0(ListIter it, Entry* e);                           // 0x00e3f2a0 (iterator by value)
    void  Fe3a270(int a, int b);                                    // 0x00e3a270
    void  Fe3a8f0();                                                // 0x00e3a8f0
    void  Fe3c000();                                                // 0x00e3c000
    void  Fe3caa0();                                                // 0x00e3caa0

    void Refresh();                                                 // 0x00e3f970
};

// @ 0x00e3f970
void EntryPanel::Refresh()
{
    EntryVec collected;
    PropertyList* propList = 0;
    char hasFlag;
    ListNode* head = GetItemService()->GetItems(0xc);
    mSeen.clear();
    if (head) {
        ListNode* node = head;
        ListNode* end = head->mpFirst;
        if (node != end) {
            do {
                ItemData* data = &node->mpNext->mData;
                uint32_t key = (uint32_t)data;
                if (mSeen.find(key) == mSeen.end()) {
                    uint32_t id = *data->mpID;
                    IPropManager* pm = PropertyManager();
                    if (propList) {
                        PropertyList* old = propList;
                        propList = 0;
                        old->Release();
                    }
                    pm->GetPropertyList(id, 0xe1d7164f, &propList);
                    if (propList) {
                        Property* prop;
                        if (propList->GetProperty(0x94f79745, &prop) && prop->mType == 1)
                            hasFlag = *prop->GetBytes();
                    }
                    if (id != 0xa7a9e952 && id != 0xeca9947e && id != 0x2500e82c) {
                        Entry* e = new("SPUIEntry", 0, 0, 0, 0) Entry();
                        Ref<Entry> ref(e);
                        if (hasFlag)
                            Fe3f2a0(ListIter(node), e);
                        else
                            e->Init(&mObjs, data, 1, 0);
                        collected.push_back(ref);
                    }
                }
                node = node->mpNext;
            } while (node != end);
        }
    }

    float cursor = 5.0f;
    int prevEnd = 0;          // A: end key of the previous step
    int entryKey = 0;         // B: key (+0x68) of the current entry
    int prevEntryKey = 0;     // D
    IObj* obj = 0;            // C: object of the previous step
    mEntries.erase(mEntries.mpBegin, mEntries.mpEnd);
    for (int i = (int)(collected.mpEnd - collected.mpBegin) - 1; i >= 0; --i) {
        Entry* e = collected.mpBegin[i].mpObject;
        entryKey = e->mKey;
        int nextKey = e->mKeyE4;
        if (prevEnd == 0)
            prevEnd = nextKey;
        IObj* o = mObjs[nextKey];
        o->SetFlags(1, 1);
        {
            Ref<IObj> tmp(o);
            mObjRefs[tmp]->SetDepth(-1);
        }
        if (prevEntryKey == mSelectedKey) {
            float v = obj ? obj->GetVec4()[0] : 0.0f;
            mF28c = v + cursor;
        }
        prevEntryKey = entryKey;
        obj = o;
        cursor = Run(cursor, prevEnd, nextKey);
        prevEnd = nextKey;
        Fe3a270(entryKey, e->GetA8());
        float w = e->mWidth;
        float h = e->mHeight;
        if (e->mpChild) {
            float* p = e->mpChild->GetVec4();
            Vec2 pos; pos.x = cursor; pos.y = ((p[3] - p[1]) - w) * 0.5f;
            Vec2 size; size.x = g_Vec2X; size.y = g_Vec2Y;
            e->SetPosition(pos, 0, size, 0);
        }
        cursor = (h + cursor) + 5.0f;
        mEntries.push_back(Ref<Entry>(e));
        e->Fe47100(&mField1dc);
        if (nextKey == 0x2db6dad3) {
            float* p = o->GetVec4();
            float v[4];
            v[0] = p[0]; v[1] = p[1]; v[2] = p[2]; v[3] = p[3];
            v[2] = p[0] + cursor;
            o->SetVec4(v);
        }
        if (entryKey == mSelectedKey)
            mF28c = o->GetVec4()[0] + cursor;
    }

    mpCurrent = mEntries.mpEnd[-1].mpObject;
    if (mSelectedKey == 0 || mSelectedKey == entryKey) {
        float v = obj ? obj->GetVec4()[0] : 0.0f;
        mF28c = v + cursor;
    }

    int nextEnd = 0;
    switch (prevEnd) {
    case (int)0xa426730b: nextEnd = 0xad56080c; break;
    case (int)0xad56080c: nextEnd = 0xf71fa311; break;
    case (int)0xbeb528cb: nextEnd = 0x2db6dad3; break;
    case (int)0xf71fa311: nextEnd = 0xbeb528cb; break;
    case 0x2db6dad3:      nextEnd = 0x2db6dad3; break;
    }
    Run(cursor, prevEnd, nextEnd);
    Fe3a8f0();
    Fe3c000();
    Fe3caa0();

    int count = mEntries.size();
    int limit = count;
    for (int j = 0; j < count; ++j) {
        Entry* e = mEntries.mpBegin[j].mpObject;
        if (e && e->mKey == (int)0xdbd1b537) {
            limit = j;
            break;
        }
    }
    for (int k = 0; k < limit; ++k) {
        Entry* e = mEntries.mpBegin[k].mpObject;
        if (e && e->mFlag109)
            e->mFlag108 = 1;
    }

    Entry* cur = mpCurrent.mpObject;
    if (cur && cur->mpChild) {
        float h = cur->mHeight;
        float r = h * 0.5f + cur->mFloatF8 + cur->mpChild->GetVec4()[0];
        const float* m = &mF98;
        if (r < mF98)
            m = &r;
        mFa0 = *m;
        mFa4 = mF9c;
    }
    if (propList)
        propList->Release();
}
