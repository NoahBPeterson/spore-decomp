// s00bf2ce0 -- SP::cCivilization: star-record bookkeeping, streaming of its
// id maps, embassy/first-contact checks and the class destructor.
// Engine objects are addressed by fixed offsets.

typedef unsigned char byte;
typedef unsigned int uint;

// ---------------------------------------------------------------------------
// engine routines (defined elsewhere)
// ---------------------------------------------------------------------------
int   __cdecl    WriteUint32(void* stream, const void* data, int count, int a); // 0x0093aa70
int   __cdecl    ReadInt32(void* stream, void* data, int count, int a);        // 0x0093a780
void* __cdecl    RBTreeIncrement(void* node);                                  // 0x00921580
void* __cdecl    do_copy(void* first, void* last, void* dst);                  // 0x006782c0
void  __cdecl    operator_delete(void* p);                                     // 0x00f47380
void* __cdecl    EAAllocate(uint size, const char* file, int a, int b, int c, int line); // 0x00f473a0
void* __cdecl    SP_BehaviorManager();                                         // 0x00b3d260
void* __cdecl    SP_NounManager();                                             // 0x00b3d300
void* __cdecl    SP_RelationshipManager();                                     // 0x00b3d2c0
void* __cdecl    CommManager();                                                // 0x00b3d4a0
void* __cdecl    FUN_01021260();                                               // 0x01021260
int   __cdecl    FUN_00b26930();                                               // 0x00b26930

void  __fastcall FUN_00bf1b60(void* self);                                     // 0x00bf1b60
void* __fastcall GetPlayerCivilization(void* self);                            // 0x00b25fb0
void* __fastcall GetCivilizationList(void* self);                              // 0x00b25ca0
int   __fastcall CommScreen_IsActive(void* self);                              // 0x00ae9390
void* __fastcall GetCommContext(void* self, int dummy, int a, int b, int c);   // 0x00ce6950
void  __fastcall cCommManager_ShowCommEvent(void* self, int dummy, void* a, void* b, void* c, int d); // 0x00aeb760
int   __fastcall FUN_00bef620(void* self, int dummy, int a);                   // 0x00bef620
uint  __fastcall RandomUint32Uniform(void* self, int dummy, int range);        // 0x00a68fb0
void  __fastcall FUN_00ba95a0(void* self, int dummy, void* list);              // 0x00ba95a0
int   __fastcall FUN_00be2b10(void* self, int dummy, int tag, int** out);      // 0x00be2b10
int   __fastcall FUN_00bd9b60(void* self);                                     // 0x00bd9b60
int*  __fastcall cCity_GetPositionPtr(void* self);                             // 0x00fa0e00
void  __fastcall FUN_00ae6970(void* self);                                     // 0x00ae6970
void  __fastcall FUN_00aed92d0(void* self);                                    // 0x00ad92d0
void  __fastcall cGonzagoTimer_dtor(void* self);                               // 0x00b638b0
void  __fastcall FUN_00b6edf0(void* self);                                     // 0x00b6edf0
void  __fastcall cGameData_dtor(void* self);                                   // 0x00b184c0
void  __fastcall SetSerializer_or_release(void* self);                         // 0x00c2e4e0
void  __fastcall SimSingleton_ctor(void* self);                                // 0x00ae5c30
void* __cdecl    ConvertToString16(void* dst, int str, int len);              // 0x0093c5a0
void  __fastcall RangeInitialize(void* self, int dummy, int a);                // 0x00579a90
void  __fastcall eastl_wstring_ctor(void* self, int dummy, void* src);         // 0x0056e2d0
int   __cdecl    FUN_00ae5530(void* a, int b, void* c, void* d);              // 0x00ae5530

extern "C" int   DAT_0167a60c;      // 0x0167a60c  (Simulator::SimSingleton*)
extern "C" float DAT_0168c514;      // 0x0168c514
extern "C" float DAT_0168c518;      // 0x0168c518
extern "C" float DAT_0168c51c;      // 0x0168c51c
extern "C" int   DAT_018ea2cc;      // 0x018ea2cc
extern "C" char  DAT_0145f924[];    // 0x0145f924  "Simulator/SimSingleton"
extern "C" short DAT_0145ba48[];    // 0x0145ba48  L"EA::ResourceMan::Key"
extern "C" char  DAT_013f6254;      // 0x013f6254  empty wchar buffer
extern "C" int   vtbl_014693b8[];   // 0x014693b8
extern "C" int   vtbl_014693a4[];   // 0x014693a4
extern "C" int   vtbl_0146938c[];   // 0x0146938c
extern "C" int   vtbl_0146937c[];   // 0x0146937c
extern "C" int   vtbl_01469360[];   // 0x01469360
extern "C" int   vtbl_013eb394[];   // 0x013eb394

