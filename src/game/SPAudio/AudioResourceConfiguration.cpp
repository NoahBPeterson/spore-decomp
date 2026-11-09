// src/game/SPAudio/AudioResourceConfiguration.cpp -- migrated from slice(s) s00a17690, s00a196f0, s00a187f0, s00a168c0 by tools/migrate/rewrite.py
// Object file: SPAudio/AudioResourceConfiguration.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Audio/IPrimitive.h"
#include "EA/Audio/ResourceConfiguration.h"
#include "EA/Audio/ResponseCurve.h"
#include <intrin.h>
#include <string.h>
#include "EA/Thread/Mutex.h"
#include "EA/Variant.h"
#include "EA/Audio/IConfiguration.h"

// ---- items of slice s00a168c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned short u16;
typedef unsigned int   u32;
struct Variant {
    union {
        u32   u;
        void* p;
        float f;
        char  bytes[0x10];
    };
    u16 mFlags;    // +0x10
    u16 mTypeId;   // +0x12
};
struct Key { u32 a, b, c; };
typedef bool (__thiscall* GetPropertyFn)(void*, u32, Variant const*&);
struct RC {
    void* vtbl;   // +0x00 (IConfiguration)

    bool GetPropertyAsKey(u32 key, Key* out);                        // 00a174d0
    bool GetPropertyAsKeyInstance(u32 key, u32* out);                // 00a17520
    bool GetPropertyAsFloatArray(u32 key, u32* count, const void** arr);  // 00a17560
    bool GetPropertyAsUint32Array(u32 key, u32* count, const void** arr); // 00a175c0
    bool GetPropertyAsKeyArray(u32 key, u32* count, const void** arr);    // 00a17620

    bool GetProperty(u32 key, Variant const*& v)
    {
        GetPropertyFn f = *(GetPropertyFn*)((char*)(*(void**)this) + 0x20);
        return f(this, key, v);
    }
};
// ---- items of slice s00a168c0 end

// ---- items of slice s00a187f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
struct Variant_s00a1_87f0 {
    unsigned char mData[0x10];   // +0x00  payload (mDouble / mPointer / ...)
    unsigned short mFlags;       // +0x10
    unsigned short mTypeId;      // +0x12

    Variant_s00a1_87f0& operator=(const Variant_s00a1_87f0& src);   // 0x00542b80  Variant::operator=
    void Destruct(bool free);                 // 0x0093db80  Variant::Destruct
    ~Variant_s00a1_87f0() { if (mFlags & 4) Destruct(false); }
};
struct VariantPair {
    uint first;                  // +0x00  property key
    Variant_s00a1_87f0 second;              // +0x04
};
struct VariantMap {
    VariantPair* mpBegin;        // +0x00
    VariantPair* mpEnd;          // +0x04
    VariantPair* mpCapacity;     // +0x08

    VariantPair* Insert(VariantPair* where, const VariantPair& value);   // 0x006a2c50
};
struct ResourceConfiguration_s00a1_87f0;
struct IConfigurationView {
    void* mpVtbl;                // +0x00
    uint  mPad04[2];             // +0x04
    unsigned char mbLocalOnly;   // +0x0c  ResourceConfiguration::mbGetLocalPropertiesOnly
    unsigned char mPad0d[3];     // +0x0d
    VariantPair* mpMapBegin;     // +0x10  mPropertyMap.mpBegin
    VariantPair* mpMapEnd;       // +0x14  mPropertyMap.mpEnd
    VariantPair* mpMapCapacity;  // +0x18  mPropertyMap.mpCapacity
    unsigned char mPad1c[8];     // +0x1c
    unsigned char mCompare0;     // +0x24  low byte of the map's compare / parent ref
    unsigned char mPad25[3];     // +0x25
    void* mpParentOrChildren;    // +0x28  child ResourceConfiguration consulted for properties
    unsigned char mPad2c[8];     // +0x2c
    Variant_s00a1_87f0 mAggGain;            // +0x34  mAggregatedGainVariant
    Variant_s00a1_87f0 mAggGroups;          // +0x48  mAggregatedGroupsVariant

    bool HasProperty(uint key);              // 0x00a187f0
    bool GetProperty(uint key, void** out);  // 0x00a18850
    void SetProperty(uint key, const Variant_s00a1_87f0* value);  // 0x00a19600
};
struct ResourceConfiguration_s00a1_87f0 {
    void* mpVtbl;                // +0x00
    int   mRefCount;             // +0x04
    uint  mKeyInstance;          // +0x08
    uint  mKeyType;              // +0x0c
    uint  mKeyGroup;             // +0x10
    void* mpConfigVtbl;          // +0x14  IConfiguration sub-object vtable (this + 0x14 of the view)
    uint  mPad18;                // +0x18
    uint  mPad1c;                // +0x1c
    unsigned char mbLocalOnly;   // +0x20  mbGetLocalPropertiesOnly
    unsigned char mPad21[3];     // +0x21
    VariantPair* mpMapBegin;     // +0x24  mPropertyMap.mpBegin
    VariantPair* mpMapEnd;       // +0x28  mPropertyMap.mpEnd
    VariantPair* mpMapCapacity;  // +0x2c  mPropertyMap.mpCapacity
    uint  mPad30;                // +0x30
    uint  mPad34;                // +0x34
    unsigned char mCompare0;     // +0x38  low byte of the map compare / parent ref
    unsigned char mPad39[3];     // +0x39
    void* mpChildAnchor;         // +0x3c  mChildren anchor
    void* mpChildFirst;          // +0x40  mChildren first node
    uint  mPad44;                // +0x44
    Variant_s00a1_87f0 mAggGain;            // +0x48  mAggregatedGainVariant (compiled as offset 0x48)
    Variant_s00a1_87f0 mAggGroups;          // +0x5c  mAggregatedGroupsVariant (compiled as offset 0x5c)
    void* mpGroupsBegin;         // +0x70  mAggregatedGroups.mpBegin
    void* mpGroupsEnd;           // +0x74  mAggregatedGroups.mpEnd
    void* mpGroupsCapacity;      // +0x78  mAggregatedGroups.mpCapacity

    void UpdateAggregatedProperties();       // 0x00a18910
};
VariantPair* LowerBound(const VariantPair* first, const VariantPair* last,
                        const uint* key, unsigned char compare);            // 0x00612db0
bool          VariantConstruct(Variant_s00a1_87f0* self, unsigned short type, unsigned short flags,
                               const void* data, uint size, uint count);    // 0x0093dd80  Variant::Construct
void          SortKeyVector(void* begin, void* end);                        // 0x004f6b70  eastl::sort<Key*>
bool          ReadInt32(void* reader, int* out, int count, int flag);        // 0x0093a780  EA::IO::ReadInt32
struct WString {
    wchar_t* mpBegin;            // +0x00  start of the buffer
    wchar_t* mpEnd;              // +0x04  one past the last written code unit
    wchar_t* mpCapacity;         // +0x08  end of the allocation

