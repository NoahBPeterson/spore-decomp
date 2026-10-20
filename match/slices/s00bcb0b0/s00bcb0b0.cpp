// Slice s00bcb0b0 -- the Simulator "list" var-list editor (0x668-byte object built
// around a fixed-size entry array + two eastl intrusive lists) and the
// Simulator::cAnimalTrap noun methods that follow it.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-  (no /EHsc: the string locals get no
// unwind frame; the 0xaac-byte frame of 0x00bcb730 has no /GS cookie).
#include "types.h"
#include <math.h>
#include <intrin.h>

typedef unsigned short char16;

// ---- runtime / allocator --------------------------------------------------------------
extern "C" void  __cdecl operator_delete(void* p);                                  // 0x00f47380
extern "C" void* __cdecl operator_new__(void* dst, int count, unsigned size);       // 0x011e073e
void* __cdecl operator_new(unsigned size, const char* file, int line, int, const char*, int); // 0x00f473a0
void* wrapper_alloc(unsigned size, void* p);                                        // 0x006abeb0
void  wrapper_free(void* p);                                                        // 0x00f47410

// ---- eastl string (12 bytes: begin/end/capacity; empty allocator base) ----------------
extern const char16 gEmptyString16[1];                                              // 0x01667bac

struct string16 {
    char16* mpBegin;
    char16* mpEnd;
    char16* mpCapacity;
    string16() : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(0); }
    string16(const string16& o);
    ~string16() {
        if ((mpCapacity - mpBegin) > 1) {
            if (mpBegin) operator_delete(mpBegin);
        }
    }
    void RangeInitialize(const char16* p);                                          // 0x00579a90
    const char16* c_str() const { return mpBegin; }
    bool empty() const { return mpBegin == mpEnd; }
};
string16 __cdecl ConvertToString16(const char* in, int n);                          // 0x0093c5a0

// ---- fixed allocator (EA::Allocator::FixedAllocatorBase, 0x20 bytes) ------------------
struct FixedAllocatorBase {
    uint32_t mFields[8];
    FixedAllocatorBase(unsigned objectSize, unsigned alignment, unsigned objectCount,
                       unsigned a, int b, void* pfnAlloc, void* pfnFree,
                       const char* pszName);                                    // 0x00926720
    ~FixedAllocatorBase();                                                      // 0x00926640
    bool AddCore(void* p, unsigned n);                                          // 0x00926650
};
void* FixedAllocatorBase_AddCore(FixedAllocatorBase* p, void* a, unsigned b);   // 0x00926650

// ---- the var-list entry (0x22c bytes, vtable 0x01466998) -----------------------------
typedef void (__thiscall* FnThis0)(void*);
typedef void* (__thiscall* FnThisP)(void*);

struct ListEntry {
    void** vptr;                // +0x000
    uint32_t m04;               // +0x004
    const char* mpName;         // +0x008
    uint32_t m0c;               // +0x00c
    uint32_t m10;               // +0x010
    uint32_t m14;               // +0x014
    uint32_t mValue;            // +0x018
    uint8_t m1c;                // +0x01c
    uint32_t m20[0x180 / 4];    // +0x020
    uint32_t m1a0;              // +0x1a0
    uint32_t m1a4[0x80 / 4];    // +0x1a4
    uint32_t m224;              // +0x224
    uint32_t m228;              // +0x228
    void Construct(void* record);                                               // 0x00bcab80
};

struct ListNode {               // 0x234 bytes
    ListNode* mpNext;           // +0x000
    ListNode* mpPrev;           // +0x004
    ListEntry mEntry;           // +0x008
};

struct RawList {                // 0x28 bytes: sentinel + embedded FixedAllocatorBase
    ListNode* mpNext;           // +0x00
    ListNode* mpPrev;           // +0x04
    FixedAllocatorBase mAlloc;  // +0x08
    void Clear();                                                               // 0x00bcaa00
    ListNode* AllocNode();                                                      // 0x00bcaab0
    void ConstructNode(ListEntry* p);                                           // 0x00bcab80
    RawList* Construct();                                                       // 0x00bcb590
    ListEntry* Insert(const char* name, unsigned typeId, int value, int flags); // 0x00bcb0b0
};

