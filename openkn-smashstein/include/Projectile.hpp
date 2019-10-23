/*************************************************************************** \
 * Copyright (C) by University Paris-Est - MISS team
 * Projectile.hpp created in 09 2008.
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
#ifndef __OPENKN_SMASHSTEIN__PROJECTILE_HPP__
#define __OPENKN_SMASHSTEIN__PROJECTILE_HPP__

/*
 * External Includes
 */
#include <OpenKN/math/Vector3.hpp>

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
     * \brief Interface class for projectiles
     */
		class Projectile
		{
			public :
				virtual ~Projectile() {}
				
				virtual float getVelocity()const=0 ;
				
				virtual float getPower()const=0 ;

				virtual const kn::Vector3f & getDirection()const=0;
				
				virtual const kn::Vector3f & getPosition()const=0;			
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

