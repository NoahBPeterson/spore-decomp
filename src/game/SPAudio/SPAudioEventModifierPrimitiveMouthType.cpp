// src/game/SPAudio/SPAudioEventModifierPrimitiveMouthType.cpp -- migrated from slice(s) s00a3af80 by tools/migrate/rewrite.py
// Object file: SPAudio/SPAudioEventModifierPrimitiveMouthType.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/Command.h"
#include "EA/Audio/IConfiguration.h"
#include "EA/Audio/ResponseCurve.h"
#include "SP/Audio/cEventModifierPrimitive.h"
#include "SP/Audio/cListener.h"

// unnamed retail callees and globals (address in the comment)
extern char gStrEmpty[];   // 0x1667bac (shared empty eastl string)
extern char gMouthNameA[];               // 0x014537e8
extern char gMouthNameB[];               // 0x014537ec

// ---- items of slice s00a3af80 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint32;
extern char gStrEmpty[];   // 0x1667bac (shared empty eastl string)
void operator delete[](void*);   // 0x00f47380
struct String8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    int mAlloc;
    String8() {
        mpBegin = gStrEmpty;
        mpEnd = gStrEmpty;
        mpCapacity = gStrEmpty + 1;
    }
    ~String8() { if (mpCapacity - mpBegin > 1 && mpBegin) operator delete[](mpBegin); }
    void assign(char* pBegin, char* pEnd);   // 0x00454cb0 (eastl::basic_string::assign)
};
struct StrPair {
    const uint32 first;
    String8 second;
    StrPair(const uint32& key, const String8& value);   // 0x00b209f0
};
struct StrNode {
    StrPair mValue;      // +0x00
    StrNode* mpNext;     // +0x14
};
struct StrIterBase {
    StrNode* mpNode;
    StrNode** mpBucket;
    StrIterBase(StrNode* pNode, StrNode** pBucket) : mpNode(pNode), mpBucket(pBucket) {}
};
struct StrIter : StrIterBase {
    StrIter(StrNode* pNode = 0, StrNode** pBucket = 0) : StrIterBase(pNode, pBucket) {}
    StrIter(StrNode** pBucket) : StrIterBase(*pBucket, pBucket) {}
    StrIter(const StrIter& x) : StrIterBase(x.mpNode, x.mpBucket) {}
};
inline bool operator!=(const StrIterBase& a, const StrIterBase& b) { return a.mpNode != b.mpNode; }
inline bool operator==(const StrIterBase& a, const StrIterBase& b) { return a.mpNode == b.mpNode; }
namespace eastl {
struct true_type {};
}
namespace eastl {
template <typename T1, typename T2> struct pair_s00a3_af80 { T1 first; T2 second; };
}
struct RehashPolicy {
    float mfMaxLoadFactor;
    float mfGrowthFactor;
    unsigned mnNextResize;
};
struct StrHashTable {
    int mFunctors;                // +0x00
    StrNode** mpBucketArray;      // +0x04
    unsigned mnBucketCount;       // +0x08
    unsigned mnElementCount;      // +0x0c
    RehashPolicy mRehashPolicy;   // +0x10
    StrIter find(const uint32& key);                                   // 0x00a3b2c0
    StrIter end() { return StrIter(mpBucketArray + mnBucketCount); }
    eastl::pair_s00a3_af80<StrIter, bool> DoInsertValue(const StrPair& value,
                                             eastl::true_type);        // 0x00a3b580
    eastl::pair_s00a3_af80<StrIter, bool> insert(const StrPair& value) {
        return DoInsertValue(value, eastl::true_type());
    }
    // eastl::hash_map<unsigned, String8>::operator[]; named OperatorIndex (not operator[]) so the
    // checker can bind the symbol (MSVC mangles operator[] as ??A, which the marker match rejects).
    String8& OperatorIndex(const uint32& key);
};
void operator delete(void*);       // 0x00f47380
#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define V  virtual void CAT(pad_, __COUNTER__)();
#define V4 V V V V
#define V16 V4 V4 V4 V4
extern char gMouthNameA[];               // 0x014537e8
extern char gMouthNameB[];               // 0x014537ec
namespace EA {
namespace Audio {
struct ResourceKey;
}
}
namespace EA {
namespace Audio {
struct IConfiguration_s00a3_af80;
}
}
namespace EA {
namespace Audio {
struct Command_s00a3_af80 {
    bool GetUint32(uint32 nKey, uint32* pValue);                             // 0x00a0fab0
};
}
}
namespace EA {
namespace Audio {
struct IConfiguration_s00a3_af80 {
    V
    virtual void Release();                                        // slot 1  +0x04
    V
    virtual void GetKeys(void* pKeys, int nFlags);                 // slot 3  +0x0c
    V4 V4 V4
    virtual char* GetDisplayName(uint32 nKey);                     // slot 16 +0x40
};
}
}
namespace EA {
namespace Audio {
struct AudioSystem {
    V16 V16 V16 V4 V4 V V V       // slots 0..58
    virtual char* GetNameById(uint32 nId);        // slot 59 +0xec
    V
    V
    V16
    virtual bool GetConfiguration(uint32 nInstance, IConfiguration_s00a3_af80** ppConfiguration,
                                  uint32 nGroup);                  // slot 78 +0x138
};
}
}
namespace EA {
namespace Audio {
AudioSystem* GetSystemAT();                                    // 0x00a206f0
}
}
namespace SP {
namespace Audio {
struct cEventModifierPrimitive_s00a3_af80 {
    void*  mpVtable;                             // +0x00
    int    mnRefCount;                           // +0x04
    uint32 mKeyInstance;                         // +0x08
    uint32 mKeyType;                             // +0x0c
    uint32 mKeyGroup;                            // +0x10
    EA::Audio::IConfiguration_s00a3_af80* mConfiguration;   // +0x14
    bool ReadTuningValues(const EA::Audio::ResourceKey* pKey);    // 0x00a3a610
    void Append(char* pDst, int nCapacity, char* pStr, bool bSep); // 0x00a3a4c0
};
}
}
namespace SP {
namespace Audio {
struct cEventModifierPrimitiveMouthType : cEventModifierPrimitive_s00a3_af80 {
    StrHashTable mTable;                         // +0x18
    void ModifyEvent(EA::Audio::Command_s00a3_af80* pCmd, uint32 a2, char* pDst, int nCapacity); // 0x00a3b3a0
    void Rebuild(uint32 nInstance, int nMode);   // 0x00a3b720
    bool RebuildAll();                           // 0x00a3b890
    bool RebuildIfCurrent(void* pEntry);         // 0x00a3b970
};
}
}
// ---- items of slice s00a3af80 end

