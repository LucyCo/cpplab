/**
 *  CompositionTypes.cpp
 *  cppex2
 *
 *  Implementation file for both composition types. Contains both Base Composition derived classes.
 *
 *  Created by Lauren Cohen on 10/01/2016.
 *  Copyright © 2016 Lauren Cohen. All rights reserved.
 */

#include "CompositionTypes.h"

/**
 * Constructor: creates an instance of Instrumental Composition with the given title,
 * performer, instruments and tags references. No tempo.
 */
InstrumentalComposition::InstrumentalComposition(const string& title, const string& performer, const CompMap& instruments, const CompMap& tags) : BaseComposition(title, tags)
{
    this->performer = performer;
    this->instruments = instruments;
    this->hasTempo = false;
    this->tempo = 0;
}

/**
 * Constructor: creates an instance of Instrumental Composition with the given title,
 * performer, instruments, tags references and tempo.
 */
InstrumentalComposition::InstrumentalComposition(const string& title, const string& performer, const CompMap& instruments, const CompMap& tags, const unsigned int tempo) : BaseComposition(title, tags)
{
    this->performer = performer;
    this->instruments = instruments;
    this->hasTempo = true;
    this->tempo = tempo;
}

/**
 * ovveride from base class. returns the data of the composition.
 */
string InstrumentalComposition::data()
{
    return (PERFORMED_BY + performer);
}

/**
 * Constructor: creates an instance of Instrumental Composition with the given title,
 * writer, lyrics and tags references.
 */
LyricalComposition::LyricalComposition(const string& title, const string& writer, const CompMap& lyrics, const CompMap& tags) : BaseComposition(title, tags)
{
    this->writer = writer;
    this->lyrics = lyrics;
}

/**
 * ovveride from base class. returns the data of the composition.
 */
string LyricalComposition::data()
{
    return (LYRICS_BY + writer);
}