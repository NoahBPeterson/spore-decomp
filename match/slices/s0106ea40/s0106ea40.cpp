// Slice s0106ea40 (batch gold6): SP::cSPUISpace tool-strategy / tool-id / text-zoom
// helpers, the eastl Blk28 (0x28-byte refcounted element) vector erase/insert, and the
// per-tool list teardown helpers.
//
// Flags: /O2 /MD /Gy /TP
//
// The stub classes below carry role-named fields at the retail offsets read off the
// disassembly (the migrated headers hold the 2008 dev-PDB layout, which is shifted
// relative to retail).

#include "types.h"

#pragma warning(disable : 4100)

typedef unsigned int  u32;
typedef unsigned char u8;

// ---------------------------------------------------------------------------
// external helpers (addresses are relocation bytes masked by the checker)
// ---------------------------------------------------------------------------
void* operator_new(unsigned size, const char* name, int a, int b, int c, int d);  // 0x00f473a0
void  operator_delete__(void* p);                                                 // 0x00f47380
void* mem_copy(void* dst, const void* src, unsigned n);                           // 0x011e0744

void* SP_GetUFOSimulator();     // 0x00ffbe50
u32   SP_GetPlayerEmpireID();   // 0x01021090

struct UFO {
    u8    pad00[0x70];
    void* mToolList;                        // +0x70
    void* GetToolListPtr();                 // 0x0108db30 (returns this + 0x70)
};

// ---------------------------------------------------------------------------
// generic reference-counted UI interfaces (vtable slots are role-named)
// ---------------------------------------------------------------------------
struct IFace {                              // object whose Release() sits at +4
    virtual void v00();
    virtual void Release4();                // +0x04
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1c();
    virtual void v20();                     // +0x20  reset/clear hook
    virtual void v24();
    virtual void v28();
    virtual void v2c();
    virtual void v30();
    virtual void v34(void* p);              // +0x34  set current element
    virtual void v38();
    virtual void v3c();
    virtual void v40();
    virtual bool v44();                     // +0x44
    virtual void v48();
    virtual void v4c();
    virtual void v50(u32 id);               // +0x50
    virtual void v54();
    virtual void v58();
    virtual int  v5c();                     // +0x5c  count
    virtual void* v60(u32 i);               // +0x60  element
    virtual int  v64(u32 a, void* b);       // +0x64
};

struct IRelease8 {                          // object whose Release() sits at +8
    virtual void v00();
    virtual void v04();
    virtual void Release8();                // +0x08
};

struct IElement {                           // element with a +0xc(unsigned) slot
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c(u32 flag);             // +0x0c
};

struct Uid { u32 m0; u32 m1; u32 m2; };

struct cSPUIGlobalUI {
    void* FindWindowByID(u32 id);           // 0x00e012b0
};

struct cSPUILayout {
    void* FindWindowByID(u32 id, u32 flag); // 0x008105b0
};

struct LayoutSet {
    u8             m00[0x18];
    cSPUILayout**  mpBegin;                 // +0x18
    cSPUILayout**  mpEnd;                   // +0x1c
    u8             m20[0x58];
    int            Count();                 // 0x00e09c80
    cSPUILayout*   At(int i);               // 0x00e09c90
};

struct cWindow {
    void FUN_00e30ae0(u32 id);                              // 0x00e30ae0
    void FUN_00e31030(u32 a, u32 b, u32 c, u32 d);          // 0x00e31030
};

// window handle returned by cSPUILayout::FindWindowByID
// (query slot at +0x0c, set-id slot at +0x50)
struct cUIWindow {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void* QueryIn(const Uid& uid, u32 a, u32 b, u32 c, u32 d);  // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void SetId(u32 id);                                          // +0x50
};

// ---------------------------------------------------------------------------
// UI::TextZoomName -- 0x78-byte refcounted zoom helper
// ---------------------------------------------------------------------------
struct cTextZoomName {
    virtual void v00();
    virtual void AddRef();                  // +0x04
    virtual void Release();                 // +0x08
    virtual void* Query(const Uid& uid, u32 a, u32 b, u32 c, u32 d);   // +0x0c
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
    virtual void v50(u32 id);               // +0x50

    void Shutdown();                        // 0x00834e30
    void SetTargetWindow(void* w);          // 0x00834fa0
    cTextZoomName* Construct();             // 0x008345c0
};

