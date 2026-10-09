// Havok 3.1.0 serialization: hkBinaryPackfileReader, hkPackfileObjectUpdateTracker and the
// builtin type/class/vtable registries (prebuilt MSVC lib code inside SporeApp.exe).
// Equivalent, portable source: not byte-exact.
// NOTE (64-bit port): the packfile format stores 32-bit pointer slots (PTR32 below); a 64-bit build
// must widen those slots or keep reading them as 32-bit offsets. Not addressed here.
#include <stddef.h>
#include "types.h"

typedef unsigned int hkUlong32;   // pointer-sized key in the 32-bit binary (hkPointerMapBase<unsigned long>)

enum hkResult { HK_SUCCESS = 0, HK_FAILURE = 1 };

struct hkClass { const char* getName() const; };
struct hkTypeInfo { const char* m_name; void (*m_finishLoadedObject)(void*); const void* m_vtable; };

// ---------------------------------------------------------------- memory
struct hkMemory {
    virtual void* allocateChunk(int nbytes, int memClass);          // slot 0
    virtual void  s1();
    virtual void  s2();
    virtual void  s3();
    virtual void* allocateObject(int nbytes, int memClass);         // slot 4 (+0x10)
    virtual void  deallocateObject(void* p, int nbytes, int memClass); // slot 5 (+0x14)
};
extern hkMemory* g_hkMemory;            // hkMemory::s_instance // 0x016e4178
struct hkThreadMemory { void deallocateChunk(void* p, int nbytes, int memClass); };
extern unsigned long g_hkThreadMemoryTlsIndex; // 0x016e4174
extern "C" __declspec(dllimport) void* __stdcall TlsGetValue(unsigned long);
static inline hkThreadMemory* getThreadMemory() { return (hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTlsIndex); }

struct hkArrayUtil {
    static void _reserveMore(void* arr, int elemSize);
};
void hkArray_reserve(void* arr, int n, int elemSize);   // FUN_0107f4a0 (hkArrayUtil::_reserve)
namespace hkString { int strCmp(const char* a, const char* b); }

enum { HK_ARRAY_FLAG_MASK = 0x3fffffff, HK_ARRAY_DONT_DEALLOCATE = (int)0x80000000 };

template <typename T>
struct hkArray {
    T* m_data; int m_size; int m_capacityAndFlags;
    void pushBack(const T& t) {
        if (m_size == (m_capacityAndFlags & HK_ARRAY_FLAG_MASK)) hkArrayUtil::_reserveMore(this, (int)sizeof(T));
        m_data[m_size] = t;
        m_size = m_size + 1;
    }
    void quickFree(int memClass = 0x14) {
        if (m_capacityAndFlags >= 0)
            getThreadMemory()->deallocateChunk(m_data, (m_capacityAndFlags & HK_ARRAY_FLAG_MASK) * (int)sizeof(T), memClass);
    }
};

// hkPointerMapBase<unsigned long>: keys then values in one allocation
struct hkPointerMapBase {
    hkUlong32* m_elem; int m_numElems; int m_hashMod;
    hkPointerMapBase();   // 0x0107de00 (equiv t2)
    ~hkPointerMapBase();   // 0x0107de50 (equiv t2)
    hkUlong32 getWithDefault(hkUlong32 key, hkUlong32 def) const;   // 0x0107e540 (equiv t2)
    void insert(hkUlong32 key, hkUlong32 value);   // 0x0107de70 (equiv t2)
};
struct hkStringMapBase {
    hkStringMapBase();
    ~hkStringMapBase();
    void* getIterator() const;
    bool isValid(void* it) const;          // FUN_012098f0 writes through a bool*
    const char* getKey(void* it) const;
    hkUlong32 getValue(void* it) const;
    void* getNext(void* it) const;
    void insert(const char* key, hkUlong32 value);
    hkUlong32 getWithDefault(const char* key, hkUlong32 def) const;
};

// ---------------------------------------------------------------- referenced object base
// +0 vtbl, +4 memSizeAndFlags, +6 referenceCount.  Base vtable slot 1 is a no-op (0x52e650).
struct hkReferencedObject {
    uint16_t m_memSizeAndFlags;
    uint16_t m_referenceCount;
    hkReferencedObject() : m_referenceCount(1) {}
    virtual ~hkReferencedObject() {}
    virtual void slot1() {}
    void removeReference() {
        if (m_memSizeAndFlags != 0) {
            m_referenceCount = (uint16_t)(m_referenceCount - 1);
            if (m_referenceCount == 0) delete this;
        }
    }
};