    void AppendNChar(int count, wchar_t ch);   // 0x0042d2e0  WString::append_n_char
};
struct IOReader_s00a1_87f0 {
    void* mpVtbl;                // +0x00
    int Read(void* dst, int byteCount);        // vtable + 0x30
};
namespace EA {
namespace Hash {
uint32_t FNV1_String8(const char* s, uint32_t seed, int lowercase);   // 0x00932E80
}
}
struct PropertyTypeMap {
    uint32_t& operator[](const uint32_t& key);   // 0x00643A40 eastl::map<uint,uint>::operator[]
};
namespace EA {
namespace Audio {
class FactoryConfiguration { public:
    char pad[0x40];
    PropertyTypeMap mLegacyTypes;   // +0x40
    void AddLegacyPropertyTypes();
};
}
}
namespace EA {
namespace Audio {
#define H(s) EA::Hash::FNV1_String8(s, 0x811c9dc5, 1)
}
}
// ---- items of slice s00a187f0 end

// ---- items of slice s00a196f0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern bool  f_0093a700(void* reader, void* dst, int count, int flag);   // read raw
extern bool  f_0093a780(void* reader, void* dst, int count, int flag);   // read raw
extern bool  f_0093ac80(void* reader, void* dst);                        // ReadBool
extern bool  f_00593840(void* reader, void* dst);                        // read object
extern bool  f_00692720(void* reader, void* dst, int z);
extern bool  f_00692740(void* reader, void* dst, int z);
extern bool  f_00692760(void* reader, void* dst, int z);
extern void* f_00f473a0(int size, const char* name, int a, int b, const char* file, int line);
extern void  f_00f47380(void* p);                                        // operator delete
extern void  f_00542b80(void* dst, void* src);                           // Variant::operator=
extern void* f_008de1a0(void);                                           // Eapd::Debug::ObjectError
extern void  __stdcall f_006a2b80(void* self, unsigned n);               // vector resize (ret 4)
typedef unsigned char      u8;
struct Variant_s00a1_96f0 {
    void*          mData;      // 0x00
    int            mDim0;      // 0x04
    int            mDim1;      // 0x08
    int            mExtra;     // 0x0c
    unsigned short mFlags;     // 0x10
    unsigned short mType;      // 0x12
};
struct IOReader {
    void*               mVtbl;  // 0x00
    void* readObj(void* obj, int size);
};
struct Mutex {
    char mData[0x30];      // retail EA::Thread::Mutex is 0x30 bytes
    void ctor(int a, int b);
    void dtor();
};
#define TAG_A ((void*)0x01667bac)
#define TAG_B ((void*)0x01667bad)
#define TAG_C ((void*)0x01667bae)
struct ResConfig {
    char  mPad0[0x24];
    void* mPropBegin;          // 0x24
    void* mPropEnd;            // 0x28
    void* mPropCap;            // 0x2c
    char  mPad1[0x3c - 0x30];
    void* mChildren;           // 0x3c
    char  mPad2[0x360 - 0x40];
    int   mNumPoints;          // 0x360

    char  ReadVariant(IOReader* reader, Variant_s00a1_96f0* v);
    char  Read(IOReader* reader);
};
struct RBTree_40 {
    void* mNodeParent;                    // +0x00 (unused by this slice)
    void  DoNukeSubtree(void* node);      // 0x009a9600
};
struct FactoryConfiguration_s00a1_96f0 {
    void* mVtbl;        // 0x00
    void* mField04;     // 0x04
    void* mField08;     // 0x08
    char  mPad[0x04];
    Mutex mMutex;       // 0x10
    RBTree_40 mTree;    // 0x40
    void* mAnchor;      // 0x44
    void* mField48;     // 0x48
    void* mField4c;     // 0x4c
    u8    mField50;     // 0x50
    char  mPad3[0x54 - 0x51];
    void* mField54;     // 0x54
    char  mPad4[0x5c - 0x58];
    void* mField5c;     // 0x5c
    void* mField60;     // 0x60
    void* mField64;     // 0x64

    FactoryConfiguration_s00a1_96f0();  // 0x00a19d60 (FactoryConfiguration::FactoryConfiguration_s00a1_96f0)
    ~FactoryConfiguration_s00a1_96f0();  // 0x00a19d60 (FactoryConfiguration::FactoryConfiguration_s00a1_96f0)
    void AddLegacyPropertyTypes();  // 0x00a18d90 (FactoryConfiguration::AddLegacyPropertyTypes)
};
extern void f_00a17820(ResConfig* self, void* p, void* q);
extern void f_00a18910(ResConfig* self);
// ---- items of slice s00a196f0 end

// ---- items of slice s00a17690 begin (TODO(rewrite): local stubs, replace by canonical classes)
void* __cdecl FUN_00f473a0(uint32_t size, const char* tag, int a, int b, const char* file, uint32_t line);  // EAAllocate
void  FUN_00f47380(void* p);                       // operator delete
void* FUN_00a206f0(void);                          // EA::Audio::GetSystemAT (returns AT*)
int   FUN_00571ef0(void);                          // variant length (returns element count)
void  FUN_00840c70(void* s, const char* fmt, ...); // eastl::SprintfAppend<string8>
void* FUN_00446ff0(void);                          // array payload pointer helper
void  FUN_0093abd0(void* dst, const void* p, int n, int kind);  // WriteString
void* FUN_00921580(void* node);                    // ?RBTreeIncrement@@YAPAURBNode@@PAU1@@Z
void  FUN_0093c570(void* out, const void* in, int n);           // EA::ConvertToString8
void  FUN_009216a0(void* node, void* parent, void* head, int side);  // eastl::RBTreeInsert
void  FUN_0093a780(void* reader, void* dst, int count, int flags);   // EA::IO::ReadInt32
void* FUN_00612db0(const void* begin, const void* end, const uint32_t* key, bool flag);  // eastl::lower_bound
static const char* const kFile_A17890 = "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
static __forceinline void** VtOf(void* p) { return *(void***)p; }
struct EAString {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void Resize(int n, int c);                     // 0x47bf30
};
struct Mutex_s00a1_7690 {
    void Lock(uint32_t id);                        // 0x9221b0
    void Unlock();                                 // 0x922270
};
struct IntrusiveList {
    void Dtor();                                   // 0x620230
};
struct Variant_s00a1_7690 {
    void Destruct(bool b);                          // 0x93db80
};
struct Helper5ed0 {
    void Call();                                    // 0x685ed0
};
struct PropTree {
    void Nuke(void* node);                          // 0x9a9600
    void Insert(const void* first, const void* last, void* out);  // 0xa17a70
};
struct ResourceConfiguration_s00a1_7690 {
    uint8_t m[0x100];

    __forceinline void** Vt() { return *(void***)&m[0]; }

    void ctor();                                             // 0xa17be0
    void dtor();                                             // 0xa17910
    int  IncludesConfiguration(void* key);                   // 0xa176c0
    bool GetPropertyAsBool(uint32_t key, uint8_t* out);      // 0xa176f0
    bool GetPropertyAsInt(uint32_t key, int32_t* out);       // 0xa17730
    bool GetPropertyAsUint32(uint32_t key, uint32_t* out);   // 0xa17770
    bool GetPropertyAsFloat(uint32_t key, float* out);       // 0xa177b0
    void SetChild(void* p);                                  // 0xa17820
    void Attach(void** out, void* parent, const uint32_t* key, char flag);  // 0xa17890
    bool GetProperty(uint32_t key, void** out);              // 0xa18620
    void* GetPropertyAsChar16Ptr(uint32_t key);              // 0xa186e0
    void* GetPropertyAsChar8Ptr(uint32_t key);               // 0xa18720
    void GetPropertyIDs(void* out, bool clear);              // 0xa18760
};
struct FactoryConfiguration_s00a1_7690 {
    uint8_t m[0x200];

