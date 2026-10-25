// Slice s0088d2a0 - EA::Text::FontServer (retail EAText layout, thread-safe build).
//
// 0x0088d2a0  FontServer::GetFont(const TextStyle*, Font* pFontArray[], uint32 capacity,
//                                 Char c, Script script, bool bManaged)   (__thiscall, ret 0x18)
// 0x0088d940  FontServer::AddFont(Font*)
// 0x0088daf0  FontServer::CreateNewFont(FaceSource*, const TextStyle&, bool)
// 0x0088def0  eastl::ListBase<FontServer::FaceSource,...>::DoClear
// 0x0088df70  eastl::hashtable<string16, pair<const string16, string16>, ...>::DoFreeNodes
// 0x0088e020  FontServer::GetFont(const TextStyle*, FontSet&, uint32 capacity,
//                                 Char c, Script script, bool bManaged)
// 0x0088e0e0  FontServer::AddSubstitution(const wchar_t* pFamily, const wchar_t* pSubstitute)
//
// The retail FontServer differs from the vendored upstream EATextFontServer.cpp: the array
// GetFont has no duplicate test and no score array / score sort, the container layouts follow the
// retail EASTL build (see tools/pdb_type.py) and the classes below describe only what these
// functions touch.
#include "types.h"
#include <string.h>
#include <wchar.h>
#include <math.h>

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void* cs);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void* cs);

inline void* operator new(size_t, void* p) { return p; }

void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags,
                     const char* pFile, int line);          // 0x00f473a0  (EASTL operator new)
inline void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags,
                          const char* pFile, int line)
{
    return operator new[](size, pName, flags, debugFlags, pFile, line);
}

namespace RT
{
    typedef uint16_t Char;

    void  FreeRawBlock(void* p);   // 0x00f47380  (EASTL operator delete)

    struct AutoMutex
    {
        void* mpMutex;
        AutoMutex(void* p) : mpMutex(p) { EnterCriticalSection(mpMutex); }
        ~AutoMutex() { LeaveCriticalSection(mpMutex); }
    };

    struct ListNode
    {
        ListNode* mpNext;
        ListNode* mpPrev;
    };

    struct Allocator { };                  // eastl::allocator: empty

    // eastl::fixed_pool_with_overflow: free-list head, the (empty) overflow allocator and the
    // inline pool bounds.  Retail keeps the node size in the pool block.
    struct FixedPool
    {
        void*      mpHead;              // +0x00
        Allocator  mOverflowAllocator;  // +0x04
        void*      mpPoolBegin;         // +0x08
        void*      mpPoolEnd;           // +0x0c
        uint32_t   mnNodeSize;          // +0x10
    };

    struct Font;
    struct FaceSource;

    // eastl::fixed_list<Font*,4,1> -- FaceSource::mFontList (+0x80), size 0x58.
    struct FontList
    {
        ListNode  mNode;              // +0x00 list anchor
        FixedPool mPool;              // +0x08
        char      mBuffer[0x3c];      // +0x1c inline node buffer

        bool empty() const { return mNode.mpNext == &mNode; }

        __forceinline void push_back(Font* pFont)
        {
            ListNode* pNode;
            if (mPool.mpHead)
            {
                pNode = (ListNode*)mPool.mpHead;
                mPool.mpHead = *(void**)mPool.mpHead;
            }
            else
                pNode = (ListNode*)operator new(mPool.mnNodeSize, "EASTL", 0, 0,
                                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                                0xd1);

            Font** pValue = (Font**)((char*)pNode + sizeof(ListNode));
            ::new (pValue) Font*(pFont);

            pNode->mpNext = &mNode;
            pNode->mpPrev = mNode.mpPrev;
            mNode.mpPrev->mpNext = pNode;
            mNode.mpPrev = pNode;
        }

        void FreeNodes();             // 0x00a222c0 (eastl::PoolList::FreeNodes)
        ~FontList() { FreeNodes(); }
    };

    // eastl::fixed_list<FontServer::FaceSource,4,1> -- Face::mFaceSourceList (+0x40),
    // size 0x47c (4 nodes of 0xe0 bytes and the extra slack of the retail build).
    struct FaceSourceNode;

    struct FaceSourceList
    {
        ListNode  mNode;              // +0x00 list anchor
        FixedPool mPool;              // +0x08
        char      mBuffer[0x460];     // +0x1c inline node buffer

        bool empty() const { return mNode.mpNext == &mNode; }
        void DoClear();               // 0x0088def0
        ~FaceSourceList() { DoClear(); }
    };

