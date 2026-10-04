// Havok 3.1.0 base library, part 1 (0x0107E670..0x0107F47F): stdio streams, hkOstream, hkBaseSystem,
// hkStackTracer, hkString helpers. No floating point in this slice.
#include "hk31_base.h"
#include <stdio.h>
#include <stdarg.h>

// ---- externals defined in other slices ----------------------------------------------------------------
struct hkSingletonStreambufFactory { static void replaceInstance(hkStreambufFactory* f); };   // 0x0107E5F0
class hkDefaultError : public hkError
{
public:
	hkDefaultError(void (*reportFn)(const char*, void*), void* reportObj);                    // 0x005D6AE0
	virtual void message(int severity, int id, const char* description, const char* file, int line);
};
struct hkErrorSingleton { static void replaceInstance(hkError* e); };                          // 0x005D6120
struct hkUnknownBaseObject { virtual void v0(); virtual void v1(); virtual void v2(); };      // object at 0x016E417C
extern hkUnknownBaseObject* g_hkBaseObject;
extern void* SporeAlloc(size_t nbytes);                                                        // 0x006ABEB0
extern bool g_hkBaseSystemInitialized;                                                         // 0x016E4180
extern hkReferencedObject* g_hkStreambufFactoryInstance;                                       // 0x016E42B4

// ---- stdio readers ------------------------------------------------------------------------------------

// @ 0x0107e670
hkStreamReader* hkDefaultStreambufFactory::openReader(const char* name)
{
	hkStreamReader* reader = new hkStdioStreamReader(name);
	hkStreamReader* result = reader;
	if (!reader->markSupported())
	{
		// Streams that cannot mark/rewind are wrapped in a 4KB buffered reader.
		result = new hkBufferedStreamReader(reader, 0x1000);
		reader->removeReference();
	}
	return result;
}

// @ 0x0107e700
hkStdioStreamReader::hkStdioStreamReader(const char* name)
{
	m_ok = true;
	m_file = fopen(name, "rb");
	m_ok = (m_file != 0);
}

// @ 0x0107e740
hkResult hkSeekableStreamReader::setMark(int markLimit)
{
	m_markPos = tell();
	return m_markPos == -1 ? HK_FAILURE : HK_SUCCESS;
}

// @ 0x0107e760
hkResult hkSeekableStreamReader::rewindToMark()
{
	return seek(m_markPos, STREAM_SET);
}

// @ 0x0107e770
int hkStdioStreamReader::read(void* buf, int nbytes)
{
	int r = (int)fread(buf, 1, nbytes, m_file);
	if (r <= 0)
		m_ok = false;
	return r;
}

// @ 0x0107e7a0
hkBool hkStdioStreamReader::isOk() const
{
	return m_ok;
}

// @ 0x0107e7b0
hkResult hkStdioStreamReader::seek(int offset, SeekWhence whence)
{
	return fseek(m_file, offset, whence) != 0 ? HK_FAILURE : HK_SUCCESS;
}

// @ 0x0107e7d0
int hkStdioStreamReader::tell() const
{
	return ftell(m_file);
}

// @ 0x0107e7e0
hkStdioStreamReader::~hkStdioStreamReader()
{
	if (m_file)
		fclose(m_file);
}

// ---- stdio writers ------------------------------------------------------------------------------------

// @ 0x0107e820
hkStreamWriter* hkDefaultStreambufFactory::openWriter(const char* name)
{
	hkStreamWriter* writer = new hkStdioStreamWriter(name);
	hkStreamWriter* result = new hkBufferedStreamWriter(writer, 0x1000);
	writer->removeReference();
	return result;
}

// @ 0x0107e890
hkStdioStreamWriter::hkStdioStreamWriter(const char* name)
{
	m_ownsFile = true;
	// The original leaves m_file uninitialised when name is null (quirk kept).
	if (name)
		m_file = fopen(name, "wb");
}

// @ 0x0107e8d0
int hkStdioStreamWriter::write(const void* buf, int nbytes)
{
	if (m_file)
	{
		int w = (int)fwrite(buf, 1, nbytes, m_file);
		if (w <= 0)
			close();
		return w;
	}
	return 0;
}

