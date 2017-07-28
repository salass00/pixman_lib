/* Pixman uses some non-standard compiler features. This file ensures
 * they exist
 *
 * The features are:
 *
 *    FUNC	     must be defined to expand to the current function
 *    PIXMAN_EXPORT  should be defined to whatever is required to
 *                   export functions from a shared library
 *    limits	     limits for various types must be defined
 *    inline         must be defined
 *    force_inline   must be defined
 */
#ifdef __amigaos4__
# undef SIZE_MAX
#endif

#if defined (__GNUC__)
#  define FUNC     ((const char*) (__PRETTY_FUNCTION__))
#elif defined (__sun) || (defined (__STDC_VERSION__) && __STDC_VERSION__ >= 199901L)
#  define FUNC     ((const char*) (__func__))
#else
#  define FUNC     ((const char*) ("???"))
#endif

#if defined (__GNUC__)
#  define unlikely(expr) __builtin_expect ((expr), 0)
#else
#  define unlikely(expr)  (expr)
#endif

#if defined (__GNUC__)
#  define MAYBE_UNUSED  __attribute__((unused))
#else
#  define MAYBE_UNUSED
#endif

#ifndef INT16_MIN
# define INT16_MIN              (-32767-1)
#endif

#ifndef INT16_MAX
# define INT16_MAX              (32767)
#endif

#ifndef INT32_MIN
# define INT32_MIN              (-2147483647-1)
#endif

#ifndef INT32_MAX
# define INT32_MAX              (2147483647)
#endif

#ifndef UINT32_MIN
# define UINT32_MIN             (0)
#endif

#ifndef UINT32_MAX
# define UINT32_MAX             (4294967295U)
#endif

#ifndef INT64_MIN
# define INT64_MIN              (-9223372036854775807-1)
#endif

#ifndef INT64_MAX
# define INT64_MAX              (9223372036854775807)
#endif

#ifndef SIZE_MAX
# define SIZE_MAX               ((size_t)-1)
#endif


#ifndef M_PI
# define M_PI			3.14159265358979323846
#endif

#ifdef _MSC_VER
/* 'inline' is available only in C++ in MSVC */
#   define inline __inline
#   define force_inline __forceinline
#   define noinline __declspec(noinline)
#elif defined __GNUC__ || (defined(__SUNPRO_C) && (__SUNPRO_C >= 0x590))
#   define inline __inline__
#   define force_inline __inline__ __attribute__ ((__always_inline__))
#   define noinline __attribute__((noinline))
#else
#   ifndef force_inline
#      define force_inline inline
#   endif
#   ifndef noinline
#      define noinline
#   endif
#endif

/* GCC visibility */
#if defined(__GNUC__) && __GNUC__ >= 4 && !defined(_WIN32)
#   define PIXMAN_EXPORT __attribute__ ((visibility("default")))
/* Sun Studio 8 visibility */
#elif defined(__SUNPRO_C) && (__SUNPRO_C >= 0x550)
#   define PIXMAN_EXPORT __global
#else
#   define PIXMAN_EXPORT
#endif

/* member offsets */
#define CONTAINER_OF(type, member, data)				\
    ((type *)(((uint8_t *)data) - offsetof (type, member)))

/* TLS */
#if defined(PIXMAN_NO_TLS)

#   define PIXMAN_DEFINE_THREAD_LOCAL(type, name)			\
    static type name
#   define PIXMAN_GET_THREAD_LOCAL(name)				\
    (&name)

#elif defined(__amigaos4__)

#   include <proto/exec.h>

#   define PIXMAN_DEFINE_THREAD_LOCAL(type, name) \
    static const char tls_ ## name ## _id [] = #name; \
     \
    static type * \
    tls_ ## name ## _alloc (void) \
    { \
        struct Task *me = IExec->FindTask(NULL); \
        struct MemList ML, *mlist; \
        type *result = NULL; \
         \
        ML.ml_NumEntries = 1; \
        ML.ml_ME[0].me_Reqs = MEMF_PRIVATE | MEMF_CLEAR; \
		ML.ml_ME[0].me_Length = sizeof(type); \
         \
        mlist = IExec->AllocTaskMemEntry(&ML); \
        if (mlist) \
        { \
            mlist->ml_Node.ln_Name = tls_ ## name ## _id; \
            IExec->AddHead(&me->tc_MemEntry, &mlist->ml_Node); \
            result = mlist->ml_ME[0].me_Addr; \
        } \
         \
        return result; \
    } \
     \
    static type * \
    tls_ ## name ## _get (void) \
    { \
        struct Task *me = IExec->FindTask(NULL); \
        struct Node *node; \
        struct MemList *mlist; \
        type *result = NULL; \
         \
        for (node = me->tc_MemEntry.lh_Head; node->ln_Succ; node = node->ln_Succ) \
        { \
            mlist = (struct MemList *)node; \
            if (mlist->ml_Node.ln_Name == tls_ ## name ## _id && \
                mlist->ml_NumEntries == 1 && \
                mlist->ml_ME[0].me_Length == sizeof(type)) \
            { \
                result = mlist->ml_ME[0].me_Addr; \
            } \
        } \
         \
        if (!result) \
            result = tls_ ## name ## _alloc(); \
         \
        return result; \
    }