    // eastl::basic_string<wchar_t, eastl::allocator> (string16): 0x10 bytes.
    // SSO strings keep mpCapacity - mpBegin <= 2 bytes and are not freed.
    struct Str16
    {
        wchar_t* mpBegin;      // +0x00
        wchar_t* mpEnd;        // +0x04
        wchar_t* mpCapacity;   // +0x08
        Allocator mAllocator;  // +0x0c

        Str16() : mpBegin(NULL), mpEnd(NULL), mpCapacity(NULL) {}

        void RangeInitialize(const wchar_t* p);  // 0x00579a90
        void make_lower();                       // 0x005e8e80
        uint32_t length() const { return (uint32_t)(mpEnd - mpBegin); }

        void insert(wchar_t* pPosition, const wchar_t* pFirst, const wchar_t* pLast); // 0x0088c170

        ~Str16()
        {
            int nSize = (int)((uint32_t)mpCapacity - (uint32_t)mpBegin) & ~1;
            if (nSize > 2 && mpBegin)
                FreeRawBlock(mpBegin);
        }
    };

    // eastl::pair<const string16, string16> (also the substitution hash node value).
    struct StrPair
    {
        Str16 first;   // +0x00
        Str16 second;  // +0x10

        StrPair(const Str16& a, const Str16& b);  // 0x0088c0d0
        ~StrPair();                               // 0x00614c00
    };

    // eastl::fixed_string<wchar_t,129,true>, size 0x118.
    struct PathString16
    {
        wchar_t* mpBegin;       // +0x00
        wchar_t* mpEnd;         // +0x04
        wchar_t* mpCapacity;    // +0x08
        char     mAllocator;    // +0x0c
        char     mAllocatorPad[3]; // +0x0d
        wchar_t* mpPoolBegin;   // +0x10
        wchar_t  mBuffer[0x82]; // +0x14

        PathString16(uint32_t n, const wchar_t& value); // 0x0088c6e0
        void resize(uint32_t n);                        // 0x009310a0
        void insert(wchar_t* pPosition, const wchar_t* pFirst, const wchar_t* pLast); // 0x0088c170

        ~PathString16()
        {
            int nSize = (int)((uint32_t)mpCapacity - (uint32_t)mpBegin) & ~1;
            if (nSize > 2 && mpBegin && mpBegin != mpPoolBegin)
                FreeRawBlock(mpBegin);
        }
    };

    // EA::IO::IStream (retail EAIO version): the slots used by EAText.
    class IStream
    {
    public:
        virtual ~IStream();                                      // 0 (+0x00)
        virtual int AddRef();                                    // 1 (+0x04)
        virtual int Release();                                   // 2 (+0x08)
        virtual uint32_t GetType() const;                        // 3 (+0x0c)
        virtual void v04(); virtual void v05(); virtual void v06();
        virtual void v07(); virtual void v08(); virtual void v09();
        virtual void v10(); virtual void v11(); virtual void v12();
        virtual void v13(); virtual void v14(); virtual void v15();
        virtual void v16();                                      // 16 (+0x40)
        virtual uint32_t GetPath(wchar_t* pPath, uint32_t nPathCapacity); // 17 (+0x44)
        virtual void v18();                                      // 18 (+0x48)
        virtual bool Open(int nAccess, int nSharing, int nCD, int nUsageHints); // 19 (+0x4c)
    };

    // EA::IO::FileStream (retail size used by CreateNewFont's allocation).
    class FileStream : public IStream
    {
    public:
        FileStream(const wchar_t* pPath16);  // 0x00931e10
        char mData[0x22c - sizeof(IStream)];
    };

    struct BitmapTextureInfo;
    struct BmpTextureInfo;

    // EA::Text::BmpTextureInfo: only the texture path at +0x1a0 is used here.
    struct BmpTextureInfo
    {
        char         mPrefix[0x1a0];
        PathString16 mTextureFilePath;  // +0x1a0
        char         mSuffix[0x2d8 - 0x1a0 - sizeof(PathString16)];
    };

    // EA::Text::FontDescription, size 0x74.
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
        unsigned mEffect;       // +0x5c
        float    mfEffectX;     // +0x60
        float    mfEffectY;     // +0x64
        unsigned mEffectBaseColor; // +0x68
        unsigned mEffectColor;     // +0x6c
        unsigned mHighLightColor;  // +0x70

