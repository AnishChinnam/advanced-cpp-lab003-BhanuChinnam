#pragma once

#include <cstddef>
#include <stdexcept>
#include <string>

// =======================================================
// TODO: This file defines the class contract.
// Implement the class in src/exercise.cpp.
// You are not allowed to use std::vector for this exercise.
// =======================================================

class DynamicBuffer {
public:
    DynamicBuffer();
    explicit DynamicBuffer(size_t capacity);
    DynamicBuffer(const DynamicBuffer& other);
    DynamicBuffer& operator=(const DynamicBuffer& other);
    DynamicBuffer(DynamicBuffer&& other) noexcept;
    DynamicBuffer& operator=(DynamicBuffer&& other) noexcept;
    ~DynamicBuffer();

    size_t size() const noexcept;
    bool empty() const noexcept;

    void resize(size_t newSize);
    void fill(int value);
    void setAt(size_t index, int value);
    int at(size_t index) const;

    int& operator[](size_t index);
    const int& operator[](size_t index) const;

    bool operator==(const DynamicBuffer& other) const;
    bool operator!=(const DynamicBuffer& other) const;
    explicit operator bool() const noexcept;

private:
    int* data_;
    size_t size_;

    void release();
    void copyFrom(const DynamicBuffer& other);
    void swap(DynamicBuffer& other) noexcept;
};