// @ 0x0107e910
void hkStdioStreamWriter::close()
{
	if (m_file && m_ownsFile)
		fclose(m_file);
	m_file = 0;
}

// @ 0x0107e940
void hkStdioStreamWriter::flush()
{
	if (m_file)
		fflush(m_file);
}

// @ 0x0107e950
hkBool hkStdioStreamWriter::isOk() const
{
	return m_file != 0;
}

// @ 0x0107e970
hkResult hkStdioStreamWriter::seek(int offset, SeekWhence whence)
{
	return fseek(m_file, offset, whence) != 0 ? HK_FAILURE : HK_SUCCESS;
}

// @ 0x0107e990
int hkStdioStreamWriter::tell() const
{
	return ftell(m_file);
}

// @ 0x0107e9a0
hkStdioStreamWriter::~hkStdioStreamWriter()
{
	close();
}

// ---- hkBaseSystem -------------------------------------------------------------------------------------

// @ 0x0107ea10
void hkBaseSystem::initSingletons()
{
	hkArray<hkSingletonInitNode*> deferred;
	hkSingletonInitNode** link = &g_hkSingletonInitList;
	hkSingletonInitNode* node = g_hkSingletonInitList;
	if (node)
	{
		do
		{
			if (*node->m_value == 0)
			{
				hkReferencedObject* instance = node->m_func();
				if (instance != 0)
				{
					*node->m_value = instance;
					link = &node->m_next;
					node = node->m_next;
				}
				else
				{
					// Creation failed (dependency not up yet): unlink the node and retry it below.
					deferred.pushBack(node);
					node = node->m_next;
					(*link)->m_next = 0;
					*link = node;
				}
			}
			else
			{
				link = &node->m_next;
				node = node->m_next;
			}
		} while (node != 0);

		while (deferred.m_size != 0)
		{
			int i = deferred.m_size;
			while (--i >= 0)
			{
				hkSingletonInitNode* n = deferred.m_data[i];
				hkReferencedObject* instance = n->m_func();
				if (instance != 0)
				{
					*n->m_value = instance;
					*link = n;
					deferred.m_size -= 1;
					link = &n->m_next;
					deferred.m_data[i] = deferred.m_data[deferred.m_size];
				}
			}
		}
	}
}

// @ 0x0107eb20
hkResult hkBaseSystem::init(hkMemory* memoryManager, hkThreadMemory* threadMemory,
                            void (*errorReportFunction)(const char*, void*), void* errorReportObject)
{
	if (!g_hkBaseSystemInitialized)
	{
		hkMonitorStream::init();
		if (memoryManager == 0)
		{
			HK_BREAKPOINT();
			return HK_FAILURE;
		}
		hkMemory::replaceInstance(memoryManager);
		if (threadMemory == 0)
		{
			void* mem = SporeAlloc(0x330);
			hkThreadMemory* tm = mem ? new (mem) hkThreadMemory(memoryManager, 0) : 0;
			hkThreadMemory::replaceInstance(tm);
			hkMonitorStream::init();
			tm->removeReference();
		}
		else
		{
			hkThreadMemory::replaceInstance(threadMemory);
			hkMonitorStream::init();
		}
		hkSingletonStreambufFactory::replaceInstance(new hkDefaultStreambufFactory());
		hkErrorSingleton::replaceInstance((hkError*)new (hkMemory::s_instance->allocateChunk(0x28, HK_MEMORY_CLASS_BASE))
			hkDefaultError(errorReportFunction, errorReportObject));
		initSingletons();
		g_hkBaseObject->v2();
		g_hkBaseSystemInitialized = true;
	}
	return HK_SUCCESS;
}

// @ 0x0107ec20
void hkBaseSystem::quitSingletons()
{
	// hkInplaceArray<hkSingletonInitNode*, 128>
	struct
	{
		hkArray<hkSingletonInitNode*> a;
		hkSingletonInitNode* storage[128];
	} nodes;
	nodes.a.m_data = nodes.storage;
	nodes.a.m_size = 0;
	nodes.a.m_capacityAndFlags = (int)0x80000080;

	for (hkSingletonInitNode* n = g_hkSingletonInitList; n != 0; n = n->m_next)
		nodes.a.pushBack(n);

	int i = nodes.a.m_size - 1;
	while (i >= 0)
	{
		hkReferencedObject* obj = (hkReferencedObject*)*nodes.a.m_data[i]->m_value;
		obj->removeReference();
		*nodes.a.m_data[i]->m_value = 0;
		i = i - 1;
	}
}

