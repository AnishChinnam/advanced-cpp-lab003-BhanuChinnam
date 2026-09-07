// =======================================================
// GitHub Classroom exercise.
// Implement the class and keep the TODO comments as guidance.
// =======================================================

#include <iostream>
#include "project/exercise.hpp"

int main() {
    DynamicBuffer values(5);
    values.fill(7);
    values.setAt(0, 10);
    values.setAt(1, 20);

    std::cout << "Size: " << values.size() << "\n";
    std::cout << "values[0] = " << values[0] << "\n";
    std::cout << "values[1] = " << values[1] << "\n";

    DynamicBuffer copy(values);
    copy.setAt(2, 42);
    std::cout << "Copy[2] = " << copy[2] << "\n";
    std::cout << "Original[2] = " << values[2] << "\n";

    DynamicBuffer moved(std::move(values));
    std::cout << "Moved[0] = " << moved[0] << "\n";
    std::cout << "Original bool = " << (values ? "true" : "false") << "\n";

    DynamicBuffer resized(3);
    resized.fill(4);
    resized.resize(6);
    resized[5] = 99;
    std::cout << "Resized[5] = " << resized[5] << "\n";

    return 0;
}
