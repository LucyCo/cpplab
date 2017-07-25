/**
 *  RankerTypes.cpp
 *  cppex2
 *
 *  Implementation file for all the ranker types classes.
 *
 *  Created by Lauren Cohen on 10/01/2016.
 *  Copyright © 2016 Lauren Cohen. All rights reserved.
 */

#include <stdio.h>
#include "RankerTypes.h"
#include <cmath>

/**
 * Implementation for the overriden checkKeyWord function with check how much the given keyword is
 * relevant to this Instrumental Composition.
 */
unsigned int InstrumentRanker::checkKeyWord(const BaseComposition& composition, string keyword)
{
    InstrumentalComposition instrumental = dynamic_cast<InstrumentalComposition&>(const_cast<BaseComposition&>(composition));
    if (instrumental.instruments.find(keyword) != instrumental.instruments.end())
    {
        return instrumental.instruments.at(keyword) * weight;
    }
    return 0;
}

/**
 * Implementation for the overriden checkKeyWord function with check how much the given keyword is
 * relevant to this Lyrical Composition.
 */
unsigned int LyricsRanker::checkKeyWord(const BaseComposition& composition, string keyword)
{
    LyricalComposition lyrical = dynamic_cast<LyricalComposition&>(const_cast<BaseComposition&>(composition));
    if (lyrical.lyrics.find(keyword) != lyrical.lyrics.end())
    {
        return lyrical.lyrics.at(keyword) * weight;
    }
    return 0;
}

/**
 * Implementation for the overriden checkKeyWord function with check how much the given keyword is
 * relevant to this Composition.
 */
unsigned int TagRanker::checkKeyWord(const BaseComposition& composition, string keyword)
{
    if (composition.tags.find(keyword) != composition.tags.end())
    {
        return composition.tags.at(keyword) * weight;
    }
    return 0;
}

/**
 * Implementation for the overriden checkKeyWord function with check how much the given keyword is
 * relevant to this Composition.
 */
unsigned int TempoRanker::checkKeyWord(const BaseComposition& composition, string keyword)
{
    InstrumentalComposition instrumental = dynamic_cast<InstrumentalComposition&>(const_cast<BaseComposition&>(composition));
    if (instrumental.hasTempo && tempoTagMap.find(keyword) != tempoTagMap.end())
    {
        return static_cast<unsigned int>(floor(exp(-(pow(instrumental.tempo - tempoTagMap.at(keyword).first, 2) / (2 * pow(tempoTagMap.at(keyword).second, 2)))) * weight));
    }
    return 0;
}