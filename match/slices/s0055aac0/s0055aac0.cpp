// Slice s0055aac0: SP::cFunctionalTestCheat::Execute (the "functionaltest" OTDB cheat).
// Unoptimized module (SPObjectTemplateDB.obj): /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast, no /EHsc.
//
// Options:
//   -get_key_params <name>   look the asset up by name, then dump its OTDB parameters
//   -get_id_params <id>      same, by Pollen server ID (via the asset directory)
//   -query <param>=<value>   list the assets whose integer parameter equals value
//   -test_asset <name> <param>=<value>   test one asset against an integer constraint
//   -touch <name>            touch the asset in the OTDB
//   -reindex                 rebuild the OTDB index
//   -stress                  run random float/integer queries against the OTDB
//
// Types follow the neighbouring slices (s005580e0: FunctionalMatch::Constraint layout and ctors).
// Local names partly come from the dev-build PDB (bDoGetParams, checkKey, va, nParameter, nValue,
// resultList, itEnd, msg, itCur, query, random); assetKey and fVal were chosen to reproduce the /Od
// stack-slot order (every named local and temporary sits on the original's slot). Not byte-exact:
// cl inlines a different subset of the vector-destructor/empty() call sites (see nonmatching.txt).
#include "types.h"

namespace eastl {

struct allocator_tag { allocator_tag() {} };
struct sp_vector_allocator {
    sp_vector_allocator(const allocator_tag& tag);
    const char* mpName;
    uint32_t mFlags;
};

template<typename T, typename A>
struct VectorBase {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    A mAllocator;
    VectorBase(const allocator_tag& a)
        : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(a) {}
    ~VectorBase();
};

template<typename T, typename A = sp_vector_allocator>
class vector : public VectorBase<T, A> {
public:
    typedef VectorBase<T, A> base_type;
    typedef T* iterator;
    vector(const allocator_tag& a = allocator_tag()) : base_type(a) {}
    ~vector() { DoDestroyValues(base_type::mpBegin, base_type::mpEnd); }
    iterator begin() { return base_type::mpBegin; }
    iterator end() { return base_type::mpEnd; }
    bool empty() const;
    void push_back(const T& value);
    iterator erase(iterator first, iterator last);
    void clear() { erase(base_type::mpBegin, base_type::mpEnd); }
    void DoDestroyValues(T* first, T* last) {
        for (; first < last; ++first)
            first->~T();
    }
};

extern char gEmptyString[1];

template<typename T>
class basic_string {
public:
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator;
    basic_string() : mpBegin(0), mpEnd(0), mpCapacity(0) { AllocateSelf(); }
    ~basic_string();
    void AllocateSelf() {
        mpBegin = gEmptyString;
        mpEnd = mpBegin;
        mpCapacity = mpBegin + 1;
    }
    const T* c_str() const { return mpBegin; }
    bool empty() const { return mpBegin == mpEnd; }
};
typedef basic_string<char> string;

}

struct ResourceKey {
    uint32_t mInstanceID;
    uint32_t mTypeID;
    uint32_t mGroupID;
    ResourceKey() : mInstanceID(0), mTypeID(0), mGroupID(0) {}
};

extern "C" __declspec(dllimport) int sscanf(const char* buffer, const char* format, ...);
bool SPKeyFromName(ResourceKey& key, const char* pName, uint32_t defaultType, uint32_t defaultGroup);

namespace SP {
namespace FunctionalMatch {

enum eType {
    kInteger = 48342877,    // 0x2e1a75d
    kFloat = 48343039,      // 0x2e1a7ff
    kTerminal = 48343507    // 0x2e1a9d3
};
enum Sentinel { kEndConstraint = 0 };
enum EqualConstraint { kEquals = 0 };
enum RangeConstraint { kBetween = 0 };
enum ToleranceConstraint { kWithin = 0 };

struct Constraint {
    unsigned int mParameter;
    eType mType;
    union {
        struct { int mMin; int mMax; } mIntVal;
        struct { float mMin; float mMax; } mFloatVal;
    };
    eastl::vector<Constraint, eastl::sp_vector_allocator> mConstraints;

