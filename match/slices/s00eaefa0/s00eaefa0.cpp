// Slice s00eaefa0 -- SP::Audio::cResourceCityMusic / cPlayerCityMusic cluster.
//
// Modelled classes:
//   Vec4f    engine std::vector-like container of 4-byte elements (0xc bytes: begin/end/cap)
//   ResMusic 0x6c-byte audio resource: vtable + 5 dwords + 4 Vec4f members at +0x1c/+0x30/+0x44/+0x58
//
// Retail member offsets are read from the disassembly; the dev PDB layout differs,
// so objects are modelled locally with role-named members at retail offsets.

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef int i32s;
long _InterlockedExchange(volatile long *p, long v);

// ---------------------------------------------------------- indirect this-call
typedef void *(__thiscall *F0p)(void *);
typedef void  (__thiscall *F1p)(void *, void *);
typedef void  (__thiscall *F1u)(void *, u32);

// --------------------------------------------------------------- vector model
// A 12-byte container of 4-byte elements: begin, end, capacity.
struct Vec4f {
    void *mpBegin;   // +0x00
    void *mpEnd;     // +0x04
    void *mpCap;     // +0x08
    void *mpAlloc;   // +0x0c (fixed allocator payload: SP_STL_Sound)
    void *mpAlloc2;  // +0x10
    void Assign(const Vec4f &src);             // 0x00eae540 (declared, defined elsewhere)
};

#define Vec4fAssign(pT, pS) ((pT)->Assign(*(pS)))

// ---------------------------------------------------- the music resource type
struct ResMusic {
    void *mpVtbl;     // +0x00
    void *mpPad04;    // +0x04
    u32   mField08;   // +0x08
    u32   mField0c;   // +0x0c
    u32   mField10;   // +0x10
    u32   mField14;   // +0x14
    u32   mField18;   // +0x18
    Vec4f mVec1c;     // +0x1c
    Vec4f mVec30;     // +0x30
    Vec4f mVec44;     // +0x44
    Vec4f mVec58;     // +0x58

    // these are declared in-class so the compiler emits __thiscall codegen
    ResMusic(const ResMusic &src);   // 0x00eaf190
    ResMusic *ScalarDeletingDtor(u8 flags);   // 0x00eaf2b0
};

// --------------------------------------------------------------- extern decls
extern "C" void  operator_delete_array(void *p);                  // 0x00f47380
extern "C" void *memcpy(void *d, const void *s, u32 n);           // 0x011e0744
extern "C" void  FUN_00b93c60(int count, void *pAlloc);           // 0x00b93c60
extern "C" void  FUN_00eae010(void *first, void *last, void *dst); // 0x00eae010
extern "C" void  FUN_00eae040(void *first, void *last, void *dst); // 0x00eae040
extern "C" void *FUN_00eadb10(void *pOut, u32 n);                  // 0x00eadb10
extern "C" void *operator_new(u32 n, const char *pTag, int a, int b); // 0x00f473a0
extern "C" void *memmove(void *d, const void *s, u32 n);           // via [0x13cc480]

// player-city-music helpers
extern "C" u32   RandomUint32Uniform(void *pRng, u32 range);                 // 0x00a68fb0
extern "C" u32   RandomUint32WeightedChoice(void *pRng, u32 a, u32 b);       // 0x005e8ec0
extern "C" double RandomDoubleUniform(void *pRng);                           // 0x009360d0
extern "C" void *EA__Audio__GetSystemAT();                                   // 0x00a206f0
extern "C" void  FUN_00ea9440(void *pVec, const void *pVal);                 // 0x00ea9440
extern "C" void  FUN_00eae430(void *pVec, const void *pVal);                 // 0x00eae430
extern "C" void  EA__ConvertToString16(void *pOut, const u16 *pStr, int a);  // 0x0093c5a0
extern "C" void  eastl__wstring__range_initialize(void *pThis, u32 a, u32 b);// 0x00579a90

// eastl::wstring::basic_string(const) is __thiscall(dst, src); model with a
// tiny struct so the compiler emits ecx = destination.
struct WStringStub { void AssignFrom(const void *pSrc); };  // 0x0056e2d0
#define eastl_wstring_ctor(pDst, pSrc) ((WStringStub *)(pDst))->AssignFrom(pSrc)
extern "C" char  SP__TypedValueToStringT_short__Write(void *pThis, void *pOut, int a, const u16 *pName); // 0x00675990

