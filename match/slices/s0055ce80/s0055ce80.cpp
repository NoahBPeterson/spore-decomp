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
    bool Empty() const;                                  // 0x00526430
};

// 12-byte entry of the "counted" vectors used by the parameter tables.
struct Entry12 { uint32_t mValue; uint32_t mType; uint32_t mKey; };

// Same 12-byte parameter entry, with the trailing word viewed as either an
// integer key (type 0x2e1a75d) or a float weight (type 0x2e1a7ff).
struct ParamEntry {
    uint32_t mValue;    // +0x00  parameter id
    uint32_t mType;     // +0x04  entry kind
    union { uint32_t mKey; float mWeight; };  // +0x08
};

// ---- EASTL container layouts used by the parameter tables ------------------

// rbtree anchor: rightmost/leftmost links and the root (mpNodeParent).
struct RBAnchor {
    void* mpNodeRight;    // +0x00
    void* mpNodeLeft;     // +0x04
    void* mpNodeParent;   // +0x08  root
    uint32_t mColor;      // +0x0c
};

// An rbtree iterator is a single node pointer; `end` is the map's anchor address.
struct TreeIter {
    void* mpNode;                                        // +0x00
    void* Deref();                                       // 0x00564f50
    void Set(void* pNode);                               // 0x00566c50
    void Copy(const TreeIter* pSrc);                     // 0x005673e0
};

// pair<iterator, bool> returned by the sret insert helpers.
struct IterBoolResult { TreeIter mIter; uint8_t mbInserted; uint8_t mPad[3]; };
// pair<iterator, iterator> returned by equal_range.
struct IterRange { TreeIter mFirst; TreeIter mSecond; };

// eastl::map<uint32_t, V> object (0x1c bytes).
struct ParamTree {
    uint32_t mCompare;    // +0x00  empty eastl::less
    RBAnchor mAnchor;     // +0x04
    uint32_t mnSize;      // +0x14
    uint32_t mAllocator;  // +0x18  empty eastl::allocator

    void TreeCtor(const void* pAllocator);                                   // 0x00564cb0
    void TreeDestroy(void* pRoot);                                           // 0x00566900
    void FindU32(TreeIter* pOut, const void* pKey);                          // 0x00564b50
    void FindInnerU32(TreeIter* pOut, const void* pKey);                     // 0x00564ab0
    void FindInnerFloat(TreeIter* pOut, const void* pKey);                   // 0x00564bf0
    void InsertGroupParam(IterBoolResult* pOut, const void* pValue, char flag);    // 0x00566740
    void InsertWeightedParam(IterBoolResult* pOut, const void* pValue, char flag); // 0x00566b10
    void InsertIndexU32(IterBoolResult* pOut, const void* pValue, char flag);      // 0x00566600
    void InsertIndexFloat(IterBoolResult* pOut, const void* pValue, char flag);    // 0x00566970
    void EraseIter(TreeIter* pOut, TreeIter iter);                           // 0x00566570
};

// eastl::vector_set<uint32_t> object (0x18 bytes).
struct U32Set {
    uint32_t* mpBegin;       // +0x00
    uint32_t* mpEnd;         // +0x04
    uint32_t* mpCapacity;    // +0x08
    const char* mpName;      // +0x0c  sp_vector_allocator
    uint32_t mFlags;         // +0x10
    uint8_t mCompare;        // +0x14
    uint8_t mComparePad[3];

    void SetCtor(const void* pAllocator);                // 0x00540470
    void DoDestroyValues();                              // 0x00553fb0
    void SetCopy(const U32Set* pSrc);                    // 0x00564690
    void FreeBuffer();                                   // 0x00548400
    bool Empty() const;                                  // 0x00526430
    void Insert(IterBoolResult* pOut, const void* pKey); // 0x00554020
    void EqualRange(IterRange* pOut, const void* pKey);  // 0x00555980
    bool Erase(const void* pKey);                        // 0x005540d0
};

// map node value_types: pair<const K, V>, plus the copy helpers used when the
// temporaries are cloned into the inserted node.
struct PairU32Tree {
    uint32_t mKey;                                       // +0x00
    ParamTree mValue;                                    // +0x04
    void PairCtor(const void* pKey, const void* pValue); // 0x005670d0
    void ValueCopy(const void* pSrcValue);               // 0x005659a0
};
struct PairU32Tree2 {
    uint32_t mKey;                                       // +0x00
    ParamTree mValue;                                    // +0x04
    void PairCtor(const void* pKey, const void* pValue); // 0x00567150
    void ValueCopy(const void* pSrcValue);               // 0x005659c0
};
struct PairU32Set {
    uint32_t mKey;                                       // +0x00
    U32Set mValue;                                       // +0x04
    void PairCtor(const void* pKey, const void* pValue); // 0x00567110
};
struct PairF32Set {
    float mKey;                                          // +0x00
    U32Set mValue;                                       // +0x04
};

