#include <iostream>
#include "pch.h"
#include <stdio.h>
#include <winternl.h>
#include <windows.h>
#include <cstdlib>
#include <ctime>

namespace fb {

    class BuildInformation {
    public:
        static const char* g_branchName;
        static const char* g_licenseeId;
        static const char* g_studioName;
        static int g_changelist;
        static int g_frostbiteChangelist;
        static const char* g_frostbiteRelease;
        static bool g_isAutoBuild;
        static const char* g_username;
        static int g_usergroup;
        static const char* g_buildTime;
        static const char* g_buildDate;
        static const char* g_buildIso;
        static const char* g_titleId;
    };
    //* for bf2042
    const char* BuildInformation::g_titleId = "BattlefieldGameData";
    const char* BuildInformation::g_branchName = "BattlefieldGameData";
    const char* BuildInformation::g_licenseeId = "BattlefieldGame";
    const char* BuildInformation::g_studioName = "dice";
    int BuildInformation::g_changelist = 21287806;
    int BuildInformation::g_frostbiteChangelist = 11285198;
    const char* BuildInformation::g_frostbiteRelease = "2021-1.1";
    bool BuildInformation::g_isAutoBuild = true;
    const char* BuildInformation::g_username = "svc_auto_kingston";
    int BuildInformation::g_usergroup = 0;
    const char* BuildInformation::g_buildTime = "11:05:46Z";
    const char* BuildInformation::g_buildDate = "2024-09-29";
    const char* BuildInformation::g_buildIso = "2024-09-29T11:05:46Z";

    class BuildInfoImpl {
    public:
        virtual const char* getBranchName() const;
        virtual const char* getLicenseeId() const;
        virtual const char* getStudioName() const;
        virtual int getChangelist() const;
        virtual int getFrostbiteChangelist() const;
        virtual const char* getFrostbiteRelease() const;
        virtual bool getIsAutoBuild() const;
        virtual const char* getUsername() const;
        virtual int getUsergroup() const;
        virtual const char* getBuildTime() const;
        virtual const char* getBuildDate() const;
        virtual const char* getBuildIso() const;
        virtual const char* getTitleId() const;

        static BuildInfoImpl* getBuildInfo();

    private:
        typedef const char* (BuildInfoImpl::* StringMemberFn)() const;
        typedef int (BuildInfoImpl::* IntMemberFn)() const;
        typedef bool (BuildInfoImpl::* BoolMemberFn)() const;

        static StringMemberFn stringMemberFns[];
        static IntMemberFn intMemberFns[];
        static BoolMemberFn boolMemberFns[];

        union VtableEntry {
            void* as_void;
            StringMemberFn as_string_fn;
            IntMemberFn as_int_fn;
            BoolMemberFn as_bool_fn;
        };

        VtableEntry __vftable[13];
    };

    bool isInitialized = false;
    BuildInfoImpl s_buildInfo;

    BuildInfoImpl::StringMemberFn BuildInfoImpl::stringMemberFns[] = {
        &BuildInfoImpl::getBranchName,
        &BuildInfoImpl::getLicenseeId,
        &BuildInfoImpl::getStudioName,
        &BuildInfoImpl::getFrostbiteRelease,
        &BuildInfoImpl::getUsername,
        &BuildInfoImpl::getBuildTime,
        &BuildInfoImpl::getBuildDate,
        &BuildInfoImpl::getBuildIso,
        &BuildInfoImpl::getTitleId
    };

    BuildInfoImpl::IntMemberFn BuildInfoImpl::intMemberFns[] = {
        &BuildInfoImpl::getChangelist,
        &BuildInfoImpl::getFrostbiteChangelist,
        &BuildInfoImpl::getUsergroup
    };

    BuildInfoImpl::BoolMemberFn BuildInfoImpl::boolMemberFns[] = {
        &BuildInfoImpl::getIsAutoBuild
    };

