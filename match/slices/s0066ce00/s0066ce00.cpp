// Slice s0066ce00: UI panel message handler (0x0066d430) plus outline placeholders for the neighbouring refreshers.
// Flags: /O2 /MD /Gy /TP.
#include "types.h"

typedef void  (__thiscall *FnVoid)(void*);
typedef void  (__thiscall *FnVoidI)(void*, int);
typedef void* (__thiscall *FnPtrV)(void*);
#define VT(p) (*(void***)(p))

void* __cdecl SP_PropertyManager();               // 0x0067de30
void* __cdecl SP_GetPropertyAsKey(void* p, unsigned key, void* out); // 0x006a1250
void  __cdecl SPUIHelpers_SetWindowImage(void* w, void* key, int a); // 0x00807bb0
void  __cdecl EASTL_allocator_deallocate(void* p); // 0x00f47380
void* __cdecl cSPUILayout_FindWindow(void* self, unsigned id, int flag);

// ---- types used by the message handler at 0x0066d430 ----
struct ResKey { uint32_t instance, type, group; };

// UTFWin-style window (retail vtable); only GetControlID (+0x1c) is called here.
struct MsgWindow
{
	virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3();
	virtual void w4(); virtual void w5(); virtual void w6();
	virtual uint32_t GetControlID() const;   // +0x1c
};

struct Message
{
	MsgWindow* source;   // +0x00
	int field04;         // +0x04
	uint32_t eventType;  // +0x08
	int field0C;         // +0x0c (kMsgComponentActivated: command/event id)
	int field10;         // +0x10 (key code for key messages)
};

struct cPropertyList
{
	bool GetDescription(uint32_t id) const;   // 0x006A25A0 (returns "has property id")
};
extern cPropertyList* sAppProperties;         // 0x015FD918

// resource-key "axis" helpers (4 state axes + reset), all cdecl on a ResKey
int      __cdecl KeyGetAxis(ResKey* key, uint32_t axis);                  // 0x00556140
void     __cdecl KeyResetAxis(ResKey* key, uint32_t axis);                // 0x005562A0
void     __cdecl KeySetValue(ResKey* key, uint32_t value);                // 0x00555F70
uint32_t __cdecl KeyCombine(int a, int b, int c, int d);                  // 0x00556440
bool     __cdecl IsLinkedActive(void* obj);                               // 0x008050B0

struct MsgServer
{
	virtual void m0(); virtual void m1(); virtual void m2(); virtual void m3(); virtual void m4();
	virtual void Send(uint32_t id, void* data, int z);   // +0x14
};
MsgServer* __cdecl GetMessageServer();                    // 0x0067DCC0

struct WinMgrSink
{
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void Apply(void* v);                          // +0x10
};
struct WinMgrObj
{
	virtual void p0(); virtual void p1(); virtual void p2(); virtual void p3(); virtual void p4(); virtual void p5();
	virtual void p6(); virtual void p7(); virtual void p8(); virtual void p9(); virtual void pA(); virtual void pB();
	virtual void pC();
	virtual void Apply34(void* v);                        // +0x34
};
struct WinMgr
{
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void Apply10(void* v);                        // +0x10
};
WinMgr* __cdecl GetWindowManager();                       // 0x0067CAA0 (SP::WindowManager)

struct Singleton67de40
{
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual WinMgrObj* GetTarget();                       // +0x20
};
Singleton67de40* __cdecl GetSingleton67de40();            // 0x0067DE40

struct PtrVec
{
	void** mBegin; void** mEnd; void** mCap;
	uint32_t mAllocator[2];   // eastl allocator state (untouched by the ctor)
	PtrVec() : mBegin(0), mEnd(0), mCap(0) {}
	~PtrVec();                                            // 0x007A41A0
};

struct SpaceInv
{
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void v8();                                    // +0x20
	void SetItem(void* item);                             // 0x00599BE0 (TraitSuperPowerRollover wrapper)
	void SetActive();                                     // 0x00599530
	void SetInactive();                                   // 0x00599560
	void* GetRootWindow();                                // 0x00828100
};
void __cdecl SetWindowParent(void* w, void* root, int flag);   // 0x00808B20
void __cdecl CalloutMessageBox(void* where, const void* what); // 0x00809DB0
extern const char kCalloutText[];                               // 0x01527F2C

struct TextZoomName
{
	void Activate(int a);     // 0x00834A00
	void Deactivate(int a);   // 0x00834C60
};

struct FlagsObj   // flags at +4
{
	uint32_t pad;
	uint32_t flags;
	bool Test(int bit) const { return ((flags >> bit) & 1) != 0; }
	void Set(int bit) { flags |= (1u << bit); }
	void Clear(int bit) { flags &= ~(1u << bit); }
};

