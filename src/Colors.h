#ifndef __COLORS_H__
#define __COLORS_H__

#include <windows.h>
#include <stdio.h>

void SetConsoleColour(WORD* Attributes, DWORD Colour);
void ResetConsoleColour(WORD Attributes);

#endif 