#define HK_CLASS_ALLOC(CLS, MEMCLASS) \
    static void* operator new(size_t sz) { void* p = g_hkMemory->allocateObject((int)sz, MEMCLASS); \
        *(uint16_t*)((char*)p + 4) = (uint16_t)sz; return p; } \
    static void operator delete(void* p) { g_hkMemory->deallocateObject(p, *(uint16_t*)((char*)p + 4), MEMCLASS); }

// ---------------------------------------------------------------- registries
struct hkClassNameRegistry : hkReferencedObject {
    hkStringMapBase m_map;     // +8
    virtual void registerClass(const hkClass* klass, const char* name);                 // 2
    virtual const hkClass* getClassByName(const char* name) const;                     // 3
    virtual void registerList(const hkClass* const* classes);                          // 4
    virtual void merge(const hkClassNameRegistry& from);                               // 5
};

struct hkFinishLoadedObjectRegistry : hkReferencedObject {
    hkStringMapBase m_map;     // +8
    virtual void registerTypeInfo(const hkTypeInfo* info);                              // 2
    virtual void finishLoadedObject(void* obj, const char* className) const;           // 3
    virtual void merge(const hkFinishLoadedObjectRegistry& from);                       // 4
};

struct hkVtableClassRegistry : hkReferencedObject {
    hkPointerMapBase m_map;    // +8
    virtual void registerVtable(const void* vtable, const hkClass* klass);              // 2
    virtual const hkClass* getClassFromVirtualInstance(const void* obj) const;          // 3
    virtual void merge(const hkVtableClassRegistry& from);                              // 4
    void registerList(const hkTypeInfo* const* infos, const hkClass* const* classes);
};

struct hkBuiltinTypeRegistry : hkReferencedObject {
    virtual hkFinishLoadedObjectRegistry* getLoadedObjectRegistry() = 0;   // 2
    virtual hkClassNameRegistry* getClassNameRegistry() = 0;               // 3
    virtual hkVtableClassRegistry* getVtableClassRegistry() = 0;           // 4
    virtual void addType(hkTypeInfo* info, hkClass* klass);                // 5
    static hkBuiltinTypeRegistry* s_instance;    // DAT_016e60a8
};

struct hkDefaultBuiltinTypeRegistry : hkBuiltinTypeRegistry {
    hkClassNameRegistry*          m_classNameRegistry;       // +8
    hkFinishLoadedObjectRegistry* m_loadedObjectRegistry;    // +0xc
    hkVtableClassRegistry*        m_vtableClassRegistry;     // +0x10
    hkDefaultBuiltinTypeRegistry();
    ~hkDefaultBuiltinTypeRegistry();
    virtual hkFinishLoadedObjectRegistry* getLoadedObjectRegistry() { return m_loadedObjectRegistry; }
    virtual hkClassNameRegistry* getClassNameRegistry() { return m_classNameRegistry; }
    virtual hkVtableClassRegistry* getVtableClassRegistry() { return m_vtableClassRegistry; }
    HK_CLASS_ALLOC(hkDefaultBuiltinTypeRegistry, 0x15)
};
extern const hkClass* const g_StaticLinkedClasses[];          // 0x14645e8
extern const hkTypeInfo* const g_StaticLinkedTypeInfos[];     // 0x1464480
extern const hkClass g_hkReferencedObjectClass;               // first entry, unrolled by the optimizer
hkBuiltinTypeRegistry* hkBuiltinTypeRegistry::s_instance;

// ---------------------------------------------------------------- packfile data
struct hkPackfileChunk { void* pointer; int numBytes; int memClass; };
struct hkPackfileData : hkReferencedObject {                 // "AllocatedData", size 0x20
    hkArray<void*>          m_memory;     // +8
    hkArray<hkPackfileChunk> m_chunks;    // +0x14
    void addChunk(void* p, int n, int memClass) {
        hkPackfileChunk c; c.pointer = p; c.numBytes = n; c.memClass = memClass;
        m_chunks.pushBack(c);
    }
};

