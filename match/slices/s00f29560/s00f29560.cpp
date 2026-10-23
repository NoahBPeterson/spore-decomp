// Slice s00f29560: the script-analysis serializer reader (0xf29560) and the twelve
// ListUI "tree dump" helpers (0xf29650..0xf2a430) that walk an analysis container and
// feed each element to a typed-value callback between BeginList/EndList.
//
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS-   (no /EHsc: 0xf10000-0xf30000 contains
//   no `mov eax,fs:[0]` C++-EH prologue at all; /GS-: none of these functions has a stack
//   cookie, yet 0xf29560 keeps a 0xa14-byte serializer object as a local, which /GS would
//   instrument — so this module was built with the buffer check off)
#include "types.h"

typedef unsigned int size_t;

void __cdecl operator_delete_array(void* p);                          // 0x00F47380

// -------------------------------------------------------------------------------------
// eastl::basic_string<wchar_t, eastl::allocator> — 4 members (the trailing allocator
// makes the object 16 bytes, which is what the callers' frames assume).
namespace eastl {
class allocator { public: };

template <typename T, typename Alloc = allocator>
class basic_string {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    Alloc mAlloc;

    basic_string() : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInitialize(0); }
    basic_string(const basic_string& x);            // 0x0056E2D0
    ~basic_string()
    {
        if ((mpCapacity - mpBegin) > 1) {
            if (mpBegin)
                operator_delete_array(mpBegin);
        }
    }
    void RangeInitialize(const T* p);               // 0x00579A90
};
}  // namespace eastl

namespace EA { eastl::basic_string<wchar_t> ConvertToString16(const char* s, int len); }   // 0x0093C5A0

// The UI object every helper drives: slot 0 BeginList, slot 1 EndList, one wchar_t* arg.
struct ListUI {
    virtual void BeginList(const wchar_t* label);
    virtual void EndList(const wchar_t* label);
};

// The per-element callbacks (all cdecl; arg2 is always pushed as 0).
bool __cdecl FUN_00ac8050(ListUI* ui, int unused, void* value);                          // 0x00AC8050
bool __cdecl FUN_00f28780(ListUI* ui, int unused, void* value);                          // 0x00F28780
bool __cdecl FUN_00f28680(ListUI* ui, int unused, void* value);                          // 0x00F28680
bool __cdecl FUN_00f28580(ListUI* ui, int unused, void* value);                          // 0x00F28580
bool __cdecl FUN_00f28480(ListUI* ui, int unused, void* value);                          // 0x00F28480
bool __cdecl FUN_0057c770(ListUI* ui, int unused, void* value, const wchar_t* type);     // 0x0057C770

// The helpers only touch the first two pointers of the container they walk.
template <class T> struct Vec2 { T* mpBegin; T* mpEnd; };

// Analysis records, one struct per element stride.
struct Info20  { uint32_t m0, m1, m2, m3, m4, m5, m6, m7; };
struct Rec4E0  { uint8_t mData[0x4E0]; };
struct Rec34   { uint8_t mData[0x34]; };
struct Rec188  { uint8_t mData[0x188]; };
struct Rec38   { uint8_t mData[0x38]; };
struct Rec27E8 { uint8_t mData[0x27E8]; };
struct Rec534  { uint8_t mData[0x534]; };
struct Rec27E0 { uint8_t mData[0x27E0]; };

// The fragmented (rope-like) container walked by 0xf29f80: a count at +0x14 plus one
// sentinel count value meaning "walk from mpEnd instead".
struct FragmentedVec {
    uint8_t* mpBegin;
    uint8_t* mpEnd;
    uint8_t* mpCapacity;
    uint32_t mUnk0c;
    uint32_t mUnk10;
    uint32_t mCount;                                            // +0x14
};

// -------------------------------------------------------------------------------------
// 0x00f29560 — read an int32 count, resize, then Serialize() count analysis records
// into the vector.  The original frame is 0xa3c bytes: the serializer object itself
// occupies 0xa14 of them and the four small locals fill the rest.
struct StreamObj {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14();
    virtual void* GetRaw();                                     // +0x18 -> the raw EA::IO stream
    virtual void v1c();
};