struct DoorObj   // object at this+0x70
{
	void Poke(int a, int b, int c);   // 0x006571E0 (thiscall, ret 0xc)
};

struct KeyPanel;   // the 0x66d430 owner

struct ObjHolder3c   // objects at this+0x3c / +0x40 (vtable +0x10 is used with 0 or 3 stack args)
{
	virtual void a0(); virtual void a1(); virtual void a2(); virtual void a3();
	virtual int Slot4();   // +0x10
};

struct MetaObj
{
	__int64 GetAssetKey() const;   // 0x005508A0
};

struct ItemSource    // object at this+0x74
{
	virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3();
	virtual void* Slot4(int a);   // +0x10
};

struct ChildPanel    // object at this+0x7c: window-ish with HandleMessage at +0x18, +0x34 getter, +0x118 flags object
{
	virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3();
	virtual void c4(); virtual void c5();
	virtual bool HandleMessage(void* window, Message* msg);   // +0x18
	virtual void c7(); virtual void c8(); virtual void c9(); virtual void cA(); virtual void cB();
	virtual void cC();
	virtual void* GetLinkable();                              // +0x34
	char pad[0x118 - 4];
	FlagsObj* mpFlags;   // +0x118
};

struct KeyPanel
{
	char       pad04[0x3c - 0];
	ObjHolder3c* mp3c;    // +0x3c
	ObjHolder3c* mp40;    // +0x40
	char       pad44[0x70 - 0x44];
	DoorObj*   mp70;      // +0x70
	void*      mp74;      // +0x74  (ItemSource-like, accessed through raw vtable slots)
	MetaObj*   mp78;      // +0x78
	ChildPanel* mp7c;     // +0x7c
	void*      mp80;
	SpaceInv*  mp84;      // +0x84
	char       pad88[0x90 - 0x88];
	TextZoomName* mp90;   // +0x90

	bool HandleMessage(void* window, Message* msg);
};

typedef ResKey*   (__thiscall *FnGetKey)(void*);
typedef bool      (__thiscall *FnFill)(void*, PtrVec*);
typedef int       (__thiscall *FnSlot4a)(void*);
typedef int       (__thiscall *FnSlot4b)(void*, void*, Message*, int);
typedef void*     (__thiscall *FnSlot4c)(void*, int);

