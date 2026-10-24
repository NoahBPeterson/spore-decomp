// spore-decomp slice s00c99140: tribe totem / grid / hut setup
// all functions below are annotated with their retail VA

// ---------------------------------------------------------------------------
// small shared models
// ---------------------------------------------------------------------------

struct Vec3 { float x, y, z; };

struct WString {
    wchar_t* mpBegin;   // +0x00
    wchar_t* mpEnd;     // +0x04
    wchar_t* mpCap;     // +0x08
    void __thiscall Assign(const WString& src);   // 0xb6f380
};

struct VtblObj { void* mpVtbl; };   // start of any object whose first dword is its vtable
struct RefObj  { void* mpVtbl; };   // refcounted object: slot 0 = AddRef, slot 4 = Release

// object whose vtable slot 0x94 takes one request pointer (used by the totem pole)
struct VObj94 {
    virtual void v000(); virtual void v004(); virtual void v008(); virtual void v00c();
    virtual void v010(); virtual void v014(); virtual void v018(); virtual void v01c();
    virtual void v020(); virtual void v024(); virtual void v028(); virtual void v02c();
    virtual void v030(); virtual void v034(); virtual void v038(); virtual void v03c();
    virtual void v040(); virtual void v044(); virtual void v048(); virtual void v04c();
    virtual void v050(); virtual void v054(); virtual void v058(); virtual void v05c();
    virtual void v060(); virtual void v064(); virtual void v068(); virtual void v06c();
    virtual void v070(); virtual void v074(); virtual void v078(); virtual void v07c();
    virtual void v080(); virtual void v084(); virtual void v088(); virtual void v08c();
    virtual void v090();
    virtual void OnRequest(void* req);        // +0x94
};

#define VSLOT(p, o) (*(void**)(*(char**)(p) + (o)))

typedef void   (__thiscall* TFnV)(void*);
typedef void*  (__thiscall* TFnP)(void*);
typedef int    (__thiscall* TFnI)(void*);
typedef float  (__thiscall* TFnF)(void*);
typedef char   (__thiscall* TFnC)(void*);
typedef void   (__thiscall* TFnVP)(void*, void*);
typedef void*  (__thiscall* TFnPP)(void*, void*);
typedef void*  (__thiscall* TFnPIP)(void*, int, void*);
typedef char   (__thiscall* TFnCIP)(void*, int, void*);
typedef void*  (__thiscall* TFnPI)(void*, int);
typedef void   (__thiscall* TFnVPP)(void*, void*, void*);
typedef void   (__thiscall* TFnVPPP)(void*, void*, void*, void*);
typedef char   (__thiscall* TFnCPPP)(void*, void*, void*, void*);
typedef void*  (__thiscall* TFnPFI)(void*, float, int);
typedef void   (__thiscall* TFnVPPPP)(void*, void*, void*, void*, void*);

// 0x58-byte body copied around inside the 0x60-byte tool-reference element
struct TribeToolBody {
    char mData[0x58];
    void __thiscall CopyFrom(const TribeToolBody& src);          // 0xc93dc0
    TribeToolBody& __thiscall operator=(const TribeToolBody& s); // 0xc95010
};

// element of cTribe's tool-reference vector (0x60 bytes)
struct TribeToolRef {
    void* mpVtbl;                // +0x00
    int   miUnk04;               // +0x04
    TribeToolBody mBody;         // +0x08
};

// 0x14-byte vector header (begin / end / cap / allocator words)
struct ToolVec {
    TribeToolRef* mpBegin;       // +0x00
    TribeToolRef* mpEnd;         // +0x04
    TribeToolRef* mpCap;         // +0x08
    void*         mpUnk0C;       // +0x0c
    void*         mpAllocator;   // +0x10
    void __thiscall InsertAt(TribeToolRef* pos, const TribeToolRef* val);
    TribeToolRef* __thiscall PushBackAt(TribeToolRef* pos, const TribeToolRef* val);
};

// action-circle slot (0x18 bytes)
struct ActionSlot {
    char  mPad00[0x0c];
    float mf0C;                  // +0x0c
    float mf10;                  // +0x10
    float mf14;                  // +0x14
    void __thiscall Clear();                 // 0xafa0a0
    void __thiscall Reserve(void* obj);      // 0xafa030
};

