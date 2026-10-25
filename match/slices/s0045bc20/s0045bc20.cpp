// Slice s0045bc20: skinning-influence bookkeeping helpers from the /Od editor module.
// Flags: /Od /Ob1 /MD /Gy /TP.
#include "types.h"

extern "C" void FUN_0045d790(void*);              // 0x45d790 (vector assign, masked)
extern "C" void* FUN_0045da80(void* dst, void* src); // 0x45da80
extern "C" void* _Unchecked_idl0(void* dst, void* a, void* b); // 0x0045daa0

// =====================================================================
// @ 0x45bc20  free-list unlink (reverse the free chain from `index`)
// =====================================================================
struct FreeList {
    char  pad[0xec];
    int*  next;
    void  Unlink(int index);
};

void FreeList::Unlink(int index)
{
    int prev = -1;
    int cur = index;
    while (cur != -1) {
        int nxt = next[cur];
        next[cur] = prev;
        prev = cur;
        cur = nxt;
    }
    return;
}

// =====================================================================
// @ 0x45bc80  compact bone influences: fold duplicate joint slots into their weight
// =====================================================================
struct Infl {
    int16_t j0;
    int16_t j1;
    int16_t j2;
    int16_t j3;
};

struct Weights {
    float w0;
    float w1;
    float w2;
    float w3;
};

struct Skel {
    char   pad0[0x74];
    Infl*  infl[2];       // +0x74 begin, +0x78 end (one array, so the loop test
                          // takes this+0x74 as its base and leaves it in eax)
    char   pad1[0x0c];
    Weights* weights;     // +0x88
    void   Compact();
};

void Skel::Compact()
{
    Infl* in = infl[0];
    Weights* wt = weights;
    // The bound is re-derived from this+0x74/+0x78 on every iteration, so the
    // loop test leaves &infl[0] (this+0x74) in eax exactly as retail does.
    Infl** inflp = &infl[0];
    for (unsigned int i = 0; i < (unsigned int)(inflp[1] - inflp[0]); i = i + 1) {
        Infl* r = &in[i];
        Weights* w = &wt[i];
        if (r->j3 == r->j0) {
            w->w0 = w->w0 + w->w3;
            r->j3 = (int16_t)-1;
            w->w3 = 0;
        } else if (r->j3 == r->j1) {
            w->w1 = w->w1 + w->w3;
            r->j3 = (int16_t)-1;
            w->w3 = 0;
        } else if (r->j3 == r->j2) {
            w->w2 = w->w2 + w->w3;
            r->j3 = (int16_t)-1;
            w->w3 = 0;
        }

        if (r->j2 == r->j0) {
            w->w0 = w->w0 + w->w2;
            r->j2 = r->j3;
            w->w2 = w->w3;
            r->j3 = (int16_t)-1;
            w->w3 = 0;
        } else if (r->j2 == r->j1) {
            w->w1 = w->w1 + w->w2;
            r->j2 = r->j3;
            w->w2 = w->w3;
            r->j3 = (int16_t)-1;
            w->w3 = 0;
        }

        if (r->j1 == r->j0) {
            w->w0 = w->w0 + w->w1;
            r->j1 = r->j2;
            w->w1 = w->w2;
            r->j2 = r->j3;
            w->w2 = w->w3;
            r->j3 = (int16_t)-1;
            w->w3 = 0;
        }
    }
    return;
}

// =====================================================================
// @ 0x45c0f0  rebuild skinning arrays into local copies + remap indices
// =====================================================================
struct Mat4 { float m[16]; };              // 0x40-byte matrix element

struct sp_vector_allocator {
    const char* mpName;
    int         mFlags;
};

// EASTL vector with sp_vector_allocator (0x14 bytes).
template <class T>
struct vec {
    T*                   mpBegin;      // +0x00
    T*                   mpEnd;        // +0x04
    T*                   mpCapacity;   // +0x08
    sp_vector_allocator  mAllocator;   // +0x0c
    void Assign(const vec& src);       // 0x0045d790
};

// Collada export target (same layout as ColladaExport in s004629e0).
struct ColladaExport {
    char       pad00[0xec];      // +0x000
    vec<int>   mBoneParents;     // +0x0ec  source element per output bone (-1 = keep)
    vec<Mat4>  mBindMatrices;    // +0x100  local bind matrices
    vec<Mat4>  mWorkMatrices;    // +0x114  working copy of the bind matrices
    vec<Mat4>  mBoneMatrices;    // +0x128  bone matrices (also the normal-matrix source)
    vec<Mat4>  mWorkNormals;     // +0x13c  working copy of the bone matrices

    void Finalize0();
};

// @ 0x45c0f0
void ColladaExport::Finalize0()
{
    Mat4 tmpC, tmpB, tmpA;

    mWorkMatrices.Assign(mBindMatrices);
    mWorkNormals.Assign(mBoneMatrices);

    unsigned int i = 0;
    unsigned int n = (unsigned int)(mWorkMatrices.mpEnd - mWorkMatrices.mpBegin);
    for (; i < n; i = i + 1) {
        Mat4& da = mWorkMatrices.mpBegin[i];
        Mat4* ra = (Mat4*)FUN_0045da80(&tmpA, &mWorkMatrices.mpBegin[i]);
        da = *ra;

        Mat4& db = mWorkNormals.mpBegin[i];
        Mat4* rb = (Mat4*)FUN_0045da80(&tmpB, &mWorkNormals.mpBegin[i]);
        db = *rb;
    }

    unsigned int j = 0;
    unsigned int m = (unsigned int)(mBoneMatrices.mpEnd - mBoneMatrices.mpBegin);
    for (; j < m; j = j + 1) {
        if (mBoneParents.mpBegin[j] >= 0) {
            Mat4& dc = mBoneMatrices.mpBegin[j];
            Mat4* rc = (Mat4*)_Unchecked_idl0(&tmpC, &mBoneMatrices.mpBegin[j],
                                              &mWorkNormals.mpBegin[mBoneParents.mpBegin[j]]);
            dc = *rc;
        }
    }
    return;
}
