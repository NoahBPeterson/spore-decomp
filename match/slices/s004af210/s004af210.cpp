// Slice s004af210 — SP::cSPEditorModel vector helpers.
#include "types.h"

extern void* FUN_0042dee0(void* p, int size, int align, int flags);
extern void FUN_004b03f0(void* a, void* b, void* c);
extern void FUN_f47380(void* p);

struct Block194 { uint32_t d[0x76]; };

struct BBox24 { char b[0x18]; void FUN_00409c00(); };            // 0x409c00 (thiscall ctor)
struct ReserveLock { void FUN_004b00a0(void* owner); void FUN_004b0140(); };  // 0x4b00a0 / 0x4b0140

struct VecBase {
    char* mpBegin;      // +0x0
    char* mpEnd;        // +0x4
    char* mpCapacity;   // +0x8
    char* mpAllocName;  // +0xc (eastl allocator name passed to EASTL_Allocate)

    void Resize4(unsigned int n);     // 0x4afbf0
    void Resize4F(unsigned int n);    // 0x4afc80
    void Resize24(unsigned int n);    // 0x4aff80
    void Resize1d8(unsigned int n);   // 0x4afd00
    void Reserve194(unsigned int n);  // 0x4afdd0
    Block194* Erase194(Block194* dst, Block194* end);  // 0x4b0340
    void* Init8();                    // 0x4b0040

    // out-of-line vector primitives: thiscall, ecx is the vector base, the callee pops the stack args
    void FUN_00454280(char* first, char* last);            // 0x454280
    void FUN_004b0590(char* end, int n, void** out);       // 0x4b0590
    void FUN_004b0a10(char* end, int n, void** out);       // 0x4b0a10
    void FUN_004b1800(char* end, int n, void* elem);       // 0x4b1800
    void FUN_004b11f0(char* end, int n, void* elem);       // 0x4b11f0
    void FUN_004b0490(char* first, char* last);            // 0x4b0490
    char* FUN_004769b0(char* first, char* last);           // 0x4769b0
    void FUN_004b0180(void* local);                        // 0x4b0180
};

// @ 0x004af210
struct PropVal { unsigned int& GetValue(); };
bool GetPropertyAsUint32(void* propList, unsigned int id, unsigned int* out)
{
    if (propList != 0) {
        int pad;
        int local;
        if ((*(unsigned char(__thiscall*)(void*, unsigned int, int*))(*(void**)((char*)*(void**)propList + 0x24)))(propList, id, &local) != 0) {
            if (*(uint16_t*)(local + 0x12) == 10) {
                *out = ((PropVal*)local)->GetValue();
                return true;
            }
        }
    }
    return false;
}

// @ 0x004afbf0
void VecBase::Resize4(unsigned int n)
{
    unsigned int count = (unsigned int)((mpEnd - mpBegin) >> 2);
    if (count < n) {
        void* local = 0;
        FUN_004b0590(mpEnd, (int)(n - count), &local);
        if (local != 0) {
            (*(void(__thiscall*)(void*))(*(uint32_t*)local + 8))(local);
        }
    }
    else {
        FUN_00454280(mpBegin + n * 4, mpEnd);
    }
}

// @ 0x004afc80
void VecBase::Resize4F(unsigned int n)
{
    unsigned int count = (unsigned int)((mpEnd - mpBegin) >> 2);
    if (count < n) {
        float local = 0.0f;
        FUN_004b0a10(mpEnd, (int)(n - count), (void**)&local);
    }
    else {
        FUN_004769b0(mpBegin + n * 4, mpEnd);
    }
}

// @ 0x004aff80
void VecBase::Resize24(unsigned int n)
{
    int count = (int)((mpEnd - mpBegin) / 0x18);
    if ((unsigned int)count < n) {
        char local[0x18];
        ((BBox24*)local)->FUN_00409c00();
        FUN_004b1800(mpEnd, (int)(n - (unsigned int)count), local);
    }
    else {
        FUN_004b0490(mpBegin + n * 0x18, mpEnd);
    }
}

// @ 0x004b0340
Block194* VecBase::Erase194(Block194* dst, Block194* end)
{
    Block194* out = (Block194*)mpEnd;
    Block194* local_14 = dst;
    for (Block194* local_10 = end; local_10 != out; ++local_10) {
        *local_14 = *local_10;
        ++local_14;
    }
    for (Block194* local_1c = local_14; local_1c < (Block194*)mpEnd; ++local_1c) {
    }
    mpEnd = (char*)mpEnd + ((char*)end - (char*)dst) / 0x1d8 * -0x1d8;
    return dst;
}

