#include <Victory.hpp>
#include <StandBy.hpp>

Victory::Victory(Boxman * robot):bot(robot)
{
	//frame = 0;
	// Anim: position Victory
	bot->animation.getAnimeType() = ONE_SHOT;
	bot->animation.setAnimation(VICTORY, 30);
}

void Victory::act()
{
	if(bot->animation.isTerminate())
		bot->setMovement(new StandBy(bot));
	//++frame;
}