// ------------------------------------------------------------------ functions

// @ 0x00eaf350
void do_fill_Music(ResMusic *pDst, ResMusic *pEnd, const ResMusic *pSrc)
{
    if (pDst == pEnd)
        return;
    do {
        pDst->mField08 = pSrc->mField08;
        pDst->mField0c = pSrc->mField0c;
        pDst->mField10 = pSrc->mField10;
        pDst->mField14 = pSrc->mField14;
        pDst->mField18 = pSrc->mField18;
        Vec4fAssign(&pDst->mVec1c, &pSrc->mVec1c);
        Vec4fAssign(&pDst->mVec30, &pSrc->mVec30);
        Vec4fAssign(&pDst->mVec44, &pSrc->mVec44);
        Vec4fAssign(&pDst->mVec58, &pSrc->mVec58);
        pDst = (ResMusic *)((char *)pDst + 0x6c);
    } while (pDst != pEnd);
}

// @ 0x00eaf410
ResMusic *do_copy_Music(ResMusic *pBegin, ResMusic *pEnd, ResMusic *pDst)
{
    if (pBegin == pEnd)
        return pDst;
    do {
        pDst->mField08 = pBegin->mField08;
        pDst->mField0c = pBegin->mField0c;
        pDst->mField10 = pBegin->mField10;
        pDst->mField14 = pBegin->mField14;
        pDst->mField18 = pBegin->mField18;
        Vec4fAssign(&pDst->mVec1c, &pBegin->mVec1c);
        Vec4fAssign(&pDst->mVec30, &pBegin->mVec30);
        Vec4fAssign(&pDst->mVec44, &pBegin->mVec44);
        Vec4fAssign(&pDst->mVec58, &pBegin->mVec58);
        pBegin = (ResMusic *)((char *)pBegin + 0x6c);
        pDst = (ResMusic *)((char *)pDst + 0x6c);
    } while (pBegin != pEnd);
    return pDst;
}

// Plain (non-owning) dword copy of one vector: copies begin/end/cap only.
static inline void CopyVecRaw(Vec4f *pDst, const Vec4f *pSrc)
{
    pDst->mpBegin = pSrc->mpBegin;
    pDst->mpEnd   = pSrc->mpEnd;
    pDst->mpCap   = pSrc->mpCap;
}

// @ 0x00eaf490
ResMusic *do_copy_backward_Music(ResMusic *pBegin, ResMusic *pEnd, ResMusic *pDst)
{
    if (pEnd == pBegin)
        return pDst;
    do {
        pEnd = (ResMusic *)((char *)pEnd - 0x6c);
        pDst = (ResMusic *)((char *)pDst - 0x6c);
        pDst->mField08 = pEnd->mField08;
        pDst->mField0c = pEnd->mField0c;
        pDst->mField10 = pEnd->mField10;
        pDst->mField14 = pEnd->mField14;
        pDst->mField18 = pEnd->mField18;
        CopyVecRaw(&pDst->mVec1c, &pEnd->mVec1c);
        CopyVecRaw(&pDst->mVec30, &pEnd->mVec30);
        CopyVecRaw(&pDst->mVec44, &pEnd->mVec44);
        CopyVecRaw(&pDst->mVec58, &pEnd->mVec58);
    } while (pEnd != pBegin);
    return pDst;
}

// @ 0x00eaf2b0
ResMusic *ResMusic::ScalarDeletingDtor(u8 flags)
{
    if (mVec58.mpBegin != 0)
        operator_delete_array(mVec58.mpBegin);
    if (mVec44.mpBegin != 0)
        operator_delete_array(mVec44.mpBegin);
    if (mVec30.mpBegin != 0)
        operator_delete_array(mVec30.mpBegin);
    if (mVec1c.mpBegin != 0)
        operator_delete_array(mVec1c.mpBegin);
    mpVtbl = (void *)0x013eb938;
    if ((flags & 1) != 0)
        operator_delete_array(this);
    return this;
}

