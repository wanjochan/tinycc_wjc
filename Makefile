# --------------------------------------------------------------------------
#
# Tiny C Compiler Makefile
#

ifndef TOP
 TOP = .
 INCLUDED = no
endif

#include $(TOP)/Makefile.env
#include Makefile.env

ENV_MAK=Makefile.env
ifeq ($(ENV_MAK), $(wildcard $(ENV_MAK)))
include $(ENV_MAK)
endif
ENV_MAK=../Makefile.env
ifeq ($(ENV_MAK), $(wildcard $(ENV_MAK)))
include $(ENV_MAK)
endif

CONFIG_MAK = $(TOP)/config.mak
ifeq ($(CONFIG_MAK), $(wildcard $(CONFIG_MAK)))
include $(CONFIG_MAK)
else
NEED_CONFIG=1
endif

ifeq (-$(CC)-$(GCC_MAJOR)-$(findstring $(GCC_MINOR),56789)-,-gcc-4--)
 CFLAGS += -D_FORTIFY_SOURCE=0
endif

LIBTCC = libtcc.a
LIBTCC1 = libtcc1.a
LINK_LIBTCC =
LIBS =
CFLAGS += -I$(TOP)
CFLAGS += $(CPPFLAGS)
VPATH = $(TOPSRC)

ifdef CONFIG_WIN32
 ifneq ($(CONFIG_static),yes)
  LIBTCC = libtcc$(DLLSUF)
  LIBTCCDEF = libtcc.def
 endif
 CFGWIN = -win
 NATIVE_TARGET = $(TCC_ARCH)-WIN$(if $(findstring ARM,$(TCC_ARCH)),CE,32)
else

ifdef CONFIG_OSX
else
 LIBS=-lm
 ifneq ($(CONFIG_ldl),no)
  LIBS+=-ldl
 endif
endif
 # make libtcc as static or dynamic library?
 ifeq ($(CONFIG_static),no)
  LIBTCC=libtcc$(DLLSUF)
  export LD_LIBRARY_PATH := $(CURDIR)/$(TOP)
  ifneq ($(CONFIG_rpath),no)
   LINK_LIBTCC += -Wl,-rpath,"$(libdir)"
  endif
 endif
 CFGWIN =-unx

 NATIVE_TARGET = $(TCC_ARCH)-$(TCC_OS)
 
# NATIVE_TARGET = $(TCC_ARCH)
 ifdef CONFIG_OSX
#  NATIVE_TARGET = $(TCC_ARCH)-OSX
ifeq (-$(findstring $(CC),tcc)-,-tcc-)
  LDFLAGS += -flat_namespace
else

ifdef CONFIG_OSX
  LDFLAGS += -flat_namespace
else
  LDFLAGS += -flat_namespace -undefined warning
endif

endif
  export MACOSX_DEPLOYMENT_TARGET := 10.2
 endif
endif

# run local version of tcc with local libraries and includes
TCCFLAGS-unx = -B$(TOP) -I$(TOPSRC)/include -I$(TOPSRC) -I$(TOP)
TCCFLAGS-win = -B$(TOPSRC)/win32 -I$(TOPSRC)/include -I$(TOPSRC) -I$(TOP) -L$(TOP)
TCCFLAGS = $(TCCFLAGS$(CFGWIN))
TCC = $(TOP)/tcc$(EXESUF) $(TCCFLAGS)
ifdef CONFIG_OSX
 TCCFLAGS += -D_ANSI_SOURCE
endif

CFLAGS_P = $(CFLAGS) -pg -static -DCONFIG_TCC_STATIC -DTCC_PROFILE
LIBS_P = $(LIBS)
LDFLAGS_P = $(LDFLAGS)

