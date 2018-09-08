/***************************************************************************\
*    _____ ____        __          ________                                 *
*   / ____|  _ \      /\ \        / /  ____|                                *
*  | (___ | |_) |    /  \ \  /\  / /| |__                                   *
*   \___ \|  _ <    / /\ \ \/  \/ / |  __|                                  *
*   ____) | |_) |  / ____ \  /\  /  | |____                                 *
*  |_____/|____/  /_/    \_\/  \/   |______|    Native Mode Driver.         *
*                                                                           *
*                                                                           *
*  Copyright (c) Samuel Gomes (a.k.a. Blade), 1998-2002.                    *
*  All rights reserved.                                                     *
*                                                                           *
*  mailto: v_2samg@hotmail.com || gomes.samuel@gmail.com                    *
*                                                                           *
*  MikMod driver for output on SB AWE and compatibles (native mode).        *
*                                                                           *
\***************************************************************************/

/***************************************************************************\
*                                                                           *
*  Bibliography:                                                            *
*                                                                           *
*  1) "The Un-official Sound Blaster AWE32 Programming Guide" by Vince Vu   *
*       a.k.a. Judge Dredd.                                                 *
*                                                                           *
*  2) "Low-level control of the EMU8000" sources by Lada Kopecky.           *
*                                                                           *
*  3) "AWE32/EMU8000 Programmer's Guide" (AEPG) by Dave Rossum. The AEPG    *
*       is part of the "AWE32 Developer's Information Pack" (ADIP) from     *
*       E-mu/Creative Technology Ltd.                                       *
*                                                                           *
*  4) The "Omega AWE32 Module Player" source by Cygnus X-1.                 *
*                                                                           *
*  5) The "Open Cubic Player" sources by Niklas Beisert/Tammo Hinrichs.     *
*                                                                           *
*  6) "Allegro Game Library" sources by Shawn Hargreaves.                   *
*                                                                           *
*  7) "MikMod 3 AWE32 Driver" sources by Steffen Rusitschka/Jake Stine.     *
*                                                                           *
*  8) "MikMod Sound System" sources by Jean Paul Mikkers.                   *
*                                                                           *
\***************************************************************************/

/***************************************************************************\
*                                                                           *
*  Conditions:                                                              *
*                                                                           *
*  This code frankly speaking is open source/freeware. You can do whatever  *
*  you want with it.                                                        *
*                                                                           *
*  If you use this code in your projects, please try to give me some        *
*  credit, as I have spent long sleepless nights fiddling with my SBAWE64.  *
*                                                                           *
*  I do not accept responsibility for any effects, adverse or otherwise,    *
*  that this code may have on you, your computer, your sanity, your dog,    *
*  and anything else that you can think of. Use it at your own risk.        *
*                                                                           *
\***************************************************************************/

/***************************************************************************\
*                                                                           *
*  Portability:                                                             *
*                                                                           *
*  DOS  :  Borland C(?) Watcom C(y) DJGPP(y)                                *
*  Win32:  n                                                                *
*  OS/2 :  n                                                                *
*  Linux:  n                                                                *
*                                                                           *
*  (y) - yes                                                                *
*  (n) - no (not possible or not useful)                                    *
*  (?) - may be possible, but not tested                                    *
*                                                                           *
\***************************************************************************/

/***************************************************************************\
*                                                                           *
*  Requirements:                                                            *
*                                                                           *
*  1) MikMod 2.10 (full MS-DOS support). Seems like the original MikMod     *
*       team's AWE driver never saw the light of day! ;)                    *
*                                                                           *
*  2) Watcom C 9.1+ (I use 9.1) or DJGPP 2.01+ (I use 2.03). Can't we just  *
*       forget those old half-hearted 16-bit compilers ;)                   *
*                                                                           *
*  3) And ofcourse, a SB32 or SBAWE32 or SBAWE64 or compatible with some    *
*       DRAM (512KB+ to be exact).                                          *
*                                                                           *
\***************************************************************************/

/***************************************************************************\
*                                                                           *
*  Notes:                                                                   *
*                                                                           *
*  1) Don't be fooled by the number in AWE64! Even though it is a better    *
*       and slicker version of the AWE32, it only supports upto 32 voices   *
*       at the same time (like it's AWE32 cousin). Then why the hell        *
*       Creative calls it the AWE64?!!! Just because of the lame reason     *
*       that in Windows they use the WaveSynth/WG Software Wavetable        *
*       Synthesizer along with the AWE64 to provide a total of              *
*       32 + 32 = 64 channels! Isn't that sick? And the speed really sucks  *
*       if ya don't have a fast CPU. On top of that if we use the onboard   *
*       DRAM we gotta sacrifice 2 channels for the DRAM refresh. :( That    *
*       leaves us with 30 channels.                                         *
*                                                                           *
*  2) The detection function only looks at the BLASTER environment          *
*       variable; no hardware scanning is done. So make sure you set that   *
*       environment variable correctly.                                     *
*                                                                           *
*  3) Using the BLASTER environment variable we can detect the majority of  *
*       sound blaster compatible devices:                                   *
*       BLASTER=A220 I5 D1 H5 P330 E620 T6                                  *
*       |       |    |  |  |  |    |    |                                   *
*       |       |    |  |  |  |    |    |_____ Type of Card                 *
*       |       |    |  |  |  |    |__________ AWE32/64 Only Parameter      *
*       |       |    |  |  |  |_______________ MIDI Port                    *
*       |       |    |  |  |__________________ "High" DMA Channel           *
*       |       |    |  |_____________________ DMA Channel                  *
*       |       |    |________________________ Interrupt                    *
*       |       |_____________________________ Port Address                 *
*       |_____________________________________ Environment Variable         *
*                                                                           *
*  4) The AWE uses only 16-bit samples internally; all 8-bit sample data    *
*       are converted to 16-bit by the driver. Also, each sound requires    *
*       few bytes of overhead for internal storage. This is so that we can  *
*       make all uploaded samples anti-click. On top of that if the sound   *
*       has to do a bi-directional loop then this calls for unrolling the   *
*       sound in the AWE DRAM, 'cause the AWE can't do reverse playback     *
*       (properly). As a result this hogs up some extra amount of AWE DRAM  *
*       needed for the sound.                                               *
*                                                                           *
\***************************************************************************/

/* Driver version numbers */
#define DRIVER_VERSION "5.6.3"

#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <dos.h>
#ifdef __DJGPP__
#include <dir.h>
#endif

#include "mikmod.h"
#include "mirq.h"


/* Start address of AWE's DRAM (in SAMPLES!!!) */
#define AWE_DRAM_START                  0x200000

/* Anti-clicking stuff */
#define AWE_ANTICLICK                   16
#define AWE_INTERPOLATION_POINTS        4

/* AWE channel stuff */
#define AWE_TOTAL_CHANNELS              32
#define AWE_USEABLE_CHANNELS            30

/* Panning stuff */
#define AWE_PAN_LEFT                    0
#define AWE_PAN_RIGHT                   255

#define AWE_FRQ_MAX (1408 - (5 * 16))

