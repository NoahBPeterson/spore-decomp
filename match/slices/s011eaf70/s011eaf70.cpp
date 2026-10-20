// Slice s011eaf70 -- RenderWare 4 core: the arena type registry / arena resource
// accumulator helpers, the static atom table fixup, the core string helpers and the
// PC file-device driver.
//
// RenderWare 4 core is equivalence-only (its objects are built with /vc71-visible
// inlining and the raw 6*N / 0x18 index arithmetic makes byte-exact matching
// impractical), so this file aims for complete, behaviourally faithful C++. Flags:
// /O2 /MD /Gy /EHsc /TP (the same set the neighbouring s011ebf70 RW4 slice uses).
#include "types.h"

// ---------------------------------------------------------------------------------------------------------
// out-of-slice helpers and imports
// ---------------------------------------------------------------------------------------------------------
extern "C" {

// arena / atom helpers
int   FUN_011eab10(void*);                                  // 0x011eab10  arena count (low 16 bits used)
int   FUN_011eab40(void*);                                  // 0x011eab40  arena base pointer
void  FUN_011eabe0(void*, int, int);                        // 0x011eabe0  arena init
void  FUN_011eaf10(void*, void*);                           // 0x011eaf10  arena resource fixup
void  FUN_011ea8f0(void*, int);                             // 0x011ea8f0  rw::core::stdc::MemClear
// FUN_011e2240 / FUN_011e2670 are __thiscall: ecx = the field-table object, one stack
// argument (the 0x20-byte scratch buffer). Model them as members of a small struct.
struct RwFieldTableRef
{
	int  lookup(void* out);      // 0x011e2240
	int  entry(void* out);       // 0x011e2670
};
// Arena subreference container (rw::core::arena::DynamicArenaSubreferencesData);
// its ctor and AddNewSubreference are __thiscall, so model them as members.
struct RwArenaSubrefsData
{
	int* ctor(int arg);          // 0x011eb410
	unsigned int addNew();       // 0x011eb490
};
int   FUN_011e8b20(char*, const char*);                     // 0x011e8b20  stdc::StringCopy
int   FUN_011e8b50(char*, const char*);                     // 0x011e8b50  stdc::StringAppend
int   FUN_011e22c0(int id);                                 // 0x011e22c0  rw::core::arena::ArenaTypeRegGetType
void* FUN_011e6d20(unsigned int);                           // 0x011e6d20  StreamImpl::operator_new
void* FUN_011eb0d0(void*);                                  // 0x011eb0d0  arena unfix callback
void* FUN_011fb220(void*);                                  // 0x011fb220  arena no-op callback
void* FUN_012057f0(void*);                                  // 0x012057f0  arena refix callback
void  FUN_011e0846(void);                                   // 0x011e0846  lib_crt::ftol2

// import thunks (resolved through the binary's IAT)
void* __stdcall GlobalAlloc(unsigned int, unsigned int);
unsigned long __stdcall GetLogicalDrives(void);
int   __stdcall CloseHandle(void*);
int   __stdcall FindClose(void*);
int   __stdcall FindNextFileA(void*, void*);
int   __stdcall SetEndOfFile(void*);
unsigned long __stdcall SetFilePointer(void*, long, int*, unsigned long);
unsigned long __stdcall GetFileSize(void*, unsigned long*);
unsigned long __stdcall GetLastError(void);
int   __stdcall ReadFile(void*, void*, unsigned long, unsigned long*, void*);
int   __stdcall WriteFile(void*, const void*, unsigned long, unsigned long*, void*);
int   __stdcall DeleteFileA(const char*);
int   __stdcall MoveFileA(const char*, const char*);
int   __stdcall CreateDirectoryA(const char*, void*);
int   __stdcall RemoveDirectoryA(const char*);
void* __stdcall CreateFileA(const char*, unsigned long, unsigned long, void*, unsigned long, unsigned long, void*);
}

// data
extern "C" void* g_rwAllocFn;                              // 0x016f4ae4  rw::core::stdc alloc callback
extern "C" void* g_rwFreeFn;                               // 0x016f4aec  rw::core::stdc free callback
extern "C" char  g_driveNames[26][4];                      // 0x015d0628  "a:\\" ... "z:\\"
extern "C" char  g_driveList[0x68];                        // 0x016f4b88  filled by DriveListGet
extern "C" void* g_rwFsAllocator;                          // 0x016f4b10  rw::core::filesys allocator
extern "C" const float g_rwFloatBias;                      // 0x013f4fd0  unsigned-to-float bias (2^32)

// ---------------------------------------------------------------------------------------------------------
// helper structs
// ---------------------------------------------------------------------------------------------------------

// Six 32-bit fields, laid out as the packed arena block header used by the accumulator helpers.
struct ArenaField
{
	unsigned int  m_lo;      // +0x00
	unsigned int  m_hi;      // +0x04
	unsigned int  m_pad08;   // +0x08
	unsigned int  m_data;    // +0x0c
	unsigned int  m_pad10;   // +0x10
	unsigned int  m_type;    // +0x14  resource type (0x10030..0x1003f => index 1..0x10)
};
struct ArenaFieldPair { unsigned int m_v0; unsigned int m_v1; unsigned int m_v2; unsigned int m_v3;
                        unsigned int m_v4; unsigned int m_v5; unsigned int m_v6; unsigned int m_v7; };

