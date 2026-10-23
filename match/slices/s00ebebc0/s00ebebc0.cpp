// s00ebebc0 -- SPUI badge / tutorial window placement helpers.
// Rebuilt from the shipped PE.  The module walks engine UI objects through
// their vtables and through a global layout manager; a few helpers use the
// MSVC thiscall convention and are modelled as member functions.

typedef unsigned char byte;
typedef unsigned int  uint;

// ---------------------------------------------------------------------------
// engine helpers
// ---------------------------------------------------------------------------
int*  __cdecl FUN_0067dd50();                              // 0x0067dd50
int*  __cdecl SP_App();                                    // 0x0067dd10
int*  __cdecl FUN_00eeca30(int resource);                  // 0x00eeca30
int*  __cdecl FUN_00b72230(void* cursor);                  // 0x00b72230
void  __cdecl FUN_00b72080(int a, int b);                  // 0x00b72080
int*  __cdecl FUN_00b72160();                              // 0x00b72160
int*  __cdecl FUN_00b72210(int key);                       // 0x00b72210
int*  __cdecl FUN_00eec0d0();                              // 0x00eec0d0
struct CreatureBase
{
	void __thiscall Hide();                                // 0x00c0f280
	void __thiscall Show();                                // 0x00c0f2b0
};
void  __cdecl SP_cSPCreatureBase_Hide(void* p);             // 0x00c0f280
void  __cdecl SP_cSPCreatureBase_Show(void* p);             // 0x00c0f2b0
void* __cdecl VecClear(void* p);                            // 0x00743b50
void* __cdecl SPUIHelpers_CenterWindowInRect(void* p);      // 0x00810000
bool  __cdecl cSPUILayout_Init(void* p, void* key, bool a, int b); // 0x008120d0
int*  __cdecl FUN_00b18e00(void* app);                     // 0x00b18e00
int   __cdecl FUN_00efe6a0(void* id);                      // 0x00efe6a0
int*  __cdecl FUN_00efc910();                              // 0x00efc910
int*  __cdecl FUN_00ff3f00(void* a);                       // 0x00ff3f00
int   __cdecl FUN_00eec870(int p);                         // 0x00eec870
int*  __cdecl FUN_00f3bcb0();                              // 0x00f3bcb0
void  __cdecl FUN_00f3e8a0(int p);                         // 0x00f3e8a0
void  __cdecl FUN_00f25190(void* out, void* flag);         // 0x00f25190
void* __cdecl FUN_00f3d780(int resource);                  // 0x00f3d780
void* __cdecl operator_new(uint size, const char* file, int a, int b, int c, int d); // 0x00f473a0
void  __cdecl operator_delete__(void* p);                  // 0x00f47380
void* __cdecl eastl_vector_insert(void* dst, void* src, int size); // 0x011e0744
void  __cdecl eastl_vector_insert_boundary(void* dst, void* src, void* end); // 0x011e0744
void* __cdecl EAAllocate(uint size, const char* name, int a, int b, const char* file, int line); // 0x00f473a0
void  __cdecl FUN_004c0530(void* v, void* src, int n);     // 0x004c0530
void  __cdecl FUN_00b96600(void* end, void* value);        // 0x00b96600
void  __cdecl FUN_00b93c60(int n, void* v);                // 0x00b93c60
void  __cdecl FUN_00b8ef40(void* v);                       // 0x00b8ef40
void* __cdecl SPUIHelpers_GetMainWindowArea(void* out);    // 0x00805ea0
int*  __cdecl cSPUILayout_FindWindowByID(void* self, uint id, bool a); // 0x008105b0
bool  __cdecl cSPUILayout_SetVisibility(void* self, bool vis); // 0x00810590
void  __cdecl SPUIHelpers_SetWindowImage(void* w, void* img, uint a); // 0x00807bb0

// window accessor used by the pixel writers
void __fastcall FUN_007c4180(void* self, float* out, float* in); // 0x007c4180