// clamp that keeps a reference to the selected operand (5 bytes: pointer select)
template <class T> const T& ClampRef(const T& v, const T& lo, const T& hi)
{
    return v < lo ? lo : (v >= hi ? hi : v);
}
template <class T> const T& MaxRef(const T& a, const T& b) { return a < b ? b : a; }
template <class T> const T& MinRef(const T& a, const T& b) { return a < b ? a : b; }

// ---- 16-byte element of the editor's flat array --------------------------------------
struct Quad16 {
    int mIndex;                 // +0x00
    uint32_t mPad;              // +0x04
    double mValue;              // +0x08
};
void* __cdecl copy_705250(void* dst, const void* first, const void* last);      // 0x00705250
struct QuadVec {                // lives at editor +0x5e8
    Quad16* mpBegin;            // +0x00
    Quad16* mpEnd;              // +0x04
    Quad16* mpCap;              // +0x08
    void SetArraySize(unsigned count);                                          // 0x00bcb5f0
    void DoInsertN(Quad16* pos, unsigned n, const Quad16* value);               // 0x00bcacf0
};

// ---- the 0x668-byte editor object -----------------------------------------------------
struct SelEntry {
    uint8_t mUsed;              // +0x00
    uint32_t mA;                // +0x04
    uint32_t mB;                // +0x08
};
struct SelItem {
    void** vptr;                // +0x00
    uint32_t m04;               // +0x04
    uint32_t m08;               // +0x08
    uint32_t m0c;               // +0x0c
    int mUsedCount;             // +0x10
    uint32_t m14;               // +0x14
    uint32_t mCount;            // +0x18
    uint32_t m1c;               // +0x1c
    SelEntry mEntries[1];       // +0x20
};
struct VarSource {              // object assigned to the editor (count at +0x24)
    uint32_t m00[9];            // +0x00..+0x23
    uint32_t mCount;            // +0x24
};

struct cVarListEditor {
    void* mpObject;                 // +0x000
    uint32_t m04;                   // +0x004
    uint32_t mElems[8 * 0x38 / 4];  // +0x008  (8 x 0x38-byte blocks)
    uint32_t mElemTail[2];          // +0x1c8
    uint32_t mSub1[0x418 / 4];      // +0x1d0
    Quad16* mpVecBegin;             // +0x5e8
    Quad16* mpVecEnd;               // +0x5ec
    Quad16* mpVecCap;               // +0x5f0
    uint32_t m5f4;                  // +0x5f4
    uint32_t m5f8;                  // +0x5f8
    void* mp5fc;                    // +0x5fc
    SelItem* mpSelected;            // +0x600
    int mIndex;                     // +0x604
    void* mpItem;                   // +0x608
    RawList mList1;                 // +0x60c
    RawList mList2;                 // +0x634
    string16 mName;                 // +0x65c

    ListEntry* Insert(const char* name, unsigned typeId, int value, int flags); // 0x00bcb0b0
    cVarListEditor* Construct();                                                // 0x00bcb2a0
    void Reset();                                                               // 0x00bcb3d0
    void ClearSelection();                                                      // 0x00bcb430
    void SetSelection(SelItem* item, int a, int b, void* c);                    // 0x00bcb480
    int  SelectByName(const char* name, int a, const char* c);                  // 0x00bcb510
    void SetListObject(VarSource* item);                                        // 0x00bcb660
    void RemoveItem(SelItem* item, int index);                                  // 0x00bcafe0
    SelItem* FindItem(uint32_t key0, void* key, const char* name);              // 0x00bca620
};

extern cVarListEditor* g_pVarListEditor;                                        // 0x0168b56c

struct ElemOps { void Clear(); void Alloc(); };
bool __cdecl WriteListElement(void* writer, int a, ListEntry* e);               // 0x00ac8050
bool __cdecl WriteListProperty(void* writer, const char* name, RawList* list);  // 0x00bcb160

// @ 0x00bcb0b0
ListEntry* RawList::Insert(const char* name, unsigned typeId, int value, int flags)
{
    ListNode* node = AllocNode();
    node->mpNext = (ListNode*)this;
    node->mpPrev = mpPrev;
    mpPrev->mpNext = node;
    mpPrev = node;
    ListEntry* e = &node->mEntry;
    ((FnThis0)(*(void***)e)[1])(e);
    e->mpName = name;
    e->m0c = (uint32_t)value;
    e->m10 = 0;
    e->m14 = 0;
    const uint32_t& clamped = MinRef(MaxRef(typeId, 1u), 0x20u);
    e->mValue = clamped;
    operator_new__((char*)e + 0x20, 0, 0x180);
    operator_new__((char*)e + 0x1a4, 0, 0x80);
    return e;
}