// ---------------------------------------------------------------- update tracker
struct hkObjectUpdateTracker : hkReferencedObject {
    virtual void addAllocation(void* p) = 0;                 // 2
    virtual void addChunk(void* p, int n, int memClass) = 0; // 3
    virtual void objectPointedBy(void* object, void* fromWhere) = 0;   // 4
    virtual void replaceObject(void* oldObject, void* newObject, const hkClass* newClass) = 0; // 5
    virtual void addFinish(void* newObject, const char* className) = 0; // 6
    virtual void removeFinish(void* oldObject) = 0;          // 7
};

struct hkPointerMapItem { void** pointer; int next; };
// hkPointerMultiMap<void*, void*>: items chained by 'next' (-1 ends), map holds the chain head index.
struct hkPointerMultiMap {
    hkArray<hkPointerMapItem> m_items;   // +0
    hkPointerMapBase          m_map;     // +0xc
    ~hkPointerMultiMap() { m_map.~hkPointerMapBase(); m_items.quickFree(0x14); }
    void insert(hkUlong32 key, void** const& value) {
        hkUlong32 head = m_map.getWithDefault(key, 0xffffffff);
        hkPointerMapItem it; it.pointer = value; it.next = (int)head;
        m_items.pushBack(it);
        m_map.insert(key, (hkUlong32)(m_items.m_size - 1));
    }
};

extern const char* hkClass_getFlagPtr(const hkClass* c, const hkClass** tmp);   // FUN_01080450 (class has-vtable style flag byte)

struct hkPackfileObjectUpdateTracker : hkObjectUpdateTracker {
    hkPackfileData*   m_packfileData;     // +8
    hkPointerMultiMap m_pointersTo;       // +0xc (array) / +0x18 (map)
    hkPointerMapBase  m_finish;           // +0x24 : object -> class name
    void*             m_topLevelObject;   // +0x30
    const char*       m_topLevelClassName;// +0x34
    hkPackfileObjectUpdateTracker(hkPackfileData* d);
    ~hkPackfileObjectUpdateTracker();
    virtual void addAllocation(void* p);
    virtual void addChunk(void* p, int n, int memClass);
    virtual void objectPointedBy(void* object, void* fromWhere);
    virtual void replaceObject(void* oldObject, void* newObject, const hkClass* newClass);
    virtual void addFinish(void* newObject, const char* className);
    virtual void removeFinish(void* oldObject);
    HK_CLASS_ALLOC(hkPackfileObjectUpdateTracker, 0x12)
};

// ---------------------------------------------------------------- packfile reader
struct hkStreamReader {
    virtual void d0(); virtual void d1(); virtual void d2();
    virtual int read(void* buf, int nbytes);     // +0xc
};
struct hkPackfileHeader {
    int m_magic[2];                          // +0
    int m_userTag;                           // +8
    int m_fileVersion;                       // +0xc
    uint8_t m_layoutRules[4];                // +0x10
    int m_numSections;                       // +0x14
    int m_contentsSectionIndex;              // +0x18
    int m_contentsSectionOffset;             // +0x1c
    int m_contentsClassNameSectionIndex;     // +0x20
    int m_contentsClassNameSectionOffset;    // +0x24
};
struct hkPackfileSectionHeader {             // stride 0x30
    char m_tag[0x14];
    int m_absoluteDataStart;                 // +0x14
    int m_localFixupsOffset;                 // +0x18  (pairs: src, dst)
    int m_globalFixupsOffset;                // +0x1c  (triples: src, section, dst)
    int m_virtualFixupsOffset;               // +0x20  (triples: src, section, classNameOffset)
    int m_exportsOffset;                     // +0x24
    int m_endOffset;                         // +0x28  (section size)
    int m_pad2c;
};
struct hkVariant { void* m_object; const hkClass* m_class; };
struct hkStructureLayout {
    uint8_t m_rules[4];
    hkStructureLayout();
    void computeMemberOffsetsInplace(const hkClass* k, hkPointerMapBase& done);   // FUN_0112c4c0
};
void hkPackfileReader_convertClassVersion1Inplace(hkClass* k);   // hkPackfileReader::convertClassVersion1Inplace

