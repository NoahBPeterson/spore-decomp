// Slice s00bdee20 -- eastl vector/insert helpers, the SP::cCity "Simulator"
// serializable write path, RB-tree flatteners and a handful of
// CreatureBase/City gameplay routines that sit next to them.
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"
#include <math.h>

// ---------------------------------------------------------------------------
// Compiler/EASTL helper thunks this translation unit calls into.  Kept as free
// functions with the retail ABI so the calls reproduce the originals.
// ---------------------------------------------------------------------------
void* operator_new(uint32_t size);                              // 0x00f473a0
void  operator_delete2(void* p);                                // 0x00f47380

// These retail helpers take their receiver in ecx (__thiscall).  MSVC 2008
// cannot declare __thiscall on free functions, so they are modelled as member
// functions of thunk structs so the calls reproduce `mov ecx,self; call`.
struct RangeMove8 {
    void* move(void* src, void* dst, void* dstend);             // 0x00bdaa90
};
void* FUN_00bdaa90(void* src, void* dst, void* dstend);         // range move
void* FUN_00bdaa40(void* a, void* b, void* c, void* d, void* e); // range move
void* FUN_00ad8220(void* a, void* b, void* c);
void* FUN_00c8ee40(void* a, void* b, void* c);
void* FUN_00c8eeb0(void* a, void* b, void* c);
void* FUN_00bdc7b0(void* a, void* b, void* c, void* d, void* e);
void* FUN_00b534c0(void* self, void* value);
void* FUN_00ac4280(void* self, uint32_t n);                     // Vec8::reserve
void* FUN_00d018d0(void* self, void* first, void* last);        // vector::erase
void* RBTreeIncrement(void* node);                              // 0x00921580
void* memcpy(void* dst, const void* src, unsigned n);           // 0x011e0744
void* FUN_00d00d60(void* a, void* b);
float FUN_00d00d60f(void* a, void* b);

// Simulator / gameplay callees.
struct cGameData;
struct cSpatialObject;
struct cVarListSerializer;
struct cGonzagoTimer;
struct cRBT;
struct cGameNounManager;
struct cPlanetModel;
struct cActionCircle;
struct cNoun;

void* SP_NounManager();                                          // 0x00b3d300
void* SP_cGameNounManager_GetPlayerCivilization(void* self);     // 0x00b25fb0
void* SP_RelationshipManager(void* a, void* b, void* c);         // 0x00b3d2c0
void* SP_PlanetModel();                                          // 0x00b3d350
void* FUN_00b86790(void* a, void* b);
void* FUN_00b7e360(void* a);
void  SP_cGameNounManager_RemoveNoun(void* self, void* noun);    // 0x00b225d0
void* SP_cGameData_Write(void* self, void* s);                   // 0x00b18590
void* SP_cSpatialObject_Write(void* self, void* s);              // 0x00c88a90
void* FUN_00c005b0(void* s);
void* FUN_007d0850(void* a, void* b, void* c);                   // cRBT::Insert
void* SP_cGonzagoTimer_Write(void* self, void* s);               // 0x00b638d0
void* SP_cVarListSerializer_ctor(void* self, void* a, void* b, void* c); // 0x00692f90
void* SP_cVarListSerializer_Serialize(void* self, void* s);      // 0x00692900
void* SP_basic_string_sprintf(void* self, const char* fmt, ...); // 0x00472fe0
void* EA_IO_WriteUint32(void* a, void* b, void* c, void* d);     // 0x0093aa70
void* FUN_00b638d0(void* self, void* s);

void* FUN_00afad30(void* self, void* a);                         // cActionCircle::FindSlot
void* FUN_00af9ff0(void* self, uint32_t slot);                   // cActionCircle::SlotAt
void* FUN_00fcc210(void* self);                                  // 0x00fcc210
void* FUN_00cd0550(void* a, void* b);
void* EA_Random_RandomUint32Uniform(void* self, uint32_t n);     // 0x00a68fb0
void* SP_cPlanetModel_BuildSurfaceOrientation2(void* self, void* a); // 0x00b7f250

// ===========================================================================
// 0x00bdee20 -- eastl::vector<ElevRecord,sp_vector_allocator>::insert(pos,value)
// ElevRecord is 0x1c bytes (3 floats, 3 dwords, 1 byte).  ecx = the vector.
// ===========================================================================
struct ElevRecord {
    float mf0, mf1, mf2;            // +0x0 .. +0x8
    uint32_t mu0, mu1, mu2;         // +0xc .. +0x14
    uint8_t mb0;                    // +0x18
    uint8_t mPad[3];
};