// @ 0x00bcb160
bool __cdecl WriteListProperty(void* writer, const char* name, RawList* list)
{
    bool ok = true;
    if (list->mpNext != (ListNode*)list) {
        string16 s = name ? ConvertToString16(name, -1) : string16();
        const char16* label = s.empty() ? (const char16*)L"list" : s.mpBegin;
        ((void (__thiscall*)(void*, const char16*))(*(void***)writer)[0])(writer, label);
        for (ListNode* n = list->mpNext; n != (ListNode*)list; n = n->mpNext)
            ok = ok && WriteListElement(writer, 0, &n->mEntry);
        ((void (__thiscall*)(void*, const char16*))(*(void***)writer)[1])(writer, label);
    }
    return ok;
}

// @ 0x00bcb2a0
cVarListEditor* cVarListEditor::Construct()
{
    mpObject = 0;
    for (int i = 0; i < 8; i++)
        mElems[i * 0x38 / 4 + 0x2c / 4] = 0;
    ((ElemOps*)&mElems[0])->Clear();
    ((ElemOps*)mSub1)->Alloc();

    mpVecBegin = 0;
    mpVecEnd = 0;
    mpVecCap = 0;
    mp5fc = 0;
    mpSelected = 0;
    mIndex = -1;
    mpItem = 0;

    {
        FixedAllocatorBase a(0x98, 8, 1, 0, -1, (void*)&wrapper_alloc, (void*)&wrapper_free, "Simulator/list");
        mList1.mAlloc = a;
        mList1.mpNext = (ListNode*)&mList1;
        mList1.mpPrev = (ListNode*)&mList1;
    }
    {
        FixedAllocatorBase a(0x28, 4, 8, 0, -1, (void*)&wrapper_alloc, (void*)&wrapper_free, "Simulator/list");
        mList2.mAlloc = a;
        mList2.mpNext = (ListNode*)&mList2;
        mList2.mpPrev = (ListNode*)&mList2;
    }
    mName.mpBegin = (char16*)gEmptyString16;
    mName.mpEnd = (char16*)gEmptyString16;
    mName.mpCapacity = (char16*)gEmptyString16 + 1;
    return this;
}

// @ 0x00bcb3d0
void cVarListEditor::Reset()
{
    ((ElemOps*)mSub1)->Alloc();
    ((ElemOps*)&mElems[0])->Clear();
    Quad16* begin = mpVecBegin;
    Quad16* end = mpVecEnd;
    copy_705250(end, end, begin);
    mpVecEnd = (Quad16*)((char*)mpVecEnd + (((char*)end - (char*)begin) >> 4) * -16);
    mpObject = 0;
    RawList* list = &mList1;
    list->Clear();
    list->mpNext = (ListNode*)list;
    list->mpPrev = (ListNode*)list;
}

// @ 0x00bcb430
void cVarListEditor::ClearSelection()
{
    SelItem* p = mpSelected;
    if (p) {
        mpSelected = 0;
        ((FnThis0)(*(void***)p)[2])(p);
    }
    g_pVarListEditor->RemoveItem(p, mIndex);
    mIndex = -1;
}

// @ 0x00bcb480
void cVarListEditor::SetSelection(SelItem* item, int a, int b, void* c)
{
    if (mpSelected) {
        if (mpSelected == item)
            return;
        ClearSelection();
    }
    unsigned i = 0;
    if (item->mCount > 0) {
        SelEntry* e = item->mEntries;
        do {
            if (!e->mUsed) {
                e->mA = (uint32_t)a;
                e->mUsed = 1;
                e->mB = (uint32_t)b;
                item->mUsedCount++;
                goto haveIndex;
            }
            i++;
            e++;
        } while (i < item->mCount);
    }
    i = 0;
haveIndex:
    mIndex = (int)i;
    _ReadWriteBarrier();
    SelItem* old = mpSelected;
    if (item != old) {
        ((FnThis0)(*(void***)item)[1])(item);
        mpSelected = item;
        if (old)
            ((FnThis0)(*(void***)old)[2])(old);
    }
    mpItem = c;
}

