#pragma once
#include <iostream>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <VMProtectSDK.h>
#include "Base64Utils.h"

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

class AESUtils {
public:

        static std::string aes_encrypt(const std::string& text) {

                VMProtectBegin("aes_encrypt");

                const int AES_KEY_SIZE = 128; // 使用128位的AES密钥
                unsigned char iv[AES_BLOCK_SIZE] = { 0 }; // 初始化向量为0
                //I_am_T1t4n4pwn_+
                char key[]{ 'I', '_', 'a', 'm', '_', 'T', '1', 't', '4', 'n', '4', 'p', 'w', 'n', '_', '+'};

                // 创建并初始化AES密钥和上下文
                EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
                EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, reinterpret_cast<const unsigned char*>(key), iv);

                // 计算加密后的长度
                int enc_len = text.length() + AES_BLOCK_SIZE;
                unsigned char* enc_text = new unsigned char[enc_len] {0};

                // 执行加密操作
                int len;
                EVP_EncryptUpdate(ctx, enc_text, &len, reinterpret_cast<const unsigned char*>(text.c_str()), text.length());

                // 结束加密操作
                int final_len;
                EVP_EncryptFinal_ex(ctx, enc_text + len, &final_len);

                // 组合加密后的数据并输出为字符串
                std::string encrypted_value(reinterpret_cast<char*>(enc_text), len + final_len);

                // 释放资源
                delete[] enc_text;
                EVP_CIPHER_CTX_free(ctx);

                return Base64Utils::base64_encode(encrypted_value);
                VMProtectEnd();
        }

        static std::string aes_decrypt(const std::string& encrypted) {
                VMProtectBegin("aes_decrypt");
                std::string encrypted_text = Base64Utils::base64_decode(encrypted);

                const int AES_KEY_SIZE = 128; // 使用128位的AES密钥
                unsigned char iv[AES_BLOCK_SIZE] = { 0 }; // 初始化向量为0
                //I_am_T1t4n4pwn_+
                char key[]{ 'I', '_', 'a', 'm', '_', 'T', '1', 't', '4', 'n', '4', 'p', 'w', 'n', '_', '+'};

                // 创建并初始化AES密钥和上下文
                EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
                EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, reinterpret_cast<const unsigned char*>(key), iv);
                // 计算解密后的长度
                int dec_len = encrypted_text.length();
                unsigned char* dec_text = new unsigned char[dec_len] {0};

                // 执行解密操作
                int len;
                EVP_DecryptUpdate(ctx, dec_text, &len, reinterpret_cast<const unsigned char*>(encrypted_text.c_str()), dec_len);

                // 结束解密操作
                int final_len;
                EVP_DecryptFinal_ex(ctx, dec_text + len, &final_len);

                // 组合解密后的数据并输出为字符串
                std::string decrypted_value(reinterpret_cast<char*>(dec_text), len + final_len);

                // 释放资源
                delete[] dec_text;
                EVP_CIPHER_CTX_free(ctx);
                VMProtectEnd();
                return decrypted_value;
        }


};