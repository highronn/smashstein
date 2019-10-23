#include <Particle.hpp>
#include <variables.hpp>

Particle::Particle(void)
{
	//bidon value
	image = NULL;
	alpha = 0.0f;
	lifeTime = 0;
	currentLifeTime = 0;
	speed = 0.0;
	t = 0;
}

Particle::Particle(int currentLT,float speedo,BillBoard *bill)
{
	image = bill;
	alpha = 1.0f;
	lifeTime = currentLT;
	currentLifeTime = currentLT;
	speed = speedo;
	t = TIMER.elapsed();
}

Particle::Particle(const Particle & parti)
{
	image = parti.image;
	alpha = parti.alpha;
	lifeTime = parti.lifeTime;
	currentLifeTime = parti.currentLifeTime;
	speed = parti.speed;
	t = parti.t;
}

Particle::~Particle(void)
{
	delete image;
}

void Particle::drawParticle(RTPoint::point3 camera)
{ 
	glDepthMask(GL_FALSE);
	//glColor4f(alpha,alpha/2.0f,0.1f,alpha);
	glColor4f(alpha, alpha/2.0, 0.1, 1.0);
	
	image->draw(camera);
	
	glDepthMask(GL_TRUE); 
}

void Particle::updateParticle(void)
{
	int cpt = TIMER.elapsed();
	int diff = cpt - t;
	currentLifeTime -= diff;
	t = cpt;
 	image->position.y += speed/1000.0f * diff;
	alpha = float(currentLifeTime) / float(lifeTime) * 5;
}

