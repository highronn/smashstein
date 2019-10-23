#include <Throw.hpp>
#include <StandBy.hpp>
#include <EffectFactory.hpp>
#include <Arena.hpp>
#include <Robots.hpp>


Throw::Throw(Boxman * robot):bot(robot)
{
	frame = 0;
}

void Throw::act()
{

	if(frame==0)
	{
		bot->animation.getAnimeType() = ONE_SHOT;
		bot->animation.setAnimation(THROW, 40);
	}
	else if(frame==8)
	{
		EffectFactory factory = EffectFactory::getInstance();
		
		if(bot->type() == OPERA) // send fireball
		{
			FireBall *coco = factory.giveMeAFireBall();
			coco->posX = bot->getRobotState().getPosition()[0];
			coco->posY = bot->getRobotState().getPosition()[1]+0.3;
			coco->vectVit[0] = ((bot->getRobotState().getRotation()[1]) > 90)? -3. : 3.;
			coco->rot = bot->getRobotState().getRotation()[1];
			coco->timeStart = TIMER.elapsed();
			coco->idLauncher = bot->id(); // <-------------------
			Arena::getFireballs().push_back(coco);
		}
		else if(bot->type() == BANDICOOT)
		{
			CocoNut *coco = factory.giveMeACocoNut();
			coco->posX = bot->getRobotState().getPosition()[0];
			coco->posY = bot->getRobotState().getPosition()[1]+0.5;
			coco->vectVit[0] = ((bot->getRobotState().getRotation()[1]) > 90)? -3. : 3.;
			coco->rot = bot->getRobotState().getRotation()[1];
			coco->timeStart = TIMER.elapsed();
			coco->idLauncher = bot->id();
			Arena::getCocoNuts().push_back(coco);
		}
		else if(bot->type() == HECTOR)
		{
			WaterBall *coco = factory.giveMeAWaterBall();
			coco->posX = bot->getRobotState().getPosition()[0];
			coco->posY = bot->getRobotState().getPosition()[1]+0.4;
			coco->vectVit[0] = ((bot->getRobotState().getRotation()[1]) > 90)? -3. : 3.;
			coco->rot = bot->getRobotState().getRotation()[1];
			coco->timeStart = TIMER.elapsed();
			coco->idLauncher = bot->id();
			Arena::getWaterBalls().push_back(coco);
		}
		else if(bot->type() == BOXMAN)
		{
			ExplodingCube *coco = factory.giveMeAnExplodingCube();
			coco->posX = bot->getRobotState().getPosition()[0];
			coco->posY = bot->getRobotState().getPosition()[1]+0.5;
			coco->vectVit[0] = ((bot->getRobotState().getRotation()[1]) > 90)? -4. : 4.;
			coco->rot = bot->getRobotState().getRotation()[1];
			coco->timeStart = TIMER.elapsed();
			coco->idLauncher = bot->id();
			Arena::getExplodingCubes().push_back(coco);
		}
	}
	else if(bot->animation.isTerminate())
	{
		bot->setMovement(new StandBy(bot));
	}

	++frame;
}

