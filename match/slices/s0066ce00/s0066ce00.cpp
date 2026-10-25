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

// ===========================================================================
// Reconstructed types for 0x0066ce00 (cSPUILargeAssetView::Show, secondary
// this at primary+0xc) and 0x0066d280 (UpdateDescription, primary this).
// ===========================================================================
struct RectF { float x1, y1, x2, y2; };

struct IProperty
{
	virtual int AddRef();                      // +0x00
	virtual int Release();                     // +0x04
};

// SP::IPropertyManager (retail vtable; GetProperty sits at +0x2c).
struct IPropertyManager
{
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28();
	virtual bool GetProperty(uint32_t item, uint32_t propID, IProperty** out); // +0x2c
};

struct ICastable
{
	virtual int AddRef();            // +0x00
	virtual int Release();           // +0x04
	virtual void v08();              // +0x08
	virtual void* Cast(uint32_t type); // +0x0c
};

struct IVecU32
{
	uint32_t* mpBegin;
	uint32_t* mpEnd;
	uint32_t* mpCap;
};

// UTFWin::IWindow (retail vtable; only the slots used here are named).
struct IWindow
{
	virtual int AddRef();                        // +0x00
	virtual int Release();                       // +0x04
	virtual void v08();                          // +0x08
	virtual void* Cast(uint32_t type);           // +0x0c
	virtual IWindow* GetParent();                // +0x10
	virtual void v14(); virtual void v18(); virtual void v1c(); virtual void v20();
	virtual void v24(); virtual void v28(); virtual void v2c(); virtual void v30();
	virtual void v34(); virtual void v38(); virtual void v3c(); virtual void v40();
	virtual void v44(); virtual void v48(); virtual void v4c(); virtual void v50();
	virtual void v54(); virtual void v58(); virtual void v5c();
	virtual void SetArea(const RectF& area);     // +0x60
	virtual void v64(); virtual void v68(); virtual void v6c(); virtual void v70();
	virtual void v74(); virtual void v78();
	virtual void SetFlag(int flag, bool value);  // +0x7c
};

// Sporepedia::IAssetData: vtable per ModAPI AssetData.h, key at +4, the
// ref-count/cast sub-object at +0x10.
struct IAssetData
{
	virtual void v00();                                 // +0x00
	virtual void v04();                                 // +0x04
	virtual void v08();                                 // +0x08
	virtual const wchar_t* GetName();                   // +0x0c
	virtual const wchar_t* GetAuthorName();             // +0x10
	virtual const wchar_t* GetDescription();            // +0x14
	virtual void GetImageKey();                         // +0x18
	virtual void GetBackgroundImageKey();               // +0x1c
	virtual void GetTags();                             // +0x20
	virtual uint32_t GetAssetSubtype();                 // +0x24
	virtual int64_t GetTimeCreated();                   // +0x28
	virtual bool HasName();                             // +0x2c
	virtual int v30();                                  // +0x30
	virtual int v34();                                  // +0x34
	virtual int v38();                                  // +0x38
	virtual float v3c();                                // +0x3c
	virtual const ResKey* GetKey();                     // +0x40
	virtual void AsyncSetKey(const ResKey& key);        // +0x44
	virtual bool v48();                                 // +0x48
	virtual void v4c();                                 // +0x4c
	virtual void LoadData();                            // +0x50
	virtual int64_t GetAuthorID();                      // +0x54
	virtual bool v58();                                 // +0x58
	virtual bool v5c();                                 // +0x5c
	virtual bool IsEditable();                          // +0x60
	virtual bool v64();                                 // +0x64
	virtual bool IsShareable();                         // +0x68
	virtual bool v6c();                                 // +0x6c
	virtual bool IsShared();                            // +0x70
	virtual bool IsPlayable();                          // +0x74
	virtual bool IsViewableLarge();                     // +0x78
	virtual bool v7c();                                 // +0x7c
	virtual bool v80();                                 // +0x80
	virtual bool v84();                                 // +0x84
	virtual int  v88();                                 // +0x88
	virtual bool GetConsequenceTraits(IVecU32& dst);    // +0x8c
	virtual bool GetAssetID(uint64_t& dst);             // +0x90

	ResKey    mKey;      // +0x04
	ICastable mObject;   // +0x10

	int AddRef() { return mObject.AddRef(); }
	int Release() { return mObject.Release(); }
	void* Cast(uint32_t type) { return mObject.Cast(type); }
};

struct cSPAssetData : IAssetData
{
	bool IsLocalAsset();                       // 0x006418e0
};

struct ResourceObject
{
	virtual int AddRef();                      // +0x00
	virtual int Release();                     // +0x04
	virtual void v08();                        // +0x08
	virtual void* Cast(uint32_t type);         // +0x0c
};

