// Created on: 2006-04-13
// Created by: Andrey BETENEV
// Copyright (c) 2006-2014 OPEN CASCADE SAS
//
// This file is part of Open CASCADE Technology software library.
//
// This library is free software; you can redistribute it and/or modify it under
// the terms of the GNU Lesser General Public License version 2.1 as published
// by the Free Software Foundation, with special exception defined in the file
// OCCT_LGPL_EXCEPTION.txt. Consult the file LICENSE_LGPL_21.txt included in OCCT
// distribution for complete text of the license and disclaimer of any warranty.
//
// Alternatively, this file may be used under the terms of Open CASCADE
// commercial license or contractual agreement.

// On Windows, function TryEnterCriticalSection has appeared in Windows NT
// and is surrounded by #ifdef in MS VC++ 7.1 headers.
// Thus to use it we need to define appropriate macro saying that we wil
// run on Windows NT 4.0 at least
#if ((defined(_WIN32) || defined(__WIN32__)) && !defined(_WIN32_WINNT))
  #define _WIN32_WINNT 0x0400
#endif

#include <Standard_Mutex.hxx>
#include <Standard_OStream.hxx>

//=============================================
// Standard_Mutex::Standard_Mutex
//=============================================

Standard_Mutex::Standard_Mutex () 
{
#if (defined(_WIN32) || defined(__WIN32__))
  InitializeCriticalSection (&myMutex);
#elif defined (__APPLE__)
    myMutex = dispatch_semaphore_create(0);
    myCount = 0;
#else
  pthread_mutexattr_t anAttr;
  pthread_mutexattr_init (&anAttr);
  pthread_mutexattr_settype (&anAttr, PTHREAD_MUTEX_RECURSIVE);
  pthread_mutex_init (&myMutex, &anAttr);
  pthread_mutexattr_destroy (&anAttr);
#endif
}

//=============================================
// Standard_Mutex::~Standard_Mutex
//=============================================

Standard_Mutex::~Standard_Mutex () 
{
#if (defined(_WIN32) || defined(__WIN32__))
  DeleteCriticalSection (&myMutex);
#elif defined (__APPLE__)
    dispatch_release(myMutex);
#else
  pthread_mutex_destroy (&myMutex);
#endif
}

//=============================================
// Standard_Mutex::Lock
//=============================================

void Standard_Mutex::Lock ()
{
#if (defined(_WIN32) || defined(__WIN32__))
  EnterCriticalSection (&myMutex);
#elif defined (__APPLE__)
    for (unsigned spins = 0; spins != 5000; ++spins)
    {
        if (OSAtomicCompareAndSwap32Barrier(0, 1, &myCount))
            return;

        sched_yield();
    }
    if (OSAtomicIncrement32Barrier(&myCount) > 1) // if (++count > 1)
        dispatch_semaphore_wait(myMutex, DISPATCH_TIME_FOREVER);
#else
  pthread_mutex_lock (&myMutex);
#endif
}

//=============================================
// Standard_Mutex::TryLock
//=============================================

Standard_Boolean Standard_Mutex::TryLock ()
{
#if (defined(_WIN32) || defined(__WIN32__))
  return (TryEnterCriticalSection (&myMutex) != 0);
#elif defined(__APPLE__)
    if (OSAtomicIncrement32Barrier(&myCount) > 1) // if (++count > 1)
        return dispatch_semaphore_wait(myMutex, DISPATCH_TIME_NOW) == 0;
    else
        return false;
#else
  return (pthread_mutex_trylock (&myMutex) != EBUSY);
#endif
}

//=============================================
// Standard_Mutex::DestroyCallback
//=============================================

void Standard_Mutex::DestroyCallback ()
{
  UnregisterCallback();
  Unlock();
}
