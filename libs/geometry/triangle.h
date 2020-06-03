#pragma once

class Triangle{
    
    private:
        unsigned int VAO, VBO;
        float data[15];
    public:
        Triangle();
        Triangle(float * points, float * textureCoord);
        unsigned int getVAO() const;
};