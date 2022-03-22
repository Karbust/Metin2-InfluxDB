//Add before the last #endif:

#ifdef INFLUX_STATS
extern bool isInfluxEnabled;
extern std::string influxUrl;
extern std::string influxToken;
extern std::string influxOrg;
extern std::string influxBucket;
#endif