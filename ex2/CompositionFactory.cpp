/**
 *  CompositionFactory.cpp
 *  cppex2
 *
 *  Implementation file for creating a composition according to the given params.
 *
 *  Created by Lauren Cohen on 10/01/2016.
 *  Copyright © 2016 Lauren Cohen. All rights reserved.
 */

#include <assert.h>
#include <iterator>
#include <sstream>
#include <iostream>
#include <memory>
#include "CompositionFactory.h"
#include "SavedWords.h"

using namespace std;

/**
 * Implementation of create map of compositions function. if hasweight is true calculates the power of tag.
 */
CompMap CompositionFactory::_createCompMap(const string& str, bool hasWeight)
{
    istream_iterator<string> isIt(*new istringstream(str.substr(str.find('{') + 1, (str.find('}') - (str.find('{') + 1)))));
    istream_iterator<string> end;
    CompMap compMap;
    while (isIt != end)
    {
        if (hasWeight)
        {
            string theTag = *(isIt++);
            int power = stoi(*isIt++);
            compMap[theTag] = power;
        }
        else
        {
            string word = *(isIt);
            *(isIt)++;
            compMap[word]++;
        }
    }
    return compMap;
}

/**
 * creates a shared pointer for the new composition which is created based on the given stream.
 */
VectBaseComp::value_type CompositionFactory::newComp(ifstream& stream)
{
    string line;
    getline(stream, line);
    if (!line.compare(END))
    { //unknown type, value -1
        stream.setstate(ios_base::eofbit);
        return VectBaseComp::value_type(RankableComp::DEFAULT, nullptr);
    }
    getline(stream, line);
    unsigned long index = TITLE.size() + WHITE_SPACE;
    string title = line.substr(index);
    getline(stream, line);
    CompMap tags = _createCompMap(line, true);
    getline(stream, line);
    if (!line.substr(0, LYRICS.size()).compare(LYRICS))
    {
        //this is a lyrical composition
        CompMap lyrics = _createCompMap(line);
        getline(stream, line);
        index = (LYRICSBY.size() + WHITE_SPACE);
        string writer = line.substr(index);
        if (stream.peek() == *(END.c_str()))
        {
            stream.setstate(ios_base::eofbit);
        }
        auto p = std::make_shared<LyricalComposition>(title, writer, lyrics, tags);
        return VectBaseComp::value_type(RankableComp::LYRICAL_COMPOSITION, static_pointer_cast<BaseComposition>(p));
    }
    else
    {
        // this is an instrumental composition
        CompMap instruments = _createCompMap(line);
        getline(stream, line);
        index = (PERFORMEDBY.size() + WHITE_SPACE);
        string performer = line.substr(index);
        int bpm = 0;
        bool hasBpm = false;
        // check wether bmp was given
        char check;
        check = stream.peek();
        // check bpm without changing the next line in the stream
        if (check == BPM[0])
        {
            getline(stream, line);
            index = BPM.size() + WHITE_SPACE;
            string bpmNumber = (line.substr(index));
            bpm = stoi(bpmNumber);
            hasBpm = true;
            //cout << bmpNumber << endl;
        }
        if (hasBpm)
        { //when bpm is given use the constructor with the bpm
            return VectBaseComp::value_type(RankableComp::INSTRUMENTAL_COMPOSITION, static_pointer_cast<BaseComposition>(make_shared<InstrumentalComposition>(title, performer, instruments, tags, bpm)));
        }
        else
        {
            return VectBaseComp::value_type(RankableComp::INSTRUMENTAL_COMPOSITION, static_pointer_cast<BaseComposition>(make_shared<InstrumentalComposition>(title, performer, instruments, tags)));
        }
    }
}

/**
 * Removes all created compositions from memory.
 */
CompositionFactory::~CompositionFactory()
{
    for (unsigned i = 0; i < compositions.size(); i++)
    {
        compositions[i].second.reset();
    }
}