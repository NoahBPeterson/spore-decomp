// Slice s00735350 — sorted-vector (eastl::set-like) operations over 0xc/0x24/0x20-byte keys plus
// a refcounted element fill.  Small operations are reconstructed; the two large ones are
// skeletons.
#include "types.h"
#include <string.h>

struct EltArray
{
    int32_t  mNumElts;    // +0x00
    void*    mData;       // +0x04
    uint16_t mEltSize;    // +0x08
    uint16_t mEltStride;  // +0x0a
    void*    mRC;         // +0x0c
};

// Element source/destination descriptor used by FUN_00735960.  On entry +0x04/+0x08/+0x0a
// describe the lookup table and +0x0c/+0x10 bound the output dword array; on exit the record
// has been refilled with the built EltArray.
struct EltSrc
{
    int32_t   mNumElts;   // +0x00
    void*     mSrcBase;   // +0x04 (element lookup table base)
    uint16_t  mMaskIdx;   // +0x08 (index into g_masks)
    uint16_t  mStride;    // +0x0a (byte stride per index unit)
    uint32_t* mOut;       // +0x0c (output dword array)
    uint32_t* mOutEnd;    // +0x10
};
extern uint32_t g_masks[]; // 0x140d4e0

struct RefCounted
{
    virtual int AddRef();   // vtable[0] @ 0x461290
    virtual int Release();  // vtable[1]
};

// 0x24-byte index vector; data lives at +0x0c/+0x10.
struct IntVecObj
{
    uint8_t   pad00[0x0c];
    uint32_t* mData;             // +0x0c
    uint32_t* mDataEnd;          // +0x10

    IntVecObj* ctor(int count);  // 0x723680 (thiscall: ecx = this)
};

// Builds a 0x10-byte EltArray descriptor over src+0x0c..src+0x10 and AddRefs src.
struct ContV
{
    EltArray* Make4(EltArray* out); // 0x732ff0 (thiscall: ecx = this)
};

int   FUN_007330d0(int, int, int*, int);
int   FUN_0072ac10(int*);
void  FUN_007348a0(int*);
void* FUN_00723680(int);
int   FUN_0071e7d0(int, int, int); // 0x71e7d0 cdecl copy helper
void  FUN_0047b290(void**, int, int, int, void*);
void  FUN_0072a1a0(uint32_t, int*);
void* EAAlloc(int, const char*, int, int, const char*, int);
void* EAAllocate(unsigned size, const char* area, int a, int b, void* alloc, int d); // 0x00F473A0
void  EAFree(void*); // 0x00F47380
void* __cdecl FUN_011e0744(void* dst, void* src, unsigned n); // 0x011E0744 import thunk -> memcpy
unsigned char g_eastlAllocator;                              // 0x13ebb38

// 0x8c-byte record in the container at param_1+0x1c.
struct Rec
{
    int32_t  mNumElts;    // +0x00
    void*    mSrcBase;    // +0x04
    uint16_t mEltSize;    // +0x08 (2 or 4; also the index into g_masks)
    uint16_t mStride;     // +0x0a
    void*    mRC;         // +0x0c (refcounted element owner)
    int32_t  mCount;      // +0x10
    uint8_t  pad14[0x44 - 0x14];
    EltSrc*  mChildBegin; // +0x44
    EltSrc*  mChildEnd;   // +0x48
};

// 0x14-byte description span in the vector at container+0x30.
struct Span14
{
    int32_t mTag;      // +0x00 (0 = emptied; 4..7 select an expansion kind)
    int32_t mRecIndex; // +0x04
    int32_t mBegin;    // +0x08
    int32_t mEnd;      // +0x0c
    int32_t mPad;      // +0x10
};

struct SpanVec
{
    Span14* mBegin; // +0x00
    Span14* mEnd;   // +0x04
    Span14* mCap;   // +0x08

    void resize(uint32_t n); // 0x71efa0 (thiscall, ret 4)
};

// The container walked by FUN_00735470: a record array at +0x1c and the span vector at +0x30.
struct BuildCtx
{
    uint8_t pad00[0x1c];
    Rec*    mRecBegin; // +0x1c
    Rec*    mRecEnd;   // +0x20
    uint8_t pad24[0x30 - 0x24];
    SpanVec mSpans;    // +0x30
};

// int vector used for the group order; push_back is the inlined grow check + 0x4558a0.
struct GroupVec
{
    int* mBegin;   // +0x00
    int* mEnd;     // +0x04
    int* mCap;     // +0x08

