// =============================================================================================
// SporeApp.exe slice s00afbaf0  (batch gold7, worker 5)
//
// 11 routines from the Simulator creature-mode action circle (cActionCircle) and the
// EASTL-style {begin,end,cap} vector helpers it uses:
//
//   0x00afbaf0  cActionCircle ctor - initialise the slot vector and tuning fields
//   0x00afbf40  intro-sort make-heap helper
//   0x00afbfb0  intro-sort sort-heap helper
//   0x00afc030  find a slot + insert a neighbour slot
//   0x00afc0d0  erase a [first,last) range of slots
//   0x00afc150  insert one slot (grow if full)
//   0x00afc2a0  sift each moved slot then final heap pass
//   0x00afc410  erase one slot from +0x50/+0x54
//   0x00afc470  push_back one object into the +0x04/+0x08 vector
//   0x00afc4b0  find + erase one object from that vector
//   0x00afc500  intro-sort recursion
//
// Layout: offsets are taken from the disassembly of this build. Every touched field is named.
// Flags: /O2 /Ob2 /MD /Gy /TP /arch:SSE /GS-
// =============================================================================================
#include "types.h"

// ---------------------------------------------------------------------------------------------
// external helpers (retail addresses; not defined here)
// ---------------------------------------------------------------------------------------------
// 16-byte value bundle (3 floats + one pointer) passed by value to the sort helpers.
// The user-defined copy ctor / dtor make MSVC copy the aggregate member-wise, so the
// three floats travel through XMM (movss) exactly as the original does.
struct tFloat4 {
    float       x;
    float       y;
    float       z;
    void*       pCtx;

    tFloat4() {}
    tFloat4(const tFloat4& o) { x = o.x; y = o.y; z = o.z; pCtx = o.pCtx; }
    ~tFloat4() {}
};

void*   __cdecl operator_new(uint32_t nSize, const char* pName, int32_t nA, int32_t nB,
                             const char* pFile, int32_t nLine);                 // 0x00f473a0
void    __cdecl operator_delete_(void* pBlock);                                 // 0x00f47380

void    __stdcall FUN_00bab900(void** pVec, void** ppValue);                    // 0x00bab900
void    __cdecl FUN_00c83c90(void* pDst, void* pEnd, void* pSrc);               // 0x00c83c90
void*   __cdecl FUN_00afa430(void* pFirst, void* pLast, void* pOut);            // 0x00afa430
void*   __cdecl FUN_00afa380(void* pFirst, void* pLast, void* pOut);            // 0x00afa380
void*   __cdecl FUN_00afa3f0(void* pFirst, void* pLast, void* pOut);            // 0x00afa3f0
void*   __cdecl FUN_00afa4a0(void* pFirst, void* pLast, void* pOut);            // 0x00afa4a0
void    __stdcall FUN_00afb0d0(void* pOut, const void* pKey);                   // 0x00afb0d0
void*   __cdecl FUN_00afb430(void* pA, void* pB, void* pC, tFloat4 v1, tFloat4 v2); // 0x00afb430
void*   __cdecl FUN_00afb540(void* pFirst, void* pLast, int32_t nPivot);        // 0x00afb540
void    __cdecl FUN_00afb8f0(int32_t* pBase, int32_t nFirst, int32_t nCount, int32_t nRoot,
                             int32_t nKey, tFloat4 v);                          // 0x00afb8f0
void    __cdecl FUN_00afbf40(int32_t* pBase, int32_t* pLast, tFloat4 v);        // 0x00afbf40
void    __cdecl FUN_00afbfb0(int32_t* pBase, int32_t* pLast, tFloat4 v);        // 0x00afbfb0
void    __cdecl FUN_00afc2a0(void** pFirst, void** pLast, void** pLast2, tFloat4 v); // 0x00afc2a0
void    __cdecl FUN_00afc500(int32_t* pFirst, int32_t* pLast, int32_t nLimit, tFloat4 v); // 0x00afc500

