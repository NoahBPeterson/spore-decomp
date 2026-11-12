#pragma once
// Minimal EAThread atomics for the retail EAText EATEXT_THREAD_SAFETY_ENABLED build.
#ifndef EATHREAD_EATHREAD_ATOMIC_H
#define EATHREAD_EATHREAD_ATOMIC_H

#include <EABase/eabase.h>
#include <windows.h>
#include <intrin.h>

namespace EA
{
    namespace Thread
    {
        class AtomicInt32
        {
        public:
            AtomicInt32() {}
            AtomicInt32(int n) : mValue(n) {}

            void SetValue(int n)       { InterlockedExchange(reinterpret_cast<volatile LONG*>(&mValue), n); }
            int GetValue() const       { return mValue; }
            bool SetValueConditional(int nExpectedValue, int nNewValue)
            {
                return InterlockedCompareExchange(reinterpret_cast<volatile LONG*>(&mValue), nNewValue, nExpectedValue) == nExpectedValue;
            }

            int Increment()            { return InterlockedIncrement(reinterpret_cast<volatile LONG*>(&mValue)); }
            int Decrement()            { return InterlockedDecrement(reinterpret_cast<volatile LONG*>(&mValue)); }
            int Add(int n)  { return InterlockedExchangeAdd(reinterpret_cast<volatile LONG*>(&mValue), n) + n; }

            int operator++()           { return InterlockedIncrement(reinterpret_cast<volatile LONG*>(&mValue)); }
            int operator--()           { return InterlockedDecrement(reinterpret_cast<volatile LONG*>(&mValue)); }
            int operator++(int)        { return InterlockedIncrement(reinterpret_cast<volatile LONG*>(&mValue)) - 1; }
            int operator--(int)        { return InterlockedDecrement(reinterpret_cast<volatile LONG*>(&mValue)) - 1; }
            int operator=(int n) { InterlockedExchange(reinterpret_cast<volatile LONG*>(&mValue), n); return n; }
            int operator+=(int n) { return Add(n); }
            int operator-=(int n) { return Add(-n); }
            operator int() const       { return mValue; }

            int mValue;
        };

    } // namespace Thread
} // namespace EA

#endif // EATHREAD_EATHREAD_ATOMIC_H
