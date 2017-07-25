/**
 *  RankerFactory.cpp
 *  cppex2
 *
 *  Implementation for the ranker factory class and functions.
 *
 *  Created by Lauren Cohen on 10/01/2016.
 *  Copyright © 2016 Lauren Cohen. All rights reserved.
 */

#include <sstream>
#include "RankerFactory.h"
#include "RankerTypes.h"
#include "SavedWords.h"

/**
 * Constructor: creates an instance of Ranker Factory which creates a ranker with the given stream.
 */
RankerFactory::RankerFactory(ifstream& stream)
{
    if (stream.is_open())
    {
        while (!stream.eof())
        {
            SharedPtrVect newRanker = RankerFactory::newComp(stream);
            if (newRanker != nullptr)
            {
                rankers.push_back(newRanker);
            }
        }
    }
}

/**
 * Destructor - removes all instances of rankers from the memory.
 */
RankerFactory::~RankerFactory()
{
    for (unsigned i = 0; i < rankers.size(); i++)
    {
        rankers[i].reset();
    }
}

/**
 * Parses tag to tempo with the given tag map reference.
 */
void RankerFactory::_parseTagToTempo(TempoMap& tempoTagMap, const string& str)
{
    if (tempoTagMap.find(str.substr(0, str.find(COLON))) == tempoTagMap.end())
    {
        tempoTagMap.insert(make_pair(str.substr(0, str.find(COLON)), make_pair(stof(str.substr(str.find(COLON) + 1, str.find(COMMA))), stof(str.substr(str.find(COMMA) + 1)))));
    }
}

/**
 * creates a shared pointer for the new ranker which is created based on the given stream.
 */
shared_ptr<BaseWeightRanker> RankerFactory::newComp(ifstream& stream)
{
	string line;
    unsigned long index;
    unsigned int weight;
	getline(stream, line);
    //line is tag match score
	if (!line.substr(0, TAG_MATCH_SCORE.length()).compare(TAG_MATCH_SCORE))
	{
		index = (TAG_MATCH_SCORE.length() + WHITE_SPACE);
		weight = stoi(line.substr(index));
		return static_pointer_cast<BaseWeightRanker>(make_shared<TagRanker>(RankableComp::DEFAULT, weight));
	}
    //line is instrument match score
    if (!line.substr(0, INST_MATCH_SCORE.length()).compare(INST_MATCH_SCORE))
    {
        index = (INST_MATCH_SCORE.length() + WHITE_SPACE);
        weight = stoi(line.substr(index));
        return static_pointer_cast<BaseWeightRanker>
        (make_shared<InstrumentRanker>(RankableComp::INSTRUMENTAL_COMPOSITION, weight));
    }
    //line is lyrics match score
	if (!line.substr(0, LYRICS_MATCH_SCORE.length()).compare(LYRICS_MATCH_SCORE))
	{
		index = (LYRICS_MATCH_SCORE.length() + WHITE_SPACE);
		weight = stoi(line.substr(index));
		return static_pointer_cast<BaseWeightRanker>(make_shared<LyricsRanker>(RankableComp::LYRICAL_COMPOSITION, weight));
	}
    //line is bmp likelihood weight
	else
	{
		index = (BPM_LIKELIHOOD_WEIGHT.length() + WHITE_SPACE);
        weight = stoi(line.substr(index));
		TempoMap tempoMap;
		while(!stream.eof())
		{
            getline(stream, line);
			if (line.length() == 0)
			{
				continue;
			}
            //call again with the next line
			_parseTagToTempo(tempoMap, line);
		}

		return static_pointer_cast<BaseWeightRanker>(make_shared<TempoRanker>(RankableComp::INSTRUMENTAL_COMPOSITION, weight, tempoMap));
	}
}