// rw::core::arena::ArenaTypeReg: one 0x14-byte registry record.
struct ArenaTypeReg
{
	unsigned int  id;          // +0x00
	void*         unfixCB;     // +0x04
	void*         refixCB;     // +0x08
	void*         fixupCB;     // +0x0c
	void*         destructCB;  // +0x10
};
// rw::core::arena::rw_ArenaTypeRegistry: {numUsed; numAlloc} header + record array.
struct rw_ArenaTypeRegistry
{
	unsigned int  m_numUsed;   // +0x00
	unsigned int  m_numAlloc;  // +0x04
	ArenaTypeReg  m_record[1]; // +0x08
};
// rw::core::atom::StaticAtomTable::Members
struct StaticAtomMembers
{
	int  m_atomNames;          // +0x00
	int  m_atomNameTail;       // +0x04
	int  m_stringIndex;        // +0x08
	int  m_idArray;            // +0x0c
};
// rw::core::filesys stream: HANDLE + read/write offset, 0x10 bytes.
struct StreamImpl
{
	void*         m_handle;    // +0x00
	unsigned int  m_pad04;     // +0x04
	unsigned int  m_offsetLo;  // +0x08
	unsigned int  m_offsetHi;  // +0x0c
};
// rw::core::filesys search data: FIND_DATA fields the driver copies out.
struct FileFindData
{
	unsigned int  m_flags;         // +0x00
	unsigned int  m_pad04;         // +0x04
	unsigned int  m_creationLo;    // +0x08
	unsigned int  m_creationHi;    // +0x0c
	unsigned int  m_accessLo;      // +0x10
	unsigned int  m_accessHi;      // +0x14
	unsigned int  m_writeLo;       // +0x18
	unsigned int  m_writeHi;       // +0x1c
	unsigned int  m_sizeLo;        // +0x20
	unsigned int  m_sizeHi;        // +0x24
	char          m_name[0x100];   // +0x28
};
// The raw WIN32_FIND_DATAA/FILE shape (0x140 bytes) the driver reads into.
struct Win32FindDataA { unsigned char m_raw[0x140]; };

// ---------------------------------------------------------------------------------------------------------
// 011eaf70: arena accumulate-all -- walks the arena block list, copies each resource
// through FUN_011eabe0 and fixes up every registered resource.
// ---------------------------------------------------------------------------------------------------------
// @ 0x11eaf70
void FUN_011eaf70(void* alloc, int* blockList, int* fieldTable, unsigned int* out)
{
	unsigned int  count = (unsigned int)FUN_011eab10(alloc);
	int           base  = FUN_011eab40(alloc);

	// local_20[0] is count*6 + base + 0x1c; the rest is the 8-dword descriptor.
	unsigned int  desc[8];
	desc[0] = (unsigned int)(base + 0x1c + (count & 0xffff) * 6);
	desc[1] = 1;
	desc[2] = 0;
	desc[3] = 1;
	desc[4] = 0;
	desc[5] = 1;
	desc[6] = 0;
	desc[7] = 1;

	unsigned int  header[4];
	for (int i = 0; i < 8; ++i)
		out[i] = desc[i];

	// descriptor vtable[1](header, out, 0)
	((void (__thiscall*)(void*, unsigned int*, unsigned int*, int))((void**)*fieldTable)[1])(fieldTable, header, out, 0);

	FUN_011eabe0((char*)header + 4, (int)desc[0] - 4, (int)count);

	unsigned int  n = (unsigned int)blockList[1];
	for (unsigned int i = 0; i < n; ++i)
		FUN_011eaf10((void*)blockList[i * 0 + 0], header);   // source block from the list

	// write the accumulated 4 dwords back
	unsigned int* dst = (unsigned int*)desc;
	dst[0] = header[0];
	dst[1] = header[1];
	dst[2] = header[2];
	dst[3] = header[3];
	for (int i = 0; i < 4; ++i)
		out[i] = dst[i];
}

// ---------------------------------------------------------------------------------------------------------
// 011eb040: rw::core::atom::StaticAtomTable::Fixup -- rebases the four table-member
// pointers by `this`.
// ---------------------------------------------------------------------------------------------------------
// @ 0x11eb040
void StaticAtomTable_Fixup(StaticAtomMembers* self)
{
	int  tbl = self->m_atomNames + (int)self;
	self->m_atomNames = tbl;
	*(int*)(tbl + 0) = *(int*)(tbl + 0) + (int)self;
	self->m_atomNameTail = self->m_atomNameTail + (int)self;
	self->m_stringIndex  = self->m_stringIndex + (int)self;
	self->m_idArray      = self->m_idArray + (int)self;
}

