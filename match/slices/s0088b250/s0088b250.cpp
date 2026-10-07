// Slice s0088b250 (0x88b250..0x88c559) - EA::Text FontServer / Font / GlyphCache.
//
// This region is the original EAWebKit EAText/EAIO source (vendored under
// work/ext/EAWebKitSupportPackages), together with the EASTL container instantiations it
// forces. Two functions reproduce this retail build exactly (listed in manifest.txt); the
// remainder are present as the same complete upstream implementation but differ from retail
// because the vendored drop uses a different allocator/config (see nonmatching.txt).
//
// Byte-exact:  0088b850 (?IsFilePathSeparator@IO@EA@@YA_NH@Z)
//              0088b8a0 (?GetSystemFontDirectory@Text@EA@@YAIPA_WI@Z)
//
// Original identities (names from the retail image; corrected 2026-10: an earlier table here
// had most labels shifted, which pointed the equivalence checker at the wrong functions).
//   0x0088b250  RT::GlyphCache::AddTextureInfo     (EA::Text, retail layout; defined at the end)
//   0x0088b450  RT::GlyphCache::~GlyphCache        (EA::Text, retail layout; defined at the end)
//   0x0088b500  RT::FontDescription::operator==    (EA::Text, retail layout; defined at the end)
//   0x0088b560  RT::Font::~Font                    (EA::Text, retail layout; defined at the end)
//   0x0088b580  RT::Font::Release                  (EA::Text, retail layout; defined at the end)
//   0x0088b5b0  RT::Font::Font                     (EA::Text, retail layout; defined at the end)
//   0x0088b600  RT::Font scalar deleting dtor      (EA::Text, retail layout; compiler-generated)
//   0x0088b640  RT::Font::SetupSupportedScriptSet  (EA::Text, retail layout; defined at the end)
//   0x0088b850  EA::IO::IsFilePathSeparator                          BYTE-EXACT
//   0x0088b870  EA::IO::Path::GetFileName (retail EAIO form, defined below)
//   0x0088b8a0  EA::Text::GetSystemFontDirectory                    BYTE-EXACT
//   0x0088b930  EA::Text::GetFontTypeFromFilePath
//   0x0088b9a0  EA::Text::FontServer::SetOption
//   0x0088b9e0  EA::Text::FontServer::GetFontDescriptionScore
//   0x0088bb20  EA::Text::FontServer::AddFace          (const char16_t* path, FontType)
//   0x0088bbb0  EA::Text::FontServer::Init
//   0x0088be70  eastl::hashtable::DoRehash          (Face map)
//   0x0088bf40  eastl::hashtable::DoRehash          (string map)
//   0x0088c010  hashtable<Face map>::DoFindNode<const wchar_t*, equal_to_2>
//   0x0088c050  fixed_list<Font*,4,1>::fixed_list
//   0x0088c0d0  pair<const string16,string16>::pair(const string16&, const string16&)
//   0x0088c170  basic_string<wchar_t>::insert(wchar_t*, const wchar_t*, const wchar_t*)
//   0x0088c380  hashtable<string16 -> string16 map>::DoAllocateNode
//   0x0088c500  list<Font*>::erase(first, last)

#include "types.h"

#define WIN32 1
#define NDEBUG 1
#define _SECURE_SCL 0
#define UTF_USE_EAASSERT 1
#define ENABLE_NON_RAM_STREAM 1
#define EATEXT_USE_FREETYPE 1
#define EATEXT_BITMAP_USE_EAGIMEX 0
#define _WIN32_WINNT 0x0501
#define WINVER 0x0501
#define _WIN32_IE 0x0501

#include "../../../work/ext/EAWebKitSupportPackages/EAIOEAWebKit/local/source/EAFileDirectory.cpp"

// Retail EAIO/EAText differ from the vendored drop in a few leaf helpers. The retail image has
// no Path::GetFileExtension / Text::Stricmp: its callers go through EA::IO::SplitPathPtrs (the
// older EAIO path splitter) and _wcsicmp directly. These definitions restore that behaviour.
#include <EAText/internal/StdC.h>

