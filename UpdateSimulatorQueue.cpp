/**
 * this object allow making operations on a guarded contatiner.
 * this container serves several threads.
 * container is a queue of data needed to be send to the simulator.
 *
 * @author: Yehonatan Sofri
 * @date: 12.25.19
 */

#include "GeneralData.h"
#include "GlobalVars.h"

/**
 * Ctor.
 */
UpdateSimulatorQueue::UpdateSimulatorQueue() {
    this -> _var_data_queue = new queue<VarData>;
}

/**
 * enqueue.
 *
 * @param var_data the struct to be enqueued.
 */
void UpdateSimulatorQueue::enqueue(VarData var_data) {
    lock_guard<mutex> lock(_locker);

    this -> _var_data_queue -> push(var_data);
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

    lock_guard<mutex> lock(_locker);

    var_data = this ->_var_data_queue -> front();

    this ->_var_data_queue ->pop();

    return var_data;
}

/**
 * check if queue is empty.
 *
 * @return boolean
 */
bool UpdateSimulatorQueue::isEmpty() {
    lock_guard<mutex> lock(_locker);

    return this -> _var_data_queue -> empty();
}

/**
 * Dtor.
 */
UpdateSimulatorQueue::~UpdateSimulatorQueue() {

    //make sure no thread is on object
    if (_locker.try_lock()) {
        _locker.unlock();
    } else {
        _locker.lock();
        _locker.unlock();
    }

    delete(this->_var_data_queue);
}