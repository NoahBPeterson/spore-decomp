// Slice s007e20a0. Only 0x007E20A0 in this slice's VA list is a real function entry point.
// The other listed VAs land mid-instruction or mid-body inside neighbouring functions, so the
// slice lists them as skipped (see nonmatching.txt / the report). Needs /GS- (manifest flags).
//
// 0x007E20A0 belongs to a game-mode manager. It loads a properties/config file from `path`,
// switches to the "Preload" mode when -preload is on the command line, and then activates
// "Demo" (in a demo build), the mode given by -state:<name>, or "Main".
#include "types.h"

void EASTL_allocator_deallocate(void* p) throw();
extern wchar_t gEmptyString16[];

struct string8 {
  char* mpBegin;
  char* mpEnd;
  char* mpCapacity;
  struct allocator {} mAllocator;
  const char* c_str() const { return mpBegin; }
  ~string8() {
    if ((mpCapacity - mpBegin) > 1 && mpBegin)
      EASTL_allocator_deallocate(mpBegin);
  }
};

struct string16 {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  struct allocator {} mAllocator;
  string16() : mpBegin(gEmptyString16), mpEnd(gEmptyString16), mpCapacity(gEmptyString16 + 1) {}
  ~string16() {
    if ((mpCapacity - mpBegin) > 1 && mpBegin)
      EASTL_allocator_deallocate(mpBegin);
  }
};

bool FUN_00931fa0(const wchar_t* path);
string8 FUN_0093c440(const wchar_t* s, int len);
string8 FUN_0093c570(const string16& s);

struct ICommandLine {
  int FindSwitch(const wchar_t* name, int a, string16* value, int b);
};

struct IAppProps {
  virtual void v00();
  virtual void v04();
  virtual void Init();
  virtual void v0c();
  virtual void SetOwner(void* p);
  virtual void v14();
  virtual void Reset();
  virtual void Load(const char* path, int flags);
  virtual void Finish();
};

struct IDemoQuery {
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
  virtual void v20(); virtual void v24(); virtual void v28(); virtual void v2c();
  virtual void v30(); virtual void v34(); virtual void v38(); virtual void v3c();
  virtual void v40(); virtual void v44(); virtual void v48(); virtual void v4c();
  virtual bool IsDemo();
};
IDemoQuery* FUN_0067dd00();
void* FUN_00840940();

struct PropsPtr {
  IAppProps* p;
  IAppProps* operator->() const { return p; }
  void Assign(void* q);
};

class cModeManager {
public:
  virtual void v00(); virtual void v04(); virtual void v08(); virtual void v0c();
  virtual void v10(); virtual void v14(); virtual void v18(); virtual void v1c();
  virtual void v20(); virtual void v24();
  virtual void SetActiveMode(int id);
  virtual void v2c(); virtual void v30(); virtual void v34();
  virtual int GetModeID(const char* name);

  bool FUN_007e20a0(const wchar_t* path, ICommandLine* cmd, bool flag);

  char pad04[0x81 - 4];
  bool mFlag81;
  char pad82[0x154 - 0x82];
  PropsPtr mProps;
  void* mOwner;
};

// @ 0x007E20A0
bool cModeManager::FUN_007e20a0(const wchar_t* path, ICommandLine* cmd, bool flag) {
  mFlag81 = flag;
  if (!path || !FUN_00931fa0(path))
    return false;
  if (!mProps.p) {
    mProps.Assign(FUN_00840940());
    mProps->Init();
    IAppProps* p = mProps.p;
    void* o = mOwner;
    p->SetOwner(o);
  } else {
    mProps->Reset();
  }
  mProps->Load(FUN_0093c440(path, -1).c_str(), 5);
  mProps->Finish();

  if (cmd->FindSwitch(L"preload", 0, 0, 0) != -1) {
    int id = GetModeID("Preload");
    if (id != -1)
      SetActiveMode(id);
  }

  string16 state;
  int id;
  if (FUN_0067dd00()->IsDemo()) {
    id = GetModeID("Demo");
  } else if (cmd->FindSwitch(L"state", 0, &state, 0) != -1) {
    id = GetModeID(FUN_0093c570(state).c_str());
  } else {
    id = GetModeID("Main");
  }
  if (id != -1)
    SetActiveMode(id);
  return true;
}
