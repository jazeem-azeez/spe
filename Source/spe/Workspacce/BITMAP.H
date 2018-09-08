#ifndef BITMAP_H
#define BITMAP_H


	typedef unsigned char BYTE;
	typedef unsigned int WORD;
	typedef unsigned long DWORD;

	typedef struct FILE_HEADER
	 {
	  char B,M;
	  DWORD FileSize;
	  WORD Reserved1;
	  WORD Reserved2;
	  DWORD DataOffset;
	 }FILE_HEADER;

	typedef struct INFO_HEADER
	 {
	  DWORD StructSize;
	  long Width;
	  long Height;
	  WORD NumPlanes;
	  WORD BitCount;
	  DWORD Compr;
	  DWORD ImageSize;
	  long Xpix;
	  long Ypix;
	  DWORD ClrUsed;
	  DWORD ClrImp;
	 }INFO_HEADER;

	typedef struct RGB_QUAD
	 {
	  BYTE Blue;
	  BYTE Green;
	  BYTE Red;
	  BYTE Reserved;
	 }RGB_QUAD;

	struct FILE_HEADER our_fhdr=
	 {
	  'B','M',308278,0,0,1078
	 };
	struct INFO_HEADER our_ihdr=
	 {
	  40,640,480,1,8,0,307200,50190,50190,256,0
	 };

	class BITMAP
	 {
	  private:
		   FILE_HEADER *fHead;
		   INFO_HEADER *iHead;
		   RGB_QUAD *color;
	  public:
		   int ReadBitmapData(FILE *);
		   void DisplayBitmap(FILE *);
		   void LoadBitmap(char *);
	 };
#endif