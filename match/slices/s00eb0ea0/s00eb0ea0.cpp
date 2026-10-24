// SP::Audio city music player, its configuration block and the city music
// resource factory.

#include "types.h"

#define nullptr 0

extern "C" long _InterlockedExchange(volatile long* pTarget, long nValue);
#pragma intrinsic(_InterlockedExchange)

inline void* operator new(uint32_t, void* pPlace) { return pPlace; }

// ---------------------------------------------------------------------------
// External helpers of the audio / resource subsystems.
// ---------------------------------------------------------------------------
void* operator_new(uint32_t nSize, const char* pName, int32_t nA, int32_t nB,
                   const char* pFile, int32_t nLine);           // 0x00f473a0
void  operator_delete__(void* pMemory);                         // 0x00f47380

bool WriteUint32(void* pStream, const uint32_t* pValue, uint32_t nCount,
                 int32_t nEndian);                              // 0x0093aa70

void GetPropertyAsUint32(void* pList, uint32_t nKey, uint32_t* pValue);        // 0x004af210
void GetPropertyT(void* pList, uint32_t nKey, int32_t* pValue);              // 0x0040cf10
void GetPropertyAsFloatArray(void* pList, uint32_t nKey, int32_t* pCount,
                             float** ppValues);                             // 0x006a08b0
void GetPropertyAsUint32Array(void* pList, uint32_t nKey, int32_t* pCount,
                              uint32_t** ppValues);                         // 0x006a0840
float GetCyclesToUnitsCoefficient(int32_t nUnits);              // 0x0093a420
void FUN_00eaed40(float* pBuffer, int32_t nCount, const float* pValue);  // 0x00eaed40
void FUN_00eb1460(int32_t nCount, void** ppValues);              // 0x00eb1460

extern uint32_t g_nResourceKeyA;                                // 0x015a93b4
extern uint32_t g_nResourceKeyB;                                // 0x015a93b8
extern uint32_t g_nResourceKeyC;                                // 0x015a93bc
extern uint32_t g_nResourceKeyD;                                // 0x015a93c0
extern uint32_t g_nResourceKeyE;                                // 0x015a93c4
extern uint32_t g_nResourceKeyF;                                // 0x015a93c8
extern const uint32_t g_nDegreeFloatKeys[7];                    // 0x0148850c
extern const uint32_t g_nDegreeUintKeys[7];                     // 0x01488528
extern uint16_t gEmptyString16[];                               // 0x01667bac

// ---------------------------------------------------------------------------
// Notification server and the audio event messages.
// ---------------------------------------------------------------------------
class cMessageServer {
public:
    virtual void m00(); virtual void m04(); virtual void m08(); virtual void m0c();
    virtual void m10(); virtual void m14();
    virtual bool Send(uint32_t nId, int32_t nA, int32_t nB, int32_t nC);   // 0x018
    virtual void m1c(); virtual void m20();
    virtual bool Register(uint32_t nId, void* pHandler);                   // 0x024
};

cMessageServer* MessageServer();                                // 0x0067dcc0

class cEapdMessage {
public:
    uint32_t GetType();                                         // 0x00fcc210
    bool GetNextFloat(float* pValue);                           // 0x00a34e30
    void MarkProcessed();                                       // 0x00a34e80

    uint8_t  mPad004[0x04];                                     // 0x004
    uint32_t mnField08;                                         // 0x008
    uint32_t mnField0C;                                         // 0x00c
    uint32_t mnField10;                                         // 0x010
    uint8_t  mPad014[0x04];                                     // 0x014
    uint32_t mnField18;                                         // 0x018
};

// ---------------------------------------------------------------------------
// Resource manager (loads the two configuration property lists).
// ---------------------------------------------------------------------------
class cResourceManager {
public:
    virtual void r00(); virtual void r04(); virtual void r08();
    virtual void* GetResource(uint32_t* pKey, void** ppOut, int32_t nA,
                              int32_t nB, int32_t nC, int32_t nD);  // 0x00c
};

cResourceManager* GetManager();                                 // 0x0067dcd0