        FontDescription()
          : mfSize(0.f), mStyle(0), mfWeight(400.f), mfStretch(1.f),
            mPitch(0), mVariant(0), mSmooth(0), mEffect(0),
            mfEffectX(1.f), mfEffectY(1.f), mEffectBaseColor(0xffffffff),
            mEffectColor(0xff000000), mHighLightColor(0xffffffff) { mFamily[0] = 0; }
    };

    struct TextStyle
    {
        wchar_t  mFamilyNameArray[8][32];   // +0x00
        float    mfSize;                    // +0x200
        char     pad204[0x214 - 0x204];
        int      mSmooth;                   // +0x214
        unsigned mEffect;                   // +0x218
        float    mfEffectX;                 // +0x21c
        float    mfEffectY;                 // +0x220
        char     pad224[0x22c - 0x224];
        unsigned mEffectBaseColor;          // +0x22c
        unsigned mEffectColor;              // +0x230
        unsigned mHighLightColor;           // +0x234
        char     pad238[0x278 - 0x238];
    };

    // EA::Text::FontServer::FaceSource, size 0xd8.
    struct FaceSource
    {
        IStream*        mpStream;           // +0x00
        int             mFontType;          // +0x04
        FontDescription mFontDescription;   // +0x08
        uint8_t         mnFontIndex;        // +0x7c
        char            pad7d[3];
        FontList        mFontList;          // +0x80

        FaceSource();                       // 0x0088c7e0
    };

    // eastl list node for FaceSource values: links + value (node size 0xe0).
    struct FaceSourceNode
    {
        ListNode   links;   // +0x00
        FaceSource value;   // +0x08
    };

    // Font node of FaceSource::mFontList: links then the value.
    struct FontNode
    {
        ListNode links;   // +0x00
        Font*    value;   // +0x08
    };

    // eastl::fixed_list<FaceSource,4,1>::DoClear.
// @ 0x0088def0
    void FaceSourceList::DoClear()
    {
        ListNode* p = mNode.mpNext;
        while (p != &mNode)
        {
            ListNode* const pTemp = p;
            p = p->mpNext;
            FaceSourceNode* const pNode = (FaceSourceNode*)pTemp;
            FontList* const pFontList = &pNode->value.mFontList;
            ListNode* pFont = pFontList->mNode.mpNext;
            ListNode* const pFontEnd = &pFontList->mNode;
            while (pFont != pFontEnd)
            {
                ListNode* const pFontTemp = pFont;
                pFont = pFont->mpNext;
                if ((char*)pFontTemp < (char*)pFontList->mPool.mpPoolBegin ||
                    (char*)pFontTemp >= (char*)pFontList->mPool.mpPoolEnd)
                    FreeRawBlock(pFontTemp);
                else
                {
                    *(void**)pFontTemp = pFontList->mPool.mpHead;
                    pFontList->mPool.mpHead = pFontTemp;
                }
            }
            if ((char*)pTemp < (char*)mPool.mpPoolBegin ||
                (char*)pTemp >= (char*)mPool.mpPoolEnd)
                FreeRawBlock(pTemp);
            else
            {
                *(void**)pTemp = mPool.mpHead;
                mPool.mpHead = pTemp;
            }
        }
    }

    // EA::Text::FontServer::Face, size 0x4bc.
    struct Face
    {
        wchar_t        mFamily[32];       // +0x00
        FaceSourceList mFaceSourceList;   // +0x40
    };

    // Hash node of the face map: key string (0x10), Face, next pointer at +0x4cc.
    struct FaceNode
    {
        char      mKey[0x10];
        Face      mFace;     // +0x10
        FaceNode* mpNext;    // +0x4cc
    };

    // Substitution hash node: key at +0x00, value at +0x10, next at +0x20.
    struct SubstNode
    {
        Str16      first;    // +0x00
        Str16      second;   // +0x10
        SubstNode* mpNext;   // +0x20
    };

    // eastl::hashtable_iterator (8 bytes; the user constructor makes MSVC return it via sret).
    template<class NodeT> struct HashIter
    {
        NodeT*  mpNode;
        NodeT** mpBucket;

        HashIter() : mpNode(NULL), mpBucket(NULL) {}

        void increment_bucket()
        {
            ++mpBucket;
            while (*mpBucket == 0)
                ++mpBucket;
            mpNode = *mpBucket;
        }
        void increment()
        {
            mpNode = mpNode->mpNext;
            while (mpNode == 0)
                mpNode = *++mpBucket;
        }
    };

    struct EmptyFunctor { };                       // hash<>: plain empty struct
    struct EmptyPred { EmptyPred() {} };           // equal_to_2<>: user ctor, so no zeroing store
    struct IntegralTrue { };                       // eastl::integral_constant<bool,true>

    // eastl::fixed_hash_map<string16, Face, 8, 9, 1>, size 0x2bd4.
    struct FaceMapRT
    {
        char        pad0[4];            // +0x00
        FaceNode**  mpBucketArray;      // +0x04
        uint32_t    mnBucketCount;      // +0x08
        uint32_t    mnElementCount;     // +0x0c
        char        mRest[0x2bd4 - 0x10];

        HashIter<FaceNode> find_as(const wchar_t* const& key, EmptyFunctor, EmptyPred); // 0x0088c600

        HashIter<FaceNode> begin() const
        {
            HashIter<FaceNode> it;
            it.mpBucket = mpBucketArray;
            it.mpNode   = *mpBucketArray;
            if (!it.mpNode)
                it.increment_bucket();
            return it;
        }
        FaceNode* endNode() const { return mpBucketArray[mnBucketCount]; }
    };

    // eastl::fixed_hash_map<string16, string16, 4, 5, 1>, size 0x118.
    struct SubstInsertResult
    {
        HashIter<SubstNode> first;
        bool                second;
    };

    struct SubstMapRT
    {
        char        pad0[4];            // +0x00
        SubstNode** mpBucketArray;      // +0x04
        uint32_t    mnBucketCount;      // +0x08
        uint32_t    mnElementCount;     // +0x0c
        char        mRehashPolicy[0x0c];// +0x10
        FixedPool   mPool;              // +0x1c
        void*       mpBucketBuffer;     // +0x30
        char        mRest[0x118 - 0x34];

        HashIter<SubstNode> find(const Str16& key);                       // 0x0088cf80
        HashIter<SubstNode> find_as(const wchar_t* const& key, EmptyFunctor, EmptyPred); // 0x0088cf00
        SubstInsertResult DoInsertValue(const StrPair& value, IntegralTrue); // 0x0088d020
        SubstNode* endNode() const { return mpBucketArray[mnBucketCount]; }

        void DoFreeNodes(SubstNode** pBucketArray, uint32_t nBucketCount); // 0x0088df70
    };

