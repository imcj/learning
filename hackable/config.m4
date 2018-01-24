dnl $Id$
dnl config.m4 for extension hackable

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(hackable, for hackable support,
dnl Make sure that the comment is aligned:
dnl [  --with-hackable             Include hackable support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(hackable, whether to enable hackable support,
dnl Make sure that the comment is aligned:
[  --enable-hackable           Enable hackable support])

if test "$PHP_HACKABLE" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-hackable -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/hackable.h"  # you most likely want to change this
  dnl if test -r $PHP_HACKABLE/$SEARCH_FOR; then # path given as parameter
  dnl   HACKABLE_DIR=$PHP_HACKABLE
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for hackable files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       HACKABLE_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$HACKABLE_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the hackable distribution])
  dnl fi

  dnl # --with-hackable -> add include path
  dnl PHP_ADD_INCLUDE($HACKABLE_DIR/include)

  dnl # --with-hackable -> check for lib and symbol presence
  dnl LIBNAME=hackable # you may want to change this
  dnl LIBSYMBOL=hackable # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $HACKABLE_DIR/$PHP_LIBDIR, HACKABLE_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_HACKABLELIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong hackable lib version or lib not found])
  dnl ],[
  dnl   -L$HACKABLE_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(HACKABLE_SHARED_LIBADD)

  PHP_NEW_EXTENSION(hackable, hackable.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
