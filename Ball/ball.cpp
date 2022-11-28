# include "ball.h"
# include <math.h>

//frictionCoefficientOnDirt = 0.5;
//gravitationalAcceleration = 9.81;

glm::vec3 xRotate(1.0f, 0.0f, 0.0f);

Ball::Ball()
{
	this->ballPosition = glm::vec3(0.0f, 0.0f, 0.0f);
}

Ball::Ball(glm::vec3 ballPosition, int throwTrue, int calibrateTrue, 
	int spawnTrue, float throwDist, float throwSpeed, int disqualified, int collisionTrue, Sphere sphere)
{
	this->ballPosition = ballPosition;
	this->throwTrue = throwTrue;
	this->calibrateTrue = calibrateTrue;
	this->spawnTrue = spawnTrue;
	this->throwDist = throwDist;
	this->throwSpeed = throwSpeed;
	this->disqualified = disqualified;
	this->collisionTrue = collisionTrue;
	this->sphere = sphere;

}

Ball::~Ball()
{
}

void Ball::drawBall(glm::mat4 MVP, glm::mat4 projection, glm::mat4 view, glm::mat4 model, GLuint programID)
{
	model = glm::translate(model, this->getBallPosition());

	//model = glm::scale(model, glm::vec3(0.2f));
	
	unsigned int transformLoc0 = glGetUniformLocation(programID, "model");
	glUniformMatrix4fv(transformLoc0, 1, GL_FALSE, glm::value_ptr(model));

	unsigned int transformLoc1 = glGetUniformLocation(programID, "transform");
	glUniformMatrix4fv(transformLoc1, 1, GL_FALSE, glm::value_ptr(MVP));

	//glDrawArrays(GL_QUADS, 0, 24);

	glDrawElements(GL_TRIANGLES,                    // primitive type
		this->sphere.getIndexCount(),          // # of indices
		GL_UNSIGNED_INT,                 // data type
		(void*)0);
}


glm::mat4 Ball::ballRotate(glm::mat4 model)
{
	if (this->getBallPositionZ() > -this->throwDist)
	{
		//model = glm::scale(model, glm::vec3(0.2f));

		model = glm::rotate(model,(float)glfwGetTime() * -throwSpeed, glm::vec3(1.0f, 0.0f, 0.0f));
		
		this->throwSpeed = sqrt(pow(this->throwSpeed, 2) + pow(this->throwSpeed, 2));
	}
	return model;
}

glm::mat4 Ball::ballAdvance(glm::mat4 model)
{
	if (this->getBallPositionZ() > -(this->throwDist))
		model = glm::translate(model, this->getBallPosition());
	else model = glm::translate(model, 
		glm::vec3(this->getBallPositionX(), this->getBallPositionY(), -this->throwDist));
	
	//model = glm::scale(model, glm::vec3(0.2f));

	return model;
}

glm::mat4 Ball::ballThrow(glm::mat4 model)
{
	//model = glm::scale(model, glm::vec3(0.2f));
	model = this->ballAdvance(model);
	model = this->ballRotate(model);
	return model;
}

glm::mat4 Ball::ballCalibrate(glm::mat4 model)
{
	//model = glm::scale(model, glm::vec3(0.2f));
	model = glm::translate(model, this->getBallPosition());
	return model;
}

void Ball::ballBlock()
{
	if (this->getBallPositionZ() < -1600.0f)
	{
		this->setBallSpawnTrue(0);
		this->setBallCalibrateTrue(0);
		this->setBallThrowTrue(0);
		this->setBallThrowSpeed(0);
		this->setBallThrowDist(0);
		this->setBallDisqualified(1);

		this->setBallPosition(glm::vec3(0.0f, 0.0f, 0.0f));
	}
}

void Ball::ballReset()
{
	this->setBallSpawnTrue(0);
	this->setBallCalibrateTrue(0);
	this->setBallThrowTrue(0);
	this->setBallThrowSpeed(0);
	this->setBallThrowDist(0);
	this->setBallDisqualified(0);
	this->setBallCollisionTrue(0);

	this->setBallPosition(glm::vec3(0.0f, 0.0f, 0.0f));
}



glm::vec3 Ball::getBallPosition()
{
	return this->ballPosition;
}

float Ball::getBallPositionX()
{
	return this->ballPosition.x;
}

float Ball::getBallPositionY()
{
	return this->ballPosition.y;
}

float Ball::getBallPositionZ()
{
	return this->ballPosition.z;
}

int Ball::getBallThrowTrue()
{
	return this->throwTrue;
}

int Ball::getBallCalibrateTrue()
{
	return this->calibrateTrue;
}

int Ball::getBallSpawnTrue()
{
	return this->spawnTrue;
}

float Ball::getBallThrowDist()
{
	return this->throwDist;
}

float Ball::getBallThrowSpeed()
{
	return this->throwSpeed;
}

int Ball::getBallDisqualified()
{
	return this->disqualified;
}

int Ball::getBallCollisionTrue()
{
	return this->collisionTrue;
}



void Ball::setBallPosition(glm::vec3 ballPosition)
{
	this->ballPosition = ballPosition;
}

void Ball::setBallPositionX(float x)
{
	this->ballPosition.x = x;
}

void Ball::setBallPositionY(float y)
{
	this->ballPosition.y = y;
}

void Ball::setBallPositionZ(float z)
{
	this->ballPosition.z = z;
}

void Ball::setBallThrowTrue(int throwTrue)
{
	this->throwTrue = throwTrue;
}

void Ball::setBallCalibrateTrue(int calibrateTrue)
{
	this->calibrateTrue = calibrateTrue;
}

void Ball::setBallSpawnTrue(int spawnTrue)
{
	this->spawnTrue = spawnTrue;
}

void Ball::setBallThrowDist(float throwDist)
{
	this->throwDist = throwDist;
}

void Ball::setBallThrowSpeed(float throwSpeed)
{
	this->throwSpeed = throwSpeed;
}

void Ball::setBallDisqualified(int disqualified)
{
	this->disqualified = disqualified;
}

void Ball::setBallCollisionTrue(int collisionTrue)
{
	this->collisionTrue = collisionTrue;
}
