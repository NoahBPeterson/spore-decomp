// EA::ArgScript::cCommandStateT<State, Base>: a command base plus the state pointer (dev: every instantiation is
// sizeof(Base) + 4, mState at the end, e.g. <cNullState, cCommandBase> 0x10 with mState at +0xc).  Hand-maintained.
#ifndef GAME_EA_ARGSCRIPT_CCOMMANDSTATET_H
#define GAME_EA_ARGSCRIPT_CCOMMANDSTATET_H
namespace EA { namespace ArgScript {
template <typename State, typename Base>
struct cCommandStateT : public Base {
  State* mState;
};
}}  // namespace EA::ArgScript
#endif