/* See the EMU8K docs by Dave Rossum from Creative. */
#define aweWriteCPF(_channel_, _data_) aweWriteDWord(0x0 + (_channel_), 0x620, (_data_))
#define aweWritePTRX(_channel_, _data_) aweWriteDWord(0x20 + (_channel_), 0x620, (_data_))
#define aweWriteCVCF(_channel_, _data_) aweWriteDWord(0x40 + (_channel_), 0x620, (_data_))
#define aweWriteVTFT(_channel_, _data_) aweWriteDWord(0x60 + (_channel_), 0x620, (_data_))
#define aweWritePSST(_channel_, _data_) aweWriteDWord(0xC0 + (_channel_), 0x620, (_data_))
#define aweWriteCSL(_channel_, _data_) aweWriteDWord(0xE0 + (_channel_), 0x620, (_data_))
#define aweWriteCCCA(_channel_, _data_) aweWriteDWord(0x0 + (_channel_), 0xA20, (_data_))
#define aweWriteHWCF4(_data_) aweWriteDWord(0x29, 0xA20, (_data_))
#define aweWriteHWCF5(_data_) aweWriteDWord(0x2A, 0xA20, (_data_))
#define aweWriteHWCF6(_data_) aweWriteDWord(0x2D, 0xA20, (_data_))
#define aweWriteSMALR(_data_) aweWriteDWord(0x34, 0xA20, (_data_))
#define aweWriteSMARR(_data_) aweWriteDWord(0x35, 0xA20, (_data_))
#define aweWriteSMALW(_data_) aweWriteDWord(0x36, 0xA20, (_data_))
#define aweWriteSMARW(_data_) aweWriteDWord(0x37, 0xA20, (_data_))
#define aweWriteSMLD(_data_) aweWriteWord(0x3A, 0xA20, (_data_))
#define aweWriteSMRD(_data_) aweWriteWord(0x3A, 0xA22, (_data_))
#define aweWriteWC(_data_) aweWriteWord(0x3B, 0xA22, (_data_))
#define aweWriteHWCF1(_data_) aweWriteWord(0x3D, 0xA20, (_data_))
#define aweWriteHWCF2(_data_) aweWriteWord(0x3E, 0xA20, (_data_))
#define aweWriteHWCF3(_data_) aweWriteWord(0x3F, 0xA20, (_data_))
#define aweWriteINIT1(_channel_, _data_) aweWriteWord(0x40 + (_channel_), 0xA20, (_data_))
#define aweWriteINIT2(_channel_, _data_) aweWriteWord(0x40 + (_channel_), 0xA22, (_data_))
#define aweWriteINIT3(_channel_, _data_) aweWriteWord(0x60 + (_channel_), 0xA20, (_data_))
#define aweWriteINIT4(_channel_, _data_) aweWriteWord(0x60 + (_channel_), 0xA22, (_data_))
#define aweWriteENVVOL(_channel_, _data_) aweWriteWord(0x80 + (_channel_), 0xA20, (_data_))
#define aweWriteDCYSUSV(_channel_, _data_) aweWriteWord(0xA0 + (_channel_), 0xA20, (_data_))
#define aweWriteENVVAL(_channel_, _data_) aweWriteWord(0xC0 + (_channel_), 0xA20, (_data_))
#define aweWriteDCYSUS(_channel_, _data_) aweWriteWord(0xE0 + (_channel_), 0xA20, (_data_))
#define aweWriteATKHLDV(_channel_, _data_) aweWriteWord(0x80 + (_channel_), 0xA22, (_data_))
#define aweWriteLFO1VAL(_channel_, _data_) aweWriteWord(0xA0 + (_channel_), 0xA22, (_data_))
#define aweWriteATKHLD(_channel_, _data_) aweWriteWord(0xC0 + (_channel_), 0xA22, (_data_))
#define aweWriteLFO2VAL(_channel_, _data_) aweWriteWord(0xE0 + (_channel_), 0xA22, (_data_))
#define aweWriteIP(_channel_, _data_) aweWriteWord(0x0 + (_channel_), 0xE20, (_data_))
#define aweWriteIFATN(_channel_, _data_) aweWriteWord(0x20 + (_channel_), 0xE20, (_data_))
#define aweWritePEFE(_channel_, _data_) aweWriteWord(0x40 + (_channel_), 0xE20, (_data_))
#define aweWriteFMMOD(_channel_, _data_) aweWriteWord(0x60 + (_channel_), 0xE20, (_data_))
#define aweWriteTREMFRQ(_channel_, _data_) aweWriteWord(0x80 + (_channel_), 0xE20, (_data_))
#define aweWriteFM2FRQ2(_channel_, _data_) aweWriteWord(0xA0 + (_channel_), 0xE20, (_data_))
#define aweReadCPF(_channel_) aweReadDWord(0x0 + (_channel_), 0x620)
#define aweReadPTRX(_channel_) aweReadDWord(0x20 + (_channel_), 0x620)
#define aweReadCVCF(_channel_) aweReadDWord(0x40 + (_channel_), 0x620)
#define aweReadVTFT(_channel_) aweReadDWord(0x60 + (_channel_), 0x620)
#define aweReadPSST(_channel_) aweReadDWord(0xC0 + (_channel_), 0x620)
#define aweReadCSL(_channel_) aweReadDWord(0xE0 + (_channel_), 0x620)
#define aweReadCCCA(_channel_) aweReadDWord(0x0 + (_channel_), 0xA20)
#define aweReadHWCF4() aweReadDWord(0x29, 0xA20)
#define aweReadHWCF5() aweReadDWord(0x2A, 0xA20)
#define aweReadHWCF6() aweReadDWord(0x2D, 0xA20)
#define aweReadSMALR() aweReadDWord(0x34, 0xA20)
#define aweReadSMARR() aweReadDWord(0x35, 0xA20)
#define aweReadSMALW() aweReadDWord(0x36, 0xA20)
#define aweReadSMARW() aweReadDWord(0x37, 0xA20)
#define aweReadSMLD() aweReadWord(0x3A, 0xA20)
#define aweReadSMRD() aweReadWord(0x3A, 0xA22)
#define aweReadWC() aweReadWord(0x3B, 0xA22)
#define aweReadHWCF1() aweReadWord(0x3D, 0xA20)
#define aweReadHWCF2() aweReadWord(0x3E, 0xA20)
#define aweReadHWCF3() aweReadWord(0x3F, 0xA20)
#define aweReadINIT1() aweReadWord(0x40, 0xA20)
#define aweReadINIT2() aweReadWord(0x40, 0xA22)
#define aweReadINIT3() aweReadWord(0x60, 0xA20)
#define aweReadINIT4() aweReadWord(0x60, 0xA22)
#define aweReadENVVOL(_channel_) aweReadWord(0x80 + (_channel_), 0xA20)
#define aweReadDCYSUSV(_channel_) aweReadWord(0xA0 + (_channel_), 0xA20)
#define aweReadENVVAL(_channel_) aweReadWord(0xC0 + (_channel_), 0xA20)
#define aweReadDCYSUS(_channel_) aweReadWord(0xE0 + (_channel_), 0xA20)
#define aweReadATKHLDV(_channel_) aweReadWord(0x80 + (_channel_), 0xA22)
#define aweReadLFO1VAL(_channel_) aweReadWord(0xA0 + (_channel_), 0xA22)
#define aweReadATKHLD(_channel_) aweReadWord(0xC0 + (_channel_), 0xA22)
#define aweReadLFO2VAL(_channel_) aweReadWord(0xE0 + (_channel_), 0xA22)
#define aweReadIP(_channel_) aweReadWord(0x0 + (_channel_), 0xE20)
#define aweReadIFATN(_channel_) aweReadWord(0x20 + (_channel_), 0xE20)
#define aweReadPEFE(_channel_) aweReadWord(0x40 + (_channel_), 0xE20)
#define aweReadFMMOD(_channel_) aweReadWord(0x60 + (_channel_), 0xE20)
#define aweReadTREMFRQ(_channel_) aweReadWord(0x80 + (_channel_), 0xE20)
#define aweReadFM2FRQ2(_channel_) aweReadWord(0xA0 + (_channel_), 0xE20)

#define aweWaitLR() {while (aweReadSMALR() & 0x80000000);}
#define aweWaitLW() {while (aweReadSMALW() & 0x80000000);}
#define aweWaitRR() {while (aweReadSMARR() & 0x80000000);}
#define aweWaitRW() {while (aweReadSMARW() & 0x80000000);}

#define SB_DSP_RESET (sbBase + 0x6)
#define SB_DSP_READ_DATA (sbBase + 0xA)
#define SB_DSP_WRITE_DATA (sbBase + 0xC)
#define SB_DSP_WRITE_STATUS (sbBase + 0xC)
#define SB_DSP_DATA_AVAIL (sbBase + 0xE)
#define SB_TC 210
#define SB_FREQ (1000000L / (256 - SB_TC))


/* AWE initialization data sets; thanks E-mu; yawn... */

/* First initialization set: */
static UWORD aweInit1_1[] = {
    0x03ff, 0x0030, 0x07ff, 0x0130, 0x0bff, 0x0230, 0x0fff, 0x0330,
    0x13ff, 0x0430, 0x17ff, 0x0530, 0x1bff, 0x0630, 0x1fff, 0x0730,
    0x23ff, 0x0830, 0x27ff, 0x0930, 0x2bff, 0x0a30, 0x2fff, 0x0b30,
    0x33ff, 0x0c30, 0x37ff, 0x0d30, 0x3bff, 0x0e30, 0x3fff, 0x0f30
};

static UWORD aweInit1_2[] = {
    0x43ff, 0x0030, 0x47ff, 0x0130, 0x4bff, 0x0230, 0x4fff, 0x0330,
    0x53ff, 0x0430, 0x57ff, 0x0530, 0x5bff, 0x0630, 0x5fff, 0x0730,
    0x63ff, 0x0830, 0x67ff, 0x0930, 0x6bff, 0x0a30, 0x6fff, 0x0b30,
    0x73ff, 0x0c30, 0x77ff, 0x0d30, 0x7bff, 0x0e30, 0x7fff, 0x0f30
};

static UWORD aweInit1_3[] = {
    0x83ff, 0x0030, 0x87ff, 0x0130, 0x8bff, 0x0230, 0x8fff, 0x0330,
    0x93ff, 0x0430, 0x97ff, 0x0530, 0x9bff, 0x0630, 0x9fff, 0x0730,
    0xa3ff, 0x0830, 0xa7ff, 0x0930, 0xabff, 0x0a30, 0xafff, 0x0b30,
    0xb3ff, 0x0c30, 0xb7ff, 0x0d30, 0xbbff, 0x0e30, 0xbfff, 0x0f30
};

static UWORD aweInit1_4[] = {
    0xc3ff, 0x0030, 0xc7ff, 0x0130, 0xcbff, 0x0230, 0xcfff, 0x0330,
    0xd3ff, 0x0430, 0xd7ff, 0x0530, 0xdbff, 0x0630, 0xdfff, 0x0730,
    0xe3ff, 0x0830, 0xe7ff, 0x0930, 0xebff, 0x0a30, 0xefff, 0x0b30,
    0xf3ff, 0x0c30, 0xf7ff, 0x0d30, 0xfbff, 0x0e30, 0xffff, 0x0f30
};

/* Second initialization set: */
static UWORD aweInit2_1[] = {
    0x03ff, 0x8030, 0x07ff, 0x8130, 0x0bff, 0x8230, 0x0fff, 0x8330,
    0x13ff, 0x8430, 0x17ff, 0x8530, 0x1bff, 0x8630, 0x1fff, 0x8730,
    0x23ff, 0x8830, 0x27ff, 0x8930, 0x2bff, 0x8a30, 0x2fff, 0x8b30,
    0x33ff, 0x8c30, 0x37ff, 0x8d30, 0x3bff, 0x8e30, 0x3fff, 0x8f30
};

static UWORD aweInit2_2[] = {
    0x43ff, 0x8030, 0x47ff, 0x8130, 0x4bff, 0x8230, 0x4fff, 0x8330,
    0x53ff, 0x8430, 0x57ff, 0x8530, 0x5bff, 0x8630, 0x5fff, 0x8730,
    0x63ff, 0x8830, 0x67ff, 0x8930, 0x6bff, 0x8a30, 0x6fff, 0x8b30,
    0x73ff, 0x8c30, 0x77ff, 0x8d30, 0x7bff, 0x8e30, 0x7fff, 0x8f30
};

static UWORD aweInit2_3[] = {
    0x83ff, 0x8030, 0x87ff, 0x8130, 0x8bff, 0x8230, 0x8fff, 0x8330,
    0x93ff, 0x8430, 0x97ff, 0x8530, 0x9bff, 0x8630, 0x9fff, 0x8730,
    0xa3ff, 0x8830, 0xa7ff, 0x8930, 0xabff, 0x8a30, 0xafff, 0x8b30,
    0xb3ff, 0x8c30, 0xb7ff, 0x8d30, 0xbbff, 0x8e30, 0xbfff, 0x8f30
};

static UWORD aweInit2_4[] = {
    0xc3ff, 0x8030, 0xc7ff, 0x8130, 0xcbff, 0x8230, 0xcfff, 0x8330,
    0xd3ff, 0x8430, 0xd7ff, 0x8530, 0xdbff, 0x8630, 0xdfff, 0x8730,
    0xe3ff, 0x8830, 0xe7ff, 0x8930, 0xebff, 0x8a30, 0xefff, 0x8b30,
    0xf3ff, 0x8c30, 0xf7ff, 0x8d30, 0xfbff, 0x8e30, 0xffff, 0x8f30
};

/* Third initialization set: */
static UWORD aweInit3_1[] = {
    0x0C10, 0x8470, 0x14FE, 0xB488, 0x167F, 0xA470, 0x18E7, 0x84B5,
    0x1B6E, 0x842A, 0x1F1D, 0x852A, 0x0DA3, 0x8F7C, 0x167E, 0xF254,
    0x0000, 0x842A, 0x0001, 0x852A, 0x18E6, 0x8BAA, 0x1B6D, 0xF234,
    0x229F, 0x8429, 0x2746, 0x8529, 0x1F1C, 0x86E7, 0x229E, 0xF224
};

static UWORD aweInit3_2[] = {
    0x0DA4, 0x8429, 0x2C29, 0x8529, 0x2745, 0x87F6, 0x2C28, 0xF254,
    0x383B, 0x8428, 0x320F, 0x8528, 0x320E, 0x8F02, 0x1341, 0xF264,
    0x3EB6, 0x8428, 0x3EB9, 0x8528, 0x383A, 0x8FA9, 0x3EB5, 0xF294,
    0x3EB7, 0x8474, 0x3EBA, 0x8575, 0x3EB8, 0xC4C3, 0x3EBB, 0xC5C3
};

