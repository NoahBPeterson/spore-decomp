// Slice s004ae3b0: SP::cSPEditorModel::LoadFromBinary (0x004ae3b0, 3676 bytes).
// Unoptimized editor module (/Od /Ob1 /arch:SSE /fp:fast, no /EHsc).
//
// Rebuilds an editor model from the binary model description produced by
// WriteBinaryEditorModel(): copies the header fields, loads the model's name
// from its resource, then creates one cSPEditorBlock per entry, links the
// parent/mirror blocks and copies every per-block transform / attribute.
#include "types.h"

void* operator new(unsigned int n, const char* pName, int flags, unsigned int debugFlags, const char* pFile, int line);

struct Vec3 { float x, y, z; };
struct Mat3 { uint32_t m[9]; };           // 3x3 float matrix (copied with rep movsd)

template <typename T> struct ARC {         // EA::AutoRefCount
    T* mp;
    ARC() : mp(0) {}
    ARC(T* p) : mp(p) { if (mp) mp->AddRef(); }
    ~ARC() { if (mp) mp->Release(); }
    ARC& operator=(T* p)
    {
        if (p != mp) {
            T* old = mp;
            if (p) p->AddRef();
            mp = p;
            if (old) old->Release();
        }
        return *this;
    }
    ARC& operator=(const ARC& o)
    {
        T* p = o.mp;
        if (p != mp) {
            T* old = mp;
            if (p) p->AddRef();
            mp = p;
            if (old) old->Release();
        }
        return *this;
    }
    T* operator->() const { return mp; }
};

// ---- resources ------------------------------------------------------------
struct ResKey { uint32_t instance, type, group; };

struct IResource {                         // loaded model resource (name provider)
    virtual int AddRef();
    virtual int Release();                 // +4
};
struct IModelInfo {                        // object obtained from the resource
    const wchar_t* GetName();              // 0x00414e10
    uint32_t GetDescription();             // 0x005508c0
};
IModelInfo* GetModelInfo(ARC<IResource>* res);       // 0x00421f60 (cdecl)

struct IResourceManager {
    virtual void v0(); virtual void v1(); virtual void v2();
    virtual bool GetResource(const ResKey* key, IResource** out, int a, int b, int c, int d);   // +0x0c
};
namespace EA { namespace ResourceMan { IResourceManager* GetManager(); } }   // 0x0067dcd0

// ---- property manager ------------------------------------------------------
struct IPropertyList {
    virtual int AddRef();
    virtual int Release();                 // +4
};
struct IPropertyManager {
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10();
    virtual void GetPropertyList(int config, uint32_t group, IPropertyList** out);   // +0x2c
};
struct PropListRef {
    IPropertyList* mp;
    IPropertyList** Out();                 // 0x0041d870 (releases, returns &mp)
};
namespace SP {
IPropertyManager* PropertyManager();                                                   // 0x0067de30
bool GetPropertyAsUint32(IPropertyList* list, uint32_t id, uint32_t* out);             // 0x004af210
namespace Editor { int GetConfigFromModelType(uint32_t modelType); }                   // 0x00432f10
}
extern uint32_t gPropertyGroup;            // 0x015d68a8

// ---- containers ------------------------------------------------------------
struct WString {                           // eastl::basic_string<wchar_t> (begin/end/cap + allocator)
    uint16_t* mpBegin;
    uint16_t* mpEnd;
    uint16_t* mpCapacity;
    uint32_t mAllocator;
    void clear()
    {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
    }
};

struct Bitset60 {                          // std::bitset<60>
    uint32_t w[2];
    void set(uint32_t pos, bool val)
    {
        if (pos < 60) {
            if (val)
                w[pos >> 5] |= 1u << (pos % 32);
            else
                w[pos >> 5] &= ~(1u << (pos % 32));
        }
    }
};

struct CountVec {                          // eastl::fixed_vector<uint32_t, 128>
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    uint32_t mFixedPad[2];
    uint32_t mOverflow;                    // +0x14
    uint32_t mBuffer[128];                 // +0x18
    void Init(void* allocTag);             // 0x00540470
    void InitFixed();                      // 0x004c5e30
    void resize(uint32_t n, uint32_t value);   // 0x004b0560
    void FreeOverflow();                   // 0x00425990
    uint32_t& operator[](int i) { return mpBegin[i]; }
};

