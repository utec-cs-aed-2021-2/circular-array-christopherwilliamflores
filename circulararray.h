#include <iostream>
#include <algorithm>
using namespace std;

template <class T>
class CircularArray {
protected:
    T *arr;
    int capacity, len;
    int back, front;
public:
    CircularArray(); // done
    CircularArray(int _capacity); // done
    virtual ~CircularArray(); // done
    void push_front(T data); // done
    void push_back(T data); // done
    void insert(T data, int pos);
    T pop_front(); // done
    T pop_back(); // done
    bool is_full(); // done
    bool is_empty(); // done
    int size(); // done
    void display(); // done
    void clear(); // done
    T &operator[](int); // done
    void sort(); // done
    bool is_sorted(); // done
    CircularArray *reverse(); // done
    void merge (int l, int m, int r); // done
    void mergesort (int l, int r); // done
private:
    int next(int); // done
    int prev(int); // done
    void expand(); // done
};

template <class T>
void CircularArray<T>::merge(int l, int m, int r) {
    int l2 = m-l+1, r2 = r-m;
    int l3[l2], r3[r2];
    for(int i = 0; i < l2; i++) {
        l3[i] = (*this)[l + i];
    }
    for(int j = 0; j<r2; j++) {
        r3[j] = (*this)[m + 1 + j];
    }
    int i = 0, j = 0, k = l;
    while(i < l2 && j < r2) {
        if(l3[i] <= r3[j]) {
            (*this)[k] = l3[i++];
        } else{
            (*this)[k] = r3[j++];
        }
        k++;
    }
    while (i < l2) {
        (*this)[k++] = l3[i++];
    }
    while (j < r2) {
        (*this)[k++] = r3[j++];
    }
}

template <class T>
void CircularArray<T>::mergesort(int l, int r) {
    if (l < r) {
        int m = l+(r-l)/2;
        mergesort(l, m);
        mergesort(m+1, r);
        merge(l, m, r);
    }
}

template <class T>
void CircularArray<T>::insert(T data, int pos) {
    if (this->is_full() || this->is_empty()) {
        cout << "No se puede insertar\n";
        return;
    }
    for (int i = this->size(); i > pos; i--) {
        (*this)[i] = (*this)[i-1];
    }
    (*this)[pos] = data;
}

template <class T>
CircularArray<T> * CircularArray<T>::reverse() {
    CircularArray<T>* temp = new CircularArray<T>(this->capacity);
    int it = this->back;
    for (int i = 0; i < this->size(); i++) {
        temp->push_back(this->arr[it]);
        it = this->prev(it);
    }
    return temp;
}

template <class T>
bool CircularArray<T>::is_sorted() {
    int it = this->front;
    for (int i = 0; i < this->size()-1; i++) {
        if ((*this)[it] > (*this)[it+1]) { return false; }
        it = this->next(it);
    }
    return true;
}

template <class T>
void CircularArray<T>::sort() {
    this->mergesort(0, this->size()-1);
    /*this->front = 0;
    this->back = this->len-1;*/
}

template <class T>
T& CircularArray<T>::operator[] (int i) {
    if (this->is_empty ()) {
        cout << "Lista vacía.\n";
        exit (0);
    }
    return this->arr[(i)%(this->capacity+1)];
}

template <class T>
void CircularArray<T>::clear () {
    this->len = 0;
    this->front = this->back = -1;
}

template <class T>
int CircularArray<T>::size () {
    return this->len;
}

template <class T>
T CircularArray<T>::pop_front () {
    if (this->size() == 1) {
        this->len--;
        this->front = this->back = -1;
        return this->arr[0];
    } else if (!this->is_empty ()) {
        this->len--;
        T temp = this->arr[this->front];
        this->front = this->next(this->front);
        return temp;
    }
}

template <class T>
T CircularArray<T>::pop_back () {
    if (this->size() == 1) {
        this->len--;
        this->front = this->back = -1;
        return this->arr[0];
    } else if (!this->is_empty ()) {
        this->len--;
        T temp = this->arr[this->back];
        this->back = this->prev(this->back);
        return temp;
    }
}

template <class T>
void CircularArray<T>::expand () {
    T* temp = this->arr;
    int it = this->front;
    this->arr = nullptr;
    this->arr = new T[this->capacity*2];
    for (int i = 0; i < this->capacity; i++) {
        this->arr[i] = temp[it];
        it = this->next(it);
    }
    delete [] temp;
    this->back = capacity-1;
    this->front = 0;
    this->capacity *= 2;
}

template <class T>
void CircularArray<T>::push_back (T data) {
    if (this->is_empty()) {
        this->arr[0] = data;
        this->back = this->front = 0;
    } else if (this->is_full()) {
        this->expand();
        this->back = this->next(this->back);
        this->arr[this->back] = data;
    } else {
        this->back = this->next(this->back);
        this->arr[this->back] = data;
    }
    this->len++;
}

template <class T>
void CircularArray<T>::push_front (T data) {
    if (this->is_empty()) {
        this->arr[0] = data;
        this->back = this->front = 0;
    } else if (this->is_full()) {
        this->expand();
        this->front = this->prev(this->front);
        this->arr[this->front] = data;
    } else {
        this->front = this->prev(this->front);
        this->arr[this->front] = data;
    }
    this->len++;
}

template <class T>
CircularArray<T>::CircularArray() {
    this->capacity = 0;
    this->front = this->back = -1;
    this->arr = new T[0];
    this->len = 0;
}

template <class T>
CircularArray<T>::CircularArray(int _capacity) {
    this->capacity = _capacity;
    this->front = this->back = -1;
    this->arr = new T[_capacity];
    this->len = 0;
}

template <class T>
CircularArray<T>::~CircularArray() {
    delete[] arr;
}

template <class T>
int CircularArray<T>::prev(int index) {
    return (index == 0) ? this->capacity - 1 : index - 1;
}

template <class T>
int CircularArray<T>::next(int index) {
    return (index + 1) % this->capacity;
}

template <class T>
bool CircularArray<T>::is_empty() {
    return this->front == -1;
}

template <class T>
bool CircularArray<T>::is_full() {
    return this->front == this->next(this->back) && !this->is_empty();
}

template <class T>
void CircularArray<T>::display() {
    int it = this->front;
    for (int i = 0; i < this->size(); i++) {
        cout << (*this)[it] << ",";
        it = this->next(it);
    }
    cout << endl;
}
#endif //LISTACIRCULAR_CIRCULARARRAY_H

