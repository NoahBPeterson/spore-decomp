// Slice s00f170c0: the "Simulator" UI screen (0x00f170c0, 0x00f17870, 0x00f17a70, 0x00f17b00, 0x00f17ea0).
// 00f17b00 boots the Simulator screen (property flags, palette, category, category UI, space inventory, effect,
// message handlers), 00f17a70 resizes the screen's item vector, 00f170c0 handles the progress panel's
// news/window messages, 00f17870 ends the animation of the progress panel and 00f17ea0 shuts the progress
// panel down.
// Flags: /O2 /MD /Gy /TP /vc71 /arch:SSE
#include "types.h"

#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV PV
#define PV4 PV2 PV2
#define PV8 PV4 PV4

typedef unsigned int uint;

extern "C" long __stdcall _InterlockedExchange(long volatile* target, long value);

void* __cdecl operator new(unsigned int size, const char* tag, int a, int b, int c, int d);   // 0x00f473a0
void  __cdecl operator delete(void* p);                                                       // 0x00f47380

// ----------------------------------------------------------------------------- UI stubs
struct IWin {
	virtual void AddRef();                                   // +0x00
	virtual void Release();                                  // +0x04
	PV2 PV2 PV                                               // +0x08..+0x18
	virtual int GetWindowType();                             // +0x1c
	PV2                                                      // +0x20..+0x24
	virtual bool IsVisible();                                // +0x28
	PV2 PV                                                   // +0x2c..+0x34
	virtual void GetRect(int id);                            // +0x38
	PV8 PV8                                                  // +0x3c..+0x78
	virtual void SetVisible(int a, bool b);                  // +0x7c
	PV8 PV8 PV8 PV8 PV2 PV                                   // +0x80..+0x108
	virtual int GetOwnerId(int a);                           // +0x10c
};

struct IWinContainer {
	virtual void AddRef();                                   // +0x00
	virtual void Release();                                  // +0x04
	PV2 PV2 PV                                               // +0x08..+0x18
	virtual int GetWindowType();                             // +0x1c
	PV2                                                      // +0x20..+0x24
	virtual bool IsVisible();                                // +0x28
	PV2 PV                                                   // +0x2c..+0x34
	virtual void GetRect(int id);                            // +0x38
	PV8 PV8                                                  // +0x3c..+0x78
	virtual void SetVisible(int a, bool b);                  // +0x7c
	PV8 PV8 PV8 PV4                                          // +0x80..+0xec
	virtual IWin* FindChildWindow(uint id, int a, int b);    // +0xf0
	PV2 PV2 PV                                               // +0xf4..+0x108
	virtual int GetOwnerId(int a);                           // +0x10c
};

struct LayoutObj {
	virtual void v0();                                       // +0x00
	virtual void v1();                                       // +0x04
	virtual void Release();                                  // +0x08
	void SetVisibility(int visible);                         // 0x00810590
	IWin* FindWindowByID(uint id, int recurse);              // 0x008105b0
	bool IsVisible();                                        // 0x00810070
	void Shutdown(uint flags);                               // 0x00811ad0
};

// Refcounted objects whose Release sits in the second vtable slot.
struct IObj20 {
	virtual void v0();                                       // +0x00
	virtual void Release();                                  // +0x04
	bool Teardown();                                         // 0x00f46a40
};
struct IObjB4 {
	virtual void v0();                                       // +0x00
	virtual void Release();                                  // +0x04
	void Teardown();                                         // 0x00f128f0
	void FUN_00f12970();                                     // 0x00f12970
};

// --------------------------------------------------------------------- messaging
struct IHandler { PV8 };

struct IServer {
	PV4 PV
	virtual void Send(uint32_t id, int a, int b);            // +0x14
	PV2 PV
	virtual void AddHandler(IHandler* h, uint32_t id);       // +0x24
};
IServer* MessageServer();                                    // 0x0067dcc0
namespace EA { namespace Messaging {
void RemoveHandler(IServer* server, IHandler* h, uint32_t id, int prio, int flags);   // 0x00571db0
} }

// --------------------------------------------------------------------- resource keys / properties
namespace EA { namespace ResourceMan {
struct Key { uint32_t mData[4]; };                           // resource key (passed by reference)
} }

