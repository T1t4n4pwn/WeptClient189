#pragma once

#include <iostream>
#include <intrin.h>
#include <string>
#include <Windows.h>
#include <openssl/evp.h>
#include <openssl/md5.h>
#include <VMProtectSDK.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "crypt32.lib")
#ifdef NDEBUG
#pragma comment(lib, "libcrypto64MT.lib")
#pragma comment(lib, "libssl64MT.lib")
#else
#pragma comment(lib, "libcrypto64MTd.lib")
#pragma comment(lib, "libssl64MTd.lib")
#endif

class HWIDHelper {
public:
    static std::string GetProcessorID()
    {
        VMProtectBegin("GetProcessorID");
        std::string strCPUId;

        unsigned long s1, s2;
        char buf[32] = { 0 };
        INT32 Infobuf[4];

        __cpuid(Infobuf, 1);

        s1 = Infobuf[3];
        s2 = Infobuf[0];

        if (s1)
        {
            memset(buf, 0, 32);
            sprintf_s(buf, 32, "%08X", s1);
            strCPUId += buf;
        }

        if (s2)
        {
            memset(buf, 0, 32);
            sprintf_s(buf, 32, "%08X", s2);
            strCPUId += buf;
        }

        __cpuid(Infobuf, 3);
        s1 = Infobuf[3];
        s2 = Infobuf[0];

        if (s1)
        {
            memset(buf, 0, 32);
            sprintf_s(buf, 32, "%08X", s1);
            strCPUId += buf;
        }

        if (s2)
        {
            memset(buf, 0, 32);
            sprintf_s(buf, 32, "%08X", s2);
            strCPUId += buf;
        }

        return strCPUId;
        VMProtectEnd();
    }
    static std::string GetDiskID()
    {
        VMProtectBegin("GetDiskID");
        std::string id;
        char Name[MAX_PATH];
        DWORD serno;
        DWORD length;
        DWORD FileFlag;
        char FileName[MAX_PATH];
        BOOL Ret;
        Ret = GetVolumeInformationA("C:\\", Name, MAX_PATH, &serno, &length, &FileFlag, FileName, MAX_PATH);
        if (Ret)
        {

            id = std::to_string(serno);
        }
        return id;
        VMProtectEnd();
    }

    static std::string md5(const std::string& message) {

        VMProtectBegin("md5");
        EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
        if (mdctx == nullptr) {
            // 错误处理
            return "";
        }

        unsigned char digest[MD5_DIGEST_LENGTH];

        if (EVP_DigestInit_ex(mdctx, EVP_md5(), nullptr) != 1) {
            // 错误处理
            EVP_MD_CTX_free(mdctx);
            return "";
        }

        if (EVP_DigestUpdate(mdctx, message.c_str(), message.length()) != 1) {
            // 错误处理
            EVP_MD_CTX_free(mdctx);
            return "";
        }

        if (EVP_DigestFinal_ex(mdctx, digest, nullptr) != 1) {
            // 错误处理
            EVP_MD_CTX_free(mdctx);
            return "";
        }

        EVP_MD_CTX_free(mdctx);

        char md5String[MD5_DIGEST_LENGTH * 2 + 1];
        for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
            sprintf(&md5String[i * 2], "%02X", (unsigned int)digest[i]);
        }

        return std::string(md5String);

        VMProtectEnd();
    }

};
