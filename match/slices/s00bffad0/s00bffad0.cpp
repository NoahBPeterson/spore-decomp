// Slice s00bffad0: Simulator::ISimulatorSerializable::func18h (VA 0x00bffad0, 2488 bytes).
// __thiscall, 5 stack args (ret 0x14). `this` is the serializable subobject. Sub-objects: A at
// this-0x108 (slot 0x4c = current id, slot 0x18 = send message), D at this-0xd4 (position and
// effect queries). VT(obj, byteOffset) selects the vtable slot; the offsets are taken from the asm.
#include "types.h"

#define VT(obj, off) ((*(void***)(obj))[(off) / 4])

typedef uint32_t (__thiscall *FnU32)(void*);
typedef uint32_t (__thiscall *FnU32_2)(void*, uint32_t, uint32_t);
typedef bool     (__thiscall *FnBool)(void*);
typedef bool     (__thiscall *FnBool_3)(void*, uint32_t, int, void**);
typedef float*   (__thiscall *FnPtr)(void*);
typedef float*   (__thiscall *FnPtr_2)(void*, float*, int);
typedef void     (__thiscall *FnVoid_1)(void*, void*);
typedef void     (__thiscall *FnVoid_1u)(void*, uint32_t);
typedef void     (__thiscall *FnVoid_Send)(void*, void*);
typedef int      (__thiscall *FnInt_1)(void*, uint32_t);
typedef void     (__thiscall *FnVoid_Start)(void*, int);
typedef void     (__thiscall *FnVoid_Rel)(void*);

// MessageBasicRC<5>: 0x3c bytes. Ctor 0x00421c80(id), dtor 0x00421cf0.
// u16 flags at +0 (|4 = position, |2 = matrix), u16 count at +2, then the 4-byte-aligned payload.
struct Msg5 {
    uint16_t flags;                 // +0
    uint16_t count;                 // +2
    uint32_t mRefValue;             // +4 (x)
    uint32_t mData0Lo;              // +8 (y)
    uint32_t mData0Hi;              // +0xc (z)
    uint32_t payload[9];            // +0x10 .. +0x30 (matrix copy starts at +0x10)
    uint32_t mId;                   // +0x34
    uint32_t pad38;                 // +0x38
};

// XformMsg (ctor 0x00434040), 0x38 bytes, used as the matrix/position message.
struct XformMsg {
    uint16_t flags;                 // +0
    uint16_t count;                 // +2
    float    pos[3];                // +4
    uint32_t pad[2];                // +0x10
    uint32_t mat[9];                // +0x18
    XformMsg();                     // 0x00434040
};

// AutoRefCount<EA::Swarm::cIVisualEffect> temporary (frame slot +0x18).
struct AutoEffect {
    void* mp;
    void** AsPPTypeParam();         // 0x00a16f40 (thiscall)
    ~AutoEffect();                  // vt+4 (Release) when mp != 0
};

// Free and member functions called from this body.
uint32_t SP_GetCurrentGameMode();                                       // 0x00b5b800
void*    SP_GetActivePlanet();                                          // 0x01021260
uint32_t SP_GetPlayerEmpireID();                                        // 0x01021090
void*    SP_NounManager();                                              // 0x00b3d300
void*    SP_RelationshipManager();                                      // 0x00b3d2c0
void*    SP_GameTimeManager();                                          // 0x00b3d380
void*    SP_EventLog(uint32_t, uint32_t, uint32_t);                     // 0x00b3d3e0
void*    SP_EffectsManager();                                           // 0x0067ddd0
void     SP_KillSetiEffects(uint32_t, uint32_t);                        // 0x00435ed0
void*    SP_GetServer();                                                // 0x00883860
float*   SP_NormalizedSafe(float* out, float* v);                       // 0x00449c20
float*   SP_Matrix3FromFacingAndUp(float* out, float* v);               // 0x0069b440
void     FUN_00bff2d0(void* self, uint32_t id, uint32_t mode);          // 0x00bff2d0, thiscall
void     FUN_00bfe450(void* self, uint32_t id, void* p);                // 0x00bfe450, thiscall
void*    FUN_00ae3350(void* p);                                         // 0x00ae3350, cdecl
int      FUN_00c70e00(void* planet);                                    // 0x00c70e00, thiscall
int      FUN_00b1f9d0(void* noun);                                      // 0x00b1f9d0, thiscall
void*    FUN_00b25fb0(void* noun);                                      // 0x00b25fb0, thiscall
void     FUN_00d06270(void* mgr, uint32_t a, uint32_t b, uint32_t c, float d);   // thiscall, ret 0x10
uint64_t FUN_00b316c0(void* gtm);                                       // thiscall
void*    FUN_00dd8640_log(void* log, uint32_t a, uint32_t b, void* c, uint32_t d, uint32_t e);   // thiscall, ret 0x18

struct Simulator_ISS {
    void func18h(float dt, uint32_t id, int kind, uint32_t p5, void* p6);
};

void Simulator_ISS::func18h(float dt, uint32_t id, int kind, uint32_t p5, void* p6)
{
    char* self = (char*)this;
    (void)p5;
    if (p6 != 0 && ((FnInt_1)VT(p6, 0x5c))(p6, 0xd0036e08) != 0) {
        return;
    }
    void* a = self - 0x108;
    if (((FnU32)VT(a, 0x4c))(a) == id) {
        return;
    }
    bool flag = false;
    if (kind != 0xc && kind != 10 && kind != 0x10 && kind != 4 && kind != 0xf) {
        flag = true;
    }
    float* pT = 0;
    if (p6 != 0) {
        pT = (float*)(size_t)((FnInt_1)VT(p6, 0x5c))(p6, 0x137e8e0);
    }
    if (!flag) {
        return;
    }
    if (SP_GetCurrentGameMode() == 0x1654c05) {
        void* planet = SP_GetActivePlanet();
        if (FUN_00c70e00(planet) != 4) {
            return;
        }
        if (id == SP_GetPlayerEmpireID()) {
            return;
        }
    }
    if (((FnU32)VT(a, 0x4c))(a) == id) {
        return;
    }
    if (SP_GetCurrentGameMode() != 0x1654c04) {
        goto LAB_00c00107;
    }
    if (id != 0xffffffff) {
        if (kind == 3) {
            void* mgr = SP_RelationshipManager();
            FUN_00d06270(mgr, ((FnU32)VT(a, 0x4c))(a), id, 0x526e504, 1.0f);
            if (pT != 0) {
                void* d = self - 0xd4;
                if (((FnBool)VT(d, 0x48))(d)) {
                    void* fx = SP_EffectsManager();
                    AutoEffect tmp; tmp.mp = 0;
                    if (((FnBool_3)VT(fx, 0x2c))(fx, 0xb817df5c, 0, tmp.AsPPTypeParam())) {
                        // TODO (partial): position/normal/matrix message build and the Send at
                        // VT(a,0x18), then Start(0) on tmp, Release, Restart of the timer at this+0x160.
                        float* dpos = ((FnPtr)VT(d, 0x2c))(d);
                        float* tpos = ((FnPtr)VT((char*)pT + 0x34, 0x2c))((char*)pT + 0x34);
                        (void)dpos; (void)tpos;
                    }
                    (void)tmp;
                }
            }
        } else {
            void* mgr = SP_RelationshipManager();
            FUN_00d06270(mgr, ((FnU32)VT(a, 0x4c))(a), id, 0x526e501, 1.0f);
        }
    }
LAB_00c00107:
    (void)dt;
    return;
}
