/**
 *  RankerFactory.h
 *  cppex2
 *
 *  Header for the ranker factory class and functions.
 *
 *  Created by Lauren Cohen on 10/01/2016.
 *  Copyright © 2016 Lauren Cohen. All rights reserved.
 */

#ifndef _RANKER_FACTORY_H
#define _RANKER_FACTORY_H

#include <vector>
#include <memory>
#include <fstream>
#include "BaseWeightRanker.h"
#include "RankerTypes.h"

typedef shared_ptr<BaseWeightRanker> SharedPtrVect;
typedef vector<SharedPtrVect> VectBaseRanker;

/** 
 * Ranker factory class.
 */
class RankerFactory
{
public:
    VectBaseRanker rankers;
    
    /**
     * shared pointer for the new composition.
     */
	static shared_ptr<BaseWeightRanker> newComp(ifstream& stream);
    
    /** 
     * Default constructor. 
     */
    RankerFactory(){};
    
    /**
     * Constructor: creates an instance of Ranker Factory which creates a ranker with the given stream.
     */
    RankerFactory(ifstream& stream);
    
    /**
     * Destructor - removes all instances of rankers from the memory.
     */
    ~RankerFactory();
    
    private:
    
	/**
	 * Parses tag to tempo with the given tag map reference.
	 */
	static void _parseTagToTempo(TempoMap& tempoTagMap, const string& str);

};
#endif
