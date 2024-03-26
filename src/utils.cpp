//
// Created by Jakit Liang <jakitliang@gmail.com> on 2024/3/26.
//

#include "cc/utils.h"
#include <cstdlib>

#ifdef _WIN32
#include <Windows.h>
#endif

CC::String GetEnv(const char * varName) {
    char * var = nullptr;
    size_t requiredSize;
    CC::String strVar;

#ifdef _WIN32
    getenv_s(&requiredSize, nullptr, 0, varName);
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
    getenv_s(&requiredSize, var, requiredSize, varName);
#else
    var = std::getenv(varName);
#endif

    if (var != nullptr) {
        strVar.Push(var);

#ifdef _WIN32
        free(var);
#endif
    }

    return strVar;
}

void * CC::Registry::ReadValue(CCRegRoot root, const char * path, const char * key) {
#ifdef _WIN32
    DWORD bufferSize = 8;
    DWORD valueType = REG_NONE;
    char smallBuffer[8];
    memset(smallBuffer, 0, bufferSize);
    HKEY * rootKey = reinterpret_cast<HKEY *>(&root); // Ignore endian

    auto ret = RegGetValueA(*rootKey, path, key, RRF_RT_ANY, &valueType, &smallBuffer, &bufferSize);

    if (ret != ERROR_SUCCESS && ret != ERROR_MORE_DATA) {
        return nullptr;
    }

    if (bufferSize == 0) {
        return nullptr;
    }

    auto buffer = static_cast<char *>(malloc(bufferSize + 1));
    memset(buffer, 0, bufferSize + 1);

    RegGetValueA(*rootKey, path, key, RRF_RT_ANY, &valueType, buffer, &bufferSize);

    return buffer;
#else
    return nullptr;
#endif
}

bool CC::Registry::WriteValue(CCRegRoot root, const char * path, const char * key, CCRegKeyType keyType, const void * value, CC::Size sizeOfValue) {
#ifdef _WIN32
    HKEY * rootKey = reinterpret_cast<HKEY *>(&root); // Ignore endian
    auto ret = RegSetKeyValueA(*rootKey, path, key, keyType, value, sizeOfValue);
    return ret == ERROR_SUCCESS;
#else
    return true;
#endif
}

bool CC::Registry::CreatePath(CCRegRoot root, const char * path) {
#ifdef _WIN32
    HKEY res = nullptr;
    HKEY * rootKey = reinterpret_cast<HKEY *>(&root); // Ignore endian
    auto ret = RegCreateKeyA(*rootKey, path, &res);
    if (ret != ERROR_SUCCESS) {
        std::cout << "Create failed: " << ret << std::endl;
        return false;
    }

    RegCloseKey(res);
#endif
    return true;
}
