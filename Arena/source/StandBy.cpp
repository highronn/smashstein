#include <Run.hpp>
#include <Jump.hpp>
#include <Block.hpp>
#include <Throw.hpp>
#include <Shoot.hpp>
#include <Shoot2.hpp>
#include <StandBy.hpp>
#include <Victory.hpp>
#include <GLWidget.hpp>

StandBy::StandBy(Boxman * robot):bot(robot)
{
	startTime = TIMER.elapsed(); // on peut le mettre ici car l'obet est utilisé immédiatement après avoir été instancié
	//std::cout << "standBy" << std::endl;
}

void StandBy::act()
{
	bot->getRobotState().getVelocity()[0] = 0.0;
	bot->getRobotState().getAcceleration()[0] = 0.0;
	bot->getRobotState().getDirection()[0] = 0.0;

	// Anim: position StandBy
	bot->animation.getAnimeType() = LOOP;
	bot->animation.setAnimation(STANDBY, 40);

	//std::cout << "StandBy-------------------------------------------------------------" << std::endl;
	/*
	* Interprêtation des ordres
	*/
	std::string order = bot->getSpeaker().getLastOrder().first;
	int param = bot->getSpeaker().getLastOrder().second;
	if (order == "Throw")
	{
		bot->setMovement(new Throw(bot));
	}
	else if (order == "Attack" && param == 1)
	{
		bot->setMovement(new Shoot(bot));
	}
	else if (order == "Attack" && param == 2)
	{
		bot->setMovement(new Shoot2(bot));
	}
	else if (order == "Jump")
	{
		bot->setMovement(new Jump(bot));
	}
	else if (order == "Block")
	{
		bot->setMovement(new Block(bot));
	}
	else if (order == "Run")
	{
		bot->setMovement(new Run(bot));

		//std::cout << "StanBy > Run" << std::endl;
	}
	// En cas d'inactivité prolongée, on lance l'animation du perso "victory"
	else if( TIMER.elapsed() - startTime > 6000)
	{
		bot->setMovement(new Victory(bot));
		startTime = TIMER.elapsed();
	}

}