struct ISerialStream {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
    virtual void v10(); virtual void v14(); virtual void v18();
    virtual void Done();                                        // +0x1c
    virtual StreamObj* GetInner();                              // +0x20
};

namespace EA { namespace IO { void ReadInt32(void* stream, unsigned int* dst, unsigned int count, int flag); } }   // 0x0093A780

extern uint8_t g_cDataSerializerGeneric;                        // 0x015ADD00

struct cVarListSerializer {
    uint8_t mData[0xA14];
    cVarListSerializer(void* info, void* generic, unsigned int id);          // 0x00692F90
    bool Serialize(ISerialStream* stream);                                   // 0x00693E10
};

struct AnalysisInfoVec {
    Info20* mpBegin;
    Info20* mpEnd;
    Info20* mpCapacity;

    void erase(Info20* first, Info20* last);                    // 0x00899420
    void resize(int count);                                     // 0x00F281F0
    Info20* insert(Info20* pos, const Info20* value);           // 0x00C06C30
};

// @ 0x00f29560
void __cdecl DeserializeAnalysisInfos(ISerialStream* s, AnalysisInfoVec* v)
{
    v->erase(v->mpBegin, v->mpEnd);

    unsigned int count = 0;
    void* raw = s->GetInner()->GetRaw();
    EA::IO::ReadInt32(raw, &count, 1, 0);
    v->resize(count);

    for (unsigned int i = 0; i < count; ++i)
    {
        Info20 info;
        cVarListSerializer ser(&info, &g_cDataSerializerGeneric, 0x1a80d26);
        ser.Serialize(s);

        if (v->mpEnd < v->mpCapacity)
        {
            Info20* const dst = v->mpEnd;
            v->mpEnd = dst + 1;
            if (dst)
                *dst = info;
        }
        else
            v->insert(v->mpEnd, &info);
    }

    s->Done();
}

// -------------------------------------------------------------------------------------
// The list/map/set dumpers: guarded body, `ok = ok && Elem(...)`.
// @ 0x00f29650
bool __cdecl PopulateAnalysisList(ListUI* ui, const char* name, Vec2<Info20>* v)
{
    bool ok = true;
    if (v->mpBegin != v->mpEnd)
    {
        const eastl::basic_string<wchar_t> s(name ? EA::ConvertToString16(name, -1) : eastl::basic_string<wchar_t>());
        const wchar_t* const pBegin = s.mpBegin;
        ui->BeginList(pBegin == s.mpEnd ? L"list" : pBegin);

        Info20* const end = v->mpEnd;
        for (Info20* it = v->mpBegin; it != end; ++it)
            ok = ok && FUN_00ac8050(ui, 0, it);

        ui->EndList(pBegin == s.mpEnd ? L"list" : pBegin);
    }
    return ok;
}

// @ 0x00f297a0
bool __cdecl PopulateRec4E0List(ListUI* ui, const char* name, Vec2<Rec4E0>* v)
{
    bool ok = true;
    if (v->mpBegin != v->mpEnd)
    {
        const eastl::basic_string<wchar_t> s(name ? EA::ConvertToString16(name, -1) : eastl::basic_string<wchar_t>());
        const wchar_t* const pBegin = s.mpBegin;
        ui->BeginList(pBegin == s.mpEnd ? L"list" : pBegin);

        Rec4E0* const end = v->mpEnd;
        for (Rec4E0* it = v->mpBegin; it != end; ++it)
            ok = ok && FUN_00f28780(ui, 0, it);

        ui->EndList(pBegin == s.mpEnd ? L"list" : pBegin);
    }
    return ok;
}

// @ 0x00f298f0
bool __cdecl PopulateRec34List(ListUI* ui, const char* name, Vec2<Rec34>* v)
{
    bool ok = true;
    if (v->mpBegin != v->mpEnd)
    {
        const eastl::basic_string<wchar_t> s(name ? EA::ConvertToString16(name, -1) : eastl::basic_string<wchar_t>());
        const wchar_t* const pBegin = s.mpBegin;
        ui->BeginList(pBegin == s.mpEnd ? L"list" : pBegin);

        Rec34* const end = v->mpEnd;
        for (Rec34* it = v->mpBegin; it != end; ++it)
            ok = ok && FUN_00ac8050(ui, 0, it);

        ui->EndList(pBegin == s.mpEnd ? L"list" : pBegin);
    }
    return ok;
}