CONFIG_$(TCC_ARCH) = yes
NATIVE_DEFINES_$(CONFIG_i386) += -DTCC_TARGET_I386
NATIVE_DEFINES_$(CONFIG_X86-64) += -DTCC_TARGET_X86_64
NATIVE_DEFINES_$(CONFIG_WIN32) += -DTCC_TARGET_PE
NATIVE_DEFINES_$(CONFIG_OSX) += -DTCC_TARGET_MACHO
NATIVE_DEFINES_$(CONFIG_uClibc) += -DTCC_UCLIBC
NATIVE_DEFINES_$(CONFIG_musl) += -DTCC_MUSL
NATIVE_DEFINES_$(CONFIG_libgcc) += -DCONFIG_USE_LIBGCC
NATIVE_DEFINES_$(CONFIG_selinux) += -DHAVE_SELINUX
NATIVE_DEFINES_$(CONFIG_ARM-32) += -DTCC_TARGET_ARM
NATIVE_DEFINES_$(CONFIG_ARM-32_EABIHF) += -DTCC_ARM_EABI -DTCC_ARM_HARDFLOAT
NATIVE_DEFINES_$(CONFIG_ARM-32_EABI) += -DTCC_ARM_EABI
NATIVE_DEFINES_$(CONFIG_ARM-32_VFP) += -DTCC_ARM_VFP
NATIVE_DEFINES_$(CONFIG_ARM-64) += -DTCC_TARGET_ARM64
NATIVE_DEFINES += $(NATIVE_DEFINES_yes)

ifeq ($(INCLUDED),no)
# --------------------------------------------------------------------------
# running top Makefile

PROGS = tcc$(EXESUF)
TCCLIBS = $(LIBTCC1) $(LIBTCC) $(LIBTCCDEF)


# --------------------------------------------------------------------------
ifdef NEED_CONFIG

default:env
	@echo ERROR: not found config.mak, maybe need ./configure
everything:env
	@echo ERROR: not found config.mak, maybe need ./configure

else #NEED_CONFIG

default:env $(PROGS) $(TCCLIBS)

ifeq ($(CONFIG_WIN32),yes)
everything:env clean $(PROGS) $(TCCLIBS) cross libtcc.dll
else
everything:env clean $(PROGS) $(TCCLIBS) cross libtcc.so
endif

ifdef CONFIG_cross
default:cross
endif

all:default

endif #NEED_CONFIG
# --------------------------------------------------------------------------

env:
	$(eval export TCC_ARCH=$(TCC_ARCH))
	$(eval export TCC_OS=$(TCC_OS))
	@echo ${TCC_OS},${TCC_ARCH}

# cross compiler targets to build

#TCC_X = X86-32 X86-64 X86-32-WIN X86-64-WIN X86-64-OSX ARM-32 ARM-64 ARM-32-WIN C67
#TCC_X     = X86-32 X86-64 X86-32-WIN X86-64-WIN X86-64-OSX ARM-32 ARM-64
TCC_X     = X86-32-LNX X86-64-LNX X86-32-WIN X86-64-WIN X86-64-OSX ARM-32-LNX ARM-64-LNX

# cross libtcc1.a targets to build
#LIBTCC1_X = X86-32 X86-64 X86-32-WIN X86-64-WIN X86-64-OSX ARM-32 ARM-64 ARM-32-WIN
#LIBTCC1_X = X86-32 X86-64 X86-32-WIN X86-64-WIN X86-64-OSX ARM-32 ARM-64
LIBTCC1_X = X86-32-LNX X86-64-LNX X86-32-WIN X86-64-WIN X86-64-OSX ARM-32-LNX ARM-64-LNX

PROGS_CROSS = $(foreach X,$(TCC_X),$X-tcc$(EXESUF))
LIBTCC1_CROSS = $(foreach X,$(LIBTCC1_X),$X-libtcc1.a)

# build cross compilers & libs
cross: $(LIBTCC1_CROSS) $(PROGS_CROSS)

# build specific cross compiler & lib
cross-%: %-tcc$(EXESUF) %-libtcc1.a ;

install: ; @$(MAKE) --no-print-directory install$(CFGWIN)
install-strip: ; @$(MAKE) --no-print-directory install$(CFGWIN) CONFIG_strip=yes
uninstall: ; @$(MAKE) --no-print-directory uninstall$(CFGWIN)

# --------------------------------------------

T = $(or $(CROSS_TARGET),$(NATIVE_TARGET),unknown)
X = $(if $(CROSS_TARGET),$(CROSS_TARGET)-)

