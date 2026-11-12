#pragma once
// Minimal EAThread Futex/AutoFutex for the retail EAText EATEXT_THREAD_SAFETY_ENABLED build.
// The retail SporeApp links the 2010 EAThread, whose Win32 Futex is a bare CRITICAL_SECTION and
// whose AutoFutex Lock/Unlock inline to EnterCriticalSection/LeaveCriticalSection.  Re-declaring
// that here keeps the retail class layout and the exact mutex call sequence used by the EAText
// StyleManager (EATextStyle.cpp).
#ifndef EATHREAD_EATHREAD_FUTEX_H
#define EATHREAD_EATHREAD_FUTEX_H

#include <EABase/eabase.h>
#include <windows.h>

namespace EA
{
    namespace Thread
    {
        class Futex
        {
        public:
            Futex()
            {
                InitializeCriticalSection(&mFutex);
            }

            ~Futex()
            {
                DeleteCriticalSection(&mFutex);
            }

            void Lock()
            {
                EnterCriticalSection(&mFutex);
            }

            void Unlock()
            {
                LeaveCriticalSection(&mFutex);
            }

            bool LockTry()
            {
                return TryEnterCriticalSection(&mFutex) != 0;
            }

            CRITICAL_SECTION mFutex;
        };


        class AutoFutex
        {
        public:
            AutoFutex(Futex& futex) : mFutex(futex)
            {
                mFutex.Lock();
            }

            ~AutoFutex()
            {
                mFutex.Unlock();
            }

        private:
            Futex& mFutex;
        };

    } // namespace Thread
} // namespace EA

#endif // EATHREAD_EATHREAD_FUTEX_H