// ---------------------------------------------------------------------------
// the eastl list<int>-like circular tool list (0xc-byte nodes: next/prev/value)
// ---------------------------------------------------------------------------
struct Node {
    Node* mpNext;       // +0x00
    Node* mpPrev;       // +0x04
    u32   mValue;       // +0x08
};

struct ToolList {
    Node* mpHead;       // +0x00  (sentinel next, points at itself when empty)
    Node* mpTail;       // +0x04  (sentinel prev)

    ToolList() { Node* s = (Node*)this; s->mpNext = s; s->mpPrev = s; }
    void assign(const ToolList& self, Node* first, Node* last, u32 flags);  // 0x0106b950
    void pushBack(const u32& v);                                           // 0x00c58360
    void destroy();                                                        // 0x00700f90
};

// ---------------------------------------------------------------------------
// eastl hashtable (u32 key -> value) -- mpBuckets has mnBuckets + 1 entries
// ---------------------------------------------------------------------------
struct HashNode;
struct HashIter {
    HashNode*  mpNode;      // +0x00
    HashNode** mpBucket;    // +0x04
};

struct HashTable {
    u32         m00;            // +0x00
    HashNode**  mpBuckets;      // +0x04
    u32         mnBuckets;      // +0x08
    u32         mnElements;     // +0x0c

    void find(HashIter* out, const u32& key);       // 0x00645ed0
    void begin(HashIter* out);                      // 0x00594410
    u32* insertEntry(const u32& key);               // 0x00b474c0
    HashIter erase(HashIter pos);                   // 0x01068380
    void freeNodes(HashNode** buckets, u32 n);      // 0x00961d60
    void freeBuckets(HashNode** buckets, u32 n);    // 0x00693230
};

struct HashNode {
    u32        mKey;        // +0x00
    u32        mValue;      // +0x04
    HashNode*  mpNext;      // +0x08
};

// ---------------------------------------------------------------------------
// eastl Blk28 (0x28-byte refcounted element) vector
// ---------------------------------------------------------------------------
struct RefObj { virtual void AddRef(); virtual void Release(); };            // Release at +4
struct ObjRel { virtual void v0(); virtual void v1(); virtual void Release(); };  // Release at +8

struct Blk28 {
    RefObj* mpRef;      // +0x00
    u32     m04;        // +0x04
    ObjRel* m08;        // +0x08
    u32     m0c;
    u32     m10;
    u32     m14;
    u32     m18;
    u8      m1c;
    u8      mPad[3];
    u32     m20;
    u32     m24;

    Blk28* CopyCtor(const Blk28& src);      // 0x01068450
};

// Blk28 range helpers (free functions, resolved by address)
Blk28*  Blk28_copy_b(Blk28* begin, Blk28* end, Blk28* dst);             // 0x01068610
void    Blk28_reloc_b(Blk28* begin, Blk28* end, Blk28* dst);            // 0x01068690
void    Blk28_fill3(Blk28* dst, u32 count, const Blk28* src);           // 0x01068530 (3 args)
void    Blk28_fill4(Blk28* dst, u32 count, const Blk28* src, Blk28* x);  // 0x01068530 (4 args)
Blk28** Blk28_ccopy(Blk28** out, Blk28* begin, Blk28* end, Blk28* dst);  // 0x010684b0
Blk28*  Blk28_mback(Blk28* begin, Blk28* end, Blk28* dst);              // 0x01068710
void    Blk28_assignr(Blk28* begin, Blk28* end, const Blk28* src);      // 0x0106cc40
Blk28*  Blk28_mvassign(Blk28* a, Blk28* b, Blk28* c);                   // 0x010686d0

struct Blk28Vec {
    Blk28* mpBegin;
    Blk28* mpEnd;
    Blk28* mpCap;

    Blk28* erase(Blk28* first, Blk28* last);                 // 0x0106eb40
    Blk28* insert(Blk28* pos, u32 n, const Blk28& value);    // 0x0106ebb0
};

// ---------------------------------------------------------------------------
// pointer / u32 vectors
// ---------------------------------------------------------------------------
inline void* MoveRange(void* dst, const void* first, const void* last) {
    return mem_copy(dst, first, (unsigned)((const char*)last - (const char*)first));
}

struct U32Vec3 {
    u32* mpBegin;
    u32* mpEnd;
    u32* mpCap;

