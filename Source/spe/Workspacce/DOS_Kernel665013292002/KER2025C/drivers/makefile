#
# makefile for device.lib
#
# $Id: makefile,v 1.4 2001/11/18 17:48:20 bartoldeman Exp $
#


!include "..\mkfiles\generic.mak"


# MICROSOFT C
# -----------
#MODEL  = s
#CFLAGS = /c /Gs /A$(MODEL)
#AFLAGS = /Mx /Dmem$(MODEL)=1
#TERM   = ;

# BORLAND C
# -----------
#MODEL  = s
#CFLAGS = -c -m$(MODEL)
#AFLAGS = /Mx /Dmem$(MODEL)=1
#LIBFLAGS = /c

OBJS   = devend.obj floppy.obj getvec.obj timer.obj rdpcclk.obj rdatclk.obj \
wrpcclk.obj wratclk.obj

LIBOBJS= +devend +floppy +getvec +timer +rdpcclk +rdatclk +wrpcclk +wratclk



# Build the LIBRARY
# -----------------
all:            production

production:     ..\lib\device.lib

..\lib\device.lib: device.lib
	copy device.lib ..\lib

clobber:        clean
	-$(RM) device.lib status.me ..\lib\device.lib

clean:
	-$(RM) *.obj *.bak *.crf *.xrf *.map *.lst *.cod *.err

device.lib : $(OBJS)
	-$(RM) device.lib
	$(LIBUTIL) $(LIBFLAGS) device $(LIBOBJS) $(LIBTERM)

# Log: makefile,v 
#
# Revision 1.6  1999/08/25 03:16:36  jprice
# ror4 patches to allow TC 2.01 compile.
#
# Revision 1.5  1999/08/10 17:21:08  jprice
# ror4 2011-01 patch
#
# Revision 1.4  1999/04/23 03:44:52  jprice
# Improved by jprice
#
# Revision 1.3  1999/04/13 15:47:07  jprice
# no message
#
# Revision 1.2  1999/03/29 17:08:31  jprice
# ror4 changes
#
# Revision 1.1.1.1  1999/03/29 15:40:23  jprice
# New version without IPL.SYS
#
# Revision 1.3  1999/02/09 04:49:25  jprice
# Make makefile use common config.mak file
#
# Revision 1.2  1999/01/22 04:16:39  jprice
# Formating
#
# Revision 1.1.1.1  1999/01/20 05:51:00  jprice
# Imported sources
#
#
#   Rev 1.2   29 Aug 1996 13:07:12   patv
#Bug fixes for v0.91b
#
#   Rev 1.1   19 Feb 1996  3:19:26   patv
#Added NLS, int2f and config.sys processing
#
#   Rev 1.0   02 Jul 1995  7:54:52   patv
#Initial revision.
#
