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

// =============================================================================================
// Retail 0xc004a0..0xc00ad0: the app-mode / attack-timer helpers and the shared four-byte id
// table (0x0168d228), used by the community and simulator code.
// =============================================================================================

extern uint32_t g_168d248;              // 0x0168d248  application mode (0..4)
extern uint32_t g_168d228[8];           // 0x0168d228  cached four-byte ids, seven entries used

void  SP_Eapd_sys_gui();                // 0x00c2e4e0  empty in this build
void* SP_PropertyManager();             // 0x0067de30
extern "C" void EA_IO_WriteUint32(void* stream, const uint32_t& value, int count, int flags); // 0x0093aa70
extern char DAT_015710b8;               // 0x015710b8  cVarList descriptor passed to the serializer

struct cGameTimeMgr {                   // 0x00b316c0  Ticks() (thiscall, returns edx:eax)
    uint64_t Ticks();
};

typedef void* (__thiscall *FnVp)(void*);
typedef bool  (__thiscall *FnBool2)(void*, uint32_t, void**);
typedef bool  (__thiscall *FnGetProps)(void*, uint32_t, int, void**);

// cProperty: the property-manager object; the type tag used here lives at +0x12.
struct cProperty {
    uint8_t  mPad0[0xc];                // +0 is the vtable pointer
    uint16_t mFlags;                    // 0x10
    uint16_t mType;                     // 0x12
    virtual int AddRef();
    virtual int Release();              // vtable slot 1 (+4)
    const char* GetString8();           // 0x0041e990
};

// EA::AutoRefCount<T>: the members this slice exercises.
template <class T>
struct AutoRef {
    T* mp;
    AutoRef() : mp(0) {}
    void Reset() { if (mp) { T* p = mp; mp = 0; p->Release(); } }
    void** AsPPTypeParam() { Reset(); return (void**)&mp; }
    ~AutoRef() { if (mp) mp->Release(); }
};

// 0x009692f90 is the cVarListSerializer constructor; 0x00692900 its Serialize.
struct cVarListSerializer {
    uint8_t mData[0xa14];
    cVarListSerializer(void* object, const void* descriptor, uint32_t classId);
    void Serialize(void* stream);
};

