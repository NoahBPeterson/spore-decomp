// Model/ability property refresh, 0x0040D2D0.
// One large function, built unoptimized like its neighbours: /Od /Ob1 /MD /Gy /TP /arch:SSE.
// It publishes a number of computed values (sizes, damage totals, creature-type specific
// resource keys, ...) into the owner's property bag via vtable slot 5 (SetProperty).
// The source below is behaviorally equivalent to the original but NOT byte-exact: the original
// expands many inline helpers (property-variant constructors/destructors, vector sizes) whose
// exact original spelling is not recovered.

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;

// Variant-like temporary used when setting a property (16 bytes payload + flags word).
struct PropVal {
    unsigned char data[16];
    uint16_t flags;
    uint16_t type;
    PropVal() : flags(0), type(0) {}
};

struct PropInfo { char pad[0x12]; short typeId; };

// Property bag interface (vtable slots 1,5,7,9).
struct IPropertyBag {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void SetProperty(uint32_t id, void* val);          // +0x14
    virtual void v6();
    virtual bool HasProperty(uint32_t id);                      // +0x1c
    virtual void v8();
    virtual bool GetPropertyInfo(uint32_t id, PropInfo** out); // +0x24
};

struct IModelData { virtual int GetPartRoot(); };               // slot at +4

struct RangeVec { int* begin; int* end; };

struct KeyedFloat { uint32_t key; float value; };
struct KeyedFloatList { KeyedFloat* first; KeyedFloat* last; };

// Callees (calling conventions from the original).
bool __fastcall IsEditorMode(void* self);                                  // 0x526430
void __fastcall InitEmptyA(void* p);                                       // 0x409930
void __fastcall InitVecInline(void* p);                                    // 0x41f650
void __cdecl    LocalCleanup1();                                           // 0x472540
void __cdecl    LocalCleanup2();                                           // 0x4a9b10
void __cdecl    LocalCleanup3();                                           // 0x4ad330
void __fastcall FinishRefresh(void* self);                                 // 0x422360
void __fastcall WrapInt(void* p);                                          // 0x422eb0
void __cdecl    FreePropVal(int);                                          // 0x93db80
float* __cdecl  GetDefaultScale();                                         // 0x41ea70
void __cdecl    ApplyScale(float);                                         // 0x409b30
void __cdecl    WrapArray(int, int, void* base, int stride, int count);    // 0x93dd80
void __cdecl    InitBool(char*);                                           // 0x540470
void __fastcall CollectKeyedFloats(void* model, KeyedFloatList* out);      // 0x4333c0
void __fastcall WrapFloat(float* p);                                       // 0x428060
void __cdecl    FreeKeyedFloats();                                         // 0x45daf0
void __fastcall WrapPtr(void* p);                                          // 0x4279d0
int  __fastcall GetPartInfo(int part, void* tmp);                          // 0x41df50
void __cdecl    PostPart();                                                // 0x4237d0
void __fastcall WrapKey(void* p);                                          // 0x427fd0

extern int g_KeyA, g_KeyB, g_KeyC, g_KeyD, g_KeyE;  // 0x13eb2cc, 2d0, 2d4, 2c4, 2c8

