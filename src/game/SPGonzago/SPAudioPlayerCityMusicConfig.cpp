// src/game/SPGonzago/SPAudioPlayerCityMusicConfig.cpp -- migrated from slice(s) s00eb0ea0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPAudioPlayerCityMusicConfig.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Random/RandomLinearCongruential.h"
#include "EA/Stopwatch.h"

// unnamed retail callees and globals (address in the comment)
extern "C" long _InterlockedExchange(volatile long* pTarget, long nValue);
extern uint32_t g_nResourceKeyA;                                // 0x015a93b4
extern uint32_t g_nResourceKeyB;                                // 0x015a93b8
extern uint32_t g_nResourceKeyC;                                // 0x015a93bc
extern uint32_t g_nResourceKeyD;                                // 0x015a93c0
extern uint32_t g_nResourceKeyE;                                // 0x015a93c4
extern uint32_t g_nResourceKeyF;                                // 0x015a93c8
extern const uint32_t g_nDegreeFloatKeys[7];                    // 0x0148850c
extern const uint32_t g_nDegreeUintKeys[7];                     // 0x01488528
#pragma intrinsic(_InterlockedExchange)

// ---- items of slice s00eb0ea0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#define nullptr 0
extern "C" long _InterlockedExchange(volatile long* pTarget, long nValue);
void  operator_delete__(void* pMemory);                         // 0x00f47380
void GetPropertyAsUint32(void* pList, uint32_t nKey, uint32_t* pValue);        // 0x004af210
void GetPropertyT(void* pList, uint32_t nKey, int32_t* pValue);              // 0x0040cf10
void GetPropertyAsFloatArray(void* pList, uint32_t nKey, int32_t* pCount,
                             float** ppValues);                             // 0x006a08b0
void GetPropertyAsUint32Array(void* pList, uint32_t nKey, int32_t* pCount,
                              uint32_t** ppValues);                         // 0x006a0840
void FUN_00eb1460(int32_t nCount, void** ppValues);              // 0x00eb1460
extern uint32_t g_nResourceKeyA;                                // 0x015a93b4
extern uint32_t g_nResourceKeyB;                                // 0x015a93b8
extern uint32_t g_nResourceKeyC;                                // 0x015a93bc
extern uint32_t g_nResourceKeyD;                                // 0x015a93c0
extern uint32_t g_nResourceKeyE;                                // 0x015a93c4
extern uint32_t g_nResourceKeyF;                                // 0x015a93c8
extern const uint32_t g_nDegreeFloatKeys[7];                    // 0x0148850c
extern const uint32_t g_nDegreeUintKeys[7];                     // 0x01488528
class cResourceManager {
public:
virtual void r00();
virtual void r04();
virtual void r08();
    virtual void* GetResource(uint32_t* pKey, void** ppOut, int32_t nA,
                              int32_t nB, int32_t nC, int32_t nD);  // 0x00c
};
cResourceManager* GetManager();                                 // 0x0067dcd0
class cPropertyValue {
public:
    uint32_t GetUint32()
    {
        uint32_t* pData = (mbFlags & 0x30) ? (uint32_t*)mpValue : (uint32_t*)this;
        return *pData;
    }

    void*    mpValue;                                           // 0x000
    uint8_t  mPad004[0x0c];                                     // 0x004
    uint8_t  mbFlags;                                           // 0x010
    uint8_t  mPad011;                                           // 0x011
    uint16_t mnType;                                            // 0x012
};
class cPropertyList {
public:
    __forceinline cPropertyList()
    {
        _InterlockedExchange(&mnRefCount, 0);
        mnField08 = 0;
        mnField0C = 0;
        mnField10 = 0;
    }
virtual void p00();
virtual void p04();
virtual void p08();
    virtual void* GetProperty(uint32_t nKey);                   // 0x00c
    virtual void* GetPropertyValue(uint32_t nKey, void** ppValue);  // 0x024