struct Property;
struct PropertyList {
	virtual void v0();                                       // +0x00
	virtual void Release();                                  // +0x04
	PV4 PV2 PV
	virtual bool GetPropertyByKey(uint32_t name, Property** out);   // +0x24
	virtual Property* GetProperty(uint32_t name);            // +0x28
};
struct Property {
	uint32_t mValue;                                         // +0x00
	uint32_t pad04[3];                                       // +0x04
	uint8_t mFlags;                                          // +0x10
	uint8_t pad11;                                           // +0x11
	uint16_t mType;                                          // +0x12
	uint8_t* GetBool();                                      // 0x0041e920
};
bool GetEditorPropertyList(const EA::ResourceMan::Key& key, PropertyList** out);   // 0x005bf0e0
bool LoadCollectableItems(PropertyList* list, void** out);                         // 0x005bf1e0
void FUN_005970d0(int arg);                                                        // 0x005970d0
void* FUN_00556140(const EA::ResourceMan::Key* key, uint32_t name);                // 0x00556140
void* FUN_00556140(const EA::ResourceMan::Key* key, uint32_t name, void* parent);  // 0x00556140
void* FUN_00556440(void* node);                                                    // 0x00556440
void  FUN_00555e80(void* node, void* outVector);                                   // 0x00555e80
extern EA::ResourceMan::Key g_key15ad8a8;                    // 0x015ad8a8 palette key
extern uint32_t g_slot15ad8a4;                               // 0x015ad8a4 global slot
extern uint32_t g_handlerIds15ad8e4[2];                      // 0x015ad8e4 handler message ids

// --------------------------------------------------------------------- misc gameplay/UI objects
struct Updater {
	int ResetSlots();                                        // 0x00ae8ea0 (CommHost::ResetSlots)
};
Updater* GetUpdater();                                       // 0x00b3d490

struct GameTimeManager {
	void DecPauseGate(uint32_t gate);                        // 0x00b32250
};
GameTimeManager* GameTimeManager();                          // 0x00b3d380

struct IWinContent { virtual void v0(); };
struct WinOwnerBase { virtual void v0(); };
struct WinOwner : WinOwnerBase, IWinContent {                // IWinContent lives at +0x04
	void Set(bool on);                                       // 0x00812d60
};
struct IWindowManager {
	virtual void v0();                                       // +0x00
	virtual IWinContent* GetActiveContent();                 // +0x04
	PV8 PV8 PV2                                              // +0x08..+0x48
	virtual void ContentSet(int a, IWin* w);                 // +0x4c
};
IWindowManager* WindowManager();                             // 0x0067caa0
void SPUIHelpersEndModal(IWin* win, int a, int b);           // 0x00809c50

struct IGlobalSlots {
	virtual void v0();                                       // +0x00
	virtual void Set(void* slot, int value);                 // +0x04
};
IGlobalSlots* GlobalSlots();                                 // 0x0067ca90

// --------------------------------------------------------------------- message handling callees
struct IAudioSystem {
	virtual void v0();                                       // +0x00
	PV8 PV8 PV8 PV
	virtual int GetSomething();                              // +0x20
};
IAudioSystem* EAAudioGetSystemAT();                          // 0x00a206f0
void  KillSetiEffects(uint32_t id, uint32_t value);          // 0x00435ed0
uint32_t GetRecorderState();                                 // 0x00435e90
bool  FUN_00f0e250(void* win);                               // 0x00f0e250 (window visibility test)
void  FUN_00e12f80(void* win, int value);                    // 0x00e12f80 (SetVisible wrapper)
void  FUN_00e12fc0(void* win, void* value);                  // 0x00e12fc0 (SetText wrapper)
bool  FUN_00806a60(void* win, void* layout, int a, int b);   // 0x00806a60
void* FUN_00eec570();                                        // 0x00eec570
void  FUN_00f14120(void* out, const wchar_t* fmt, int a, void* b);  // 0x00f14120
extern char     g_16c7aa4[];                                 // 0x016c7aa4 globals struct
extern void*    g_16c7a28;                                   // 0x016c7a28

// SP::cString: the wide-string helper used to format "/" tachometers.
struct cString {
	uint32_t mPad00;                                         // +0x00
	uint32_t mPad04;                                         // +0x04
	uint32_t mText;                                          // +0x08 (inline text pointer)
	uint32_t mPad0c;                                         // +0x0c
	uint32_t mPad10;                                         // +0x10
	void ctor(uint32_t tag, uint32_t id, const wchar_t* s);  // 0x006b5770
	const wchar_t* GetText();                                // 0x006b55c0
	void dtor();                                             // 0x006b5240
};

