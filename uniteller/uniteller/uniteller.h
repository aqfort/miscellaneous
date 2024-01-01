#pragma once

#include "test_runner.h"
#include "profile.h"

#include <string>
#include <vector>
#include <sstream>
#include <mutex>

using namespace std;

// cyclic id class: max value is followed by min value
class Identificator
{
public:
    // permitted symbols, it is better to update them than write new cases with forbidden symbols
    // static const inline vector<char> prefixes = {'A', 'B', 'C', 'E', 'H', 'I', 'K', 'L', 'N', 'O', 'P', 'R', 'S', 'T', 'U', 'W', 'X', 'Y', 'Z'};
    // static const inline vector<char> suffixes = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

    Identificator() = default;
    ~Identificator() = default;

    // bad setter: without checking invalid input
    // can implement parser if it's required
    void Set(const string &id);
    string Increment();

private:
    class Element
    {
    public:
        Element() = default;
        ~Element() = default;

        // char prefix = Identificator::prefixes.front();
        // char suffix = Identificator::suffixes.front();

        char prefix = 'A';
        char suffix = '1';

        // for complex dictionaries could use arrays of permitted symbols
        // and iterate over those arrays
        bool Increment();
    };

    void Increment(string &result);

    // makes string from id_ (vector)
    string ToString();

private:
    vector<Element> id_; // can use array instead of vector, if it's requiered
    const int max_id_size_ = 10;

    mutex mutex_; // async
};