struct hkBinaryPackfileReader : hkReferencedObject {
    hkPackfileData*          m_packfileData;     // +8
    hkPackfileHeader*        m_header;           // +0xc
    hkPackfileSectionHeader* m_sections;         // +0x10
    hkArray<void*>           m_sectionDataArr;   // +0x14 (hkInplaceArray<void*,16>)
    void*                    m_sectionDataStorage[16];  // +0x20
    int                      m_streamOffset;     // +0x60
    hkArray<hkVariant>*      m_loadedObjects;    // +0x64
    hkPackfileObjectUpdateTracker* m_tracker;    // +0x68

    hkBinaryPackfileReader();
    ~hkBinaryPackfileReader();
    virtual hkResult loadEntireFile(hkStreamReader* reader);                                   // 2
    virtual void* getContentsWithRegistry(const char* className, const hkFinishLoadedObjectRegistry* finish); // 3
    virtual void* getContents(const char* className);                                          // 4
    virtual const char* getContentsClassName() const;                                          // 5
    virtual hkArray<hkVariant>& getLoadedObjects();                                            // 6
    virtual hkObjectUpdateTracker& getUpdateTracker();                                         // 7
    virtual const char* getOriginalContentsVersion() const { return 0; }                       // 8
    virtual void slot9() {}                                                                    // 9
    virtual hkResult loadEntireFileInplace(void* data, int n) { return HK_FAILURE; }           // 10
    virtual int getSectionIndex(const char* tag) const { return -1; }                          // 11
    virtual void* getSectionDataByIndex(int sectionIndex, int offset) { return 0; }            // 12

    hkResult loadFileHeader(hkStreamReader* reader, hkPackfileHeader* dst);
    hkResult loadSectionHeadersNoSeek(hkStreamReader* reader, hkPackfileSectionHeader* dst);
    hkResult fixupGlobalReferences();
    hkResult loadSectionNoSeek(hkStreamReader* reader, int sectionIndex, void* buf);
    hkResult finishLoadedObjects(const hkFinishLoadedObjectRegistry& finish);
    HK_CLASS_ALLOC(hkBinaryPackfileReader, 0x12)
};

// @ 0x0112adf0
hkResult hkBinaryPackfileReader::loadSectionNoSeek(hkStreamReader* reader, int sectionIndex, void* buf)
{
    hkPackfileSectionHeader* sh = &m_sections[sectionIndex];
    int size = sh->m_endOffset;
    char* base = (char*)buf;
    if (base == 0) {
        base = (char*)g_hkMemory->allocateChunk(size, 5);
        m_packfileData->m_memory.pushBack(base);
    }
    if (reader->read(base, size) != size)
        return HK_FAILURE;

    // local fixups: pairs (srcOffset, dstOffset); PTR32 slot
    const int* fix = (const int*)(base + sh->m_localFixupsOffset);
    int i = 0;
    while (i < (sh->m_globalFixupsOffset - sh->m_localFixupsOffset) / 4) {
        if (fix[i] != -1)
            *(char**)(base + fix[i]) = base + fix[i + 1];     // PTR32
        i += 2;
    }

    m_sectionDataArr.m_data[sectionIndex] = base;
    hkPackfileHeader* h = m_header;
    if (sectionIndex == h->m_contentsClassNameSectionIndex && h->m_contentsClassNameSectionOffset >= 0
        && h->m_fileVersion < 3) {
        const hkClass* c = (const hkClass*)getSectionDataByIndex(sectionIndex, h->m_contentsClassNameSectionOffset);
        h->m_contentsClassNameSectionOffset = (int)(uintptr_t)(c->getName() - base);
    }
    return HK_SUCCESS;
}