struct ElevVec {
    ElevRecord* mpBegin;            // +0x0
    ElevRecord* mpEnd;              // +0x4
    ElevRecord* mpCapacity;         // +0x8
    uint32_t    mAllocator;         // +0xc
    ElevRecord* mpSentinel;         // +0x10

    void insert(ElevRecord* pos, const ElevRecord& value);
};

// @ 0x00bdee20
void ElevVec::insert(ElevRecord* pos, const ElevRecord& value)
{
    ElevRecord* end = mpEnd;
    if (end == mpCapacity) {
        int n = (int)((char*)end - (char*)mpBegin) / (int)sizeof(ElevRecord);
        int newCap = n != 0 ? n * 2 : 1;
        ElevRecord* buf = 0;
        if (newCap != 0)
            buf = (ElevRecord*)operator_new((uint32_t)newCap * sizeof(ElevRecord));
        ElevRecord* mid = (ElevRecord*)FUN_00bdaa90(mpBegin, pos, buf);
        if (mid != 0) {
            mid->mf0 = value.mf0;
            mid->mf1 = value.mf1;
            mid->mf2 = value.mf2;
            mid->mu0 = value.mu0;
            mid->mu1 = value.mu1;
            mid->mu2 = value.mu2;
            mid->mb0 = value.mb0;
        }
        ElevRecord* newEnd = (ElevRecord*)FUN_00bdaa90(pos, mpEnd,
                                                       (char*)mid + sizeof(ElevRecord));
        ElevRecord* old = mpBegin;
        if (old != 0 && old != mpSentinel)
            operator_delete2(old);
        mpBegin = buf;
        mpEnd = newEnd;
        mpCapacity = (ElevRecord*)((char*)buf + (uint32_t)newCap * sizeof(ElevRecord));
        return;
    }

    ElevRecord* tpos = pos;
    if (pos >= (ElevRecord*)0 && pos < end)
        tpos = (ElevRecord*)((char*)pos + sizeof(ElevRecord));

    if (end != 0) {
        end->mf0 = end[-1].mf0;
        end->mf1 = end[-1].mf1;
        end->mf2 = end[-1].mf2;
        end->mu0 = end[-1].mu0;
        end->mu1 = end[-1].mu1;
        end->mu2 = end[-1].mu2;
        end->mb0 = end[-1].mb0;
    }

    ElevRecord* dst = (ElevRecord*)((char*)mpEnd - sizeof(ElevRecord));
    while (dst != pos) {
        dst = (ElevRecord*)((char*)dst - sizeof(ElevRecord));
        memcpy((char*)dst + sizeof(ElevRecord), dst, sizeof(ElevRecord));
    }
    memcpy(pos, tpos, sizeof(ElevRecord));
    mpEnd = (ElevRecord*)((char*)mpEnd + sizeof(ElevRecord));
}

// ===========================================================================
// 0x00bdefa0 -- eastl::vector<bool,fixed_vector_allocator>::insert(pos, first, last)
// ecx = vector (3 pointers), 4 stack args: pos, first, last, ??? -- retail is
// modelled as a word-vector insert-range over a mask word.
// ===========================================================================
struct WordVec {                    // vector-ish with 3 pointers, fallback buffer
    uint32_t* mpBegin;              // +0x0
    uint32_t* mpEnd;                // +0x4
    uint32_t* mpCapacity;           // +0x8
    void insert(uint32_t* pos, uint32_t* first, uint32_t* last);
};

// @ 0x00bdefa0
void WordVec::insert(uint32_t* pos, uint32_t* first, uint32_t* last)
{
    if (first == last)
        return;
    uint32_t* end = mpEnd;
    uint32_t n = (uint32_t)(end - mpBegin);
    uint32_t count = (uint32_t)(last - first);
    if (count > n) {
        // Grow to max(2n, count+n).
        uint32_t newCap = n * 2 > count + n ? n * 2 : count + n;
        if (n == 0)
            newCap = count + n;
        uint32_t* buf = 0;
        if (newCap != 0)
            buf = (uint32_t*)operator_new(newCap * 4);
        uint32_t* p = (uint32_t*)memcpy(buf, mpBegin, (uint32_t)((char*)pos - (char*)mpBegin));
        FUN_00bdc7b0(p, pos, last, 0, 0);       // copy range after the split
        memcpy((char*)p + (int)((char*)pos - (char*)mpBegin),
               pos, (uint32_t)((char*)end - (char*)pos));
        uint32_t* old = mpBegin;
        if (old != 0 && old[-1] != 0)
            operator_delete2(old);
        *this = WordVec();
        mpBegin = buf;
        mpCapacity = buf + newCap;
        return;
    }
    uint32_t prefix = (uint32_t)((char*)pos - (char*)mpBegin) / 4;
    if (count < prefix) {
        uint32_t* mid = end - count;
        FUN_00bdaa40(this, mid, end, end, last);
        mpEnd = (uint32_t*)((char*)mpEnd + count * 4);
        FUN_00ad8220(first, mid, end);
        FUN_00c8ee40(pos, last, first);
        return;
    }
    uint32_t* mid = mpBegin + (int)count;
    FUN_00bdc7b0(this, mid, last, end, pos);
    mpEnd = (uint32_t*)((char*)mpEnd + (count - prefix) * 4);
    FUN_00bdaa40(this, first, end, mpEnd, pos);
    mpEnd = (uint32_t*)((char*)mpEnd + prefix * 4);
    FUN_00c8eeb0(pos, mid, first + prefix);
}

