// Slice s0054c780: SP::Pollen::cAssetMetadataResourceFactory::ReadResource (0x0054c780).
// Deserializes a cAssetMetadata (versions 7..13 accepted by the gate, which is always true:
// the original tests `ver < 7 && ver > 13`). Complete: every version gate, the localized
// (cString table) and inline-string branches, author/tag/consequence-trait lists and the
// final IsShareable computation are reproduced.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /GS- /fp:fast (no /EHsc).
// Layout from ModAPI Pollinator/cAssetMetadata.h (matches the retail offsets used here).
#include "types.h"

// ---------------------------------------------------------------- EA::IO
namespace EA { namespace IO {
class IStream {
public:
    virtual int  AddRef();
    virtual int  Release();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual uint32_t GetSize();
    virtual void slot20();
    virtual void slot24();
    /* 28h */ virtual bool SetPosition(int position, int positionType);
    virtual void slot2C();
    /* 30h */ virtual uint32_t Read(void* pData, uint32_t nSize);
};
bool ReadInt32(IStream* pIS, uint32_t* p, uint32_t n, int endian);    // 0x0093a780
bool ReadUInt64(IStream* pIS, uint64_t* p, uint32_t n, int endian);   // 0x0093a800
enum { kPositionTypeCurrent = 1 };
enum { kEndianBig = 0 };
}}

// ---------------------------------------------------------------- EASTL stand-ins
namespace eastl {
struct allocator { uint32_t mName; };
struct sp_vector_allocator { uint32_t mName; uint32_t mFlags; };

template <typename T>
struct basic_string {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    allocator mAllocator;

    void resize(uint32_t n, T c);                          // 0x00552800 / 0x005527a0
    basic_string& assign(const T* pBegin, const T* pEnd);  // 0x00423650 (wchar_t)

    T* data() { return mpBegin; }
    T& operator[](uint32_t n) { return mpBegin[n]; }
    static uint32_t CharStrlen(const T* p)
    {
        const T* pCurrent = p;
        while (*pCurrent)
            ++pCurrent;
        return (uint32_t)(pCurrent - p);
    }
    basic_string& operator=(const T* p) { return assign(p, p + CharStrlen(p)); }
};
typedef basic_string<char>    string8;
typedef basic_string<wchar_t> string16;

template <typename T>
struct vector {
    T* mpBegin;
    T* mpEnd;
    T* mpCapacity;
    sp_vector_allocator mAllocator;

    void resize(uint32_t n);                 // 0x00553be0 / 0x00553e60
    T* erase(T* first, T* last);             // 0x00554b60
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
    T& front() { return *mpBegin; }
    void clear() { erase(mpBegin, mpEnd); }
};

struct InsertResult {                        // pair<iterator, bool>
    uint32_t* first;
    bool second;
    InsertResult() {}
};
struct vector_set_u32 {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    sp_vector_allocator mAllocator;
    InsertResult insert(const uint32_t& value);   // 0x00554020
};
}

// ---------------------------------------------------------------- SP::cString
namespace SP {
class cString {
public:
    cString();                                                                  // 0x006b5060
    ~cString();                                                                 // 0x006b5240
    bool Load(uint32_t tableID, uint32_t instanceID, const wchar_t* pDefault);  // 0x006b54b0
    const wchar_t* GetText();                                                   // 0x006b55c0
private:
    uint32_t mData[6];
};
}

// ---------------------------------------------------------------- resources
class ResourceObject {
public:
    virtual int AddRef();
    virtual int Release();
    virtual void slot08();
    virtual void* Cast(uint32_t type);
};

class IRecord {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    /* 18h */ virtual EA::IO::IStream* GetStream();
};

struct ResourceKey { uint32_t instanceID, typeID, groupID; };

namespace SP { namespace Pollen {
class cAssetMetadata : public ResourceObject {
public:
    enum { TYPE = 0x30BDEE3 };
    bool SetTags(const wchar_t* pTags);       // 0x00550bd0

    /* 04h */ uint32_t mPad04[5];
    /* 18h */ uint64_t mAssetID;
    /* 20h */ ResourceKey mAssetKey;
    /* 2Ch */ ResourceKey mParentAssetKey;
    /* 38h */ uint64_t mParentAssetID;
    /* 40h */ uint64_t mOriginalParentAssetID;
    /* 48h */ uint64_t mTimeCreated;
    /* 50h */ uint64_t mTimeDownloaded;
    /* 58h */ eastl::string16 mAuthorName;
    /* 68h */ int64_t mAuthorID;
    /* 70h */ int mUseLocale;
    /* 74h */ bool mIsShareable;
    /* 78h */ eastl::string16 mName;
    /* 88h */ eastl::string16 mDescription;
    /* 98h */ eastl::vector<eastl::string8> mAuthors;
    /* ACh */ eastl::vector<eastl::string16> mTags;
    /* C0h */ eastl::vector_set_u32 mConsequenceTraits;
};

class IAuthManager {
public:
    virtual void slot00(); virtual void slot04(); virtual void slot08(); virtual void slot0C();
    virtual void slot10(); virtual void slot14(); virtual void slot18(); virtual void slot1C();
    virtual void slot20(); virtual void slot24(); virtual void slot28(); virtual void slot2C();
    virtual void slot30(); virtual void slot34(); virtual void slot38(); virtual void slot3C();
    /* 40h */ virtual int64_t GetUserID();
};
IAuthManager* AuthManager();                  // 0x00607a60

class cAssetMetadataResourceFactory {
public:
    virtual void slot00();
    bool ReadResource(IRecord* pRecord, ResourceObject* pResource, void* pExtraData, uint32_t typeID);
};
}}

