/**
 * This file has no copyright assigned and is placed in the Public Domain.
 * This file is part of the w64 mingw-runtime package.
 * No warranty is given; refer to the file DISCLAIMER within this package.
 */
#ifndef _INC_CUSTCNTL
#define _INC_CUSTCNTL

#ifdef __cplusplus
extern "C" {
#endif

#define CCHCCCLASS 32
#define CCHCCDESC 32
#define CCHCCTEXT 256

  typedef struct tagCCSTYLEA {
    DWORD flStyle;
    DWORD flExtStyle;
    CHAR szText[CCHCCTEXT];
    LANGID lgid;
    WORD wReserved1;
  } CCSTYLEA,*LPCCSTYLEA;

  typedef struct tagCCSTYLEW {
    DWORD flStyle;
    DWORD flExtStyle;
    WCHAR szText[CCHCCTEXT];
    LANGID lgid;
    WORD wReserved1;
  } CCSTYLEW,*LPCCSTYLEW;

#ifdef UNICODE
#define CCSTYLE CCSTYLEW
#define LPCCSTYLE LPCCSTYLEW
#define LPFNCCSTYLE LPFNCCSTYLEW
#define LPFNCCSIZETOTEXT LPFNCCSIZETOTEXTW
#define CCSTYLEFLAG CCSTYLEFLAGW
#define LPCCSTYLEFLAG LPCCSTYLEFLAGW
#define CCINFO CCINFOW
#define LPCCINFO LPCCINFOW
#define LPFNCCINFO LPFNCCINFOW
#else
#define CCSTYLE CCSTYLEA
#define LPCCSTYLE LPCCSTYLEA
#define LPFNCCSTYLE LPFNCCSTYLEA
#define LPFNCCSIZETOTEXT LPFNCCSIZETOTEXTA
#define CCSTYLEFLAG CCSTYLEFLAGA
#define LPCCSTYLEFLAG LPCCSTYLEFLAGA
#define CCINFO CCINFOA
#define LPCCINFO LPCCINFOA
#define LPFNCCINFO LPFNCCINFOA
#endif

  typedef WINBOOL (CALLBACK *LPFNCCSTYLEA)(HWND hwndParent,LPCCSTYLEA pccs);
  typedef WINBOOL (CALLBACK *LPFNCCSTYLEW)(HWND hwndParent,LPCCSTYLEW pccs);
  typedef INT (CALLBACK *LPFNCCSIZETOTEXTA)(DWORD flStyle,DWORD flExtStyle,HFONT hfont,LPSTR pszText);
  typedef INT (CALLBACK *LPFNCCSIZETOTEXTW)(DWORD flStyle,DWORD flExtStyle,HFONT hfont,LPWSTR pszText);

  typedef struct tagCCSTYLEFLAGA {
    DWORD flStyle;
    DWORD flStyleMask;
    LPSTR pszStyle;
  } CCSTYLEFLAGA,*LPCCSTYLEFLAGA;

  typedef struct tagCCSTYLEFLAGW {
    DWORD flStyle;
    DWORD flStyleMask;
    LPWSTR pszStyle;
  } CCSTYLEFLAGW,*LPCCSTYLEFLAGW;

#define CCF_NOTEXT 0x00000001

  typedef struct tagCCINFOA {
    CHAR szClass[CCHCCCLASS];
    DWORD flOptions;
    CHAR szDesc[CCHCCDESC];
    UINT cxDefault;
    UINT cyDefault;
    DWORD flStyleDefault;
    DWORD flExtStyleDefault;
    DWORD flCtrlTypeMask;
    CHAR szTextDefault[CCHCCTEXT];
    INT cStyleFlags;
    LPCCSTYLEFLAGA aStyleFlags;
    LPFNCCSTYLEA lpfnStyle;
    LPFNCCSIZETOTEXTA lpfnSizeToText;
    DWORD dwReserved1;
    DWORD dwReserved2;
  } CCINFOA,*LPCCINFOA;

  typedef struct tagCCINFOW {
    WCHAR szClass[CCHCCCLASS];
    DWORD flOptions;
    WCHAR szDesc[CCHCCDESC];
    UINT cxDefault;
    UINT cyDefault;
    DWORD flStyleDefault;
    DWORD flExtStyleDefault;
    DWORD flCtrlTypeMask;
    INT cStyleFlags;
    LPCCSTYLEFLAGW aStyleFlags;
    WCHAR szTextDefault[CCHCCTEXT];
    LPFNCCSTYLEW lpfnStyle;
    LPFNCCSIZETOTEXTW lpfnSizeToText;
    DWORD dwReserved1;
    DWORD dwReserved2;
  } CCINFOW,*LPCCINFOW;

  typedef UINT (CALLBACK *LPFNCCINFOA)(LPCCINFOA acci);
  typedef UINT (CALLBACK *LPFNCCINFOW)(LPCCINFOW acci);

#ifdef __cplusplus
}
#endif
#endif