    void DoInsertValue(int* pos, const int* value); // 0x4558a0 (thiscall, ret 8)
    void push_back(int value)
    {
        if (mEnd < mCap)
        {
            *mEnd = value;
            ++mEnd;
            return;
        }
        DoInsertValue(mEnd, &value);
    }
};

int  __cdecl FUN_00921240(int* child);                        // 0x921240 sort key for a child descriptor
void __cdecl FUN_007345f0(int* first, int* last, int key);   // 0x7345f0 stable sort of [first,last) by key
bool __cdecl FUN_007321a0(const void* rec, int a, int b);    // 0x7321a0 same-group test over all children
void __cdecl FUN_00921df0(const int* pTime);                 // 0x921df0 EA::Thread::ThreadSleep

struct Vec
{
    int*   mBegin;   // +0x00
    int*   mEnd;     // +0x04
    int*   mCap;     // +0x08
    void*  mEmptyRef; // +0x0c (shared-empty sentinel; copied by the copy ctor)
    int    pad1;     // +0x10
    int8_t mFlag;    // +0x14

    void   copyCtor(Vec* src);          // 0x72ac10 (thiscall; builds *this from *src)
    void   assign(Vec* src);            // 0x7348a0 (thiscall; *this = *src)
    void   FUN_007353c0(Vec* other);    // 0x7353c0 (thiscall; swap-or-assign)
    int*   insertL(int* a, int* b);     // 0x735350
    int*   FUN_00734660(int* a, int* b); // 0x734660 (thiscall helper, ecx = this)
    void   FUN_00b85500(int* dst, int* src); // 0xb85500 Vertex3DVec::CopyUninit (thiscall)
    void   FUN_007346d0(int* dst, int count, int value); // 0x7346d0 fill/construct (thiscall)
    int*   FUN_007334b0(uint32_t n, int src, int srcEnd); // 0x7334b0 realloc (thiscall)
    void   FUN_00714b10(int from, int to); // 0x714b10 destroy range (thiscall)
    int*   operator=(int* other);       // 0x735dd0
    int*   findLower(int* key);         // 0x735ec0
    void   resize24(uint32_t n, int v); // 0x735f30
    void   fill(uint32_t n, int* v);   // 0x736090
    void   DoAllocate(uint32_t n, int* flags); // 0x72a1a0 (thiscall; build n-element buffer)
};

// @ 0x00735350
int* Vec::insertL(int* param_2, int* param_3)
{
    int* piVar2 = mEnd;
    int uVar1;
    int* piVar3;
    if (param_2 != piVar2)
    {
        if ((*param_3 < *param_2) || ((*param_3 <= *param_2 && (param_3[1] < param_2[1]))))
        {
            uVar1 = (uint8_t)mFlag;
            piVar3 = mBegin;
            goto call;
        }
    }
    uVar1 = (uint8_t)mFlag;
    piVar3 = param_2;
    param_2 = piVar2;
call:
    piVar3 = (int*)FUN_007330d0((int)piVar3, (int)param_2, param_3, uVar1);
    if (piVar3 != piVar2)
    {
        if (*piVar3 <= *param_3)
        {
            if (*piVar3 < *param_3)
                return piVar3;
            if (piVar3[1] <= param_3[1])
                return piVar3;
        }
    }
    return FUN_00734660(piVar3, param_3);
}

// @ 0x00735ec0
int* Vec::findLower(int* param_2)
{
    int* piVar1 = mEnd;
    int* piVar2 = (int*)FUN_007330d0((int)mBegin, (int)piVar1, param_2, (uint8_t)mFlag);
    if (piVar2 != piVar1)
    {
        if ((*piVar2 <= *param_2) && ((*piVar2 < *param_2) || (piVar2[1] <= param_2[1])))
            goto ret;
    }
    {
        int key[3];
        key[0] = param_2[0];
        key[1] = param_2[1];
        key[2] = 0;
        piVar2 = insertL(piVar2, key);
    }
ret:
    return piVar2 + 2;
}

// @ 0x00735f30
void Vec::resize24(uint32_t param_2, int param_3)
{
    uint8_t* begin = (uint8_t*)mBegin;
    uint8_t* end = (uint8_t*)mEnd;
    int count = (int)(end - begin) / 0x24;
    if (param_2 > (uint32_t)count)
    {
        FUN_007346d0((int*)end, (int)(param_2 - (uint32_t)count), param_3);
        return;
    }
    FUN_00b85500((int*)(begin + param_2 * 0x24), (int*)end);
}

