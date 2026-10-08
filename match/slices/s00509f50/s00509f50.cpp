// w1g1 slice s00509f50 -- table-index helpers and small vector ops.
//
// Flags: /Od /Ob1 /MD /Gy /TP (x87 fabs; /arch:SSE for movss copies).

typedef unsigned int uint32_t;
typedef unsigned char uint8_t;

float fabsf(float);
struct V3 { float x, y, z; };

// @ 0x0050a880  (component-wise abs)
V3* __cdecl AbsV3(V3* out, const V3* in)
{
    out->x = fabsf(in->x);
    out->y = fabsf(in->y);
    out->z = fabsf(in->z);
    return out;
}

// ---------------------------------------------------------------------------
int TableInsert(int self, int idx, uint32_t* key, int slot);   // 0x00509c80
extern const signed char gCode3[3];                            // 0x013f18d0
extern const signed char gOff3[3];                             // 0x013f18d8

// ---- types of the big skin/mesh container (see slice s00507670 for the full layout) ----
void* operator new(unsigned int size, const char* pName, int flags, unsigned int debugFlags,
                   const char* pFile, int line);              // 0x00f473a0
void operator delete(void* p);                                 // 0x00f47380

struct Alloc { Alloc() {} };
struct SpAlloc { char pad[8]; SpAlloc(const Alloc& a); };      // 0x00429360

// 0x14-byte vector_set of (first, second) pairs: the work list of the face walk
struct Pair2 {
    unsigned int first, second;
    Pair2() {}
    Pair2(unsigned int a, unsigned int b) : first(a), second(b) {}
};
struct PairSet {
    Pair2* mpBegin; Pair2* mpEnd; Pair2* mpCap; SpAlloc mAlloc;
    PairSet(const Alloc& a = Alloc());                         // 0x00540470
    ~PairSet();                                                // 0x004cddd0
    unsigned int size() const;                                 // 0x00474050
    Pair2& operator[](unsigned int i) { return mpBegin[i]; }
    void push_back(const Pair2& v);                            // 0x005402c0
    void erase(Pair2* first, Pair2* last);                     // 0x00530c80
};

// vector<unsigned> with out-of-line resize
struct VecU {
    unsigned int* mpBegin; unsigned int* mpEnd; unsigned int* mpCap; SpAlloc mAlloc;
    unsigned int size() const { return mpEnd - mpBegin; }
    unsigned int& operator[](unsigned int i) { return mpBegin[i]; }
    unsigned int* erase(unsigned int* first, unsigned int* last);               // 0x004769b0
    void insert(unsigned int* pos, unsigned int n, const unsigned int& value);  // 0x004cea40
    void resize(unsigned int n)                                // 0x004cd3c0
    {
        if (n > size()) {
            unsigned int value = 0;
            unsigned int diff = n - size();
            unsigned int* pos = mpEnd;
            insert(pos, diff, value);
        } else {
            erase(mpBegin + n, mpEnd);
        }
    }
};
struct Vertex12 { float x, y, z; };
struct VecV {
    Vertex12* mpBegin; Vertex12* mpEnd; Vertex12* mpCap; SpAlloc mAlloc;
    int size() const { return mpEnd - mpBegin; }
};
struct Entry { unsigned int a, b; };
struct VecE {                                                  // 8-byte entries
    Entry* mpBegin; Entry* mpEnd; Entry* mpCap; SpAlloc mAlloc;
    Entry* begin() { return mpBegin; }
    Entry* end() { return mpEnd; }
    unsigned int size() const { return mpEnd - mpBegin; }
    Entry* erase(Entry* first, Entry* last);                   // 0x00530c80
    void insert(Entry* pos, unsigned int n, const Entry& value);   // 0x004cef00
    void resize(unsigned int n)                                // 0x0050da10
    {
        if (n > size()) {
            Entry value;
            value.a = 0;
            value.b = 0;
            unsigned int diff = n - size();
            Entry* pos = mpEnd;
            insert(pos, diff, value);
        } else {
            erase(mpBegin + n, mpEnd);
        }
    }
};