    void clear() {
        u32* p = mpEnd;
        MoveRange(mpBegin, p, p);
        mpEnd -= (mpEnd - mpBegin);
    }
    void DoInsertValueI(u32* pos, const u32& value);        // 0x004558a0
};

struct U32Vec2 {
    u32* mpBegin;
    u32* mpEnd;
};

struct PtrVec {
    void** mpBegin;
    void** mpEnd;
    void** mpCap;

    void** eraseA(void** first, void** last);      // 0x00533500
    void** eraseB(void** first, void** last);      // 0x005c2170
    void** insertEntry(void** pos, void** value);  // 0x00f14270
};

// ---------------------------------------------------------------------------
// generic tool item (vtable slot +0x44) with an embedded helper at +0x0c
// ---------------------------------------------------------------------------
struct Sub0c {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void* v0c(u32 key);   // +0x0c
    u32 m10;                      // +0x10
};

struct SpItemVtbl {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
    virtual void v40();
    virtual bool v44();           // +0x44
};

struct SpItem : SpItemVtbl {
    u8     mPad04[8];             // +0x04 .. +0x0b
    Sub0c  mSub;                  // +0x0c
    u32    mFlag;                 // +0x14
};

struct B8F860 { int  Get(); };      // 0x00b8f860
struct AC0C50 { bool Test(); };     // 0x00ac0c50

// ---------------------------------------------------------------------------
// SP::cSPUISpace
// ---------------------------------------------------------------------------
class cSPUISpace {
public:
    u8              m000[0x224];                 // +0x000
    cSPUIGlobalUI*  mpGlobalUI;                  // +0x224
    u8              m228[0x10];                  // +0x228
    IFace*          mpToolList;                  // +0x238
    u32             m23c;                        // +0x23c
    U32Vec3         mIds;                        // +0x240
    u8              m24c[0x8];                   // +0x24c
    IRelease8*      mp254;                       // +0x254
    u8              m258[0x4];                   // +0x258
    HashTable       mToolTable;                  // +0x25c
    u8              m26c[0x10];                  // +0x26c
    U32Vec3         mSortedIds;                  // +0x27c
    u8              m288[0xc];                   // +0x288
    IFace*          mp294;                       // +0x294
    IFace*          mp298;                       // +0x298
    IFace*          mp29c;                       // +0x29c
    u8              m2a0[0x20];                  // +0x2a0
    U32Vec3         mIds2c0;                     // +0x2c0
    u8              m2cc[0x8];                   // +0x2cc
    HashTable       mStrategyTable;              // +0x2d4
    u8              m2e4[0x10];                  // +0x2e4
    u32             m2f4;                        // +0x2f4
    u8              m2f8[0x10];                  // +0x2f8
    PtrVec          mVec308;                     // +0x308
    u8              m314[0x2c1];                 // +0x314
    u8              m5d5;                        // +0x5d5
    u8              m5d6[0x2];                   // +0x5d6
    U32Vec2         mIdArray;                    // +0x5d8
    u8              m5e0[0x3c];                  // +0x5e0
    cWindow*        mpWindow61c;                 // +0x61c
    LayoutSet       mLayoutSet;                  // +0x620
    PtrVec          mZoomVec;                    // +0x698

    void        FUN_0106ea40(u32 index);                  // 0x0106ea40
    u32         FUN_0106edc0(u32 key);                    // 0x0106edc0
    void        FUN_0106ef30();                           // 0x0106ef30
    void        FUN_0106f120(u32 id);                     // 0x0106f120
    void        FUN_0106f160(u32 id);                     // 0x0106f160
    void        FUN_0106f1a0(int param_2, char param_3);  // 0x0106f1a0
    void        FUN_0106f380();                           // 0x0106f380
    void        FUN_0106f3d0();                           // 0x0106f3d0
    void        FUN_0106f540();                           // 0x0106f540
    void        FUN_0106dd10(u32 index, u32 value);       // 0x0106dd10
    void        FUN_0106e680(u32 id);                     // 0x0106e680
    void        ToggleToolUI(u32 id);                     // 0x0106e3e0
};