// @ 0x00bcb510
int cVarListEditor::SelectByName(const char* name, int a, const char* c)
{
    SelItem* sel = mpSelected;
    if (mpItem && sel) {
        const char* key = c ? c : name;
        SelItem* found = g_pVarListEditor->FindItem(sel->m08, mpItem, key);
        if (found) {
            if (found != mpSelected)
                SetSelection(found, (int)name, a, mpItem);
            if (found != sel)
                return true;
        }
    }
    return false;
}

// @ 0x00bcb590
RawList* RawList::Construct()
{
    FixedAllocatorBase a(0x234, 4, 0x20, 0, -1, (void*)&wrapper_alloc, (void*)&wrapper_free, "Simulator/list");
    mAlloc = a;
    mpNext = (ListNode*)this;
    mpPrev = (ListNode*)this;
    return this;
}

// @ 0x00bcb5f0
void QuadVec::SetArraySize(unsigned count)
{
    Quad16* end = mpEnd;
    Quad16* begin = mpBegin;
    unsigned n = (unsigned)(end - begin);
    if (count > n) {
        Quad16 v;
        v.mIndex = -1;
        v.mValue = 0.0;
        DoInsertN(end, count - n, &v);
        return;
    }
    Quad16* p = begin + count;
    copy_705250(end, end, p);
    int back = (int)((char*)end - (char*)p) >> 4;
    back = -back;
    mpEnd = (Quad16*)((char*)mpEnd + back * 16);
}

// @ 0x00bcb660
void cVarListEditor::SetListObject(VarSource* item)
{
    if (mpObject)
        Reset();
    mpObject = item;
    if (item) {
        QuadVec* vec = (QuadVec*)&mpVecBegin;
        vec->SetArraySize(item->mCount);
        for (unsigned i = 0; i < item->mCount; i++) {
            Quad16* e = &mpVecBegin[i];
            e->mValue = 0.0;
            e->mIndex = -1;
        }
    }
}

// @ 0x00bcb700
void __cdecl DestroyVarList()
{
    cVarListEditor* p = g_pVarListEditor;
    if (p) {
        ((RawList*)p)->Clear();
        ((RawList*)p)->mAlloc.~FixedAllocatorBase();
        operator_delete(p);
    }
    g_pVarListEditor = 0;
}

// ---- cAnimalTrap ----------------------------------------------------------------------
extern void* vtbl_cAnimalTrap[1];                                               // 0x01466b40
extern void* vtbl_cAnimalTrapRef[1];                                            // 0x01466b2c
extern void* vtbl_cAnimalTrapSpatial[1];                                        // 0x01466a68

struct CGameDataOps {
    void Ctor();                                                                // 0x00b18660
    void Dtor();                                                                // 0x00b184c0
    bool Write(void* stream);                                                   // 0x00b18590
};
struct CSpatialOps {
    void Ctor();                                                                // 0x00c89630
    bool Write(void* stream);                                                   // 0x00c88a90
    void Destroy();                                                             // 0x00c8b2e0
    void DtorBody();                                                            // 0x00c8a420
};
uint32_t __cdecl FNV1_String8(const char* s, uint32_t basis, int flags);        // 0x00932e80

struct cSpatialObjectPart {     // 0xd4 bytes, cAnimalTrap +0x34..+0x107
    void** vptr;                // +0x00
    uint32_t m04[0x50 / 4];     // +0x04..+0x53
    uint32_t m54;               // +0x54  (set to 2 by the cAnimalTrap ctor)
    uint32_t m58[0x38 / 4];     // +0x58..+0x8f
    uint32_t m90;               // +0x90  (0x00c4 absolute: tool-type hash)
    uint32_t m94;               // +0x94
    uint32_t m98;               // +0x98  (0x00cc absolute: tribal-tools hash)
    uint32_t m9c[0x38 / 4];     // +0x9c..+0xd3
};

struct cVarListSerializer;                                                      // 0xa14 bytes
bool __cdecl WriteUint32_93aa70(void* stream, const uint32_t* p, unsigned n, int flags); // 0x0093aa70

