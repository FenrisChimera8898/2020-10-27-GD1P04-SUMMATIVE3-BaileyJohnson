// 
//  Bachelor of Software Engineering 
//  Media Design School 
//  Auckland 
//  New Zealand 
// 
//  (c) 2020 Media Design School 
// 
//  File Name   : Text.cpp
//  Description : Text class to get text and translate it to a displayable text from the string and font given
//  Author      : Bailey Johnson
//  Mail        : bailey.johnson@mds.ac.nz
// 
// This Includes 

#include "Text.h"

// Implementation

//Constructor
Text::Text(std::string text, std::string font, glm::vec2 pixelSize, glm::vec2 position, glm::vec3 color, glm::vec2 scale)
{
	SetText(text);
	SetPosition(position);
	SetColor(color);
	SetScale(scale);

	matProjection = glm::ortho(0.0f, 800.0f, 0.0f, 800.0f);
	programText = ShaderLoader::CreateProgram("Resources/Shaders/Text.vs", "Resources/Shaders/Text.fs");

	FT_Library Library;
	FT_Face Face;

	if (FT_Init_FreeType(&Library) != FT_Err_Ok)
	{
		std::cout << "ERROR: FREETYPE: Could not initialize Freetype Library" << std::endl;
		return;
	}

	if (FT_New_Face(Library, font.c_str(), 0, &Face) != FT_Err_Ok)
	{
		std::cout << "ERROR: FREETYPE: Failed to load font" << std::endl;
		return;
	}

	FT_Set_Pixel_Sizes(Face, (FT_UInt)pixelSize.x, (FT_UInt)pixelSize.y);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	for (GLubyte CharIndex = 0; CharIndex < fontCharacterLimit; CharIndex++)
	{
		if (FT_Load_Char(Face, CharIndex, FT_LOAD_RENDER) != FT_Err_Ok)
		{
			std::cout << "ERROR: FREETYPE: Failed to load glyph ascii index" << std::endl;
			continue;
		}

		fontCharacters[CharIndex] = {
			GenerateTexture(&Face),
			glm::ivec2(Face->glyph->bitmap.width, Face->glyph->bitmap.rows),
			glm::ivec2(Face->glyph->bitmap_left, Face->glyph->bitmap_top),
			(GLuint)Face->glyph->advance.x >> 6,
		};
	}

	FT_Done_Face(Face);
	FT_Done_FreeType(Library);

	GLuint Indices[] = {
		0, 1, 2,
		0, 2, 3,
	};

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint EBO;

	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 4 * 4, NULL, GL_DYNAMIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	initializedCorrectly = true;
}

void Text::Render()
{
	if (initializedCorrectly == false)
	{
		return;
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glUseProgram(programText);
	glUniform3fv(glGetUniformLocation(programText, "TextColor"), 1, glm::value_ptr(vColor));
	glUniformMatrix4fv(glGetUniformLocation(programText, "ProjectionMat"), 1, GL_FALSE, glm::value_ptr(matProjection));

	glBindVertexArray(VAO);

	glm::vec2 localPosition = vPosition;

	for (std::string::const_iterator CharIter = strText.begin(); CharIter != strText.end(); CharIter++)
	{
		FontCharacter fontChar = fontCharacters[*CharIter];
		GLfloat xPos = localPosition.x + (fontChar.Bearing.x * vScale.x);
		GLfloat yPos = localPosition.y - (fontChar.Size.y - fontChar.Bearing.y) * vScale.y;
		GLfloat width = fontChar.Size.x * vScale.x;
		GLfloat height = fontChar.Size.y * vScale.y;

		GLfloat Vertices[4][4] = {
			{xPos, yPos + height, 0.0f, 0.0f},
			{xPos, yPos, 0.0f, 1.0f},
			{xPos + width, yPos, 1.0f, 1.0f},
			{xPos + width, yPos + height, 1.0f, 0.0f},
		};

		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vertices), Vertices);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, fontChar.textureID);
		glUniform1i(glGetUniformLocation(programText, "TextTexture"), 0);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		localPosition.x += fontChar.Advance * vScale.x;
	}

	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);

	glDisable(GL_BLEND);
}

GLuint Text::GenerateTexture(FT_Face* face) 
{
	GLuint textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, (*face)->glyph->bitmap.width, (*face)->glyph->bitmap.rows, 0, GL_RED, GL_UNSIGNED_BYTE, (*face)->glyph->bitmap.buffer);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return textureID;
}