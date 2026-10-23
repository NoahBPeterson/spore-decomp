// Spore (SporeApp.exe) -- slice s00ec51a0: SP::cTestScript message/tick helpers.
//
//   0x00EC51A0  SP::cTestScript::DestroyMessage? -- removes the EA::Messaging handler and
//               resets the state machine (FUN_00ec4f70(this,1,0))
//   0x00EC51F0  tick / timeout pump
//   0x00EC5310  message filter (__thiscall, ret 8)
//   0x00EC5340  SP::cTestScript::HandleMessage  (PDB caller-scored candidate)
//   0x00EC56B0  message pipeline (__thiscall, ret 8)
//   0x00EC5990  Start / Begin
//   0x00EC5A60  asset request helper
//   0x00EC5B10  SP::RelationShipDebugDraw  (PDB caller-scored candidate)
//   0x00EC5C70  RelationShipDebugDraw helper
//   0x00EC5DE0  game-mode dispatch
//
// Names come from symbols/pdb_candidates.json (0x00ec5340 -> SP::cTestScript::HandleMessage,
// 0x00ec5b10 -> SP::RelationShipDebugDraw).
//
// Self-contained single TU: every type is modelled here so the compiler emits the same member
// offsets the original used.
#include "types.h"

#define NULL 0
typedef unsigned int uint;

// ---------------------------------------------------------------------------
// external helpers (defined elsewhere in the binary)
// ---------------------------------------------------------------------------
extern "C" __declspec(dllimport) int __cdecl sscanf(const char* buf, const char* fmt, ...);
extern "C" __declspec(dllimport) void __cdecl operator_delete__(void* p);
extern void eastl_vector_insert(void* dst, void* src, int n);   // 0x11e0744

// wstring-like helper used by the debug-draw helpers
struct WString;                                   // modelled below

// ---------------------------------------------------------------------------
// eastl / wstring element types used by RelationShipDebugDraw
// ---------------------------------------------------------------------------
extern wchar_t gEmptyString16a;                   // 0x01667bac  eastl::gEmptyString16[0]
extern wchar_t gEmptyString16b;                   // 0x01667bae

// A tiny eastl::basic_string<wchar_t>: { mpBegin, mpEnd, mpCapacity-1 } (3 pointers)
struct EaString
{
	wchar_t* mpBegin;      // +0x00
	wchar_t* mpEnd;        // +0x04
	wchar_t* mpCapacity;   // +0x08

	void push_back(wchar_t c);                       // 0x4f6510
	void append(const wchar_t* first, const wchar_t* last);   // 0x429580 (WStr::Append)
	void assign(const wchar_t* first, const wchar_t* last);   // 0x423650 (WString_Assign)
};

// 0x429580  WStr::Append
extern void WStr_Append(EaString* self, const wchar_t* first, const wchar_t* last);
// 0x423650  WString_Assign
extern void WString_Assign(EaString* self, const wchar_t* first, const wchar_t* last);
// 0x4f6510  eastl::basic_string<wchar_t>::push_back
extern void EaString_push_back(EaString* self, wchar_t c);
// 0x00eeea50  builds a string from a struct (key -> text)
extern void FUN_00eeea50(const void* key, EaString* out);

// ---------------------------------------------------------------------------
// EA::ResourceMan / EA::Messaging and the SP managers reached through the
// exported getters.
// ---------------------------------------------------------------------------
namespace EA { namespace ResourceMan {
	struct Manager
	{
		virtual void v0();                                   // +0x00
		virtual void v1();
		virtual void v2();
		virtual char v3();                                   // +0x0c
	};
	Manager* GetManager();                                   // 0x0067dcd0
}}

// SP::Pollen::AuthManager  (0x00607a60)
struct AuthManager
{
	virtual void v0();                                       // +0x00
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual char v9();                                       // +0x24
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14();
	virtual void v15();
	virtual void v16();
	virtual void v17();
	virtual void v18();
	virtual void v19();
	virtual void v20();
	virtual void v21();
	virtual char v22();                                      // +0x58
};
AuthManager* SP_AuthManager();                               // 0x00607a60

