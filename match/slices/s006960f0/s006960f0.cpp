// slice s006960f0 — SP locale manager (cLocaleManager), App::cLocaleChangeMessage and the
// eastl::fixed_string<wchar_t,16,1> / eastl::basic_string<wchar_t> helpers they use.
// Flags: /O2 /MD /Gy /EHsc /TP /GS-
#include "types.h"
#include <intrin.h>

void* operator new(size_t n, const char* pName, int flags, unsigned debugFlags, const char* file, int line);
void operator delete(void* p);

namespace eastl {

class allocator { public:
  void deallocate(void* p) { ::operator delete(p); }
  void* allocate(size_t n, const char* pName, int flags, unsigned debugFlags, const char* file, int line) {
    return ::operator new(n, pName, flags, debugFlags, file, line);
  }
};
typedef unsigned int size_type;

// ---------------------------------------------------------------------------------------------
// eastl::basic_string<wchar_t, fixed_vector_allocator<2,16,2,0,1>> — the base of fixed_string.
// Layout: 0 mpBegin, 4 mpEnd, 8 mpCapacity, 0xc empty overflow allocator, 0x10 mpPoolBegin.
struct FixedStringBase {
  wchar_t* mpBegin;
  wchar_t* mpEnd;
  wchar_t* mpCapacity;
  allocator mOverflowAllocator;
  void* mpPoolBegin;

  FixedStringBase() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  FixedStringBase(void* pool) : mpBegin(0), mpEnd(0), mpCapacity(0) { mpPoolBegin = pool; }
  FixedStringBase& append(const wchar_t* pBegin, const wchar_t* pEnd);  // 0x68cc10

  void clear() {
    if (mpBegin != mpEnd) {
      *mpBegin = 0;
      mpEnd = mpBegin;
    }
  }
  // (cap - begin) cleared of its low bit, compared signed, then the begin / pool-begin identity.
  void DeallocateSelf() {
    if (((((int)((char*)mpCapacity - (char*)mpBegin)) & ~1) > 2) && mpBegin != 0 &&
        mpBegin != mpPoolBegin) {
      mOverflowAllocator.deallocate(mpBegin);
    }
  }
  ~FixedStringBase() { DeallocateSelf(); }
};

inline size_t CharStrlenW(const wchar_t* p) {
  const wchar_t* q = p;
  while (*q) ++q;
  return (size_t)(q - p);
}

// eastl::fixed_string<wchar_t,16,1>: 0x34 bytes, inline buffer at +0x14 (16 wchar_t).
struct FixedString16 : FixedStringBase {
  union {
    wchar_t mArray[1];
    char mBuffer[32];
  };

  FixedString16(const wchar_t* p);
  FixedString16(const FixedString16& x);
  FixedString16& operator=(const FixedString16& x);
};

// @ 0x006962a0
FixedString16::FixedString16(const wchar_t* p) : FixedStringBase(mBuffer) {
  mpBegin = mpEnd = mArray;
  mpCapacity = mpBegin + 16;
  *mpBegin = 0;
  append(p, p + CharStrlenW(p));
}

// @ 0x00696230
FixedString16::FixedString16(const FixedString16& x) : FixedStringBase(mBuffer) {
  mpBegin = mpEnd = mArray;
  mpCapacity = mpBegin + 16;
  *mpBegin = 0;
  append(x.mpBegin, x.mpEnd);
}

// @ 0x00696320
FixedString16& FixedString16::operator=(const FixedString16& x) {
  if (this != &x) {
    clear();
    append(x.mpBegin, x.mpEnd);
  }
  return *this;
}

// ---------------------------------------------------------------------------------------------
// eastl::basic_string<wchar_t> — the plain 0xc-byte string the locale manager keeps on the stack
// (command-line switch values, search paths). begin / end / capacity; the empty sentinel is the
// global gEmptyString16, whose (cap - begin) is 2 so DeallocateSelf never frees it.
struct WStr {
  wchar_t* mpBegin;      // +0
  wchar_t* mpEnd;        // +4
  wchar_t* mpCapacity;   // +8

