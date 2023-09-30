#pragma once
#include <iostream>
#include <sstream>
#include <iomanip>
#include <windows.h>

class Encoding {
public:

        static std::string uft8_to_gbk(const std::string& utf8String) {

                // ��ȡת��������軺������С
                int bufferSize = MultiByteToWideChar(CP_UTF8, 0, utf8String.c_str(), -1, NULL, 0);

                // ���仺����
                wchar_t* wideBuffer = (wchar_t*)malloc(bufferSize * sizeof(wchar_t));

                // ��UTF-8�ַ���ת��Ϊ���ַ��ַ���
                MultiByteToWideChar(CP_UTF8, 0, utf8String.c_str(), -1, wideBuffer, bufferSize);

                // ��ȡת��������軺������С
                bufferSize = WideCharToMultiByte(CP_ACP, 0, wideBuffer, -1, NULL, 0, NULL, NULL);

                // ���仺����
                char* gbkBuffer = (char*)malloc(bufferSize * sizeof(char));

                // �����ַ��ַ���ת��ΪGBK������ַ���
                WideCharToMultiByte(CP_ACP, 0, wideBuffer, -1, gbkBuffer, bufferSize, NULL, NULL);

                std::string ret(gbkBuffer);

                // �ͷ��ڴ�
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
