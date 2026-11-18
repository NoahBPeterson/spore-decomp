// Slice s00c43c10 -- SP::cLocomotiveObject::Read(SP::cIObjectDatabaseIStream &).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
//
// Reads the class version dword from the database's IO stream, chains to
// SP::cSpatialObject::Read, serializes the variable list through
// SP::cVarListSerializer (signature 0x1a80d26) and finally refreshes the
// refcounted object kept at +0x4cc:
//   if (new != old) { if (new) new->AddRef(); old_member = new; if (old) old->Release(); }
// +0x4cc is the same field the neighbouring SP::cLocomotiveObject::Shutdown
// (0x00c43f90) releases through vtable slot 1.
#include "types.h"

namespace SP {

struct IOStream;

// cVarListSerializer is 0xa14 bytes (SP/cVarListSerializer.h); only its
// storage is needed here, the constructor/Serialize calls are external.
struct cVarListSerializer {
    uint32_t mStorage[0xa14 / 4];   // not a char array: a byte array would arm /GS
};

// Refcounted object stored at +0x4cc (AddRef slot 0, Release slot 1).
struct cRefCounted {
    virtual int AddRef();
    virtual int Release();
};

// cIObjectDatabaseIStream: slot 8 (+0x20) hands out the database, whose
// slot 6 (+0x18) hands out the underlying EA::IO stream.
struct cObjectDatabase;
struct cObjectDatabaseVt {
    virtual void vf00(); virtual void vf04();
    virtual void vf08(); virtual void vf0c();
    virtual void vf10(); virtual void vf14();
    virtual IOStream* GetStream();                                 // slot 6, +0x18
};

struct cObjectDatabase : cObjectDatabaseVt {};

struct cIObjectDatabaseIStream {
    virtual void vf00(); virtual void vf04();
    virtual void vf08(); virtual void vf0c();
    virtual void vf10(); virtual void vf14();
    virtual void vf18(); virtual void vf1c();
    virtual cObjectDatabase* GetDatabase();                        // slot 8, +0x20
};

struct cLocomotiveObject {
    uint32_t mPad00[0x4cc / 4];                                    // +0x00 .. +0x4cb
    cRefCounted* mpRef4cc;                                         // +0x4cc

    bool Read(cIObjectDatabaseIStream& stream);
};

// ---- retail callees (call targets are address-masked by the fingerprint) ----
bool __cdecl ReadInt32(void* pStream, int32_t* pValue, unsigned int count, int endian); // 0x93a780
void FUN_00c88b00();                                               // 0xc88b00 cSpatialObject::Read (this, stream)
void FUN_00692f90();                                               // 0x692f90 cVarListSerializer ctor (this, obj, data, sig)
bool FUN_00693e10();                                               // 0x693e10 cVarListSerializer::Serialize (this, stream)
void* __cdecl FUN_00b3d310();                                      // 0xb3d310
void* __cdecl FUN_00c14350();                                      // 0xc14350 (context arrives in ecx)

// @ 0x00c43c10
bool cLocomotiveObject::Read(cIObjectDatabaseIStream& stream)
{
    int version;
    IOStream* pStream = stream.GetDatabase()->GetStream();
    ReadInt32(pStream, &version, 1, 0);

    ((void (__thiscall*)(cLocomotiveObject*, cIObjectDatabaseIStream*))FUN_00c88b00)(this, &stream);

    cVarListSerializer serializer;
    ((void (__thiscall*)(cVarListSerializer*, void*, void*, unsigned int))FUN_00692f90)(
        &serializer, this, (void*)0x1574258, 0x1a80d26u);

    bool ok = ((bool (__thiscall*)(cVarListSerializer*, cIObjectDatabaseIStream*))FUN_00693e10)(
        &serializer, &stream);

    cRefCounted* pNew = (cRefCounted*)((void* (__thiscall*)(void*))FUN_00c14350)(FUN_00b3d310());
    cRefCounted* pOld = mpRef4cc;
    if (pNew != pOld) {
        if (pNew)
            pNew->AddRef();
        mpRef4cc = pNew;
        if (pOld)
            pOld->Release();
    }
    return ok;
}

} // namespace SP