// 0x0067dd20 -- manager whose +0x28 virtual takes a message id
struct IdDispatcher
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10(int id);                                // +0x28
};
IdDispatcher* GetIdDispatcher();                             // 0x0067dd20

// 0x0067cb30 -- returns the Pollinator object (its +0x58 is the asset directory)
struct Pollinator
{
	char _pad[0x58];
};
Pollinator* FUN_0067cb30();                                  // 0x0067cb30

// The asset directory (EA::ResourceMan::Key based) reached via Pollinator+0x58
struct AssetDirectory_s
{
	char GetServerId(const void* key, unsigned long long* out, bool b) const;   // 0x54e530
};
// free form: dir = (char*)pollinator + 0x58
extern char FUN_0054e530(AssetDirectory_s* dir, const void* key, unsigned long long* out, bool b);  // 0x54e530
extern char FUN_0054e740(AssetDirectory_s* dir, unsigned int lo, unsigned int hi);       // 0x54e740
extern char FUN_0054ed50(AssetDirectory_s* dir, unsigned int lo, unsigned int hi, int c); // 0x54ed50
extern char FUN_0054e460(AssetDirectory_s* dir, unsigned int lo, unsigned int hi, void* out); // 0x54e460
#define POLL_ASSETDIR(poll) ((AssetDirectory_s*)((char*)(poll) + 0x58))

// 0x00610c20  PostGetAssetFeedEx(ptr, ptr)
extern char FUN_00610c20(void* self, void* p, void* q);
// 0x006108a0  FUN_006108a0(ecx=self, ptr, ptr)
extern void FUN_006108a0(void* self, void* a, void* b);

// AssetDirectory_s helper used for server-id lookups

// Free functions (this-call helpers of cTestScript, defined elsewhere).  In the
// original all of these are __thiscall members of the same object, so they are
// modelled as members of a data-less base class (layout is unchanged).
struct CScriptOps
{
	void OpReset(int a, int b);                   // 0x00ec4f70
	void Op4c80();                                // 0x00ec4c80
	void Op5100();                                // 0x00ec5100
	void Op4750();                                // 0x00ec4750
	char Op4330(void* p);                         // 0x00ec4330
	char Op4380(char a, char b, char c);          // 0x00ec4380
	void Op4e50(void* it);                        // 0x00ec4e50
};
extern void* FUN_00ec4430(void* first, void* last, const void* key);  // 0x00ec4430
struct Vec34 { void* mBegin; void* mEnd; };
extern char FUN_005962b0(Vec34* self);                        // 0x005962b0
struct cTestScript;

// cSPUILayout / UI / window helpers
struct cSPUILayout
{
	void* FindWindowByID(int id, int b);                     // 0x8105b0
};
extern void* cSPUILayout_FindWindowByID(void* layout, int id, int b);  // 0x8105b0
extern float SPUIHelpers_GetElapsedSeconds();                // 0x805080
extern void FUN_00808230(void* wnd, float* params);          // 0x808230
extern void UI_CalloutMessageBox(void* text, const void* loc); // 0x809db0
// cTestScript's mpInstance (+0x18) is an object with these thiscall helpers:
//   0x00f2b270  char  IsFlag(int mask)   (ecx = instance)
//   0x00f2b690  void  Collect(int mask, void* vec)
//   0x00f2b790  void  Reset()
struct TestInstance
{
	char IsFlag(int mask);                        // 0x00f2b270
	void Collect(int mask, void* vec);            // 0x00f2b690
	void Reset();                                 // 0x00f2b790
};
extern char FUN_00f2b270(void* self, int a);          // 0x00f2b270
extern void FUN_00f2b690(void* self, int a, void* b); // 0x00f2b690
extern void FUN_00f2b790(void* self);                 // 0x00f2b790

// 0x00ed8130
// 0x00ed8130  takes a 3-dword key struct by value
struct Key3 { int a; int b; int c; };
extern "C" void __stdcall FUN_00ed8130(Key3 key);

