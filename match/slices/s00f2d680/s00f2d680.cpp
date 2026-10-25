// Slice s00f2d680 -- Simulator scenario/action object region (bfs2 slice 10).
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE  (scalar movss float ops; no x87 copies).
// Class layouts reconstructed from the disassembly; no real names were recoverable for this
// region from the 2008 dev PDB.
#include "types.h"

// ---------------------------------------------------------------- masked externals
void* __cdecl EA_Alloc(size_t, const char*, int, int, const char*, int);  // 0x00F473A0
void  __cdecl EA_Delete(void*);                                           // 0x00F47380

// raw element-mover helpers (out-of-line template instantiations in the original)

// ---------------------------------------------------------------- fixed_vector<0x44,5>
struct E44 { char pad[0x44]; };

struct FixedVec5 {
    E44* mpBegin;        // +0x00
    E44* mpEnd;          // +0x04
    E44* mpCapacity;     // +0x08
    int  mPad0c;         // +0x0c
    int  mPad10;         // +0x10
    int  mZero14;        // +0x14
    E44  mBuf[5];        // +0x18
    void resize5(int n); // 0x00F0B390 (thiscall, ret 4)
};

// ---------------------------------------------------------------- cString (0x14 in retail)
struct CString {
    char pad[0x14];
    void ctor();                       // 0x006B5060
};

extern wchar_t g_emptyW[];             // 0x01667BAC
extern wchar_t g_emptyW2[];            // 0x01667BAE

// ---------------------------------------------------------------- the 0x4e0 element
struct E4e0 {
    unsigned char mData[0x4e0];
    E4e0();
    void Destroy();                        // 0x00DFBBA0 (thiscall)
    void CopyCtor(const E4e0& src);        // 0x00DFD080 (thiscall, ecx=dst)
    void Assign(const E4e0& src);          // 0x00DFCCE0 (thiscall, ecx=dst)
    void Serialize(void* owner);           // 0x00F2D090 (thiscall, ecx=this, owner on stack)
};
E4e0* __cdecl CopyRange4e0(E4e0* first, E4e0* last, E4e0* dst);      // 0x00F2CE90
void  __cdecl DestroyRange4e0(E4e0* first, E4e0* last, E4e0* dst);   // 0x00F2BC70
void  __cdecl MoveBackward4e0(E4e0* first, E4e0* last, E4e0* dst);   // 0x00F2CF60

// @ 0x00F2D680
E4e0::E4e0()
{
    unsigned char* b = mData;
    b[0] = 1;
    b[1] = 0;
    b[2] = 0;

    *(void**)(b + 0x04) = b + 0x1c;
    *(void**)(b + 0x08) = b + 0x1c;
    *(void**)(b + 0x0c) = b + 0x170;
    *(int*)(b + 0x18) = 0;
    ((FixedVec5*)(b + 0x04))->resize5(5);

    *(void**)(b + 0x170) = b + 0x188;
    *(void**)(b + 0x174) = b + 0x188;
    *(void**)(b + 0x178) = b + 0x2dc;
    *(int*)(b + 0x184) = 0;
    ((FixedVec5*)(b + 0x170))->resize5(5);

    *(void**)(b + 0x2dc) = b + 0x2f4;
    *(void**)(b + 0x2e0) = b + 0x2f4;
    *(void**)(b + 0x2e4) = b + 0x448;
    *(int*)(b + 0x2f0) = 0;

    ((CString*)(b + 0x448))->ctor();
    *(wchar_t**)(b + 0x45c) = g_emptyW;
    *(wchar_t**)(b + 0x460) = g_emptyW;
    *(wchar_t**)(b + 0x464) = g_emptyW2;
    *(int*)(b + 0x46c) = 0;
    *(int*)(b + 0x470) = 0;
    *(wchar_t**)(b + 0x474) = g_emptyW;
    *(wchar_t**)(b + 0x478) = g_emptyW;
    *(wchar_t**)(b + 0x47c) = g_emptyW2;

    *(float*)(b + 0x484) = 50.0f;
    *(float*)(b + 0x488) = 20.0f;
    *(float*)(b + 0x48c) = 1.0f;
    *(float*)(b + 0x490) = 1.0f;
    *(float*)(b + 0x494) = 1.0f;
    *(int*)(b + 0x4a4) = -1;
    *(int*)(b + 0x4a8) = 0;
    *(int*)(b + 0x4ac) = 0;
    *(int*)(b + 0x4b0) = 0;
    *(int*)(b + 0x4b4) = 0;
    *(int*)(b + 0x4b8) = 0;
    *(int*)(b + 0x4bc) = -1;
    *(int*)(b + 0x4c0) = -1;
    *(int*)(b + 0x4c4) = -1;
    b[0x4c8] = 0;
    *(float*)(b + 0x498) = 10.0f;
    *(float*)(b + 0x49c) = 10.0f;
    *(float*)(b + 0x4a0) = 10.0f;
    *(int*)(b + 0x4cc) = 0;
    *(int*)(b + 0x4d0) = 0;
    *(int*)(b + 0x4d4) = 0;
}

