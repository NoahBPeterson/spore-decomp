// Slice s004fe8c0: cSPTransform back-transform helpers and a skeleton/bone graph class (/Od region).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }
struct Vec3 { float x, y, z; };
struct Vec3f : Vec3 {
    Vec3f() {}
    Vec3f(const Vec3f& o) { x = o.x; y = o.y; z = o.z; }
    Vec3f& operator=(const Vec3f& o) { x = o.x; y = o.y; z = o.z; return *this; }
};
struct Mat3 { float m[9]; };

struct cSPTransform {
    uint16_t mFlags;
    uint16_t mModificationCount;
    Vec3 mTranslation;
    float mScale;
    Mat3 mRotation;
    void BackTransformPoint(Vec3* p);
    cSPTransform& operator=(const cSPTransform& o);  // 0x00537dc0
};

void __cdecl FUN_004fc5a0(Vec3* p, Vec3* t);
void __cdecl FUN_004a9d20(Vec3* p, float* s);
Vec3* __cdecl FUN_0047ff90(Vec3* out, Mat3* m, Vec3* p);

// @ 0x004ff660
Vec3f* __cdecl FUN_004ff660(Vec3f* out, cSPTransform* t, Vec3f* in) {
    ScratchSlots<9>();
    Vec3f v = *in;
    t->BackTransformPoint(&v);
    *out = v;
    return out;
}

// @ 0x004ff6d0
void cSPTransform::BackTransformPoint(Vec3* p) {
    FUN_004fc5a0(p, &mTranslation);
    if (mScale != 1.0f)
        FUN_004a9d20(p, &mScale);
    if (mFlags & 2) {
        ScratchSlots<6>();
        Vec3 tmp;
        *p = *FUN_0047ff90(&tmp, &mRotation, p);
    }
}


template<class T, int N> struct Vec {
    T* mpBegin; T* mpEnd; T* mpCap; uint32_t mAlloc[2];
    void erase(T* f, T* l);
    void clear() { ScratchSlots<N>(); erase(mpBegin, mpEnd); }
    void resize(uint32_t n);  // 0x004cd3c0 (only Vec<int,4> uses it)
    void grow(uint32_t n);
    T& operator[](uint32_t i) { return mpBegin[i]; }
    int size() const { return mpEnd - mpBegin; }
};
struct DwordVector : Vec<uint32_t, 12> {
    void assign(const uint32_t* first, const uint32_t* last, char tag);
};

struct SrcNode {        // 0x34 bytes
    Vec3 mPos;
    DwordVector mEdges;
    uint32_t pad[5];
};
struct SrcLink { uint32_t a, b; };

struct GraphNode {      // 0x48 bytes
    Vec3 mPos;
    DwordVector mEdges; // +0x0c: indices into the edge array
    uint32_t pad[9];
    int mDepth;         // +0x44
};

struct GraphEdge {      // 0x54 bytes
    cSPTransform mXform;
    Vec3f mLocal;       // +0x38
    uint8_t mFlag;      // +0x44
    uint8_t pad[3];
    int mA;             // +0x48
    int mB;             // +0x4c
    int mC;             // +0x50
};

// The two grow instantiations live at different addresses; separate classes let each carry its own.
struct NodeVec : Vec<GraphNode, 7> {
    void grow(uint32_t n);  // 0x00501350
};
struct EdgeVec : Vec<GraphEdge, 6> {
    void grow(uint32_t n);  // 0x00501430
};

struct UIntVec {
    uint32_t* mpBegin; uint32_t* mpEnd; uint32_t* mpCap; uint32_t mAlloc[2];
    UIntVec(uint32_t n);  // 0x005012d0
    ~UIntVec();  // 0x004c0b80
    uint32_t& operator[](uint32_t i) { return mpBegin[i]; }
};
struct UIntDeque {
    uint32_t pad[17];
    UIntDeque(char* tag);  // 0x004aa100
    ~UIntDeque();  // 0x004aa120
    bool empty();  // 0x00425430
    uint32_t* front();  // 0x00501e20
    void pop_front();  // 0x00501eb0
    void push_back(const uint32_t* v);  // 0x00501e40
};

struct cSPModelGraph {
    wchar_t* mpName;  // eastl wstring: begin, end, cap, alloc
    wchar_t* mpNameEnd;
    wchar_t* mpNameCap;
    uint32_t mNameAlloc;
    NodeVec mNodes;     // +0x10
    EdgeVec mEdges;     // +0x24
    int mRoot;          // +0x38
    uint8_t mFlag;      // +0x3c
    uint8_t pad3d[3];
    Vec<int, 4> mParent;     // +0x40
    Vec<uint32_t, 12> mExtra;     // +0x54
    int m68;
    void* mpFile;       // +0x6c

    void Reset();
    void Build(const wchar_t* name, Vec<SrcNode, 0>* nodes, Vec<SrcLink, 0>* links, Vec<cSPTransform, 0>* xforms, int firstChild, char flag);
    void ComputeTree();
    void NameAssign(const wchar_t* b, const wchar_t* e);  // 0x00423650
    void FUN_004ff750();
    void Finish();
};

extern "C" __declspec(dllimport) int __cdecl fclose(void*);
char __fastcall GetResourceTypeFromModelType(Vec<GraphNode, 7>* v);  // 0x00526430

