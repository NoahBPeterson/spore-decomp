// w1g1 slice s004e88a0 -- /Od EASTL rbtree/hashtable plumbing around 0x4e88a0.
//
// Flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast.

typedef unsigned int uint32_t;

// allocator deallocate thunk (one pointer arg, cdecl)
void AllocFree(void* p); // 0x00f47380

// allocator allocate (allocator, size, alignment, extra) -- 0x0042dee0
void* AllocNodeMem(void* alloc, uint32_t size, uint32_t align, uint32_t extra);

struct Key5 {
    int m0, m1, m2, m3, m4;
};

struct NodeAlloc {
    char pad[0x18];
    Key5* Allocate(const Key5* rp); // @ 0x004e8d30
};

struct FreeCtx {
    void FreeNodes(void* p); // @ 0x004e8a30
};

// rbtree node: [+0 left][+4 right][+8 parent?][+0xc colour?][+0x10 key].
struct RBNode {
    RBNode* mLeft;   // +0
    RBNode* mRight;  // +4
    RBNode* mParent; // +8
    int     mColor;  // +0xc
    int     mKey;    // +0x10
};

// iterator/handle wrapper: a single node pointer.
struct RBSink {
    RBNode* mNode;         // +0
    void Init(void* node); // 0x00566c50
    int* Payload();        // 0x00564f50  (returns node + 0x10)
};

inline bool KeyLess(int a, int b) { return a < b; }

// eastl red-black tree relink helper (external to this slice).
namespace eastl {
    void RBTreeInsert(void* node, void* parent, void* header, int side); // 0x009216a0
}

// ---- external rbtree helpers called from this slice ----
// Retail __thiscall (this in ECX, callee pops): modelled as __fastcall + a dummy
// second register argument, the convention used elsewhere in this tree.
void  __fastcall FUN_005673e0(void* dst, int, const void* src);                            // 0x005673e0
void  __fastcall FUN_00422c50(void* it, int);                                              // 0x00422c50
void  __fastcall FUN_004e8da0(void* self, int, void* out, const Key5* value, char flag);   // 0x004e8da0
void* __fastcall FUN_004e8980(void* self, int, void* out, RBNode* pos, const Key5* value); // 0x004e8980

struct RBTree {
    int      pad0;    // +0
    void*    mAnchor; // +4
    void*    mAnchor2;// +8
    RBNode*  mRoot;   // +0xc
    int      pad10;   // +0x10
    int      mCount;  // +0x14

    void*   LowerBound(RBSink* out, int* key);                                      // @ 0x004e89c0
    int     FindOrInsert(const int* key);                                           // @ 0x004e88a0
    void*   InsertUnique(void* result, RBNode* pos, const Key5* value, int unused); // @ 0x004e8a80
    RBSink* InsertNode(RBSink* result, RBNode* pos, const Key5* value, char flag);  // @ 0x004e8be0
};

// ---------------------------------------------------------------------------
// Transform object (r/w render transform) and the math helpers it drives.
// ---------------------------------------------------------------------------
struct Vector3 { float x, y, z; };

struct Matrix33 {
    float m[9];
    void Assign(const void* src); // 0x0041cb40
};

// Snapshot one row (three floats) of a matrix as a vector value.
inline Vector3 Row3(const Matrix33& m, int row)
{
    Vector3 v;
    v.x = m.m[row * 3 + 0];
    v.y = m.m[row * 3 + 1];
    v.z = m.m[row * 3 + 2];
    return v;
}

// refcounted object vtable: +0 AddRef, +4 Release, +0xc GetBasis.
struct RefVtbl {
    void (__thiscall* mAddRef)(void* self);              // +0x00
    void (__thiscall* mRelease)(void* self);             // +0x04
    void (__thiscall* mSlot08)(void* self);              // +0x08
    void (__thiscall* mGetBasis)(void* self, void* out); // +0x0c
};

struct RefObj {
    RefVtbl* mVtbl; // +0x00
};

// render object vtable: the transform-builder slot lives at +0x114.
struct BuildVtbl {
    void* mSlots[0x114 / 4];                                                   // +0x00..+0x110
    char (__thiscall* mBuild)(void* self, void* a, int b, void** out, char c); // +0x114
};

