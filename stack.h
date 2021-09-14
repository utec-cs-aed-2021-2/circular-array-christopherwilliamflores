#include "circulararray.h"

template <typename T>
class StackArray : public CircularArray<T> { 
public:
    Stack () : CircularArray<T>(){

    }
    Stack (int c) : CircularArray<T>(c) {

    }

    void push (int val) {
        this->push_back(val);
    }

    T pop () {
        return this->pop_back();
    }
};
#endif //LISTACIRCULAR_STACK_H
