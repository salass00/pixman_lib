#ifndef PROTO_PIXMAN_H
#define PROTO_PIXMAN_H

/****************************************************************************/

#ifndef __NOLIBBASE__
 extern struct Library * PixmanBase;
#endif

/****************************************************************************/

#ifdef __amigaos4__
 #include <interfaces/pixman.h>
 #ifdef __USE_INLINE__
  #include <inline4/pixman.h>
 #endif /* __USE_INLINE__ */
 #ifndef CLIB_PIXMAN_PROTOS_H
  #define CLIB_PIXMAN_PROTOS_H 1
 #endif /* CLIB_PIXMAN_PROTOS_H */
 #ifndef __NOGLOBALIFACE__
  extern struct PixmanIFace *IPixman;
 #endif /* __NOGLOBALIFACE__ */
#else /* __amigaos4__ */
 #ifndef CLIB_PIXMAN_PROTOS_H
  #include <clib/pixman_protos.h>
 #endif /* CLIB_PIXMAN_PROTOS_H */
 #if defined(__GNUC__)
  #ifndef __PPC__
   #include <inline/pixman.h>
  #else
   #include <ppcinline/pixman.h>
  #endif /* __PPC__ */
 #elif defined(__VBCC__)
  #ifndef __PPC__
   #include <inline/pixman_protos.h>
  #endif /* __PPC__ */
 #else
  #include <pragmas/pixman_pragmas.h>
 #endif /* __GNUC__ */
#endif /* __amigaos4__ */

/****************************************************************************/

#endif /* PROTO_PIXMAN_H */
