#pragma once
// Havok 3.1.0 (as statically linked into SporeApp.exe) - shared class declarations for the base-library
// slices s0107e670, s01080450 and s0107f4a0. Layouts come from the binary (vtable dumps + member offsets);
// the Havok 6.x headers were used for naming only. Slot comments are vtable slot numbers (4 bytes each on x86).
#include "types.h"
#include <stddef.h>

#if defined(_MSC_VER)
#define HK_BREAKPOINT() __debugbreak()
#else
#define HK_BREAKPOINT() __builtin_trap()
#endif

typedef int16_t hkInt16;
typedef uint16_t hkUint16;
typedef uint8_t hkUint8;
typedef uint32_t hkUint32;
typedef uint64_t hkUint64;
typedef size_t hkUlong;   // pointer-sized unsigned (address arithmetic)

enum hkResult { HK_SUCCESS = 0, HK_FAILURE = 1 };

// A user-declared constructor makes this non-POD, so MSVC returns it through a hidden pointer, as the binary does.
class hkBool
{
public:
	hkBool(bool b) : m_bool(b ? 1 : 0) {}
	operator bool() const { return m_bool != 0; }
private:
	char m_bool;
};

// HK_MEMORY_CLASS values seen in the binary.
enum
{
	HK_MEMORY_CLASS_ARRAY = 0x14,
	HK_MEMORY_CLASS_BASE = 0x15,
	HK_MEMORY_CLASS_STREAM = 0x17
};

struct hkMemoryStatistics
{
	int m_numBigBlocks;       // 0x10 in hkMemory
	int m_bigBlockBytes;      // 0x14
	int m_peakBigBlockBytes;  // 0x18
	int m_numPages;           // 0x1c
	int m_pageSize;           // 0x20
	int m_pageAlignment;      // 0x24
	int m_inUseBytes;         // 0x28
};

class hkOstream;

// Not an hkReferencedObject: slot 0 is allocate(). hkMemory::s_instance is the global at 0x016E4178.
class hkMemory
{
public:
	virtual void* allocate(int nbytes, int cl);                          // 0
	virtual void deallocate(void* p);                                    // 1
	virtual void* alignedAllocate(int alignment, int nbytes, int cl);    // 2
	virtual void alignedDeallocate(void* p);                             // 3
	virtual void* allocateChunk(int nbytes, int cl);                     // 4
	virtual void deallocateChunk(void* p, int nbytes, int cl);           // 5
	virtual void* allocateChunkByRow(int row, int cl);                   // 6
	virtual void deallocateChunkByRow(void* p, int row);                 // 7
	virtual void slot8();                                                // 8 (0x00B1FBF0)
	virtual void printStatistics(hkOstream* o);                          // 9
	virtual int getAllocatedSize(int nbytes);                            // 10
	virtual void getStatSynopsis(hkMemoryStatistics* s);                 // 11
	virtual bool slot12();                                               // 12 (0x01091960, returns 0)
	virtual ~hkMemory() {}                                               // 13 (deleting dtor 0x0107FBC0 for the pool)

	static hkMemory* s_instance;
	static void replaceInstance(hkMemory* m);

	hkMemory();                      // 0x0107DC90 (not in these slices)

	int m_unk04;                     // 0x04
	int m_unk08;                     // 0x08 (0x7FFFFFFF)
	int m_unk0c;                     // 0x0c (1)
	hkMemoryStatistics m_stats;      // 0x10..0x2b
};

class hkReferencedObject
{
public:
	virtual ~hkReferencedObject() {}                                     // 0
	virtual void slot1() {}                                              // 1 (0x0052E650, empty)

	// HK_DECLARE_CLASS_ALLOCATOR with the stream memory class, as the binary allocates these objects.
	static void* operator new(size_t nbytes)
	{
		void* p = hkMemory::s_instance->allocateChunk((int)nbytes, HK_MEMORY_CLASS_STREAM);
		((hkReferencedObject*)p)->m_memSizeAndFlags = (hkInt16)nbytes;
		return p;
	}
	static void operator delete(void* p)
	{
		hkMemory::s_instance->deallocateChunk(p, ((hkReferencedObject*)p)->m_memSizeAndFlags, HK_MEMORY_CLASS_STREAM);
	}
	static void* operator new(size_t, void* p) { return p; }
	static void operator delete(void*, void*) {}