// The global app object (0x016c7aa4 holds the pointer)
struct SporeApp
{
	char  _pad00[0x14];      // +0x00
	void* mpCurrentGame;     // +0x14
	char  _pad18[0xcc - 0x18];
	int   mMode;             // +0xcc
};

// EA::Stopwatch (0x78 region of cTestScript)
struct Stopwatch
{
	unsigned long long mnStartTime;      // +0x00
	unsigned long long mnTotalElapsed;   // +0x08
	int   mnUnits;                       // +0x10
	float mfCoeff;                       // +0x14
	void Restart();                      // 0x00571e80
	unsigned long long GetElapsedTime() const;  // 0x0093a5e0
};

// EA::Messaging::RemoveHandler
extern void EA_Messaging_RemoveHandler(void* id, void* a, void* b, void* c, void* d);  // 0x571db0

// SP::GetCurrentGameMode
extern void* SP_GetCurrentGameMode();        // 0x00b5b800
extern void* gModeA;                          // 0x01654c10
extern void* gSporeApp;                       // 0x016c7aa4 (globals struct)
extern float gNegTwo;                         // 0x013ef61c  (constant -2.0f)
extern float gOne;                            // 0x01485720  (constant 1.0f)

// ---------------------------------------------------------------------------
// SP::cTestScript
// ---------------------------------------------------------------------------
struct cTestScript : CScriptOps
{
	char         _pad00[0x10];      // +0x00
	void*        mTestName0;        // +0x10  (localized-string begin)
	void*        mTestName1;        // +0x14  (localized-string end)
	void*        mpInstance;        // +0x18
	int          mState;            // +0x1c
	char         _pad20[4];         // +0x20
	char         mFlag24;           // +0x24
	char         _pad25[3];
	int          mCount;            // +0x28
	int          mStep;             // +0x2c
	char         mFlag30;           // +0x30
	char         _pad31[3];
	void*        mVec34begin;       // +0x34
	void*        mVec34end;         // +0x38
	char         _pad3c[0x10];      // +0x3c
	void*        mVec4cbegin;       // +0x4c
	void*        mVec4cend;         // +0x50
	char         _pad54[0xc];       // +0x54
	void*        mVec60begin;       // +0x60
	void*        mVec60end;         // +0x64
	char         _pad68[0xc];       // +0x68
	void*        mpWindow;          // +0x74 (cSPUILayout*)
	Stopwatch    mTimer;            // +0x78
	int          mMsgState;         // +0x90
	void*        mpHandler;         // +0x94
	void*        mHandlerArg1;      // +0x98
	void*        mHandlerArg2;      // +0x9c
	void*        mHandlerArg3;      // +0xa0
	void*        mHandlerArg4;      // +0xa4

	void HandlerTeardown();                                 // 0x00EC51A0
	void Tick();                                            // 0x00EC51F0
	char HandleMessage(char replay);                        // 0x00EC5340
	char ProcessMessage(int* msg, void* payload);           // 0x00EC56B0
	char Start(void* instance, char a, char b);             // 0x00EC5990
	char RequestAsset(void* key, void* a, void* b);         // 0x00EC5A60
	void DebugDraw();                                       // 0x00EC5B10
	void DebugDrawHelper();                                 // 0x00EC5C70
};

// A secondary subobject of cTestScript living at +0xc, whose message-filter slot is
// 0x00EC5310.  Its `this` is cTestScript+0xc.
struct cTestScriptSlotC
{
	char Filter(void* unused, int* msg);                    // 0x00EC5310
};

// A secondary subobject of cTestScript living at +0x14, whose virtual slot is
// 0x00EC5DE0.  Its `this` is cTestScript+0x14, so the methods recover the outer object.
struct cTestScriptSlot
{
	char  _pad00[8];          // +0x00
	int   mState;             // +0x08  (= outer + 0x1c)
	char  _pad0c[4];          // +0x0c
	char  mFlag10;            // +0x10  (= outer + 0x24)
	char  _pad11[3];
	char Dispatch(int* key, char replay);                   // 0x00EC5DE0
};

