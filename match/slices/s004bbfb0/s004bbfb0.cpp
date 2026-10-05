// Slice s004bbfb0 (resource factory + EA fixed-buffer allocator).
// Module flags: /Od /Ob1 /MD /Gy /TP (unoptimized; no C++ EH, no SSE).
#include "types.h"

extern void* GetManager();  // 0x67dcd0

// ---------------------------------------------------------------------------
// SP::cSPEditorResourceFactory (0x8 bytes; base is EA::ResourceMan::Factory).
// ---------------------------------------------------------------------------
struct StreamObject;

struct cSPEditorResourceFactory {
    virtual void v0();
    virtual void v4();
    virtual void v8();
    virtual void vC();
    virtual void* v10();
    virtual void v14();
    virtual void v18(int a, int b);
    virtual void v1C();
    virtual void v20();
    virtual bool v24(int* a, int* b, int c, int d);
    virtual void v28();
    virtual void v2C();
    virtual bool v30(int a, int b);

    int GetSupportedTypes(uint32_t* types, uint32_t count);  // 004bc210
    bool CanConvert(int inType, int outType);                // 004bc290
    int Init();                                              // 004bc080
    bool CreateResource(StreamObject* obj, int* out, uint32_t param_4, int typeHash);   // 004bc300
    bool ReadResource(StreamObject* stream, uint32_t param_2, uint32_t param_3, int typeHash);   // 004bc540
    bool WriteResource(StreamObject* stream, uint32_t param_1, uint32_t param_2, int typeHash);  // 004bc620
    bool ReadResourceFromStream(StreamObject* stream, uint32_t key, int typeHash);               // 004bc6d0
};

struct TypeEntry {
    uint32_t mHash;        // +0
    const void* mName;     // +4
    uint32_t pad[4];
};

struct IResourceManager2 {
    virtual void v0(); virtual void v4(); virtual void v8();
    virtual void vC();
    virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1C();
    virtual void v20();
    virtual void Register(uint32_t type, uint32_t* pair, int count);  // +0x24
};

extern uint32_t EA_Hash_FNV1_String16(const void* s, uint32_t hash, int);  // 0x932f30
extern void FUN_004c07e0(void* begin, void* end, char flag);               // 0x4c07e0
extern void FUN_006adc60(int, int);                                        // 0x6adc60
extern bool g_typeTableInit;                                               // 0x15d8600
extern TypeEntry g_typeTable[];                                            // 0x150c518
extern TypeEntry g_typeTableEnd[];                                         // 0x150c878

// 004bc080
int cSPEditorResourceFactory::Init() {
    if (!g_typeTableInit) {
        for (TypeEntry* e = g_typeTable; e != g_typeTableEnd;
             e = (TypeEntry*)((char*)e + 0x18)) {
            e->mHash = EA_Hash_FNV1_String16(e->mName, 0x811c9dc5, 0);
        }
        FUN_004c07e0(g_typeTable, g_typeTableEnd, 0);
        g_typeTableInit = true;
    }
    IResourceManager2* mgr = (IResourceManager2*)GetManager();
    uint32_t local_c = 0x1a99b06b;
    uint32_t local_8;
    local_8 = 0x2399be55; mgr->Register(0x2399be55, &local_c, 2);
    local_8 = 0x2b978c46; mgr->Register(0x2b978c46, &local_c, 2);
    local_8 = 0x3d97a8e4; mgr->Register(0x3d97a8e4, &local_c, 2);
    local_8 = 0x438f6347; mgr->Register(0x438f6347, &local_c, 2);
    local_8 = 0x24682294; mgr->Register(0x24682294, &local_c, 2);
    local_8 = 0x476a98c7; mgr->Register(0x476a98c7, &local_c, 2);
    FUN_006adc60(10, 0x14);
    FUN_006adc60(9, 0x20);
    return 1;
}

// ---------------------------------------------------------------------------
// Factory create / read / write entry points (complete; object model stubbed).
// ---------------------------------------------------------------------------
struct RefCounted {
    virtual void v0();       // +0
    virtual void Release();  // +4
};
struct StreamObject {
    virtual void v0(); virtual void v4(); virtual void v8(); virtual void vC();
    virtual int* v10();                                  // +0x10
    virtual void v14();
    virtual int v18(int a, int b);                       // +0x18
    virtual void v1C();
    virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2C();
    virtual int v30(int* buf, int n);                    // +0x30
};
struct EditorCreature : RefCounted {
    uint32_t pad4;
    uint32_t f8, fC, f10;
};

