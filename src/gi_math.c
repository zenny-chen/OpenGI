/*
 *  OpenGI: Library for Parameterization and Geometry Image creation
 *  Copyright (C) 2008-2011  Christian Rau
 *
 *  This library is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published 
 *  by the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with this library. If not, see <http://www.gnu.org/licenses/>.
 *
 *  If you modify this software, you should include a notice giving the
 *  name of the person performing the modification, the date of modification,
 *  and the reason for such modification.
 *
 *  Contact: Christian Rau
 *
 *     rauy@users.sourceforge.net
 */

/** \internal
 *  \file
 *  \brief Implementation of simple mathematic helper functions.
 */

#include "gi_math.h"

/** \internal
 *  \brief Vertices of platonic solids.
 *  \ingroup math
 */
const GIfloat g_platonic_v[50][3] = 
{
	{ 0.0f, 0.0f, 1.0f }, { 0.942809f, 0, -0.333333f }, 
	{ -0.471405f, 0.816497f, -0.333333 }, { -0.471405f, -0.816497f, -0.333333 }, 

	{ -0.57735f, -0.57735f, -0.57735f }, { 0.57735f, -0.57735f, -0.57735f }, 
	{ 0.57735f, 0.57735f, -0.57735f }, { -0.57735f, 0.57735f, -0.57735f }, 
	{ -0.57735f, -0.57735f, 0.57735f }, { 0.57735f, -0.57735f, 0.57735f }, 
	{ 0.57735f, 0.57735f, 0.57735f }, { -0.57735f, 0.57735f, 0.57735f }, 

	{ 1.0f, 0.0f, 0.0f }, { -1.0f, 0.0f, 0.0f }, 
	{ 0.0f, 1.0f, 0.0f }, { 0.0f, -1.0f, 0.0f }, 
	{ 0.0f, 0.0f, 1.0f }, { 0.0f, 0.0f, -1.0f }, 

	{ 0.57735f, 0.57735f, 0.57735f }, { 0.57735f, 0.57735f, -0.57735f }, 
	{ 0.57735f, -0.57735f, 0.57735f }, { 0.57735f, -0.57735f, -0.57735f }, 
	{ -0.57735f, 0.57735f, 0.57735f }, { -0.57735f, 0.57735f, -0.57735f }, 
	{ -0.57735f, -0.57735f, 0.57735f }, { -0.57735f, -0.57735f, -0.57735f }, 
	{ 0.356822f, 0.934172, 0.0f }, { -0.356822f, 0.934172, 0.0f }, 
	{ 0.356822f, -0.934172, 0.0f }, { -0.356822f, -0.934172, 0.0f }, 
	{ 0.934172, 0.0f, 0.356822f }, { 0.934172, 0.0f, -0.356822f }, 
	{ -0.934172, 0.0f, 0.356822f }, { -0.934172, 0.0f, -0.356822f }, 
	{ 0.0f, 0.356822f, 0.934172 }, { 0.0f, -0.356822f, 0.934172 }, 
	{ 0.0f, 0.356822f, -0.934172 }, { 0.0f, -0.356822f, -0.934172 }, 

	{ 0.85065f, 0.525731f, 0.0f }, { -0.85065f, 0.525731f, 0.0f }, 
	{ 0.85065f, -0.525731f, 0.0f }, { -0.85065f, -0.525731f, 0.0f }, 
	{ 0.525731f, 0.0f, 0.85065f }, { 0.525731f, 0.0f, -0.85065f }, 
	{ -0.525731f, 0.0f, 0.85065f }, { -0.525731f, 0.0f, -0.85065f }, 
	{ 0.0f, 0.85065f, 0.525731f }, { 0.0f, -0.85065f, 0.525731f }, 
	{ 0.0f, 0.85065f, -0.525731f }, { 0.0f, -0.85065f, -0.525731f }, 
};

