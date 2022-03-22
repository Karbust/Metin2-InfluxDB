//
// Created by Karbust on 04/02/2022.
//

#ifndef SRC_INFLUXDATA_H
#define SRC_INFLUXDATA_H

#ifdef INFLUX_STATS
#include <curl/curl.h>

class CInfluxData : public singleton<CInfluxData> {
public:
    void Initialize();
    void Check(int day, int hour, int minute, int second);

    static bool cURLCalls(const std::string &curl_fields,long *http_code) ;

    static void Cleanup(CURL* curl, curl_slist* headers) {
        if (curl)
            curl_easy_cleanup(curl);
        if (headers)
            curl_slist_free_all(headers);
        curl_global_cleanup();
    }
};
#endif

#endif //SRC_INFLUXDATA_H