// Deep-copies one 4-byte-element vector: reserve via FUN_00b93c60 then memcpy.
static void CopyVec(Vec4f *pDst, const Vec4f *pSrc)
{
    int n = (int)((char *)pSrc->mpEnd - (char *)pSrc->mpBegin) >> 2;
    FUN_00b93c60(n, (char *)pSrc + 0xc);
    u32 bytes = (u32)((char *)pSrc->mpEnd - (char *)pSrc->mpBegin);
    char *p = (char *)memcpy(pDst->mpBegin, pSrc->mpBegin, bytes);
    pDst->mpEnd = p + bytes;
}

// @ 0x00eaf190
ResMusic::ResMusic(const ResMusic &src)
{
    mpVtbl = (void *)0x013ebcdc;
    _InterlockedExchange((volatile long *)&mpPad04, 0);
    mField08 = src.mField08;
    mField0c = src.mField0c;
    mField10 = src.mField10;
    mpVtbl = (void *)0x014884a0;
    mField14 = src.mField14;
    mField18 = src.mField18;
    CopyVec(&mVec1c, &src.mVec1c);
    CopyVec(&mVec30, &src.mVec30);
    CopyVec(&mVec44, &src.mVec44);
    CopyVec(&mVec58, &src.mVec58);
}

// --------------------------------------------------------- pointer-vector type
// A 12-byte container of (4-byte) pointers; the inserted range is a singly
// linked list whose nodes have `next` at +0 and the payload at +8.
struct ListNode {
    ListNode *mpNext;   // +0x00
    u32       mPad04;   // +0x04
    u32       mValue;   // +0x08
};

struct VecP {
    void *mpBegin;   // +0x00
    void *mpEnd;     // +0x04
    void *mpCap;     // +0x08
    u32   Count() const { return (u32)((char *)mpEnd - (char *)mpBegin) >> 2; }
    u32   Capacity() const { return (u32)((char *)mpCap - (char *)mpBegin) >> 2; }
    void InsertRange(void *pos, ListNode *first, ListNode *last);  // 0x00eaefa0
};

// @ 0x00eaefa0
void VecP::InsertRange(void *pos, ListNode *first, ListNode *last)
{
    if (first == last)
        return;

    u32 n = 0;
    for (ListNode *it = first; it != last; it = it->mpNext)
        ++n;

    u32 cap = Capacity();
    if (n <= cap) {
        u32 elemsEnd = (u32)((char *)mpEnd - (char *)mpBegin) >> 2;
        u32 elemsBefore = (elemsEnd - ((u32)((char *)pos - (char *)mpBegin) >> 2));

        if (n < elemsBefore) {
            // shift the tail right by n and splice the source in
            void *pTail = (char *)mpEnd - n * 4;
            FUN_00eae010(mpEnd, pTail, mpEnd);
            mpEnd = (char *)mpEnd + n * 4;
            memmove((char *)mpEnd - (elemsBefore * 4), pos, elemsBefore * 4);
            FUN_00eae010(first, last, pos);
            return;
        }

        // append then move the tail
        void *pInsert = pos;
        ListNode *mid = first;
        FUN_00eadb10(&pInsert, elemsBefore);
        FUN_00eae010(mid, last, mpEnd);
        mpEnd = (char *)mpEnd + (n - elemsBefore) * 4;
        FUN_00eae040(mpEnd, pos, (char *)mpEnd + elemsBefore * 4);
        mpEnd = (char *)mpEnd + elemsBefore * 4;
        FUN_00eae040(first, mid, (char *)pos + elemsBefore * 4);
        return;
    }

    // grow: new capacity = max(2*size, 1) rounded up to at least n+size
    u32 size = Count();
    u32 newCap = size * 2;
    if (size == 0)
        newCap = 1;
    u32 need = size + n;
    if (need >= newCap)
        newCap = need;

    void *pNew = 0;
    if (newCap != 0)
        pNew = operator_new(newCap * 4, "Simulator", 0, 0);

    char *pMid = (char *)memcpy(pNew, mpBegin, (u32)((char *)pos - (char *)mpBegin));
    for (ListNode *it = first; it != last; it = it->mpNext) {
        *(u32 *)pMid = it->mValue;
        pMid += 4;
    }
    u32 tailBytes = (u32)((char *)mpEnd - (char *)pos);
    char *pEndNew = (char *)memcpy(pMid, pos, tailBytes) + tailBytes;

    if (mpBegin != 0)
        operator_delete_array(mpBegin);
    mpBegin = pNew;
    mpEnd = pEndNew;
    mpCap = (char *)pNew + newCap * 4;
}