struct ActionCircle {
    char  mPad00[0x14];
    float mfRadius;              // +0x14
    float mf18;                  // +0x18
    float mf1C;                  // +0x1c
    char  mPad20[0x08];
    char  mb28;                  // +0x28
    char  mPad29[0x50 - 0x29];
    void __thiscall Clear();                          // 0xafaec0
    ActionSlot* __thiscall FindSlot(const Vec3* p);   // 0xafad70
    void __thiscall AssignSlot(ActionSlot* s);        // 0xafc410
};

struct TribeHut {
    char     mPad000[0x34];
    VtblObj  mSpatial;           // +0x34
    char     mPad038[0x120 - 0x38];
    struct {
        void* mpVtbl;
        void __thiscall SetHeight(float v);   // 0xf924e0
    } mQueue;                    // +0x120
    char     mPad124[0x14c - 0x124];
    float    mf14C;              // +0x14c
    void __thiscall RefreshModelProps();   // 0xc9c680
};

struct TribeTool {
    char          mPad000[0x34];
    VtblObj       mSpatial;      // +0x34
    char          mPad038[0xa5 - 0x38];
    unsigned char mbA5;          // +0xa5
};

struct cSpeciesProfile {
    char   mPad000[0x52c];
    void*  mp52C;                // +0x52c
    char   mPad530[0x608 - 0x530];
    unsigned mi608;              // +0x608
    unsigned mi60C;              // +0x60c
    void __thiscall GetUiName(WString* out);   // 0x4da330
};

struct RbTree {
    void** __thiscall find(void* key, void* out);   // 0xe5c780
};

struct ReservationGrid {
    char    mPad0000[0x984];
    ToolVec mEntries;            // +0x984
    char    mPad0998[0x1374 - 0x998];
    void* __thiscall GetReservedList();                                  // 0xcc7070
    void  __thiscall RemoveReservedByID(void* entries, const void* id);  // 0xcc86a0
    void  __thiscall AddReserved(void* entries, const Vec3* pos, float radius,
                                 const void* id);                        // 0xcc8350
    float __thiscall ComputeGridResolution(float a, float b);            // 0xcc7830
};

struct cPlanetModel {
    void* mpVtbl;
    float* __thiscall DirectionToSurfacePosition(Vec3* out, const Vec3* dir);   // 0xb815a0
    void   __thiscall BuildSurfaceOrientation(Vec3* out, const Vec3* a,
                                              const Vec3* b);                  // 0xb7f250
};

struct cGameNounManager {
    void* mpVtbl;
    void* __thiscall CreateNoun(unsigned type);        // 0xb20c60
    void  __thiscall AttachNoun(void* noun);           // 0xb1fe00
};

struct cPropertyManager {
    void* mpVtbl;
};

struct cTerraformingManager {
    void* mpVtbl;
    void __thiscall InitTerrain();                     // 0xbbc3f0
};

// object at the fixed address 0x1581208 that produces reservation parameters
struct cReserveParams {
    float __thiscall GetRadius(void* profile);         // 0xce6a40
    float __thiscall GetHeight(int index);             // 0xce6910
};

struct PtrList { void** mpBegin; void** mpEnd; };

struct cTribe {
    char     mPad0034[0x34];
    VtblObj  mObj34;             // +0x34
    char     mPad0038[0x120 - 0x38];
    VtblObj  mQueue120;          // +0x120
    char     mPad0124[0x230 - 0x124];
    WString  mName230;           // +0x230
    RbTree   mTree238;           // +0x238
    char     mPad023C[0x260 - 0x23c];
    TribeHut* mpHut260;          // +0x260
    float     mfRadius268;       // +0x268
    char      mPad026C[0x2d4 - 0x26c];
    RefObj*   mpTool2d4;         // +0x2d4
    char      mPad02D8[0x2e8 - 0x2d8];
    Vec3      mVec2e8;           // +0x2e8
    char      mPad02F4[0x368 - 0x2f4];
    TribeHut* mpHut368;          // +0x368
    char      mPad036C[0x3b4 - 0x36c];
    ActionCircle mCircle3b4;     // +0x3b4
    ActionSlot*  mpSlotsBegin;   // +0x404
    ActionSlot*  mpSlotsEnd;     // +0x408
    ActionSlot*  mpSlotsCap;     // +0x40c
    char         mPad0410[0x558 - 0x410];
    ReservationGrid mRGrid558;   // +0x558
    cSpeciesProfile* mpProfile18CC;  // +0x18cc
    char             mPad18D0[0x19c4 - 0x18d0];
    TribeTool* mpTool19C4;       // +0x19c4
    TribeTool* mpTool19C8;       // +0x19c8
    char       mPad19CC[0x19d0 - 0x19cc];
    TribeTool* mpTotem19D0;      // +0x19d0