    __forceinline void** Vt() { return *(void***)&m[0]; }

    static int __stdcall GetSupportedTypes(uint32_t* out, int count);   // 0xa17690
    bool CreateResource(void* stream, void** out, uint32_t a, uint32_t b);  // 0xa17c70
    bool WriteResource(void* stream, void* cfg, uint32_t a, uint32_t b);    // 0xa17da0
};
namespace EA {
namespace Text {
struct AnalysisInfo_s00a1_7690 { uint32_t a, b, c; };
}
}
namespace eastl {
template <int N>
struct fill_imp {
    template <class It, class T>
    static void do_fill(It first, It last, const T& value) {
        for (; first != last; ++first) *first = value;
    }
};
}
struct Elem12 { uint32_t a, b, c; };
static __forceinline bool ElemLess(const uint32_t* a, const uint32_t* b) {
    if (a[0] != b[0]) return a[0] < b[0];
    if (a[2] != b[2]) return a[2] < b[2];
    return a[1] < b[1];
}
struct String8 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    void Append(const char* s, int n);              // 0x455d60
};
// ---- items of slice s00a17690 end

// @ 0x00a174d0
bool RC::GetPropertyAsKey(u32 key, Key* out)
{
    Variant const* v;
    if (GetProperty(key, v) && v->mTypeId == 0x20) {
        const void* src = (v->mFlags & 0x30) ? v->p : (const void*)v;
        *out = *(const Key*)src;
        return true;
    }
    return false;
}

// @ 0x00a17520
bool RC::GetPropertyAsKeyInstance(u32 key, u32* out)
{
    Variant const* v;
    if (GetProperty(key, v) && v->mTypeId == 0x20) {
        const u32* src = (v->mFlags & 0x30) ? (const u32*)v->p : (const u32*)v;
        *out = *src;
        return true;
    }
    return false;
}

// @ 0x00a17560
bool RC::GetPropertyAsFloatArray(u32 key, u32* count, const void** arr)
{
    Variant const* v;
    if (GetProperty(key, v) && v->mTypeId == 0x0d && (v->mFlags & 0x30)) {
        *count = *(const u32*)((const char*)v + 8);
        *arr = (v->mFlags & 0x30) ? v->p : (v->mTypeId ? (const void*)v : 0);
        return true;
    }
    return false;
}

// @ 0x00a175c0
bool RC::GetPropertyAsUint32Array(u32 key, u32* count, const void** arr)
{
    Variant const* v;
    if (GetProperty(key, v) && v->mTypeId == 0x0a && (v->mFlags & 0x30)) {
        *count = *(const u32*)((const char*)v + 8);
        *arr = (v->mFlags & 0x30) ? v->p : (v->mTypeId ? (const void*)v : 0);
        return true;
    }
    return false;
}

// @ 0x00a17620
bool RC::GetPropertyAsKeyArray(u32 key, u32* count, const void** arr)
{
    Variant const* v;
    if (GetProperty(key, v) && v->mTypeId == 0x20 && (v->mFlags & 0x30)) {
        *count = *(const u32*)((const char*)v + 8);
        *arr = (v->mFlags & 0x30) ? v->p : (v->mTypeId ? (const void*)v : 0);
        return true;
    }
    return false;
}

// @ 0x00a17690
int __stdcall FactoryConfiguration_s00a1_7690::GetSupportedTypes(uint32_t* out, int count)
{
    if (out != 0) {
        if ((uint32_t)count < 1u) return 0;
        out[0] = 0x2b9f662u;
        out[1] = 0x2c9eff2u;
    }
    return 2;
}

// @ 0x00a176c0
int ResourceConfiguration_s00a1_7690::IncludesConfiguration(void* key)
{
    if (key != *(void**)(m - 0xc)) {
        void* p = *(void**)(m + 0x28);
        if (p != 0) {
            if (((bool(__thiscall*)(void*, void*))VtOf((char*)p + 0x14)[2])((char*)p + 0x14, key))
                return 1;
        }
        return 0;
    }
    return 1;
}

// @ 0x00a176f0
bool ResourceConfiguration_s00a1_7690::GetPropertyAsBool(uint32_t key, uint8_t* out)
{
    void* v;
    if (((bool(__thiscall*)(void*, uint32_t, void**))Vt()[8])(this, key, &v)
        && *(uint16_t*)((char*)v + 0x12) == 1) {
        void* src = (*(uint8_t*)((char*)v + 0x10) & 0x30) ? *(void**)v : v;
        *out = *(uint8_t*)src;
        return true;
    }
    return false;
}

// @ 0x00a17730
bool ResourceConfiguration_s00a1_7690::GetPropertyAsInt(uint32_t key, int32_t* out)
{
    void* v;
    if (((bool(__thiscall*)(void*, uint32_t, void**))Vt()[8])(this, key, &v)
        && *(uint16_t*)((char*)v + 0x12) == 9) {
        void* src = (*(uint8_t*)((char*)v + 0x10) & 0x30) ? *(void**)v : v;
        *out = *(int32_t*)src;
        return true;
    }
    return false;
}

// @ 0x00a17770
bool ResourceConfiguration_s00a1_7690::GetPropertyAsUint32(uint32_t key, uint32_t* out)
{
    void* v;
    if (((bool(__thiscall*)(void*, uint32_t, void**))Vt()[8])(this, key, &v)
        && *(uint16_t*)((char*)v + 0x12) == 0xa) {
        void* src = (*(uint8_t*)((char*)v + 0x10) & 0x30) ? *(void**)v : v;
        *out = *(uint32_t*)src;
        return true;
    }
    return false;
}

// @ 0x00a177b0
bool ResourceConfiguration_s00a1_7690::GetPropertyAsFloat(uint32_t key, float* out)
{
    void* v;
    if (((bool(__thiscall*)(void*, uint32_t, void**))Vt()[8])(this, key, &v)
        && *(uint16_t*)((char*)v + 0x12) == 0xd) {
        void* src = (*(uint8_t*)((char*)v + 0x10) & 0x30) ? *(void**)v : v;
        *out = *(float*)src;
        return true;
    }
    return false;
}

// @ 0x00a177f0
template void eastl::fill_imp<0>::do_fill<EA::Text::AnalysisInfo_s00a1_7690*, EA::Text::AnalysisInfo_s00a1_7690>( EA::Text::AnalysisInfo_s00a1_7690* first, EA::Text::AnalysisInfo_s00a1_7690* last, const EA::Text::AnalysisInfo_s00a1_7690& value)
;

