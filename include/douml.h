/*	
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#ifndef DU_DOUML_H
#define DU_DOUML_H

#ifdef _MSC_VER
    #ifdef DU_STATIC
        #define DU_API
    #elif defined DU_EXPORT
        #define DU_API __declspec(dllexport)
    #else
        #define DU_API __declspec(dllimport)
    #endif
#else
    #define DU_API
#endif

/* basic types */
typedef int    du_int;
typedef double du_float;
typedef char   du_char;
typedef wchar_t  du_unicode;

#ifdef _MSC_VER
    #ifndef _WIN32_WINNT
        #define _WIN32_WINNT _WIN32_WINNT_MAXVER
    #endif

    /*only for new and delete
     if want malloc and free 
     #define _CRTDBG_MAP_ALLOC
        #include <stdlib.h>
        #include <crtdbg.h>
     */
    #include <afxwin.h>
    
    #ifdef _DEBUG
        #define _CRTDBG_MAP_ALLOC
        #include <stdlib.h>
        #include <crtdbg.h>
    #endif
    
    #ifdef _DEBUG
        #define new DEBUG_NEW
    #endif
#endif

#endif