struct cVarListSerializer {
    uint32_t mData[0xa14 / 4];
    cVarListSerializer* Construct(void* obj, void* generic, unsigned sig); // 0x00692f90
    bool Serialize(void* stream);                                          // 0x00692900
};

extern int s_serializerGeneric;                                                 // 0x0156d600

struct cAnimalTrap {
    void** vptr;                // +0x000
    void* mRefVtbl;             // +0x004
    uint32_t m08[9];            // +0x008..+0x02b
    void* mp2c;                 // +0x02c
    uint32_t m30;               // +0x030
    cSpatialObjectPart mSpatial;// +0x034
    int mState;                 // +0x108
    uint32_t m10c;              // +0x10c
    uint32_t m110;              // +0x110
    void* mp114;                // +0x114

    cAnimalTrap* __fastcall Construct();                                        // 0x00bcb980
    void SetState(int s);                                                       // 0x00bcb960
    void __fastcall Destroy();                                                  // 0x00bcba80
    bool Write(void* stream);                                                   // 0x00bcbad0
    void Update();                                                              // 0x00bcbc80
    cAnimalTrap* ScalarDeletingDtor(unsigned flags);                            // 0x00bcbc30
};

// @ 0x00bcb960
void cAnimalTrap::SetState(int s)
{
    mState = s;
    if (s == 5)
        m110 = 0;
}

// @ 0x00bcb980
cAnimalTrap* cAnimalTrap::Construct()
{
    ((CGameDataOps*)this)->Ctor();
    ((CSpatialOps*)&mSpatial)->Ctor();
    vptr = vtbl_cAnimalTrap;
    mRefVtbl = vtbl_cAnimalTrapRef;
    mSpatial.vptr = vtbl_cAnimalTrapSpatial;
    mState = 0;
    m10c = 0;
    m110 = 0;
    mp114 = 0;
    mSpatial.m54 = 2;
    mSpatial.m90 = FNV1_String8("trg_sacrifice_altar1", 0x811c9dc5, 1);
    mSpatial.m98 = FNV1_String8("TribalTools", 0x811c9dc5, 1);
    return this;
}

// @ 0x00bcba80
void cAnimalTrap::Destroy()
{
    if (mp114) {
        ((void (__thiscall*)(void*, int))(*(void***)mp114)[3])(mp114, 1);
        if (mp114) {
            void* p = mp114;
            mp114 = 0;
            ((FnThis0)(*(void***)p)[1])(p);
        }
    }
    if (mp2c) {
        void* p = mp2c;
        mp2c = 0;
        ((FnThis0)(*(void***)p)[1])(p);
    }
    ((CSpatialOps*)&mSpatial)->Destroy();
}

// @ 0x00bcbad0
bool cAnimalTrap::Write(void* stream)
{
    void* a = ((void* (__thiscall*)(void*))(*(void***)stream)[8])(stream);
    uint32_t version = 0x61494bd;
    void* b = ((void* (__thiscall*)(void*))(*(void***)a)[6])(a);
    WriteUint32_93aa70(b, &version, 1, 0);
    bool ok = ((CGameDataOps*)this)->Write(stream)
           && ((CSpatialOps*)&mSpatial)->Write(stream);
    cVarListSerializer ser;
    ser.Construct(this, &s_serializerGeneric, 0x1a80d26);
    if (ok && ser.Serialize(stream))
        return true;
    return false;
}

// @ 0x00bcbc30
cAnimalTrap* cAnimalTrap::ScalarDeletingDtor(unsigned flags)
{
    vptr = vtbl_cAnimalTrap;
    mRefVtbl = vtbl_cAnimalTrapRef;
    mSpatial.vptr = vtbl_cAnimalTrapSpatial;
    _ReadWriteBarrier();
    void* p = mp114;
    if (p)
        ((FnThis0)(*(void***)p)[1])(p);
    ((CSpatialOps*)&mSpatial)->DtorBody();
    ((CGameDataOps*)this)->Dtor();
    if (flags & 1)
        operator_delete(this);
    return this;
}