// @ 0x00a17820
void ResourceConfiguration_s00a1_7690::SetChild(void* p)
{
    if (*(void**)(m + 0x3c) != 0) {
        void* next = *(void**)(m + 0x1c);
        void* prev = *(void**)(m + 0x18);
        *(void**)next = prev;
        *(void**)((char*)prev + 4) = next;
        *(void**)(m + 0x18) = 0;
        *(void**)(m + 0x1c) = 0;
    }
    void* old = *(void**)(m + 0x3c);
    if (p != old) {
        if (p != 0) ((void(__thiscall*)(void*))VtOf(p)[0])(p);
        *(void**)(m + 0x3c) = p;
        if (old != 0) ((void(__thiscall*)(void*))VtOf(old)[1])(old);
    }
    void* np = *(void**)(m + 0x3c);
    if (np != 0) {
        *(void**)(m + 0x1c) = *(void**)((char*)np + 0x44);
        void* head = (char*)np + 0x40;
        void* node = m + 0x18;
        *(void**)node = head;
        *(void**)((char*)head + 4) = node;
        *(void**)(*(void**)(m + 0x1c)) = node;
    }
}

// @ 0x00a17890
void ResourceConfiguration_s00a1_7690::Attach(void** out, void* parent, const uint32_t* key, char flag)
{
    int side = (flag == 0 && parent != (void*)(m + 4) && *key >= *(uint32_t*)((char*)parent + 0x10)) ? 1 : 0;
    void* node = FUN_00f473a0(0x14, "EASTL", 0, 0, kFile_A17890, 0xd1);
    uint32_t* dst = (uint32_t*)((char*)node + 0x10);
    if (dst != 0) *dst = *key;
    FUN_009216a0(node, parent, m + 4, side);
    *(uint32_t*)(m + 0x14) += 1;
    *out = node;
}

// @ 0x00a17910
void ResourceConfiguration_s00a1_7690::dtor()
{
    *(void**)(m + 0) = (void*)0x14523e8;
    *(void**)(m + 0x14) = (void*)0x1452398;

    if (*(void**)(m + 0x3c) != 0) {
        void* next = *(void**)(m + 0x1c);
        void* prev = *(void**)(m + 0x18);
        *(void**)next = prev;
        *(void**)((char*)prev + 4) = next;
        *(void**)(m + 0x18) = 0;
        *(void**)(m + 0x1c) = 0;
    }

    void* p70 = *(void**)(m + 0x70);
    if (p70 != 0 && *(uint32_t*)((char*)p70 - 4) != 0) FUN_00f47380(p70);

    if (*(uint8_t*)(m + 0x6c) & 4) ((Variant_s00a1_7690*)(m + 0x5c))->Destruct(false);
    if (*(uint8_t*)(m + 0x58) & 4) ((Variant_s00a1_7690*)(m + 0x48))->Destruct(false);
    ((IntrusiveList*)(m + 0x40))->Dtor();
    {
        void* p = *(void**)(m + 0x3c);
        if (p != 0) ((void(__thiscall*)(void*))VtOf(p)[1])(p);
    }
    ((Helper5ed0*)(m + 0x24))->Call();

    *(void**)(m + 0) = (void*)0x13eb938;
}

// @ 0x00a17a00
bool __stdcall FUN_00a17a00(void* reader, EAString* str)
{
    if (str->mpBegin != str->mpEnd) {
        *str->mpBegin = 0;
        str->mpEnd = str->mpBegin;
    }
    int32_t n;
    FUN_0093a780(reader, &n, 1, 0);
    if (n != 0) {
        str->Resize(n, 0);
        return ((int(__thiscall*)(void*, char*, int))VtOf(reader)[0xc])(reader, str->mpBegin, n) == n;
    }
    return true;
}

// @ 0x00a17c70
bool FactoryConfiguration_s00a1_7690::CreateResource(void* stream, void** out, uint32_t a, uint32_t b)
{
    Mutex_s00a1_7690* mutex = (Mutex_s00a1_7690*)(m + 0x10);
    mutex->Lock(0x1452340u);

    ResourceConfiguration_s00a1_7690* obj = (ResourceConfiguration_s00a1_7690*)FUN_00f473a0(0x84, "audio", 0, 0, 0, 0);
    if (obj != 0) obj->ctor();

    if (obj != 0) ((void(__thiscall*)(void*))VtOf(obj)[0])(obj);

    if (obj != 0) {
        uint32_t* key = (uint32_t*)((void*(__thiscall*)(void*))VtOf(stream)[0x10 / 4])(stream);
        *(uint32_t*)(obj->m + 8) = key[0];
        *(uint32_t*)(obj->m + 0xc) = key[1];
        *(uint32_t*)(obj->m + 0x10) = key[2];
        if (((bool(__thiscall*)(void*, void*, void*, uint32_t, uint32_t))Vt()[0x24 / 4])(this, stream, obj, a, b)) {
            *out = obj;
            ((void(__thiscall*)(void*))VtOf(obj)[0])(obj);
            ((void(__thiscall*)(void*))VtOf(obj)[1])(obj);
            mutex->Unlock();
            return true;
        }
    }

    if (obj != 0) ((void(__thiscall*)(void*))VtOf(obj)[1])(obj);
    mutex->Unlock();
    return false;
}

