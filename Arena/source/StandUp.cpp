#include <StandUp.hpp>
#include <StandBy.hpp>

StandUp::StandUp(Boxman * robot):bot(robot)
{
	//frame = 0;
}

void StandUp::act()
{

	// Anim: Stand Up
	bot->animation.getAnimeType() = ONE_SHOT;
	bot->animation.setAnimation(STANDUP, 40);

	if(bot->animation.isTerminate())
	{
		bot->setMovement(new StandBy(bot));
		bot->getRobotState().isDead() = false;
	}
	//++frame;
}


