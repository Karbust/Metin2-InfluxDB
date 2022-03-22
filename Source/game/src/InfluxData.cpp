//
// Created by Karbust on 04/02/2022.
//

#include "stdafx.h"

#ifdef INFLUX_STATS
#include <chrono>

#include "config.h"
#include "desc_manager.h"
#include "InfluxData.h"

void CInfluxData::Initialize() {

}

void CInfluxData::Check(int day, int hour, int minute, int second) {
    int lastNumber = minute % 10;

    if (isInfluxEnabled && lastNumber == 0 && second == 00)
    {
        int iTotal;
        int * paiEmpireUserCount;
        int iLocal;

        DESC_MANAGER::instance().GetUserCount(iTotal, &paiEmpireUserCount, iLocal);

        auto now = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

        std::string data = "online_users_" + g_stHostname + " empire1=" + std::to_string(paiEmpireUserCount[1]) + "i,empire2=" + std::to_string(paiEmpireUserCount[2]) + "i,empire3=" + std::to_string(paiEmpireUserCount[3]) + "i,total=" + std::to_string(iTotal) + "i " + std::to_string(now);

        long http_code = 0;
        cURLCalls(data,&http_code);
    }
}

bool CInfluxData::cURLCalls(const std::string& curl_fields,long *http_code) {
    CURL *curl;

    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    struct curl_slist* headers = nullptr;

    if (!curl)
    {
        if (test_server)
            sys_log(0, "ERROR : cURL initialization.");

        Cleanup(curl, headers);
        return false;
    }

    std::vector<std::string> headersStrings{
        "Authorization: Token " + influxToken,
        "Content-Type: text/plain; charset=utf-8",
        "Accept: application/json",
    };

    for (const std::string& string : headersStrings) {
        headers = curl_slist_append(headers, string.c_str());
    }

    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);

    curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L); //maximum time allowed for operation to finish, in seconds

    std::string url = influxUrl + "/api/v2/write?org=" + influxOrg + "&bucket=" + influxBucket + "&precision=s";

    if (test_server) {
        sys_log(0, "URL: %s", url.c_str());
        sys_log(0, "curl_fields: %s", curl_fields.c_str());
    }

    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_POST, 1);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, curl_fields.c_str());
    curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
    curl_easy_setopt(curl, CURLOPT_PROTOCOLS, CURLPROTO_HTTP | CURLPROTO_HTTPS);

    CURLcode status = curl_easy_perform(curl);
    if (status != 0)
    {
        if (test_server) {
            sys_log(0, "ERROR: The InfluxDB request failed.");
            sys_log(0, "Error Code: [%d] - [%s]", status, curl_easy_strerror(status));
        }

        Cleanup(curl, headers);

        return false;
    }

    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, http_code);

    if (test_server)
        sys_log(0, "HTTP Status Code: [%ld]", *http_code);

    curl_easy_cleanup(curl);
    curl_slist_free_all(headers);
    curl_global_cleanup();

    return true;
}
#endif