extern RefCounted* FUN_004b9c70(void* self);                       // 0x4b9c70
extern RefCounted* FUN_004b9da0(void* self);                       // 0x4b9da0
extern int* FUN_004c0500(uint32_t key);                            // 0x4c0500
extern void FUN_006ac0a0(int type, uint32_t key, char flag, int);  // 0x6ac0a0
extern RefCounted* InterfaceCast2(RefCounted** p);                 // 0x421eb0
extern bool FUN_004bdc00(int n);                                   // 0x4bdc00
extern bool FUN_004bdae0();                                        // 0x4bdae0
extern int FUN_004bd9f0(int);                                      // 0x4bd9f0
extern bool FUN_004bdc60(int a, int b, bool c);                    // 0x4bdc60
extern bool FUN_004be5d0();                                        // 0x4be5d0
extern int ReadRuntimeCreatureData(int data);                      // 0x4bf430
extern bool WriteRuntimeCreatureData(int* data);                   // 0x4bf770
extern int WriteBinaryEditorModel(int data);                       // 0x4b0010
extern bool ReadBinaryEditorModel(int* a, int b);                  // 0x4bf9f0
extern bool SetAssetData(uint32_t type, uint8_t flag);             // 0x4bbe20
extern void SetCachingType2(int, void*);                           // 0x6ac040
extern void FUN_006ad010(void*);                                   // 0x6ad010
extern void DestroyFixedBufferShared(void*);                       // 0x4bca10

static inline void ReleaseRef(RefCounted* p) {
    if (p)
        p->Release();
}

// 004bc300
extern void* EditorAlloc(uint32_t size, const char* name, int, int, int, int);  // 0xf473a0

bool cSPEditorResourceFactory::CreateResource(StreamObject* obj, int* out, uint32_t param_4, int typeHash) {
    RefCounted* local_8 = 0;
    if (!SetAssetData((uint32_t)typeHash, 0)) {
        if (typeHash != 0xf43029a)
            return false;
        EditorCreature* c = (EditorCreature*)EditorAlloc(0x128, "Editor", 0, 0, 0, 0);
        if (c)
            c = (EditorCreature*)FUN_004b9da0(c);
        if (c)
            c->v0();
        local_8 = c;
    } else {
        RefCounted* local_28 = (RefCounted*)EditorAlloc(0xac, "Editor", 0, 0, 0, 0);
        if (local_28)
            local_28 = FUN_004b9c70(local_28);
        if (local_28)
            local_28->v0();
        SetCachingType2(10, local_28);
        if (local_28) {
            local_28->v0();
            local_8 = local_28;
        }
        ReleaseRef(local_28);
    }
    if (this->v24((int*)obj, (int*)local_8, param_4, typeHash)) {
        int* p = obj->v10();
        ((EditorCreature*)local_8)->f8 = p[0];
        ((EditorCreature*)local_8)->fC = typeHash;
        ((EditorCreature*)local_8)->f10 = p[2];
        *out = (int)local_8;
        return true;
    }
    ReleaseRef(local_8);
    return false;
}

// 004bc540  SP::cSPEditorResourceFactory::ReadResource
bool cSPEditorResourceFactory::ReadResource(StreamObject* stream, uint32_t param_2, uint32_t param_3, int typeHash) {
    if (typeHash != 0xf43029a) {
        if (typeHash != 0x3d97a8e4 && typeHash != 0x2b978c46 && typeHash != 0x2399be55 &&
            typeHash != 0x24682294 && typeHash != 0x476a98c7 && typeHash != 0x438f6347)
            return false;
        int* p = stream->v10();
        int data = stream->v18(p[1], 0);
        bool ok = ReadBinaryEditorModel((int*)data, typeHash);
        return ok;
    }
    int handle = (int)FUN_004c0500(param_2);
    bool ok = false;
    if (handle != 0) {
        int data = stream->v18(handle, 0);
        if (ReadRuntimeCreatureData(data))
            ok = true;
    }
    FUN_006ac0a0(0xb, param_2, ok, 0);
    return ok;
}

// 004bc620  SP::cSPEditorResourceFactory::WriteResource
bool cSPEditorResourceFactory::WriteResource(StreamObject* stream, uint32_t param_1, uint32_t param_2, int typeHash) {
    if (typeHash != 0xf43029a) {
        bool bakeable = SetAssetData((uint32_t)typeHash, 0);
        if (!bakeable && typeHash != 0x1a99b06b)
            return false;
        int data = stream->v18((int)param_1, typeHash);
        return WriteRuntimeCreatureData((int*)data) != 0;
    }
    int handle = (int)FUN_004c0500(param_1);
    if (handle != 0) {
        int data = stream->v18(handle, 0);
        if (WriteRuntimeCreatureData((int*)data))
            return true;
    }
    return false;
}