// @ 0x0112af00
hkResult hkBinaryPackfileReader::finishLoadedObjects(const hkFinishLoadedObjectRegistry& finish)
{
    if (m_tracker == 0) {
        for (int s = 0; s < m_header->m_numSections; ++s) {
            char* data = (char*)m_sectionDataArr.m_data[s];
            if (data) {
                hkPackfileSectionHeader* sh = &m_sections[s];
                const int* vf = (const int*)(data + sh->m_virtualFixupsOffset);
                for (int j = 0; j < (sh->m_endOffset - sh->m_virtualFixupsOffset) / 4; j += 3) {
                    if (vf[j] != -1) {
                        const char* name = (const char*)getSectionDataByIndex(vf[j + 1], vf[j + 2]);
                        finish.finishLoadedObject(data + vf[j], name);
                    }
                }
            }
        }
    } else {
        // walk the tracker's object->className map (hkPointerMapBase: keys[0..hashMod], values after)
        hkPointerMapBase& m = m_tracker->m_finish;
        int hashMod = m.m_hashMod;
        int i = 0;
        if (hashMod >= 0) {
            const hkUlong32* k = m.m_elem;
            do {
                if (*k != 0) break;
                ++i; ++k;
            } while (i <= hashMod);
        }
        while (i <= hashMod) {
            finish.finishLoadedObject((void*)m.m_elem[i], (const char*)m.m_elem[hashMod + i + 1]);
            hashMod = m.m_hashMod;
            ++i;
            if (i <= hashMod) {
                const hkUlong32* k = m.m_elem + i;
                do {
                    if (*k != 0) break;
                    ++i; ++k;
                } while (i <= hashMod);
            }
        }
    }
    return HK_SUCCESS;
}

// @ 0x0112b050
// hkPointerMultiMap<void*,void*> destructor (inlined in the tracker destructor)
static void hkPointerMultiMap_destruct(hkPointerMultiMap* self)
{
    self->m_map.~hkPointerMapBase();
    if (self->m_items.m_capacityAndFlags >= 0)
        getThreadMemory()->deallocateChunk(self->m_items.m_data,
            (self->m_items.m_capacityAndFlags & HK_ARRAY_FLAG_MASK) << 3, 0x14);
}

// @ 0x0112b090
hkResult hkBinaryPackfileReader::loadEntireFile(hkStreamReader* reader)
{
    if (loadFileHeader(reader, 0) == HK_SUCCESS && loadSectionHeadersNoSeek(reader, 0) == HK_SUCCESS) {
        for (int i = 0; i < m_header->m_numSections; ++i) {
            if (loadSectionNoSeek(reader, i, 0) == HK_FAILURE)
                return HK_FAILURE;
        }
        return fixupGlobalReferences() == HK_FAILURE ? HK_FAILURE : HK_SUCCESS;
    }
    return HK_FAILURE;
}

// @ 0x0112b110
hkArray<hkVariant>& hkBinaryPackfileReader::getLoadedObjects()
{
    if (m_loadedObjects != 0)
        return *m_loadedObjects;

    hkArray<hkVariant>* out = (hkArray<hkVariant>*)g_hkMemory->allocateObject(0xc, 0x14);
    if (out) { out->m_data = 0; out->m_size = 0; out->m_capacityAndFlags = HK_ARRAY_DONT_DEALLOCATE; }
    m_loadedObjects = out;

    int classIndex = getSectionIndex("__classindex__");
    int dataIndex = getSectionIndex("__dataindex__");
    if (classIndex >= 0 && dataIndex >= 0) {
        hkArray<void*> classes;
        classes.m_data = 0; classes.m_size = 0; classes.m_capacityAndFlags = HK_ARRAY_DONT_DEALLOCATE;
        unsigned int numClasses = (unsigned int)m_sections[classIndex].m_endOffset >> 3;
        if ((int)numClasses > 0)
            hkArray_reserve(&classes, (int)numClasses, 4);
        const int* cidx = (const int*)getSectionDataByIndex(classIndex, 0);
        int i = 0;
        while (i < (int)numClasses) {
            if (cidx[i * 2] == -1) break;
            void* k = getSectionDataByIndex(cidx[i * 2], cidx[i * 2 + 1]);
            classes.m_data[classes.m_size] = k;
            classes.m_size = classes.m_size + 1;
            ++i;
        }
        if (m_header->m_fileVersion == 1) {
            for (int c = 0; c < classes.m_size; ++c)
                hkPackfileReader_convertClassVersion1Inplace((hkClass*)classes.m_data[c]);
        }

        unsigned int numObjects = (unsigned int)m_sections[dataIndex].m_endOffset / 12u;
        int cap = out->m_capacityAndFlags & HK_ARRAY_FLAG_MASK;
        if (cap < (int)numObjects) {
            int newCap = cap + cap;
            if ((int)numObjects >= newCap) newCap = (int)numObjects;
            hkArray_reserve(out, newCap, 8);
        }
        const int* obj = (const int*)getSectionDataByIndex(dataIndex, 0);
        for (unsigned int n = numObjects; n != 0; --n, obj += 3) {
            int sec = obj[0], off = obj[1], cls = obj[2];
            if (sec != -1 && cls != -1) {
                hkVariant v;
                v.m_object = getSectionDataByIndex(sec, off);
                v.m_class = (const hkClass*)classes.m_data[cls];
                out->pushBack(v);
            }
        }

        hkStructureLayout layout;
        hkPointerMapBase done;
        for (int o = 0; o < out->m_size; ++o)
            layout.computeMemberOffsetsInplace(out->m_data[o].m_class, done);
        done.~hkPointerMapBase();
        classes.quickFree(0x14);
    }
    return *m_loadedObjects;
}

