#include <Damage.hpp>
#include <StandBy.hpp>

Damage::Damage(Boxman * robot):bot(robot)
{
	frame = 0;
}

void Damage::act()
{
	if(frame==0)
	{
		bot->animation.getAnimeType() = ONE_SHOT;
		bot->animation.setAnimation(DAMAGE, 40);
	}
	else if(bot->animation.isTerminate())
	{
		bot->setMovement(new StandBy(bot));
	}
	++frame;
}