typedef int (__thiscall *T0)(void*);          // virtual call, no stack args
typedef int (__thiscall *T1)(void*, int);     // virtual call, one stack arg

struct Tri { int a, b, c; };

// engine members called as ordinary this-calls (names define the callee ABI)
struct Eng {
	void  Sub3b50(int noun);                              // 0x00bf3b50
	void  RemoveNoun(void* noun);                         // 0x00b225d0
	void  Eb6280(void* a);                                // 0x00eb6280
	void  NukeSubtree(void* node);                        // 0x009a9600
	void  E2ed0(void* out);                               // 0x00ae2ed0
	int   B2b10(int tag, int** out);                      // 0x00be2b10
	int   Bf2710(void* a, void* b, int c);                // 0x00bf2710
	int   Bf2e70(void* a, void* b, int c);                // 0x00bf2e70
	void* Bf2da0(void* out, void* where, void* key, int flag); // 0x00bf2da0
	void* Bf9700(int key);                                // 0x00bf9700
	int*  FindEmb(int* out, int* key);                    // 0x00e39fb0
	void* GetCommCtx(int a, int b, int c, int d);         // 0x00ce6950
	void  ShowCommEvent(void* a, void* b, void* c, int d); // 0x00aeb760
	int   RelCheck(int a);                                // 0x00bef620
	uint  RandomUniform(int range);                       // 0x00a68fb0
	void  ListCopy(void* list);                            // 0x00ba95a0
	int   AddKey(void* a, void* b, int c);                // 0x00ae5530
	void* ToString16(int a, int b);                       // 0x0093c5a0
	void  RangeInit(int a);                               // 0x00579a90
	void  WstringCtor(void* src);                          // 0x0056e2d0
};

// ---------------------------------------------------------------------------
// stream the civilization's star-record set to an IO stream
// @ 0x00bf2ce0
void __cdecl FUN_00bf2ce0(int* stream, int* set)
{
	int* obj = (int*)((T0)(*(int*)(*stream + 0x20)))((void*)stream);
	int writer = ((T0)(*(int*)(*obj + 0x18)))((void*)obj);
	int key = set[5];
	WriteUint32((void*)writer, &key, 1, 0);

	for (int node = set[2]; node != (int)set + 4; node = (int)RBTreeIncrement((void*)node))
	{
		int id = 0;
		int* p = *(int**)(node + 0x10);
		if (p != 0)
			id = ((T1)(*(int*)(*p + 0xc)))((void*)p, 0x179c807);

		((T1)(*(int*)(*stream + 0x2c)))((void*)stream, id);
		((T0)(*(int*)(*stream + 0x1c)))((void*)stream);

		int* o2 = (int*)((T0)(*(int*)(*stream + 0x20)))((void*)stream);
		int w2 = ((T0)(*(int*)(*o2 + 0x18)))((void*)o2);
		int star = *(int*)(node + 0x14);
		WriteUint32((void*)w2, &star, 1, 0);
		((T0)(*(int*)(*stream + 0x1c)))((void*)stream);
	}
	((T0)(*(int*)(*stream + 0x1c)))((void*)stream);
}