struct IResourceManager
{
	virtual void v00(); virtual void v04(); virtual void v08();
	virtual bool GetResource(const ResKey& key, ResourceObject** ppOut,
	                         int a, int b, int c, int d);   // +0x0c
};
IResourceManager* __cdecl EA_ResourceMan_GetManager();          // 0x0067dcd0

struct cAssetMetadata
{
	virtual int AddRef();                      // +0x00
	virtual int Release();                     // +0x04
};

struct IModelWorld
{
	virtual int AddRef();                      // +0x00
	virtual int Release();                     // +0x04
};

struct IModelManager
{
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual IModelWorld* GetMainWorld();       // +0x20
};
IModelManager* __cdecl SP_ModelManager();                       // 0x0067dd80

struct IMessageListener
{
	virtual bool HandleMessage(uint32_t id, void* data);   // +0x00
	virtual int AddRef();                                  // +0x04
	virtual int Release();                                 // +0x08
};

struct ISPUILargeAssetView
{
	virtual int AddRef();                      // +0x00
	virtual int Release();                     // +0x04
	virtual void* Dispose();                   // +0x08
	virtual void* AsInterface(uint32_t id);    // +0x0c
	virtual int GetPriority();                 // +0x10
	virtual uint32_t GetEventMask();           // +0x14
	virtual bool func18(int a, IWindow* win);  // +0x18
	virtual void LoadAssetViewLarge();         // +0x1c
};

struct IMessageServer
{
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20();
	virtual void AddListener(IMessageListener* listener, uint32_t msgID);  // +0x24
};
IMessageServer* __cdecl SP_MessageServer();                     // 0x0067dcc0

struct IConfigManager
{
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual int GetValue(uint32_t id);                          // +0x30
};
IConfigManager* __cdecl SP_ConfigManager();                    // 0x0067dd30

struct IAuthManager
{
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20();
	virtual bool IsOffline();                                   // +0x24
};
IAuthManager* __cdecl SP_AuthManager();                        // 0x00607a60

struct IWindowManager
{
	virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
	virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
	virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
	virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
	virtual void v40(); virtual void v44(); virtual void v48();
	virtual void SetFocus(int a, IWindow* w);                   // +0x4c
};
IWindowManager* __cdecl SP_WindowManager();                    // 0x0067caa0

struct cDirectValues
{
	uint32_t pad[0x118 / 4];
	int mOfflineMode;                                           // +0x118
};
struct cDirectPropertyList
{
	uint32_t pad[0x3c / 4];
	cDirectValues* mpValues;                                    // +0x3c
};
extern cDirectPropertyList* gAppProperties;                    // 0x015fd918

struct cSPUILayout
{
	IWindow* FindWindowByID(uint32_t id, bool recursive);       // 0x008105b0
};

struct cSPUIAssetComments
{
	virtual int AddRef();                                       // +0x00
	virtual int Release();                                      // +0x04
	void SetVisibility(int visible);                            // 0x0064e400
	bool LoadAssetComments(uint64_t id);                        // 0x0064e460
};

struct cSPUIMissingExpansionPackPage
{
	virtual int AddRef();                                       // +0x00
	virtual int Release();                                      // +0x04
	void SetVisibility(int visible);                            // 0x006717e0
	bool ShowMissingExpansionPacks(const ResKey* key);          // 0x00671840
};

struct ShowParams
{
	uint32_t pItem;      // +0x00
	bool b4;             // +0x04
	bool b5;             // +0x05
	bool b6;             // +0x06
	char pad7;           // +0x07
	uint32_t field8;     // +0x08
	bool bc;             // +0x0c
	char padD[3];        // +0x0d
	ShowParams();                                               // 0x006563c0
};

struct cSPUIAssetVerbs
{
	void Update(int one, ShowParams* params, IAssetData* asset);  // 0x006571e0
};

struct MessageListenerData
{
	IMessageServer* mpMessageManager;   // +0x00
	IMessageListener* mpMessageListener;// +0x04
	const uint32_t* mpMessageIDs;       // +0x08
	uint32_t mNumMessageIDs;            // +0x0c
	int field_10;                       // +0x10
};

// EA::AutoRefCount<T>
template <class T> struct AutoRefCount
{
	T* mpObject;
	AutoRefCount() : mpObject(0) {}
	~AutoRefCount() { if (mpObject) mpObject->Release(); }
	AutoRefCount& operator=(T* p)
	{
		if (p != mpObject) {
			T* old = mpObject;
			if (p) p->AddRef();
			mpObject = p;
			if (old) old->Release();
		}
		return *this;
	}
	void Reset()
	{
		if (mpObject) {
			T* old = mpObject;
			mpObject = 0;
			old->Release();
		}
	}
	T** AsPPTypeParam()
	{
		if (mpObject) {
			T* old = mpObject;
			mpObject = 0;
			old->Release();
		}
		return &mpObject;
	}
	T* operator->() const { return mpObject; }
	operator T*() const { return mpObject; }
};

