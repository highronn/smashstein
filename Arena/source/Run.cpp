#include <Run.hpp>
#include <Jump.hpp>
#include <Fall.hpp>
#include <Shoot.hpp>
#include <Block.hpp>
#include <Shoot2.hpp>
#include <Return.hpp>
#include <StandBy.hpp>
#include <GLWidget.hpp>

//Run::Run(kn::smashstein::Robot & robot):bot(robot)
Run::Run(Boxman * robot):bot(robot)
{
	state = RUN_START;
	frame = 0;
	frameFall = 0;
}

void Run::act()
{
	// variables pour simplifier l'écriture
	kn::Vector3f & directionRobot = bot->getRobotState().getDirection();
	float & relativeSpeedX = bot->getRobotState().getVelocity()[0];
	//float absSpeedX = ( relativeSpeedX > 0)? relativeSpeedX : -relativeSpeedX;

	directionRobot[1] = 0.0;
	//if(GLWidget::keyRight);

	/*
	* Interprêtation des ordres
	*/
	std::string order = bot->getSpeaker().getLastOrder().first;
	int param = bot->getSpeaker().getLastOrder().second;
	if (order == "None")
	{
		bot->getRobotState().getAcceleration() = kn::Vector3f(0., 0., 0.);
		bot->getRobotState().getDirection()[0] = 0.;
	  //std::cout << "Robot " << i << " is doing nothing" << std::endl;
	}
	else if (order == "Throw")
	{
	// std::cout << "Robot " << i << " is adjusting speed to " << param << std::endl;
	//  bot->getRobotState().getVelocity()= param*40;
	}
	else if (order == "Attack" && param == 1)
	{
		bot->setMovement(new Shoot(bot));
	}
	else if (order == "Attack" && param == 2)
	{
		bot->setMovement(new Shoot2(bot));
	}
	else if (order == "Block")
	{
		bot->setMovement(new Block(bot));
	}
	else if (order == "Run")
	{
		double angle;
		if (param>0)
		{
		  angle = 1.f;
		}
		else
		{
		  angle = -1.f;
		}

		// changing position : 1 = right, -1 = left
		directionRobot[0] = angle;// *  directionRobot[0];

		// Retournement ?
		float r = bot->getRobotState().getRotation()[1];
		// rotation de 180°
		if(
				(
					r > -90. && r <= 90. // dirigé vers la droite
					&& relativeSpeedX <= 0.2
					&& angle < 0
				)
				||
				(
					!(r > -90. && r <= 90.) // dirigé vers la gauche
					&& relativeSpeedX >= -0.2
					&& angle > 0
				)
			)
		{
			bot->setMovement(new Return(bot));
			return;
		}

	}
	else if (order == "Jump")
	{
		if(bot->getRobotState().isOnTheFloor())
			bot->setMovement(new Jump(bot));
	}

	/// ---------- ANIMATING ---------- ///

	// Si Il TOMBE
	if(bot->getRobotState().getVelocity()[1] < 0)
	{
		++frameFall;
		if(frameFall >= 20) // grande chute
			bot->setMovement(new Fall(bot));
	}
	else
		frameFall = 0;
	// relativeSpeedX = 2; // debug, avancer tout le temps

	// Si il démarre

	// premier cas, début = lancement de l'anim
	if(state==RUN_START && frame == 0 && !bot->getRobotState().noPrerun())
	{
		bot->animation.getAnimeType() = ONE_SHOT;
		bot->animation.setAnimation(PRERUN, 60);

		//std::cout << "START Running" << std::endl;
	}
	// cas 2 : l'anim prerun n'en est pas encore au niveau où on on peut avancer
	else if(state==RUN_START && !bot->animation.isTerminate() && frame < 3 && !bot->getRobotState().noPrerun())
	{
		bot->getRobotState().getDirection()[0] = 0.0;
		bot->getRobotState().getAcceleration()[0] = 0.0;
		relativeSpeedX = 0.0;
	}
	// cas suivant, toujours prerun mais on commence à avancer
	else if(state==RUN_START && !bot->animation.isTerminate() && !bot->getRobotState().noPrerun())
	{
	}
	// anim prerun terminée
	else if(state==RUN_START && (bot->animation.isTerminate() || !bot->getRobotState().noPrerun() ))
	{
		//std::cout << "Run > Run" << std::endl;
		bot->animation.getAnimeType() = LOOP;
		bot->animation.setAnimation(RUN, 25);
		frame = 0;
		state = RUN_CONTINUE;
		bot->getRobotState().noPrerun() = false;
	}
	// Si il est en train de s'arreter
	else if( // pas genial ce test
			state == RUN_CONTINUE
			&& frame > 0
			&& bot->getRobotState().getDirection()[0] < 0.001
			&& bot->getRobotState().getDirection()[0] > -0.001
			/*
			&& absSpeedX < 1
			*/
			)
	{
		bot->animation.getAnimeType() = ONE_SHOT;
		bot->animation.setAnimation(POSTRUN, 30);
		frame = 0;
		state = RUN_STOP;
	}
	// Si il est en train de s'arreter mais qu'on veut le faire avancer
	else if(
			state == RUN_STOP
			&& frame > 0
			&& (directionRobot[0] > 0.001 || directionRobot[0] < -0.001)
			)
	{
		bot->animation.getAnimeType() = ONE_SHOT;
		bot->animation.setAnimation(PRERUN, 40);
		frame = 0;
		state = RUN_START;
	}
	// Si il est arrêté et en train de se mettre en position stable (fin de postRun)
	else if(state == RUN_STOP && !bot->animation.isTerminate() && frame > 13)
	{
		// Si Il CHUTE tout en voulant s'arrêter, anim TOMBE.
		if(bot->getRobotState().getVelocity()[1] < 0.0)
			bot->setMovement(new Fall(bot));
		// sinon arrêt du perso
		else
			relativeSpeedX = 0;
	}
	// Si il est arrêté et stable
	else if(state == RUN_STOP && bot->animation.isTerminate())
	{
		bot->setMovement(new StandBy(bot));
	}

	++frame;

}
