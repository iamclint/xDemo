// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <thread>
#include <string>
#include <Windows.h>
#include "cMemory.h"
#include "xDemo.h"
bool __stdcall RIB_Main(int a, int b)
{
    return true;
}

void CG_RegisterWeapon(int weapon_id)
{
    reinterpret_cast<void(__stdcall*)(int)>(0x454320)(weapon_id);
}

void CG_REGISTERITEMS()
{
    int iVar2;
    char* ConfigString = (char*)(0xC64F14 + *(int*)0xC64D14);
    int uVar4;
    char items[132];
    memcpy_s(items, sizeof(items), ConfigString, sizeof(items)); //redo code
    iVar2 = -(int)ConfigString;
    uVar4 = 0x1;
    while ((int)uVar4 < 0x80)
    {
        if (items[uVar4 >> 0x2] < 0x3a) {
            iVar2 = -0x30;
        }
        else {
            iVar2 = -0x57;
        }
        if ((items[uVar4 >> 0x2] + iVar2 & 0x1 << ((BYTE)uVar4 & 0x3)) != 0x0) {
            CG_RegisterWeapon(uVar4);
        }
        uVar4 = uVar4 + 0x1;
    }
    return;
}

void console_echo(const std::string& msg)
{
    std::string new_msg = "^6x^7Demo^6:^7 " + msg + " \n";
    reinterpret_cast<void(__cdecl*)(int, const char*, int)>(0x4FCA50)(0, new_msg.c_str(), 0);
}


void init()
{
    console_echo("Initializing cod4x demo fix for 1.7 (issue found by Anomaly)");
    console_echo("xDemo written by Salty#1509");
    cMemory::replace_call(0x43EDDD, CG_REGISTERITEMS);
    cMemory::replace_call(0x44AF69, CG_REGISTERITEMS);
    console_echo("Fix applied succesfully");
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        std::thread(init).detach();
        break;
    case DLL_THREAD_ATTACH:
        break;
    case DLL_THREAD_DETACH:
        break;
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