// ---------------------------------------------------------------------------
// number of halved "counts" of the civilization's star records, by mode
// @ 0x00bf2f00
int __fastcall FUN_00bf2f00(int self, int dummy, int mode)
{
	int* it = (int*)*(int*)(self + 0x9c);
	int* end = (int*)*(int*)(self + 0xa0);
	int total = 0;
	int limit = 0xf;

	if (it != end)
	{
		do
		{
			int obj = *it;
			int count = 3;
			if (mode == 0)
			{
				int* v[3] = { 0, 0, 0 };
				((Eng*)obj)->B2b10((int)&DAT_018ea2cc, v);
				count = (int)((((int)v[1] - (int)v[0]) >> 2) + 1U) >> 1;
				limit = 0xf;
				for (int** p = (int**)v[0]; (int)p < (int)v[1]; p++)
					if (*p != 0)
						(*(T0*)(*(int*)*p + 4))((void*)*p);
				if (v[0] != 0 && v[0][-1] != 0)
					operator_delete(v[0]);
			}
			else if (mode == 1)
			{
				int* pos = cCity_GetPositionPtr((void*)obj);
				if (*(float*)pos != DAT_0168c514 || *(float*)((char*)pos + 4) != DAT_0168c518
				    || *(float*)((char*)pos + 8) != DAT_0168c51c)
				{
					int* v[3] = { 0, 0, 0 };
					((Eng*)obj)->B2b10((int)&DAT_018ea2cc, v);
					count = (int)((uint)(((int)v[1] - (int)v[0]) >> 2) >> 1);
					limit = 0xa;
					FUN_00ae6970(v);
				}
			}
			else if (mode == 2)
			{
				int n = FUN_00bd9b60((void*)obj);
				count = (n + 1) / 2;
				limit = 0xf;
			}
			total += count < 3 ? count : 3;
			it++;
		} while (it != end);
	}
	return total < limit ? total : limit;
}

// ---------------------------------------------------------------------------
// map a communication hash to its embassy-data key, then look the record up
// @ 0x00bf30b0
void __fastcall FUN_00bf30b0(int self, int dummy, int key, Tri* out)
{
	int mapped = -1;
	switch (key)
	{
	case 0x441cd3e6:
	case 0x8f963dcb:
		mapped = 0x7d433fad;
		break;
	case 0x1f2a25b6:
	case 0x449c040f:
		mapped = 0x9ad7d4aa;
		break;
	case 0x1a4e0708:
	case 0x2a5147a9:
		mapped = 0xf670aa43;
		break;
	case 0x4e3f7777:
	case 0x47c10953:
	case 0x72c49181:
		mapped = 0x99e92f05;
		break;
	}

	int slot;
	int arg = mapped;
	int** res = (int**)((Eng*)self)->FindEmb(&slot, &arg);
	if (*res != (int*)(self + 4))
	{
		Tri* v = (Tri*)((Eng*)self)->Bf9700(mapped);
		out->a = v->a;
		out->b = v->b;
		out->c = v->c;
		return;
	}

	Tri t;
	t.a = -1;
	t.b = -1;
	t.c = -1;
	*out = t;
}

