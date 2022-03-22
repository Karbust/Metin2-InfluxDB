//Add:

#ifdef INFLUX_STATS
//Replace the following variables with your values, or load them from CONFIG.
bool isInfluxEnabled = false;
std::string influxUrl = "http://127.0.0.1:8086";
std::string influxToken = "<token>";
std::string influxOrg = "<organization>";
std::string influxBucket = "<bucket>";
#endif

//Add:
#ifdef INFLUX_STATS
        TOKEN("INFLUX_ENABLE")
        {
            int flag = 0;

            str_to_number(flag, value_string);

            if (1 == flag)
            {
                isInfluxEnabled = true;
                fprintf(stderr, "INFLUX_ENABLE: %i\n", flag);
            }
        }
        TOKEN("INFLUX_URL")
        {
            influxUrl = value_string;
            fprintf(stderr, "INFLUX_URL: %s\n", influxUrl.c_str());
        }

        TOKEN("INFLUX_TOKEN")
        {
            influxToken = value_string;
            fprintf(stderr, "INFLUX_TOKEN: %s\n", influxToken.c_str());
        }

        TOKEN("INFLUX_ORG")
        {
            influxOrg = value_string;
            fprintf(stderr, "INFLUX_ORG: %s\n", influxOrg.c_str());
        }

        TOKEN("INFLUX_BUCKET")
        {
            influxBucket = value_string;
            fprintf(stderr, "INFLUX_BUCKET: %s\n", influxBucket.c_str());
        }
#endif