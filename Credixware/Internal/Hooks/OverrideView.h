// Created by Credix - Licence: https://creativecommons.org/licenses/by-nc-sa/4.0/
#ifndef OVERRIDEVIEW_H
#define OVERRIDEVIEW_H

#include "../Headers/Interfaces.h"
#include "../Hacks/Hacks.h"

typedef void(__thiscall* OverrideView_t)(void*, CViewSetup*);
OverrideView_t oOverrideView;
unsigned int* oOverrideViewFunc;

void __fastcall hkOverrideView(void* ecx, void* edx, CViewSetup* setup) {
	Thirdperson::Update(setup);
	GrenadeHelper::View();
	setup->fovViewmodel = 100.0f;
	//setup->fov = 110.0f;
	oOverrideView(ecx, setup);
}

#endif