	// memSize == 0 means the object is not heap-owned and is never reference counted.
	void addReference() { if (m_memSizeAndFlags != 0) ++m_referenceCount; }
	void removeReference()
	{
		if (m_memSizeAndFlags != 0)
		{
			if (--m_referenceCount == 0)
				delete this;
		}
	}

	hkInt16 m_memSizeAndFlags;  // 0x04
	hkInt16 m_referenceCount;   // 0x06

protected:
	hkReferencedObject() : m_referenceCount(1) {}
};

//
// Streams
//
class hkStreamReader : public hkReferencedObject
{
public:
	enum SeekWhence { STREAM_SET = 0, STREAM_CUR = 1, STREAM_END = 2 };

	virtual hkBool isOk() const = 0;                              // 2
	virtual int read(void* buf, int nbytes) = 0;                  // 3
	virtual int skip(int nbytes);                                 // 4  0x010808F0
	virtual hkBool markSupported() const;                         // 5
	virtual hkResult setMark(int markLimit);                      // 6
	virtual hkResult rewindToMark();                              // 7
	virtual hkBool seekTellSupported() const;                     // 8
	virtual hkResult seek(int offset, SeekWhence whence);         // 9
	virtual int tell() const;                                     // 10
};

class hkSeekableStreamReader : public hkStreamReader
{
public:
	virtual hkResult setMark(int markLimit);                      // 0x0107E740
	virtual hkResult rewindToMark();                              // 0x0107E760
	int m_markPos;                                                // 0x08

protected:
	hkSeekableStreamReader() : m_markPos(-1) {}
};

class hkStreamWriter : public hkReferencedObject
{
public:
	enum SeekWhence { STREAM_SET = 0, STREAM_CUR = 1, STREAM_END = 2 };

	virtual hkBool isOk() const = 0;                              // 2
	virtual int write(const void* buf, int nbytes) = 0;           // 3
	virtual void flush();                                         // 4
	virtual hkBool seekTellSupported() const;                     // 5
	virtual hkResult seek(int offset, SeekWhence whence);         // 6
	virtual int tell() const;                                     // 7
};

struct _iobuf;
typedef struct _iobuf FILE;

class hkStdioStreamReader : public hkSeekableStreamReader
{
public:
	hkStdioStreamReader(const char* name);                        // 0x0107E700
	virtual ~hkStdioStreamReader();                               // 0x0107E7E0 (deleting)
	virtual hkBool isOk() const;
	virtual int read(void* buf, int nbytes);
	virtual hkResult seek(int offset, SeekWhence whence);
	virtual int tell() const;

	FILE* m_file;                                                 // 0x0c
	bool m_ok;                                                    // 0x10
};

class hkStdioStreamWriter : public hkStreamWriter
{
public:
	hkStdioStreamWriter(const char* name);                        // 0x0107E890
	virtual ~hkStdioStreamWriter();                               // 0x0107E9A0 (deleting)
	virtual hkBool isOk() const;                                  // 0x0107E950
	virtual int write(const void* buf, int nbytes);
	virtual void flush();
	virtual hkResult seek(int offset, SeekWhence whence);
	virtual int tell() const;
	void close();                                                 // 0x0107E910

	FILE* m_file;                                                 // 0x08
	bool m_ownsFile;                                              // 0x0c
};

class hkBufferedStreamReader : public hkStreamReader
{
public:
	hkBufferedStreamReader(hkStreamReader* s, int bufSize);       // 0x01080830
	virtual ~hkBufferedStreamReader();                            // 0x01080890 (deleting)
	virtual hkBool isOk() const;
	virtual int read(void* buf, int nbytes);
	virtual int skip(int nbytes);
	virtual hkBool markSupported() const;
	virtual hkResult setMark(int markLimit);
	virtual hkResult rewindToMark();
	virtual hkBool seekTellSupported() const;
	virtual hkResult seek(int offset, SeekWhence whence);
	virtual int tell() const;
	virtual hkResult refillBuffer();                              // 11
	void prepareBufferForRefill();                                // 0x01080540