struct RenderObj {
    BuildVtbl* mVtbl;      // +0x00
    uint32_t   mPad04[3];  // +0x04
    void*      mp10;       // +0x10
    uint32_t   mPad14;     // +0x14
    void*      mp18;       // +0x18
    uint32_t   mPad1c[11]; // +0x1c
    Vector3    mVec48;     // +0x48
    uint32_t   mPad54[97]; // +0x54
    float      mf1d8;      // +0x1d8
};

extern float    g_015da588; // 0x015da588
extern float    g_015da58c; // 0x015da58c
extern float    g_015da590; // 0x015da590
extern Matrix33 g_015da458; // 0x015da458

Matrix33* Matrix33_Convert(Matrix33* out, const Matrix33* in);                  // 0x0041ded0
float*    FUN_0041db10(float* out, float* a, float* b);                         // 0x0041db10  (out = a - b)
float*    MulVectorMatrix(float* out, const float* v, const float* m);          // 0x0041daf0
Matrix33* MulMatrixMatrix(Matrix33* out, const Matrix33* a, const Matrix33* b); // 0x0041de20
float*    FUN_00453880(float* out, float* a, float* b);                         // 0x00453880
void      __fastcall Vector3_CopyCtor(void* self, int, const void* src);        // 0x004098a0
Vector3   FUN_00499b40(Vector3 a, Vector3 b, Vector3 c, Vector3 p);             // 0x00499b40
Matrix33* FUN_00499f10(Matrix33* out, Vector3 a, Vector3 b, Vector3 c);         // 0x00499f10
void*     __fastcall FUN_004363d0(void* self, int, void* arg);                  // 0x004363d0
void      FUN_49ef80(void* tracker, void* vec);                                 // 0x0049ef80
void      __fastcall FUN_004e95e0(void* self, int, void* out1, void* out2);     // 0x004e95e0

struct RWXform {
    RenderObj* mp00;   // +0x00  (render object)
    void*      mp04;   // +0x04  (refcounted object)
    Vector3    mVec08; // +0x08
    Vector3    mVec14; // +0x14
    Matrix33   mMat20; // +0x20
    int        mInt44; // +0x44
    char       mChar48;// +0x48

    RWXform();                                                                              // @ 0x004e8f70
    void Build(RenderObj* a0, void* a1, float fx, float fy, float fz, void* a5, void* a6);  // @ 0x004e9050
    char Attach(RenderObj* a0, int a1, char a2);                                            // @ 0x004e9500
};

// @ 0x004e8a30
// Post-order free of a node chain: recurse into the first field, deallocate the
// node, then continue with its second field.
void FreeCtx::FreeNodes(void* p)
{
    while (p != 0) {
        FreeNodes(*(void**)p);
        void* next;
        void* tmp = ((void**)p)[1];
        next = p;
        AllocFree(next);
        p = tmp;
    }
}

// ---------------------------------------------------------------------------
// Skeletons for the remaining /Od bodies.
// ---------------------------------------------------------------------------

// @ 0x004e88a0
// Tree find-or-insert: look up *key and, when absent, insert a zero-initialised tail.
// Returns the address of the stored element's second word (node + 0x14).
int RBTree::FindOrInsert(const int* key)
{
    RBSink lb;   // lower_bound result
    RBSink end;  // end() handle
    LowerBound(&lb, (int*)key);
    end.Init((char*)this + 4);
    if (lb.mNode == end.mNode || *key < *lb.Payload()) {
        Key5 value;
        value.m0 = *key;
        value.m1 = 0;
        value.m2 = 0;
        value.m3 = 0;
        value.m4 = 0;
        RBSink node;
        RBSink* r = (RBSink*)FUN_004e8980(this, 0, &node, lb.mNode, &value);
        lb.mNode = r->mNode;
    }
    return (int)((char*)lb.Payload() + 4);
}

// @ 0x004e89c0
// rbtree lower_bound: descend to the first node whose key is not less than *key.
void* RBTree::LowerBound(RBSink* out, int* key)
{
    RBNode* current = mRoot;
    RBNode* candidate = (RBNode*)&mAnchor;
    void* unused;
    while (current != 0) {
        if (KeyLess(current->mKey, *key)) {
            current = current->mLeft;
        } else {
            candidate = current;
            current = current->mRight;
        }
    }
    out->Init(candidate);
    return out;
}

