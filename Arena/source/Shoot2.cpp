
#include <StandBy.hpp>
#include <Shoot2.hpp>
#include <Run.hpp>

Shoot2::Shoot2(Boxman * robot):bot(robot)
{
	frame = 0;
}

void Shoot2::act()
{
	if(frame==0)
	{
		bot->animation.getAnimeType() = ONE_SHOT;
		bot->animation.setAnimation(ATTACK2, 40);
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