// @ 0x0088df70
    void SubstMapRT::DoFreeNodes(SubstNode** pBucketArray, uint32_t nBucketCount)
    {
        for (uint32_t i = 0; i < nBucketCount; ++i)
        {
            SubstNode* pNode = pBucketArray[i];
            while (pNode)
            {
                SubstNode* pCurrent = pNode;
                pNode = pNode->mpNext;
                pCurrent->second.~Str16();
                pCurrent->first.~Str16();

                if (pCurrent != mpBucketBuffer)
                {
                    if ((char*)pCurrent < (char*)mPool.mpPoolBegin ||
                        (char*)pCurrent >= (char*)mPool.mpPoolEnd)
                        FreeRawBlock(pCurrent);
                    else
                    {
                        *(void**)pCurrent = mPool.mpHead;
                        mPool.mpHead = pCurrent;
                    }
                }
            }
            pBucketArray[i] = 0;
        }
    }

    // eastl::fixed_vector<Face*,8,1>, size 0x38 (only the first three members are used).
    struct FaceVector
    {
        Face**   mpBegin;               // +0x00
        Face**   mpEnd;                 // +0x04
        Face**   mpCapacity;            // +0x08
        char     mBuffer[0x38 - 0x0c];  // +0x0c

        void DoInsertValue(Face** position, Face* const& value);   // 0x00899480

        void clear()
        {
            Face** first = mpBegin;
            Face** last  = mpEnd;
            memcpy(first, last, (char*)mpEnd - (char*)last);
            mpEnd -= (last - first);
        }
        void push_back(Face* const& value)
        {
            if (mpEnd < mpCapacity)
            {
                ::new(mpEnd++) Face*(value);
            }
            else
                DoInsertValue(mpEnd, value);
        }
        uint32_t size() const { return (uint32_t)(mpEnd - mpBegin); }
    };

    // EA::Text::Font (retail virtual order; size 0x48).
    class Font
    {
    public:
        virtual ~Font();                                         // 0 (+0x00)
        virtual void SetAllocator(void* pCoreAllocator);         // 1 (+0x04)
        virtual int  AddRef();                                   // 2 (+0x08)
        virtual int  Release();                                  // 3 (+0x0c)
        virtual void v04();                                      // 4 (+0x10)
        virtual void v05();                                      // 5 (+0x14)
        virtual IStream* GetStream();                            // 6 (+0x18)
        virtual void v07();                                      // 7 (+0x1c)
        virtual void SetOption(int option, int value);           // 8 (+0x20)
        virtual void v09();                                      // 9 (+0x24)
        virtual int  GetFontType();                              // 10 (+0x28)
        virtual bool GetFontDescription(FontDescription& fd);    // 11 (+0x2c)
        virtual void v12();                                      // 12 (+0x30)
        virtual void v13();                                      // 13 (+0x34)
        virtual void v14();                                      // 14 (+0x38)
        virtual bool IsCharSupported(Char c, int script);        // 15 (+0x3c)
        virtual void v16();                                      // 16 (+0x40)
        virtual void v17();                                      // 17 (+0x44)
        virtual void SetTransform(float fSize, float fAngle, float fSkew); // 18 (+0x48)
        virtual void v19();                                      // 19 (+0x4c)
        virtual void v20();                                      // 20 (+0x50)
        virtual void v21();                                      // 21 (+0x54)
        virtual void* GetOTF();                                  // 22 (+0x58)
    };

    // eastl::AutoRefCount<Font>: holds one reference on the Font.
    class AutoRefCount
    {
    public:
        Font* mpObject;   // +0x00

        AutoRefCount(Font* p) : mpObject(p) { p->AddRef(); }
        AutoRefCount(const AutoRefCount& rhs) : mpObject(rhs.mpObject) { mpObject->AddRef(); }
        ~AutoRefCount() { mpObject->Release(); }
    };

    // FontSelection: eastl::fixed_set<AutoRefCount<Font>,8,1>.
    struct RbIter { void* mpNode; };

    struct SetInsertResult
    {
        RbIter first;
        bool   second;
    };

    struct FontSet
    {
        SetInsertResult DoInsertValue(const AutoRefCount& value, IntegralTrue);  // 0x0088d120
        void insert(const AutoRefCount& value)
        {
            DoInsertValue(value, IntegralTrue());
        }
    };

    class OutlineFont : public Font
    {
    public:
        OutlineFont(void* pCoreAllocator);

        virtual bool v23();                                      // 23 (+0x5c)
        virtual bool Open(IStream* pStream, int nFaceIndex);     // 24 (+0x60)
        virtual bool SetSmoothing(int nSmooth);                  // 25 (+0x64)
        virtual bool SetEffect(unsigned effect, float fEffectX, float fEffectY,
                               unsigned effectBaseColor, unsigned effectColor,
                               unsigned highLightColor);         // 26 (+0x68)
        char mData[0x2d0 - sizeof(Font)];
    };

    class BmpFont : public Font
    {
    public:
        BmpFont(void* pCoreAllocator);

        virtual bool Open(FaceSource* pFaceSource, int nArg);    // 23 (+0x5c)
        virtual void* GetGlyphCache();                           // 24 (+0x60)
        virtual void SetGlyphCache(void* pGlyphCache);           // 25 (+0x64)
        virtual unsigned GetTextureCount();                      // 26 (+0x68)
        virtual BmpTextureInfo* GetBitmapTextureInfo(unsigned index); // 27 (+0x6c)
        virtual void ReadBmpTexture(IStream* pStream, unsigned index); // 28 (+0x70)
        char mData[0x1e0 - sizeof(Font)];
    };

    class PolygonFont : public Font
    {
    public:
        PolygonFont(void* pCoreAllocator);

        virtual bool v23();                                      // 23 (+0x5c)
        virtual bool Open(IStream* pStream);                     // 24 (+0x60)
        char mData[0x198 - sizeof(Font)];
    };

    class FontServer
    {
    public:
        virtual ~FontServer();                                   // 0
        virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
        virtual Font* CreateNewFont(FaceSource* pFaceSource, const TextStyle& ssCSS, bool bManaged); // 5 (+0x14)
        virtual Font* GetFont(const TextStyle* pTextStyle, Font* pFontArray[],
                              uint32_t nFontArrayCapacity, Char c, int script, bool bManaged); // 6 (+0x1c)
        virtual Font* GetFont(const TextStyle* pTextStyle, FontSet& fontSelection,
                              uint32_t nMaxFonts, Char c, int script, bool bManaged); // 7 (+0x18)
        virtual bool AddFont(Font* pFont);                       // 8 (+0x20)
        virtual void v09(); virtual void v10(); virtual void v11();
        virtual void v12(); virtual void v13();
        virtual bool AddSubstitution(const wchar_t* pFamilyName, const wchar_t* pSubstituteName); // 14 (+0x38)
        virtual int GetFontDescriptionScore(const FontDescription& fd, const TextStyle& ssCSS);    // 15 (+0x3c)
        virtual void AddFaceSource(const FaceSource& faceSource);                                  // 16 (+0x40)

        char   mPad04[4];              // +0x04 (unused, keeps PDB offsets)
        bool   mbInitialized;           // +0x08
        bool   mbOTFEnabled;            // +0x09
        bool   mbSmartFallbackEnabled;  // +0x0a
        char   pad0b[1];
        void*  mpCoreAllocator;         // +0x0c
        TextStyle mTextStyleDefault;    // +0x10
        FaceMapRT mFaceMap;             // +0x288
        void*  mpGlyphCacheDefault;     // +0x2e5c
        FaceVector mFaceArray;          // +0x2e60
        SubstMapRT mFamilySubstitutionMap; // +0x2e98
        char   mMutex[0x20];            // +0x2fb0 (EA::Thread::Futex)
    };

    const wchar_t* GetFileName(const wchar_t* pPath); // 0x0088b870

