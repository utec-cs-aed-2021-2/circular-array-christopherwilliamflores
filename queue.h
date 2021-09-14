#include "circulararray.h"

template <class T>
class Queue : public CircularArray<T> {
public:
    Queue () : CircularArray<T>(){

    }
    Queue (int c) : CircularArray<T>(c) {

    }

    void enQueue (int val) {
        this->push_back(val);
    }

    T deQueue () {
        return this->pop_front();
    }
};
#endif //LISTACIRCULAR_QUEUE_H