#   define PIXMAN_GET_THREAD_LOCAL(name) \
    tls_ ## name ## _get ()

#elif defined(TLS)

#   define PIXMAN_DEFINE_THREAD_LOCAL(type, name)			\
    static TLS type name
#   define PIXMAN_GET_THREAD_LOCAL(name)				\
    (&name)

#elif defined(__MINGW32__)

#   define _NO_W32_PSEUDO_MODIFIERS
#   include <windows.h>

#   define PIXMAN_DEFINE_THREAD_LOCAL(type, name)			\
    static volatile int tls_ ## name ## _initialized = 0;		\
    static void *tls_ ## name ## _mutex = NULL;				\
    static unsigned tls_ ## name ## _index;				\
									\
    static type *							\
    tls_ ## name ## _alloc (void)					\
    {									\
        type *value = calloc (1, sizeof (type));			\
        if (value)							\
            TlsSetValue (tls_ ## name ## _index, value);		\
        return value;							\
    }									\
									\
    static force_inline type *						\
    tls_ ## name ## _get (void)						\
    {									\
	type *value;							\
	if (!tls_ ## name ## _initialized)				\
	{								\
	    if (!tls_ ## name ## _mutex)				\
	    {								\
		void *mutex = CreateMutexA (NULL, 0, NULL);		\
		if (InterlockedCompareExchangePointer (			\
			&tls_ ## name ## _mutex, mutex, NULL) != NULL)	\
		{							\
		    CloseHandle (mutex);				\
		}							\
	    }								\
	    WaitForSingleObject (tls_ ## name ## _mutex, 0xFFFFFFFF);	\
	    if (!tls_ ## name ## _initialized)				\
	    {								\
		tls_ ## name ## _index = TlsAlloc ();			\
		tls_ ## name ## _initialized = 1;			\
	    }								\
	    ReleaseMutex (tls_ ## name ## _mutex);			\
	}								\
	if (tls_ ## name ## _index == 0xFFFFFFFF)			\
	    return NULL;						\
	value = TlsGetValue (tls_ ## name ## _index);			\
	if (!value)							\
	    value = tls_ ## name ## _alloc ();				\
	return value;							\
    }

#   define PIXMAN_GET_THREAD_LOCAL(name)				\
    tls_ ## name ## _get ()

#elif defined(_MSC_VER)

#   define PIXMAN_DEFINE_THREAD_LOCAL(type, name)			\
    static __declspec(thread) type name
#   define PIXMAN_GET_THREAD_LOCAL(name)				\
    (&name)

#elif defined(HAVE_PTHREADS)

#include <pthread.h>

#  define PIXMAN_DEFINE_THREAD_LOCAL(type, name)			\
    static pthread_once_t tls_ ## name ## _once_control = PTHREAD_ONCE_INIT; \
    static pthread_key_t tls_ ## name ## _key;				\
									\
    static void								\
    tls_ ## name ## _destroy_value (void *value)			\
    {									\
	free (value);							\
    }									\
									\
    static void								\
    tls_ ## name ## _make_key (void)					\
    {									\
	pthread_key_create (&tls_ ## name ## _key,			\
			    tls_ ## name ## _destroy_value);		\
    }									\
									\
    static type *							\
    tls_ ## name ## _alloc (void)					\
    {									\
	type *value = calloc (1, sizeof (type));			\
	if (value)							\
	    pthread_setspecific (tls_ ## name ## _key, value);		\
	return value;							\
    }									\
									\
    static force_inline type *						\
    tls_ ## name ## _get (void)						\
    {									\
	type *value = NULL;						\
	if (pthread_once (&tls_ ## name ## _once_control,		\
			  tls_ ## name ## _make_key) == 0)		\
	{								\
	    value = pthread_getspecific (tls_ ## name ## _key);		\
	    if (!value)							\
		value = tls_ ## name ## _alloc ();			\
	}								\
	return value;							\
    }

#   define PIXMAN_GET_THREAD_LOCAL(name)				\
    tls_ ## name ## _get ()

#else

#    error "Unknown thread local support for this system. Pixman will not work with multiple threads. Define PIXMAN_NO_TLS to acknowledge and accept this limitation and compile pixman without thread-safety support."

#endif