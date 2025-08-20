#include "AbstractSample.hpp"

std::ostream& operator<<(std::ostream& os, const AbstractSample& sample) {
    // Should not be called directly, instead should be subclasses' representation
    os << "!AbstractSample!";
    return os;
}