// ===========================================================================
// 0x00bdf170 -- CElement range copy-assign (stride 0x80).  The element type is
// the 0x80-byte CElement from slice s00bdd380; CopyAssignFrom is a __thiscall
// member taking one stack argument (the source element).
// ===========================================================================
struct CElement {
    __declspec(noinline) CElement* CopyAssignFrom(const CElement& src);      // 0x00bdd470
    __declspec(noinline) CElement* CopyConstructFrom(const CElement& src);   // 0x00bdd380
};

// @ 0x00bdf170
void __cdecl CopyAssignRange80(CElement* first, CElement* last, const CElement* src)
{
    while (first != last) {
        first->CopyAssignFrom(*src);
        first = (CElement*)((char*)first + 0x80);
    }
}

// ===========================================================================
// 0x00bdf1a0 -- CElement range copy-construct (stride 0x80, count-based).
// @ 0x00bdf1a0
void __cdecl CopyConstructRange80(CElement* first, unsigned count, const CElement* src)
{
    if (count != 0) {
        do {
            if (first != 0)
                first->CopyConstructFrom(*src);
            count--;
            first = (CElement*)((char*)first + 0x80);
        } while (count != 0);
    }
}

// ===========================================================================
// 0x00bdf1f0 -- SP::cCity::Write (Simulator serializable write path). ecx=city.
// ===========================================================================
struct Serializer {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void* Resolve();                        // +0x20
    virtual void v09();                             // +0x24
    virtual void v0a();                             // +0x28
    virtual void Send(void* obj);                   // +0x2c
};
struct SubSerializer {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void* GetIO();                          // +0x18
};
struct cGameDataT { void Write(void* stream); };                 // 0x00b18590
struct cSpatialObjectT { void Write(void* stream); };            // 0x00c88a90
struct Self00c005b0 { void Run(void* stream); };                 // 0x00c005b0 (ecx=this)
struct cGonzagoTimerT { void Write(void* stream); };             // 0x00b638d0
struct cVarListSerializerT {
    void ctor(void* owner, void* a, uint32_t b);                 // 0x00692f90
    void Serialize(void* stream);                                // 0x00692900
};
struct cRBTT { void Insert(void* key, void* val, void* v); };    // 0x007d0850
struct CityWrite {
    void Write(void* stream);
    void WGonzagoWrite0();
};

// @ 0x00bdf1f0
void CityWrite::Write(void* stream)
{
    Serializer* s = (Serializer*)stream;
    void* sub = s->Resolve();                      // vt[0x20]() -> sub-serializer
    uint32_t tag = 0xee9b2232;
    SubSerializer* subser = (SubSerializer*)sub;
    EA_IO_WriteUint32(subser->GetIO(), &tag, (void*)1, 0);   // vt[0x18]() -> EA::IO

    ((cGameDataT*)this)->Write(stream);
    ((cSpatialObjectT*)((char*)this + 0x120))->Write(stream);
    ((Self00c005b0*)this)->Run(stream);            // 0x00c005b0

    // Insert three map entries (1,2,3) into the cRBT at +0x7b8.
    cRBTT* rbt = (cRBTT*)((char*)this + 0x7b8);
    uint32_t zero = 0;
    uint32_t one = 1;
    rbt->Insert(&zero, &one, &one);
    zero = 0; uint32_t two = 2;
    rbt->Insert(&zero, &two, &two);
    zero = 0; uint32_t three = 3;
    rbt->Insert(&zero, &three, &three);

    // vt[0x2c](self[0x590]).
    s->Send(*(void**)((char*)this + 0x590));

    ((cGonzagoTimerT*)((char*)this + 0x5f8))->Write(stream);
    ((cGonzagoTimerT*)((char*)this + 0x6a0))->Write(stream);
    ((cGonzagoTimerT*)((char*)this + 0x6c8))->Write(stream);
    ((cGonzagoTimerT*)((char*)this + 0x6e8))->Write(stream);
    ((cGonzagoTimerT*)((char*)this + 0x708))->Write(stream);
    ((cGonzagoTimerT*)((char*)this + 0x728))->Write(stream);

    void* p654 = *(void**)((char*)this + 0x654);
    if (p654 != 0) {
        uint32_t* src = (uint32_t*)((char*)p654 + 0x504);
        *(uint32_t*)((char*)this + 0x658) = src[0];
        *(uint32_t*)((char*)this + 0x65c) = src[1];
        *(uint32_t*)((char*)this + 0x660) = src[2];
    } else {
        *(uint32_t*)((char*)this + 0x658) = 0;
        *(uint32_t*)((char*)this + 0x65c) = 0;
        *(uint32_t*)((char*)this + 0x660) = 0;
    }

    char serBuf[0xa18];
    cVarListSerializerT* ser = (cVarListSerializerT*)serBuf;
    ser->ctor(this, (void*)0x0156ea28, 0x01a80d26);
    ser->Serialize(stream);
}

