#ifndef EURYDICE_H
#define EURYDICE_H

#include <string>

class Eurydice {
public:
    Eurydice();
    ~Eurydice();
    
    void run();
    void processData(const std::string& data);
    std::string getStatus() const;
    
private:
    // Private members can be added here
};

#endif // EURYDICE_H 