// ---- 0x00bcb730: read the serialized list records -------------------------------------
// The retail build builds a 0x90-byte stack record (cGonzagoTimer + four EA::Variants +
// a Vector3 seed + a refcounted pointer), hands the serializer that record, then copies it
// into a fresh 0x234-byte list node.  Engine types are opaque here.
struct cGonzagoTimer {
    uint32_t m[0x40 / 4];
    cGonzagoTimer();                                                            // 0x00b63890
    ~cGonzagoTimer();                                                           // 0x00b638b0
};
struct Variant { uint32_t m[5]; void Destruct(bool free); };                    // 0x0093db80
struct Vector3f { float x, y, z; };
struct ListRecord {
    int mIndex;                 // +0x00
    uint32_t m04;               // +0x04
    cGonzagoTimer mTimer;       // +0x08
    uint32_t m48;               // +0x48
    Vector3f mVec;              // +0x2c (seed vector)
    void* mpRef;                // +0x28 (refcounted payload)
    Variant mV0, mV1, mV2, mV3;
};
extern Vector3f g_readVecSeed;                                                  // 0x0168b580
extern int s_serializerGenericList;                                             // 0x0156d2a8
bool __cdecl ReadInt32_93a780(void* stream, void* dst, int count, int flags);   // 0x0093a780

static bool RecordVariantNeedsFree(const Variant& v)
{
    return (((const uint8_t*)&v)[5] & 4) != 0;
}

// @ 0x00bcb730
void __cdecl ReadListProperty(void* stream, RawList* list)
{
    uint32_t count = 0;
    list->Clear();
    list->mpNext = (ListNode*)list;
    list->mpPrev = (ListNode*)list;
    void* a = ((void* (__thiscall*)(void*))(*(void***)stream)[8])(stream);
    void* s = ((void* (__thiscall*)(void*))(*(void***)a)[6])(a);
    ReadInt32_93a780(s, &count, 1, 0);
    for (uint32_t i = 0; i < count; i++) {
        ListRecord rec;
        rec.mIndex = -1;
        rec.mVec = g_readVecSeed;
        rec.mpRef = 0;
        rec.m48 = 0;
        rec.mV0.m[0] = rec.mV1.m[0] = rec.mV2.m[0] = rec.mV3.m[0] = 0;
        rec.mV0.m[1] = rec.mV1.m[1] = rec.mV2.m[1] = rec.mV3.m[1] = 0;
        cVarListSerializer ser;
        ser.Construct(&rec, &s_serializerGenericList, 0x1a80d26);
        ser.Serialize(stream);

        ListNode* node;
        for (;;) {
            if (list->mAlloc.mFields[4]) {
                node = (ListNode*)list->mAlloc.mFields[4];
                list->mAlloc.mFields[4] = *(uint32_t*)node;
                break;
            }
            if (!list->mAlloc.AddCore(0, 0)) {
                node = 0;
                break;
            }
        }
        if (node) {
            node->mEntry.Construct(&rec);
            node->mpNext = (ListNode*)list;
            node->mpPrev = list->mpPrev;
            list->mpPrev->mpNext = node;
            list->mpPrev = node;
        }

        if (RecordVariantNeedsFree(rec.mV3)) rec.mV3.Destruct(false);
        if (RecordVariantNeedsFree(rec.mV1)) rec.mV1.Destruct(false);
        if (RecordVariantNeedsFree(rec.mV0)) rec.mV0.Destruct(false);
        if (RecordVariantNeedsFree(rec.mV2)) rec.mV2.Destruct(false);
        if (rec.mpRef)
            ((FnThis0)(*(void***)rec.mpRef)[1])(rec.mpRef);
    }
    ((void (__thiscall*)(void*))(*(void***)stream)[7])(stream);
}

// ---- 0x00bcbc80: cAnimalTrap state update ----------------------------------------------
struct Matrix3 { float m[9]; };
struct PtrVec { void** mpBegin; void** mpEnd; void** mpCap; };
extern float g_matrixSeed;                                                      // 0x0168b5fc
void Matrix3Assign(Matrix3* self, const void* src);                             // 0x0041cb40
Matrix3* Matrix3FromFacingAndUp(Matrix3* out, const Vector3f* up, const Vector3f* facing); // 0x0069b440
void* EffectsManager();                                                         // 0x0067ddd0
void* NounManagerCall(int a, void* b, void* c);                                 // 0x00b3d300
int GetPlayerEmpireOrMinus1();                                                  // 0x00b1f9d0
float GetPropertyFloat(void* list, uint32_t key, float def);                    // 0x004e1c70
void* FUN_00d1e660();                                                           // 0x00d1e660
void* FUN_00b3d240();                                                           // 0x00b3d240

