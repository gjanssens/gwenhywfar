# $Id$
# (c) 2002 Martin Preuss<martin@libchipcard.de>
# This function checks for libgwenhywfar

AC_DEFUN([AC_GWENHYWFAR], [
dnl searches for gwenhywfar
dnl Arguments: 
dnl   $1: major version minimum
dnl   $2: minor version minimum
dnl   $3: patchlevel version minimum
dnl   $4: build version minimum
dnl Returns: gwenhywfar_dir
dnl          gwenhywfar_bindir
dnl          gwenhywfar_libs
dnl          gwenhywfar_plugins
dnl          gwenhywfar_includes
dnl          gwenhywfar_headers
dnl          gwenhywfar_has_crypt
dnl          have_gwenhywfar

if test -z "$1"; then vma="0"; else vma="$1"; fi
if test -z "$2"; then vmi="1"; else vmi="$2"; fi
if test -z "$3"; then vpl="0"; else vpl="$3"; fi
if test -z "$4"; then vbld="0"; else vbld="$4"; fi

AC_MSG_CHECKING(if gwenhywfar support desired)
AC_ARG_ENABLE(gwenhywfar,
  [  --enable-gwenhywfar      enable gwenhywfar support (default=yes)],
  enable_gwenhywfar="$enableval",
  enable_gwenhywfar="yes")
AC_MSG_RESULT($enable_gwenhywfar)

have_gwenhywfar="no"
gwenhywfar_dir=""
gwenhywfar_plugins=""
gwenhywfar_libs=""
gwenhywfar_bindir=""
gwenhywfar_libspp=""
gwenhywfar_includes=""
gwenhywfar_has_crypt="yes"
if test "$enable_gwenhywfar" != "no"; then
  AC_MSG_CHECKING(for gwenhywfar)
  AC_ARG_WITH(gwen-dir, [  --with-gwen-dir=DIR
                            uses gwenhywfar from given dir],
    [lcc_dir="$withval"
     user_dir=yes
    ],
    [lcc_dir="${prefix} \
	     /usr/local \
             /usr \
	     /gwen \
             /sw \
             /"
     user_dir=no
    ])

  for li in $lcc_dir; do
      if test -x "$li/bin/xmlmerge"; then
          gwenhywfar_dir="$li";
          break
      fi
  done
  if test -z "$gwenhywfar_dir"; then
      AC_MSG_RESULT([not found ])
      AC_MSG_ERROR([
*** The library Gwenhywfar was not found. Obtain it from 
*** http://www.aquamaniac.de . 
*** If it is already installed (including the -devel package), 
*** you might need to specify the location with the 
*** option --with-gwen-dir=DIR.])
  else
      dnl If gwen-dir was set by user, assume gwenhywfar.pc is not in
      dnl pgk-config's default search path
      if test "x$user_dir" = "xyes"; then
          gwen_pc=$(find "$gwenhywfar_dir" -name gwenhywfar.pc)
          if test -z "$gwen_pc"; then
              AC_MSG_ERROR([
*** The directory passed via --with-gwen-dir doesn't seem to be
*** a proper gwen installation directory. It's missing the gwenhywfar.pc file.])
          else
              gwen_pc_dir=$(dirname "$gwen_pc")
              save_path="$PKG_CONFIG_PATH"
              export PKG_CONFIG_PATH="$gwen_pc_dir"
          fi
      fi
      AC_MSG_RESULT($gwenhywfar_dir)
      AC_MSG_CHECKING(for gwen libs)
      gwenhywfar_libs="`$PKG_CONFIG --libs gwenhywfar`"
      AC_MSG_RESULT($gwenhywfar_libs)
      AC_MSG_CHECKING(for gwen includes)
      gwenhywfar_includes="`$PKG_CONFIG --cflags gwenhywfar`"
      AC_MSG_RESULT($gwenhywfar_includes)
      AC_MSG_CHECKING(for gwen binary tools)
      gwenhywfar_bindir="`$PKG_CONFIG --variable=bindir gwenhywfar`"
      AC_MSG_RESULT($gwenhywfar_bindir)
      AC_MSG_CHECKING(for gwen plugins)
      gwenhywfar_plugins="`$PKG_CONFIG --variable=plugindir gwenhywfar`"
      AC_MSG_RESULT($gwenhywfar_plugins)
      AC_MSG_CHECKING(for gwen headers)
      gwenhywfar_headers="`$PKG_CONFIG --variable=headerdir gwenhywfar`"
      AC_MSG_RESULT($gwenhywfar_headers)
  fi
  AC_MSG_CHECKING(if gwenhywfar test desired)
  AC_ARG_ENABLE(gwenhywfar,
    [  --enable-gwenhywfar-test   enable gwenhywfar-test (default=yes)],
     enable_gwenhywfar_test="$enableval",
     enable_gwenhywfar_test="yes")
  AC_MSG_RESULT($enable_gwenhywfar_test)
  AC_MSG_CHECKING(for Gwenhywfar version >=$vma.$vmi.$vpl.$vbld)
  if test "$enable_gwenhywfar_test" != "no"; then
    gwen_vmajor="`$PKG_CONFIG --variable=vmajor gwenhywfar`"
    gwen_vminor="`$PKG_CONFIG --variable=vminor gwenhywfar`"
    gwen_vpatchlevel="`$PKG_CONFIG --variable=vpatchlevel gwenhywfar`"
    gwen_vstring="`$PKG_CONFIG --variable=vstring gwenhywfar`"
    gwen_vbuild="`$PKG_CONFIG --variable=vbuild gwenhywfar`"
    gwen_versionstring="$gwen_vstring.$gwen_vbuild"
    AC_MSG_RESULT([found $gwen_versionstring])
    if test "$vma" -gt "$gwen_vmajor"; then
      AC_MSG_ERROR([Your Gwenhywfar version is way too old.
      Please update from http://www.aquamaniac.de])
    elif test "$vma" = "$gwen_vmajor"; then
      if test "$vmi" -gt "$gwen_vminor"; then
        AC_MSG_ERROR([Your Gwenhywfar version is too old.
          Please update from http://www.aquamaniac.de])
      elif test "$vmi" = "$gwen_vminor"; then
          if test "$vpl" -gt "$gwen_vpatchlevel"; then
            AC_MSG_ERROR([Your Gwenhywfar version is a little bit too old.
            Please update from http://www.aquamaniac.de])
          elif test "$vpl" = "$gwen_vpatchlevel"; then
            if test "$vbld" -gt "$gwen_vbuild"; then
              AC_MSG_ERROR([Your Gwenhywfar version is a little bit too old. 
  Please update to the latest SVN version. Instructions for accessing 
  SVN can be found on http://www.aquamaniac.de])
             fi
           fi
      fi
    fi
    have_gwenhywfar="yes"
    #AC_MSG_RESULT(yes)
  else
    have_gwenhywfar="yes"
    AC_MSG_RESULT(assuming yes)
  fi
  if test -n "$save_path"; then
      export PGK_CONFIG_PATH="$save_path"
  fi
dnl end of "if enable-gwenhywfar"
fi

AC_SUBST(gwenhywfar_dir)
AC_SUBST(gwenhywfar_plugins)
AC_SUBST(gwenhywfar_bindir)
AC_SUBST(gwenhywfar_libs)
AC_SUBST(gwenhywfar_includes)
AC_SUBST(gwenhywfar_headers)
AC_SUBST(gwenhywfar_has_crypt)
])