// @ 0x00735dd0
int* Vec::operator=(int* param_2)
{
    if (param_2 != (int*)this)
    {
        int iVar1 = *param_2;
        int iVar4 = (int)mBegin;
        int iVar2 = param_2[1];
        uint32_t uVar7 = (uint32_t)(iVar2 - iVar1) >> 5;
        if ((uint32_t)((int)mCap - iVar4) >> 5 < uVar7)
        {
            iVar4 = (int)FUN_007334b0(uVar7, iVar1, iVar2);
            FUN_00714b10((int)mBegin, (int)mEnd);
            if (mBegin != 0 && *(int*)((int)mBegin - 4) != 0)
                EAFree(mBegin);
            mEnd = (int*)(uVar7 * 0x20 + iVar4);
            mCap = (int*)(uVar7 * 0x20 + iVar4);
            mBegin = (int*)iVar4;
            return (int*)this;
        }
        uint32_t uVar5 = (uint32_t)((int)mEnd - iVar4) >> 5;
        if (uVar5 < uVar7)
        {
            FUN_0071e7d0(iVar1, uVar5 * 0x20 + iVar1, iVar4);
            FUN_0047b290((void**)&param_2, ((int)((int)mEnd - (int)mBegin) >> 5) * 0x20 + *param_2,
                         param_2[1], (int)mEnd, param_2);
            mEnd = (int*)(uVar7 * 0x20 + (int)mBegin);
            return (int*)this;
        }
        int uVar6 = FUN_0071e7d0(iVar1, iVar2, iVar4);
        FUN_00714b10(uVar6, (int)mEnd);
        mEnd = (int*)(uVar7 * 0x20 + (int)mBegin);
    }
    return (int*)this;
}