// ---------------------------------------------------------------------------
// Property list value returned by cPropertyList::GetProperty.
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// Reference counted property list, base of the city music resource.
// ---------------------------------------------------------------------------
class cPropertyList {
public:
    __forceinline cPropertyList()
    {
        _InterlockedExchange(&mnRefCount, 0);
        mnField08 = 0;
        mnField0C = 0;
        mnField10 = 0;
    }
    virtual void p00(); virtual void p04(); virtual void p08();
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

// ---------------------------------------------------------------------------
// SP::Audio::cResourceCityMusic (0x6c bytes).
// ---------------------------------------------------------------------------
class cResourceCityMusic : public cPropertyList {
public:
    cResourceCityMusic();

    uint32_t mnField14;                                         // 0x014
    uint32_t mnField18;                                         // 0x018
    uint32_t* mpData1CBegin;                                    // 0x01c
    uint32_t* mpData1CEnd;                                      // 0x020
    uint32_t* mpData1CCap;                                      // 0x024
    uint8_t  mPad028[0x08];                                     // 0x028
    uint32_t* mpData30Begin;                                    // 0x030
    uint32_t* mpData30End;                                      // 0x034
    uint32_t* mpData30Cap;                                      // 0x038
    uint8_t  mPad03C[0x08];                                     // 0x03c
    uint32_t* mpData44Begin;                                    // 0x044
    uint32_t* mpData44End;                                      // 0x048
    uint32_t* mpData44Cap;                                      // 0x04c
    uint8_t  mPad050[0x08];                                     // 0x050
    uint32_t* mpData58Begin;                                    // 0x058
    uint32_t* mpData58End;                                      // 0x05c
    uint32_t* mpData58Cap;                                      // 0x060
    uint8_t  mPad064[0x08];                                     // 0x064
};

class cMusicRing;

struct cRingIter {
    cMusicRing* mpRing;                                         // 0x00
    cResourceCityMusic* mpState;                                // 0x04
};

// ---------------------------------------------------------------------------
// Ring buffer of undo states (20 bytes of bookkeeping after the vector).
// ---------------------------------------------------------------------------
class cMusicRing {
public:
    cMusicRing* resize(int32_t nCount);                         // 0x00eb0d60
    cMusicRing* reserve(int32_t nCount);                        // 0x00eb0df0
    cRingIter erase(cRingIter aFirst, cRingIter aLast);         // 0x00eb0cb0

    int32_t GetCount()
    {
        return (int32_t)((uint8_t*)mpEnd - (uint8_t*)mpBegin) / 0x6c;
    }

    cResourceCityMusic* mpBegin;                                // 0x00
    cResourceCityMusic* mpEnd;                                  // 0x04
    void*    mpField08;                                         // 0x08
    uint8_t  mPad00C[0x08];                                     // 0x0c
    cResourceCityMusic* mpHead;                                 // 0x14
    cResourceCityMusic* mpTail;                                 // 0x18
    uint32_t mnWrap;                                            // 0x1c
};

// ---------------------------------------------------------------------------
// SP::Audio::cPlayerCityMusicConfig (0xc8 bytes).
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// Small engine helpers used by the player state.
// ---------------------------------------------------------------------------
class cRandom {
public:
    void SetSeed(uint32_t nSeed);                               // 0x00936090
};

class cStopwatch {
public:
    void Init(int32_t nCycles, bool bStart);                    // 0x0093a560
    void Restart();                                             // 0x00571e80

    uint8_t mPad00[0x0c];                                       // 0x00
};

// ---------------------------------------------------------------------------
// SP::Audio::cPlayerCityMusic.
// ---------------------------------------------------------------------------
class cPlayerCityMusic {
public:
    cPlayerCityMusic();
    virtual void v00();

    void SaveData(cResourceCityMusic* pState);                  // 0x00eb0390
    void ResetUndoBuffer();                                     // 0x00eb10d0
    void AddUndoState();                                        // 0x00eb1170
    bool HandleMessage(int32_t nType, cEapdMessage* pMessage);  // 0x00eb12a0
    void FUN_00eb0460();                                        // 0x00eb0460
    void Reset(bool bFull);                                     // 0x00ead1a0

