#include "camera.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>


Camera::Camera(unsigned int scr_width, unsigned int scr_height){
    aspectRatio = (float) scr_width / (float) scr_height;
    fov = 45.0f;
    yaw = -90.0f;
    pitch = 0.0f;
	projection = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);
    cameraPos = glm::vec3(0.0f, 0.0f,  3.0f);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    cameraUp = glm::vec3(0.0f, 1.0f,  0.0f);
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

Camera::~Camera(){}

const glm::mat4& Camera::getProjectionMatrix() const{
    return projection;
}

const glm::mat4& Camera::getViewMatrix() const{
    return view;
}

const glm::vec3& Camera::getCameraPos() const{
    return cameraPos;
}


void Camera::updateProjectionMatrix(float fov, float aspectRatio){
    this->fov = fov;
    projection = glm::perspective(glm::radians(fov), aspectRatio, 0.1f, 100.0f);
}

void Camera::updateViewMatrix(){
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
}

void Camera::processKeyboardInput(char direction, float cameraSpeed)
{
    switch (direction){
        case 'F':
            cameraPos += cameraSpeed * cameraFront;
            break;
        case 'B':
            cameraPos -= cameraSpeed * cameraFront;
            break;
        case 'L':
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            break;
        case 'R':
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
            break;
    }
    updateViewMatrix();
}

void Camera::processMouseInput(double xoffset, double yoffset)
{

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);

    updateViewMatrix();
}

void Camera::processMouseScroll(double yoffset){
    fov -= (float) yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
    updateProjectionMatrix(fov, aspectRatio);
}