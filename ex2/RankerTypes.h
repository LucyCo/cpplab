/**
 *  RankerTypes.h
 *  cppex2
 *
 *  Header for all the ranker types classes.
 *
 *  Created by Lauren Cohen on 10/01/2016.
 *  Copyright © 2016 Lauren Cohen. All rights reserved.
 */

#ifndef _RANKER_TYPES_H
#define _RANKER_TYPES_H

#include "BaseWeightRanker.h"
#include "CompositionTypes.h"
#include "BaseComposition.h"

//BaseWeightRanker derived classes header
typedef unordered_map<string, pair<double, double> > TempoMap;

/** 
 * instruments ranker for instrumental compositions.
 */
class InstrumentRanker : public BaseWeightRanker
{
public:
    /**
     * Constructor: creates an instance of Instrumental Ranker with the given rankable type and weight
     */
    InstrumentRanker(const RankableComp type, unsigned int weight) : BaseWeightRanker(type, weight)
    {}
    
    /** 
     * Default sestructor. 
     */
    ~InstrumentRanker(){};
    
    /**
     * Check how much the keyword is relevant for this composition.
     */
    virtual unsigned int checkKeyWord(const BaseComposition& composition, string keyword) override;
};

/**
 * lyrics ranker for lyrical compositions.
 */
class LyricsRanker : public BaseWeightRanker
{
public:
    /**
     * Constructor: creates an instance of Instrumental Ranker with the given rankable type and weight
     */
    LyricsRanker(const RankableComp type, unsigned int weight) : BaseWeightRanker(type, weight)
    {}
    
    /**
     * Default sestructor.
     */
    ~LyricsRanker(){};
    
    /**
     * Check how much the keyword is relevant for this composition.
     */
    virtual unsigned int checkKeyWord(const BaseComposition& composition, string keyword) override;
};

/**
 * tags ranker for all compositions.
 */
class TagRanker : public BaseWeightRanker
{
public:
    /**
     * Constructor: creates an instance of Instrumental Ranker with the given rankable type and weight
     */
    TagRanker(const RankableComp type, unsigned int weight) : BaseWeightRanker(type, weight)
    {}
    
    /**
     * Default sestructor.
     */
    ~TagRanker(){};
    
    /**
     * Check how much the keyword is relevant for this composition.
     */
    virtual unsigned int checkKeyWord(const BaseComposition& composition, string keyword) override;
};

/**
 * tempo ranker class.
 */
class TempoRanker : public BaseWeightRanker
{
public:
    TempoMap tempoTagMap;
    
    /**
     * Constructor: creates an instance of Instrumental Ranker with the given rankable type, weight and
     * tempo map.
     */
    TempoRanker(const RankableComp type, unsigned int weight, const TempoMap& tempoTagMap) : BaseWeightRanker(type, weight)
    {
        this->tempoTagMap = tempoTagMap;
    }

    /**
     * Default sestructor.
     */
    ~TempoRanker(){};
    
    /**
     * Check how much the keyword is relevant for this composition.
     */
    virtual unsigned int checkKeyWord(const BaseComposition& composition, string keyword) override;
};

#endif /* RankerTypes_h */