DEF-X86-32      = -DTCC_TARGET_I386
DEF-X86-64      = -DTCC_TARGET_X86_64
DEF-X86-32-WIN  = -DTCC_TARGET_PE -DTCC_TARGET_I386
DEF-X86-64-WIN  = -DTCC_TARGET_PE -DTCC_TARGET_X86_64
DEF-X86-64-OSX  = -DTCC_TARGET_MACHO -DTCC_TARGET_X86_64
DEF-ARM-32-WIN  = -DTCC_TARGET_PE -DTCC_TARGET_ARM -DTCC_ARM_EABI -DTCC_ARM_VFP -DTCC_ARM_HARDFLOAT
DEF-ARM-64      = -DTCC_TARGET_ARM64
DEF-C67         = -DTCC_TARGET_C67 -w # disable warnigs
DEF-ARM-FPA     = -DTCC_TARGET_ARM
DEF-ARM-FPA-LD  = -DTCC_TARGET_ARM -DLDOUBLE_SIZE=12
DEF-ARM-VFP     = -DTCC_TARGET_ARM -DTCC_ARM_VFP
DEF-ARM-EABI    = -DTCC_TARGET_ARM -DTCC_ARM_VFP -DTCC_ARM_EABI
DEF-ARM-EABIHF  = -DTCC_TARGET_ARM -DTCC_ARM_VFP -DTCC_ARM_EABI -DTCC_ARM_HARDFLOAT
DEF-ARM         = $(DEF-ARM-EABIHF)
DEF-$(NATIVE_TARGET) = $(NATIVE_DEFINES)

DEFINES += $(DEF-$T) $(DEF-all)
DEFINES += $(if $(ROOT-$T),-DCONFIG_SYSROOT="\"$(ROOT-$T)\"")
DEFINES += $(if $(CRT-$T),-DCONFIG_TCC_CRTPREFIX="\"$(CRT-$T)\"")
DEFINES += $(if $(LIB-$T),-DCONFIG_TCC_LIBPATHS="\"$(LIB-$T)\"")
DEFINES += $(if $(INC-$T),-DCONFIG_TCC_SYSINCLUDEPATHS="\"$(INC-$T)\"")
DEFINES += $(DEF-$(or $(findstring win,$T),unx))

ifneq ($(X),)
ifeq ($(CONFIG_WIN32),yes)
DEF-win += -DTCC_LIBTCC1="\"$(X)libtcc1.a\""
DEF-unx += -DTCC_LIBTCC1="\"$(X)libtcc1.a\""
else
DEF-all += -DTCC_LIBTCC1="\"$(X)libtcc1.a\""
#DEF-win += -DCONFIG_TCCDIR="\"$(tccdir)\""
endif
endif

# include custom configuration (see make help)
-include config-extra.mak

CORE_FILES = tcc.c tcctools.c libtcc.c tccpp.c tccgen.c tccasm.c tccrun.c
CORE_FILES += tcc.h config.h libtcc.h tcctok.h

X86-32-LNX_FILES = $(CORE_FILES) tcc-ELF.c   gen-X86-32.c link-X86.c asm-X86.c asm-X86-32.h tok-X86.h
X86-32-WIN_FILES = $(CORE_FILES) tcc-PE.c    gen-X86-32.c link-X86.c asm-X86.c asm-X86-32.h tok-X86.h
X86-64-LNX_FILES = $(CORE_FILES) tcc-ELF.c   gen-X86-64.c link-X86-64.c asm-X86.c asm-X86-64.h
X86-64-WIN_FILES = $(CORE_FILES) tcc-PE.c    gen-X86-64.c link-X86-64.c asm-X86.c asm-X86-64.h
X86-64-OSX_FILES = $(CORE_FILES) tcc-MACHO.c gen-X86-64.c link-X86-64.c asm-X86.c asm-X86-64.h
ARM-32-LNX_FILES = $(CORE_FILES) tcc-ELF.c   gen-ARM-32.c link-ARM-32.c asm-ARM-32.c
ARM-32-WIN_FILES = $(CORE_FILES) tcc-PE.c    gen-ARM-32.c link-ARM-32.c asm-ARM-32.c
ARM-64-LNX_FILES = $(CORE_FILES) tcc-ELF.c   gen-ARM-64.c link-ARM-64.c

