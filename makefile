URL           ?= github.com/theballaam96/dk64-practice-rom
ifeq ($(origin DK_VERSION), undefined)
  TAG_COMMIT    := $(shell git rev-list --abbrev-commit --tags --max-count=1)
  TAG           := $(shell git describe --abbrev=0 --tags ${TAG_COMMIT} 2>/dev/null || true)
  COMMIT 	    := $(shell git rev-parse --short HEAD)
  DATE          := $(shell git log -1 --format=%cd --date=format:"%m-%d-%y")
  DK_VERSION 	:= $(COMMIT)-$(DATE)
  ifeq ('$(TAG_COMMIT)', '$(COMMIT)')
    ifneq ('$(TAG)', '')
      DK_VERSION := $(TAG)
    endif
  endif
endif
CC             = mips64-gcc
LD             = mips64-g++
AS             = mips64-gcc -x assembler-with-cpp
OBJCOPY        = mips64-objcopy
GRC            = grc
GENHOOKS       = CPPFLAGS='$(subst ','\'',$(CPPFLAGS))' ./genhooks
RESDESC        = $(RESDIR)/resources.json
SRCDIR         = src
BUILDDIR       = build
OBJDIR         = $(BUILDDIR)/obj
BINDIR         = $(BUILDDIR)/bin
LIBDIR         = lib
RESDIR         = res
CFILES         = *.c
SFILES         = *.s
DK_VERSIONS    = US PAL JP
NAME           = dk
NDEBUG        ?= 0

DK_HEAP_SIZE = 0x23000
CFLAGS         = -c -MMD -MP -std=gnu11 -Wall -ffunction-sections -fdata-sections -O2 -fno-reorder-blocks
ALL_CPPFLAGS   = -DURL=$(URL) -DDK_VERSION=$(DK_VERSION) -DF3DEX_GBI_2 $(CPPFLAGS)
ALL_LDFLAGS    = -T gl-n64.ld -L$(LIBDIR) -nostartfiles -specs=nosys.specs -Wl,--gc-sections $(LDFLAGS)
ALL_LIBS       = $(LIBS)

ifeq ($(NDEBUG),1)
  CFLAGS += -DNDEBUG
  ALL_CPPFLAGS += -DNDEBUG
endif

DK_ALL      = $(foreach v,$(DK_VERSIONS),dk-$(v))
LDR         = $(foreach v,$(DK_VERSIONS),ldr-dk-$(v))

DK-ALL      = $(DK-US) $(DK-PAL) $(DK-JP)
DK-US       = $(OBJ-dk-US) $(ELF-dk-US) $(HOOKS-dk-US)
DK-PAL 		= $(OBJ-dk-PAL) $(ELF-dk-PAL) $(HOOKS-dk-PAL)
DK-JP       = $(OBJ-dk-JP) $(ELF-dk-JP) $(HOOKS-dk-JP)

FILE_SORT   = 

HEAP_END_US 	= 0x805FAE00
HEAP_END_PAL 	= 0x805F3E00
HEAP_END_JP 	= 0x805F8600
HEAP_START_US 	= 0x805D7E00
HEAP_START_PAL 	= 0x805D0E00
HEAP_START_JP 	= 0x805D5600

all         : ./test.sh $(DK_ALL)
clean       :
	rm -rf $(BUILDDIR)
	rm -f dk-us.z64 dk-pal.z64 dk-jp.z64 

.PHONY: clean all

define bin_template
SRCDIR-$(1)      = $(4)
RESDIR-$(1)      = $(5)
OBJDIR-$(1)      = $(BUILDDIR)/obj/$(1)
BINDIR-$(1)      = $(BUILDDIR)/bin/$(1)
HOOKSDIR-$(1)    = $(BUILDDIR)/patch/$(1)
NAME-$(1)        = $(1)
CPPFLAGS-$(1)    = -DDK64_VERSION=$(2) $(ALL_CPPFLAGS)
CSRC-$(1)       := $$(foreach s,$$(CFILES),$$(wildcard $$(SRCDIR-$(1))/$$(s)))

