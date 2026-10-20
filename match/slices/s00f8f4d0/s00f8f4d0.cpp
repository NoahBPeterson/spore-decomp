// Slice s00f8f4d0 -- eastl vector helpers + Simulator vector-container ctors/dtors.
// Reconstructed from the retail object. Local stub declarations instead of shared
// headers (see slice notes).

#include <string.h>

typedef unsigned char  u8;
typedef unsigned short u16;
typedef unsigned int   u32;

extern "C" void* operator_new(int size, int align, int a3, const char* a4,
                              int a5, int a6, const char* file, int line); // 0xf473d0
extern "C" void  operator_delete__(void* p);                                  // 0xf47380
extern "C" void  operator_new__(void* dst, const void* src, int len);         // 0x11e073e
extern "C" void* eastl_fill(void* dst, const void* src, int nbytes);          // 0x11e0744
extern "C" void* eastl_find(void* a, int b, int c);                           // 0x7ec550
extern "C" void  CopyVec12(void* dst, unsigned int n, const void* src);       // 0x6a4100
extern "C" void  DoCopyBackward(void* first, void* last, void* result);       // 0xabced0
extern "C" void  DoFill(void* first, void* last, const void* value);          // 0xa177f0
extern "C" void  FUN_004797a0(const void* value, void* a, void* b, void* c,
                              void* pos);                                     // 0x4797a0
extern "C" void  FUN_00f8f130();                                              // 0xf8f130
extern "C" void  FUN_00f8f330();                                              // 0xf8f330

// eastl::vector<float> reallocation helper (thiscall, 3 stack args).
struct VecGrower {
    void* Grow(int n, const void* srcBegin, const void* srcEnd);   // 0x00f8eef0
};

#define ALLOC_FILE \
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

// ---------------------------------------------------------------------------
// eastl::vector<float>
// ---------------------------------------------------------------------------
struct VecF {
    float* mpBegin;   // +0x00
    float* mpEnd;     // +0x04
    float* mpCap;     // +0x08

    void Insert(float* pos, unsigned int n, const float* pvalue);
};

// @ 0x00f8f4d0
void VecF::Insert(float* pos, unsigned int n, const float* pvalue)
{
    if (n > (unsigned int)((mpCap - mpEnd) >> 2)) {
        int size = (int)((mpEnd - mpBegin) >> 2);
        unsigned int newCap = (unsigned int)(size * 2);
        if (size == 0)
            newCap = 1;
        unsigned int need = (unsigned int)size + n;
        if (newCap <= need)
            newCap = need;
        float* pNew;
        if (newCap == 0)
            pNew = 0;
        else
            pNew = (float*)operator_new((int)(newCap * 4), 0x80, 0, "Simulator", 0, 0,
                                        ALLOC_FILE, 0xe5);
        unsigned int off = (unsigned int)((char*)pos - (char*)mpBegin);
        char* base = (char*)eastl_fill(pNew, mpBegin, (int)off);
        float* dst = (float*)(base + off);
        float v = *pvalue;
        for (unsigned int i = 0; i < n; ++i)
            dst[i] = v;
        unsigned int tail = (unsigned int)((char*)mpEnd - (char*)pos);
        char* newEnd = (char*)eastl_fill(dst + n, pos, (int)tail);
        if (mpBegin != 0)
            operator_delete__(mpBegin);
        mpBegin = pNew;
        mpEnd = (float*)(newEnd + ((tail >> 2) << 2));
        mpCap = (float*)((char*)pNew + (int)(newCap * 4));
    } else if (n != 0) {
        float v = *pvalue;
        unsigned int tailCount = (unsigned int)((mpEnd - pos) >> 2);
        if (n < tailCount) {
            float* src = mpEnd - n;
            eastl_fill(mpEnd, src, (int)(n * 4));
            mpEnd = (float*)((char*)mpEnd + n * 4);
            memmove(pos + n, pos, (int)((char*)src - (char*)pos));
            for (float* q = pos; q != pos + n; ++q)
                *q = v;
        } else {
            float* oldEnd = mpEnd;
            unsigned int fill = n - tailCount;
            for (unsigned int i = 0; i < fill; ++i)
                mpEnd[i] = v;
            mpEnd = (float*)((char*)mpEnd + fill * 4);
            eastl_fill(mpEnd, pos, (int)((char*)oldEnd - (char*)pos));
            mpEnd = (float*)((char*)mpEnd + tailCount * 4);
            for (float* q = pos; q != oldEnd; ++q)
                *q = v;
        }
    }
}

// ---------------------------------------------------------------------------
// eastl::vector<AnalysisInfo> (12-byte element)
// ---------------------------------------------------------------------------
struct VecAI {
    char* mpBegin;   // +0x00
    char* mpEnd;     // +0x04
    char* mpCap;     // +0x08