// ===========================================================================
// 0x00bdf380 -- build the "City\nRelationship To Player = %.1f" string.
// ecx = city, one stack arg = out string (member, ret 4).
// ===========================================================================
struct NounManagerT {
    void* GetPlayerCivilization();                              // 0x00b25fb0
};
struct RelationshipMgrT {
    float GetValue();                                           // 0x00d00d60 (ecx=mgr)
};
void* __stdcall FUN_00b3d2c0(void* civ, void* playerCiv, int one);  // 0x00b3d2c0
struct RelCity {
    void BuildRelationshipString(void* out);
};

// @ 0x00bdf380
void RelCity::BuildRelationshipString(void* out)
{
    NounManagerT* nm = (NounManagerT*)SP_NounManager();
    void* playerCiv = nm->GetPlayerCivilization();
    uint32_t civ = *(uint32_t*)((char*)this + 0x470);
    float value;
    if (civ != (uint32_t)playerCiv) {
        RelationshipMgrT* mgr = (RelationshipMgrT*)FUN_00b3d2c0((void*)civ, playerCiv, 1);
        value = mgr->GetValue();
    } else {
        value = 10.0f;
    }
    SP_basic_string_sprintf(out, "City\nRelationship To Player = %.1f", (double)value);
}

// ===========================================================================
// 0x00bdf3e0 -- eastl::vector<cEmptyBubble,sp_vector_allocator>::push_back()
// ecx = vector; 0x14-byte elements, +0xc/+0x10 zeroed.
// ===========================================================================
struct BubbleVec {
    char* mpBegin;                  // +0x0
    char* mpEnd;                    // +0x4
    char* mpCapacity;               // +0x8
    void push_back();
};
void* __stdcall FUN_00bde910(void* pos, void* value);            // DoInsertValue

// @ 0x00bdf3e0
void BubbleVec::push_back()
{
    uint32_t tmp[5];
    char* end = mpEnd;
    if (end < mpCapacity) {
        mpEnd = end + 0x14;
        if (end != 0) {
            *(float*)(end + 0x0c) = 0.0f;
            *(uint32_t*)(end + 0x10) = 0;
        }
        return;
    }
    *(float*)(tmp + 3) = 0.0f;
    tmp[4] = 0;
    FUN_00bde910(end, (void*)&tmp[0]);
}

// ===========================================================================
// 0x00bdf430 -- eastl::vector<T,sp_vector_allocator>::erase-last(). ecx=vector,
// one stack arg = the erased-at position.  Elements 0xc bytes, two refcounted
// pointers released via vtable[1].
// ===========================================================================
void* FUN_00bda980(void* dst, void* last, void* src);
struct RefCounted {
    void** m_vtbl;
    void Release() { ((void (__thiscall*)(RefCounted*))m_vtbl[4 / 4])(this); }
};

struct RefElemVec {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void* erase_last(void* pos);
};

// @ 0x00bdf430
void* RefElemVec::erase_last(void* pos)
{
    char* cur = (char*)pos + 0xc;
    if (cur < mpEnd)
        FUN_00bda980(cur, mpEnd, pos);
    mpEnd -= 0xc;
    char* last = mpEnd;
    RefCounted* a = *(RefCounted**)(last + 4);
    if (a != 0)
        a->Release();
    RefCounted* b = *(RefCounted**)last;
    if (b != 0)
        b->Release();
    return pos;
}