    // getBuildInfo函数实现
    BuildInfoImpl* BuildInfoImpl::getBuildInfo() {
        if (!isInitialized) {
            //OpenConsole();
            isInitialized = true;
            s_buildInfo.__vftable[0].as_string_fn = stringMemberFns[0];
            s_buildInfo.__vftable[1].as_string_fn = stringMemberFns[1];
            s_buildInfo.__vftable[2].as_string_fn = stringMemberFns[2];
            s_buildInfo.__vftable[3].as_int_fn = intMemberFns[0];
            s_buildInfo.__vftable[4].as_int_fn = intMemberFns[1];
            s_buildInfo.__vftable[5].as_string_fn = stringMemberFns[3];
            s_buildInfo.__vftable[6].as_bool_fn = boolMemberFns[0];
            s_buildInfo.__vftable[7].as_int_fn = intMemberFns[2];
            s_buildInfo.__vftable[8].as_string_fn = stringMemberFns[4];
            s_buildInfo.__vftable[9].as_string_fn = stringMemberFns[5];
            s_buildInfo.__vftable[10].as_string_fn = stringMemberFns[6];
            s_buildInfo.__vftable[11].as_string_fn = stringMemberFns[7];
            s_buildInfo.__vftable[12].as_string_fn = stringMemberFns[8];
        }
        return &s_buildInfo;
    }

    const char* BuildInfoImpl::getBranchName() const {
        return BuildInformation::g_branchName;
    }

    const char* BuildInfoImpl::getLicenseeId() const {
        return BuildInformation::g_licenseeId;
    }

    const char* BuildInfoImpl::getStudioName() const {
        return BuildInformation::g_studioName;
    }

    int BuildInfoImpl::getChangelist() const {
        return BuildInformation::g_changelist;
    }

    int BuildInfoImpl::getFrostbiteChangelist() const {
        return BuildInformation::g_frostbiteChangelist;
    }

    const char* BuildInfoImpl::getFrostbiteRelease() const {
        return BuildInformation::g_frostbiteRelease;
    }

    bool BuildInfoImpl::getIsAutoBuild() const {
        return BuildInformation::g_isAutoBuild;
    }

    const char* BuildInfoImpl::getUsername() const {
        return BuildInformation::g_username;
    }

    int BuildInfoImpl::getUsergroup() const {
        return BuildInformation::g_usergroup;
    }

    const char* BuildInfoImpl::getBuildTime() const {
        return BuildInformation::g_buildTime;
    }

    const char* BuildInfoImpl::getBuildDate() const {
        return BuildInformation::g_buildDate;
    }

    const char* BuildInfoImpl::getBuildIso() const {
        return BuildInformation::g_buildIso;
    }
    
    const char* BuildInfoImpl::getTitleId() const {
        return BuildInformation::g_titleId;
    }
    
} // namespace fb

typedef NTSTATUS(NTAPI* NtProtectVirtualMemory_t)(
    HANDLE ProcessHandle,
    PVOID* BaseAddress,
    PULONG RegionSize,
    ULONG NewProtect,
    PULONG OldProtect);

NtProtectVirtualMemory_t NtProtectVirtualMemory = NULL;

void InitializeFunctions()
{
    HMODULE hNtdll = GetModuleHandleA("ntdll.dll");
    if (hNtdll) {
        NtProtectVirtualMemory = (NtProtectVirtualMemory_t)GetProcAddress(hNtdll, "NtProtectVirtualMemory");
    }
    if (!NtProtectVirtualMemory) {
    }
}

void mPatch(__int64 patch, BYTE value)
{
    int Myoffset = 0;
    DWORD oldProtect;
    BYTE* p;

    p = (BYTE*)(patch + Myoffset);
    VirtualProtect(p, 1, PAGE_EXECUTE_READWRITE, &oldProtect);
    *p = value;
    VirtualProtect(p, 1, oldProtect, &oldProtect);
}


extern "C" __declspec(dllexport) fb::BuildInfoImpl * getBuildInfo()
{
    //for bfv
    //mPatch(0x141D823CF, 0x84); 

    //bf2042 ssl
    mPatch(0x141D8721F, 0x84);
    return fb::BuildInfoImpl::getBuildInfo();
}

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved) {
    switch (ul_reason_for_call) {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}