// ---------------------------------------------------------------------------
// periodically show the embassy / first-contact communication events
// @ 0x00bf3180
void __fastcall FUN_00bf3180(int* self)
{
	if ((*(int*)((char*)self + 0xa0) - *(int*)((char*)self + 0x9c)) & 0xfffffffc)
	{
		if (DAT_0167a60c == 0)
		{
			int p = (int)EAAllocate(0xc8, DAT_0145f924, 0, 0, 0, 0);
			if (p != 0)
			{
				SimSingleton_ctor((void*)p);
				DAT_0167a60c = p;
			}
			else
			{
				DAT_0167a60c = 0;
			}
		}

		if (*(int*)(DAT_0167a60c + 0xb0) <= 0)
		{
			int* civ = (int*)self[0x27];
			if (civ != 0)
			{
				int* player = (int*)GetPlayerCivilization(SP_NounManager());
				if (player != 0 && *(char*)((char*)player + 0x8d) != 0 && player[0xa6] >= 3
				    && *(char*)((char*)player + 0x4cc) == 0)
				{
					if (CommScreen_IsActive(CommManager()) == 0 && *(char*)((char*)self + 0x90) == 0)
					{
						if (*(char*)((char*)self + 0x91) != 0)
						{
							int* ctx = (int*)GetCommContext((void*)(*(int*)((char*)FUN_01021260() + 0x13c)), 0,
							                                0xdbf385bf, 0xd9597cc9, 0);
							cCommManager_ShowCommEvent(CommManager(), 0, (void*)civ, (void*)civ, ctx, 0);
							*(char*)((char*)self + 0x90) = 1;
						}

						if (RandomUint32Uniform((void*)0x1601760, 0, 0x14) == 0)
						{
							int a = (*(T0*)(*(int*)player + 0x4c))((void*)player);
							int b = (*(T1*)(*self + 0x4c))((void*)self, a);
							if (FUN_00bef620(SP_RelationshipManager(), 0, b) != 0)
							{
								int* list = 0;
								FUN_00ba95a0((void*)GetCivilizationList(SP_NounManager()), 0, &list);
								int* begin = list;
								int count = (int)((char*)list - (char*)begin) >> 2;
								int n = (int)((char*)list - (char*)begin);
								(void)n;
								int total = 0;
								for (int i = 0; i < count; i++)
								{
									int* c = (int*)((int*)begin)[i];
									if (c == self || c == player
									    || FUN_00bef620(SP_RelationshipManager(), 0,
									                     (*(T1*)(*(int*)c + 0x4c))((void*)c,
									                        (*(T0*)(*(int*)player + 0x4c))((void*)player))) != 0)
										total += (*(int*)((char*)c + 0xa0) - *(int*)((char*)c + 0x9c)) >> 2;
								}
								if (total == *(int*)(FUN_00b26930() + 0xac))
								{
									int* ctx = (int*)GetCommContext((void*)(*(int*)((char*)FUN_01021260() + 0x13c)), 0,
									                                0xdbf385bf, 0x6b6ad65e, 0);
									cCommManager_ShowCommEvent(CommManager(), 0, (void*)civ, (void*)civ, ctx, 0);
									*(char*)((char*)self + 0x90) = 1;
								}
								FUN_00ae6970(&list);
								return;
							}

							if (((*(int*)((char*)self + 0xa0) - *(int*)((char*)self + 0x9c)) & 0xfffffffc) == 4)
							{
								int n2 = (*(int*)((char*)player + 0xa0) - *(int*)((char*)player + 0x9c)) >> 2;
								if (n2 + 1 == *(int*)(FUN_00b26930() + 0xac))
								{
									int* ctx = (int*)GetCommContext((void*)(*(int*)((char*)FUN_01021260() + 0x13c)), 0,
									                                0xdbf385bf, 0xd9597cc9, 0);
									cCommManager_ShowCommEvent(CommManager(), 0, (void*)civ, (void*)civ, ctx, 0);
									*(char*)((char*)self + 0x90) = 1;
								}
							}
						}
					}
				}
			}
		}
	}
}

// ---------------------------------------------------------------------------
// erase one element of an intrusive vector and release it
// @ 0x00bf3420
int __fastcall FUN_00bf3420(int* v, int dummy, int pos)
{
	if ((uint)(pos + 4) < (uint)v[1])
		do_copy((void*)(pos + 4), (void*)v[1], (void*)pos);

	v[1] -= 4;
	int* end = (int*)v[1];
	int obj = *end;
	if (obj != 0)
		(*(T0*)(*(int*)obj + 4))((void*)obj);
	return pos;
}

// ---------------------------------------------------------------------------
// load the id -> world map from the stream
// @ 0x00bf34f0
void __fastcall FUN_00bf34f0(int* self, int dummy, int* map)
{
	((Eng*)map)->NukeSubtree((void*)map[3]);

	int* anchor = (int*)((char*)map + 4);
	*anchor = (int)anchor;
	map[2] = (int)anchor;
	map[3] = 0;
	*(char*)((char*)map + 0x10) = 0;
	map[5] = 0;

	int count = 0;
	int* w = (int*)((T0)(*(int*)(*self + 0x20)))((void*)self);
	int stream = ((T0)(*(int*)(*w + 0x18)))((void*)w);
	ReadInt32((void*)stream, &count, 1, 0);

	for (uint i = 0; i < (uint)count; i++)
	{
		int key = 0;
		int world[3] = { 0, 0, 0 };

		int* w2 = (int*)((T0)(*(int*)(*self + 0x20)))((void*)self);
		int s2 = ((T0)(*(int*)(*w2 + 0x18)))((void*)w2);
		ReadInt32((void*)s2, &key, 1, 0);
		((T0)(*(int*)(*self + 0x1c)))((void*)self);
		((Eng*)self)->E2ed0(world);
		((T0)(*(int*)(*self + 0x1c)))((void*)self);

		int slot = 0;
		int inserted = ((Eng*)map)->Bf2710(&key, world, 0);
		if (inserted == 0)
		{
			*(int*)(slot + 0x14) = world[0];
			*(int*)(slot + 0x18) = world[1];
			*(int*)(slot + 0x1c) = world[2];
		}
	}

	((T0)(*(int*)(*self + 0x1c)))((void*)self);
}

