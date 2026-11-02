// src/game/SPAudio/eapdclock.cpp -- migrated from slice(s) s00a488d0 by tools/migrate/rewrite.py
// Object file: SPAudio/eapdclock.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// ---- items of slice s00a488d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Audio {
namespace Eapd {
struct t_clock {
    double   c_settime;   // +0
    int      c_set;       // +8
    void*    c_owner;     // +0xc
    void*    c_method;    // +0x10
    t_clock* c_next;      // +0x14
};
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern t_clock*    s_clocklist;     // 0x1675410
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern double      s_time;          // 0x1675420
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
extern const double s_ctime;        // 0x1454410  (clock_new's initial c_settime constant)
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void* getbytes(int n, const char* tag);                                        // 0xa49610
}
}
}
namespace EA {
namespace Audio {
namespace Eapd {
void  freebytes(void* p, int n);                                               // 0xa49650
}
}
}
// ---- items of slice s00a488d0 end

// @ 0x00a49080
namespace EA { namespace Audio { namespace Eapd {
t_clock* clock_new(void* owner, void* fn)
{
    t_clock* c = (t_clock*)getbytes(0x18, "clock");
    c->c_settime = s_ctime;
    c->c_set = 0;
    c->c_owner = owner;
    c->c_method = fn;
    c->c_next = 0;
    return c;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a490b0
namespace EA { namespace Audio { namespace Eapd {
void clock_unset(t_clock* c)
{
    if (c->c_set == 1) {
        t_clock* o = s_clocklist;
        if (c == o) {
            s_clocklist = c->c_next;
            c->c_set = 0;
            return;
        }
        while (o->c_next != c)
            o = o->c_next;
        o->c_next = c->c_next;
    }
    c->c_set = 0;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a490f0
namespace EA { namespace Audio { namespace Eapd {
void clock_set(t_clock* c, double systime)
{
    if (c->c_set == 1)
        clock_unset(c);
    double t = (s_time > systime) ? s_time : systime;
    c->c_settime = t;
    t_clock* cl = s_clocklist;
    if (cl == 0 || t < cl->c_settime) {
        c->c_next = cl;
        s_clocklist = c;
        c->c_set = 1;
    } else {
        t_clock* o = cl;
        t_clock* n = cl->c_next;
        while (n && n->c_settime <= t) {
            o = n;
            n = n->c_next;
        }
        o->c_next = c;
        c->c_set = 1;
        c->c_next = n;
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a49170
namespace EA { namespace Audio { namespace Eapd {
void clock_pause(t_clock* c)
{
    if (c->c_set == 1) {
        double t = c->c_settime - s_time;
        clock_unset(c);
        c->c_set = 2;
        c->c_settime = t;
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a491a0
namespace EA { namespace Audio { namespace Eapd {
void clock_unpause(t_clock* c)
{
    if (c->c_set == 2) {
        double t = c->c_settime + s_time;
        c->c_set = 0;
        clock_set(c, t);
    }
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a491d0
namespace EA { namespace Audio { namespace Eapd {
bool clock_ispaused(t_clock* c)
{
    return c->c_set == 2;
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a491e0
namespace EA { namespace Audio { namespace Eapd {
void clock_delay(t_clock* c, float delay)
{
    clock_set(c, (double)(delay * (float)0.001f) + s_time);
}
}}}  // namespace EA::Audio::Eapd

// @ 0x00a49210
namespace EA {
namespace Audio {
namespace Eapd {
double clock_getlogicaltime()
{
    return s_time;
}
}
}
}  // namespace EA::Audio::Eapd

// @ 0x00a49220
namespace EA {
namespace Audio {
namespace Eapd {
double clock_gettimesince(double systime)
{
    return (s_time - systime) * *(const double*)0x01454428;
}
}
}
}  // namespace EA::Audio::Eapd

// @ 0x00a49240
namespace EA {
namespace Audio {
namespace Eapd {
double clock_getlogicaltimeafter(float delay)
{
    return (double)delay * (float)0.001f + s_time;
}
}
}
}  // namespace EA::Audio::Eapd

// @ 0x00a49260
namespace EA { namespace Audio { namespace Eapd {
void clock_free(t_clock* c)
{
    if (c->c_set == 1) {
        t_clock* o = s_clocklist;
        if (c == o) {
            s_clocklist = c->c_next;
            c->c_set = 0;
            freebytes(c, 0x18);
            return;
        }
        while (o->c_next != c)
            o = o->c_next;
        o->c_next = c->c_next;
    }
    c->c_set = 0;
    freebytes(c, 0x18);
}
}}}  // namespace EA::Audio::Eapd
