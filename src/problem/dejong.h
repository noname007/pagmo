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

#ifndef PAGMO_PROBLEM_DEJONG_H
#define PAGMO_PROBLEM_DEJONG_H

#include <string>

#include "../types.h"
#include "base.h"

namespace pagmo{ namespace problem {

/// The De Jong's problem.
/**
 * \image html dejong.gif "Two-dimensional De Jong's function."
 * \image latex dejong.gif "Two-dimensional De Jong's function." width=5cm
 *
 * This is a box-constrained continuous single-objecive problem.
 * The objective function is the  n-dimensional De Jong's function:
 * \f[
 * 	F \left(x_1,\ldots,x_n\right) = \sum_{i=1}^n sin(x_i) x_i^2, \quad x_i \in \left[ -5.12,5.12 \right].
 * \f]
 * Global local minimum \fx_i = 0\f.
 *
 * @see http://www.geatbx.com/docu/fcnindex-01.html#P89_3085
 * @author Andrea Mambrini (andrea.mambrini@gmail.com)
 */

class __PAGMO_VISIBLE dejong : public base
{
	public:
		dejong(int n);
		base_ptr clone() const;
		std::string get_name() const;
	protected:
		void objfun_impl(fitness_vector &, const decision_vector &) const;
	private:
};

}} //namespaces

#endif // PAGMO_PROBLEM_MICHALEWICZ_H
