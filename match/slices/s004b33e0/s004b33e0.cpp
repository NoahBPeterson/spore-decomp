// Slice s004b33e0: SP::cSPEditorPaintTheme prop/region helpers (unoptimized editor module,
// /Od /Ob1 /arch:SSE, no /EHsc).  Complements slice s004b2320.
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct cSPColorRGB { uint32_t x, y, z; };
struct PropObj;
struct PropMgr;

struct PropObj {
    virtual void v0(); virtual void Release();
    virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
    virtual char Has(uint32_t id);
    virtual void v8(); virtual void v9();
    virtual void* Get(uint32_t id);
};
struct PropMgr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual char GetPropertyList(int id, uint32_t type, void** out);
};

extern "C" {
    void* SP_PropertyManager();
    void  FUN_006a0760(void* obj, uint32_t id, void* a, void* b);
    void  FUN_004553b0(void* out, void* key);
    void* FUN_00454420(void* value);
    char  FUN_0041db10(void* a, void* b, void* c);
    void  FUN_004098a0(void* dst, const void* src);
    void  FUN_00566c50(void* tree);
    int   FUN_004b5210(void* out, void* key);
    float* FUN_004b5370(void* key);
    int   FUN_00564f50();
    void  FUN_00422c50();
    void  FUN_004e8a30(void* o);
    int   FUN_004accf0();
    void* FUN_004accb0(int i);
    void  FUN_004769b0(void* a, void* b);
    void  GetPropertyAsIntArray(PropObj* list, uint32_t id, void* a, void* b);
    void  FUN_004b3e10(int a);
    void  FUN_004b5980(void* tag);
    void  FUN_00441d10(void* a);
    void  FUN_004b5xxx_push(void* value);
}

// ---- editor paint records and the two lookaside containers used below -------------------------
struct PaintRGB {                       // rw::math::fpu::Vector3Template<float,0>, 12 bytes
    uint32_t x, y, z;
    PaintRGB(const PaintRGB& src);      // 0x004098a0 (copy ctor)
};

struct PaintEntry {                     // SP::tSPEditorPaint, 0x1c bytes
    uint32_t mPaint;                    // +0x00
    PaintRGB mColor1;                   // +0x04
    PaintRGB mColor2;                   // +0x10
    PaintEntry();                       // 0x00440f60 (default ctor)
    PaintEntry(uint32_t paint, const PaintRGB& c1, const PaintRGB& c2)
        : mPaint(paint), mColor1(c1), mColor2(c2) {}
};

struct PaintCount;                      // rbtree node value: PaintEntry key + tally
struct PaintEntryIter {                 // eastl rbtree iterator over one node pointer
    void* mpNode;                       // +0x00
    PaintEntryIter(void* node);         // 0x00566c50
    PaintEntryIter& operator++();       // 0x00422c50
    PaintCount* operator->();           // 0x00564f50
};
inline bool operator!=(const PaintEntryIter& a, const PaintEntryIter& b)
{
    return a.mpNode != b.mpNode;
}
struct PaintCount {
    PaintEntry mEntry;                  // +0x00 (node+0x10)
    int        mCount;                  // +0x1c (node+0x2c)
};
struct AllocTag { AllocTag() {} };
struct PaintCountTree {                 // eastl::rbtree<PaintCount-ish>, 0x1c bytes
    void*    mpAllocator;               // +0x00
    void*    mpEnd;                     // +0x04 anchor node (also the end iterator)
    void*    mpBegin;                   // +0x08 leftmost node
    void*    mpRoot;                    // +0x0c
    uint8_t  mColor;                    // +0x10
    uint8_t  mPad0, mPad1, mPad2;
    uint32_t mSize;                     // +0x14
    uint32_t mAllocTag;                 // +0x18
    PaintCountTree(const AllocTag& = AllocTag());       // 0x004b5980
    ~PaintCountTree() { DoNuke(mpRoot); }
    PaintEntryIter begin() { return PaintEntryIter(mpBegin); }
    PaintEntryIter end() { return PaintEntryIter(&mpEnd); }
    PaintEntryIter find(const PaintEntry& key);         // 0x00564b50
    int& operator[](const PaintEntry& key);             // 0x004b5160
    void DoNuke(void* root);                            // 0x004e8a30
};