    bool __thiscall SetupTotemPole();
    void __thiscall UpdateGridAndHutArea(int unused);
    void __thiscall ReserveToolsSlots(bool active);
    void __thiscall ChooseNewHutModel();
    void __thiscall NotifyToolSelection();
    TribeTool* __thiscall GetToolOfType(int type);      // 0xc8f6e0
    void __thiscall FinishTask(int task);               // 0xc987b0
    void __thiscall FUN_00c91700();                     // 0xc91700
    void __thiscall SetupChatAreas();                   // 0xc95af0
    void __thiscall PromoteChieftain(int level);        // 0xc8fd50
    void __thiscall InitDomesticatedAnimalsHerd();      // 0xc8fef0
};

// ---------------------------------------------------------------------------
// externals
// ---------------------------------------------------------------------------

extern "C" bool __cdecl GetPropertyAsVector3(void* propList, unsigned propId, Vec3* out);   // 0x6a1110
extern "C" float* __cdecl FUN_0059aed0(Vec3* a, Vec3* b, void* c);                          // 0x59aed0
extern "C" int __cdecl FUN_00a1ad10();                                                      // 0xa1ad10
extern "C" void* __cdecl FUN_00f473a0(int size, const char* file, int a, int b,
                                      const void* alloc, int line);                         // 0xf473a0
extern "C" void __cdecl FUN_00f47380(void* p);                                              // 0xf47380
extern "C" TribeToolRef* __cdecl FUN_00c943f0(TribeToolRef* a, TribeToolRef* b,
                                              TribeToolRef* c);                             // 0xc943f0
extern "C" void __cdecl FUN_00c92f80(TribeToolRef* a, TribeToolRef* b, TribeToolRef* c);    // 0xc92f80
extern "C" void __cdecl FUN_00c95ab0(TribeToolRef* a, TribeToolRef* b, TribeToolRef* c);    // 0xc95ab0
extern "C" char __cdecl FUN_006a0ae0(void* p, unsigned model, void* a, void* b);            // 0x6a0ae0
extern "C" cGameNounManager* __cdecl NounManager();                                         // 0xb3d300
extern "C" cPropertyManager* __cdecl PropertyManager();                                     // 0x67de30
extern "C" cTerraformingManager* __cdecl TerraformingManager();                             // 0xb3d430
extern "C" cPlanetModel* __cdecl PlanetModel();                                             // 0xb3d350
extern "C" unsigned __cdecl GetPlayerEmpireID();                                            // 0x1021090
struct cSPEditorSpeciesManager {
    cSpeciesProfile* __thiscall GetAvatarProfile();                                        // 0x4df420
};
extern "C" cSPEditorSpeciesManager* __cdecl GetSetting9();                                  // 0x401090

// ---------------------------------------------------------------------------
// code
// ---------------------------------------------------------------------------