// @ 0x00f29a40
bool __cdecl PopulateRec188List(ListUI* ui, const char* name, Vec2<Rec188>* v)
{
    bool ok = true;
    if (v->mpBegin != v->mpEnd)
    {
        const eastl::basic_string<wchar_t> s(name ? EA::ConvertToString16(name, -1) : eastl::basic_string<wchar_t>());
        const wchar_t* const pBegin = s.mpBegin;
        ui->BeginList(pBegin == s.mpEnd ? L"list" : pBegin);

        Rec188* const end = v->mpEnd;
        for (Rec188* it = v->mpBegin; it != end; ++it)
            ok = ok && FUN_00f28680(ui, 0, it);

        ui->EndList(pBegin == s.mpEnd ? L"list" : pBegin);
    }
    return ok;
}

// @ 0x00f29b90
bool __cdecl PopulateRec38List(ListUI* ui, const char* name, Vec2<Rec38>* v)
{
    bool ok = true;
    if (v->mpBegin != v->mpEnd)
    {
        const eastl::basic_string<wchar_t> s(name ? EA::ConvertToString16(name, -1) : eastl::basic_string<wchar_t>());
        const wchar_t* const pBegin = s.mpBegin;
        ui->BeginList(pBegin == s.mpEnd ? L"list" : pBegin);

        Rec38* const end = v->mpEnd;
        for (Rec38* it = v->mpBegin; it != end; ++it)
            ok = ok && FUN_00ac8050(ui, 0, it);

        ui->EndList(pBegin == s.mpEnd ? L"list" : pBegin);
    }
    return ok;
}

// @ 0x00f29ce0
bool __cdecl PopulateRec27E8Map(ListUI* ui, const char* name, Vec2<Rec27E8>* v)
{
    bool ok = true;
    if (v->mpBegin != v->mpEnd)
    {
        const eastl::basic_string<wchar_t> s(name ? EA::ConvertToString16(name, -1) : eastl::basic_string<wchar_t>());
        const wchar_t* const pBegin = s.mpBegin;
        ui->BeginList(pBegin == s.mpEnd ? L"map" : pBegin);

        Rec27E8* const end = v->mpEnd;
        for (Rec27E8* it = v->mpBegin; it != end; ++it)
            ok = ok && FUN_00f28480(ui, 0, it->mData + 8);

        ui->EndList(pBegin == s.mpEnd ? L"map" : pBegin);
    }
    return ok;
}

// @ 0x00f29e30
bool __cdecl PopulateRec534List(ListUI* ui, const char* name, Vec2<Rec534>* v)
{
    bool ok = true;
    if (v->mpBegin != v->mpEnd)
    {
        const eastl::basic_string<wchar_t> s(name ? EA::ConvertToString16(name, -1) : eastl::basic_string<wchar_t>());
        const wchar_t* const pBegin = s.mpBegin;
        ui->BeginList(pBegin == s.mpEnd ? L"list" : pBegin);

        Rec534* const end = v->mpEnd;
        for (Rec534* it = v->mpBegin; it != end; ++it)
            ok = ok && FUN_00f28580(ui, 0, it);

        ui->EndList(pBegin == s.mpEnd ? L"list" : pBegin);
    }
    return ok;
}