// ---------------------------------------------------------------- helpers
namespace EA {
template <typename T>
class AutoRefCount {
public:
    AutoRefCount(T* p) : mpObject(p) { if (mpObject) mpObject->AddRef(); }
    ~AutoRefCount() { if (mpObject) mpObject->Release(); }
    T* operator->() const { return mpObject; }
    T* mpObject;
};
}

template <typename T>
T* object_cast(ResourceObject* p)             // 0x00554140 (cAssetMetadata instance)
{
    return p ? (T*)p->Cast(T::TYPE) : 0;
}

class cDirectPropertyList {
public:
    uint32_t mPad[15];
    /* 3Ch */ int* mpValues;
    bool GetBool(int index) { return mpValues[index] != 0; }
};
extern cDirectPropertyList* sAppProperties;   // 0x015fd918
inline cDirectPropertyList* AppProperties() { return sAppProperties; }
enum { kAppPropLegacyTimeDownloaded = 0x46 };   // property slot 0x46 (meaning not recovered)

namespace SP { namespace Pollen {

const int64_t kLocalAuthorID = -2;

// @ 0x0054c780
bool cAssetMetadataResourceFactory::ReadResource(IRecord* pRecord, ResourceObject* pResource,
                                                 void* pExtraData, uint32_t typeID)
{
    using namespace EA::IO;
    if (typeID != cAssetMetadata::TYPE)
        return false;

    EA::AutoRefCount<cAssetMetadata> pMeta = object_cast<cAssetMetadata>(pResource);
    IStream* pStream = pRecord->GetStream();

    uint32_t version;
    bool ok = ReadInt32(pStream, &version, 1, kEndianBig) && (version >= 7 || version <= 13);
    if (!ok)
        return false;

    ok = ok && ReadUInt64(pStream, &pMeta->mAssetID, 1, kEndianBig);
    if (!ok)
        return false;

    ok = ok && ReadInt32(pStream, &pMeta->mAssetKey.typeID, 1, kEndianBig);
    ok = ok && ReadInt32(pStream, &pMeta->mAssetKey.groupID, 1, kEndianBig);
    ok = ok && ReadInt32(pStream, &pMeta->mAssetKey.instanceID, 1, kEndianBig);
    ok = ok && ReadInt32(pStream, &pMeta->mParentAssetKey.typeID, 1, kEndianBig);
    ok = ok && ReadInt32(pStream, &pMeta->mParentAssetKey.groupID, 1, kEndianBig);
    ok = ok && ReadInt32(pStream, &pMeta->mParentAssetKey.instanceID, 1, kEndianBig);

    if (version >= 10)
        ok = ok && ReadUInt64(pStream, &pMeta->mParentAssetID, 1, kEndianBig);
    if (version >= 12)
        ok = ok && ReadUInt64(pStream, &pMeta->mOriginalParentAssetID, 1, kEndianBig);
    ok = ok && ReadUInt64(pStream, &pMeta->mTimeCreated, 1, kEndianBig);

    if (version >= 9)
    {
        if (AppProperties()->GetBool(kAppPropLegacyTimeDownloaded) && version == 10)
        {
            // Version 10 files written by an older build stored the download time as two
            // 32-bit halves; anything else is rewound and treated as "same as created".
            uint32_t high;
            ok = ok && ReadInt32(pStream, &high, 1, kEndianBig);
            if (ok && high != 0 && high != 0xffffffff)
            {
                uint32_t low;
                ok = ok && ReadInt32(pStream, &low, 1, kEndianBig);
                pMeta->mTimeDownloaded = (uint64_t)high;
                pMeta->mTimeDownloaded <<= 32;
                pMeta->mTimeDownloaded |= (uint64_t)low;
            }
            else
            {
                pMeta->mTimeDownloaded = pMeta->mTimeCreated;
                if (ok)
                    ok = pStream->SetPosition(-4, kPositionTypeCurrent);
            }
        }
        else
            ok = ok && ReadUInt64(pStream, &pMeta->mTimeDownloaded, 1, kEndianBig);
    }
    else
        pMeta->mTimeDownloaded = pMeta->mTimeCreated;

    uint32_t isLocalized;
    uint32_t length;
    ok = ok && ReadInt32(pStream, &isLocalized, 1, kEndianBig);

    if (isLocalized == 0)
    {
        ok = ok && ReadUInt64(pStream, (uint64_t*)&pMeta->mAuthorID, 1, kEndianBig);

        ok = ok && ReadInt32(pStream, &length, 1, kEndianBig);
        ok = ok && length < 0x100;
        pMeta->mAuthorName.resize(length, 0);
        ok = ok && pStream->Read(&pMeta->mAuthorName[0], length * 2);
        pMeta->mUseLocale = -1;

        ok = ok && ReadInt32(pStream, &length, 1, kEndianBig);
        ok = ok && length < 0x100;
        pMeta->mName.resize(length, 0);
        ok = ok && pStream->Read(&pMeta->mName[0], length * 2);

        ok = ok && ReadInt32(pStream, &length, 1, kEndianBig);
        ok = ok && length < 0x1000;
        pMeta->mDescription.resize(length, 0);
        if (length != 0)
            ok = ok && pStream->Read(&pMeta->mDescription[0], length * 2);
    }
    else
    {
        uint32_t tableID, authorID, nameID, descriptionID;
        ok = ok && ReadInt32(pStream, &tableID, 1, kEndianBig);
        ok = ok && ReadInt32(pStream, &authorID, 1, kEndianBig);
        ok = ok && ReadInt32(pStream, &nameID, 1, kEndianBig);
        ok = ok && ReadInt32(pStream, &descriptionID, 1, kEndianBig);

        SP::cString author;
        ok = authorID != 0xffffffff && author.Load(tableID, authorID, L"Error Author");
        if (ok)
        {
            pMeta->mUseLocale = 1;
            pMeta->mAuthorName = author.GetText();
            pMeta->mAuthorID = -1;
            pMeta->mIsShareable = false;
        }
        else
            return false;

        SP::cString name;
        ok = nameID != 0xffffffff && name.Load(tableID, nameID, L"Error Name");
        if (ok)
            pMeta->mName = name.GetText();
        else
            return false;

        if (descriptionID != 0xffffffff)
        {
            SP::cString description;
            ok = description.Load(tableID, descriptionID, L"");
            if (ok)
                pMeta->mDescription = description.GetText();
            else
                return false;
        }
    }

    if (version >= 1)
    {
        if (version >= 2)
        {
            ok = ok && ReadInt32(pStream, &length, 1, kEndianBig);
            if (!ok)
                return false;
            pMeta->mAuthors.resize(length);
            for (eastl::string8* it = pMeta->mAuthors.begin(), *itEnd = pMeta->mAuthors.end();
                 ok && it != itEnd; ++it)
            {
                eastl::string8& author = *it;
                ok = ok && ReadInt32(pStream, &length, 1, kEndianBig);
                if (ok)
                {
                    author.resize(length, 0);
                    if (length != 0)
                        ok = ok && pStream->Read(author.data(), length);
                }
            }
        }
        else
        {
            ok = ok && ReadInt32(pStream, &length, 1, kEndianBig);
            if (ok)
            {
                pMeta->mAuthors.resize(1);
                eastl::string8& author = pMeta->mAuthors.front();
                author.resize(length, 0);
                ok = ok && pStream->Read(author.data(), length);
            }
        }
    }

    isLocalized = 0;
    if (version >= 13)
        ok = ok && ReadInt32(pStream, &isLocalized, 1, kEndianBig);

    if (isLocalized == 0)
    {
        ok = ok && ReadInt32(pStream, &length, 1, kEndianBig);
        if (!ok)
            return false;
        pMeta->mTags.resize(length);
        for (eastl::string16* it = pMeta->mTags.begin(), *itEnd = pMeta->mTags.end();
             ok && it != itEnd; ++it)
        {
            eastl::string16& tag = *it;
            ok = ok && ReadInt32(pStream, &length, 1, kEndianBig);
            if (ok && length != 0)
            {
                tag.resize(length, 0);
                ok = ok && pStream->Read(&tag[0], length * 2);
            }
        }
    }
    else
    {
        uint32_t tagTableID, tagInstanceID;
        ok = ok && ReadInt32(pStream, &tagTableID, 1, kEndianBig);
        ok = ok && ReadInt32(pStream, &tagInstanceID, 1, kEndianBig);
        if (tagInstanceID != 0xffffffff)
        {
            SP::cString tags;
            ok = tags.Load(tagTableID, tagInstanceID, L"");
            if (ok)
            {
                pMeta->mTags.clear();
                ok = ok && pMeta->SetTags(tags.GetText());
            }
            else
                return false;
        }
    }

    if (ok && version >= 8)
    {
        uint32_t isShareable;
        ok = ok && ReadInt32(pStream, &isShareable, 1, kEndianBig);
        pMeta->mIsShareable = isShareable != 0;

        uint32_t traitCount;
        ok = ok && ReadInt32(pStream, &traitCount, 1, kEndianBig);
        for (uint32_t i = 0; ok && i < traitCount; ++i)
        {
            uint32_t trait;
            ok = ok && ReadInt32(pStream, &trait, 1, kEndianBig);
            pMeta->mConsequenceTraits.insert(trait);
        }
    }
    else
    {
        pMeta->mIsShareable = pMeta->mAuthorID == kLocalAuthorID ||
                              pMeta->mAuthorID == AuthManager()->GetUserID();
    }

    return ok;
}

}}
