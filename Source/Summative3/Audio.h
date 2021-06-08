// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2020 Media Design School 
// 
//  File Name   : Audio.h
//  Description : Audio class to create a audioSystem to play sounds
//  Author      : Bailey Johnson
//  Mail        : bailey.johnson@mds.ac.nz
// 
// Library Includes 

#include <string>
#include <fmod.hpp>

// Implementation

class Audio {
public:
    Audio(std::string fileName); //Constructor - Takes in the file name of the desired audio file
    ~Audio(); //Deconstructor

    //Returns if Audio is initialised
    bool AudioInit();

    FMOD::System* audioSystem;
    FMOD::Sound* FX_Thump;
    FMOD::Sound* music;
};