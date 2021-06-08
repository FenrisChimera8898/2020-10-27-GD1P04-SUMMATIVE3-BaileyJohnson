// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2020 Media Design School 
// 
//  File Name   : Audio.cpp
//  Description : Audio class to create a audioSystem to play sounds
//  Author      : Bailey Johnson
//  Mail        : bailey.johnson@mds.ac.nz
// 
// This Includes 

#include "Audio.h"

// Implementation

//Constructor - Takes in the file name of the desired audio file
Audio::Audio(std::string fileName) 
{
    std::string strFullFilePath = "Resources/Audio/" + fileName;

    //Returns if Audio is initialised
    AudioInit();
    FMOD_RESULT Result;

    Result = audioSystem->createSound(strFullFilePath.c_str(), FMOD_DEFAULT, 0, &FX_Thump);
}

//Deconstructor
Audio::~Audio() 
{

}

//Returns if Audio is initialised
bool Audio::AudioInit() 
{
    //FMOD_RESULT Result;

    //Checks if sound was created
    if (FMOD::System_Create(&audioSystem) != FMOD_OK) {
        return false;
    }

    if (audioSystem->init(100, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0)) {
        return false;
    }

    return true;
}