// slice s00591690 -- SP::cAppModeEditorBase::HandlePaletteItemTriggerMessage (0x00591690, 2307 B).
// Called with (message, messageID) from the editor's palette-item trigger path.  Messages with messageID
// 0xeccc3657 apply a palette item to the current model (paint colour, skin theme, region paint, animated
// events); messageID 0 starts placing a part from the palette (0xa2e50993: place at the cursor,
// 0xc9db779b: place the part described by an effect property).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast /GS- (same module as s00591fa0).
#include "types.h"

struct Vector3 {
    float x, y, z;
    Vector3() {}
    Vector3(const Vector3& v) : x(v.x), y(v.y), z(v.z) {}
};
struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
};

#define CAT2(a, b) a##b
#define CAT(a, b) CAT2(a, b)
#define PAD1 virtual void CAT(vpad, __COUNTER__)();
#define PAD4 PAD1 PAD1 PAD1 PAD1
#define PAD8 PAD4 PAD4

void* operator new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
inline void* operator new(unsigned, void* p) { return p; }

namespace EA { namespace Hash {
uint32_t FNV1_String16(const wchar_t* s, uint32_t seed, int mode);                 // 0x00932f30
}}

namespace SP {

class cSPEditorModel {
public:
    uint32_t pad0[0x58 / 4];
    const wchar_t* mpName;                                  // +0x58
};
class cSPEditorBlock {
public:
    virtual void v00(); virtual void v04();
    virtual void Release();                                 // +0x08
};
class cSPEditorSkinManager {
public:
    void* GetSkin(int which);                               // 0x004c49e0
    bool IsBusy();                                          // 0x004c58b0
    void RepaintModel(cSPEditorModel* model);               // 0x004c5200
};

// intrusive pointer to a resource-info object (refcount base at +4); Reset() = 0x005766b0, dtor = 0x004a9ae0
class cResourceInfo {
public:
    virtual void v00();
    virtual const wchar_t* GetName();                       // +0x04
};
struct ResourceInfoRef {
    cResourceInfo* mpObject;
    ResourceInfoRef() : mpObject(0) {}
    ~ResourceInfoRef();                                     // 0x004a9ae0
    ResourceInfoRef* Reset();                               // 0x005766b0
};

class cSPEditorUndoState {
public:
    virtual void v00();
    virtual void AddRef();                                  // +0x04
    virtual void Release();                                 // +0x08
    uint32_t pad4[(0x18 - 4) / 4];
    ResourceKey mKey;                                       // +0x18
    int mRegion;                                            // +0x24
    void* mpMessage;                                        // +0x28
    cSPEditorUndoState();                                   // 0x00572ae0
};
struct UndoStateRef {                                       // EA::AutoRefCount<cSPEditorUndoState>
    cSPEditorUndoState* mpObject;
    UndoStateRef() : mpObject(0) {}
    ~UndoStateRef() { if (mpObject) mpObject->Release(); }
    UndoStateRef& operator=(cSPEditorUndoState* p);         // 0x00572620
};

struct tSPEditorPaint {
    uint32_t mPaint;
    Vector3 mColor1;                                        // +0x04
    Vector3 mColor2;                                        // +0x10
};

class cSPEditorPaintTheme {
public:
    virtual void AddRef();
    virtual void Release();                                 // +0x04
    uint32_t pad4[(0x164 - 4) / 4];
    uint32_t mSkinEffects[3];                               // +0x164 (effect ids per skin slot)
    uint32_t pad170[(0x1a0 - 0x170) / 4];
    cSPEditorPaintTheme();                                  // 0x004b24c0
    ~cSPEditorPaintTheme();                                 // 0x004b25e0
    void SetSource(uint32_t source);                        // 0x004b26e0
    void ReadFromProp(uint32_t propID);                     // 0x004b2bb0
    bool ReadFromProp2(uint32_t propID, bool useColors);    // 0x004b29b0
    void ReadFromAsset(cSPEditorModel* model);              // 0x004b2800
    void WriteToProp(cSPEditorModel* model, int region);    // 0x004b2f80
    void SetRegionColor(Vector3 color, int region);         // 0x004b3c70
    void ReadSkinThemeFromProp(cResourceInfo* info, uint32_t a, uint32_t hash);   // 0x004b4470
    void ExtractRegionPaintData(cResourceInfo* info, uint32_t a, uint32_t hash);  // 0x004b4930
    static bool Apply(const ResourceKey* key, ResourceInfoRef* info, int flags);  // 0x004badd0
    static bool ExtractSkinPaintData(uint32_t source);      // 0x004bbe90
    static bool IsRegionSource(uint32_t source);            // 0x004bbed0
};
struct ThemeRef {                                           // EA::AutoRefCount<cSPEditorPaintTheme>
    cSPEditorPaintTheme* mpObject;
    ThemeRef(cSPEditorPaintTheme* p);                       // 0x00572660
    ~ThemeRef() { if (mpObject) mpObject->Release(); }
};
uint32_t SourceFromName(const wchar_t* name);               // 0x004bb860

class cPaletteCategory;
class cSPPaletteCategoryUI {
public:
    bool IsColor1Default();                                 // 0x005c2e80
    tSPEditorPaint GetSelectedPaint();                      // 0x005c2d30
};
class cSPPaletteUI {
public:
    int GetSelectedRegion();                                // 0x005ca930
    int GetSelectedCategoryID();                            // 0x005ca940
    int FindCategoryIndex();                                // 0x005ca9c0
    cSPPaletteCategoryUI* GetCategory(int index);           // 0x005cae30
};

class cEditorLaunchData {
public:
    uint32_t pad0[0x6e / 4];
    uint8_t pad6c[2];
    bool mbEnabled;                                         // +0x6e
};

class cSPEditorAnimatedEventInfo {
public:
    virtual void v00(); virtual void AddRef();
    virtual void Release();                                 // +0x08
    uint32_t mData[(0x30 - 4) / 4];
    cSPEditorAnimatedEventInfo();                           // 0x0059d960
    void MessageSend(uint32_t messageID, int a, cSPEditorModel* model, uint32_t brainLevel, int b,
                     float delay, int c, uint32_t animID, float speed);   // 0x0059d8b0
};

// outgoing message with a table of listener slots (0x00421c80 / 0x00421cf0)
struct SlotMessage {
    void* vptr;
    long refCount;
    uint32_t mValue;                                        // +0x08
    uint32_t pad0c;
    uint32_t mRegion;                                       // +0x10
    uint32_t pad14;
    uint32_t mFlags;                                        // +0x18
    uint32_t pad1c[(0x30 - 0x1c) / 4];
    uint32_t mMessageID;                                    // +0x30
    uint32_t pad34[(0x40 - 0x34) / 4];
    SlotMessage* Construct(uint32_t arg);                   // 0x00421c80
    void Destruct();                                        // 0x00421cf0
};
class IMessageServer {
public:
    PAD4 PAD1
    virtual void PostMSG(uint32_t messageID, void* data, int flags);          // +0x14
};
IMessageServer* MessageServer();                            // 0x0067dcc0

// global services reached through vtables (0x0067dce0 -> +0x14(2, 0) -> +0x1c(1000))
class IRequirement {
public:
    PAD4 PAD1 PAD1 PAD1
    virtual bool IsAvailable(int id);                       // +0x1c
};
class IRequirements {
public:
    PAD4 PAD1
    virtual IRequirement* GetRequirement(int kind, int arg);   // +0x14
};
IRequirements* GetRequirements();                           // 0x0067dce0

// property list holder: vtable +4 = Release
class cPropertyList {
public:
    virtual void v00();
    virtual void Release();
};
struct PropRef {                                            // EA::AutoRefCount<cPropertyList>
    cPropertyList* mpObject;
    PropRef() : mpObject(0) {}
    cPropertyList** AsPPTypeParam();                        // 0x00a16f40
};
class IPropertyManager {
public:
    PAD8 PAD1 PAD1 PAD1
    virtual bool GetPropertyList(uint32_t id, uint32_t group, cPropertyList** out);   // +0x2c
};
IPropertyManager* PropertyManager();                        // 0x0067de30
bool GetPropertyAsKey(cPropertyList* prop, uint32_t id, ResourceKey* out);            // 0x006a1250

void PlayEditorSound(uint32_t soundID, uint32_t group, float pitch, int flags);   // 0x00435f40
void PlayUISound(uint32_t soundID);                         // 0x004a88d0
extern int gEditorSoundCounter;                             // 0x015e4eec

// pointer holder at +0xd0 (EA::AutoRefCount<cSPEditorBlock>)
struct BlockRef {
    cSPEditorBlock* mpObject;
    BlockRef* Reset();                                      // 0x00c463d0
    __forceinline void Clear() {
        cSPEditorBlock* p = mpObject;
        if (p) {
            mpObject = 0;
            p->Release();
        }
    }
};

struct SlotEntry {
    bool* mpFlags;
    uint32_t pad[4];
};

struct MsgPaletteItem {
    uint32_t pad0[3];
    ResourceKey mKey;                                       // +0x0c
    uint32_t pad18[3];
    uint32_t mID;                                           // +0x24
};

class cAppModeEditorBase {
public:
    PAD8 PAD1 PAD1 PAD1
    virtual bool PlaceFromCursor(int id, float x, float y, int flag);   // +0x2c
    uint32_t pad04[(0x28 - 4) / 4];
    float mMouseX;                                          // +0x28
    float mMouseY;                                          // +0x2c
    uint32_t pad30[(0x98 - 0x30) / 4];
    cSPEditorModel* mEditorModel;                           // +0x98
    uint32_t pad9c[(0xd0 - 0x9c) / 4];
    BlockRef mPendingBlock;                                 // +0xd0
    uint32_t padd4[(0x150 - 0xd4) / 4];
    cSPEditorSkinManager* mSkinManager;                     // +0x150
    cSPEditorSkinManager* mSaveSkinManager;                 // +0x154
    uint32_t pad158[(0x1cc - 0x158) / 4];
    cEditorLaunchData* mLaunchData;                         // +0x1cc
    uint32_t pad1d0[(0x2a0 - 0x1d0) / 4];
    cSPEditorPaintTheme* mCurrentPaintTheme;                // +0x2a0
    uint32_t pad2a4[(0x3c0 - 0x2a4) / 4];
    uint32_t mField3c0;                                     // +0x3c0
    cSPPaletteUI* mpPaintPaletteUI;                         // +0x3c4
    uint32_t pad3c8[(0x4b0 - 0x3c8) / 4];
    uint8_t pad4b0[2];
    bool mbModelPainted;                                    // +0x4b2
    uint8_t pad4b3[0x4d8 - 0x4b3];
    bool* mpFlagArray;                                      // +0x4d8
    uint32_t pad4dc[(0x508 - 0x4dc) / 4];
    SlotEntry mSlots[6];                                    // +0x508