// ---------------------------------------------------------------------------------------------
// 0x00c004a0 -- notify the audio GUI when the app is in mode 4 (and not in the transient modes).
// ---------------------------------------------------------------------------------------------
// @ 0x00c004a0
void FUN_00c004a0()
{
    if (g_168d248 != 2 && g_168d248 != 1 && g_168d248 == 4) {
        SP_Eapd_sys_gui();
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00c004c0 -- true when stamp[idx] is between 0 and 20000 ticks behind the current game time.
// ---------------------------------------------------------------------------------------------
// @ 0x00c004c0
bool __fastcall FUN_00c004c0(void* ecx_this, void* edx, int idx)
{
    uint64_t now = ((cGameTimeMgr*)SP_GameTimeManager())->Ticks();
    return now > 20000 && now - ((uint64_t*)((char*)ecx_this + 0x98))[idx] < 20000;
}

// ---------------------------------------------------------------------------------------------
// 0x00c00510 -- clear one of the three attack timestamps.
// ---------------------------------------------------------------------------------------------
// @ 0x00c00510
void __fastcall FUN_00c00510(void* ecx_this, void* edx, int idx)
{
    ((uint64_t*)((char*)ecx_this + 0x98))[idx] = 0;
}

// ---------------------------------------------------------------------------------------------
// 0x00c00590 -- cCommunity::GetInhabitantCount: size of the inhabitant vector (slot 28).
// ---------------------------------------------------------------------------------------------
// @ 0x00c00590
int __fastcall FUN_00c00590(void* ecx_this, void* edx)
{
    int* v = (int*)((FnVp)VT(ecx_this, 0x70))(ecx_this);
    return (v[1] - v[0]) >> 2;
}

// ---------------------------------------------------------------------------------------------
// 0x00c005b0 -- Write: stamp the object's interface id, drop the cached COM pointer, then let
// the cVarList serializer write the property list.
// ---------------------------------------------------------------------------------------------
// @ 0x00c005b0
void __fastcall FUN_00c005b0(void* ecx_this, void* edx, void* stream)
{
    void* iface = ((FnVp)VT(stream, 0x20))(stream);
    uint32_t tag = 0x17f243b;
    void* io = ((FnVp)VT(iface, 0x18))(iface);
    EA_IO_WriteUint32(io, tag, 1, 0);

    void* p = *(void**)((char*)ecx_this + 0x11c);
    if (p != 0 && ((FnBool)VT(p, 0x2c))(p)) {
        p = *(void**)((char*)ecx_this + 0x11c);
        if (p != 0) {
            *(void**)((char*)ecx_this + 0x11c) = 0;
            ((FnVoid_Rel)VT(p, 4))(p);
        }
    }

    cVarListSerializer ser(ecx_this, &DAT_015710b8, 0x1a80d26);
    ser.Serialize(stream);
}

// ---------------------------------------------------------------------------------------------
// 0x00c00850 -- copy 32-byte elements into newly allocated raw storage.
// ---------------------------------------------------------------------------------------------
struct Elem20 {
    float f0, f1, f2, f3, f4, f5, f6;
    uint32_t u;
};

// @ 0x00c00850
void FUN_00c00850(Elem20* first, Elem20* last, Elem20* dst)
{
    for (; first != last; ++first, ++dst) {
        if (dst) {
            dst->f0 = first->f0;
            dst->f1 = first->f1;
            dst->f2 = first->f2;
            dst->f3 = first->f3;
            dst->f4 = first->f4;
            dst->f5 = first->f5;
            dst->f6 = first->f6;
            dst->u = first->u;
        }
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00c008c0 -- fill the cached four-byte id table from the property list, once.
// ---------------------------------------------------------------------------------------------
// @ 0x00c008c0
void FUN_00c008c0(uint32_t* out)
{
    void* val;
    if (out[0] != 0) {
        return;
    }
    AutoRef<cProperty> prop;
    void* pm = SP_PropertyManager();
    if (((FnGetProps)VT(pm, 0x2c))(pm, 0x16d4dff8, 0, prop.AsPPTypeParam())) {
        if (!prop.mp) return;
        if (((FnBool2)VT(prop.mp, 0x24))(prop.mp, 0x1905e43, &val) &&
            ((cProperty*)val)->mType == 9)
            out[0] = *(const uint32_t*)((cProperty*)val)->GetString8();
        if (!prop.mp) return;
        if (((FnBool2)VT(prop.mp, 0x24))(prop.mp, 0x1905e44, &val) &&
            ((cProperty*)val)->mType == 9)
            out[1] = *(const uint32_t*)((cProperty*)val)->GetString8();
        if (!prop.mp) return;
        if (((FnBool2)VT(prop.mp, 0x24))(prop.mp, 0x1905e45, &val) &&
            ((cProperty*)val)->mType == 9)
            out[2] = *(const uint32_t*)((cProperty*)val)->GetString8();
        if (!prop.mp) return;
        if (((FnBool2)VT(prop.mp, 0x24))(prop.mp, 0x1905e46, &val) &&
            ((cProperty*)val)->mType == 9)
            out[3] = *(const uint32_t*)((cProperty*)val)->GetString8();
        if (!prop.mp) return;
        if (((FnBool2)VT(prop.mp, 0x24))(prop.mp, 0x1905e47, &val) &&
            ((cProperty*)val)->mType == 9)
            out[4] = *(const uint32_t*)((cProperty*)val)->GetString8();
        if (!prop.mp) return;
        if (((FnBool2)VT(prop.mp, 0x24))(prop.mp, 0x1905e48, &val) &&
            ((cProperty*)val)->mType == 9)
            out[5] = *(const uint32_t*)((cProperty*)val)->GetString8();
        if (!prop.mp) return;
        if (((FnBool2)VT(prop.mp, 0x24))(prop.mp, 0x1905e49, &val) &&
            ((cProperty*)val)->mType == 9)
            out[6] = *(const uint32_t*)((cProperty*)val)->GetString8();
    }
}

// ---------------------------------------------------------------------------------------------
// 0x00c00aa0 -- index of the first cached id that is >= value (0 when none is).
// ---------------------------------------------------------------------------------------------
// @ 0x00c00aa0
int FUN_00c00aa0(int value)
{
    FUN_00c008c0(g_168d228);
    for (int i = 0; i < 7; ++i) {
        if (value <= (int)g_168d228[i]) {
            return i;
        }
    }
    return 0;
}

// ---------------------------------------------------------------------------------------------
// 0x00c00ad0 -- cached id by index (0 for an out-of-range index).
// ---------------------------------------------------------------------------------------------
// @ 0x00c00ad0
uint32_t FUN_00c00ad0(int index)
{
    if (index < 8) {
        FUN_00c008c0(g_168d228);
        return g_168d228[index];
    }
    return 0;
}
