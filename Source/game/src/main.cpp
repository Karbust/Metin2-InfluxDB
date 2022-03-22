//Add:
#ifdef ENABLE_AUTO_EVENTS
#include "auto_event_manager.h"
#endif

#ifdef INFLUX_STATS
#include "InfluxData.h"
#endif

//Add:
#ifdef ENABLE_AUTO_EVENTS
    CEventsManager    EventsManager;
#endif

#ifdef INFLUX_STATS
    CInfluxData    InfluxData;
#endif

//Add after: if ( g_bTrafficProfileOn ):
#ifdef ENABLE_AUTO_EVENTS
        EventsManager.Initialize();
#endif

#ifdef INFLUX_STATS
        InfluxData.Initialize();
#endif