    void Insert(char* pos, unsigned int n, const char* pvalue);
};

// @ 0x00f8f6d0
void VecAI::Insert(char* pos, unsigned int n, const char* pvalue)
{
    if (n > (unsigned int)((mpCap - mpEnd) / 0xc)) {
        int size = (int)((mpEnd - mpBegin) / 0xc);
        unsigned int newCap = (unsigned int)(size * 2);
        if (size == 0)
            newCap = 1;
        unsigned int need = (unsigned int)size + n;
        if (newCap <= need)
            newCap = need;
        char* pNew;
        if (newCap == 0)
            pNew = 0;
        else
            pNew = (char*)operator_new((int)(newCap * 0xc), 0x80, 0, "Simulator", 0, 0,
                                       ALLOC_FILE, 0xe5);
        unsigned int off = (unsigned int)(pos - mpBegin);
        char* base = (char*)eastl_fill(pNew, mpBegin, (int)off);
        char* dst = base + off;
        char tmp[0xc];
        *(int*)(tmp + 0) = *(int*)(pvalue + 0);
        *(int*)(tmp + 4) = *(int*)(pvalue + 4);
        *(int*)(tmp + 8) = *(int*)(pvalue + 8);
        for (unsigned int i = 0; i < n; ++i) {
            *(int*)(dst + 0) = *(int*)(tmp + 0);
            *(int*)(dst + 4) = *(int*)(tmp + 4);
            *(int*)(dst + 8) = *(int*)(tmp + 8);
            dst += 0xc;
        }
        unsigned int tail = (unsigned int)(mpEnd - pos);
        char* newEnd = (char*)eastl_fill(dst, pos, (int)tail);
        if (mpBegin != 0)
            operator_delete__(mpBegin);
        mpBegin = pNew;
        mpEnd = newEnd + ((tail / 0xc) * 0xc);
        mpCap = pNew + (int)(newCap * 0xc);
    } else if (n != 0) {
        char tmp[0xc];
        *(int*)(tmp + 0) = *(int*)(pvalue + 0);
        *(int*)(tmp + 4) = *(int*)(pvalue + 4);
        *(int*)(tmp + 8) = *(int*)(pvalue + 8);
        unsigned int tailCount = (unsigned int)((mpEnd - pos) / 0xc);
        if (n < tailCount) {
            char* src = mpEnd - (int)(n * 0xc);
            eastl_fill(mpEnd, src, (int)(n * 0xc));
            mpEnd = mpEnd + n * 0xc;
            memmove(pos + n * 0xc, pos, (int)(src - pos));
            for (char* q = pos; q != pos + n * 0xc; q += 0xc)
                DoFill(q, q + 0xc, tmp);
        } else {
            char* oldEnd = mpEnd;
            unsigned int fill = n - tailCount;
            char* q = mpEnd;
            for (unsigned int i = 0; i < fill; ++i) {
                DoFill(q, q + 0xc, tmp);
                q += 0xc;
            }
            mpEnd = mpEnd + fill * 0xc;
            eastl_fill(mpEnd, pos, (int)(oldEnd - pos));
            mpEnd = mpEnd + tailCount * 0xc;
            for (q = pos; q != oldEnd; q += 0xc)
                DoFill(q, q + 0xc, tmp);
        }
    }
}

// ---------------------------------------------------------------------------
// vector<float>::operator=
// ---------------------------------------------------------------------------
struct VecFAssign {
    float* mpBegin;   // +0x00
    float* mpEnd;     // +0x04
    float* mpCap;     // +0x08

    VecFAssign* Assign(VecFAssign* other);
};

// @ 0x00f8f8a0
VecFAssign* VecFAssign::Assign(VecFAssign* other)
{
    if (other == this)
        return this;
    float* srcBeg = other->mpBegin;
    float* dstBeg = mpBegin;
    float* srcEnd = other->mpEnd;
    unsigned int n = (unsigned int)((srcEnd - srcBeg) >> 2);
    if ((unsigned int)((mpCap - dstBeg) >> 2) < n) {
        float* p = (float*)((VecGrower*)this)->Grow((int)n, srcBeg, srcEnd);
        if (mpBegin != 0)
            operator_delete__(mpBegin);
        mpBegin = p;
        mpCap = p + n;
        mpEnd = p + n;
        return this;
    }
    unsigned int used = (unsigned int)((mpEnd - dstBeg) >> 2);
    if (used < n) {
        eastl_fill(dstBeg, srcBeg, (int)(used * 4));
        char* extra = (char*)other->mpBegin + ((char*)mpEnd - (char*)mpBegin);
        eastl_fill(mpEnd, extra, (int)((char*)other->mpEnd - extra));
        mpEnd = mpBegin + n;
        return this;
    }
    eastl_fill(dstBeg, srcBeg, (int)((char*)srcEnd - (char*)srcBeg));
    mpEnd = mpBegin + n;
    return this;
}

