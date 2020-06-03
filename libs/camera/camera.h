#pragma once
#include <glad.h>
#include <glm/glm.hpp>


class Camera{

    private:
        glm::mat4 view, projection;
        glm::vec3 cameraPos, cameraFront, cameraUp;
        float yaw, pitch, fov, aspectRatio;
        void updateViewMatrix();
        void updateProjectionMatrix(float fov, float aspectRatio);
    public:
        Camera(unsigned int, unsigned int);
        ~Camera();
        void processKeyboardInput(char direction, float deltaTime);
        void processMouseInput(double xoffset, double yoffset);
        void processMouseScroll(double yoffset);
        const glm::mat4& getProjectionMatrix() const;
        const glm::mat4& getViewMatrix() const;
        const glm::vec3& getCameraPos() const;
};







