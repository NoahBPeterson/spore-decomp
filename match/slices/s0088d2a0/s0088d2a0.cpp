// Slice s0088d2a0 - EA::Text::FontServer::GetFont (retail EAText layout, thread-safe build).
//
// 0x0088d2a0  FontServer::GetFont(const TextStyle*, Font* pFontArray[], uint32 capacity,
//                                 Char c, Script script, bool bManaged)   (__thiscall, ret 0x18)
//
// The retail GetFont differs from the vendored upstream EATextFontServer.cpp: it has no
// duplicate test and no score array / score sort, and the pFontArray entries that are not
// returned are not Released. The retail FontServer layout (map/vector/mutex offsets) also differs
// from the vendored header, so the classes below describe only what GetFont touches.
#include "types.h"
#include <string.h>
#include <wchar.h>
#include <math.h>

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void* cs);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void* cs);

inline void* operator new(size_t, void* p) { return p; }

namespace RT
{
    typedef uint16_t Char;

    struct AutoMutex
    {
        void* mpMutex;
        AutoMutex(void* p) : mpMutex(p) { EnterCriticalSection(mpMutex); }
        ~AutoMutex() { LeaveCriticalSection(mpMutex); }
    };

    struct ListNode
    {
        ListNode* next;
        ListNode* prev;
        bool empty() const { return next == this; }
    };

    // 0x74 bytes (matches upstream EA::Text::FontDescription).
    struct FontDescription
    {
        wchar_t  mFamily[32];
        float    mfSize;        // +0x40
        int      mStyle;
        float    mfWeight;
        float    mfStretch;
        int      mPitch;
        int      mVariant;
        int      mSmooth;       // +0x58
        unsigned mEffect;       // +0x5c
        float    mfEffectX;
        float    mfEffectY;
        unsigned mEffectBaseColor;
        unsigned mEffectColor;
        unsigned mHighLightColor;

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
    };

    struct Font
    {
        virtual ~Font();                                     // 0
        virtual void v01();
        virtual int  AddRef();                               // 2 (+8)
        virtual int  Release();                              // 3 (+0xc)
        virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
        virtual void v08(); virtual void v09(); virtual void v10();
        virtual void GetFontDescription(FontDescription& fd);   // 11 (+0x2c)
        virtual void v12(); virtual void v13(); virtual void v14();
        virtual bool IsCharSupported(Char c, int script);       // 15 (+0x3c)
    };

    struct FaceSource
    {
        void*           mpStream;           // +0x00
        int             mFontType;          // +0x04
        FontDescription mFontDescription;   // +0x08
        uint8_t         mnFaceIndex;        // +0x7c
        char            pad7d[3];
        ListNode        mFontList;          // +0x80 (anchor of a list of Font*; node value at +8)
    };

    // Node of the FaceSourceList / FontList: links, then the value.
    struct FaceSourceNode { ListNode links; FaceSource value; };
    struct FontNode       { ListNode links; Font* value; };

    struct Face
    {
        wchar_t   mFamily[32];              // +0x00
        ListNode  mFaceSourceList;          // +0x40 (anchor)
    };

    // Hash node of the face map: key string (0x10), Face, next pointer at +0x4cc.
    struct FaceNode
    {
        char     key[0x10];
        Face     face;                      // +0x10
        char     pad[0x4cc - 0x10 - sizeof(Face)];
        FaceNode* mpNext;                   // +0x4cc
    };

    struct SubstNode
    {
        char     key[0x10];
        wchar_t* valueBegin;                // value string's c_str at +0x10
    };

    template<class NodeT> struct HashIter
    {
        NodeT*  mpNode;
        NodeT** mpBucket;

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

    struct EmptyFunctor {};                       // hash<>: plain empty struct
    struct EmptyPred { EmptyPred() {} };          // equal_to_2<>: user ctor, so no zeroing store

    struct FaceMapRT
    {
        int      pad0;
        FaceNode** mpBucketArray;           // +4
        uint32_t mnBucketCount;             // +8
        uint32_t mnElementCount;            // +0xc

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

    struct SubstMapRT
    {
        int       pad0;
        SubstNode** mpBucketArray;          // +4
        uint32_t  mnBucketCount;            // +8
        uint32_t  mnElementCount;           // +0xc

        HashIter<SubstNode> find_as(wchar_t* const& key, EmptyFunctor, EmptyPred); // 0x0088c560
        SubstNode* endNode() const { return mpBucketArray[mnBucketCount]; }
    };

    struct FaceVector
    {
        Face** mpBegin;
        Face** mpEnd;
        Face** mpCapacity;

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

    struct FontServer
    {
        virtual ~FontServer();                                  // 0
        virtual void v01(); virtual void v02(); virtual void v03(); virtual void v04();
        virtual Font* CreateNewFont(FaceSource* pFaceSource, const TextStyle& ssCSS, bool bManaged); // 5 (+0x14)
        virtual void v06(); virtual void v07(); virtual void v08(); virtual void v09();
        virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
        virtual int GetFontDescriptionScore(const FontDescription& fd, const TextStyle& ssCSS);       // 15 (+0x3c)

        Font* GetFont(const TextStyle* pTextStyle, Font* pFontArray[], uint32_t nFontArrayCapacity,
                      Char c, int script, bool bManaged);

        char       pad04[6];
        bool       mbSmartFallbackEnabled;  // +0x0a
        char       pad0b[5];
        TextStyle  mTextStyleDefault;       // +0x10
        char       pad_to_map[0x288 - 0x10 - sizeof(TextStyle)];
        FaceMapRT  mFaceMap;                // +0x288
        char       pad2[0x2e60 - 0x288 - sizeof(FaceMapRT)];
        FaceVector mFaceArray;              // +0x2e60
        char       pad3[0x2e98 - 0x2e60 - sizeof(FaceVector)];
        SubstMapRT mFamilySubstitutionMap;  // +0x2e98
        char       pad4[0x2fb0 - 0x2e98 - sizeof(SubstMapRT)];
        char       mMutex[0x18];            // +0x2fb0 CRITICAL_SECTION
    };

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
                    wcsncpy(pFamily, it.mpNode->valueBegin, 32);
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
                Face* face = &it.mpNode->face;
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

            for (ListNode* node = pFace->mFaceSourceList.next;
                 (node != &pFace->mFaceSourceList) && (nCharSupported != 0); node = node->next)
            {
                FaceSource& faceSource = ((FaceSourceNode*)node)->value;

                if ((nCharSupported == -1) && !faceSource.mFontList.empty())
                {
                    Font* const pFont = ((FontNode*)faceSource.mFontList.next)->value;
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
                    Face* face = &it.mpNode->face;
                    mFaceArray.push_back(face);
                    it.increment();
                }

                goto TryFaceArray;
            }
            else
            {
                for (HashIter<FaceNode> it = mFaceMap.begin(); it.mpNode != mFaceMap.endNode(); )
                {
                    ListNode* list = &it.mpNode->face.mFaceSourceList;
                    if (!list->empty())
                    {
                        pFaceSourceArray[nFaceSourceArraySize] = &((FaceSourceNode*)list->next)->value;
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
                for (ListNode* node = pFaceSourceArray[k]->mFontList.next; node != &pFaceSourceArray[k]->mFontList; node = node->next)
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
}