// --------------------------------------------------------- player-music model
// A large (~0x1f0-byte) object mixing u32 and float members. Rather than model
// the full layout, accessors name the retail offsets used by this cluster; the
// offsets are documented in the comments.
struct VecU {                     // 12-byte u32/float vector (begin/end/cap)
    float *mpBegin;               // +0x00
    float *mpEnd;                 // +0x04
    float *mpCap;                 // +0x08
};

struct PlayerMusic {
    u8     mPad00[0x2c];
    float  mTempo;                // +0x2c
    u8     mPad30[0x38];
    i32s   mTranspose;            // +0x68
    u8     mPad6c[0x08];
    u32   *mpVolTable;            // +0x74
    u8     mPad78[0x8c];
    u8     mRng[1];               // +0x104 (random generator state)
    u8     mPad105[0x24];
    VecU   mVec128;               // +0x128
    VecU   mVec13c;               // +0x13c
    float  mLastTime;             // +0x150
    u32    mNoteIndex;            // +0x154
    u8     mPad158[0x74];
    VecU   mVec1cc;               // +0x1cc
    VecU   mVec1e0;               // +0x1e0

    void AddNote(u32 *pOut);           // 0x00eaf510
    void MoveNote(u32 noteIndex, u32 numMoved);  // 0x00eaf8d0
};

