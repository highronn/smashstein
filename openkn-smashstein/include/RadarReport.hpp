/*************************************************************************** \
 * Copyright (C) by University Paris-Est - MISS team
 * RadarReport.hpp created in 09 2008.
 * Mail : herubel@gmail.com
 *
 * This file is part of the OpenKN-Smashstein
 *
 * The OpenKN-Smashstein is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The OpenKN-Smashstein is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
\***************************************************************************/

/*
 * Anti-doublon
 */
#ifndef __OPENKN_SMASHSTEIN__RADARREPORT_HPP__
#define __OPENKN_SMASHSTEIN__RADARREPORT_HPP__

/*
 * External Includes
 */
#include <vector>
#include <OpenKN/math/Vector3.hpp>


/*
 * Internal Includes
 */
#include <Obstacle.hpp>
#include <Projectile.hpp>


/*
 * Namespace
 */
namespace kn
{
	namespace smashstein
	{

		/* 
		 * Predeclarations
		 */
		class Robot;
		//class ArenaGraph;

		/*
		 * Class definition
		 */

		/**
		 * \brief Interface class for radarreports
		 */
		class RadarReport
		{
			public :
				virtual ~RadarReport() {}
				
				virtual const std::vector<Robot *> & getNearbyRobots() const=0 ;

				virtual const std::vector<Obstacle *> & getNearbyObstacles() const=0 ;			

				virtual const std::vector<Projectile *> & getNearbyProjectiles() const=0 ;
				
				//virtual ArenaGraph * getGraph() =0;
	
				//virtual const int getNearestRobot(const kn::smashstein::Robot & me) const=0;
				//virtual const int getNearestRobot(const kn::smashstein::Robot & me) const=0;
				
				//virtual const int getWeakestRobot(const kn::smashstein::Robot & me) const=0;		
		};

 		/*
		 * End of Namespace
		 */
	}
}


/*
 * End of Anti-doublon
 */
#endif