// @ 0x004b0040
void* VecBase::Init8()
{
    int local_8 = 8;
    char* local_4 = (char*)this + 0x118;
    while (true) {
        local_8 = local_8 - 1;
        if (local_8 < 0) break;
        local_4 += 0xc;
    }
    int local_10 = 8;
    char* local_c = (char*)this + 0x178;
    while (true) {
        local_10 = local_10 - 1;
        if (local_10 < 0) break;
        local_c += 0xc;
    }
    return this;
}

// @ 0x004afd00
void VecBase::Resize1d8(unsigned int n)
{
    int count = (int)((mpEnd - mpBegin) / 0x1d8);
    if ((unsigned int)count < n) {
        char tmp[0x1d8];
        void* elem = ((VecBase*)tmp)->Init8();
        FUN_004b11f0(mpEnd, (int)(n - (unsigned int)count), elem);
    }
    else {
        Erase194((Block194*)(mpBegin + n * 0x1d8), (Block194*)mpEnd);
    }
}

// @ 0x004afdd0
void VecBase::Reserve194(unsigned int n)
{
    unsigned int size = (unsigned int)((mpEnd - mpBegin) / 0x1d8);
    if (n == 0xffffffffu || n <= size) {
        if (n < size) Resize1d8(n);
        char local[0x14];
        ((ReserveLock*)local)->FUN_004b00a0(this);
        FUN_004b0180(local);
        ((ReserveLock*)local)->FUN_004b0140();
    }
    else {
        void* p = (n == 0) ? 0 : FUN_0042dee0(&mpAllocName, n * 0x1d8, 4, 0);
        FUN_004b03f0(mpBegin, mpEnd, p);
        char* old = mpBegin;
        if (old != 0 && *(int*)(old - 4) != 0) {
            FUN_f47380(old);
        }
        int oldCount = (int)((mpEnd - old) / 0x1d8);
        mpBegin = (char*)p;
        mpEnd = oldCount * 0x1d8 + (char*)p;
        mpCapacity = n * 0x1d8 + (char*)p;
    }
}

// ---------------------------------------------------------------------------
// SP::cSPEditorModel::SaveResource (0x004af260, 2446 bytes)
//
// Inverse of LoadFromBinary (s004ae3b0): build the binary model description with
// WriteBinaryEditorModel(), then fill its header and one 0x1d8-byte entry per editor
// block (ids, parent/mirror indices, transforms, deformation words and attachments).
// ---------------------------------------------------------------------------
extern "C" void* memset(void* dst, int value, unsigned int count);

