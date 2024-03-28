//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#ifndef CHOCO_CPP_UTILS_H
#define CHOCO_CPP_UTILS_H

#include "cc/types.h"
#include "cc/string.h"

typedef CC_ENUM(unsigned long, CCRegRoot) {
    CCRegRootHKCR = 0x80000000,
    CCRegRootHKCU = 0x80000001,
    CCRegRootHKLM = 0x80000002,
    CCRegRootHKU = 0x80000003,
    CCRegRootHKPD = 0x80000004,
    CCRegRootHKPT = 0x80000050,
    CCRegRootHKPN = 0x80000060,
    CCRegRootHKCC = 0x80000005,
    CCRegRootHKDD = 0x80000006,
    CCRegRootHKCULS = 0x80000007
};

typedef CC_ENUM(unsigned long, CCRegKeyFlag) {
    CCRegKeyFlagNone        = 0x00000001,  // restrict type to REG_NONE      (other data types will not return ERROR_SUCCESS)
    CCRegKeyFlagSZ          = 0x00000002,  // restrict type to REG_SZ        (other data types will not return ERROR_SUCCESS)
    CCRegKeyFlagExpandSZ    = 0x00000004,  // restrict type to REG_EXPAND_SZ (other data types will not return ERROR_SUCCESS)
    CCRegKeyFlagBinary      = 0x00000008,  // restrict type to REG_BINARY    (other data types will not return ERROR_SUCCESS)
    CCRegKeyFlagDWORD       = 0x00000010,  // restrict type to REG_DWORD     (other data types will not return ERROR_SUCCESS)
    CCRegKeyFlagMultiSZ     = 0x00000020,  // restrict type to REG_MULTI_SZ  (other data types will not return ERROR_SUCCESS)
    CCRegKeyFlagQWORD       = 0x00000040,  // restrict type to REG_QWORD     (other data types will not return ERROR_SUCCESS)
    CCRegKeyFlagBinaryDWORD = (CCRegKeyFlagBinary | CCRegKeyFlagDWORD), // restrict type to *32-bit* RRF_RT_REG_BINARY or RRF_RT_REG_DWORD
    CCRegKeyFlagBinaryQWORD = (CCRegKeyFlagBinary | CCRegKeyFlagQWORD), // restrict type to *64-bit* RRF_RT_REG_BINARY or RRF_RT_REG_DWORD
    CCRegKeyFlagAny         = 0x0000ffff                             // no type restriction
};

typedef CC_ENUM(unsigned long, CCRegKeyType) {
    CCRegKeyTypeNone                     = ( 0ul ), // No value type
    CCRegKeyTypeSZ                       = ( 1ul ), // Unicode nul terminated string
    CCRegKeyTypeExpandSZ                 = ( 2ul ), // Unicode nul terminated string
    CCRegKeyTypeBinary                   = ( 3ul ), // Free form binary
    CCRegKeyTypeDWORD                    = ( 4ul ), // 32-bit number
    CCRegKeyTypeDWORDLittleEndian        = ( 4ul ), // 32-bit number (same as RegKeyTypeDWORD)
    CCRegKeyTypeDWORDBigEndian           = ( 5ul ), // 32-bit number
    CCRegKeyTypeLink                     = ( 6ul ), // Symbolic Link (unicode)
    CCRegKeyTypeMultiSZ                  = ( 7ul ), // Multiple Unicode strings
    CCRegKeyTypeResourceList             = ( 8ul ), // Resource list in the resource map
    CCRegKeyTypeFullResourceDescriptor   = ( 9ul ), // Resource list in the hardware description
    CCRegKeyTypeResourceRequirementsList = ( 10ul ),
    CCRegKeyTypeQWORD                    = ( 11ul ), // 64-bit number
    CCRegKeyTypeQWORDLittleEndian        = ( 11ul ) // 64-bit number (same as RegKeyTypeQWORD)
};

namespace CC {
    String GetEnv(const char * varName);

    // Only for windows
    namespace Registry {
        void * ReadValue(CCRegRoot root, const char * path, const char * key);

        bool WriteValue(CCRegRoot root,
                        const char * path,
                        const char * key,
                        CCRegKeyType keyType,
                        const void * value,
                        Size sizeOfValue);

        bool CreatePath(CCRegRoot root, const char * path);
    }
}

#endif //CHOCO_CPP_UTILS_H