// @ 0x0112b390
void* hkBinaryPackfileReader::getContentsWithRegistry(const char* className, const hkFinishLoadedObjectRegistry* finish)
{
    if (finish != 0)
        finishLoadedObjects(*finish);

    void* top;
    const char* name;
    if (m_tracker == 0) {
        int s = m_header->m_contentsSectionIndex, o = m_header->m_contentsSectionOffset;
        if (s < 0 || o < 0)
            top = getSectionDataByIndex(getSectionIndex("__data__"), 0);
        else
            top = getSectionDataByIndex(s, o);
        int cs = m_header->m_contentsClassNameSectionIndex, co = m_header->m_contentsClassNameSectionOffset;
        if (cs < 0 || co < 0) name = 0;
        else name = (const char*)getSectionDataByIndex(cs, co);
    } else {
        top = m_tracker->m_topLevelObject;
        name = m_tracker->m_topLevelClassName;
    }
    if (className != 0 && name != 0) {
        if (hkString::strCmp(className, name) != 0)
            return 0;
    }
    return top;
}

// @ 0x0112b460
hkPackfileObjectUpdateTracker::hkPackfileObjectUpdateTracker(hkPackfileData* d)
{
    m_packfileData = d;
    m_pointersTo.m_items.m_data = 0; m_pointersTo.m_items.m_size = 0;
    m_pointersTo.m_items.m_capacityAndFlags = HK_ARRAY_DONT_DEALLOCATE;
    m_topLevelObject = 0;
    m_topLevelClassName = 0;
}

// @ 0x0112b4d0
void hkPackfileObjectUpdateTracker::addAllocation(void* p)
{
    m_packfileData->m_memory.pushBack(p);
}

// @ 0x0112b520
void hkPackfileData_addChunk(hkPackfileData* self, void* p, int n, int memClass)
{
    self->addChunk(p, n, memClass);
}

// @ 0x0112b570
void hkPackfileObjectUpdateTracker::replaceObject(void* oldObject, void* newObject, const hkClass* newClass)
{
    if (oldObject == m_topLevelObject) {
        m_topLevelObject = newObject;
        m_topLevelClassName = newClass->getName();
    }
    hkUlong32 idx = m_pointersTo.m_map.getWithDefault((hkUlong32)(uintptr_t)oldObject, 0xffffffff);
    m_pointersTo.m_map.insert((hkUlong32)(uintptr_t)newObject, idx);
    while ((int)idx != -1) {
        *m_pointersTo.m_items.m_data[(int)idx].pointer = newObject;
        idx = (hkUlong32)m_pointersTo.m_items.m_data[(int)idx].next;
    }
    if (newClass != 0) {
        const hkClass* tmp = newClass;
        if (*hkClass_getFlagPtr(newClass, &tmp) != 0)
            addFinish(newObject, newClass->getName());
    }
}

// @ 0x0112b600
void hkPackfileObjectUpdateTracker::objectPointedBy(void* object, void* fromWhere)
{
    void** w = (void**)fromWhere;
    m_pointersTo.insert((hkUlong32)(uintptr_t)object, w);
}

// @ 0x0112b620
void hkPointerMultiMap_insert(hkPointerMultiMap* self, void* key, void** const& value)
{
    self->insert((hkUlong32)(uintptr_t)key, value);
}

