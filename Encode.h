#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>
#include <windows.h>

class Encoding {
public:

        static std::string uft8_to_gbk(const std::string& utf8String) {

                // 获取转换后的所需缓冲区大小
                int bufferSize = MultiByteToWideChar(CP_UTF8, 0, utf8String.c_str(), -1, NULL, 0);

                // 分配缓冲区
                wchar_t* wideBuffer = (wchar_t*)malloc(bufferSize * sizeof(wchar_t));

                // 将UTF-8字符串转换为宽字符字符串
                MultiByteToWideChar(CP_UTF8, 0, utf8String.c_str(), -1, wideBuffer, bufferSize);

                // 获取转换后的所需缓冲区大小
                bufferSize = WideCharToMultiByte(CP_ACP, 0, wideBuffer, -1, NULL, 0, NULL, NULL);

                // 分配缓冲区
                char* gbkBuffer = (char*)malloc(bufferSize * sizeof(char));

                // 将宽字符字符串转换为GBK编码的字符串
                WideCharToMultiByte(CP_ACP, 0, wideBuffer, -1, gbkBuffer, bufferSize, NULL, NULL);

                std::string ret(gbkBuffer);

                // 释放内存
                free(wideBuffer);
                free(gbkBuffer);

                return ret;
        }

        static std::string url_encode(const std::string& str) {
                std::ostringstream escaped;
                escaped.fill('0');
                escaped << std::hex;

                for (char c : str) {
                        if (std::isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
                                escaped << c;
                        }
                        else {
                                escaped << '%' << std::setw(2) << int((unsigned char)c);
                        }
                }

                return escaped.str();
        }


};
