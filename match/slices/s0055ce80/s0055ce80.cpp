// Slice s0055ce80: SP::cSPObjectTemplateDB asset/parameter load helpers and
// classifier/summarizer registration.
// Unoptimized module: /Od /Ob1 /MD /Gy /TP /arch:SSE /fp:fast (no /EHsc).
#include "s0055ce80.h"

namespace EA { namespace IO {
bool ReadInt32(void* pStream, void* pData, int nCount, int nFlags);
}}

// A 12-byte weighted id (8-byte ID pair + float weight), used by the save format.
struct WeightedID2 { uint32_t mID; uint32_t mIndex; float mWeight; };

// A saved parameter vector: eastl::vector<WeightedID> followed (at +0x18) by a float total.
struct WeightedIDVec {
    eastl::vector<WeightedID2, eastl::sp_vector_allocator> mEntries;  // +0x00
    char pad14[4];
    float mTotal;                                                     // +0x18
};

// 12-byte resource key with zeroing default ctor (as the binary default-constructs it).
struct RKey { uint32_t mInstanceID; uint32_t mTypeID; uint32_t mGroupID;
              RKey() : mInstanceID(0), mTypeID(0), mGroupID(0) {} };

// A minimal vector whose elements are 12 bytes, with no stored allocator (EBO).
template<typename T>
struct SmallVec {
    T* mpBegin; T* mpEnd; T* mpCapacity;
    SmallVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    T* begin() { return mpBegin; }
    T* end() { return mpEnd; }
};

// 12-byte entry of the "counted" vectors used by the parameter tables.
struct Entry12 { uint32_t mValue; uint32_t mType; uint32_t mKey; };

// Interface with a single method at vtable offset 0x58.
typedef bool (__thiscall *GetAt58Fn)(void* self, void* key);

// Reference-counted object interface used by the classifier/summarizer registration.
struct IRefObj {
    virtual void v0();
    virtual int AddRef();
    virtual int Release();
    virtual void v3();
    virtual int GetA();
    virtual int GetB();
    virtual int GetCount();
    virtual int GetItem(int i);
};

