// Slice s0055a550: SP::Audio parameter tables / extraction (unoptimized /Od module).
#include "types.h"
#include <string.h>
#pragma intrinsic(wcscmp)

// Reserves N unused /Od frame dwords (stands in for the frame of an inline helper cl declined).
template <int N> inline void ScratchSlots()
{
    uint32_t s[N];
    (void)s;
}

uint32_t FNV1_String8(const char* s, uint32_t seed, int caseSens);   // 0x00932e80
extern const wchar_t* g_TagTarget;                                   // 0x00150cbcc

namespace EA { namespace ResourceMan {
class Key {
public:
    uint32_t instance;      // +0x00
    uint32_t type;          // +0x04
    uint32_t group;         // +0x08
};

struct ResourceObject {
    virtual int AddRef();       // +0x00
    virtual int Release();      // +0x04
};

struct IResourceManager {
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual bool GetResource(const Key& key, ResourceObject** ppOut, int, int, int, int);  // +0x0c
};

IResourceManager* GetManager();   // 0x0067dcd0
}}

// Intrusive ref pointer (EA AutoRefCount-style); AsPointer() releases the old object first.
template <class T> struct ResourcePtr {
    T* mpObject;
    ResourcePtr() {}
    ~ResourcePtr() { if (mpObject) mpObject->Release(); }
    T** AsPointer()
    {
        if (mpObject) {
            T* const pTemp = mpObject;
            mpObject = 0;
            pTemp->Release();
        }
        return &mpObject;
    }
};

namespace SP {

class IConfigManager {
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
    virtual int GetInt(uint32_t id);   // +0x30
};

IConfigManager* ConfigManager();   // 0x0067dd30

namespace FunctionalMatch {

struct DeclareParam {
    uint32_t mParameter;      // +0x00
    int mType;                // +0x04
    union { int mIntVal; float mFloatVal; };   // +0x08
    DeclareParam(uint32_t parameter, int value);   // 0x00558bc0
};

} // namespace FunctionalMatch

} // namespace SP

namespace eastl {
template <class T> struct sp_vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    uint32_t mAllocator;
    void push_back(const T& value);   // 0x004e19a0
};
}