class cSPEditorBlock;
struct BlockList {                         // eastl::vector<AutoRefCount<cSPEditorBlock>>
    ARC<cSPEditorBlock>* mpBegin;
    ARC<cSPEditorBlock>* mpEnd;
    ARC<cSPEditorBlock>* mpCapacity;
    void erase(ARC<cSPEditorBlock>* first, ARC<cSPEditorBlock>* last);   // 0x00454280
    void resize(uint32_t n);                                             // 0x004afbf0
    void push_back(const ARC<cSPEditorBlock>& v);                        // 0x004541f0
    void reserve(uint32_t n);                                            // 0x004e0880
};
struct WordVec {                           // eastl::vector<Word32>
    uint32_t* mpBegin;
    uint32_t* mpEnd;
    uint32_t* mpCapacity;
    void assign(const uint32_t* first, const uint32_t* last, const void* tag);   // 0x004d04f0
};
struct AttachEntry {
    uint32_t id;
    Vec3 a;
    Vec3 b;
};
struct AttachVec {
    uint32_t pad[3];
    AttachEntry* AddEntry(const uint32_t* key);                          // 0x00454420
};

// ---- the block (0xe08 bytes) -------------------------------------------------
class cSPEditorModel;
class cSPEditorBlock {
public:
    cSPEditorBlock();                                                    // 0x004346b0
    virtual void v0();
    virtual int AddRef();
    virtual int Release();
    uint32_t pad04[(0x1c - 0x04) / 4];
    uint32_t mField1c;                                                   // +0x1c
    uint32_t mField20;                                                   // +0x20
    uint32_t pad24[1];
    cSPEditorModel* mpModel;                                             // +0x28
    uint32_t pad2c[(0x48 - 0x2c) / 4];
    Vec3 mOffset;                                                        // +0x48
    uint32_t pad54[(0x60 - 0x54) / 4];
    Mat3 mMatrix;                                                        // +0x60
    uint32_t pad84[(0xa8 - 0x84) / 4];
    Mat3 mMatrixA;                                                       // +0xa8
    uint32_t pada8[(0xf0 - 0xcc) / 4];
    Mat3 mMatrixB;                                                       // +0xf0
    uint32_t pad114[(0x1cc - 0x114) / 4];
    uint32_t mField1cc;                                                  // +0x1cc
    float mField1d0;                                                     // +0x1d0
    float mScale;                                                        // +0x1d4
    float mField1d8;                                                     // +0x1d8
    uint32_t pad1dc[(0x33c - 0x1dc) / 4];
    ARC<cSPEditorBlock> mpParent;                                        // +0x33c
    BlockList mChildren;                                                 // +0x340
    uint32_t pad34c[(0x3a0 - 0x34c) / 4];
    Vec3 mVecA;                                                          // +0x3a0
    Vec3 mVecB;                                                          // +0x3ac
    uint32_t pad3b8[(0x3e0 - 0x3b8) / 4];
    ARC<cSPEditorBlock> mpMirror;                                        // +0x3e0
    ARC<cSPEditorBlock> mpMirrorSource;                                  // +0x3e4
    uint32_t pad3e8[(0x4c8 - 0x3e8) / 4];
    AttachVec mAttachments;                                              // +0x4c8
    uint32_t pad4d4[(0x704 - 0x4d4) / 4];
    WordVec mWordsA;                                                     // +0x704
    uint32_t pad710[(0x73c - 0x710) / 4];
    WordVec mWordsB;                                                     // +0x73c
    uint32_t pad748[(0xdc8 - 0x748) / 4];
    Bitset60 mFlags;                                                     // +0xdc8
    uint32_t paddd0[(0xe08 - 0xdd0) / 4];
};

