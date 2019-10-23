/*
 * External Includes
 */
#include <Robot.hpp>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <ctime>
#include <vector>

#include <Robot.hpp>
#include <../Arena/include/Boxman.hpp>
#include <../Arena/include/BoxmanRadarReport.hpp>

#include <Behavior.hpp>

/*#define AGRESSIVE 1
#define FEARFUL 2
#define SUICIDAL 3*/

#define radar ((BoxmanRadarReport)(((Boxman*)(myrobot))->getRadarReport()))
#define myradar ((BoxmanRadarReport)(((Boxman)(me))->getRadarReport()))
//#define robot 

int randomTable2(const std::vector<int> & tab);
int modifyCaratere2(void);
int getVictim2(const kn::smashstein::Robot & bot);
int getRevenge2(const kn::smashstein::Robot & bot);
int findTarget2(const std::vector<kn::smashstein::Robot*> & allTarget, const kn::smashstein::Robot & me);
void findBehavior2(kn::smashstein::Robot & me, const int & idTarget);
void findReflexe2(kn::smashstein::Robot & me);
void execBehavior2(kn::smashstein::Robot & me, const int & idTarget);

// functions to manage IA behavior
int modifyCaratere2(void)
{
	//la table des hasards avec dans l'ordre: peureux,suicidaire,paranoiaque
	std::vector<int> probaractere; //10%,20%,70%
	probaractere.push_back(10);
	probaractere.push_back(30);
	probaractere.push_back(100);

	int res = randomTable2(probaractere);
	/*switch(res)
	{
		case 1 : // Do nothing
			return FEARFUL;
		break;
		
		case 2 : // Change To suicidal
			return SUICIDAL;
		break;
		
		case 3 : // Change to paranoiaque
			return PARANOIA;
		break;
	}*/
	
	return FEARFUL;
}

int randomTable2(const std::vector<int> & tab)
{
	if(tab.size() == 0) return -1;	
	int alea = (int)(rand()*100.0f/RAND_MAX);
	
	//printf("aleaTOIRe ............. %d\n", alea);
	
	for(unsigned int i=0; i<tab.size()-1; ++i)
	{
		if(alea > tab[tab.size()-2-i])
		{//-1 for the index et -1 because last probability is set to 100
			return (tab.size()-i);// return the place in the tab and not the index
		}
	}
	
	return 1;//la solution est le premier element du tableau
}

int getRevenge2(const kn::smashstein::Robot & bot) // take the robot who is thinking
{
	int idRevenge = -1;//The more killer robot for a given bot
	int tmpRevenge = -1;
	
	for(unsigned int i=0; i<bot.getRevenge().size(); ++i)
	{
		if(bot.getRevenge()[i].second > tmpRevenge)
			idRevenge = bot.getRevenge()[i].first;
	}
	
	return idRevenge;
}

int getVictim2(const kn::smashstein::Robot & bot) // take the robot who is thinking
{
	int idVictim = -1;//Id of the most hitted robot for a given bot
	int tmpVictim = -1;
	
	for(unsigned int i=0; i<bot.getVictim().size(); ++i)
	{
		if(bot.getVictim()[i].second > tmpVictim)
			idVictim = bot.getVictim()[i].first;
	}
	
	return idVictim;
}

int findTarget2(const std::vector<kn::smashstein::Robot*> & allTarget, const kn::smashstein::Robot & me)
{
	// all robots radars have the same radars
	if(allTarget.size() == 0) return -1;
	//BoxmanRadarReport Radar = ((Boxman*)(allTarget[0]))->getRadarReport();
	//kn::smashstein::RadarReport* Radar = &(allTarget[0])->getRadarReport();
		
	//la table des hasards avec dans l'ordre: idNear,idDying,idRevenge,idVictim
	std::vector<int> proba;//20%,5%,70%,5%
	proba.push_back(20);
	proba.push_back(25);
	proba.push_back(95);
	proba.push_back(100);
	
	int res = randomTable2(proba); 
	
	switch(res)
	{
		case 1 : // Nearest robot
			return ((BoxmanRadarReport*)(me.getRadarReportP()))->getNearestRobot(me);
		break;
		
		case 2 : // Weakest robot
			return ((BoxmanRadarReport*)(me.getRadarReportP()))->getWeakestRobot(me);
		break;
		
		case 3 : // Revenge bot
			return getRevenge2(me); 
		break;
		
		case 4 : // Victim bot
			return getVictim2(me);
		break;
	}
	
	return -1;
}