struct PaintFindResult {                // eastl hashtable find() result pair
    void* mpNode;                       // +0x00
    void* mpFound;                      // +0x04
};
struct PaintTable {                     // eastl::map<int, tSPEditorPaint> hashtable, 0x11c bytes
    void*   mpBuckets;                  // +0x000
    void*   mpEnd;                      // +0x004
    char    mPad[0x110];                // +0x008
    uint8_t mVersion;                   // +0x118
    char    mPad2[3];
    PaintFindResult* Find(PaintFindResult* out, const int& key);   // 0x004553b0
    PaintEntry* GetPaint(const int& key);                          // 0x00454420
};
struct PaintMapList {                   // eastl::vector<PaintTable, sp_vector_allocator>, 0x11c bytes
    PaintTable* mpBegin;                // +0x000
    PaintTable* mpEnd;                  // +0x004
    PaintTable* mpCap;                  // +0x008
    char        mInline[0x110];         // +0x00c
};

struct ModelEntry;                      // rbtree node value: unsigned key + PaintMapList
struct ModelIter {                      // eastl rbtree iterator over the theme's model map
    void* mpNode;                       // +0x00
    ModelIter(void* node);              // 0x00566c50
    ModelIter& operator++();            // 0x00422c50
    ModelEntry* operator->();           // 0x00564f50
};
inline bool operator!=(const ModelIter& a, const ModelIter& b)
{
    return a.mpNode != b.mpNode;
}
struct ModelEntry {
    uint32_t     mKey;                  // +0x00 (node+0x10)
    PaintMapList mValue;                // +0x04 (node+0x14)
};

namespace SP {
struct PaintVector {
    void* mpBegin; void* mpEnd; void* mpCap;
    char  mInline[0x110];
    void* Insert(void* value);
    void FUN_004b4fa0(void* a);   // 0x004b4fa0
};
struct ModelTree {                      // eastl::map<unsigned, vector<PaintTable>>, 0x1c bytes
    void*    mpAllocator;               // +0x00
    void*    mpEnd;                     // +0x04 anchor node (also the end iterator)
    void*    mpBegin;                   // +0x08 leftmost node
    void*    mpRoot;                    // +0x0c
    uint8_t  mColor;                    // +0x10
    char     mPad[3];
    uint32_t mSize;                     // +0x14
    char     mAllocTag[4];              // +0x18
    ModelIter begin() { return ModelIter(mpBegin); }
    ModelIter end() { return ModelIter(&mpEnd); }
    void* FUN_004b5080(void* a);        // 0x004b5080
};
class cSPEditorPaintTheme {
public:
    void* mpVtbl0; void* mpVtbl1; int mRefCount;
    PaintVector mPropTheme;          // +0xc
    ModelTree   mModelTheme;         // +0x128
    uint32_t mPropThemeID;           // +0x144
    uint32_t mSourceRef;             // +0x148
    uint32_t mResourceType;          // +0x14c
    void* mpClosestBegin;            // +0x150
    void* mpClosestEnd;              // +0x154
    void* mpClosestCap;              // +0x158
    char  pad_15c[8];
    uint32_t mSkinEffects[3];
    uint32_t mSkinEffectSeeds[3];
    cSPColorRGB mSkinColors[3];
    void InitClosestRegions(int a, int b);
    void SetRegionColor(int a, int b, int c, int d);
    int  FUN_004b33e0(int* out, int* range, int key);
    char FUN_004b3660(int* out, int key);
    char FUN_004b3910(int* out, int key, int arg3);
    char FUN_004b3a50(int out, int key, int arg3);
    char FUN_004b3b20(int key, int* outCount, int* outPtr);
    void FUN_004b3c20(int model);
};
}
using namespace SP;