// @ 0x00eaf510
void PlayerMusic::AddNote(u32 *pOut)
{
    PlayerMusic *pThis = this;
    // Step 1: pick a note index (uniform if the degree list is empty, else a
    // weighted choice keyed by the last degree).
    u32 degreeCount = (u32)((char *)pThis->mVec13c.mpEnd - (char *)pThis->mVec13c.mpBegin) >> 2;
    u32 drawn;
    if (pThis->mVec13c.mpBegin == pThis->mVec13c.mpEnd) {
        drawn = RandomUint32Uniform(pThis->mRng, 7);
    } else {
        u32 lastKey = ((u32 *)pThis->mVec13c.mpEnd)[-1];
        u32 weight = ((u32 *)(void *)((char *)pThis + 0x78))[lastKey];
        drawn = RandomUint32WeightedChoice(pThis->mRng, 7, weight);
    }
    // push the drawn degree onto the degree history
    if (pThis->mVec13c.mpEnd < pThis->mVec13c.mpCap) {
        float *p = pThis->mVec13c.mpEnd;
        pThis->mVec13c.mpEnd = p + 1;
        if (p != 0)
            *(u32 *)p = drawn;
    } else {
        FUN_00ea9440(&pThis->mVec13c, &drawn);
    }

    // Step 2: absolute pitch for the drawn degree
    u32 lastKey2 = ((u32 *)pThis->mVec13c.mpEnd)[-1];
    u32 pitch = pThis->mpVolTable[lastKey2] + (u32)pThis->mTranspose;
    if (pThis->mVec1cc.mpEnd < pThis->mVec1cc.mpCap) {
        float *p = pThis->mVec1cc.mpEnd;
        pThis->mVec1cc.mpEnd = p + 1;
        if (p != 0)
            *(u32 *)p = pitch;
    } else {
        FUN_00ea9440(&pThis->mVec1cc, &pitch);
    }

    // Step 3: whether this degree differs from the previous one (rest = 2)
    u32 noteIndex = degreeCount;
    u32 diffFlag;
    u32 cur = ((u32 *)pThis->mVec13c.mpBegin)[noteIndex];
    if (cur == 0xffffffff)
        diffFlag = 2;
    else if (noteIndex == 0)
        diffFlag = 0;
    else {
        u32 prev = ((u32 *)pThis->mVec13c.mpBegin)[noteIndex - 1];
        u32 *row = (u32 *)(void *)((char *)pThis + 0x94 + prev * 4);
        diffFlag = (row[cur] == 0) ? 1 : 0;
    }
    if (pThis->mVec128.mpEnd < pThis->mVec128.mpCap) {
        float *p = pThis->mVec128.mpEnd;
        pThis->mVec128.mpEnd = p + 1;
        if (p != 0)
            *(u32 *)p = diffFlag;
    } else {
        FUN_00ea9440(&pThis->mVec128, &diffFlag);
    }

    // Step 4: compute the next onset time and record the delta.
    float frac = pThis->mLastTime / pThis->mTempo;
    u32 notePos = pThis->mNoteIndex;
    u32 rows = ((u32 *)(void *)((char *)pThis + 0x40))[notePos];
    float *table = *(float **)((char *)(void *)((char *)pThis + 0x54) + notePos * 4);

    u32 step = (u32)(long long)(frac + 0.5) + 1;
    float r;
    do {
        r = (float)RandomDoubleUniform(pThis->mRng);
        step++;
    } while (table[(step - 1) % rows] < r);

    float newTime = (float)step * pThis->mTempo;
    float delta = newTime - pThis->mLastTime;
    if (pThis->mVec1e0.mpEnd < pThis->mVec1e0.mpCap) {
        float *p = pThis->mVec1e0.mpEnd;
        pThis->mVec1e0.mpEnd = p + 1;
        if (p != 0)
            *p = delta;
    } else {
        FUN_00eae430(&pThis->mVec1e0, &delta);
    }
    pThis->mLastTime = newTime;

    // Step 5: emit the debug/trace channel values.
    void *pSys;
    pSys = EA__Audio__GetSystemAT();
    if (pSys != 0) {
        ((void (__thiscall *)(void *, u32))((void **)*(void **)pSys)[0x38/4])(pSys, 0x3cdd1a9);
        ((void (__thiscall *)(void *, u32, u32))((void **)*(void **)pSys)[0x40/4])(pSys, 0x34753a7, 0xe7b72656);
        ((void (__thiscall *)(void *, u32, float))((void **)*(void **)pSys)[0x3c/4])(pSys, 0x34753aa, (float)(i32s)noteIndex);
        ((void (__thiscall *)(void *))((void **)*(void **)pSys)[0x58/4])(pSys);
    }
    pSys = EA__Audio__GetSystemAT();
    if (pSys != 0) {
        ((void (__thiscall *)(void *, u32))((void **)*(void **)pSys)[0x38/4])(pSys, 0x3cdd1a9);
        ((void (__thiscall *)(void *, u32, u32))((void **)*(void **)pSys)[0x40/4])(pSys, 0x34753a7, 0xfe31e5d9);
        ((void (__thiscall *)(void *, u32, float))((void **)*(void **)pSys)[0x3c/4])(pSys, 0x34753aa, (float)(i32s)((u32 *)pThis->mVec1cc.mpEnd)[-1]);
        ((void (__thiscall *)(void *))((void **)*(void **)pSys)[0x58/4])(pSys);
    }
    pSys = EA__Audio__GetSystemAT();
    if (pSys != 0) {
        ((void (__thiscall *)(void *, u32))((void **)*(void **)pSys)[0x38/4])(pSys, 0x3cdd1a9);
        ((void (__thiscall *)(void *, u32, u32))((void **)*(void **)pSys)[0x40/4])(pSys, 0x34753a7, 0xc309bcc9);
        ((void (__thiscall *)(void *, u32, float))((void **)*(void **)pSys)[0x3c/4])(pSys, 0x34753aa, pThis->mVec1e0.mpEnd[-1]);
        ((void (__thiscall *)(void *))((void **)*(void **)pSys)[0x58/4])(pSys);
    }
    pSys = EA__Audio__GetSystemAT();
    if (pSys != 0) {
        ((void (__thiscall *)(void *, u32))((void **)*(void **)pSys)[0x38/4])(pSys, 0x3cdd1a9);
        ((void (__thiscall *)(void *, u32, u32))((void **)*(void **)pSys)[0x40/4])(pSys, 0x34753a7, 0x0ead8248);
        ((void (__thiscall *)(void *, u32, float))((void **)*(void **)pSys)[0x3c/4])(pSys, 0x34753aa,
                (float)(i32s)((u32)((char *)pThis->mVec1cc.mpEnd - (char *)pThis->mVec1cc.mpBegin) >> 2));
        ((void (__thiscall *)(void *))((void **)*(void **)pSys)[0x58/4])(pSys);
    }

    // Step 6: return the newly-appended values.
    pOut[0] = ((u32 *)pThis->mVec1cc.mpEnd)[-1];
    pOut[1] = ((u32 *)pThis->mVec1e0.mpEnd)[-1];
    pOut[2] = ((u32 *)pThis->mVec128.mpEnd)[-1];
}