// ---------------------------------------------------------------------------
// 0x00EC51A0 -- remove messaging handler + reset
// ---------------------------------------------------------------------------
// @ 0x00ec51a0
void cTestScript::HandlerTeardown()
{
	if (mpHandler != NULL)
	{
		void* h = mpHandler;
		mpHandler = NULL;
		EA_Messaging_RemoveHandler(h, mHandlerArg1, mHandlerArg2, mHandlerArg3, mHandlerArg4);
	}
	OpReset(1, 0);
}

// ---------------------------------------------------------------------------
// 0x00EC51F0 -- tick / timeout pump
// ---------------------------------------------------------------------------
// @ 0x00ec51f0
void cTestScript::Tick()
{
	if (mCount > 0)
	{
		if (--mCount == 0)
		{
			mFlag24 = 0;
			GetIdDispatcher()->v10(0x21851ebe);
		}
	}

	if (mState != 0)
	{
		if (mpWindow != NULL)
		{
			void* wnd = ((cSPUILayout*)mpWindow)->FindWindowByID(0x72993a8, 1);
			if (wnd != NULL)
			{
				float t = SPUIHelpers_GetElapsedSeconds() * gNegTwo;
				float params[4];
				params[3] = t;
				params[0] = 0.0f;
				params[1] = 0.0f;
				params[2] = 1.0f;
				FUN_00808230(wnd, params);
			}
		}

		unsigned long long elapsed = mTimer.GetElapsedTime();
		if (((uint)(elapsed >> 32) > 0) || ((uint)elapsed > 60000))
		{
			mTimer.mnStartTime = 0;
			mTimer.mnTotalElapsed = 0;

			int s = mState;
			if (s == 1)
			{
				if (mFlag30 != 0)
				{
					Op4c80();
					mMsgState = 7;
					UI_CalloutMessageBox(&mTestName0, (const void*)0x015abc10);
					return;
				}
				Op4c80();
				mMsgState = 8;
				UI_CalloutMessageBox(&mTestName0, (const void*)0x015abc04);
			}
			else if (s == 2)
			{
				OpReset(1, 0);
				return;
			}
		}
	}
}

// ---------------------------------------------------------------------------
// 0x00EC5310 -- message filter (thiscall, ret 8)
// ---------------------------------------------------------------------------
// @ 0x00ec5310
char cTestScriptSlotC::Filter(void* unused, int* msg)
{
	if (*(int*)((char*)msg + 8) == 0x287259f6 && *(int*)((char*)msg + 0xc) == 0x7298e88)
		((cTestScript*)((char*)this - 0xc))->OpReset(1, 0);
	return 0;
}

