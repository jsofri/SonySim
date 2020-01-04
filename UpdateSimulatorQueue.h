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

#include "VarData.h"
#include <queue>
#include <mutex>

class UpdateSimulatorQueue {
public:
    /**
     * enqueue.
     *
     * @param var_data the struct to be enqueued.
     */
    void enqueue(VarData);
    
    /**
     * dequeue.
     *
     * @return the struct to be dequeued.
     */
    VarData dequeue();
    
    /**
     * check if queue is empty.
     *
     * @return boolean
     */
    bool isEmpty();
    
    /**
     * Constructor.
     */
    UpdateSimulatorQueue();
    
    /**
     * Destructor.
     */
    ~UpdateSimulatorQueue();
    
private:
    queue<VarData> * _var_data_queue;
    mutex _locker;
};


#endif //UPDATESIMULATORQUEUE_H