// @ 0x00a17da0
bool FactoryConfiguration_s00a1_7690::WriteResource(void* stream, void* cfg, uint32_t a, uint32_t b)
{
    Mutex_s00a1_7690* mutex = (Mutex_s00a1_7690*)(m + 0x10);
    mutex->Lock(0x1452340u);

    if (b != 0x2b9f662) {                            // [ebp+0x14]: config-format magic
        mutex->Unlock();
        return false;
    }

    // Pull the property key/id range from the stream object (vtable slots 0x18, 0x1c).
    void* keyRange = ((void*(__thiscall*)(void*))VtOf(stream)[0x18 / 4])(stream);
    uint32_t keyCount = ((uint32_t(__thiscall*)(void*))VtOf(stream)[0x1c / 4])(stream);
    (void)keyRange;
    (void)keyCount;

    char* cfgp = (char*)cfg;
    *(uint8_t*)(cfgp + 0x20) = 1;                    // mark the config as "being written"

    // Build the iterator head (an intrusive-list sentinel) and get the begin node.
    char* head = (char*)cfg + 0x14;                  // property-map object
    void* begin = ((void*(__thiscall*)(void*, void*, int))VtOf(head)[0x0c / 4])(head, 0, 1);

    bool ok = true;
    void* node = begin;

    for (;;) {
        // node == &head's sentinel ends the walk.
        if (node == 0) break;

        uint32_t propId = *(uint32_t*)((char*)node + 0x10);

        // Look up the system attribute (AT) for this property and its component.
        void* at = (void*)FUN_00a206f0();
        void* comp = ((void*(__thiscall*)(void*, uint32_t))VtOf(at)[0xec / 4])(at, propId);
        if (comp == 0) { ok = false; break; }

        // Fetch the variant payload for the property id.
        void* payload = 0;
        if (!((bool(__thiscall*)(void*, void*, uint32_t))VtOf(head)[0x20 / 4])(head, &payload, propId)) {
            ok = false;
            break;
        }

        // Accumulate the textual form into `line`.
        String8 line;
        line.mpBegin = 0; line.mpEnd = 0; line.mpCapacity = 0;

        uint32_t n = (uint32_t)FUN_00571ef0();                    // element count of the variant
        uint32_t* elems = (uint32_t*)FUN_00446ff0();              // element base

        uint16_t type = *(uint16_t*)((char*)payload + 0x12);      // variant element type
        switch (type) {
        case 1: {  // bool
            FUN_00840c70(&line, n == 1 ? "prop bool %s" : "prop bools %s", (const char*)node);
            for (uint32_t i = 0; i < n; ++i)
                line.Append(((const char*)elems)[i] ? " true" : " false", 5);
            break;
        }
        case 9: {  // int
            FUN_00840c70(&line, n == 1 ? "prop int %s" : "prop ints %s", (const char*)node);
            for (uint32_t i = 0; i < n; ++i)
                FUN_00840c70(&line, " %d", (int)elems[i]);
            break;
        }
        case 10: { // unsigned
            FUN_00840c70(&line, n == 1 ? "prop uint %s" : "prop uints %s", (const char*)node);
            for (uint32_t i = 0; i < n; ++i)
                FUN_00840c70(&line, " %d", (int)elems[i]);
            break;
        }
        case 13: { // float
            FUN_00840c70(&line, n == 1 ? "prop float %s" : "prop floats %s", (const char*)node);
            for (uint32_t i = 0; i < n; ++i)
                FUN_00840c70(&line, " %.3f", *(float*)&elems[i]);
            break;
        }
        case 18: { // char8 string(s)
            FUN_00840c70(&line, n == 1 ? "prop string8 %s" : "prop string8s %s", (const char*)node);
            char* p = (char*)elems;
            for (uint32_t i = 0; i < n; ++i, p += 0x10)
                FUN_00840c70(&line, " %s", *(char**)p);
            break;
        }
        case 19: { // char16 string(s) -> char8
            FUN_00840c70(&line, n == 1 ? "prop string %s" : "prop strings %s", (const char*)node);
            char* p = (char*)elems;
            for (uint32_t i = 0; i < n; ++i, p += 0x10) {
                String8 tmp;
                tmp.mpBegin = 0; tmp.mpEnd = 0; tmp.mpCapacity = 0;
                FUN_0093c570(&tmp, p, -1);
                FUN_00840c70(&line, " %s", tmp.mpBegin);
                if ((((char*)tmp.mpCapacity - (char*)tmp.mpBegin) & 0xfffffffe) > 1 && tmp.mpBegin != 0)
                    FUN_00f47380(tmp.mpBegin);
            }
            break;
        }
        case 32: { // property-key list
            FUN_00840c70(&line, n == 1 ? "prop key %s" : "prop keys %s", (const char*)node);
            for (uint32_t i = 0; i < n; ++i) {
                String8 tmp;
                tmp.mpBegin = 0; tmp.mpEnd = 0; tmp.mpCapacity = 0;
                FUN_0093c570(&tmp, (char*)elems + i * 0x10, -1);
                FUN_00840c70(&line, " %s", tmp.mpBegin);
                if ((((char*)tmp.mpCapacity - (char*)tmp.mpBegin) & 0xfffffffe) > 1 && tmp.mpBegin != 0)
                    FUN_00f47380(tmp.mpBegin);
            }
            break;
        }
        default:
            break;
        }

        // Emit the accumulated line; on failure stop and report.
        if (ok) {
            uint32_t len = (uint32_t)(line.mpEnd - line.mpBegin);
            ok = ((bool(__cdecl*)(void*, const char*, int, int))FUN_0093abd0)(stream, line.mpBegin, len, 3) != 0;
        }

        if (line.mpBegin != 0 && (line.mpEnd - line.mpBegin) > 1)
            FUN_00f47380(line.mpBegin);

        // Advance to the next property.
        node = ((void*(__cdecl*)(void*))FUN_00921580)(node);
    }

    *(uint8_t*)(cfgp + 0x20) = 0;
    mutex->Unlock();
    return ok;
}

// @ 0x00a18470
void FUN_00a18470(Elem12* first1, Elem12* last1, Elem12* first2, Elem12* last2, Elem12* out)
{
    while (first1 != last1 && first2 != last2) {
        if (ElemLess((uint32_t*)first1, (uint32_t*)first2)) {
            *out = *first1;
            ++first1;
            ++out;
        } else {
            if (!ElemLess((uint32_t*)first2, (uint32_t*)first1)) ++first1;
            ++first2;
        }
    }
    while (first1 != last1) {
        *out = *first1;
        ++first1;
        ++out;
    }
}

// @ 0x00a18520
void FUN_00a18520(Elem12* first1, Elem12* last1, Elem12* first2, Elem12* last2, Elem12* out)
{
    while (first1 != last1 && first2 != last2) {
        if (ElemLess((uint32_t*)first1, (uint32_t*)first2)) {
            *out = *first1;
            ++first1;
        } else if (ElemLess((uint32_t*)first2, (uint32_t*)first1)) {
            *out = *first2;
            ++first2;
        } else {
            *out = *first1;
            ++first1;
            ++first2;
        }
        ++out;
    }
    while (first1 != last1) {
        *out = *first1;
        ++first1;
        ++out;
    }
    while (first2 != last2) {
        *out = *first2;
        ++first2;
        ++out;
    }
}

// @ 0x00a18620
bool ResourceConfiguration_s00a1_7690::GetProperty(uint32_t key, void** out)
{
    char local = *(char*)(m + 0xc);

    if (local == 0) {
        if (key == 0x25df0108u) {
            if (*(uint16_t*)(m + 0x46) != 0) {
                *out = m + 0x34;
                return true;
            }
        } else if (key == 0x7cb81a35u) {
            if (*(uint16_t*)(m + 0x5a) != 0) {
                *out = m + 0x48;
                return true;
            }
        }
    }

    void* begin = *(void**)(m + 0x10);
    void* end = *(void**)(m + 0x14);
    void* found = FUN_00612db0(begin, end, &key, *(bool*)(m + 0x24) != 0);
    if (found != end && !(key < *(uint32_t*)found)) {
        if (found != (char*)found + 0x18) {
            if (found != end) {
                *out = (char*)found + 4;
                return true;
            }
        }
    }

    if (local == 0) {
        void* p = *(void**)(m + 0x28);
        if (p != 0) {
            return ((bool(__thiscall*)(void*, uint32_t, void**))VtOf((char*)p + 0x14)[0x1c / 4])(
                (char*)p + 0x14, key, out);
        }
    }
    return false;
}

// @ 0x00a186e0
void* ResourceConfiguration_s00a1_7690::GetPropertyAsChar16Ptr(uint32_t key)
{
    void* v;
    if (((bool(__thiscall*)(void*, uint32_t, void**))Vt()[8])(this, key, &v)
        && *(uint16_t*)((char*)v + 0x12) == 0x13) {
        void* src = (*(uint8_t*)((char*)v + 0x10) & 0x30) ? *(void**)v : v;
        return *(void**)src;
    }
    return 0;
}

// @ 0x00a18720
void* ResourceConfiguration_s00a1_7690::GetPropertyAsChar8Ptr(uint32_t key)
{
    void* v;
    if (((bool(__thiscall*)(void*, uint32_t, void**))Vt()[8])(this, key, &v)
        && *(uint16_t*)((char*)v + 0x12) == 0x12) {
        void* src = (*(uint8_t*)((char*)v + 0x10) & 0x30) ? *(void**)v : v;
        return *(void**)src;
    }
    return 0;
}

