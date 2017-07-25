/**
 *  BaseComposition.h
 *  cppex2
 *  
 *  Header file for abstract composition.
 *
 *  Created by Lauren Cohen on 10/01/2016.
 *  Copyright © 2016 Lauren Cohen. All rights reserved.
 */
#ifndef _BASE_COMPOSITION_H
#define _BASE_COMPOSITION_H

#include <string>
#include <unordered_map>

#define LYRICS_BY "lyrics by: "
#define PERFORMED_BY "performed by: "

using namespace std;

typedef unordered_map<string, unsigned int> CompMap;

/** 
 * Base class for composition types
 */
class BaseComposition
{
public:
    /**
     * override for each composition type
     */
    virtual string data() = 0;
    string title;
    CompMap tags;

	/**
	 * Constructor: constructs Base Composition with the given title and tags references.
	 */
	BaseComposition(const string& title, const CompMap& tags)
    {
        this->title = title;
        this->tags = tags;
    }

	/** 
     * Default destructor.
     */
	~BaseComposition() {}
};

#endif 