// ---------------------------------------------------------------------------
// engine globals
// ---------------------------------------------------------------------------
extern "C" void* DAT_016c744c;                             // 0x016c744c
extern "C" byte  DAT_016c7494;                             // 0x016c7494
extern "C" byte  DAT_016c7488[];                           // 0x016c7488
extern "C" float DAT_01485720;                             // 0x01485720
extern "C" float DAT_01471064;                             // 0x01471064
extern "C" float DAT_013ebc5c;                             // 0x013ebc5c
extern "C" float DAT_013f4fd0;                             // 0x013f4fd0
extern "C" void* DAT_013cc480;                             // 0x013cc480
extern "C" char  DAT_013f09b4[];                           // 0x013f09b4
extern "C" char  DAT_013ebb38[];                           // 0x013ebb38
extern "C" void* DAT_013f01bc;                             // 0x013f01bc
extern "C" uint  DAT_015a9614;                             // 0x015a9614
extern "C" void* DAT_016c7aa4;                             // 0x016c7aa4

// ---------------------------------------------------------------------------
// thiscall helpers / engine object shapes
// ---------------------------------------------------------------------------
struct WinProc
{
	int __thiscall GetPriority();                          // 0x00e31100
};

struct LayoutMgr
{
	int* __thiscall Next(int* cursor);                     // 0x00b72230 (free helper)
};

struct Transform
{
	void __thiscall xform(float* out, float* in);          // 0x007c4180
};

struct UiWindow
{
	void __thiscall MapPoint(void* out, float x, float y); // vtable +0xc8
	bool __thiscall HitTest(float x, float y);             // vtable +0xbc
};

// A generic engine object exposing a vtable.
struct VObj
{
	void* vtbl[1];
};

static void* vtfn(void* o, int off)
{
	return *(void**)((byte*)(*(void***)o) + off);
}

// ---------------------------------------------------------------------------
// Deactivate -- tear down the active badge window set
// @ 0x00ebebc0
int FUN_00ebebc0()
{
	int* app = FUN_0067dd50();
	void* rect = (*(void* (__thiscall*)(void*))(*(void***)app)[7])(app);
	float fx = (float)*(int*)((byte*)rect + 8);
	float fy = (float)*(int*)((byte*)rect + 0xc);

	int cursor = ((WinProc*)DAT_016c744c)->GetPriority();

	for (;;)
	{
		int* e = FUN_00b72230(&cursor);
		if (e == 0)
			return 0;

		if (((e[6] - e[5]) & ~3) != 0)
		{
			void* win = (void*)cSPUILayout_FindWindowByID((void*)e[0xa], 0x100a0000, true);
			float pos[2];
			(*(void (__thiscall*)(void*, float*, float, float))(*(void***)win)[0x32])(win, pos, fx, fy);
			if ((*(bool (__thiscall*)(void*, float, float))(*(void***)win)[0x2f])(win, pos[0], pos[1]))
				return e[5];
		}
	}
}

// ---------------------------------------------------------------------------
// FUN_00ebecc0 -- compute the on-screen rect of a resource by id
// @ 0x00ebecc0
void FUN_00ebecc0(float* out, int resource)
{
	void* res = FUN_00eeca30(resource);
	void* app = SP_App();
	int   id  = (*(int (__thiscall*)(void*))(*(void***)res)[0xb])(res);

	float local[2];
	void* xf = (*(void* (__thiscall*)(void*, float*, int))(*(void***)app)[0x16])(app, local, id);
	((Transform*)xf)->xform(local, (float*)id);

	float area[4];
	SPUIHelpers_GetMainWindowArea(area);

	out[0] = (local[0] + 1.0f) * area[2] * 0.5f;
	out[1] = (1.0f - local[1]) * area[3] * 0.5f;
}

// ---------------------------------------------------------------------------
// FUN_00ebed50 -- show/hide the badge creature and notify the badge object
// @ 0x00ebed50
void FUN_00ebed50(int enable)
{
	int* mgr = FUN_00eec0d0();
	if (mgr == 0)
		return;

	int* creature  = (*(int* (__thiscall*)(void*, uint))(*(void***)mgr)[3])(mgr, 0xce9f6639);
	int* objA      = (*(int* (__thiscall*)(void*, uint))(*(void***)mgr)[3])(mgr, 0x175cdc9);
	int* objB      = (*(int* (__thiscall*)(void*, uint))(*(void***)mgr)[3])(mgr, 0x3a25119);

	if (creature != 0)
	{
		*(byte*)((byte*)creature + 0xf90) = enable;
		int* v = (int*)FUN_00b18e00(mgr);
		if (v != 0 && (*(bool (__thiscall*)(void*))(*(void***)v)[0x27])(v))
		{
			if ((byte)enable == 0)
				((CreatureBase*)creature)->Hide();
			else
				((CreatureBase*)creature)->Show();
		}
	}
	else if (objA != 0)
	{
		(*(void (__thiscall*)(void*, byte))(*(void***)objA)[0x15])(objA, enable);
	}
	else if (objB != 0)
	{
		(*(void (__thiscall*)(void*, byte))(*(void***)objB)[0x18])(objB, enable);
	}

	if (mgr[5] != 0)
		(*(void (__thiscall*)(void*, byte))(*(void***)mgr[5])[4])((void*)mgr[5], enable);
}

