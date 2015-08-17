#ifndef OPGL_CAMERA_H
#define OPGL_CAMERA_H 1

// C/C++ Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// OpenGL
#include "opengl.h"

// Program Includes

// Defines
#define CAM_X 0
#define CAM_Y 1
#define CAM_Z 2
#define CAM_PITCH 0
#define CAM_YAW 1
#define CAM_ROLL 2

class Camera {
	glm::vec3 m_position;
	glm::vec3 m_angle;

	glm::vec3 m_forward;
	glm::vec3 m_right;
	glm::vec3 m_up;

	GLfloat m_fovy;
	GLfloat m_aspectRatio;
	GLfloat m_nearPlane;
	GLfloat m_farPlane;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;

	GLdouble m_lastControllerUpdate;
	GLfloat m_speed;
	GLfloat m_angularSpeed;

public:
	Camera(GLfloat fovy, GLfloat aspectRatio, GLfloat nearPlane, GLfloat farPlane);
	
	void setX(GLfloat x);
	void setY(GLfloat y);
	void setZ(GLfloat z);
	GLfloat getX();
	GLfloat getY();
	GLfloat getZ();

	void setPitch(GLfloat pitch);
	void setYaw(GLfloat yaw);
	void setRoll(GLfloat roll);
	GLfloat getPitch();
	GLfloat getYaw();
	GLfloat getRoll();

	void setSpeed(GLfloat speed);
	void setAngularSpeed(GLfloat angularSpeed);
	GLfloat getSpeed();
	GLfloat getAngularSpeed();

	void setPos(glm::vec3 pos);
	void setPos(GLfloat x, GLfloat y, GLfloat z);
	glm::vec3 getPos();

	void setAngle(glm::vec3 angle);
	void setAngle(GLfloat pitch, GLfloat yaw, GLfloat roll);
	glm::vec3 getAngle();

	glm::mat4 getProjectionViewMatrix();
	void updateFromController(GLFWwindow& m_window);
	void updateDirections();
};

#endif