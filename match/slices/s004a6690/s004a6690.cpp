// Slice s004a6690: SP editor block-validity helpers.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct cSPEditorBlock {
    virtual void _v0();
    bool FUN_43fc20(int a, int b);               // @ 0x43fc20
    void SetValid(bool v);                       // @ 0x43f6b0
};
struct cSPEditorModel {
    cSPEditorBlock* GetBlock(int i);             // @ 0x4accb0
    int GetBlockCount();                         // @ 0x4accf0
    bool FUN_4adc40();                           // @ 0x4adc40
    void FUN_4adc20(int v);                      // @ 0x4adc20
};

// @ 0x4a6ca0
void FUN_4a6ca0(cSPEditorModel* model, int value)
{
    bool saved = model->FUN_4adc40();
    model->FUN_4adc20(0);
    int t14 = 0;
    int tmp = model->GetBlockCount();
    for (; t14 < tmp; t14++) {
        cSPEditorBlock* block = model->GetBlock(t14);
        block->SetValid(block->FUN_43fc20(0, value));
    }
    model->FUN_4adc20(saved);
}

// @ 0x4a6690
void FUN_4a6690(cSPEditorBlock* block) { (void)block; }

// @ 0x4a6d20
void FUN_4a6d20(cSPEditorBlock* block) { (void)block; }
