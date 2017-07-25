/**
 *  MIR.cpp
 *  cppex2
 *
 *  main function, runs the seach of the given files
 *
 *  Created by Lauren Cohen on 10/01/2016.
 *  Copyright © 2016 Lauren Cohen. All rights reserved.
 */

#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "CompositionFactory.h"
#include "RankerFactory.h"
#include <algorithm>

#define TITLE	"Query word: "
#define TAB    "\t"
#define USAGE_ERR "Usage: MIR < songs file name > < parameters file name >" <<\
" < queries file name >"
#define SEPARATOR	"----------------------------------------" << endl
#define SONG_DB_FILE 1
#define PARAMS_FILE	2
#define QUERIES_FILE 3
#define VALID_ARG_NUM 4

using namespace std;

/**
 * A struct for the results returned by the factories
 */
typedef struct Result
{
    unsigned int score;
    shared_ptr<BaseComposition> ptr;
}Result;

/**
 * Compare scored result.
 *
 * @param	lhs	The left hand side.
 * @param	rhs	The right hand side.
 *
 * @return	true if it succeeds, false if it fails.
 */
bool compareScore(const Result& res1, const Result& res2)
{
    return res1.score > res2.score;
}

/**
 * Perform search for compositions in DB by given keyword.
 * Pass compositions and the query through all available scorers,
 * aggregate their scores and scoring types.
 *
 * @param compositions database
 * @param scorers collection
 * @param keyword (search query)
 *
 * @return list sorted descending by relevance
 */
void output(CompositionFactory& compositions, RankerFactory& rankers, string keyword)
{
    vector<Result> results1;
    for (unsigned i = 0; i < compositions.compositions.size(); i++)
    {
        unsigned int totalScore = 0;
        for (unsigned j = 0; j < rankers.rankers.size(); j++)
        {
            if (rankers.rankers[j]->type == RankableComp::DEFAULT || rankers.rankers[j]->type == compositions.compositions[i].first)
            {
                totalScore += rankers.rankers[j]->checkKeyWord(*compositions.compositions[i].second, keyword);
            }

        }
        if (totalScore > 0)
        {
            Result res;
            res.score = totalScore;
            res.ptr = compositions.compositions[i].second;
            results1.push_back(res);
        }

    }
    
    // Sort the output
    stable_sort(results1.begin(), results1.end(), compareScore);
    for (unsigned i = 0; i < results1.size(); i++)
    {
        cout << results1[i].ptr->title << TAB << results1[i].score << TAB
        << results1[i].ptr->data() << endl;
    }

}

/**
 * Main entry-point for this application.
 *
 * @param	argc	Number of command-line arguments.
 * @param	argv	Array of command-line argument strings.
 *
 * @return	Exit-code for the process - 0 for success, else an error code.
 */
int main(int argc, char** argv)
{
    if (argc != VALID_ARG_NUM)
    {
        cerr << USAGE_ERR << endl;
        return 1;
    }
    
    //retrieve song database
    ifstream databaseStream(argv[SONG_DB_FILE]);
    CompositionFactory compositions;
    if (!databaseStream.is_open())
    {   //unable to open song database file
        return 1;
    }
    else
    {
        compositions = CompositionFactory(databaseStream);
    }
    databaseStream.close();
    
    //retrieve ranker parameters
    ifstream rankerParameters(argv[PARAMS_FILE]);
    RankerFactory rankers;
    if (!rankerParameters.is_open())
    {   //unable to open parameters file
        return 1;
    }
    else
    {
        rankers = RankerFactory(rankerParameters);
    }
    rankerParameters.close();
    
    //retrieve query word
    //string query;
    ifstream queries(argv[QUERIES_FILE]);
    if (!queries.is_open())
    {   //unable to open query words file
        return 1;
    }
     vector<string> list;
        string line;
    while(!queries.eof())
    {
        queries >> line;
        list.push_back(line);
    }
    queries.close();
    //cout << "vector" << *list.begin() << endl;
    for (vector<string>::const_iterator query = list.begin(); query != (list.end()-1); query++)
    {
        cout << SEPARATOR << TITLE << *query << endl << endl;
        output(compositions, rankers, *query);
    }
    return 0;
}
