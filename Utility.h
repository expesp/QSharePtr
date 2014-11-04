/*@version $Id: Utility.h 305 2011-11-25 09:01:32Z zhangxin $*/

#ifndef UTILITY_H
#define UTILITY_H
#include "Common.h"

#ifdef __GNUG__
#include <execinfo.h>
#include <sstream>
#endif

#include <vector>

using namespace std;


#ifdef _MSC_VER
#pragma warning (disable: 4251 4996 4290 4101)

#ifndef EXPORT_UTILITY_DLL
#define UTILITY_DLL_CLASS _declspec(dllimport)
#define UTILITY_DLL_INTERFACE _declspec(dllimport)
#else 
#define UTILITY_DLL_CLASS _declspec(dllexport)
#define UTILITY_DLL_INTERFACE _declspec(dllexport)
#endif
#else  //It is __GNUG__
#define UTILITY_DLL_CLASS
#define UTILITY_DLL_INTERFACE
#endif

#undef FUANDA_DISALLOW_EVIL_CONSTRUCTORS
#define FUANDA_DISALLOW_EVIL_CONSTRUCTORS(TypeName)		\
	TypeName(const TypeName&);							\
	void operator=(const TypeName&)

#define Enter Enter_fun(__FUNCTION__)
#define Leave Leave_fun(__FUNCTION__)

#ifdef WIN32
#include <float.h>

#define is_nan(x) _isnan(x)

#ifndef NAN
static const unsigned long __nan[2] = {0xffffffff, 0x7fffffff};
#define NAN (*(const double *) __nan)
#endif

#elif defined __GNUG__
#include <math.h>
#define is_nan(x) isnan(x)
#endif


namespace Q_COMMON{

	void UTILITY_DLL_INTERFACE print_stacktrace();
	void UTILITY_DLL_INTERFACE Enter_fun(const char *name);
	void UTILITY_DLL_INTERFACE Leave_fun(const char *name);  
    

    class QCMutex{
    public:
        QCMutex() {QMUTEX_CREATE(&mutext_);};
        ~QCMutex() {QMUTEX_DESTROY(&mutext_);};
        void lock() {QMUTEX_LOCK(&mutext_);};
        void unlock(){QMUTEX_UNLOCK(&mutext_);} ;
    private:
        QMUTEX mutext_;
    };  
}

#endif

