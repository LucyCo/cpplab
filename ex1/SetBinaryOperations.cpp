/**
 * This file is demonstrating the operators overloading for this exercise
 */
#include <iostream>
#include <string>
#include "MySet.h"

/**
 * main function for executable file
 */
int main()
{
    MySet ops;
    cout << "Creating two sets of Batman villains to destroy Gotham:" << endl;
    MySet set1;
    set1.add("joker", 10.3);
    set1.add("harley", 7);
    set1.add("penguin", 2);
    MySet set2;
    set2.add("nigma", 11.9);
    set2.add("ivy", 13);
    set2.add("bane", 9.1);
    set2.add("joker", 8);
    set2.add("scarecrow", 3.1);
    cout << "Set 1 includes:" << endl;
    set1.printSet();
    cout << "= = = =" << endl;
    cout << "Set 2 includes:" << endl;
    set2.printSet();
    cout << "(of course the joker can play both sets, he's the joker after all.)" << endl;
    cout << "= = = =" << endl;
    cout << "Lets see which set can cause more damage to the wretched city..." << endl;
    //testing comparator
    if (set1 < set2)
    {
        cout << "As expected, set 2 is currently more powerful than set 1" << endl;
    }
    cout << "the two sets of Arkham escapees decide to unite in order to envoke chaos and blow up the city "
    << "hall, the union contains:" << endl;
    //testing union
    ops = set1 | set2;
    ops.printSet();
    cout << "with the city hall ruined, the two sets flee to the outskirts of the city, set 2 temporaily "
    <<
    "parts from the joker, who's off to fight with batsy and the good guys, so after substruction of "
    << "set 1 from set 2, it now contains:" << endl;
    //testing substruction
    ops = set2 - set1;
    ops.printSet();
    MySet goodies;
    goodies.add("batsy", 3);
    goodies.add("jim gordon", 5.5);
    goodies.add("nightwing", 7.4);
    goodies.add("joker", 4);
    cout << "= = = =" << endl;
    cout << "harley misses poodin' so she drags the rest of her set to help him fight off the goodies set "
    << "which, upon arrival she sees that includes:" << endl;
    goodies.printSet();
    cout << "set 1 clashes the goodies who fight back, while the joker again, slips off to cause some more "
    << "havoc elsewhere, so after intersection between goodies set and set 1 who's left?" << endl;
    //testing intersection
    ops = goodies & set1;
    ops.printSet();
    cout << "= = = =" << endl;
    //another comparator and intersection testing
    if (ops == (goodies & set2))
    {
        cout << "after two days of non-stop chaos finally tensed silence returns to gotham with the " <<
        "recapture of all the criminals, except of course the joker who managed to slip off again when "
        << "the goodies set arrest the members of set 2 after seizing set 1 and sending them back to "
        << "Arkham" << endl;
    }
    cout << "= = the end (now to exercise 2) = =" << endl;
    return 0;
}