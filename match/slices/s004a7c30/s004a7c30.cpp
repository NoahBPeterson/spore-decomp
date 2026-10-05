// Slice s004a7c30 — Spore editor symmetry helpers (module is /Od /Ob1).
#include "types.h"

// ---- minimal stub types (offsets from retail disassembly) ----

struct Key {
    uint32_t mInstance;   // +0x0
    uint32_t mType;       // +0x4
    uint32_t mGroup;      // +0x8
};

// Receiver of 0x438f20: an object whose +0xc points at the property list.
struct ResKeySource {
    char pad0[0xc];
    Key GetKey(int mode, int arg);
};

// ---- forward decls ----
struct cSPEditorBlock;
struct cSPEditorModel;

// eastl::vector<unsigned int, sp_vector_allocator> (layout only)
struct UIntVector {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    void**     mpCapacity;
    void push_back(const uint32_t& value);
};

struct cSPEditorModel {
    char pad0[0x18];
    bool FUN_004adc40();             // +0x0
    int  GetBlockCount();            // 0x4accf0
    cSPEditorBlock* GetBlock(int i); // 0x4accb0
};

struct cSPEditorBlock {
    char pad0[0x28];
    cSPEditorModel* mEditorModel;    // +0x28
    char pad1[0x33c - 0x2c];
    void* mSocketConnector;          // +0x33c
    char pad2[0x3e0 - 0x340];
    void* mField3e0;                 // +0x3e0
    char pad3[0xdc8 - 0x3e4];
    uint32_t mFlags[4];              // +0xdc8

    bool HasAnyBlockFlag();          // 0x435d40
    bool IsFlagSet(unsigned int index)
    {
        bool result;
        uint32_t flag;
        if (index < 0x3c) { flag = mFlags[index / 32]; result = (flag & (1u << (index % 32))) != 0; }
        else { result = false; }
        return result;
    }
    cSPEditorBlock* GetParent() { return (cSPEditorBlock*)mSocketConnector; }
};

// @ 0x004a7c30
bool SameKey(ResKeySource* a, ResKeySource* b)
{
    Key first = a->GetKey(-1, 0);
    Key src = b->GetKey(-1, 0);
    return first.mInstance == src.mInstance
        && first.mType == src.mType
        && first.mGroup == src.mGroup;
}

// @ 0x004a7c90
void GatherBlocks(cSPEditorBlock* param_1, UIntVector* param_2)
{
    if (param_1 == 0) return;
    cSPEditorModel* model = param_1->mEditorModel;
    if (model == 0) return;
    int i = 0;
    int count = model->GetBlockCount();
    for (; i < count; ++i) {
        cSPEditorBlock* blk = model->GetBlock(i);
        if (blk == 0 || blk == param_1) continue;
        if (!SameKey((ResKeySource*)blk, (ResKeySource*)param_1)) continue;
        param_2->push_back((uint32_t)blk);
        if (!model->FUN_004adc40()) continue;
        uint32_t v = (uint32_t)blk->mField3e0;
        if (v == 0) continue;
        uint32_t* it = param_2->mpBegin;
        uint32_t* end = param_2->mpEnd;
        while (it != end && *it != v) ++it;
        if (it == end) {
            param_2->push_back(v);
        }
    }
}

// @ 0x004a7dd0
bool EntHasFlag(cSPEditorBlock* e)
{
    if (e != 0) { if (e->IsFlagSet(8)) { return true; } else { return EntHasFlag(e->GetParent()); } }
    else { return false; }
}

extern bool FUN_004986d0(cSPEditorBlock* b);

// @ 0x004a7e60
bool BlockBlocked(cSPEditorBlock* b)
{
    if (b != 0) {
        bool r = b->HasAnyBlockFlag();
        if (r == false) r = FUN_004986d0(b);
        return r;
    }
    else {
        return false;
    }
}

// @ 0x004a7ea0
bool AdjacentDir(int a, int b, unsigned char flipped)
{
    if (flipped != 0) return a != b;
    bool result = false;
    if ((a == -1) && (b == 0)) { }
    else if ((a == -1) && (b == 1)) result = true;
    else if ((a == 0) && (b == 1)) result = true;
    else if ((a == 0) && (b == -1)) { }
    else if ((a == 1) && (b == 0)) result = true;
    else if ((a == 1) && (b == -1)) result = true;
    return result;
}

struct RefObj {
    char pad0[0x3e0];
    void SetRef(int v);              // 0x438cc0
};

// @ 0x004a8860
void ReleaseRefs(RefObj* b, UIntVector* list)
{
    if (b != 0) {
        b->SetRef(0);
        if (list != 0) {
            int n = list->mpEnd - list->mpBegin;
            for (int i = 0; i < n; ++i) {
                uint32_t& elem = list->mpBegin[i];
                RefObj* ptr = (RefObj*)elem;
                ptr->SetRef(0);
            }
        }
    }
}

// @ 0x004a88d0
extern int GetRecorderState();
extern void KillSetiEffects(int a, int b);
void KillSeti(int arg)
{
    int a;
    int b;
    KillSetiEffects(arg, GetRecorderState());
}

// @ 0x004a88f0
struct Vec3 { float x, y, z; };
struct Mat3 { float m[9]; };
struct XformMsg {
    uint16_t mFlags;     // +0x0
    uint16_t mCount;     // +0x2
    Vec3     mPos;       // +0x4
    uint32_t mUnk10;     // +0x10
    Mat3     mMat;       // +0x14
    char pad[0x38 - 0x38];
    XformMsg();
};
struct EffectsManager {
    void* vtable;
};
extern EffectsManager* GetEffectsManager();

// virtual-slot helper
static void* VSlot(void* obj, int off) { return *(void**)(*(char**)obj + off); }

bool PostXformEffect(unsigned int id, char* src, void** out)
{
    void* handle = 0;
    EffectsManager* mgr = GetEffectsManager();
    bool ok = ((bool(__thiscall*)(void*, unsigned int, int, void**))VSlot(mgr, 0x2c))(mgr, id, 0, &handle);
    if (!ok) return false;
    XformMsg msg;
    if (src != 0) {
        msg.mPos = *(Vec3*)(src + 0x48);
        for (int i = 0; i < 9; ++i)
            msg.mMat.m[i] = ((float*)(src + 0x60))[i];
        msg.mFlags |= 4;
        msg.mCount = (uint16_t)(msg.mCount + 1);
        msg.mFlags |= 2;
        msg.mCount = (uint16_t)(msg.mCount + 1);
        ((void(__thiscall*)(void*, void*))VSlot(handle, 0x18))(handle, &msg);
    }
    ((void(__thiscall*)(void*, int))VSlot(handle, 8))(handle, 0);
    if (out != 0) *out = handle;
    else ((void(__thiscall*)(void*))VSlot(handle, 4))(handle);
    return true;
}

// @ 0x004a7f30
// Incomplete: the body is a large 2347-byte editor routine; only the entry
// guards are represented. Listed in partial.txt.
void SetSymmetricBlocksUIState(cSPEditorBlock* param_1, unsigned int param_2, unsigned char param_3)
{
    (void)param_1;
    (void)param_2;
    (void)param_3;
}