// ---------------------------------------------------------------------------
// 0x00EC5340 -- SP::cTestScript::HandleMessage
// ---------------------------------------------------------------------------
// @ 0x00ec5340
char cTestScript::HandleMessage(char replay)
{
	if (mStep > 6)
		return 1;

	for (;;)
	{
		int step = mStep;
		if (step != 0)
		{
			if (step == 1)
			{
				AuthManager* auth = SP_AuthManager();
				if (mVec34begin != mVec34end &&
					(auth->v22() == 0 || auth->v9() != 0))
				{
					if (replay != 0)
						return 1;
					mMsgState = 9;
					if (mFlag30 != 0)
					{
						UI_CalloutMessageBox(&mTestName0, (const void*)0x015abc34);
						return 1;
					}
					UI_CalloutMessageBox(&mTestName0, (const void*)0x015abc28);
					return 1;
				}
			}
			else if (step == 2)
			{
				char a = ((TestInstance*)mpInstance)->IsFlag(0x800);
				char b = ((TestInstance*)mpInstance)->IsFlag(0x20000);
				if (a != 0 || b != 0)
				{
					if (replay != 0)
						return 0;
					return Op4380(a, b, mFlag30);
				}
			}
			else if (step == 3)
			{
				char a = ((TestInstance*)mpInstance)->IsFlag(0x400);
				if (a != 0 && replay == 0)
				{
					mMsgState = 4;
					UI_CalloutMessageBox(&mTestName0, (const void*)0x015abc88);
					return 1;
				}
			}
			else if (step == 4)
			{
				AuthManager* auth = SP_AuthManager();
				if (auth->v9() == 0)
				{
					char* inst = (char*)mpInstance;
					unsigned int k0 = 0xffffffffu;
					unsigned int k1 = 0xffffffffu;
					Pollinator* poll = FUN_0067cb30();
					FUN_0054e530(POLL_ASSETDIR(poll), inst + 8, (unsigned long long*)&k0, false);
					if ((k0 & k1) != 0xffffffffu)
					{
						unsigned int i = 0;
						unsigned int off = 0x68;
						do
						{
							int tag = *(int*)(inst + off);
							if (tag == 1 || tag == 0)
							{
								unsigned int v0 = *(unsigned int*)(inst + 8);
								unsigned int v1 = *(unsigned int*)(inst + 0xc);
								unsigned int v2 = *(unsigned int*)(inst + 0x10);
								unsigned int key = (i + 1) ^ v2;
								key &= 0xff;
								key ^= v2;
								unsigned int loc[3];
								loc[0] = v0;
								loc[1] = 0x2f7d0004;
								loc[2] = key;
								EA::ResourceMan::Manager* mgr = EA::ResourceMan::GetManager();
								char got = mgr->v3();
								if (got == 0)
								{
									Pollinator* poll2 = FUN_0067cb30();
									FUN_00610c20(poll2, (void*)k0, (void*)k1);
									if (replay == 0)
										goto doReset;
									break;
								}
							}
							off += 4;
							i++;
						} while (off < 0x78);
					}
				}
			}
			else if (step == 5)
			{
				void* vec = &mVec34begin;
				FUN_005962b0((Vec34*)vec);
				int mask = 0x600;
				if (replay != 0)
					mask = 0x200;
				((TestInstance*)mpInstance)->Collect(mask, vec);
				if (mVec34begin != mVec34end)
				{
					unsigned int n = (unsigned int)(((int)mVec34end - (int)mVec34begin) >> 3);
					if (n != 0)
					{
						unsigned int i = 0;
						do
						{
							unsigned int v0 = *(unsigned int*)((int)mVec34begin + i * 8);
							unsigned int v1 = *(unsigned int*)((int)mVec34begin + i * 8 + 4);
							Pollinator* poll = FUN_0067cb30();
							AssetDirectory_s* dir = POLL_ASSETDIR(poll);
							unsigned int loc[3];
							FUN_0054e460(dir, v0, v1, loc);
							if (FUN_0054e740(dir, v0, v1) == 0)
								FUN_0054ed50(dir, v0, v1, 1);
							Pollinator* poll2 = FUN_0067cb30();
							FUN_006108a0(poll2, (void*)v0, (void*)v1);
							i++;
						} while (i < n);
					}
					if (replay == 0)
					{
						if (mpWindow == NULL)
						{
						doReset:
							Op4750();
						}
						mTimer.Restart();
						return 1;
					}
				}
			}
			else if (step == 6)
			{
				if (replay == 0)
					Op5100();
				else
					OpReset(0, 0);
			}
		}
		mStep++;
		if (mStep > 6)
			return 1;
	}
}