// @ 0x00eaf8d0
void PlayerMusic::MoveNote(u32 noteIndex, u32 numMoved)
{
    PlayerMusic *pThis = this;
    // Compute the element offset and save the three parallel values for this note.
    u32 off = noteIndex * 4;
    u8 *base = (u8 *)pThis;
    VecU *pVec13c = (VecU *)(base + 0x13c);
    VecU *pVec1cc = (VecU *)(base + 0x1cc);
    VecU *pVec128 = (VecU *)(base + 0x128);
    VecU *pVec1e0 = (VecU *)(base + 0x1e0);

    u32 saved13c = ((u32 *)pVec13c->mpBegin)[noteIndex];
    float saved1e0 = pVec1e0->mpBegin[noteIndex];
    u32 saved1cc = ((u32 *)pVec1cc->mpBegin)[noteIndex];
    u32 saved128 = ((u32 *)pVec128->mpBegin)[noteIndex];

    // Remove the note from each of the four parallel vectors by shifting the
    // tail down one slot and decrementing the end pointer.
    VecU *rm[4];
    rm[0] = pVec1cc;
    rm[1] = pVec13c;
    rm[2] = pVec1e0;
    rm[3] = pVec128;
    for (int i = 0; i < 4; i++) {
        VecU *v = rm[i];
        u8 *p = (u8 *)v->mpBegin + off;
        u8 *q = p + 4;
        if (q < (u8 *)v->mpEnd)
            memcpy(p, q, (u32)((u8 *)v->mpEnd - q));
        v->mpEnd = (float *)((u8 *)v->mpEnd - 4);
    }

    // Re-insert the saved values through the same push_back paths as AddNote.
    if (pVec1cc->mpEnd < pVec1cc->mpCap) {
        float *p = pVec1cc->mpEnd++;
        if (p != 0)
            *(u32 *)p = saved1cc;
    } else {
        FUN_00ea9440(pVec1cc, &saved1cc);
    }
    if (pVec13c->mpEnd < pVec13c->mpCap) {
        float *p = pVec13c->mpEnd++;
        if (p != 0)
            *(u32 *)p = saved13c;
    } else {
        FUN_00ea9440(pVec13c, &saved13c);
    }
    if (pVec1e0->mpEnd < pVec1e0->mpCap) {
        float *p = pVec1e0->mpEnd++;
        if (p != 0)
            *p = saved1e0;
    } else {
        FUN_00eae430(pVec1e0, &saved1e0);
    }
    if (pVec128->mpEnd < pVec128->mpCap) {
        float *p = pVec128->mpEnd++;
        if (p != 0)
            *(u32 *)p = saved128;
    } else {
        FUN_00ea9440(pVec128, &saved128);
    }

    // Re-emit the trace channel values for noteIndex (four groups: one for each
    // parallel vector value).
    void *pSys = EA__Audio__GetSystemAT();
    if (pSys != 0) {
        ((void (__thiscall *)(void *, u32))((void **)*(void **)pSys)[0x38/4])(pSys, 0x3cdd1a9);
        ((void (__thiscall *)(void *, u32, u32))((void **)*(void **)pSys)[0x40/4])(pSys, 0x34753a7, 0xe7b72656);
        ((void (__thiscall *)(void *, u32, float))((void **)*(void **)pSys)[0x3c/4])(pSys, 0x34753aa, (float)(i32s)noteIndex);
        ((void (__thiscall *)(void *))((void **)*(void **)pSys)[0x58/4])(pSys);
    }
    pSys = EA__Audio__GetSystemAT();
    if (pSys != 0) {
        ((void (__thiscall *)(void *, u32))((void **)*(void **)pSys)[0x38/4])(pSys, 0x3cdd1a9);
        ((void (__thiscall *)(void *, u32, u32))((void **)*(void **)pSys)[0x40/4])(pSys, 0x34753a7, 0xfe31e5d9);
        ((void (__thiscall *)(void *, u32, float))((void **)*(void **)pSys)[0x3c/4])(pSys, 0x34753aa, (float)(i32s)((u32 *)pVec1cc->mpBegin)[noteIndex]);
        ((void (__thiscall *)(void *))((void **)*(void **)pSys)[0x58/4])(pSys);
    }
    pSys = EA__Audio__GetSystemAT();
    if (pSys != 0) {
        ((void (__thiscall *)(void *, u32))((void **)*(void **)pSys)[0x38/4])(pSys, 0x3cdd1a9);
        ((void (__thiscall *)(void *, u32, u32))((void **)*(void **)pSys)[0x40/4])(pSys, 0x34753a7, 0xc309bcc9);
        ((void (__thiscall *)(void *, u32, float))((void **)*(void **)pSys)[0x3c/4])(pSys, 0x34753aa, pVec1e0->mpBegin[noteIndex]);
        ((void (__thiscall *)(void *))((void **)*(void **)pSys)[0x58/4])(pSys);
    }
    pSys = EA__Audio__GetSystemAT();
    if (pSys != 0) {
        ((void (__thiscall *)(void *, u32))((void **)*(void **)pSys)[0x38/4])(pSys, 0x3cdd1a9);
        ((void (__thiscall *)(void *, u32, u32))((void **)*(void **)pSys)[0x40/4])(pSys, 0x34753a7, 0x0ead8248);
        ((void (__thiscall *)(void *, u32, float))((void **)*(void **)pSys)[0x3c/4])(pSys, 0x34753aa,
                (float)(i32s)((u32)((char *)pVec13c->mpEnd - (char *)pVec13c->mpBegin) >> 2));
        ((void (__thiscall *)(void *))((void **)*(void **)pSys)[0x58/4])(pSys);
    }

    (void)numMoved;
    (void)saved128;
}