// @ 0x0088d2a0
    Font* FontServer::GetFont(const TextStyle* pTextStyle, Font* pFontArray[], uint32_t nFontArrayCapacity,
                              Char c, int script, bool bManaged)
    {
        AutoMutex autoMutex(mMutex);

        Font*           pPrimaryFont = NULL;
        wchar_t         familyNameArray[8][32];
        uint32_t        nFamilyNameCount = 0;
        FaceSource*     pFaceSourceArray[32];
        uint32_t        nFaceSourceArraySize = 0;
        uint32_t        nMaxFaceSourceArraySize = 32;
        uint32_t        i, iEnd;
        bool            bSmartFallbackEnabled = mbSmartFallbackEnabled;

        if (nFontArrayCapacity > 32)
            nFontArrayCapacity = 32;

        if (!pTextStyle)
            pTextStyle = &mTextStyleDefault;

        if (nFontArrayCapacity)
            memset(pFontArray, 0, sizeof(Font*) * nFontArrayCapacity);

        mFaceArray.clear();

        // Copy the family names, lower-cased.
        for (i = 0; (i < 8) && pTextStyle->mFamilyNameArray[i][0]; i++)
        {
            wcscpy(familyNameArray[i], pTextStyle->mFamilyNameArray[i]);
            _wcslwr(familyNameArray[i]);
            ++nFamilyNameCount;
        }

        if (mFamilySubstitutionMap.mnElementCount != 0)
        {
            for (int n = (int)nFamilyNameCount - 1; n >= 0; --n)
            {
                wchar_t* const pFamily = familyNameArray[n];
                HashIter<SubstNode> it = mFamilySubstitutionMap.find_as(pFamily, EmptyFunctor(), EmptyPred());
                if (it.mpNode != mFamilySubstitutionMap.endNode())
                {
                    wcsncpy(pFamily, it.mpNode->second.mpBegin, 32);
                    pFamily[31] = 0;
                }
            }
        }

        for (i = 0; i < nFamilyNameCount; i++)
        {
            const wchar_t* key = familyNameArray[i];
            HashIter<FaceNode> it = mFaceMap.find_as(key, EmptyFunctor(), EmptyPred());
            if (it.mpNode != mFaceMap.endNode())
            {
                Face* face = &it.mpNode->mFace;
                mFaceArray.push_back(face);
            }
        }

    TryFaceArray:
        for (i = 0, iEnd = mFaceArray.size(); (i < iEnd) && (nFaceSourceArraySize < nMaxFaceSourceArraySize); i++)
        {
            Face* const pFace = mFaceArray.mpBegin[i];
            FaceSource* pFaceSourceBestMatch = NULL;
            int         nScoreBestMatch = -1;
            int         nCharSupported = -1;

            for (ListNode* node = pFace->mFaceSourceList.mNode.mpNext;
                 (node != &pFace->mFaceSourceList.mNode) && (nCharSupported != 0); node = node->mpNext)
            {
                FaceSource& faceSource = ((FaceSourceNode*)node)->value;

                if ((nCharSupported == -1) && !faceSource.mFontList.empty())
                {
                    Font* const pFont = ((FontList*)&faceSource.mFontList)->mNode.mpNext ?
                                        *(Font**)((char*)faceSource.mFontList.mNode.mpNext + sizeof(ListNode)) : NULL;
                    nCharSupported = (pFont->IsCharSupported(c, script) ? 1 : 0);
                }

                if (nCharSupported != 0)
                {
                    const int nScore = GetFontDescriptionScore(faceSource.mFontDescription, *pTextStyle);
                    if (nScore > nScoreBestMatch)
                    {
                        pFaceSourceBestMatch = &faceSource;
                        nScoreBestMatch = nScore;
                    }
                }
            }

            if (pFaceSourceBestMatch)
            {
                if (nCharSupported == -1)
                {
                    if ((c < 0x80) || ((c == 0xffff) && (script == -1)))
                        nCharSupported = 1;
                    else
                    {
                        Font* const pFont = CreateNewFont(pFaceSourceBestMatch, *pTextStyle, true);
                        if (pFont)
                        {
                            nCharSupported = (pFont->IsCharSupported(c, script) ? 1 : 0);
                            pFont->Release();
                        }
                    }
                }

                if (nCharSupported == 1)
                {
                    pFaceSourceArray[nFaceSourceArraySize] = pFaceSourceBestMatch;
                    ++nFaceSourceArraySize;
                }
            }
        }

        if (!nFaceSourceArraySize)
        {
            if (bSmartFallbackEnabled)
            {
                bSmartFallbackEnabled = false;
                nMaxFaceSourceArraySize = 1;
                mFaceArray.clear();

                for (HashIter<FaceNode> it = mFaceMap.begin(); it.mpNode != mFaceMap.endNode(); )
                {
                    Face* face = &it.mpNode->mFace;
                    mFaceArray.push_back(face);
                    it.increment();
                }

                goto TryFaceArray;
            }
            else
            {
                for (HashIter<FaceNode> it = mFaceMap.begin(); it.mpNode != mFaceMap.endNode(); )
                {
                    FaceSourceList* list = &it.mpNode->mFace.mFaceSourceList;
                    if (!list->empty())
                    {
                        pFaceSourceArray[nFaceSourceArraySize] = &((FaceSourceNode*)list->mNode.mpNext)->value;
                        nFaceSourceArraySize++;
                        break;
                    }
                    it.increment();
                }
            }
        }

        FontDescription fontDescription;

        for (uint32_t k = 0; k < nFaceSourceArraySize; k++)
        {
            Font* pFontCurrent = NULL;

            if (bManaged)
            {
                for (ListNode* node = pFaceSourceArray[k]->mFontList.mNode.mpNext;
                     node != &pFaceSourceArray[k]->mFontList.mNode; node = node->mpNext)
                {
                    pFontCurrent = ((FontNode*)node)->value;
                    pFontCurrent->GetFontDescription(fontDescription);

                    if ((fabsf(fontDescription.mfSize - pTextStyle->mfSize) < 0.05f) &&
                        (fontDescription.mSmooth == pTextStyle->mSmooth) &&
                        (fontDescription.mEffect == pTextStyle->mEffect))
                    {
                        pFontCurrent->AddRef();
                        break;
                    }
                    else
                        pFontCurrent = NULL;
                }
            }

            if (!pFontCurrent)
            {
                if (!pPrimaryFont || (k < nFontArrayCapacity))
                    pFontCurrent = CreateNewFont(pFaceSourceArray[k], *pTextStyle, bManaged);
            }

            if (pFontCurrent)
            {
                if (!pPrimaryFont)
                    pPrimaryFont = pFontCurrent;

                if (k < nFontArrayCapacity)
                    pFontArray[k] = pFontCurrent;
            }
        }

        return pPrimaryFont;
    }