// @ 0x004e8a80
// rbtree insert_unique with a hint.  `unused` mirrors the retail frame's extra slot.
void* RBTree::InsertUnique(void* result, RBNode* pos, const Key5* value, int unused)
{
    (void)unused;
    if (pos == (RBNode*)mAnchor || pos == (RBNode*)((char*)this + 4)) {
        if (mCount != 0 && ((RBNode*)mAnchor)->mKey < value->m0) {
            InsertNode((RBSink*)result, (RBNode*)mAnchor, value, 0);
        } else {
            RBSink n;
            FUN_004e8da0(this, 0, &n, value, 0);
            FUN_005673e0(result, 0, &n);
        }
    } else {
        RBSink before;
        FUN_005673e0(&before, 0, &pos);
        FUN_00422c50(&before, 0);
        if (pos->mKey < value->m0 && value->m0 < before.mNode->mKey) {
            if (pos->mLeft == 0)
                InsertNode((RBSink*)result, pos, value, 0);
            else
                InsertNode((RBSink*)result, before.mNode, value, 1);
        } else {
            RBSink n;
            FUN_004e8da0(this, 0, &n, value, 0);
            FUN_005673e0(result, 0, &n);
        }
    }
    return result;
}

// @ 0x004e8be0
// Allocate a node for `value`, relink it into the tree at `pos`, bump the count, and
// hand the new node back through the `result` iterator.
RBSink* RBTree::InsertNode(RBSink* result, RBNode* pos, const Key5* value, char flag)
{
    int side;
    if (flag == 0 && pos != (RBNode*)((char*)this + 4) && pos->mKey <= value->m0)
        side = 1;
    else
        side = 0;
    RBNode* node = (RBNode*)reinterpret_cast<NodeAlloc*>(this)->Allocate(value);
    eastl::RBTreeInsert(node, pos, (char*)this + 4, side);
    this->mCount += 1;
    result->Init(node);
    return result;
}

// @ 0x004e8c80
// Copy a range of refcounted pointers into `dest`, AddRef-ing each non-null element.
// Returns the destination past the last element written.
void** Body8c80(void** first, void** last, void** dest)
{
    void** d = dest;
    for (void** s = first; s != last; ++s, ++d) {
        if (d != 0 && (*d = *s) != 0)
            (*(void(__thiscall**)(void*))*d)(*d);
    }
    return d;
}

// @ 0x004e8d30
// Allocates a 0x24-byte node and stores the 0x14-byte key at node+0x10.  Retail keeps the
// node+0x10 temporary in its own /Od slot but returns the raw node (the iterator's node base).
Key5* NodeAlloc::Allocate(const Key5* rp)
{
    void* foo = AllocNodeMem((char*)this + 0x18, 0x24, 4, 0);
    Key5* cc = (Key5*)((char*)foo + 0x10);
    // Retail copies through a discarded conditional expression: the copy happens when the key slot
    // is non-null and the (unused) result is the key pointer, else null; the node is returned.
    cc != 0 ? &(*cc = *rp) : (Key5*)0;
    return (Key5*)foo;
}

// @ 0x004e8da0
// 309-byte /Od body.  Skeleton.
void Body8da0(void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
}

// @ 0x004e8ee0
// Same refcounted-pointer range copy, but writes the destination end through `out`
// and returns `out`.
void** ApplyCopyLoop8ee0(void** out, void** first, void** last, void** dest)
{
    void** d = dest;
    for (void** s = first; s != last; ++s, ++d) {
        if (d != 0 && (*d = *s) != 0)
            (*(void(__thiscall**)(void*))*d)(*d);
    }
    *out = d;
    return out;
}

// @ 0x004e8f70
// Construct a transform: null render/refcounted pointers, default basis vectors,
// the default matrix and the reset sentinels.
RWXform::RWXform()
{
    mp00 = 0;
    mp04 = 0;
    if (mp04 != 0)
        ((RefObj*)mp04)->mVtbl->mAddRef(mp04);
    mVec08.x = g_015da588;
    mVec08.y = g_015da58c;
    mVec08.z = g_015da590;
    mVec14.x = g_015da588;
    mVec14.y = g_015da58c;
    mVec14.z = g_015da590;
    mMat20.Assign(&g_015da458);
    mInt44 = -1;
    mChar48 = 0;
}