namespace EA
{
    namespace IO
    {
        void SplitPathPtrs(const char16_t* pPath, const char16_t** pDirectory,
                           const char16_t** pFileName, const char16_t** pExtension); // 0x00930070

        namespace Path
        {
            // @ 0x0088b870
            PathString16::iterator GetFileName(PathString16::const_iterator first, PathString16::const_iterator)
            {
                const char16_t* pDirectory;
                const char16_t* pFileName = NULL;
                const char16_t* pExtension;
                SplitPathPtrs(first, &pDirectory, &pFileName, &pExtension);
                return (PathString16::iterator)pFileName;
            }

            inline PathString16::iterator GetFileExtension(PathString16::const_iterator first, PathString16::const_iterator)
            {
                const char16_t* pDirectory;
                const char16_t* pFileName;
                const char16_t* pExtension = NULL;
                SplitPathPtrs(first, &pDirectory, &pFileName, &pExtension);
                return (PathString16::iterator)pExtension;
            }
        }
    }

    namespace Text
    {
        inline int Stricmp(const char16_t* pString1, const char16_t* pString2)
        {
            return _wcsicmp(pString1, pString2);
        }
    }
}

// Addresses of out-of-line class members the inlined vendored code calls (read by the
// equivalence checker only; a member cannot be redeclared outside its class).
#if 0
EA::IO::FileStream::FileStream(const char16_t* pPath16); // 0x00931e10
void operator delete[](void* p); // 0x00f47380
#endif
#include "../../../work/ext/EAWebKitSupportPackages/EATextEAWebKit/local/source/EATextFontServer.cpp"

// Original addresses for the equivalence checker (redeclarations of the upstream declarations).
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags, const char* file, int line); // 0x00f473a0
void operator delete[](void* p); // 0x00f47380
namespace eastl
{
    extern EASTL_API EmptyString gEmptyString; // 0x01667bac
}

// ---------------------------------------------------------------------------------------------
// Retail-layout Font / FontDescription / GlyphCache members (0x88b250..0x88b84a).
//
// The retail EAText was built with EATEXT_THREAD_SAFETY_ENABLED (EAThread AtomicInt refcounts
// and a CRITICAL_SECTION mutex in Font and GlyphCache), which the vendored drop compiles out, so
// the vendored classes have the wrong layout for these members. They are written here against
// the retail layout, in namespace RT so they do not collide with the vendored EA::Text classes.
// Behaviour follows the upstream EATextFont.cpp / EATextCache.cpp bodies; the retail differences
// (Greek test characters 0x37E/0x3CE, the script bit numbers, Release resetting the count to 1
// before deleting itself) are taken from the retail code.
// ---------------------------------------------------------------------------------------------
extern "C" long __cdecl _InterlockedExchange(long volatile* p, long v);
extern "C" long __cdecl _InterlockedExchangeAdd(long volatile* p, long v);
extern "C" long __cdecl _InterlockedDecrement(long volatile* p);
#pragma intrinsic(_InterlockedExchange, _InterlockedExchangeAdd, _InterlockedDecrement)

namespace RT
{
    void* GetAllocator(); // 0x008859d0  (EA::Text::GetAllocator)

    struct FontDescription
    {
        wchar_t  mFamily[32];   // +0x00
        float    mfSize;        // +0x40
        int      mStyle;        // +0x44
        float    mfWeight;      // +0x48
        float    mfStretch;     // +0x4c
        int      mPitch;        // +0x50
        int      mVariant;      // +0x54
        int      mSmooth;       // +0x58
        int      mEffect;       // +0x5c

        bool operator==(const FontDescription& fd) const;
    };

    // @ 0x0088b500
    bool FontDescription::operator==(const FontDescription& fd) const
    {
        return  (mfSize   == fd.mfSize) &&
                (mStyle   == fd.mStyle) &&
                (mfWeight == fd.mfWeight) &&
                (mSmooth  == fd.mSmooth) &&
                (_wcsicmp(mFamily, fd.mFamily) == 0) &&
                (mEffect  == fd.mEffect);
    }

