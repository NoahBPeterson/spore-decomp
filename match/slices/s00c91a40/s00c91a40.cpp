// s00c91a40 -- three __thiscall members of the space-stage tribe tool view
// (SP::cTribeToolView), recovered from 0x00c91a40, 0x00c91b60 and 0x00c91c80.
//
// Every field touched is named on a real class declaration.  The polymorphic
// sub-objects that the image dispatches through are modelled as classes whose
// virtual functions are declared in vtable order, so the `[eax+<slot>]`
// offsets in the original dispatch appear verbatim.  Only the slots this slice
// exercises are named; the same object's other unnamed virtuals are declared
// in order between them.
//
// Build flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int  u32;
typedef int           i32;
typedef float         f32;

// eastl containers used by the model list.  The image resolves the list-fill
// helper through this instantiation and calls it as a plain four-argument
// function (self, id, &count, &begin).
namespace eastl {
    class sp_vector_allocator {};

    template <class Elem, class Alloc>
    class vector {
    public:
        Elem *mBegin;         // first element
        u32   mCount;         // number of elements
        u32   mCapacity;      // allocated capacity
    };

    template <class Elem, class Alloc>
    bool reserve(vector<Elem, Alloc> *self, u32 id, u32 *count, Elem **begin);
}

// ---------------------------------------------------------------------------
// global tuning data
// ---------------------------------------------------------------------------
namespace SP {
    extern u8 DAT_01654c02;              // 0x01654c02  current-game-mode sentinel
}

// ---------------------------------------------------------------------------
// interfaces / classes
// ---------------------------------------------------------------------------
namespace SP {

class cTool;
class cMWModel;

// Reference-counted interface: slot 0x00 = AddRef, slot 0x04 = Release.
class cRefCounted {
public:
    virtual void AddRef(void);           // 0x00
    virtual void Release(void);          // 0x04
};

// Rendered-model object stored in the hut-model list; only its refcount
// interface matters to this slice.
class cMWModel : public cRefCounted {
public:
};

// Small intrusive smart pointer used by the model owner.
template <class T>
class AutoRefCount {
public:
    T *mPtr;
    AutoRefCount &operator=(T *p)
    {
        T *old = mPtr;
        if (p != old) {
            p->AddRef();
            mPtr = p;
            if (old != 0)
                old->Release();
        }
        return *this;
    }
};

// Polymorphic model object embedded at cTool+0x34.  The slots this slice uses
// are 0x94 (SetDesc), 0xa0 (SetWorld) and 0xac (GetOwner).
class cModel {
public:
    virtual void vm00(void); virtual void vm01(void); virtual void vm02(void);
    virtual void vm03(void); virtual void vm04(void); virtual void vm05(void);
    virtual void vm06(void); virtual void vm07(void); virtual void vm08(void);
    virtual void vm09(void); virtual void vm10(void); virtual void vm11(void);
    virtual void vm12(void); virtual void vm13(void); virtual void vm14(void);
    virtual void vm15(void); virtual void vm16(void); virtual void vm17(void);
    virtual void vm18(void); virtual void vm19(void); virtual void vm20(void);
    virtual void vm21(void); virtual void vm22(void); virtual void vm23(void);
    virtual void vm24(void); virtual void vm25(void); virtual void vm26(void);
    virtual void vm27(void); virtual void vm28(void); virtual void vm29(void);
    virtual void vm30(void); virtual void vm31(void); virtual void vm32(void);
    virtual void vm33(void); virtual void vm34(void); virtual void vm35(void);
    virtual void vm36(void);
    virtual void SetDesc(const void *desc);          // 0x94
    virtual void vm38(void); virtual void vm39(void);
    virtual void SetWorld(void *world);              // 0xa0
    virtual void vm41(void); virtual void vm42(void);
    virtual void *GetOwner(void);                    // 0xac
};

// Polymorphic definition object embedded at cTool+0x120; only slot 0x58
// (IsActive) is used here.
class cToolDef {
public:
    virtual void vd00(void); virtual void vd01(void); virtual void vd02(void);
    virtual void vd03(void); virtual void vd04(void); virtual void vd05(void);
    virtual void vd06(void); virtual void vd07(void); virtual void vd08(void);
    virtual void vd09(void); virtual void vd10(void); virtual void vd11(void);
    virtual void vd12(void); virtual void vd13(void); virtual void vd14(void);
    virtual void vd15(void); virtual void vd16(void); virtual void vd17(void);
    virtual void vd18(void); virtual void vd19(void); virtual void vd20(void);
    virtual void vd21(void);
    virtual bool IsActive(void);                     // 0x58
};

// The tool object returned by cTribe::GetToolOfType.
class cTool : public cRefCounted {
public:
    unsigned char pad_04[0x34 - 4];
    cModel        mModel;                // 0x34  the tool's rendered model
    unsigned char pad_38[0x120 - 0x38];
    cToolDef      mDef;                  // 0x120 the tool's definition