// ---------------------------------------------------------------------------------------------------------
// 011eb060: the free-function twin of the above (rebases an object's four dwords).
// ---------------------------------------------------------------------------------------------------------
// @ 0x11eb060
void FUN_011eb060(int* p)
{
	int* q = (int*)(*p + (int)p);
	*p = (int)q;
	*q = *q + (int)p;
	*(int*)(*p + 4)  = *(int*)(*p + 4) + (int)p;
	*(int*)(*p + 8)  = *(int*)(*p + 8) + (int)p;
	*(int*)(*p + 0xc) = *(int*)(*p + 0xc) + (int)p;
}

// ---------------------------------------------------------------------------------------------------------
// 011eb0a0: rw::core::arena::rw_ArenaTypeRegistry::Find
// ---------------------------------------------------------------------------------------------------------
// @ 0x11eb0a0
ArenaTypeReg* rw_ArenaTypeRegistry_Find(rw_ArenaTypeRegistry* self, unsigned int id)
{
	ArenaTypeReg* first = &self->m_record[0];
	ArenaTypeReg* last  = &self->m_record[self->m_numUsed];
	for (ArenaTypeReg* p = first; p != last; ++p)
		if (p->id == id)
			return p;
	return 0;
}

// ---------------------------------------------------------------------------------------------------------
// 011eb0e0: rw::core::arena::rw_ArenaTypeRegistry::Open -- first record of a block
// sized for `count` records.
// ---------------------------------------------------------------------------------------------------------
// @ 0x11eb0e0
unsigned int* rw_ArenaTypeRegistry_Open(int self, int sizeBytes)
{
	unsigned int* p = (unsigned int*)((self + 3) & 0xfffffffc);
	*p = (unsigned int)((unsigned int)(self - (int)p) + (unsigned int)sizeBytes - 8u) / 0x14u;
	p[1] = 0;
	return p;
}

// ---------------------------------------------------------------------------------------------------------
// 011eb110: rw::core::arena::rw_ArenaTypeRegistry::Add
// ---------------------------------------------------------------------------------------------------------
// @ 0x11eb110
void rw_ArenaTypeRegistry_Add(rw_ArenaTypeRegistry* self, unsigned int id)
{
	unsigned int  used = self->m_numUsed;
	self->m_numUsed = used + 1;
	ArenaTypeReg* r = &self->m_record[used];
	r->id         = id;
	r->unfixCB    = (void*)0x011eb0d0;
	r->refixCB    = (void*)0x011fb220;
	r->fixupCB    = (void*)0x012057f0;
	r->destructCB = 0;
}

// ---------------------------------------------------------------------------------------------------------
// 011eb180: tears down both 4-slot sub-tables (slot 9.. and slot 1..), dispatching
// the first non-null slot through its object's vtable[2].
// ---------------------------------------------------------------------------------------------------------
// @ 0x11eb180
void FUN_011eb180(int* self)
{
	int* a = self + 9;
	for (unsigned int i = 0; i < 4; ++i)
	{
		if (a[i] != 0)
		{
			int* obj = (int*)self[8];
			((void (__thiscall*)(void*, int*))((void**)*obj)[2])(obj, a);
			break;
		}
	}

	int* b = self + 1;
	for (unsigned int i = 0; i < 4; ++i)
	{
		if (b[i] != 0)
		{
			int* obj = (int*)self[0];
			((void (__thiscall*)(void*, int*))((void**)*obj)[2])(obj, b);
			break;
		}
	}
}

// ---------------------------------------------------------------------------------------------------------
// 011eb1d0 / 011eb2f0: arena block grow helpers. Both clamp the requested count
// against twice the current one (via the FP round), reallocate the backing store
// through the object's vtable[1] and memcpy the old contents across.
// ---------------------------------------------------------------------------------------------------------
// @ 0x11eb1d0
void FUN_011eb1d0(int* self, unsigned int requested)
{
	unsigned int cur = (unsigned int)self[6];
	if (cur > requested)
		return;

	float fCur = (float)(int)cur;
	if ((int)cur < 0)
		fCur += 4294967296.0f;
	float fReq = (float)(int)requested;
	if ((int)requested < 0)
		fReq += 4294967296.0f;

	if (fReq <= fCur + fCur)
	{
		// _ftol2 of (fCur + fCur)
		self[6] = (int)(fCur + fCur);
	}
	else
	{
		self[6] = (int)requested;
	}

	int* oldBuf = (int*)self[5];

	unsigned int hdr[4];
	hdr[0] = (unsigned int)self[1];
	hdr[1] = (unsigned int)self[2];
	hdr[2] = (unsigned int)self[3];
	hdr[3] = (unsigned int)self[4];

	unsigned int req2[8];
	req2[0] = (unsigned int)self[6] << 3;   // 8 bytes per element
	req2[1] = 4;
	req2[2] = 0;
	req2[3] = 1;
	req2[4] = 0;
	req2[5] = 1;
	req2[6] = 0;
	req2[7] = 1;

	unsigned int out[4];
	((void (__thiscall*)(int*, unsigned int*, unsigned int*, int))((void**)*self)[1])(self, out, req2, 0);

	self[1] = out[0];
	self[2] = out[1];
	self[3] = out[2];
	self[4] = out[3];
	self[5] = (int)out[0];

	if (oldBuf != 0)
	{
		unsigned int n = ((unsigned int)self[7] & 0x1fffffff) << 1;   // dwords
		unsigned int* d = (unsigned int*)self[5];
		unsigned int* s = (unsigned int*)oldBuf;
		for (unsigned int i = 0; i < n; ++i)
			d[i] = s[i];

		int* obj = (int*)self[0];
		((void (__thiscall*)(void*, unsigned int*))((void**)*obj)[2])(obj, hdr);
	}
}