// @ 0x0107ed00
hkResult hkBaseSystem::quit()
{
	if (g_hkBaseSystemInitialized == true)
	{
		quitSingletons();

		hkReferencedObject* e = hkError::s_instance;
		if (e != 0)
			e->removeReference();
		hkError::s_instance = 0;

		hkReferencedObject* f = g_hkStreambufFactoryInstance;
		if (f != 0)
			f->removeReference();
		g_hkStreambufFactoryInstance = 0;

		hkMonitorStream::quit();
		hkThreadMemory::getInstance().releaseCachedMemory();
		hkThreadMemory::replaceInstance(0);
		hkMemory::replaceInstance(0);
		g_hkBaseSystemInitialized = false;
	}
	return HK_SUCCESS;
}

// @ 0x0107edb0
void hkErrorMessage(const char* message)
{
	char buf[512];
	hkOstream stream(buf, 512, true);
	stream << message;
	hkError::s_instance->message(3, 0x2636fe25, buf, ".\\error\\hkError.cpp", 0x1b);
}

// ---- hkOstream ----------------------------------------------------------------------------------------

// @ 0x0107ee10
hkOstream& hkOstream::operator<<(char c)
{
	m_writer->write(&c, 1);
	return *this;
}

// @ 0x0107ee30
hkOstream& hkOstream::operator<<(const char* s)
{
	if (s != 0)
	{
		m_writer->write(s, hkString::strLen(s));
		return *this;
	}
	m_writer->write("(null)", 6);
	return *this;
}

// @ 0x0107ee80
hkOstream& hkOstream::operator<<(int i)
{
	char buf[1024];
	hkString::snprintf(buf, 0x400, "%i", i);
	m_writer->write(buf, hkString::strLen(buf));
	return *this;
}

// @ 0x0107eed0
hkOstream& hkOstream::operator<<(unsigned int u)
{
	char buf[1024];
	hkString::snprintf(buf, 0x400, "%u", u);
	m_writer->write(buf, hkString::strLen(buf));
	return *this;
}

// @ 0x0107ef20
void hkOstream::printf(const char* fmt, ...)
{
	char buf[1024];
	va_list args;
	va_start(args, fmt);
	_vsnprintf(buf, 0x400, fmt, args);
	va_end(args);
	m_writer->write(buf, hkString::strLen(buf));
}

// @ 0x0107ef80
hkOstream::hkOstream(void* buf, int bufSize, hkBool nullTerminate)
{
	m_writer = new hkBufferedStreamWriter(buf, bufSize, nullTerminate);
}

// @ 0x0107efd0 (non-deleting dtor; the deleting form is 0x0107f000)
hkOstream::~hkOstream()
{
	if (m_writer)
		m_writer->removeReference();
}

// ---- hkStackTracer (Win32, loads dbghelp.dll dynamically) -----------------------------------------------

typedef int (__stdcall *SymInitializeFn)(void* process, const char* userSearchPath, int invade);
typedef hkUint32 (__stdcall *SymGetOptionsFn)(void);
typedef hkUint32 (__stdcall *SymSetOptionsFn)(hkUint32 options);
struct HK_IMAGEHLP_SYMBOL
{
	hkUint32 SizeOfStruct, Address, Size, Flags, MaxNameLength;
	char Name[2008];
};
struct HK_IMAGEHLP_LINE64
{
	hkUint32 SizeOfStruct;
	void* Key;
	hkUint32 LineNumber;
	const char* FileName;
	hkUint64 Address;
};
typedef int (__stdcall *SymGetSymFromAddrFn)(void* process, hkUint32 addr, hkUint32* displacement, HK_IMAGEHLP_SYMBOL* sym);
typedef int (__stdcall *SymGetLineFromAddr64Fn)(void* process, hkUint64 addr, hkUint32* displacement, HK_IMAGEHLP_LINE64* line);

