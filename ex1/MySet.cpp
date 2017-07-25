/**
 * Implementation for MySet header file and class
 */
#include "MySet.h"
#include <string>
#include <iostream>

using namespace std;

/**
 * The hash function.
 * Input parameter - any C++ string.
 * Return value: the hash value - the sum of all the characters of the string
 *   (according to their ASCII value). The hash value of the
 *   empty string is 0 (since there are no characters, their sum according to
 *   the ASCII value is 0).
 * NOTE: In a better design the function would have belong to the string class
 *	 (or to a class that is derived from std::string). We implement it as a "stand
 *	 alone" function since you didn't learn inheritance yet. Keep the function
 *	 global (it's important to the automatic tests).
 */
static int myHashFunction(const string &str)
{
    int sum = 0;
    for (unsigned int i = 0; i < str.length(); i++)
    {
        char x = str.at(i);
        sum += int(x);
    }
    return sum;
}

/**
 * Class Node is an inner class for MySet, which implements the nodes of the set
 */
class MySet::Node
{
public:
    string _key;
    double _data;
    Node* prev;
    Node()
    {
        prev = NULL;
    }
};

/**
 * a private function which initializes the current MySet to an empty MySet set.
 */
void MySet::_init()
{
    first = NULL;
    last = NULL;
    setSize = 0;
}
    
/**
 * Empty constructor
 */
MySet::MySet()
{
    _init();
}

/**
 * Creates an instance of MySet and adds this first element to it
 */
MySet::MySet(string key, double data)
{
    _init();
    add(key, data);
};

/**
 * Copy constructor
 */
MySet::MySet(const MySet &set)
{
    _init();
    Node * element = set.last;
    while (element != NULL)
    {
        add(element->_key, element->_data);
        element = element->prev;
    }
};

/**
 * Destructor
 */
MySet::~MySet()
{
    if (first != NULL)
    {
        Node* element = last;
        while (element != NULL)
        {
            Node * temp = element->prev;
            delete element;
            --setSize;
            element = temp;
        }
        delete element;
    }
}

/**
 * resets this to an empty set
 */
void MySet::reset()
{
    if (!isEmpty())
    {
        Node * temp = last->prev;
        Node * element = last;
        while (element != NULL)
        {
            remove(element->_key);
            element = temp;
            if (temp != NULL)
            {
                temp = temp->prev;
            }
        }
    }
    _init();
}

/**
 * - Add a string to the MySet. and add the element to the begin of of the data structure.
 * If the element already exists , change its data to the input parameter.
 * parameters: string(key),double(data)
 *  return type void
 */
void MySet::add(string key, double data)
{
    if (!isInSet(key, data))
    {
        Node* element = new Node;
        element->_data = data;
        element->_key = key;
        if (!isEmpty())
        {
            first->prev = element;
        }
        else
        {
            last = element;
        }
        first = element;
        ++setSize;
    }
}

/**
 * Remove a string from the MySet.
 * Return the numbr of removed elements (0/1)
 * parameters: key
 * return type size_t
 */
size_t MySet::remove(string key)
{
    double num;
    if (isInSet(key, num))
    {
        if (last->_key == key)
        {
            if (last->prev == NULL)
            { //only one element in set
                Node* element = last;
                delete element;
                last = NULL;
            }
            else
            {
                Node* element = last;
                delete element;
                last = last->prev;
            }
        }
        else
        {
            Node* element = last;
            while (element->prev != NULL)
            {
                if ((key == element->prev->_key) && (element->prev == first))
                { //if the element to be deleted is the first
                    first = element;
                    delete element->prev;
                    first->prev = NULL;
                }
                else if ((key == element->prev->_key) && !(element->prev == first))
                {
                    Node* temp = element->prev;
                    delete temp;
                    element->prev = element->prev->prev;
                }
                else
                {
                    element = element->prev;
                }
            }
        }
        --setSize;
        return 1;
    }
    return 0;
}

