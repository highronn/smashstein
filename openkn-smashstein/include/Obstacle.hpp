/*************************************************************************** \
 * Copyright (C) by University Paris-Est - MISS team
 * Obstacle.hpp created in 09 2008.
 * Mail : herubel@gmail.com
 *
 * This file is part of the openkn-Smashstein
 *
 * The openkn-Smashstein is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * The openkn-Smashstein is distributed in the hope that it will be useful,
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
#ifndef __OPENKN_SMASHSTEIN__OBSTACLE_HPP__
#define __OPENKN_SMASHSTEIN__OBSTACLE_HPP__

/*
 * External Includes
 */
#include <vector>
#include <OpenKN/math/Vector3.hpp>

struct Wrap;

/*
 * Namespace
 */
namespace kn
{
	namespace smashstein
	{

    //
    // Class definition
    //

    /**
     * \brief Interface class for obstacles
     */
		class Obstacle {
		public : 
			virtual ~Obstacle() {}

			//virtual const std::vector<kn::Vector3f> & getBoundingBox()const=0 ;			
			virtual const Wrap & getBoundingBox()const=0 ;			

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