static UWORD aweInit3_3[] = {
    0x0000, 0xA404, 0x0001, 0xA504, 0x141F, 0x8671, 0x14FD, 0x8287,
    0x3EBC, 0xE610, 0x3EC8, 0x8C7B, 0x031A, 0x87E6, 0x3EC8, 0x86F7,
    0x3EC0, 0x821E, 0x3EBE, 0xD208, 0x3EBD, 0x821F, 0x3ECA, 0x8386,
    0x3EC1, 0x8C03, 0x3EC9, 0x831E, 0x3ECA, 0x8C4C, 0x3EBF, 0x8C55
};

static UWORD aweInit3_4[] = {
    0x3EC9, 0xC208, 0x3EC4, 0xBC84, 0x3EC8, 0x8EAD, 0x3EC8, 0xD308,
    0x3EC2, 0x8F7E, 0x3ECB, 0x8219, 0x3ECB, 0xD26E, 0x3EC5, 0x831F,
    0x3EC6, 0xC308, 0x3EC3, 0xB2FF, 0x3EC9, 0x8265, 0x3EC9, 0x8319,
    0x1342, 0xD36E, 0x3EC7, 0xB3FF, 0x0000, 0x8365, 0x1420, 0x9570
};

/* Fourth initialization set: */
static UWORD aweInit4_1[] = {
    0x0C10, 0x8470, 0x14FE, 0xB488, 0x167F, 0xA470, 0x18E7, 0x84B5,
    0x1B6E, 0x842A, 0x1F1D, 0x852A, 0x0DA3, 0x0F7C, 0x167E, 0x7254,
    0x0000, 0x842A, 0x0001, 0x852A, 0x18E6, 0x0BAA, 0x1B6D, 0x7234,
    0x229F, 0x8429, 0x2746, 0x8529, 0x1F1C, 0x06E7, 0x229E, 0x7224
};

static UWORD aweInit4_2[] = {
    0x0DA4, 0x8429, 0x2C29, 0x8529, 0x2745, 0x07F6, 0x2C28, 0x7254,
    0x383B, 0x8428, 0x320F, 0x8528, 0x320E, 0x0F02, 0x1341, 0x7264,
    0x3EB6, 0x8428, 0x3EB9, 0x8528, 0x383A, 0x0FA9, 0x3EB5, 0x7294,
    0x3EB7, 0x8474, 0x3EBA, 0x8575, 0x3EB8, 0x44C3, 0x3EBB, 0x45C3
};

static UWORD aweInit4_3[] = {
    0x0000, 0xA404, 0x0001, 0xA504, 0x141F, 0x0671, 0x14FD, 0x0287,
    0x3EBC, 0xE610, 0x3EC8, 0x0C7B, 0x031A, 0x07E6, 0x3EC8, 0x86F7,
    0x3EC0, 0x821E, 0x3EBE, 0xD208, 0x3EBD, 0x021F, 0x3ECA, 0x0386,
    0x3EC1, 0x0C03, 0x3EC9, 0x031E, 0x3ECA, 0x8C4C, 0x3EBF, 0x0C55
};

static UWORD aweInit4_4[] = {
    0x3EC9, 0xC208, 0x3EC4, 0xBC84, 0x3EC8, 0x0EAD, 0x3EC8, 0xD308,
    0x3EC2, 0x8F7E, 0x3ECB, 0x0219, 0x3ECB, 0xD26E, 0x3EC5, 0x031F,
    0x3EC6, 0xC308, 0x3EC3, 0x32FF, 0x3EC9, 0x0265, 0x3EC9, 0x8319,
    0x1342, 0xD36E, 0x3EC7, 0x33FF, 0x0000, 0x8365, 0x1420, 0x9570
};

/*
Pre-computed lin->log AWE volume table
Range 0..64 according to Mikmod's requirements
#define AWE_VOLUME(__v) ((double)127 - log(max((__v), 1)) * (double)26.6899)
*/
static UBYTE aweVolumeTable[] = {
    255,127,108, 97, 89, 84, 79, 75, 71, 68, 65, 63, 60,
     58, 56, 54, 52, 51, 49, 48, 47, 45, 44, 43, 42, 41,
     40, 39, 38, 37, 36, 35, 34, 33, 32, 32, 31, 30, 29,
     29, 28, 27, 27, 26, 26, 25, 24, 24, 23, 23, 22, 22,
     21, 21, 20, 20, 19, 19, 18, 18, 17, 17, 16, 16, 15
};

/*
Frequency Table Math calulation

for (k = 0; k < FrqMax; k++) {
    f = (int)(log((float)(k << 4)) * 5909.27 - 5850.98);
    if (f > 0xFFFF) f = 0xFFFF;
    FrqTable[k] = (short)f;
}
*/
static UWORD aweLowFrqTable[512] = {
     6144, 10532, 14628, 17024, 18724, 20043, 21120, 22031, 22820, 23516, 24139, 24702, 25216, 25689, 26127, 26535,
    26916, 27275, 27612, 27932, 28235, 28523, 28798, 29061, 29312, 29554, 29785, 30008, 30223, 30431, 30631, 30825,
    31012, 31194, 31371, 31542, 31708, 31870, 32028, 32181, 32331, 32477, 32619, 32758, 32894, 33027, 33157, 33284,
    33408, 33530, 33650, 33767, 33881, 33994, 34104, 34213, 34319, 34424, 34527, 34628, 34727, 34825, 34921, 35015,
    35108, 35200, 35290, 35379, 35467, 35553, 35638, 35722, 35804, 35886, 35966, 36046, 36124, 36201, 36277, 36353,
    36427, 36500, 36573, 36645, 36715, 36785, 36854, 36923, 36990, 37057, 37123, 37188, 37253, 37317, 37380, 37443,
    37504, 37566, 37626, 37686, 37746, 37804, 37863, 37920, 37977, 38034, 38090, 38146, 38200, 38255, 38309, 38362,
    38415, 38468, 38520, 38572, 38623, 38673, 38724, 38774, 38823, 38872, 38921, 38969, 39017, 39064, 39111, 39158,
    39204, 39250, 39296, 39341, 39386, 39431, 39475, 39519, 39563, 39606, 39649, 39692, 39734, 39776, 39818, 39859,
    39900, 39941, 39982, 40022, 40062, 40102, 40142, 40181, 40220, 40259, 40297, 40335, 40373, 40411, 40449, 40486,
    40523, 40560, 40596, 40633, 40669, 40705, 40741, 40776, 40811, 40846, 40881, 40916, 40950, 40985, 41019, 41053,
    41086, 41120, 41153, 41186, 41219, 41252, 41284, 41317, 41349, 41381, 41413, 41445, 41476, 41507, 41539, 41570,
    41600, 41631, 41662, 41692, 41722, 41752, 41782, 41812, 41842, 41871, 41900, 41930, 41959, 41988, 42016, 42045,
    42073, 42102, 42130, 42158, 42186, 42214, 42241, 42269, 42296, 42324, 42351, 42378, 42405, 42432, 42458, 42485,
    42511, 42538, 42564, 42590, 42616, 42642, 42668, 42693, 42719, 42744, 42769, 42795, 42820, 42845, 42870, 42894,
    42919, 42944, 42968, 42992, 43017, 43041, 43065, 43089, 43113, 43137, 43160, 43184, 43207, 43231, 43254, 43277,
    43300, 43323, 43346, 43369, 43392, 43415, 43437, 43460, 43482, 43505, 43527, 43549, 43571, 43593, 43615, 43637,
    43659, 43680, 43702, 43724, 43745, 43766, 43788, 43809, 43830, 43851, 43872, 43893, 43914, 43935, 43955, 43976,
    43996, 44017, 44037, 44058, 44078, 44098, 44118, 44138, 44158, 44178, 44198, 44218, 44238, 44257, 44277, 44296,
    44316, 44335, 44355, 44374, 44393, 44412, 44431, 44450, 44469, 44488, 44507, 44526, 44545, 44563, 44582, 44601,
    44619, 44637, 44656, 44674, 44692, 44711, 44729, 44747, 44765, 44783, 44801, 44819, 44837, 44854, 44872, 44890,
    44907, 44925, 44942, 44960, 44977, 44995, 45012, 45029, 45046, 45064, 45081, 45098, 45115, 45132, 45149, 45165,
    45182, 45199, 45216, 45232, 45249, 45266, 45282, 45299, 45315, 45331, 45348, 45364, 45380, 45397, 45413, 45429,
    45445, 45461, 45477, 45493, 45509, 45525, 45541, 45556, 45572, 45588, 45603, 45619, 45635, 45650, 45666, 45681,
    45696, 45712, 45727, 45742, 45758, 45773, 45788, 45803, 45818, 45833, 45848, 45863, 45878, 45893, 45908, 45923,
    45938, 45952, 45967, 45982, 45996, 46011, 46026, 46040, 46055, 46069, 46084, 46098, 46112, 46127, 46141, 46155,
    46169, 46184, 46198, 46212, 46226, 46240, 46254, 46268, 46282, 46296, 46310, 46324, 46337, 46351, 46365, 46379,
    46392, 46406, 46420, 46433, 46447, 46460, 46474, 46487, 46501, 46514, 46528, 46541, 46554, 46568, 46581, 46594,
    46607, 46621, 46634, 46647, 46660, 46673, 46686, 46699, 46712, 46725, 46738, 46751, 46764, 46776, 46789, 46802,
    46815, 46827, 46840, 46853, 46865, 46878, 46891, 46903, 46916, 46928, 46941, 46953, 46966, 46978, 46990, 47003,
    47015, 47027, 47040, 47052, 47064, 47076, 47088, 47101, 47113, 47125, 47137, 47149, 47161, 47173, 47185, 47197,
    47209, 47221, 47233, 47244, 47256, 47268, 47280, 47292, 47303, 47315, 47327, 47338, 47350, 47362, 47373, 47385
};

