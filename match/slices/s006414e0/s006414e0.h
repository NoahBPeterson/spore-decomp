// Shared declarations for the asset-data / thumbnail module (retail layout).
#pragma once
#include "types.h"

struct ResourceKey {
    uint32_t instanceID, typeID, groupID;
    ResourceKey() {}
    ResourceKey(uint32_t i, uint32_t t, uint32_t g) : instanceID(i), typeID(t), groupID(g) {}
};

struct IRefCounted { virtual int AddRef(); virtual int Release(); };

// Asset metadata object (cAssetMetadata): thiscall helpers (names unknown)
struct cAssetMetadata : IRefCounted {
    uint64_t* FUN_005507a0();     // 0x005507A0
    uint64_t* FUN_00550840();     // 0x00550840
    uint64_t* FUN_00550860();     // 0x00550860
    uint64_t  FUN_005508a0();     // 0x005508A0
    bool      FUN_00550970();     // 0x00550970
};

template <class T>
struct AutoRef {
    T* mpObject;
    AutoRef() : mpObject(0) {}
    ~AutoRef() { if (mpObject) mpObject->Release(); }
    AutoRef& operator=(T* p)
    {
        if (p != mpObject) {
            T* const pTemp = mpObject;
            if (p) p->AddRef();
            mpObject = p;
            if (pTemp) pTemp->Release();
        }
        return *this;
    }
};

struct IResource : IRefCounted {
    virtual void s2();
    virtual IRefCounted* Cast(uint32_t id);   // +0xC
};

struct IResourceManager {
    virtual void s0(); virtual void s1(); virtual void s2();
    virtual bool GetResource(const ResourceKey* k, AutoRef<IResource>* out, int a, int b, int c, int d);   // +0xC
    virtual bool GetResourceEx(const ResourceKey* k, void* slot, AutoRef<IResource>* out, int a, int b, int c, int d, int e);   // +0x10
};
IResourceManager* GetManager();   // 0x0067DCD0

struct ILoadSlot : IRefCounted {
    virtual void s2(); virtual void s3();
    virtual bool IsReady();                          // +0x10
    virtual bool GetResult(AutoRef<IResource>* out); // +0x14
};

void operator delete(void* p);   // 0x00F47380 (EASTL allocator deallocate)
inline void* operator new(size_t, void* p) { return p; }