// ---- the binary model description ----------------------------------------------
struct ModelBlockEntry {                   // 0x1d8 bytes
    uint32_t id;                           // +0x00
    uint32_t field04;                      // +0x04
    uint32_t parent;                       // +0x08
    uint32_t mirror;                       // +0x0c
    float field10;                         // +0x10
    Vec3 offset;                           // +0x14
    Vec3 vecA;                             // +0x20
    Vec3 vecB;                             // +0x2c
    Mat3 matA;                             // +0x38
    Mat3 matB;                             // +0x5c
    uint8_t flagA;                         // +0x80
    uint8_t flagB;                         // +0x81
    uint8_t pad82[2];
    uint32_t field84;                      // +0x84
    float field88;                         // +0x88
    float scale;                           // +0x8c
    uint32_t wordCount;                    // +0x90
    uint32_t wordsA[8];                    // +0x94
    uint32_t wordsB[8];                    // +0xb4
    uint32_t attachCount;                  // +0xd4
    uint32_t attachKeys[8];                // +0xd8
    uint32_t attachIds[8];                 // +0xf8
    Vec3 attachA[8];                       // +0x118
    Vec3 attachB[8];                       // +0x178
};
struct ModelHeader {                       // at data+0x18
    uint32_t type;                         // +0x00
    uint32_t zcorp;                        // +0x04
    uint32_t skinEffects[3];               // +0x08
    uint32_t skinSeeds[3];                 // +0x14
    Vec3 skinColors[3];                    // +0x20
};
struct EditorModelData {
    uint32_t pad00[2];
    ResKey key;                            // +0x08
    uint32_t pad14[1];
    ModelHeader header;                    // +0x18
    uint32_t pad5c[(0x98 - 0x5c) / 4];
    ModelBlockEntry* mpBegin;              // +0x98
    ModelBlockEntry* mpEnd;                // +0x9c
};
namespace { EditorModelData* WriteBinaryEditorModel(void* model); }          // 0x004b0010

Mat3* MatrixMultiply(Mat3* out, const Mat3* a, const Mat3* b);              // 0x0041de20 (cdecl)

// ---- the editor model -----------------------------------------------------------
struct cISPEditorNameProvider {
    virtual void SetName(const wchar_t* name);            // +0
    virtual void v1();
    virtual void SetDescription(uint32_t desc);           // +8
};
struct RefCountBase { virtual int AddRef(); virtual int Release(); int mRefCount; };

struct Tag {};   // empty allocator tag

inline int Strcmp(const uint16_t* a, const uint16_t* b)
{
    uint16_t c;
    do {
        c = *a;
        if (c != *b)
            return c < *b ? -1 : 1;
        if (c == 0)
            break;
        c = a[1];
        if (c != b[1])
            return c < b[1] ? -1 : 1;
        a += 2;
        b += 2;
    } while (c != 0);
    return 0;
}

extern const uint16_t kEmptyWString[];     // L"" at 0x013ec468

class cSPEditorModel : public cISPEditorNameProvider {
public:
    uint32_t pad04[2];
    ResKey mKey;                           // +0x0c
    BlockList mBlockList;                  // +0x18
    uint32_t pad24[(0x54 - 0x24) / 4];
    uint32_t mModelTranslationOptions;     // +0x54
    uint32_t mModelType;                   // +0x58
    WString mName;                         // +0x5c
    WString mDescription;                  // +0x6c
    WString mCleanName;                    // +0x7c
    uint32_t mSkinEffects[3];              // +0x8c
    uint32_t mSkinEffectSeeds[3];          // +0x98
    Vec3 mSkinColors[3];                   // +0xa4
    uint32_t padc8[(0xdc - 0xc8) / 4];
    uint32_t mZCorpScore;                  // +0xdc

    bool LoadFromBinary(void* source);
};