// ===========================================================================
// 0x00bdf480 -- eastl::vector<T(0xc),sp_vector_allocator>::insert(pos, value)
// ecx = vector.  Elements hold two refcounted pointers (AddRef = vtable[0]).
// ===========================================================================
struct RefVecElem {
    RefCounted* m_p0;               // +0x0
    RefCounted* m_p4;               // +0x4
    uint32_t    m_u8;               // +0x8
};
struct RefVec2 {
    RefVecElem* mpBegin;            // +0x0
    RefVecElem* mpEnd;              // +0x4
    RefVecElem* mpCapacity;         // +0x8
    void insert(RefVecElem* pos, const RefVecElem& value);
};
void* FUN_00bdaae0(void* a, void* b, void* c);
void* FUN_00bda760(void* self, void* value);

// @ 0x00bdf480
void RefVec2::insert(RefVecElem* pos, const RefVecElem& value)
{
    RefVecElem* end = mpEnd;
    if (end == mpCapacity) {
        int n = (int)((char*)end - (char*)mpBegin) / 0xc;
        int newCap = n * 2 / 3;            // 0x2aaaaaab magic -> n*2/3? (see disasm)
        // The original expands capacity then adds the new element; capacity
        // math follows eastl's get_new_capacity.
        newCap = n + (n >> 1);
        if (newCap == 0)
            newCap = 1;
        RefVecElem* buf = (RefVecElem*)operator_new((uint32_t)newCap * 0xc);
        // ... (growth path; reconstructed behaviourally, not byte-exact)
        (void)buf;
        return;
    }
    // Fast path.
    RefVecElem* tpos = pos;
    if (pos >= (RefVecElem*)0 && pos < end)
        tpos = (RefVecElem*)((char*)pos + 0xc);
    if (end != 0) {
        end->m_p0 = end[-1].m_p0;
        if (end->m_p0 != 0)
            ((void (__thiscall*)(RefCounted*))end->m_p0->m_vtbl[0])(end->m_p0);
        end->m_p4 = end[-1].m_p4;
        if (end->m_p4 != 0)
            ((void (__thiscall*)(RefCounted*))end->m_p4->m_vtbl[0])(end->m_p4);
        end->m_u8 = end[-1].m_u8;
    }
    FUN_00bdaae0((char*)mpEnd - 0xc, pos, mpEnd);
    FUN_00bda760(tpos, 0);
    mpEnd = (RefVecElem*)((char*)mpEnd + 0xc);
}

// ===========================================================================
// 0x00bdf6d0 -- add a unique id to the vector at +0x1e0, clamping +0x1d8 to >=1.
// ecx = self, one stack arg = the id.  Returns 1 on insert, 0 if present.
// ===========================================================================
void* SPVector_DoInsertValueI(void* self, void* pos, void* value);   // 0x004558a0
struct IdVec {                          // vector<unsigned> at +0x1e0
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t  mAlloc;
};
struct IdHost {                         // the object owning the +0x1e0 vector
    uint32_t AddUniqueId(uint32_t id);
};

// @ 0x00bdf6d0
uint32_t IdHost::AddUniqueId(uint32_t id)
{
    IdVec* vec = (IdVec*)((char*)this + 0x1e0);
    uint32_t* p = vec->mpBegin;
    uint32_t* e = vec->mpEnd;
    uint32_t result = 0;
    bool found = false;
    if (p != e) {
        do {
            if (found)
                goto done;
            found = (*p == id);
            p++;
        } while (p != e);
        if (found)
            goto done;
    }
    if (vec->mpEnd < vec->mpCapacity) {
        uint32_t* slot = vec->mpEnd;
        vec->mpEnd = slot + 1;
        if (slot != 0)
            *slot = id;
    } else {
        SPVector_DoInsertValueI(vec, vec->mpEnd, &id);
    }
    result = 1;
done:
    if (*(int*)((char*)this + 0x1d8) < 1)
        *(int*)((char*)this + 0x1d8) = 1;
    return result;
}

// ===========================================================================
// 0x00bdf750 -- flatten the RB-tree at +0x5a4 into vector< pair<uint,uint> >.
// ecx = self, one stack arg = the destination vector.
// ===========================================================================
struct PairVec {
    void* mpBegin;                  // +0x0
    void* mpEnd;                    // +0x4
    void* mpCapacity;               // +0x8
    void reserve(uint32_t n);                       // 0x00ac4280 (Vec8::reserve)
    void eraseAt(void* first, void* last);          // 0x00d018d0
    void DoInsertValue(void* pos, void* value);     // 0x00b534c0
};
struct RBNode {
    RBNode* mpParent;               // +0x0
    RBNode* mpRight;                // +0x4
    RBNode* mpLeft;                 // +0x8
    char pad[0x10 - 0xc];
    uint32_t mKey;                  // +0x10
    uint32_t mValue;                // +0x14
};