// @ 0x0066d430
bool KeyPanel::HandleMessage(void* window, Message* msg)
{
	switch (msg->eventType)
	{
	case 9:
	{
		int src = msg->field04;
		ObjHolder3c* w = mp3c;
		if (w && src == w->Slot4())
		{
			ObjHolder3c* t = mp3c;
			GetWindowManager()->Apply10((void*)((FnSlot4b)VT(t)[4])(t, mp3c, msg, 0));
		}
		w = mp40;
		if (!w)
			return false;
		if (src != w->Slot4())
			return false;
		ObjHolder3c* t = mp40;
		GetWindowManager()->Apply10((void*)((FnSlot4b)VT(t)[4])(t, mp40, msg, 0));
		return false;
	}
	case 2:
	{
		ChildPanel* c = mp7c;
		if (!c)
			return false;
		if (!IsLinkedActive(c->GetLinkable()))
			return false;
		if (!mp7c->HandleMessage(window, msg))
			return false;
		return true;
	}
	case 1:
	{
		if (sAppProperties->GetDescription(0xb4daca6a) && mp74)
		{
			ResKey key = *((FnGetKey)VT(mp74)[0x40 / 4])(mp74);
			if (key.type == 0x2b978c46)
			{
				uint32_t axis;
				uint32_t nv;
				switch (msg->field10)
				{
				case 0x31:
					axis = 0xa426730b;
					switch (KeyGetAxis(&key, axis))
					{
					case 0xcfb01b93: nv = 0xa8ec6f99; goto doSet;
					case 0xa8ec6f99: nv = 0x5ece4770; goto doSet;
					case 0: nv = 0xcfb01b93; goto doSet;
					case 0x5ece4770:
					default:
						goto doReset;
					}
				case 0x32:
					axis = 0xad56080c;
					switch (KeyGetAxis(&key, axis))
					{
					case 0xfd159d91: nv = 0xb9de15f2; goto doSet;
					case 0: nv = 0x17e5ef84; goto doSet;
					case 0x17e5ef84: nv = 0xfd159d91; goto doSet;
					case 0xb9de15f2:
					default:
						goto doReset;
					}
				case 0x33:
					axis = 0xf71fa311;
					switch (KeyGetAxis(&key, axis))
					{
					case 0: nv = 0x0cac124d; goto doSet;
					case 0x0cac124d: nv = 0x60a78928; goto doSet;
					case 0x60a78928: nv = 0xc2ca9495; goto doSet;
					case 0xc2ca9495:
					default:
						goto doReset;
					}
				case 0x34:
					axis = 0xbeb528cb;
					switch (KeyGetAxis(&key, axis))
					{
					case 0x0a35d0f5: nv = 0x3360727f; goto doSet;
					case 0: nv = 0x0a35d0f5; goto doSet;
					case 0x3360727f: nv = 0x6aeb96a1; goto doSet;
					case 0x6aeb96a1:
					default:
						goto doReset;
					}
				case 0x35:
					KeyResetAxis(&key, 0xa426730b);
					KeyResetAxis(&key, 0xad56080c);
					KeyResetAxis(&key, 0xf71fa311);
					KeyResetAxis(&key, 0xbeb528cb);
					KeyResetAxis(&key, 0x2db6dad3);
					return false;
				default:
					goto tail;
				}
			doReset:
				KeyResetAxis(&key, axis);
				goto recompute;
			doSet:
				KeySetValue(&key, nv);
			recompute:
				{
					int a = KeyGetAxis(&key, 0xa426730b);
					int b = KeyGetAxis(&key, 0xad56080c);
					int c = KeyGetAxis(&key, 0xf71fa311);
					int d = KeyGetAxis(&key, 0xbeb528cb);
					KeySetValue(&key, KeyCombine(a, b, c, d));
				}
			}
		}
	tail:
		{
			ChildPanel* c = mp7c;
			if (c)
			{
				if (IsLinkedActive(c->GetLinkable()))
				{
					if (!mp7c->HandleMessage(window, msg))
						return false;
					return true;
				}
			}
		}
		return false;
	}
	case 0x1b:
	{
		MsgWindow* w = msg->source;
		if (!w)
			return false;
		uint32_t id = w->GetControlID();
		if (id == 0x53d6fe29)
		{
			if (!mp90)
				return false;
			mp90->Activate(0);
			return false;
		}
		if (id + 0x4b2511b0u > 4)
			return false;
		void* src74 = mp74;
		PtrVec items;
		if (src74 && ((FnFill)VT(src74)[0x8c / 4])(src74, &items))
		{
			void* item = items.mBegin[w->GetControlID() + 0x4b2511b0u];
			if (mp84 && item)
			{
				mp84->SetItem(item);
				mp84->v8();
				mp84->SetActive();
				SetWindowParent(w, mp84->GetRootWindow(), 1);
			}
		}
		return false;
	}
	case 0x287259f6:
	{
		switch (msg->field0C)
		{
		case 0x53d6fe2a:
		{
			if (!mp78)
				return false;
			__int64 k = mp78->GetAssetKey();
			GetMessageServer()->Send(0x6299932, &k, 0);
			return true;
		}
		case 0x06135298:
		{
			void* src74 = mp74;
			if (src74)
			{
				WinMgrObj* target = GetSingleton67de40()->GetTarget();
				void* v = ((FnSlot4c)VT(src74)[4])(src74, 0);
				target->Apply34(v);
			}
			CalloutMessageBox((char*)this + 8, kCalloutText);
			return true;
		}
		case 0x54acb9f1:
			mp70->Poke(0, 0, 0);
			return false;
		case 0x74d01473:
		{
			if (!mp7c)
				return false;
			FlagsObj* f = mp7c->mpFlags;
			if (!f)
				return false;
			if (!f->Test(2))
				f->Set(2);
			else
				f->Clear(2);
			f = mp7c->mpFlags;
			if (!f->Test(10))
			{
				f->Set(10);
				return false;
			}
			f->Clear(10);
			return false;
		}
		case 0x74174c59:
			GetMessageServer()->Send(0x14ac4938, 0, 0);
			return true;
		}
		return false;
	}
	case 0x1c:
	{
		MsgWindow* w = msg->source;
		if (!w)
			return false;
		uint32_t id = w->GetControlID();
		if (id == 0x53d6fe29)
		{
			if (mp90)
				mp90->Deactivate(0);
			return false;
		}
		if (id + 0x4b2511b0u > 4)
			return false;
		if (mp84)
			mp84->SetInactive();
		return false;
	}
	}
	return false;
}

// @ 0x0066ce00
void __fastcall FUN_0066ce00(void* self) { (void)self; }
// @ 0x0066d280
void __fastcall FUN_0066d280(void* self) { (void)self; }