// Instances whose assignment is emitted out of line.
template <class T> struct AutoRefCountOOL
{
	T* mpObject;
	AutoRefCountOOL() : mpObject(0) {}
	~AutoRefCountOOL() { if (mpObject) mpObject->Release(); }
	AutoRefCountOOL& operator=(T* p);                           // 0x00b5f950
	void Reset()
	{
		if (mpObject) {
			T* old = mpObject;
			mpObject = 0;
			old->Release();
		}
	}
	T* operator->() const { return mpObject; }
	operator T*() const { return mpObject; }
};

// The full primary object (UpdateDescription receives this).
struct cSPUILargeAssetView : ISPUILargeAssetView, IMessageListener
{
	uint32_t pad08[(0x18 - 0x08) / 4];
	cSPUILayout* mLayout;                                   // +0x18
	uint32_t pad1c[(0x5c - 0x1c) / 4];
	IWindow* mWin5c;                                        // +0x5c
	uint32_t pad60[(0x74 - 0x60) / 4];
	AutoRefCount<IAssetData> mAssetData;                    // +0x74

	void UpdateDescription();                               // 0x0066d280
};

// The secondary sub-object that receives Show's `this` (primary + 0x0c).
struct AssetViewShow
{
	uint32_t pad00[(0x10 - 0x00) / 4];
	AutoRefCount<IWindow> mWinParent;                       // +0x10
	AutoRefCount<IWindow> mWinRoot;                         // +0x14
	AutoRefCount<IWindow> mWinBakingArea;                   // +0x18
	AutoRefCount<IWindow> mWin28;                           // +0x1c
	uint32_t pad20[(0x2c - 0x20) / 4];
	AutoRefCount<IWindow> mWinAuthor;                       // +0x2c
	uint32_t pad30[(0x54 - 0x30) / 4];
	AutoRefCountOOL<cSPUIAssetComments> mComments;          // +0x54
	AutoRefCountOOL<cSPUIMissingExpansionPackPage> mExpansionPage; // +0x58
	uint32_t pad5c[(0x64 - 0x5c) / 4];
	cSPUIAssetVerbs* mAssetVerbs;                           // +0x64
	AutoRefCount<IAssetData> mAssetData;                    // +0x68
	AutoRefCountOOL<cAssetMetadata> mMetadata;              // +0x6c
	uint32_t pad70[(0x7c - 0x70) / 4];
	AutoRefCount<IModelWorld> mModelWorld;                  // +0x7c
	uint32_t pad80[(0x8c - 0x80) / 4];
	RectF mBakingArea;                                      // +0x8c
	char pad9c;
	bool mIsPlayable;                                       // +0x9d
	bool mBusy;                                             // +0x9e
	bool mHasResource;                                      // +0x9f
	bool mIsEditable;                                       // +0xa0
	char padA1[0xaf - 0xa1];
	MessageListenerData mReg;                               // +0xb0

	cSPUILargeAssetView* GetPrimary() const { return (cSPUILargeAssetView*)((char*)this - 0x0c); }
	bool Show(IWindow* parent, IAssetData* asset, uint32_t item, bool b5, bool bc);
};

extern const uint32_t kAssetViewMessages[4];                    // 0x014007e4