    class Font
    {
    public:
        Font(void* pCoreAllocator);
        virtual ~Font();                                        // slot 0
        virtual void v01() = 0; virtual void v02() = 0; virtual void v03() = 0;
        virtual void v04() = 0; virtual void v05() = 0; virtual void v06() = 0;
        virtual void v07() = 0; virtual void v08() = 0; virtual void v09() = 0;
        virtual void v10() = 0; virtual void v11() = 0; virtual void v12() = 0;
        virtual void v13() = 0; virtual void v14() = 0;
        virtual bool IsCharSupported(wchar_t c, int script) = 0;  // slot 15 (+0x3c)

        int  Release();
        void SetupSupportedScriptSet();

        static void operator delete(void* p) { ::operator delete[](p); }

        unsigned          mUnknown04;            // +0x04
        void*             mpCoreAllocator;       // +0x08
        void*             mpUserData;            // +0x0c
        void*             mpStream;              // +0x10
        unsigned short    mReplacementGlyphId;   // +0x14
        eastl::bitset<64> mSupportedScriptSet;   // +0x18 (EA::Text::SupportedScriptSet)
        volatile long     mRefCount;             // +0x20 (EA::Thread::AtomicInt32)
        unsigned          mUnknown24;            // +0x24
        CRITICAL_SECTION  mMutex;                // +0x28
    };

    // @ 0x0088b5b0
    Font::Font(void* pCoreAllocator)
      : mpCoreAllocator(pCoreAllocator ? pCoreAllocator : GetAllocator()),
        mpUserData(NULL),
        mpStream(NULL),
        mReplacementGlyphId(0),
        mSupportedScriptSet()
    {
        _InterlockedExchange(&mRefCount, 0);
        InitializeCriticalSection(&mMutex);
    }

    // @ 0x0088b560
    Font::~Font()
    {
        DeleteCriticalSection(&mMutex);
    }

    // @ 0x0088b580
    int Font::Release()
    {
        int rc = _InterlockedDecrement(&mRefCount);
        if(rc)
            return rc;
        _InterlockedExchange(&mRefCount, 1);
        delete this;
        return 0;
    }

    // @ 0x0088b640
    void Font::SetupSupportedScriptSet()
    {
        mSupportedScriptSet.reset();
        mSupportedScriptSet.set(0);                     // kScriptCommon

        if(IsCharSupported(0x0621, -1) && IsCharSupported(0x0641, -1))
            mSupportedScriptSet.set(2);          // Arabic
        if(IsCharSupported(0x0401, -1) && IsCharSupported(0x0414, -1))
            mSupportedScriptSet.set(12);         // Cyrillic
        if(IsCharSupported(0x0909, -1) && IsCharSupported(0x092A, -1))
            mSupportedScriptSet.set(14);         // Devanagari
        if(IsCharSupported(0x037E, -1) && IsCharSupported(0x03CE, -1))
            mSupportedScriptSet.set(18);         // Greek
        if(IsCharSupported(0x70A7, -1) && IsCharSupported(0x7535, -1))
            mSupportedScriptSet.set(21);         // Han
        if(IsCharSupported(0xC2B9, -1) && IsCharSupported(0xC9D1, -1))
            mSupportedScriptSet.set(22);         // Hangul
        if(IsCharSupported(0x05D0, -1) && IsCharSupported(0x05E2, -1))
            mSupportedScriptSet.set(24);         // Hebrew
        if(IsCharSupported(0x3061, -1) && IsCharSupported(0x3078, -1))
            mSupportedScriptSet.set(25);         // Hiragana
        if(IsCharSupported(0x30A4, -1) && IsCharSupported(0x30EE, -1))
            mSupportedScriptSet.set(27);         // Katakana
        if(IsCharSupported(0x0041, -1) && IsCharSupported(0x007A, -1))
            mSupportedScriptSet.set(30);         // Latin
        if(IsCharSupported(0x0E01, -1) && IsCharSupported(0x0E2C, -1))
            mSupportedScriptSet.set(50);              // Thai
    }

    // The scalar deleting destructor at 0x0088b600 is the compiler-generated one for Font
    // (??_GFont@RT@@UAEPAXI@Z: ~Font, then operator delete[] when (flags & 1)).