// The palette category UI owning the animation sub-object.
struct PaletteHolder {
	bool IsVisible();                                        // 0x005c2940
	IWin* mpLayout;                                          // +0x18
};

// Refcounted interface whose Release sits in the third vtable slot (the panel sub-objects).
struct IObj3 {
	virtual void v0();                                       // +0x00
	virtual void AddRef();                                   // +0x04
	virtual void Release();                                  // +0x08
};

// Animation sub-object at +0x24 of the progress panel (its +0x04 is a refcounted interface).
struct SubA {
	uint32_t pad00;                                          // +0x00
	IObj3 mRef;                                              // +0x04 (Release at +0x08)
	uint32_t pad08[4];                                       // +0x08
	PaletteHolder* mpPalette;                                // +0x18
	uint32_t pad1c;                                          // +0x1c
	void* mpField20;                                         // +0x20
	void FUN_00f16fd0();                                     // 0x00f16fd0
	void FUN_00f126d0();                                     // 0x00f126d0
};

// Embedded list at +0x28 of the progress panel.
struct ListObj {
	void Reset();                                            // 0x00f14980
};

// Embedded object at +0x30 of the progress panel.
struct Obj30 {
	void Destroy();                                          // 0x00e0a5c0
};

// The icon list and the embedded object it is destroyed together with (+0x28 of the progress panel).
struct Pair28 {
	ListObj mList;                                           // +0x00
	uint32_t pad04;                                          // +0x04
	Obj30 mObj;                                              // +0x08
};

// Secondary interface at +0x04 of UI panels (AddRef at +4, Release at +8).
struct PanelIface {
	uint32_t pad00;                                          // +0x00
	IObj3 mRef;                                              // +0x04 (Release at +0x08)
	uint32_t pad08[(0x90 - 8) / 4];                          // +0x08
	int mMode;                                               // +0x90
};

// The effect installed on the screen: Stop at +0x0c, SetTarget at +0x104.
struct IUiEffect {
	virtual void AddRef();                                   // +0x00
	virtual void Release();                                  // +0x04
	virtual void v2();                                       // +0x08
	virtual void Stop(int a);                                // +0x0c
	PV8 PV8 PV8 PV8 PV8 PV8 PV8 PV4 PV
	virtual void SetTarget(void* target);                    // +0x104
};

struct PanelPrimary { virtual void v0(); };
struct PanelHandlerBase : IHandler {
	virtual bool HandleMessage(uint msg, void* payload);
};

// The progress panel (cSPUIProgress) two of the functions belong to.
class cSPUIProgress : public PanelPrimary, public PanelHandlerBase {
public:
	uint32_t pad08[2];                                       // +0x08
	PanelIface* mpWindow;                                    // +0x10
	void* mpScenario;                                        // +0x14
	LayoutObj* mpLayout;                                     // +0x18
	IUiEffect* mpEffect;                                     // +0x1c
	IObj20* mpField20;                                       // +0x20
	SubA* mpSubA;                                            // +0x24
	Pair28 mPair28;                                          // +0x28
	uint32_t pad34[(0xb4 - 0x34) / 4];                       // +0x34
	IObjB4* mpFieldB4;                                       // +0xb4
	PropertyList* mpPropList;                                // +0xb8
	float mTimer;                                            // +0xbc
	float mTimeC0;                                           // +0xc0
	uint32_t padC4;                                          // +0xc4
	float mTimeC8;                                           // +0xc8
	uint32_t padCc;                                          // +0xcc
	int mCountD0;                                            // +0xd0
	int mState;                                              // +0xd4
	int mState2;                                             // +0xd8
	IWinContainer* mpWinA;                                   // +0xdc
	IWinContainer* mpWinB;                                   // +0xe0
	IServer* mpServer;                                       // +0xe4
	IHandler* mpHandler;                                     // +0xe8
	uint32_t mMsg;                                           // +0xec
	int mPrio;                                               // +0xf0
	int mFlags;                                              // +0xf4

	void FUN_00f12eb0();                                     // 0x00f12eb0 page/category switch

	void StartNextAnimation();                               // 0x00f17870
	void Shutdown();                                         // 0x00f17ea0

	bool DoMessage(uint32_t msg, int* data);                 // 0x00f170c0
	bool FUN_00f135b0(int a);                                // 0x00f135b0
	void FUN_00f16580(int a);                                // 0x00f16580
};