// @ 0x11eb2f0
void FUN_011eb2f0(int* self, unsigned int requested)
{
	unsigned int cur = (unsigned int)self[6];
	if (cur > requested)
		return;

	float fCur = (float)(int)cur;
	if ((int)cur < 0)
		fCur += 4294967296.0f;
	float fReq = (float)(int)requested;
	if ((int)requested < 0)
		fReq += 4294967296.0f;

	if (fReq <= fCur + fCur)
		self[6] = (int)(fCur + fCur);
	else
		self[6] = (int)requested;

	int* oldBuf = (int*)self[5];

	unsigned int hdr[4];
	hdr[0] = (unsigned int)self[1];
	hdr[1] = (unsigned int)self[2];
	hdr[2] = (unsigned int)self[3];
	hdr[3] = (unsigned int)self[4];

	unsigned int req2[8];
	req2[0] = ((unsigned int)self[6] * 3) << 3;   // 0x18 bytes per element
	req2[1] = 4;
	req2[2] = 0;
	req2[3] = 1;
	req2[4] = 0;
	req2[5] = 1;
	req2[6] = 0;
	req2[7] = 1;

	unsigned int out[4];
	((void (__thiscall*)(int*, unsigned int*, unsigned int*, int))((void**)*self)[1])(self, out, req2, 0);

	self[1] = out[0];
	self[2] = out[1];
	self[3] = out[2];
	self[4] = out[3];
	self[5] = (int)out[0];

	if (oldBuf != 0)
	{
		unsigned int n = (((unsigned int)self[7] * 3) & 0x1fffffff) << 1;
		unsigned int* d = (unsigned int*)self[5];
		unsigned int* s = (unsigned int*)oldBuf;
		for (unsigned int i = 0; i < n; ++i)
			d[i] = s[i];

		int* obj = (int*)self[0];
		((void (__thiscall*)(void*, unsigned int*))((void**)*obj)[2])(obj, hdr);
	}
}

// ---------------------------------------------------------------------------------------------------------
// 011eb410: subreference-container constructor -- clears both 0x20-byte sub-tables
// (8 dwords each) and pre-grows 8-byte / 0x18-byte element stores via the grow helpers.
// ---------------------------------------------------------------------------------------------------------
// @ 0x11eb410
int* RwArenaSubrefsData::ctor(int arg)
{
	int* self = (int*)this;
	int  zero = 0;
	self[0] = arg;
	self[1] = zero;
	self[2] = zero;
	self[3] = zero;
	self[4] = zero;
	self[1] = zero;
	self[5] = zero;
	self[6] = zero;
	self[7] = zero;
	FUN_011eb1d0(self, 0x10);
	FUN_011eb1d0(self, 0);
	self[7] = zero;

	int* s2 = self + 8;
	s2[0] = arg;
	s2[1] = zero;
	s2[2] = zero;
	s2[3] = zero;
	s2[4] = zero;
	s2[1] = zero;
	s2[5] = zero;
	s2[6] = zero;
	s2[7] = zero;
	FUN_011eb2f0(s2, 0x10);
	FUN_011eb2f0(s2, 0);
	s2[7] = zero;
	return self;
}

// ---------------------------------------------------------------------------------------------------------
// 011eb490: rw::core::arena::DynamicArenaSubreferencesData::AddNewSubreference --
// appends one zeroed 8-byte record and one zeroed 0x18-byte dict entry, returns the
// record index used.
// ---------------------------------------------------------------------------------------------------------
// @ 0x11eb490
unsigned int RwArenaSubrefsData::addNew()
{
	int* self = (int*)this;
	unsigned int old = (unsigned int)self[7];
	unsigned int idx = old + 1;
	FUN_011eb1d0(self, idx);

	unsigned int* rec = (unsigned int*)self[5];
	self[7] = (int)idx;
	rec[old * 2]     = 0;
	rec[old * 2 + 1] = 0;

	int* dict = self + 8;
	unsigned int old2 = (unsigned int)self[15];
	unsigned int idx2 = old2 + 1;
	FUN_011eb2f0(dict, idx2);

	unsigned int* d = (unsigned int*)self[13];
	self[15] = (int)idx2;
	unsigned int* e = (unsigned int*)((char*)d + (old2 * 3) * 8);
	e[0] = 0; e[1] = 0; e[2] = 0; e[3] = 0; e[4] = 0; e[5] = 0;
	return old;
}

