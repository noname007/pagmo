/*****************************************************************************
 *   Copyright (C) 2004-2009 The PaGMO development team,                     *
 *   Advanced Concepts Team (ACT), European Space Agency (ESA)               *
 *   http://apps.sourceforge.net/mediawiki/pagmo                             *
 *   http://apps.sourceforge.net/mediawiki/pagmo/index.php?title=Developers  *
 *   http://apps.sourceforge.net/mediawiki/pagmo/index.php?title=Credits     *
 *   act@esa.int                                                             *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.               *
 *****************************************************************************/

#ifndef ASTEROID_GTOC5_H
#define ASTEROID_GTOC5_H

#include "../serialization.h"
#include "planet.h"

namespace kep_toolbox{

/// A GTOC5 asteroid
/**
 * This class derives from the planet class and allow to instantiate asteroids
 * from the Global Trajectory Optimization Competition (GTOC) 5th edition
 *
 * @see http://www.esa.int/gsp/ACT/mad/op/GTOC/index.htm
 * @author Dario Izzo (dario.izzo _AT_ googlemail.com)
 * @author Francesco Biscani (bluescarni@gmail.com)
 */

class asteroid_gtoc5 : public planet
{
public:
	/// Constructor
	/**
	 * Construct from a consecutive id from 1 to 7076 (Earth). The order is that of the original
	 * data file from Russio
	 * Asteroid: 1 - 7075
	 * Earth: 7076
	 * \param[in] name a string describing a planet
	 */
	asteroid_gtoc5(const int & = 7076);

	planet_ptr clone() const;
private:
	friend class boost::serialization::access;
	template <class Archive>
	void serialize(Archive &ar, const unsigned int)
	{
		ar & boost::serialization::base_object<planet>(*this);
	}
};


} /// End of namespace kep_toolbox

BOOST_CLASS_EXPORT(kep_toolbox::asteroid_gtoc5);

#endif //ASTEROID_GTOC5_H