	hkStreamReader* m_stream;                                     // 0x08
	char* m_buf;                                                  // 0x0c
	int m_current;                                                // 0x10
	int m_end;                                                    // 0x14
	int m_bufSize;                                                // 0x18
	int m_markPos;                                                // 0x1c
	int m_markLimit;                                              // 0x20
};

class hkBufferedStreamWriter : public hkStreamWriter
{
public:
	hkBufferedStreamWriter(hkStreamWriter* s, int bufSize);       // 0x01080C30
	hkBufferedStreamWriter(void* buf, int bufSize, hkBool nullTerminate); // 0x01080B70
	virtual ~hkBufferedStreamWriter();                            // 0x01080BD0 (+ deleting 0x01080C90)
	virtual hkBool isOk() const;
	virtual int write(const void* buf, int nbytes);
	virtual void flush();
	virtual hkBool seekTellSupported() const;
	virtual hkResult seek(int offset, SeekWhence whence);
	virtual int tell() const;
	int flushBuffer();                                            // 0x01080950

	hkStreamWriter* m_stream;                                     // 0x08
	char* m_buf;                                                  // 0x0c
	int m_current;                                                // 0x10
	int m_bufSize;                                                // 0x14
	bool m_ownBuf;                                                // 0x18
};

class hkMemoryStreamReader : public hkStreamReader
{
public:
	enum MemoryType { MEMORY_COPY = 0, MEMORY_TAKE = 1, MEMORY_INPLACE = 2 };
	hkMemoryStreamReader(const void* mem, int size, MemoryType t); // 0x010801D0
	virtual ~hkMemoryStreamReader();                               // 0x01080240 (deleting)
	virtual hkBool isOk() const;
	virtual int read(void* buf, int nbytes);
	virtual int skip(int nbytes);
	virtual hkBool markSupported() const;
	virtual hkResult setMark(int markLimit);
	virtual hkResult rewindToMark();
	virtual hkResult seek(int offset, SeekWhence whence);

	const char* m_buf;      // 0x08
	int m_pos;              // 0x0c
	int m_length;           // 0x10
	int m_mark;             // 0x14
	MemoryType m_memType;   // 0x18
};

class hkOstream : public hkReferencedObject
{
public:
	hkOstream(void* buf, int bufSize, hkBool nullTerminate);      // 0x0107EF80
	virtual ~hkOstream();                                         // 0x0107EFD0 (deleting 0x0107F000)
	hkOstream& operator<<(char c);                                // 0x0107EE10
	hkOstream& operator<<(const char* s);                         // 0x0107EE30
	hkOstream& operator<<(int i);                                 // 0x0107EE80 ("%i")
	hkOstream& operator<<(unsigned int u);                        // 0x0107EED0 ("%u")
	void printf(const char* fmt, ...);                            // 0x0107EF20

	hkStreamWriter* m_writer;                                     // 0x08
};

class hkStreambufFactory : public hkReferencedObject
{
public:
	virtual hkStreamReader* openReader(const char* name) = 0;     // 2
	virtual hkStreamWriter* openWriter(const char* name) = 0;     // 3
	static void* operator new(size_t nbytes)
	{
		void* p = hkMemory::s_instance->allocateChunk((int)nbytes, HK_MEMORY_CLASS_BASE);
		((hkReferencedObject*)p)->m_memSizeAndFlags = (hkInt16)nbytes;
		return p;
	}
	static void operator delete(void* p)
	{
		hkMemory::s_instance->deallocateChunk(p, ((hkReferencedObject*)p)->m_memSizeAndFlags, HK_MEMORY_CLASS_BASE);
	}
};

class hkDefaultStreambufFactory : public hkStreambufFactory
{
public:
	virtual hkStreamReader* openReader(const char* name);         // 0x0107E670
	virtual hkStreamWriter* openWriter(const char* name);         // 0x0107E820
};

