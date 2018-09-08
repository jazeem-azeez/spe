#include "x86.h"
#include "iostream.h"

#if !defined ( __FDC_H_ )
#define __FDC_H_

class FDC
{
 private:
    /* IO ports */
    #define FDC_DOR  (0x3f2)   /* Digital Output Register */
    #define FDC_MSR  (0x3f4)   /* Main Status Register (input) */
    #define FDC_DRS  (0x3f4)   /* Data Rate Select Register (output) */
    #define FDC_DATA (0x3f5)   /* Data Register */
    #define FDC_DIR  (0x3f7)   /* Digital Input Register (input) */
    #define FDC_CCR  (0x3f7)   /* Configuration Control Register (output) */

    #define CMD_VERSION (0x10)  /* FDC version */
 public:
    FDC();
    ~FDC();
    void init();
    void sendbyte(int);
    int getbyte();
};



#endif