struct SkinBuildData {                                         // 0x94-byte "Skinner" element
    unsigned int mId;                                          // +0
    unsigned int mGroup;                                       // +4
    char pad08[0x58 - 8];
    float mMinU, mMaxU, mMinV, mMaxV;                          // +0x58
    int mZero;                                                 // +0x68
    char pad6c[0x94 - 0x6c];
    SkinBuildData();                                           // 0x004cbdf0
    SkinBuildData(const SkinBuildData& o);                     // 0x00508320
    ~SkinBuildData();                                          // 0x00507b30
    SkinBuildData& operator=(const SkinBuildData& o);          // 0x0050a9e0
};
struct VecP {                                                  // vector of element pointers
    SkinBuildData** mpBegin; SkinBuildData** mpEnd; SkinBuildData** mpCap; SpAlloc mAlloc;
    unsigned int size() const { return mpEnd - mpBegin; }
    void push_back(SkinBuildData* const& v);                   // 0x00454860
};
extern const float kFloatMax;                                  // 0x013f18c4

// Unused stack words that stand in for the reserved frames of inline callees that cl declined
// (see docs/matching.md, /Od frame layout).
template <int N> inline void ScratchSlots() { unsigned int slots[N]; }

inline void FillEntries(Entry* first, Entry* last, const Entry& value)
{
    for (; first != last; ++first)
        *first = value;
}

struct SlotTable {
    char pad00[8];
    VecV mVerts;            // +0x08
    char pad1c[0x58 - 0x1c];
    VecU mIndices;          // +0x58
    char pad6c[0x80 - 0x6c];
    VecU mEdgeSlots;        // +0x80
    VecU mAdjacent;         // +0x94
    char padA8[0xe4 - 0xa8];
    VecP mGroups;           // +0xe4
    char padf8[0x110 - 0xf8];
    VecU mFaceMark;         // +0x110
    char pad124[0x1b8 - 0x124];
    VecE mSlots;            // +0x1b8
    char pad1cc[0x200 - 0x1cc];

    // @ 0x00509f50
    void InsertEdge(int a, int b, uint32_t* key);

    // @ 0x0050a920
    uint8_t Adjacent(int a, int b, int c, int d);

    // @ 0x0050a730
    int FaceHelper(int face);

    // @ 0x0050a9e0
    void* CopyRecord(void** src);

    // @ 0x00509c80
    int Insert(int idx, SkinBuildData* key, int slot);

    // @ 0x0052e640
    uint8_t Check(int face, int edge, SkinBuildData* group);

    // @ 0x0050a0a0
    void BuildFaces();
};

void SlotTable::InsertEdge(int a, int b, uint32_t* key)
{
    uint32_t idx = (uint32_t)(a * 3 + b);
    signed char c = gCode3[idx % 3];
    int i = (int)(signed char)gOff3[idx % 3] + (int)idx;
    uint32_t* e = (uint32_t*)(*(int*)((char*)this + 0x1b8) + *(int*)(*(int*)((char*)this + 0x58) + i * 4) * 8);
    if (*e == *key)
        *(uint32_t*)(*(int*)((char*)this + 0x80) + i * 4) = e[1];
    else
        TableInsert((int)this, i, key, -1);
    *(uint32_t*)(*(int*)((char*)this + 0x80) + idx * 4) =
        *(uint32_t*)(*(int*)((char*)this + 0x1b8) + *(int*)(*(int*)((char*)this + 0x58) + idx * 4) * 8 + 4);
    *(uint32_t*)(*(int*)((char*)this + 0x80) + ((int)c + (int)idx) * 4) =
        *(uint32_t*)(*(int*)((char*)this + 0x1b8) + *(int*)(*(int*)((char*)this + 0x58) + ((int)c + (int)idx) * 4) * 8 + 4);
    *(uint32_t*)(*(int*)((char*)this + 0x110) + a * 4) = ~*key;
}

uint8_t SlotTable::Adjacent(int a, int b, int c, int d)
{
    int i = d * 3 + (c + 1) % 3;
    int* t = *(int**)((char*)this + 0x6c);
    uint8_t result;
    if (t[(a * 3 + b)] == t[i]) {
        int j = t[(a * 3 + (b + 1) % 3)];
        if (j == t[(d * 3 + c)])
            result = 1;
        else
            result = 0;
    } else {
        result = 0;
    }
    return result;
}

int SlotTable::FaceHelper(int face)
{
    int base = *(int*)((char*)this + 8);
    int tab = *(int*)((char*)this + 0x58);
    return *(int*)(tab + (base + face * 0xc));
}