    uint8_t  mPad004[0x0c];                                     // 0x004 (IHandler part)
    cPlayerCityMusicConfig mConfig;                             // 0x010
    cMusicRing mUndoBuffer;                                     // 0x0d8
    cMusicRing* mpUndo;                                         // 0x0f8
    cResourceCityMusic* mpUndoBegin;                            // 0x0fc
    uint8_t  mbPaused;                                          // 0x100
    uint8_t  mbQuiet;                                           // 0x101
    uint8_t  mPad102[0x02];                                     // 0x102
    cRandom  mRandom;                                           // 0x104
    uint32_t mnMagic;                                           // 0x108
    void*    mpArray10CBegin;                                   // 0x10c
    void*    mpArray10CEnd;                                     // 0x110
    void*    mpArray10CCap;                                     // 0x114
    void*    mpArray118Begin;                                   // 0x118
    void*    mpArray118End;                                     // 0x11c
    uint8_t  mPad120[0x08];                                     // 0x120
    void*    mpArray128Begin;                                   // 0x128
    void*    mpArray128End;                                     // 0x12c
    void*    mpArray128Cap;                                     // 0x130
    uint8_t  mPad134[0x08];                                     // 0x134
    void*    mpArray13CBegin;                                   // 0x13c
    void*    mpArray13CEnd;                                     // 0x140
    void*    mpArray13CCap;                                     // 0x144
    uint8_t  mPad148[0x08];                                     // 0x148
    float    mfField150;                                        // 0x150
    int32_t  mnField154;                                        // 0x154
    int32_t  mnField158;                                        // 0x158
    int32_t  mnField15C;                                        // 0x15c
    cStopwatch mStopwatch;                                      // 0x160
    float    mfField170;                                        // 0x170
    float    mfField174;                                        // 0x174
    uint16_t* mpVolumesBegin;                                   // 0x178
    uint16_t* mpVolumesEnd;                                     // 0x17c
    uint16_t* mpVolumesCap;                                     // 0x180
    uint8_t  mPad184[0x04];                                     // 0x184
    uint16_t* mpVolumesBufA;                                    // 0x188
    uint16_t* mpVolumesBufB;                                    // 0x18c
    uint16_t* mpVolumesBufC;                                    // 0x190
    uint8_t  mPad194[0x04];                                     // 0x194
    float*   mpNotePitchesBegin;                                // 0x198
    float*   mpNotePitchesEnd;                                  // 0x19c
    float*   mpNotePitchesCap;                                  // 0x1a0
    uint8_t  mPad1A4[0x08];                                     // 0x1a4
    float    mfNotePitchesBuffer[3];                            // 0x1ac
    void*    mpList1B8Next;                                     // 0x1b8
    void*    mpList1B8Prev;                                     // 0x1bc
    void*    mpList1C4;                                         // 0x1c4
    void*    mpList1C8;                                         // 0x1c8
    void*    mpList1CC;                                         // 0x1cc
    void*    mpList1D0;                                         // 0x1d0
    void*    mpList1D4;                                         // 0x1d4
    uint8_t  mPad1D8[0x08];                                     // 0x1d8
    void*    mpList1E0;                                         // 0x1e0
    void*    mpList1E4;                                         // 0x1e4
    void*    mpList1E8;                                         // 0x1e8
    uint8_t  mPad1EC[0x08];                                     // 0x1ec
    cMessageServer* mpMessageServer;                            // 0x1f4
    void*    mpHandler;                                         // 0x1f8
    uint32_t mnHandlerId;                                       // 0x1fc
    int32_t  mnHandlerKind;                                     // 0x200
    void*    mpHandlerData;                                     // 0x204
    uint8_t  mPad208[0x14];                                     // 0x208
};

// ---------------------------------------------------------------------------
// SP::Audio::cFactoryCityMusic.
// ---------------------------------------------------------------------------
class cWriter {
public:
    virtual void w00(); virtual void w04(); virtual void w08(); virtual void w0c();
    virtual void w10();
    virtual void SetField08(void* pValue);                      // 0x014
    virtual void* GetStream();                                  // 0x018
};

class cFactoryCityMusic {
public:
    virtual void f00(); virtual void f04(); virtual void f08(); virtual void f0c();
    virtual void f10(); virtual void f14(); virtual void f18(); virtual void f1c();
    virtual void f20();
    virtual bool CreateAndWrite(void* pArg1, void* pResource, uint32_t nArg3,
                                uint32_t nArg4);                // 0x024