extern uint32_t DAT_015d6cc8;
extern PaintRGB DAT_015d6e2c;
extern "C" void* g_closestReserve;

// @ 0x004b33e0
int cSPEditorPaintTheme::FUN_004b33e0(int* out, int* range, int key)
{
    if (out != 0) {
        PaintEntry paint(0, DAT_015d6e2c, DAT_015d6e2c);
        PaintCountTree counts;

        int i = 0;
        int n = (int)(((PaintMapList*)range)->mpEnd - ((PaintMapList*)range)->mpBegin);
        for (; i < n; i++) {
            PaintTable* table = &((PaintMapList*)range)->mpBegin[i];
            PaintFindResult pair;
            table->Find(&pair, key);
            void* node = (pair.mpNode != pair.mpFound) ? pair.mpNode : table->mpEnd;
            if (node != table->mpEnd) {
                paint = *table->GetPaint(key);
                PaintEntryIter end = counts.end();
                PaintEntryIter it = counts.find(paint);
                if (it != end)
                    ++counts[paint];
                else
                    counts[paint] = 1;
            }
        }

        if (!counts.mSize)
            return 0;

        int bestCount = 0;
        PaintEntry best(0, DAT_015d6e2c, DAT_015d6e2c);
        PaintEntryIter it = counts.begin();
        PaintEntryIter end = counts.end();
        while (it != end) {
            if (it.operator->()->mCount > bestCount) {
                bestCount = it.operator->()->mCount;
                best = it.operator->()->mEntry;
            }
            ++it;
        }
        *((PaintEntry*)out) = best;
        return bestCount;
    }
    return 0;
}

// @ 0x004b3660
char cSPEditorPaintTheme::FUN_004b3660(int* out, int key)
{
    if (out != 0) {
        int bestCount = 0;
        PaintEntry best;
        ModelIter it = mModelTheme.begin();
        ModelIter end = mModelTheme.end();
        while (it != end) {
            PaintMapList* list = &it.operator->()->mValue;
            PaintEntry candidate;
            int n = FUN_004b33e0((int*)&candidate, (int*)list, key);
            if (n > bestCount) {
                best = candidate;
                bestCount = n;
            }
            ++it;
        }
        if (bestCount > 0) {
            *((PaintEntry*)out) = best;
            return 1;
        }
    }
    return 0;
}

// @ 0x004b3730
void cSPEditorPaintTheme::InitClosestRegions(int a, int b)
{
    FUN_004769b0((void*)mResourceType, (void*)mSourceRef);
    int id = 0;
    bool match = false;
    if ((a == 0x24682294) || (a == 0x476a98c7)) {
        if ((b == 0x24682294) || (b == 0x476a98c7))
            id = 0x1625a584;
        else if (b == 0x2399be55)
            id = (int)0xb5306a4c;
    } else if (a == 0x2399be55) {
        if ((b == 0x24682294) || (b == 0x476a98c7))
            id = (int)0x844c912e;
        else if (b == 0x2399be55)
            id = (int)0xb3ef1246;
    }
    (void)match;
    if (id != 0) {
        PropObj* list = 0;
        PropMgr* mgr = (PropMgr*)SP_PropertyManager();
        if (list)
            list->Release();
        char ok = mgr->GetPropertyList(id, 0x4060e200, (void**)&list);
        if (ok) {
            int count = 0;
            int data = 0;
            GetPropertyAsIntArray(list, 0x52c57aa, &count, &data);
            FUN_00441d10(&mpClosestBegin);
            for (int i = 0; i < count; i++)
                FUN_004b5xxx_push((void*)(data + i * 4));
        }
        if (list)
            list->Release();
    }
}

