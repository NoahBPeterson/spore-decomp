// Slice s00b981a0: cSpotGrid::FinishRegions (0x00b983b0, 2122 bytes).
// Flags: /O2 /MD /Gy /TP /GS-.
// The planet "spot" grid (static object at 0x156c060, see s00ba0770) is a 6-face cube of mnSize x mnSize
// cells (12 bytes each: region pointer +0, border flag byte +4). After the flood fill every region is a
// rectangle of cells; this pass (1) sorts the regions by area (largest first), (2) grows every live region
// into neighbouring regions that lie completely inside its row/column span and have uniform thickness,
// (3) re-points the absorbed cells at the grown region (and marks the absorbed regions dead), (4) recomputes
// the region's border flags (OR of the flag bytes of the cells around it) and its area, and finally
// (5) drops the dead regions from the list and re-sorts it by area.
typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

extern "C" void* __cdecl memcpy(void* dst, const void* src, unsigned int n);

struct cRegion {               // size 0x18
    u8    mbDone;              // +0x00 (0 = dead / not a region any more)
    char  mFace;               // +0x01
    short mRowMin;             // +0x02
    short mRowMax;             // +0x04
    short mColMin;             // +0x06
    short mColMax;             // +0x08
    short pad0a;
    int   mArea;               // +0x0c
    u8    mSide[4];            // +0x10 flags OR'ed from the cells left / above / right / below
    u8    mbAnySide;           // +0x14
    u8    pad15[3];
};
struct cCell { cRegion* mpRegion; u8 mFlag; u8 pad05[3]; u32 pad08; };   // size 0xc

int __cdecl WrapCubeFace(int size, int* face, int* col, int* row, int a, int b);   // 0x684ca0

typedef char (__cdecl* RegionPred)(const cRegion*, const cRegion*);
void __cdecl SortRegions(cRegion** first, cRegion** last, RegionPred pred);        // 0xbbf6c0
void __cdecl introsort(cRegion** first, cRegion** last, int depth, RegionPred pred);   // 0xd53940
void __cdecl insertion_sort(cRegion** first, cRegion** last, RegionPred pred);     // 0xb909f0

// larger regions first: return b->mArea < a->mArea;  (inlined at the one place the pointer is also called)
char __cdecl RegionLess(const cRegion* a, const cRegion* b);   // 0xb90730

struct cSpotGrid {
    u32 pad00[2];
    cRegion** mpRegionBegin;    // +0x08
    cRegion** mpRegionEnd;      // +0x0c
    u32 pad10[5];
    int mnSize;                 // +0x24
    u32 pad28[3];
    cCell* mpCells;             // +0x34

    void FinishRegions();                                                  // 0xb983b0

    __forceinline cCell& CellAt(int face, int row, int col)
    {
        int f = face, r = row, c = col;
        while (WrapCubeFace(mnSize, &f, &c, &r, 0, 0))
            ;
        return mpCells[(f * mnSize + r) * mnSize + c];
    }
};