// ---------------------------------------------------------------------------
// FUN_00ebee10 -- bounding box (with 25px padding) for a list of resources
// @ 0x00ebee10
float* FUN_00ebee10(float* out, int* list)
{
	float lo[2];

	if (DAT_016c7494 == 0)
	{
		float* p = out;
		FUN_00ebecc0(lo, *(int*)*list);
		lo[0] = p[0];
		out[0] = lo[0] - 25.0f;
	}
	else
	{
		lo[0] = 0.0f;
		lo[1] = 0.0f;
		int* end = (int*)list[1];
		for (int* it = (int*)*list; it != end; ++it)
		{
			void* res = FUN_00eeca30(*it);
			void* app = SP_App();
			int   id  = (*(int (__thiscall*)(void*))(*(void***)res)[0xb])(res);
			float local[2];
			void* xf = (*(void* (__thiscall*)(void*, float*, int))(*(void***)app)[0x16])(app, local, id);
			((Transform*)xf)->xform(local, (float*)id);
			float area[4];
			SPUIHelpers_GetMainWindowArea(area);
			lo[0] += (local[0] + 1.0f) * area[2] * 0.5f;
			lo[1] += (1.0f - local[1]) * area[3] * 0.5f;
		}
		int n = (int)(((char*)list[1] - (char*)*list) >> 2);
		float inv = 1.0f / (float)n;
		lo[0] *= inv;
		lo[1] *= inv;
		out[0] = lo[0] - 25.0f;
	}

	out[3] = lo[1] + 25.0f;
	out[2] = lo[0] + 25.0f;
	out[1] = lo[1] - 25.0f;
	return out;
}

// ---------------------------------------------------------------------------
// FUN_00ebefa0 -- insert a range into the layout event vector (EASTL)
// @ 0x00ebefa0
struct Vec14
{
	int* begin;
	int* end;
	int* cap;
	void __thiscall insert(void* pos, void* first, void* last, void* extra); // 0x00ebefa0
};

void FUN_00ebefa0(Vec14* self, int* pos, int* first, int* last, void* extra)
{
	(void)extra;
	if (first == last)
		return;

	int* oldEnd = self->end;
	int  count  = (int)(last - first);
	int  tail   = (int)(self->cap - oldEnd);

	if (count <= tail)
	{
		int before = (int)(oldEnd - pos);
		if (before <= count)
		{
			// the new range spills past the current end: move the tail of the
			// source range behind end, then shift the old [pos,end) after it
			int* srcTail = first + before;
			eastl_vector_insert(oldEnd, srcTail, (int)((byte*)last - (byte*)srcTail));
			self->end += (count - before);
			eastl_vector_insert(self->end, pos, (int)((byte*)oldEnd - (byte*)pos));
			self->end += before;
			eastl_vector_insert_boundary(pos, first, srcTail);
			return;
		}

		int* slot = oldEnd - count;
		eastl_vector_insert(oldEnd, slot, (int)((byte*)oldEnd - (byte*)slot));
		self->end += count;
		eastl_vector_insert_boundary(slot, pos, oldEnd);
		eastl_vector_insert(pos, first, count * 4);
		return;
	}

	// grow: at least double, but enough for the inserted range
	int size = (int)(self->end - self->begin);
	int newCap = size * 2;
	if (size == 0)
		newCap = 1;
	if (newCap < size + count)
		newCap = size + count;
	if (newCap == 0)
		newCap = 0;

	int* storage = 0;
	if (newCap != 0)
		storage = (int*)EAAllocate(newCap * 4, DAT_013f09b4, 0, 0, DAT_013ebb38, 0xd1);

	int* mid = (int*)eastl_vector_insert(storage, self->begin, (int)((byte*)pos - (byte*)self->begin));
	mid = (int*)((byte*)eastl_vector_insert(mid, first, count * 4) + count * 4);
	int* newEnd = (int*)eastl_vector_insert(mid, pos, (int)((byte*)self->end - (byte*)pos));

	int* oldBegin = self->begin;
	if (oldBegin != 0 && *(int*)((byte*)oldBegin - 4) != 0)
		operator_delete__(oldBegin);

	self->end   = (int*)((byte*)newEnd + ((byte*)self->end - (byte*)pos));
	self->begin = storage;
	self->cap   = storage + newCap;
}