// @ 0x00c99140
bool __thiscall cTribe::SetupTotemPole()
{
    if (this->mpTool2d4 == 0 || this->mpTotem19D0 != 0)
        return false;

    Vec3 pos;
    if (GetPropertyAsVector3(this->mpTool2d4, 0x55cea88, &pos)) {
        VtblObj* queue = &this->mQueue120;
        void* handle = ((TFnP)VSLOT(queue, 0x30))(queue);
        Vec3 dir;
        float* d = FUN_0059aed0(&dir, &pos, handle);
        dir.x = d[0];
        dir.y = d[1];
        dir.z = d[2];
        float* base = (float*)((TFnP)VSLOT(queue, 0x2c))(queue);
        pos.x = base[0] + dir.x;
        pos.y = base[1] + dir.y;
        pos.z = base[2] + dir.z;
    } else {
        VtblObj* spatial = &this->mpHut368->mSpatial;
        Vec3 scratch;
        float* d = (float*)((TFnPP)VSLOT(spatial, 0x5c))(spatial, &scratch);
        Vec3 off;
        off.x = d[0] * 20.0f;
        off.y = d[1] * 20.0f;
        off.z = d[2] * 20.0f;
        float* base = (float*)((TFnP)VSLOT(spatial, 0x2c))(spatial);
        pos.x = base[0] + off.x;
        pos.y = base[1] + off.y;
        pos.z = base[2] + off.z;
    }

    void* noun = NounManager()->CreateNoun(0x55cf865);
    if (noun != this->mpTotem19D0) {
        if (noun != 0)
            ((TFnV)VSLOT(noun, 0))(noun);
        TribeTool* old = this->mpTotem19D0;
        this->mpTotem19D0 = (TribeTool*)noun;
        if (old != 0)
            ((TFnV)VSLOT(old, 4))(old);
    }
    TribeTool* totem = this->mpTotem19D0;
    ((TFnVP)VSLOT(totem, 0x28))(totem, this);

    Vec3 surface;
    cPlanetModel* pm = PlanetModel();
    float* s = (float*)pm->DirectionToSurfacePosition(&surface, &pos);
    pos.x = s[0];
    pos.y = s[1];
    pos.z = s[2];
    ((TFnVP)VSLOT(&totem->mSpatial, 0x38))(&totem->mSpatial, &pos);

    VtblObj* hutSpatial = &this->mpHut368->mSpatial;
    Vec3 hutScratch;
    float* hd = (float*)((TFnPP)VSLOT(hutSpatial, 0x5c))(hutSpatial, &hutScratch);
    Vec3 neg;
    neg.x = -hd[0];
    neg.y = -hd[1];
    neg.z = -hd[2];
    Vec3 orient;
    Vec3 basis;
    pm = PlanetModel();
    pm->BuildSurfaceOrientation(&orient, &neg, &surface);
    ((TFnVP)VSLOT(&totem->mSpatial, 0x3c))(&totem->mSpatial, &orient);
    totem->mbA5 = 1;

    ReservationGrid* grid = &this->mRGrid558;
    grid->RemoveReservedByID(grid->GetReservedList(), (const void*)0x55cee70);
    grid->AddReserved(grid->GetReservedList(), &pos, *(float*)0x01470f1c,
                      (const void*)0x55cee70);

    this->FinishTask(0xd);
    return true;
}

// @ 0x00c993f0
void __thiscall ToolVec::InsertAt(TribeToolRef* pos, const TribeToolRef* val)
{
    if (this->mpEnd != this->mpCap) {
        if (pos <= val && val < this->mpEnd)
            val = (const TribeToolRef*)((char*)val + 0x60);

        TribeToolRef* end = this->mpEnd;
        if (end != 0) {
            TribeToolRef* prev = (TribeToolRef*)((char*)end - 0x60);
            end->mpVtbl = prev->mpVtbl;
            end->mBody.CopyFrom(prev->mBody);
        }
        FUN_00c95ab0(pos, (TribeToolRef*)((char*)this->mpEnd - 0x60), this->mpEnd);

        pos->mpVtbl = val->mpVtbl;
        pos->mBody = val->mBody;
        this->mpEnd = (TribeToolRef*)((char*)this->mpEnd + 0x60);
        return;
    }

    int count = (int)(this->mpEnd - this->mpBegin);
    int cap;
    TribeToolRef* buf;
    if (count == 0) {
        cap = 1;
        buf = (TribeToolRef*)FUN_00f473a0(cap * 0x60, "Simulator", 0, 0,
                                          (void*)0x13ebb38, 0xd1);
    } else {
        cap = count * 2;
        if (cap == 0)
            buf = 0;
        else
            buf = (TribeToolRef*)FUN_00f473a0(cap * 0x60, "Simulator", 0, 0,
                                              (void*)0x13ebb38, 0xd1);
    }

    TribeToolRef* begin = this->mpBegin;
    TribeToolRef* mid = FUN_00c943f0(begin, pos, buf);
    FUN_00c92f80(begin, pos, buf);
    if (mid != 0) {
        mid->mpVtbl = val->mpVtbl;
        mid->mBody.CopyFrom(val->mBody);
    }

    TribeToolRef* oldEnd = this->mpEnd;
    TribeToolRef* newEnd = FUN_00c943f0(pos, oldEnd, mid + 1);
    FUN_00c92f80(pos, oldEnd, mid + 1);

    if (this->mpBegin != 0 && this->mpBegin != (TribeToolRef*)this->mpAllocator)
        FUN_00f47380(this->mpBegin);
    this->mpBegin = buf;
    this->mpEnd = newEnd;
    this->mpCap = (TribeToolRef*)((char*)buf + cap * 0x60);
}

