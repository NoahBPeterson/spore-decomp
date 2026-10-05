// Slice s004a0b70: SP editor model-block helpers.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct cSPEditorBlock {
    virtual void _v0();
    void FUN_451360();                           // @ 0x451360
};
struct cSPEditorModel {
    cSPEditorBlock* GetBlock(int i);             // @ 0x4accb0
    int GetBlockCount();                         // @ 0x4accf0
};

// @ 0x4a1020
void FUN_4a1020(cSPEditorModel* model)
{
    int tmp = 0;
    int t14 = model->GetBlockCount();
    for (; tmp < t14; tmp++) {
        model->GetBlock(tmp)->FUN_451360();
    }
}

// @ 0x4a0b70
cSPEditorBlock* FUN_4a0b70() { return 0; }

// @ 0x4a0bf0
void FUN_4a0bf0(cSPEditorBlock* block) { (void)block; }

// @ 0x4a1070
void FUN_4a1070(cSPEditorBlock* block) { (void)block; }

// @ 0x4a18b0
void FUN_4a18b0(cSPEditorBlock* block) { (void)block; }
