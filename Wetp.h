#pragma once
#include <iostream>
#include <sstream>
#include <curl/curl.h>
#include <json/json.h>
#include <iomanip>
#include <chrono>
#include "Encode.h"
#include <VMProtectSDK.h>
#include "AESUtils.h"

#include "Crypt.h"

class WeptCookie {
public:
        std::string cfg_keeplogin;
        std::string cfg_username;
        std::string cfg_password;
        std::string cfg_token_type;
        std::string cfg_token;

        WeptCookie() {
                cfg_keeplogin = "null";
                cfg_username = "";
                cfg_password = "";
                cfg_token_type = "";
                cfg_token = "";
        }

        //cfg_keeplogin=null; cfg_username=YunLuo27; cfg_password=; cfg_token_type=; cfg_token=
        std::string toString() {

                std::stringstream ss;

                ss << "cfg_keeplogin=" << cfg_keeplogin << ";" << " "
                        << "cfg_username=" << cfg_username << ";" << " "
                        << "cfg_password=" << cfg_password << ";" << " "
                        << "cfg_token_type=" << cfg_token_type << ";" << " "
                        << "cfg_token=" << cfg_token;

                return ss.str();
        }

};

struct StoreItem {
        int id;
        std::string name;
        std::string desc;
        float price;
        int day_time;
        int weight;
};

class Wept {
public:

        std::string get_version() {
                std::string response;
                std::string  url = "http://api.wept.buzz/api/auth/oauth/version";

                CURL* curl;
                CURLcode res;
                curl = curl_easy_init();
                if (curl) {
                        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
                        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
                        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
                        struct curl_slist* headers = NULL;
                        headers = curl_slist_append(headers, "User-Agent: WeptClient");
                        headers = curl_slist_append(headers, "Content-Type: application/json");
                        headers = curl_slist_append(headers, "Accept: */*");
                        headers = curl_slist_append(headers, "Host: api.wept.buzz");
                        headers = curl_slist_append(headers, "Connection: keep-alive");
                        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

                        std::string cookie = wept_cookie.toString();
                        curl_easy_setopt(curl, CURLOPT_COOKIE, cookie.c_str());


                        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
                        res = curl_easy_perform(curl);

                        if (res != CURLE_OK) {
                                return response;
                        }


                        std::cout << response.c_str() << std::endl;
                }
                curl_easy_cleanup(curl);

                return response;
        }

        bool get_balance(float& balance, std::string& err_msg) {
                std::string  url = "http://api.wept.buzz/api/pay/balance/user";
                std::stringstream ss;

                std::string authorizationStr = "Authorization: ";

                authorizationStr.append(wept_cookie.cfg_token_type);
                authorizationStr.append(" ");
                authorizationStr.append(wept_cookie.cfg_token);

                CURL* curl;
                CURLcode res;
                curl = curl_easy_init();
                if (curl) {
                        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
                        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
                        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
                        curl_easy_setopt(curl, CURLOPT_COOKIE, wept_cookie.toString().c_str());

                        struct curl_slist* headers = NULL;
                        headers = curl_slist_append(headers, "User-Agent: WeptClient");
                        headers = curl_slist_append(headers, "Content-Type: application/json");
                        headers = curl_slist_append(headers, "Accept: */*");
                        headers = curl_slist_append(headers, "Host: api.wept.buzz");
                        headers = curl_slist_append(headers, authorizationStr.c_str());

                        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);


                        std::string response;
                        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
                        res = curl_easy_perform(curl);

                        if (res != CURLE_OK) {
                                return false;
                        }

                        Json::Value rspRoot;
                        Json::Reader reader;

                        if (!reader.parse(response, rspRoot)) {
                                err_msg = "响应包解析失败";
                                return false;
                        }

                        int code = rspRoot["code"].asInt();

                        if (code != 0) {
                                err_msg = Encoding::uft8_to_gbk(rspRoot["msg"].asString());
                                curl_easy_cleanup(curl);
                                return false;
                        }

                        balance = rspRoot["data"]["balance"].asFloat();

                        curl_easy_cleanup(curl);
                        return true;
                }