  WStr& assign(const wchar_t* pBegin, const wchar_t* pEnd);   // 0x423650
  WStr& Append(const wchar_t* pBegin, const wchar_t* pEnd);   // 0x429580
  ~WStr() {
    if (((((int)((char*)mpCapacity - (char*)mpBegin)) & ~1) > 2) && mpBegin != 0)
      ::operator delete(mpBegin);
  }
};

}  // namespace eastl

extern wchar_t gEmptyString16[2];   // 0x1667bac — eastl empty wide-string sentinel
extern wchar_t gPathSep[];          // 0x13fa488 — L"\\"
extern char g_localeState;          // 0x152d97c — EA::Locale global state block

namespace EA {
struct AtomicInt {
  int mValue;
  AtomicInt() { _InterlockedExchange((long*)&mValue, 0); }
};
template <typename T>
class RefCountVTemplate { public:
  virtual ~RefCountVTemplate() {}
  T mRefCount;
  RefCountVTemplate() : mRefCount() {}
};
namespace Messaging {
class IMessageRC { public:
  virtual ~IMessageRC() {}
};
}  // namespace Messaging
namespace Allocator {
class ICoreAllocator {
 public:
  static ICoreAllocator* GetDefaultAllocator();               // 0x925cb0
  virtual void* v00();
  virtual void* v04();
  virtual void* Allocate(size_t n, int flags, void* tag);     // vtable +0x08
  virtual void  Free(void* p, size_t n);                      // vtable +0x0c
};
}  // namespace Allocator
namespace CommandLine {
class CommandLine {
 public:
  int FindSwitch(const wchar_t* s, int a, void* b, void* c);  // 0x92b300, -1 when absent
};
}  // namespace CommandLine
namespace Locale {
void Init();                                                  // 0x883730
bool SetLocale(void* state, int a, int b);                    // 0x882b30
void GetLocaleInfoInt(const wchar_t* name, const wchar_t* data);   // 0x881220
int GetLocaleInfoString(int a, int b, wchar_t* out, int n, const void* locale);  // 0x880910
}  // namespace Locale
namespace IO {
class Directory { public:
  static bool Exists(const wchar_t* path);                    // 0x9322b0
};
}  // namespace IO
}  // namespace EA

namespace App {
using eastl::FixedString16;

void SetStringManagerGlobal(void* p);   // 0x67e070

class cStringManager { public:
  cStringManager();                     // 0x6b6d10
  char mOpaque[0x2c];                   // allocation size the retail requests
};

// vtables 0x013eb918 / 0x013f65b4 (base), 0x01403d6c / 0x01403d5c (derived).
// Layout: 0 IMessageRC vftable, 4 RefCountVTemplate vftable + 8 mRefCount, 0xc mLocaleId.
class cLocaleChangeMessage : public EA::Messaging::IMessageRC, public EA::RefCountVTemplate<EA::AtomicInt> {
 public:
  FixedString16 mLocaleId;  // +0xc
  cLocaleChangeMessage(const FixedString16& id);
};

// @ 0x00696350
cLocaleChangeMessage::cLocaleChangeMessage(const FixedString16& id) : mLocaleId(id) {}

// Forces cl to emit the compiler-generated scalar deleting destructor (??_G).
void DestroyLocaleChangeMessage(cLocaleChangeMessage* p) { delete p; }

}  // namespace App

namespace SP {
using eastl::FixedString16;

// Intrusive list head the locale manager keeps (0x10 bytes: next, prev, allocator, tag slot) and
// the 0xc-byte node the broadcast helper splices into a local copy of it.
struct List16 {
  void* mNext;
  void* mPrev;
  EA::Allocator::ICoreAllocator* mAlloc;
  void* mZero;
};
struct LocaleNode {
  LocaleNode* mNext;
  LocaleNode* mPrev;
  void* mValue;
};

// The locale name/code table (0x152d6c8): 24 { name, code } pairs used by the locale matchers.
struct LocalePair { const wchar_t* mName; const wchar_t* mCode; };
extern LocalePair g_localeTable[24];   // 0x152d6c8
int LocaleCommonPrefix(const wchar_t* a, const wchar_t* b);  // 0x695c70
bool FUN_0087fd10(int* a, int* b, char c);                   // 0x87fd10
void* GetManager();                                          // 0x67dcd0 (resource manager)
bool GetDirString(unsigned hash, void* out, int dflt);       // 0x688830
bool GetRegistryLocale(const wchar_t* key, void* out);       // 0x6aba80

class cLocaleManager : public EA::RefCountVTemplate<int> {
 public:
  bool mbInit;             // +8
  bool field9;             // +9
  bool fieldA;             // +0xa
  char padB;               // +0xb
  int fieldC;              // +0xc
  int field10;             // +0x10
  int field14;             // +0x14
  FixedString16 mLocaleId;  // +0x18
  void* mpStringManager;   // +0x4c
  List16 mList50;          // +0x50
  List16 mList60;          // +0x60