// @ 0x004feb50
void cSPModelGraph::Reset() {
    if (mpName != mpNameEnd) {
        *mpName = 0;
        mpNameEnd = mpName;
    }
    mNodes.clear();
    mEdges.clear();
    mRoot = -1;
    mParent.clear();
    mExtra.clear();
    m68 = 0;
    if (mpFile) {
        fclose(mpFile);
        mpFile = 0;
    }
    Finish();
}

// @ 0x004fe8c0
void cSPModelGraph::Build(const wchar_t* name, Vec<SrcNode, 0>* nodes, Vec<SrcLink, 0>* links, Vec<cSPTransform, 0>* xforms, int firstChild, char flag) {
    Reset();
    mFlag = flag;
    const wchar_t* e = name;
    while (*e) e++;
    NameAssign(name, name + (e - name));
    mNodes.grow(nodes->size());
    uint32_t i, n;
    for (i = 0, n = nodes->size(); i < n; i++) {
        SrcNode* src = &(*nodes)[i];
        GraphNode* dst = mNodes.mpBegin + i;
        dst->mPos = src->mPos;
        char tag;
        const uint32_t* sl = (*nodes)[i].mEdges.mpEnd;
        const uint32_t* sf = (*nodes)[i].mEdges.mpBegin;
        mNodes[i].mEdges.assign(sf, sl, tag);
        mNodes.mpBegin[i].mDepth = -1;
    }
    mEdges.grow(links->size());
    int j, m;
    for (j = 0, m = links->size(); j < m; j++) {
        mEdges.mpBegin[j].mA = (*links)[j].a;
        mEdges.mpBegin[j].mB = (*links)[j].b;
        mEdges.mpBegin[j].mC = -1;
        mEdges.mpBegin[j].mXform = (*xforms)[j];
        mEdges.mpBegin[j].mFlag = j >= firstChild;
    }
    ComputeTree();
    FUN_004ff750();
}

// @ 0x004fec80
void cSPModelGraph::ComputeTree() {
    if (GetResourceTypeFromModelType(&mNodes)) return;
    char tag;
    UIntDeque queue(&tag);
    UIntVec depth(mNodes.size());
    uint32_t bestDepth = 0, bestNode = 0xffffffff;
    uint32_t best3Depth = 0, best3Node = 0xffffffff;
    uint32_t i;
    for (i = 0; i < (uint32_t)mNodes.size(); i++) {
        GraphNode* n = &mNodes[i];
        int cnt = n->mEdges.size();
        if (cnt == 1) {
            depth[i] = 0;
            bestNode = i;
            queue.push_back(&i);
        } else {
            depth[i] = 0xffffffff;
        }
    }
    while (!queue.empty()) {
        int cur = *queue.front();
        queue.pop_front();
        GraphNode* node = &mNodes[cur];
        uint32_t n = node->mEdges.size();
        for (i = 0; i < n; i++) {
            GraphEdge* ed = &mEdges[node->mEdges[i]];
            uint32_t other = (ed->mA == cur) ? ed->mB : ed->mA;
            uint32_t nb = other;
            GraphNode* onode = &mNodes[other];
            if (depth[other] == 0xffffffff) {
                uint32_t unvisited = 0, maxd = 0;
                for (uint32_t k = 0; k < (uint32_t)onode->mEdges.size(); k++) {
                    GraphEdge* e2 = &mEdges[onode->mEdges[k]];
                    uint32_t o2 = (e2->mA == (int)other) ? e2->mB : e2->mA;
                    if (depth[o2] == 0xffffffff) {
                        unvisited++;
                    } else {
                        uint32_t* p = &depth[o2];
                        if (*p <= maxd) p = &maxd;
                        maxd = *p;
                    }
                }
                if (unvisited < 2) {
                    depth[other] = maxd + 1;
                    if (unvisited == 1) queue.push_back(&nb);
                    if (bestDepth < depth[nb]) {
                        bestDepth = depth[nb];
                        bestNode = nb;
                    }
                    if (2 < (uint32_t)onode->mEdges.size() && best3Depth < depth[nb]) {
                        best3Depth = depth[nb];
                        best3Node = nb;
                    }
                }
            }
        }
    }
    mParent.resize(mNodes.size());
    mRoot = (best3Node == 0xffffffff) ? bestNode : best3Node;
    mParent[mRoot] = -1;
    for (uint32_t* d = depth.mpBegin; d != depth.mpEnd; d++) *d = 0xffffffff;
    queue.push_back((uint32_t*)&mRoot);
    depth[mRoot] = 0;
    while (!queue.empty()) {
        int cur = *queue.front();
        queue.pop_front();
        GraphNode* node = &mNodes[cur];
        uint32_t n = node->mEdges.size();
        for (i = 0; i < n; i++) {
            GraphEdge* ed = &mEdges[node->mEdges[i]];
            int other = (ed->mA == cur) ? ed->mB : ed->mA;
            int nb = other;
            if (depth[other] == 0xffffffff) {
                depth[other] = depth[cur] + 1;
                mParent[other] = cur;
                queue.push_back((uint32_t*)&nb);
            }
        }
    }
    for (uint32_t k = 0; k < (uint32_t)mEdges.size(); k++) {
        int a = mEdges[k].mA;
        int b = mEdges[k].mB;
        if (mParent[a] == b) {
            int t = mEdges[k].mA;
            mEdges[k].mA = mEdges[k].mB;
            mEdges[k].mB = t;
            b = a;
            a = mEdges[k].mA;
        }
        GraphEdge* ed = &mEdges[k];
        Vec3f tmp;
        ed->mLocal = *FUN_004ff660(&tmp, &ed->mXform, (Vec3f*)&mNodes[a]);
    }
}