#C67_FILES = $(CORE_FILES) gen-C67.c link-C67.c tcccoff.c

# libtcc sources
LIBTCC_SRC = $(filter-out tcc.c tcctools.c,$(filter %.c,$($T_FILES)))

ifeq ($(ONE_SOURCE),yes)
LIBTCC_OBJ = $(X)libtcc.o
LIBTCC_INC = $($T_FILES)
TCC_FILES = $(X)tcc.o
tcc.o : DEFINES += -DONE_SOURCE=0
else
LIBTCC_OBJ = $(patsubst %.c,$(X)%.o,$(LIBTCC_SRC))
LIBTCC_INC = $(filter %.h gen-%.c link-%.c,$($T_FILES))
TCC_FILES = $(X)tcc.o $(LIBTCC_OBJ)
$(TCC_FILES) : DEFINES += -DONE_SOURCE=0
endif

# target specific object rule
$(X)%.o : %.c $(LIBTCC_INC)
	$(CC) -o $@ -c $< $(DEFINES) $(CFLAGS)

# additional dependencies
$(X)tcc.o : tcctools.c

# Host Tiny C Compiler
tcc$(EXESUF): tcc.o $(LIBTCC)
	$(CC) -o $@ $^ $(LIBS) $(LDFLAGS) $(LINK_LIBTCC)

# Cross Tiny C Compilers
%-tcc$(EXESUF): FORCE
	@$(MAKE) --no-print-directory $@ CROSS_TARGET=$* ONE_SOURCE=$(or $(ONE_SOURCE),yes)

$(CROSS_TARGET)-tcc$(EXESUF): $(TCC_FILES)
	$(CC) -o $@ $^ $(LIBS) $(LDFLAGS)

# profiling version
tcc_p$(EXESUF): $($T_FILES)
	$(CC) -o $@ $< $(DEFINES) $(CFLAGS_P) $(LIBS_P) $(LDFLAGS_P)

# static libtcc library
libtcc.a: $(LIBTCC_OBJ)
	$(AR) rcs $@ $^

# dynamic libtcc library
libtcc.so: $(LIBTCC_OBJ)
ifdef CONFIG_OSX
	$(CC) -shared -Wl,-install_name,$@ -o $@ $^ $(LDFLAGS)
else
	$(CC) -shared -Wl,-soname,$@ -o $@ $^ $(LDFLAGS)
endif

libtcc.so: CFLAGS+=-fPIC
libtcc.so: LDFLAGS+=-fPIC

# windows dynamic libtcc library
libtcc.dll : $(LIBTCC_OBJ)
	$(CC) -shared -o $@ $^ $(LDFLAGS)
libtcc.dll : DEFINES += -DLIBTCC_AS_DLL

# import file for windows libtcc.dll
libtcc.def : libtcc.dll tcc$(EXESUF)
	$(XTCC) -impdef $< -o $@
XTCC ?= ./tcc$(EXESUF)

# TinyCC runtime libraries
libtcc1.a : tcc$(EXESUF) FORCE
	@echo libtcc1.a =: $(MAKE) -C lib DEFINES='$(DEF-$T)'
	@$(MAKE) -C lib DEFINES='$(DEF-$T)'

# Cross libtcc1.a
%-libtcc1.a : %-tcc$(EXESUF) FORCE
	@echo *-libtcc1.a =: $(MAKE) -C lib DEFINES='$(DEF-$*)' CROSS_TARGET=$*
	@$(MAKE) -C lib DEFINES='$(DEF-$*)' CROSS_TARGET=$*

.PRECIOUS: %-libtcc1.a
FORCE:

# --------------------------------------------------------------------------
# documentation and man page
#tcc-doc.html: tcc-doc.texi
#	makeinfo --no-split --html --number-sections -o $@ $< || true

#tcc.1: tcc-doc.texi
#	$(TOPSRC)/texi2pod.pl $< tcc.pod \
#	&& pod2man --section=1 --center="Tiny C Compiler" --release="$(VERSION)" tcc.pod >tmp.1 \
#	&& mv tmp.1 $@ || rm -f tmp.1

