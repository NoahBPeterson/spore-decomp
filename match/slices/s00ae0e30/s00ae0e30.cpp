// Slice s00ae0e30: the single function in this slice is
//   0x00AE0E30  FUN_00ae0e30   (8164 bytes, __thiscall, ret 8)
//
// It is a giant message-dispatch handler: the first stack argument is a 32-bit
// message id (an FNV hash of a message name) and the second is a pointer to a
// boxed message. The compiler turned `switch (messageID)` over ~40 cases into a
// nested binary-search compare tree (cmp eax, imm; ja/je ...), and several case
// bodies contain inner `switch (msg->field)` jump tables. The handler touches
// SP::MessageServer, SP::EffectsManager, SP::NounManager, SP::PlanetModel,
// cSPUISpace, cSPEditorVerbIconTray, cSPCreatureBase and eastl hashtables/rbtrees.
//
// The body is far too large (8164 bytes, ~2250 instructions, ~1600 decompiled
// lines) to reconstruct exhaustively within the slice budget without it being an
// assembly transcription. This file keeps the exact signature and a faithful
// skeleton of the outer dispatch; the uncompiled remainder is recorded in
// partial.txt as incomplete.
//
// Calling convention: ECX = this, two stack args consumed by `ret 8`.
#include "types.h"

namespace SP {

// The message payload is a tagged box: the first dword is an instance/type id and
// the following dwords carry value copies. Only the offsets the handler reads are
// listed; everything else is opaque.
struct Msg {
    uint32_t pad00[2];
    uint32_t value8;    // +0x08  first payload dword (usually an id/pointer)
    uint32_t valueC;    // +0x0c
    uint32_t value10;   // +0x10
    uint32_t value14;   // +0x14
    uint32_t value18;   // +0x18
    uint32_t value1c;   // +0x1c
    uint32_t value20;   // +0x20
    uint32_t value24;   // +0x24
    uint32_t value28;   // +0x28
};

class cSPGameModeBase {
public:
    bool HandleMessage(uint32_t messageID, Msg* pMsg);

    char pad04[0x2a - 0x04];
    uint8_t mb2a;       // +0x2a
    uint8_t mb2b;       // +0x2b
    uint32_t m2c;       // +0x2c
    char pad30[4];
    uint32_t m34;       // +0x34
    uint8_t mb38;       // +0x38
    char pad39;
    uint8_t mb3a;       // +0x3a
    uint8_t mb3b;       // +0x3b
    uint8_t mb3c;       // +0x3c
    uint8_t mb3d;       // +0x3d
    char pad3e[0x44 - 0x3e];
    void* mp44;         // +0x44  owned sub-object (UI/verb tray owner)
    char pad48[0x15c - 0x48];
    uint8_t mb15c;      // +0x15c
    uint8_t mb15d;      // +0x15d
    uint8_t mb15e;      // +0x15e
};

}  // namespace SP

// @ 0x00AE0E30
bool SP::cSPGameModeBase::HandleMessage(uint32_t messageID, Msg* pMsg)
{
    // The outer dispatch is a compiler-generated binary search over messageID.
    // Reconstructed only in outline; see partial.txt.
    switch (messageID) {
    case 0x473eb91:   // payload -> eastl hashtable find + audio system
    case 0x445f729:
    case 0x4448b81:
    case 0x4448b7a:
    case 0x4448b85:
    case 0x440377c:
    case 0x445f6e8:
    case 0x4448cb4:
    case 0x2319915:
    case 0x2800a7f:
    case 0xe11331:
    case 0x476ad30:
    case 0x4740862:
    case 0x47691c0:
    case 0x47b92d6:
    case 0x47feba4:
    case 0x490cec8:
    case 0x493440d:
    case 0x4cea5ff:
    case 0x4dd9f67:
    case 0x5b70e8b:
    case 0x5caabce:
    case 0x5d6b782:
    case 0x5dbc9c4:
    case 0x5dbc9c8:
    case 0x6133baa:
    case 0x636bf2d:
    case 0x67a195b:
    case 0x750d599:
    case 0x798207d:
    case 0x7982226:
        (void)pMsg;
        return true;
    default:
        return false;
    }
}