// ---------------------------------------------------------------------------------------------------------
// 011eb4f0: rw::core::arena::rw_RegisterBaseResourceTypes -- installs the three
// base callbacks (fixup / unfix / no-op) into the resource-type registry entries
// 0x1002f..0x10032 (index 0 maps to id 0).
// ---------------------------------------------------------------------------------------------------------
// @ 0x11eb4f0
void rw_RegisterBaseResourceTypes(void)
{
	for (unsigned int i = 0; i < 4; ++i)
	{
		int id = (i == 0) ? 0 : (int)(i + 0x1002f);
		int reg = FUN_011e22c0(id);
		*(int*)(reg + 0xc) = (int)&FUN_012057f0;
		*(int*)(reg + 4)  = (int)&FUN_011eb0d0;
		*(int*)(reg + 8)  = (int)&FUN_011fb220;
	}
}

// ---------------------------------------------------------------------------------------------------------
// 011eb530: rw::core::arena::ArenaAccumulateNextResource
// ---------------------------------------------------------------------------------------------------------
// @ 0x11eb530
int ArenaAccumulateNextResource(int index, int base, int end, unsigned int* out, int** pOut, int* pIndex)
{
	int cur = base + index * 0x18;
	if (cur == end)
		return 0;

	unsigned int type = *(unsigned int*)(cur + 0x14);
	if (type < 0x10030 || type > 0x1003f)
	{
		*out = *(unsigned int*)(cur + 8);
	}
	else
	{
		int slot;
		if (type < 0x10030 || type > 0x1003f)
			slot = 0;
		else
			slot = (int)type - 0x1002f;
		out[slot] = *(unsigned int*)(cur + 8);
	}

	*pOut   = (int*)cur;
	*pIndex = index + 1;
	return 1;
}

// ---------------------------------------------------------------------------------------------------------
// 011eb5a0: the backward twin of the above, filling a 4-slot accumulator.
// ---------------------------------------------------------------------------------------------------------
// @ 0x11eb5a0
void FUN_011eb5a0(unsigned int* out, int* cur, int* end)
{
	unsigned int acc[4];
	acc[0] = 0; acc[1] = 0; acc[2] = 0; acc[3] = 0;

	for (;;)
	{
		unsigned int type = *(unsigned int*)((char*)cur + 0x14);
		int slot = (type < 0x10030 || type > 0x1003f) ? 0 : (int)(type - 0x1002f);
		acc[slot] = (unsigned int)*cur;

		if (cur == end)
			break;
		unsigned int prev = *(unsigned int*)((char*)cur - 4);
		if (prev <= 0x1002f || prev >= 0x10040)
			break;
		cur = (int*)((char*)cur - 0x18);
	}

	out[0] = acc[0];
	out[1] = acc[1];
	out[2] = acc[2];
	out[3] = acc[3];
}

// ---------------------------------------------------------------------------------------------------------
// 011eb630: arena accumulate pass over a 4-slot field table.
// ---------------------------------------------------------------------------------------------------------
// @ 0x11eb630
void FUN_011eb630(unsigned int* out, int param)
{
	unsigned int local[16];
	unsigned int* p1 = (unsigned int*)(param + 0xc0);
	for (int i = 0; i < 8; ++i)
		local[i] = p1[i];
	unsigned int* p2 = (unsigned int*)(param + 0x0c);
	for (int i = 0; i < 8; ++i)
		local[8 + i] = p2[i];

	unsigned int uVar9 = 0;
	unsigned int uVar6 = 0;
	for (;;)
	{
		unsigned int uVar1 = uVar6 + 1;
		unsigned int uVar4 = 1;
		for (unsigned int uVar2 = uVar1; uVar2 < 4; ++uVar2)
		{
			if (uVar2 != 2 && uVar2 != 3 && local[uVar2 * 2] != 0)
			{
				uVar4 = local[uVar2 * 2 + 9];
				if (uVar4 < local[uVar2 * 2 + 1])
					uVar4 = local[uVar2 * 2 + 1];
				break;
			}
		}

		unsigned int uVar2 = local[uVar6 * 2];
		if (uVar2 != 0)
		{
			if (uVar6 != 2 && uVar6 != 3)
				uVar9 += uVar2;

			unsigned int uVar3 = uVar9;
			if (uVar4 > 1)
				uVar3 = ((uVar4 - 1) + uVar9) & ~(uVar4 - 1);
			int iVar5 = (int)uVar3 - (int)uVar9;
			if (uVar6 != 2 && uVar6 != 3)
				uVar9 += (unsigned int)iVar5;

			unsigned int hi = local[uVar6 * 2 + 9];
			local[uVar6 * 2] = (unsigned int)iVar5 + uVar2;
			unsigned int lo = local[uVar6 * 2 + 1];
			if (hi < lo)
				hi = lo;
			local[uVar6 * 2 + 1] = hi;
		}

		uVar6 = uVar1;
		if (uVar1 >= 4)
			break;
	}

	for (int i = 0; i < 8; ++i)
		out[i] = local[i];
}