#tcc-doc.info: tcc-doc.texi
#	makeinfo $< || true

# --------------------------------------------------------------------------
# install

INSTALL = install -m644
INSTALLBIN = install -m755 $(STRIP_$(CONFIG_strip))
STRIP_yes = -s

LIBTCC1_W = $(filter %-win32-libtcc1.a %-wince-libtcc1.a,$(LIBTCC1_CROSS))
LIBTCC1_U = $(filter-out $(LIBTCC1_W),$(LIBTCC1_CROSS))
IB = $(if $1,mkdir -p $2 && $(INSTALLBIN) $1 $2)
IBw = $(call IB,$(wildcard $1),$2)
IF = $(if $1,mkdir -p $2 && $(INSTALL) $1 $2)
IFw = $(call IF,$(wildcard $1),$2)
IR = mkdir -p $2 && cp -r $1/. $2

# install progs & libs
install-unx:
	$(call IBw,$(PROGS) $(PROGS_CROSS),"$(bindir)")
	$(call IFw,$(LIBTCC1) $(LIBTCC1_U),"$(tccdir)")
	#$(call IF,$(TOPSRC)/include/*.h,"$(tccdir)/include")
	$(call $(if $(findstring .so,$(LIBTCC)),IBw,IFw),$(LIBTCC),"$(libdir)")
	$(call IF,$(TOPSRC)/libtcc.h,"$(includedir)")
	#$(call IFw,tcc-doc.info,"$(infodir)")
	#$(call IFw,tcc-doc.html,"$(docdir)")
