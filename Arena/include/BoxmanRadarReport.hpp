//
// Anti-doublon
//
#ifndef BOXMANRADARREPORT_HPP
#define BOXMANRADARREPORT_HPP


//
// External Includes
//
#include <RadarReport.hpp>

#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>

#include <Node.hpp>

// Graph to manage movements in the Arena
typedef boost::adjacency_list<  // adjacency_list template depending on :
    boost::listS,               //  type of container for nodes. Here, std::list.
    boost::vecS,                //  Type of container for edges. Here, std::vector.
    boost::bidirectionalS,      //  Tyype of arcs. Should be boost::directedS.
    Node,                   //  Nodes type.
    boost::property < boost::edge_weight_t, float >          //  Edge type
	> ArenaGraph;
	
typedef ArenaGraph::vertex_descriptor ArenaNodeID; // Vertex

typedef ArenaGraph::edge_descriptor   ArenaEdgeID; // Edges
typedef boost::property_map<ArenaGraph, boost::edge_weight_t>::type ArenaEdgeMap; // Edge map type

typedef boost::graph_traits<ArenaGraph>::vertex_iterator ArenaNodeIterator; // Iterator on vertex
typedef boost::graph_traits<ArenaGraph>::edge_iterator ArenaEdgeIterator; // Iterator on edges

class BoxmanRadarReport  : public kn::smashstein::RadarReport
{
	public:
		BoxmanRadarReport() {};
		~BoxmanRadarReport() {};


	private :
		std::vector<kn::smashstein::Robot *> nearbyRobots;
	public :
		const std::vector<kn::smashstein::Robot *> & getNearbyRobots()const;
		std::vector<kn::smashstein::Robot *> & getNearbyRobots();

	private :
		std::vector<kn::smashstein::Obstacle *> nearbyObstacles;
	public :
		inline const std::vector<kn::smashstein::Obstacle *> & getNearbyObstacles()const {return nearbyObstacles;}
		inline  std::vector<kn::smashstein::Obstacle *> & getNearbyObstacles() {return nearbyObstacles;}

	private :
		std::vector<kn::smashstein::Projectile *> nearbyProjectiles;
	public :
		inline const std::vector<kn::smashstein::Projectile *> & getNearbyProjectiles()const {return nearbyProjectiles;}
		inline std::vector<kn::smashstein::Projectile *> & getNearbyProjectiles() {return nearbyProjectiles;}
		
	public : // Specific function in the graph to find specials robots
		int getNearestRobot(const kn::smashstein::Robot & me);
		int getWeakestRobot(const kn::smashstein::Robot & me);
		//std::pair<std::string, int> goTo(const ArenaGraph &, const int &, const int &);

	private :
		ArenaGraph* graphe;
	public :
		inline const ArenaGraph & getGraph() const {return *graphe;}
		inline ArenaGraph & getGraph() {return *graphe;}
		inline void setGraph(ArenaGraph & g) {graphe = &g;};
		
	public : // fonctions de parcourt du graphe
		ArenaNodeID getRobotNodeID(const int &, bool &, kn::Vector3f & pos); // give node id where the robot given in parameter is in - give is position in pos vector
		ArenaNodeID getRobotNodeID(const int & id, bool & found);
		ArenaNodeID giveNextNodeToGo(ArenaGraph & graphe, const ArenaNodeID & myNode, const ArenaNodeID & avatarNodeID); // give next node to go to reach myNode to avaNodeID using dijkstra
		ArenaNodeID giveNearestNode(ArenaGraph & graphe, const kn::smashstein::Robot & robot); // give nearest node from the robot
		std::pair<std::string, int> getOrderToGo(const ArenaGraph & graphe, const ArenaNodeID & myNode, const ArenaNodeID & nextNodeToGo, 
												 const kn::Vector3f & myPos, const kn::Vector3f & posToGo, const bool & isJumping); // find order to give to go frolm myNode to nextNodeToGo
		std::pair<std::string, int> getOrderToGoNear(const kn::Vector3f & botPos, const kn::Vector3f & avatarPos); // give order to go near from a target when they are both in a same node

};

//
// End Anti-doublon
//
#endif
