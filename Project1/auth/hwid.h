#include <windows.h>
#include <string>
#include <cstdio>
#include <iostream>
#include <string>
#include "md5.h"
#include <vector>
#include <Windows.h>
#include <Iphlpapi.h>
#include <Assert.h>
#pragma comment(lib, "iphlpapi.lib")
char szBuffer[512];

std::string hwid_data;

#pragma comment(lib,"advapi32.lib")

TCHAR   MachineName[32];
DWORD   buf = 32;

char value_clean[64];

char* getdMacAddresses()
{

    IP_ADAPTER_INFO AdapterInfo[32];       // Allocate information for up to 32 NICs
    DWORD dwBufLen = sizeof(AdapterInfo);  // Save memory size of buffer
    DWORD dwStatus = GetAdaptersInfo(      // Call GetAdapterInfo
        AdapterInfo,                 // [out] buffer to receive data
        &dwBufLen);                  // [in] size of receive data buffer

    //Exit When Error 
    if (dwStatus != ERROR_SUCCESS)
        return 0;

    PIP_ADAPTER_INFO pAdapterInfo = AdapterInfo;
    while (pAdapterInfo)
    {
        if (pAdapterInfo->Type == MIB_IF_TYPE_ETHERNET)
        {

            sprintf_s(szBuffer, sizeof(szBuffer), "%.2x-%.2x-%.2x-%.2x-%.2x-%.2x"
                , pAdapterInfo->Address[0]
                , pAdapterInfo->Address[1]
                , pAdapterInfo->Address[2]
                , pAdapterInfo->Address[3]
                , pAdapterInfo->Address[4]
                , pAdapterInfo->Address[5]
            );

            return szBuffer;

        }


        pAdapterInfo = pAdapterInfo->Next;

    }

    return 0;
}


//hwid
std::string getHWID() {
    HW_PROFILE_INFO hwProfileInfo;
    GetCurrentHwProfile(&hwProfileInfo);
    std::string hwidWString = hwProfileInfo.szHwProfileGuid;
    std::string hwid(hwidWString.begin(), hwidWString.end());

    return hwid;
}

void get_calc_hwid() {

    getdMacAddresses();

    hwid_data = getHWID() + szBuffer;

}