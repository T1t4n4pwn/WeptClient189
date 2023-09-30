#pragma once
#include <iostream>
#include <openssl/bio.h>
#include <openssl/buffer.h>

class Base64Utils {
public:

        static std::string base64_encode(const std::string& input) {
                BIO* bmem = nullptr;
                BIO* b64 = nullptr;
                BUF_MEM* bptr = nullptr;

                b64 = BIO_new(BIO_f_base64());
                BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
                bmem = BIO_new(BIO_s_mem());
                b64 = BIO_push(b64, bmem);

                BIO_write(b64, input.c_str(), input.length());
                BIO_flush(b64);
                BIO_get_mem_ptr(b64, &bptr);

                std::string output(bptr->data, bptr->length - 1);

                BIO_free_all(b64);

                return output;
        }

        // Base64½âÂë
        static std::string base64_decode(const std::string& input) {
                BIO* b64 = nullptr;
                BIO* bmem = nullptr;
                std::string output(input.length(), '\0');

                b64 = BIO_new(BIO_f_base64());
                BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
                bmem = BIO_new_mem_buf(input.c_str(), input.length());
                bmem = BIO_push(b64, bmem);

                int size = BIO_read(bmem, &output[0], input.length());

                output.resize(size);

                BIO_free_all(bmem);

                return output;
        }

};