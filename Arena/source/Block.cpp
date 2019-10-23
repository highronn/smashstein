#include <StandBy.hpp>
#include <Block.hpp>

Block::Block(Boxman * robot):bot(robot), frame(0), state(BLOCK_START)
{
}
// INACHEVE!!!
void Block::act()
{

	if(state == BLOCK_START && frame == 0)
	{
		bot->getRobotState().isBlocking() = false;
		bot->animation.getAnimeType() = ONE_SHOT;
		bot->animation.setAnimation(PREBLOCK, 30);
		bot->getRobotState().getDirection()[0] = 0.0;
		bot->getRobotState().getAcceleration()[0] = 0.0;
	}
	else if(state == BLOCK_START && bot->animation.isTerminate())
	{
		bot->getRobotState().isBlocking() = true;
		state = BLOCK_WAIT;
		frame = 0;
	}
	else if(state == BLOCK_WAIT)// && frame > 15)
	{
		//state = BLOCK_END;
		//bot->animation.getAnimeType() = ONE_SHOT;
		//bot->animation.setAnimation(POSTBLOCK, 30);
		if(bot->getRobotState().shootBlocked())
		{
			bot->getRobotState().shootBlocked() = false;
			bot->animation.getAnimeType() = ONE_SHOT;
			bot->animation.setAnimation(BLOCK, 30);
			state = BLOCK_SHOCK;
		}
	}
	else if(state == BLOCK_SHOCK && bot->animation.isTerminate())
	{
		state = BLOCK_WAIT;
	}

	if(bot->getSpeaker().getLastOrder().first != "Block" || frame>60)
	{
		state = BLOCK_END;
		bot->getRobotState().isBlocking() = false;
	}
	if(state == BLOCK_END && bot->animation.isTerminate())
	{
		bot->setMovement(new StandBy(bot));
		bot->getRobotState().isBlocking() = false;
	}

	++frame;
}



