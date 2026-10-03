// Rebuilds a table of (resource key, vertex count, offset) entries plus flat
// float/int pools by scanning every key of a resource manager and reading
// several property arrays from each matching resource.
// Built without optimization: /Od /Ob1.
#include "../../include/types.h"

struct Tag { Tag() {} };
struct Entry { uint32_t key; int count; int offset; };

struct IRefCounted;
struct RefSlot { IRefCounted* p; IRefCounted** Out(); };
struct IRefCounted {
    virtual void Unused0() {}
    virtual void Release() {}
};

struct IResourceManager {
    virtual void v00() {} virtual void v01() {} virtual void v02() {} virtual void v03() {}
    virtual void v04() {} virtual void v05() {} virtual void v06() {} virtual void v07() {}
    virtual void v08() {} virtual void v09() {} virtual void v0a() {}
    virtual bool GetResource(uint32_t key, uint32_t group, IRefCounted** out);       // +0x2c
    virtual void v0c() {} virtual void v0d() {} virtual void v0e() {} virtual void v0f() {}
    virtual void v10() {} virtual void v11() {}     virtual void GetKeys(uint32_t group, struct KeyVector* out);                      // +0x48
};

struct KeyVector {
    uint32_t* begin; uint32_t* end; uint32_t* cap; uint32_t alloc;
    KeyVector(const Tag&);
    uint32_t& operator[](int i) { return begin[i]; }
    int size() { return end - begin; }
    void Destroy();
};

struct EntryVector { Entry* begin; Entry* end; void Destroy(Entry* b, Entry* e); void clear() { Destroy(begin, end); } };
struct IntVector {
    int* begin; int* end;
    void Clear(int* b, int* e);
    void clear() { Clear(begin, end); }
    int size() { return end - begin; }
    void Insert(int* where, void* first, void* last, Tag tag);
    void append(void* first, void* last) { Insert(end, first, last, Tag()); }
};

struct Owner {
    char pad[0x90];
    EntryVector entries;   // 0x90
    uint32_t pad2[3];
    IntVector offsets;     // 0xa4
    void GrowEntries();    // FUN_0041ffc0
    void Rebuild();
};

extern uint32_t g_ResourceGroup;
IResourceManager* GetResourceManager();
struct IntVector;
void* GetCompareFn();
void SortEntriesImpl(Entry* b, Entry* e, void* cmp, Tag tag);
inline void SortEntries(Entry* b, Entry* e) { SortEntriesImpl(b, e, GetCompareFn(), Tag()); }
void* GetTagStorage();
bool GetArrayProp(IRefCounted* o, uint32_t id, int* count, Entry** data);
bool GetArrayPropB(IRefCounted* o, uint32_t id, int* count, int** data);
bool GetArrayPropC(IRefCounted* o, uint32_t id, int* count, void** data);

// @ 0x004124b0
void Owner::Rebuild()
{
    entries.clear();
    offsets.clear();

    IResourceManager* mgr = GetResourceManager();
    KeyVector keys((Tag()));
    mgr->GetKeys(g_ResourceGroup, &keys);

    for (int i = 0, n = keys.size(); i < n; i++) {
        RefSlot res = {0};
        int subCount; Entry* subs;
        if (mgr->GetResource(keys[i], g_ResourceGroup, res.Out())) {
            if (GetArrayProp(res.p, 0xf05faa79, &subCount, &subs) && subCount != 0) {
                for (int j = 0; j < subCount; j++) {
                    RefSlot sub = {0};
                    int* dataB; int cntA; void* dataA; int cntC; int* dataC; int cntB;
                    if (mgr->GetResource(subs[j].key, g_ResourceGroup, sub.Out())) {
                        if (GetArrayPropC(sub.p, 0x105f5303, &cntA, &dataA) &&
                            GetArrayPropB(sub.p, 0x105f5302, &cntB, &dataB) &&
                            GetArrayPropB(sub.p, 0x105f5304, &cntC, &dataC) &&
                            cntA >= 3 && cntA == cntB && cntA == cntC)
                        {
                            GrowEntries();
                            Entry* e = entries.end - 1;
                            e->key = keys[i];
                            e->count = cntA;
                            e->offset = offsets.size();
                            offsets.append(dataA, (char*)dataA + cntA * 12);
                            offsets.append(dataB, dataB + cntA);
                            offsets.append(dataC, dataC + cntA);
                        }
                    }
                    if (sub.p) sub.p->Release();
                }
            }
        }
        if (res.p) res.p->Release();
    }
    SortEntries(entries.begin, entries.end);
    for (uint32_t* p = keys.begin; p < keys.end; p++) {}
    keys.Destroy();
}