// ---------------------------------------------------------------------------
// 0x00EC56B0 -- message pipeline (thiscall, ret 8)
// ---------------------------------------------------------------------------
// @ 0x00ec56b0
char cTestScript::ProcessMessage(int* msg, void* payload)
{
	int mstate = mMsgState;
	if (mstate == 7 || mstate == 8)
		return 0;

	char* pl = (char*)payload;
	unsigned int k0 = 0, k1 = 0;
	int step = mStep;
	if (step == 1)
	{
		unsigned int id = (unsigned int)msg;
		if (id < 0x5b98f53)
		{
			if (id == 0x5b98f52)
				goto resetState;
			if (id == 0x44db12e)
			{
				if (payload == NULL)
					return 0;
				mStep = 2;
				(void)HandleMessage(0);
				return 0;
			}
			if (id != 0x5b96086)
				return 0;
		}
		else
		{
			if (id != 0x5c5594a && id != 0x5dd52c7)
				return 0;
		}
	resetState:
		OpReset(1, 0);
		return 0;
	}
	else if (step == 4)
	{
		if ((unsigned int)msg == 0x1dd7bda9 && payload != NULL)
		{
			char* p1 = *(char**)(pl + 4);
			if (p1 != NULL)
			{
				int type = (int)(**(int(__thiscall**)(char*))(*(int*)p1 + 0x10))(p1);
				if (type == 0x226182d1)
				{
					mStep++;
					(void)HandleMessage(0);
					mTimer.Restart();
					return 0;
				}
			}
		}
		return 0;
	}
	else if (step == 5)
	{
		if ((unsigned int)msg == 0x1dd7bda9)
		{
			int isOne = *pl == 1;
			char* p1 = *(char**)(pl + 4);
			if (p1 != NULL)
			{
				int type = (int)(**(int(__thiscall**)(char*))(*(int*)p1 + 0x10))(p1);
				if (type == 0x3053c62)
				{
					int obj = *(int*)(pl + 4);
					if (*(int*)(obj + 0xc) != 3)
						return 0;
					unsigned long long number = 0;
					if (sscanf(*(const char**)(obj + 0x1c), "%I64u", &number) == 0)
						return 0;
					if (isOne)
					{
						int inner = *(int*)(obj + 8);
						if (*(int*)(inner + 0x60) != *(int*)(inner + 0x64))
							return 0;
						k0 = (unsigned int)number;
						k1 = (unsigned int)(number >> 32);
					}
					else
					{
						k0 = (unsigned int)number;
						k1 = (unsigned int)(number >> 32);
					}
					goto doInsert;
				}
				type = (int)(**(int(__thiscall**)(char*))(*(int*)p1 + 0x10))(p1);
				if (type == 0x30d6f6b)
				{
					if (isOne)
						return 0;
					int a = *(int*)(p1 + 0xc);
					int b = *(int*)(p1 + 8);
					int base = *(int*)(a + 0x60);
					k0 = *(unsigned int*)(b * 0x118 + base + 0x10);
					k1 = *(unsigned int*)(b * 0x118 + base + 0x14);
				}
				else
				{
					type = (int)(**(int(__thiscall**)(char*))(*(int*)p1 + 0x10))(p1);
					if (type != 0x30d7c0b || isOne)
						return 0;
					int a = *(int*)(p1 + 0x10);
					int b = *(int*)(p1 + 0xc);
					int base = *(int*)(b + 0x60);
					k0 = *(unsigned int*)(a * 0x118 + base + 0x10);
					k1 = *(unsigned int*)(a * 0x118 + base + 0x14);
				}
			doInsert:
				void* found = FUN_00ec4430(mVec34begin, mVec34end, &k0);
				if (found != mVec34end)
				{
					if (mFlag30 == 0)
					{
						Op4c80();
						mMsgState = 8;
						UI_CalloutMessageBox(&mTestName0, (const void*)0x015abc04);
					}
					else
					{
						Op4c80();
						mMsgState = 7;
						UI_CalloutMessageBox(&mTestName0, (const void*)0x015abc10);
					}
				}
			}
			return 0;
		}
		else if ((unsigned int)msg == 0x9421c619)
		{
			if (mVec34begin != mVec34end)
			{
				unsigned int key[3];
				key[0] = (unsigned int)((int*)pl)[0];
				key[1] = (unsigned int)((int*)pl)[1];
				key[2] = (unsigned int)((int*)pl)[2];
				Pollinator* poll = FUN_0067cb30();
				char ok = FUN_0054e530(POLL_ASSETDIR(poll), key, 0, false);
				if (ok != 0)
				{
					void* found = FUN_00ec4430(mVec34begin, mVec34end, 0);
					if (found != mVec34end)
					{
						Op4e50(found);
						if (mVec34begin != mVec34end)
						{
							mTimer.Restart();
							return 0;
						}
						Op5100();
						return 0;
					}
				}
			}
			return 0;
		}
	}
	return 0;
}

