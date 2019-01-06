// Created by Credix - Licence: https://creativecommons.org/licenses/by-nc-sa/4.0/ 
#ifndef MENU_H
#define MENU_H

#include "../Headers/Interfaces.h"

HFont font;

namespace Menu {
	bool bOpen = false;
	void Init() {
		font = g_pSurface->_CreateFont();
		g_pSurface->SetFontGlyphSet(font, "Tahoma", 14, 400, 0, 0, g_pSurface->FONTFLAG_OUTLINE);
	}
	void Draw() {
		if (Utils::GetKey(VK_INSERT)) {
			printf("Down!\n");
			bOpen = !bOpen;
		}
		if (bOpen) {
			g_pSurface->DrawSetTextFont(font);
			g_pSurface->DrawSetTextColor(255, 255, 255, 255);
			g_pSurface->DrawSetTextPos(5, 5);
			g_pSurface->DrawPrintText(L"Credixware | January 2019", wcslen(L"Credixware | January 2019"));
			g_pSurface->DrawSetColor(255, 0, 0, 255);
			g_pSurface->DrawFilledRect(0, 0, 400, 300);
		}
	}
};

#endif