static UWORD aweHighFrqTable[1408 - (5 * 16)] = {
    47396, 47488, 47578, 47667, 47755, 47841, 47926, 48010, 48092, 48174, 48254, 48334, 48412, 48489, 48565, 48641,
    48715, 48788, 48861, 48933, 49003, 49073, 49142, 49211, 49278, 49345, 49411, 49476, 49541, 49605, 49668, 49731,
    49792, 49854, 49914, 49974, 50034, 50092, 50151, 50208, 50265, 50322, 50378, 50433, 50488, 50543, 50597, 50650,
    50703, 50756, 50808, 50860, 50911, 50961, 51012, 51062, 51111, 51160, 51209, 51257, 51305, 51352, 51399, 51446,
    51492, 51538, 51584, 51629, 51674, 51719, 51763, 51807, 51851, 51894, 51937, 51980, 52022, 52064, 52106, 52147,
    52188, 52229, 52270, 52310, 52350, 52390, 52430, 52469, 52508, 52547, 52585, 52623, 52661, 52699, 52737, 52774,
    52811, 52848, 52884, 52921, 52957, 52993, 53029, 53064, 53099, 53134, 53169, 53204, 53238, 53273, 53307, 53341,
    53374, 53408, 53441, 53474, 53507, 53540, 53572, 53605, 53637, 53669, 53701, 53733, 53764, 53795, 53827, 53858,
    53888, 53919, 53950, 53980, 54010, 54040, 54070, 54100, 54130, 54159, 54188, 54218, 54247, 54276, 54304, 54333,
    54361, 54390, 54418, 54446, 54474, 54502, 54529, 54557, 54584, 54612, 54639, 54666, 54693, 54720, 54746, 54773,
    54799, 54826, 54852, 54878, 54904, 54930, 54956, 54981, 55007, 55032, 55057, 55083, 55108, 55133, 55158, 55182,
    55207, 55232, 55256, 55280, 55305, 55329, 55353, 55377, 55401, 55425, 55448, 55472, 55495, 55519, 55542, 55565,
    55588, 55611, 55634, 55657, 55680, 55703, 55725, 55748, 55770, 55793, 55815, 55837, 55859, 55881, 55903, 55925,
    55947, 55968, 55990, 56011, 56033, 56054, 56076, 56097, 56118, 56139, 56160, 56181, 56202, 56223, 56243, 56264,
    56284, 56305, 56325, 56346, 56366, 56386, 56406, 56426, 56446, 56466, 56486, 56506, 56526, 56545, 56565, 56584,
    56604, 56623, 56643, 56662, 56681, 56700, 56719, 56738, 56757, 56776, 56795, 56814, 56833, 56851, 56870, 56889,
    56907, 56925, 56944, 56962, 56980, 56999, 57017, 57035, 57053, 57071, 57089, 57107, 57125, 57142, 57160, 57178,
    57195, 57213, 57230, 57248, 57265, 57283, 57300, 57317, 57334, 57352, 57369, 57386, 57403, 57420, 57437, 57453,
    57470, 57487, 57504, 57520, 57537, 57554, 57570, 57587, 57603, 57619, 57636, 57652, 57668, 57685, 57701, 57717,
    57733, 57749, 57765, 57781, 57797, 57813, 57829, 57844, 57860, 57876, 57891, 57907, 57923, 57938, 57954, 57969,
    57984, 58000, 58015, 58030, 58046, 58061, 58076, 58091, 58106, 58121, 58136, 58151, 58166, 58181, 58196, 58211,
    58226, 58240, 58255, 58270, 58284, 58299, 58314, 58328, 58343, 58357, 58372, 58386, 58400, 58415, 58429, 58443,
    58457, 58472, 58486, 58500, 58514, 58528, 58542, 58556, 58570, 58584, 58598, 58612, 58625, 58639, 58653, 58667,
    58680, 58694, 58708, 58721, 58735, 58748, 58762, 58775, 58789, 58802, 58816, 58829, 58842, 58856, 58869, 58882,
    58895, 58909, 58922, 58935, 58948, 58961, 58974, 58987, 59000, 59013, 59026, 59039, 59052, 59064, 59077, 59090,
    59103, 59115, 59128, 59141, 59153, 59166, 59179, 59191, 59204, 59216, 59229, 59241, 59254, 59266, 59278, 59291,
    59303, 59315, 59328, 59340, 59352, 59364, 59376, 59389, 59401, 59413, 59425, 59437, 59449, 59461, 59473, 59485,
    59497, 59509, 59521, 59532, 59544, 59556, 59568, 59580, 59591, 59603, 59615, 59626, 59638, 59650, 59661, 59673,
    59684, 59696, 59707, 59719, 59730, 59742, 59753, 59765, 59776, 59787, 59799, 59810, 59821, 59833, 59844, 59855,
    59866, 59877, 59889, 59900, 59911, 59922, 59933, 59944, 59955, 59966, 59977, 59988, 59999, 60010, 60021, 60032,
    60043, 60054, 60064, 60075, 60086, 60097, 60107, 60118, 60129, 60140, 60150, 60161, 60172, 60182, 60193, 60203,
    60214, 60225, 60235, 60246, 60256, 60266, 60277, 60287, 60298, 60308, 60319, 60329, 60339, 60350, 60360, 60370,
    60380, 60391, 60401, 60411, 60421, 60432, 60442, 60452, 60462, 60472, 60482, 60492, 60502, 60512, 60522, 60532,
    60542, 60552, 60562, 60572, 60582, 60592, 60602, 60612, 60622, 60632, 60641, 60651, 60661, 60671, 60680, 60690,
    60700, 60710, 60719, 60729, 60739, 60748, 60758, 60768, 60777, 60787, 60796, 60806, 60815, 60825, 60834, 60844,
    60853, 60863, 60872, 60882, 60891, 60901, 60910, 60919, 60929, 60938, 60947, 60957, 60966, 60975, 60985, 60994,
    61003, 61012, 61021, 61031, 61040, 61049, 61058, 61067, 61076, 61086, 61095, 61104, 61113, 61122, 61131, 61140,
    61149, 61158, 61167, 61176, 61185, 61194, 61203, 61212, 61221, 61229, 61238, 61247, 61256, 61265, 61274, 61283,
    61291, 61300, 61309, 61318, 61326, 61335, 61344, 61353, 61361, 61370, 61379, 61387, 61396, 61405, 61413, 61422,
    61430, 61439, 61448, 61456, 61465, 61473, 61482, 61490, 61499, 61507, 61516, 61524, 61533, 61541, 61549, 61558,
    61566, 61575, 61583, 61591, 61600, 61608, 61616, 61625, 61633, 61641, 61650, 61658, 61666, 61674, 61683, 61691,
    61699, 61707, 61715, 61724, 61732, 61740, 61748, 61756, 61764, 61772, 61781, 61789, 61797, 61805, 61813, 61821,
    61829, 61837, 61845, 61853, 61861, 61869, 61877, 61885, 61893, 61901, 61909, 61917, 61924, 61932, 61940, 61948,
    61956, 61964, 61972, 61980, 61987, 61995, 62003, 62011, 62019, 62026, 62034, 62042, 62050, 62057, 62065, 62073,
    62080, 62088, 62096, 62103, 62111, 62119, 62126, 62134, 62142, 62149, 62157, 62164, 62172, 62180, 62187, 62195,
    62202, 62210, 62217, 62225, 62232, 62240, 62247, 62255, 62262, 62270, 62277, 62285, 62292, 62299, 62307, 62314,
    62322, 62329, 62336, 62344, 62351, 62358, 62366, 62373, 62380, 62388, 62395, 62402, 62410, 62417, 62424, 62431,
    62439, 62446, 62453, 62460, 62468, 62475, 62482, 62489, 62496, 62503, 62511, 62518, 62525, 62532, 62539, 62546,
    62553, 62561, 62568, 62575, 62582, 62589, 62596, 62603, 62610, 62617, 62624, 62631, 62638, 62645, 62652, 62659,
    62666, 62673, 62680, 62687, 62694, 62701, 62708, 62715, 62721, 62728, 62735, 62742, 62749, 62756, 62763, 62770,
    62776, 62783, 62790, 62797, 62804, 62811, 62817, 62824, 62831, 62838, 62844, 62851, 62858, 62865, 62871, 62878,
    62885, 62892, 62898, 62905, 62912, 62918, 62925, 62932, 62938, 62945, 62952, 62958, 62965, 62972, 62978, 62985,
    62991, 62998, 63005, 63011, 63018, 63024, 63031, 63037, 63044, 63050, 63057, 63063, 63070, 63076, 63083, 63089,
    63096, 63102, 63109, 63115, 63122, 63128, 63135, 63141, 63148, 63154, 63160, 63167, 63173, 63180, 63186, 63192,
    63199, 63205, 63211, 63218, 63224, 63230, 63237, 63243, 63249, 63256, 63262, 63268, 63275, 63281, 63287, 63293,
    63300, 63306, 63312, 63318, 63325, 63331, 63337, 63343, 63350, 63356, 63362, 63368, 63374, 63381, 63387, 63393,
    63399, 63405, 63411, 63417, 63424, 63430, 63436, 63442, 63448, 63454, 63460, 63466, 63472, 63479, 63485, 63491,
    63497, 63503, 63509, 63515, 63521, 63527, 63533, 63539, 63545, 63551, 63557, 63563, 63569, 63575, 63581, 63587,
    63593, 63599, 63605, 63611, 63617, 63623, 63628, 63634, 63640, 63646, 63652, 63658, 63664, 63670, 63676, 63681,
    63687, 63693, 63699, 63705, 63711, 63717, 63722, 63728, 63734, 63740, 63746, 63751, 63757, 63763, 63769, 63775,
    63780, 63786, 63792, 63798, 63803, 63809, 63815, 63821, 63826, 63832, 63838, 63844, 63849, 63855, 63861, 63866,
    63872, 63878, 63883, 63889, 63895, 63900, 63906, 63912, 63917, 63923, 63929, 63934, 63940, 63945, 63951, 63957,
    63962, 63968, 63973, 63979, 63985, 63990, 63996, 64001, 64007, 64012, 64018, 64023, 64029, 64035, 64040, 64046,
    64051, 64057, 64062, 64068, 64073, 64079, 64084, 64090, 64095, 64101, 64106, 64111, 64117, 64122, 64128, 64133,
    64139, 64144, 64150, 64155, 64160, 64166, 64171, 64177, 64182, 64187, 64193, 64198, 64203, 64209, 64214, 64220,
    64225, 64230, 64236, 64241, 64246, 64252, 64257, 64262, 64268, 64273, 64278, 64284, 64289, 64294, 64299, 64305,
    64310, 64315, 64321, 64326, 64331, 64336, 64342, 64347, 64352, 64357, 64362, 64368, 64373, 64378, 64383, 64389,
    64394, 64399, 64404, 64409, 64415, 64420, 64425, 64430, 64435, 64440, 64446, 64451, 64456, 64461, 64466, 64471,
    64476, 64482, 64487, 64492, 64497, 64502, 64507, 64512, 64517, 64522, 64528, 64533, 64538, 64543, 64548, 64553,
    64558, 64563, 64568, 64573, 64578, 64583, 64588, 64593, 64598, 64603, 64608, 64613, 64618, 64623, 64628, 64633,
    64638, 64643, 64648, 64653, 64658, 64663, 64668, 64673, 64678, 64683, 64688, 64693, 64698, 64703, 64708, 64713,
    64718, 64723, 64727, 64732, 64737, 64742, 64747, 64752, 64757, 64762, 64767, 64772, 64776, 64781, 64786, 64791,
    64796, 64801, 64806, 64810, 64815, 64820, 64825, 64830, 64835, 64840, 64844, 64849, 64854, 64859, 64864, 64868,
    64873, 64878, 64883, 64888, 64892, 64897, 64902, 64907, 64911, 64916, 64921, 64926, 64930, 64935, 64940, 64945,
    64949, 64954, 64959, 64964, 64968, 64973, 64978, 64982, 64987, 64992, 64997, 65001, 65006, 65011, 65015, 65020,
    65025, 65029, 65034, 65039, 65043, 65048, 65053, 65057, 65062, 65067, 65071, 65076, 65081, 65085, 65090, 65094,
    65099, 65104, 65108, 65113, 65117, 65122, 65127, 65131, 65136, 65140, 65145, 65150, 65154, 65159, 65163, 65168,
    65172, 65177, 65182, 65186, 65191, 65195, 65200, 65204, 65209, 65213, 65218, 65222, 65227, 65231, 65236, 65240,
    65245, 65249, 65254, 65258, 65263, 65267, 65272, 65276, 65281, 65285, 65290, 65294, 65299, 65303, 65308, 65312,
    65317, 65321, 65325, 65330, 65334, 65339, 65343, 65348, 65352, 65356, 65361, 65365, 65370, 65374, 65379, 65383,
    65387, 65392, 65396, 65401, 65405, 65409, 65414, 65418, 65422, 65427, 65431, 65436, 65440, 65444, 65449, 65453,
    65457, 65462, 65466, 65470, 65475, 65479, 65483, 65488, 65492, 65496, 65501, 65505, 65509, 65513, 65518, 65522,
    65526, 65531, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535, 65535
};

