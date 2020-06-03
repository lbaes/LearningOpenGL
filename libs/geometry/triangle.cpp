#include "triangle.h"
#include "glad.h"
#include <iostream>


Triangle::Triangle(){
    float t_vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f, 0.5f, 0.0f};

	float t_texCoords[] = {
		0.0f, 0.0f, // lower-left corner
		1.0f, 0.0f, // lower-right corner
		0.5f, 1.0f	// top-center corner
	};

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            data[5 * i + j] = t_vertices[3 * i + j];

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 2; j++)
            data[3 + (5 * i + j)] = t_texCoords[2 * i + j];

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 15, data, GL_STATIC_DRAW);

    //Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    //Texture Coords Data
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

Triangle::Triangle(float *points, float *textureCoords)
{

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            data[5 * i + j] = points[3 * i + j];

    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 2; j++)
            data[3 + (5 * i + j)] = textureCoords[2 * i + j];

    glGenBuffers(1, &VBO);
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 15, data, GL_STATIC_DRAW);

    //Positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    //Texture Coords Data
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

}

unsigned int Triangle::getVAO() const {
    return VAO;
}