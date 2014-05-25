/* Version defines */

#ifndef _VERS_ID
#define _VERS_ID

#define __stringize2(X)	#X
#define __stringize(X)	__stringize2(X)

#define RH_VERSION "1.2.6" // CED

#define D2XMAJOR __stringize(DXX_VERSION_MAJORi)
#define D2XMINOR __stringize(DXX_VERSION_MINORi)
#define D2XMICRO __stringize(DXX_VERSION_MICROi)

#define BASED_VERSION "Full Version v1.2"
#define VERSION D2XMAJOR "." D2XMINOR "." D2XMICRO
#define DESCENT_VERSION "D2X-Rebirth v" VERSION " -- Retro Mod " RH_VERSION  

extern const char g_descent_version[40];
extern const char g_descent_build_datetime[21];

#endif /* _VERS_ID */