/**
 * Return true if the element is in the Set, or false otherwise.
 * If the element exists in the Set, return in 'data' its appropriate data
 * value. Otherwise don't change the value of 'data'.
 * parameters: key,data
 *	return type: bool
 */
bool MySet::isInSet(string key, double &data) const
{
    Node* current = this->last;
    while (current != NULL)
    {
        if (current->_key == key)
        {
            data = current->_data;
            return true;
        }
        if (current == this->first)
        { //current node is the first in the set but the key wasn't found, return false
            return false;
        }
        current = current->prev;
    }
    return false;
}

/**
 * return true if the list is an empty list
 */
bool MySet::isEmpty() const
{
    return (setSize == 0);
}

/**
 * Return number of elements stored in the Set.
 *  return type size_t
 */
size_t MySet::size()
{
    return setSize;
}

/**
 * print Set contents.
 */
void MySet::printSet() const
{
    if (!isEmpty())
    {
        Node *element = last;
        while (element != NULL)
        {
            cout << element->_key << "," << element->_data << endl;
            element = element->prev;
        }
    }
    else
    {
        cout << "EMPTY" << endl;
    }
}

/**
 * Return sum of all data elements stored in the Set.
 * return type double
 */
double MySet::sumSet() const
{
    double sum = 0;
    if (!isEmpty())
    {
        Node *element = last;
        while (element != NULL)
        {
            sum += element->_data;
            element = element->prev;
        }
    }
    return sum;
}

/**
 * Return the total myHashFunction weight of all the Set keys
 * return type double
 */
 double MySet::totWeight() const
{
    double weight = 0;
    if (!isEmpty())
    {
        Node *element = last;
        while (element != NULL)
        {
            const string str = element->_key;
            weight += myHashFunction(str);
            element = element->prev;
        }
    }
    return weight;
}

/**
 * returns an instance of a set after performing assignment operator between the two sets
 */
MySet &MySet::operator=(const MySet& set)
{
    if (this != &set)
    {
        reset();
        Node* pointer = set.last;
        while (pointer != NULL)
        {
            add(pointer->_key, pointer->_data);
            pointer = pointer->prev;
        }

    }
    return *this;
}

/**
 * returns an instance of a set after performing substruction operator between the two sets
 */
MySet MySet::operator-(const MySet& set)
{
    MySet newSet;
    double dataRef = 0;
    Node* element = last;
    while (element != NULL)
    {
        if (!set.isInSet(element->_key, dataRef))
        {
            newSet.add(element->_key, element->_data);
        }
        element = element->prev;
    }
    return newSet;
}

/**
 * returns an instance of a set after performing union operator between the two sets
 */
MySet MySet::operator|(const MySet& set)
{
    MySet newSet(*this);
    Node* element = set.last;
    double dataRef;
    while (element != NULL)
    {
        if (!isInSet(element->_key, dataRef))
        {
            newSet.add(element->_key, element->_data);
        }
        element = element->prev;
    }
    return newSet;
}

/**
 * returns an instance of a set after performing intersection operator between the two sets
 */
MySet MySet::operator&(const MySet& set)
{
    MySet newSet;
    double dataRef = 0;
    Node* element = last;
    while (element != NULL)
    {
        if (set.isInSet(element->_key, dataRef))
        {
            newSet.add(element->_key, element->_data);
        }
        element = element->prev;
    }
    return newSet;
}

/**
 * returns true if the right set weights more than the left set
 */
bool MySet::operator<(const MySet& set)
{
    return (this->totWeight() < set.totWeight());
}

/**
 * returns true if the left set weights more than the right set
 */
bool MySet::operator>(const MySet& set)
{
    return (this->totWeight() > set.totWeight());
}

/**
 * returns true if the weight of the two sets are equal
 */
bool MySet::operator== (const MySet& set)
{
    return (this->totWeight() == set.totWeight());
}