// match/slices/s00bce740/s00bce740.cpp
// Slice s00bce740 -- Simulator::cTurret serialization read path.
// Flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast

typedef unsigned int   u32;
typedef signed int     i32;
typedef unsigned char  u8;
typedef float          f32;

// ---------------------------------------------------------------------------
// Globals referenced by absolute address in the original.
// ---------------------------------------------------------------------------
extern "C" u8  g_156dc20;    // 0x0156dc20  serializer descriptor
extern "C" u8  g_1466ee4;    // 0x01466ee4  allocation tag
extern "C" u8  g_13ec458;    // 0x013ec458  base vtable stored by the ctor
extern "C" u8  g_1466c50;    // 0x01466c50  primary vtable of the new object
extern "C" u8  g_1475114;    // 0x01475114  second vtable of the new object
extern "C" f32 g_168b66c;    // 0x0168b66c
extern "C" f32 g_168b670;    // 0x0168b670
extern "C" f32 g_168b674;    // 0x0168b674

// ---------------------------------------------------------------------------
// External callees.
// ---------------------------------------------------------------------------
bool __cdecl EA_IO_ReadInt32(void* io, void* p, u32 count, i32 flags); // 0x0093a780
void* __cdecl EAAllocate(u32 size, const char* name, i32 a, i32 b,
                         const char* file, i32 line);                  // 0x00f473a0

struct GameDataPart {
    void Read(void* stream);                                   // 0x00b18600
};

// ---------------------------------------------------------------------------
// Stream access.  Slot 0x20 returns a sub object whose slot 0x18 yields the
// IO stream; slot 0x3c returns the save-format version.
// ---------------------------------------------------------------------------
struct StreamSub {
    void* GetIO()
    {
        return (**(void* (__thiscall**)(void*))(*(void***)this + 6))(this);
    }
};

struct StreamObj {
    StreamSub* GetSub()
    {
        return (**(StreamSub* (__thiscall**)(void*))(*(void***)this + 8))(this);
    }
    u32 GetVersion()
    {
        return (**(u32 (__thiscall**)(void*))(*(void***)this + 15))(this);
    }
};

// ---------------------------------------------------------------------------
// XML variable-list serializer (0xa14 bytes), same helper the road Read uses.
// ---------------------------------------------------------------------------
struct cVarListSerializer {
    u32 mData[0xa14 / 4];
    void Ctor(void* owner, void* desc, u32 tag);   // 0x00692f90
    bool Read(void* stream);                       // 0x00693e10
};

// ---------------------------------------------------------------------------
// The parts of cTurret touched by Read.
// ---------------------------------------------------------------------------
struct LocoPart {
    void* mVtbl;              // +0x00
    u8    pad[0x60];
    bool Read(void* stream);  // 0x00c43c10 (cLocomotiveObject::Read)
    void Slot94(void* p);     // vtable +0x94
    void SetLocomotion(void* loco); // 0x00c421b0
};

struct OldSpatialPart {
    void* mVtbl;
    u8    pad[0x60];
    bool Read(void* stream);  // 0x00c88b00 (cSpatialObject::Read)
};

struct CombatantPart {
    u8   pad[0x18];
    bool Read(void* stream);  // 0x00bfc540 (cCombatant::Read)
};

struct cTurret {
    u8             m00[0x34];
    LocoPart       mLoco;                 // +0x34
    u8             pad98[0xc4 - 0x98];
    u8             mC4[0x224 - 0xc4];     // +0xc4 .. +0x223
    u32            m224;                  // +0x224
    u8             pad228[0x588 - 0x228];
    CombatantPart  mCombat;               // +0x588

    bool Read(void* stream);
};

// The locomotion object created at the end of Read (0x24 bytes).
struct NewLoco {
    void* mVtbl;   // +0x00
    void* m04;     // +0x04
    void* m08;     // +0x08
    u32   m0c;     // +0x0c
    u32   m10;     // +0x10
    u32   m14;     // +0x14
    f32   x;       // +0x18
    f32   y;       // +0x1c
    f32   z;       // +0x20
};

// ---------------------------------------------------------------------------
// @ 0x00bce740
// ---------------------------------------------------------------------------
bool cTurret::Read(void* stream)
{
    StreamSub* sub = ((StreamObj*)stream)->GetSub();
    u32 tag;
    void* io = sub->GetIO();
    EA_IO_ReadInt32(io, &tag, 1, 0);

    ((GameDataPart*)this)->Read(stream);

    bool ok = ((((StreamObj*)stream)->GetVersion() < 0x1c0008)
                   ? ((OldSpatialPart*)&mLoco)->Read(stream)
                   : mLoco.Read(stream))
              && mCombat.Read(stream);

    cVarListSerializer ser;
    ser.Ctor(this, &g_156dc20, 0x1a80d26);

    ok = ok && ser.Read(stream);
    if (ok)
        ((void (__thiscall*)(LocoPart*, void*))\
            (*(void***)&mLoco)[0x94 / 4])(&mLoco, mC4);

    m224 = 5;
    NewLoco* loco = (NewLoco*)EAAllocate(0x24, (const char*)&g_1466ee4,
                                         0, 0, 0, 0);
    if (loco) {
        *(void* volatile*)&loco->m08 = &g_13ec458;
        loco->m0c = 0;
        loco->mVtbl = &g_1466c50;
        loco->m08 = &g_1475114;
        loco->m10 = 1;
        loco->m14 = 0;
        loco->x = g_168b66c;
        loco->y = g_168b670;
        loco->z = g_168b674;
    } else {
        loco = 0;
    }
    mLoco.SetLocomotion(loco);

    return ok;
}