// @ 0x0112b680
hkPackfileObjectUpdateTracker::~hkPackfileObjectUpdateTracker()
{
    m_finish.~hkPointerMapBase();
    hkPointerMultiMap_destruct(&m_pointersTo);
}

// @ 0x0112b6c0
hkBinaryPackfileReader::hkBinaryPackfileReader()
{
    m_header = 0;
    m_sections = 0;
    m_sectionDataArr.m_size = 0;
    m_sectionDataArr.m_capacityAndFlags = (int)0x80000010;
    m_sectionDataArr.m_data = m_sectionDataStorage;
    m_streamOffset = 0;
    m_loadedObjects = 0;
    m_tracker = 0;
    hkPackfileData* d = (hkPackfileData*)g_hkMemory->allocateObject(0x20, 0x12);
    *(uint16_t*)((char*)d + 4) = 0x20;
    d->m_referenceCount = 1;
    d->m_memory.m_data = 0; d->m_memory.m_size = 0; d->m_memory.m_capacityAndFlags = HK_ARRAY_DONT_DEALLOCATE;
    d->m_chunks.m_data = 0; d->m_chunks.m_size = 0; d->m_chunks.m_capacityAndFlags = HK_ARRAY_DONT_DEALLOCATE;
    m_packfileData = d;
}

// @ 0x0112b740
hkBinaryPackfileReader::~hkBinaryPackfileReader()
{
    m_packfileData->removeReference();
    if (m_tracker != 0) delete m_tracker;
    if (m_loadedObjects != 0) {
        m_loadedObjects->quickFree(0x14);
        g_hkMemory->deallocateObject(m_loadedObjects, 0xc, 0x14);
    }
    m_sectionDataArr.quickFree(0x14);
}

// @ 0x0112b7f0
hkObjectUpdateTracker& hkBinaryPackfileReader::getUpdateTracker()
{
    if (m_tracker == 0) {
        m_tracker = new hkPackfileObjectUpdateTracker(m_packfileData);
        for (int s = 0; s < m_header->m_numSections; ++s) {
            char* data = (char*)m_sectionDataArr.m_data[s];
            if (data != 0) {
                hkPackfileSectionHeader* sh = &m_sections[s];
                const int* gf = (const int*)(data + sh->m_globalFixupsOffset);
                for (int j = 0; j < (sh->m_virtualFixupsOffset - sh->m_globalFixupsOffset) / 4; j += 3) {
                    if (gf[j] != -1) {
                        void* target = getSectionDataByIndex(gf[j + 1], gf[j + 2]);
                        m_tracker->objectPointedBy(target, data + gf[j]);
                    }
                }
                const int* vf = (const int*)(data + sh->m_virtualFixupsOffset);
                for (int j = 0; j < (sh->m_endOffset - sh->m_virtualFixupsOffset) / 4; j += 3) {
                    if (vf[j] != -1) {
                        void* obj = getSectionDataByIndex(s, vf[j]);
                        const char* name = (const char*)getSectionDataByIndex(vf[j + 1], vf[j + 2]);
                        m_tracker->addFinish(obj, name);
                    }
                }
            }
        }
        int s = m_header->m_contentsSectionIndex, o = m_header->m_contentsSectionOffset;
        if (s < 0 || o < 0)
            m_tracker->m_topLevelObject = getSectionDataByIndex(getSectionIndex("__data__"), 0);
        else
            m_tracker->m_topLevelObject = getSectionDataByIndex(s, o);
        int cs = m_header->m_contentsClassNameSectionIndex, co = m_header->m_contentsClassNameSectionOffset;
        if (cs >= 0 && co >= 0) {
            m_tracker->m_topLevelClassName = (const char*)getSectionDataByIndex(cs, co);
            return *m_tracker;
        }
        m_tracker->m_topLevelClassName = 0;
    }
    return *m_tracker;
}

// @ 0x0112ba20
void hkBuiltinTypeRegistry::addType(hkTypeInfo* info, hkClass* klass)
{
    getClassNameRegistry()->registerClass(klass, klass->getName());
    getLoadedObjectRegistry()->registerTypeInfo(info);
    getVtableClassRegistry()->registerVtable(info->m_vtable, klass);
}

