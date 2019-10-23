#include <Jump.hpp>
#include <Run.hpp>
#include <Fall.hpp>
#include <Return.hpp>
#include <GLWidget.hpp>
#include <Throw.hpp>

Jump::Jump(Boxman * robot):bot(robot)
{
	robot->getRobotState().isJumping() = true;
}


void Jump::act()
{
	// variables pour simplifier l'écriture
	kn::Vector3f & directionRobot = bot->getRobotState().getDirection();
	kn::Vector3f & accelerationRobot = bot->getRobotState().getAcceleration();
	kn::Vector3f & speedRobot = bot->getRobotState().getVelocity();

	if(bot->getRobotState().isOnTheFloor() && speedRobot[1]<=0.0001)
	{

		//std::cout << "start jump" << std::endl;

		directionRobot[1] = 1.0;
		directionRobot[0] = 0.0;
		speedRobot[1] = 4.0;
		accelerationRobot[1] = 0.0;

		bot->animation.getAnimeType() = ONE_SHOT;
		bot->animation.setAnimation(JUMP, 40);
	}
	else if(speedRobot[1] < 0.0){
		//std::cout << "jump > run" << std::endl;

		bot->setMovement(new Fall(bot));
	}
	else
	{
		//std::cout << "continue jump, speedY: " << speedRobot[1] << std::endl;
		directionRobot[1] = 0;
		directionRobot[0] = 0;



		/*
		* Interprêtation des ordres
		*/
		std::string order = bot->getSpeaker().getLastOrder().first;
		int param = bot->getSpeaker().getLastOrder().second;
		float & r = bot->getRobotState().getRotation()[1];
		if (order == "Run")
		{
			double angle;
			if (param>0)
			  angle = 1.f;
			else
			  angle = -1.f;

			// changing position : 1 = right, -1 = left
			//directionRobot[0] = angle/2.0;// *  directionRobot[0];
			//accelerationRobot[0] = 0.0;

			if(speedRobot[0]*angle < 0)
			{
				// rotation et inversion du sens
				speedRobot[0]*= -1;
				// rotation de 180°
				if( r > -90. && r <= 90. ) // à droite
					r = 180.f;
				else // gauche
					r = 0.f;
			}

			// dans tous les cas, on peut diriger le perso en vol :)
			if( r > -90. && r <= 90. ) // à droite
				speedRobot[0] += 0.3;
			else // gauche
				speedRobot[0] -= 0.3;
		}
		else
		{
			// si on n'insiste pas sur la direction pendant le saut, on perd de la vitesse
			if( r > -90. && r <= 90. && speedRobot[0] > 0) // à droite
				speedRobot[0] -= 0.1;
			else if( !(r > -90. && r <= 90.) && speedRobot[0] < 0) // gauche
				speedRobot[0] += 0.1;
		}


		if (order == "Throw")
		{
			bot->getRobotState().isJumping() = false;
			bot->setMovement(new Throw(bot));
		}
	}
}
