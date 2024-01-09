//#include <TimerThread.hpp>
#include <safe_queue.hpp>
#include "type/msg_base.hpp"
#include "room_handler.hpp"

struct TimeRoom{
    int timestamp;
    int mode;
    RoomHandler *room;
};

class TimerThread
{
    static TSQueue<TimeRoom> queueTimeHandler;
    
    static void addToQueue(int seconds, RoomHandler* room , int mode);

    void countTime();
};