    Constraint(Sentinel);
    Constraint(unsigned int param, ToleranceConstraint, float value, float tolerance);
    Constraint(unsigned int param, RangeConstraint, float minVal, float maxVal);
    Constraint(unsigned int param, EqualConstraint, int value);
};

struct DeclareParam {
    unsigned int mParameter;
    eType mType;
    union { int mIntVal; float mFloatVal; };
};

}

struct cAssetSummary {
    eastl::vector<FunctionalMatch::DeclareParam, eastl::sp_vector_allocator>& GetParameters();
};

class cISPObjectTemplateDB {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05();
    virtual void Reindex(bool bForce, bool bWriteSummarizers);                              // +0x18
    virtual void v07(); virtual void v08();
    virtual bool FindAssets(eastl::vector<ResourceKey, eastl::sp_vector_allocator>& results, int maxResults,
                            const eastl::vector<FunctionalMatch::Constraint, eastl::sp_vector_allocator>& query);  // +0x24
    virtual bool FindAssetsV(eastl::vector<ResourceKey, eastl::sp_vector_allocator>& results, ...);  // +0x28
    virtual void v0b(); virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
    virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
    virtual void v15(); virtual void v16(); virtual void v17();
    virtual void TouchAsset(const ResourceKey& key);                                        // +0x60
    virtual void v19(); virtual void v1a(); virtual void v1b(); virtual void v1c(); virtual void v1d();
    virtual void v1e(); virtual void v1f(); virtual void v20();
    virtual bool TestAsset(const ResourceKey& key, const FunctionalMatch::Constraint& constraint);  // +0x84
};
cISPObjectTemplateDB* ObjectTemplateDB();

// Empty in this build (metadata lookup compiled out).
void GetAssetMetadata(const ResourceKey& key, eastl::string& msg);

namespace Pollen {
class cAssetDirectory {
public:
    bool GetLocalKey(uint64_t serverID, ResourceKey& key);
};
struct cPollenManager {
    uint32_t pad00[0x58 / 4];
    cAssetDirectory* mpAssetDirectory;   // +0x58
};
cPollenManager* GetPollenManager();
inline cAssetDirectory* AssetDirectory() {
    cPollenManager* pManager = GetPollenManager();
    return pManager->mpAssetDirectory;
}
}

}

namespace EA {
namespace StdC { uint64_t StrtoU64(const char* pString, char** ppStringEnd, int nBase); }

namespace Random {
class RandomLinearCongruential {
public:
    RandomLinearCongruential(uint32_t nSeed) { SetSeed(nSeed); }
    void SetSeed(uint32_t nSeed);
    double RandomDoubleUniform();
    uint32_t RandomUint32Uniform(uint32_t nLimit);
    uint32_t mnSeed;
};
}

namespace ResourceMan {
struct IResource {
    virtual int AddRef();
    virtual int Release();
};
struct IResourceManager {
    virtual void v00(); virtual void v01(); virtual void v02();
    virtual bool GetResource(const ResourceKey& key, IResource** ppResource, int a, int b, int c, int d);
};
IResourceManager* GetManager();
}

namespace ArgScript {
class cIParser;
void Output(cIParser* pParser, const char* pFormat, ...);
class cArguments {
public:
    bool HasArgument(const char* pName);
    const char** OptionArguments(const char* pName, int count);
    bool HasFlag(const char* pName);
};
class cCommandBase {
public:
    virtual void v00();
    cIParser* mParser;
    int mRefCount;
};
}
}

