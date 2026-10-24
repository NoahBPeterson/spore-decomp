// s00b23e60 - noun-type registration (gold6 worker 36)
typedef unsigned int uint32_t;

// ---------------------------------------------------------------------------
// Foreign helpers
// ---------------------------------------------------------------------------
void* operator_new(uint32_t nSize, const char* pFile, uint32_t nA,
                   uint32_t nB, const char* pAllocator, uint32_t nLine);  // 0x00f473a0
void operator_delete(void* pMemory);                                      // 0x00f47380
void* memcpy(void* pDst, const void* pSrc, uint32_t nSize);               // 0x011e0744

extern char gEmptyString8[1];                                             // 0x01667bac
extern const char gAllocatorName[];                                       // 0x013ebb38
extern const char gBuildFile[];                                           // 0x013f09b4

// ---------------------------------------------------------------------------
// eastl::basic_string<char> with the 1-byte small-string optimisation:
// an empty string points at the shared terminator, otherwise the buffer is
// heap allocated with room for the terminator.
// ---------------------------------------------------------------------------
class cEAString8 {
public:
    cEAString8() { mpBegin = gEmptyString8; mpEnd = gEmptyString8 + 1; }
    cEAString8(const char* pStr);
    cEAString8(const cEAString8& src);
    ~cEAString8()
    {
        if (mpEnd - mpBegin > 1 && mpBegin != 0)
            operator_delete((void*)mpBegin);
    }

    const char* mpBegin;                                        // 0x00
    const char* mpEnd;                                          // 0x04
};

cEAString8::cEAString8(const char* pStr)
{
    uint32_t nLen = 0;
    while (pStr[nLen] != '\0')
        ++nLen;
    if (nLen + 1 > 1) {
        char* pBuffer = (char*)operator_new(nLen + 1, "Simulator", 0, 0,
                                           gAllocatorName, 0xd1);
        mpBegin = pBuffer;
        mpEnd = pBuffer + nLen + 1;
    } else {
        mpBegin = gEmptyString8;
        mpEnd = gEmptyString8 + 1;
    }
    memcpy((void*)mpBegin, pStr, nLen);
    *(char*)(mpEnd - 1) = '\0';
}

cEAString8::cEAString8(const cEAString8& src)
{
    uint32_t nLen = (uint32_t)(src.mpEnd - src.mpBegin) - 1;
    if (nLen + 1 > 1) {
        char* pBuffer = (char*)operator_new(nLen + 1, "Simulator", 0, 0,
                                           gAllocatorName, 0xd1);
        mpBegin = pBuffer;
        mpEnd = pBuffer + nLen + 1;
    } else {
        mpBegin = gEmptyString8;
        mpEnd = gEmptyString8 + 1;
    }
    memcpy((void*)mpBegin, src.mpBegin, nLen);
    *(char*)(mpEnd - 1) = '\0';
}

// ---------------------------------------------------------------------------
// Noun-type registry
// ---------------------------------------------------------------------------
class cNounTypeRegistry {
public:
    void AddNounType(const cEAString8* pName, uint32_t nFlags,
                     uint32_t nUnk);                             // 0x00b1aba0
};

class cNounTypeTable {
public:
    uint32_t FindNounType(const cEAString8* pName);               // 0x00b209f0
    void SetNounTypeName(const cEAString8* pName, uint32_t nFound,
                         uint32_t nFlags);                        // 0x00b23020
};

extern cNounTypeRegistry gNounTypeRegistry;                       // 0x01568514
extern cNounTypeTable gNounTypeTable;                             // 0x0156851c

// ---------------------------------------------------------------------------
// 0x00b23e60  RegisterNounType
// ---------------------------------------------------------------------------
// @ 0x00b23e60
void RegisterNounType(uint32_t nId, uint32_t nFlags, const char* pName)
{
    cEAString8 name(pName);
    cEAString8 copy(name);
    gNounTypeRegistry.AddNounType(&copy, nId, nFlags);

    cEAString8 name2(pName);
    cEAString8 copy2(name2);
    gNounTypeRegistry.AddNounType(&copy2, nFlags, nId);

    cEAString8 name3(pName);
    uint32_t nFound = gNounTypeTable.FindNounType(&name3);
    gNounTypeTable.SetNounTypeName(&name3, nFound, nId);

    cEAString8 name4(pName);
    uint32_t nFound2 = gNounTypeTable.FindNounType(&name4);
    gNounTypeTable.SetNounTypeName(&name4, nFound2, nFlags);
}

// ---------------------------------------------------------------------------
// 0x00b24260  cCommunityEditor::RemoveObjectFromCommunity
// ---------------------------------------------------------------------------
// Only the entry block of the original 1236-byte routine is decoded: the noun
// manager is reached through this - 4, its vtable is 0x013eb844 and 0x00b206d0
// starts the removal pass over the community's member list.
class cGameNounManager {
public:
    void BeginRemovalPass();                                    // 0x00b206d0
};

// @ 0x00b24260
void RemoveObjectFromCommunity(uint32_t nEditorObject)
{
    cGameNounManager* pNounManager =
        (cGameNounManager*)(nEditorObject - sizeof(uint32_t));
    pNounManager->BeginRemovalPass();
}