// ---------------------------------------------------------------------------
// cSPUISpace tool list construction
// ---------------------------------------------------------------------------
// @ 0x0106ea40
void cSPUISpace::FUN_0106ea40(u32 index)
{
    if (index >= 3)
        return;
    if ((int)index >= (int)(mIdArray.mpEnd - mIdArray.mpBegin))
        return;

    u32* pValue = &mIdArray.mpBegin[index];

    UFO* ufo = (UFO*)SP_GetUFOSimulator();
    ToolList* src = (ToolList*)ufo->GetToolListPtr();

    ToolList lst;
    lst.assign(lst, src->mpHead, (Node*)src, 0);

    u32 empire = SP_GetPlayerEmpireID();
    lst.pushBack(empire);

    Node* head = lst.mpHead;
    Node* p = head;
    while (p != (Node*)&lst) {
        if (p->mValue == *pValue)
            break;
        p = p->mpNext;
    }
    if (p != (Node*)&lst) {
        if (p->mValue == head->mValue)
            *pValue = lst.mpTail->mValue;
        else
            *pValue = p->mpPrev->mValue;
        FUN_0106dd10(index, *pValue);
    }
    lst.destroy();
}

// ---------------------------------------------------------------------------
// Blk28 vector erase / insert
// ---------------------------------------------------------------------------
// @ 0x0106eb40
Blk28* Blk28Vec::erase(Blk28* first, Blk28* last)
{
    Blk28* p = Blk28_mvassign(last, mpEnd, first);
    Blk28* end = mpEnd;
    while (p < end) {
        if (p->mpRef != 0)
            p->mpRef->Release();
        p += 1;
    }
    mpEnd += last - first;
    return first;
}

// @ 0x0106ebb0
Blk28* Blk28Vec::insert(Blk28* position, u32 n, const Blk28& value)
{
    if ((u32)(mpCap - mpEnd) < n) {
        u32 size = (u32)(mpEnd - mpBegin);
        u32 newCap = size + n;
        u32 doubled = size * 2;
        if (doubled == 0)
            doubled = 1;
        if (doubled > newCap)
            newCap = doubled;
        Blk28* newBegin = 0;
        if (newCap != 0)
            newBegin = (Blk28*)operator_new(newCap * 0x28, "Simulator", 0, 0, 0, 0xd1);
        Blk28* dst1 = Blk28_copy_b(mpBegin, position, newBegin);
        Blk28_reloc_b(mpBegin, position, dst1);
        Blk28_fill4(dst1, n, &value, dst1);
        Blk28* dst2 = dst1 + n;
        Blk28* dst3 = Blk28_copy_b(position, mpEnd, dst2);
        Blk28_reloc_b(position, mpEnd, dst3);
        if (mpBegin != 0 && ((int*)mpBegin)[-1] != 0)
            operator_delete__(mpBegin);
        mpBegin = newBegin;
        mpEnd = dst3;
        mpCap = newBegin + newCap;
    } else if (n != 0) {
        Blk28 temp;
        temp.CopyCtor(value);
        Blk28* oldEnd = mpEnd;
        u32 after = (u32)(mpEnd - position);
        if (n < after) {
            Blk28* srcEnd = oldEnd - n;
            Blk28* dstEnd;
            Blk28_ccopy(&dstEnd, srcEnd, oldEnd, oldEnd);
            mpEnd += n;
            Blk28_mback(position, srcEnd, oldEnd);
            Blk28_assignr(position, position + n, &temp);
        } else {
            Blk28_fill3(oldEnd, n - after, &temp);
            mpEnd += n - after;
            Blk28* dstEnd;
            Blk28_ccopy(&dstEnd, position, oldEnd, mpEnd);
            Blk28_assignr(position, oldEnd, &temp);
        }
        if (temp.mpRef != 0)
            temp.mpRef->Release();
    }
    return position;
}