// ---------------------------------------------------------------------------
// FUN_00ebf160 -- create the badge layout windows
// @ 0x00ebf160
void FUN_00ebf160()
{
	int* obj = (int*)operator_new(0x1c, DAT_013f09b4, 0, 0, 0, 0);
	if (obj != 0)
		VecClear((void*)obj);
	DAT_016c744c = obj;
	FUN_00b72080(0x30, 0x40);

	void* windows[64];
	for (int i = 0; i < 0x40; ++i)
	{
		void* w = operator_new(0x18, DAT_013f09b4, 0, 0, 0, 0);
		if (w != 0)
			SPUIHelpers_CenterWindowInRect(w);
		windows[i] = w;
		cSPUILayout_Init(w, DAT_016c7488, true, 0x3469e7a3);
	}

	for (int i = 0x40; i != 0; --i)
	{
		int* key = FUN_00b72160();
		int* e = FUN_00b72210((int)key);
		int* old = (int*)e[0xa];
		int* nw = (int*)windows[i - 1];
		if (nw != old)
		{
			if (nw != 0)
				(*(void (__thiscall*)(void*))(*(void***)nw)[1])(nw);
			e[0xa] = (int)nw;
			if (old != 0)
				(*(void (__thiscall*)(void*))(*(void***)old)[2])(old);
		}
		byte* src = (byte*)e[6];
		byte* dst = (byte*)e[5];
		eastl_vector_insert(dst, src, 0);
		e[6] += (int)((src - dst) >> 2) * -4;
		cSPUILayout_SetVisibility((void*)e[0xa], false);
	}
}

// ---------------------------------------------------------------------------
// FUN_00ebf290 -- place or refresh the badge for one scenario object
// @ 0x00ebf290
void FUN_00ebf290(int obj, int* cursor)
{
	int rating = FUN_00efe6a0((void*)obj);
	FUN_00ebed50(rating == 0);

	if (rating != 1)
		return;

	int* target = FUN_00efc910();
	float box[4];
	FUN_00ebecc0(box, obj);

	float left   = box[0] - 25.0f;
	float top    = box[1] - 25.0f;
	float right  = box[0] + 25.0f;
	float bottom = box[1] + 25.0f;

	int it = ((WinProc*)DAT_016c744c)->GetPriority();
	for (int* e = FUN_00b72230(&it); e != 0; e = FUN_00b72230(&it))
	{
		if (((e[6] - e[5]) & ~3) == 0)
			continue;
		if ((int*)*(int*)e[5] == target)
			continue;
		if (!(*(float*)(e + 3) > left))
			continue;
		if (!(right > *(float*)(e + 1)))
			continue;
		if (!(*(float*)(e + 4) > top))
			continue;
		if (!(bottom > *(float*)(e + 2)))
			continue;

		int* a = e + 5;
		int* endp = (int*)a[1];
		if (endp < (int*)a[2])
		{
			a[1] = (int)(endp + 1);
			if (endp != 0)
				*endp = obj;
		}
		else
		{
			FUN_00b96600(endp, &obj);
		}

		float tmp[4];
		float* r = FUN_00ebee10(tmp, a);
		*(float*)(e + 1) = r[0];
		*(float*)(e + 2) = r[1];
		*(float*)(e + 3) = r[2];
		*(float*)(e + 4) = r[3];
		*(byte*)(e + 0xb) = 1;
		return;
	}

	int* e = FUN_00b72230(cursor);
	if (e == 0)
		return;

	*(float*)(e + 1) = left;
	*(float*)(e + 2) = top;
	*(float*)(e + 3) = right;
	*(float*)(e + 4) = bottom;

	int* a = e + 5;
	int* endp = (int*)a[1];
	if (endp < (int*)a[2])
	{
		a[1] = (int)(endp + 1);
		if (endp != 0)
			*endp = obj;
	}
	else
	{
		FUN_00b96600(endp, &obj);
	}
	*(byte*)(e + 0xb) = 0;
}