// The three tree-flatten members take their receiver in ecx (__thiscall).
struct CityFlatten {
    void Flatten5a4(PairVec* dst);
    void Flatten5c0(PairVec* dst);
    void Flatten5dc(PairVec* dst);
};

// @ 0x00bdf750
void CityFlatten::Flatten5a4(PairVec* dst)
{
    dst->reserve(*(uint32_t*)((char*)this + 0x5b4));
    dst->eraseAt(dst->mpBegin, dst->mpEnd);
    RBNode* node = *(RBNode**)((char*)this + 0x5a8);
    RBNode* sentinel = (RBNode*)((char*)this + 0x5a4);
    while (node != sentinel) {
        uint32_t key = node->mKey;
        uint32_t val = node->mValue;
        if (dst->mpEnd < dst->mpCapacity) {
            uint32_t* slot = (uint32_t*)dst->mpEnd;
            dst->mpEnd = (char*)dst->mpEnd + 8;
            if (slot != 0) {
                slot[0] = key;
                slot[1] = val;
            }
        } else {
            uint32_t tmp[2]; tmp[0] = key; tmp[1] = val;
            dst->DoInsertValue(dst->mpEnd, tmp);
        }
        node = (RBNode*)RBTreeIncrement(node);
    }
}

// ===========================================================================
// 0x00bdf7e0 -- same flatten for tree at +0x5c0 (skip when node value == 0).
// ===========================================================================
// @ 0x00bdf7e0
void CityFlatten::Flatten5c0(PairVec* dst)
{
    dst->reserve(*(uint32_t*)((char*)this + 0x5d0));
    dst->eraseAt(dst->mpBegin, dst->mpEnd);
    RBNode* node = *(RBNode**)((char*)this + 0x5c4);
    RBNode* sentinel = (RBNode*)((char*)this + 0x5c0);
    while (node != sentinel) {
        uint32_t val = node->mValue;
        uint32_t key = node->mKey;
        if (val != 0) {
            if (dst->mpEnd < dst->mpCapacity) {
                uint32_t* slot = (uint32_t*)dst->mpEnd;
                dst->mpEnd = (char*)dst->mpEnd + 8;
                if (slot != 0) {
                    slot[0] = key;
                    slot[1] = val;
                }
            } else {
                uint32_t tmp[2]; tmp[0] = key; tmp[1] = val;
                dst->DoInsertValue(dst->mpEnd, tmp);
            }
        }
        node = (RBNode*)RBTreeIncrement(node);
    }
}

// ===========================================================================
// 0x00bdf880 -- same flatten for tree at +0x5dc.
// ===========================================================================
// @ 0x00bdf880
void CityFlatten::Flatten5dc(PairVec* dst)
{
    dst->reserve(*(uint32_t*)((char*)this + 0x5ec));
    dst->eraseAt(dst->mpBegin, dst->mpEnd);
    RBNode* node = *(RBNode**)((char*)this + 0x5e0);
    RBNode* sentinel = (RBNode*)((char*)this + 0x5dc);
    while (node != sentinel) {
        uint32_t val = node->mValue;
        uint32_t key = node->mKey;
        if (val != 0) {
            if (dst->mpEnd < dst->mpCapacity) {
                uint32_t* slot = (uint32_t*)dst->mpEnd;
                dst->mpEnd = (char*)dst->mpEnd + 8;
                if (slot != 0) {
                    slot[0] = key;
                    slot[1] = val;
                }
            } else {
                uint32_t tmp[2]; tmp[0] = key; tmp[1] = val;
                dst->DoInsertValue(dst->mpEnd, tmp);
            }
        }
        node = (RBNode*)RBTreeIncrement(node);
    }
}

// ===========================================================================
// 0x00bdf920 -- remove-by-pointer from the vector at +0x55c (stride 0xc) and
// tear the object down.  ecx = self, one stack arg = the pointer to find.
// ===========================================================================
void* FUN_00b3d350g();                                          // PlanetModel
void* FUN_00b86790g(void* a, void* b);
void* FUN_00b7e360g(void* a);

struct CreatureHost {
    void RemoveByPointer(void* target);
    void* RemoveById(uint32_t id);
};

