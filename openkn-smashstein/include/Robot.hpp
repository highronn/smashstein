/*************************************************************************** \
 * Copyright (C) by University Paris-Est - MISS team
 * Robot.hpp created in 09 2008.
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
#ifndef __OPENKN_SMASHSTEIN__ROBOT_HPP__
#define __OPENKN_SMASHSTEIN__ROBOT_HPP__

/*
 * External Includes
 */
#include <OpenKN/math/Vector3.hpp>

/*
 * Internal Includes
 */
#include <Projectile.hpp>
#include <RobotState.hpp>
#include <Speaker.hpp>
#include <RadarReport.hpp>
#include <Movement.hpp>

// pre-declaration
class Movement;
class Behavior;
//class Animation;


/*
 * Namespace
 */
namespace kn
{
	namespace smashstein
	{

    /*
     * Class definition
     */

    /**
     * \brief Interface class for robots
     */
		class Robot
		{
			public :
				virtual ~Robot() {}
				
				virtual const int & id() const=0;
				
				virtual void setMovement(Movement * newMovement)=0;

				virtual const RobotState & getRobotState()const=0;
				
				virtual const std::vector< std::pair<int,int> > & getRevenge() const=0;
				
				virtual const std::vector< std::pair<int,int> > & getVictim() const=0;
				
				virtual std::vector<Behavior*> & getActionBar()=0; // give the action bar of the bot
				
				//virtual Animation & getAnimation()=0;

				virtual const Speaker & getSpeaker()const=0;			
				virtual  Speaker & getSpeaker()=0;			

				virtual const RadarReport & getRadarReport()const=0;
				virtual const RadarReport * getRadarReportP()const=0;

				virtual float getRadarRange()const=0;						

				virtual kn::Vector3f getMaxSpeed()const=0;

				virtual float getWeight()const=0;						

				virtual float getGunFrequency()const=0;						

				virtual float getGunPower()const=0;						

				virtual float getGunProjectileVelocity()const=0;
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

