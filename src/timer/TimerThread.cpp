#include <TimerThread.hpp>
#include <iostream>
#include <chrono>
#include <ctime>
#include <msg/msg_format.hpp>

int getCurrentTime()
{
    auto current_time = std::chrono::system_clock::now();
    std::time_t time_now = std::chrono::system_clock::to_time_t(current_time);
    int seconds_since_epoch = static_cast<int>(time_now);
    return seconds_since_epoch;
}

void TimerThread::addToQueue(int seconds, RoomHandler *room, int mode)
{
    // get time in queue push by timestamp

    int timeEnd = seconds + getCurrentTime();
    TimeRoom tr;

    tr.room = room;
    tr.timestamp = timeEnd;
    tr.mode = mode;

    queueTimeHandler.push(tr);
}

void TimerThread::countTime()
{
    while (1)
    {
        int now = getCurrentTime();
        std::this_thread::sleep_for(std::chrono::seconds(1));
        TimeRoom t = queueTimeHandler.front();
        RoomHandler *r = t.room;
        int m = t.mode;

        if(t.timestamp < now)
            {
                queueTimeHandler.pop();
                if( m == 1 ){
                    r->setState(new InGameState(r , r->roundIndex+1));
                }
                else if(m == 2){
                    // state ping
                }
            }
    }
}