namespace SP {

struct Vec3 {
    float v[3];
    float& operator[](int i) { return v[i]; }
};
struct ResKey { uint32_t instance, type, group; };
struct Mat3 { uint32_t m[9]; };

struct Bitset60 {                                   // std::bitset<60>
    uint32_t w[2];
    bool Get(uint32_t pos) const
    {
        if (pos < 60)
            return (w[pos >> 5] & (1u << (pos % 32))) != 0;
        return false;
    }
};

class cSPEditorBlock;
struct BlockRef { cSPEditorBlock* mp; };             // AutoRefCount<cSPEditorBlock>
struct BlockList {
    BlockRef* mpBegin;
    BlockRef* mpEnd;
    BlockRef* mpCapacity;
};

class cSPEditorBlock { public:
    char pad00[0x10];
    void* mpModel;                                  // +0x10
    char pad14[0x08];
    uint32_t mField1c;                              // +0x1c
    uint32_t mField20;                              // +0x20
    char pad24[0x24];
    Vec3 mPosition;                                 // +0x48
    char pad54[0x54];
    Mat3 mMatA;                                     // +0xa8
    char padcc[0x24];
    Mat3 mMatB;                                     // +0xf0
    char pad114[0xb8];
    uint32_t mField1cc;                             // +0x1cc
    float mField1d0;                                // +0x1d0
    float mScale;                                   // +0x1d4
    float mField1d8;                                // +0x1d8
    char pad1dc[0x160];
    BlockRef mpParent;                              // +0x33c
    char pad340[0x60];
    Vec3 mVecA;                                     // +0x3a0
    Vec3 mVecB;                                     // +0x3ac
    char pad3b8[0x28];
    BlockRef mpMirror;                              // +0x3e0
    BlockRef mpMirrorSource;                        // +0x3e4
    char pad3e8[0xe0];
    char* mAttachBegin;                             // +0x4c8
    char* mAttachEnd;                               // +0x4cc
    char* mAttachCapacity;                          // +0x4d0
    char pad4d4[0x1f8];
    char* mDefBegin;                                // +0x6cc
    char* mDefEnd;                                  // +0x6d0
    char* mDefCapacity;                             // +0x6d4
    char pad6d8[0x2c];
    float* mDeltaBegin;                             // +0x704
    float* mDeltaEnd;                               // +0x708
    float* mDeltaCapacity;                          // +0x70c
    char pad710[0x2c];
    uint32_t* mAnimBegin;                           // +0x73c
    uint32_t* mAnimEnd;                             // +0x740
    uint32_t* mAnimCapacity;                        // +0x744
    char pad748[0x680];
    Bitset60 mFlags;                                // +0xdc8
    char paddd0[0x34];
    int mIndex;                                     // +0xe04
    int GetSymmetrySign();                          // 0x0044f220
};

struct DefHandle {                                  // cSPEditorHandleDeform
    char pad000[0x8c];
    uint32_t field8c;                               // +0x8c
    char pad090[0xf0];
    float mDelta;                                   // +0x180
};

struct U32Vec {
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    void resize(unsigned int n);                    // 0x004cd3c0
};

// ---- the binary model description (see s004ae3b0) --------------------------
struct ModelBlockEntry {                            // 0x1d8 bytes
    uint32_t id;                                    // +0x00
    uint32_t field04;                               // +0x04
    uint32_t parent;                                // +0x08
    uint32_t mirror;                                // +0x0c
    float field10;                                  // +0x10
    Vec3 offset;                                    // +0x14
    Vec3 vecA;                                      // +0x20
    Vec3 vecB;                                      // +0x2c
    Mat3 matA;                                      // +0x38
    Mat3 matB;                                      // +0x5c
    uint8_t flagA;                                  // +0x80
    uint8_t flagB;                                  // +0x81
    uint8_t pad82[2];
    uint32_t field84;                               // +0x84
    float field88;                                  // +0x88
    float scale;                                    // +0x8c
    uint32_t wordCount;                             // +0x90
    float wordsA[8];                                // +0x94
    uint32_t wordsB[8];                             // +0xb4
    uint32_t attachCount;                           // +0xd4
    uint32_t attachKeys[8];                         // +0xd8
    uint32_t attachIds[8];                          // +0xf8
    Vec3 attachA[8];                                // +0x118
    Vec3 attachB[8];                                // +0x178
};
struct ModelHeader {                                // at data+0x18
    uint32_t type;                                  // +0x00
    uint32_t zcorp;                                 // +0x04
    uint32_t skinEffects[3];                        // +0x08
    uint32_t skinSeeds[3];                          // +0x14
    Vec3 skinColors[3];                             // +0x20
};
struct EntryVec {
    ModelBlockEntry* mpBegin;
    ModelBlockEntry* mpEnd;
    ModelBlockEntry* mpCapacity;
};
struct EditorModelData {
    char pad00[0x08];
    ResKey key;                                     // +0x08
    char pad14[0x04];
    ModelHeader header;                             // +0x18
    char pad5c[0x3c];
    EntryVec blocks;                                // +0x98
};

EditorModelData* WriteBinaryEditorModel(void* source);   // 0x004b0010
uint32_t FUN_004bb860(uint32_t modelType);              // 0x004bb860
extern const float kZero;                               // 0x01485378

// ---- the editor model (retail layout, see s004ae3b0/s0043e3f0) -------------
struct cSPEditorModel {
    char pad00[0x0c];
    ResKey mKey;                                    // +0x0c
    BlockList mBlocks;                              // +0x18
    char pad24[0x08];
    uint8_t mAllBlocksLoaded;                       // +0x2c
    char pad2d[0x22];
    uint8_t mUsingSymmetry;                         // +0x4f
    char pad50[0x08];
    uint32_t mModelType;                            // +0x58
    char pad5c[0x30];
    uint32_t mSkinEffects[3];                       // +0x8c
    uint32_t mSkinSeeds[3];                         // +0x98
    Vec3 mSkinColors[3];                            // +0xa4
    char padc8[0x14];
    uint32_t mZCorpScore;                           // +0xdc

