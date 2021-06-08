#pragma once
// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2020 Media Design School 
// 
//  File Name   : Text.h
//  Description : Text class to get text and translate it to a displayable text from the string and font given
//  Author      : Bailey Johnson
//  Mail        : bailey.johnson@mds.ac.nz
// 
// Library Includes 

#include <string>
#include <iostream>
#include <glew.h>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

// Local Includes 

#include "ShaderLoader.h"

// Implementation

class Text
{
public:
	//Constructor
	Text(
		std::string text,
		std::string font,
		glm::vec2 pixelSize,
		glm::vec2 position,
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec2 scale = glm::vec2(1.0f, 1.0f));

	~Text() {}; //Deconstructor

	void Render();
	void SetColor(glm::vec3 color) { this->vColor = color; };
	void SetPosition(glm::vec2 position) { this->vPosition = position; };
	void SetScale(glm::vec2 scale) { this->vScale = scale; };
	void SetText(std::string text) { this->strText = text; };

private:
	struct FontCharacter
	{
		GLuint textureID = 0; //Texture ID
		glm::ivec2 Size; //Size of the glyph
		glm::ivec2 Bearing; //Offset of the glyph (top left) from the baseline
		GLuint Advance = 0; //How far to move for the next character
	};

	Text() {};
	GLuint GenerateTexture(FT_Face* face);

	static const int fontCharacterLimit = 128;
	bool initializedCorrectly = false;

	std::string strText;
	glm::vec2 vPosition;
	glm::vec2 vScale;
	glm::vec3 vColor;

	glm::mat4 matProjection;
	GLuint VAO = 0;
	GLuint VBO = 0;
	GLuint programText = 0;
	FontCharacter fontCharacters[fontCharacterLimit];
};