void __fastcall RefreshProperties(char* self)
{
    int*  model = *(int**)(self + 0x334);
    void* flagsBlock = self + 0x234;
    void* editorBlock = self + 0x388;
    (void)flagsBlock;

    if (!IsEditorMode(editorBlock)) {
        char tmpA[0x40]; (void)tmpA;
        InitEmptyA(0); InitEmptyA(0);
        LocalCleanup1();
        LocalCleanup2();
    }

    IPropertyBag** bagPtr = (IPropertyBag**)(self + 0x434);
    if (*bagPtr == 0) {
        LocalCleanup3();
        FinishRefresh(self);
        return;
    }

    RangeVec* vecA = (RangeVec*)(self + 0x438);
    RangeVec* vecB = (RangeVec*)(self + 0x510);
    RangeVec* vecC = (RangeVec*)(self + 0x8a8);
    RangeVec* vecD = (RangeVec*)(self + 0x980);
    RangeVec* vecE = (RangeVec*)(self + 0xd18);
    int*      keyOrPtr = (int*)(self + 0xd70);
    void*     keyVal   = self + 0xd78;

    {
        PropVal v; v.type = 9; v.flags = 2;
        WrapInt(self + 0xd88);
        (*bagPtr)->SetProperty(0x7ff150b, &v);
        if (v.flags & 4) FreePropVal(0);
    }

    if (!IsEditorMode(editorBlock)) {
        float scale = 1.0f;
        bool haveScale;
        PropInfo* info;
        if (*bagPtr == 0 || !(*bagPtr)->GetPropertyInfo(0xfba611, &info) || info->typeId != 0xd) {
            haveScale = false;
        } else {
            scale = *GetDefaultScale();
            haveScale = true;
        }
        if (haveScale) {
            int n = (vecB->end - vecB->begin) / 14;
            for (int i = 0; i < n; i++) ApplyScale(*(int*)&scale);
        }
        PropVal p1, p2;
        WrapArray(0x20, 0x98, vecA->begin, 0xc, (vecA->end - vecA->begin) / 3);
        WrapArray(0x38, 0x98, vecB->begin, 0x38, (vecB->end - vecB->begin) / 14);
        (*bagPtr)->SetProperty(0x2a907b5, &p1);
        (*bagPtr)->SetProperty(0x2a907b6, &p2);
        if (p2.flags & 4) FreePropVal(0);
        if (p1.flags & 4) FreePropVal(0);
    }

    if (!IsEditorMode(editorBlock)) {
        float scale = 1.0f;
        bool haveScale;
        PropInfo* info;
        if (*bagPtr == 0 || !(*bagPtr)->GetPropertyInfo(0xfba611, &info) || info->typeId != 0xd) {
            haveScale = false;
        } else {
            scale = *GetDefaultScale();
            haveScale = true;
        }
        if (haveScale) {
            int n = (vecD->end - vecD->begin) / 14;
            for (int i = 0; i < n; i++) ApplyScale(*(int*)&scale);
        }
        PropVal a, b, c;
        WrapArray(0x20, 0x98, vecC->begin, 0xc, (vecC->end - vecC->begin) / 3);
        WrapArray(0x38, 0x98, vecD->begin, 0x38, (vecD->end - vecD->begin) / 14);
        WrapArray(9, 0x98, vecE->begin, 4, vecE->end - vecE->begin);
        (*bagPtr)->SetProperty(0xf1fae962, &a);
        (*bagPtr)->SetProperty(0xf1fae963, &b);
        (*bagPtr)->SetProperty(0x4caccce, &c);
        if (c.flags & 4) FreePropVal(0);
        if (b.flags & 4) FreePropVal(0);
        if (a.flags & 4) FreePropVal(0);
    }

    if ((*bagPtr)->HasProperty(0x720be500) && (*bagPtr)->HasProperty(0x720be501) &&
        (*bagPtr)->HasProperty(0x720be502)) {
        char dummy;
        InitBool(&dummy);
        KeyedFloatList list;
        CollectKeyedFloats(model, &list);
        float total = 0.0f;
        int count = list.last - list.first;
        for (int i = 0; i < count; i++) {
            float v = list.first[i].value * 0.1;
            uint32_t k = list.first[i].key;
            if (k < 0x11b78a72) {
                if (k == 0x11b78a71) {
                    PropVal pv; WrapFloat(&v);
                    (*bagPtr)->SetProperty(0x720be502, &pv);
                    if (pv.flags & 4) FreePropVal(0);
                } else if (k > 0x6329467) {
                    if (k < 0x632946b) { total += v; }
                    else if (k == 0x11b78a70) {
                        PropVal pv; WrapFloat(&v);
                        (*bagPtr)->SetProperty(0x720be500, &pv);
                        if (pv.flags & 4) FreePropVal(0);
                    }
                }
            } else if (k == 0x11b78a72) {
                total += v;
            }
        }
        PropVal pt; WrapFloat(&total);
        (*bagPtr)->SetProperty(0x720be501, &pt);
        if (pt.flags & 4) FreePropVal(0);
        FreeKeyedFloats();
    }

    int part = ((IModelData*)model)->GetPartRoot();
    if (part != 0) {
        char tmp[20];
        int info = GetPartInfo(part, tmp);
        PropVal pv; WrapPtr((void*)info);
        (*bagPtr)->SetProperty(0x43afa7e, &pv);
        if (pv.flags & 4) FreePropVal(0);
        PostPart();
    }

    int* keyPtr = keyOrPtr;
    if (*keyPtr != 0) {
        PropVal p1; WrapKey(keyPtr);
        (*bagPtr)->SetProperty(0x46d0560, &p1);
        if (p1.flags & 4) FreePropVal(0);
        PropVal p2; WrapFloat((float*)keyVal);
        (*bagPtr)->SetProperty(0x46d0572, &p2);
        if (p2.flags & 4) FreePropVal(0);
    } else {
        int one = 1;
        PropVal p;
        WrapInt(&one);
        (*bagPtr)->SetProperty(0x46d0572, &p);
        if (p.flags & 4) FreePropVal(0);

        int kind = model[0x16];
        int* which = 0;
        switch (kind) {
        case -0x43efbe1a: case -0x65282b56: case -0x3f48bd79: case -0x98f55bd:
        case 0x7d433fad:
            which = &g_KeyA; break;
        case -0x7069c235: case -0x3ea96a26: case 0x1f2a25b6: case 0x2a5147a9:
            which = &g_KeyB; break;
        case 0x1a4e0708: case -0x671fc3f3: case 0x441cd3e6: case 0x2090a11b:
        case 0x449c040f:
            which = &g_KeyC; break;
        }
        if (which) {
            PropVal pk; WrapKey(which);
            (*bagPtr)->SetProperty(0x46d0560, &pk);
            if (pk.flags & 4) FreePropVal(0);
        }
    }

    if (!(*bagPtr)->HasProperty(0x4a5b8d2)) {
        if (model[0x16] == 0x47c10953) {
            PropVal pv; WrapKey(&g_KeyD);
            (*bagPtr)->SetProperty(0x4a5b8d2, &pv);
            if (pv.flags & 4) FreePropVal(0);
        } else if (model[0x16] == 0x72c49181) {
            PropVal pv; WrapKey(&g_KeyE);
            (*bagPtr)->SetProperty(0x4a5b8d2, &pv);
            if (pv.flags & 4) FreePropVal(0);
        }
    }

    bool hasFlag = (*(uint16_t*)(self + 0x238) & 0x100) != 0;
    if (hasFlag) {
        int v1 = *(int*)(self + 0x10fc);
        PropVal pa; WrapInt(&v1);
        (*bagPtr)->SetProperty(0xafb4cda4, &pa);
        if (pa.flags & 4) FreePropVal(0);
        int v2 = *(int*)(self + 0x10f8);
        PropVal pb; WrapInt(&v2);
        (*bagPtr)->SetProperty(0x98e3be5, &pb);
        if (pb.flags & 4) FreePropVal(0);
    }

    LocalCleanup3();
    FinishRefresh(self);
}