    void NotifyMessage(void* msg);                          // 0x010829f0 (empty, ret 4)
    int  GetSlotIndex();                                    // 0x00576140
    void SetupCameraUI();                                   // 0x00575f20
    void SetDirtyFlag(int index, bool value);               // 0x0057c530
    void SomeLoader();                                      // 0x00577dd0
    bool HasSkin();                                         // 0x00577620
    void FUN_00573970();                                    // 0x00573970
    void FUN_005724a0();                                    // 0x005724a0
    void SelectBlockAt(const ResourceKey* key, BlockRef* out, float x, float y, int flag);   // 0x0057d710
    void PurchaseBlock(cSPEditorBlock* block);              // 0x00574850
    void FillUndoState(cSPEditorUndoState* undo);           // 0x00574080
    void AddUndoState(bool a, cSPEditorUndoState* undo);    // 0x00586410
    bool HandlePaletteItemTriggerMessage(MsgPaletteItem* msg, uint32_t id);   // 0x00591690

    __forceinline void MarkEditing(int bit);
};

// Sets the editing flag (bit) in the global flag array and in the flag array of the current slot.
__forceinline void cAppModeEditorBase::MarkEditing(int bit)
{
    mpFlagArray[bit] = true;
    int idx = GetSlotIndex();
    if (idx < 6 && mLaunchData && mLaunchData->mbEnabled)
        mSlots[idx].mpFlags[bit] = true;
}

// @ 0x00591690
bool cAppModeEditorBase::HandlePaletteItemTriggerMessage(MsgPaletteItem* msg, uint32_t id)
{
    NotifyMessage(msg);

    switch (id) {
    case 0xeccc3657:
    {
    MarkEditing(0xc);

    switch (msg->mID) {
    case 0x17d37d90: {
        if (!mEditorModel)
            return true;
        if (!mCurrentPaintTheme)
            return true;
        int region = mpPaintPaletteUI ? mpPaintPaletteUI->GetSelectedRegion() : 0;
        mCurrentPaintTheme->ReadFromProp(msg->mKey.instanceID);
        if (region != -1) {
            cSPPaletteUI* ui = mpPaintPaletteUI;
            cSPPaletteCategoryUI* cat = ui->GetCategory(ui->FindCategoryIndex());
            if (cat && !cat->IsColor1Default()) {
                tSPEditorPaint paint = cat->GetSelectedPaint();
                mCurrentPaintTheme->SetRegionColor(paint.mColor1, region);
            }
        }
        mCurrentPaintTheme->WriteToProp(mEditorModel, region);
        mbModelPainted = true;
        AddUndoState(true, 0);
        SlotMessage m;
        m.Construct(0);
        m.mValue = msg->mKey.instanceID;
        m.mRegion = region;
        m.mFlags = 0;
        m.mMessageID = 0x5090434;
        MessageServer()->PostMSG(m.mMessageID, &m, 0);
        PlayUISound(0xb6da7093);
        PlayEditorSound(0x1d6253c0, 0x401b14c3, (float)++gEditorSoundCounter, 0);
        m.Destruct();
        return true;
    }

    case 0x674ab27: {
        if (!mEditorModel)
            return true;
        uint32_t source = SourceFromName(mEditorModel->mpName);
        ThemeRef theme(new("Editor", 0, 0, 0, 0) cSPEditorPaintTheme());
        theme.mpObject->SetSource(source);
        ResourceInfoRef info;
        if (cSPEditorPaintTheme::Apply(&msg->mKey, info.Reset(), 0)) {
            uint32_t hash = EA::Hash::FNV1_String16(info.mpObject->GetName(), 0x811c9dc5, 0);
            if (cSPEditorPaintTheme::ExtractSkinPaintData(source)) {
                theme.mpObject->ReadSkinThemeFromProp(info.mpObject, mField3c0, hash);
            } else if (cSPEditorPaintTheme::IsRegionSource(source)) {
                theme.mpObject->ExtractRegionPaintData(info.mpObject, mField3c0, hash);
            } else {
                return true;   // (dtors of info / theme run)
            }
            theme.mpObject->WriteToProp(mEditorModel, -1);
            mCurrentPaintTheme->ReadFromAsset(mEditorModel);
            mbModelPainted = true;
            UndoStateRef undo;
            undo = new("Editor", 0, 0, 0, 0) cSPEditorUndoState();
            cSPEditorUndoState* u = undo.mpObject;
            FillUndoState(u);
            const ResourceKey* src = &msg->mKey;
            u->mKey.instanceID = src->instanceID;
            u->mKey.typeID = src->typeID;
            u->mKey.groupID = src->groupID;
            u->mRegion = -1;
            u->mpMessage = msg;
            AddUndoState(false, u);
            if (mSkinManager && mSkinManager->GetSkin(1)) {
                cSPEditorSkinManager* save = mSaveSkinManager;
                cSPEditorModel* model = mEditorModel;
                if (!save || !save->IsBusy()) {
                    if (model && mSkinManager)
                        mSkinManager->RepaintModel(model);
                }
            }
            PlayUISound(0xb6da7093);
            PlayEditorSound(0x1d6253c0, 0x401b14c3, (float)++gEditorSoundCounter, 0);
        }
        return true;
    }

    case 0xbd110a25:
        PlayUISound(0x108a5376);
        PlayEditorSound(0x1d6253c0, 0x8b9ebc64, (float)++gEditorSoundCounter, 0);
        return true;

    case 0xdee3d8a8: {
        int categoryID = mpPaintPaletteUI ? mpPaintPaletteUI->GetSelectedCategoryID() : 0;
        if (!mEditorModel)
            return true;
        bool useColors = true;
        cSPPaletteUI* ui = mpPaintPaletteUI;
        cSPPaletteCategoryUI* cat = ui->GetCategory(ui->FindCategoryIndex());
        if (cat && !cat->IsColor1Default())
            useColors = false;
        uint32_t source = SourceFromName(mEditorModel->mpName);
        cSPEditorPaintTheme theme;
        theme.SetSource(source);
        if (theme.ReadFromProp2(msg->mKey.instanceID, useColors)) {
            theme.WriteToProp(mEditorModel, -1);
            mbModelPainted = true;
            AddUndoState(false, 0);
            cSPEditorSkinManager* save = mSaveSkinManager;
            cSPEditorModel* model = mEditorModel;
            if (!save || !save->IsBusy()) {
                if (model && mSkinManager)
                    mSkinManager->RepaintModel(model);
            }
            if (categoryID == -1) {
                for (int i = 0; i < 3; ++i) {
                    uint32_t effect = theme.mSkinEffects[i];
                    if (effect) {
                        SlotMessage m;
                        m.Construct(0);
                        m.mMessageID = 0x5090434;
                        m.mValue = effect;
                        m.mRegion = i;
                        m.mFlags = 0;
                        MessageServer()->PostMSG(m.mMessageID, &m, 0);
                        m.Destruct();
                    }
                }
            }
            PlayEditorSound(0x1d6253c0, 0xbd1e7359, (float)++gEditorSoundCounter, 0);
            cSPEditorAnimatedEventInfo* ev = new("Editor", 0, 0, 0, 0) cSPEditorAnimatedEventInfo();
            if (ev)
                ev->AddRef();
            ev->MessageSend(0x9e810fb3, 0, mEditorModel, 0, 0, 0.0f, 0, 0xffffffff, 1.0f);
            if (ev)
                ev->Release();
        }
        return true;
    }
    }
    return true;
    }
    case 0:
        switch (msg->mID) {
        case 0xc9db779b: {
            if (!GetRequirements()->GetRequirement(2, 0)->IsAvailable(1000))
                return false;
            SetDirtyFlag(0, true);
            SetupCameraUI();
            if (mPendingBlock.mpObject)
                return true;
            PropRef effect;
            if (PropertyManager()->GetPropertyList(msg->mKey.instanceID, msg->mKey.groupID, effect.AsPPTypeParam())) {
                ResourceKey key;
                key.instanceID = 0;
                key.typeID = 0;
                key.groupID = 0;
                if (GetPropertyAsKey(effect.mpObject, 0x22e8410, &key)) {
                    SelectBlockAt(&key, mPendingBlock.Reset(), mMouseX, mMouseY, 1);
                    SomeLoader();
                    if (HasSkin())
                        FUN_00573970();
                    FUN_005724a0();
                    bool r = PlaceFromCursor(1000, mMouseX, mMouseY, 0);
                    PurchaseBlock(mPendingBlock.mpObject);
                    if (effect.mpObject)
                        effect.mpObject->Release();
                    return r;
                }
            }
            if (effect.mpObject)
                effect.mpObject->Release();
            return true;
        }
        case 0xa2e50993: {
            if (!GetRequirements()->GetRequirement(2, 0)->IsAvailable(1000))
                return false;
            mpFlagArray[0] = true;
            int idx = GetSlotIndex();
            if (idx < 6 && mLaunchData && mLaunchData->mbEnabled)
                mSlots[idx].mpFlags[0] = true;
            SetupCameraUI();
            if (mPendingBlock.mpObject)
                return true;
            mPendingBlock.Clear();
            SelectBlockAt(&msg->mKey, &mPendingBlock, mMouseX, mMouseY, 0);
            if (!mPendingBlock.mpObject)
                return true;
            SomeLoader();
            if (HasSkin())
                FUN_00573970();
            FUN_005724a0();
            bool r = PlaceFromCursor(1000, mMouseX, mMouseY, 0);
            PurchaseBlock(mPendingBlock.mpObject);
            return r;
        }
        }
        return true;
    }
    return true;
}

}  // namespace SP
