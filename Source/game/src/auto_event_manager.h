#ifndef SRC_AUTO_EVENT_MANAGER_H
#define SRC_AUTO_EVENT_MANAGER_H

class CEventsManager : public singleton<CEventsManager>
{
    enum
    {
        MONDAY = 1,
        TUESDAY = 2,
        WEDNESDAY = 3,
        THURSDAY = 4,
        FRIDAY = 5,
        SATURDAY = 6,
        SUNDAY = 0,
    };

public :
    bool		Initialize();
    void		Destroy();
    void		PrepareChecker();

};

#endif //SRC_AUTO_EVENT_MANAGER_H