// @ 0x00b983b0
void cSpotGrid::FinishRegions()
{
    SortRegions(mpRegionBegin, mpRegionEnd, (RegionPred)RegionLess);

    cRegion** const listEnd = mpRegionEnd;
    for (cRegion** it = mpRegionBegin; it != listEnd; ++it) {
        cRegion* region = *it;
        if (region->mbDone == 0)
            continue;

        const int face = region->mFace;
        int rowMin = region->mRowMin;
        int rowMax = region->mRowMax;
        int colMin = region->mColMin;
        int colMax = region->mColMax;
        bool growLeft = true, growRight = true, growUp = true, growDown = true;
        do {
            // grow the column span: scan the cells left of / right of every row
            int thickLeft = 0, thickRight = 0, thickUp = 0, thickDown = 0;
            int row = rowMin;
            while (growLeft || growRight) {
                if (row > rowMax) {
                    if (growLeft) colMin -= thickLeft;
                    if (growRight) colMax += thickRight;
                    break;
                }
                cRegion* left = CellAt(face, row, colMin - 1).mpRegion;
                cRegion* right = CellAt(face, row, colMax + 1).mpRegion;
                bool okLeft = left && left->mbDone && left->mRowMin >= rowMin && left->mRowMax <= rowMax
                    && (thickLeft == 0 || left->mColMax - left->mColMin + 1 == thickLeft);
                growLeft = growLeft & okLeft;
                if (growLeft && thickLeft == 0)
                    thickLeft = left->mColMax - left->mColMin + 1;
                bool okRight = right && right->mbDone && right->mRowMin >= rowMin && right->mRowMax <= rowMax
                    && (thickRight == 0 || right->mColMax - right->mColMin + 1 == thickRight);
                growRight = growRight & okRight;
                if (growRight && thickRight == 0)
                    thickRight = right->mColMax - right->mColMin + 1;
                row++;
            }
            // grow the row span: scan the cells above / below every column
            int col = colMin;
            while (growUp || growDown) {
                if (col > colMax) {
                    if (growUp) rowMin -= thickUp;
                    if (growDown) rowMax += thickDown;
                    break;
                }
                cRegion* up = CellAt(face, rowMin - 1, col).mpRegion;
                cRegion* down = CellAt(face, rowMax + 1, col).mpRegion;
                bool okUp = up && up->mbDone && up->mColMin >= colMin && up->mColMax <= colMax
                    && (thickUp == 0 || up->mRowMax - up->mRowMin + 1 == thickUp);
                growUp = growUp & okUp;
                if (growUp && thickUp == 0)
                    thickUp = up->mRowMax - up->mRowMin + 1;
                bool okDown = down && down->mbDone && down->mColMin >= colMin && down->mColMax <= colMax
                    && (thickDown == 0 || down->mRowMax - down->mRowMin + 1 == thickDown);
                growDown = growDown & okDown;
                if (growDown && thickDown == 0)
                    thickDown = down->mRowMax - down->mRowMin + 1;
                col++;
            }
        } while (growLeft || growRight || growUp || growDown);

        region->mColMin = (short)colMin;
        region->mRowMin = (short)rowMin;
        region->mRowMax = (short)rowMax;
        region->mColMax = (short)colMax;

        // take over every cell of the grown rectangle
        for (int r = rowMin; r <= rowMax; r++) {
            for (int c = colMin; c <= colMax; c++) {
                cRegion* other = CellAt(face, r, c).mpRegion;
                if (other && other != region) {
                    other->mbDone = 0;
                    CellAt(face, r, c).mpRegion = region;
                }
            }
        }

        // border flags
        region->mSide[0] = 0;
        region->mSide[1] = 0;
        region->mSide[2] = 0;
        region->mSide[3] = 0;
        region->mbAnySide = 0;
        const int leftCol = colMin - 1;
        const int rightCol = colMax + 1;
        int r;
        for (r = rowMin; r <= rowMax; r++) {
            region->mSide[0] |= CellAt(face, r, leftCol).mFlag;
            region->mSide[2] |= CellAt(face, r, rightCol).mFlag;
        }
        int c;
        for (c = colMin; c <= colMax; c++) {
            region->mSide[1] |= CellAt(face, rowMin - 1, c).mFlag;
            region->mSide[3] |= CellAt(face, rowMax + 1, c).mFlag;
        }
        region->mbAnySide = region->mSide[3] | region->mSide[2] | region->mSide[1] | region->mSide[0];
        region->mArea = (colMax - colMin + 1) * (rowMax - rowMin + 1);
    }

    // drop the dead regions (remove_if + erase), then sort again
    cRegion** const first = mpRegionBegin;
    cRegion** const last = mpRegionEnd;
    cRegion** dst = first;
    while (dst != last && (*dst)->mbDone != 0)
        ++dst;
    if (dst != last) {
        for (cRegion** src = dst + 1; src != last; ++src) {
            if ((*src)->mbDone != 0) {
                *dst = *src;
                ++dst;
            }
        }
    }
    memcpy(dst, last, (mpRegionEnd - last) * sizeof(cRegion*));
    mpRegionEnd -= (last - dst);

    cRegion** const sfirst = mpRegionBegin;
    cRegion** const slast = mpRegionEnd;
    if (sfirst != slast) {
        int n = (int)(slast - sfirst);
        int lg = 0;
        for (int m = n; m != 0; m >>= 1)
            lg++;
        introsort(sfirst, slast, lg * 2 - 2, (RegionPred)RegionLess);
        if (n > 28) {
            cRegion** const mid = sfirst + 28;
            insertion_sort(sfirst, mid, (RegionPred)RegionLess);
            for (cRegion** p = mid; p != slast; ++p) {
                cRegion* val = *p;
                cRegion** q = p;
                while (q[-1]->mArea < val->mArea) {
                    *q = q[-1];
                    --q;
                }
                *q = val;
            }
        } else {
            insertion_sort(sfirst, slast, (RegionPred)RegionLess);
        }
    }
}