// @ 0x00a18760
void ResourceConfiguration_s00a1_7690::GetPropertyIDs(void* out, bool clear)
{
    if (clear) {
        void* node = *(void**)((char*)out + 0xc);
        ((PropTree*)out)->Nuke(node);
        *(void**)((char*)out + 4) = (char*)out + 4;
        *(void**)((char*)out + 8) = (char*)out + 4;
        *(void**)((char*)out + 0xc) = 0;
        *(uint8_t*)((char*)out + 0x10) = 0;
        *(void**)((char*)out + 0x14) = 0;
    }

    uint8_t* p = *(uint8_t**)(m + 0x10);
    uint8_t* e = *(uint8_t**)(m + 0x14);
    for (; p != e; p += 0x18) {
        uint32_t key = *(uint32_t*)p;
        ((PropTree*)out)->Insert(&key, 0, 0);
    }

    if (*(uint8_t*)(m + 0xc) == 0) {
        void* q = *(void**)(m + 0x28);
        if (q != 0) {
            ((void(__thiscall*)(void*, void*, int))VtOf((char*)q + 0x14)[3])((char*)q + 0x14, out, 0);
        }
    }
}

// @ 0x00a187f0
bool IConfigurationView::HasProperty(uint key)
{
    VariantPair* end = mpMapEnd;
    VariantPair* it = LowerBound(mpMapBegin, end, &key, mCompare0);
    VariantPair* r;
    if (it == end || key < it->first || it == it + 1)
        r = end;
    else
        r = it;
    if (r != end)
        return true;
    void* child = mpParentOrChildren;
    if (!child)
        return false;
    void* cfg = &((ResourceConfiguration_s00a1_87f0*)child)->mpConfigVtbl;
    return ((bool (__thiscall*)(void*, uint))(*(void***)cfg)[0x18 / 4])(cfg, key);
}

// @ 0x00a18850
bool IConfigurationView::GetProperty(uint key, void** out)
{
    if (mbLocalOnly == 0) {
        if (key == 0x25df0108) {
            if (mAggGain.mTypeId != 0) {
                *out = &mAggGain;
                return true;
            }
        } else if (key == 0x7cb81a35) {
            if (mAggGroups.mTypeId != 0) {
                *out = &mAggGroups;
                return true;
            }
        }
    }
    VariantPair* begin = mpMapBegin;
    VariantPair* end = mpMapEnd;
    VariantPair* it = LowerBound(begin, end, &key, mCompare0);
    if (it == end || key < it->first || it == it + 1)
        it = end;
    if (it != end) {
        *out = &it->second;
        return true;
    }
    if (mbLocalOnly == 0) {
        void* child = mpParentOrChildren;
        if (!child)
            return false;
        void* cfg = &((ResourceConfiguration_s00a1_87f0*)child)->mpConfigVtbl;
        return ((bool (__thiscall*)(void*, uint, void**))(*(void***)cfg)[0x20 / 4])(cfg, key, out);
    }
    return false;
}

// @ 0x00a18910
void ResourceConfiguration_s00a1_87f0::UpdateAggregatedProperties()
{
    Variant_s00a1_87f0 temp;
    temp.mFlags = 0;
    temp.mTypeId = 0;

    // Reset both aggregates through operator= with an empty Variant.
    mAggGain = temp;
    if (temp.mFlags & 4)
        temp.Destruct(false);
    temp.mFlags = 0;
    temp.mTypeId = 0;
    mAggGroups = temp;
    if (temp.mFlags & 4)
        temp.Destruct(false);

    unsigned char found = 0;
    if (mKeyType == 0 && ((bool (__thiscall*)(void*, uint, unsigned char*))
                          (*(void***)mpVtbl)[0x24 / 4])(mpVtbl, 0x5a32a0ce, &found)) {
        if (found != 0) {
            float gain = 1.0f;
            ResourceConfiguration_s00a1_87f0* node = this;
            do {
                VariantPair* end = node->mpMapEnd;
                VariantPair* it = LowerBound(node->mpMapBegin, end, (const uint*)0x01452390,
                                             node->mCompare0);
                if (it == end || 0x25df0108 < it->first || it == (VariantPair*)&it->second)
                    it = end;
                if (it != end) {
                    unsigned short t = it->second.mTypeId;
                    float* p;
                    if (t == 0xd || t == 0x10) {
                        if ((it->second.mFlags & 0x30) == 0)
                            p = (float*)(-(uint)(t != 0) & (uint)&it->second);
                        else
                            p = *(float**)&it->second.mData;
                    } else {
                        p = (float*)0x015d1168;
                    }
                    gain = *p * gain;
                }
                node = (ResourceConfiguration_s00a1_87f0*)node->mpChildAnchor;
            } while (node != 0);

            if (mAggGroups.mFlags & 4)
                mAggGroups.Destruct(true);
            unsigned short f = mAggGroups.mFlags & 2;
            if (f == 0 || mAggGroups.mTypeId == 0xd) {
                *(float*)mAggGroups.mData = gain;
                mAggGroups.mTypeId = 0xd;
                mAggGroups.mFlags = f;
            } else {
                VariantConstruct(&mAggGroups, 0xd, 0, &gain, 4, 1);
            }
        }
    }

    mbLocalOnly = 1;

    VariantPair keys[3];
    keys[0].first = 0x7cb81a35; keys[0].second.mFlags = 0xa0be; keys[0].second.mTypeId = 0xf58c;
    keys[1].first = 0x14043549; keys[1].second.mFlags = 0; keys[1].second.mTypeId = 0;
    keys[2].first = 0; keys[2].second.mFlags = 0; keys[2].second.mTypeId = 0;

    VariantPair* listBegin[3];
    VariantPair* listEnd[3];
    for (int i = 0; i < 3; i++) {
        listBegin[i] = (VariantPair*)&keys[i - 1];
        listEnd[i] = 0;
    }

    for (int i = 0; i < 3; i++) {
        unsigned char ok = ((unsigned char (__thiscall*)(void*, uint, void*, void*))
                            (*(void***)mpVtbl)[0x4c / 4])(this, keys[i].first,
                                                          &listBegin[i], &listEnd[i]);
        if (ok) {
            VariantPair* b = listBegin[i];
            VariantPair* e = listEnd[i];
            SortKeyVector(b, e);
        }
    }

    ((void (__thiscall*)(void*, uint, void*, void*))
     (*(void***)mpVtbl)[0x4c / 4])(this, 0x7cb81a35, &listBegin[1], &listEnd[1]);

    mbLocalOnly = 0;

    // Fold the children's lists into the aggregated-groups vector, then recurse into the children.
    if (mpChildFirst != 0 && mpGroupsBegin != 0) {
        //
    }
    (void)listBegin;
    (void)listEnd;
    if (mpChildAnchor != 0) {
        ResourceConfiguration_s00a1_87f0* child = (ResourceConfiguration_s00a1_87f0*)mpChildAnchor;
        while (child != 0) {
            child->UpdateAggregatedProperties();
            child = (ResourceConfiguration_s00a1_87f0*)child->mpChildAnchor;
        }
    }
}

