// Slice s004a3dc0: SP editor pick/block lookup helpers.
// Module flags: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "types.h"

template<int N> inline void ScratchSlots() { uint32_t s[N]; }

struct cSPEditorBlock {
    virtual void _v0();
    char pad0[0x18c - 4];
    int mField18c;                               // +0x18c
};
struct cSPEditorModel {
    cSPEditorBlock* GetBlock(int i);             // @ 0x4accb0
    int GetBlockCount();                         // @ 0x4accf0
};

// @ 0x4a4cf0
cSPEditorBlock* FUN_4a4cf0(cSPEditorModel* model, int id)
{
    if (model && (unsigned)model->GetBlockCount() > 0) {
        int tmp = 0;
        int t14 = model->GetBlockCount();
        cSPEditorBlock* block;
        for (; tmp < t14; tmp++) {
            block = model->GetBlock(tmp);
            int field = block->mField18c;
            if (field == id) return block;
        }
    }
    return 0;
}

struct cSPEditorPickInfo {
    int m0;
    int m4;
    int m8;
    int mC;
    int m10;
    bool m14;
    bool m15;
    cSPEditorPickInfo();                         // @ 0x4a4c70
};

// @ 0x4a4c70
cSPEditorPickInfo::cSPEditorPickInfo()
{
    m0 = 0;
    m4 = 0;
    m8 = 0;
    mC = 0;
    m10 = 0;
    m14 = 0;
    m15 = 0;
}

// @ 0x4a3dc0
void FUN_4a3dc0(cSPEditorBlock* block) { (void)block; }

// @ 0x4a4840
void PickBlocks(cSPEditorBlock* block) { (void)block; }