// ---------------------------------------------------------------- generic 0x4e0 vector
struct Vec4e0 {
    E4e0* mpBegin;       // +0x00
    E4e0* mpEnd;         // +0x04
    E4e0* mpCapacity;    // +0x08
    void set_capacity(unsigned n);
    void Clear(E4e0* begin, E4e0* end);                // 0x00F2DD70 (thiscall, returns new end; ret 8)
    E4e0* Insert(E4e0* position, const E4e0& value);
};

// serializer owner: vtable +0x20 -> object whose vtable +0x18 -> stream, and owner +0x1C after the loop
struct IStreamOwner {
    virtual void s00(); virtual void s04(); virtual void s08(); virtual void s0c();
    virtual void s10(); virtual void s14();
    virtual void* GetStream();                          // +0x18
    virtual void Finish();                              // +0x1C
    virtual void* GetChild();                           // +0x20
};

// @ 0x00F2DBE0
void Vec4e0::set_capacity(unsigned n)
{
    if (n > (unsigned)(mpCapacity - mpBegin)) {
        E4e0* pNewData = n ? (E4e0*)EA_Alloc(n * 0x4e0, "Simulator", 0, 0,
                                             "allocator.h", 0xd1) : 0;
        E4e0* pOldEnd = mpEnd;
        E4e0* pOldBegin = mpBegin;
        CopyRange4e0(pOldBegin, pOldEnd, pNewData);
        DestroyRange4e0(pOldBegin, pOldEnd, pNewData);
        if (mpBegin && ((int*)mpBegin)[-1])
            EA_Delete(mpBegin);
        unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewData + nPrevSize;
        mpCapacity = pNewData + n;
    }
}