// @ 0x004b3910
char cSPEditorPaintTheme::FUN_004b3910(int* out, int key, int arg3)
{
    if (out == 0)
        return 0;
    FUN_00566c50((void*)((int)this + 300));
    int local_c = 0;
    void* found = (void*)FUN_004b5210(&local_c, &arg3);
    if (found != 0) {
        void* r = mModelTheme.FUN_004b5080((void*)&arg3);
        int iVar2 = FUN_004b33e0(out, (int*)r, key);
        if (iVar2 != 0)
            return 1;
    }
    char cVar1 = FUN_004b3660(out, key);
    if (cVar1 != '\0')
        return 1;
    int a = 0, b = 0;
    FUN_004553b0(&a, &key);
    int node = (a == b) ? *(int*)((int)this + 0x10) : a;
    if (node != *(int*)((int)this + 0x10)) {
        int* src = (int*)FUN_00454420(&key);
        for (int k = 0; k < 7; k++)
            out[k] = src[k];
        return 1;
    }
    return 0;
}

// @ 0x004b3a50
char cSPEditorPaintTheme::FUN_004b3a50(int out, int key, int arg3)
{
    int local_8 = 0;
    int local_10 = 0;
    char c = FUN_004b3b20(key, &local_8, &local_10);
    if (c == '\0') {
        if (FUN_004b3910((int*)out, key, arg3) != 0)
            return 1;
    } else {
        for (int i = 0; i < local_8; i++) {
            if (FUN_004b3910((int*)out, *(int*)(local_10 + i * 4), arg3) != 0)
                return 1;
        }
    }
    int limit = 0x22;
    int i = 0;
    while (i < limit) {
        if (FUN_004b3910((int*)out, i, arg3) != 0)
            return 1;
        i++;
    }
    return (char)(i - limit);   // always 0 here; keeps the tail in a full-width eax like the /Od original
}

// @ 0x004b3b20
char cSPEditorPaintTheme::FUN_004b3b20(int key, int* outCount, int* outPtr)
{
    int self = (int)this;
    if (outCount == 0 || outPtr == 0 || key < 0)
        return 0;
    *outCount = 0;
    int found = 0;
    int start = *(int*)(self + 0x150);
    int n = (*(int*)(self + 0x154) - start) >> 2;
    int i = 0;
    while (i < n && found != key) {
        if (*(int*)(start + i * 4) == -1)
            found++;
        i++;
    }
    if (i == n)
        return 0;
    *outPtr = start + i * 4;
    do {
        int off = i * 4;
        i++;
        if (*(int*)(start + off) == -1)
            break;
        *outCount = *outCount + 1;
    } while (i != n);
    return 1;
}

// @ 0x004b3c20
void cSPEditorPaintTheme::FUN_004b3c20(int model)
{
    if (model != 0) {
        int local = *(int*)(model + 0x1c);
        int local2 = local;
        void* r = mModelTheme.FUN_004b5080(&local2);
        ((PaintVector*)r)->FUN_004b4fa0((void*)(model + 0x4c8));
    }
}

// @ 0x004b3c70
void cSPEditorPaintTheme::SetRegionColor(int a, int b, int c, int d)
{
    PropObj* list = 0;
    PropMgr* mgr = (PropMgr*)SP_PropertyManager();
    if (list)
        list->Release();
    mgr->GetPropertyList(d, 0x406a6f00, (void**)&list);
    if (list != 0) {
        int n = 0;
        int data = 0;
        FUN_006a0760(list, 0xf21a7bdc, &data, &n);
        for (int i = 0; i < n; i++) {
            if (*(char*)(data + i) == 1) {
                int a1 = 0, b1 = 0;
                FUN_004553b0(&a1, &i);
                int node = (a1 == b1) ? *(int*)((char*)&mPropTheme + 0xc)
                                      : a1;
                if (node != *(int*)((char*)&mPropTheme + 0xc)) {
                    int e = (int)FUN_00454420(&i);                    *(int*)(e + 0x10) = a;
                    *(int*)(e + 0x14) = b;
                    *(int*)(e + 0x18) = c;
                }
            }
        }
    }
    if (list)
        list->Release();
}