COBJ-$(1)        = $$(patsubst $$(SRCDIR-$(1))/%,$$(OBJDIR-$(1))/%.o,$$(CSRC-$(1)))
SSRC-$(1)       := $$(foreach s,$$(SFILES),$$(wildcard $$(SRCDIR-$(1))/$$(s)))
SOBJ-$(1)        = $$(patsubst $$(SRCDIR-$(1))/%,$$(OBJDIR-$(1))/%.o,$$(SSRC-$(1)))
RESSRC-$(1)     := $$(wildcard $$(RESDIR-$(1))/*)
RESOBJ-$(1)      = $$(patsubst $$(RESDIR-$(1))/%,$$(OBJDIR-$(1))/$$(RESDIR)/%.o,$$(RESSRC-$(1)))
OBJ-$(1)         = $$(COBJ-$(1)) $$(SOBJ-$(1)) $$(RESOBJ-$(1))
ELF-$(1)         = $$(BINDIR-$(1))/$(3).elf
BIN-$(1)         = $$(BINDIR-$(1))/$(3).bin
OUTDIR-$(1)      = $$(OBJDIR-$(1)) $$(OBJDIR-$(1))/$$(RESDIR) $$(BINDIR-$(1)) $$(HOOKSDIR-$(1))
HOOKS-$(1)       = $(BUILDDIR)/patch/$(1)/hooks.gsc
BUILD-$(1)       = $(1)
CLEAN-$(1)       = clean-$(1)
$$(BUILD-$(1))   : $$(BIN-$(1))
$$(CLEAN-$(1))   : rm -rf $$(OUTDIR-$(1))

$$(COBJ-$(1))     : $$(OBJDIR-$(1))/%.o: $$(SRCDIR-$(1))/% | $$(OBJDIR-$(1))
	$(CC) $$(CPPFLAGS-$(1)) $$(CFLAGS) $$< -o $$@
$$(SOBJ-$(1))     : $$(OBJDIR-$(1))/%.o: $$(SRCDIR-$(1))/% | $$(OBJDIR-$(1))
	$(AS) -c -MMD -MP $$(ALL_CPPFLAGS) $$< -o $$@
$$(ELF-$(1))      : $$(OBJ-$(1)) | $$(BINDIR-$(1))
	$(LD) $$(ALL_LDFLAGS) $$^ $$(ALL_LIBS) -o $$@
$$(BIN-$(1))      : $$(ELF-$(1)) | $$(BINDIR-$(1))
	$(OBJCOPY) -S -O binary $$< $$@
$$(RESOBJ-$(1))   : $$(OBJDIR-$(1))/$$(RESDIR)/%.o: $$(RESDIR-$(1))/% $$(RESDESC) | $$(OBJDIR-$(1))/$$(RESDIR)
	$$(GRC) $$< -d $$(RESDESC) -o $$@
$$(OUTDIR-$(1))   :
	mkdir -p $$@
$$(HOOKS-$(1))      :   $$(ELF-$(1)) $$(HOOKSDIR-$(1))
	$$(GENHOOKS) $$< $(7) > $$@
endef

$(foreach v,$(DK_VERSIONS),$(eval $(call bin_template,dk-$(v),$(v),dk,src,res/dk)))
$(foreach v,$(DK_VERSIONS),$(eval $(call bin_template,ldr-dk-$(v),$(v),ldr,src/asm,res/ldr)))

$(DK-US)	:	ALL_LDFLAGS	+=	-Wl,-Map=$(BUILDDIR)/dk-us.map -Wl,--defsym,start=$(HEAP_START_US)
$(DK-PAL)	: 	ALL_LDFLAGS += 	-W1,-Map=$(BUILDDIR)/dk-pal.map -W1,--defsym,start=$(HEAP_START_PAL)
$(DK-JP)	:	ALL_LDFLAGS	+=	-Wl,-Map=$(BUILDDIR)/dk-jp.map -Wl,--defsym,start=$(HEAP_START_JP)

$(DK-US)	:	LIBS	:=	-ldk-us
$(DK-PAL)	:	LIBS	:=	-ldk-pal
$(DK-JP)	:	LIBS	:=	-ldk-jp