static UWORD aweBase;               /* AWE base port */
static ULONG aweDRAMSize = 0;       /* total DRAM */
static UWORD sbBase;                /* SB base port */
static UBYTE sbInt;                 /* interrupt vector that belongs to sbIRQ */
static UWORD sbVer;                 /* DSP version number */
static UBYTE sbIRQ;                 /* SB IRQ */
static UWORD sbSilenceLen;
static SWORD sbSilenceLenAdd = 0;
static UWORD aweTimerReq;
static UWORD aweBPM;
static PVI sbOldInt;

/* The AWE memory multiplier stuff; yuck! */
static double aweMemMagic = 1;
static BOOL aweMemOptimized = FALSE;

/* AWE DRAM manager structure */
static struct {
    BOOL active;    /* this handle is active; contains an empty or used block */
    BOOL empty;     /* is this block free? */
    ULONG offset;   /* position of the sound in the AWE DRAM in SAMPLES! */
    ULONG size;     /* size of the sound in SAMPLES! */
} aweDRAM[MAXSAMPLEHANDLES + 1];        /* one extra for unused bytes */

/* The raw instrument sample holder struct */
static struct {
    BOOL empty;         /* if block is empty */
    SWORD *sound;       /* pointer to the sound */
    SWORD handle;       /* handle from the AWE DRAM manager */
    ULONG samples;      /* original sample size */
    ULONG loopstart;    /* start pos of loop */
    ULONG loopend;      /* end pos of loop */
    ULONG bidilen;      /* extra space for unrolling loops */
    ULONG nSamples;     /* actual size to be demanded from AWE DRAM manager */
    UWORD flags;        /* extra flags */
} aweRawSample[MAXSAMPLEHANDLES];

/* Physical channel info */
/* Just points to which voice it's currently linked to */
static SWORD aweChannel[AWE_USEABLE_CHANNELS];  /* 30 */

/* Virtual channel info */
static struct {
    BOOL kick;                      /* = TRUE -> sample has to be restarted */
    UWORD flags;                    /* looping/one-shot */
    SWORD handle;                   /* identifies the sample */
    SWORD channel;                  /* which AWE channel */
    ULONG start;                    /* start index */
    ULONG size;                     /* samplesize */
    ULONG reppos;                   /* loop start */
    ULONG repend;                   /* loop end */
    ULONG frq;                      /* current frequency */
    UBYTE vol;                      /* current volume */
    UBYTE pan;                      /* current panning position */
    UBYTE panold;                   /* previous panning position */
} aweVoice[AWE_TOTAL_CHANNELS];     /* 30 + 2 */

/* The frills ;) */
#define AWE_DRIVER_NAME_FORMAT "Sound Blaster AWE with %lu KB DRAM"
static char aweDriverName[] = "Sound Blaster AWE\0with 28672 KB DRAM";


/***************************************************************************\
*                                                                           *
*   Low level hardware interface functions                                  *
*                                                                           *
\***************************************************************************/

/* Parses settings from the BLASTER environment string */
static UWORD sbGetSetting(char id, BOOL isHex, UWORD defaultVal) {
    char *envVar;
    char *paramstart;
    char buf1[_MAX_PATH];
    char buf2[_MAX_PATH];

    /* Get variable value */
    envVar = getenv("BLASTER");

    /* Check if it's there */
    if (envVar == NULL) return defaultVal;

    /* Copy & normalize */  
    strupr(strcpy(buf1, envVar));

    /* Search id */
    if (strchr(buf1, id) != NULL) {
        paramstart = strchr(buf1, id) + 1;

        if (strchr(paramstart, ' ') != NULL)
            *(strchr(paramstart, ' ')) = 0;
        if (isHex)
            strcpy(buf2, "0x");
        else
            strcpy(buf2, "");

        strcat(buf2, paramstart);

        return (UWORD)strtoul(buf2, NULL, 0);
    }

    return defaultVal;
}

/*
    Waits until the DSP is ready to be written to.
    Returns FALSE on timeout.
*/
static BOOL sbWaitDSPWrite(void) {
    UWORD timeout = USHRT_MAX;

    while (timeout--) {
        if (!(inportb(SB_DSP_WRITE_STATUS) & 0x80)) return TRUE;
    }
    
    return FALSE;
}

/*
    Waits until the DSP is ready to read from.
    Returns FALSE on timeout.
*/
static BOOL sbWaitDSPRead(void) {
    UWORD timeout = USHRT_MAX;

    while (timeout--) {
        if (inportb(SB_DSP_DATA_AVAIL) & 0x80) return TRUE;
    }
    
    return FALSE;
}

/*
    Writes byte 'data' to the DSP.
    Returns FALSE on timeout.
*/
static BOOL sbWriteDSP(UBYTE data) {
    if (!sbWaitDSPWrite()) return FALSE;
    outportb(SB_DSP_WRITE_DATA, data);
    return TRUE;
}

/*
    Reads a byte from the DSP.
    Returns 0xffff on timeout.
*/
static UWORD sbReadDSP(void) {
    if (!sbWaitDSPRead()) return 0xFFFF;
    return inportb(SB_DSP_READ_DATA);
}

/* Resets the DSP. */
static void sbResetDSP(void) {
    int t;
    
    /* reset the DSP by sending 1, (delay), then 0 */
    outportb(SB_DSP_RESET, 1);
    for (t = 0; t < 8; t++) inportb(SB_DSP_RESET);
    outportb(SB_DSP_RESET, 0);
}

/*
    Checks if a SB is present at the current baseport by
    resetting the DSP and checking if it returned the value 0xaa.

    returns: TRUE   => SB is present
             FALSE  => No SB detected
*/
static BOOL sbDetect(void) {
    sbResetDSP();
    return (sbReadDSP() == 0xAA);
}

/* Gets SB-dsp version. returns 0xffff if dsp didn't respond. */
static UWORD sbGetDSPVersion(void) {
    UWORD hi, lo;

    if (!sbWriteDSP(0xE1)) return 0xFFFF;

    hi = sbReadDSP();
    lo = sbReadDSP();

    return ((hi << 8) | lo);
}

static BOOL sbIsThere(void) {
#ifdef __DJGPP__
    __dpmi_version_ret dvr;
#endif

    sbBase = sbGetSetting('A', TRUE, 0xFFFF);
    sbIRQ = sbGetSetting('I', FALSE, 0xFF);

    if (sbBase == 0xFFFF || sbIRQ == 0xFF) return FALSE;

    /* determine interrupt vector */
#ifdef __DJGPP__
    if (__dpmi_get_version(&dvr) == 0) {
        sbInt = (sbIRQ > 7) ? sbIRQ + dvr.slave_pic : sbIRQ + dvr.master_pic;
    }
    else {
        sbInt = (sbIRQ > 7) ? sbIRQ + 104 : sbIRQ + 8;
    }
#else
    sbInt = (sbIRQ > 7) ? sbIRQ + 104 : sbIRQ + 8;
#endif

    if (!sbDetect()) return FALSE;

    /* get dsp version. */
    sbVer = sbGetDSPVersion();
    if ((sbVer == 0xFFFF) || (sbVer < 0x400)) return FALSE;

    return TRUE;
}

static void sbSetBPM(UWORD bpm) {
    aweBPM = bpm;
    if (bpm == 0) bpm = 1;	/* safety first! ;) */
    sbSilenceLen = SB_FREQ * 125 / (bpm * 50) - 1;
    aweTimerReq  = 44100 * 125 / (bpm * 50);
}

static void sbStartSilence() {
    sbWriteDSP(0x80);
    sbWriteDSP((sbSilenceLen + sbSilenceLenAdd) & 0xFF);
    sbWriteDSP((sbSilenceLen + sbSilenceLenAdd) >> 8);
}

/* Write 16-bit EMU8K register */
static void aweWriteWord(UWORD Command, UWORD DataPort, UWORD Data) {
    disable();

    outpw(aweBase + 0x802, Command);    /* select index */
    outpw(aweBase - 0x620 + DataPort, Data);

    enable();
}

/* Write 32-bit EMU8K register */
static void aweWriteDWord(UWORD Command, UWORD DataPort, ULONG Data) {
    disable();

    outpw(aweBase + 0x802, Command);    /* select index */
#ifdef __DJGPP__
    /* DJGPP optimization */
    outportl(aweBase - 0x620 + DataPort, Data);
#else
    outpw(aweBase - 0x620 + DataPort, Data);
    outpw(aweBase - 0x620 + DataPort + 2, Data >> 16);
#endif

    enable();
}

/* Read 16-bit EMU8K register */
static UWORD aweReadWord(UWORD Command, UWORD DataPort) {
    UWORD k;

    disable();

    outpw(aweBase + 0x802, Command);    /* select index */
    k = inpw(aweBase - 0x620 + DataPort);

    enable();

    return k;
}

/* Read 32-bit EMU8K register */
static ULONG aweReadDWord(UWORD Command, UWORD DataPort) {
    ULONG k;

#ifdef __DJGPP__
    disable();
        
    /* DJGPP optimization */
    outportw(aweBase + 0x802, Command); /* select index */
    k = inportl(aweBase - 0x620 + DataPort);
#else
    ULONG Temp;

    disable();

    outpw(aweBase + 0x802, Command);    /* select index */
    k = inpw(aweBase - 0x620 + DataPort);
    Temp = inpw(aweBase - 0x620 + DataPort + 2);
    k |= Temp << 16;
#endif

    enable();

    return k;
}

/* Detects any AWE32 device at the port aweBase */
static BOOL aweDetect(void) {
    /* Do a test */
    if ((aweReadWord(0xE0, 0xE20) & 0x0C) != 0x0C) return FALSE;
    if ((aweReadWord(0x3D, 0xA20) & 0x58) != 0x58) return FALSE;
    if ((aweReadWord(0x3E, 0xA20) & 0x03) != 0x03) return FALSE;
    
    return TRUE;    /* we found it! */
}