    struct ICoreAllocator
    {
        virtual ~ICoreAllocator();
        virtual void* Alloc(unsigned size, const char* name, unsigned flags) = 0;
        virtual void* Alloc(unsigned size, const char* name, unsigned flags, unsigned align, unsigned offset) = 0;
        virtual void  Free(void* p, unsigned size) = 0;    // slot 3 (+0x0c)
    };

    struct TextureInfo
    {
        TextureInfo();                         // 0x00889f10
        virtual ~TextureInfo();
        virtual int AddRef();                  // slot 1 (+0x04)
        virtual int Release();                 // slot 2 (+0x08)

        unsigned char  mPad04[0x30];           // +0x04
        unsigned       mTexture;               // +0x34
        unsigned       mPad38[2];              // +0x38
        float          mfSizeInverse;          // +0x40
        unsigned       mFormat;                // +0x44
        unsigned       mnSize;                 // +0x48
        unsigned       mnGeneration;           // +0x4c
        unsigned       mnColumnHeights[64];    // +0x50
        unsigned       mnOpenAreaX;            // +0x150
        unsigned       mnOpenAreaY;            // +0x154
        unsigned       mnOpenAreaLineH;        // +0x158
        unsigned char  mPad15c[2];             // +0x15c
        unsigned char  mnColumnCount;          // +0x15e
        unsigned char  mnColumnWidths[64];     // +0x15f
        bool           mbWritable;             // +0x19f
    };

    // eastl::hashtable<..., CoreAllocatorAdapter> (GlyphCache::mGlyphTextureMap, +0x0c).
    struct GlyphTextureMap
    {
        unsigned         mFunctors;            // +0x00
        void**           mpBucketArray;        // +0x04
        unsigned         mnBucketCount;        // +0x08
        unsigned         mnElementCount;       // +0x0c
        float            mfMaxLoadFactor;      // +0x10
        float            mfGrowthFactor;       // +0x14
        unsigned         mnNextResize;         // +0x18
        ICoreAllocator*  mpCoreAllocator;      // +0x1c
        unsigned         mAllocFlags;          // +0x20

        void DoFreeNodes(void** pBucketArray, unsigned n); // 0x008dac90

        ~GlyphTextureMap()
        {
            DoFreeNodes(mpBucketArray, mnBucketCount);
            mnElementCount = 0;
            if(mnBucketCount > 1)
                mpCoreAllocator->Free(mpBucketArray, (mnBucketCount + 1) * sizeof(void*));
        }
    };

    // eastl::fixed_vector<TextureInfo*, 4, true> (GlyphCache::mTextureInfoArray, +0x30).
    struct TextureInfoArray
    {
        TextureInfo**  mpBegin;                // +0x00
        TextureInfo**  mpEnd;                  // +0x04
        TextureInfo**  mpCapacity;             // +0x08
        unsigned       mAllocatorName;         // +0x0c (fixed_vector_allocator)
        TextureInfo**  mpPoolBegin;            // +0x10
        TextureInfo*   mBuffer[3];             // +0x14

        void DoInsertValue(TextureInfo** position, TextureInfo* const& value); // 0x00899480

        void push_back(TextureInfo* value)
        {
            if(mpEnd < mpCapacity)
                ::new((void*)mpEnd++) TextureInfo*(value);
            else
                DoInsertValue(mpEnd, value);
        }

        ~TextureInfoArray()
        {
            if(mpBegin && (mpBegin != mpPoolBegin))
                ::operator delete[](mpBegin);
        }
    };

    class GlyphCache
    {
    public:
        virtual ~GlyphCache();                                         // slot 0
        virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
        virtual void v05(); virtual void v06(); virtual void v07();
        virtual unsigned CreateTexture(TextureInfo* pTextureInfo);      // slot 8 (+0x20)
        virtual void v09(); virtual void v10(); virtual void v11(); virtual void v12();
        virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
        virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20();
        virtual void v21(); virtual void v22();
        virtual bool ClearTextureInternal(TextureInfo* pTextureInfo);   // slot 23 (+0x5c)

        TextureInfo* AddTextureInfo(TextureInfo* pTextureInfo, bool bInitialized);
        bool Shutdown(); // 0x0088b000