// @ 0x00a3b3a0
namespace SP { namespace Audio {
void cEventModifierPrimitiveMouthType::ModifyEvent( EA::Audio::Command_s00a3_af80* pCmd, uint32 a2, char* pDst, int nCapacity)
{
    EA::Audio::AudioSystem* pSystem = EA::Audio::GetSystemAT();
    uint32 v0;
    if (pCmd->GetUint32(0x39fb001u, &v0) && v0 != 0) {
        StrIter it = mTable.find(v0);
        if (it != mTable.end())
            Append(pDst, nCapacity, it.mpNode->mValue.second.mpBegin, true);
        return;
    }
    uint32 u;
    pCmd->GetUint32(0x39f9e01u, &u);
    if (u == 0) return;
    uint32 w = 0;
    pCmd->GetUint32(0x39f9e08u, &w);
    char* pName;
    uint32 sel;
    if (u == 1) {
        sel = 0x156573c3u;
        if (w >= 5) sel = 0x0b65639du;
    } else if (w < 5) {
        pName = pSystem->GetNameById(u);
        goto have_name;
    } else if (w == 5) {
        {
            StrIter it = mTable.find(u);
            if (it == mTable.end()) return;
            pName = it.mpNode->mValue.second.mpBegin;
        }
        goto have_name;
    } else {
        sel = 0x0b65639du;
    }
    {
        StrIter it = mTable.find(sel);
        if (it == mTable.end()) return;
        pName = it.mpNode->mValue.second.mpBegin;
    }
have_name:
    if (pName == 0) return;
    Append(pDst, nCapacity, pName, false);
    Append(pDst, nCapacity, (w < 5) ? gMouthNameA : gMouthNameB, false);
    uint32 b = 1;
    if (pCmd->GetUint32(0x44d63a2u, &b) && b == 0) pDst[0] = 'b';
    uint32 e = 0;
    if (pCmd->GetUint32(0x48def6du, &e) && e != 0) pDst[0] = 'e';
}
}}  // namespace SP::Audio
