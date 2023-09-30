#pragma once
#include <iostream>
#include <openssl/evp.h>
#include <openssl/md5.h>
#include <VMProtectSDK.h>

#pragma comment(lib, "VMProtectSDK64.lib")

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "crypt32.lib")
#ifdef NDEBUG
#pragma comment(lib, "libcrypto64MT.lib")
#pragma comment(lib, "libssl64MT.lib")
#else
#pragma comment(lib, "libcrypto64MTd.lib")
#pragma comment(lib, "libssl64MTd.lib")
#endif

class Crypt {
public:
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
                        sprintf(&md5String[i * 2], "%02x", (unsigned int)digest[i]);
                }

                return std::string(md5String);

                VMProtectEnd();
        }


};