/* Writes the given set of initialisation arrays to the card. */
static void aweWriteInitArrays(UWORD *init1, UWORD *init2, UWORD *init3, UWORD *init4) {
    int i;
 
    for (i = 0; i < 32; i++) aweWriteINIT1(i, init1[i]);
    for (i = 0; i < 32; i++) aweWriteINIT2(i, init2[i]);
    for (i = 0; i < 32; i++) aweWriteINIT3(i, init3[i]);
    for (i = 0; i < 32; i++) aweWriteINIT4(i, init4[i]);
}

static SLONG aweTimerDiff(SLONG t1, SLONG t2) {
    if (t1 < t2) t1 += 0x10000;
    return t1 - t2;
}

/*
    Wait for some EMU clocks (1/44100 sec)
    Now does real high precision waits. ;)
*/
static void aweWait(SLONG Clocks) {
    SLONG k;

    k = aweReadWC();    /* 44100Hz clock */
    while (aweTimerDiff(aweReadWC(), k) < Clocks);
}

/* Initialization of the EMU8K hardware */
/* This is the true "by the book" E-mu initialization. :) */
static void aweInit(void) {
    UWORD k;

    /* Turn off audio */
    aweWriteHWCF3(0x0000);  /* according to the MikMod 3 sources */

    /* Initialize */
    aweWriteHWCF1(0x0059);
    aweWriteHWCF2(0x0020);

    /* Turn off envelope engine */
    for (k = 0; k < AWE_TOTAL_CHANNELS; k++) {
        aweWriteDCYSUSV(k, 0x0080);
    }

    /* Initialize required envelope and sound engines */
    for (k = 0; k < AWE_TOTAL_CHANNELS; k++) {
        aweWriteENVVOL(k, 0);
        aweWriteENVVAL(k, 0);
        aweWriteDCYSUS(k, 0);
        aweWriteATKHLDV(k, 0);
        aweWriteLFO1VAL(k, 0);
        aweWriteATKHLD(k, 0);
        aweWriteLFO2VAL(k, 0);
        aweWriteIP(k, 0);
        aweWriteIFATN(k, 0);
        aweWritePEFE(k, 0);
        aweWriteFMMOD(k, 0);
        aweWriteTREMFRQ(k, 0);
        aweWriteFM2FRQ2(k, 0);
        aweWritePTRX(k, 0);
        aweWriteVTFT(k, 0);
        aweWritePSST(k, 0);
        aweWriteCSL(k, 0);
        aweWriteCCCA(k, 0);
    }

	/* Initialize "current" registers */
    for (k = 0; k < AWE_TOTAL_CHANNELS; k++) {
        aweWriteCPF(k, 0);
        aweWriteCVCF(k, 0);
    }

    /* Initialize sound memory DMA registers */
    aweWriteSMALR(0);
    aweWriteSMARR(0);
    aweWriteSMALW(0);
    aweWriteSMARW(0);

    /* Copy first initialization array set */
    aweWriteInitArrays(aweInit1_1, aweInit1_2, aweInit1_3, aweInit1_4);
     
    /* Wait for 1024 sample periods; i.e. 24 ms */
    aweWait(1024);

    /* Copy second initialization array set */
    aweWriteInitArrays(aweInit2_1, aweInit2_2, aweInit2_3, aweInit2_4);

    /* Copy third initialization array set */
    aweWriteInitArrays(aweInit3_1, aweInit3_2, aweInit3_3, aweInit3_4);

    aweWriteHWCF4(0);
    aweWriteHWCF5(0x83);
    aweWriteHWCF6(0x8000);

    /* Copy fourth initialization array set */
    aweWriteInitArrays(aweInit4_1, aweInit4_2, aweInit4_3, aweInit4_4);

    /* Init DRAM refresh; courtesy Judge Dredd ;) */

    /* Setup oscillator 30 */
    aweWriteDCYSUSV(30, 0x80);
    aweWritePSST(30, 0xFFFFFFE0);
    aweWriteCSL(30, 0x00FFFFE8);
    aweWritePTRX(30, 0x0);
    aweWriteCPF(30, 0x0);
    aweWriteCCCA(30, 0x00FFFFE3);

    /* Setup oscillator 31 */
    aweWriteDCYSUSV(31, 0x80);
    aweWritePSST(31, 0x00FFFFF0);
    aweWriteCSL(31, 0x00FFFFF8);
    aweWritePTRX(31, 0xFF);
    aweWriteCPF(31, 0x8000);
    aweWriteCCCA(31, 0x00FFFFF3);

    /* Tight DRAM refresh timing loop */
    disable();
    outpw(aweBase + 0x802, 0x3E);               /* Select index */
    outpw(aweBase, 0);                          /* Register 0x101E */

    while (!(inpw(aweBase + 0x802) & 0x1000));
    while (inpw(aweBase + 0x802) & 0x1000);

    outpw(aweBase + 0x2, 0x4828);               /* Okay, now write the high word */
    outpw(aweBase + 0x802, 0x3C);               /* Select index */
    outpw(aweBase + 0x400, 0);                  /* Register 0x141C */
    enable();

    /* Finale touch */
    aweWriteVTFT(30, 0xFFFFFFFF);
    aweWriteVTFT(31, 0xFFFFFFFF);

    /* Enable audio output. Yeah! */
    aweWriteHWCF3(0x0004);
}

/*
	Enable AWE32 DRAM access.
    If read_write is true then this routines sets up the hardware for
    both reading and writing. In that case 15 channels are dedicated
    for reading and 15 for writing. On the other hand, if read_write is
	false then all the channels are setup for writing only.
*/
static void aweEnableDRAM(BOOL read_write) {
    UWORD k;

    for (k = 0; k < AWE_USEABLE_CHANNELS; k++) {
        aweWriteDCYSUSV(k, 0x80);
        aweWriteVTFT(k, 0);
        aweWriteCVCF(k, 0);
        aweWritePTRX(k, 0x40000000);
        aweWriteCPF(k, 0x40000000);
		aweWritePSST(k, 0);
        aweWriteCSL(k, 0);
		aweWriteCCCA(k, (((k & 1) && read_write) ? 0x04000000 : 0x06000000));
	}
}

/* Disable AWE32 DRAM access */
static void aweDisableDRAM(void) {
	UWORD k;

	/* Disable DRAM access */
	for (k = 0; k < AWE_USEABLE_CHANNELS; k++) {
		aweWriteCCCA(k, 0);
		aweWriteDCYSUSV(k, 0x807F);
	}
}

/* Check the sample RAM size */
static ULONG aweCheckDRAM(void) {
    if (aweDRAMSize > 0) return aweDRAMSize;

    aweEnableDRAM(TRUE);

	aweWaitLW();							/* wait till ready to write */
    aweWriteSMALW(AWE_DRAM_START);          /* Address for writing */
    aweWriteSMLD(0xDEAD);                   /* write some test pattern */
    aweWriteSMLD(0xBEEF);                   /* DEAD BEEF!!! */
    
	while (aweDRAMSize < (28 * 1024)) {
		aweWaitLW();						/* wait till data is written */
		aweWaitLR();						/* wait till ready to read */
		aweWriteSMALR(AWE_DRAM_START);      /* Address for reading */
		aweReadSMLD();                      /* Skip first "stale" word */
		if (aweReadSMLD() != 0xDEAD) break;	/* check for address wrap */
		if (aweReadSMLD() != 0xBEEF) break; /* ditto */
		aweDRAMSize += 32;					/* increment size by 32 */
        aweWaitLW();
        aweWriteSMALW(AWE_DRAM_START + aweDRAMSize * 512UL); /* Address for writing */
        aweWriteSMLD(0x1234);
        aweWriteSMLD(0xABCD);
    }
    
    aweDisableDRAM();

	/* Do not use the last 1 kB (reserved & unusable) */
    if (aweDRAMSize == (28 * 1024)) aweDRAMSize--;

    /* Convert to bytes */
    aweDRAMSize *= 1024UL;
    
    return aweDRAMSize;
}

/*
    Turns the note off for the given channel.
    Use this to ramp.
    Value = 0x80xx (both).
	0x7F or 127 (7 bits) is the max value that can be passed!
	127 = min time, 1 = max time, 0 = no change.
	127 gives min of 140 usec/db, 1 gives max of 470 msec/db.
	92 gives 100 msec...
*/
static void aweNoteOff(SWORD gChan) {
	aweWriteDCYSUSV(gChan, 0x807F);
	aweWriteDCYSUS(gChan, 0x807F);
}

/*
    The fastest possible destroying of the note
    It can cause a click!
*/
static void aweNoteCut(SWORD gChan) {
    aweWriteDCYSUSV(gChan, 0x80);
    aweWriteVTFT(gChan, 0x0);
    aweWriteCVCF(gChan, 0x0);
    aweWritePTRX(gChan, 0x0);
    aweWriteCPF(gChan, 0x0);
}

/* Starts a new note */
static void aweNoteOn(SWORD gChan, ULONG base, ULONG start, ULONG loopstart, ULONG loopend, UWORD flags) {
    base += AWE_DRAM_START;
    if (flags & SF_BIDI) loopend += (loopend - loopstart);
    if (!(flags & SF_LOOP)) loopend += AWE_ANTICLICK - AWE_INTERPOLATION_POINTS;

    /* Speak! */
    aweWriteENVVOL(gChan, 0x8000);
    aweWriteENVVAL(gChan, 0x8000);
    aweWriteDCYSUS(gChan, 0x7F7F);
    aweWriteATKHLDV(gChan, 0x7F7F);
    /*aweWriteLFO1VAL(gChan, 0x8000);*/
    aweWriteATKHLD(gChan, 0x7F7F);
    /*aweWriteLFO2VAL(gChan, 0x8000);*/
    /*aweWriteIP(gChan, 0xE000);*/
    /*aweWriteIFATN(gChan, 0xFF00);*/
    /*aweWritePEFE(gChan, 0x0);*/
    /*aweWriteFMMOD(gChan, 0x0);*/
    aweWriteTREMFRQ(gChan, 0x10);
    aweWriteFM2FRQ2(gChan, 0x10);

    aweWritePSST(gChan, base + loopstart);
    aweWriteCSL(gChan, base + loopend);
    aweWriteCCCA(gChan, base + start);

    aweWriteVTFT(gChan, 0x0000FFFF);
    aweWriteCVCF(gChan, 0x0000FFFF);
    aweWriteDCYSUSV(gChan, 0x7F7F);
    aweWritePTRX(gChan, 0x40000000);
    aweWriteCPF(gChan, 0x40000000);
}

static void aweSetPan(SWORD gChan, UBYTE pan) {
    aweWritePSST(gChan, ((ULONG)(255 - pan) << 24LU) | (aweReadPSST(gChan) & 0x00FFFFFF));
}

static void aweSetVolume(SWORD gChan, UBYTE vol) {
	aweWriteLFO1VAL(gChan, 0x8000);
	aweWriteLFO2VAL(gChan, 0x8000);
	aweWriteIFATN(gChan, 0xFF00 | aweVolumeTable[vol]);
	aweWritePEFE(gChan, 0x0);
    aweWriteFMMOD(gChan, 0x0);
}