namespace SP {

// @ 0x0055ce80
bool FUN_0055ce80(void* pStream, WeightedIDVec* pOut) {
    bool ok = true;
    int count;
    ScratchSlots<11>();
    ok = ok && EA::IO::ReadInt32(pStream, &count, 1, 0);
    if (ok)
        pOut->mEntries.resize(count);
    char* base = (char*)pOut->mEntries.mpBegin;
    for (uint32_t i = 0; ok && i < (uint32_t)count; ++i) {
        char* entry = base + i * 0xc;
        ok = ok && EA::IO::ReadInt32(pStream, entry, 1, 0);
        ok = ok && EA::IO::ReadInt32(pStream, entry + 4, 1, 0);
        ok = ok && EA::IO::ReadInt32(pStream, entry + 8, 1, 0);
        pOut->mTotal += *(float*)(entry + 8);
    }
    return ok;
}

// @ 0x0055cff0
bool cSPObjectTemplateDB::FUN_0055cff0(void* pKey) {
    bool result = true;
    RKey local;
    local = *(RKey*)pKey;
    local.mTypeID = SP::EditorEntityToResourceType((*(RKey*)pKey).mGroupID >> 16 & 0xff, 1);
    SmallVec<Entry12> list;
    int index = FUN_00560c30(&local);
    char* asset = (char*)(index * 0x50 + *(int*)((char*)this + 0x14));
    if (FUN_0055cd90(pKey, &list, asset + 0x10)) {
        RKey key2 = local;
        key2.mTypeID = 0x1a99b06b;
        void* mgr = EA::ResourceMan::GetManager();
        bool found = ((GetAt58Fn)(*(void***)mgr)[0x58 / 4])(mgr, &local);
        if (!found) {
            mgr = EA::ResourceMan::GetManager();
            ((GetAt58Fn)(*(void***)mgr)[0x58 / 4])(mgr, &key2);
        }
        if (FUN_0055d230(index, &list)) {
            FUN_00561850(index);
            unsigned val = 0;
            void* itEnd;
            ((DBSub*)((char*)this + 0xf8))->End(&itEnd);
            void* itpair[2];
            ((DBSub*)((char*)this + 0xdc))->Find(itpair, &local.mTypeID);
            void* it = (itpair[0] != itpair[1]) ? itpair[0] : itEnd;
            void* realEnd = *(void**)((char*)this + 0xe0);
            if (it != realEnd)
                val = *(unsigned*)((char*)it + 4);
            ((DBSub*)((char*)this + 0x174))->AddVal(1, asset + 0x10, val);
        } else {
            result = false;
        }
    } else {
        result = false;
    }
    if (!result) {
        char tmp[12];
        ((DBSub*)((char*)this + 0x28))->AddKey1(tmp, &index);
    }
    bool resultCopy = result;
    for (Entry12* p = list.begin(); p < list.end(); ++p) {
    }
    ((DBSub*)&list)->Destroy();
    return resultCopy;
}

// @ 0x0055d230
char cSPObjectTemplateDB::FUN_0055d230(int index, void* pList) {
    bool result = false;
    char* asset = (char*)(*(int*)((char*)this + 0x14) + 0x2c + index * 0x50);
    char* it = *(char**)pList;
    char* last = *((char**)pList + 1);
    for (; it != last; it += 0xc) {
        char* entry = it;
        uint32_t type = *(uint32_t*)(entry + 4);
        if (type == 0x2e1a75d) {
            Entry12 tmp;
            ((DBSub*)((char*)this + 0xf4))->AddKey0(&tmp, entry, 0);
            ((DBSub*)((char*)this + 0xf8))->AddKey1(&tmp, entry);
            if (*(uint32_t*)entry == 0x2dc9d1e)
                *(uint32_t*)(asset + 0xc) = *(uint32_t*)(entry + 8);
            ((DBSub*)((char*)this + 0x94))->AddKey0(&tmp, entry, 0);
            result = true;
        } else if (type == 0x2e1a7ff) {
            Entry12 tmp;
            ((DBSub*)((char*)this + 0x110))->AddKey0(&tmp, entry, 0);
            ((DBSub*)((char*)this + 0x114))->AddKey1(&tmp, entry);
            ((DBSub*)((char*)this + 0x94))->AddKey0(&tmp, entry, 0);
            result = true;
        }
    }
    return (char)result;
}

// @ 0x0055d790
bool cSPObjectTemplateDB::FUN_0055d790(void* pKey, void* pList) {
    bool result = (((DBSub*)pList)->GetResType() == 0);
    char* it = *(char**)pList;
    char* last = *((char**)pList + 1);
    for (; it != last; it += 0xc) {
        char* entry = it;
        uint32_t type = *(uint32_t*)(entry + 4);
        if (type == 0x2e1a75d) {
            void* a;
            ((DBSub*)((char*)this + 0xf4))->Find(&a, entry);
            void* b;
            ((DBSub*)((char*)this + 0xf8))->End(&b);
            if (a != b) {
                void* val = ((DBSub*)&a)->Deref(&a);
                if (val != 0) {
                    void* inner;
                    ((DBSub*)val)->Find(&inner, entry + 8);
                    void* innerEnd;
                    ((DBSub*)val)->End(&innerEnd);
                    if (inner != innerEnd) {
                        void* v = ((DBSub*)val)->Deref(&inner);
                        ((DBSub*)((char*)this + 0x94))->AddKey1(pKey, v);
                    }
                }
            } else {
                result = false;
            }
        } else if (type == 0x2e1a7ff) {
            void* a;
            ((DBSub*)((char*)this + 0x110))->Find(&a, entry);
            void* b;
            ((DBSub*)((char*)this + 0x114))->End(&b);
            if (a != b) {
                void* val = ((DBSub*)&a)->Deref(&a);
                if (val != 0) {
                    void* inner;
                    ((DBSub*)val)->Find(&inner, entry + 8);
                    void* innerEnd;
                    ((DBSub*)val)->End(&innerEnd);
                    if (inner != innerEnd) {
                        void* v = ((DBSub*)val)->Deref(&inner);
                        ((DBSub*)((char*)this + 0x94))->AddKey1(pKey, v);
                    }
                }
            } else {
                result = false;
            }
        } else {
            result = false;
        }
    }
    return result;
}

// @ 0x0055d9e0
char cSPObjectTemplateDB::FUN_0055d9e0(void* pObj, int count, void* pItems, char flag) {
    char result = 0;
    if (pObj == 0)
        return 0;
    bool add = true;
    if (!flag) {
        int a = ((IRefObj*)pObj)->GetB();
        int b = ((IRefObj*)pObj)->GetA();
        add = FUN_00558bf0(b, a);
    }
    for (int i = 0; i < count; ++i) {
        uint32_t item = ((uint32_t*)pItems)[i];
        void* tmp;
        ((DBSub*)((char*)this + 0x208))->AddKey0(&tmp, &item, 0);
        if (add) {
            ((DBSub*)((char*)this + 0x228))->AddKey1(&tmp, &item);
        }
        result = 1;
    }
    return result;
}

// @ 0x0055db30
char cSPObjectTemplateDB::FUN_0055db30(void* pObj) {
    bool result = false;
    if (pObj == 0)
        return 0;
    if (((IRefObj*)pObj)->GetA() == 0x55a63a0) {
        IRefObj** slot = (IRefObj**)((char*)this + 0x224);
        if (pObj != (void*)*slot) {
            IRefObj* old = *slot;
            ((IRefObj*)pObj)->AddRef();
            *slot = (IRefObj*)pObj;
            if (old)
                old->Release();
        }
    }
    int a = ((IRefObj*)pObj)->GetB();
    int b = ((IRefObj*)pObj)->GetA();
    char add = FUN_00558bf0(b, a);
    int n = ((IRefObj*)pObj)->GetCount();
    result = (n != 0);
    for (int i = 0; i < n; ++i) {
        uint32_t item = ((IRefObj*)pObj)->GetItem(i);
        void* tmp;
        ((DBSub*)((char*)this + 0x1ec))->AddKey0(&tmp, &item, 0);
        if (add) {
            ((DBSub*)((char*)this + 0x228))->AddKey1(&tmp, &item);
        }
    }
    return (char)result;
}

}
