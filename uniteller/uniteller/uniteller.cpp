#include "uniteller.h"
#include "profile.h"

// bad setter: without checking invalid input
// can implement parser if it's required
void Identificator::Set(const string &id)
{
    lock_guard<mutex> guard(mutex_); // critical section lock for whole function

    id_.clear();

    stringstream ss;

    ss.str(id);

    Element element;

    while (!ss.eof())
    {
        ss >> element.prefix >> element.suffix;
        ss.ignore();

        id_.insert(id_.begin(), element);
    }
}

string Identificator::Increment()
{
    lock_guard<mutex> guard(mutex_); // critical section lock for whole function

    bool increment_next = false;

    for (auto &element : id_)
    {
        increment_next = element.Increment();
        if (!increment_next)
        {
            break;
        }
    }

    // id is cyclic: after reaching max value -> min value
    if (increment_next)
    {
        if (!(id_.size() < max_id_size_))
        {
            id_.clear();
        }
        id_.push_back(Element{});
    }

    return ToString(); // copy elision
}

// for complex dictionaries could use arrays of permitted symbols
// and iterate over those arrays
bool Identificator::Element::Increment()
{
    bool res = false;

    if (++suffix > '9')
    {
        suffix = '1';

        prefix++;
        while (prefix == 'D' ||
               prefix == 'F' ||
               prefix == 'G' ||
               prefix == 'J' ||
               prefix == 'M' ||
               prefix == 'Q' ||
               prefix == 'V')
        {
            prefix++;
        }

        if (prefix > 'Z')
        {
            prefix = 'A';
            res = true;
        }
    }

    return res; // nrvo
}

// makes string from id_ (vector)
string Identificator::ToString()
{
    string result;

    for (auto it = id_.rbegin(); it != id_.rend(); it++)
    {
        result += it->prefix;
        result += it->suffix;

        if (next(it) != id_.rend())
        {
            result += '-';
        }
    }

    return result; // nrvo
}