// 0x40-byte "Simulator" UI message (vtable 0x013eb844, base vtable 0x013eb90c).
struct SimMessage {
	void* m_vtbl;                                            // +0x00
	long m_refCount;                                         // +0x04
	void* m_payload;                                         // +0x08
	uint32_t m_pad0c[9];                                     // +0x0c
	uint32_t m_field30;                                      // +0x30
	uint32_t m_pad34;                                        // +0x34
	uint32_t m_field38;                                      // +0x38
	uint32_t m_pad3c;                                        // +0x3c

	SimMessage* Construct()
	{
		m_field30 = 0;
		m_vtbl = (void*)0x013eb90c;                          // RefBaseA22 (base message)
		_InterlockedExchange(&m_refCount, 0);
		m_vtbl = (void*)0x013eb844;                          // concrete message vtable
		m_field38 = 0;
		return this;
	}
};

// 0x70-byte element of the screen's item vector.
struct Item70 {
	uint32_t m_pad00[0x1c];                                  // +0x00
	Item70* Init();                                          // 0x00e0a390
	void Destroy();                                          // 0x00e0a400
};

struct cItemVector {
	Item70* m_begin;                                         // +0x00
	Item70* m_end;                                           // +0x04

	void Resize(uint count);                                 // 0x00f17a70
	void Insert(Item70* where, int count, Item70* src);      // 0x00f16390
	void Erase(Item70* first, Item70* last);                 // 0x00f16330
};

// Refcounted item arrays whose AddRef/Release sit in the first two vtable slots.
struct ISimItems {
	virtual void AddRef();                                   // +0x00
	virtual void Release();                                  // +0x04
};

// cSPPaletteCategory: the vector of palette entries sits at +0x0c/+0x10.
struct cSPPaletteCategory {
	virtual void v0();                                       // +0x00
	virtual void v1();                                       // +0x04
	uint32_t pad08;                                          // +0x08
	int* m_begin;                                            // +0x0c
	int* m_end;                                              // +0x10
	uint32_t pad14[3];                                       // +0x14
	uint32_t mField20;                                       // +0x20
	uint32_t pad24[2];                                       // +0x24
	uint32_t mField2c;                                       // +0x2c
};

// The 0x40-byte palette (SP::cSPPalette), AddRef at +4 and Release at +8.
struct cSPPalette {
	virtual void v0();                                       // +0x00
	virtual void AddRef();                                   // +0x04
	virtual void Release();                                  // +0x08
	cSPPalette* Construct();                                 // 0x005c5e30
	bool Init(const EA::ResourceMan::Key& key, uint a, uint b, uint c, uint d, int e, int modelType);  // 0x005c6340
	cSPPaletteCategory* GetCategory(int index);              // 0x005c5de0
};

// The 0x34-byte category holder at +0x14 of the screen (AddRef +4, Release +8).
struct cCategoryHolder {
	virtual void v0();                                       // +0x00
	virtual void AddRef();                                   // +0x04
	virtual void Release();                                  // +0x08
	uint32_t pad0c;                                          // +0x0c
	ISimItems* mpItems;                                      // +0x10
	uint32_t pad14[3];                                       // +0x14
	uint32_t mField20;                                       // +0x20
	uint32_t pad24[2];                                       // +0x24
	uint32_t mField2c;                                       // +0x2c
	cCategoryHolder* Construct();                            // 0x005c64e0
};

// The 0xfc-byte palette category UI at +0x18 of the screen (AddRef +8, Release +0x0c).
struct cPaletteCategoryUI {
	virtual void v0();                                       // +0x00
	virtual void v1();                                       // +0x04
	virtual void AddRef();                                   // +0x08
	virtual void Release();                                  // +0x0c
	cPaletteCategoryUI* Construct();                         // 0x005c3e00
};

// The 0xb0-byte space inventory at +0x38 of the screen (AddRef +0, Release +4, virtual setup at +0x1c).
struct cSpaceInventory {
	virtual void AddRef();                                   // +0x00
	virtual void Release();                                  // +0x04
	PV4 PV
	virtual void Setup();                                    // +0x1c
	void Init(uint a, uint b);                               // 0x00827fa0
	cSpaceInventory* Construct();                            // 0x005994d0
};