// @ 0x00735fa0
void FUN_00735fa0(int param_1, int param_2, int* param_3)
{
    if (param_2 != 0)
    {
        int* piVar2 = (int*)(param_1 + 0x14);
        do
        {
            if (piVar2 != (int*)0x14)
            {
                piVar2[-5] = param_3[0];
                piVar2[-4] = param_3[1];
                piVar2[-3] = param_3[2];
                piVar2[-2] = param_3[3];
                int iVar3 = (param_3[5] - param_3[4]) >> 2;
                void* pvVar1 = 0;
                if (iVar3 != 0)
                    pvVar1 = EAAlloc(iVar3 * 4, "Graphics", 0, 0,
                                     "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
                piVar2[-1] = (int)pvVar1;
                *piVar2 = (int)pvVar1;
                piVar2[1] = (int)pvVar1 + iVar3 * 4;
                size_t sz = param_3[5] - param_3[4];
                pvVar1 = memcpy(pvVar1, (void*)param_3[4], sz);
                *piVar2 = (int)pvVar1 + ((int)sz >> 2) * 4;
            }
            param_2 = param_2 - 1;
            piVar2 = piVar2 + 9;
        } while (param_2 != 0);
    }
}

// @ 0x007353c0
void Vec::FUN_007353c0(Vec* other)
{
    // SSO fast path: both share the inline sentinel, so swap the three pointers.
    if ((char*)this + 0xc == (char*)other + 0xc) {
        int* t = mBegin;   mBegin = other->mBegin;   other->mBegin = t;
        t = mEnd;          mEnd = other->mEnd;       other->mEnd = t;
        t = mCap;          mCap = other->mCap;       other->mCap = t;
        return;
    }
    Vec tmp;
    tmp.copyCtor(this);
    this->assign(other);
    other->assign(&tmp);
    if (tmp.mBegin != 0 && tmp.mBegin != (int*)tmp.mEmptyRef)
        EAFree(tmp.mBegin);
}

// @ 0x00735470
bool FUN_00735470(void* param_1, bool param_2)
{
    BuildCtx* ctx = (BuildCtx*)param_1;
    int nrec = (int)(((uint8_t*)ctx->mRecEnd - (uint8_t*)ctx->mRecBegin) / 0x8c);
    bool changed = false;
    bool result = false;
    if (nrec <= 0)
        return false;

    int recTotal = nrec;
    uint32_t recOff = 0;
    for (int ri = 0; ri < recTotal; ++ri)
    {
        Rec* r = (Rec*)((uint8_t*)ctx->mRecBegin + recOff);
        int nspan = (int)(((uint8_t*)ctx->mSpans.mEnd - (uint8_t*)ctx->mSpans.mBegin) / 0x14);
        int total = 0;
        bool expand = false;

        // Pass 1: size the flattened index list this record needs.
        for (int k = 0; k < nspan; ++k)
        {
            Span14* sp = ctx->mSpans.mBegin + k;
            if (sp->mRecIndex != ri)
                continue;
            int end   = sp->mEnd;
            int begin = sp->mBegin;
            if (begin >= end)
            {
                changed = true;
                sp->mTag = 0;
                continue;
            }
            int kind = sp->mTag - 4;
            if ((unsigned)kind > 3u)
            {
                expand = true;
                sp->mTag = 0;
                continue;
            }
            switch (kind)
            {
            case 0:
                total += end - begin;
                break;
            case 1:
                total += (end - begin - 2) * 3;
                expand = true;
                break;
            case 2:
                total += (end - begin - 2) * 3;
                expand = true;
                break;
            case 3:
                total += ((end - begin) * 3) / 2;
                expand = true;
                break;
            }
        }

        // Rebuild the record's element descriptor when the spans expanded, or when a new
        // record (no source data yet) is being initialised.
        if (expand || (param_2 && r->mSrcBase == 0))
        {
            IntVecObj* tmp = (IntVecObj*)EAAllocate(0x24, "Graphics", 0, 0, 0, 0);
            IntVecObj* obj = 0;
            if (tmp != 0)
                obj = tmp->ctor(total);
            if (obj != 0)
                ((int(__thiscall*)(void*))(*(void***)obj)[0])(obj); // AddRef

            // Pass 2: expand each span into the object's index array.
            int w = 0;
            for (int k = 0; k < nspan; ++k)
            {
                Span14* sp = ctx->mSpans.mBegin + k;
                if (sp->mRecIndex != ri)
                    continue;
                if (sp->mTag == 0)
                    continue;

                int begin = sp->mBegin;
                int end   = sp->mEnd;
                int off   = w - begin;
                int kind  = sp->mTag - 4;
                if ((unsigned)kind > 3u)
                {
                    changed = true;
                }
                else
                {
                    switch (kind)
                    {
                    case 0: // single values
                        for (int v = begin; v < end; ++v)
                            obj->mData[w++] = (uint32_t)v;
                        break;
                    case 1: // overlapping six-entry groups over a two-step
                    {
                        int i = begin;
                        int lim = end - 2;
                        while (i < lim)
                        {
                            obj->mData[w]     = (uint32_t)i;
                            obj->mData[w + 1] = (uint32_t)(i + 1);
                            w += 2;
                            obj->mData[w]     = (uint32_t)(i + 2);
                            obj->mData[w + 1] = (uint32_t)(i + 1);
                            w += 2;
                            obj->mData[w]     = (uint32_t)(i + 3);
                            ++w;
                            obj->mData[w]     = (uint32_t)(i + 2);
                            i += 2;
                            ++w;
                        }
                        break;
                    }
                    case 2: // triples with a zero head
                    {
                        int lim = end - 2;
                        for (int i = begin; i < lim; ++i)
                        {
                            obj->mData[w++] = 0;
                            obj->mData[w++] = (uint32_t)(i + 1);
                            obj->mData[w++] = (uint32_t)(i + 2);
                        }
                        break;
                    }
                    case 3: // four-step six-entry groups
                    {
                        int i = begin;
                        while (i < end)
                        {
                            obj->mData[w]     = (uint32_t)i;
                            obj->mData[w + 1] = (uint32_t)(i + 1);
                            obj->mData[w + 2] = (uint32_t)(i + 2);
                            obj->mData[w + 3] = (uint32_t)i;
                            obj->mData[w + 4] = (uint32_t)(i + 2);
                            obj->mData[w + 5] = (uint32_t)(i + 3);
                            i += 4;
                            w += 6;
                        }
                        break;
                    }
                    }
                }
                // Re-express the span in flattened-list coordinates.
                sp->mEnd += off;
                sp->mBegin += off;
                sp->mTag = 4;
            }

            // Remap the record's own element array through the built index list.
            if (r->mSrcBase != 0 && total > 0)
            {
                for (int i = 0; i < total; ++i)
                {
                    uint32_t idx = obj->mData[i];
                    obj->mData[i] = *(uint32_t*)((char*)r->mSrcBase + (uint32_t)r->mStride * idx)
                                    & g_masks[r->mEltSize];
                }
            }

            EltArray local;
            ((ContV*)obj)->Make4(&local);

            r->mNumElts = local.mNumElts;
            r->mSrcBase = local.mData;
            r->mEltSize = local.mEltSize;
            r->mStride  = local.mEltStride;

            void* nw  = local.mRC;
            void* old = r->mRC;
            if (nw != old)
            {
                if (nw != 0)
                    ((int(__thiscall*)(void*))(*(void***)nw)[0])(nw);   // AddRef
                r->mRC = nw;
                if (old != 0)
                    ((int(__thiscall*)(void*))(*(void***)old)[1])(old); // Release
            }

            if (local.mRC != 0)
                ((int(__thiscall*)(void*))(*(void***)local.mRC)[1])(local.mRC);
            result = true;
            if (obj != 0)
                ((int(__thiscall*)(void*))(*(void***)obj)[1])(obj);
        }

        recOff += 0x8c;
    }

    // Drop the spans that the passes marked empty.
    if (changed)
    {
        int nspan = (int)(((uint8_t*)ctx->mSpans.mEnd - (uint8_t*)ctx->mSpans.mBegin) / 0x14);
        int w = 0;
        if (nspan > 0)
        {
            for (int k = 0; k < nspan; ++k)
            {
                Span14* sp = ctx->mSpans.mBegin + k;
                if (sp->mTag != 0)
                {
                    ctx->mSpans.mBegin[w] = *sp;
                    ++w;
                }
            }
        }
        ctx->mSpans.resize((uint32_t)w);
    }

    return result;
}

// @ 0x00735960
void FUN_00735960(int* param_1, EltSrc* param_2)
{
    IntVecObj* tmp = (IntVecObj*)EAAllocate(0x24, "Graphics", 0, 0, 0, 0);
    int count = (int)((param_1[1] - param_1[0]) >> 2);
    IntVecObj* cur;
    if (tmp != 0)
        cur = tmp->ctor(count);
    else
        cur = 0;

    int n = (int)((param_1[1] - param_1[0]) >> 2);
    if (n > 0) {
        uint32_t* srcIdx = (uint32_t*)param_1[0];
        for (int i = 0; i < n; ++i) {
            uint32_t off = param_2->mStride * (uint32_t)(srcIdx[i]);
            uint32_t v = *(uint32_t*)((char*)param_2->mSrcBase + off);
            uint32_t* out = *(uint32_t**)((char*)param_2 + 0xc);
            out[i] = v & g_masks[param_2->mMaskIdx];
            cur = (IntVecObj*)param_2;
        }
    }

    EltArray local;
    ((ContV*)cur)->Make4(&local);

    param_2->mNumElts = local.mNumElts;
    param_2->mSrcBase = local.mData;
    param_2->mMaskIdx = local.mEltSize;
    param_2->mStride  = local.mEltStride;

    RefCounted* nw  = (RefCounted*)local.mRC;
    RefCounted* old = *(RefCounted**)((char*)param_2 + 0xc);
    if (nw != old) {
        if (nw != 0)
            ((int(__thiscall*)(void*))(*(void***)nw)[0])(nw);   // AddRef
        *(RefCounted**)((char*)param_2 + 0xc) = nw;
        if (old != 0)
            ((int(__thiscall*)(void*))(*(void***)old)[1])(old); // Release
    }

    if (tmp != 0)
        ((int(__thiscall*)(void*))(*(void***)tmp)[1])(tmp);     // Release
}

// @ 0x00735a90
void FUN_00735a90(void* param_1)
{
    uint8_t* recBegin = *(uint8_t**)((char*)param_1 + 0x1c);
    uint8_t* recEnd   = *(uint8_t**)((char*)param_1 + 0x20);
    int nrec = (int)((recEnd - recBegin) / 0x8c);
    if (nrec <= 0)
        return;

    int remaining = nrec;
    uint32_t off = 0;
    do
    {
        Rec* r = (Rec*)(*(uint8_t**)((char*)param_1 + 0x1c) + off);
        if (r->mChildBegin != r->mChildEnd)
        {
            int count = r->mCount;
            int* order = 0;
            if (count != 0)
                order = (int*)EAAllocate((unsigned)(count * 4), "Graphics", 0, 0, &g_eastlAllocator, 0xd1);
            int* orderEnd = order + count;
            for (int k = 0; k < count; ++k)
                order[k] = k;

            int nchild = (int)((uint8_t*)r->mChildEnd - (uint8_t*)r->mChildBegin) / 0x10;
            for (int i = 0; i < nchild; ++i)
            {
                EltSrc* c = r->mChildBegin + i;
                if (c->mNumElts != 0)
                    FUN_007345f0(order, orderEnd, FUN_00921240((int*)c));
            }

            int zero = 0;
            FUN_00921df0(&zero);

            GroupVec groups;
            groups.mBegin = 0;
            groups.mEnd = 0;
            groups.mCap = 0;

            int* gids = 0;
            if (count != 0)
            {
                gids = (int*)EAAllocate((unsigned)(count * 4), "Graphics", 0, 0, &g_eastlAllocator, 0xd1);
                for (int k = 0; k < count; ++k)
                    gids[k] = -1;
            }

            int cur = order[0];
            groups.push_back(cur);
            gids[cur] = 0;

            int rem = count - 1;
            if (rem > 0)
            {
                int* it = order;
                do
                {
                    ++it;
                    int idx = *it;
                    if (!FUN_007321a0(r, cur, idx))
                    {
                        groups.push_back(*it);
                        cur = *it;
                    }
                    --rem;
                    gids[idx] = (int)(groups.mEnd - groups.mBegin) - 1;
                } while (rem != 0);
            }

            if (r->mEltSize == 2)
            {
                for (int i = 0; i < r->mNumElts; ++i)
                {
                    uint16_t* p = (uint16_t*)((char*)r->mSrcBase + r->mStride * i);
                    *p = (uint16_t)gids[*p];
                }
            }
            else if (r->mEltSize == 4)
            {
                for (int i = 0; i < r->mNumElts; ++i)
                {
                    uint32_t* p = (uint32_t*)((char*)r->mSrcBase + r->mStride * i);
                    *p = (uint32_t)gids[*p];
                }
            }

            FUN_00921df0(&zero);

            int nchild2 = (int)((uint8_t*)r->mChildEnd - (uint8_t*)r->mChildBegin) / 0x10;
            for (int i = 0; i < nchild2; ++i)
                FUN_00735960((int*)&groups, r->mChildBegin + i);

            r->mCount = (int)(groups.mEnd - groups.mBegin) >> 2;

            FUN_00921df0(&zero);

            if (gids != 0 && gids[-1] != 0)
                EAFree(gids);
            if (groups.mBegin != 0 && groups.mBegin[-1] != 0)
                EAFree(groups.mBegin);
            if (order != 0 && order[-1] != 0)
                EAFree(order);
        }
        off += 0x8c;
    } while (--remaining != 0);
}

// @ 0x00736090
void Vec::fill(uint32_t param_2, int* param_3)
{
    uint32_t capacity = (uint32_t)(int*)((char*)mCap - (char*)mBegin) >> 2;
    if (param_2 > capacity)
    {
        Vec tmp;
        tmp.DoAllocate(param_2, (int*)&mEmptyRef);
        int v = *param_3;
        for (uint32_t i = 0; i < param_2; ++i)
            tmp.mBegin[i] = v;
        tmp.mEnd = (int*)((char*)tmp.mBegin + param_2 * 4);
        this->FUN_007353c0(&tmp);
        if (tmp.mBegin != 0 && tmp.mBegin != (int*)tmp.mEmptyRef)
            EAFree(tmp.mBegin);
        return;
    }

    uint32_t size = (uint32_t)(int*)((char*)mEnd - (char*)mBegin) >> 2;
    if (param_2 > size)
    {
        int v = *param_3;
        for (uint32_t i = 0; i < size; ++i)
            mBegin[i] = v;
        for (uint32_t i = size; i < param_2; ++i)
            mBegin[i] = v;
        mEnd = (int*)((char*)mBegin + param_2 * 4);
        return;
    }

    int v = *param_3;
    for (uint32_t i = 0; i < param_2; ++i)
        mBegin[i] = v;
    int* newEnd = (int*)((char*)mBegin + param_2 * 4);
    FUN_011e0744(newEnd, mEnd, 0);
    int tail = (int)((char*)mEnd - (char*)newEnd) >> 2;
    mEnd = mEnd - tail;
}
