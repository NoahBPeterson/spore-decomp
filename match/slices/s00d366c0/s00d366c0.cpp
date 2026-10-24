// s00d366c0 - creature mode input strategy setup (gold6 worker 36)
typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

// ---------------------------------------------------------------------------
// Cursor table
// ---------------------------------------------------------------------------
class CursorTable {
public:
    void* AddCursor(int nCursorId, const wchar_t* pCursorName, char cAlpha,
                    int nArg3, int nArg4);                          // 0x00802050
};

CursorTable* GetCursorTable();                                      // 0x0067cab0

// ---------------------------------------------------------------------------
// Messaging
// ---------------------------------------------------------------------------
class cMessageServer {
public:
    void* mpVtable;                                                 // 0x00
};

class cMessageHandler {
public:
    uint32_t mUnk000[0x10];                                         // 0x00
};

namespace EA { namespace Messaging {
    cMessageServer* GetServer();                                    // 0x00883860
} }

// ---------------------------------------------------------------------------
// Property list
// ---------------------------------------------------------------------------
class cProperty {
public:
    uint32_t mUnk000[4];                                            // 0x00
    uint16_t mUnk010;                                               // 0x10
    uint16_t mnType;                                                // 0x12

    char* GetBool();                                                // 0x0041e920
};

class cDirectPropertyList {
public:
    void* mpVtable;                                                 // 0x00
};

extern cDirectPropertyList* gAppProperties;                         // 0x015fd918
extern uint32_t gMessageIds[0x1b];                                  // 0x0147a610

// ---------------------------------------------------------------------------
// cCreatureModeInputStrategy: primary base 0x00..0x47, message handler at 0x48
// ---------------------------------------------------------------------------
class cStrategyBase {
public:
    uint32_t mUnk000[0x12];                                         // 0x00
};

class cCreatureModeInputStrategy : public cStrategyBase,
                                   public cMessageHandler {
public:
    cMessageServer* mpMessageServer;                                // 0x088
    cMessageHandler* mpMessageHandler;                              // 0x08c
    uint32_t* mpMessageTable;                                       // 0x090
    uint32_t mnMessageCount;                                        // 0x094
    uint32_t mnUnk098;                                              // 0x098
    uint32_t mUnk09c[0x1a];                                         // 0x09c
    char mbUseKeyArray;                                             // 0x104
    char mbUnk105;                                                  // 0x105

public:
    void InitCursors();
    void SetInputPriorityStrategy(int nPriority);                   // 0x00d33ec0
    void InitSubstate();                                            // 0x00d35030
};

// ---------------------------------------------------------------------------
// @ 0x00d366c0  cCreatureModeInputStrategy::InitCursors
// ---------------------------------------------------------------------------
void cCreatureModeInputStrategy::InitCursors()
{
    CursorTable* pCursors = GetCursorTable();
    pCursors->AddCursor(0x514ab7b0, L"cursor-target", 1, 0, 0);
    pCursors->AddCursor(0x314ab7b1, L"cursor-mate", 1, 0, 0);
    pCursors->AddCursor(0xf14ab7b3, L"cursor-heal", 1, 0, 0);
    pCursors->AddCursor(0xb14ab7b6, L"cursor-eat-fruit", 1, 0, 0);
    pCursors->AddCursor(0x514ab7b7, L"cursor-eat-carcass", 1, 0, 0);
    pCursors->AddCursor(0xb14ab7b9, L"cursor_atk", 1, 0, 0);
    pCursors->AddCursor(0x114ab7ba, L"cursor-evolve", 1, 0, 0);
    pCursors->AddCursor(0x514abe0b, L"cursor-validate", 1, 0, 0);
    pCursors->AddCursor(0x71664d85, L"cursor_social", 1, 0, 0);
    pCursors->AddCursor(0x755c4eb5, L"cursor_friend", 1, 0, 0);
    pCursors->AddCursor(0xf4f6c345, L"cursor_socialNo", 1, 0, 0);
    pCursors->AddCursor(0x03b360d8, L"cursor-crg-addposse", 1, 0, 0);
    pCursors->AddCursor(0x03b360dc, L"cursor-crg-pickup", 1, 0, 0);
    pCursors->AddCursor(0x03b360df, L"cursor-crg-putdown", 1, 0, 0);
    pCursors->AddCursor(0x7542cdb5, L"cur_ClaimNest", 1, 0, 0);
    pCursors->AddCursor(0x03b360e2, L"cursor-crg-give", 1, 0, 0);
    pCursors->AddCursor(0x03b360e4, L"cursor-crg-throw", 1, 0, 0);
    pCursors->AddCursor(0xf36a0c84, L"cursor-target-creature", 1, 0, 0);
    pCursors->AddCursor(0x342d221f, L"cursor_skeleton2", 1, 0, 0);

    cMessageServer* pServer = EA::Messaging::GetServer();
    cMessageHandler* pHandler = this;
    mpMessageServer = pServer;
    mpMessageHandler = pHandler;
    mpMessageTable = gMessageIds;
    mnMessageCount = 0x1b;
    mnUnk098 = 0;
    if (pServer != 0 && pHandler != 0) {
        for (uint32_t nOffset = 0; nOffset < 0x6c; nOffset += 4)
            ((void (__thiscall*)(cMessageServer*, cMessageHandler*, uint32_t))
                 ((void**)pServer->mpVtable)[0x24 / 4])(
                pServer, pHandler,
                *(uint32_t*)((char*)gMessageIds + nOffset));
    }

    SetInputPriorityStrategy(0);
    InitSubstate();

    cDirectPropertyList* pProperties = gAppProperties;
    cProperty* pProperty;
    if (pProperties != 0 &&
        ((bool (__thiscall*)(cDirectPropertyList*, int, cProperty**))
             ((void**)pProperties->mpVtable)[0x24 / 4])(
            pProperties, 0x064a44a8, &pProperty) &&
        pProperty->mnType == 1) {
        mbUseKeyArray = *pProperty->GetBool();
    }
    mbUnk105 = false;
}