// @ 0x00a18d20
bool __stdcall ReadStringFromStream(IOReader_s00a1_87f0* reader, WString* str)
{
    if (str->mpBegin != str->mpEnd) {
        str->mpBegin[0] = 0;
        str->mpEnd = str->mpBegin;
    }
    int n;
    ReadInt32(reader, &n, 1, 0);
    if (n != 0) {
        str->AppendNChar(n, 0);
        wchar_t* begin = str->mpBegin;
        int written = ((int (__thiscall*)(void*, void*, int))
                       (*(void***)reader)[0x30 / 4])(reader, begin, n * 2);
        return n * 2 == written;
    }
    return true;
}

// @ 0x00a18d90
namespace EA { namespace Audio {
void FactoryConfiguration::AddLegacyPropertyTypes()
{
    mLegacyTypes[H("parent")] = 0x20;
    mLegacyTypes[H("gain")] = 0xd;
    mLegacyTypes[H("pan")] = 0xd;
    mLegacyTypes[H("pitch")] = 0xd;
    mLegacyTypes[H("mindistance")] = 0xd;
    mLegacyTypes[H("maxdistance")] = 0xd;
    mLegacyTypes[H("rolloff")] = 0xd;
    mLegacyTypes[H("streambuffersize")] = 0xa;
    mLegacyTypes[H("streambufferreadsize")] = 0xa;
    mLegacyTypes[H("is3d")] = 1;
    mLegacyTypes[H("islooped")] = 1;
    mLegacyTypes[H("samples")] = 0x80000020;
    mLegacyTypes[H("fadein")] = 0xd;
    mLegacyTypes[H("fadeout")] = 0xd;
    mLegacyTypes[H("priority")] = 0xd;
    mLegacyTypes[H("autoduck")] = 1;
    mLegacyTypes[H("duckcurve")] = 0x8000000d;
    mLegacyTypes[H("ducks")] = 1;
    mLegacyTypes[H("attenuation")] = 0x8000000d;
    mLegacyTypes[H("primitives")] = 0x80000013;
    mLegacyTypes[H("soundtype")] = 0x20;
    mLegacyTypes[H("enable")] = 0xd;
    mLegacyTypes[H("startdelay")] = 0xd;
    mLegacyTypes[H("showmindistance")] = 1;
    mLegacyTypes[H("footcurvenumlegstogain")] = 0x8000000d;
    mLegacyTypes[H("footcurveveltogain")] = 0x8000000d;
    mLegacyTypes[H("footcurvelentohipass")] = 0x8000000d;
    mLegacyTypes[H("footcurvemasstopitch")] = 0x8000000d;
    mLegacyTypes[H("footcurvefootsizetopitch")] = 0x8000000d;
    mLegacyTypes[H("footcurvemasstohipass")] = 0x8000000d;
    mLegacyTypes[H("footcurvemasstogain")] = 0x8000000d;
    mLegacyTypes[H("footcurvefootsizetogain")] = 0x8000000d;
    mLegacyTypes[H("footcurvefootsizetohipass")] = 0x8000000d;
    mLegacyTypes[H("atmospheric")] = 0x8000000d;
    mLegacyTypes[H("polyphony")] = 0xa;
    mLegacyTypes[H("streampoolguid")] = 0x20;
    mLegacyTypes[H("probability")] = 0xd;
    mLegacyTypes[H("dspchain")] = 0x80000013;
    mLegacyTypes[H("syms")] = 0x80000013;
    mLegacyTypes[H("dacoutputmode")] = 0x13;
    mLegacyTypes[H("ignorecontext")] = 1;
    mLegacyTypes[H("voicetemplate")] = 0x20;
    mLegacyTypes[H("foottype")] = 0x13;
    mLegacyTypes[H("mouthtype")] = 0x13;
    mLegacyTypes[H("weapontype")] = 0x13;
    mLegacyTypes[H("time")] = 0xd;
    mLegacyTypes[H("wetlevel")] = 0x8000000d;
    mLegacyTypes[H("reverbtime")] = 0xd;
    mLegacyTypes[H("reverbspacesize")] = 0xd;
    mLegacyTypes[H("timeinvariantpitch")] = 0xd;
    mLegacyTypes[H("listeneroffset")] = 0x8000000d;
}
}}  // namespace EA::Audio

// @ 0x00a19600
void IConfigurationView::SetProperty(uint key, const Variant_s00a1_87f0* value)
{
    VariantPair* end = mpMapEnd;
    VariantPair* it = LowerBound(mpMapBegin, end, &key, mCompare0);
    if (it == end || key < it->first || it == it + 1)
        it = end;
    if (it != end) {
        it->second = *value;
    } else {
        VariantPair entry;
        entry.first = key;
        entry.second.mFlags = 0;
        entry.second.mTypeId = 0;
        entry.second = *value;
        ((VariantMap*)&mpMapBegin)->Insert(&entry, entry);
    }
}