// @ 0x00c99550
void __thiscall cTribe::UpdateGridAndHutArea(int unused)
{
    cPropertyManager* mgr = PropertyManager();
    if (this->mpTool2d4 != 0) {
        RefObj* old = this->mpTool2d4;
        this->mpTool2d4 = 0;
        ((TFnV)VSLOT(old, 4))(old);
    }
    ((TFnVPPP)VSLOT(mgr, 0x2c))(mgr, (void*)0x535dc193, (void*)0x2be764e2,
                                &this->mpTool2d4);

    this->SetupChatAreas();
    float base = ((cReserveParams*)0x1581208)->GetRadius(this->mpProfile18CC);

    float scale;
    if (this->mpTool2d4 == 0) {
        scale = 1.5f;
    } else {
        void* prop = 0;
        char ok = ((TFnCIP)VSLOT(this->mpTool2d4, 0x24))(this->mpTool2d4, 0x1fb2b4e, &prop);
        if (ok == 0) {
            scale = 1.5f;
        } else {
            unsigned short type = *(unsigned short*)((char*)prop + 0x12);
            if (type == 0xd || type == 0x10) {
                if ((*(unsigned char*)((char*)prop + 0x10) & 0x30) == 0)
                    scale = *(float*)(-(int)(type != 0) & (int)prop);
                else
                    scale = *(float*)*(void**)prop;
            } else {
                scale = *(float*)0x015d9c6c;
            }
        }
    }

    float radius = scale * base * 2.0f;
    this->mfRadius268 = radius;
    ReservationGrid* grid = &this->mRGrid558;
    grid->ComputeGridResolution(radius, base);
    this->FinishTask(0xc);
    this->FinishTask(0xd);
    this->FUN_00c91700();

    Vec3 pos;
    if (this->mpHut368 != 0) {
        VtblObj* spatial = &this->mpHut368->mSpatial;
        float height = ((TFnF)VSLOT(spatial, 0x74))(spatial) + 3.0f;
        Vec3 scratch;
        float* d = (float*)((TFnPP)VSLOT(spatial, 0x5c))(spatial, &scratch);
        Vec3 off;
        off.x = d[0] * height;
        off.y = d[1] * height;
        off.z = d[2] * height;
        float* p = (float*)((TFnP)VSLOT(spatial, 0x2c))(spatial);
        pos.x = p[0] + off.x;
        pos.y = p[1] + off.y;
        pos.z = p[2] + off.z;
        grid->RemoveReservedByID(grid->GetReservedList(), (const void*)0x58cac6e);
        grid->AddReserved(grid->GetReservedList(), &pos, *(float*)0x0147b9f0,
                          (const void*)0x58cac6e);
    }

    if (this->mpTool19C4 != 0) {
        grid->RemoveReservedByID(grid->GetReservedList(), (const void*)0x55cee67);
        float rad = *(float*)0x01486110;
        VtblObj* obj = (VtblObj*)((char*)this->mpTool19C4 + 0x70);
        Vec3* p = (Vec3*)((TFnPFI)VSLOT(obj, 0x2c))(obj, rad, 0x55cee67);
        grid->AddReserved(grid->GetReservedList(), p, rad, (const void*)0x55cee67);
    }
    if (this->mpTool19C8 != 0) {
        grid->RemoveReservedByID(grid->GetReservedList(), (const void*)0x5b9a134);
        float rad = *(float*)0x01486110;
        VtblObj* obj = (VtblObj*)((char*)this->mpTool19C8 + 0x70);
        Vec3* p = (Vec3*)((TFnPFI)VSLOT(obj, 0x2c))(obj, rad, 0x5b9a134);
        grid->AddReserved(grid->GetReservedList(), p, rad, (const void*)0x5b9a134);
    }

    if (this->mpTotem19D0 != 0) {
        grid->RemoveReservedByID(grid->GetReservedList(), (const void*)0x55cee70);
        float rad = *(float*)0x01470f1c;
        VtblObj* obj = &this->mpTotem19D0->mSpatial;
        Vec3* p = (Vec3*)((TFnPFI)VSLOT(obj, 0x2c))(obj, rad, 0x55cee70);
        grid->AddReserved(grid->GetReservedList(), p, rad, (const void*)0x55cee70);
    }
}

