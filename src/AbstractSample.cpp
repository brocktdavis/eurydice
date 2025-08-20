#include "AbstractSample.hpp"

std::ostream& operator<<(std::ostream& os, const AbstractSample& sample) {
    os << sample.describe();
    return os;
}