// @ 0x004e9050
// Rebuild the transform from a render object, an optional refcounted object, a
// translation vector and two optional matrix/vector inputs.
void RWXform::Build(RenderObj* a0, void* a1, float fx, float fy, float fz, void* a5, void* a6)
{
    Matrix33 local_78;   // the basis matrix; its three rows are the retail local_78/6c/60
    Matrix33 local_b0, local_cc, local_54;
    Matrix33 local_fc, local_120, local_148, local_154, local_160, local_16c, local_178;
    float    local_124;
    Vector3  local_30, local_24;
    Vector3  vf;

    mp00 = a0;
    if (a1 != mp04) {
        void* old = mp04;
        if (a1 != 0)
            ((RefObj*)a1)->mVtbl->mAddRef(a1);
        mp04 = a1;
        if (old != 0)
            ((RefObj*)old)->mVtbl->mRelease(old);
    }
    {
        // retail walks a dead 3-entry table at 0xc stride.
        int n = 3;
        char* p = (char*)&local_78;
        for (;;) {
            --n;
            if (n < 0)
                break;
            p += 0xc;
        }
    }
    ((RefObj*)mp04)->mVtbl->mGetBasis(mp04, &local_78);

    void* tracker = FUN_004363d0(a0, 0, &local_b0);
    FUN_49ef80(tracker, &local_78.m[0]);

    vf.x = fx;
    vf.y = fy;
    vf.z = fz;
    Vector3 r0 = Row3(local_78, 0);
    Vector3 r1 = Row3(local_78, 1);
    Vector3 r2 = Row3(local_78, 2);
    Vector3 basis = FUN_00499b40(r0, r1, r2, vf);
    mVec14.x = basis.x;
    mVec14.y = basis.y;
    mVec14.z = basis.z;

    Vector3 copy78;
    Vector3_CopyCtor(&copy78, 0, &local_78);
    FUN_00499f10(&local_54, copy78, r1, r2);

    if (a6 != 0) {
        Matrix33* conv = Matrix33_Convert(&local_fc, &local_54);
        Matrix33* prod = MulMatrixMatrix(&local_120, (const Matrix33*)a6, conv);
        mMat20 = *prod;
    } else {
        mMat20 = g_015da458;
    }

    if (a5 != 0) {
        local_124 = mp00->mf1d8;
        Matrix33_Convert(&local_148, &local_54);
        FUN_0041db10(&local_154.m[0], (float*)a5, (float*)&vf);
        MulVectorMatrix(&local_160.m[0], &local_154.m[0], &local_148.m[0]);
        FUN_00453880(&local_16c.m[0], &local_160.m[0], &local_124);
        mVec08.x = local_16c.m[0];
        mVec08.y = local_16c.m[1];
        mVec08.z = local_16c.m[2];
    } else {
        mVec08.x = g_015da588;
        mVec08.y = g_015da58c;
        mVec08.z = g_015da590;
    }

    FUN_004e95e0(this, 0, &local_30, &local_24);
    FUN_0041db10(&local_178.m[0], &local_30.x, &a0->mVec48.x);
    local_30.x = local_178.m[0];
    local_30.y = local_178.m[1];
    local_30.z = local_178.m[2];
}

// @ 0x004e9500
// Bind the transform to a render object and let it rebuild itself through the
// object's builder vtable slot.  Records the arguments on success.
char RWXform::Attach(RenderObj* a0, int a1, char a2)
{
    mp00 = a0;
    if (mp00 == 0 || mp00->mp10 == 0 || mp00->mp18 == 0)
        return 0;
    void** slot = &mp04;
    if (*slot != 0) {
        void* old = *slot;
        *slot = 0;
        ((RefObj*)old)->mVtbl->mRelease(old);
    }
    char r = ((RenderObj*)mp00->mp18)->mVtbl->mBuild(mp00->mp18, mp00->mp10, a1, slot, a2);
    if (r != 0) {
        mInt44 = a1;
        mChar48 = a2;
    }
    return r;
}