// ---------------------------------------------------------------------------
// 0x00EC5990 -- Start
// ---------------------------------------------------------------------------
// @ 0x00ec5990
char cTestScript::Start(void* instance, char a, char b)
{
	if (mState != 0 && b != 0)
		return 0;

	OpReset(1, 0);
	if (instance != NULL)
	{
		void* oldInst = mpInstance;
		if (instance != oldInst)
		{
			(**(void(__thiscall**)(void*))(*(int*)instance))((void*)instance);
			mpInstance = instance;
			if (oldInst != NULL)
				(**(void(__thiscall**)(void*))(*(int*)oldInst + 4))(oldInst);
		}

		void* first = mVec34begin;
		void* last = mVec34end;
		eastl_vector_insert(first, last, 0);
		mVec34end = (void*)((int)mVec34end + (((int)last - (int)first >> 3) * -8));

		int mask = 0x600;
		if (b != 0)
			mask = 0x200;
		((TestInstance*)mpInstance)->Reset();
		((TestInstance*)mpInstance)->Collect(mask, &mVec34begin);
		mFlag30 = a;
		mState = 1;
		mStep = 0;
		return HandleMessage(b);
	}
	return 0;
}

// ---------------------------------------------------------------------------
// 0x00EC5A60 -- asset request helper (thiscall, ret 0xc)
// ---------------------------------------------------------------------------
// @ 0x00ec5a60
char cTestScript::RequestAsset(void* key, void* a, void* b)
{
	OpReset(1, 0);

	void* obj = NULL;
	void* mgr = EA::ResourceMan::GetManager();

	char ok = (**(char(__thiscall**)(void*, void*, void**, int, int, int, int))(*(int*)mgr + 0xc))(
		mgr, key, &obj, 0, 0, 0, 0);
	if (ok != 0)
	{
		if (obj == NULL)
			return 0;
		int found = (**(int(__thiscall**)(void*, int))(*(int*)obj + 0xc))(obj, 0xe742574a);
		if (found != 0)
		{
			char r = Start((void*)found, (char)(int)a, (char)(int)b);
			if (obj != NULL)
				(**(void(__thiscall**)(void*))(*(int*)obj + 4))(obj);
			return r;
		}
	}
	if (obj != NULL)
		(**(void(__thiscall**)(void*))(*(int*)obj + 4))(obj);
	return 0;
}

// ---------------------------------------------------------------------------
// 0x00EC5B10 -- SP::RelationShipDebugDraw
// ---------------------------------------------------------------------------
// @ 0x00ec5b10
void cTestScript::DebugDraw()
{
	if (*(int*)((char*)gSporeApp + 0x7c) == 0)
		goto show;

	{
		int count = ((int)mVec4cend - (int)mVec4cbegin) / 0xc;
		EaString text;
		text.mpBegin = &gEmptyString16a;
		text.mpEnd = &gEmptyString16a;
		text.mpCapacity = &gEmptyString16b;

		if (count != 0)
		{
			unsigned int i = 0;
			unsigned int off = 0;
			do
			{
				if (i >= 0x60)
					break;
				EaString piece;
				piece.mpBegin = &gEmptyString16a;
				piece.mpEnd = &gEmptyString16a;
				piece.mpCapacity = &gEmptyString16b;
				FUN_00eeea50((const void*)((int)mVec4cbegin + off), &piece);
				if (piece.mpBegin != piece.mpEnd)
				{
					if (i != 0)
						EaString_push_back(&text, 10);
					WStr_Append(&text, piece.mpBegin, piece.mpEnd);
				}
				if (((int)piece.mpCapacity - (int)piece.mpBegin & 0xfffffffe) > 2 && piece.mpBegin != NULL)
					operator_delete__(piece.mpBegin);
				i++;
				off += 0xc;
				count = ((int)mVec4cend - (int)mVec4cbegin) / 0xc;
			} while (i < (unsigned int)count);
		}

		wchar_t* end = text.mpBegin;
		while (*end != 0)
			end++;
		WString_Assign(&text, text.mpBegin, end);

		if (((int)text.mpCapacity - (int)text.mpBegin & 0xfffffffe) > 2 && text.mpBegin != NULL)
			operator_delete__(text.mpBegin);
	}

show:
	mMsgState = 5;
	UI_CalloutMessageBox(&mTestName0, (const void*)0x015abc94);
}