ifneq "$(wildcard $(LIBTCC1_W))" ""
	$(call IFw,$(TOPSRC)/lib/*.def $(LIBTCC1_W),"$(tccdir)")
endif

# uninstall
uninstall-unx:
	@rm -fv $(foreach P,$(PROGS) $(PROGS_CROSS),"$(bindir)/$P")
	@rm -fv "$(libdir)/libtcc.a" "$(libdir)/libtcc.so" "$(includedir)/libtcc.h"
	rm -r "$(tccdir)"

# install progs & libs on windows
install-win:
	$(call IBw,$(PROGS) $(PROGS_CROSS) $(subst libtcc.a,,$(LIBTCC)),"$(bindir)")
	$(call IF,$(TOPSRC)/lib/*.def,"$(tccdir)")
	$(call IFw,libtcc1.a $(LIBTCC1_W),"$(tccdir)")
	$(call IFw,$(TOPSRC)/libtcc.h $(subst .dll,.def,$(LIBTCC)),"$(libdir)")
ifneq "$(wildcard $(LIBTCC1_U))" ""
	$(call IFw,$(LIBTCC1_U),"$(tccdir)")
endif

# the msys-git shell works to configure && make except it does not have install
ifeq "$(and $(CONFIG_WIN32),$(shell which install >/dev/null 2>&1 || echo no))" "no"
install-win : INSTALL = cp
install-win : INSTALLBIN = cp
endif

# uninstall on windows
uninstall-win:
	@rm -fv $(foreach P,$(PROGS) $(PROGS_CROSS) libtcc.dll,"$(bindir)/$P")
	@rm -fv $(foreach F,tcc-doc.html tcc-win32.txt,"$(docdir)/$F")
	@rm -fv $(foreach F,libtcc.h libtcc.def libtcc.a,"$(libdir)/$F")
	rm -r "$(tccdir)"

# --------------------------------------------------------------------------
# other stuff

#TAGFILES = *.[ch] include/*.h lib/*.[chS]
#tags : ; ctags $(TAGFILES)
## cannot have both tags and TAGS on windows
#ETAGS : ; etags $(TAGFILES)

# create release tarball from *current* git branch (including tcc-doc.html
# and converting two files to CRLF)
TCC-VERSION = tcc-$(VERSION)
#tar:    tcc-doc.html
#	mkdir $(TCC-VERSION)
#	( cd $(TCC-VERSION) && git --git-dir ../.git checkout -f )
#	cp tcc-doc.html $(TCC-VERSION)
#	for f in tcc-win32.txt build-tcc.bat ; do \
#	    cat win32/$$f | sed 's,\(.*\),\1\r,g' > $(TCC-VERSION)/win32/$$f ; \
#	done
#	tar cjf $(TCC-VERSION).tar.bz2 $(TCC-VERSION)
#	rm -rf $(TCC-VERSION)
#	git reset

config.mak:
	$(if $(wildcard $@),,@echo "Please run ./configure." && exit 1)

# run all tests
test:
	$(MAKE) -C tests
# run test(s) from tests2 subdir (see make help)
tests2.%:
	$(MAKE) -C tests/tests2 $@

testspp.%:
	$(MAKE) -C tests/pp $@

clean:
	rm -f tcc$(EXESUF) tcc_p$(EXESUF) *-tcc$(EXESUF) tcc.pod
	rm -f  *~ *.o *.a *.so* *.out *.log lib*.def *.exe *.dll a.out tags TAGS
	@$(MAKE) -C lib $@
	@$(MAKE) -C tests $@

distclean: clean
	rm -f config.h config.mak config.texi tcc.1 tcc-doc.info tcc-doc.html

#.PHONY: all clean test tar tags ETAGS distclean install uninstall FORCE

help:
	@echo "make"
	@echo "make default"
	@echo "make all"
	@echo "   build native compiler (from separate objects)"
	@echo ""
	@echo "make everything"
	@echo "   clean and make everything can be make..."
	@echo ""
	@echo "make cross"
	@echo "   build cross compilers (from one source)"
	@echo ""
	@echo "make ONE_SOURCE=yes / no"
	@echo "   force building from one source / separate objects"
	@echo ""
	@echo "make cross-TARGET"
	@echo "   build one specific cross compiler for 'TARGET', as in"
	@echo "   $(TCC_X)"
	@echo ""
	@echo "Custom configuration:"
	@echo "   The makefile includes a file 'config-extra.mak' if it is present."
	@echo "   This file may contain some custom configuration.  For example:"
	@echo ""
	@echo "      NATIVE_DEFINES += -D..."
	@echo ""
	@echo "   Or for example to configure the search paths for a cross-compiler"
	@echo "   that expects the linux files in <tccdir>/i386-linux:"
	@echo ""
	@echo "      ROOT-i386 = {B}/i386-linux"
	@echo "      CRT-i386  = {B}/i386-linux/usr/lib"
	@echo "      LIB-i386  = {B}/i386-linux/lib:{B}/i386-linux/usr/lib"
	@echo "      INC-i386  = {B}/lib/include:{B}/i386-linux/usr/include"
	@echo "      DEF-i386  += -D__linux__"
	@echo ""
	@echo "make test"
	@echo "   run all tests"
	@echo ""
	@echo "make tests2.all / make tests2.37 / make tests2.37+"
	@echo "   run all/single test(s) from tests2, optionally update .expect"
	@echo "make testspp.all / make testspp.17"
	@echo "   run all/single test(s) from tests/pp"
	@echo ""
	@echo "Other supported make targets:"
	@echo "   install install-strip tags ETAGS tar clean distclean help"
	@echo ""

makedebug:
	@echo T=$(T),X=$(X)
	@echo DEF-T=$(DEF-$T)
	@echo T_FILES=$($T_FILES)
	@echo TCCLIBS=$(TCCLIBS)
	@echo LIBTCC=$(LIBTCC)
	@echo TCCFLAGS=$(TCCFLAGS)
	@echo CFGWIN=$(CFGWIN)
	@echo TCC_ARCH=$(TCC_ARCH)
	@echo CROSS_TARGET=$(CROSS_TARGET)
	@echo NATIVE_TARGET=$(NATIVE_TARGET)
	@echo DEFINES=$(DEFINES)
	@echo LIBTCC_SRC=$(LIBTCC_SRC)
	@echo CONFIG_OSX=$(CONFIG_OSX)
	@echo ONE_SOURCE=$(ONE_SOURCE)
	@echo LIBTCC_OBJ=$(LIBTCC_OBJ)
	@echo LIBTCC_INC=$(LIBTCC_INC)

# --------------------------------------------------------------------------
endif # ($(INCLUDED),no)
