#include "project/exercise.hpp"
#include <algorithm>
#include <utility>

// Default constructor: owns nothing.
DynamicBuffer::DynamicBuffer() : data_(nullptr), size_(0) {
}

// Allocate a zero-initialized buffer. The () on new int[capacity]()
// value-initializes every element to 0.
DynamicBuffer::DynamicBuffer(size_t capacity) : data_(nullptr), size_(0) {
    if (capacity > 0) {
        data_ = new int[capacity]();
        size_ = capacity;
    }
}

// Deep-copy constructor: allocates its own storage.
DynamicBuffer::DynamicBuffer(const DynamicBuffer& other) : data_(nullptr), size_(0) {
    copyFrom(other);
}

// Move constructor: steals the pointer and leaves the source empty but valid.
DynamicBuffer::DynamicBuffer(DynamicBuffer&& other) noexcept
    : data_(other.data_), size_(other.size_) {
    other.data_ = nullptr;
    other.size_ = 0;
}

// Destructor: RAII cleanup.
DynamicBuffer::~DynamicBuffer() {
    release();
}

// Copy assignment via copy-and-swap: strong exception safety.
// If the copy throws, *this is untouched.
DynamicBuffer& DynamicBuffer::operator=(const DynamicBuffer& other) {
    if (this != &other) {
        DynamicBuffer temp(other);
        swap(temp);
    }
    return *this;
}

// Move assignment: release what we hold, then take the source's resource.
DynamicBuffer& DynamicBuffer::operator=(DynamicBuffer&& other) noexcept {
    if (this != &other) {
        release();
        data_ = other.data_;
        size_ = other.size_;
        other.data_ = nullptr;
        other.size_ = 0;
    }
    return *this;
}

size_t DynamicBuffer::size() const noexcept {
    return size_;
}

bool DynamicBuffer::empty() const noexcept {
    return size_ == 0;
}

// Resize preserving the first min(old, new) values; new slots are zeroed.
// The old buffer is freed only after the new allocation succeeds.
void DynamicBuffer::resize(size_t newSize) {
    if (newSize == size_) {
        return;
    }
    if (newSize == 0) {
        release();
        return;
    }
    int* buffer = new int[newSize]();
    const size_t kept = std::min(size_, newSize);
    for (size_t i = 0; i < kept; ++i) {
        buffer[i] = data_[i];
    }
    delete[] data_;
    data_ = buffer;
    size_ = newSize;
}

void DynamicBuffer::fill(int value) {
    for (size_t i = 0; i < size_; ++i) {
        data_[i] = value;
    }
}

// Bounds-checked write.
void DynamicBuffer::setAt(size_t index, int value) {
    if (index >= size_) {
        throw std::out_of_range("DynamicBuffer::setAt: index out of range");
    }
    data_[index] = value;
}

// Bounds-checked read.
int DynamicBuffer::at(size_t index) const {
    if (index >= size_) {
        throw std::out_of_range("DynamicBuffer::at: index out of range");
    }
    return data_[index];
}

// Unchecked access, matching std::vector's operator[] contract.
int& DynamicBuffer::operator[](size_t index) {
    return data_[index];
}

const int& DynamicBuffer::operator[](size_t index) const {
    return data_[index];
}

bool DynamicBuffer::operator==(const DynamicBuffer& other) const {
    if (size_ != other.size_) {
        return false;
    }
    for (size_t i = 0; i < size_; ++i) {
        if (data_[i] != other.data_[i]) {
            return false;
        }
    }
    return true;
}

bool DynamicBuffer::operator!=(const DynamicBuffer& other) const {
    return !(*this == other);
}

// True when the buffer owns usable storage.
DynamicBuffer::operator bool() const noexcept {
    return data_ != nullptr && size_ > 0;
}

// Free the storage and return to the empty-but-valid state.
void DynamicBuffer::release() {
    delete[] data_;
    data_ = nullptr;
    size_ = 0;
}

// Replace current contents with a deep copy of other.
void DynamicBuffer::copyFrom(const DynamicBuffer& other) {
    release();
    if (other.size_ > 0) {
        data_ = new int[other.size_];
        for (size_t i = 0; i < other.size_; ++i) {
            data_[i] = other.data_[i];
        }
        size_ = other.size_;
    }
}

void DynamicBuffer::swap(DynamicBuffer& other) noexcept {
    std::swap(data_, other.data_);
    std::swap(size_, other.size_);
}