    volatile long mnRefCount;                                   // 0x004
    uint32_t mnField08;                                         // 0x008
    uint32_t mnField0C;                                         // 0x00c
    uint32_t mnField10;                                         // 0x010
};
class cAutoRefCount {
public:
    void Assign(void* pValue)
    {
        void* pOld = mpObject;
        if (pValue != pOld) {
            if (pValue != nullptr)
                ((cPropertyList*)pValue)->p00();
            mpObject = pValue;
            if (pOld != nullptr)
                ((cPropertyList*)pOld)->p04();
        }
    }

    void* mpObject;                                             // 0x000
};
class cPlayerCityMusicConfig {
public:
    cPlayerCityMusicConfig();
    bool Reload(uint32_t nKeyA, uint32_t nKeyB, uint32_t nKeyC); // 0x00eb14c0

    uint32_t mNumAmbiences;                                     // 0x000
    uint32_t mNumRhythms;                                       // 0x004
    uint32_t mNumInstruments;                                   // 0x008
    uint32_t mMaxAmbienceLayers;                                // 0x00c
    uint32_t mMinNotes;                                         // 0x010
    uint32_t mMaxNotes;                                         // 0x014
    float*   mpNumNoteDistribution;                             // 0x018
    float    mfBeatIncrement;                                   // 0x01c
    float    mfMaxBeats;                                        // 0x020
    uint32_t mMouseWheelIncrement;                              // 0x024
    uint32_t* mpBeatDistSizesBegin;                             // 0x028
    uint32_t* mpBeatDistSizesEnd;                               // 0x02c
    uint32_t* mpBeatDistributionsBegin;                         // 0x030
    uint32_t* mpBeatDistributionsEnd;                           // 0x034
    uint32_t* mpBeatDistributionsCap;                           // 0x038
    uint8_t  mPad03C[0x1c];                                     // 0x03c
    uint32_t mDegreeTransitions[4];                             // 0x058
    float*   mpDegreeNotes[7];                                  // 0x068
    uint32_t* mpDegreeSuggestions[7];                           // 0x084
    uint32_t mMouseWheelUndoTimeMs;                             // 0x0a0
    uint32_t mIcons[3];                                         // 0x0a4
    void*    mpConfig;                                          // 0x0b0
    void*    mpBeatConfig;                                      // 0x0b4
    uint8_t  mPad0B8[0x08];                                     // 0x0b8
    cAutoRefCount mTribeSource;                                 // 0x0c0
    cAutoRefCount mBeatSource;                                  // 0x0c4
};
// ---- items of slice s00eb0ea0 end