// ===========================================================================
// cSpawnTable (global at 0x0168890c): sorted vector of 16-byte spawn records
// plus the hash-bucket nodes that own the lists of spawned objects.
// ===========================================================================
struct Entry { u32 k0, k1, v2, v3; };   // 16 bytes
struct Key   { u32 m0, m1, m2; };       // 12 bytes (EA::ResourceMan::Key)

class Node;

class ChildVector {
public:
    void** mpBegin;      // +0x00
    void** mpEnd;        // +0x04
    void** mpCap;        // +0x08
    u32    mPad0c;       // +0x0c
    u32    mPad10;       // +0x10
    u32    mSize;        // +0x14
    void*  mInline[8];   // +0x18

    void CopyFrom(const void* src);                  // 0x01011cc0
    u32  AllocFlagBefore() const { return ((const u32*)mpBegin)[-1]; }
};

struct NodeKey { u32 m0, m1; };

class Node {
public:
    union { NodeKey mKey; Node* mpFreeNext; };   // +0x00
    ChildVector mChildren;                      // +0x08
    Node* mpNext;                               // +0x40
};

struct NodeSource {
    NodeKey mKey;
    ChildVector mChildren;
};

struct InsertResult {
    Entry* mpPos;
    bool   mbInserted;
    char   mPad05[3];
};

void* operator_new(void* allocator, const char* name, int a, int b, const char* file, int line);  // 0xf473a0
void  operator_delete(void* p);                                                                   // 0xf47380
void* __cdecl FUN_00b952e0(Entry* first, Entry* last, const Entry* value, u32 flag);              // 0xb952e0

static const char kAllocFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";

class cSpawnTable {
public:
    Entry* mpBegin;      // +0x00
    Entry* mpEnd;        // +0x04
    Entry* mpCap;        // +0x08
    u32    mPad0c;       // +0x0c
    u32    mPad10;       // +0x10
    bool   mbFlag;       // +0x14
    u8     mPad15[7];    // +0x15
    Node*  mpFreeList;   // +0x1c
    u32    mPad20;       // +0x20
    Node*  mpPoolBegin;  // +0x24
    Node*  mpPoolEnd;    // +0x28
    void*  mpAllocator;  // +0x2c
    Node*  mpSentinel;   // +0x30

    void Realloc(u32 n);                                      // 0x00b95ef0
    Entry* InsertAt(Entry* pos, const Entry* e);              // 0x00b97140
    Entry* InsertShift(Entry* pos, const Entry* e);           // 0x00b96710
    InsertResult* Insert(InsertResult* out, const Entry* e);  // 0x00b98230
    Node* AllocNode(const NodeSource* src);                   // 0x00b98270
    void DestroyBuckets(Node** buckets, u32 count);           // 0x00b982e0
};
extern cSpawnTable g_SpawnTable;   // 0x0168890c