void CopyRangeA(const void* src);   // vector<float>::operator=
void CopyRangeB(const void* src);   // 0x0050db60
void CopyRangeC(const void* src);   // 0x0050dea0

void* SlotTable::CopyRecord(void** src)
{
    void** dst = (void**)this;
    dst[0] = src[0];
    dst[1] = src[1];
    CopyRangeA(src + 2);
    CopyRangeA(src + 7);
    CopyRangeA(src + 0xc);
    CopyRangeB(src + 0x11);
    dst[0x16] = src[0x16];
    dst[0x17] = src[0x17];
    dst[0x18] = src[0x18];
    dst[0x19] = src[0x19];
    dst[0x1a] = src[0x1a];
    CopyRangeA(src + 0x1b);
    CopyRangeC(src + 0x20);
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x0050a0a0  face-table builder: groups the faces of the mesh into connected, coplanar-id
// patches ("SkinBuildData" elements) by flood fill over the shared-edge adjacency table.
// ---------------------------------------------------------------------------
void SlotTable::BuildFaces()
{
    unsigned int nTris = mIndices.size() / 3;
    mEdgeSlots.resize(mIndices.size());
    mSlots.resize(mVerts.size());
    Entry tmpl;
    tmpl.a = 0xffffffff;
    FillEntries(mSlots.begin(), mSlots.end(), tmpl);
    ScratchSlots<2>();

    SkinBuildData* region = new("Skinner", 0, 0, 0, 0) SkinBuildData();
    const unsigned int none = 0x7fffffff;
    unsigned int index = mGroups.size();
    ScratchSlots<44>();
    PairSet pending;
    unsigned int qPos;
    unsigned int resume = 0;
    while (1) {
        unsigned int f;
        unsigned int grp;
        int err;
        f = resume;
        if (mFaceMark[f] > index) {
            for (f = 0; f < nTris; ++f) {
                if (mFaceMark[f] <= index)
                    break;
            }
        }
        if (f == nTris)
            break;
        grp = FaceHelper(f);
        *region = SkinBuildData();
        region->mId = index;
        region->mGroup = grp;
        region->mMinU = kFloatMax;
        region->mMaxU = -kFloatMax;
        region->mMinV = kFloatMax;
        region->mMaxV = -kFloatMax;
        region->mZero = 0;
        pending.erase(pending.mpBegin, pending.mpEnd);
        qPos = 0;
        err = Insert(f * 3, region, -1);
        err = Insert(f * 3 + 1, region, -1);
        InsertEdge(f, 0, (uint32_t*)region);
        for (unsigned int i = 0; i < 3; ++i) {
            unsigned int val;
            unsigned int edgeIdx;
            unsigned int otherFace;
            unsigned int adjEdge;
            edgeIdx = f * 3 + i;
            val = mAdjacent[edgeIdx];
            otherFace = val / 3;
            adjEdge = val % 3;
            if (mFaceMark[otherFace] <= index && FaceHelper(otherFace) == grp &&
                Adjacent(f, i, otherFace, adjEdge) && !Check(otherFace, adjEdge, region)) {
                mFaceMark[otherFace] = none;
                pending.push_back(Pair2(otherFace, adjEdge));
            }
        }
        while (qPos < pending.size()) {
            unsigned int side;
            Pair2 pair;
            unsigned int a;
            pair = pending[qPos++];
            a = pair.first;
            side = pair.second;
            InsertEdge(a, side, (uint32_t*)region);
            for (unsigned int m = 0; m < 3; ++m) {
                if (m != side) {
                    unsigned int nbr2;
                    unsigned int offset2;
                    unsigned int word2;
                    unsigned int otherEdge2;
                    offset2 = a * 3 + m;
                    word2 = mAdjacent[offset2];
                    nbr2 = word2 / 3;
                    otherEdge2 = word2 % 3;
                    if (mFaceMark[nbr2] <= index) {
                        if (FaceHelper(nbr2) == grp && Adjacent(a, m, nbr2, otherEdge2) &&
                            !Check(nbr2, otherEdge2, region)) {
                            mFaceMark[nbr2] = none;
                            pending.push_back(Pair2(nbr2, otherEdge2));
                        } else {
                            mFaceMark[nbr2] = index + 1;
                            resume = nbr2;
                        }
                    }
                }
            }
        }
        mGroups.push_back(new("Skinner", 0, 0, 0, 0) SkinBuildData(*region));
        index = index + 1;
    }
    delete region;
}
