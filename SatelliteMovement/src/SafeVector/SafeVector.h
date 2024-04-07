#ifndef SAFEVECTOR_H
#define SAFEVECTOR_H

#include <vector>
#include <mutex>

template <typename T>
class SafeVector {
public:
    void emplace_back(T value) {
        std::lock_guard<std::mutex> lock(mtx_);
        vector_.emplace_back(value);
    }

    T& operator[](size_t pos) {
        std::lock_guard<std::mutex> lock(mtx_);
        return vector_[pos];
    }

    const T& operator[](size_t pos) const {
        std::lock_guard<std::mutex> lock(mtx_);
        return vector_[pos];
    }

    std::vector<T> get(){
        return vector_;
    }

private:
    std::vector<T> vector_;
    std::mutex mtx_;
};


#endif //SAFEVECTOR_H
