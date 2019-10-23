#include <Run.hpp>
#include <Fall.hpp>
#include <Land.hpp>
#include <StandBy.hpp>

Fall::Fall(Boxman * robot):bot(robot), frame(0)
{
}

void Fall::act()
{
	if(bot->getRobotState().isOnTheFloor())
	{
		if(frame > 5) // grande chute
			bot->setMovement(new Land(bot));
		else
			bot->setMovement(new StandBy(bot));
		// fini de sauter :)
		bot->getRobotState().isJumping() = false;
	}
	else{
		// variables pour simplifier l'écriture
		//kn::Vector3f & directionRobot = bot->getRobotState().getDirection();
		//kn::Vector3f & accelerationRobot = bot->getRobotState().getAcceleration();
		kn::Vector3f & speedRobot = bot->getRobotState().getVelocity();

		bot->animation.getAnimeType() = LOOP;
		bot->animation.setAnimation(FALL, 40);

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
				speedRobot[0] += 0.5;
			else // gauche
				speedRobot[0] -= 0.5;
		}
		else
		{
			// si on n'insiste pas sur la direction pendant la chute, on perd de la vitesse
			if( r > -90. && r <= 90. && speedRobot[0] > 0) // à droite
				speedRobot[0] -= 0.09;
			else if( !(r > -90. && r <= 90.) && speedRobot[0] < 0) // gauche
				speedRobot[0] += 0.09;
		}
	}
	++frame;
}