// The Simulator screen (this of 0x00f17b00, owner of the item vector at +0x24).
class cSimScreen {
public:
	uint32_t pad00[3];                                       // +0x00
	uint32_t mParam0c;                                       // +0x0c
	cSPPalette* mpPalette;                                   // +0x10
	cCategoryHolder* mpCategory;                             // +0x14
	cPaletteCategoryUI* mpCategoryUI;                        // +0x18
	IUiEffect* mpEffect;                                     // +0x1c
	uint32_t pad20;                                          // +0x20
	cItemVector mItems;                                      // +0x24
	uint32_t pad2c[(0x38 - 0x2c) / 4];                       // +0x2c
	cSpaceInventory* mpInventory;                            // +0x38
	bool mShowCollectables;                                  // +0x3c
	uint8_t pad3d[3];                                        // +0x3d
	uint32_t mCollectableId;                                 // +0x40
	uint32_t pad44;                                          // +0x44
	IServer* mpServer;                                       // +0x48
	IHandler* mpHandler;                                     // +0x4c
	uint32_t mMsg[2];                                        // +0x50
	int mPrio;                                               // +0x54
	int mFlags;                                              // +0x58

	void FUN_00f12eb0();                                     // 0x00f12eb0 page/category switch
	bool Init(IUiEffect* effect, const EA::ResourceMan::Key& key);   // 0x00f17b00
};