// ---------------------------------------------------------------------------
// strategy-id lookup / creation
// ---------------------------------------------------------------------------
// @ 0x0106edc0
u32 cSPUISpace::FUN_0106edc0(u32 key)
{
    HashIter it;
    mStrategyTable.find(&it, key);
    if (mStrategyTable.mpBuckets[mStrategyTable.mnBuckets] != it.mpNode)
        return it.mpNode->mValue;

    u32 n = m2f4;
    if (n != 0x68e0310) {
        m2f4 = n + 1;
        *mStrategyTable.insertEntry(key) = n;
        return n;
    }

    if (mIds2c0.mpBegin == mIds2c0.mpEnd) {
        HashIter cur;
        mToolTable.begin(&cur);
        while (cur.mpNode != mToolTable.mpBuckets[mToolTable.mnBuckets]) {
            u32 v = cur.mpNode->mValue;
            if (mpGlobalUI->FindWindowByID(v) == 0) {
                cur = mToolTable.erase(cur);
                if (mIds2c0.mpEnd < mIds2c0.mpCap) {
                    u32* slot = mIds2c0.mpEnd++;
                    if (slot != 0)
                        *slot = v;
                } else {
                    mIds2c0.DoInsertValueI(mIds2c0.mpEnd, v);
                }
            } else {
                cur.mpNode = cur.mpNode->mpNext;
                while (cur.mpNode == 0) {
                    ++cur.mpBucket;
                    cur.mpNode = *cur.mpBucket;
                }
            }
        }
    }

    if (mIds2c0.mpBegin != mIds2c0.mpEnd) {
        u32 v = mIds2c0.mpEnd[-1];
        mIds2c0.mpEnd -= 1;
        *mStrategyTable.insertEntry(key) = v;
        return v;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// full tool-strategy teardown
// ---------------------------------------------------------------------------
// @ 0x0106ef30
void cSPUISpace::FUN_0106ef30()
{
    {
        HashIter it;
        it.mpBucket = mToolTable.mpBuckets;
        it.mpNode = *it.mpBucket;
        while (it.mpNode == 0) {
            ++it.mpBucket;
            it.mpNode = *it.mpBucket;
        }
        HashNode* end = mToolTable.mpBuckets[mToolTable.mnBuckets];
        while (it.mpNode != end) {
            ((IFace*)it.mpNode->mValue)->v20();
            it.mpNode = it.mpNode->mpNext;
            while (it.mpNode == 0) {
                ++it.mpBucket;
                it.mpNode = *it.mpBucket;
            }
        }
    }

    if (mp294 != 0) {
        IFace* p = mp294;
        mp294 = 0;
        p->Release4();
    }
    if (mp298 != 0)
        mp298->v20();
    if (IFace* p = mp298) {
        mp298 = 0;
        p->Release4();
    }
    if (mp29c != 0)
        mp29c->v20();
    if (IFace* p = mp29c) {
        mp29c = 0;
        p->Release4();
    }
    if (IFace* p = mpToolList) {
        mpToolList = 0;
        p->Release4();
    }
    m23c = 0;

    mIds.clear();
    mToolTable.freeNodes(mToolTable.mpBuckets, mToolTable.mnBuckets);
    mToolTable.mnElements = 0;
    mSortedIds.clear();
    mIds2c0.clear();

    mStrategyTable.freeBuckets(mStrategyTable.mpBuckets, mStrategyTable.mnBuckets);
    mStrategyTable.mnElements = 0;
    m2f4 = 0x68e0210;

    IRelease8* p = mp254;
    if (p != 0) {
        mp254 = 0;
        p->Release8();
    }
}

// ---------------------------------------------------------------------------
// per-id tool refresh
// ---------------------------------------------------------------------------
// @ 0x0106f120
void cSPUISpace::FUN_0106f120(u32 id)
{
    if (m5d5 != 0) {
        FUN_0106e680(id);
        cWindow* w = mpWindow61c;
        w->FUN_00e31030(FUN_0106edc0(id), 0x622c8f6, 0, 0);
    }
}

// @ 0x0106f160
void cSPUISpace::FUN_0106f160(u32 id)
{
    if (m5d5 != 0) {
        FUN_0106e680(id);
        cWindow* w = mpWindow61c;
        w->FUN_00e31030(FUN_0106edc0(id), 0x651886d, 0, 0x5f72e19);
    }
}

// ---------------------------------------------------------------------------
// tool-item activation
// ---------------------------------------------------------------------------
// @ 0x0106f1a0
void cSPUISpace::FUN_0106f1a0(int param_2, char param_3)
{
    if (param_3 != 0)
        ToggleToolUI(0xb0000016);

    if (m23c != 0xb0000016)
        return;

    u32 flag = (*(int*)((char*)param_2 + 0x10) != 0) ? 1 : 0;
    int kind = *(int*)((char*)param_2 + 0x18);

    if (kind == 0) {
        int r = mpToolList->v64(flag, (void*)((char*)param_2 + 4));
        if (r <= 0)
            return;
        mpWindow61c->FUN_00e30ae0(0x622c9ce);
        void* item = mpToolList->v60((u32)r);
        mp294->v34(item);
        mpWindow61c->FUN_00e31030(FUN_0106edc0((u32)item), 0x622c9ce, 0, 0);
        return;
    }
    if (kind != 3)
        return;

    mpWindow61c->FUN_00e30ae0(0x622c9ce);
    char first = 1;
    int count = mpToolList->v5c();
    if (count <= 0)
        return;

    int i = 0;
    for (;;) {
        SpItem* item = (SpItem*)mpToolList->v60((u32)i);
        if (item->mFlag == flag && !item->v44()) {
            void* a = item->mSub.v0c(0x70a2863c);
            void* b = item->mSub.v0c(0x30fc270b);
            int sel = *(int*)((char*)param_2 + 0x10);
            bool hit = false;
            if (sel == 0)
                hit = (((B8F860*)a)->Get() == *(int*)((char*)param_2 + 0x14));
            else if (sel == 1)
                hit = !((AC0C50*)b)->Test();
            else if (sel == 2)
                hit = ((AC0C50*)b)->Test();
            if (hit) {
                if (first) {
                    mp294->v34(item);
                    first = 0;
                }
                mpWindow61c->FUN_00e31030(FUN_0106edc0((u32)item), 0x622c9ce, 0, 0);
            }
        }
        ++i;
        if (i >= count)
            return;
    }
}

// ---------------------------------------------------------------------------
// pending-tool list teardown (u32 slots, elements released at +0xc)
// ---------------------------------------------------------------------------
// @ 0x0106f380
void cSPUISpace::FUN_0106f380()
{
    PtrVec& v = mVec308;
    u32 n = (u32)(v.mpEnd - v.mpBegin);
    u32 i = 0;
    while (i < n) {
        ((IElement*)v.mpBegin[i])->v0c(1);
        ++i;
    }
    v.eraseA(v.mpBegin, v.mpEnd);
}

// ---------------------------------------------------------------------------
// text-zoom rebuild
// ---------------------------------------------------------------------------
// @ 0x0106f3d0
void cSPUISpace::FUN_0106f3d0()
{
    int n = (int)(mZoomVec.mpEnd - mZoomVec.mpBegin);
    for (int i = 0; i < n; ++i) {
        cTextZoomName* p = (cTextZoomName*)mZoomVec.mpBegin[i];
        if (p != 0)
            p->Shutdown();
    }
    mZoomVec.eraseB(mZoomVec.mpBegin, mZoomVec.mpEnd);

    LayoutSet* ls = &mLayoutSet;
    int count = ls->Count();
    for (int i = 0; i < count; ++i) {
        cSPUILayout* lay = ls->At(i);
        if (lay == 0)
            continue;

        cTextZoomName* t = (cTextZoomName*)operator_new(0x78, "UI/cSPUITextZoom", 0, 0, 0, 0);
        if (t == 0) {
            t = 0;
        } else {
            t = t->Construct();
        }

        cTextZoomName* local = t;
        if (local != 0)
            local->AddRef();

        if (mZoomVec.mpEnd < mZoomVec.mpCap) {
            void** slot = mZoomVec.mpEnd++;
            if (slot != 0) {
                *slot = local;
                if (local != 0)
                    local->AddRef();
            }
        } else {
            mZoomVec.insertEntry(mZoomVec.mpEnd, (void**)&local);
        }
        if (local != 0)
            local->Release();

        cUIWindow* win = (cUIWindow*)lay->FindWindowByID(0x7edb1e8, 1);
        if (win != 0) {
            win->SetId(0x7edb1e8 + (u32)i);
            Uid uid;
            uid.m0 = 0;
            uid.m1 = 0;
            uid.m2 = 0;
            void* w2 = win->QueryIn(uid, 0, 0, 0, 0xf15f4bd);
            ((cTextZoomName*)mZoomVec.mpBegin[i])->SetTargetWindow(w2);
        }
    }
}

// ---------------------------------------------------------------------------
// text-zoom teardown
// ---------------------------------------------------------------------------
// @ 0x0106f540
void cSPUISpace::FUN_0106f540()
{
    PtrVec& v = mZoomVec;
    int n = (int)(v.mpEnd - v.mpBegin);
    for (int i = 0; i < n; ++i) {
        if (v.mpBegin[i] != 0) {
            ((cTextZoomName*)v.mpBegin[i])->Shutdown();
            if (v.mpBegin[i] != 0) {
                cTextZoomName* p = (cTextZoomName*)v.mpBegin[i];
                v.mpBegin[i] = 0;
                p->Release();
            }
        }
    }
    v.eraseB(v.mpBegin, v.mpEnd);
}