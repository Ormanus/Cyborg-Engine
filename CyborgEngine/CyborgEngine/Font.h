#ifndef FONT_H
#define FONT_H

#include <ft2build.h>
#include FT_FREETYPE_H

FT_Library library;

class Font
{
public:
	Font();
	~Font();
};

#endif