// @ 0x0088d940
    bool FontServer::AddFont(Font* pFont)
    {
        AutoMutex autoMutex(mMutex);

        FontDescription fd;

        if (pFont && pFont->GetFontDescription(fd))
        {
            FaceSource faceSource;

            faceSource.mpStream = pFont->GetStream();
            faceSource.mpStream->AddRef();
            faceSource.mFontType = pFont->GetFontType();
            faceSource.mFontDescription = fd;
            faceSource.mnFontIndex = 0;
            pFont->AddRef();
            faceSource.mFontList.push_back(pFont);
            AddFaceSource(faceSource);
        }

        return false;
    }

// @ 0x0088daf0
    Font* FontServer::CreateNewFont(FaceSource* pFaceSource, const TextStyle& ssCSS, bool bManaged)
    {
        bool  bResult = false;
        Font* pFont   = NULL;

        if (pFaceSource->mFontType == 2) // kFontTypeOutline
        {
            OutlineFont* const pOutlineFont =
                new ("EAText/Font", 0, 0, 0, 0) OutlineFont(NULL);

            if (pOutlineFont)
            {
                pOutlineFont->AddRef();
                pOutlineFont->SetAllocator(mpCoreAllocator);
                pOutlineFont->SetOption(1, mbOTFEnabled ? 1 : 0);
                bResult = pOutlineFont->Open(pFaceSource->mpStream, pFaceSource->mnFontIndex);

                if (bResult)
                {
                    pOutlineFont->SetTransform(ssCSS.mfSize, 0.f, 0.f);
                    pOutlineFont->SetSmoothing(ssCSS.mSmooth);
                    if (ssCSS.mEffect)
                    {
                        pOutlineFont->SetEffect(ssCSS.mEffect, ssCSS.mfEffectX, ssCSS.mfEffectY,
                                                ssCSS.mEffectBaseColor, ssCSS.mEffectColor,
                                                ssCSS.mHighLightColor);
                    }
                }
                pFont = pOutlineFont;
            }
        }
        else if (pFaceSource->mFontType == 1) // kFontTypeBitmap
        {
            BmpFont* const pBmpFont =
                new ("EAText/BmpFont", 0, 0, 0, 0) BmpFont(NULL);

            if (pBmpFont)
            {
                pBmpFont->AddRef();
                pBmpFont->SetAllocator(mpCoreAllocator);
                pBmpFont->SetOption(1, mbOTFEnabled ? 1 : 0);

                if (!pBmpFont->GetGlyphCache())
                    pBmpFont->SetGlyphCache(mpGlyphCacheDefault);

                bResult = pBmpFont->Open(pFaceSource, 1);

                if (bResult && (pFaceSource->mpStream->GetType() == 0x34722300))
                {
                    FileStream* const pFileStream =
                        static_cast<FileStream*>(pFaceSource->mpStream);

                    PathString16 path(0x100, 0);
                    pFileStream->GetPath(path.mpBegin, 0x100);

                    const wchar_t* const pPathBegin = path.mpBegin;
                    const wchar_t* pFileName = GetFileName(pPathBegin);
                    path.resize((uint32_t)(pFileName - pPathBegin));

                    const unsigned nTextureCount = pBmpFont->GetTextureCount();
                    for (unsigned i = 0; i < nTextureCount; i++)
                    {
                        BmpTextureInfo* pTextureInfo = pBmpFont->GetBitmapTextureInfo(i);
                        pTextureInfo->mTextureFilePath.insert(pTextureInfo->mTextureFilePath.mpBegin,
                                                              path.mpBegin, path.mpEnd);

                        FileStream* pStream =
                            new ("EAText/BmpFont", 0, 0, 0, 0) FileStream(pTextureInfo->mTextureFilePath.mpBegin);
                        pStream->AddRef();
                        if (pStream->Open(1, 6, 1, 0))
                            pBmpFont->ReadBmpTexture(pStream, i);
                        pStream->Release();
                    }
                }
                pFont = pBmpFont;
            }
        }
        else if (pFaceSource->mFontType == 4) // kFontTypePolygon
        {
            PolygonFont* const pPolygonFont =
                new ("EAText/PolygonFont", 0, 0, 0, 0) PolygonFont(NULL);

            if (pPolygonFont)
            {
                pPolygonFont->AddRef();
                pPolygonFont->SetAllocator(mpCoreAllocator);
                pPolygonFont->SetOption(1, mbOTFEnabled ? 1 : 0);
                bResult = pPolygonFont->Open(pFaceSource->mpStream);
                if (bResult)
                    pFont = pPolygonFont;
            }
        }

        if (bResult)
        {
            pFont->AddRef();
            if (bManaged)
            {
                pFont->AddRef();
                pFaceSource->mFontList.push_back(pFont);
            }
        }

        if (pFont)
            pFont->Release();

        return pFont;
    }