        unsigned           mPad04[2];                  // +0x04
        GlyphTextureMap    mGlyphTextureMap;           // +0x0c
        TextureInfoArray   mTextureInfoArray;          // +0x30
        unsigned           mnTextureInfoCountMax;      // +0x50
        unsigned           mnTextureSizeDefault;       // +0x54
        unsigned           mnTextureFormatDefault;     // +0x58
        unsigned           mnColumnCountDefault;       // +0x5c
        unsigned           mnColumnWidthsDefault[66];  // +0x60
        CRITICAL_SECTION   mMutex;                     // +0x168
        unsigned           mPad180[2];                 // +0x180
        volatile long      mnInitCount;                // +0x188
    };

    // @ 0x0088b450
    GlyphCache::~GlyphCache()
    {
        if(_InterlockedExchangeAdd(&mnInitCount, 0) > 0)
        {
            _InterlockedExchange(&mnInitCount, 1);
            Shutdown();
        }
        DeleteCriticalSection(&mMutex);
    }

    // EA::Thread::AutoFutex over the retail Futex (a CRITICAL_SECTION).
    struct AutoFutex
    {
        CRITICAL_SECTION* mpFutex;
        AutoFutex(CRITICAL_SECTION* p) : mpFutex(p) { EnterCriticalSection(mpFutex); }
        ~AutoFutex() { LeaveCriticalSection(mpFutex); }
    };

    // @ 0x0088b250
    TextureInfo* GlyphCache::AddTextureInfo(TextureInfo* pTextureInfo, bool bInitialized)
    {
        AutoFutex autoMutex(&mMutex);

        // If already present then just return OK.
        if(eastl::find(mTextureInfoArray.mpBegin, mTextureInfoArray.mpEnd, pTextureInfo) != mTextureInfoArray.mpEnd)
            return pTextureInfo;

        if((unsigned)(mTextureInfoArray.mpEnd - mTextureInfoArray.mpBegin) < mnTextureInfoCountMax)
        {
            if(pTextureInfo)
                pTextureInfo->AddRef();
            else
            {
                pTextureInfo = new(::operator new[](sizeof(TextureInfo), "EAText/TextureInfo", 0, 0, NULL, 0)) TextureInfo;
                pTextureInfo->AddRef();
                bInitialized = false;
            }

            if(!pTextureInfo->mTexture)
            {
                if(pTextureInfo->mnSize == 0)
                    pTextureInfo->mnSize = mnTextureSizeDefault;
                else if(pTextureInfo->mnSize < 64)
                    pTextureInfo->mnSize = 64;

                if(pTextureInfo->mFormat == 0)
                    pTextureInfo->mFormat = mnTextureFormatDefault;

                pTextureInfo->mTexture = CreateTexture(pTextureInfo);
            }

            if(pTextureInfo->mTexture)
            {
                pTextureInfo->mfSizeInverse = (float)(1.f / pTextureInfo->mnSize);

                if(!bInitialized)
                {
                    pTextureInfo->mnGeneration    = 1;
                    pTextureInfo->mnColumnCount   = (unsigned char)mnColumnCountDefault;
                    pTextureInfo->mbWritable      = true;
                    pTextureInfo->mnOpenAreaX     = 0;
                    pTextureInfo->mnOpenAreaY     = 0;
                    pTextureInfo->mnOpenAreaLineH = 0;

                    for(unsigned j = 0; j < mnColumnCountDefault; j++)
                    {
                        pTextureInfo->mnColumnWidths[j]  = (unsigned char)mnColumnWidthsDefault[j];
                        pTextureInfo->mnColumnHeights[j] = 0;
                        pTextureInfo->mnOpenAreaX        = pTextureInfo->mnOpenAreaX + pTextureInfo->mnColumnWidths[j];
                    }

                    ClearTextureInternal(pTextureInfo);
                }

                // We transfer the AddRef for this function to mTextureInfoArray.
                mTextureInfoArray.push_back(pTextureInfo);
                return pTextureInfo;
            }

            pTextureInfo->Release(); // Matches the AddRef for this function.
        }

        return NULL;
    }
}