// The subset of SP::cSPObjectTemplateDB touched by the parameter-table loaders.
struct ParamTables {
    char pad00[0x94];
    U32Set mKnownGroupIDs;       // +0x94  ids already present in the asset list
    char padAc[0xf4 - 0xac];
    ParamTree mGroupParams;      // +0xf4  map<id, map<key, vector_set<index> > >
    ParamTree mWeightedParams;   // +0x110 map<id, map<float, vector_set<index> > >
};

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
    char result = 0;
    ParamTables* tables = reinterpret_cast<ParamTables*>(this);
    SmallVec<ParamEntry>* list = reinterpret_cast<SmallVec<ParamEntry>*>(pList);
    eastl::allocator allocator;

    ParamEntry* it = list->mpBegin;
    ParamEntry* last = list->mpEnd;
    for (; it != last; ++it) {
        ParamEntry* entry = it;
        if (entry->mType == 0x2e1a75d) {
            // tables->mGroupParams[entry->mValue][entry->mKey].insert(index)
            ParamTree emptyInner;
            emptyInner.TreeCtor(&allocator);
            PairU32Tree tmpPair;
            tmpPair.PairCtor(&entry->mValue, &emptyInner);
            emptyInner.TreeDestroy(emptyInner.mAnchor.mpNodeParent);

            PairU32Tree pairCopy;
            pairCopy.mKey = tmpPair.mKey;
            pairCopy.ValueCopy(&tmpPair.mValue);
            IterBoolResult inserted;
            tables->mGroupParams.InsertGroupParam(&inserted, &pairCopy, 0);
            ParamTree* inner = &reinterpret_cast<PairU32Tree*>(inserted.mIter.Deref())->mValue;
            pairCopy.mValue.TreeDestroy(pairCopy.mValue.mAnchor.mpNodeParent);
            tmpPair.mValue.TreeDestroy(tmpPair.mValue.mAnchor.mpNodeParent);

            U32Set emptySet;
            emptySet.SetCtor(&allocator);
            PairU32Set tmpSetPair;
            tmpSetPair.PairCtor(&entry->mKey, &emptySet);
            emptySet.DoDestroyValues();

            PairU32Set setPairCopy;
            setPairCopy.mKey = tmpSetPair.mKey;
            setPairCopy.mValue.SetCopy(&tmpSetPair.mValue);
            IterBoolResult insertedSet;
            inner->InsertIndexU32(&insertedSet, &setPairCopy, 0);
            U32Set* set = &reinterpret_cast<PairU32Set*>(insertedSet.mIter.Deref())->mValue;
            setPairCopy.mValue.DoDestroyValues();
            tmpSetPair.mValue.DoDestroyValues();

            IterBoolResult insertedIndex;
            set->Insert(&insertedIndex, &index);

            // Subtype 0x2dc9d1e records the entry key as the asset's model subtype.
            if (entry->mValue == 0x2dc9d1e)
                this->mAssetList[index].mnModelSubtype = entry->mKey;

            // Groups already known to the DB also copy the key into the asset's group set.
            IterRange known;
            tables->mKnownGroupIDs.EqualRange(&known, &entry->mValue);
            if (known.mFirst.mpNode != known.mSecond.mpNode) {
                IterBoolResult addedGroup;
                U32Set* groupIDs = reinterpret_cast<U32Set*>(&this->mAssetList[index].mGroupIDs);
                groupIDs->Insert(&addedGroup, &entry->mKey);
            }
            result = 1;
        } else if (entry->mType == 0x2e1a7ff) {
            // tables->mWeightedParams[entry->mValue][entry->mWeight].insert(index)
            ParamTree emptyInner;
            emptyInner.TreeCtor(&allocator);
            PairU32Tree2 tmpPair;
            tmpPair.PairCtor(&entry->mValue, &emptyInner);
            emptyInner.TreeDestroy(emptyInner.mAnchor.mpNodeParent);

            PairU32Tree2 pairCopy;
            pairCopy.mKey = tmpPair.mKey;
            pairCopy.ValueCopy(&tmpPair.mValue);
            IterBoolResult inserted;
            tables->mWeightedParams.InsertWeightedParam(&inserted, &pairCopy, 0);
            ParamTree* inner = &reinterpret_cast<PairU32Tree2*>(inserted.mIter.Deref())->mValue;
            pairCopy.mValue.TreeDestroy(pairCopy.mValue.mAnchor.mpNodeParent);
            tmpPair.mValue.TreeDestroy(tmpPair.mValue.mAnchor.mpNodeParent);

            U32Set emptySet;
            emptySet.SetCtor(&allocator);
            PairF32Set tmpWeightPair;
            tmpWeightPair.mKey = entry->mWeight;
            tmpWeightPair.mValue.SetCopy(&emptySet);
            emptySet.DoDestroyValues();

            PairF32Set weightPairCopy;
            weightPairCopy.mKey = tmpWeightPair.mKey;
            weightPairCopy.mValue.SetCopy(&tmpWeightPair.mValue);
            IterBoolResult insertedSet;
            inner->InsertIndexFloat(&insertedSet, &weightPairCopy, 0);
            U32Set* set = &reinterpret_cast<PairF32Set*>(insertedSet.mIter.Deref())->mValue;
            weightPairCopy.mValue.DoDestroyValues();
            for (uint32_t* p = tmpWeightPair.mValue.mpBegin; p < tmpWeightPair.mValue.mpEnd; ++p) {
            }
            tmpWeightPair.mValue.FreeBuffer();

            IterBoolResult insertedIndex;
            set->Insert(&insertedIndex, &index);
            result = 1;
        }
    }
    return result;
}

