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

struct BlockRef {
    cSPEditorBlock* mpObject;
    cSPEditorBlock* get() { return mpObject; }
    cSPEditorBlock* operator->() { return mpObject; }
};
struct Alloc { Alloc() {} };                       // empty tag (temporary)
struct SpAlloc { uint32_t mName; void Init(const Alloc&); };   // 0x429360 (ret 4)
template<int N> inline void ScratchSlots() { uint32_t s[N]; }
struct BlockVec {
    BlockRef* mpBegin;
    BlockRef* mpEnd;
    BlockRef* mpCapacity;
    SpAlloc mAlloc;
    uint32_t mPad;
    BlockVec(const Alloc&);          // 0x540470
    BlockVec(const Alloc& a, int) { mpBegin = 0; mpEnd = 0; mpCapacity = 0; mAlloc.Init(a); }
    ~BlockVec();                     // 0x453eb0
    BlockRef& operator[](int i) { return mpBegin[i]; }
    int size() { return mpEnd - mpBegin; }
    void* erase(BlockRef* first, BlockRef* last);   // 0x454280
};

struct cSPEditorBlock {
    char pad0[0xc];
    void* mPropList;                 // +0xc
    char pad0b[0x28 - 0x10];
    cSPEditorModel* mEditorModel;    // +0x28
    char pad1[0x33c - 0x2c];
    cSPEditorBlock* mSocketConnector; // +0x33c
    cSPEditorBlock* GetParent2() { cSPEditorBlock* r = mSocketConnector; return r; }
    BlockVec mChildren;              // +0x340
    char pad2[0x3e0 - 0x354];
    cSPEditorBlock* mLinked;         // +0x3e0
    char pad3[0xdc8 - 0x3e4];
    uint32_t mFlags[4];              // +0xdc8

    bool HasAnyBlockFlag();          // 0x435d40
    int  CalculateSymmetrySign();    // 0x44f240
    int  F44c050();
    bool F44c030();
    void F44ba20(int, int);
    void F44bcf0(int, int);
    cSPEditorBlock* GetLinked() { return mLinked; }
    cSPEditorModel* GetModel() { return mEditorModel; }
    void* GetPropList() { void* r = mPropList; return r; }
    bool IsFlagSet(unsigned int index)
    {
        bool result;
        uint32_t flag;
        if (index < 0x3c) { flag = mFlags[index / 32]; result = (flag & (1u << (index % 32))) != 0; }
        else { result = false; }
        return result;
    }
    cSPEditorBlock* GetParent() { return mSocketConnector; }
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
        uint32_t v = (uint32_t)blk->mLinked;
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

extern void FUN_0049dd20(cSPEditorBlock* b, BlockVec* out, int one);   // cdecl
extern void GetBoolProperty(void* props, unsigned int id, bool* out);   // 0x407190 cdecl

// @ 0x004a7f30
void SetSymmetricBlocksUIState(cSPEditorBlock* b, unsigned int param_2, unsigned char p3)
{
    if (b->GetModel() != 0 && b->GetModel()->FUN_004adc40() && !b->IsFlagSet(0x39)) {
        int item = b->CalculateSymmetrySign();
        cSPEditorBlock* p13 = b->GetParent2();
        if (b->IsFlagSet(0x23)) {
            int tmp = b->F44c050();
            bool t14 = false;
            if (tmp == 0) { if (item == 0) t14 = true; }
            else t14 = true;
            if (t14) {
                if (b->GetLinked() != 0 && b->GetLinked()->F44c030())
                    b->GetLinked()->F44ba20(0, 0);
            } else {
                if (b->GetLinked() != 0 && !b->GetLinked()->F44c030() && !b->IsFlagSet(0x3a))
                    b->GetLinked()->F44bcf0(0, 0);
            }
        } else if (!BlockBlocked(b)) {
            if (b->GetLinked() != 0 && b->GetLinked()->F44c030())
                b->GetLinked()->F44ba20(0, 0);
            BlockVec v((Alloc()));
            FUN_0049dd20(b, &v, 1);
            for (int block = 0, mem = v.size(); block < mem; ++block) {
                if (b->F44c030()) v[block]->F44bcf0(0, 0);
                else v[block]->F44ba20(0, 0);
            }
            v.erase(v.mpBegin, v.mpEnd);
            FUN_0049dd20(b->GetLinked(), &v, 1);
            for (int block = 0, mem = v.size(); block < mem; ++block) {
                if (b->GetLinked()->F44c030()) v[block]->F44bcf0(0, 0);
                else v[block]->F44ba20(0, 0);
            }
            ScratchSlots<2>();
        } else if (item == 0) {
            if (b->GetLinked() != 0) {
                bool h = b->IsFlagSet(0xb);
                bool p33 = false;
                void* elem = b->GetPropList();
                GetBoolProperty(elem, 0x7bd0ca3e, &p33);
                ScratchSlots<3>();
                if (!p33 && (!h || !p3)) {
                    if (b->F44c030()) {
                        b->GetLinked()->F44ba20(0, 0);
                        BlockVec w((Alloc()), 0);
                        FUN_0049dd20(b->GetLinked(), &w, 1);
                        for (int block = 0, mem = w.size(); block < mem; ++block) {
                            if (w[block].get() != 0 && !w[block]->F44c030())
                                w[block]->F44bcf0(0, 0);
                        }
                        ScratchSlots<2>();
                    }
                } else {
                    if (b->F44c030() && !b->GetLinked()->F44c030() && !b->IsFlagSet(0x3a))
                        b->GetLinked()->F44bcf0(0, 0);
                }
            }
        } else {
            if (b->GetLinked() != 0) {
                if (b->F44c030()) {
                    if (!b->GetLinked()->F44c030() && !b->IsFlagSet(0x3a)) {
                        b->GetLinked()->F44bcf0(0, 0);
                    } else {
                        if (b->IsFlagSet(0x3a) && b->GetLinked()->F44c030())
                            b->GetLinked()->F44ba20(0, 0);
                    }
                } else if (b->GetLinked()->F44c030()) {
                    b->F44bcf0(0, 0);
                }
            }
        }
        BlockVec* t7 = &b->mChildren;
        for (int block = 0, mem = t7->size(); block < mem; ++block)
            SetSymmetricBlocksUIState((*t7)[block].get(), 0, p3);
    }
}
