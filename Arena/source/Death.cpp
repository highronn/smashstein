#include <Death.hpp>
#include <StandUp.hpp>

Death::Death(Boxman * robot):bot(robot)
{
	frame = 0;
	//startTime = TIMER.elapsed();
	state = DEATH_START;
}

void Death::act()
{
	// variables pour simplifier l'écriture
	kn::Vector3f & directionRobot = bot->getRobotState().getDirection();
	kn::Vector3f & accelerationRobot = bot->getRobotState().getAcceleration();
	kn::Vector3f & speedRobot = bot->getRobotState().getVelocity();
	float & r = bot->getRobotState().getRotation()[1];

	if(frame == 0)
	{
		// Le robot prend l'état "dead"
		bot->getRobotState().isDead() = true;

		directionRobot[1] = 0.0;
		directionRobot[0] = 0.0;
		float speed = 2.0*pow(bot->getRobotState().getDamages()/100.0, 2.0)+1.0;

		// Anim: PreDeath
		bot->animation.getAnimeType() = ONE_SHOT;
		bot->animation.setAnimation(PREDEATH, 40);

		// faut l'envoyer en l'air du bon côté :)
		if( r > -90. && r <= 90. ) // tournée à droite
			speedRobot[0] = -speed; // il vole à gauche!
		else // tourné à gauche
			speedRobot[0] = speed; // il vole à droite...

		speedRobot[1] = 1.5*speed;
		accelerationRobot[1] = 0.0;
	}
	else if(state == DEATH_START && bot->animation.isTerminate() && !bot->getRobotState().isOnTheFloor())
	{

		//std::cout << "start jump" << std::endl;

		// Anim: Death/loop (vol plané)
		bot->animation.getAnimeType() = LOOP;
		bot->animation.setAnimation(DEATH, 40);
		state = DEATH_FLY;
	}
	else if(state == DEATH_FLY && bot->getRobotState().isOnTheFloor())
	{
		// Anim: Rebond au sol
		bot->animation.getAnimeType() = ONE_SHOT;
		bot->animation.setAnimation(POSTDEATH, 40);
		startTime = TIMER.elapsed();
		state = DEATH_FLOOR;
	}
	else if(DEATH_FLOOR && bot->getRobotState().isOnTheFloor() && bot->animation.isTerminate())
	{

		// Au bout de quelques secondes inconscient au sol, le perso se relève
		if( TIMER.elapsed() - startTime > 0001)
		{
			bot->setMovement(new StandUp(bot));
			startTime = TIMER.elapsed();
		}
	}
	++frame;
}


