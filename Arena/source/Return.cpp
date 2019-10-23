#include <StandBy.hpp>
#include <Return.hpp>

Return::Return(Boxman * robot):bot(robot)
{
	frame = 0;
}

void Return::act()
{
	// lancement de la rotation
	if(frame == 0)
	{
		bot->animation.getAnimeType() = ONE_SHOT;
		bot->animation.setAnimation(ROTATE, 70);
		bot->getRobotState().getDirection()[0] = 0;
	}
	else if(bot->animation.isTerminate())
	{
		float & r = bot->getRobotState().getRotation()[1];
		// rotation de 180°
		if( r > -90. && r <= 90. ) // tout ça pour dire r==0
			r = 180.f;
		else
			r = 0.f;
		// fin de la rotation!
		bot->setMovement(new StandBy(bot));
		bot->animation.setAnimation(STANDBY, 40); // on doit définir ce mouvement maintenant sinon la rotation s'effectue le temps d'une frame sur la fin de l'anim rotate...
	}

	++frame;
}