// ---------------------------------------------------------------------------
// destructor of the civilization object
// @ 0x00bf36f0
void __fastcall FUN_00bf36f0(int* self)
{
	int* p = (int*)self[0x10b];
	int* sub = (int*)((char*)self + 0x3c);

	self[0] = (int)vtbl_014693b8;
	self[1] = (int)vtbl_014693a4;
	self[0xd] = (int)vtbl_0146938c;
	self[0xe] = (int)vtbl_0146937c;
	self[0xf] = (int)vtbl_01469360;

	if (p != 0)
	{
		SetSerializer_or_release((void*)p);
		operator_delete(p);
	}
	*(volatile int*)(self + 0x10b) = 0;
	int* q = (int*)*(volatile int*)(self + 0x129);

	if (q != 0)
		(*(T0*)(*(int*)q + 4))((void*)q);
	FUN_00bf1b60((void*)((char*)self + 0x490));
	FUN_00aed92d0((void*)((char*)self + 0x470));

	if ((int*)self[0x11b] != 0)
		(*(T0*)(*(int*)self[0x11b] + 4))((void*)self[0x11b]);
	if ((int*)self[0x11a] != 0)
		(*(T0*)(*(int*)self[0x11a] + 4))((void*)self[0x11a]);
	if ((int*)self[0x119] != 0)
		(*(T0*)(*(int*)self[0x119] + 4))((void*)self[0x119]);
	if ((int*)self[0x118] != 0)
		(*(T0*)(*(int*)self[0x118] + 4))((void*)self[0x118]);
	if ((int*)self[0x117] != 0)
		(*(T0*)(*(int*)self[0x117] + 4))((void*)self[0x117]);
	if ((int*)self[0x116] != 0)
		(*(T0*)(*(int*)self[0x116] + 4))((void*)self[0x116]);
	if ((int*)self[0x115] != 0)
		(*(T0*)(*(int*)self[0x115] + 4))((void*)self[0x115]);

	Eng* eng = (Eng*)((char*)self + 0x410);
	eng->Eb6280((void*)*(volatile int*)(self + 0x107));

	cGonzagoTimer_dtor((void*)((char*)self + 0x3f0));
	cGonzagoTimer_dtor((void*)((char*)self + 0x3c8));
	cGonzagoTimer_dtor((void*)((char*)self + 0x3a0));
	cGonzagoTimer_dtor((void*)((char*)self + 0x378));
	cGonzagoTimer_dtor((void*)((char*)self + 0x350));
	cGonzagoTimer_dtor((void*)((char*)self + 0x328));
	cGonzagoTimer_dtor((void*)((char*)self + 0x300));

	if ((int*)self[0xbe] != 0)
		(*(T0*)(*(int*)self[0xbe] + 4))((void*)self[0xbe]);

	cGonzagoTimer_dtor((void*)((char*)self + 0x2d8));

	if ((int*)self[0xb4] != 0)
		(*(T0*)(*(int*)self[0xb4] + 4))((void*)self[0xb4]);

	cGonzagoTimer_dtor((void*)((char*)self + 0x2b0));

	if ((int*)self[0xab] != 0)
		(*(T0*)(*(int*)self[0xab] + 4))((void*)self[0xab]);
	if ((int*)self[0xaa] != 0)
		(*(T0*)(*(int*)self[0xaa] + 4))((void*)self[0xaa]);
	if ((int*)self[0xa9] != 0)
		(*(T0*)(*(int*)self[0xa9] + 4))((void*)self[0xa9]);

	int e = self[0xa2];
	if ((int)((self[0xa4] - e) & 0xfffffffe) > 2 && e != 0)
		operator_delete((void*)e);

	e = self[0x9e];
	if ((int)((self[0xa0] - e) & 0xfffffffe) > 2 && e != 0)
		operator_delete((void*)e);

	if ((int*)self[0x9d] != 0)
		(*(T0*)(*(int*)self[0x9d] + 4))((void*)self[0x9d]);

	cGonzagoTimer_dtor((void*)((char*)self + 0x248));
	cGonzagoTimer_dtor((void*)((char*)self + 0x228));
	cGonzagoTimer_dtor((void*)((char*)self + 0x208));
	cGonzagoTimer_dtor((void*)((char*)self + 0x1e8));
	cGonzagoTimer_dtor((void*)((char*)self + 0x1c8));
	cGonzagoTimer_dtor((void*)((char*)self + 0x1a8));
	cGonzagoTimer_dtor((void*)((char*)self + 0x188));
	cGonzagoTimer_dtor((void*)((char*)self + 0x168));
	cGonzagoTimer_dtor((void*)((char*)self + 0x148));
	cGonzagoTimer_dtor((void*)((char*)self + 0x128));
	cGonzagoTimer_dtor((void*)((char*)self + 0x108));
	cGonzagoTimer_dtor((void*)((char*)self + 0xe8));

	FUN_00aed92d0((void*)((char*)self + 0xd4));
	FUN_00ae6970((void*)((char*)self + 0xb0));
	FUN_00ae6970((void*)((char*)self + 0x9c));
	Eng* sub2 = (Eng*)((char*)self + 0x6c);
	sub2->NukeSubtree((void*)*(volatile int*)(self + 0x1e));
	FUN_00b6edf0((void*)sub);
	self[0xe] = (int)vtbl_013eb394;
	cGameData_dtor((void*)self);
}