// ---------------------------------------------------------------------------
// FUN_00ebf480 -- swap two layout event vectors
// @ 0x00ebf480
void FUN_00ebf480(int* a, int* b)
{
	int* av = (int*)a[0];
	int* bv = (int*)b[0];
	if ((av == 0 || av[-1] != 0) && (bv == 0 || bv[-1] != 0))
	{
		a[0] = (int)bv;
		b[0] = (int)av;
		int t = a[1]; a[1] = b[1]; b[1] = t;
		t = a[2]; a[2] = b[2]; b[2] = t;
		return;
	}

	FUN_00b93c60((a[1] - (int)av) >> 2, a + 3);
	byte* tmp = (byte*)0;
	int n = a[1] - a[0];
	tmp = (byte*)eastl_vector_insert(tmp, (void*)a[0], n);
	tmp += (n >> 2) * 4;
	FUN_00b8ef40(b);
	FUN_00b8ef40(&tmp);
	if (tmp != 0 && *(int*)(tmp - 4) != 0)
		operator_delete__(tmp);
}

// ---------------------------------------------------------------------------
// FUN_00ebf530 -- merge one badge rectangle into another
// @ 0x00ebf530
void FUN_00ebf530(int* dst, int* src)
{
	Vec14* v = (Vec14*)(dst + 5);
	v->insert((void*)dst[6], (void*)src[5], (void*)src[6], src);

	float box[4];
	float* r = FUN_00ebee10(box, dst + 5);
	float* f = (float*)dst;
	f[1] = r[0];
	f[2] = r[1];
	f[3] = r[2];
	f[4] = r[3];
	*(byte*)(dst + 0xb) = 1;

	byte* s = (byte*)src[6];
	byte* d = (byte*)src[5];
	eastl_vector_insert(d, s, (int)((byte*)src[6] - s));
	src[6] += (int)((s - d) >> 2) * -4;
}

