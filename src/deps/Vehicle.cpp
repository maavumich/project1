#include "Vehicle.hpp"

Vehicle::Vehicle(float xInit, float yInit, float yawInit, float radiusInit,
	const float *colorIn, Program *program) :

	AnimatedEntity(Constants::defaultSpeed,
		Constants::roombaMass,xInit,yInit,yawInit,radiusInit,program),

	body {Rectangle(xInit,yInit,yawInit,radiusInit,Constants::bodyColor,program,
		radiusInit * (float)sin(PI / 4) * 0.3, radiusInit * (float)sin(PI / 4) * 0.3)},

	bar1 {Rectangle(xInit,yInit,yawInit + PI / 4,radiusInit,Constants::barColor,program,
		radiusInit / 2 - 0.01, radiusInit * 0.025)},

	bar2 {Rectangle(xInit,yInit,yawInit - PI / 4,radiusInit,Constants::barColor,program,
		radiusInit / 2 - 0.01, radiusInit * 0.025)},

	playerIdentifier {Circle(xInit,yInit,yawInit,radius * 0.1f,colorIn,program)}
{
	// Initialize the ring surrounding the vehicle
	float theta {0.0f};
	// Initialize bumper ring
	for (int i {0}; i < numRects; ++i)
	{
		ring.emplace_back(x + radius * cos(theta), y + radius * sin(theta), theta, radius,
			Constants::ringColor,program,radius * 0.05, 4 * PI * radius / numRects);
		updateTheta(theta,thetaIncrement);
		ring[i].update();
	}
	// Initialize prop caps
	for (int i {0}; i < 4; ++i)
	{
		propCaps.emplace_back(x + radius * cos(PI * i / 2 + PI / 4 + yaw) * 0.75,
			y + radius * sin(PI * i / 2 + PI / 4 + yaw) * 0.75, yaw, radius * 0.04,
			Constants::propCapColor,program);
		propCaps[i].update();
	}
	// Initialize props
	for (int i {0}; i < 4; ++i)
	{
		for (int ii {0}; ii < 2; ++ii)
		{
			props.emplace_back(x + radius * cos(PI * i / 2 + PI / 4 + yaw) * 0.75,
				y + radius * sin(PI * i / 2 + PI / 4 + yaw) * 0.75, yaw + ii * PI / 2,
				radius,Constants::propColor,program,
				radius * 0.49 * 0.3,radius * 0.03);
			props[i].update();
		}
	}
}

void Vehicle::update()
{
	// Update the body
	body.setPosition(x,y);
	body.setYaw(yaw);
	body.update();
	// Update the player identifier
	playerIdentifier.setPosition(x,y);
	playerIdentifier.update();
	// Update the vehicle bars
	// bar1 update:
	bar1.setPosition(x,y);
	bar1.setYaw(yaw + PI / 4);
	bar1.update();
	// bar2 update:
	bar2.setPosition(x,y);
	bar2.setYaw(yaw - PI / 4);
	bar2.update();
	// Update the vehicle prop caps
	for (int i {0}; i < 4; ++i)
	{
		propCaps[i].setPosition(x + radius * cos(PI * i / 2 + PI / 4 + yaw) * 0.75,
			y + radius * sin(PI * i / 2 + PI / 4 + yaw) * 0.75);
		propCaps[i].update();
	}
	// Update the vehicle props
	for (int i {0}; i < 4; ++i)
	{
		for (int ii {0}; ii < 2; ++ii)
		{
			props[i * 2 + ii].setPosition(x + radius * cos(PI * i / 2 + PI / 4 + yaw) * 0.75,
				y + radius * sin(PI * i / 2 + PI / 4 + yaw) * 0.75);
			if (i % 2)
			{
				props[i * 2 + ii].setYaw(propAngle + yaw + ii * PI / 2);
			}
			else
			{
				props[i * 2 + ii].setYaw(-propAngle + yaw + ii * PI / 2);
			}
			props[i * 2 + ii].update();
			updateTheta(propAngle,Constants::propSpeed);
		}
	}
	// Update the vehicle ring
	float theta {0.0f};
	for (int i {0}; i < numRects; ++i)
	{
		ring[i].setPosition(x + radius * cos(theta), y + radius * sin(theta));
		updateTheta(theta,thetaIncrement);
		ring[i].update();
	}
}

void Vehicle::render()
{
	// render bars
	bar1.render();
	bar2.render();
	// render ring
	for (int i {0}; i < numRects; ++i)
		ring[i].render();
	// render body
	body.render();
	// render player identifier
	playerIdentifier.render();
	// render props
	for (int i {0}; i < 8; ++i)
		props[i].render();
	// render prop caps
	for (int i {0}; i < 4; ++i)
		propCaps[i].render();
}
