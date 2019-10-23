/*
 * Internal Includes
 */
#include <Boxman.hpp>
#include <Wrap.hpp>

int absf(const float & n)
{
	if(n < 0)
		return -n;
	else
		return n;
}

const std::vector<kn::smashstein::Robot *> & BoxmanRadarReport::getNearbyRobots()const
{
	return nearbyRobots;
}

std::vector<kn::smashstein::Robot *> & BoxmanRadarReport::getNearbyRobots()
{
	return nearbyRobots;
}

int BoxmanRadarReport::getNearestRobot(const kn::smashstein::Robot & me)
{
	int botId = -1;
	float min = 10000000000.0f;
	kn::Vector3f myPosition = me.getRobotState().getPosition();
	
	if(nearbyRobots.size() == 0)
		return botId; // target is the avatar
	
	// Looking on all robots
	for(unsigned int i=0; i<nearbyRobots.size(); ++i)
	{
		if(nearbyRobots[i]->id() != me.id()) // if it's not the same robot
		{
			kn::Vector3f u = nearbyRobots[i]->getRobotState().getPosition();
			kn::Vector3f distance = u-myPosition;
			
			if(distance.getNorm() < min)
			{
				min = distance.getNorm();
				botId = nearbyRobots[i]->id();
			}
		}
	}
	
	return botId;
}

int BoxmanRadarReport::getWeakestRobot(const kn::smashstein::Robot & me)
{
	int botId = -1;
	int max = 0;
	kn::Vector3f myPosition = me.getRobotState().getPosition();
	
	if(nearbyRobots.size() == 0)
		return botId; // target is the avatar
	
	// Looking on all robots
	for(unsigned int i=0; i<nearbyRobots.size(); ++i)
	{
		if(nearbyRobots[i]->id() != me.id()) // if it's not the same robot
		{
			if(nearbyRobots[i]->getRobotState().getDamages() > max)
			{
				max = nearbyRobots[i]->getRobotState().getDamages();
				botId = nearbyRobots[i]->id();
			}
		}
	}
	
	return botId;
}

ArenaNodeID BoxmanRadarReport::getRobotNodeID(const int & id, bool & found)
{
	ArenaNodeID node = 0;
	found = false;
	
	ArenaNodeIterator first, last;
	boost::tie(first, last) = boost::vertices(*graphe);
	
	while((first != last) && !found)
	{
		Node N = (*graphe)[*first];
		
		// Looking in the node's bots
		for(unsigned int i=0; i<N.getBotsInside().size(); ++i)
		{
			if( ((Boxman*)(N.getBotsInside()[i]))->id() == id )
			{
				found = true;
				node = *first;
			}
		}
		
		++first;
	}
	
	return node;

}

ArenaNodeID BoxmanRadarReport::getRobotNodeID(const int & id, bool & found, kn::Vector3f & pos)
{
	ArenaNodeID node = 0;
	found = false;
	
	ArenaNodeIterator first, last;
	boost::tie(first, last) = boost::vertices(*graphe);
	
	while((first != last) && !found)
	{
		Node N = (*graphe)[*first];
		
		// Looking in the node's bots
		for(unsigned int i=0; i<N.getBotsInside().size(); ++i)
		{
			if( ((Boxman*)(N.getBotsInside()[i]))->id() == id )
			{
				found = true;
				node = *first;
				pos = ((Boxman*)(N.getBotsInside()[i]))->getRobotState().getPosition();
			}
		}
		
		++first;
	}
	
	return node;
}