void findBehavior2(kn::smashstein::Robot & me, const int & idTarget)
{
	//la table des hasards avec dans l'ordre: goTo,attack1,attack2,throw,block
	std::vector<int> proBehavior;//66%,2%,2%,15%,15%
	proBehavior.push_back(66);
	proBehavior.push_back(68);
	proBehavior.push_back(70);
	proBehavior.push_back(85);
	proBehavior.push_back(100);
	
	int res = randomTable2(proBehavior);
	printf("LE RANDOM TAB MA ENVOYE %d\n", res);
	std::string aname1("Attack");
	std::string aname2("GoTo");
	std::string aname3("None");
	
	Behavior *behav1; 
	Behavior *behav2; 
	Behavior *behav3;
	
	switch(res)
	{
		case 1 :
			//fixe des coordonnées aléatoires pour se promener et empile goTo
			int alea;
			alea = (int)(rand()*15/RAND_MAX);
			
			Behavior* behav;
			
			behav = new Behavior("GoTo", alea, 50);
			me.getActionBar().push_back(behav);
		break;
		
		case 2 :
			//emplie le behavior attack1 puis goTo
			aname1 = "Attack";
			aname2 = "GoTo";
			
			behav1 = new Behavior(aname1, 1.0, 50);
			behav2 = new Behavior(aname2, (float)idTarget, 50);

			me.getActionBar().push_back(behav1);
			me.getActionBar().push_back(behav2);
		break;
		
		case 3 :
			//emplie le behavior attack2 puis goTo
			aname1 = "Attack";
			aname2 = "GoTo";
			
			behav1 = new Behavior(aname1, 1.0, 50);
			behav2 = new Behavior(aname2, (float)idTarget, 50);


			
			me.getActionBar().push_back(behav1);
			me.getActionBar().push_back(behav2);
		break;
		
		case 4 :
			//Stacking throw behavior
			aname1 = "Throw";
			aname2 = "GoTo";
			aname3 = "None";
			//behav1 = new Behavior(aname1, bot.getPorteeProjectile(), 50);//où le second parametre est la portée (maximale pour les prudents, divisée par 2 pour être sur de toucher...)
			behav1 = new Behavior(aname1, 10, 50);//où le second parametre est la portée (maximale pour les prudents, divisée par 2 pour être sur de toucher...)
			behav2 = new Behavior(aname2, (float)idTarget, 50);
			behav3 = new Behavior(aname3, 15, 50);

			me.getActionBar().push_back(behav1);
			me.getActionBar().push_back(behav3);
			me.getActionBar().push_back(behav2);
		break;
	}
	
	return;
}

void findReflexe2(kn::smashstein::Robot & me)
{
	//la table des hasards avec dans l'ordre: goTo,block,do nothing
	std::vector<int> probaReflexes; //20%,70%,10%
	//probaReflexes.push_back(20);//Rony doen't rule
	probaReflexes.push_back(90);
	probaReflexes.push_back(100);

	int res = randomTable2(probaReflexes);
	std::string aname("");
	int delta;
	
	Behavior* behav = NULL;
	
	switch(res)
	{
		case 1 :
			// Look for nearest neighboor node		
			aname = "GoTo";
			
			//behav = new Behavior(aname, (float)(((BoxmanRadarReport)(me.getRadarReport())).getNearestNode(me)), 50);
			behav = new Behavior(aname, (float)(((BoxmanRadarReport*)(me.getRadarReportP()))->giveNearestNode(((BoxmanRadarReport*)(me.getRadarReportP()))->getGraph(), me)), 50);
			me.getActionBar().push_back(behav);
		break;
		
		case 2 :
			// Stack block behavior
			delta = (int)(rand()*40.0f/RAND_MAX - 20.0f);
			aname = "Block";
			
			behav = new Behavior(aname, 30+delta, 50);//Second paramter : Number of frames while block will be taken
			me.getActionBar().push_back(behav);
		break;
		
		case 3 :
			//do nothing
		break;
	}
	
	return;
}

