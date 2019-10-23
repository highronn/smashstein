#include <StandBy.hpp>
#include <Shoot.hpp>
#include <Run.hpp>

Shoot::Shoot(Boxman * robot):bot(robot)
{
	frame = 0;
}

void Shoot::act()
{
	if(frame==0)
	{
		bot->animation.getAnimeType() = ONE_SHOT;
		bot->animation.setAnimation(ATTACK1, 40);
		bot->getRobotState().getDirection()[0] = 0;
		bot->getRobotState().isAttacking() = 1;
	}
	else if(frame == 10)
	{
		bot->getRobotState().isAttacking() = 2;

	}
	else if(frame > 10)
	{
		bot->getRobotState().isAttacking() = 0;

		if(bot->animation.isTerminate())
		{
			float & relativeSpeedX = bot->getRobotState().getVelocity()[0];
			float absSpeedX = ( relativeSpeedX > 0)? relativeSpeedX : -relativeSpeedX;

			if(absSpeedX > 0.1 )
			{
				bot->setMovement(new Run(bot));
			}
			else
				bot->setMovement(new StandBy(bot));

			bot->getRobotState().isAttacking() = 0;
		}
	}

	++frame;
}