// @ 0x00bcbc80
void cAnimalTrap::Update()
{
    if (mp114 && ((bool (__thiscall*)(void*))(*(void***)mp114)[4])(mp114))
        return;

    Matrix3 mtx;
    Matrix3Assign(&mtx, &g_matrixSeed);

    void* spatial = &mSpatial;
    Vector3f* pos = (Vector3f*)((void* (__thiscall*)(void*))(*(void***)spatial)[0x2c / 4])(spatial);

    Vector3f facing;
    float inv = 1.0f / sqrtf((pos->x * pos->x + pos->y * pos->y + pos->z * pos->z) + 1e-8f);
    facing.x = pos->x * inv;
    facing.y = pos->y * inv;
    facing.z = pos->z * inv;
    Matrix3 tmp;
    Matrix3FromFacingAndUp(&tmp, (const Vector3f*)&mtx.m[6], &facing);
    mtx = tmp;

    void* em = EffectsManager();
    if (mp114) {
        void* p = mp114;
        mp114 = 0;
        ((FnThis0)(*(void***)p)[1])(p);
    }
    if (((bool (__thiscall*)(void*, uint32_t, int, void**))(*(void***)em)[0x2c / 4])
            (em, 0x39897926, 0, &mp114)) {
        ((void (__thiscall*)(void*, Matrix3*))(*(void***)mp114)[6])(mp114, &mtx);
        ((void (__thiscall*)(void*, int))(*(void***)mp114)[2])(mp114, 0);
    }
    if (mState == 4) {
        void* em2 = EffectsManager();
        if (mp114) {
            void* p = mp114;
            mp114 = 0;
            ((FnThis0)(*(void***)p)[1])(p);
        }
        if (((bool (__thiscall*)(void*, uint32_t, int, void**))(*(void***)em2)[0x2c / 4])
                (em2, 0x2cb92f84, 0, &mp114)) {
            ((void (__thiscall*)(void*, Matrix3*))(*(void***)mp114)[6])(mp114, &mtx);
            ((void (__thiscall*)(void*, int))(*(void***)mp114)[2])(mp114, 0);
        }
    }

    void* propOwner = FUN_00d1e660();
    float radius = GetPropertyFloat(*(void**)(*(uint32_t*)((char*)propOwner + 0x1c) + 0x130),
                                    0xb1112498, 10.0f);

    void* buf[32];
    PtrVec vec;
    vec.mpBegin = buf;
    vec.mpEnd = buf;
    vec.mpCap = buf + 32;
    void* hits = FUN_00b3d240();
    uint32_t q = ((uint32_t (__thiscall*)(void*, float, PtrVec*, int, int))
                  (*(void***)spatial)[0x2c / 4])(spatial, radius, &vec, 0, 0);
    unsigned n = (unsigned)(vec.mpEnd - vec.mpBegin);
    if (((bool (__thiscall*)(void*, uint32_t))(*(void***)hits)[0x48 / 4])(hits, q)) {
        for (unsigned i = 0; i < n; i++) {
            void* obj = vec.mpBegin[i];
            if (!obj)
                continue;
            void* found = ((void* (__thiscall*)(void*, uint32_t))(*(void***)obj)[0xb8 / 4])
                              (obj, 0xd0036e08);
            if (!found)
                continue;
            void* tool = *(void**)((char*)found + 0x5a8);
            NounManagerCall(0x11, &mtx, 0);
            int empire = GetPlayerEmpireOrMinus1();
            ((void (__thiscall*)(void*, float, int))(*(void***)tool)[6])(tool, 10.0f, empire);
        }
    }

    mState++;
    if (mState == 5)
        m110 = 0;
    for (unsigned i = 0; i < n; i++) {
        void* obj = vec.mpBegin[i];
        if (obj)
            ((void (__thiscall*)(void*))(*(void***)obj)[0xc0 / 4])(obj);
    }
    if (vec.mpBegin && *(uint32_t*)(vec.mpBegin - 1))
        operator_delete(vec.mpBegin);
}