// A 12-byte container of 4-byte elements (u32/pointer): begin, end, cap.
struct PtrVec {
    void *mpBegin;
    void *mpEnd;
    void *mpCap;
};

// @ 0x00eafcf0
char PlayerMusic_ToString(PlayerMusic *pThis, void *pWriter, u16 *pName)
{
    (void)pThis;
    // Serializer: opens a "list", writes each circular-list node's payload as a
    // "uint32_t" typed value, then closes the list.  The list head is the first
    // argument (a sentinel whose `next` points at the first element).
    char ok = 1;
    ListNode *pHead = (ListNode *)pWriter;
    if (pHead != pHead->mpNext) {
        u32 w[4];
        void *pKey;
        if (pName != 0) {
            EA__ConvertToString16(w, pName, -1);
            pKey = w;
        } else {
            u32 z[3] = { 0, 0, 0 };
            eastl__wstring__range_initialize(z, 0, 0);
            pKey = z;
        }
        void *pNameStr;
        eastl_wstring_ctor(&pNameStr, pKey);
        // vtable slot 0: BeginList(name)
        ((void (__thiscall *)(void *, void *))((void **)*(void **)pWriter)[0])(pWriter, pNameStr);
        // walk nodes, writing the +8 payload of each
        ListNode *end = (ListNode *)0;
        for (ListNode *it = pHead->mpNext; it != end; it = it->mpNext) {
            if (ok)
                ok = SP__TypedValueToStringT_short__Write(&pNameStr, (void *)it->mValue, 0, (const u16 *)0x1401158);
        }
        // vtable slot 4: EndList(name)
        ((void (__thiscall *)(void *, void *))((void **)*(void **)pWriter)[1])(pWriter, pNameStr);
    }
    return ok;
}

// @ 0x00eafe40
char PlayerMusic_FromString(PtrVec *pVec, u16 *pName, void *pWriter)
{
    // Serializer over a (begin,end) range of u32: BeginList(name), Write each
    // element as "uint32_t", EndList(name).
    char ok = 1;
    if (pVec->mpBegin != pVec->mpEnd) {
        u32 w[4];
        void *pKey;
        if (pName != 0) {
            EA__ConvertToString16(w, pName, -1);
            pKey = w;
        } else {
            u32 z[3] = { 0, 0, 0 };
            eastl__wstring__range_initialize(z, 0, 0);
            pKey = z;
        }
        void *pNameStr;
        eastl_wstring_ctor(&pNameStr, pKey);
        ((void (__thiscall *)(void *, void *))((void **)*(void **)pWriter)[0])(pWriter, pNameStr);
        for (u32 *it = (u32 *)pVec->mpBegin; it != (u32 *)pVec->mpEnd; ++it) {
            if (!ok)
                break;
            ok = SP__TypedValueToStringT_short__Write(&pNameStr, it, 0, (const u16 *)0x1401158);
        }
        ((void (__thiscall *)(void *, void *))((void **)*(void **)pWriter)[1])(pWriter, pNameStr);
    }
    return ok;
}

