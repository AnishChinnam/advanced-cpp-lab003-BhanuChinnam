#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "project/exercise.hpp"

TEST_CASE("Default constructor creates empty buffer") {
    DynamicBuffer buffer;
    REQUIRE(buffer.empty() == true);
    REQUIRE(buffer.size() == 0);
}

TEST_CASE("Size and element access work as expected") {
    DynamicBuffer buffer(3);
    buffer.setAt(0, 10);
    buffer.setAt(1, 20);
    buffer.setAt(2, 30);

    REQUIRE(buffer.size() == 3);
    REQUIRE(buffer.at(0) == 10);
    REQUIRE(buffer.at(1) == 20);
    REQUIRE(buffer.at(2) == 30);
    REQUIRE(buffer[0] == 10);
}

TEST_CASE("Copy constructor deep-copies contents") {
    DynamicBuffer original(4);
    original.fill(7);

    DynamicBuffer copy(original);
    copy[0] = 99;

    REQUIRE(original[0] == 7);
    REQUIRE(copy[0] == 99);
}

TEST_CASE("Copy assignment makes an independent copy") {
    DynamicBuffer a(2);
    a[0] = 1;
    a[1] = 2;

    DynamicBuffer b(1);
    b = a;
    b[0] = 42;

    REQUIRE(a[0] == 1);
    REQUIRE(b[0] == 42);
}

TEST_CASE("Move constructor and move assignment transfer ownership cleanly") {
    DynamicBuffer a(3);
    a.fill(5);

    DynamicBuffer b(std::move(a));
    REQUIRE(b.size() == 3);
    REQUIRE(b[2] == 5);

    DynamicBuffer c(1);
    c = std::move(b);
    REQUIRE(c.size() == 3);
    REQUIRE(c[0] == 5);
}

TEST_CASE("Resize preserves values and expands the buffer") {
    DynamicBuffer buffer(2);
    buffer[0] = 10;
    buffer[1] = 20;

    buffer.resize(4);
    REQUIRE(buffer.size() == 4);
    REQUIRE(buffer[0] == 10);
    REQUIRE(buffer[1] == 20);
    REQUIRE(buffer[2] == 0);
}

TEST_CASE("Comparison operators work correctly") {
    DynamicBuffer a(2);
    a[0] = 1;
    a[1] = 2;

    DynamicBuffer b(2);
    b[0] = 1;
    b[1] = 2;

    REQUIRE(a == b);
    REQUIRE(!(a != b));
}