// ---------------------------------------------------------------------------
// 0x00EC5C70 -- RelationShipDebugDraw helper
// ---------------------------------------------------------------------------
// @ 0x00ec5c70
void cTestScript::DebugDrawHelper()
{
	if (*(int*)((char*)gSporeApp + 0x7c) == 0)
		goto show;

	{
		int count = ((int)mVec60end - (int)mVec60begin) >> 3;
		EaString text;
		text.mpBegin = &gEmptyString16a;
		text.mpEnd = &gEmptyString16a;
		text.mpCapacity = &gEmptyString16b;

		if (count > 0)
		{
			unsigned int i = 0;
			do
			{
				if (i >= 8)
					break;
				unsigned int v0 = *(unsigned int*)((int)mVec60begin + i * 8);
				unsigned int v1 = *(unsigned int*)((int)mVec60begin + i * 8 + 4);
				unsigned int key[3];
				key[0] = 0;
				key[1] = 0;
				key[2] = 0;
				Pollinator* poll = FUN_0067cb30();
				char ok = FUN_0054e530(POLL_ASSETDIR(poll), &v0, (unsigned long long*)key, false);
				if (ok != 0)
				{
					EaString piece;
					piece.mpBegin = &gEmptyString16a;
					piece.mpEnd = &gEmptyString16a;
					piece.mpCapacity = &gEmptyString16b;
					FUN_00eeea50((const void*)key, &piece);
					if (piece.mpBegin != piece.mpEnd)
					{
						if (i != 0)
							EaString_push_back(&text, 10);
						WStr_Append(&text, piece.mpBegin, piece.mpEnd);
					}
					if (((int)piece.mpCapacity - (int)piece.mpBegin & 0xfffffffe) > 2 && piece.mpBegin != NULL)
						operator_delete__(piece.mpBegin);
				}
				i++;
				count = ((int)mVec60end - (int)mVec60begin) >> 3;
			} while ((int)i < count);
		}

		wchar_t* end = text.mpBegin;
		while (*end != 0)
			end++;
		WString_Assign(&text, text.mpBegin, end);

		if (((int)text.mpCapacity - (int)text.mpBegin & 0xfffffffe) > 2 && text.mpBegin != NULL)
			operator_delete__(text.mpBegin);
	}

show:
	mMsgState = 6;
	UI_CalloutMessageBox(&mTestName0, (const void*)0x015abca0);
}

// ---------------------------------------------------------------------------
// 0x00EC5DE0 -- game-mode dispatch (thiscall, ret 8); `this` = cTestScript+0x14
// ---------------------------------------------------------------------------
// @ 0x00ec5de0
char cTestScriptSlot::Dispatch(int* key, char replay)
{
	void* mode = SP_GetCurrentGameMode();
	if (mode != (void*)0x01654c10)
	{
		if (mode == (void*)0x2ccd1d2 && replay == 0)
		{
			cTestScript* outer = (cTestScript*)((char*)this - 0x14);
			if (outer->RequestAsset(key, (void*)1, (void*)0) != 0)
			{
				if (mState == 1)
				{
					mFlag10 = 1;
					return 1;
				}
				outer->Op4330(key);
			}
		}
	}
	else
	{
			SporeApp* app = (SporeApp*)gSporeApp;
		if (app != NULL && app->mMode == 1)
		{
			void* p = app->mpCurrentGame;
			if (p != NULL)
				FUN_00ed8130(*(Key3*)key);
		}
	}
	return 1;
}