// ---------------------------------------------------------------------------------------------
// image constants / data
// ---------------------------------------------------------------------------------------------
extern float    g_f2f1c;            // 0x01470f1c
extern float    g_f8a0;             // 0x013eb8a0
extern float    g_fSpace;           // 0x0167aec4
extern float    g_fSpaceB;          // 0x0167aec8
extern float    g_fSpaceC;          // 0x0167aecc
extern float    g_fVec7c;           // 0x0156737c
extern float    g_fVec80;           // 0x01567380
extern float    g_fVec84;           // 0x01567384
extern float    g_fVec88;           // 0x01567388
extern float    g_f8c5448;          // 0x01485548
extern float    g_f3eb1bc;          // 0x013eb1bc
extern int32_t  g_nSlots;           // 0x0156734c
extern void*    g_pSlotVtable;      // 0x0154df28
extern float    g_f1_48;            // 0x01485720  (1.0f)

extern const char g_szSimulator[];  // 0x013f09b4
extern const char g_szAllocFile[];  // ".../EASTL/include/EASTL/allocator.h"

// ---------------------------------------------------------------------------------------------
// one 0x18-byte slot (dummy polymorphic element whose vtable pointer sits at +0)
// ---------------------------------------------------------------------------------------------
class tSlot {
public:
    virtual void    v00();
    virtual void    v04();                          // +0x04 destructor slot
    void*           mpOwned;                        // +0x04  (owned sub-object pointer)
    uint8_t         mPad08[0x18 - 0x08];

    void        CopyConstruct(const tSlot& src);    // 0x00afa110 (thiscall)
    void        Assign(const tSlot& src);           // 0x00afa230 (thiscall)
};

// ---------------------------------------------------------------------------------------------
// EASTL-style vector of 0x18-byte slots: begin/end/cap at +0/+4/+8
// ---------------------------------------------------------------------------------------------
class cSlotVec {
public:
    tSlot*  mpBegin;                                // +0x00
    tSlot*  mpEnd;                                  // +0x04
    tSlot*  mpCap;                                  // +0x08

    tSlot*      EraseRange(tSlot* pFirst, tSlot* pLast);        // 0x00afc0d0
    void        InsertOne(tSlot* pPos, tSlot* pValue);          // 0x00afc150
};

// ---------------------------------------------------------------------------------------------
// EASTL-style vector of object pointers: begin/end/cap at +0/+4/+8
// ---------------------------------------------------------------------------------------------
class cPtrVec {
public:
    void**  mpBegin;                                // +0x00
    void**  mpEnd;                                  // +0x04
    void**  mpCap;                                  // +0x08

    void        PushBack(void** ppValue);           // 0x00afc470
    void        Grow(void* pEnd, void** ppValue);   // 0x00bab900
};

