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

                const int AES_KEY_SIZE = 128; // ʹ��128λ��AES��Կ
                unsigned char iv[AES_BLOCK_SIZE] = { 0 }; // ��ʼ������Ϊ0
                //I_am_T1t4n4pwn_+
                char key[]{ 'I', '_', 'a', 'm', '_', 'T', '1', 't', '4', 'n', '4', 'p', 'w', 'n', '_', '+'};

                // ��������ʼ��AES��Կ��������
                EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
                EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, reinterpret_cast<const unsigned char*>(key), iv);

                // ������ܺ�ĳ���
                int enc_len = text.length() + AES_BLOCK_SIZE;
                unsigned char* enc_text = new unsigned char[enc_len] {0};

                // ִ�м��ܲ���
                int len;
                EVP_EncryptUpdate(ctx, enc_text, &len, reinterpret_cast<const unsigned char*>(text.c_str()), text.length());

                // �������ܲ���
                int final_len;
                EVP_EncryptFinal_ex(ctx, enc_text + len, &final_len);

                // ��ϼ��ܺ�����ݲ����Ϊ�ַ���
                std::string encrypted_value(reinterpret_cast<char*>(enc_text), len + final_len);

                // �ͷ���Դ
                delete[] enc_text;
                EVP_CIPHER_CTX_free(ctx);

                return Base64Utils::base64_encode(encrypted_value);
                VMProtectEnd();
        }

        static std::string aes_decrypt(const std::string& encrypted) {
                VMProtectBegin("aes_decrypt");
                std::string encrypted_text = Base64Utils::base64_decode(encrypted);

                const int AES_KEY_SIZE = 128; // ʹ��128λ��AES��Կ
                unsigned char iv[AES_BLOCK_SIZE] = { 0 }; // ��ʼ������Ϊ0
                //I_am_T1t4n4pwn_+
                char key[]{ 'I', '_', 'a', 'm', '_', 'T', '1', 't', '4', 'n', '4', 'p', 'w', 'n', '_', '+'};

                // ��������ʼ��AES��Կ��������
                EVP_CIPHER_CTX* ctx = EVP_CIPHER_CTX_new();
                EVP_DecryptInit_ex(ctx, EVP_aes_128_cbc(), nullptr, reinterpret_cast<const unsigned char*>(key), iv);
                // ������ܺ�ĳ���
                int dec_len = encrypted_text.length();
                unsigned char* dec_text = new unsigned char[dec_len] {0};

                // ִ�н��ܲ���
                int len;
                EVP_DecryptUpdate(ctx, dec_text, &len, reinterpret_cast<const unsigned char*>(encrypted_text.c_str()), dec_len);

                // �������ܲ���
                int final_len;
                EVP_DecryptFinal_ex(ctx, dec_text + len, &final_len);

                // ��Ͻ��ܺ�����ݲ����Ϊ�ַ���
                std::string decrypted_value(reinterpret_cast<char*>(dec_text), len + final_len);

                // �ͷ���Դ
                delete[] dec_text;
                EVP_CIPHER_CTX_free(ctx);
                VMProtectEnd();
                return decrypted_value;
        }


};