// ---------------------------------------------------------------------------
// Appends a value to each of the two child vectors and recomputes their sum.
// ---------------------------------------------------------------------------
class HeapU32Vector {
public:
    u32* mpBegin;
    u32* mpEnd;
    u32* mpCap;
    void DoInsertValue(u32* pos, const u32& value);   // 0x004558a0

    __forceinline u32  size() const  { return (u32)(mpEnd - mpBegin); }
    __forceinline u32* begin() const { return mpBegin; }

    __forceinline void push_back(const u32& value)
    {
        if (mpEnd < mpCap)
        {
            u32* p = mpEnd++;
            if (p)
                *p = value;
        }
        else
        {
            DoInsertValue(mpEnd, value);
        }
    }
};

class U32Vector {
public:
    u32* mpBegin;
    u32* mpEnd;
    u32* mpCap;
    void DoInsertKey4(u32* pos, const u32& value);    // 0x00b96600

    __forceinline void push_back(const u32& value)
    {
        if (mpEnd < mpCap)
        {
            u32* p = mpEnd++;
            if (p)
                *p = value;
        }
        else
        {
            DoInsertKey4(mpEnd, value);
        }
    }
};

class cChildList {
public:
    u32 mPad00[2];          // +0x00
    HeapU32Vector mValues;  // +0x08
    u32 mPad14[2];          // +0x14
    U32Vector mObjects;     // +0x1c
    u32 mPad28[2];          // +0x28
    u32 mTotal;             // +0x30

    void Add(u32 value, u32 object);
};

// @ 0x00b981a0
void cChildList::Add(u32 value, u32 object)
{
    mValues.push_back(value);
    mObjects.push_back(object);

    mTotal = 0;
    u32 n = mValues.size();
    for (u32 i = 0; i < n; ++i)
        mTotal += mValues.begin()[i];
}

// ---------------------------------------------------------------------------
// Inserts a record and reports the (position, inserted) pair.
// ---------------------------------------------------------------------------
// @ 0x00b98230
InsertResult* cSpawnTable::Insert(InsertResult* out, const Entry* e)
{
    Entry* pos = (Entry*)FUN_00b952e0(mpBegin, mpEnd, e, mbFlag);
    out->mpPos = InsertAt(pos, e);
    out->mbInserted = true;
    return out;
}

// ---------------------------------------------------------------------------
// Takes a node from the free list (or allocates one) and copies the source
// key and child vector into it.
// ---------------------------------------------------------------------------
// @ 0x00b98270
Node* cSpawnTable::AllocNode(const NodeSource* src)
{
    Node* node = mpFreeList;
    if (node)
        mpFreeList = node->mpFreeNext;
    else
        node = (Node*)operator_new(mpAllocator, "Simulator", 0, 0, kAllocFile, 0xd1);

    if (node)
    {
        const NodeSource* s = src;
        node->mKey = s->mKey;
        ChildVector& children = node->mChildren;
        children.mpBegin = children.mInline;
        children.mpEnd = children.mInline;
        children.mSize = 0;
        children.mpCap = children.mpBegin + 8;
        children.CopyFrom(&s->mChildren);
    }
    node->mpNext = 0;
    return node;
}

// ---------------------------------------------------------------------------
// Destroys every bucket chain: the owned objects, the child storage and then
// the node itself (pool nodes go back to the free list).
// ---------------------------------------------------------------------------
struct Destroyable {
    virtual void v00();
    virtual void v01();
};