// @ 0x0088e020
    Font* FontServer::GetFont(const TextStyle* pTextStyle, FontSet& fontSelection,
                              uint32_t nMaxFonts, Char c, int script, bool bManaged)
    {
        Font*          pPrimaryFont;
        const uint32_t kFontArraySize = 32;
        Font*          pFontArray[kFontArraySize];
        const uint32_t nFontArrayCapacity =
            (nMaxFonts < kFontArraySize ? nMaxFonts : kFontArraySize);

        pPrimaryFont = GetFont(pTextStyle, pFontArray, nFontArrayCapacity,
                               c, script, bManaged);

        for (uint32_t i = 0; i < nFontArrayCapacity; i++)
        {
            Font* const pFont = pFontArray[i];
            if (!pFont)
                break;

            fontSelection.insert(pFont);
            pFontArray[i]->Release();
        }

        return pPrimaryFont;
    }

// @ 0x0088e0e0
    bool FontServer::AddSubstitution(const wchar_t* pFamilyName, const wchar_t* pSubstituteName)
    {
        AutoMutex autoMutex(mMutex);

        Str16 familyName;
        familyName.RangeInitialize(pFamilyName);
        familyName.make_lower();

        if (familyName.length() <= 0x1f)
        {
            Str16 substituteName;
            substituteName.RangeInitialize(pSubstituteName);
            substituteName.make_lower();

            if (substituteName.length() <= 0x1f)
            {
                const HashIter<SubstNode> it =
                    mFamilySubstitutionMap.find(familyName);
                if (it.mpNode == mFamilySubstitutionMap.endNode())
                {
                    StrPair entry(familyName, substituteName);
                    mFamilySubstitutionMap.DoInsertValue(entry, IntegralTrue());
                }
            }
        }

        return false;
    }
}