void execBehavior2(kn::smashstein::Robot & me, const int & idTarget)
{
	//ici on compare deux string
	std::string whichBehavior = me.getActionBar().back()->getTypeAction();
	
	ArenaNodeID myNode, targetNode;
	
	if(whichBehavior == "GoTo")
	{
		// Give bot Node ID
		bool found = false;

		kn::Vector3f botPos;
		kn::Vector3f targetPos;

		ArenaNodeID myNode = ((BoxmanRadarReport*)(me.getRadarReportP()))->getRobotNodeID(me.id(), found, botPos);
		ArenaNodeID targetNode = ((BoxmanRadarReport*)(me.getRadarReportP()))->getRobotNodeID(idTarget, found, targetPos);

		std::pair<std::string, int> order("None", 0);

		if(found)
		{
			//printf("\n");
			//printf("My id %d - ", me.id());
			//std::cout << "Im in node " << myNode << " " << "avatar is in node " << targetNode << std::endl;
			
			// Recherche du chemin avec l'algo de dijkstra
			ArenaGraph & graphe = ((BoxmanRadarReport*)(me.getRadarReportP()))->getGraph();
			
			if(found)
			{
				if((myNode != targetNode))
				{
					ArenaNodeID nextNodeToGo = ((BoxmanRadarReport*)(me.getRadarReportP()))->giveNextNodeToGo(graphe, myNode, targetNode);
					//printf("Go To %d -> %d - ", (int)myNode, (int)nextNodeToGo);
					
					order = ((BoxmanRadarReport*)(me.getRadarReportP()))->getOrderToGo(graphe, myNode, 
																					   nextNodeToGo, botPos, targetPos, 
																					   me.getRobotState().isJumping());
				}
				else // if we are in the same node as the avatar
				{
					me.getActionBar().back()->getPriority() = 0;
					order = ((BoxmanRadarReport*)(me.getRadarReportP()))->getOrderToGoNear(botPos, targetPos);
					//order.first = "None";
				}
			}
			else
				order.first = "None";
		}
		
		me.getSpeaker().sendOrder(order.first, order.second);
	}
	else if(whichBehavior == "Attack")
	{
		
		float espilon = 0.4;
		// Ask to change attack animation
		if(me.getActionBar().back()->getObjectif()  < 1.0+espilon)
		{
			// Attack order number 1
			me.getSpeaker().sendOrder("Attack", 1);
		}
		else
		{
			// Attack order number 2
			me.getSpeaker().sendOrder("Attack", 2);
		}
		
		me.getActionBar().back()->getPriority() = 0;
	}		
	else if(whichBehavior == "Throw")
	{
		//selon le paramètre on s'approche plus ou moins grâce à un "goTo" reflexe (pas encore géré)
		me.getSpeaker().sendOrder("Throw",15);

		// If blocking time is decreasing
		me.getActionBar().back()->getObjectif() -= 1.0;
		//si l'objectif est rempli alors on met la priorite à 0
		if(me.getActionBar().back()->getObjectif() <= 0.0)
			me.getActionBar().back()->getPriority() = 0;
	}
	else if(whichBehavior == "Block")
	{
		me.getSpeaker().sendOrder("Block",-1); // Dumb parameter
		
		// If blocking time is decreasing
		me.getActionBar().back()->getObjectif() -= 1.0;
		//si l'objectif est rempli alors on met la priorite à 0
		if(me.getActionBar().back()->getObjectif() <= 0.0)
			me.getActionBar().back()->getPriority() = 0;
	}
	else if(whichBehavior == "None")
	{
		me.getSpeaker().sendOrder("None",-1.0); // Dumb parameter
		
		// Stand time decresing
		me.getActionBar().back()->getObjectif() -= 1.0;
		
		// If goal is done -> priority to 0
		if(me.getActionBar().back()->getObjectif() <= 0.0)
			me.getActionBar().back()->getPriority() = 0;
	}
	
	return ;
}

