#include "x86.h"

#if !defined ( __SILVER_H_ )
#define __SILVER_H_

#define TEXT 't'
#define GRAPHICS 'g'


#define	VGA_AC_INDEX		0x3C0
#define	VGA_AC_WRITE		0x3C0
#define	VGA_AC_READ		0x3C1
#define	VGA_MISC_WRITE		0x3C2
#define VGA_SEQ_INDEX		0x3C4
#define VGA_SEQ_DATA		0x3C5
#define	VGA_DAC_READ_INDEX	0x3C7
#define	VGA_DAC_WRITE_INDEX	0x3C8
#define	VGA_DAC_DATA		0x3C9
#define	VGA_MISC_READ		0x3CC
#define VGA_GC_INDEX 		0x3CE
#define VGA_GC_DATA 		0x3CF
/*			COLOR emulation		MONO emulation */
#define VGA_CRTC_INDEX		0x3D4		/* 0x3B4 */
#define VGA_CRTC_DATA		0x3D5		/* 0x3B5 */
#define	VGA_INSTAT_READ		0x3DA

#define	VGA_NUM_SEQ_REGS	5
#define	VGA_NUM_CRTC_REGS	25
#define	VGA_NUM_GC_REGS		9
#define	VGA_NUM_AC_REGS		21
#define	VGA_NUM_REGS		(1 + VGA_NUM_SEQ_REGS + VGA_NUM_CRTC_REGS + \
				VGA_NUM_GC_REGS + VGA_NUM_AC_REGS)


extern unsigned char g_40x25_text[], g_40x50_text[], g_80x25_text[], g_80x50_text[], g_90x30_text[], g_90x60_text[], g_640x480x2[], g_320x200x4[], g_640x480x16[], g_720x480x16[], g_320x200x256[], g_320x200x256_modex[];

class Silver
{
 private:
    void write_regs(unsigned char *);
 public:
    static char maxx, maxy, type;
    Silver();
    ~Silver();
    void init();
    void set_mode(unsigned char *);
};

#endif