  cLocaleManager();

  // vtable 0x1403d34: +0 dtor, +4 AddRef, +8 Release, +0xc GetReferenceCount, +0x10 SetLocale,
  // +0x14 helper, +0x18 SetFromMatch, +0x1c FindMatchingLocale.
  virtual void* AddRef() { return 0; }                                   // vtable +0x04
  virtual void* Release() { return 0; }                                  // vtable +0x08
  virtual int GetReferenceCount() { return 0; }                          // vtable +0x0c
  virtual bool ApplyLocaleId(const FixedString16& id) { return mbInit; } // vtable +0x10
  virtual void* LocaleHelper() { return 0; }                             // vtable +0x14
  virtual bool SetFromMatch(const eastl::WStr& id);                      // vtable +0x18
  virtual const wchar_t* FindMatchingLocale();                           // vtable +0x1c

  bool Init(void* pCommandLine, void* pUnknown);                         // 0x6964c0
  bool GetDefaultLanguage(const FixedString16& locale);                  // 0x696a60
};

// @ 0x00696420
cLocaleManager::cLocaleManager()
    : mbInit(false), field9(false), fieldA(false), fieldC(0), field10(2), field14(2),
      mLocaleId(L"**-**") {
  mpStringManager = 0;
  mList50.mAlloc = EA::Allocator::ICoreAllocator::GetDefaultAllocator();
  mList50.mZero = 0;
  mList50.mNext = &mList50;
  mList50.mPrev = &mList50;
  mList60.mAlloc = EA::Allocator::ICoreAllocator::GetDefaultAllocator();
  mList60.mZero = 0;
  mList60.mNext = &mList60;
  mList60.mPrev = &mList60;
}

// @ 0x006964c0
bool cLocaleManager::Init(void* pCommandLine, void* pUnknown) {
  (void)pUnknown;
  EA::CommandLine::CommandLine* cmd = (EA::CommandLine::CommandLine*)pCommandLine;

  if (cmd->FindSwitch(L"baseGame", 0, 0, 0) != -1) field9 = true;
  fieldA = false;
  if (cmd->FindSwitch(L"devDirs", 0, 0, 0) != -1) fieldA = true;
  if (cmd->FindSwitch(L"shipDirs", 0, 0, 0) != -1) fieldA = false;

  mpStringManager = new ("App/cStringManager", 0, 0, 0, 0) App::cStringManager();
  App::SetStringManagerGlobal(mpStringManager);
  EA::Locale::Init();

  // The locale-format tables registered with EA::Locale (name^..., data^...).  Each call is a
  // straight-line GetLocaleInfoInt(name, data); the payloads are the game's shipped locale data.
  EA::Locale::GetLocaleInfoInt(L"en^English^English^Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday^Mon.,Tue.,Wed.,Thur.,Fri.,Sat.,Sun.^January,February,March,April,May,June,July,August,September,October,November,December^Jan.,Feb.,Mar.,Apr.,May,June,July,Aug.,Sept.,Oct.,Nov.,Dec.^0^%f %l^", L"us^United States^United States^R^E^AM,PM^%h:%<02M:%<02S %<A^%#02m/%#02d/%02y^%>+m %<#d, %<y^$^,^.^%$%W%?p%?02F^%$-%W%?p%?02F^USA^840^%N%?p%?02F^%N%?p%?02F%%");
  EA::Locale::GetLocaleInfoInt(L"en^English^English^Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday^Mon.,Tue.,Wed.,Thur.,Fri.,Sat.,Sun.^January,February,March,April,May,June,July,August,September,October,November,December^Jan.,Feb.,Mar.,Apr.,May,June,July,Aug.,Sept.,Oct.,Nov.,Dec.^0^%f %l^", L"gb^United Kingdom^United Kingdom^L^E^^%02H:%02M:%<02S^%#02d/%#02m/%02y^%>#d %+m %<y^^,^.^%$%W%?p%?02F^-%$%W%?p%?02F^GBR^826^%N%?p%?02F^%N%?p%?02F%%");
  EA::Locale::GetLocaleInfoInt(L"fr^French^French^Lundi,Mardi,Mercredi,Jeudi,Vendredi,Samedi,Dimanche^Lun,Mar,Mer,Jeu,Ven,Sam,Dim^Janvier,Fevrier,Mars,Avril,Mai,Juin,Juillet,Aout,Septembre,Octobre,Novembre,Decembre^Jan,Fev,Mar,Avr,Mai,Juin,Juil,Aout,Sept,Oct,Nov,Dec^0^%f %l^", L"fr^France^France^R^M^^%#02H:%<#02M:%<#02S^%#02d/%>#02m/%>#04y^%#d %>m+ %>#04y^^^,^%W%?p%?02F %$^-%W%?p%?02F %$^FRA^250^%N%?p%?02F^%N%?p%?02F %%");
  EA::Locale::GetLocaleInfoInt(L"de-de^German^Deutsch^Montag,Dienstag,Mittwoch,Donnerstag,Freitag,Samstag,Sonntag^Mo,Di,Mi,Do,Fr,Sa,So^Januar,Februar,Marz,April,Mai,Juni,Juli,August,September,Oktober,November,Dezember^Jan,Feb,Mrz,Apr,Mai,Jun,Jul,Aug,Sep,Okt,Nov,Dez^0^%f %l", L"de^Germany^Deutschland^R^M^^%02H:%02M:%<02S^%#02d.%#02m.%02y^%>#d. %+m %<y^^.^,^%W%?p%?02F %$^-%W%?p%?02F %$^DEU^276^%N%?p%?02F^%N%?p%?02F %%");
  EA::Locale::GetLocaleInfoInt(L"es-es^Spanish^Espanol^Lunes,Martes,Miercoles,Jueves,Viernes,Sabado,Domingo^L,M,M,J,V,S,D^Enero,Febrero,Marzo,Abril,Mayo,Junio,Julio,Agosto,Septiembre,Octubre,Noviembre,Diciembre^En,Feb,Mar,Abr,Mayo,Jun,Jul,Ag,Sep,Oct,Nov,Dic^0^%f %l^", L"es^Spain^Espana^R^M^^%H:%<02M:%<02S^%#02d/%>#02m/%>#04y^%d %>m+ %>#04y^^.^,^%W%?p%?02F %$^-%W%?p%?02F %$^ESP^724^%N%?p%?02F^%N%?p%?02F%%");
  EA::Locale::GetLocaleInfoInt(L"it^Italian^Italiano^Lunedi,Martedi,Mercoledi,Giovedi,Venerdi,Sabato,Domenica^Lun,Mar,Mer,Gio,Ven,Sab,Dom^Gennaio,Febbraio,Marzo,Aprile,Maggio, Giugno, Luglio, Agosto, Settembre, Ottobre, Novembre, Dicembre^Gen,Feb,Mar,Apr,Mag,Giu,Lug,Ago,Set,Ott,Nov,Dic^0^%f %l^", L"it^Italy^Italia^R^M^^%H.%<02M.%<02S^%#02d/%>#02m/%>#02y^%#d %>m+ %>#04y^^.^,^%$ %W%?p%?02F^-%$ %W%?p%?02F^ITA^380^%N%?p%?02F^%N%?p%?02F%%");
  EA::Locale::GetLocaleInfoInt(L"pt-pt^Portuguese^Portugues^Segunda-feira,Tera-feira,Quarta-feira,Quinta-feira,Sexta-feira,Sabado,Domingo^Seg,Ter,Qua,Qui,Sex,Sab,Dom^Janeiro,Fevereiro,Marco,Abril,Maio,Junho,Julho,Agosto,Setembro,Outubro,Novembro,Dezembro^Jan,Feb,Mar,Apr,Mei,Jun,Jul,Aug,Sept,Okt,Nov,Dec^0^%f %l^", L"pt^Portugal^Portugal^R^M^^%H:%<02M:%<02S^%#02d-%<#02m-%<#04y^%d %>m+ %>#04y^^.^,^%W%?p%?02F %$^-%W%?p%?02F %$^PRT^620^%N%?p%?02F^%N%?p%?02F%%");
  EA::Locale::GetLocaleInfoInt(L"el^Greek^Greek^^0^%f %l^", L"gr^Greece^Greece^R^M^%p,%m^%h:%>02M:%>02S %>A^%#d/%>#m/%>#04y^%#d %>m+ %>#04y^^.^,^%W%?p%?02F %$^-%W%?p%?02F %$^GRC^300^%N%?p%?02F^%N%?p%?02F%%");
  EA::Locale::GetLocaleInfoInt(L"pt-br^Portuguese^Portugues^Segunda-feira,Tera-feira,Quarta-feira,Quinta-feira,Sexta-feira,Sabado,Domingo^Seg,Ter,Qua,Qui,Sex,Sab,Dom^Janeiro,Fevereiro,Marco,Abril,Maio,Junho,Julho,Agosto,Setembro,Outubro,Novembro,Dezembro^Jan,Feb,Mar,Apr,Mei,Jun,Jul,Aug,Sept,Okt,Nov,Dec^0^%f %l^", L"br^Brazil^Brasil^R^M^^%02H:%<02M:%<02S^%#02d/%<#02m/%<#02y^%#02d/%<#02m/%<#04y^R$^.^,^%$ %W%?p%?02F^-%$ %W%?p%?02F^BRA^076^%N%?p%?02F^%N%?p%?02F%%");
  EA::Locale::GetLocaleInfoInt(L"nl^Dutch^Nederlands^Maandag,Dinsdag,Woensdag,Donderdag,Vrijdag,Zaterdag,Zondag^Ma,Di,Wo,Do,Vr,Za,Zo^Januari,Februari,Maart,April,Mei,Juni,Juli,Augustus,September,Oktober,November,December^Jan,Feb,Mar,Apr,Mei,Jun,Jul,Aug,Sept,Okt,Nov,Dec^0^%f %l^", L"nl^Netherlands^Nederland^R^M^^%H:%<02M:%<02S^%#d-%>#m-%>#02y^%#d %>m+ %>#04y^^.^,^%$ %W%?p%?02F^%$ %W%?p%?02F-^NLD^528^%N%?p%?02F^%N%?p%?02F%%");
  EA::Locale::GetLocaleInfoInt(L"da^Danish^Dansk^Mandag,Tirsdag,Onsdag,Torsdag,Fredag,Lordag,Sondag^Man,Tir,Ons,Tor,Fre,Lor,Sun^januar,februar,marts,april,maj,juni,juli,august,september,oktober,november,december^jan,feb,mar,apr,maj,jun,jul,aug,sept,okt,nov,dec^0^%f %l^", L"dk^Denmark^Danmark^R^M^^%#02H:%<#02M:%<#02S^%#02d-%>#02m-%>#02y^########^kr^ ^,^%$ %W%?p%?02F^-%$ %W%?p%?02F^DNK^208^%N%?p%?02F^%N%?p%?02F %%");
  EA::Locale::GetLocaleInfoInt(L"fi^Finnish^Suomi^Maanantai,Tiistai,Keskiviikko,Torstai,Perjantai,Lauantai,Sunnuntai^Ma,Ti,Ke,To,Pe,La,Su^tammikuu,helmikuu,maaliskuu,huhtikuu,toukokuu,kesakuu,heinakuu,elokuu,syyskuu,lokakuu,marraskuu,joulukuu^En,Feb,Mar,Abr,Mayo,Jun,Jul,Ag,Sep,Oct,Nov,Dic^0^%f %l", L"fi^Finland^Suomi^R^M^^%#H:%>#02M:%>#02S^%#d.%>#m.%>#04y^%#d.%>m+ta %#04y^^ ^,^%W%?p%?02F %$^-%W%?p%?02F %$^FIN^246^%N%?p%?02F^%N%?p%?02F %%");
  EA::Locale::GetLocaleInfoInt(L"no^Norwegian^Norwegian^Mandag,Tirsdag,Onsdag,Torsdag,Fredag,Lordag,Sondag^mn,Tis,Ons,Tor,Fre,lr,sn^Januari,Februari,Mars,April,Maj,Juni,Juli,Augusti,September,Oktober,November,December^Jan,Feb,Mar,Apr,Mej,Jun,Jul,Aug,Sept,Okt,Nov,Dec^0", L"no^Norway^Noreg^R^M^^%02H:%<02M:%<02S^%#02d.%>#02m.%>#04y^%#d. %>m+ %>#04y^kr^ ^,^%$ %W%?p%?02F^%$ -%W%?p%?02F^NOR^578^%N%?p%?02F^%N%?p%?02F %%");
  EA::Locale::GetLocaleInfoInt(L"sv^Swedish^Svensk^mandag,tisdag,onsdag,torsdag,fredag,lordag,sondag^mn,Tis,Ons,Tor,Fre,lr,sn^Januari,Februari,Mars,April,Maj,Juni,Juli,Augusti,September,Oktober,November,December^Jan,Feb,Mar,Apr,Mej,Jun,Jul,Aug,Sept,Okt,Nov,Dec^0^%f %l^", L"se^Sweden^Sverige^R^M^^%02H:%<02M:%<02S^%04y-%<#02m-%<#02d^%d %>m+ %>04y^kr^ ^,^%W%?p%?02F %$^-%W%?p%?02F %$^SWE^752^%N%?p%?02F^%N%?p%?02F %%");
  EA::Locale::GetLocaleInfoInt(L"pl^Polish^Polish^Poniedzialek,Wtorek,Sroda,Czwartek,Piatek,Sobota,Niedziela^Pn,Wt,Sr,Cz,Pt,So,N^January,February,March,April,May,June,July,August,September,October,November,December^Jan,Feb,Mar,Apr,May,Jun,Jul,Aug,Sept,Oct,Nov,Dec^0^%f %l^", L"pl^Poland^Polska^R^M^^%02H:%<02M:%<02S^%02y-%<#02m-%<#02d^%d %>m+ %>#04y^l^ ^,^%W%?p%?02F %$^-%W%?p%?02F %$^POL^616^%N%?p%?02F^%N%?p%?02F%%");
  EA::Locale::GetLocaleInfoInt(L"cs^Czech^Czech^pondeli,utery,streda,ctvrtek,patek,sobota,nedele^Po,Ut,St,Ct,Pa,So,Ne^January,February,March,April,May,June,July,August,September,October,November,December^Jan,Feb,Mar,Apr,May,Jun,Jul,Aug,Sept,Oct,Nov,Dec^0^%f %l^", L"cz^Czech Republic^Ceska republika^R^M^^%#H:%<#02M:%<#02S^%#d.%>#m.%>#02y^%#d. %>+m%> #04y^^ ^,^%W%?p%?02F %$^-%W%?p%?02F %$^CZE^203^%N%?p%?02F^%N%?p%?02F %%");
  EA::Locale::GetLocaleInfoInt(L"ru^Russian^Russian^Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday^0^%f %l", L"ru^Russia^Russia^R^M^^%H:%<02M:%<02S^%#02d.%>#02m.%>#04y^%d %>m+ %>#04y^r.^ ^,^%W%?p%?02F%$^-%W%?p%?02F%$^RUS^643^%N%?p%?02F ^%N%?p%?02F%%");
  EA::Locale::GetLocaleInfoInt(L"hu^Hungarian^Magyarorszag^hetfo,kedd,szerda,csutortok,pentek,szombat,vasarnap^H,K,Sze,Cs,P,Szo,V^januar,februar,marcius,aprilis,majus,junius,julius,augusztus,szeptember,oktober,november,december^jan.,febr.,marc.,apr.,maj.,jun.,jul.,aug.,szept.,okt.,nov.,dec.^0^%f %l^", L"hu^Hungary^Magyarorszag^L^M^^%#H:%>#02M:%>#02S^%#y.%<#02m.%<#02d.^%#y. %<m+ %<#d.^Ft^^,^%W%?p%?02F %$^-%W%?p%?02F %$^HUN^348^%N%?p%?02F^%N%?p%?02F%%");
  EA::Locale::GetLocaleInfoInt(L"ja^Japanese^Japanese^Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday^Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday^January,February,March,April,May,June,July,August,September,October,November,December^Jan,Feb,Mar,Apr,May,Jun,Jul,Aug,Sept,Oct,Nov,Dec^0^%l %f^I", L"jp^Japan^Japan^L^M^^%H:%<02M:%<02S^%#04y/%<#02m/%<#02d^%#04y year %<#m month %<#d day^^,^.^%$%W%?p%?02F^-%$%W%?p%?02F^JPN^392^%N%?p%?02F^%N%?p%?02F%%");
  EA::Locale::GetLocaleInfoInt(L"th^Thai^Thai^Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday^0^%f %l^", L"th^Thailand^Thailand^L^M^^%H:%<02M:%<02S^%#d/%>#m/%>04y^%d %>m+ %>04y^^,^.^%$%W%?p%?02F^-%$%W%?p%?02F^THA^764^%N%?p%?02F^%N%?p%?02F%%");
  EA::Locale::GetLocaleInfoInt(L"ko^Korean^Korean^Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday^Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday^January,February,March,April,May,June,July,August,September,October,November,December^Jan,Feb,Mar,Apr,May,Jun,Jul,Aug,Sept,Oct,Nov,Dec^0^%l %f^I", L"kr^South Korea^Korea^R^M^^%A <%h:%<02M:%<02S^%#04y-%<#02m-%<#02d^%#04y year %<#m month %<#d day^^,^.^%$%W%?p%?02F^-%$%W%?p%?02F^KOR^410^%N%?p%?02F^%N%?p%?02F%%");
  EA::Locale::GetLocaleInfoInt(L"zh-tw^Chinese^Chinese Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday^Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday^January,February,March,April,May,June,July,August,September,October,November,December^Jan,Feb,Mar,Apr,May,Jun,Jul,Aug,Sept,Oct,Nov,Dec^0^%l%f^I", L"tw^China Taiwan^Taiwan^R^M^^%A %<02h:%<02M:%<02S^%04y/%<#m/%<#d^%04y year %m month %d day^NT$^,^.^%$%W%?p%?02F^-%$%W%?p%?02F^TWN^158^%N%?p%?02F^%N%?p%?02F%%");
  EA::Locale::GetLocaleInfoInt(L"zh-cn^Chinese^Chinese Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday^Monday,Tuesday,Wednesday,Thursday,Friday,Saturday,Sunday^January,February,March,April,May,June,July,August,September,October,November,December^Jan,Feb,Mar,Apr,May,Jun,Jul,Aug,Sept,Oct,Nov,Dec^0^%lx00b7%f^I", L"cn^China^China^R^M^^%#H:%<#02M:%<#02S^%04y-%<#m-%<#d^%04y year %<#m month %<#d day^^,^.^%$ %W%?p%?02F^%$ -%W%?p%?02F^CHN^156^%N%?p%?02F^%N%?p%?02F%%");

  eastl::WStr w;
  w.mpBegin = w.mpEnd = gEmptyString16;
  w.mpCapacity = gEmptyString16 + 1;

  if (cmd->FindSwitch(L"locale", 0, &w, 0) != -1) {
    FixedString16 tmp(w.mpBegin);
    mbInit = ApplyLocaleId(tmp);
  } else if (cmd->FindSwitch(L"l", 0, &w, 0) != -1) {
    mbInit = SetFromMatch(w);
  } else if (GetRegistryLocale(L"HKEY_LOCAL_MACHINE\\Software\\Electronic Arts\\SPORE\\Locale", &w)) {
    FixedString16 tmp(w.mpBegin);
    mbInit = ApplyLocaleId(tmp);
  }

  if (!mbInit) {
    if (EA::Locale::SetLocale(&g_localeState, 0, 0)) {
      wchar_t buf[0x80];
      if (EA::Locale::GetLocaleInfoString(2, 0, buf, 0x80, &g_localeState) != -1) {
        FixedString16 tmp(buf);
        mbInit = ApplyLocaleId(tmp);
      }
    }
  }
  if (!mbInit) {
    FixedString16 tmp(L"en-gb");
    mbInit = ApplyLocaleId(tmp);
  }
  return mbInit;
}

// @ 0x006968f0
bool cLocaleManager::SetFromMatch(const eastl::WStr& id) {
  int best = 0;
  int bestScore = 0;
  for (int i = 0; i < 24; ++i) {
    int score = LocaleCommonPrefix(id.mpBegin, g_localeTable[i].mName);
    if (score > bestScore) {
      best = i;
      bestScore = score;
    }
  }
  FixedString16 code(g_localeTable[best].mCode);
  return ApplyLocaleId(code);
}

// @ 0x006969b0
const wchar_t* cLocaleManager::FindMatchingLocale() {
  for (int i = 0; i < 24; ++i) {
    bool matched;
    {
      FixedString16 code(g_localeTable[i].mCode);
      matched = FUN_0087fd10((int*)&mLocaleId, (int*)&code, 1);
    }
    if (matched) return g_localeTable[i].mName;
  }
  return 0;
}

// @ 0x00696a60
bool cLocaleManager::GetDefaultLanguage(const FixedString16& locale) {
  bool matched;
  {
    FixedString16 tmp(L"en-us");
    matched = FUN_0087fd10((int*)&locale, (int*)&tmp, 1);
  }
  if (matched) return true;

  eastl::WStr path;
  path.mpBegin = path.mpEnd = gEmptyString16;
  path.mpCapacity = gEmptyString16 + 1;
  if (!GetDirString(0x6cbed3a, &path, 0)) {
    if (!GetDirString(0x45962cc, &path, 0)) return false;
  }

  eastl::WStr lang;
  lang.mpBegin = lang.mpEnd = gEmptyString16;
  lang.mpCapacity = gEmptyString16 + 1;

  wchar_t buf[0x80];
  if (EA::Locale::GetLocaleInfoString(2, 0, buf, 0x80, &locale) <= 0) return false;

  lang.assign(buf, buf + eastl::CharStrlenW(buf));
  path.Append(lang.mpBegin, lang.mpEnd);
  path.Append(gPathSep, gPathSep + eastl::CharStrlenW(gPathSep));
  return EA::IO::Directory::Exists(path.mpBegin);
}

}  // namespace SP