//
// Arrays (layout shared by every hkArray<T>: data, size, capacity | flags)
//
struct hkArrayUtil
{
	static void _reserveMore(void* array, int elemSize);                               // 0x0107F530
	static void _reserveExactly(void* array, int newCapacity, int elemSize);           // 0x0107F4A0
	static void _reduce(void* array, int elemSize, void* inplaceStorage, int inplaceCapacity); // 0x0107F5D0
};

class hkThreadMemory
{
public:
	static void* operator new(size_t, void* p) { return p; }
	void* allocateChunk(int nbytes, int cl);             // 0x0107DAA0
	void deallocateChunk(void* p, int nbytes, int cl);   // 0x0107DB10
	static hkThreadMemory& getInstance();                // TlsGetValue(g_hkThreadMemoryTls), defined below
	static void replaceInstance(hkThreadMemory* t);      // 0x0107DBD0
	hkThreadMemory(hkMemory* m, int n);                  // 0x0107D7E0
	void removeReference();                              // 0x0107D790
	virtual void releaseCachedMemory();                  // slot 1 (0x0107D740)
};

template <typename T>
struct hkArray
{
	enum { CAPACITY_MASK = 0x3FFFFFFF, DONT_DEALLOCATE_FLAG = (int)0x80000000 };
	T* m_data;
	int m_size;
	int m_capacityAndFlags;

	hkArray() : m_data(0), m_size(0), m_capacityAndFlags(DONT_DEALLOCATE_FLAG) {}
	~hkArray()
	{
		m_size = 0;
		if (m_capacityAndFlags >= 0)
			hkThreadMemory::getInstance().deallocateChunk(m_data, m_capacityAndFlags * (int)sizeof(T), HK_MEMORY_CLASS_ARRAY);
	}
	void pushBack(const T& t)
	{
		if (m_size == (m_capacityAndFlags & CAPACITY_MASK))
			hkArrayUtil::_reserveMore(this, (int)sizeof(T));
		m_data[m_size++] = t;
	}
};

//
// Monitors, singletons, base system
//
struct hkMonitorStream
{
	static void init();   // 0x01080480
	static void quit();   // 0x010804C0
};

class hkError : public hkReferencedObject
{
public:
	virtual void message(int severity, int id, const char* description, const char* file, int line) = 0; // 2
	static hkError* s_instance;   // 0x016E4184
};

struct hkSingletonInitNode
{
	typedef hkReferencedObject* (*SingletonCreationFunction)();
	SingletonCreationFunction m_func;   // 0x00
	hkSingletonInitNode* m_next;        // 0x04
	void** m_value;                     // 0x08
};


// Win32 imports used by the base library, declared by hand (no <windows.h>).
extern "C"
{
	__declspec(dllimport) void* __stdcall TlsGetValue(hkUint32 index);
	__declspec(dllimport) int __stdcall TlsSetValue(hkUint32 index, void* value);
	__declspec(dllimport) int __stdcall TryEnterCriticalSection(void* cs);
	__declspec(dllimport) void __stdcall EnterCriticalSection(void* cs);
	__declspec(dllimport) void __stdcall LeaveCriticalSection(void* cs);
	__declspec(dllimport) void __stdcall DeleteCriticalSection(void* cs);
	__declspec(dllimport) int __stdcall InitializeCriticalSectionAndSpinCount(void* cs, hkUint32 spin);
	__declspec(dllimport) hkUint32 __stdcall GetCurrentThreadId(void);
	__declspec(dllimport) void* __stdcall GetCurrentProcess(void);
	__declspec(dllimport) void* __stdcall LoadLibraryA(const char* name);
	__declspec(dllimport) int __stdcall FreeLibrary(void* module);
	__declspec(dllimport) void* __stdcall GetProcAddress(void* module, const char* name);
}