// @ 0x00f29f80
bool __cdecl PopulateFragmentedList(ListUI* ui, const char* name, FragmentedVec* v)
{
    bool ok = true;
    if (v->mCount != 0x3fffffff)
    {
        const eastl::basic_string<wchar_t> s(name ? EA::ConvertToString16(name, -1) : eastl::basic_string<wchar_t>());
        const wchar_t* const pBegin = s.mpBegin;
        ui->BeginList(pBegin == s.mpEnd ? L"list" : pBegin);

        uint8_t* const end = v->mpEnd;
        uint8_t* it = v->mCount < 0x3fffffff ? v->mpBegin + v->mCount * 0x238 : v->mpEnd;
        if (it != end)
        {
            do
            {
                ok = ok && FUN_00ac8050(ui, 0, it + 4);

                // Step over the run of sub-records this fragment covers.
                do
                {
                    const uint32_t flags = *(const uint32_t*)it;
                    it += 0x238;
                    if ((flags >> 30) & 1)
                        break;
                } while ((*(const uint32_t*)it >> 31) & 1);
            } while (it != end);
        }

        ui->EndList(pBegin == s.mpEnd ? L"list" : pBegin);
    }
    return ok;
}

// @ 0x00f2a100
bool __cdecl PopulateIntList(ListUI* ui, const char* name, Vec2<int>* v)
{
    bool ok = true;
    if (v->mpBegin != v->mpEnd)
    {
        const eastl::basic_string<wchar_t> s(name ? EA::ConvertToString16(name, -1) : eastl::basic_string<wchar_t>());
        const wchar_t* const pBegin = s.mpBegin;
        ui->BeginList(pBegin == s.mpEnd ? L"set" : pBegin);

        int* const end = v->mpEnd;
        for (int* it = v->mpBegin; it != end; ++it)
            ok = ok && FUN_0057c770(ui, 0, it, L"int32_t");

        ui->EndList(pBegin == s.mpEnd ? L"set" : pBegin);
    }
    return ok;
}

// @ 0x00f2a250
bool __cdecl PopulateRec27E0List(ListUI* ui, const char* name, Vec2<Rec27E0>* v)
{
    bool ok = true;
    if (v->mpBegin != v->mpEnd)
    {
        const eastl::basic_string<wchar_t> s(name ? EA::ConvertToString16(name, -1) : eastl::basic_string<wchar_t>());
        const wchar_t* const pBegin = s.mpBegin;
        ui->BeginList(pBegin == s.mpEnd ? L"list" : pBegin);

        Rec27E0* const end = v->mpEnd;
        for (Rec27E0* it = v->mpBegin; it != end; ++it)
            ok = ok && FUN_00f28480(ui, 0, it);

        ui->EndList(pBegin == s.mpEnd ? L"list" : pBegin);
    }
    return ok;
}

// -------------------------------------------------------------------------------------
// 0x00f2a3a0 — eastl::vector<0x18-byte element>::insert: the in-place fast path when
// pos is the end and there is spare capacity, otherwise the out-of-line reallocator.
struct Elem18 { uint32_t m0, m1, m2, m3, m4, m5; };

struct Vec18 {
    Elem18* mpBegin;
    Elem18* mpEnd;
    Elem18* mpCapacity;

    void DoInsertSlow(Elem18* pos, const Elem18& value);        // 0x00F29170
    Elem18* insert(Elem18* pos, const Elem18& value);
};

// @ 0x00f2a3a0
Elem18* Vec18::insert(Elem18* pos, const Elem18& value)
{
    const int index = (int)(pos - mpBegin);
    Elem18* const p = mpEnd;
    if (pos == p && p != mpCapacity)
    {
        mpEnd = p + 1;
        if (p)
        {
            *p = value;
            return mpBegin + index;
        }
    }
    else
        DoInsertSlow(pos, value);
    return mpBegin + index;
}

// -------------------------------------------------------------------------------------
// 0x00f2a430 — copy-assign from one source element into [dst, dstEnd).
struct Vec20B {                                                 // 20-byte member with its own operator=
    uint32_t m0, m1, m2, m3, m4;
    Vec20B& operator=(const Vec20B& x);                         // 0x00473500
};

struct Elem34 {
    float m0;
    uint32_t m1, m2, m3, m4, m5, m6;
    Vec20B mVec;
    uint32_t m7;
};

// @ 0x00f2a430
void __cdecl CopyElem34Range(Elem34* dst, Elem34* dstEnd, const Elem34* src)
{
    if (dst != dstEnd)
    {
        do
        {
            *dst = *src;
            ++dst;
        } while (dst != dstEnd);
    }
}