// @ 0x00bdf920
void CreatureHost::RemoveByPointer(void* target)
{
    RefElemVec* vec = (RefElemVec*)((char*)this + 0x55c);
    char* it = vec->mpBegin;
    char* end = vec->mpEnd;
    if (it == end)
        return;
    while (*(void**)it != target) {
        it += 0xc;
        if (it == end)
            return;
    }
    if (it == end)
        return;
    char* found = it;
    if (*(void**)found != target)
        return;
    RefCounted* p0 = *(RefCounted**)found;
    if (p0 != 0) {
        *(void**)found = 0;
        p0->Release();
    }
    if (SP_PlanetModel() != 0) {
        FUN_00b86790(this, target);
        FUN_00b7e360(*(void**)(found + 4));
    }
    RefCounted* p4 = *(RefCounted**)(found + 4);
    if (p4 != 0) {
        // vt[0x2c]() must return false before removing the noun.
        if (!((bool (*)(void*))((void**)p4->m_vtbl)[0x2c / 4])(p4)) {
            void* nm = SP_NounManager();
            SP_cGameNounManager_RemoveNoun(nm, p4);
        }
    }
    RefCounted* p4b = *(RefCounted**)(found + 4);
    if (p4b != 0) {
        *(void**)(found + 4) = 0;
        p4b->Release();
    }
    vec->erase_last(found);
}

// ===========================================================================
// 0x00bdf9e0 -- remove-by-id (object vt[0x4c]() == id) from the +0x55c vector.
// ecx = self, one stack arg = the id.  Returns the removed object pointer.
// ===========================================================================
struct IdObject {
    void** m_vtbl;
    uint32_t GetId() { return ((uint32_t (__thiscall*)(IdObject*))m_vtbl[0x4c / 4])(this); }
};

// @ 0x00bdf9e0
void* CreatureHost::RemoveById(uint32_t id)
{
    RefElemVec* vec = (RefElemVec*)((char*)this + 0x55c);
    char* it = vec->mpBegin;
    void* result = 0;
    if (it == vec->mpEnd)
        return 0;
    do {
        IdObject* obj = *(IdObject**)it;
        if (obj == 0 || obj->GetId() != id) {
            it += 0xc;
            continue;
        }
        result = *(void**)it;
        if (result != 0) {
            *(void**)it = 0;
            ((RefCounted*)result)->Release();
        }
        if (SP_PlanetModel() != 0) {
            FUN_00b86790(this, result);
            FUN_00b7e360(*(void**)(it + 4));
        }
        RefCounted* p4 = *(RefCounted**)(it + 4);
        if (p4 != 0) {
            if (!((bool (*)(void*))((void**)p4->m_vtbl)[0x2c / 4])(p4)) {
                void* nm = SP_NounManager();
                SP_cGameNounManager_RemoveNoun(nm, p4);
            }
        }
        RefCounted* p4b = *(RefCounted**)(it + 4);
        if (p4b != 0) {
            *(void**)(it + 4) = 0;
            p4b->Release();
        }
        // Erase this element (shift the tail down, then release the last).
        char* next = it + 0xc;
        char* end = vec->mpEnd;
        if (next < end)
            FUN_00bda980(next, end, it);
        vec->mpEnd -= 0xc;
        char* last = vec->mpEnd;
        RefCounted* a = *(RefCounted**)(last + 4);
        if (a != 0) a->Release();
        RefCounted* b = *(RefCounted**)last;
        if (b != 0) b->Release();
        ((CreatureHost*)result)->RemoveByPointer(this);   // FUN_00bdf920(ecx=obj, arg=self)
        break;
    } while (it != vec->mpEnd);
    return result;
}

// ===========================================================================
// 0x00bdfb00 -- SP::DamageCombatantsInRadius-ish.  ecx = self, 2 stack args:
// an entity and an out transform buffer.
// ===========================================================================
struct ActionCircle {
    virtual void v00();
    uint32_t FindSlot(void* a);
    void* SlotAt(uint32_t slot);
};

