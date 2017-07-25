/**
 *  CompositionFactory.h
 *  cppex2
 *
 *  Header file for creating a composition according to the given params.
 *
 *  Created by Lauren Cohen on 10/01/2016.
 *  Copyright © 2016 Lauren Cohen. All rights reserved.
 */

#ifndef _COMPOSITION_FACTORY_H
#define _COMPOSITION_FACTORY_H

#include <memory>
#include <fstream>
#include <vector>
#include "CompositionTypes.h"

/**
 * enum class, derived from int, for rankable compositions.
 */
enum class RankableComp
{
    LYRICAL_COMPOSITION,
    INSTRUMENTAL_COMPOSITION,
    DEFAULT = -1
};

typedef vector<pair<RankableComp, shared_ptr<BaseComposition> > > VectBaseComp;

/** 
 * Composition Factory class. 
 */
class CompositionFactory
{
public:
    
    VectBaseComp compositions;
    
    /**
     * Default constructor.
     */
    CompositionFactory(){};

    /**
     * Constructor: creates a new instance of Composition Factory with the given stream.
     */
    CompositionFactory(ifstream& stream)
    {
        if (stream.is_open())
        {
            while (!stream.eof())
            {
                VectBaseComp::value_type newComposition = CompositionFactory::newComp(stream);
                if (newComposition.second != nullptr)
                {
                    compositions.push_back(newComposition);
                }
            }
        }
    }
    
    /**
     * Destructor.
     */
    ~CompositionFactory();
    
    /**
     * shared pointer for the new composition.
     */
    static VectBaseComp::value_type newComp(ifstream& stream);
    
private:
    
    /**
     * parses list of words to map of word count. If withWeights is given then creates pairs of string, int
     * in a map.
     */
    static CompMap _createCompMap(const string& str, bool withWeights = 0);
};
    
#endif