// ---------------------------------------------------------------------------------------------
// the action circle owning the slot vector; every field touched by this slice is named
// ---------------------------------------------------------------------------------------------
class cActionCircle {
public:
    cSlotVec    mSlots;                             // +0x000  (slot vector: begin/end/cap)
    int32_t     mnField0c;                          // +0x00c
    int32_t     mnField10;                          // +0x010
    int32_t     mnField14;                          // +0x014
    float       mf18;                               // +0x018 (inline slot buffer x)
    float       mf1c;                               // +0x01c
    float       mf20;                               // +0x020
    float       mf24;                               // +0x024
    int32_t     mnField28;                          // +0x028
    int32_t     mnField2c;                          // +0x02c
    int32_t     mnField30;                          // +0x030
    int32_t     mnField34;                          // +0x034
    int32_t     mnField38;                          // +0x038
    void*       mpField3c;                          // +0x03c
    int32_t     mnField40;                          // +0x040
    int32_t     mnField44;                          // +0x044
    float       mfField48;                          // +0x048
    float       mfField4c;                          // +0x04c
    cSlotVec    mSlots2;                            // +0x050  (second slot vector)
    float       mf5c;                               // +0x05c
    int32_t     mn60;                               // +0x060
    float       mf64;                               // +0x064
    float       mf68;                               // +0x068
    float       mf6c;                               // +0x06c
    float       mf70;                               // +0x070
    float       mf74;                               // +0x074
    float       mf78;                               // +0x078
    float       mf7c;                               // +0x07c
    float       mf80;                               // +0x080
    float       mf84;                               // +0x084
    float       mf88;                               // +0x088
    float       mf8c;                               // +0x08c
    float       mf90;                               // +0x090
    float       mf94;                               // +0x094
    uint8_t     mb98;                               // +0x098
    uint8_t     mPad99[3];                          // +0x099
    float       mf9c;                               // +0x09c
    float       mfa0;                               // +0x0a0
    float       mfa4;                               // +0x0a4
    float       mfa8;                               // +0x0a8
    float       mfac;                               // +0x0ac
    float       mfb0;                               // +0x0b0
    float       mfb4;                               // +0x0b4
    float       mfb8;                               // +0x0b8
    float       mfbc;                               // +0x0bc
    float       mfc0;                               // +0x0c0
    float       mfc4;                               // +0x0c4 (unwritten in ctor)
    uint8_t     mbc8;                               // +0x0c8
    uint8_t     mPadc9[3];                          // +0x0c9
    float       mfcc;                               // +0x0cc
    float       mfd0;                               // +0x0d0
    float       mfd4;                               // +0x0d4
    float       mfd8;                               // +0x0d8
    int32_t     mdc;                                // +0x0dc
    int32_t     me0;                                // +0x0e0
    int32_t     me4;                                // +0x0e4
    int32_t     me8;                                // +0x0e8 (unwritten in ctor)
    int32_t     mec;                                // +0x0ec (unwritten in ctor)
    int32_t     mf0;                                // +0x0f0
    int32_t     mf4;                                // +0x0f4
    int32_t     mf8;                                // +0x0f8
    float       mffc;                               // +0x0fc (unwritten in ctor)
    float       mf100;                              // +0x100 (unwritten in ctor)
    float       mf104;                              // +0x104
    float       mf108;                              // +0x108
    float       mf10c;                              // +0x10c
    float       mf110;                              // +0x110
    float       mf114;                              // +0x114
    float       mf118;                              // +0x118
    float       mf11c;                              // +0x11c
    float       mf120;                              // +0x120
    float       mf124;                              // +0x124
    float       mf128;                              // +0x128 (unwritten in ctor)
    uint8_t     mbc12c;                             // +0x12c
    uint8_t     mPad12d[3];                         // +0x12d
    float       mf130;                              // +0x130
    float       mf134;                              // +0x134
    float       mf138;                              // +0x138
    float       mf13c;                              // +0x13c
    int32_t     m140;                               // +0x140
    int32_t     m144;                               // +0x144
    int32_t     m148;                               // +0x148
    int32_t     m14c;                               // +0x14c (unwritten in ctor)
    int32_t     m150;                               // +0x150 (unwritten in ctor)
    int32_t     m154;                               // +0x154
    int32_t     m158;                               // +0x158
    int32_t     m15c;                               // +0x15c
    int32_t     m160;                               // +0x160 (unwritten in ctor)
    int32_t     m164;                               // +0x164 (unwritten in ctor)
    int32_t     m168;                               // +0x168
    int32_t     m16c;                               // +0x16c
    int32_t     m170;                               // +0x170
    int32_t     mnField174;                         // +0x174

    cActionCircle();                                // 0x00afbaf0
    bool        EraseOne(tSlot* pPos);              // 0x00afc410
};

