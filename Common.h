
#ifndef INCLUDE_H
#define INCLUDE_H

#define USING_DOUBLE                    // elements of type double
//#define USING_FLOAT                   // elements of type float                  

//*********************** end of options set by user ********************

// for Gnu C++ version 3
#if defined __GNUG__ && __GNUG__ >= 3
   #define _STANDARD_                   // use standard library
   #define ios_format_flags ios::fmtflags
#endif

// for Intel C++ for Linux
#if defined __ICC
   #define _STANDARD_                   // use standard library
   #define ios_format_flags ios::fmtflags
#endif

// for Microsoft Visual C++ 7 and above (and Intel simulating these)
#if defined _MSC_VER && _MSC_VER >= 1300
   #define _STANDARD_                   // use standard library
#endif


#ifdef _STANDARD_                       // using standard library
   #include <cstdlib>
   #if defined _MSC_VER && _MSC_VER == 1200
      #include <limits>              // for VC++6
   #endif

   #ifdef WANT_STREAM
      #include <iostream>
      #include <iomanip>	  
   #endif

   #ifdef WANT_SSTREAM
   #include <sstream>
   #endif

   #ifdef WANT_MATH
      #include <cmath>
   #endif

   #ifdef WANT_STRING
      #include <cstring>
	  #include <iomanip>
   #endif

   #ifdef WANT_TIME
      #include <ctime>
   #endif

   #ifdef WANT_FSTREAM
      #include <fstream>
   #endif

   using namespace std;
#endif                                  // _STANDARD_

#if defined __GNUG__
#define _Q_Linux
#else
#if defined _MSC_VER
#define _Q_WIN
#endif
#endif


#if defined _Q_WIN
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
typedef CRITICAL_SECTION QMUTEX;
#define QMUTEX_CREATE(mutex_ptr) InitializeCriticalSection(mutex_ptr)
#define QMUTEX_DESTROY(mutex_ptr) DeleteCriticalSection(mutex_ptr)
#define QMUTEX_LOCK(mutex_ptr) EnterCriticalSection(mutex_ptr)
#define QMUTEX_UNLOCK(mutex_ptr) LeaveCriticalSection(mutex_ptr)

#define q_sleep(milliseconds) Sleep(milliseconds)

#define get_th_id() GetCurrentThreadId()

#elif defined _Q_Linux
#include <pthread.h>
#include <semaphore.h>
#include <sys/syscall.h>
   typedef pthread_mutex_t QMUTEX;
#define QMUTEX_CREATE(mutex_ptr) pthread_mutex_init(mutex_ptr,0) 
#define QMUTEX_DESTROY(mutex_ptr) pthread_mutex_destroy(mutex_ptr)
#define QMUTEX_LOCK(mutex_ptr) pthread_mutex_lock(mutex_ptr)
#define QMUTEX_UNLOCK(mutex_ptr) pthread_mutex_unlock(mutex_ptr)

#define q_sleep(milliseconds) usleep(milliseconds*1000)

#define get_th_id() syscall(SYS_gettid)
#elif defined _QDEF_UNIX

#endif


#if defined(_WIN32) || defined(_WIN64)
#include <math.h>
#define fmax max
#define fmin min
#define fabs abs
#endif
/******************************************************/
// definition of market location

#define LOC_CN "CN"                     // China exchange market
//#define LOC_JP "JP"
//#define LOC_HK "HK"
#define LOC_OTH "99"                    // Other market


#ifndef DefaultLOC
#define DefaultLOC LOC_CN
#endif

/******************************************************/

#endif

