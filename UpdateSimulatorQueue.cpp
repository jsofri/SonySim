/**
 * this object allow making operations on a guarded contatiner.
 * this container serves several threads.
 * container is a queue of data needed to be send to the simulator.
 *
 * @author: Yehonatan Sofri
 * @date: 12.25.19
 */

#include "UpdateSimulatorQueue.h"

/**
 * Ctor.
 */
UpdateSimulatorQueue::UpdateSimulatorQueue() {
    this -> _var_data_queue = new queue<VarData>;
    this -> _locker = PTHREAD_MUTEX_INITIALIZER;
}

/**
 * enqueue.
 *
 * @param var_data the struct to be enqueued.
 */
void UpdateSimulatorQueue::enqueue(VarData var_data) {
    pthread_mutex_lock(&(this->_locker));

    this ->_var_data_queue -> push(var_data);

    pthread_mutex_unlock(&(this->_locker));
}

/**
 * dequeue.
 *
 * @return the struct to be dequeued.
 */
VarData UpdateSimulatorQueue::dequeue() {
    VarData var_data;

    if(this -> isEmpty()) {
        throw "queue is empty";
    }

    pthread_mutex_lock(&(this->_locker));

    var_data = this ->_var_data_queue -> front();

    this ->_var_data_queue ->pop();

    pthread_mutex_unlock(&(this->_locker));

    return var_data;
}

/**
 * check if queue is empty.
 *
 * @return boolean
 */
bool UpdateSimulatorQueue::isEmpty() {
    pthread_mutex_lock(&(this->_locker));
    bool boolean;

    boolean = this -> _var_data_queue->empty();

    pthread_mutex_unlock(&(this->_locker));

    return boolean;
}

/**
 * Dtor.
 */
UpdateSimulatorQueue::~UpdateSimulatorQueue() {
    pthread_mutex_lock(&(this->_locker));

    delete(this->_var_data_queue);

    pthread_mutex_unlock(&(this->_locker));

    pthread_mutex_destroy(&(this->_locker));
}