// slice s00585d40 -- SP::cAppModeEditorBase: save-in-progress state machine, undo-list init and a
// few small editor helpers.  Retail class layout differs slightly from the 2008 PDB; offsets are
// taken from the disassembly.  Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast.
#include "types.h"

struct Vector3 { float x, y, z; };

namespace SP {

class cSPEditorUI {
public:
    void EnableUndoButton(bool b);
    void EnableRedoButton(bool b);
    void UpdateUIBasedOnModelSaveability();
};

// A vector-like container as used by the editor undo lists (begin/end at +0/+4, 0x14 bytes strided).
struct UndoVector {
    void* mpBegin;      // +0x00
    void* mpEnd;        // +0x04
    void* mpCapacity;   // +0x08
    uint32_t mPad0c;    // +0x0c
    uint32_t mPad10;    // +0x10
    void erase(void* first, void* last);
};

// Only the fields touched by this slice.
class cAppModeEditorBase {
public:
    char pad0[0x78];
    cSPEditorUI* mDevUI;                 // +0x78
    char pad7c[0x160 - 0x7c];
    UndoVector mUndoLocalStateList;      // +0x160
    UndoVector mUndoList;                // +0x174
    int mUndosLeft;                      // +0x188
    char pad18c[0x4d8 - 0x18c];

    void InitializeUndoList();                              // 0x00586690
    __declspec(noinline) void FUN_00586410(char a, void* b); // 0x00586410
    void FUN_00586700();                                    // 0x00586700
    uint8_t FUN_00586800(void* a);                          // 0x00586800
    void FUN_00586960();                                    // 0x00586960
    void ContinueSaveInProgress();                          // 0x00585d40
};

}  // namespace SP

using namespace SP;

// @ 0x00586690
void cAppModeEditorBase::InitializeUndoList()
{
    mUndosLeft = 0;
    UndoVector& undo = mUndoList;
    undo.erase(undo.mpBegin, undo.mpEnd);
    mUndoLocalStateList.erase(mUndoLocalStateList.mpBegin, mUndoLocalStateList.mpEnd);
    FUN_00586410(0, 0);
    mDevUI->EnableUndoButton(0);
    mDevUI->EnableRedoButton(0);
    *(bool*)((char*)this + 0x4b3) = 0;
    *(bool*)((char*)this + 0x4b4) = 0;
    mDevUI->UpdateUIBasedOnModelSaveability();
}

// @ 0x00586410
// PARTIAL: pushes a new editor resource onto the undo list.  Only the entry sequence is modelled;
// the EASTL vector<bool> / refcount traffic is stubbed.
void cAppModeEditorBase::FUN_00586410(char a, void* b)
{
    (void)a;
    (void)b;
    mUndoLocalStateList.erase(mUndoLocalStateList.mpBegin, mUndoLocalStateList.mpEnd);
    mUndoList.erase(mUndoList.mpBegin, mUndoList.mpEnd);
}

// @ 0x00586700
// PARTIAL: resets per-slot bit vectors to 0x23 bytes each.
void cAppModeEditorBase::FUN_00586700()
{
    uint8_t* bitsA = (uint8_t*)this + 0x4d8;
    for (int i = 0; i < 0x23; ++i)
        bitsA[i] = 0;
    for (int s = 0; s < 6; ++s) {
        *(int*)((char*)this + 0x4f0 + s * 4) = 0;
        uint8_t* slot = (uint8_t*)this + 0x50c + s * 0x14;
        for (int i = 0; i < 0x23; ++i)
            slot[i] = 0;
    }
}

// @ 0x00586800
// PARTIAL: serialises the editor state through cVarListSerializer and normalises the bit vectors.
uint8_t cAppModeEditorBase::FUN_00586800(void* a)
{
    (void)a;
    for (int s = 0; s < 6; ++s) {
        *(int*)((char*)this + 0x4f0 + s * 4) = 0;
        uint8_t* slot = (uint8_t*)this + 0x50c + s * 0x14;
        for (int i = 0; i < 0x23; ++i)
            slot[i] = 0;
    }
    return 0;
}

// @ 0x00586960
// PARTIAL: resets the current selection/block state and refreshes the editor.
void cAppModeEditorBase::FUN_00586960()
{
    *(bool*)((char*)this + 0x472) = 0;
    *(void**)((char*)this + 0x48c) = 0;
    *(void**)((char*)this + 0x490) = 0;
    FUN_00586410(1, 0);
}

// @ 0x00585d40
// PARTIAL: multi-stage "save in progress" state machine.  Skeleton preserving the state dispatch;
// individual stage bodies are stubbed.
void cAppModeEditorBase::ContinueSaveInProgress()
{
    int* state = (int*)((char*)this + 0x38c);
    if (*state == 1) {
        *state = 2;
    }
    if (*state == 2) {
        *state = 3;
    }
    if (*state == 3) {
        *state = 4;
    }
    if (*state == 4) {
        *state = 5;
    }
    if (*state == 5) {
        return;
    }
}