template<typename T>
struct IntrusivePtr {
    T* mpObject;
    IntrusivePtr(T* p = 0) : mpObject(p) {
        if (mpObject)
            mpObject->AddRef();
    }
    ~IntrusivePtr() {
        if (mpObject)
            mpObject->Release();
    }
    T** operator&() {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
};

namespace SP {

cAssetSummary* object_cast_summary(IntrusivePtr<EA::ResourceMan::IResource>& res);

struct IntPair { int a; int b; };
// Pairs of integer parameter values (0x2dd90af, 0x2dc9d1e) for the integer stress queries,
// terminated by {-1, -1} (data at 0x013f4358, 28 entries).
extern const IntPair kStressIntegerPairs[];

using namespace FunctionalMatch;
typedef eastl::vector<ResourceKey, eastl::sp_vector_allocator> KeyVector;
typedef eastl::vector<Constraint, eastl::sp_vector_allocator> ConstraintVector;

class cFunctionalTestCheat : public EA::ArgScript::cCommandBase {
public:
    virtual void Execute(EA::ArgScript::cArguments& args);
};

// @ 0x0055AAC0
void cFunctionalTestCheat::Execute(EA::ArgScript::cArguments& args) {
    bool bDoGetParams = false;
    ResourceKey checkKey;
    const char** va;

    if (args.HasArgument("get_key_params") && (va = args.OptionArguments("get_key_params", 1)) != 0) {
        if (SPKeyFromName(checkKey, va[0], 0, 0))
            bDoGetParams = true;
        else
            EA::ArgScript::Output(mParser, "Couldn't parse %s as a key\n", va[0]);
    }

    if (args.HasArgument("get_id_params") && (va = args.OptionArguments("get_id_params", 1)) != 0) {
        uint64_t serverID = EA::StdC::StrtoU64(va[0], 0, 10);
        if (Pollen::AssetDirectory()->GetLocalKey(serverID, checkKey))
            bDoGetParams = true;
        else
            EA::ArgScript::Output(mParser,
                "That server ID (%s) doesn't seem to have been downloaded yet. Try:\npollen -get %s\n",
                va[0], va[0]);
    }

    if (args.HasArgument("query") && (va = args.OptionArguments("query", 1)) != 0) {
        KeyVector resultList;
        unsigned int nParameter, nValue;
        if (sscanf(va[0], "%x=%x", &nParameter, &nValue) == 2) {
            ObjectTemplateDB()->FindAssetsV(resultList, Constraint(nParameter, kEquals, nValue),
                                            Constraint(kEndConstraint));
        }
        if (!resultList.empty()) {
            ResourceKey* it = resultList.begin();
            ResourceKey* itEnd = resultList.end();
            for (; it != itEnd; ++it) {
                const ResourceKey& assetKey = *it;
                eastl::string msg;
                GetAssetMetadata(assetKey, msg);
                EA::ArgScript::Output(mParser, "Asset (T:0x%08x G:0x%08x I:0x%08x)\n",
                                      assetKey.mTypeID, assetKey.mGroupID, assetKey.mInstanceID);
                if (!msg.empty())
                    EA::ArgScript::Output(mParser, "%s\n", msg.c_str());
                else
                    EA::ArgScript::Output(mParser, "Couldn't find metadata\n\n");
            }
        } else {
            EA::ArgScript::Output(mParser, "Query returned no matches\n");
        }
    }

    if (args.HasArgument("test_asset") && (va = args.OptionArguments("test_asset", 2)) != 0 &&
        SPKeyFromName(checkKey, va[0], 0, 0)) {
        unsigned int nParameter, nValue;
        if (sscanf(va[1], "%x=%x", &nParameter, &nValue) == 2) {
            if (ObjectTemplateDB()->TestAsset(checkKey, Constraint(nParameter, kEquals, nValue)))
                EA::ArgScript::Output(mParser, "Yes\n\n");
            else
                EA::ArgScript::Output(mParser, "No\n\n");
        }
    }

    if (args.HasArgument("touch") && (va = args.OptionArguments("touch", 1)) != 0 &&
        SPKeyFromName(checkKey, va[0], 0, 0)) {
        ObjectTemplateDB()->TouchAsset(checkKey);
    }

    if (bDoGetParams) {
        ResourceKey paramsKey = checkKey;
        paramsKey.mTypeID = 0x2d5c9af;
        IntrusivePtr<EA::ResourceMan::IResource> res;
        if (EA::ResourceMan::GetManager()->GetResource(paramsKey, &res, 0, 0, 0, 0)) {
            cAssetSummary* pSummary = object_cast_summary(res);
            DeclareParam* itCur = pSummary->GetParameters().begin();
            DeclareParam* itEnd = pSummary->GetParameters().end();
            if (itCur != itEnd) {
                for (; itCur != itEnd; ++itCur) {
                    if (itCur->mType == kInteger)
                        EA::ArgScript::Output(mParser, "0x%08x  =  %d\n", itCur->mParameter, itCur->mIntVal);
                    else
                        EA::ArgScript::Output(mParser, "0x%08x  =  %f\n", itCur->mParameter,
                                              (double)itCur->mFloatVal);
                }
            } else {
                EA::ArgScript::Output(mParser,
                    "That's weird. Asset %s is in the OTDB, but has no parameters\n", va[0]);
            }
        } else {
            EA::ArgScript::Output(mParser, "Asset %s is not in the OTDB\n", va[0]);
        }
    }

    if (args.HasFlag("reindex"))
        ObjectTemplateDB()->Reindex(true, false);

    if (args.HasFlag("stress")) {
        EA::Random::RandomLinearCongruential random(1);
        ConstraintVector query;
        KeyVector resultList;
        float fVal;

        // Float parameters.
        for (unsigned int i = 0; i < 20; i++) {
            query.clear();

            fVal = (float)(random.RandomDoubleUniform() * 2.5);
            query.push_back(Constraint(0x7358629a, kBetween, fVal - 7.5f, fVal + 7.5f));
            query.push_back(Constraint(0x2f05c58, kWithin, (float)random.RandomUint32Uniform(2), 0.00001f));
            query.push_back(Constraint(0x2f05c59, kWithin, (float)random.RandomUint32Uniform(2), 0.00001f));

            fVal = (float)(random.RandomDoubleUniform() * 16.0 + 9.5);
            query.push_back(Constraint(0x2f05c5e, kBetween, fVal - 7.5f, fVal + 7.5f));
            fVal = (float)(random.RandomDoubleUniform() * 5.0 + 2.5);
            query.push_back(Constraint(0x2f05c5f, kBetween, fVal - 7.5f, fVal + 7.5f));
            fVal = (float)(random.RandomDoubleUniform() * 5.0 + 2.5);
            query.push_back(Constraint(0x2f05c60, kBetween, fVal - 7.5f, fVal + 7.5f));
            fVal = (float)(random.RandomDoubleUniform() * 5.0 + 2.5);
            query.push_back(Constraint(0x2f05c61, kBetween, fVal - 7.5f, fVal + 7.5f));

            fVal = (float)(random.RandomUint32Uniform(3) * 2);
            query.push_back(Constraint(0x3fea1c0, kBetween, fVal - 0.5f, fVal + 0.5f));

            fVal = (float)(random.RandomDoubleUniform() * 5.0 + 2.5);
            query.push_back(Constraint(0x3fea210, kBetween, fVal - 7.5f, fVal + 7.5f));
            fVal = (float)(random.RandomDoubleUniform() * 5.0 + 2.5);
            query.push_back(Constraint(0x3fea1a0, kBetween, fVal - 7.5f, fVal + 7.5f));
            fVal = (float)(random.RandomDoubleUniform() * 5.0 + 2.5);
            query.push_back(Constraint(0x4ab3bd8, kBetween, fVal - 7.5f, fVal + 7.5f));
            fVal = (float)(random.RandomDoubleUniform() * 5.0 + 2.5);
            query.push_back(Constraint(0x4ab3bd9, kBetween, fVal - 7.5f, fVal + 7.5f));
            fVal = (float)(random.RandomDoubleUniform() * 5.0 + 2.5);
            query.push_back(Constraint(0x4ab3bda, kBetween, fVal - 7.5f, fVal + 7.5f));
            fVal = (float)(random.RandomDoubleUniform() * 5.0 + 2.5);
            query.push_back(Constraint(0x4ab3bdb, kBetween, fVal - 7.5f, fVal + 7.5f));
            fVal = (float)(random.RandomDoubleUniform() * 5.0 + 2.5);
            query.push_back(Constraint(0xf42136d5, kBetween, fVal - 7.5f, fVal + 7.5f));
            fVal = (float)(random.RandomDoubleUniform() * 5.0 + 2.5);
            query.push_back(Constraint(0xf42136d6, kBetween, fVal - 7.5f, fVal + 7.5f));
            fVal = (float)(random.RandomDoubleUniform() * 5.0 + 2.5);
            query.push_back(Constraint(0xf42136d7, kBetween, fVal - 7.5f, fVal + 7.5f));
            fVal = (float)(random.RandomDoubleUniform() * 5.0 + 2.5);
            query.push_back(Constraint(0xf42136d8, kBetween, fVal - 7.5f, fVal + 7.5f));

            ObjectTemplateDB()->FindAssets(resultList, 10, query);
        }

        // Integer parameters.
        for (unsigned int j = 0; j < 15; j++) {
            for (int k = 0; kStressIntegerPairs[k].a != -1; k++) {
                query.clear();
                query.push_back(Constraint(0x2dd90af, kEquals, kStressIntegerPairs[k].a));
                query.push_back(Constraint(0x2dc9d1e, kEquals, kStressIntegerPairs[k].b));
                ObjectTemplateDB()->FindAssets(resultList, 10, query);
            }
        }
    }
}

}