                err_msg = "初始化错误";
                return false;
        }

        bool register_account(std::string username, std::string  userword, std::string  email, std::string  activeCode, std::string& err_msg) {

                std::string  url = "http://api.wept.buzz/api/register/be/";
                url += activeCode;

                CURL* curl;
                CURLcode res;
                curl = curl_easy_init();
                if (curl) {
                        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
                        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
                        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
                        struct curl_slist* headers = NULL;
                        headers = curl_slist_append(headers, "User-Agent: WeptClient");
                        headers = curl_slist_append(headers, "Content-Type: application/json");
                        headers = curl_slist_append(headers, "Accept: */*");
                        headers = curl_slist_append(headers, "Host: api.wept.buzz");
                        headers = curl_slist_append(headers, "Connection: keep-alive");
                        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
                        wept_cookie.cfg_username = username;
                        std::string cookie = wept_cookie.toString();
                        curl_easy_setopt(curl, CURLOPT_COOKIE, cookie.c_str());

                        Json::Value root;
                        root["username"] = username;
                        root["userword"] = Crypt::md5(userword);
                        root["email"] = email;

                        std::string data = Json2String(root);

                        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data.c_str());

                        std::string response;
                        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
                        res = curl_easy_perform(curl);

                        if (res != CURLE_OK) {
                                curl_easy_cleanup(curl);
                                return false;
                        }

                        Json::Value rspRoot;
                        Json::Reader reader;

                        if (!reader.parse(response, rspRoot)) {
                                err_msg = "响应包解析失败";
                                curl_easy_cleanup(curl);
                                return false;
                        }

                        int code = rspRoot["code"].asInt();

                        if (code != 0) {
                                err_msg = Encoding::uft8_to_gbk(rspRoot["msg"].asString());
                                curl_easy_cleanup(curl);
                                return false;
                        }
                        return true;
                }

                err_msg = "初始化错误";
                return false;
        }

        bool login_account(std::string username, std::string password, std::string& err_msg) {

                std::string grant_type = "password";

                Json::Value root;
                root["client"] = "BEProxy";
                root["type"] = "sign";
                root["password"] = Crypt::md5(password);
                root["machine"] = Crypt::md5("BEProxy");

                std::string param_password = Encoding::url_encode(Json2String(root));

                std::stringstream ss;

                ss << "grant_type=" << grant_type << "&" << "username=" << username << "&"
                        << "password=" << param_password << "&" << "betoken=" << "" << "&"
                        << "client=" << "BEProxy";

                std::string params = ss.str();


                std::string  url = "http://api.wept.buzz/api/auth/oauth/token?";
                url.append(params);

                CURL* curl;
                CURLcode res;
                curl = curl_easy_init();
                if (curl) {
                        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
                        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
                        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
                        struct curl_slist* headers = NULL;
                        headers = curl_slist_append(headers, "User-Agent: WeptClient");
                        headers = curl_slist_append(headers, "Content-Type: application/json");
                        headers = curl_slist_append(headers, "Accept: */*");
                        headers = curl_slist_append(headers, "Host: api.wept.buzz");
                        headers = curl_slist_append(headers, "Connection: keep-alive");
                        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);



                        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, params.c_str());

                        std::string response;
                        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

                        res = curl_easy_perform(curl);
                        if (res != CURLE_OK) {
                                curl_easy_cleanup(curl);
                                return false;
                        }

                        Json::Value rspRoot;
                        Json::Reader reader;

                        if (!reader.parse(response, rspRoot)) {
                                return false;
                        }

                        if (!rspRoot["error"].isNull()) {
                                std::string err = rspRoot["message"].asString();
                                err_msg = Encoding::uft8_to_gbk(err);
                                curl_easy_cleanup(curl);
                                return false;
                        }

                        if (rspRoot["access_token"].isNull()) {
                                std::cout << "响应错误" << std::endl;
                                curl_easy_cleanup(curl);
                                return false;
                        }


                        wept_cookie.cfg_token_type = rspRoot["token_type"].asString();
                        wept_cookie.cfg_token = rspRoot["access_token"].asString();



                        curl_easy_cleanup(curl);

                        return true;
                }

                err_msg = "初始化错误";
                return false;
        }

        bool get_store_items(int start, int count, std::vector<StoreItem>& items, std::string& err_msg) {

                std::string  url = "http://api.wept.buzz/api/pay/store/items/";
                std::stringstream ss;

                ss << url << start << "/" << count;

                url = ss.str();

                std::string authorizationStr = "Authorization: ";

                authorizationStr.append(wept_cookie.cfg_token_type);
                authorizationStr.append(" ");
                authorizationStr.append(wept_cookie.cfg_token);

                CURL* curl;
                CURLcode res;
                curl = curl_easy_init();
                if (curl) {
                        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
                        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
                        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
                        //curl_easy_setopt(curl, CURLOPT_COOKIE, wept_cookie.toString().c_str());

                        struct curl_slist* headers = NULL;
                        headers = curl_slist_append(headers, "User-Agent: WeptClient");
                        headers = curl_slist_append(headers, "Content-Type: application/json");
                        headers = curl_slist_append(headers, "Accept: */*");
                        headers = curl_slist_append(headers, "Host: api.wept.buzz");
                        headers = curl_slist_append(headers, authorizationStr.c_str());

                        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);


                        std::string response;
                        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
                        res = curl_easy_perform(curl);

                        if (res != CURLE_OK) {
                                return false;
                        }

                        Json::Value rspRoot;
                        Json::Reader reader;

                        if (!reader.parse(response, rspRoot)) {
                                err_msg = "响应包解析失败";
                                return false;
                        }

                        int code = rspRoot["code"].asInt();

                        if (code != 0) {
                                err_msg = Encoding::uft8_to_gbk(rspRoot["msg"].asString());
                                curl_easy_cleanup(curl);
                                return false;
                        }

                        int item_count = rspRoot["count"].asInt();
                        Json::Value data_obj_array = rspRoot["data"];

                        for (int i = 0; i < item_count; i++)
                        {
                                const Json::Value& element = data_obj_array[i];

                                StoreItem current_item{ 0 };

                                current_item.id = element["id"].asInt();
                                current_item.name = Encoding::uft8_to_gbk(element["name"].asString());
                                current_item.desc = Encoding::uft8_to_gbk(element["desc"].asString());
                                current_item.price = element["price"].asFloat();
                                current_item.day_time = element["dtime"].asInt();
                                current_item.weight = element["weight"].asInt();

                                items.push_back(current_item);
                        }

                        curl_easy_cleanup(curl);
                        return true;
                }

                err_msg = "初始化错误";
                return false;
        }

        bool buy_item(int item, int count, std::string& err_msg) {

                std::string  url = "http://api.wept.buzz/api/pay/store/order/";
                std::stringstream ss;

                ss << url << item << "/" << count;

                url = ss.str();

                std::string authorizationStr = "Authorization: ";

                authorizationStr.append(wept_cookie.cfg_token_type);
                authorizationStr.append(" ");
                authorizationStr.append(wept_cookie.cfg_token);

                CURL* curl;
                CURLcode res;
                curl = curl_easy_init();
                if (curl) {
                        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
                        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
                        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");

                        struct curl_slist* headers = NULL;
                        headers = curl_slist_append(headers, "User-Agent: WeptClient");
                        headers = curl_slist_append(headers, "Content-Type: application/json");
                        headers = curl_slist_append(headers, "Accept: */*");
                        headers = curl_slist_append(headers, "Host: api.wept.buzz");
                        headers = curl_slist_append(headers, authorizationStr.c_str());

                        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);


                        std::string response;
                        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
                        res = curl_easy_perform(curl);

                        if (res != CURLE_OK) {
                                return false;
                        }

                        Json::Value rspRoot;
                        Json::Reader reader;

                        if (!reader.parse(response, rspRoot)) {
                                err_msg = "响应包解析失败";
                                return false;
                        }

                        int code = rspRoot["code"].asInt();

                        if (code != 0) {
                                err_msg = Encoding::uft8_to_gbk(rspRoot["msg"].asString());
                                curl_easy_cleanup(curl);
                                return false;
                        }



                        curl_easy_cleanup(curl);
                        return true;
                }

                err_msg = "初始化错误";
                return false;
        }

        bool check_user_permission(std::string& err_msg) {

                VMProtectBegin("check_user_permission");
                std::string  url = "http://api.wept.buzz/api/auth/permission/user";


                std::string authorizationStr = "Authorization: ";

                authorizationStr.append(wept_cookie.cfg_token_type);
                authorizationStr.append(" ");
                authorizationStr.append(wept_cookie.cfg_token);

                CURL* curl;
                CURLcode res;
                curl = curl_easy_init();
                if (curl) {
                        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
                        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
                        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");

                        struct curl_slist* headers = NULL;
                        headers = curl_slist_append(headers, "User-Agent: WeptClient");
                        headers = curl_slist_append(headers, "Content-Type: application/json");
                        headers = curl_slist_append(headers, "Accept: */*");
                        headers = curl_slist_append(headers, "Host: api.wept.buzz");
                        headers = curl_slist_append(headers, authorizationStr.c_str());

                        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);


                        std::string response;
                        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

                        res = curl_easy_perform(curl);

                        if (res != CURLE_OK) {
                                return false;
                        }

                        Json::Value rspRoot;
                        Json::Reader reader;

                        if (!reader.parse(response, rspRoot)) {
                                err_msg = "响应包解析失败";
                                return false;
                        }

                        int code = rspRoot["code"].asInt();

                        if (code != 0) {
                                err_msg = Encoding::uft8_to_gbk(rspRoot["msg"].asString());
                                curl_easy_cleanup(curl);
                                return false;
                        }

                        Json::Value data_obj_array = rspRoot["data"];

                        const Json::Value& data_obj = data_obj_array[0];

                        if (data_obj.isNull()) {
                                err_msg = "用户无权访问";
                                curl_easy_cleanup(curl);
                                return false;
                        }

                        std::string expire = data_obj["permission"].asString();

                        std::string decrypted = AESUtils::aes_decrypt(expire);

                        std::istringstream converter{ decrypted };
                        
      

                        std::time_t expire_time = 0;
                        converter >> expire_time;

                        if (get_current_timestamp() > expire_time) {
                                err_msg = "用户过期";
                                curl_easy_cleanup(curl);
                                return false;
                        }

                        curl_easy_cleanup(curl);
                        return true;
                }

                err_msg = "初始化错误";
                return false;
                VMProtectEnd();
        }


        bool balance_use_active_code(const std::string& active_code, std::string& err_msg) {

                VMProtectBegin("balance_use_active_code");

                std::string  url = "http://154.12.32.216:10086/api/pay/balance/useActiveCode/";
                url += active_code;


                std::string authorizationStr = "Authorization: ";

                authorizationStr.append(wept_cookie.cfg_token_type);
                authorizationStr.append(" ");
                authorizationStr.append(wept_cookie.cfg_token);

                CURL* curl;
                CURLcode res;
                curl = curl_easy_init();
                if (curl) {
                        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "PUT");
                        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
                        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");

                        struct curl_slist* headers = NULL;
                        headers = curl_slist_append(headers, "User-Agent: WeptClient");
                        headers = curl_slist_append(headers, "Content-Type: application/json");
                        headers = curl_slist_append(headers, "Accept: */*");
                        headers = curl_slist_append(headers, "Host: 154.12.32.216:10086");
                        headers = curl_slist_append(headers, authorizationStr.c_str());

                        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);


                        std::string response;
                        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

                        res = curl_easy_perform(curl);

                        if (res != CURLE_OK) {
                                return false;
                        }

                        Json::Value rspRoot;
                        Json::Reader reader;

                        if (!reader.parse(response, rspRoot)) {
                                err_msg = "响应包解析失败";
                                return false;
                        }

                        int code = rspRoot["code"].asInt();

                        if (code != 0) {
                                err_msg = Encoding::uft8_to_gbk(rspRoot["msg"].asString());
                                curl_easy_cleanup(curl);
                                return false;
                        }




                        curl_easy_cleanup(curl);
                        return true;
                }

                err_msg = "初始化错误";
                return false;
                VMProtectEnd();

        }

private:

        __forceinline long long get_current_timestamp() {
                //VMProtectBegin("get_current_timestamp");
                std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
                std::chrono::seconds secondsSinceEpoch = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
                std::time_t timestamp = secondsSinceEpoch.count();
                return timestamp;
                //VMProtectEnd();
        }

        static std::time_t convert_to_timestamp(const std::string& iso8601Date) {
                VMProtectBegin("convert_to_timestamp");
                std::tm timeInfo = {};
                std::istringstream iss(iso8601Date);
                iss >> std::get_time(&timeInfo, "%Y-%m-%dT%H:%M:%S");
                if (iss.fail()) {
                        std::cerr << "Failed to parse date: " << iso8601Date << std::endl;
                        return 0;
                }
                return std::mktime(&timeInfo);
                VMProtectEnd();
        }


        static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* response)
        {
                size_t totalSize = size * nmemb;
                response->append((char*)contents, totalSize);
                return totalSize;
        }

        static std::string Json2String(Json::Value root) {
                Json::StreamWriterBuilder writer;
                writer["indentation"] = "";
                writer["emitUTF8"] = true;
                std::string data = Json::writeString(writer, root);
                return data;
        }

private:
        WeptCookie wept_cookie;
};