// @ 0x00F2DF80 (inlined generic insert; growth path uses doubling)
E4e0* Vec4e0::Insert(E4e0* position, const E4e0& value)
{
    if (mpEnd != mpCapacity) {
        E4e0* pValue = (E4e0*)&value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        if (mpEnd)
            mpEnd->CopyCtor(mpEnd[-1]);
        MoveBackward4e0(position, mpEnd - 1, mpEnd);
        position->Assign(*pValue);
        ++mpEnd;
    } else {
        unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
        unsigned nNewSize = nPrevSize ? nPrevSize * 2 : 1;
        E4e0* pNewData = nNewSize ? (E4e0*)EA_Alloc(nNewSize * 0x4e0, "Simulator", 0, 0,
                                                    "allocator.h", 0xd1) : 0;
        E4e0* p = CopyRange4e0(mpBegin, position, pNewData);
        DestroyRange4e0(mpBegin, position, pNewData);
        if (p)
            p->CopyCtor(value);
        E4e0* pNewEnd = CopyRange4e0(position, mpEnd, p + 1);
        DestroyRange4e0(position, mpEnd, p + 1);
        if (mpBegin && ((int*)mpBegin)[-1])
            EA_Delete(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
    return position;
}

// ---------------------------------------------------------------- 0x238 element / vector
struct E238 {
    char pad[0x238];
    E238();
    void Destroy();                        // 0x00DFE???
    void CopyCtor(const E238& src);        // 0x00DFDFE0 (thiscall, ecx=dst)
    void Assign(const E238& src);          // 0x00DFE170 (thiscall, ecx=dst)
};

E238* __cdecl CopyRange238(E238* first, E238* last, E238* dst);      // 0x00F2D5E0
void  __cdecl DestroyRange238(E238* first, E238* last, E238* dst);   // 0x00F2BBD0
void  __cdecl MoveBackward238(E238* first, E238* last, E238* dst);   // 0x00F2D640

struct Vec238 {
    E238* mpBegin;
    E238* mpEnd;
    E238* mpCapacity;
    void set_capacity(unsigned n);
    E238* Insert(E238* position, const E238& value);
};

// @ 0x00F2E230
void Vec238::set_capacity(unsigned n)
{
    if (n > (unsigned)(mpCapacity - mpBegin)) {
        E238* pNewData = n ? (E238*)EA_Alloc(n * 0x238, "Simulator", 0, 0,
                                             "allocator.h", 0xd1) : 0;
        E238* pOldEnd = mpEnd;
        E238* pOldBegin = mpBegin;
        CopyRange238(pOldBegin, pOldEnd, pNewData);
        DestroyRange238(pOldBegin, pOldEnd, pNewData);
        if (mpBegin)
            EA_Delete(mpBegin);
        unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewData + nPrevSize;
        mpCapacity = pNewData + n;
    }
}

// ---------------------------------------------------------------- serializers
extern void* __cdecl ObjectTemplateDB();       // 0x0067CB40
void  __cdecl ReadInt32(void* stream, void* out, int n, int flag);  // 0x0093A780
void  __cdecl SerializeElement(void* obj, void* v);   // 0x00F2D090
void  __cdecl DestroyElement4e0(void* p);             // 0x00DFD080
void  __cdecl DestroyElement238(void* p);             // 0x00DFDFE0
void  __cdecl CopyElement4e0(void* dst, const void* src);  // 0x00DFCCE0
void  __cdecl CopyElement238(void* dst, const void* src);  // 0x00DFE170
void* __cdecl GetStream(void* obj);            // vtable [0x18] accessor

// @ 0x00F2E370
void __cdecl SerializeVec4e0(void* reader, Vec4e0* vec)
{
    vec->Clear(vec->mpBegin, vec->mpEnd);
    unsigned count = 0;
    IStreamOwner* pReader = (IStreamOwner*)reader;
    IStreamOwner* pChild = (IStreamOwner*)pReader->GetChild();
    void* stream = pChild->GetStream();
    ReadInt32(stream, &count, 1, 0);
    vec->set_capacity(count);
    for (unsigned i = 0; i < count; ++i) {
        E4e0 tmp;
        tmp.Serialize(reader);
        if (vec->mpEnd < vec->mpCapacity) {
            E4e0* slot = vec->mpEnd++;
            if (slot)
                slot->CopyCtor(tmp);
        } else {
            vec->Insert(vec->mpEnd, tmp);
        }
        tmp.Destroy();
    }
    pReader->Finish();
}

// @ 0x00F2E440
void SerializeVec188(void* vec, void* owner)
{
    unsigned count = 0;
    void* stream = GetStream(owner);
    ReadInt32(stream, &count, 1, 0);
    (void)vec;
    (void)count;
}

// @ 0x00F2E5D0
E238* Vec238::Insert(E238* position, const E238& value)
{
    if (mpEnd != mpCapacity) {
        E238* pValue = (E238*)&value;
        if ((pValue >= position) && (pValue < mpEnd))
            ++pValue;
        if (mpEnd)
            mpEnd->CopyCtor(mpEnd[-1]);
        MoveBackward238(position, mpEnd - 1, mpEnd);
        position->Assign(*pValue);
        ++mpEnd;
    } else {
        unsigned nPrevSize = (unsigned)(mpEnd - mpBegin);
        unsigned nNewSize = nPrevSize ? nPrevSize * 2 : 1;
        E238* pNewData = nNewSize ? (E238*)EA_Alloc(nNewSize * 0x238, "Simulator", 0, 0,
                                                    "allocator.h", 0xd1) : 0;
        E238* p = CopyRange238(mpBegin, position, pNewData);
        DestroyRange238(mpBegin, position, pNewData);
        if (p)
            p->CopyCtor(value);
        E238* pNewEnd = CopyRange238(position, mpEnd, p + 1);
        DestroyRange238(position, mpEnd, p + 1);
        if (mpBegin)
            EA_Delete(mpBegin);
        mpBegin = pNewData;
        mpEnd = pNewEnd;
        mpCapacity = pNewData + nNewSize;
    }
    return position;
}

// @ 0x00F2D7E0 -- serialize this 0x4e0 element from a cVarListSerializer / reader
int SerializeE4e0(void* self, void* reader)
{
    // Layout of the local frame is huge; behaviour: read via cVarListSerializer, then
    // adjust an embedded 0x34 element array and clamp positions.
    (void)self; (void)reader;
    return 0;
}

// ---------------------------------------------------------------- constraint evaluator
struct Constraint;

// the nested constraint list occupies +0x10..+0x1f of a Constraint node
struct ConstraintVec {
    Constraint* mpBegin;
    Constraint* mpEnd;
    Constraint* mpCapacity;
    void*       mpOwner;                                          // allocator/owner slot copied by grow
    void DoInsertValue(Constraint* pos, const Constraint& v);    // 0x004E39D0 (thiscall)
    void destroy(Constraint* first, Constraint* last);           // 0x004E39A0 (thiscall)
};

// 0x24-byte constraint node; ctor 0x00558960 stores (param, kInteger, value, value+1)
// and zeroes the nested constraint vector at +0x10.
struct Constraint {
    unsigned      mParameter;   // +0x00
    unsigned      mType;        // +0x04
    int           mMin;         // +0x08
    int           mMax;         // +0x0c
    ConstraintVec mNested;      // +0x10
    int           mPad20;       // +0x20
    void ctor(unsigned param, int kind, int value);   // 0x00558960 (thiscall, ret 0xc)
    void DestroyNested()
    {
        mNested.destroy(mNested.mpBegin, mNested.mpEnd);
        if (mNested.mpBegin && ((int*)mNested.mpBegin)[-1])
            EA_Delete(mNested.mpBegin);
    }
};

void __cdecl ConstraintCopyCtor(Constraint* dst, const Constraint& src);  // 0x00606880

// 0x0c-byte result element returned by the template DB query.
struct ConstraintResult { char mData[0xc]; };
struct ResultVec {
    ConstraintResult* mpBegin;
    ConstraintResult* mpEnd;
    ConstraintResult* mpCapacity;
};
void __cdecl FinalizeResult(ConstraintResult* elem);   // 0x00F27E00

struct TemplateDB {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
    virtual void v30(); virtual void v34();
    virtual void Query(ConstraintVec* constraints, ResultVec* out);   // vtable +0x38
};

// append one constraint, inlined push_back with out-of-line growth
static void AppendConstraint(ConstraintVec& v, Constraint& c)
{
    if (v.mpEnd < v.mpCapacity) {
        Constraint* slot = v.mpEnd++;
        if (slot)
            ConstraintCopyCtor(slot, c);
    } else {
        v.DoInsertValue(v.mpEnd, c);
    }
}

// @ 0x00F2DDE0
void EvaluateConstraints()
{
    ConstraintVec constraints = { 0, 0, 0, 0 };
    ResultVec     results     = { 0, 0, 0 };

    Constraint c0;
    c0.ctor(0x2dd90af, 0, 0x366a930d);
    AppendConstraint(constraints, c0);
    c0.DestroyNested();

    Constraint c1;
    c1.ctor(0x15e8afc8, 0, 1);
    AppendConstraint(constraints, c1);
    c1.DestroyNested();

    TemplateDB* db = (TemplateDB*)ObjectTemplateDB();
    db->Query(&constraints, &results);

    unsigned n = (unsigned)(results.mpEnd - results.mpBegin);
    for (unsigned i = 0; i < n; ++i)
        FinalizeResult(&results.mpBegin[i]);

    if (results.mpBegin && ((int*)results.mpBegin)[-1])
        EA_Delete(results.mpBegin);

    constraints.destroy(constraints.mpBegin, constraints.mpEnd);
    if (constraints.mpBegin && ((int*)constraints.mpBegin)[-1])
        EA_Delete(constraints.mpBegin);
}