    bool SaveResource(void* source);
};

// @ 0x004af260  SP::cSPEditorModel::SaveResource
bool cSPEditorModel::SaveResource(void* source)
{
    if (!mAllBlocksLoaded)
        return false;

    cSPEditorModel* self = this;
    EditorModelData* data = WriteBinaryEditorModel(source);
    if (data == 0)
        return false;

    bool special = false;
    uint32_t hash = FUN_004bb860(this->mModelType);
    if (hash == 0x3d97a8e4 || hash == 0x2b978c46 || hash == 0x438f6347)
        special = true;

    BlockList* pBlocks = &self->mBlocks;
    int count = (int)(pBlocks->mpEnd - pBlocks->mpBegin);
    BlockRef* blocks = pBlocks->mpBegin;
    for (int i = 0; i < count; ++i)
        blocks[i].mp->mIndex = i;

    ModelHeader* header = &data->header;
    ((VecBase*)&data->blocks)->Reserve194(0);
    ((VecBase*)&data->blocks)->Resize1d8((unsigned int)count);

    memset(&data->header, 0, 0x80);

    EntryVec* pEntries = &data->blocks;
    int entryCount = (int)(pEntries->mpEnd - pEntries->mpBegin);
    ModelBlockEntry* entryBase = pEntries->mpBegin;
    memset(entryBase, 0, entryCount * 0x1d8);

    header->type = self->mModelType;
    for (int i = 0; i < 3; ++i) {
        header->skinEffects[i] = self->mSkinEffects[i];
        header->skinSeeds[i] = self->mSkinSeeds[i];
        header->skinColors[i] = self->mSkinColors[i];
    }
    header->zcorp = self->mZCorpScore;

    for (int i = 0; i < count; ++i) {
        ModelBlockEntry* entry = &entryBase[i];
        cSPEditorBlock* block = blocks[i].mp;

        entry->id = block->mField20;
        entry->field04 = block->mField1c;
        entry->parent = 0xffffffffu;
        if (block->mpParent.mp != 0 && block->mpParent.mp != block) {
            uint32_t parent = (uint32_t)block->mpParent.mp->mIndex;
            if (parent < (uint32_t)count && blocks[parent].mp == block->mpParent.mp)
                entry->parent = parent;
        }

        entry->mirror = 0xffffffffu;
        if (block->mpMirror.mp != 0 && block->mpMirror.mp != block) {
            uint32_t mirror = (uint32_t)block->mpMirror.mp->mIndex;
            if (mirror < (uint32_t)count && blocks[mirror].mp == block->mpMirror.mp)
                entry->mirror = mirror;
        }

        if (block->mFlags.Get(0x39)) {
            entry->flagB = 1;
            if (block->mpMirrorSource.mp != 0 && block->mpMirrorSource.mp != block) {
                uint32_t mirror = (uint32_t)block->mpMirrorSource.mp->mIndex;
                if (mirror < (uint32_t)count && blocks[mirror].mp == block->mpMirrorSource.mp)
                    entry->mirror = mirror;
            }
        }

        entry->field10 = block->mField1d8;
        entry->offset = block->mPosition;
        if (this->mUsingSymmetry && block->GetSymmetrySign() == 0)
            entry->offset[0] = kZero;

        entry->matA = block->mMatA;
        entry->matB = block->mMatB;
        entry->vecA = block->mVecA;
        entry->vecB = block->mVecB;
        entry->field84 = block->mField1cc;

        if (block->mFlags.Get(0xb))
            entry->field88 = block->mField1d0;
        if (block->mFlags.Get(0x1f))
            entry->scale = block->mScale;
        if (block->mFlags.Get(0xc))
            entry->flagA = 1;

        if (block->mpModel != 0) {
            int handleCount = (int)((DefHandle**)block->mDefEnd - (DefHandle**)block->mDefBegin);
            ((VecBase*)((char*)block + 0x704))->Resize4F((unsigned int)handleCount);
            ((U32Vec*)((char*)block + 0x73c))->resize((unsigned int)handleCount);
            for (int j = 0; j < handleCount; ++j) {
                DefHandle* handle = ((DefHandle**)block->mDefBegin)[j];
                block->mDeltaBegin[j] = handle->mDelta;
                block->mAnimBegin[j] = handle->field8c;
            }
        }

        int deltaCount = (int)(block->mDeltaEnd - block->mDeltaBegin);
        int wordCount = (8 < deltaCount) ? 8 : deltaCount;
        entry->wordCount = (uint32_t)wordCount;
        for (int j = 0; j < wordCount; ++j) {
            entry->wordsA[j] = block->mDeltaBegin[j];
            entry->wordsB[j] = block->mAnimBegin[j];
        }

        int attachTotal = (int)((block->mAttachEnd - block->mAttachBegin) / 0x20);
        int attachCount = (8 < attachTotal) ? 8 : attachTotal;
        if (special)
            attachCount = 0;
        entry->attachCount = (uint32_t)attachCount;
        char* p = block->mAttachBegin;
        for (int j = 0; j < attachCount; ++j) {
            entry->attachKeys[j] = *(uint32_t*)p;
            entry->attachIds[j] = *(uint32_t*)(p + 4);
            entry->attachA[j] = *(Vec3*)(p + 8);
            entry->attachB[j] = *(Vec3*)(p + 0x14);
            p += 0x20;
        }
    }

    data->key = self->mKey;
    return true;
}

} // namespace