// ----------------------------------------------------------------------------- 0x00f170c0
// The progress panel's message handler. The payload is the shared UI message ("W_s0080_68d0"):
// +0x00 source window, +0x08 news type, +0x0c control id, +0x10 the "reset" flag, +0x18 the owner id.
// News type 0x287259f6 carries a button/news event whose control id walks a small state machine
// (mState 0..10); news type 0x7e1a521 carries a window event whose window type walks the same machine,
// which swaps between the two container panels and fills the remaining-time tachometer with FUN_00f14120.
// @ 0x00f170c0
bool cSPUIProgress::DoMessage(uint32_t msg, int* data)
{
	bool ok = false;
	int news = data[2];

	if (news == 1) {
		if (data[4] != 0x1b)
			return false;
		if (mState != 0)
			return false;
		if (mpWinB != 0 && mpWinB->IsVisible()) {
			FUN_00e12f80(mpWinB, 0);
			mState = 9;
			return true;
		}
		if (!FUN_00f0e250(mpWinA))
			return true;
		FUN_00e12f80(mpWinA, 0);
		mpScenario = (void*)1;
		mState = 10;
		FUN_00f16580(1);
		return true;
	}

	if (news == 0x287259f6) {
		switch (data[3]) {
		case 0x7c79940:
		case 0x7c79948:
			if (mpWinA != 0)
				((IWin*)mpWinA)->SetVisible(1, false);
			mpScenario = (void*)((data[3] != 0x7c79948) + 1);
			mState = 10;
			FUN_00f16580(1);
			return true;

		case 0x7c79c50:
			{
				IAudioSystem* sysA = EAAudioGetSystemAT();
				KillSetiEffects(0x9ef448c0, sysA != 0 ? sysA->GetSomething() : 0);
			}
			if (mpWinA != 0)
				((IWin*)mpWinA)->SetVisible(1, false);
			mState = 9;
			return true;

		case 0x7c79c78:
			{
				IAudioSystem* sysB = EAAudioGetSystemAT();
				KillSetiEffects(0x9ef448c0, sysB != 0 ? sysB->GetSomething() : 0);
			}
			if (mpWinB != 0)
				((IWin*)mpWinB)->SetVisible(1, false);
			mState = 9;
			return true;

		case 0x7e20437:
			if (!FUN_00f135b0(0))
				return true;
			mpFieldB4->FUN_00f12970();
			return true;

		default:
			return false;
		}
	}

	if (news != 0x7e1a521)
		return false;

	IWin* win = (IWin*)data[0];
	if (win->GetOwnerId(0) != data[6])
		return false;
	bool notVis = !(win != 0 && win->IsVisible());
	bool visA = win != 0 && win->IsVisible();
	uint type = win->GetWindowType();

	switch (type) {
	case 0x774b418:
		if (!notVis)
			return false;
		if (mState == 10)
			mState2 = 3;
		return false;

	case 0x7c79d78:
		if (mState != 2)
			return true;
		if (!visA)
			return true;
		if (mTimer > 0.0f) {
			mState = 3;
			return true;
		}
		mState = 0;
		return true;

	case 0x7db8990:
		if (mState == 6 && visA) {
			FUN_00e12f80(mpLayout->FindWindowByID(0x7e09668, 1), 0);
			mState = 7;
			return true;
		}
		if (!notVis)
			return true;
		FUN_00e12f80(mpLayout->FindWindowByID(0x7e09668, 1), 1);
		return true;

	case 0x7e098d0:
		if (mState != 5)
			return true;
		if (!notVis)
			return true;
		FUN_00e12f80(mpLayout->FindWindowByID(0x7db8991, 1), 0);
		FUN_00e12f80(mpLayout->FindWindowByID(0x7db8990, 1), 1);
		mState = 6;
		KillSetiEffects(0x3c035721, GetRecorderState());
		{
			LayoutObj* layout = mpLayout;
			int arg = mCountD0 + 0x7d10de0;
			FUN_00806a60(layout->FindWindowByID(0x7c55300, 1), layout, arg, -1);
			*(uint32_t*)(*(char**)(g_16c7aa4 + 0x7c) + 0x20) = mCountD0;
			cString a;
			a.ctor(0x623d2fc0, 0x7ceb16a, 0);
			FUN_00e12fc0(mpLayout->FindWindowByID(0x7c79b20, 1), (void*)a.GetText());
			cString b;
			b.ctor(0x623d2fc0, 0x7ceb16b, 0);
			FUN_00e12fc0(mpLayout->FindWindowByID(0x7c79b21, 1), (void*)b.GetText());
			b.dtor();
			a.dtor();
		}
		return true;

	case 0x7e09668:
		if (mState != 7)
			return true;
		if (!notVis)
			return true;
		FUN_00e12f80(mpLayout->FindWindowByID(0x7db8990, 1), 0);
		FUN_00e12f80(mpLayout->FindWindowByID(0x7c66c00, 1), 1);
		{
			cString out;
			FUN_00f14120(&out, L"%d/%d", mCountD0, FUN_00eec570());
			FUN_00e12fc0(mpLayout->FindWindowByID(0x7c79af8, 1), (void*)out.mText);
			mpSubA->FUN_00f126d0();
			out.dtor();
		}
		mState = 8;
		return true;

	case 0x7e09670:
		if (!visA)
			return true;
		FUN_00e12f80(win, 0);
		return true;

	case 0x7eb2740:
		if (mState == 4 && visA) {
			FUN_00e12f80(mpLayout->FindWindowByID(0x7e098d0, 1), 0);
			mState = 5;
			return true;
		}
		if (!notVis)
			return true;
		FUN_00e12f80(mpLayout->FindWindowByID(0x7e098d0, 1), 1);
		return true;

	case 0x7c796d0:
	case 0x7c79820:
	case 0x7c79918:
		break;

	default:
		return false;
	}

	if (mState == 1 && visA) {
		IWin* w = mpWinA->FindChildWindow(0x7c79d78, 1, 1);
		FUN_00e12f80(w, 0);
		if (mpWindow->mMode == 5) {
			w = mpWinA->FindChildWindow(0x7e09670, 1, 1);
			FUN_00e12f80(w, 0);
		}
		if (mTimeC0 != mTimeC8) {
			mState = 2;
			return true;
		}
	} else if (mState == 10 && notVis) {
		if (mpScenario != (void*)1 || !FUN_00f135b0(1)) {
			mState2 = 3;
			return true;
		}
		mpFieldB4->FUN_00f12970();
		return true;
	} else {
		if (mState != 9)
			return true;
		if (!notVis)
			return true;
		IWin* w = (void*)data[0] == (void*)mpWinA ? (IWin*)mpWinB : (IWin*)mpWinA;
		FUN_00e12f80(w, 1);
		WindowManager()->ContentSet(0, w);
	}
	mState = 0;
	return true;
}

