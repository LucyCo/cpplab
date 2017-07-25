/**
 *  BaseWeightRanker.h
 *  cppex2
 *
 *  Header file of the base ranker class. all ranker types classes will be derived from this one.
 *
 *  Created by Lauren Cohen on 10/01/2016.
 *  Copyright © 2016 Lauren Cohen. All rights reserved.
 */

#ifndef _BASE_WEIGHT_RANKER_H
#define _BASE_WEIGHT_RANKER_H

#include <string>
#include "BaseComposition.h"
#include "CompositionFactory.h"

/** 
 * Base class for ranker types classes.
 */
class BaseWeightRanker
{
public:
    unsigned int weight;
    //the type of composition with ranker works with
    RankableComp type;
    
	/**
	 * Constructor: creates an instance of Base Weight Ranker with the given type and reference to weight
	 */
    BaseWeightRanker(const RankableComp type, unsigned int& weight)
    {
        this->weight = weight;
        this->type = type;
    }
    
	/** 
     * Default destructor. 
     */
    ~BaseWeightRanker(){};

	/**
	* Check how much the keyword is relevant for this composition - will be overriden with each ranker type
	*/
	virtual unsigned int checkKeyWord(const BaseComposition& composition, string keyword) = 0;
};

#endif