// @ 0x00c99840
void __thiscall cTribe::NotifyToolSelection()
{
    unsigned req[3];
    req[0] = 0x093256ba;
    req[1] = 0;
    req[2] = 0xf37c24e6;

    switch (FUN_00a1ad10()) {
    case 0:
        req[0] = 0x093256ba;
        break;
    case 1:
        req[0] = 0x093256b9;
        break;
    case 2:
        req[0] = 0x093256b8;
        break;
    }

    TribeTool* totem = this->mpTotem19D0;
    ((VObj94*)&totem->mSpatial)->OnRequest(req);
    this->FinishTask(0xd);
}

// @ 0x00c998c0
void __thiscall cTribe::ReserveToolsSlots(bool active)
{
    ActionCircle* circle = &this->mCircle3b4;
    if (circle->mfRadius != *(float*)0x01695374 ||
        circle->mf18 != *(float*)0x01695378 ||
        circle->mf1C != *(float*)0x0169537c ||
        circle->mb28 != 0) {

        circle->Clear();
        int count = (int)(this->mpSlotsEnd - this->mpSlotsBegin);
        for (int i = 0; i < count; ++i)
            this->mpSlotsBegin[i].Clear();

        if (active != 0) {
            TribeTool* tool = this->GetToolOfType(10);
            VtblObj* spatial = &tool->mSpatial;
            float* p = (float*)((TFnP)VSLOT(spatial, 0x2c))(spatial);
            Vec3 pos;
            pos.x = p[0];
            pos.y = p[1];
            pos.z = p[2];
            ActionSlot* slot = circle->FindSlot(&pos);
            if (slot != 0) {
                slot->Reserve(tool);
                pos.x = slot->mf0C;
                pos.y = slot->mf10;
                pos.z = slot->mf14;
                circle->AssignSlot(slot);

                Vec3 scratch;
                float* d = (float*)((TFnPP)VSLOT(spatial, 0x5c))(spatial, &scratch);
                Vec3 orient;
                Vec3 basis;
                cPlanetModel* pm = PlanetModel();
                pm->BuildSurfaceOrientation(&orient, &pos, (const Vec3*)d);
                ((TFnVP)VSLOT(spatial, 0x38))(spatial, &orient);
                ((TFnVP)VSLOT(spatial, 0x3c))(spatial, &basis);
            }

            if (this->mpHut260 != 0) {
                VtblObj* hutSpatial = &this->mpHut260->mSpatial;
                float* hp = (float*)((TFnP)VSLOT(hutSpatial, 0x2c))(hutSpatial);
                pos.x = hp[0];
                pos.y = hp[1];
                pos.z = hp[2];
                ActionSlot* hutSlot = circle->FindSlot(&pos);
                if (hutSlot != 0) {
                    pos.x = hutSlot->mf0C;
                    pos.y = hutSlot->mf10;
                    pos.z = hutSlot->mf14;
                    circle->AssignSlot(hutSlot);
                }

                VtblObj* dirObj = &this->mpHut368->mSpatial;
                Vec3 scratch2;
                float* hd = (float*)((TFnPP)VSLOT(dirObj, 0x5c))(dirObj, &scratch2);
                Vec3 neg;
                neg.x = -hd[0];
                neg.y = -hd[1];
                neg.z = -hd[2];
                Vec3 orient2;
                Vec3 basis2;
                cPlanetModel* pm2 = PlanetModel();
                pm2->BuildSurfaceOrientation(&orient2, &pos, &neg);
                ((TFnVP)VSLOT(hutSpatial, 0x38))(hutSpatial, &orient2);
                ((TFnVP)VSLOT(hutSpatial, 0x3c))(hutSpatial, &basis2);
                this->FinishTask(0xd);
                this->mVec2e8 = pos;
            }
        }

        PtrList* list = (PtrList*)((TFnP)VSLOT(this, 0xbc))(this);
        void** it = list->mpBegin;
        void** end = list->mpEnd;
        while (it != end) {
            void* obj = *it;
            if (obj != 0 && ((TFnI)VSLOT(obj, 0x58))(obj) != 10) {
                VtblObj* objSpatial = (VtblObj*)((char*)obj + 0x34);
                float* p = (float*)((TFnP)VSLOT(objSpatial, 0x2c))(objSpatial);
                Vec3 pos2;
                pos2.x = p[0];
                pos2.y = p[1];
                pos2.z = p[2];
                ActionSlot* slot = circle->FindSlot(&pos2);
                if (slot != 0) {
                    slot->Reserve(obj);
                    pos2.x = slot->mf0C;
                    pos2.y = slot->mf10;
                    pos2.z = slot->mf14;
                }
                Vec3 scratch3;
                float* d = (float*)((TFnPP)VSLOT(objSpatial, 0x5c))(objSpatial, &scratch3);
                Vec3 orient;
                Vec3 basis;
                cPlanetModel* pm = PlanetModel();
                pm->BuildSurfaceOrientation(&orient, &pos2, (const Vec3*)d);
                ((TFnVP)VSLOT(objSpatial, 0x38))(objSpatial, &orient);
                ((TFnVP)VSLOT(objSpatial, 0x3c))(objSpatial, &basis);
            }
            ++it;
        }
    }
}