// ----------------------------------------------------------------------------- 0x00f17870
// Ends the animation of the progress panel: tells the message server whether the panel is still in the finishing
// state, drops the registered handler, hides and releases the windows, resets the effect, the sub-object, the
// icon list and the game-time pause gate, then re-posts the "Simulator" message when a scenario is loaded.
// @ 0x00f17870
void cSPUIProgress::StartNextAnimation()
{
	IServer* server = MessageServer();
	int finishing = mpWindow->mMode == 5 ? 1 : 0;
	server->Send(0x7e36045, finishing, 0);

	if (mpServer) {
		IServer* oldServer = mpServer;
		mpServer = 0;
		EA::Messaging::RemoveHandler(oldServer, mpHandler, mMsg, mPrio, mFlags);
	}

	mpLayout->SetVisibility(0);
	if (mpWinA)
		mpWinA->SetVisible(1, false);
	if (mpWinB)
		mpWinB->SetVisible(1, false);
	IWin* win = mpLayout->FindWindowByID(0x7c62860, 1);
	if (win)
		win->SetVisible(2, false);

	if (mpWinA) {
		IWinContainer* old = mpWinA;
		mpWinA = 0;
		old->Release();
	}
	if (mpWinB) {
		IWinContainer* old = mpWinB;
		mpWinB = 0;
		old->Release();
	}
	if (mpPropList) {
		PropertyList* old = mpPropList;
		mpPropList = 0;
		old->Release();
	}
	if (mpWindow) {
		PanelIface* old = mpWindow;
		mpWindow = 0;
		old->mRef.Release();
	}

	mTimer = 0.0f;
	mpSubA->FUN_00f16fd0();
	mPair28.mList.Reset();
	GetUpdater()->ResetSlots();
	GameTimeManager()->DecPauseGate(0x4bf38a7);

	if (mpEffect) {
		mpEffect->Stop(0);
		IUiEffect* fx = mpEffect;
		if (fx) {
			mpEffect = 0;
			fx->Release();
		}
	}

	WinOwner* owner = (WinOwner*)WindowManager()->GetActiveContent();
	owner->Set(false);

	win = mpLayout->FindWindowByID(0xffffffff, 1);
	SPUIHelpersEndModal(win, 0, 1);
	mState = 0;

	if (mpScenario) {
		SimMessage* msg = (SimMessage*)operator new(0x40, "Simulator", 0, 0, 0, 0);
		if (msg)
			msg = msg->Construct();
		msg->m_payload = mpScenario;
		MessageServer()->Send(0x70b18c7, (int)msg, 0);
	}
}

// ----------------------------------------------------------------------------- 0x00f17a70
// Resizes the screen's item vector to count elements: when it has to grow it inserts default-initialised items
// after the end, otherwise it erases everything from element count on.
// @ 0x00f17a70
void cItemVector::Resize(uint count)
{
	if (count > (uint)(int)(m_end - m_begin)) {
		Item70 tmp;
		Item70* created = tmp.Init();
		Insert(m_end, (int)count - (int)(m_end - m_begin), created);
		tmp.Destroy();
		return;
	}
	Erase(m_begin + count, m_end);
}