    void RefreshModel(void);             // 0x00c9d030  thiscall
    void UpdateTransform(void);          // 0x00c9dd50  thiscall
};

// The object returned by cModel::GetOwner(); it owns the currently-bound tool
// through an intrusive smart pointer at +0x64.
class cModelOwner {
public:
    unsigned char        pad_00[0x64];
    AutoRefCount<cTool>  mTool;          // 0x64  the tool currently bound to this model
};

// Flag object held by the view at +0x18cc.
class cHutModelState {
public:
    unsigned char pad_00[0x608];
    i32           m608;                  // 0x608
    i32           m60c;                  // 0x60c
};

// The property manager returned by SP::PropertyManager(); only slot 0x2c
// (Query) is exercised by this slice.
class cPropertyManager {
public:
    virtual void pm00(void); virtual void pm01(void); virtual void pm02(void);
    virtual void pm03(void); virtual void pm04(void); virtual void pm05(void);
    virtual void pm06(void); virtual void pm07(void); virtual void pm08(void);
    virtual void pm09(void); virtual void pm10(void);
    virtual bool Query(u32 a, u32 b, void *out);     // 0x2c
};

// The tool-view base: the tribe object the view is layered onto.
class cTribe {
public:
    cTool *GetToolOfType(int toolType);  // 0x00c8f6e0
    i32    GetModeVariant(void);         // 0x00a1ad10
    void   GetClosestWater(void);        // 0x00c8fe20
};

// The view object itself.  It carries the tool-definition sub-object at +0x120,
// the "water available" byte at +0x300, the cached water height at +0x310 and
// the hut-model state pointer at +0x18cc.
class cTribeToolView : public cTribe {
public:
    unsigned char pad_00[0x120];         // (the empty cTribe base occupies no bytes)
    cToolDef      mDef;                  // 0x120
    unsigned char pad_124[0x300 - 0x124];
    u8            m300;                  // 0x300  water-query dirty/valid byte
    unsigned char pad_301[0x310 - 0x301];
    f32           m310;                  // 0x310  closest-water / ground height
    unsigned char pad_314[0x18cc - 0x314];
    cHutModelState *m18cc;               // 0x18cc

    void UpdateModel(void);              // 0x00c91a40
    void *ChooseNewHutModel(void);       // 0x00c91b60
    f32  GetWaterOrHeight(void);         // 0x00c91c80
};

} // namespace SP

// free functions used by the routines
namespace SP {
    void  *GetCurrentGameMode(void);     // 0x00b5b800
    void  *GonzagoModelWorld(void);      // 0x00b3d520
    void  *PropertyManager(void);        // 0x0067de30
}

// property-set descriptor: the model id plus two tuning words
struct SP_ToolDesc {
    u32 id;
    u32 param0;
    u32 param1;
};

// ---------------------------------------------------------------------------
// @ 0x00c91a40
// ---------------------------------------------------------------------------
void SP::cTribeToolView::UpdateModel(void)
{
    cTool *pTool = GetToolOfType(10);

    SP_ToolDesc desc;
    desc.id     = 0x1ae006ab;
    desc.param0 = 0;
    desc.param1 = 0xf37c24e6;

    if (GetCurrentGameMode() != &DAT_01654c02) {
        switch (GetModeVariant()) {
        case 0: desc.id = 0x9ce9ce8c; break;
        case 1: desc.id = 0x9ce9ce8f; break;
        case 2: desc.id = 0x9ce9ce8e; break;
        }
    } else {
        switch (GetModeVariant()) {
        case 0: desc.id = 0x1ae006ab; break;
        case 1: desc.id = 0x1ae006a8; break;
        case 2: desc.id = 0x1ae006a9; break;
        }
    }

    cModel *pModel = &pTool->mModel;
    pModel->SetDesc(&desc);
    pModel->SetWorld(GonzagoModelWorld());

    if (pModel->GetOwner() != 0) {
        cModelOwner *pOwner = (cModelOwner *)pModel->GetOwner();
        pOwner->mTool = pTool;
    }

    pTool->RefreshModel();
    pTool->UpdateTransform();
}

// ---------------------------------------------------------------------------
// @ 0x00c91b60
// ---------------------------------------------------------------------------
void *SP::cTribeToolView::ChooseNewHutModel(void)
{
    if (!mDef.IsActive())
        return 0;

    // pick the hut-model id: a fully-built model beats a partially-built one
    u32 id;
    cHutModelState *pState = m18cc;
    if (pState != 0 && pState->m608 > 0 && pState->m60c > 0)
        id = 0x654e036;
    else if (pState != 0 && pState->m60c > 0)
        id = 0x654e034;
    else
        id = 0x654e035;

    // ask the property manager for the model list, then take the variant that
    // matches the current game mode
    SP::AutoRefCount<cMWModel> found;
    found.mPtr = 0;
    cPropertyManager *pm = (cPropertyManager *)PropertyManager();
    found = 0;
    if (pm->Query(0xc42e83f6, 0x2be764e2, &found)) {
        eastl::vector<SP::AutoRefCount<cMWModel>, eastl::sp_vector_allocator> list;
        u32 count = 0;
        if (eastl::reserve(&list, id, &count, &list.mBegin)) {
            i32 index = GetModeVariant() - 1;
            if (index < (i32)count) {
                SP::AutoRefCount<cMWModel> chosen = list.mBegin[index];
                found = 0;
                return chosen.mPtr;
            }
        }
    }
    found = 0;
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00c91c80
// ---------------------------------------------------------------------------
f32 SP::cTribeToolView::GetWaterOrHeight(void)
{
    if (m300 == 0)
        GetClosestWater();
    return m310;
}