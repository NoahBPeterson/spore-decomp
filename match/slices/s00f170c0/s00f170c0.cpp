// Slice s00f170c0: the "Simulator" UI screen (0x00f17870, 0x00f17a70, 0x00f17b00, 0x00f17ea0).
// 00f17b00 boots the Simulator screen (property flags, palette, category, category UI, space inventory, effect,
// message handlers), 00f17a70 resizes the screen's item vector, 00f17870 ends the animation of the progress
// panel and 00f17ea0 shuts the progress panel down.
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
	PV8 PV4
	virtual void GetRect(int id);                            // +0x38
	PV8 PV8
	virtual void SetVisible(int a, bool b);                  // +0x7c
};

struct IWinContainer {
	virtual void AddRef();                                   // +0x00
	virtual void Release();                                  // +0x04
	PV8 PV4 PV8 PV4 PV4 PV
	virtual void SetVisible(int a, bool b);                  // +0x7c
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
};
IWindowManager* WindowManager();                             // 0x0067caa0
void SPUIHelpersEndModal(IWin* win, int a, int b);           // 0x00809c50

struct IGlobalSlots {
	virtual void v0();                                       // +0x00
	virtual void Set(void* slot, int value);                 // +0x04
};
IGlobalSlots* GlobalSlots();                                 // 0x0067ca90

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
	uint32_t padC0[(0xd4 - 0xc0) / 4];                       // +0xc0
	int mState;                                              // +0xd4
	uint32_t padD8;                                          // +0xd8
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
