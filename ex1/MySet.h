/**
 * Header file for MySet.cpp
 */
#ifndef MY_SET_H
#define MY_SET_H
#include <string>

using namespace std;

/**
 * The definition of the Set
 */
class MySet
{

private:
    class Node; //private class for the intersections
    Node* first;
    Node* last;
    size_t setSize;
    
    /**
     * a private function which initializes the current MySet to an empty MySet set.
     */
    void _init();

public:
    //constructors / destructor

    /**
     * empty constructor
     */
    MySet(); //empty
    
    /**
     * constructor by single value
     */
    MySet(string key, double data); //by single value
    
    /**
     * copy constructor
     */
    MySet(const MySet &set); //copy constructor
    
    /**
     * destructor
     */
    ~MySet(); //delete MySet

    /**
     * - Add a string to the MySet. and add the element to the begin of of the data structure.
     * If the element already exists , change its data to the input parameter.
     * parameters: string(key),double(data)
     *  return type void
     */
    void add(string key, double data);

    /**
     * Remove a string from the MySet.
     * Return the numbr of removed elements (0/1)
     * parameters: key
     * return type size_t
     */
    size_t remove(string key);

    /**
     * Return true if the element is in the Set, or false otherwise.
     * If the element exists in the Set, return in 'data' its appropriate data
     * value. Otherwise don't change the value of 'data'.
     * parameters: key,data
     *	return type: bool
     */
    bool isInSet(string key, double &data) const;

    /**
     * return true if the list is an empty list
     */
    bool isEmpty() const;

    /**
     * Return number of elements stored in the Set.
     *  return type size_t
     */
    size_t size();

    /**
     * print Set contents.
     */
    void printSet() const;

    /**
     * Return sum of all data elements stored in the Set.
     * return type double
     */
    double sumSet() const;

    /**
     * Return the total myHashFunction weight of all the Set keys
     * return type double
     */
    double totWeight() const;
    
    /**
     * resets this to an empty set
     */
    void reset();

    //================ operators override ===================
    /**
     * returns true if the left set weights more than the right set
     */
    bool operator>(const MySet&  set);
    
    /**
     * returns true if the right set weights more than the left set
     */
    bool operator<(const MySet& set);
    
    /**
     * returns true if the weight of the two sets are equal
     */
    bool operator==(const MySet& set);
    
    /**
     * returns an instance of a set after performing assignment operator between the two sets
     */
    MySet & operator=(const MySet& set);
    
    /**
     * returns an instance of a set after performing substruction operator between the two sets
     */
    MySet operator-(const MySet& set);
    
    /**
     * returns an instance of a set after performing union operator between the two sets
     */
    MySet operator|(const MySet& set);
    
    /**
     * returns an instance of a set after performing intersection operator between the two sets
     */
    MySet operator&(const MySet& set);
};

#endif