// @ 0x00b982e0
void cSpawnTable::DestroyBuckets(Node** buckets, u32 count)
{
    for (u32 i = 0; i < count; i++)
    {
        Node* node = buckets[i];
        while (node)
        {
            Node* cur = node;
            node = cur->mpNext;
            void** end = cur->mChildren.mpEnd;
            void** p = cur->mChildren.mpBegin;
            while (p < end)
            {
                if (*p)
                    ((Destroyable*)*p)->v01();
                ++p;
            }
            if (cur->mChildren.mpBegin && cur->mChildren.AllocFlagBefore() != 0)
                operator_delete(cur->mChildren.mpBegin);

            if (cur != mpSentinel)
            {
                if (cur < mpPoolBegin || cur >= mpPoolEnd)
                {
                    operator_delete(cur);
                }
                else
                {
                    cur->mpFreeNext = mpFreeList;
                    mpFreeList = cur;
                }
            }
        }
        buckets[i] = 0;
    }
}

// ---------------------------------------------------------------------------
// Spawn-table serialization.
// ---------------------------------------------------------------------------
class IOStream {
public:
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual void s3(); virtual void s4(); virtual void s5();
    virtual void* GetStream();                 // +0x18
};

class IOSource {
public:
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
    virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
    virtual IOStream* GetStreamSource();       // +0x20
};

class cSPEditorSpeciesManager {
public:
    const void* GetProfile(const Key& key);    // 0x004df550
};
cSPEditorSpeciesManager* GetSetting9();        // 0x00401090

void __cdecl ReadInt32(void* stream, void* out, int count, int flags);   // 0x0093a780
void __cdecl ReadBool(void* stream, bool* out);                          // 0x0093ac80
void __cdecl FUN_00ae2ed0(void* obj, Key* key);                          // 0x00ae2ed0
void* __cdecl copy_705250(const void* first, const void* last, void* dst);// 0x00705250