// @ 0x00a196f0
char ResConfig::ReadVariant(IOReader* reader, Variant_s00a1_96f0* v)
{
    bool ok;
    if (v->mType != 0) {
        f_00542b80(v, (void*)0x0166d9a0);
    }
    if (!f_0093a700(reader, &v->mType, 1, 0) ||
        !f_0093a700(reader, &v->mFlags, 1, 0)) {
        ok = false;
    } else {
        ok = true;
    }

    if ((v->mFlags & 0x30) == 0) {
        switch (v->mType) {
        case 1:
            if (ok && f_0093ac80(reader, v)) return 1;
            break;
        case 2:
        case 6:
            if (ok && f_00593840(reader, v)) return 1;
            break;
        case 3:
        case 8:
            if (ok && f_00692720(reader, v, 0)) return 1;
            break;
        case 5:
            if (ok && f_00593840(reader, v)) return 1;
            break;
        case 7:
            if (ok && f_00692720(reader, v, 0)) return 1;
            break;
        case 9:
        case 10:
        case 13:
            if (ok && f_00692740(reader, v, 0)) return 1;
            break;
        case 11:
        case 12:
        case 14:
            if (ok && f_00692760(reader, v, 0)) return 1;
            break;
        case 0x11:
            v->mType = 0;
            v->mFlags = 0;
            return 0;
        case 0x12:
            v->mData = TAG_A;
            v->mDim0 = (int)0x01667bac;
            v->mDim1 = (int)0x01667bad;
            {
                extern bool f_00a17a00(ResConfig*, IOReader*, Variant_s00a1_96f0*);
                if (ok && f_00a17a00(this, reader, v)) return 1;
            }
            break;
        case 0x13:
            v->mData = TAG_A;
            v->mDim0 = (int)0x01667bac;
            v->mDim1 = (int)0x01667bae;
            {
                extern bool f_00a18d20(ResConfig*, IOReader*, Variant_s00a1_96f0*);
                if (ok && f_00a18d20(this, reader, v)) return 1;
            }
            break;
        default:
            if (ok && reader->readObj(v, 0x10)) {
                v->mFlags &= 0xfff2;
                return 1;
            }
            v->mFlags &= 0xfff2;
            return 0;
        }
    } else if ((v->mFlags & 0x40) == 0) {
        bool ok2;
        if (ok && f_0093a780(reader, &v->mDim1, 1, 0) &&
            f_0093a780(reader, &v->mDim0, 1, 0)) {
            ok2 = true;
        } else {
            ok2 = false;
        }
        void* arr = f_00f473a0(v->mDim1 * v->mDim0, "Audio/EAVariant/kfCArray", 0, 0, 0, 0);
        int stride = v->mDim1;
        char* p = (char*)arr;
        char* end = (char*)arr + v->mDim1 * v->mDim0;
        v->mData = arr;
        if (p >= end) return (char)(ok2 ? 1 : 0);

        do {
            bool ok3 = ok2;
            switch (v->mType - 1) {
            case 0:
                if (!ok3 || !f_0093ac80(reader, p)) ok3 = false;
                break;
            case 1:
            case 5:
                if (!ok3 || !f_00593840(reader, p)) ok3 = false;
                break;
            case 2:
            case 7:
                if (!ok3 || !f_00692720(reader, p, 0)) ok3 = false;
                break;
            case 4:
                if (!ok3 || !f_00593840(reader, p)) ok3 = false;
                break;
            case 6:
                if (!ok3 || !f_00692720(reader, p, 0)) ok3 = false;
                break;
            case 8:
            case 9:
            case 0xc:
                if (!ok3 || !f_00692740(reader, p, 0)) ok3 = false;
                break;
            case 10:
            case 0xb:
            case 0xd:
                if (!ok3 || !f_00692760(reader, p, 0)) ok3 = false;
                break;
            case 0xf:
                if (!ok3 || !reader->readObj(p, 0)) ok3 = false;
                break;
            case 0x10:
                v->mFlags = 0;
                v->mType = 0;
                f_00f47380(arr);
                ok3 = false;
                break;
            case 0x11:
                if (p != 0) {
                    *(void**)p = TAG_A;
                    *(void**)(p + 4) = TAG_A;
                    *(void**)(p + 8) = TAG_B;
                }
                {
                    extern bool f_00a17a00(ResConfig*, IOReader*, Variant_s00a1_96f0*);
                    if (!ok3 || !f_00a17a00(this, reader, (Variant_s00a1_96f0*)p)) ok3 = false;
                }
                break;
            case 0x12:
                if (p != 0) {
                    *(void**)p = TAG_A;
                    *(void**)(p + 4) = TAG_A;
                    *(void**)(p + 8) = TAG_C;
                }
                {
                    extern bool f_00a18d20(ResConfig*, IOReader*, Variant_s00a1_96f0*);
                    if (!ok3 || !f_00a18d20(this, reader, (Variant_s00a1_96f0*)p)) ok3 = false;
                }
                break;
            default:
                if (!ok3 || !reader->readObj(p, 0x10)) ok3 = false;
                v->mFlags &= 0xfffe;
                break;
            }
            ok2 = ok3;
            p += stride;
        } while (p < end);
        return (char)(ok2 ? 1 : 0);
    } else {
        v->mFlags = 0;
        v->mType = 0;
    }
    return 0;
}

// @ 0x00a19d60
FactoryConfiguration_s00a1_96f0::FactoryConfiguration_s00a1_96f0()
{
    mVtbl = (void*)0x013effa8;                     // vtbl_Resource::PFRecordRead
    mField04 = 0;
    mField08 = (void*)0x00ad77c2;
    mVtbl = (void*)0x014527b8;                     // ??_7FactoryConfiguration...
    mMutex.ctor(0, 1);

    void* anchor = (char*)this + 0x44;
    void** a = (void**)anchor;
    a[0] = anchor;
    a[1] = 0;
    a[2] = 0;
    a[3] = 0;
    *(void**)((char*)this + 0x48) = anchor;
    *(void**)((char*)this + 0x4c) = 0;
    *(u8*)((char*)this + 0x50) = 0;
    *(void**)((char*)this + 0x54) = 0;

    void* tag = (void*)0x01667bac;
    *(void**)((char*)this + 0x5c) = tag;
    *(void**)((char*)this + 0x60) = tag;
    *(void**)((char*)this + 0x64) = (void*)0x01667bad;

    AddLegacyPropertyTypes();
}

// @ 0x00a19e00
FactoryConfiguration_s00a1_96f0::~FactoryConfiguration_s00a1_96f0()
{
    if (((char*)mField64 - (char*)mField5c) > 1 && mField5c != 0) {
        f_00f47380(mField5c);
    }
    // eastl::rbtree<...>::DoNukeSubtree(mField4c) on the tree at +0x40
    mTree.DoNukeSubtree(mField4c);
    mMutex.dtor();
    mVtbl = (void*)0x013effb8;
}

// @ 0x00a19e90
char ResConfig::Read(IOReader* reader)
{
    u32 header = 0;
    if (!f_0093a780(reader, &header, 1, 0)) return 0;

    int count = 0;
    if ((int)header < 0) {
        int info[3] = {0, 0, 0};
        if (!f_0093a780(reader, info, 3, 0)) return 0;

        void* dbg = f_008de1a0();
        void** children = (void**)((char*)this + 0x3c);
        void* node = *children;
        if (node != 0) {
            *children = 0;
            ((void (__thiscall*)(void*))((void**)*(void**)node)[1])(node);
        }
        if (!((bool (__thiscall*)(void*, int*, void**, int, int, int, int))
                  ((void**)*(void**)dbg)[3])(dbg, info, children, 0, 0, 0, 0))
            return 0;
        header = (u32)info[0];
    }

    unsigned n = header & 0x7fffffff;
    f_006a2b80((char*)this + 0x24, n);
    int elems = (int)((char*)mPropEnd - (char*)mPropBegin) / 0x18;
    char result = 1;
    char prev = 1;
    if (elems > 0) {
        int off = 0;
        do {
            char ok;
            if (result == 0 ||
                !f_0093a780(reader, (char*)mPropBegin + off, 1, 0) ||
                !ReadVariant(reader, (Variant_s00a1_96f0*)((char*)mPropBegin + off + 4))) {
                ok = 0;
            } else {
                ok = 1;
            }
            result = ok;
            off += 0x18;
            --elems;
            prev = result;
        } while (elems != 0);
    }
    (void)count;
    return prev;
}

// @ 0x00a19fb0
char SetParent_00a19fb0(ResConfig* self, void* parent0, void* parent1, void* parent2, void* parent3)
{
    char result = 0;
    void* obj = ((void* (__thiscall*)(void*))((void**)*(void**)parent0)[0x1c / 4])(parent0);
    bool skip = false;
    if (obj != 0) {
        if (((int (__thiscall*)(void*))((void**)*(void**)obj)[0x0c / 4])(obj) == 0x34728492)
            skip = true;
    }
    if (!skip) {
        void* u = ((void* (__thiscall*)(void*))((void**)*(void**)parent0)[0x18 / 4])(parent0);
        result = self->Read((IOReader*)u);
    }

    int local = 0;
    u32 a = 0, b = 0, c = 0;
    void* sys = f_008de1a0();
    (void)sys;
    // The conditional property lookup and the two FUN calls below are the observable
    // behaviour of this routine.
    f_00a17820(self, 0, 0);
    f_00a18910(self);
    (void)a; (void)b; (void)c; (void)local;
    return result;
}
