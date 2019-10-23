#include <StandBy.hpp>
#include <Land.hpp>

Land::Land(Boxman * robot):bot(robot)
{
}

void Land::act()
{
	// premier cas, début = lancement de l'anim
	if(bot->animation.getAnimeType() == LOOP)
	{
		bot->animation.getAnimeType() = ONE_SHOT;
		bot->animation.setAnimation(POSTJUMP, 70);


		//std::cout << "START landing" << std::endl;
		bot->getRobotState().getDirection()[0] = 0.0;
		bot->getRobotState().getAcceleration()[0] = 0.0;
		bot->getRobotState().getVelocity()[0] = 0.0;
	}
	// cas 2 : l'anim est en cours
	else if(!bot->animation.isTerminate())
	{
		//std::cout << "landing..." << std::endl;
	}
	// cas 3 : l'anim est terminée
	else
	{
		//std::cout << "landing TERMINATED" << std::endl;
		bot->setMovement(new StandBy(bot));
	}
}