// TLS slots and globals owned by other translation units of the base library.
extern hkUint32 g_hkThreadMemoryTls;     // 0x016E4174 hkThreadLocalData<hkThreadMemory*>
extern hkUint32 g_hkMonitorTlsStart;     // 0x016E42A0
extern hkUint32 g_hkMonitorTlsCurrent;   // 0x016E42A4
extern hkUint32 g_hkMonitorTlsEnd;       // 0x016E42A8
extern hkUint32 g_hkMonitorTlsAC;        // 0x016E42AC
extern hkUint32 g_hkMonitorTlsOwnsBuf;   // 0x016E42B0
extern hkUint32 g_hkMonitorTlsEnabled;   // 0x016E42B8
extern hkSingletonInitNode* g_hkSingletonInitList;  // 0x016E429C

struct hkBaseSystem
{
	static hkResult init(hkMemory* memoryManager, hkThreadMemory* threadMemory,
	                     void (*errorReportFunction)(const char*, void*), void* errorReportObject); // 0x0107EB20
	static hkResult quit();               // 0x0107ED00
	static void initSingletons();         // 0x0107EA10
	static void quitSingletons();         // 0x0107EC20
};

//
// Reflection
//
struct hkClassMemberTypeProperties
{
	hkInt16 m_size;          // 0x00
	hkInt16 m_align;         // 0x02
	const char* m_name;      // 0x04
	int m_pad;               // 0x08
};

class hkClass;
class hkClassEnum;

class hkClassMember
{
public:
	enum Type
	{
		TYPE_VOID = 0, TYPE_BOOL, TYPE_CHAR, TYPE_INT8, TYPE_UINT8, TYPE_INT16, TYPE_UINT16, TYPE_INT32,
		TYPE_UINT32, TYPE_INT64, TYPE_UINT64, TYPE_REAL, TYPE_VECTOR4, TYPE_QUATERNION, TYPE_MATRIX3,
		TYPE_ROTATION, TYPE_QSTRANSFORM, TYPE_MATRIX4, TYPE_TRANSFORM, TYPE_ZERO, TYPE_POINTER,
		TYPE_FUNCTIONPOINTER, TYPE_ARRAY, TYPE_INPLACEARRAY, TYPE_ENUM, TYPE_STRUCT, TYPE_SIMPLEARRAY,
		TYPE_HOMOGENEOUSARRAY, TYPE_VARIANT
	};
	int getCstyleArraySize() const;   // 0x01080CD0
	int getSizeInBytes() const;       // 0x01080CE0
	int getAlignment() const;         // 0x01080DB0

	const char* m_name;               // 0x00
	const hkClass* m_class;           // 0x04
	const hkClassEnum* m_enum;        // 0x08
	hkUint8 m_type;                   // 0x0c
	hkUint8 m_subtype;                // 0x0d
	hkInt16 m_cArraySize;             // 0x0e
	hkUint16 m_flags;                 // 0x10
	hkUint16 m_offset;                // 0x12
};

extern const hkClassMemberTypeProperties s_classMemberTypeProperties[];  // 0x0149D2D0, stride 12

class hkClass
{
public:
	hkClass(const char* name, const hkClass* parent, int objectSize, const hkClass** implementedInterfaces,
	        int numImplementedInterfaces, const hkClassEnum* enums, int numEnums,
	        const hkClassMember* members, int numMembers, const void* defaults);   // 0x010802B0
	hkBool hasVtable() const;                                // 0x01080450
	hkBool isSuperClass(const hkClass& k) const;             // 0x01080300
	int getObjectSize() const { return m_objectSize; }
	int getNumMembers() const;                               // 0x01080330
	const hkClassMember& getMember(int i) const;             // 0x01080350
	const hkClassMember& getDeclaredMember(int i) const;     // 0x010803B0
	const hkClassMember* getMemberByName(const char* name) const; // 0x010803C0

	const char* m_name;                    // 0x00
	const hkClass* m_parent;               // 0x04
	int m_objectSize;                      // 0x08
	int m_numImplementedInterfaces;        // 0x0c
	const hkClassEnum* m_declaredEnums;    // 0x10
	int m_numDeclaredEnums;                // 0x14
	const hkClassMember* m_declaredMembers;// 0x18
	int m_numDeclaredMembers;              // 0x1c
	const void* m_defaults;                // 0x20
};