//
// Main Method
//
extern "C"
{
	void init()
    {
		srand(time(NULL));
	}
	
	void act(kn::smashstein::Robot * myrobot)
    {
		if(myrobot == NULL)
		{
			printf("No BOT Given\n");
			return;
		}
		
		// final target id
		int idTarget = -1;
			
			if(myrobot->getRadarReport().getNearbyRobots().size() == 1)
			{
				// searching of the other robot
				/*if(myrobot->getRadarReport().getNearbyRobots()[0]->id() != myrobot->id())
					idTarget = myrobot->getRadarReport().getNearbyRobots()[0]->id();
				else
					idTarget = myrobot->getRadarReport().getNearbyRobots()[1]->id();*/					
				idTarget = myrobot->getRadarReport().getNearbyRobots()[0]->id();
			}
			else //choix de cible
			{
				idTarget = findTarget2(myrobot->getRadarReport().getNearbyRobots(), *myrobot);
			}	
				
			//Checking
			// No other bot - choose the avatar player by default
			/*if(idTarget == -1)
				std::cout << "Target is the player avatar\n";
			else
				printf("target is robot %d\n", idTarget);*/

		//ETAPE II : MAJ de la memoire
		//ETAPE III : Suffisamment de probabilités ?
		//ETAPE IV : MAJ de la barette de behavior
			
			//ai-je rempli mon objectif ?
			if(((*myrobot).getActionBar().size() != 0) && (*myrobot).getActionBar().back()->getPriority() == 0)//l'objectif est atteint
			{
				//on depile l'élément au sommet de la pile
				(*myrobot).getActionBar().pop_back();
			}
			
			//ma précédente action est-elle terminée ?
			if((*myrobot).getActionBar().size() == 0)//si la pile de comportement est vide
			{
				//empile un nouveau behavior
				//printf("\t########### EMPILE BEHAVIOR\n");
				findBehavior2(*myrobot, idTarget);
				//printf("\t########### EMPILE BEHAVIOR type %s\n", (*myrobot).getActionBar().back()->getTypeAction().c_str());
			}		
		//ETAPE V : Quel est mon état ?
			//y a-t-il des évènements majeurs ? cad :
			//	- y a-t-il un projectile dans la zone de portée autour du bot ?
			//	- est-il entrain de subir des dégats ?
			//if(isProjectileThere() == true || isFightThere() == true)
			//{
				//empile un nouveau behavior "reflexe"
				findReflexe2(*myrobot);//reponse à un projectile ou à une attaque au CC
			//}
			
			
		//ETAPE : demande à l'arêne d'exécuter l'action au sommet de la pile
			execBehavior2(*myrobot, idTarget);
			
		//ETAPE VI : change de comportement ?		
		//CARACTERE	
			//int delta = (int)(rand()*20-10/RAND_MAX);
			
			//Pour un bot peureux la seule chose pouvant lui faire changer de comportement c'est l'imminence de la mort	
			//if(myrobot->getRobotState().getDamages() > 150+delta) ;
				//return modifyCaratere();
			//else ;
				//return AGRESSIVE;
	}

	void destroy2()
    {
		//std::cout << "DumbAI is going to sleep..." << std::endl;
	}
}