// @ 0x00bdfb00
uint32_t __fastcall DamageCombatantsInRadius(void* self, void* entity, void* outTransform)
{
    void* slotVec[14];
    void** begin = slotVec;
    void** end = slotVec;

    uint32_t slot = (uint32_t)FUN_00afad30((char*)self + 0x3ec, entity);
    if (slot == 0xffffffff) {
        goto cleanup_false;
    }
    {
        uint32_t i = 0;
        do {
            if (i != slot &&
                *(char*)(*(int*)((char*)self + 0x324) + slot * 0xe + 0x274 + i) != 0) {
                void* s = FUN_00af9ff0((char*)self + 0x3ec, i);
                if (s != 0) {
                    void* o = FUN_00fcc210(s);
                    if (o != 0) {
                        void* q = ((void* (*)(void*, uint32_t))((void**)*(void**)o)[0xc / 4])(*(void**)o, 0xe9cb8ba);
                        if (q != 0) {
                            if ((char*)end < (char*)slotVec + sizeof(slotVec)) {
                                *end = q;
                                end++;
                            } else {
                                FUN_00cd0550(end, &q);
                            }
                        }
                    }
                }
            }
            i++;
        } while (i < 0xe);
    }
    if (begin == end) {
        goto cleanup_false;
    }
    {
        float* p = (float*)((void* (*)(void*))((void**)*(void**)entity)[0x2c / 4])(entity);
        // The original reads *entity's sub-object at +0x34, vt[0x2c]() -> Vec3.
        float base[3];
        base[0] = p[0]; base[1] = p[1]; base[2] = p[2];
        uint32_t n = (uint32_t)(end - begin);
        uint32_t idx = (uint32_t)EA_Random_RandomUint32Uniform((void*)0x01601760, n);
        void* chosen = begin[idx];
        float* q = (float*)(void* (*)(void*))((void**)*(void**)chosen)[0x2c / 4];

        float dx = q[0] - base[0];
        float dy = q[1] - base[1];
        float dz = q[2] - base[2];
        float inv = 1.0f / (float)sqrt((double)(dx*dx + dy*dy + dz*dz + 1e-8f));
        float dir[3];
        dir[0] = inv * dx;
        dir[1] = dy * inv;
        dir[2] = dz * inv;

        float* m = (float*)SP_cPlanetModel_BuildSurfaceOrientation2(SP_PlanetModel(), dir);
        uint32_t* out = (uint32_t*)outTransform;
        out[0] = *(uint32_t*)&m[0];
        out[1] = *(uint32_t*)&m[1];
        out[2] = *(uint32_t*)&m[2];
        out[3] = *(uint32_t*)&m[3];
    }
    if (begin != 0 && begin != slotVec)
        operator_delete2(begin);
    return 1;

cleanup_false:
    if (begin != 0 && begin != slotVec)
        operator_delete2(begin);
    return 0;
}

// ===========================================================================
// 0x00bdf600 -- eastl::vector<EA::AutoRefCount<EA::Trace::ILogReporter>*,
// sp_vector_allocator>::do_assign(first, last, false_type).  ecx = vector,
// two iterator args plus the (unused) tag, hence ret 0xc.  The three paths are
// the classic assign split: grow, tail-append and plain copy.
// ===========================================================================
struct false_type {};

// Copies a refcounted element range into fresh storage (AddRef per element) and
// returns the new end.  Args: (out slot, first, last, dest, current value).
void   FUN_00829110(void* out, void* first, void* last, void* dest, void* cur); // 0x00829110
// Copy-assign a refcounted element range, returns the new end: (first, last, dest).
void** FUN_006782c0(void** first, void** last, void** dest);    // 0x006782c0

struct LogReporterVec {
    void**   mpBegin;                                           // +0x00
    void**   mpEnd;                                             // +0x04
    void**   mpCapacity;                                        // +0x08
    uint32_t mAllocator;                                        // +0x0c
    void**   mpInline;                                          // +0x10

    void** DoAllocateAndCopy(int n, void** first, void** last); // 0x00b95280
    void   DoDestroyElements(void** first, void** last);        // 0x00b007f0
    void   do_assign(void** first, void** last, false_type tag);
};

// @ 0x00bdf600
void LogReporterVec::do_assign(void** first, void** last, false_type)
{
    void** begin = mpBegin;
    int n = (int)(last - first);
    if ((unsigned)n > (unsigned)(int)(mpCapacity - begin)) {
        void** buf = DoAllocateAndCopy(n, first, last);
        DoDestroyElements(mpBegin, mpEnd);
        if (mpBegin != 0 && mpBegin != mpInline)
            operator_delete2(mpBegin);
        void** e = buf + n;
        mpBegin = buf;
        mpEnd = e;
        mpCapacity = e;
        return;
    }
    int have = (int)(mpEnd - begin);
    if ((unsigned)n <= (unsigned)have) {
        void** newEnd = FUN_006782c0(first, last, begin);
        DoDestroyElements(newEnd, mpEnd);
        mpEnd = newEnd;
        return;
    }
    void** mid = (void**)((char*)first + have * 4);
    FUN_006782c0(first, mid, begin);
    FUN_00829110(mid, &last, last, mpEnd, last);
    mpEnd = last;
}