// =============================================================================================
// @ 0xafbaf0  cActionCircle constructor
// =============================================================================================
cActionCircle::cActionCircle()
{
    mnField14 = 0;
    mSlots.mpBegin = (tSlot*)((char*)this + 0x18);
    mSlots.mpEnd = (tSlot*)((char*)this + 0x18);
    mSlots.mpCap = (tSlot*)((char*)this + 0x38);
    mfField4c = g_f2f1c;
    mfField48 = g_f1_48;
    mnField40 = 1;
    mpField3c = &g_pSlotVtable;
    mnField44 = 0;
    mSlots2.mpBegin = 0;
    mSlots2.mpCap = 0;
    mf5c = 0.0f;
    mn60 = 0;
    mf64 = g_fSpace;
    mf68 = g_fSpaceB;
    mf6c = g_fSpaceC;
    mf70 = g_fSpace;
    mf74 = g_fSpaceB;
    mf78 = g_fSpaceC;
    mf7c = 0.0f;
    mf80 = 0.0f;
    mf84 = g_f1_48;
    mf88 = g_f1_48;
    mf8c = g_f8c5448;
    mf90 = g_f3eb1bc;
    mf94 = g_f8a0;
    mb98 = 0;
    mf9c = g_f1_48;
    mfa0 = g_fSpace;
    mfa4 = g_fSpaceB;
    mfa8 = g_fSpaceC;
    mfac = g_f3eb1bc;
    mfb0 = g_f3eb1bc;
    mfb4 = g_fSpace;
    mfb8 = g_fSpaceB;
    mfbc = g_fSpaceC;
    mfc0 = 0.0f;
    mbc8 = 0;
    mfcc = g_fVec7c;
    mfd0 = g_fVec80;
    mfd4 = g_fVec84;
    mfd8 = g_fVec88;
    mdc = 0;
    me0 = 0;
    me4 = 0;
    mf0 = 0;
    mf4 = 0;
    mf8 = 0;
    mf104 = g_fSpace;
    mf108 = g_fSpaceB;
    mf10c = g_fSpaceC;
    mf110 = g_f3eb1bc;
    mf114 = g_f3eb1bc;
    mf118 = g_fSpace;
    mf11c = g_fSpaceB;
    mf120 = g_fSpaceC;
    mbc12c = 0;
    mf124 = 0.0f;
    mf130 = g_fVec7c;
    mf134 = g_fVec80;
    mf138 = g_fVec84;
    mf13c = g_fVec88;
    m140 = 0;
    m144 = 0;
    m148 = 0;
    m154 = 0;
    m158 = 0;
    m15c = 0;
    m168 = 0;
    m16c = 0;
    m170 = 0;
    mnField174 = g_nSlots++;
}

// =============================================================================================
// @ 0xafbf40  intro-sort "make heap" helper
// =============================================================================================
void __cdecl FUN_00afbf40(int32_t* pBase, int32_t* pLast, tFloat4 v)
{
    int32_t nCount = (int32_t)(pLast - pBase);
    if (nCount >= 2) {
        int32_t i = ((nCount - 2) >> 1) + 1;
        do {
            i = i - 1;
            FUN_00afb8f0(pBase, i, nCount, i, pBase[i], v);
        } while (i != 0);
    }
}

// =============================================================================================
// @ 0xafbfb0  intro-sort "sort heap" helper
// =============================================================================================
void __cdecl FUN_00afbfb0(int32_t* pBase, int32_t* pLast, tFloat4 v)
{
    int32_t nCount = (int32_t)((char*)pLast - (char*)pBase) >> 2;
    if (nCount > 1) {
        int32_t* p = pLast - 1;
        do {
            int32_t nKey = *p;
            *p = *pBase;
            FUN_00afb8f0(pBase, 0, nCount - 1, 0, nKey, v);
            p = p - 1;
            nCount = (int32_t)(p + 1 - pBase);
        } while (nCount > 1);
    }
}

// =============================================================================================
// @ 0xafc030  find a slot by key, insert its neighbour if it is the head slot
// =============================================================================================
// The object this runs on keeps a table base pointer at +0x04 and an index at +0x08.
struct tInsertArgs {
    int32_t     nKey;                               // +0x00
    float       f0;                                 // +0x04
    float       f1;                                 // +0x08
    float       f2;                                 // +0x0c
    float       f3;                                 // +0x10
    float       f4;                                 // +0x14
    float       f5;                                 // +0x18
    float       f6;                                 // +0x1c
};

struct cSearchHost {
    int32_t     mnField00;                          // +0x00
    int32_t*    mpTable;                            // +0x04
    int32_t     mnIndex;                            // +0x08

    int32_t*    FindAndInsert(const void* pKey);    // 0x00afc030
    void        FUN_00afb7e0(void* pA, void* pB, int32_t nFlags); // 0x00afb7e0
};

int32_t* cSearchHost::FindAndInsert(const void* pKey)
{
    int32_t aSlot[3];
    FUN_00afb0d0(aSlot, pKey);
    if (aSlot[0] == mpTable[mnIndex]) {
        tInsertArgs aValue;
        aValue.nKey = *(int32_t*)pKey;
        pKey = (const void*)((uint32_t)pKey & 0xFFFFFF00);
        aValue.f0 = 0.0f;
        aValue.f1 = g_fSpace;
        aValue.f2 = g_fSpaceB;
        aValue.f3 = g_fSpaceC;
        aValue.f4 = g_fSpace;
        aValue.f5 = g_fSpaceB;
        aValue.f6 = g_fSpaceC;
        FUN_00afb7e0(aSlot, &aValue, (int32_t)pKey);
    }
    return (int32_t*)(aSlot[0] + 4);
}

