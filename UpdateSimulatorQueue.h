/**
 * this object allow making operations on a guarded contatiner.
 * this container serves several threads.
 * container is a queue of data needed to be send to the simulator.
 *
 * @author: Yehonatan Sofri
 * @date: 12.25.19
 */

#ifndef UPDATESIMULATORQUEUE_H
#define UPDATESIMULATORQUEUE_H

#include "GeneralData.h"

class UpdateSimulatorQueue {
public:
    void enqueue(VarData);
    VarData dequeue();
    bool isEmpty();
    UpdateSimulatorQueue();
    ~UpdateSimulatorQueue();
private:
    queue<VarData> * _var_data_queue;
    pthread_mutex_t _locker;
};


#endif //SONYSIM_UPDATESIMULATORQUEUE_H
