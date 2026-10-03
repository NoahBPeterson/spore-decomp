// Slice s0040aeb0: one very large unoptimized (/Od /Ob1) editor member function.
// It processes one entry of the editor's part list (index at +0x10f4): resolves the part's
// model resource, appends rig-block/ability data into several editor vectors, and advances
// the index. The body is heavily inlined EASTL (ref-counted pointers, vectors), so this source is
// a structural, behaviour-oriented reconstruction, NOT byte-exact (see nonmatching.txt).
#include "types.h"

struct IRefCounted { virtual void AddRef() = 0; virtual void Release() = 0; };
struct IPropList {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8();
    virtual bool GetProperty(uint32_t id, void** outProp);   // slot 0x24
};
struct EditorPart {
    char pad0[0x10];
    struct PartModel* model;     // +0x10
    char pad1[4];
    struct IPartManager* mgr;    // +0x18
    char pad2[0xdcc - 0x1c];
    uint32_t flags;              // +0xdcc
};
struct PartModel {
    char pad[8];
    char name[8];                // +8 (key string)
    char pad1[0x90 - 0x10];
    IPropList* props;            // +0x90
};
struct IPartManager {   // slots used by the function (index = offset / 4)
    virtual void v0(); virtual void v1();
    virtual int  GetPartCount(PartModel*);                   // 0x84
    virtual void GetPartKeys(PartModel*, int* out);          // 0x90
    virtual void* CreateInstance(PartModel*, int arg);       // 0xa8
    virtual bool BuildKeys(PartModel*, void* vec, void* a, void* b, void* c); // 0x100
    virtual int  GetKeyType(PartModel*);                     // 0x108
};
struct IntVector { int* begin; int* end; int* cap; };

struct EditorState {
    char pad0[0x338];
    IntVector listA;             // +0x338
    char pad1[0xd84 - 0x344];
    int  totalCost;              // +0xd84
    int  firstFlag;              // +0xd88
    IntVector parts;             // +0xd8c
    char pad2[0x10f4 - 0xd98];
    uint32_t curIndex;           // +0x10f4
    int  counterA;               // +0x10f8
    int  counterB;               // +0x10fc

    void ProcessCurrentPart(void* arg);
    void ProcessSkipped(void* arg);       // FUN_0040d2d0
    void Finish();                        // FUN_00422280
};

// callees (addresses in comments)
extern bool IsEmptyVec(void* vec);                         // 0x526430
extern int  EntryCost(int key, int flag);                  // 0x71dd80
extern void ReleaseKey(int key);                           // 0x7387f0
extern void* AllocEditor(int size, const char* tag, int a, int b, int c, int d); // EASTL allocator
extern void LogStep();                                     // 0x472540
extern void LogEnd();                                      // 0x4a9b10


// @ 0x0040aeb0
void EditorState::ProcessCurrentPart(void* arg)
{
    if (curIndex >= (uint32_t)(parts.end - parts.begin)) {
        ProcessSkipped(arg);
        return;
    }

    EditorPart* part = (EditorPart*)parts.begin[curIndex];
    PartModel* model = part->model;
    IPartManager* mgr = part->mgr;

    bool enabled = true;
    if (model->props) {
        void* prop = 0;
        if (model->props->GetProperty(0x065fc9ab, &prop)) {
            // boolean property: disables the entry when set
            enabled = !*(char*)prop;
        }
    }
    (void)enabled;

    void* instance = mgr->CreateInstance(model, -1);
    (void)instance;

    IntVector keys = { 0, 0, 0 };
    int keyCost = 0;
    if (!IsEmptyVec(&keys))
        keyCost = EntryCost(keys.begin[0], 5);

    if (totalCost + keyCost <= 0x40) {
        if (curIndex == 0)
            firstFlag = 1;
        totalCost += keyCost;
    } else {
        for (int i = 0; i < (int)(keys.end - keys.begin); i++)
            ReleaseKey(keys.begin[i]);
    }

    LogStep();
    LogEnd();
    curIndex++;
    Finish();
}