// =============================================================================================
// @ 0xafc0d0  erase the slot range [pFirst, pLast) (thiscall, ret 8)
// =============================================================================================
tSlot* cSlotVec::EraseRange(tSlot* pFirst, tSlot* pLast)
{
    tSlot* pNewEnd = (tSlot*)FUN_00afa430(pLast, mpEnd, pFirst);
    if (pNewEnd < mpEnd) {
        int32_t* pi = (int32_t*)((char*)pNewEnd + 4);
        uint32_t n = ((uint32_t)((char*)mpEnd - (char*)pNewEnd) - 1) / 0x18 + 1;
        do {
            if (*pi != 0) {
                int32_t pObj = *pi;
                (*(void(__thiscall**)(int32_t))((char*)*(int32_t*)pObj + 4))(pObj);
            }
            pi = pi + 6;
            n = n - 1;
        } while (n != 0);
    }
    mpEnd += (pLast - pFirst);
    return pFirst;
}

// =============================================================================================
// @ 0xafc150  insert one slot, growing the buffer when full (thiscall, ret 8)
// =============================================================================================
void cSlotVec::InsertOne(tSlot* pPos, tSlot* pValue)
{
    tSlot* pOldEnd = mpEnd;
    if (pOldEnd != mpCap) {
        tSlot* pIns = pValue;
        if (pPos <= pValue && pValue < pOldEnd)
            pIns = (tSlot*)((char*)pValue + 0x18);
        if (pOldEnd != 0)
            ((tSlot*)((char*)pOldEnd - 0x18))->CopyConstruct(*(tSlot*)((char*)pOldEnd - 0x18));
        FUN_00afa4a0(pPos, (char*)pOldEnd - 0x18, pOldEnd);
        pPos->Assign(*pIns);
        mpEnd = (tSlot*)((char*)mpEnd + 0x18);
        return;
    }

    int32_t nCount = (int32_t)((char*)pOldEnd - (char*)mpBegin) / 0x18;
    int32_t nNew;
    tSlot* pNew = 0;
    if (nCount == 0) {
        nNew = 1;
    } else {
        nNew = nCount * 2;
        if (nNew == 0)
            goto alloc_done;
    }
    pNew = (tSlot*)operator_new((uint32_t)(nNew * 0x18), g_szSimulator, 0, 0, g_szAllocFile, 0xd1);
alloc_done:
    tSlot* pB = mpBegin;
    tSlot* pMid = (tSlot*)FUN_00afa380(pB, pPos, pNew);
    FUN_00afa3f0(pB, pPos, pNew);
    if (pMid != 0)
        pMid->CopyConstruct(*pValue);

    tSlot* pOldEnd2 = mpEnd;
    tSlot* pNewEnd = (tSlot*)FUN_00afa380(pPos, pOldEnd2, (char*)pMid + 0x18);
    FUN_00afa3f0(pPos, pOldEnd2, (char*)pMid + 0x18);

    tSlot* pOldBegin = mpBegin;
    if (pOldBegin != 0 && *(int32_t*)((char*)pOldBegin - 4) != 0)
        operator_delete_(pOldBegin);

    mpEnd = pNewEnd;
    mpBegin = pNew;
    mpCap = (tSlot*)((char*)pNew + nNew * 0x18);
}