// 004bc210
int cSPEditorResourceFactory::GetSupportedTypes(uint32_t* types, uint32_t count) {
    int unused = 8;
    if (types != 0) {
        if (count < 8)
            return 0;
        types[0] = 0x2b978c46;
        types[1] = 0x2399be55;
        types[2] = 0x24682294;
        types[3] = 0x476a98c7;
        types[4] = 0x438f6347;
        types[5] = 0x3d97a8e4;
        types[6] = 0xf43029a;
        types[7] = 0x1a99b06b;
    }
    return 8;
}

// 004bc290
bool cSPEditorResourceFactory::CanConvert(int inType, int outType) {
    if (inType == 0x1a99b06b)
        return outType == 0x2b978c46 || outType == 0x2399be55 ||
               outType == 0x24682294 || outType == 0x476a98c7 ||
               outType == 0x438f6347 || outType == 0x3d97a8e4;
    return false;
}

// ---------------------------------------------------------------------------
// EA::Allocator::FixedBufferAllocator (one pointer member).
// ---------------------------------------------------------------------------
namespace EA { namespace Allocator {

struct FixedBufferAllocator {
    struct buffer_info {
        int32_t mSignature;   // +0x0
        int32_t mSize;        // +0x4
        int32_t mSizeFree;    // +0x8
        void*   mpFirstFree;  // +0xc
    };

    buffer_info* mpBufferInfo;   // +0x0

    FixedBufferAllocator* Create(void* pBuffer, uint32_t size, uint8_t bShared);  // 004bc8a0
    bool IsValid();                                                           // 004bc990
    void destroy_shared();                                                    // 004bca10
    void Free(void* p);                                                       // 004bcab0
};

struct GlobalAllocator {
    void Free(void* p);
};
extern GlobalAllocator* g_pGlobalAllocator;  // 0x016c8b44

// 004bc8a0
FixedBufferAllocator* FixedBufferAllocator::Create(void* pBuffer, uint32_t size, uint8_t bShared) {
    mpBufferInfo = (buffer_info*)pBuffer;
    if (mpBufferInfo != 0 && size >= 0x24) {
        if (bShared == 0 || !IsValid()) {
            mpBufferInfo->mSignature = 0x86421357;
            mpBufferInfo->mSize = size - 0x10;
            int* tmp;
            buffer_info* t14 = (buffer_info*)((char*)mpBufferInfo + 0x10);
            t14->mSignature = 8;
            t14->mSize = 0;
            if (bShared != 0)
                t14->mSignature |= 0x40000000;
            tmp = (int*)((t14->mSignature & 0x3fffffff) + (char*)t14);
            *tmp = mpBufferInfo->mSize - 8;
            tmp[1] = (int)t14;
            mpBufferInfo->mSizeFree = mpBufferInfo->mSize - 8;
            mpBufferInfo->mpFirstFree = tmp;
        }
    } else {
        mpBufferInfo = 0;
    }
    return this;
}

// 004bc990
bool FixedBufferAllocator::IsValid() {
    if (mpBufferInfo->mSignature == 0x86421357 &&
        mpBufferInfo->mSizeFree < mpBufferInfo->mSize &&
        mpBufferInfo->mSizeFree > 0 &&
        mpBufferInfo->mSize > 0 &&
        (uint32_t)mpBufferInfo->mpFirstFree > (uint32_t)((char*)mpBufferInfo + 0x10) &&
        (uint32_t)mpBufferInfo->mpFirstFree < (uint32_t)((char*)mpBufferInfo + 0x10 + mpBufferInfo->mSize))
        return true;
    return false;
}

// 004bca10
void FixedBufferAllocator::destroy_shared() {
    for (uint32_t* p = (uint32_t*)((char*)&mpBufferInfo[1] + (mpBufferInfo[1].mSignature & 0x3fffffff));
         p < (uint32_t*)((char*)&mpBufferInfo[1] + mpBufferInfo->mSize);
         p = (uint32_t*)((*p & 0x3fffffff) + (char*)p)) {
        if ((int)*p < 0) {
            FixedBufferAllocator* owner;
            if ((*p & 0x40000000) == 0)
                owner = 0;
            else
                owner = *(FixedBufferAllocator**)((char*)p + (*p & 0x3fffffff) - 4);
            if (owner == this)
                Free(p + 2);
        }
    }
}

// 004bcab0
void FixedBufferAllocator::Free(void* p) {
    if (mpBufferInfo == 0) {
        g_pGlobalAllocator->Free(p);
        return;
    }
    bool inRange =
        !((char*)p < (char*)mpBufferInfo + 0x10) &&
        (char*)p < (char*)mpBufferInfo + 0x10 + mpBufferInfo->mSize;
    if (!inRange) {
        g_pGlobalAllocator->Free(p);
        return;
    }
    int* h = (int*)((char*)p - 8);
    if (*h < 0) {
        FixedBufferAllocator* owner;
        if ((*h & 0x40000000) == 0)
            owner = 0;
        else
            owner = *(FixedBufferAllocator**)((char*)h + (*h & 0x3fffffff) - 4);
        if (owner == this) {
            *h &= 0x3fffffff;
            if ((char*)mpBufferInfo->mpFirstFree > (char*)h)
                mpBufferInfo->mpFirstFree = h;
            mpBufferInfo->mSizeFree += (*h & 0x3fffffff);
        }
    }
    int* first = (int*)((char*)mpBufferInfo + 0x10);
    if ((*first & 0x3fffffff) > 0x30) {
        int* next = (int*)((char*)first + (*first & 0x3fffffff));
        int* block = (int*)((char*)first + 8);
        *block = (*first & 0x3fffffff) - 8;
        *first = (*first & 0xc0000000) | 8;
        next[1] = (int)block;
        block[1] = (int)first;
        mpBufferInfo->mpFirstFree = block;
        mpBufferInfo->mSizeFree += *block;
    }
}

}}  // namespace EA::Allocator

