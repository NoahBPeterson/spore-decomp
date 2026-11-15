#include "types.h"

namespace DispatcherReconstruction {
struct ParameterSet;

struct Unknown32 {
    virtual int AddRef() = 0;
    virtual int Release() = 0;
    virtual ~Unknown32() {}  // body 0x00a16a20; deleting helper 0x00517400
};
struct DispatcherInterface : Unknown32 {
    virtual void* AsInterface(unsigned id);  // overridden at 0x00689660
    virtual void Slot4();  // 0x0068b5b0
    virtual void Slot5();  // 0x00689920
    virtual void Slot6();  // 0x00689980
    virtual int ExecuteCommand(unsigned id, ParameterSet* in, ParameterSet* out);  // overridden at 0x006899d0
};
struct RefCount {
    virtual ~RefCount() {}  // body 0x005725f0; deleting helper 0x0041d780
    int count;
};
struct MessageInterface : Unknown32 {
    virtual void* AsInterface(unsigned id) = 0;
    virtual void* GetInputParameters() = 0;
    virtual void* GetOutputParameters() = 0;
};
struct MessageBasic2 {
    union { void* input; unsigned __int64 data0; };
    union { void* output; unsigned __int64 data1; };
    unsigned int id;
    MessageBasic2() : id(0) {}
};
// Release is dispatched through slot 1 of each runtime parameter object.
struct RefObject {
    virtual void Slot0();
    virtual void Release();
};
struct MessageRef {
    RefObject* p;
    MessageRef() : p(0) {}
    ~MessageRef() { if (p) p->Release(); }
};
struct DispatcherMessage : MessageInterface, MessageBasic2 {
    MessageRef inputParameters;
    MessageRef outputParameters;
    virtual int AddRef() { return 1; }
    virtual int Release() { return 1; }
    virtual void* AsInterface(unsigned id);  // 0x00689640
    virtual void* GetInputParameters() { return inputParameters.p; }
    virtual void* GetOutputParameters() { return outputParameters.p; }
    __declspec(noinline) ~DispatcherMessage();  // body 0x00689810; deleting helper 0x00689d20
};
DispatcherMessage::~DispatcherMessage() {}

struct Dispatcher : DispatcherInterface, RefCount {
    DispatcherMessage message;
    MessageRef input;
    MessageRef output;
    MessageRef generator;
    virtual int AddRef();  // 0x00c6a960
    virtual int Release();  // 0x007b86e0
    virtual void* AsInterface(unsigned id);  // 0x00689660
    ~Dispatcher();  // body 0x00689880; deleting helper 0x00689da0
    virtual int ExecuteCommand(unsigned id, ParameterSet* in, ParameterSet* out);  // 0x006899d0
};

// Retail 0x014032e8: AddRef 0x00c6a960, Release 0x007b86e0,
// deleting destructor 0x00689da0, AsInterface 0x00689660,
// remaining slots 0x0068b5b0, 0x00689920, 0x00689980, 0x006899d0.
// Retail secondary table 0x014032e4 contains thunk 0x00689910.
// Message table 0x014032cc contains 0x01154720 twice, 0x00689d20,
// 0x00689640, 0x00a42730, and 0x00ff35d0.
// @ 0x00689880
Dispatcher::~Dispatcher() {}
}