// =============================================================================================
// @ 0xafc2a0  sift each moved slot then a final heap pass
// =============================================================================================
void __cdecl FUN_00afc2a0(void** pFirst, void** pLast, void** pLast2, tFloat4 v)
{
    FUN_00afbf40((int32_t*)pFirst, (int32_t*)pLast, v);

    for (void** pp = pFirst; pp < pLast; pp++) {
        int32_t nSlot = (int32_t)*pp;
        int32_t nCtx = *(int32_t*)((char*)v.pCtx + 0x50);
        int32_t nSelf = *(int32_t*)pFirst;
        float fDx = v.x - *(float*)(nCtx + 0xc + nSlot * 0x18);
        float fDy = v.y - *(float*)(nCtx + 0x10 + nSlot * 0x18);
        float fDz = v.z - *(float*)(nCtx + 0x14 + nSlot * 0x18);
        float fDist = fDx * fDx + fDz * fDz + fDy * fDy;

        float fSx = v.x - *(float*)(nCtx + 0xc + nSelf * 0x18);
        float fSy = v.y - *(float*)(nCtx + 0x10 + nSelf * 0x18);
        float fSz = v.z - *(float*)(nCtx + 0x14 + nSelf * 0x18);
        float fSelfDist = fSx * fSx + fSz * fSz + fSy * fSy;

        if (fSelfDist > fDist) {
            *pp = (void*)nSelf;
            FUN_00afb8f0((int32_t*)pFirst, 0,
                         ((int32_t)((char*)pLast - (char*)pFirst)) >> 2,
                         0, nSlot, v);
        }
    }
    FUN_00afbfb0((int32_t*)pFirst, (int32_t*)pLast, v);
}

// =============================================================================================
// @ 0xafc410  erase one slot from the +0x50/+0x54 range (thiscall, ret 4)
// =============================================================================================
bool cActionCircle::EraseOne(tSlot* pPos)
{
    tSlot* pBegin = mSlots2.mpBegin;
    tSlot* pEnd = mSlots2.mpEnd;
    bool bResult = false;
    if (pBegin != pEnd) {
        while (pBegin != pPos) {
            pBegin = (tSlot*)((char*)pBegin + 0x18);
            if (pBegin == pEnd)
                return bResult;
        }
        if ((tSlot*)((char*)pBegin + 0x18) < pEnd)
            FUN_00afa430((char*)pBegin + 0x18, pEnd, pBegin);
        mSlots2.mpEnd = (tSlot*)((char*)mSlots2.mpEnd - 0x18);
        void** ppField = (void**)((char*)mSlots2.mpEnd + 4);
        if (*ppField != 0) {
            void* pObj = *ppField;
            (*(void(__thiscall**)(void*))((char*)*(void**)pObj + 4))(pObj);
        }
        bResult = true;
    }
    return bResult;
}

// =============================================================================================
// @ 0xafc470  push_back one object pointer (thiscall, ret 4)
// =============================================================================================
void cPtrVec::PushBack(void** ppValue)
{
    void** p = mpEnd;
    if (p < mpCap) {
        mpEnd = p + 1;
        if (p != 0) {
            void* pObj = *ppValue;
            *p = pObj;
            if (pObj != 0) {
                (*(void(__thiscall**)(void*))((char*)*(void**)pObj + 0xbc))(pObj);
                return;
            }
        }
        return;
    }
    Grow(p, ppValue);
}

// =============================================================================================
// @ 0xafc4b0  find + erase one object pointer (cdecl free helper)
// =============================================================================================
bool __cdecl FUN_00afc4b0(void** pVec, void** ppKey)
{
    void** p = (void**)pVec[0];
    void** pEnd = (void**)pVec[1];
    if (p != pEnd) {
        void* pKey = *ppKey;
        do {
            if (*p == pKey)
                goto found;
            p = p + 1;
        } while (p != pEnd);
    }
    return false;

found:
    if (p + 1 < pEnd)
        FUN_00c83c90(p + 1, pEnd, p);

    pVec[1] = (void*)((char*)pVec[1] - 4);
    void** pLast = (void**)pVec[1];
    if (*pLast != 0) {
        void* pObj = *pLast;
        (*(void(__thiscall**)(void*))((char*)*(void**)pObj + 0xc0))(pObj);
    }
    return true;
}