extern SymGetLineFromAddr64Fn g_SymGetLineFromAddr64;  // 0x016E4188
extern void* g_SymGetModuleBase64;                     // 0x016E418C
extern void* g_SymFunctionTableAccess64;               // 0x016E4190
extern void* g_StackWalk64;                            // 0x016E4194
extern SymGetSymFromAddrFn g_SymGetSymFromAddr;        // 0x016E4198
extern SymSetOptionsFn g_SymSetOptions;                // 0x016E419C
extern SymGetOptionsFn g_SymGetOptions;                // 0x016E41A0
extern SymInitializeFn g_SymInitialize;                // 0x016E41A4
extern int g_dbghelpRefCount;                          // 0x016E41A8
extern void* g_dbghelpModule;                          // 0x016E41AC
extern bool g_stackTracerReportedMissingSymbols;       // 0x016E41B0
extern const char* g_dbghelpName;                      // 0x015B9A48 -> "dbghelp.dll"

class hkStackTracer : public hkReferencedObject
{
public:
	typedef void (*printFunc)(const char*, void*);
	hkStackTracer();
	virtual ~hkStackTracer();
	void dumpStackTrace(const hkUint32* addresses, int numAddresses, printFunc output, void* outputObject);
};

// @ 0x0107f050 (non-deleting dtor)
hkStackTracer::~hkStackTracer()
{
	g_dbghelpRefCount = g_dbghelpRefCount - 1;
	if (g_dbghelpRefCount == 0)
	{
		g_SymInitialize = 0;
		g_SymGetOptions = 0;
		g_SymSetOptions = 0;
		g_SymGetSymFromAddr = 0;
		g_StackWalk64 = 0;
		g_SymFunctionTableAccess64 = 0;
		g_SymGetModuleBase64 = 0;
		g_SymGetLineFromAddr64 = 0;
		FreeLibrary(g_dbghelpModule);
		g_dbghelpModule = 0;
	}
}

// @ 0x0107f0c0
void hkStackTracer::dumpStackTrace(const hkUint32* addresses, int numAddresses, printFunc output, void* outputObject)
{
	void* process = GetCurrentProcess();
	for (int i = 0; i < numAddresses; ++i)
	{
		hkUint32 addr = addresses[i];
		HK_IMAGEHLP_SYMBOL sym;
		hkUint32 displacement = 0;
		sym.Address = 0;
		sym.Size = 0;
		sym.Flags = 0;
		sym.Name[0] = 0; sym.Name[1] = 0; sym.Name[2] = 0; sym.Name[3] = 0;
		sym.SizeOfStruct = 0x18;
		sym.MaxNameLength = 0x7e8;
		if (g_SymGetSymFromAddr(process, addr, &displacement, &sym) == 0)
		{
			if (!g_stackTracerReportedMissingSymbols)
			{
				output("**************************************************************\n"
				       "* Cannot find symbol for an address\n"
				       "* Either debug information was not found or your version of\n"
				       "* dbghelp.dll may be too old to understand the debug format.\n"
				       "* See the comments in hkStackTracer::hkStackTracer()\n"
				       "* ..\\hkbase/memory/impl/hkStackTracerWin32.cxx\n"
				       "**************************************************************\n",
				       outputObject);
				g_stackTracerReportedMissingSymbols = true;
			}
			const char* unknown = "(unknown)";
			int k = 0;
			do { sym.Name[k] = unknown[k]; } while (unknown[k++] != 0);
		}
		else
		{
			// Stop at WinMain (compares 8 bytes including the terminator).
			const char* winMain = "WinMain";
			int k = 0;
			bool equal = true;
			for (; k < 8; ++k)
			{
				equal = sym.Name[k] == winMain[k];
				if (!equal) break;
			}
			if (equal)
				break;
		}

		HK_IMAGEHLP_LINE64 line;
		hkUint32 lineDisplacement = 0;
		line.Key = 0;
		line.LineNumber = 0;
		line.FileName = 0;
		line.Address = 0;
		line.SizeOfStruct = 0x18;
		g_SymGetLineFromAddr64(process, (hkUint64)addr, &lineDisplacement, &line);

		char text[2048];
		_snprintf(text, 0x800, "%s(%i):'%s'\n", line.FileName, (int)line.LineNumber, sym.Name);
		output(text, outputObject);
	}
	output("-------------------------------------------------------------------\n\n", outputObject);
}