// ---------------------------------------------------------------------------
// Simulator float-list dtors
// ---------------------------------------------------------------------------
struct GmeListF {
    void* m_vtbl;    // +0x00
    char  m_pad04[0x0c];
    void* mpBegin;   // +0x10
    void* mpEnd;     // +0x14

    void DtorF();
};

// @ 0x00f8f970
void GmeListF::DtorF()
{
    *(int*)this = 0x1490020;
    int endp = (int)mpEnd;
    int begp = (int)mpBegin;
    eastl_fill((void*)begp, (void*)endp, 0);
    int cnt = (endp - begp) >> 2;
    *(int*)((char*)this + 0x14) += -cnt * 4;
    if (*(int*)((char*)this + 0x10) != 0)
        operator_delete__(*(void**)((char*)this + 0x10));
    *(int*)this = 0x13ef094;
}

// ---------------------------------------------------------------------------
// Simulator 16-bit-list dtors
// ---------------------------------------------------------------------------
struct GmeListS {
    void* m_vtbl;    // +0x00
    char  m_pad04[0x0c];
    void* mpBegin;   // +0x10
    void* mpEnd;     // +0x14

    void DtorH();
};

// @ 0x00f8f9c0
void GmeListS::DtorH()
{
    *(int*)this = 0x1490028;
    int endp = (int)mpEnd;
    int begp = (int)mpBegin;
    eastl_fill((void*)begp, (void*)endp, 0);
    int cnt = (endp - begp) >> 1;
    *(int*)((char*)this + 0x14) += -cnt * 2;
    if (*(int*)((char*)this + 0x10) != 0)
        operator_delete__(*(void**)((char*)this + 0x10));
    *(int*)this = 0x13ef094;
}

// ---------------------------------------------------------------------------
// Simulator dense-array container
// ---------------------------------------------------------------------------
struct SimVec12 {
    void* m_vtbl;    // +0x00
    int   m_pad04;   // +0x04
    int   mCount;    // +0x08
    char  m_pad0c[0x04];
    void* mpBegin;   // +0x10
    void* mpEnd;     // +0x14
    void* mpCap;     // +0x18

    SimVec12* Ctor(int n, const void* init);
    void DtorB();
    void* DtorD(int freeFlag);
};

// @ 0x00f8fa10
SimVec12* SimVec12::Ctor(int n, const void* init)
{
    mCount = n;
    int size = n * n * 6;
    m_pad04 = 0;
    *(int*)this = 0x1490030;
    char* p;
    if (size == 0)
        p = 0;
    else
        p = (char*)operator_new(size, 0x80, 0, "Simulator", 0, 0, ALLOC_FILE, 0xe5);
    mpBegin = p;
    mpEnd   = p;
    mpCap   = p + size;
    if (size != 0)
        operator_new__(p, init, size);
    mpEnd = (char*)mpBegin + size;
    return this;
}

// @ 0x00f8fa90
void SimVec12::DtorB()
{
    *(int*)this = 0x1490030;
    int endp = (int)mpEnd;
    int begp = (int)mpBegin;
    eastl_fill((void*)begp, (void*)endp, 0);
    *(int*)((char*)this + 0x14) += begp - endp;
    if (*(int*)((char*)this + 0x10) != 0)
        operator_delete__(*(void**)((char*)this + 0x10));
    *(int*)this = 0x13ef094;
}

// @ 0x00f8fbd0
void* SimVec12::DtorD(int freeFlag)
{
    *(int*)this = 0x1490030;
    int endp = (int)mpEnd;
    int begp = (int)mpBegin;
    eastl_fill((void*)begp, (void*)endp, 0);
    *(int*)((char*)this + 0x14) += begp - endp;
    if (*(int*)((char*)this + 0x10) != 0)
        operator_delete__(*(void**)((char*)this + 0x10));
    *(int*)this = 0x13ef094;
    if (freeFlag & 1)
        operator_delete__(this);
    return this;
}

// ---------------------------------------------------------------------------
// Simulator float-list dtor variants
// ---------------------------------------------------------------------------
struct GmeListFB {
    void* m_vtbl;    // +0x00
    char  m_pad04[0x0c];
    void* mpBegin;   // +0x10
    void* mpEnd;     // +0x14

    void* DtorI(int freeFlag);
};

// @ 0x00f8fb10
void* GmeListFB::DtorI(int freeFlag)
{
    *(int*)this = 0x1490020;
    int endp = (int)mpEnd;
    int begp = (int)mpBegin;
    eastl_fill((void*)begp, (void*)endp, 0);
    int cnt = (endp - begp) >> 2;
    *(int*)((char*)this + 0x14) += -cnt * 4;
    if (*(int*)((char*)this + 0x10) != 0)
        operator_delete__(*(void**)((char*)this + 0x10));
    *(int*)this = 0x13ef094;
    if (freeFlag & 1)
        operator_delete__(this);
    return this;
}