    bool WriteResource(cResourceCityMusic* pResource, cWriter* pWriter,
                       void* pUnusedA, void* pUnusedB);         // 0x00eb1c10
    bool CreateResource(void* pArg1, void** ppOut, uint32_t nArg3,
                        uint32_t nArg4);                        // 0x00eb1dc0
};

// ---------------------------------------------------------------------------
// 0x00eb0ea0
// ---------------------------------------------------------------------------
// @ 0x00eb0ea0
cPlayerCityMusic::cPlayerCityMusic()
{
    mUndoBuffer.mpBegin = nullptr;
    mUndoBuffer.mpEnd = nullptr;
    mUndoBuffer.mpField08 = nullptr;
    mUndoBuffer.resize(1);

    mUndoBuffer.mpHead = mUndoBuffer.mpBegin;
    mUndoBuffer.mpTail = mUndoBuffer.mpBegin;
    mUndoBuffer.mnWrap = 0;

    mpUndo = &mUndoBuffer;
    mpUndoBegin = mUndoBuffer.mpTail;

    mbPaused = 0;
    mbQuiet = 0;
    mRandom.SetSeed(0xffffffff);
    mnMagic = 0x5293d931;

    mpArray10CBegin = nullptr;
    mpArray10CEnd = nullptr;
    mpArray10CCap = nullptr;
    mpArray118Begin = nullptr;
    mpArray118End = nullptr;

    mpArray128Begin = nullptr;
    mpArray128End = nullptr;
    mpArray128Cap = nullptr;

    mpArray13CBegin = nullptr;
    mpArray13CEnd = nullptr;
    mpArray13CCap = nullptr;

    mfField150 = 0.0f;
    mnField154 = 0;
    mnField158 = 0;
    mnField15C = 0;

    mStopwatch.Init(1000, false);

    mpVolumesBegin = gEmptyString16;
    mpVolumesEnd = gEmptyString16;
    mpVolumesCap = gEmptyString16 + 1;
    mpVolumesBufA = gEmptyString16;
    mpVolumesBufB = gEmptyString16;
    mpVolumesBufC = gEmptyString16 + 1;

    mpNotePitchesBegin = mfNotePitchesBuffer;
    mpNotePitchesEnd = mfNotePitchesBuffer;
    mpNotePitchesCap = mfNotePitchesBuffer + 3;

    float fOne = 1.0f;
    FUN_00eaed40(mfNotePitchesBuffer, 3, &fOne);

    mpList1B8Next = &mpList1B8Next;
    mpList1B8Prev = &mpList1B8Next;
    mpList1C4 = nullptr;
    mpList1C8 = nullptr;
    mpList1CC = nullptr;
    mpList1D0 = nullptr;
    mpList1D4 = nullptr;
    mpList1E0 = nullptr;
    mpList1E4 = nullptr;
    mpList1E8 = nullptr;

    mpMessageServer = nullptr;
    mpHandler = nullptr;
    mnHandlerId = 0;
    mnHandlerKind = 0;
    mpHandlerData = nullptr;

    mpMessageServer = MessageServer();
    mpHandler = this;
    mnHandlerId = 0x149c618;
    mnHandlerKind = 1;
    mpHandlerData = nullptr;

    if (mpMessageServer != nullptr && mpHandler != nullptr)
        mpMessageServer->Register(0xf62def, mpHandler);

    FUN_00eb0460();
}

// ---------------------------------------------------------------------------
// 0x00eb10d0
// ---------------------------------------------------------------------------
// @ 0x00eb10d0
void cPlayerCityMusic::ResetUndoBuffer()
{
    cMusicRing* pRing = &mUndoBuffer;

    if (pRing->GetCount() <= 1)
        pRing->reserve(1);

    pRing->mpHead = pRing->mpBegin;
    pRing->mpTail = pRing->mpBegin;
    pRing->mnWrap = 0;

    pRing->mpTail = pRing->mpTail + 1;
    if (pRing->mpTail == pRing->mpEnd)
        pRing->mpTail = pRing->mpBegin;

    if (pRing->mpTail == pRing->mpHead) {
        pRing->mpHead = pRing->mpHead + 1;
        if (pRing->mpHead == pRing->mpEnd)
            pRing->mpHead = pRing->mpBegin;
    }
    else {
        ++pRing->mnWrap;
    }

    cResourceCityMusic* pTail = pRing->mpTail;
    if (pTail == pRing->mpBegin)
        pTail = pRing->mpEnd;

    SaveData(pTail - 1);

    mpUndo = pRing;
    mpUndoBegin = pRing->mpHead;
}

// ---------------------------------------------------------------------------
// 0x00eb1170
// ---------------------------------------------------------------------------
// @ 0x00eb1170
void cPlayerCityMusic::AddUndoState()
{
    cMusicRing* pRing = &mUndoBuffer;
    cMusicRing* pSaved = mpUndo;

    int32_t nCount = pRing->GetCount();
    cResourceCityMusic* pFirst = mpUndoBegin;
    if (nCount <= 1)
        pFirst = pRing->mpBegin - nCount;

    cResourceCityMusic* pNext = pFirst + 1;
    cRingIter aFirst;
    aFirst.mpRing = pSaved;
    aFirst.mpState = mpUndoBegin;
    cRingIter aLast;
    aLast.mpRing = pRing;
    aLast.mpState = pNext;
    pRing->erase(aFirst, aLast);

    int32_t nSize = pRing->GetCount() - 1;
    if ((uint32_t)nSize <= mConfig.mIcons[2]) {
        cResourceCityMusic* pHead = pRing->mpHead + 1;
        if (pHead == pRing->mpEnd)
            pHead = pRing->mpBegin;
        if (pHead == mpUndoBegin) {
            uint32_t nWanted = (uint32_t)(nSize + 1);
            uint32_t nDoubled = (nSize == 0) ? 1 : (uint32_t)(nSize * 2);
            uint32_t nReserve = (nWanted < nDoubled) ? nWanted : nDoubled;
            pRing->reserve((int32_t)nReserve);
        }
    }

    pRing->mpTail = pRing->mpTail + 1;
    if (pRing->mpTail == pRing->mpEnd)
        pRing->mpTail = pRing->mpBegin;

    if (pRing->mpTail == pRing->mpHead) {
        pRing->mpHead = pRing->mpHead + 1;
        if (pRing->mpHead == pRing->mpEnd)
            pRing->mpHead = pRing->mpBegin;
    }
    else {
        ++pRing->mnWrap;
    }

    cResourceCityMusic* pTail = pRing->mpTail;
    if (pTail == pRing->mpBegin)
        pTail = pRing->mpEnd;

    SaveData(pTail - 1);

    cResourceCityMusic* pSavedTail = pRing->mpTail;
    if (pSavedTail == pRing->mpBegin)
        pSavedTail = pRing->mpEnd;

    mpUndo = pRing;
    mpUndoBegin = pSavedTail - 1;
}

// ---------------------------------------------------------------------------
// 0x00eb12a0
// ---------------------------------------------------------------------------
// @ 0x00eb12a0
bool cPlayerCityMusic::HandleMessage(int32_t nType, cEapdMessage* pMessage)
{
    switch (nType) {
    case 0x69aa284:
        Reset(true);
        return true;

    case 0x539a4cf:
        MessageServer()->Send(0x69aa284, 0, 0, 0);
        return true;

    case 0xf62def:
        if (!mConfig.Reload(pMessage->mnField08, pMessage->mnField10, pMessage->mnField18))
            return true;
        ResetUndoBuffer();
        FUN_00eb0460();
        return true;

    case 0x41638ca: {
        uint32_t nSubType = pMessage->GetType();
        if (nSubType == 0x620bba33) {
            float fValue;
            pMessage->GetNextFloat(&fValue);
            mnField15C = (int32_t)fValue;
            mfField174 = GetCyclesToUnitsCoefficient(5) * fValue * 0.0010416667f;
        }
        else if (nSubType == 0xdec4e95f) {
            float fValue;
            pMessage->GetNextFloat(&fValue);
            mnField158 = (int32_t)fValue;
            pMessage->MarkProcessed();
            return true;
        }
        else if (nSubType != 0xe66bc36a) {
            pMessage->MarkProcessed();
            return false;
        }

        mStopwatch.Restart();
        pMessage->MarkProcessed();
        return true;
    }

    default:
        break;
    }

    return false;
}

// ---------------------------------------------------------------------------
// 0x00eb14c0
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00eb19e0
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x00eb1c10
// ---------------------------------------------------------------------------
// @ 0x00eb1c10
bool cFactoryCityMusic::WriteResource(cResourceCityMusic* pResource, cWriter* pWriter,
                                      void* pUnusedA, void* pUnusedB)
{
    pWriter->SetField08(&pResource->mnField08);

    cResourceCityMusic* pData;
    if (pResource != nullptr)
        pData = (cResourceCityMusic*)pResource->GetProperty(0x04f67fb5);
    else
        pData = nullptr;

    bool bOk = (pData != nullptr);
    if (bOk) {
        void* pStream = pWriter->GetStream();

        uint32_t nMagic = 0x20434d50;
        bOk &= WriteUint32(pStream, &nMagic, 1, 0);
        uint32_t nVersion = 1;
        bOk &= WriteUint32(pStream, &nVersion, 1, 0);
        bOk &= WriteUint32(pStream, &pData->mnField14, 1, 0);
        bOk &= WriteUint32(pStream, &pData->mnField18, 1, 0);

        uint32_t nCount = (uint32_t)(pData->mpData1CEnd - pData->mpData1CBegin);
        bOk &= WriteUint32(pStream, &nCount, 1, 0);
        bOk &= WriteUint32(pStream, pData->mpData1CBegin, nCount, 0);
        bOk &= WriteUint32(pStream, pData->mpData30Begin, nCount, 0);

        nCount = (uint32_t)(pData->mpData44End - pData->mpData44Begin);
        bOk &= WriteUint32(pStream, &nCount, 1, 0);
        bOk &= WriteUint32(pStream, pData->mpData44Begin, nCount, 0);

        nCount = (uint32_t)(pData->mpData58End - pData->mpData58Begin);
        bOk &= WriteUint32(pStream, &nCount, 1, 0);
        bOk &= WriteUint32(pStream, pData->mpData58Begin, nCount, 0);
    }

    return bOk;
}

// ---------------------------------------------------------------------------
// 0x00eb1d70
// ---------------------------------------------------------------------------
// @ 0x00eb1d70
cResourceCityMusic::cResourceCityMusic()
{
    mnField14 = 0;
    mnField18 = 0;
    mpData1CBegin = nullptr;
    mpData1CEnd = nullptr;
    mpData1CCap = nullptr;
    mpData30Begin = nullptr;
    mpData30End = nullptr;
    mpData30Cap = nullptr;
    mpData44Begin = nullptr;
    mpData44End = nullptr;
    mpData44Cap = nullptr;
    mpData58Begin = nullptr;
    mpData58End = nullptr;
    mpData58Cap = nullptr;
}

// ---------------------------------------------------------------------------
// 0x00eb1dc0
// ---------------------------------------------------------------------------
// @ 0x00eb1dc0
bool cFactoryCityMusic::CreateResource(void* pArg1, void** ppOut, uint32_t nArg3,
                                       uint32_t nArg4)
{
    uint8_t* pMemory = (uint8_t*)operator_new(0x6c, "Audio", 0, 0, 0, 0);
    cResourceCityMusic* pResource = new (pMemory) cResourceCityMusic();

    if (pResource != nullptr)
        pResource->p00();

    if (pArg1 != nullptr) {
        if (!CreateAndWrite(pArg1, pResource, nArg3, nArg4)) {
            if (pResource != nullptr)
                pResource->p04();
            return false;
        }
    }

    *ppOut = pResource;
    return true;
}
