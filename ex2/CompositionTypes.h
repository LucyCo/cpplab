/**
 *  CompositionTypes.h
 *  cppex2
 *
 *  Header file for both composition types. Contains both Base Composition derived classes.
 *
 *  Created by Lauren Cohen on 10/01/2016.
 *  Copyright © 2016 Lauren Cohen. All rights reserved.
 */

#ifndef _COMPOSITION_TYPES_H
#define _COMPOSITION_TYPES_H
#include "BaseComposition.h"

/** 
 * Instrumental composition type.
 * contains two constructors, one with tempo and one without.
 */
class InstrumentalComposition : public BaseComposition
{
public:
    string performer;
    CompMap instruments;
    bool hasTempo;
    unsigned int tempo;

    /**
     * Constructor: creates an instance of Instrumental Composition with the given title, 
     * performer, instruments and tags references. No tempo.
     */
    InstrumentalComposition(const string& title, const string& performer, const CompMap& instruments, const CompMap& tags);
    
    /**
     * Constructor: creates an instance of Instrumental Composition with the given title,
     * performer, instruments, tags references and tempo.
     */
    InstrumentalComposition(const string& title, const string& performer, const CompMap& instruments, const CompMap& tags, const unsigned int tempo);
    
	/**
	 * ovveride from base class. returns the data of the composition.
	 */
    virtual string data() override;
};

/**
 * Lyrical composition type class.
 */
class LyricalComposition : public BaseComposition
{
public:
    string writer;
    CompMap lyrics;
    
    /**
     * Constructor: creates an instance of Instrumental Composition with the given title,
     * writer, lyrics and tags references.
     */
    LyricalComposition(const string& title, const string& writer, const CompMap& lyrics, const CompMap& tags);
    
    /**
     * ovveride from base class. returns the data of the composition.
     */
    virtual string data() override;
};

#endif