// @ 0x00c99c30
void __thiscall cTribe::ChooseNewHutModel()
{
    unsigned model;
    if (((TFnC)VSLOT(&this->mQueue120, 0x58))(&this->mQueue120) == 0) {
        model = 0x653f6b9;
    } else {
        cSpeciesProfile* profile = this->mpProfile18CC;
        bool hasFirst = false;
        if (profile != 0)
            hasFirst = profile->mi608 > 0;
        if (hasFirst) {
            bool hasSecond = false;
            if (profile != 0)
                hasSecond = profile->mi60C > 0;
            if (hasSecond) {
                model = 0x653f6b8;
                goto selected;
            }
        }
        {
            bool hasSecond = false;
            if (profile != 0)
                hasSecond = profile->mi60C > 0;
            if (hasSecond)
                model = 0x653f6b6;
            else
                model = 0x653f6b7;
        }
    }
selected:
    RefObj* modelRef = 0;
    cPropertyManager* mgr = PropertyManager();
    char got = ((TFnCPPP)VSLOT(mgr, 0x2c))(mgr, (void*)0xc42e83f6, (void*)0x2be764e2,
                                           &modelRef);
    if (got != 0) {
        void* vecBase = 0;
        void* other = 0;
        char reserved = FUN_006a0ae0(modelRef, model, &vecBase, &other);
        if (reserved != 0) {
            int index = FUN_00a1ad10();
            float* sel = (float*)((char*)vecBase + index * 0xc);
            Vec3 v;
            v.x = sel[0];
            v.y = sel[1];
            v.z = sel[2];
            TribeHut* hut = this->mpHut368;
            ((TFnVP)VSLOT(&hut->mSpatial, 0x94))(&hut->mSpatial, &v);
            hut->RefreshModelProps();
            hut->mf14C = ((cReserveParams*)0x1581208)->GetHeight(index);
            float h = ((TFnF)VSLOT(&hut->mQueue, 0x58))(&hut->mQueue);
            hut->mQueue.SetHeight(h);
        }
    }
    this->FinishTask(0xc);
    if (modelRef != 0)
        ((TFnV)VSLOT(modelRef, 4))(modelRef);
}