static void aweSetFreq(SWORD gChan, ULONG frq) {
    SLONG i;
    SLONG f, fm;

    if (frq > 8192) {
        /* calculate using high-frequency table */
        frq -= 8191;
        f = frq & 127;
        fm = 128 - f;
        i = frq >> 7;
		if (i >= AWE_FRQ_MAX) i = AWE_FRQ_MAX - 1;
		i = ((SLONG)aweHighFrqTable[i] * fm + (SLONG)aweHighFrqTable[i + 1] * f) >> 7; /* linear interpolation */
	} else {
		f = frq & 15;
		fm = 16 - f;
		i = frq >> 4;
		if (i < 1) i = 1;
		i = ((SLONG)aweLowFrqTable[i] * fm + (SLONG)aweLowFrqTable[i + 1] * f) >> 4; /* linear interpolation */
    }

    aweWriteIP(gChan, (UWORD)i);
}

#if 0
/* Can be used with advanced channel allocation algorithms */
static ULONG awePosition(SWORD channel) {
    /* 24-bit address space */
    return (aweReadCCCA(channel) & 0xFFFFFF) - AWE_DRAM_START;
}
#endif

/* EMU clean-up routine */
static void aweDone(void) {
    SWORD k;

    for (k = 0; k < AWE_TOTAL_CHANNELS; k++) {
        aweNoteCut(k);
    }

    aweInit();              /* This is Nicklas's idea, not mine ;) */
}

/*
    Uploads sample/instrument data to the AWE's DRAM.
    EMU8K only accepts 16-bit signed data, so it's our responsibility to
    convert the sample data to 16-bit before uploading it to the DRAM.
    16-bit samples are assumed to be signed. Length is in samples!
*/
static void aweUploadSamples(SWORD *buffer, ULONG address, ULONG samples) {
    ULONG i;

    aweEnableDRAM(FALSE);
    aweWaitLW();
    aweWriteSMALW(AWE_DRAM_START + address);    /* write start address */

    for (i = 0; i < samples; i++) {
        aweWriteSMLD(buffer[i]);                /* upload data to AWE32 DRAM */
    }

    aweWaitLW();
    aweDisableDRAM();
}

/* Allocates a physical channel to a virtual channel */
/* Can be improved ;) */
static SWORD aweChanAlloc(UBYTE voice) {
    SWORD i, voc = -1, chan = -1;
    UBYTE vol = 0xFF;

    /* Go through the physical channel array to find an unused channel */
    for (i = 0; i < AWE_USEABLE_CHANNELS; i++) {
        if (aweChannel[i] == -1) {
            aweChannel[i] = voice;
            return i;
        }
    }

    /*
        No unused channel found? Do an intelligent ;) search to find a
        voice with the least priority and steal it's physical channel
    */
    for (i = 0; i < AWE_TOTAL_CHANNELS; i++) {
        if (aweVoice[i].handle != -1 && aweVoice[i].channel != -1) {
            /* We can't steal any channel which are looping! */
            if (!(aweVoice[i].flags & SF_LOOP) && !(aweVoice[i].flags & SF_BIDI)) {
                /* Select a single-shot channel with the lowest volume */
                if (aweVoice[i].vol < vol) {
                    /* Remember this voice's volume and physical channel */
                    vol = aweVoice[i].vol;
                    chan = aweVoice[i].channel;
                    voc = i;
                }
            }
        }
    }

    if (chan != -1) {
        /* Steal the channel! */
        aweChannel[chan] = voice;
        /* Invalidate the bankrupt voice's channel no. */
        aweVoice[voc].channel = -1;
    }

    /* Ofcourse it may also happen that we may not find any channel to steal,
        in that case the current voice just won't play. Yeah, this means that
        all physical channels are looping! */
    
    return chan;
}

/* Allocates memory from the AWE memory DRAM in SAMPLES */
static SWORD aweMemAlloc(ULONG samples) {
    int i, j;

    for (i = 0; i < MAXSAMPLEHANDLES; i++) {
        if (aweDRAM[i].active && aweDRAM[i].empty && aweDRAM[i].size >= samples) {
            /* We got an empty slot! */

            /* If the slot has some bytes more than what we need reserve
                it for future use */
            if (aweDRAM[i].size != samples) {
                /* Find an inactive handle to store the rest of the block */
                /* Note that '<=' */
                for (j = 0; j <= MAXSAMPLEHANDLES; j++) {
                    if (!aweDRAM[j].active) break;
                }

                if (aweDRAM[j].active) {
                    return -2;      /* no free inactive handles */
                }

                /* Now store the rest of the block from the current handle
                to the inactive handle and make it active */
                aweDRAM[j].active = TRUE;
                aweDRAM[j].empty = TRUE;
                aweDRAM[j].offset = aweDRAM[i].offset + samples;
                aweDRAM[j].size = aweDRAM[i].size - samples;
            }

            /* Now we can use this block with ease */
            aweDRAM[i].empty = FALSE;
            aweDRAM[i].size = samples;

            return i;
        }
    }

    return -1;      /* failed: memory too fragmented or no memory left */
}

/* Frees memory allocated from the AWE DRAM */
static BOOL aweMemFree(SWORD handle) {
    int i, j;

    /* Checks for invalid arguments */
    if (handle < 0 || handle >= MAXSAMPLEHANDLES || !aweDRAM[handle].active || aweDRAM[handle].empty) return FALSE;

    /* Simply free the block by setting its empty field to TRUE */
    aweDRAM[handle].empty = TRUE;

    /* That was so easy, but now starts the real pain */
    /* Consolidate the memory bocks as much as possible to prevent
        fragmentation! */
    for (i = 0; i < MAXSAMPLEHANDLES; i++) {
        /* Note that '<=' */
        if (aweDRAM[i].active && aweDRAM[i].empty) {
            for (j = 0; j <= MAXSAMPLEHANDLES; j++) {
                if (aweDRAM[j].active && aweDRAM[j].empty) {
                    /* Check if these two blocks are contigious */
                    if ((aweDRAM[j].offset == (aweDRAM[i].offset + aweDRAM[i].size)) || (aweDRAM[i].offset == (aweDRAM[j].offset + aweDRAM[j].size))) {
                        /* Join the blocks */
                        aweDRAM[i].offset = min(aweDRAM[i].offset, aweDRAM[j].offset);
                        aweDRAM[i].size += aweDRAM[j].size;
                        aweDRAM[j].active = aweDRAM[j].empty = FALSE;
                    }
                }
            }
        }
    }

    return TRUE;
}

/*
    Optimize usage of the AWE's DRAM
    Olso crunches samples to make them fit into the limited AWE DRAM
    This works but it's terrible. Could somebody do it right?
*/
static void aweMemOptimize(void) {
    int i;
    ULONG sampLen = 0;
    ULONG padLen = 0;   /* for the trailing silence */
    SWORD *buf;
    size_t j;
    ULONG fsize, bsize;

    /* Find out the total size of the loaded samples */
    for (i = 0; i < MAXSAMPLEHANDLES; i++) {
        if (!aweRawSample[i].empty) {
            sampLen += ((aweRawSample[i].samples * 2) + (aweRawSample[i].bidilen * 2));
            padLen += (AWE_ANTICLICK * 2);
        }
    }

    /* Now see if we really need to crunch the samples */
    if ((sampLen + padLen) < aweDRAMSize) {
        /* Set magic number to 1, i.e. no downsampling ;) */
        aweMemMagic = 1;
    }
    else {
        /* Calculate magic number */
        /* Note: Obviously we can't downsample the pad space */
        aweMemMagic = (double)sampLen / (double)(aweDRAMSize - padLen);
    }
    
    /* Release all AWE banks */
    for (i = 0; i < MAXSAMPLEHANDLES; i++) {
        /* The AWE Memory Manager can protect itself from crap input */
        aweMemFree(aweRawSample[i].handle);
        aweRawSample[i].handle = -1;
    }

    /*
        Now:
            1) calculate the crunched sample length in bytes
            2) allocate the same amount of DRAM from the AWE
            3) upload the crunched sample
    */
    for (i = 0; i < MAXSAMPLEHANDLES; i++) {
        if (!aweRawSample[i].empty) {
            fsize = (ULONG)((double)aweRawSample[i].samples / aweMemMagic);
            bsize = (ULONG)((double)aweRawSample[i].bidilen / aweMemMagic);
            aweRawSample[i].nSamples = fsize + bsize;

            /* Allocate main memory to setup the sound */
            if ((buf = calloc(aweRawSample[i].nSamples + AWE_ANTICLICK, sizeof(SWORD))) == NULL) {
                continue;
            }

            /* Downsample */
            for (j = 0; j < fsize; j++) {
                buf[j] = aweRawSample[i].sound[(size_t)((double)j * aweMemMagic)];
            }

            /* Also downsample unrolling samples (BIDI) */
            if (bsize > 0) {
                for (j = 0; j < bsize; j++) {
                    buf[(size_t)(((double)aweRawSample[i].loopend / aweMemMagic) + j)] = aweRawSample[i].sound[(size_t)((double)aweRawSample[i].loopend - ((double)j * aweMemMagic))];
                }
                /* Setup BIDI sound */
                for (j = 0; j <= AWE_INTERPOLATION_POINTS; j++) {
					buf[(size_t)(((double)aweRawSample[i].loopend / aweMemMagic) + bsize + j)] = aweRawSample[i].sound[(size_t)((double)aweRawSample[i].loopstart + ((double)j * aweMemMagic))];
                }
            }
                
            /* Setup looping sound */
            if ((aweRawSample[i].flags & SF_LOOP) && !(aweRawSample[i].flags & SF_BIDI)) {
                for (j = 0; j <= AWE_INTERPOLATION_POINTS; j++) {
                    buf[(size_t)(((double)aweRawSample[i].loopend / aweMemMagic) + j)] = aweRawSample[i].sound[(size_t)((double)aweRawSample[i].loopstart + ((double)j * aweMemMagic))];
                }
            }

            if ((aweRawSample[i].handle = aweMemAlloc(aweRawSample[i].nSamples + AWE_ANTICLICK)) < 0) {
                free(buf);
                continue;
            }
            
            /* Upload sample to DRAM */
            aweUploadSamples(buf, aweDRAM[aweRawSample[i].handle].offset, aweRawSample[i].nSamples + AWE_ANTICLICK);

            /* Free buffer */
            free(buf);
        }
    }
    
    aweMemOptimized = TRUE;     /* last (but important!) step */
}