// =============================================================================================
// @ 0xafc500  intro-sort recursion
// =============================================================================================
void __cdecl FUN_00afc500(int32_t* pFirst, int32_t* pLast, int32_t nLimit, tFloat4 v)
{
    uint32_t nBytes = (uint32_t)((char*)pLast - (char*)pFirst) & 0xFFFFFFFC;
    while ((int32_t)nBytes > 0x70 && nLimit > 0) {
        int32_t nMid = (int32_t)(pLast - pFirst);
        int32_t* pPivot = (int32_t*)FUN_00afb430(
            pFirst,
            pFirst + ((nMid >> 2) - (((nMid >> 2) >> 31))) / 2,
            pLast - 1, v, v);
        int32_t* pMid = (int32_t*)FUN_00afb540(pFirst, pLast, *pPivot);
        nLimit = nLimit - 1;
        FUN_00afc500(pMid, pLast, nLimit, v);
        nBytes = (uint32_t)((char*)pMid - (char*)pFirst) & 0xFFFFFFFC;
        pLast = pMid;
    }
    if (nLimit == 0) {
        FUN_00afc2a0((void**)pFirst, (void**)pLast, (void**)pLast, v);
    }
}

// ---------------------------------------------------------------------------
// Restored by the check-in: byte-exact 00afbde0 from commit 8dd062dbc, dropped when this
// slice was rewritten for its new functions.
// Slice s00afbaf0: teardown of a spatial-object-like class (function 00afbde0). Destroys two element
// vectors at +0x154/+0xf0 and two pointer vectors at +0x140/+0xdc, Dispose()es three refcounted members
// at +0x60/+0x5c/+0x58, frees an EASTL-style hashtable at +0x38, then runs the vector dtor at +0.
// Flags: /O2 /MD /Gy /EHsc /TP
#include "types.h"

extern "C" void __cdecl operator_delete__(void* p);  // 0x00f47380

// Virtual placeholders: slots 0..47 are never called from this function. Dispose is slot 48 (+0xc0).
struct VirtObj {
  virtual void s0();  virtual void s1();  virtual void s2();  virtual void s3();
  virtual void s4();  virtual void s5();  virtual void s6();  virtual void s7();
  virtual void s8();  virtual void s9();  virtual void s10(); virtual void s11();
  virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
  virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
  virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
  virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
  virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
  virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
  virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
  virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
  virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
  virtual void Dispose();  // slot 48
};

struct Elem24Vec {  // 0x00afb090: destroys 0x18-byte elements (VirtObj* at +4, slot 1), frees buffer
  void DtorElems();
};

struct PtrVec {  // 0x00afb7a0: destroys pointer array (VirtObj* elements, slot 23), frees buffer
  void DtorPtrs();
};

struct Hash38 {  // EASTL-style hashtable state at +0x38
  uint32_t mAllocPad;
  void** mpBuckets;         // +0x3c
  uint32_t mnBucketCount;   // +0x40
  uint32_t mnElementCount;  // +0x44
  void FreeChains(void** buckets, uint32_t n);  // 0x00ba2980 (thiscall; ECX=this, ret 8)
};

struct VecAutoRef {  // 0x00ad92d0: eastl::vector<EA::AutoRefCount<SP::cSpatialObject>> dtor
  ~VecAutoRef();
};

struct SpatialTeardown {
  VecAutoRef vec;            // +0x00
  char pad0[0x37];
  Hash38 ht;                 // +0x38
  char pad1[0x10];           // +0x48
  VirtObj* p58;              // +0x58
  VirtObj* p5c;              // +0x5c
  VirtObj* p60;              // +0x60
  char pad2[0x78];           // +0x64
  PtrVec vdc;                // +0xdc
  char pad3[0x13];
  Elem24Vec vf0;             // +0xf0
  char pad4[0x4b];
  char pad5[4];              // +0x13c
  PtrVec v140;               // +0x140
  char pad6[0x13];
  Elem24Vec v154;            // +0x154

  void Teardown();
};

void SpatialTeardown::Teardown() {
  v154.DtorElems();
  v140.DtorPtrs();
  vf0.DtorElems();
  vdc.DtorPtrs();
  VirtObj* q60 = p60;
  if (q60) q60->Dispose();
  VirtObj* q5c = p5c;
  if (q5c) q5c->Dispose();
  VirtObj* q58 = p58;
  if (q58) q58->Dispose();
  Hash38* h = &ht;
  uint32_t n = h->mnBucketCount;
  void** b = h->mpBuckets;
  h->FreeChains(b, n);
  uint32_t c = h->mnBucketCount;
  h->mnElementCount = 0;
  if (c > 1) operator_delete__(h->mpBuckets);
  vec.~VecAutoRef();
}