// @ 0x00eb14c0
bool cPlayerCityMusicConfig::Reload(uint32_t nKeyA, uint32_t nKeyB, uint32_t nKeyC)
{
    if (mTribeSource.mpObject == nullptr || mBeatSource.mpObject == nullptr) {
        mNumAmbiences = 1;
        mNumRhythms = 1;
        mNumInstruments = 1;
        mMaxAmbienceLayers = 1;
        mMinNotes = 0;
        mMaxNotes = 0;
        mpDegreeNotes[1] = nullptr;
        mpDegreeNotes[2] = (float*)1;
        return false;
    }

    if (nKeyA == g_nResourceKeyA && nKeyB == g_nResourceKeyB && nKeyC == g_nResourceKeyC) {
        void* pList = mTribeSource.mpObject;
        int32_t nCount = 0;

        GetPropertyAsUint32(pList, 0x75b15a06, &mNumAmbiences);
        GetPropertyAsUint32(pList, 0x8fe7e6ba, &mNumRhythms);
        GetPropertyAsUint32(pList, 0xbafd17bb, &mNumInstruments);
        GetPropertyAsUint32(pList, 0x6679061f, &mMaxAmbienceLayers);
        GetPropertyAsUint32(pList, 0xed9e0342, &mMinNotes);
        GetPropertyAsUint32(pList, 0x81279214, &mMaxNotes);
        GetPropertyAsFloatArray(pList, 0x2aa962c3, &nCount, &mpNumNoteDistribution);
        GetPropertyT(pList, 0x5f8dca10, (int32_t*)&mfBeatIncrement);
        GetPropertyT(pList, 0xf01da328, (int32_t*)&mfMaxBeats);
        GetPropertyAsUint32(pList, 0x7f7bb0f6, &mMouseWheelIncrement);
        GetPropertyAsUint32(pList, 0x4400b86d, (uint32_t*)&mpBeatDistSizesBegin);
        GetPropertyAsUint32(pList, 0x4a20e21d, (uint32_t*)&mpBeatDistSizesEnd);
        GetPropertyAsUint32(pList, 0x6fa7fdac, &mDegreeTransitions[0]);
        GetPropertyAsUint32(pList, 0xddd19567, &mDegreeTransitions[1]);
        GetPropertyAsUint32(pList, 0xd861c661, &mDegreeTransitions[2]);
        GetPropertyAsUint32Array(pList, 0x24adc124, &nCount, &mpDegreeSuggestions[0]);

        for (int32_t i = 0; i < 7; ++i) {
            nCount = 0;
            GetPropertyAsFloatArray(pList, g_nDegreeFloatKeys[i], &nCount, &mpDegreeNotes[i + 1]);
        }

        for (int32_t i = 0; i < 7; ++i) {
            nCount = 0;
            GetPropertyAsUint32Array(pList, g_nDegreeUintKeys[i], &nCount,
                                     &mpDegreeSuggestions[i + 1]);
        }

        void* pValue = nullptr;
        if (pList != nullptr &&
            ((cPropertyList*)pList)->GetPropertyValue(0xa62de8c7, &pValue) &&
            ((cPropertyValue*)pValue)->mnType == 10) {
            mMouseWheelUndoTimeMs = ((cPropertyValue*)pValue)->GetUint32();
        }

        pValue = nullptr;
        if (pList != nullptr &&
            ((cPropertyList*)pList)->GetPropertyValue(0xe801bd27, &pValue) &&
            ((cPropertyValue*)pValue)->mnType == 10) {
            mIcons[0] = ((cPropertyValue*)pValue)->GetUint32();
        }

        pValue = nullptr;
        if (pList != nullptr &&
            ((cPropertyList*)pList)->GetPropertyValue(0xbbe3fda9, &pValue) &&
            ((cPropertyValue*)pValue)->mnType == 10) {
            mIcons[1] = ((cPropertyValue*)pValue)->GetUint32();
        }

        pValue = nullptr;
        if (pList != nullptr &&
            ((cPropertyList*)pList)->GetPropertyValue(0xe87f3a32, &pValue) &&
            ((cPropertyValue*)pValue)->mnType == 10) {
            mIcons[2] = ((cPropertyValue*)pValue)->GetUint32();
        }

        pValue = nullptr;
        if (pList != nullptr &&
            ((cPropertyList*)pList)->GetPropertyValue(0x5263c6ee, &pValue) &&
            ((cPropertyValue*)pValue)->mnType == 10) {
            mpConfig = (void*)((cPropertyValue*)pValue)->GetUint32();
        }

        nCount = 0;
        GetPropertyAsUint32Array(pList, 0xeea41e91, &nCount, &mpBeatDistributionsBegin);
        nCount = 0;
        GetPropertyAsUint32Array(pList, 0xe0abfd7c, &nCount, &mpBeatDistributionsEnd);
        nCount = 0;
        GetPropertyAsUint32Array(pList, 0xaffacd19, &nCount, &mpBeatDistributionsCap);

        uint32_t* pCounts[3] = { &mNumAmbiences, &mNumRhythms, &mNumInstruments };
        uint32_t** ppLists[3] = { &mpBeatDistributionsBegin, &mpBeatDistributionsEnd,
                                  &mpBeatDistributionsCap };
        for (int32_t i = 0; i < 3; ++i) {
            uint32_t nEntries = *pCounts[i];
            uint32_t* pEntries = *ppLists[i];
            if (pEntries == nullptr)
                continue;
            for (uint32_t j = 0; j < nEntries; ++j) {
                pEntries[j * 3 + 0] = 0x2f7d0004;
                pEntries[j * 3 + 1] = 0x05c01e47;
            }
        }

        return true;
    }

    if (nKeyA != g_nResourceKeyD || nKeyB != g_nResourceKeyE || nKeyC != g_nResourceKeyF)
        return false;

    void* pList = mBeatSource.mpObject;
    uint32_t* pKeys = nullptr;
    uint32_t* pKeysEnd = nullptr;
    uint32_t* pKeyData = nullptr;
    ((cPropertyList*)pList)->GetPropertyValue(0, (void**)&pKeys);
    FUN_00eb1460((int32_t)((uint8_t*)pKeysEnd - (uint8_t*)pKeys) >> 2, (void**)&pKeyData);
    FUN_00eb1460((int32_t)((uint8_t*)pKeysEnd - (uint8_t*)pKeys) >> 2, (void**)&pKeyData);

    if (pKeys != nullptr) {
        int32_t nIndex = 0;
        for (uint32_t* pKey = pKeys; pKey != pKeysEnd; ++pKey) {
            int32_t nCount = 0;
            GetPropertyAsFloatArray(pList, *pKey, &nCount,
                                    (float**)((uint8_t*)mpBeatDistSizesBegin + nIndex * 4));
            nIndex += 4;
        }
    }

    if (pKeys != nullptr && ((uint32_t*)pKeys)[-1] != 0)
        operator_delete__(pKeys);

    return true;
}