// ---------------------------------------------------------------------------
// remove the given element from the two intrusive containers
// @ 0x00bf3b50
void __fastcall FUN_00bf3b50(int self, int dummy, int noun)
{
	int* p = (int*)*(int*)(self + 0xb0);
	int* e = (int*)*(int*)(self + 0xb4);

	for (; p != e; p++)
	{
		if (*p != noun)
			continue;

		if ((int*)(p + 1) < (int*)*(int*)(self + 0xb4))
			do_copy(p + 1, (void*)*(int*)(self + 0xb4), p);
		*(int*)(self + 0xb4) -= 4;
		int obj = **(int**)(self + 0xb4);
		if (obj != 0)
			(*(T0*)(*(int*)obj + 4))((void*)obj);
		break;
	}

	uint count = (uint)((*(int*)(self + 0xd8) - *(int*)(self + 0xd4)) >> 2);
	int* cur = *(int**)(self + 0xd4);
	for (uint i = 0; i < count; i++, cur++)
	{
		int key = noun != 0 ? noun + 0x34 : 0;
		if (*cur != key)
			continue;

		int* arr = (int*)*(int*)(self + 0xd4);
		int elem = arr[i];
		int last = arr[count - 1];
		if (last != elem)
		{
			if (last != 0)
				(*(T0*)(*(int*)last + 0xbc))((void*)last);
			arr[i] = last;
			if (elem != 0)
				(*(T0*)(*(int*)elem + 0xc0))((void*)elem);
		}
		*(int*)(self + 0xd8) -= 4;
		int obj = **(int**)(self + 0xd8);
		if (obj != 0)
			(*(T0*)(*(int*)obj + 0xc0))((void*)obj);
		return;
	}
}

// ---------------------------------------------------------------------------
// detach a noun from the civilization and drop it
// @ 0x00bf3c50
void __fastcall FUN_00bf3c50(int self, int dummy, int noun)
{
	byte* arg;
	if (noun != 0)
	{
		(*(T0*)(*(int*)noun))((void*)noun);
		arg = (byte*)(noun + 0x5d0);
	}
	else
	{
		arg = 0;
	}

	int* bm = (int*)SP_BehaviorManager();
	(*(T1*)(*(int*)bm + 0x3c))((void*)bm, (int)arg);
	((Eng*)self)->Sub3b50(noun);
	((Eng*)SP_NounManager())->RemoveNoun((void*)noun);
	if (noun != 0)
		(*(T0*)(*(int*)noun + 4))((void*)noun);
}

// ---------------------------------------------------------------------------
// look the key up in the id map, inserting a default entry when missing
// @ 0x00bf3cb0
void* __fastcall FUN_00bf3cb0(int* map, int dummy, int* key)
{
	int* parent = map + 1;
	int* node = (int*)map[3];
	int* where = parent;

	if (node != 0)
	{
		int k = *key;
		while (node != 0)
		{
			if (node[4] < k)
			{
				node = (int*)*node;
			}
			else
			{
				where = node;
				node = (int*)node[1];
			}
		}
	}

	if (where != parent && where[4] <= *key)
		return (char*)where + 0x14;

	int k[4] = { *key, 0, 0, 0 };
	int inserted = 0;
	((Eng*)map)->Bf2da0(&inserted, (void*)where, k, (int)key & 0xffffff00);
	return (char*)inserted + 0x14;
}

