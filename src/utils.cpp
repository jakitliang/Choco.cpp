//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#include "cc/utils.h"
#include <cstdlib>

#ifdef _WIN32
#include <Windows.h>
#endif

CC::String GetEnv(const CC::String & varName) {
    char * var = nullptr;
    size_t requiredSize;
    CC::String strVar;

#ifdef _WIN32
    getenv_s(&requiredSize, nullptr, 0, varName.CString());
    if (requiredSize == 0) {
        printf("LIB doesn't exist!\n");
        return strVar;
    }

    var = static_cast<char *>(malloc(requiredSize * sizeof(char)));

    if (!var) {
        printf("Failed to allocate memory!\n");
        return strVar;
    }

    // Get the value of the LIB environment variable.
    getenv_s(&requiredSize, var, requiredSize, varName.CString());
#else
    var = std::getenv(varName.CString());
#endif

    strVar.Push(var);

#ifdef _WIN32
    free(var);
#endif

    return strVar;
}

CC::String CC::Registry::ReadValue(CCRegRoot root, const CC::String & path, const CC::String & key) {
#ifdef _WIN32
    DWORD bufferSize = 8;
    DWORD valueType = REG_NONE;
    char smallBuffer[8];
    memset(smallBuffer, 0, bufferSize);
    HKEY * rootKey = reinterpret_cast<HKEY *>(&root); // Ignore endian

    auto ret = RegGetValueA(*rootKey, path.CString(), key.CString(),
                            RRF_RT_ANY, &valueType, &smallBuffer, &bufferSize);

    if (ret != ERROR_SUCCESS && ret != ERROR_MORE_DATA) {
        return nullptr;
    }

    if (bufferSize == 0) {
        return nullptr;
    }

    auto buffer = static_cast<char *>(malloc(bufferSize + 1));
    memset(buffer, 0, bufferSize + 1);

    RegGetValueA(*rootKey, path.CString(), key.CString(),
                 RRF_RT_ANY, &valueType, buffer, &bufferSize);

    CC::String strValue(buffer, bufferSize);

    free(buffer);
    return strValue;
#else
    return {};
#endif
}

bool CC::Registry::WriteValue(CCRegRoot root,
                              const CC::String & path, const CC::String & key,
                              CCRegKeyType keyType, const CC::String & value) {
#ifdef _WIN32
    HKEY * rootKey = reinterpret_cast<HKEY *>(&root); // Ignore endian
    auto ret = RegSetKeyValueA(*rootKey, path.CString(),
                               key.CString(), keyType,
                               value.CString(), value.Length());
    return ret == ERROR_SUCCESS;
#else
    return true;
#endif
}

bool CC::Registry::CreatePath(CCRegRoot root, const CC::String & path) {
#ifdef _WIN32
    HKEY res = nullptr;
    HKEY * rootKey = reinterpret_cast<HKEY *>(&root); // Ignore endian
    auto ret = RegCreateKeyA(*rootKey, path.CString(), &res);
    if (ret != ERROR_SUCCESS) {
        return false;
    }

    RegCloseKey(res);
#endif
    return true;
}