// @ 0x00c99dc0
cTribe* __cdecl CreatePlayerTribe(int a, int b, int c, cSpeciesProfile* profile)
{
    if (profile == 0) {
        profile = GetSetting9()->GetAvatarProfile();
    }

    void* noun = NounManager()->CreateNoun(0x18c6d19);
    cTribe* tribe;
    if (noun == 0)
        tribe = 0;
    else
        tribe = (cTribe*)((TFnPI)VSLOT(noun, 0x0c))(noun, 0x4f396a66);

    NounManager()->AttachNoun(tribe);
    ((TFnVP)VSLOT(tribe, 0x48))(tribe, (void*)GetPlayerEmpireID());
    ((TFnV)VSLOT(tribe, 0xa8))(tribe);

    tribe->mpProfile18CC = profile;
    ((TFnVPPPP)VSLOT(tribe, 0x8c))(tribe, (void*)a, (void*)b, (void*)c, (void*)1);

    WString name;
    name.mpBegin = (wchar_t*)0x01667bac;
    name.mpEnd = (wchar_t*)0x01667bac;
    name.mpCap = (wchar_t*)0x01667bae;
    profile->GetUiName(&name);
    tribe->mName230.Assign(name);

    unsigned key = 0xe;
    void* node = 0;
    void** it = tribe->mTree238.find(&key, &node);
    unsigned value = *(unsigned*)((char*)*it + 0x14);
    ((TFnVP)VSLOT(&tribe->mObj34, 0x00))(&tribe->mObj34, (void*)value);
    ((TFnVP)VSLOT(&tribe->mObj34, 0x08))(&tribe->mObj34, profile->mp52C);

    TerraformingManager()->InitTerrain();
    tribe->PromoteChieftain(0);
    tribe->InitDomesticatedAnimalsHerd();
    tribe->SetupTotemPole();

    void* hut = ((TFnP)VSLOT(tribe, 0xac))(tribe);
    if (hut != 0) {
        hut = ((TFnP)VSLOT(tribe, 0xac))(tribe);
        VtblObj* spatial = (VtblObj*)((char*)hut + 0x34);
        float height = ((TFnF)VSLOT(spatial, 0x74))(spatial) + 3.0f;
        Vec3 scratch;
        float* d = (float*)((TFnPP)VSLOT(spatial, 0x5c))(spatial, &scratch);
        Vec3 off;
        off.x = d[0] * height;
        off.y = d[1] * height;
        off.z = d[2] * height;
        float* p = (float*)((TFnP)VSLOT(spatial, 0x2c))(spatial);
        Vec3 pos;
        pos.x = p[0] + off.x;
        pos.y = p[1] + off.y;
        pos.z = p[2] + off.z;
        ReservationGrid* grid = &tribe->mRGrid558;
        grid->RemoveReservedByID(grid->GetReservedList(), (const void*)0x58cac6e);
        grid->AddReserved(grid->GetReservedList(), &pos, *(float*)0x0147b9f0,
                          (const void*)0x58cac6e);
    }

    if (((unsigned)name.mpCap - (unsigned)name.mpBegin & 0xfffffffe) > 2 &&
        name.mpBegin != 0)
        FUN_00f47380(name.mpBegin);

    return tribe;
}

// @ 0x00c9a000
TribeToolRef* __thiscall ToolVec::PushBackAt(TribeToolRef* pos, const TribeToolRef* val)
{
    int index = (int)(pos - this->mpBegin);
    if (pos == this->mpEnd && this->mpEnd != this->mpCap) {
        TribeToolRef* end = this->mpEnd;
        this->mpEnd = end + 1;
        if (end != 0) {
            end->mpVtbl = val->mpVtbl;
            end->mBody.CopyFrom(val->mBody);
        }
        return (TribeToolRef*)((char*)this->mpBegin + index * 0x60);
    }
    this->InsertAt(pos, val);
    return (TribeToolRef*)((char*)this->mpBegin + index * 0x60);
}