namespace SP {

struct cEditorResource {
    char pad0[0x18];
    uint32_t mModelType;       // +0x18
};

namespace Pollen {

struct Meta {                  // cAssetMetadata
    int64_t GetAssetKey();               // 0x005508a0
    const wchar_t* GetName();            // 0x00550880
    uint32_t GetTagCount();              // 0x005509b0
    uint32_t GetCount2();                // 0x005508e0
    const char* GetItem(uint32_t i);     // 0x00550910
    const wchar_t* GetTag(uint32_t i);   // 0x005509e0
    bool IsShared();                     // 0x00550970
    uint64_t* GetStamp();                // 0x00550860
};

Meta* GetModelInfo(void** ppRef);                   // 0x00421f60
cEditorResource* GetEditorResource(void** ppRef);   // 0x00421eb0

} // namespace Pollen

namespace Feed {
int GetFeedTypeFromURI(const char* uri);   // 0x005419c0
}

namespace Audio {

class cCityMusicSummarizer {
public:
    uint32_t GetParamId(uint32_t index);
    uint32_t GetParamType(uint32_t index);
    bool ExtractParameters(const EA::ResourceMan::Key& desc,
                           eastl::sp_vector<FunctionalMatch::DeclareParam>* pOut);
};

// @ 0x0055A550
uint32_t cCityMusicSummarizer::GetParamId(uint32_t index) {
    static const uint32_t s_table[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    if (index < 8)
        return s_table[index];
    return 0xffffffff;
}

// @ 0x0055A9D0
uint32_t cCityMusicSummarizer::GetParamType(uint32_t index) {
    static const uint32_t s_table[6] = { 0, 0, 0, 0, 0, 0 };
    if (index < 6)
        return s_table[index];
    return 0xffffffff;
}

class cMetadataSummarizer {
public:
    bool ExtractParameters(const EA::ResourceMan::Key& desc,
                           eastl::sp_vector<FunctionalMatch::DeclareParam>* pOut);
};

// @ 0x0055A580
bool cMetadataSummarizer::ExtractParameters(const EA::ResourceMan::Key& desc,
                                            eastl::sp_vector<FunctionalMatch::DeclareParam>* pOut)
{
    using namespace FunctionalMatch;

    EA::ResourceMan::IResourceManager* prev = EA::ResourceMan::GetManager();

    pOut->push_back(DeclareParam(0x2dd90af, (int)desc.type));

    EA::ResourceMan::Key key;
    key = desc;
    key.type = 0x30bdee3;

    ResourcePtr<EA::ResourceMan::ResourceObject> base;
    base.mpObject = 0;
    bool ok = false;
    {
        ScratchSlots<2>();
    }
    if (prev != 0) {
        if (prev->GetResource(key, base.AsPointer(), 0, 0, 0, 0)) {
            {
                ScratchSlots<10>();
            }
            uint32_t bucket;
            bool v6;
            uint32_t v22;
            Pollen::Meta* t20;
            uint32_t n17;
            uint64_t n24;
            int n26;
            int p30;

            t20 = Pollen::GetModelInfo((void**)&base.mpObject);
            ok = true;

            pOut->push_back(DeclareParam(0x5fb4759, t20->IsShared() != 0));

            bucket = t20->GetCount2();
            p30 = 0;
            v6 = true;
            for (uint32_t i = 0; i < bucket; ++i) {
                int lo;
                const char* pOld;
                int pBegin;
                pOld = t20->GetItem(i);
                pOut->push_back(DeclareParam(0x3cc89b1, (int)FNV1_String8(pOld, 0x811c9dc5, 1)));

                pBegin = Feed::GetFeedTypeFromURI(pOld);
                lo = 2;
                switch (pBegin) {
                case 9:
                    lo = 0;
                    break;
                case 4: case 5: case 6:
                    lo = 1;
                    break;
                default:
                    break;
                }
                if (lo > p30)
                    p30 = lo;

                switch (pBegin) {
                case 0: case 1: case 3: case 4: case 5: case 6:
                    v6 = false;
                    break;
                default:
                    break;
                }
            }

            v6 = v6 || t20->IsShared();

            if (SP::ConfigManager()->GetInt(0x5de7b4a) == 1 && v6 == false)
                return false;

            pOut->push_back(DeclareParam(0x5dc0b88, p30));

            n24 = *t20->GetStamp();
            v22 = (uint32_t)((n24 - 0x0000000ebf0cd910ULL) / 0xe10);
            pOut->push_back(DeclareParam(0x61ef9b1, (int)v22));

            n26 = 0;
            n17 = t20->GetTagCount();
            for (uint32_t t = 0; t < n17; ++t) {
                const wchar_t* tag = (const wchar_t*)t20->GetTag(t);
                if (tag != 0) {
                    if (wcscmp(tag, g_TagTarget) == 0) {
                        n26 = 1;
                        break;
                    }
                }
            }
            pOut->push_back(DeclareParam(0xcd6e902c, n26));
        }
    }
    return ok;
}

// @ 0x0055AA00
bool cCityMusicSummarizer::ExtractParameters(const EA::ResourceMan::Key& desc,
                                              eastl::sp_vector<FunctionalMatch::DeclareParam>* pOut)
{
    using namespace FunctionalMatch;

    ResourcePtr<EA::ResourceMan::ResourceObject> ref;
    EA::ResourceMan::IResourceManager* pManager;
    pManager = EA::ResourceMan::GetManager();
    ref.mpObject = 0;
    bool ok = false;
    if (pManager != 0) {
        if (pManager->GetResource(desc, ref.AsPointer(), 0, 0, 0, 0)) {
            SP::cEditorResource* pResource = Pollen::GetEditorResource((void**)&ref.mpObject);
            if (pResource != 0) {
                pOut->push_back(DeclareParam(0x2dc9d1e, (int)pResource->mModelType));
                ok = true;
            }
        }
    }
    ScratchSlots<2>();
    return ok;
}

} // namespace Audio
} // namespace SP