// @ 0x004AE3B0  SP::cSPEditorModel::LoadFromBinary
bool cSPEditorModel::LoadFromBinary(void* source)
{
    cSPEditorModel* self = this;
    EditorModelData* data = WriteBinaryEditorModel(source);
    if (!data)
        return false;

    ModelHeader* header = &data->header;
    uint32_t numBlocks = (uint32_t)(data->mpEnd - data->mpBegin);

    // header fields
    self->mModelType = header->type;
    self->mModelTranslationOptions = 0;
    int config = SP::Editor::GetConfigFromModelType(self->mModelType);
    if (config != -1) {
        const uint32_t kPropId = 0x51ce36a;
        PropListRef list;
        list.mp = 0;
        SP::PropertyManager()->GetPropertyList(config, gPropertyGroup, list.Out());
        SP::GetPropertyAsUint32(list.mp, 0x51ce36a, &self->mModelTranslationOptions);
        if (list.mp)
            list.mp->Release();
    }

    // clear the three name strings
    self->mName.clear();
    self->mDescription.clear();
    self->mCleanName.clear();

    // fetch the model's display name/description from its resource
    ResKey key = data->key;
    key.type = 0x30bdee3;
    ARC<IResource> resource;
    IResourceManager* manager = EA::ResourceMan::GetManager();
    resource = 0;
    if (manager->GetResource(&key, &resource.mp, 0, 0, 0, 0)) {
        IModelInfo* info = GetModelInfo(&resource);
        if (info) {
            const wchar_t* name = info->GetName();
            uint32_t description = info->GetDescription();
            if (Strcmp((const uint16_t*)name, kEmptyWString) != 0)
                self->SetName(name);
            self->SetDescription(description);
        }
    }

    // skin effects / seeds / colors
    for (int i = 0; i < 3; ++i) {
        self->mSkinEffects[i] = header->skinEffects[i];
        self->mSkinEffectSeeds[i] = header->skinSeeds[i];
        self->mSkinColors[i] = header->skinColors[i];
    }
    self->mZCorpScore = header->zcorp;

    // rebuild the block list
    BlockList* blocks = &self->mBlockList;
    blocks->erase(blocks->mpBegin, blocks->mpEnd);
    blocks->resize(numBlocks);

    {
        CountVec childCounts;
        Tag tag;
        childCounts.Init(&tag);
        childCounts.InitFixed();
        childCounts.resize(numBlocks, 0);

        // count the children of every block
        for (int i = 0; i < (int)numBlocks; ++i) {
            if (data->mpBegin[i].parent < numBlocks) {
                ModelBlockEntry* e = &data->mpBegin[i];
                uint32_t* slot = &childCounts.mpBegin[e->parent];
                *slot = *slot + 1;
            }
        }

        // create the blocks
        for (int i = 0; i < (int)numBlocks; ++i) {
            cSPEditorBlock* block = new ("Editor", 0, 0, 0, 0) cSPEditorBlock();
            self->mBlockList.mpBegin[i] = block;
            block->mChildren.reserve(childCounts[i]);
        }

        for (uint32_t* it = childCounts.mpBegin; it < childCounts.mpEnd; ++it) {
        }
        childCounts.FreeOverflow();
    }

    // fill in every block
    for (int i = 0; i < (int)numBlocks; ++i) {
        cSPEditorBlock* block = self->mBlockList.mpBegin[i].mp;
        ModelBlockEntry* entry = &data->mpBegin[i];

        block->mpModel = self;
        bool isFlagB = entry->flagB != 0;
        block->mFlags.set(0x39, isFlagB);

        if (entry->mirror != (uint32_t)-1) {
            if (isFlagB)
                block->mpMirror = 0;
            else
                block->mpMirror = self->mBlockList.mpBegin[entry->mirror];
            block->mpMirrorSource = self->mBlockList.mpBegin[entry->mirror];
        }
        if (entry->parent != (uint32_t)-1) {
            block->mpParent = self->mBlockList.mpBegin[entry->parent];
            ARC<cSPEditorBlock> thisBlock(block);
            block->mpParent->mChildren.push_back(thisBlock);
        }

        block->mField20 = entry->id;
        block->mField1c = entry->field04;
        block->mField1d8 = entry->field10;
        block->mOffset = entry->offset;
        block->mMatrixA = entry->matA;
        block->mMatrixB = entry->matB;
        Mat3 product;
        block->mMatrix = *MatrixMultiply(&product, &block->mMatrixB, &block->mMatrixA);
        block->mVecA = entry->vecA;
        block->mVecB = entry->vecB;
        block->mField1cc = entry->field84;
        block->mField1d0 = entry->field88;
        block->mScale = entry->scale == 0.0f ? 1.0f : entry->scale;
        bool isFlagA = entry->flagA != 0;
        block->mFlags.set(0xc, isFlagA);

        Tag tagA, tagB;
        block->mWordsA.assign(entry->wordsA, entry->wordsA + entry->wordCount, &tagA);
        block->mWordsB.assign(entry->wordsB, entry->wordsB + entry->wordCount, &tagB);

        for (int j = 0, n = (int)entry->attachCount; j < n; ++j) {
            AttachEntry* a = block->mAttachments.AddEntry(&entry->attachKeys[j]);
            a->id = entry->attachIds[j];
            a->a = entry->attachA[j];
            a->b = entry->attachB[j];
        }
    }

    self->mKey = data->key;
    return true;
}
