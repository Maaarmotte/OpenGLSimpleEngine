#include "camera.h"

Camera::Camera(GLfloat fovy, GLfloat aspectRatio, GLfloat nearPlane, GLfloat farPlane) {
	m_fovy = fovy;
	m_aspectRatio = aspectRatio;
	m_nearPlane = nearPlane;
	m_farPlane = farPlane;

	m_position = glm::vec3(0.0f, 0.0f, 0.0f);
	m_angle = glm::vec3(0.0f, 0.0f, 0.0f);

	m_speed = 0.0f;
	m_angularSpeed = 0.0f;

	m_lastControllerUpdate = 0.0;

	m_projectionMatrix = glm::perspective(fovy, aspectRatio, nearPlane, farPlane);
}

void Camera::setX(GLfloat x) { m_position[CAM_X] = x; }
void Camera::setY(GLfloat y) { m_position[CAM_Y] = y; }
void Camera::setZ(GLfloat z) { m_position[CAM_Z] = z; }
GLfloat Camera::getX() { return m_position[CAM_X]; }
GLfloat Camera::getY() { return m_position[CAM_Y]; }
GLfloat Camera::getZ() { return m_position[CAM_Z]; }

void Camera::setPitch(GLfloat pitch) { m_angle[CAM_PITCH] = pitch; }
void Camera::setYaw(GLfloat yaw) { m_angle[CAM_YAW] = yaw; }
void Camera::setRoll(GLfloat roll) { m_angle[CAM_ROLL] = roll; }
GLfloat Camera::getPitch() { return m_angle[CAM_PITCH]; }
GLfloat Camera::getYaw() { return m_angle[CAM_YAW]; }
GLfloat Camera::getRoll() { return m_angle[CAM_ROLL]; }

void Camera::setSpeed(GLfloat speed) { m_speed = speed; }
void Camera::setAngularSpeed(GLfloat angularSpeed) { m_angularSpeed = angularSpeed; }
GLfloat Camera::getSpeed() { return m_speed; }
GLfloat Camera::getAngularSpeed() { return m_angularSpeed; }

void Camera::setPos(glm::vec3 pos) {
	m_position = pos;
}
void Camera::setPos(GLfloat x, GLfloat y, GLfloat z) {
	m_position[CAM_X] = x;
	m_position[CAM_Y] = y;
	m_position[CAM_Z] = z;
}
glm::vec3 Camera::getPos() {
	return m_position;
}

void Camera::setAngle(glm::vec3 angle) {
	m_angle = angle;
}
void Camera::setAngle(GLfloat pitch, GLfloat yaw, GLfloat roll) {
	m_angle[CAM_PITCH] = pitch;
	m_angle[CAM_YAW] = yaw;
	m_angle[CAM_ROLL] = roll;
}
glm::vec3 Camera::getAngle() {
	return m_angle;
}

glm::mat4 Camera::getProjectionViewMatrix() {
	updateDirections();

	m_viewMatrix = glm::lookAt(m_position, m_position + m_forward, m_up);

	return m_projectionMatrix*m_viewMatrix;
}

void Camera::updateFromController(GLFWwindow& window) {
	updateDirections();

	GLfloat kForward = (GLfloat)glfwGetKey(&window, GLFW_KEY_W);
	GLfloat kBackward = (GLfloat)glfwGetKey(&window, GLFW_KEY_S);
	GLfloat kRight = (GLfloat)glfwGetKey(&window, GLFW_KEY_D);
	GLfloat kLeft = (GLfloat)glfwGetKey(&window, GLFW_KEY_A);
	GLfloat kUpward = (GLfloat)glfwGetKey(&window, GLFW_KEY_SPACE);
	GLfloat kDownward = (GLfloat)(glfwGetKey(&window, GLFW_KEY_LEFT_CONTROL) | glfwGetKey(&window, GLFW_KEY_RIGHT_CONTROL));

	GLdouble mouseX;
	GLdouble mouseY;

	GLint windowX;
	GLint windowY;

	glfwGetCursorPos(&window, &mouseX, &mouseY);
	glfwGetWindowSize(&window, &windowX, &windowY);

	setAngle(getAngle() + glm::vec3((-mouseY + windowY / 2)*0.001f, (-mouseX + windowX / 2)*0.001f, 0.0f));
	setPos(getPos() + m_forward*0.004f*(kForward - kBackward) + m_right*0.004f*(kRight - kLeft) + m_up*0.004f*(kUpward - kDownward));

	glfwSetCursorPos(&window, windowX / 2, windowY / 2);
}

void Camera::updateDirections() {
	m_forward = glm::normalize(glm::vec3(sin(m_angle[CAM_YAW])*cos(m_angle[CAM_PITCH]), sin(m_angle[CAM_PITCH]), cos(m_angle[CAM_YAW])*cos(m_angle[CAM_PITCH])));
	m_right = glm::normalize(glm::cross(m_forward, glm::vec3(0.0f, 1.0f, 0.0f)));
	m_up = glm::normalize(glm::cross(m_right, m_forward));
}