// @ 0x0112ba70
void hkClassNameRegistry::registerList(const hkClass* const* classes)
{
    const hkClass* k = *classes;
    while (k != 0) {
        registerClass(k, 0);
        k = *++classes;
    }
}

// @ 0x0112baa0
void hkClassNameRegistry::registerClass(const hkClass* klass, const char* name)
{
    if (name == 0) name = klass->getName();
    m_map.insert(name, (hkUlong32)(uintptr_t)klass);
}

// @ 0x0112bad0
const hkClass* hkClassNameRegistry::getClassByName(const char* name) const
{
    return (const hkClass*)m_map.getWithDefault(name, 0);
}

// @ 0x0112baf0
void hkFinishLoadedObjectRegistry::registerTypeInfo(const hkTypeInfo* info)
{
    m_map.insert(info->m_name, (hkUlong32)(uintptr_t)info);
}

// @ 0x0112bb10
void hkFinishLoadedObjectRegistry::finishLoadedObject(void* obj, const char* className) const
{
    const hkTypeInfo* t = (const hkTypeInfo*)m_map.getWithDefault(className, 0);
    if (t != 0 && t->m_finishLoadedObject != 0)
        t->m_finishLoadedObject(obj);
}

// @ 0x0112bb40
// merge: copy every entry of 'from' into this map (shared by hkClassNameRegistry/hkFinishLoadedObjectRegistry)
void hkFinishLoadedObjectRegistry::merge(const hkFinishLoadedObjectRegistry& from)
{
    void* it = from.m_map.getIterator();
    while (from.m_map.isValid(it)) {
        const char* key = from.m_map.getKey(it);
        hkUlong32 value = from.m_map.getValue(it);
        m_map.insert(key, value);
        it = from.m_map.getNext(it);
    }
}

// @ 0x0112bbd0
const hkClass* hkVtableClassRegistry::getClassFromVirtualInstance(const void* obj) const
{
    return (const hkClass*)m_map.getWithDefault(*(const hkUlong32*)obj, 0);
}

// @ 0x0112bbf0
// scalar deleting destructor of hkVtableClassRegistry
void hkVtableClassRegistry_deletingDtor(hkVtableClassRegistry* self, unsigned flags)
{
    delete self;
}

// @ 0x0112bc30
// scalar deleting destructor of hkFinishLoadedObjectRegistry / hkClassNameRegistry
void hkFinishLoadedObjectRegistry_deletingDtor(hkFinishLoadedObjectRegistry* self, unsigned flags)
{
    delete self;
}

// @ 0x0112bc70
hkDefaultBuiltinTypeRegistry::hkDefaultBuiltinTypeRegistry()
{
    m_classNameRegistry = new hkClassNameRegistry();
    m_classNameRegistry->registerList(g_StaticLinkedClasses);

    m_loadedObjectRegistry = new hkFinishLoadedObjectRegistry();
    const hkTypeInfo* const* ti = g_StaticLinkedTypeInfos;
    if (*ti != 0) {
        do {
            m_loadedObjectRegistry->registerTypeInfo(*ti);
            ++ti;
        } while (*ti != 0);
    }

    m_vtableClassRegistry = new hkVtableClassRegistry();
    m_vtableClassRegistry->registerList(g_StaticLinkedTypeInfos, g_StaticLinkedClasses);
}

// @ 0x0112bd80
hkDefaultBuiltinTypeRegistry::~hkDefaultBuiltinTypeRegistry()
{
    m_classNameRegistry->removeReference();
    m_loadedObjectRegistry->removeReference();
    m_vtableClassRegistry->removeReference();
}

// @ 0x0112bdf0
hkDefaultBuiltinTypeRegistry* hkDefaultBuiltinTypeRegistry_create()
{
    return new hkDefaultBuiltinTypeRegistry();
}

// @ 0x0112be10
void* hkBinaryPackfileReader_getContents(hkBinaryPackfileReader* self, const char* className)
{
    return self->getContentsWithRegistry(className, hkBuiltinTypeRegistry::s_instance->getLoadedObjectRegistry());
}
// --- equivalence checker address annotations
    void* operator new(unsigned int); // 0x006abeb0
    extern unsigned long g_hkThreadMemoryTlsIndex; // 0x016e4174

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
