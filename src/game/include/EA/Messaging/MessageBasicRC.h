// EA::Messaging::MessageRC, EA::Messaging::MessageBasicRC<N> (MessageBasic<N> + MessageRC) and SP::MessageBasicRC<N> (that + `mRCFlags`).
// Hand-maintained.  Layout = the dev PDB (work/devbuild/types.json): EA::Messaging::MessageBasicRC<5> 0x38 = MessageBasic<5>
// (0x30) at +0 and MessageRC (0x8: IMessageRC vptr, AtomicInt mRefCount) at +0x30; SP::MessageBasicRC<5> 0x40 with mRCFlags
// at +0x38 (<1> 0x20 / 0x18, <2> 0x28 / 0x20, <3> 0x30 / 0x28).  Unverified in retail.
#ifndef GAME_EA_MESSAGING_MESSAGEBASICRC_H
#define GAME_EA_MESSAGING_MESSAGEBASICRC_H
#include "EA/Messaging/MessageBasic.h"
#include "EA/Messaging/IMessageRC.h"
#include "EA/Thread/AtomicInt.h"
namespace EA { namespace Messaging {
#pragma pack(push, 8)
// EA::Messaging::MessageRC (dev PDB 0x8: IMessageRC vptr + AtomicInt<int> mRefCount; dev functions in SPAdjectives.obj only,
// no retail address known): defined here because no module's closure generates it.
class MessageRC : public IMessageRC {
 public:
  MessageRC();
  virtual ~MessageRC();
  virtual int AddRef();
  virtual int Release();
  EA::Thread::AtomicInt<int> mRefCount;
};
template <int N>
class MessageBasicRC : public MessageBasic<N>, public MessageRC {
 public:
};
#pragma pack(pop)
}}  // namespace EA::Messaging
namespace SP {
#pragma pack(push, 8)
template <int N>
class MessageBasicRC : public EA::Messaging::MessageBasicRC<N> {
 public:
  unsigned int mRCFlags;
};
#pragma pack(pop)
}  // namespace SP
#endif