// ---------------------------------------------------------------------------
// Simulator 16-bit-list dtor variants
// ---------------------------------------------------------------------------
struct GmeListSB {
    void* m_vtbl;    // +0x00
    char  m_pad04[0x0c];
    void* mpBegin;   // +0x10
    void* mpEnd;     // +0x14

    void* DtorC(int freeFlag);
};

// @ 0x00f8fb70
void* GmeListSB::DtorC(int freeFlag)
{
    *(int*)this = 0x1490028;
    int endp = (int)mpEnd;
    int begp = (int)mpBegin;
    eastl_fill((void*)begp, (void*)endp, 0);
    int cnt = (endp - begp) >> 1;
    *(int*)((char*)this + 0x14) += -cnt * 2;
    if (*(int*)((char*)this + 0x10) != 0)
        operator_delete__(*(void**)((char*)this + 0x10));
    *(int*)this = 0x13ef094;
    if (freeFlag & 1)
        operator_delete__(this);
    return this;
}

// ---------------------------------------------------------------------------
// Simulator Vector3-list (eastl sp_vector)
// ---------------------------------------------------------------------------
struct Vec0C {
    char* mpBegin;   // +0x00
    char* mpEnd;     // +0x04

    char* erase(char* a, char* b);
};

struct GmeListV3 {
    void* m_vtbl;    // +0x00
    char  m_pad04[0x0c];
    Vec0C mVec;      // +0x10

    void DtorE();
    void* DtorJ(int freeFlag);
};

// @ 0x00f8fad0
void GmeListV3::DtorE()
{
    *(int*)this = 0x1490038;
    mVec.erase(mVec.mpBegin, mVec.mpEnd);
    if (mVec.mpBegin != 0)
        operator_delete__(mVec.mpBegin);
    *(int*)this = 0x13ef094;
}

// @ 0x00f8fc30
void* GmeListV3::DtorJ(int freeFlag)
{
    *(int*)this = 0x1490038;
    mVec.erase(mVec.mpBegin, mVec.mpEnd);
    if (mVec.mpBegin != 0)
        operator_delete__(mVec.mpBegin);
    *(int*)this = 0x13ef094;
    if (freeFlag & 1)
        operator_delete__(this);
    return this;
}

// ---------------------------------------------------------------------------
// eastl vector append helpers (__thiscall on the vector, {begin, end} layout)
// ---------------------------------------------------------------------------
struct EastlVec {
    char* mpBegin;   // +0x00
    char* mpEnd;     // +0x04

    void Resize16(unsigned int n);
    void Resize08(unsigned int n);
    void Resize4F(unsigned int n);
};

// @ 0x00f8fce0
void EastlVec::Resize16(unsigned int n)
{
    char* endp = mpEnd;
    char* begp = mpBegin;
    unsigned int used = (unsigned int)((endp - begp) >> 1);
    if (used < n) {
        unsigned int add = n - used;
        short zero = 0;
        ((void (__thiscall*)(EastlVec*, char*, unsigned int, short*))(void*)FUN_00f8f130)
            (this, endp, add, &zero);
        return;
    }
    char* dst = begp + n * 2;
    eastl_fill(dst, endp, 0);
    int cnt = (int)((endp - dst) >> 1);
    *(int*)((char*)this + 0x04) += -cnt * 2;
}

// @ 0x00f8fd40
void EastlVec::Resize08(unsigned int n)
{
    char* endp = mpEnd;
    char* begp = mpBegin;
    if ((unsigned int)(endp - begp) < n) {
        unsigned int add = n - (unsigned int)(endp - begp);
        char zero = 0;
        ((void (__thiscall*)(EastlVec*, char*, unsigned int, char*))(void*)FUN_00f8f330)
            (this, endp, add, &zero);
        return;
    }
    char* dst = begp + n;
    eastl_fill(dst, endp, 0);
    *(int*)((char*)this + 0x04) += dst - endp;
}

// @ 0x00f8fd90
void EastlVec::Resize4F(unsigned int n)
{
    char* endp = mpEnd;
    char* begp = mpBegin;
    unsigned int used = (unsigned int)((endp - begp) >> 2);
    if (used < n) {
        unsigned int add = n - used;
        float zero = 0.0f;
        ((void (__thiscall*)(EastlVec*, char*, unsigned int, float*))(void*)FUN_00f8f130)
            (this, endp, add, &zero);
        return;
    }
    char* dst = begp + n * 4;
    eastl_fill(dst, endp, 0);
    int cnt = (int)((endp - dst) >> 2);
    *(int*)((char*)this + 0x04) += -cnt * 4;
}
