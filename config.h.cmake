/* use posix api */
#define _POSIX_C_SOURCE 200809L

/* Maximum host name length */
#define HOST_NAME_MAX 64

/* Maximum input line length */
#define LINE_MAX 2048

/* Define to 1 if translation of program messages to the user's native
   language is requested. */
#cmakedefine ENABLE_NLS @ENABLE_NLS@

/* Define if SELinux is available */
#cmakedefine HAVE_SELINUX @HAVE_SELINUX@

/* Define the location where the catalogs will be installed */
#cmakedefine LOCALEDIR "@LOCALEDIR@"
#define N_(str) str
#ifdef ENABLE_NLS
#include <libintl.h>
#define _(str) gettext(str)
#elif
#define _(str) (str)
#endif


/* Define to the full name of this package. */
#cmakedefine PACKAGE_NAME "@PACKAGE_NAME@"