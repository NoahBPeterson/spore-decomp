// Slice s00eef810: FUN_00eef810 -- picks a random ResourceKey (template id) for a game-object kind.
// Two families of ids:
//  * four "verb/theme" ids: a verb list is fetched (FUN_00661900), its entry ids are collected into a
//    uint vector, wrapped in a query object (FUN_00669360, id 0xd87454e6) and resolved through the
//    resource manager (vtable +0x38); a random result is returned.
//  * other ids: a list of property values (fixed_vector<uint,5>) is chosen from the id (and from the
//    type field of the optional object p4), turned into FunctionalMatch::Constraints (a single Equal, or
//    an Any-of-Equals compound), then ObjectTemplateDB (vtable +0x30) is asked for templates matching them,
//    and the first one that the resource manager (vtable +0x0c) accepts is returned.
// Flags: /O2 /MD /Gy /TP (no /EHsc: the original has no EH frame).
#include "types.h"

void* operator new(unsigned int size, void* p) { return p; }
void operator delete[](void* p);        // 0x00F47380

inline void SpFree(void* p)
{
    if (p && ((int*)p)[-1])
        delete[] (char*)p;
}

struct Key3 { uint32_t mInstance, mType, mGroup; };

struct UintVec {   // eastl::vector<uint32_t, sp_vector_allocator>
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mAllocator[2];
    UintVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~UintVec() { SpFree(mpBegin); }
    void reserve(uint32_t n);                                  // 0x004E0880
    void DoInsertValue(uint32_t* pos, const uint32_t& v);      // 0x004558A0
    void push_back(const uint32_t& v)
    {
        if (mpEnd < mpCapacity) {
            uint32_t* p = mpEnd++;
            if (p)
                *p = v;
        } else
            DoInsertValue(mpEnd, v);
    }
};

struct KeyVec {    // eastl::vector<ResourceKey>
    Key3* mpBegin;
    Key3* mpEnd;
    Key3* mpCapacity;
    uint32_t mAllocator[2];
    KeyVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ~KeyVec() { SpFree(mpBegin); }
};

// eastl::fixed_vector<uint32_t, 5, true>: buffer lives inside the object, header word before it is 0.
struct FixedUintVec {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mHeader[3];
    uint32_t mBuffer[5];
    FixedUintVec()
    {
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + 5;
        mHeader[2] = 0;
    }
    ~FixedUintVec() { SpFree(mpBegin); }
    void push_back(const uint32_t& v);                         // 0x0062DEE0
    uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    bool empty() const { return mpBegin == mpEnd; }
    uint32_t& operator[](uint32_t i) { return mpBegin[i]; }
};

// ---- the verb list used by the four theme ids (0x34-byte entries) ----
struct VerbEntry { uint32_t mId; uint32_t pad[12]; };
struct VerbVec {
    VerbEntry* mpBegin;
    VerbEntry* mpEnd;
    VerbEntry* mpCapacity;
    uint32_t mAllocator[2];
    VerbVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    void DoDestroyValues(VerbEntry* first, VerbEntry* last);   // 0x00646D70
    ~VerbVec()
    {
        DoDestroyValues(mpBegin, mpEnd);
        SpFree(mpBegin);
    }
};
void FillVerbList(uint32_t id, VerbVec* out);                  // 0x00661900 (cdecl)

class IMsgHandler { public: virtual ~IMsgHandler() {} };      // vtable 0x013EB394

class IdQuery : public IMsgHandler {    // constructed at 0x00669360
public:
    IdQuery(uint32_t id, const UintVec& ids);
    UintVec mIds;       // 0x04
    uint32_t pad[1];
    uint32_t mId;       // 0x18
};

struct IResourceManager {
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual bool Accept(const Key3* pKey, int a, int b, int c, int d, int e);    // 0x0C
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
    virtual void v30(); virtual void v34();
    virtual void ResolveQuery(KeyVec* out, IdQuery* pQuery, int flags);          // 0x38
};
IResourceManager* GetManager();                                // 0x0067DCD0

class RandomLinearCongruential {
public:
    uint32_t RandomUint32Uniform(uint32_t n);   // 0x00A68FB0
};
extern RandomLinearCongruential sMathRandom;                   // 0x01601760

namespace SP {
namespace FunctionalMatch {
enum EqualConstraint { kEquals = 0 };
enum AnyConstraint { kAny = 0 };
struct Constraint;

struct ConstraintVec {   // eastl::vector<Constraint, sp_vector_allocator>
    Constraint* mpBegin;
    Constraint* mpEnd;
    Constraint* mpCapacity;
    uint32_t mAllocator[2];
    ConstraintVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    ConstraintVec(const ConstraintVec& x);                     // 0x004E38D0
    ~ConstraintVec();                                          // 0x004E1780
    void push_back(const Constraint& c);                       // 0x004E18E0
    void DoInsertValue(Constraint* pos, const Constraint& c);  // 0x004E39D0
    uint32_t size() const;
};

struct Constraint {
    uint32_t mParameter;
    uint32_t mType;
    int mMin, mMax;
    ConstraintVec mConstraints;
    Constraint(uint32_t param, EqualConstraint, int value);    // 0x00558960
    Constraint(AnyConstraint, ConstraintVec subs);             // 0x00558AE0
    Constraint(const Constraint& x);                           // 0x00606880
    ~Constraint();                                             // 0x006066F0
};

__forceinline void PushBackInline(ConstraintVec& v, const Constraint& c)
{
    if (v.mpEnd < v.mpCapacity) {
        Constraint* p = v.mpEnd;
        v.mpEnd = p + 1;
        if (p)
            new (p) Constraint(c);
    } else
        v.DoInsertValue(v.mpEnd, c);
}
}
}
using namespace SP::FunctionalMatch;