// ---------------------------------------------------------------------------
// FUN_00ebf5b0 -- lay out all active badges
// @ 0x00ebf5b0
void FUN_00ebf5b0()
{
	int it = ((WinProc*)DAT_016c744c)->GetPriority();
	int* e = FUN_00b72230(&it);
	while (e != 0)
	{
		byte* s = (byte*)e[6];
		byte* d = (byte*)e[5];
		eastl_vector_insert(d, s, 0);
		e[6] += (int)((s - d) >> 2) * -4;
		cSPUILayout_SetVisibility((void*)e[0xa], false);
		e = FUN_00b72230(&it);
	}

	int cursor = ((WinProc*)DAT_016c744c)->GetPriority();
	int* cur = FUN_00efc910();
	if (cur != 0)
		FUN_00ebf290((int)cur, &cursor);
	int* other = FUN_00ff3f00(0);
	if (other != 0 && other != cur)
		FUN_00ebf290((int)other, &cursor);

	// drop stale entries from the active list
	int mgr = *(int*)(*(int*)((byte*)DAT_016c7aa4 + 0x74) + 0x10);
	int* begin;
	if (*(uint*)(mgr + 0x2c24) < 0x3fffffff)
		begin = (int*)(*(uint*)(mgr + 0x2c24) * 0x238 + *(int*)(mgr + 0x2c10));
	else
		begin = *(int**)(mgr + 0x2c14);
	int* end = *(int**)(mgr + 0x2c14);
	int* p = begin;
	while (p != end)
	{
		if ((int*)p + 1 != cur)
			FUN_00ebf290((int)(p + 1), &cursor);
		uint flags;
		do
		{
			flags = (uint)*p;
			p += 0x8e;
			if ((flags >> 0x1e) & 1)
				break;
		} while ((int)*p < 0);
	}

	// pairwise non-overlapping placement
	bool moved;
	do
	{
		moved = false;
		int it2 = ((WinProc*)DAT_016c744c)->GetPriority();
		int* a = FUN_00b72230(&it2);
		while (a != 0)
		{
			if (((a[6] - a[5]) & ~3) != 0 && *(byte*)(a + 0xb) != 0 && (int*)*(int*)a[5] != cur)
			{
				int it3 = it2;
				int* b = FUN_00b72230(&it3);
				while (b != 0)
				{
					if (a != b && ((b[6] - b[5]) & ~3) != 0 &&
					    (int*)*(int*)b[5] != cur &&
					    (float)b[2] <= (float)a[3] && (float)a[3] != (float)b[2] &&
					    (float)a[2] <= (float)b[3] && (float)b[3] != (float)a[2] &&
					    (float)b[1] <= (float)a[4] && (float)a[4] != (float)b[1] &&
					    (float)a[1] <= (float)b[4] && (float)b[4] != (float)a[1])
					{
						FUN_00ebf530(a, b);
						moved = true;
						break;
					}
					b = FUN_00b72230(&it3);
				}
			}
			a = FUN_00b72230(&it2);
		}
	} while (moved);

	// attach the badge image to every remaining entry
	int it4 = ((WinProc*)DAT_016c744c)->GetPriority();
	for (int* w = FUN_00b72230(&it4); w != 0; w = FUN_00b72230(&it4))
	{
		if (((w[6] - w[5]) & ~3) == 0)
			continue;
		void* res = FUN_00f3d780(*(int*)w[5]);
		if (res == 0)
			continue;
		int img = FUN_00eec870((int)res);
		int n = (w[6] - w[5]) >> 2;
		if (n != 0)
		{
			byte flag = 0;
			int* first = (int*)*(int*)w[5];
			int* curObj = FUN_00ff3f00(0);
			byte data[16];
			if (curObj == first)
			{
				int* q = FUN_00f3bcb0();
				*(int*)(data + 4) = *(int*)q;
				*(int*)(data + 8) = q[1];
				*(int*)(data + 0xc) = q[2];
				*(int*)(data + 0) = 0x2f7d0004;
			}
			else
			{
				FUN_00f3e8a0(*first);
				FUN_00f25190(data, &flag);
			}
			int* win = (int*)cSPUILayout_FindWindowByID((void*)w[0xa], 0x100a0000, true);
			SPUIHelpers_SetWindowImage(win, data, 0xffffffff);
			cSPUILayout_SetVisibility((void*)w[0xa], true);
			(*(void (__thiscall*)(void*, uint))(*(void***)win)[0x17])(win, flag ? DAT_015a9614 : 0xffffffff);

			int* w2 = (int*)cSPUILayout_FindWindowByID((void*)w[0xa], 0x100a0200, true);
			(*(void (__thiscall*)(void*, int))(*(void***)w2)[0x17])(w2, img);
			int* w3 = (int*)cSPUILayout_FindWindowByID((void*)w[0xa], 0x100a0002, true);
			(*(void (__thiscall*)(void*, int, int))(*(void***)w3)[0x1f])(w3, 1, 0);
			int* w4 = (int*)cSPUILayout_FindWindowByID((void*)w[0xa], 0x100a0003, true);
			(*(void (__thiscall*)(void*, int, int))(*(void***)w4)[0x1f])(w4, 1, 0);
			int* w5 = (int*)cSPUILayout_FindWindowByID((void*)w[0xa], 0x100a1000, true);
			(*(void (__thiscall*)(void*, int, int))(*(void***)w5)[0x1f])(w5, 1, 0);
			int* w6 = (int*)cSPUILayout_FindWindowByID((void*)w[0xa], 0xffffffff, true);
			(*(void (__thiscall*)(void*, float, float))(*(void***)w6)[0x19])(w6,
				(*(float*)(w + 3) + *(float*)(w + 1)) * 0.5f,
				(*(float*)(w + 4) + *(float*)(w + 2)) * 0.5f);

			if (n > 1)
			{
				int* a2 = (int*)cSPUILayout_FindWindowByID((void*)w[0xa], 0x100a0002, true);
				(*(void (__thiscall*)(void*, int, int))(*(void***)a2)[0x1f])(a2, 1, 1);
			}
			if (n > 2)
			{
				int* a3 = (int*)cSPUILayout_FindWindowByID((void*)w[0xa], 0x100a0003, true);
				(*(void (__thiscall*)(void*, int, int))(*(void***)a3)[0x1f])(a3, 1, 1);
				int* a4 = (int*)cSPUILayout_FindWindowByID((void*)w[0xa], 0x100a1000, true);
				(*(void (__thiscall*)(void*, int, int))(*(void***)a4)[0x1f])(a4, 1, 1);
			}
		}
	}
}