namespace SP {

// An 8-byte broadcast message: a base/derived vtable pair with the copied list head attached.
class LocaleBroadcastBase {
 public:
  virtual ~LocaleBroadcastBase() {}
};
class LocaleBroadcastMessage : public LocaleBroadcastBase {
 public:
  List16* mList;    // +4
};

// vtable +0x34 of the resource manager takes the target list and the message.
struct ILocaleBroadcastTarget {
  virtual void* v00(); virtual void* v04(); virtual void* v08(); virtual void* v0c();
  virtual void* v10(); virtual void* v14(); virtual void* v18(); virtual void* v1c();
  virtual void* v20(); virtual void* v24(); virtual void* v28(); virtual void* v2c();
  virtual void* v30();
  virtual int   Dispatch(void* list, LocaleBroadcastMessage* msg);   // +0x34
};

// @ 0x006960f0
int __stdcall BroadcastLocaleChange(const wchar_t* name, List16* list) {
  (void)name;
  if (GetManager() == 0) return 0;

  List16 head;
  head.mAlloc = EA::Allocator::ICoreAllocator::GetDefaultAllocator();
  head.mZero = 0;
  head.mNext = &head;
  head.mPrev = &head;
  for (LocaleNode* n = (LocaleNode*)list->mNext; n != (LocaleNode*)list; n = n->mNext) {
    LocaleNode* node = (LocaleNode*)head.mAlloc->Allocate(0xc, 0, head.mZero);
    node->mValue = n->mValue;
    node->mNext = (LocaleNode*)&head;
    node->mPrev = (LocaleNode*)head.mPrev;
    ((LocaleNode*)head.mPrev)->mNext = node;
    head.mPrev = node;
  }

  int result;
  {
    LocaleBroadcastMessage msg;
    msg.mList = &head;
    result = ((ILocaleBroadcastTarget*)GetManager())->Dispatch(list, &msg);
  }
  for (LocaleNode* n = (LocaleNode*)head.mNext; n != (LocaleNode*)&head; ) {
    LocaleNode* next = n->mNext;
    head.mAlloc->Free(n, 0xc);
    n = next;
  }
  return result;
}

}  // namespace SP