struct IObjectTemplateDB {
    virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0C(); virtual void v10();
    virtual void v14(); virtual void v18(); virtual void v1C(); virtual void v20(); virtual void v24();
    virtual void v28(); virtual void v2C();
    virtual bool FindTemplates(KeyVec* out, int count, ConstraintVec* pConstraints);   // 0x30
};
IObjectTemplateDB* ObjectTemplateDB();                         // 0x0067CB40

struct TypedObject { char pad[0x18]; int mType; };

// @ 0x00EEF810
Key3* FUN_00eef810(Key3* out, uint32_t id, int param3, TypedObject* pObj)
{
    if (id == 0x6031c03a || id == 0xe137ff08 || id == 0x7998ce71 || id == 0xcf56099a) {
        uint32_t listId = 0;
        if (id <= 0xcf56099a) {
            if (id == 0xcf56099a)
                listId = 0x41b55d34;
            else if (id == 0x6031c03a)
                listId = 0x61265923;
            else if (id == 0x7998ce71)
                listId = 0x1cccd45b;
        } else if (id == 0xe137ff08)
            listId = 0x0ffc2cee;

        VerbVec verbs;
        FillVerbList(listId, &verbs);
        UintVec ids;
        ids.reserve((uint32_t)(verbs.mpEnd - verbs.mpBegin));
        for (VerbEntry* e = verbs.mpBegin; e != verbs.mpEnd; ++e)
            ids.push_back(e->mId);
        IdQuery query(0xd87454e6, ids);
        KeyVec found;
        GetManager()->ResolveQuery(&found, &query, 0);
        if (found.mpBegin == found.mpEnd) {
            out->mInstance = 0;
            out->mType = 0;
            out->mGroup = 0;
            return out;
        } else {
            uint32_t idx = sMathRandom.RandomUint32Uniform((uint32_t)(found.mpEnd - found.mpBegin));
            *out = found.mpBegin[idx];
            return out;
        }
    }

    FixedUintVec values;
    uint32_t extra = 0;
    uint32_t key;

    if (id <= 0xd37c1045) {
        if (id == 0xd37c1045 || id == 0x5b3d1d0d) {
            if (!pObj)
                goto groupC;
            switch (pObj->mType) {
            case 0x7d433fad: case (int)0xbc1041e6: case (int)0xf670aa43: case (int)0x9ad7d4aa:
            groupC:
                key = 0x7d433fad; values.push_back(key);
                key = 0xf670aa43; values.push_back(key);
                key = 0x9ad7d4aa; values.push_back(key);
                key = 0xbc1041e6; values.push_back(key);
                break;
            case (int)0x8f963dcb: case (int)0xc15695da: case 0x1f2a25b6: case 0x2a5147a9:
                key = 0x8f963dcb; values.push_back(key);
                key = 0x2a5147a9; values.push_back(key);
                key = 0x1f2a25b6; values.push_back(key);
                key = 0xc15695da; values.push_back(key);
                break;
            case 0x441cd3e6: case 0x1a4e0708: case 0x449c040f: case 0x2090a11b: case (int)0x98e03c0d:
                key = 0x441cd3e6; values.push_back(key);
                key = 0x1a4e0708; values.push_back(key);
                key = 0x449c040f; values.push_back(key);
                key = 0x2090a11b; values.push_back(key);
                key = 0x98e03c0d; values.push_back(key);
                break;
            default:
                goto fail;
            }
            if (values.empty())
                goto fail;
        } else if (id == 0xb10e526f)
            extra = 0x2399be55;
        else
            goto fail;
    } else {
        if (id != 0xe34e8a60)
            goto fail;
        if (param3 != -2)
            extra = 0x2b978c46;
        else {
            key = 0x4178b8e8; values.push_back(key);
            if (values.empty())
                goto fail;
        }
    }

    {
        ConstraintVec constraints;
        if (!values.empty()) {
            if (values.size() == 1)
                constraints.push_back(Constraint(0x2dc9d1e, kEquals, values[0]));
            else {
                ConstraintVec alternatives;
                for (uint32_t i = 0; i < values.size(); ++i)
                    alternatives.push_back(Constraint(0x2dc9d1e, kEquals, values[i]));
                constraints.push_back(Constraint(kAny, alternatives));
            }
        }
        if (extra != 0)
            constraints.push_back(Constraint(0x2dd90af, kEquals, extra));
        PushBackInline(constraints, Constraint(0x54a32960, kEquals, 1));

        KeyVec results;
        if (ObjectTemplateDB()->FindTemplates(&results, 0x1e, &constraints) && results.mpBegin != results.mpEnd) {
            for (uint32_t i = 0; i < (uint32_t)(results.mpEnd - results.mpBegin); ++i) {
                Key3* pKey = &results.mpBegin[i];
                if (GetManager()->Accept(pKey, 0, 0, 0, 0, 0)) {
                    *out = *pKey;
                    return out;
                }
            }
        }
    }
fail:
    out->mInstance = 0;
    out->mType = 0;
    out->mGroup = 0;
    return out;
}
