// src/game/SPGonzago/SPMissionManagerBase.cpp -- migrated from slice(s) s00b6f4f0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMissionManagerBase.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameNounManager.h"
#include "SP/cVarListSerializer.h"

// unnamed retail callees and globals (address in the comment)
extern "C" bool __cdecl WriteUint32(void* stream, const void* src, int count, int endian);  // 0x0093aa70

// ---- items of slice s00b6f4f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IRefLite {
    virtual int  AddRef();                 // 0x00
    virtual int  Release();                // 0x04
    virtual void g2();                     // 0x08
    virtual void* Cast(unsigned id);       // 0x0c
virtual void g4();
virtual void g5();
    virtual void g6();                     // 0x18
    virtual void Notify(unsigned a);       // 0x1c
virtual void f8();
virtual void f9();
virtual void f10();
virtual void f11();
virtual void f12();
virtual void f13();
virtual void f14();
virtual void f15();
virtual void f16();
virtual void f17();
virtual void f18();
virtual void f19();
virtual void f20();
virtual void f21();
virtual void f22();
virtual void f23();
virtual void f24();
virtual void f25();
virtual void f26();
virtual void f27();
virtual void f28();
virtual void f29();
virtual void f30();
virtual void f31();
virtual void f32();
virtual void f33();
virtual void f34();
virtual void f35();
virtual void f36();
virtual void f37();
virtual void f38();
virtual void f39();
virtual void f40();
virtual void f41();
virtual void f42();
virtual void f43();
virtual void f44();
virtual void f45();
    virtual void NotifyB8();               // 0xb8
};
struct NodeUIntARC {              // node of the +0x28 hashtable
    unsigned  key;                // +0x00
    IRefLite* value;              // +0x04  (AutoRefCount payload)
    NodeUIntARC* next;            // +0x08
};
struct NodeTripleARC {            // node of the +0x48 hashtable
    unsigned  k0, k1, k2;         // +0x00..+0x08
    IRefLite* value;              // +0x0c
    NodeTripleARC* next;          // +0x10
};
struct HashUIntARC {              // +0x28 hashtable header
    void*         mAlloc;         // +0x00
    NodeUIntARC** mpBucket;       // +0x04
    unsigned      mnBucketCount;  // +0x08
    unsigned      mnElementCount; // +0x0c
    void*         mHashPolicy;    // +0x10
};
struct HashTripleARC {
    void*           mAlloc;         // +0x00
    NodeTripleARC** mpBucket;       // +0x04
    unsigned        mnBucketCount;  // +0x08
    unsigned        mnElementCount; // +0x0c
    void*           mHashPolicy;    // +0x10
};
struct IStreamHandle;             // EA::IO stream (opaque, passed to the Read/Write helpers)
struct ISerializerStream {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual IStreamHandle* GetStream();               // slot 6 (+0x18)
};
struct ISerializer {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
    virtual void EndItem();                           // slot 7  (+0x1c)
    virtual ISerializerStream* GetStreamHolder();     // slot 8  (+0x20)
    virtual void v9();                                // slot 9  (+0x24)
    virtual IRefLite* ReadObject(unsigned classid, IRefLite** out, int flags); // slot 10 (+0x28)
    virtual void WriteObject(IRefLite* obj);          // slot 11 (+0x2c)
};
extern "C" bool __cdecl WriteUint32(void* stream, const void* src, int count, int endian);  // 0x0093aa70
struct cVarListSerializer {
    unsigned mData[0x40 / 4];
    cVarListSerializer(void* object, unsigned listId, unsigned id);  // 0x00692f90
    void Serialize(ISerializer* s);                                  // 0x00692900
};
struct MissionMgr {
virtual void v00();
virtual void v01();
virtual void v02();
virtual void v03();
virtual void v04();
virtual void v05();
virtual void v06();
virtual void v07();
virtual void v08();
virtual void v09();
    virtual unsigned g28(int a);                   // slot 10 (+0x28)
    virtual void g2c();                            // slot 11 (+0x2c)

    char            mPad00[0x14 - 4];               // vptr at 0, so four bytes are consumed
    IRefLite**      mObjectsBegin;                 // +0x14
    IRefLite**      mObjectsEnd;                   // +0x18
    IRefLite**      mObjectsCapacity;              // +0x1c
    char            mPad20[0x28 - 0x20];
    HashUIntARC     mStrategyMap;                  // +0x28
    char            mPad3c[0x48 - 0x28 - sizeof(HashUIntARC)];
    HashTripleARC   mTripleMap;                    // +0x48
    char            mPad5c[0x68 - 0x48 - sizeof(HashTripleARC)];
    IRefLite*       mCard68;                       // +0x68
    IRefLite*       mCard6c;                       // +0x6c
    unsigned char   mFlag70;                       // +0x70

    void __thiscall Write(ISerializer* s);              // 0x00b6f570
    void __thiscall RefreshAll(int a, int b);           // 0x00b6f650
    void __thiscall RefreshCards();                     // 0x00b6f760
    IRefLite* __thiscall LookupStrategy(unsigned key);  // 0x00b6fa60
    void __thiscall Shutdown();                         // 0x00b70070
    void __thiscall OnStrategyGone(unsigned id);        // 0x00b700f0
    void __thiscall Dtor();                             // 0x00b705a0
    IRefLite* __thiscall Hint(unsigned key);            // 0x00b706a0
    unsigned __thiscall HintClear(unsigned id);         // 0x00b707a0
};
// ---- items of slice s00b6f4f0 end

// @ 0x00b6f570
void __thiscall MissionMgr::Write(ISerializer* s)
{
    ISerializerStream* holder = s->GetStreamHolder();
    IStreamHandle* stream = holder->GetStream();
    unsigned id = 0x54361546;
    WriteUint32(stream, &id, 1, 0);
    cVarListSerializer ser(this, 0x0156b198, 0x01a80d26);
    ser.Serialize(s);
}