// @ 0x0107f250
hkStackTracer::hkStackTracer()
{
	if (g_dbghelpModule == 0)
	{
		g_dbghelpModule = LoadLibraryA(g_dbghelpName);
		g_dbghelpRefCount = 1;
		g_SymInitialize = (SymInitializeFn)GetProcAddress(g_dbghelpModule, "SymInitialize");
		g_SymGetOptions = (SymGetOptionsFn)GetProcAddress(g_dbghelpModule, "SymGetOptions");
		g_SymSetOptions = (SymSetOptionsFn)GetProcAddress(g_dbghelpModule, "SymSetOptions");
		g_SymGetSymFromAddr = (SymGetSymFromAddrFn)GetProcAddress(g_dbghelpModule, "SymGetSymFromAddr");
		g_StackWalk64 = GetProcAddress(g_dbghelpModule, "StackWalk64");
		g_SymFunctionTableAccess64 = GetProcAddress(g_dbghelpModule, "SymFunctionTableAccess64");
		g_SymGetModuleBase64 = GetProcAddress(g_dbghelpModule, "SymGetModuleBase64");
		g_SymGetLineFromAddr64 = (SymGetLineFromAddr64Fn)GetProcAddress(g_dbghelpModule, "SymGetLineFromAddr64");
		hkUint32 options = g_SymGetOptions();
		g_SymSetOptions(options | 0x80000010);   // SYMOPT_DEFERRED_LOADS | SYMOPT_LOAD_LINES | SYMOPT_UNDNAME-ish bits
		g_SymInitialize(GetCurrentProcess(), 0, 1);
	}
	else
	{
		g_dbghelpRefCount = g_dbghelpRefCount + 1;
	}
}

// ---- hkString -----------------------------------------------------------------------------------------

// @ 0x0107f390
void hkString::snprintf(char* buf, int n, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	_vsnprintf(buf, n, fmt, args);
	va_end(args);
}

// @ 0x0107f3b0
void hkString::sprintf(char* buf, const char* fmt, ...)
{
	va_list args;
	va_start(args, fmt);
	vsprintf(buf, fmt, args);
	va_end(args);
}

// @ 0x0107f3d0
int hkString::strCmp(const char* a, const char* b)
{
	const unsigned char* pa = (const unsigned char*)a;
	const unsigned char* pb = (const unsigned char*)b;
	bool less;
	for (;;)
	{
		unsigned char ca = pa[0];
		less = ca < pb[0];
		if (ca != pb[0]) break;
		if (ca == 0) return 0;
		ca = pa[1];
		less = ca < pb[1];
		if (ca != pb[1]) break;
		pa += 2;
		pb += 2;
		if (ca == 0) return 0;
	}
	return (1 - (int)less) - (int)less;
}

// @ 0x0107f420
int hkString::strLen(const char* s)
{
	const char* p = s + 1;
	char c;
	do
	{
		c = *s;
		s = s + 1;
	} while (c != 0);
	return (int)(s - p);
}

// @ 0x0107f440
void hkString::memCpy(void* dst, const void* src, int n)
{
	hkUint32* d = (hkUint32*)dst;
	const hkUint32* s = (const hkUint32*)src;
	for (hkUint32 w = (hkUint32)n >> 2; w != 0; --w)
		*d++ = *s++;
	unsigned char* db = (unsigned char*)d;
	const unsigned char* sb = (const unsigned char*)s;
	for (hkUint32 r = (hkUint32)n & 3; r != 0; --r)
		*db++ = *sb++;
}

// @ 0x0107f470
void hkString::memSet(void* dst, int c, int n)
{
	hkUint32* d = (hkUint32*)dst;
	hkUint8 b = (hkUint8)c;
	for (hkUint32 w = (hkUint32)n >> 2; w != 0; --w)
		*d++ = ((hkUint32)b << 24) | ((hkUint32)b << 16) | ((hkUint32)b << 8) | b;
	unsigned char* db = (unsigned char*)d;
	for (hkUint32 r = (hkUint32)n & 3; r != 0; --r)
		*db++ = b;
}