// ---------------------------------------------------------------------------------------------------------
// 011eb710: fix up one arena resource slot, running it through the object's
// fixup callback (or the raw allocator when no callback is installed).
// ---------------------------------------------------------------------------------------------------------
// @ 0x11eb710
void FUN_011eb710(int* param_1, int* obj, int index)
{
	void* selfc = (char*)obj + 0xc;
	unsigned char local[32];
	RwFieldTableRef* ft = (RwFieldTableRef*)selfc;
	int  fields = ft->lookup(local);
	unsigned int a = *(unsigned int*)(fields + index * 4);
	int  entries = ft->entry(local);
	int  size = *(int*)(entries + index * 8);
	if (size <= 0)
		return;

	if (*(void**)((char*)obj + 0x2c) != 0)
	{
		((void (__cdecl*)(unsigned int, int, int))*(void**)((char*)obj + 0x2c))(a, size, 0);
	}
	else
	{
		((void (__cdecl*)(unsigned int, int, int, unsigned int))*(void**)((char*)obj + 0x30))(
			a, size, 0, *(unsigned int*)((char*)obj + 0x34));
	}
	*(int*)((char*)obj + 0x7c) += size;
}

// ---------------------------------------------------------------------------------------------------------
// 011eb790: backward pass filling a 4-slot field accumulator.
// ---------------------------------------------------------------------------------------------------------
// @ 0x11eb790
void FUN_011eb790(unsigned int* out, int param_2, int param_3)
{
	unsigned int local[8];
	local[0] = 0; local[1] = 1;
	local[2] = 0; local[3] = 1;
	local[4] = 0; local[5] = 1;
	local[6] = 0; local[7] = 1;

	int cur = param_2;
	for (;;)
	{
		unsigned int type = *(unsigned int*)(cur + 0x14);
		int slot = (type < 0x10030 || type > 0x1003f) ? 0 : (int)(type - 0x1002f);
		local[slot * 2]     = *(unsigned int*)(cur + 8);
		local[slot * 2 + 1] = *(unsigned int*)(cur + 0x0c);

		if (cur == param_3)
			break;
		unsigned int prev = *(unsigned int*)(cur - 4);
		if (prev <= 0x1002f || prev >= 0x10040)
			break;
		cur -= 0x18;
	}

	for (int i = 0; i < 8; ++i)
		out[i] = local[i];
}

// ---------------------------------------------------------------------------------------------------------
// 011eb830: arena allocation driver -- for each of the four slots walks the
// resource chain, sizes the block and calls the allocator callback.
// ---------------------------------------------------------------------------------------------------------
// @ 0x11eb830
void FUN_011eb830(int* param_1, int param_2)
{
	int  iVar2 = param_2;
	int* pSrc  = (param_2 == 0) ? 0 : (int*)(param_2 + 0x0c);
	unsigned int uVar8 = 0;
	int  iVar6 = 0;

	for (;;)
	{
		if (uVar8 != 2 && uVar8 != 3)
		{
			int iVar3;
			if (uVar8 == 0)
			{
				iVar3 = *(int*)(iVar2 + 0x7c);
			}
			else
			{
				iVar3 = *(int*)(iVar2 + 0x7c);
				FUN_011eb710(param_1, (int*)iVar2, (int)uVar8);
				iVar3 = *(int*)(iVar2 + 0x7c) - iVar3;
			}
			unsigned int uVar7 = (unsigned int)(iVar6 + iVar3);

			unsigned int local[7];
			local[0] = 1; local[1] = 0;
			local[2] = 1; local[3] = 0;
			local[4] = 1; local[5] = 0;
			local[6] = 1;

			unsigned int uVar1 = uVar8;
			unsigned int uVar5 = uVar7;
			for (;;)
			{
				uVar1 = uVar1 + 1;
				if (uVar1 >= 4)
					break;
				if (uVar1 == 2 || uVar1 == 3 || pSrc[uVar1 * 2] == 0)
					continue;
				unsigned int uVar4 = (unsigned int)pSrc[uVar1 * 2 + 1];
				if (uVar4 <= local[uVar1 * 2])
					uVar4 = local[uVar1 * 2];
				if (uVar4 > 1)
					uVar5 = ((uVar4 - 1) + uVar7) & ~(uVar4 - 1);
				break;
			}

			int iDiff = (int)(uVar5 - uVar7);
			if (*(void**)(iVar2 + 0x2c) == 0)
			{
				((void (__cdecl*)(int, int, int, unsigned int))*(void**)(iVar2 + 0x30))(
					0, 0, iDiff, *(unsigned int*)(iVar2 + 0x34));
			}
			else
			{
				((void (__cdecl*)(int, int, int))*(void**)(iVar2 + 0x2c))(0, 0, iDiff);
			}
			*(int*)(iVar2 + 0x7c) += iDiff;
			iVar6 = (int)(uVar7 + (unsigned int)iDiff);
		}

		uVar8 = uVar8 + 1;
		if (uVar8 >= 4)
			return;
	}
}

