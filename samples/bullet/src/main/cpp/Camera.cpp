//
// Created by NickNovikov on 03.06.2018.
//

#include "Camera.h"


void Graphic::Camera::lookAt(const double &xpos, const double &ypos) {

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    GLfloat xoffset = xpos - lastX;
    GLfloat yoffset = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    GLfloat sensitivity = 0.05;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
}

void Graphic::Camera::scroll(const double &xoffset, const double &yoffset) {
    if (fieldOfView >= 1.0f && fieldOfView <= 45.0f)
        fieldOfView -= yoffset;
    if (fieldOfView <= 1.0f)
        fieldOfView = 1.0f;
    if (fieldOfView >= 45.0f)
        fieldOfView = 45.0f;
}

void Graphic::Camera::render(const GLuint &shaderProgram) {

    glm::mat4 view, projection;
    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    projection = glm::perspective(fieldOfView, (GLfloat) width / (GLfloat) height, 0.1f, (GLfloat) range);

    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "view"), 1, GL_FALSE, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

}

void Graphic::Camera::moveTo(Graphic::Direction direction, const float &delta) {
    GLfloat speed = cameraSpeed * delta;

    if (direction == FORWARD) cameraPos += speed * cameraFront;
    if (direction == BACK) cameraPos -= speed * cameraFront;
    if (direction == RIGHT) cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
    if (direction == LEFT) cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
}