hkUint64 hkGetCurrentThreadId();   // 0x01080CC0 (GetCurrentThreadId zero-extended)

struct hkString
{
	static int strCmp(const char* a, const char* b);   // 0x0107F3D0
	static int strLen(const char* s);                  // 0x0107F420
	static void memCpy(void* dst, const void* src, int n);   // 0x0107F440
	static void memSet(void* dst, int c, int n);       // 0x0107F470
	static void snprintf(char* buf, int n, const char* fmt, ...);  // 0x0107F390 (_vsnprintf)
	static void sprintf(char* buf, const char* fmt, ...);          // 0x0107F3B0 (vsprintf)
};

//
// Math
//
struct hkVector4
{
	float x, y, z, w;
	hkBool isOk3() const;                     // 0x010812B0
	hkBool isNormalized3(float epsilon) const;// 0x010812F0
	void setTransformedPos(const struct hkTransform& t, const hkVector4& p);   // 0x01081360
};

struct hkRotation
{
	float m[12];   // three hkVector4 columns
	void setTranspose(const hkRotation& r);   // 0x01081550 (not in these slices)
};

struct hkTransform
{
	float m[16];   // rotation (12 floats, columns in hkVector4 slots) + translation hkVector4 at 12..15
	void setInverse(const hkTransform& t);                          // 0x01080E70
	void setMul(const hkTransform& a, const hkTransform& b);        // 0x01080EF0
	void setMulInverseMul(const hkTransform& a, const hkTransform& b); // 0x010810F0
};

namespace hkMath
{
	hkBool equal(float a, float b, float eps);   // 0x01080E40
}

// hkCriticalSection + pool allocator
class hkCriticalSection
{
public:
	void enter();     // 0x0107F820
	void leave();     // inlined in the pool allocator
	char m_cs[24];    // CRITICAL_SECTION, 0x00
	hkUint64 m_owner; // 0x18 (thread id while locked, -1 otherwise)
};

class hkPoolMemory : public hkMemory
{
public:
	hkPoolMemory();                                                  // 0x0107F910
	~hkPoolMemory();                                                 // 0x0107F6C0
	virtual void* allocate(int nbytes, int cl);                      // 0x0107F720
	virtual void deallocate(void* p);                                // 0x0107F750
	virtual void* alignedAllocate(int alignment, int nbytes, int cl);// 0x0107F780
	virtual void alignedDeallocate(void* p);                         // 0x0107F7D0
	virtual void* allocateChunk(int nbytes, int cl);                 // 0x0107FBE0
	virtual void deallocateChunk(void* p, int nbytes, int cl);       // 0x0107FF60
	virtual void* allocateChunkByRow(int row, int cl);               // 0x0107FDD0
	virtual void deallocateChunkByRow(void* p, int row);             // 0x0107FFF0
	virtual void printStatistics(hkOstream* o);                      // 0x0107F700
	virtual int getAllocatedSize(int nbytes);                        // 0x0107F670
	virtual void getStatSynopsis(hkMemoryStatistics* s);             // 0x0107F800

	void* _allocateFromRow(int row);

	hkUint8* m_pageList;            // 0x2c singly linked list of 0x2040-byte pages
	hkUint8* m_pageStart;           // 0x30
	hkUint8* m_pageEnd;             // 0x34
	hkUint8* m_pageCur;             // 0x38
	int m_pad3c;                    // 0x3c
	hkCriticalSection m_lock;       // 0x40
	void* m_freeLists[17];          // 0x60
	int m_rowSizes[17];             // 0xa4
	char m_sizeToRow[0x201];        // 0xe8
	char m_pad2e9[3];
	int m_bigSizeToRow[8];          // 0x2ec
	int m_rowCounts[17];            // 0x30c
};

inline hkThreadMemory& hkThreadMemory::getInstance()
{
	return *(hkThreadMemory*)TlsGetValue(g_hkThreadMemoryTls);
}

inline void hkCriticalSection::leave()
{
	m_owner = (hkUint64)-1;   // two dword stores of -1 in the binary
	LeaveCriticalSection(m_cs);
}
