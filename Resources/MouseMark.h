/*  GIMP header image file format (RGB): /Users/devlee/Dropbox/CodingStudio/Projects/OpenWorld2d/Resources/MouseMark.h  */

static unsigned int width = 40;
static unsigned int height = 20;

/*  Call this macro repeatedly.  After each use, the pixel data can be extracted  */

#define HEADER_PIXEL(data,pixel) {\
pixel[0] = (((data[0] - 33) << 2) | ((data[1] - 33) >> 4)); \
pixel[1] = ((((data[1] - 33) & 0xF) << 4) | ((data[2] - 33) >> 2)); \
pixel[2] = ((((data[2] - 33) & 0x3) << 6) | ((data[3] - 33))); \
data += 4; \
}
static char *header_data =
	"````````````````````````````````````````````````````````````````"
	"````````'\"A9'\"A9'\"A9'\"A9````````````````````````````````````````"
	"````````````````````````````````````````````````````````````````"
	"````````````````````````````````'\"A9'\"A9F_VZF_VZF_VZF_VZ'\"A9'\"A9"
	"````````````````````````````````````````````````````````````````"
	"````````````````````````````````````````````````````````'\"A9'\"A9"
	"F_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZ'\"A9'\"A9````````````````````````"
	"````````````````````````````````````````````````````````````````"
	"````````````````'\"A9'\"A9F_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZ"
	"F_VZF_VZ'\"A9'\"A9````````````````````````````````````````````````"
	"````````````````````````````````````````'\"A9'\"A9F_VZF_VZF_VZF_VZ"
	"F_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZ'\"A9'\"A9````````"
	"````````````````````````````````````````````````````````````````"
	"'\"A9'\"A9F_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZ"
	"F_VZF_VZF_VZF_VZF_VZF_VZ'\"A9'\"A9````````````````````````````````"
	"````````````````````````'\"A9'\"A9F_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZ"
	"F_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZ"
	"'\"A9'\"A9````````````````````````````````````````'\"A9'\"A9F_VZF_VZ"
	"F_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZ"
	"F_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZ'\"A9'\"A9````````````````"
	"````````'\"A9'\"A9F_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZ"
	"F_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZ"
	"F_VZF_VZF_VZF_VZ'\"A9'\"A9````````'\"A9'\"A9F_VZF_VZF_VZF_VZF_VZF_VZ"
	"F_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZ"
	"F_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZ'\"A9'\"A9"
	"'\"A9'\"A9F_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZ"
	"F_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZ"
	"F_VZF_VZF_VZF_VZF_VZF_VZ'\"A9'\"A9````````'\"A9'\"A9F_VZF_VZF_VZF_VZ"
	"F_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZ"
	"F_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZ'\"A9'\"A9````````"
	"````````````````'\"A9'\"A9F_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZ"
	"F_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZ"
	"F_VZF_VZ'\"A9'\"A9````````````````````````````````````````'\"A9'\"A9"
	"F_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZ"
	"F_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZ'\"A9'\"A9````````````````````````"
	"````````````````````````````````'\"A9'\"A9F_VZF_VZF_VZF_VZF_VZF_VZ"
	"F_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZ'\"A9'\"A9"
	"````````````````````````````````````````````````````````````````"
	"````````'\"A9'\"A9F_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZ"
	"F_VZF_VZF_VZF_VZ'\"A9'\"A9````````````````````````````````````````"
	"````````````````````````````````````````````````'\"A9'\"A9F_VZF_VZ"
	"F_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZ'\"A9'\"A9````````````````"
	"````````````````````````````````````````````````````````````````"
	"````````````````````````'\"A9'\"A9F_VZF_VZF_VZF_VZF_VZF_VZF_VZF_VZ"
	"'\"A9'\"A9````````````````````````````````````````````````````````"
	"````````````````````````````````````````````````````````````````"
	"'\"A9'\"A9F_VZF_VZF_VZF_VZ'\"A9'\"A9````````````````````````````````"
	"````````````````````````````````````````````````````````````````"
	"````````````````````````````````````````'\"A9'\"A9'\"A9'\"A9````````"
	"````````````````````````````````````````````````````````````````"
	"";