// ---------------------------------------------------------------------------------------------------------
// 011eb980: build a 4-entry table of allocated handles from {size, style} pairs.
// ---------------------------------------------------------------------------------------------------------
// @ 0x11eb980
void __stdcall FUN_011eb980(unsigned int* out, unsigned int* pairs, unsigned int unused)
{
	(void)unused;
	unsigned int acc[4];
	acc[0] = 0; acc[1] = 0; acc[2] = 0; acc[3] = 0;

	for (unsigned int i = 0; i < 4; ++i)
	{
		if (pairs[i * 2] != 0)
			acc[i] = (unsigned int)((void* (__cdecl*)(unsigned int, unsigned int))g_rwAllocFn)(
				pairs[i * 2], pairs[i * 2 + 1]);
	}

	out[0] = acc[0];
	out[1] = acc[1];
	out[2] = acc[2];
	out[3] = acc[3];
}

// ---------------------------------------------------------------------------------------------------------
// 011eb9f0: release the four handles produced by 011eb980.
// ---------------------------------------------------------------------------------------------------------
// @ 0x11eb9f0
void __stdcall FUN_011eb9f0(unsigned int* handles)
{
	for (unsigned int i = 0; i < 4; ++i)
		((void (__cdecl*)(unsigned int))g_rwFreeFn)(handles[i]);
}

// ---------------------------------------------------------------------------------------------------------
// 011eba20: rw::core::stdc::StringnCopy
// ---------------------------------------------------------------------------------------------------------
// @ 0x11eba20
char* rw_stdc_StringnCopy(char* dst, const char* src, int n)
{
	char* ret = dst;
	if (n == 0)
		return ret;

	for (;;)
	{
		--n;
		char c = *src;
		if (c == 0)
			break;
		*dst = c;
		++src;
		++dst;
		if (n == 0)
			return ret;
	}
	if (n != -1)
		*dst = 0;
	return ret;
}

// ---------------------------------------------------------------------------------------------------------
// 011eba60 / 011ebaa0: file read / write with a 64-bit byte counter.
// ---------------------------------------------------------------------------------------------------------
// @ 0x11eba60
void FUN_011eba60(unsigned int* stream, void* buf, unsigned long count)
{
	ReadFile((void*)stream[0], buf, count, &count, 0);
	unsigned int lo = stream[2];
	stream[2] = lo + count;
	stream[3] = stream[3] + (unsigned int)((lo + count) < lo);
}

// @ 0x11ebaa0
void FUN_011ebaa0(unsigned int* stream, const void* buf, unsigned long count)
{
	WriteFile((void*)stream[0], buf, count, &count, 0);
	unsigned int lo = stream[2];
	stream[2] = lo + count;
	stream[3] = stream[3] + (unsigned int)((lo + count) < lo);
}

// ---------------------------------------------------------------------------------------------------------
// 011ebae0: seek, keeping the cached 64-bit position in sync.
// ---------------------------------------------------------------------------------------------------------
// @ 0x11ebae0
void FUN_011ebae0(unsigned int* stream, int posLo, int posHi, int origin)
{
	if (origin == 0 && posLo == (int)stream[2] && posHi == (int)stream[3])
		return;

	unsigned long method;
	if (origin == 1)
		method = 1;
	else if (origin == 2)
		method = 2;
	else
		method = 0;

	int local = posHi;
	unsigned long r = SetFilePointer((void*)stream[0], posLo, &local, method);
	if (r == 0xffffffff && GetLastError() != 0)
	{
		stream[2] = 0xffffffff;
		stream[3] = 0xffffffff;
		return;
	}
	stream[2] = r;
	stream[3] = (unsigned int)local;
}

// ---------------------------------------------------------------------------------------------------------
// 011ebb70: query the file size.
// ---------------------------------------------------------------------------------------------------------
// @ 0x11ebb70
void FUN_011ebb70(unsigned int* stream)
{
	GetFileSize((void*)stream[0], 0);
}

// ---------------------------------------------------------------------------------------------------------
// 011ebb90: truncate the file to `length` bytes, restoring the position.
// ---------------------------------------------------------------------------------------------------------
// @ 0x11ebb90
char FUN_011ebb90(unsigned int* stream, long length)
{
	unsigned long saved = SetFilePointer((void*)stream[0], 0, 0, 1);
	SetFilePointer((void*)stream[0], length, 0, 0);
	long ok = SetEndOfFile((void*)stream[0]);
	SetFilePointer((void*)stream[0], (long)saved, 0, 0);

	stream[2] = saved;
	stream[3] = 0;
	return (char)(ok == 1);
}

// ---------------------------------------------------------------------------------------------------------
// 011ebbf0 / 011ebc10 / 011ebcf0 / 011ebd10: file-system wrappers.
// ---------------------------------------------------------------------------------------------------------
// @ 0x11ebbf0
bool rw_fs_DeleteFile(const char* path)
{
	return DeleteFileA(path) == 1;
}

// @ 0x11ebc10
bool rw_fs_MoveFile(const char* from, const char* to)
{
	return MoveFileA(from, to) == 1;
}

