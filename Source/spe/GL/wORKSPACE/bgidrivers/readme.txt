im only the second publisher (found it in a site).

from the svga32k & svga64k & svgaTC & svgaS3  (all the high color drivers)
only the svga64k works for me.
in win xp only mode 0 and 3 are working (320X200 & 640X480)
but i have a problem with all my svga drivers above 640X480.
in win 98 all modes but 1 and 2 are working.

to replace color in high color driver (the 4 drivers above)
use instead setcolor - setrgbpalette(1024,redstrenght,greenstrenght,bluestrenght,)
				     ^
number 1024 for regular color, 1025 for fill color, 1026 for real color.

max color strenght for svga32k is red - 0-31, green - 0-31, blue - 0-31. 
max color strenght for svga64k is red - 0-31, green - 0-63, blue - 0-31. 
max color strenght for svgaS3 is red - 0-255, green - 0-255, blue - 0-255. 



i also puted a unit of my own that simplify the usage of the svga64k
driver. i hope you will anjoy it.
in my unit you dont have to put on setrgbcolor the 1024/1025 - its 
automaticly put for them both like setrgbcolor(redstrenght,greenstrenght,bluestrenght);
and modes 1 and 2 are disabled so mode 1 is actualy mode 3 and mode 2 is mode 4 etc.
and i made all color strenght to be equal on 31 colors so it makes it
to be only 32000 colors.


hopfully all drivers 
will work for you

                    dolev