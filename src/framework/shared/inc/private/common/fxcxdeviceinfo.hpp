//
//    Copyright (C) Microsoft.  All rights reserved.
//
#ifndef _FXCXDEVICEINFO_H_
#define _FXCXDEVICEINFO_H_

#include "FxDeviceCallbacks.hpp"

struct FxCxDeviceInfo : public FxStump {
    FxCxDeviceInfo(PFX_DRIVER_GLOBALS FxDriverGlobals) :
        Driver(NULL),
        IoInCallerContextCallback(FxDriverGlobals),
        Index(0)
    {
        InitializeListHead(&ListEntry);
        RtlZeroMemory(&RequestAttributes, sizeof(RequestAttributes));
        RtlZeroMemory(&CxPnpPowerCallbackContexts, sizeof(CxPnpPowerCallbackContexts));
    }
        
    ~FxCxDeviceInfo() 
    {
        ASSERT(IsListEmpty(&ListEntry));

        for (ULONG loop = 0; loop < ARRAYSIZE(CxPnpPowerCallbackContexts); loop++) {
            if (CxPnpPowerCallbackContexts[loop] != NULL) {
                delete CxPnpPowerCallbackContexts[loop];
            }
        }
    }


    LIST_ENTRY                  ListEntry;    
    FxDriver*                   Driver;
    FxIoInCallerContext         IoInCallerContextCallback;
    WDF_OBJECT_ATTRIBUTES       RequestAttributes;
    CCHAR                       Index;

    PFxCxPnpPowerCallbackContext CxPnpPowerCallbackContexts[FxCxCallbackMax];
};

#endif // _FXCXDEVICEINFO_H_