// @ 0x11ebc30: fill a FileFindData from the next WIN32_FIND_DATAA record.
// @ 0x11ebc30
char FUN_011ebc30(void** findHandle, FileFindData* out)
{
	Win32FindDataA data;
	char ok = (char)(FindNextFileA(*findHandle, &data) == 1);
	if (!ok)
		return 0;

	if (out != 0)
	{
		unsigned int* d = (unsigned int*)data.m_raw;
		out->m_creationLo = d[5];
		out->m_creationHi = d[6];
		out->m_accessLo   = d[7];
		out->m_accessHi   = d[8];
		out->m_writeLo    = d[9];
		out->m_writeHi    = d[10];
		out->m_sizeLo     = d[1];
		out->m_sizeHi     = d[2];
		rw_stdc_StringnCopy(out->m_name, (const char*)data.m_raw + 0x2c, 0x100);

		unsigned int attrs = d[0];
		out->m_flags = 0;
		if ((attrs & 1) != 0)
			out->m_flags = 1;
		if ((attrs & 0x10) != 0)
			out->m_flags |= 2;
	}
	return ok;
}

// @ 0x11ebcf0
bool rw_fs_CreateDirectory(const char* path)
{
	return CreateDirectoryA(path, 0) == 1;
}

// @ 0x11ebd10
bool rw_fs_RemoveDirectory(const char* path)
{
	return RemoveDirectoryA(path) == 1;
}

// ---------------------------------------------------------------------------------------------------------
// 011ebd30: enumerate the present drive letters into g_driveList.
// ---------------------------------------------------------------------------------------------------------
// @ 0x11ebd30
int FUN_011ebd30(void)
{
	unsigned long mask = GetLogicalDrives();
	FUN_011ea8f0(g_driveList, 0x68);

	int n = 0;
	for (int i = 0; i < 0x1a; ++i)
	{
		if ((mask & (1u << (i & 0x1f))) != 0)
		{
			*(int*)&g_driveList[n * 4] = *(int*)&g_driveNames[i];
			++n;
		}
	}
	return n;
}

// ---------------------------------------------------------------------------------------------------------
// 011ebd80 / 011ebdc0: close a file handle / find handle and release the driver
// record through the filesystem allocator.
// ---------------------------------------------------------------------------------------------------------
// @ 0x11ebd80
void FUN_011ebd80(void** handle)
{
	CloseHandle(*handle);

	unsigned int rec[4];
	rec[0] = (unsigned int)handle;
	rec[1] = 0;
	rec[2] = 0;
	rec[3] = 0;
	void** alloc = *(void***)g_rwFsAllocator;
	((void (__thiscall*)(void*, unsigned int*))alloc[2])(g_rwFsAllocator, rec);
}

// @ 0x11ebdc0
char FUN_011ebdc0(void** findHandle)
{
	char ok = (char)(FindClose(*findHandle) == 1);

	unsigned int rec[4];
	rec[0] = (unsigned int)findHandle;
	rec[1] = 0;
	rec[2] = 0;
	rec[3] = 0;
	void** alloc = *(void***)g_rwFsAllocator;
	((void (__thiscall*)(void*, unsigned int*))alloc[2])(g_rwFsAllocator, rec);
	return ok;
}

// ---------------------------------------------------------------------------------------------------------
// 011ebe10: rw::core::filesys::PCFileDeviceDriver::Open
// ---------------------------------------------------------------------------------------------------------
// @ 0x11ebe10
StreamImpl* PCFileDeviceDriver_Open(int* self, const char* path, unsigned int mode)
{
	unsigned long access = 0x80000000;
	unsigned long share  = 0x80;
	if ((mode & 1) != 0)
		access = 0xc0000000;

	unsigned long disposition;
	if ((mode & 2) == 0)
		disposition = (unsigned long)((-(unsigned int)((mode & 4) != 0) & 2) + 3);
	else
		disposition = (unsigned long)((~(mode >> 2) & 1) | 2);

	if ((mode & 0x10) != 0)
		share = 0x20000080;
	if ((mode & 8) != 0)
		share |= 0x8000000;

	char  buffer[0x100];
	const char* openPath = path;
	if ((*path == '/' || *path == '\\') && path[1] != '\\')
	{
		FUN_011e8b20(buffer, (const char*)((char*)self + 4));   // device name
		FUN_011e8b50(buffer, path);
		openPath = buffer;
	}

	void* h = CreateFileA(openPath, access, 1, 0, disposition, share, 0);
	if (h != (void*)0xffffffff)
	{
		StreamImpl* s = (StreamImpl*)FUN_011e6d20(0x10);
		if (s != 0)
		{
			s->m_handle   = h;
			s->m_offsetLo = 0;
			s->m_offsetHi = 0;
			return s;
		}
		return 0;
	}

	if ((mode & 2) == 2 && (mode & 4) == 0)
	{
		void* h2 = CreateFileA(path, access, 1, 0, disposition & 0xfffffffd | 1, share, 0);
		if (h2 != (void*)0xffffffff)
		{
			StreamImpl* s = (StreamImpl*)FUN_011e6d20(0x10);
			if (s != 0)
			{
				s->m_handle   = h2;
				s->m_offsetLo = 0;
				s->m_offsetHi = 0;
				return s;
			}
		}
	}
	return 0;
}