/* Updates sound buffer and sends them to the hardware */
static void interrupt sbNewInt(MIRQARGS) {
    int t;
    SWORD chan, vHandle;
    UWORD vFlags;
    UBYTE vol, pan;
    ULONG base, start, reppos, repend, size, frq;
    SLONG oldTimer, diff;
    static SLONG newTimer;  /* preserve this between calls */

    sbStartSilence();
    inportb(SB_DSP_DATA_AVAIL);

    oldTimer = newTimer;
    newTimer = aweReadWC();
    diff = aweTimerDiff(newTimer, oldTimer);
    if (diff > aweTimerReq) sbSilenceLenAdd--;
    if (diff < aweTimerReq) sbSilenceLenAdd++;

    MIrq_EOI(sbIRQ);

    /* Adjust BPM */
    if (aweBPM != md_bpm) sbSetBPM(md_bpm);

    if (!aweMemOptimized) {
        md_player();
        return;
    }

    for (t = 0; t < md_numchn; t++) {
        chan = aweVoice[t].channel;
        vHandle = aweVoice[t].handle;
        vFlags = aweVoice[t].flags;
        frq = aweVoice[t].frq;
        vol = aweVoice[t].vol;
        pan = aweVoice[t].pan;

        if (pan != aweVoice[t].panold && chan != -1 && vHandle != -1) {
            /*
                When panning changes set volume to 0
                This will help us remove (some) clicks
            */
            aweSetVolume(chan, 0);
        }

        if (aweVoice[t].kick && chan != -1 && vHandle != -1) {
            aweVoice[t].kick = FALSE;

            base = aweDRAM[aweRawSample[vHandle].handle].offset;
            start = aweVoice[t].start;
            reppos = aweVoice[t].reppos;
            repend = aweVoice[t].repend;
            size = aweVoice[t].size;

            aweNoteCut(chan);

            if (vFlags & SF_LOOP) {
                aweNoteOn(chan, base, start, reppos, repend, vFlags);
            }
            else {
                aweNoteOn(chan, base, start, size, size, vFlags);
            }
			aweSetFreq(chan, frq);
            aweSetPan(chan, pan);
            aweSetVolume(chan, vol);
            aweVoice[t].panold = pan;
        }
        else {
            if (chan != -1 && vHandle != -1) {
                aweSetFreq(chan, frq);
                aweSetPan(chan, pan);
                aweSetVolume(chan, vol);
                aweVoice[t].panold = pan;
            }
        }
    }

    md_player();

    /* Ramp down voices that need to be started next */
    for (t = 0; t < md_numchn; t++) {
        if (aweVoice[t].kick && aweVoice[t].channel != -1 && aweVoice[t].handle != -1) {
			aweNoteOff(aweVoice[t].channel);
        }
    }
}

/****************************************************************************\
*                                                                            *
*   The actual driver callback functions                                     *
*                                                                            *
\****************************************************************************/

/*
    Locate the EMU8000. This tries to extract the base port from the E
    section of the BLASTER environment variable, and then does some test
    reads to check that there is an EMU8000 there.
*/
static BOOL AWE_IsThere(void) {
    aweBase = sbGetSetting('E', TRUE, 0xFFFF);
    if (aweBase == 0xFFFF) return FALSE;

    return (aweDetect() && sbIsThere());
}

/* Uploads an instrument to the AWE's DRAM */
static SWORD AWE_SampleLoad(FILE *fp, ULONG length, ULONG loopstart, ULONG loopend, UWORD flags) {
    SWORD handle;

    /* We want all samples to be auto-converted to signed 16-bits */
    SL_Init(fp, flags, flags | SF_SIGNED | SF_16BITS);

    /* Find empty slot to put sample address in */
    for (handle = 0; handle < MAXSAMPLEHANDLES; handle++) {
        if (aweRawSample[handle].empty) break;
    }

    if (handle == MAXSAMPLEHANDLES) {
        myerr = ERROR_OUT_OF_HANDLES;
        return -1;
    }

    /* Save the sample in main memory */
    if ((aweRawSample[handle].sound = calloc(length, sizeof(SWORD))) == NULL) {
        myerr = ERROR_SAMPLE_TOO_BIG;
        return -1;
    }
    
    /* Get sample data */
    SL_Load(aweRawSample[handle].sound, length * sizeof(SWORD));

    /* Set handle details */
    aweRawSample[handle].empty = FALSE;
    aweRawSample[handle].handle = -1;
    aweRawSample[handle].samples = length;
    aweRawSample[handle].loopstart = loopstart;
    aweRawSample[handle].loopend = loopend;
    aweRawSample[handle].flags = flags;
    aweRawSample[handle].nSamples = length;
	aweRawSample[handle].bidilen = ((flags & SF_BIDI) ? (loopend - loopstart) : 0);
    
    /* Clear this; so we optimize again */
    aweMemOptimized = FALSE;

    /* Return handle to caller */
    return handle;
}

/* Unloads/frees instruments from the AWE's DRAM and memory */
static void AWE_SampleUnload(SWORD handle) {
    aweMemFree(aweRawSample[handle].handle);
    if (aweRawSample[handle].sound != NULL) free(aweRawSample[handle].sound);
    aweRawSample[handle].empty = TRUE;
    aweRawSample[handle].sound = NULL;
    aweRawSample[handle].handle = -1;
    aweMemOptimized = FALSE;
}

/* Initialization of the AWE32 hardware */
static BOOL AWE_Init(void) {
    int i;
    
    md_mode |= DMODE_16BITS;        /* AWE can't do 8 bit mixing */
    md_mode |= DMODE_STEREO;        /* AWE can't do mono mixing */
    md_mode |= DMODE_INTERP;        /* AWE always does interpolated mixing */
    md_mixfreq = 44100;             /* AWE mixes only at CD sampling rate */

    /* Check for the presence of an AWE32/64 */
    if (!AWE_IsThere()) {
        myerr = "Sound Blaster AWE not detected";
        return FALSE;
    }

    /* Setup hardware */
    sbResetDSP();
    aweInit();

    /* Find out the total amount of onboard DRAM */
    if (aweCheckDRAM() < (512 * 1024)) {
        myerr = "Sound Blaster AWE with insufficient onboard DRAM";
        return FALSE;
    }

    /* Change driver name to reflect DRAM size ;) */
    sprintf(aweDriverName, AWE_DRIVER_NAME_FORMAT, aweDRAMSize / 1024);
    
    /* Initialize AWE DRAM manager */
    /* Note that '<=' */
    for (i = 0; i <= MAXSAMPLEHANDLES; i++) {
        aweDRAM[i].active = aweDRAM[i].empty = FALSE;
        aweDRAM[i].offset = aweDRAM[i].size = 0;
    }
    
    for (i = 0; i < MAXSAMPLEHANDLES; i++) {
        aweRawSample[i].empty = TRUE;
        aweRawSample[i].sound = NULL;
        aweRawSample[i].handle = -1;
    }

    /* Now put the whole DRAM block in the first handle */
    aweDRAM[0].active = aweDRAM[0].empty = TRUE;
    aweDRAM[0].size = aweDRAMSize / sizeof(SWORD);  /* total samples */

    sbOldInt = MIrq_SetHandler(sbIRQ, sbNewInt);

    return TRUE;
}

/* Shuts down the digital audio subsystem */
static void AWE_Exit(void) {
    MIrq_OnOff(sbIRQ, 0);
    MIrq_SetHandler(sbIRQ, sbOldInt);
    aweDone();
    sbResetDSP();
    sbResetDSP();
}

/* Prepare hardware for sound playback */
static void AWE_PlayStart(void) {
    UWORD t;

    /* Clear all voices */
    for (t = 0; t < AWE_TOTAL_CHANNELS; t++) {
        aweVoice[t].kick = FALSE;
        aweVoice[t].flags = 0;
        aweVoice[t].handle = -1;
        aweVoice[t].channel = -1;
        aweVoice[t].start = 0;
        aweVoice[t].size = 0;
        aweVoice[t].reppos = 0;
        aweVoice[t].repend = 0;
        aweVoice[t].frq = 10000;
        aweVoice[t].vol = 0;
        aweVoice[t].pan = (t & 1) ? AWE_PAN_LEFT : AWE_PAN_RIGHT;
        aweVoice[t].panold = (t & 1) ? AWE_PAN_RIGHT : AWE_PAN_LEFT;
    }

    /* Free all hardware channels */
    for (t = 0; t < AWE_USEABLE_CHANNELS; t++) {
        aweChannel[t] = -1;
        aweNoteCut(t);
    }

    /* Setup SB DAC and it's interrupt handler */
    sbResetDSP();
    MIrq_OnOff(sbIRQ, 1);
    sbWriteDSP(0x40);
    sbWriteDSP(SB_TC);
    sbStartSilence();
    sbSilenceLenAdd = 0;
    sbSetBPM(125);
}

/* Stops playback of sound */
static void AWE_PlayStop(void) {
    UWORD i;

    MIrq_OnOff(sbIRQ, 0);

    /* Ramp down all channels */
    for (i = 0; i < AWE_USEABLE_CHANNELS; i++) {
        aweNoteOff(i);
    }
}

/* Dummy function */
static void AWE_Update(void) {}

/* Change voice volume */
static void AWE_VoiceSetVolume(UBYTE voice, UBYTE vol) {
    aweVoice[voice].vol = vol;
}

/* Change voice pitch */
static void AWE_VoiceSetFrequency(UBYTE voice, ULONG frq) {
    aweVoice[voice].frq = (ULONG)((double)frq / aweMemMagic);
}

/* Change voice panning */
static void AWE_VoiceSetPanning(UBYTE voice, UBYTE pan) {
    aweVoice[voice].pan = pan;
}

/* Start a voice */
static void AWE_VoicePlay(UBYTE voice, SWORD handle, ULONG start, ULONG size, ULONG reppos, ULONG repend, UWORD flags) {
    if (start >= size) return;

    if (flags & SF_LOOP) {
        if (repend > size) repend = size;    /* repend can't be bigger than size */
    }

    /* Optimize AWE DRAM if needed */
    if (!aweMemOptimized) {
        MIrq_OnOff(sbIRQ, 0);
        aweMemOptimize();
        sbResetDSP();
        MIrq_OnOff(sbIRQ, 1);
        sbWriteDSP(0x40);
        sbWriteDSP(SB_TC);
        sbStartSilence();
        sbSilenceLenAdd = 0;
        sbSetBPM(125);
    }

    /* See if we've already allocated a physical channel for this voice */
    if (aweVoice[voice].channel == -1) {
        /* No? Allocate a physical channel */
        aweVoice[voice].channel = aweChanAlloc(voice);
    }

    aweVoice[voice].flags = flags;
    aweVoice[voice].handle = handle;
    aweVoice[voice].start = (ULONG)((double)start / aweMemMagic);
    aweVoice[voice].size = (ULONG)((double)size / aweMemMagic);
    aweVoice[voice].reppos = (ULONG)((double)reppos / aweMemMagic);
    aweVoice[voice].repend = (ULONG)((double)repend / aweMemMagic);
    aweVoice[voice].kick = TRUE;
}


/* Our driver interface structure */
DRIVER drv_awe = {
    NULL,
    aweDriverName,
    "MikMod Sound Blaster AWE Driver v"DRIVER_VERSION" by Blade",
    AWE_IsThere,
    AWE_SampleLoad,
    AWE_SampleUnload,
    AWE_Init,
    AWE_Exit,
    AWE_PlayStart,
    AWE_PlayStop,
    AWE_Update,
    AWE_VoiceSetVolume,
    AWE_VoiceSetFrequency,
    AWE_VoiceSetPanning,
    AWE_VoicePlay
};
