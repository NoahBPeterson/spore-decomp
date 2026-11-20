// @ 0x00dba2f0
// Behaviour-tree action.  Six stack arguments (no this pointer): the owning object,
// three unused, the caller's behaviour_stimuli slot and a "found" flag.
//
// The owner's nearby-list object lives at owner+0xc0; its vtable slot 0x48 reports
// whether the list is usable, and FUN_00c420d0 returns its pointer list (+0x278
// inside that object).  The action then checks that the cVehicle noun range of the
// game-data vector (tag 0x18c6de8) is non-empty and takes the first neighbour that
// casts to the cVehicle type descriptor (0x137e8e0, vtable slot 0xb8).  On success
// it stores the vehicle's part object (its second base, at +0x508) in the stimuli
// slot (+4), sets the flag and returns 1.0f; otherwise 0.0f.


// Retail image references, use relocatable symbols rather than numeric addresses.
extern "C" unsigned char g_00ae72d0[];
extern "C" unsigned char g_00b1e500[];
extern "C" unsigned char g_00cd7d10[];
extern "C" unsigned char g_00d3d420[];
struct PointerList {
    void** mpBegin;     // +0
    void** mpEnd;       // +4
    void** mpCapacity;  // +8
};

// The game-data vector wrapper returned by the noun manager: its own pointer range
// starts at +4 (begin at +4, end at +8).
struct GameObjectRef {
    int         mTag;      // +0
    PointerList mObjects;  // +4
};

// What the action records is a subobject of the vehicle at +0x508, i.e. a base the
// cVehicle layout places after its 0x508-byte first part.  Spelling the store as a
// conversion to that base is what makes cl 15 emit `lea eax,[edi+0x508]` and keep
// edi free for its `pop`; a plain `(char*)vehicle + 0x508` makes it fold the add
// into edi (`add edi,0x508; mov [esi+4],edi`) instead.
struct cVehiclePartA {
    char mPad[0x508];
};
struct cVehiclePartB {
    void* mpRecorded;
};
struct cVehicleLayout : cVehiclePartA, cVehiclePartB {
};

typedef bool  (__thiscall* FnBoolVoid)(void*);
typedef void* (__thiscall* FnPtrInt)(void*, int);

// Calling a declared symbol through a __thiscall function-pointer type keeps the
// direct `call rel32` shape while putting the first argument in ecx.
#define TCS(ret, params, name) ((ret(__thiscall*)params) name)

// 0x00b3d300 - current game noun manager.
extern "C" void* FUN_00b3d300();
// 0x00b21340 - noun manager game-data vector (thiscall, callee pops five args).
extern "C" void* FUN_00b21340(void*, void*, void*, void*, void*, void*);
// 0x00c420d0 - the nearby-object pointer list of the object at owner+0xc0.
extern "C" void* FUN_00c420d0();
// 0x00d997e0 - behaviour_stimuli::GetAny.
extern "C" void* FUN_00d997e0();

// @ 0x00dba2f0
float FUN_00dba2f0(void* owner, void* unused2, void* unused3, void* unused4,
                   void* stimuli, unsigned char* found)
{
    char* self = (char*)owner + 0xc0;
    if (!((FnBoolVoid)((void**)*(void***)self)[0x48 / 4])(self))
        return 0.0f;

    void* nouns = FUN_00b3d300();
    GameObjectRef* data = (GameObjectRef*)TCS(void*, (void*, void*, void*, void*, void*, void*),
                                            FUN_00b21340)(
        nouns, (void*)g_00cd7d10, (void*)g_00d3d420, (void*)g_00ae72d0,
        (void*)g_00b1e500, (void*)0x18c6de8);
    PointerList* objects = &data->mObjects;
    if (objects->mpBegin == objects->mpEnd)
        return 0.0f;

    PointerList* list = (PointerList*)TCS(void*, (void*), FUN_00c420d0)(self);
    void** it = list->mpBegin;
    void** end = list->mpEnd;
    while (it != end) {
        void* obj = *it;
        void* vehicle = 0;
        if (obj)
            vehicle = ((FnPtrInt)((void**)*(void***)obj)[0xb8 / 4])(obj, 0x137e8e0);
        if (vehicle) {
            if (stimuli)
                TCS(void*, (void*), FUN_00d997e0)(stimuli);
            cVehiclePartB* part = (cVehiclePartB*)(cVehicleLayout*)vehicle;
            *(void**)((char*)stimuli + 4) = part;
            *found = 1;
            return 1.0f;
        }
        ++it;
    }
    return 0.0f;
}
