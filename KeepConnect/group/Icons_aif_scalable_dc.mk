ifeq (WINS,$(findstring WINS, $(PLATFORM)))
ZDIR=$(EPOCROOT)epoc32\release\$(PLATFORM)\$(CFG)\Z
else
ZDIR=$(EPOCROOT)epoc32\data\z
endif
 
TARGETDIR=$(ZDIR)\resource\apps
# Adapt the filename of the .mif-file that will be created:
ICONTARGETFILENAME=$(TARGETDIR)\KeepConnect.mif
 
ICONDIR=..\gfx
 
do_nothing :
	@rem do_nothing
 
MAKMAKE : do_nothing
 
BLD : do_nothing
 
CLEAN : do_nothing
 
LIB : do_nothing
 
CLEANLIB : do_nothing
 
RESOURCE : $(ICONTARGETFILENAME)

$(ICONTARGETFILENAME) : $(ICONDIR)\connect_established.svg
	mifconv $(ICONTARGETFILENAME)  \
		 /X /c32,8 $(ICONDIR)\connect_established.svg

FREEZE : do_nothing
 
SAVESPACE : do_nothing
 
RELEASABLES :
	@echo $(ICONTARGETFILENAME)
 
FINAL : do_nothing		 