// @ 0x0066ce00
bool AssetViewShow::Show(IWindow* parent, IAssetData* asset, uint32_t item, bool b5, bool bc)
{
	mBusy = true;
	mAssetData = asset;
	mWinParent = parent;
	mMetadata.Reset();

	cSPAssetData* pData = mAssetData ? (cSPAssetData*)mAssetData->Cast(0x13d55dc8) : 0;
	if (pData) {
		mIsPlayable = pData->IsPlayable();
		mHasResource = pData->IsViewableLarge();
		mIsEditable = pData->IsEditable();
		if (!pData->IsLocalAsset()) {
			const ResKey* key = mAssetData->GetKey();
			AutoRefCount<ResourceObject> res;
			IResourceManager* mgr = EA_ResourceMan_GetManager();
			ResourceObject** pp = res.AsPPTypeParam();
			uint32_t kg = key->group;
			uint32_t ki = key->instance;
			ResKey k;
			k.group = kg;
			k.instance = ki;
			k.type = 0x30bdee3;
			if (mgr->GetResource(k, pp, 0, 0, 0, 0)) {
				cAssetMetadata* md = res ? (cAssetMetadata*)res->Cast(0x30bdee3) : 0;
				mMetadata = md;
			}
		}
	}

	mModelWorld = SP_ModelManager()->GetMainWorld();
	GetPrimary()->LoadAssetViewLarge();

	IMessageListener* listener = (IMessageListener*)(cSPUILargeAssetView*)((char*)this - 0x0c);
	IMessageServer* ms = SP_MessageServer();
	mReg.mpMessageManager = ms;
	mReg.mpMessageListener = listener;
	mReg.mpMessageIDs = kAssetViewMessages;
	mReg.mNumMessageIDs = 4;
	mReg.field_10 = 0;
	if (ms && listener) {
		for (uint32_t i = 0; i < 0x10; i += 4)
			ms->AddListener(listener, *(const uint32_t*)((const char*)kAssetViewMessages + i));
	}

	if (pData) {
		uint64_t assetID;
		if (mComments) {
			if (pData->GetAssetID(assetID) && !pData->IsLocalAsset()) {
				mComments->SetVisibility(1);
				mComments->LoadAssetComments(assetID);
			} else {
				mComments->SetVisibility(0);
			}
		}
		if (mExpansionPage && asset) {
			if (mHasResource) {
				mExpansionPage->SetVisibility(0);
			} else {
				mExpansionPage->SetVisibility(1);
				mExpansionPage->ShowMissingExpansionPacks(pData->GetKey());
			}
		}
		if (mWinBakingArea && mWin28) {
			if (pData->IsLocalAsset()) {
				RectF r = { 0.0f, 0.0f, 0.0f, 0.0f };
				mWinBakingArea->SetArea(r);
				mWin28->SetFlag(1, false);
			} else {
				mWinBakingArea->SetArea(mBakingArea);
				mWin28->SetFlag(1, true);
			}
		}
	} else {
		if (mComments && mExpansionPage && mWinBakingArea && mWin28) {
			mComments->SetVisibility(0);
			mExpansionPage->SetVisibility(0);
			RectF r = { 0.0f, 0.0f, 0.0f, 0.0f };
			mWinBakingArea->SetArea(r);
			mWin28->SetFlag(1, false);
		}
	}

	if (mAssetVerbs) {
		ShowParams p;
		p.pItem = item;
		p.b5 = b5;
		p.b4 = false;
		p.b6 = true;
		p.bc = bc;
		mAssetVerbs->Update(1, &p, mAssetData);
	}

	if (mWinParent)
		mWinParent->SetFlag(1, true);

	if (mWinAuthor) {
		bool isLocal = pData && pData->IsLocalAsset();
		bool hasAuthor = pData && pData->GetAuthorID() != 0;
		bool configValue = SP_ConfigManager()->GetValue(0x5de7b4a) != 0;
		bool authOffline = SP_AuthManager()->IsOffline();
		bool enable = !configValue && !authOffline
		           && !isLocal && hasAuthor
		           && !gAppProperties->mpValues->mOfflineMode;
		mWinAuthor->SetFlag(2, enable);
		mWinAuthor->SetFlag(0x10, !enable);
	}

	SP_WindowManager()->SetFocus(0, mWinRoot);
	return true;
}

// @ 0x0066d280
void cSPUILargeAssetView::UpdateDescription()
{
	bool any = false;
	if (mAssetData) {
		IVecU32 traits = { 0, 0, 0 };
		if (mAssetData->GetConsequenceTraits(traits)) {
			int count = (int)(traits.mpEnd - traits.mpBegin);
			if (count > 0) {
				uint32_t byteOffset = 0;
				uint32_t id = 0xb4daee50;
				do {
					IWindow* w1 = mLayout->FindWindowByID(id - 0x10, true);
					IWindow* w2 = mLayout->FindWindowByID(id, true);
					if (w1 && w2) {
						if (*(const uint32_t*)((const char*)traits.mpBegin + byteOffset) == 0) {
							w2->SetFlag(1, false);
							w1->SetFlag(1, false);
						} else {
							any = true;
							w2->SetFlag(1, true);
							w1->SetFlag(1, true);
							AutoRefCount<IProperty> p;
							ResKey key = { 0, 0, 0 };
							IPropertyManager* mgr = (IPropertyManager*)SP_PropertyManager();
							if (mgr->GetProperty(*(const uint32_t*)((const char*)traits.mpBegin + byteOffset),
							                     0xf865c777, p.AsPPTypeParam())) {
								if (SP_GetPropertyAsKey(p, 0x54d95162, &key))
									SPUIHelpers_SetWindowImage(w2, &key, -1);
							}
						}
					}
					byteOffset += 4;
					++id;
				} while (--count);
			}
		}
		if (traits.mpBegin && ((uint32_t*)traits.mpBegin)[-1])
			EASTL_allocator_deallocate(traits.mpBegin);
	}
	if (mWin5c)
		mWin5c->SetFlag(1, any);
}