// @ 0x0055d790
bool cSPObjectTemplateDB::FUN_0055d790(void* pKey, void* pList) {
    ParamTables* tables = reinterpret_cast<ParamTables*>(this);
    SmallVec<ParamEntry>* list = reinterpret_cast<SmallVec<ParamEntry>*>(pList);
    bool result = !list->Empty();

    ParamEntry* it = list->mpBegin;
    ParamEntry* last = list->mpEnd;
    for (; it != last; ++it) {
        ParamEntry* entry = it;
        if (entry->mType == 0x2e1a75d) {
            TreeIter found;
            tables->mGroupParams.FindU32(&found, &entry->mValue);
            TreeIter outerEnd;
            outerEnd.Set(&tables->mGroupParams.mAnchor);
            if (found.mpNode == outerEnd.mpNode) {
                result = false;
            } else {
                ParamTree* inner = &reinterpret_cast<PairU32Tree*>(found.Deref())->mValue;
                TreeIter foundSet;
                inner->FindInnerU32(&foundSet, &entry->mKey);
                TreeIter innerEnd;
                innerEnd.Set(&inner->mAnchor);
                if (foundSet.mpNode != innerEnd.mpNode) {
                    U32Set* set = &reinterpret_cast<PairU32Set*>(foundSet.Deref())->mValue;
                    set->Erase(pKey);
                    if (set->Empty()) {
                        TreeIter setCopy;
                        setCopy.Copy(&foundSet);
                        TreeIter eraseArg;
                        eraseArg.Copy(&setCopy);
                        TreeIter erased;
                        inner->EraseIter(&erased, eraseArg);
                    }
                }
            }
        } else if (entry->mType == 0x2e1a7ff) {
            TreeIter found;
            tables->mWeightedParams.FindU32(&found, &entry->mValue);
            TreeIter outerEnd;
            outerEnd.Set(&tables->mWeightedParams.mAnchor);
            if (found.mpNode == outerEnd.mpNode) {
                result = false;
            } else {
                ParamTree* inner = &reinterpret_cast<PairU32Tree2*>(found.Deref())->mValue;
                TreeIter foundSet;
                inner->FindInnerFloat(&foundSet, &entry->mWeight);
                TreeIter innerEnd;
                innerEnd.Set(&inner->mAnchor);
                if (foundSet.mpNode != innerEnd.mpNode) {
                    U32Set* set = &reinterpret_cast<PairF32Set*>(foundSet.Deref())->mValue;
                    set->Erase(pKey);
                    if (set->Empty()) {
                        TreeIter setCopy;
                        setCopy.Copy(&foundSet);
                        TreeIter eraseArg;
                        eraseArg.Copy(&setCopy);
                        TreeIter erased;
                        inner->EraseIter(&erased, eraseArg);
                    }
                }
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