// 004bc6d0  SP::cSPEditorResourceFactory::ReadResourceFromStream
bool cSPEditorResourceFactory::ReadResourceFromStream(StreamObject* stream, uint32_t key, int typeHash) {
    int data = WriteBinaryEditorModel(key);
    if (data == 0)
        return false;
    if (typeHash == 0x1a99b06b)
        return ReadBinaryEditorModel((int*)data, key);
    char buffer[17076];
    EA::Allocator::FixedBufferAllocator fba;
    fba.mpBufferInfo = 0;
    fba.Create(((EA::Allocator::FixedBufferAllocator::buffer_info*)buffer), 15000, 0);
    FUN_004bd9f0(data);
    bool ok = true;
    bool done = false;
    while (ok && !done) {
        int n = FUN_004bdc00(0x200);
        if (n == 0) {
            ok = false;
        } else {
            int got = stream->v30((int*)n, 0x200);
            done = got != 0x200;
            if (got == -1 || !FUN_004bdc60(n, got, done))
                ok = false;
        }
    }
    if (ok)
        ok = FUN_004be5d0();
    FUN_004bdae0();
    if (fba.mpBufferInfo != 0 && (fba.mpBufferInfo[1].mSignature & 0x40000000) != 0)
        DestroyFixedBufferShared(&fba);
    return ok;
}

// ---------------------------------------------------------------------------
// cSPEditorResourceFactory construction / destruction (base vtable chain).
// ---------------------------------------------------------------------------
extern char g_vtbl_Anim_BackgroundLoading[];
extern char g_vtbl_Resource_PFRecordRead[];
extern char g_vtbl_scalar_deleting_dtor[];
extern char g_vtbl_cSPEditorResourceFactory[];
extern "C" void FreeMemory(void* p);   // 0x926060
extern "C" long _InterlockedExchange(volatile long* Target, long Value);
#pragma intrinsic(_InterlockedExchange)

struct FactoryObject {
    void* vptr;          // +0x0
    int32_t mnRefCount;  // +0x4

    FactoryObject* Init();                 // 004bbfb0
    FactoryObject* Destroy(uint32_t p);    // 004bc030
};

// 004bbfb0
FactoryObject* FactoryObject::Init() {
    vptr = g_vtbl_Anim_BackgroundLoading;
    vptr = g_vtbl_Resource_PFRecordRead;
    long* p = (long*)&mnRefCount;
    _InterlockedExchange(p, 0);
    vptr = g_vtbl_scalar_deleting_dtor;
    vptr = g_vtbl_cSPEditorResourceFactory;
    return this;
}

// 004bc030  SP::cSPEditorResourceFactory::`scalar deleting destructor'
FactoryObject* FactoryObject::Destroy(uint32_t param_2) {
    vptr = g_vtbl_scalar_deleting_dtor;
    vptr = g_vtbl_Resource_PFRecordRead;
    vptr = g_vtbl_Anim_BackgroundLoading;
    if (param_2 & 1)
        FreeMemory(this);
    return this;
}