// ----------------------------------------------------------------------------- 0x00f17b00
// Boots the Simulator screen from its scenario resource: reads the collectable/category properties, builds the
// palette, the category holder and its UI, the space inventory and the item list, installs the effect and the
// message handler and returns success.
// @ 0x00f17b00
bool cSimScreen::Init(IUiEffect* effect, const EA::ResourceMan::Key& key)
{
	PropertyList* propList = 0;
	GetEditorPropertyList(key, &propList);
	void* items = 0;
	LoadCollectableItems(propList, &items);
	FUN_005970d0(0);

	mShowCollectables = false;
	if (propList) {
		Property* prop = 0;
		if (propList->GetPropertyByKey(0xc54c543b, &prop) && prop->mType == 1)
			mShowCollectables = *prop->GetBool() != 0;
	}

	mCollectableId = 0;
	if (mShowCollectables) {
		void* node = FUN_00556140(&key, 0x2db6dad3);
		if (node == 0) {
			void* a = FUN_00556140(&key, 0xbeb528cb);
			void* b = FUN_00556140(&key, 0xf71fa311, a);
			void* c = FUN_00556140(&key, 0xad56080c, b);
			void* d = FUN_00556140(&key, 0xa426730b, c);
			node = FUN_00556440(d);
		}
		void* found[3] = {0, 0, 0};
		FUN_00555e80(node, found);
		if (found[0] != found[1])
			mCollectableId = *(uint32_t*)found[0];
		if (found[0] && ((uint32_t*)found[0])[-1] != 0)
			operator delete(found[0]);
	}

	GlobalSlots()->Set(&g_slot15ad8a4, 0);

	cSPPalette* palette = 0;
	{
		cSPPalette* mem = (cSPPalette*)operator new(0x40, "Simulator", 0, 0, 0, 0);
		if (mem)
			palette = mem->Construct();
	}
	if (palette != mpPalette) {
		if (palette)
			palette->AddRef();
		cSPPalette* old = mpPalette;
		mpPalette = palette;
		if (old)
			old->Release();
	}

	cCategoryHolder* category = 0;
	{
		cCategoryHolder* mem = (cCategoryHolder*)operator new(0x34, "Simulator", 0, 0, 0, 0);
		if (mem)
			category = mem->Construct();
	}
	if (category != mpCategory) {
		if (category)
			category->AddRef();
		cCategoryHolder* old = mpCategory;
		mpCategory = category;
		if (old)
			old->Release();
	}

	cPaletteCategoryUI* categoryUI = 0;
	{
		cPaletteCategoryUI* mem = (cPaletteCategoryUI*)operator new(0xfc, "Simulator", 0, 0, 0, 0);
		if (mem)
			categoryUI = mem->Construct();
	}
	if (categoryUI != mpCategoryUI) {
		if (categoryUI)
			categoryUI->AddRef();
		cPaletteCategoryUI* old = mpCategoryUI;
		mpCategoryUI = categoryUI;
		if (old)
			old->Release();
	}

	mpPalette->Init(g_key15ad8a8, 0x4178b8e8, 0x41b6160a, 0, 0, 0, 0x7c3bd3e);

	ISimItems* oldItems = mpCategory->mpItems;
	if (items != oldItems) {
		if (items)
			((ISimItems*)items)->AddRef();
		mpCategory->mpItems = (ISimItems*)items;
		if (oldItems)
			oldItems->Release();
	}
	mpCategory->mField2c = 0x4178b8e8;                       // float 15.5
	mpCategory->mField20 = 0x2b978c46;                       // float 4.3125e-13

	cSPPaletteCategory* cat = mpPalette->GetCategory(0);
	int count = (int)((cat->m_end - cat->m_begin) / 4);
	mItems.Resize((uint)count);

	cSpaceInventory* inventory = 0;
	{
		cSpaceInventory* mem = (cSpaceInventory*)operator new(0xb0, "Simulator", 0, 0, 0, 0);
		if (mem)
			inventory = mem->Construct();
	}
	if (inventory != mpInventory) {
		if (inventory)
			inventory->AddRef();
		cSpaceInventory* old = mpInventory;
		mpInventory = inventory;
		if (old)
			old->Release();
	}
	mpInventory->Init(0x146f54c, 0x40464100);
	mpInventory->Setup();

	if (effect != mpEffect) {
		if (effect)
			effect->AddRef();
		IUiEffect* old = mpEffect;
		mpEffect = effect;
		if (old)
			old->Release();
	}
	mpEffect->SetTarget(&mParam0c);

	FUN_00f12eb0();

	IServer* server = MessageServer();
	mpServer = server;
	mpHandler = (IHandler*)this;
	mMsg[0] = 0x15ad8e4;
	mMsg[1] = 2;
	mPrio = 0;
	if (server) {
		for (int i = 0; i < 2; i++)
			server->AddHandler((IHandler*)this, g_handlerIds15ad8e4[i]);
	}

	if (items)
		((ISimItems*)items)->Release();
	if (propList)
		propList->Release();
	return true;
}

// ----------------------------------------------------------------------------- 0x00f17ea0
// Shuts the progress panel down: ends a running animation, drops the layout, the effect windows, the sub-object
// and the icon list.
// @ 0x00f17ea0
void cSPUIProgress::Shutdown()
{
	if (mpLayout && mpLayout->IsVisible())
		StartNextAnimation();

	if (mpLayout) {
		mpLayout->Shutdown(1);
		LayoutObj* old = mpLayout;
		if (old) {
			mpLayout = 0;
			old->Release();
		}
	}
	if (mpField20) {
		mpField20->Teardown();
		IObj20* old = mpField20;
		if (old) {
			mpField20 = 0;
			old->Release();
		}
	}
	if (mpFieldB4) {
		mpFieldB4->Teardown();
		IObjB4* old = mpFieldB4;
		if (old) {
			mpFieldB4 = 0;
			old->Release();
		}
	}
	if (mpSubA && mpSubA->mpPalette && mpSubA->mpPalette->IsVisible()) {
		mpSubA->FUN_00f16fd0();
		SubA* old = mpSubA;
		if (old) {
			mpSubA = 0;
			old->mRef.Release();
		}
	}
	Pair28* pair = &mPair28;
	pair->mList.Reset();
	pair->mObj.Destroy();
}