// ---------------------------------------------------------------------------
// Reads the spawn table: a count, then that many {key0, key1, resource key,
// bool} records; records whose profile exists are merged into the table.
// ---------------------------------------------------------------------------
// @ 0x00b98c00
bool FUN_00b98c00(IOSource* source)
{
    cSPEditorSpeciesManager* mgr = GetSetting9();

    u32 count = 0;
    void* stream = source->GetStreamSource()->GetStream();
    ReadInt32(stream, &count, 1, 0);

    Entry* first = g_SpawnTable.mpBegin;
    Entry* last = g_SpawnTable.mpEnd;
    copy_705250(last, last, first);
    g_SpawnTable.mpEnd -= last - first;
    g_SpawnTable.Realloc(count);

    for (u32 i = 0; i < count; i++)
    {
        u32 key0 = 0;
        u32 key1 = 0;

        stream = source->GetStreamSource()->GetStream();
        ReadInt32(stream, &key0, 1, 0);

        stream = source->GetStreamSource()->GetStream();
        ReadInt32(stream, &key1, 1, 0);

        Key key = { 0, 0, 0 };
        FUN_00ae2ed0(source, &key);

        bool keep;
        stream = source->GetStreamSource()->GetStream();
        ReadBool(stream, &keep);

        const void* profile = mgr->GetProfile(key);
        if (profile)
        {
            Entry entry;
            entry.k0 = key0;
            entry.k1 = key1;
            entry.v2 = (u32)profile;
            entry.v3 = keep;

            Entry* pos = (Entry*)FUN_00b952e0(g_SpawnTable.mpBegin, g_SpawnTable.mpEnd,
                                              &entry, g_SpawnTable.mbFlag);
            if (pos == g_SpawnTable.mpEnd && g_SpawnTable.mpEnd != g_SpawnTable.mpCap)
            {
                Entry* end = g_SpawnTable.mpEnd;
                g_SpawnTable.mpEnd = end + 1;
                *end = entry;
            }
            else
            {
                g_SpawnTable.InsertShift(pos, &entry);
            }
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// Game-noun lookup used by the scenario/cell spawners.
// ---------------------------------------------------------------------------
struct Vector3 { float x, y, z; };

struct NounEmbedded {
    virtual void e00(); virtual void e01(); virtual void e02(); virtual void e03();
    virtual void e04(); virtual void e05(); virtual void e06(); virtual void e07();
    virtual void e08(); virtual void e09(); virtual void e10();
    virtual Vector3* GetPosition();            // +0x2c
};

struct NounObject {
    char mPad00[0x34];
    NounEmbedded mEmbedded;                    // +0x34
    char mPad38[0x108 - 0x38];
    u32 mTypeId0;                              // +0x108
    char mPad10c[4];
    u32 mTypeId1;                              // +0x110
};

class PtrInlineVector {
public:
    void** mpBegin;      // +0x00
    void** mpEnd;        // +0x04
    void** mpCap;        // +0x08
    u32    mPad0c;       // +0x0c
    u32    mPad10;       // +0x10
    u32    mSize;        // +0x14
    void*  mInline[8];   // +0x18

    PtrInlineVector() : mpBegin(mInline), mpEnd(mInline), mpCap(mInline + 8), mSize(0) {}

    void DoInsertKey4(void** pos, void* const& value);   // 0x00b96600
    u32  AllocFlagBefore() const { return ((const u32*)mpBegin)[-1]; }

    __forceinline void push_back(void* const& value)
    {
        if (mpEnd < mpCap)
        {
            void** p = mpEnd++;
            if (p)
                *p = value;
        }
        else
        {
            DoInsertKey4(mpEnd, value);
        }
    }
};

struct GameDataVec {
    void*  mpUnused;    // +0x00
    void** mpBegin;     // +0x04
    void** mpEnd;       // +0x08
};

class cGameNounManager {
public:
    GameDataVec* GetGameDataVector(void* f0, void* f1, void* f2, void* f3, u32 id);  // 0x00b21340
};
cGameNounManager* NounManager();      // 0x00b3d300

class cDirectPropertyList {
public:
    int GetIntProperty(u32 id) const; // 0x006a2660
};
extern cDirectPropertyList* g_AppProperties;   // 0x015fd918

class RandomLinearCongruential {
public:
    u32 RandomUint32Uniform(u32 n);   // 0x00a68fb0
};
extern RandomLinearCongruential g_Random;      // 0x016888e8

void __cdecl FUN_00d1bef0(int value);          // 0x00d1bef0

// ---------------------------------------------------------------------------
// Collects the game nouns with the "spawnable" pair of type ids, picks one
// (the property-selected index when valid, else a uniform random index) and
// returns its position plus the noun itself.
// ---------------------------------------------------------------------------
// @ 0x00b98f00
bool FUN_00b98f00(Vector3* outPos, NounObject** chosen)
{
    PtrInlineVector objects;

    cGameNounManager* mgr = NounManager();
    GameDataVec* data = mgr->GetGameDataVector((void*)0x00cd7d10, (void*)0x00d3d420,
                                              (void*)0x00ace070, (void*)0x00b1e500,
                                              0x36be27e);
    void** it = data->mpBegin;
    void** end = data->mpEnd;
    while (it != end)
    {
        NounObject* noun = (NounObject*)*it;
        if (noun->mTypeId0 == 0x91fe517b && noun->mTypeId1 == 0xd8c67022)
            objects.push_back(noun);
        ++it;
    }

    if (objects.mpBegin != objects.mpEnd)
    {
        int index = g_AppProperties->GetIntProperty(0x508662a);
        if (index < 0 || index >= (int)(objects.mpEnd - objects.mpBegin))
            index = (int)g_Random.RandomUint32Uniform((u32)(objects.mpEnd - objects.mpBegin));
        FUN_00d1bef0(index);

        NounObject* noun = (NounObject*)objects.mpBegin[index];
        Vector3* pos = noun->mEmbedded.GetPosition();
        *outPos = *pos;
        if (chosen)
            *chosen = (NounObject*)objects.mpBegin[index];

        if (objects.mpBegin && objects.AllocFlagBefore() != 0)
            operator_delete(objects.mpBegin);
        return true;
    }

    if (objects.mpBegin && objects.AllocFlagBefore() != 0)
        operator_delete(objects.mpBegin);
    return false;
}