// @ 0x00eb19e0
cPlayerCityMusicConfig::cPlayerCityMusicConfig()
{
    mfBeatIncrement = 0.0f;
    mfMaxBeats = 0.0f;
    mNumAmbiences = 0;
    mNumRhythms = 0;
    mNumInstruments = 0;
    mMaxAmbienceLayers = 0;
    mMinNotes = 0;
    mMaxNotes = 0;
    mpNumNoteDistribution = nullptr;
    mMouseWheelIncrement = 0;
    mpBeatDistSizesBegin = nullptr;
    mpBeatDistSizesEnd = nullptr;
    mpBeatDistributionsBegin = nullptr;
    mpBeatDistributionsEnd = nullptr;
    mpBeatDistributionsCap = nullptr;
    mDegreeTransitions[0] = 0;
    mDegreeTransitions[1] = 0;
    mDegreeTransitions[2] = 0;
    mDegreeTransitions[3] = 0;
    mpDegreeNotes[0] = nullptr;
    mpDegreeNotes[1] = nullptr;
    mpDegreeNotes[2] = nullptr;
    mpDegreeNotes[3] = nullptr;
    mpDegreeNotes[4] = nullptr;
    mpDegreeNotes[5] = nullptr;
    mpDegreeNotes[6] = nullptr;
    mpDegreeSuggestions[0] = nullptr;
    mpDegreeSuggestions[1] = nullptr;
    mpDegreeSuggestions[2] = nullptr;
    mpDegreeSuggestions[3] = nullptr;
    mpDegreeSuggestions[4] = nullptr;
    mpDegreeSuggestions[5] = nullptr;
    mpDegreeSuggestions[6] = nullptr;
    mMouseWheelUndoTimeMs = 0;
    mIcons[0] = 0;
    mIcons[1] = 0;
    mIcons[2] = 0;
    mpConfig = nullptr;
    mpBeatConfig = nullptr;
    mTribeSource.mpObject = nullptr;
    mBeatSource.mpObject = nullptr;

    void* pLoaded = nullptr;
    cResourceManager* pManager = GetManager();
    if (pLoaded != nullptr) {
        void* pPrev = pLoaded;
        pLoaded = nullptr;
        ((cPropertyList*)pPrev)->p04();
    }

    pManager->GetResource(&g_nResourceKeyA, &pLoaded, 0, 0, 0, 0);
    mTribeSource.Assign(pLoaded);

    pManager = GetManager();
    if (pLoaded != nullptr) {
        void* pPrev = pLoaded;
        pLoaded = nullptr;
        ((cPropertyList*)pPrev)->p04();
    }

    pManager->GetResource(&g_nResourceKeyD, &pLoaded, 0, 0, 0, 0);
    mBeatSource.Assign(pLoaded);

    Reload(g_nResourceKeyA, g_nResourceKeyB, g_nResourceKeyC);
    Reload(g_nResourceKeyD, g_nResourceKeyE, g_nResourceKeyF);

    if (pLoaded != nullptr)
        ((cPropertyList*)pLoaded)->p04();
}