// ---------------------------------------------------------------------------
// write the star-record map to the stream as text keys
// @ 0x00bf3d40
byte __cdecl FUN_00bf3d40(int* stream, int id, int* map)
{
	byte ok = 1;
	if (map[5] != 0)
	{
		int* src;
		int tmp[3];

		if (id != 0)
		{
			src = (int*)ConvertToString16(tmp + 1, id, -1);
		}
		else
		{
			tmp[0] = 0;
			tmp[1] = 0;
			tmp[2] = 0;
			((Eng*)tmp)->RangeInit(0);
			src = tmp;
		}

		int str[3];
		((Eng*)str)->WstringCtor(src);
		if (id == 0 && ((tmp[1] - tmp[0]) & 0xfffffffe) > 2 && tmp[0] != 0)
			operator_delete((void*)tmp[0]);
		if (id != 0 && ((tmp[2] - tmp[1]) & 0xfffffffe) > 2 && tmp[1] != 0)
			operator_delete((void*)tmp[1]);

		void* text = str[0] != str[1] ? (void*)str[0] : (void*)&DAT_013f6254;
		(*(void (__thiscall*)(void*, void*))(*(int*)stream))((void*)stream, text);

		for (int node = map[2]; node != (int)map + 4; node = (int)RBTreeIncrement((void*)node))
		{
			if (ok != 0)
			{
				int r = FUN_00ae5530((void*)stream, 0, (void*)(node + 0x14), (void*)DAT_0145ba48);
				ok = (byte)(r != 0);
			}
			else
			{
				ok = 0;
			}
		}

		void* text2 = str[0] != str[1] ? (void*)str[0] : (void*)&DAT_013f6254;
		(*(void (__thiscall*)(void*, void*))(*(int*)stream + 4))((void*)stream, text2);
		if (((str[1] - str[0]) & 0xfffffffe) > 2 && str[0] != 0)
			operator_delete((void*)str[0]);
	}
	return ok;
}

// ---------------------------------------------------------------------------
// load the star-record map from the stream (keyed by object id)
// @ 0x00bf3f80
void __cdecl FUN_00bf3f80(int* stream, int* map)
{
	((Eng*)map)->Eb6280((void*)map[3]);

	int* anchor = (int*)((char*)map + 4);
	*anchor = (int)anchor;
	map[2] = (int)anchor;
	map[3] = 0;
	*(char*)((char*)map + 0x10) = 0;
	map[5] = 0;

	int count = 0;
	int* w = (int*)((T0)(*(int*)(*stream + 0x20)))((void*)stream);
	int s = ((T0)(*(int*)(*w + 0x18)))((void*)w);
	ReadInt32((void*)s, &count, 1, 0);

	for (uint i = 0; i < (uint)count; i++)
	{
		int key = 0;
		float value = 0.0f;
		int obj = 0;

		(*(void (__thiscall*)(void*, int, int*, int))(*(int*)(*stream + 0x28)))(
		    (void*)stream, (int)0xee9b2232, &key, 0);
		((T0)(*(int*)(*stream + 0x1c)))((void*)stream);

		int* w2 = (int*)((T0)(*(int*)(*stream + 0x20)))((void*)stream);
		int s2 = ((T0)(*(int*)(*w2 + 0x18)))((void*)w2);
		ReadInt32((void*)s2, &value, 1, 0);
		((T0)(*(int*)(*stream + 0x1c)))((void*)stream);

		if (obj != 0)
			(*(T0*)(*(int*)obj))((void*)obj);

		int slot = ((Eng*)map)->Bf2e70(&key, &value, 0);
		if (obj != 0)
			(*(T0*)(*(int*)obj + 4))((void*)obj);

		*(float*)(slot + 0x14) = value;

		if (obj != 0)
			(*(T0*)(*(int*)obj + 4))((void*)obj);
	}

	((T0)(*(int*)(*stream + 0x1c)))((void*)stream);
}