ArenaNodeID BoxmanRadarReport::giveNextNodeToGo(ArenaGraph & graphe, const ArenaNodeID & myNode, const ArenaNodeID & avatarNodeID)
{
	std::vector<ArenaNodeID> p(boost::num_vertices(graphe));
	std::vector<int> d(boost::num_vertices(graphe));
	ArenaNodeID s = boost::vertex(myNode, graphe );

	boost::dijkstra_shortest_paths( graphe, s, boost::predecessor_map(&p[0]).distance_map(&d[0]));
	
	// Predecessor to find the path
	ArenaNodeID currentNode, previousNode;
	std::vector<bool> seen(boost::num_vertices(graphe), false);
	
	previousNode = avatarNodeID;
	currentNode = p[previousNode];
	
	seen[(int)currentNode] = true;
	seen[(int)previousNode] = true;
	
	//printf("Path : (%d, %d)", (int)previousNode, (int)d[previousNode]);
	
	while((currentNode != myNode) /*&& !seen[currentNode]*/)
	{
		previousNode = currentNode;
		//printf("<-(%d, %d)", (int)previousNode, (int)d[previousNode]);
		currentNode = p[previousNode];
		seen[(int)previousNode] = true;
		//printf("--");
	}
	
	//printf("<-(%d, %d) : ", (int)currentNode, (int)d[currentNode]);
	
	return previousNode;
}

ArenaNodeID BoxmanRadarReport::giveNearestNode(ArenaGraph & graphe, const kn::smashstein::Robot & robot)
{
	ArenaNodeID nodeID = 0;
	bool found = false;
	int dist = 10000000;
	
	nodeID = getRobotNodeID(robot.id(), found);
	
	if(found)
	{
		ArenaEdgeIterator vi, vend;
		for (boost::tie(vi, vend) = boost::edges(graphe); vi != vend; ++vi)
		{
			//boost::source(*first, graphe);
			//boost::target(*first, graphe);
			
			if(boost::source(*vi, graphe) == nodeID)
			{
				ArenaEdgeMap distances;
				
				if(boost::get(distances, *vi) < dist)
					dist = boost::get(distances, *vi);
			}
		}

	}
	
	return nodeID;
}

std::pair<std::string, int> BoxmanRadarReport::getOrderToGo(const ArenaGraph & graphe, const ArenaNodeID & myNode, const ArenaNodeID & nextNodeToGo, 
															const kn::Vector3f & myPos, const kn::Vector3f & posToGo, const bool & isJumping)
{	
	// normal parameters
	std::pair<std::string, int> order("None", 0);
	Node dep = graphe[myNode];
	Node end = graphe[nextNodeToGo];
	
	Wrap depW, endW;
	depW.x = dep.x();
	depW.y = dep.y();
	depW.width = dep.width();
	depW.height = dep.height();
	
	endW.x = end.x();
	endW.y = end.y();
	endW.width = end.width();
	endW.height = end.height();
	
	// If the node is higher
	if(endW.y > depW.y)
	{
		if( endW.x >= depW.x)
		{
			if(!isJumping)
			{
				order.first = "Jump";
				order.second = 1;
			}
			else // if the bot is jumping
			{
				order.first = "Run";
				order.second = 1;
			}
		}
		else if(endW.x <= depW.x)
		{
			if(!isJumping)
			{
				order.first = "Jump";
				order.second = 1;
			}
			else // if the bot is jumping
			{
				order.first = "Run";
				order.second = -1;
			}
		}
	}
	else if(depW.x < (endW.x - endW.width/2.0))
	{
		order.first = "Run";
		order.second = 1;
	}
	else if(depW.x > (endW.x + endW.width/2.0))
	{
		order.first = "Run";
		order.second = -1;
	}
	
	return order;
}

std::pair<std::string, int> BoxmanRadarReport::getOrderToGoNear(const kn::Vector3f & botPos, const kn::Vector3f & avatarPos)
{
	std::pair<std::string, int> order("None", 0);
	
	if(absf(botPos[0] - avatarPos[0]) > 0.1) // if we are not near enough
	{
		if(botPos[0] < avatarPos[0]) // go on right
		{
			order.first = "Run";
			order.second = 1;
		}
		else // go on left
		{
			order.first = "Run";
			order.second = -1;
		}
	}
	
	return order;
}
/*
std::pair<std::string, int> goTo(const ArenaGraph & graphe, const int & me, const int & target)
{
	std::pair<std::string, int> order("None", 0);
	
	return order;
}*/

