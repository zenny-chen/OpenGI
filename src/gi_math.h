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
 *  \brief Declaration of simple mathematic helper functions.
 */

#ifndef __GI_MATH_H__
#define __GI_MATH_H__

#if HAVE_CONFIG_H
    #include <config.h>
#endif
#include <GI/gi.h>

#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <float.h>


/*************************************************************************/
/* Variables */

/* Vertices of platonic solids */
extern const GIfloat g_platonic_v[50][3];

/* Indices of platonic solids in array */
#define GI_TETRAHEDRON			0
#define GI_HEXAHEDRON			4
#define GI_OCTAHEDRON			12
#define GI_DODECAHEDRON			18
#define GI_ICOSAHEDRON			38

#define GI_INFN		            0x7F800000
#define GI_MAXN		            0x477FE000
#define GI_MINN		            0x38800000
#define GI_SIGNN		        0x80000000
#define GI_INFC		            0x0003FC00
#define GI_NANN		            0x7F802000
#define GI_MAXC		            0x00023BFF
#define GI_MINC		            0x0001C400
#define GI_SIGNC		        0x00008000
#define GI_MULN		            0x52000000
#define GI_MULC		            0x33800000
#define GI_SUBC		            0x000003FF
#define GI_NORC		            0x00000400
#define GI_MAXD		            0x0001C000
#define GI_MIND		            0x0001C000

/*************************************************************************/
/* Macros */

/** \internal
 *  \brief Constant Pi.
 *  \ingroup math
 */
#define GI_PI						3.1415926535897932

/** \internal
 *  \brief Constant 2 * Pi.
 *  \ingroup math
 */
#define GI_TWO_PI					6.2831853071795865

/** \internal
 *  \brief Constant Pi / 2.
 *  \ingroup math
 */
#define GI_HALF_PI					1.5707963267948966

/** \internal
 *  \brief Constant 1 / Pi.
 *  \ingroup math
 */
#define GI_INV_PI					0.3183098861837907

/** \internal
 *  \brief Constant 1 / (2*Pi).
 *  \ingroup math
 */
#define GI_INV_TWO_PI				0.1591549430918953

/** \internal
 *  \brief Constant 2 / Pi.
 *  \ingroup math
 */
#define GI_INV_HALF_PI				0.6366197723675813

/** \internal
 *  \brief Convert radians to degrees.
 *  \ingroup math
 */
#define GI_RAD_TO_DEG(a)			((a)*57.295779513082321)

/** \internal
 *  \brief Convert degrees to radians.
 *  \ingroup math
 */
#define GI_DEG_TO_RAD(a)			((a)*0.0174532925199432)

/** \internal
 *  \brief Minimum of two values.
 *  \ingroup math
 */
#define GI_MIN(a,b)					(((a)<(b)) ? (a) : (b))

/** \internal
 *  \brief Maximum of two values.
 *  \ingroup math
 */
#define GI_MAX(a,b)					(((a)<(b)) ? (b) : (a))

/** \internal
 *  \brief Sign of floating point number.
 *  \ingroup math
 */
#define GI_SIGN(a)					(((a)>=0.0) ? 1.0 : -1.0)

/** \internal
 *  \brief Round floating point number.
 *  \ingroup math
 */
#define GI_ROUND(a)					(((a)-floor(a))<0.5 ? floor(a) : ceil(a))

/** \internal
 *  \brief Clamp number.
 *  \ingroup math
 */
#define GI_CLAMP(x,a,b)				GI_MAX(a, GI_MIN(x, b))

/** \internal
 *  \brief Swap arbitrary variables.
 *  \ingroup math
 */
#define GI_SWAP(a,b,t)				(t)=(a); (a)=(b); (b)=(t)

/** \internal
 *  \brief Check if power of two.
 *  \ingroup math
 */
#define GI_POWER_OF_2(x)			(!((x)&((x)-1)))

/** \internal
 *  \brief Check if not a power of two.
 *  \ingroup math
 */
#define GI_NON_POWER_OF_2(x)		((x)&((x)-1))

/** \internal
 *  \brief Round to next power of two.
 *  \ingroup math
 */
#define GI_TO_UPPER_POWER_OF_2(x)	--(x); (x)|=(x)>>1; (x)|=(x)>>2; (x)|=(x)>>4; \
                                    (x)|=(x)>>8; (x)|=(x)>>16; ++(x)

/** \internal
 *  \brief Set 2D vector.
 *  \ingroup math
 */
#define GI_VEC2_SET(d,x,y)			(d)[0]=x; (d)[1]=y;

/** \internal
 *  \brief Copy 2D vector.
 *  \ingroup math
 */
#define GI_VEC2_COPY(d,s)			(d)[0]=(s)[0]; (d)[1]=(s)[1];

/** \internal
 *  \brief Compare 2D vectors.
 *  \ingroup math
 */
#define GI_VEC2_EQUAL(v,w)			((v)[0]==(w)[0] && (v)[1]==(w)[1])

/** \internal
 *  \brief Sum of 2D vectors.
 *  \ingroup math
 */
#define GI_VEC2_ADD(d,v,w)			(d)[0]=(v)[0]+(w)[0]; (d)[1]=(v)[1]+(w)[1];

/** \internal
 *  \brief Difference of 2D vectors.
 *  \ingroup math
 */
#define GI_VEC2_SUB(d,v,w)			(d)[0]=(v)[0]-(w)[0]; (d)[1]=(v)[1]-(w)[1];

/** \internal
 *  \brief Scale 2D vector.
 *  \ingroup math
 */
#define GI_VEC2_SCALE(d,v,s)		(d)[0]=(v)[0]*(s); (d)[1]=(v)[1]*(s)

/** \internal
 *  \brief Add scaled 2D vector to other vector.
 *  \ingroup math
 */
#define GI_VEC2_ADD_SCALED(d,v,w,s)	(d)[0]=(v)[0]+(w)[0]*(s); (d)[1]=(v)[1]+(w)[1]*(s);

/** \internal
 *  \brief Negate 2D vector.
 *  \ingroup math
 */
#define GI_VEC2_NEGATE(d, s)		(d)[0]=-(s)[0]; (d)[1]=-(s)[1]

/** \internal
 *  \brief Round 2D vector.
 *  \ingroup math
 */
#define GI_VEC2_ROUND(d, s)			(d)[0]=GI_ROUND((s)[0]); (d)[1]=GI_ROUND((s)[1])

/** \internal
 *  \brief Minimum of two 2D vectors.
 *  \ingroup math
 */
#define GI_VEC2_MIN(d,v,w)			(d)[0]=GI_MIN((v)[0],(w)[0]); (d)[1]=GI_MIN((v)[1],(w)[1])

/** \internal
 *  \brief Maximum of two 2D vectors.
 *  \ingroup math
 */
#define GI_VEC2_MAX(d,v,w)			(d)[0]=GI_MAX((v)[0],(w)[0]); (d)[1]=GI_MAX((v)[1],(w)[1])

/** \internal
 *  \brief Dot product of 2D vectors.
 *  \ingroup math
 */
#define GI_VEC2_DOT(v,w)			((v)[0]*(w)[0]+(v)[1]*(w)[1])

/** \internal
 *  \brief Length of 2D vector.
 *  \ingroup math
 */
#define GI_VEC2_LENGTH_SQR(v)		GI_VEC2_DOT(v,v)

/** \internal
 *  \brief Squared length of 2D vector.
 *  \ingroup math
 */
#define GI_VEC2_LENGTH(v)			sqrt(GI_VEC2_DOT(v,v))

/** \internal
 *  \brief Cross product equivalent of 2D vectors
 *  \ingroup math
 */
#define GI_VEC2_DET(v,w)			((v)[0]*(w)[1]-(v)[1]*(w)[0])

/** \internal
 *  \brief Set 3D vector.
 *  \ingroup math
 */
#define GI_VEC3_SET(d,x,y,z)		(d)[0]=x; (d)[1]=y; (d)[2]=z

/** \internal
 *  \brief Copy 3D vector.
 *  \ingroup math
 */
#define GI_VEC3_COPY(d,s)			(d)[0]=(s)[0]; (d)[1]=(s)[1]; (d)[2]=(s)[2]

/** \internal
 *  \brief Compare 3D vectors.
 *  \ingroup math
 */
#define GI_VEC3_EQUAL(v,w)			((v)[0]==(w)[0] && (v)[1]==(w)[1] && (v)[2]==(w)[2])

/** \internal
 *  \brief Sum of 3D vectors.
 *  \ingroup math
 */
#define GI_VEC3_ADD(d,v,w)			(d)[0]=(v)[0]+(w)[0]; (d)[1]=(v)[1]+(w)[1]; (d)[2]=(v)[2]+(w)[2]

/** \internal
 *  \brief Difference of 3D vectors.
 *  \ingroup math
 */
#define GI_VEC3_SUB(d,v,w)			(d)[0]=(v)[0]-(w)[0]; (d)[1]=(v)[1]-(w)[1]; (d)[2]=(v)[2]-(w)[2]

/** \internal
 *  \brief Scale 3D vector.
 *  \ingroup math
 */
#define GI_VEC3_SCALE(d,v,s)		(d)[0]=(v)[0]*(s); (d)[1]=(v)[1]*(s); (d)[2]=(v)[2]*(s)

/** \internal
 *  \brief Add scaled 3D vector to other vector.
 *  \ingroup math
 */
#define GI_VEC3_ADD_SCALED(d,v,w,s)	(d)[0]=(v)[0]+(w)[0]*(s); (d)[1]=(v)[1]+(w)[1]*(s); (d)[2]=(v)[2]+(w)[2]*(s);

/** \internal
 *  \brief Negate 3D vector.
 *  \ingroup math
 */
#define GI_VEC3_NEGATE(d, s)		(d)[0]=-(s)[0]; (d)[1]=-(s)[1]; (d)[2]=-(s)[2];

/** \internal
 *  \brief Round 3D vector.
 *  \ingroup math
 */
#define GI_VEC3_ROUND(d, s)			(d)[0]=GI_ROUND((s)[0]); (d)[1]=GI_ROUND((s)[1]); (d)[2]=GI_ROUND((s)[2])

/** \internal
 *  \brief Minimum of two 3D vectors.
 *  \ingroup math
 */
#define GI_VEC3_MIN(d,v,w)			(d)[0]=GI_MIN((v)[0],(w)[0]); \
                                    (d)[1]=GI_MIN((v)[1],(w)[1]); \
                                    (d)[2]=GI_MIN((v)[2],(w)[2])

/** \internal
 *  \brief Maximum of two 3D vectors.
 *  \ingroup math
 */
#define GI_VEC3_MAX(d,v,w)			(d)[0]=GI_MAX((v)[0],(w)[0]); \
                                    (d)[1]=GI_MAX((v)[1],(w)[1]); \
                                    (d)[2]=GI_MAX((v)[2],(w)[2])

/** \internal
 *  \brief Dot product of 3D vectors.
 *  \ingroup math
 */
#define GI_VEC3_DOT(v,w)			((v)[0]*(w)[0]+(v)[1]*(w)[1]+(v)[2]*(w)[2])

/** \internal
 *  \brief Length of 3D vector.
 *  \ingroup math
 */
#define GI_VEC3_LENGTH_SQR(v)		GI_VEC3_DOT(v,v)

/** \internal
 *  \brief Squared length of 3D vector.
 *  \ingroup math
 */
#define GI_VEC3_LENGTH(v)			sqrt(GI_VEC3_DOT(v,v))

/** \internal
 *  \brief Cross product of 3D vectors.
 *  \ingroup math
 */
#define GI_VEC3_CROSS(d,v,w)		(d)[0]=(v)[1]*(w)[2]-(v)[2]*(w)[1]; \
                                    (d)[1]=(v)[2]*(w)[0]-(v)[0]*(w)[2]; \
                                    (d)[2]=(v)[0]*(w)[1]-(v)[1]*(w)[0]


/*************************************************************************/
/* Functions */

/** \name Half precision floating point methods
 *  \{
 */

/** \internal
 *  \brief Convert float to half.
 *  \details http://stackoverflow.com/questions/1659440/32-bit-to-16-bit-floating-point-conversion
 *  \param value single precision floating point value
 *  \return half precision floating point value
 *  \ingroup math
*/
static inline GIhalf GIhalf_from_float(GIfloat value)
{
    GIint v = *(GIint*)&value, s = GI_MULN;
    GIuint sign = v & GI_SIGNN;
    v ^= sign;
    sign >>= 16;
    s = (*(GIfloat*)&s) * (*(GIfloat*)&v);
    v ^= (s ^ v) & -(GI_MINN > v);
    v ^= (GI_INFN ^ v) & -((GI_INFN > v) & (v > GI_MAXN));
    v ^= (GI_NANN ^ v) & -((GI_NANN > v) & (v > GI_INFN));
    *(GIuint*)&v >>= 13;
    v ^= ((v - GI_MAXD) ^ v) & -(v > GI_MAXC);
    v ^= ((v - GI_MIND) ^ v) & -(v > GI_SUBC);
    return *(GIuint*)&v | sign;
}

/** \internal
 *  \brief Convert half to float.
 *  \details http://stackoverflow.com/questions/1659440/32-bit-to-16-bit-floating-point-conversion
 *  \param value half precision floating point value
 *  \return single precision floating point value
 *  \ingroup math
 */
static inline GIfloat GIhalf_to_float(GIhalf value)
{
    GIint v = value, s = GI_MULC;
    GIint sign = v & GI_SIGNC, mask;
    v ^= sign;
    sign <<= 16;
    v ^= ((v + GI_MIND) ^ v) & -(v > GI_SUBC);
    v ^= ((v + GI_MAXD) ^ v) & -(v > GI_MAXC);
    *(GIfloat*)&s *= v;
    mask = -(GI_NORC > v);
    v <<= 13;
    v ^= (s ^ v) & mask;
    v |= sign;
    return *(GIfloat*)&v;
}
/** \} */

/** \name Single precision 2D vector methods
 *  \{
 */

/** \internal
 *  \brief Set 2D vector.
 *  \param d vector to set
 *  \param x x coordinate to set
 *  \param y y coordinate to set
 *  \ingroup math
 */
static inline void GIvec2f_set(GIfloat d[2], GIfloat x, GIfloat y)
{
    GI_VEC2_SET(d, x, y);
}

/** \internal
 *  \brief Copy 2D vector.
 *  \param d vector take copy
 *  \param s vector to copy from
 *  \ingroup math
 */
static inline void GIvec2f_copy(GIfloat d[2], const GIfloat s[2])
{
    GI_VEC2_COPY(d, s);
}

/** \internal
 *  \brief compare 2D vectors.
 *  \param v first vector
 *  \param w second vector
 *  \retval GI_TRUE if equal
 *  \retval GI_FALSE if not equal
 *  \ingroup math
 */
static inline GIboolean GIvec2f_equal(const GIfloat v[2], const GIfloat w[2])
{
    return GI_VEC2_EQUAL(v, w);
}

/** \internal
 *  \brief Sum of 2D vectors.
 *  \param d vector to store sum \a v + \a w
 *  \param v first vector
 *  \param w second vector
 *  \ingroup math
 */
static inline void GIvec2f_add(GIfloat d[2], const GIfloat v[2], const GIfloat w[2])
{
    GI_VEC2_ADD(d, v, w);
}

/** \internal
 *  \brief Difference of 2D vectors.
 *  \param d vector to store difference \a v - \a w
 *  \param v first vector
 *  \param w second vector
 *  \ingroup math
 */
static inline void GIvec2f_sub(GIfloat d[2], const GIfloat v[2], const GIfloat w[2])
{
    GI_VEC2_SUB(d, v, w);
}

/** \internal
 *  \brief Scale 2D vector.
 *  \param d vector to store scaled vector
 *  \param v vector to scale
 *  \param s scalar value
 *  \ingroup math
 */
static inline void GIvec2f_scale(GIfloat d[2], const GIfloat v[2], GIfloat s)
{
    GI_VEC2_SCALE(d, v, s);
}

/** \internal
 *  \brief Negate 2D vector.
 *  \param d vector to store negative vector
 *  \param s vector to negate
 *  \ingroup math
 */
static inline void GIvec2f_negate(GIfloat d[2], const GIfloat s[2])
{
    GI_VEC2_NEGATE(d, s);
}

/** \internal
 *  \brief Round 2D vector.
 *  \param d vector to store rounded vector
 *  \param s vector to round
 *  \ingroup math
 */
static inline void GIvec2f_round(GIfloat d[2], const GIfloat s[2])
{
    GI_VEC2_ROUND(d, s);
}

/** \internal
 *  \brief Component-wise minimum of two 2D vectors.
 *  \param d vector to store minimum vector
 *  \param v first vector
 *  \param w second vector
 *  \ingroup math
 */
static inline void GIvec2f_min(GIfloat d[2], const GIfloat v[2], const GIfloat w[2])
{
    GI_VEC2_MIN(d, v, w);
}

/** \internal
 *  \brief Component-wise maximum of two 2D vectors.
 *  \param d vector to store maximum vector
 *  \param v first vector
 *  \param w second vector
 *  \ingroup math
 */
static inline void GIvec2f_max(GIfloat d[2], const GIfloat v[2], const GIfloat w[2])
{
    GI_VEC2_MAX(d, v, w);
}

/** \internal
 *  \brief Length of 2D vector.
 *  \param v vector
 *  \return eucildean norm of vector sqrt(<\a v,\a v>)
 *  \ingroup math
 */
static inline GIfloat GIvec2f_length(const GIfloat v[2])
{
    return GI_VEC2_LENGTH(v);
}

/** \internal
 *  \brief Squared length of 2D vector.
 *  \param v vector
 *  \return squared euclidean norm of vector <\a v,\a v>
 *  \ingroup math
 */
static inline GIfloat GIvec2f_length_sqr(const GIfloat v[2])
{
    return GI_VEC2_LENGTH_SQR(v);
}

/** \internal
 *  \brief Distance between 2D vectors.
 *  \param v first vector
 *  \param w second vector
 *  \return euclidean distance between vectors
 *  \ingroup math
 */
static inline GIfloat GIvec2f_dist(const GIfloat v[2], const GIfloat w[2])
{
    GIfloat vec[2];
    GI_VEC2_SUB(vec, w, v);
    return GI_VEC2_LENGTH(vec);
}

/** \internal
 *  \brief Squared distance between 2D vectors.
 *  \param v first vector
 *  \param w second vector
 *  \return squared euclidean distance between vectors
 *  \ingroup math
 */
static inline GIfloat GIvec2f_dist_sqr(const GIfloat v[2], const GIfloat w[2])
{
    GIfloat vec[2];
    GI_VEC2_SUB(vec, w, v);
    return GI_VEC2_LENGTH_SQR(vec);
}

/** \internal
 *  \brief Normalize 2D vector.
 *  \param v vector to normalize
 *  \ingroup math
 */
static inline void GIvec2f_normalize(GIfloat v[2])
{
    GIfloat fInvNorm = 1.0f / GI_VEC2_LENGTH(v);
    v[0] *= fInvNorm; v[1] *= fInvNorm;
}

/** \internal
 *  \brief Dot product of 2D vectors.
 *  \param v first vector
 *  \param w second vector
 *  \return dot product <\a v,\a w>
 *  \ingroup math
 */
static inline GIfloat GIvec2f_dot(const GIfloat v[2], const GIfloat w[2])
{
    return GI_VEC2_DOT(v, w);
}

/** \internal
 *  \brief Cross product equivalent of 2D vectors.
 *  \param v first vector
 *  \param w second vector
 *  \return dot product det(\a v,\a w)
 *  \ingroup math
 */
static inline GIfloat GIvec2f_det(const GIfloat v[2], const GIfloat w[2])
{
    return GI_VEC2_DET(v, w);
}
/** \} */

/** \name Double precision 2D vector methods
 *  \{
 */

/** \internal
 *  \brief Set 2D vector.
 *  \param d vector to set
 *  \param x x coordinate to set
 *  \param y y coordinate to set
 *  \ingroup math
 */
static inline void GIvec2d_set(GIdouble d[2], GIdouble x, GIdouble y)
{
	GI_VEC2_SET(d, x, y);
}

/** \internal
 *  \brief Copy 2D vector.
 *  \param d vector take copy
 *  \param s vector to copy from
 *  \ingroup math
 */
static inline void GIvec2d_copy(GIdouble d[2], const GIdouble s[2])
{
    GI_VEC2_COPY(d, s);
}

/** \internal
 *  \brief compare 2D vectors.
 *  \param v first vector
 *  \param w second vector
 *  \retval GI_TRUE if equal
 *  \retval GI_FALSE if not equal
 *  \ingroup math
 */
static inline GIboolean GIvec2d_equal(const GIdouble v[2], const GIdouble w[2])
{
    return GI_VEC2_EQUAL(v, w);
}

/** \internal
 *  \brief Sum of 2D vectors.
 *  \param d vector to store sum \a v + \a w
 *  \param v first vector
 *  \param w second vector
 *  \ingroup math
 */
static inline void GIvec2d_add(GIdouble d[2], const GIdouble v[2], const GIdouble w[2])
{
    GI_VEC2_ADD(d, v, w);
}

/** \internal
 *  \brief Difference of 2D vectors.
 *  \param d vector to store difference \a v - \a w
 *  \param v first vector
 *  \param w second vector
 *  \ingroup math
 */
static inline void GIvec2d_sub(GIdouble d[2], const GIdouble v[2], const GIdouble w[2])
{
    GI_VEC2_SUB(d, v, w);
}

/** \internal
 *  \brief Scale 2D vector.
 *  \param d vector to store scaled vector
 *  \param v vector to scale
 *  \param s scalar value
 *  \ingroup math
 */
static inline void GIvec2d_scale(GIdouble d[2], const GIdouble v[2], GIdouble s)
{
    GI_VEC2_SCALE(d, v, s);
}

/** \internal
 *  \brief Add scaled 2D vector to other vector.
 *  \param d vector to store sum \a v + \a s*w
 *  \param v first vector
 *  \param w second vector (to be scaled)
 *  \param s scalar value
 *  \ingroup math
 */
static inline void GIvec2d_add_scaled(GIdouble d[2], const GIdouble v[2], const GIdouble w[2], GIdouble s)
{
    GI_VEC2_ADD_SCALED(d, v, w, s);
}

/** \internal
 *  \brief Negate 2D vector.
 *  \param d vector to store negative vector
 *  \param s vector to negate
 *  \ingroup math
 */
static inline void GIvec2d_negate(GIdouble d[2], const GIdouble s[2])
{
    GI_VEC2_NEGATE(d, s);
}

/** \internal
 *  \brief Round 2D vector.
 *  \param d vector to store rounded vector
 *  \param s vector to round
 *  \ingroup math
 */
static inline void GIvec2d_round(GIdouble d[2], const GIdouble s[2])
{
    GI_VEC2_ROUND(d, s);
}

/** \internal
 *  \brief Component-wise minimum of two 2D vectors.
 *  \param d vector to store minimum vector
 *  \param v first vector
 *  \param w second vector
 *  \ingroup math
 */
static inline void GIvec2d_min(GIdouble d[2], const GIdouble v[2], const GIdouble w[2])
{
    GI_VEC2_MIN(d, v, w);
}

/** \internal
 *  \brief Component-wise maximum of two 2D vectors.
 *  \param d vector to store maximum vector
 *  \param v first vector
 *  \param w second vector
 *  \ingroup math
 */
static inline void GIvec2d_max(GIdouble d[2], const GIdouble v[2], const GIdouble w[2])
{
    GI_VEC2_MAX(d, v, w);
}

/** \internal
 *  \brief Length of 2D vector.
 *  \param v vector
 *  \return eucildean norm of vector sqrt(<\a v,\a v>)
 *  \ingroup math
 */
static inline GIdouble GIvec2d_length(const GIdouble v[2])
{
    return GI_VEC2_LENGTH(v);
}

/** \internal
 *  \brief Squared length of 2D vector.
 *  \param v vector
 *  \return squared euclidean norm of vector <\a v,\a v>
 *  \ingroup math
 */
static inline GIdouble GIvec2d_length_sqr(const GIdouble v[2])
{
    return GI_VEC2_LENGTH_SQR(v);
}

/** \internal
 *  \brief Distance between 2D vectors.
 *  \param v first vector
 *  \param w second vector
 *  \return Euclidean distance between vectors
 *  \ingroup math
 */
static inline GIdouble GIvec2d_dist(const GIdouble v[2], const GIdouble w[2])
{
    GIdouble vec[2];
    GI_VEC2_SUB(vec, w, v);
    return GI_VEC2_LENGTH(vec);
}

/** \internal
 *  \brief Squared distance between 2D vectors.
 *  \param v first vector
 *  \param w second vector
 *  \return squared euclidean distance between vectors
 *  \ingroup math
 */
static inline GIdouble GIvec2d_dist_sqr(const GIdouble v[2], const GIdouble w[2])
{
    GIdouble vec[2];
    GI_VEC2_SUB(vec, w, v);
    return GI_VEC2_LENGTH_SQR(vec);
}

/** \internal
 *  \brief Normalize 2D vector.
 *  \param v vector to normalize
 *  \ingroup math
 */
static inline void GIvec2d_normalize(GIdouble v[2])
{
    GIdouble dInvNorm = 1.0f / GI_VEC2_LENGTH(v);
    v[0] *= dInvNorm; v[1] *= dInvNorm;
}

/** \internal
 *  \brief Dot product of 2D vectors.
 *  \param v first vector
 *  \param w second vector
 *  \return dot product <\a v,\a w>
 *  \ingroup math
 */
static inline GIdouble GIvec2d_dot(const GIdouble v[2], const GIdouble w[2])
{
    return GI_VEC2_DOT(v, w);
}

/** \internal
 *  \brief Cross product equivalent of 2D vectors.
 *  \param v first vector
 *  \param w second vector
 *  \return dot product det(\a v,\a w)
 *  \ingroup math
 */
static inline GIdouble GIvec2d_det(const GIdouble v[2], const GIdouble w[2])
{
    return GI_VEC2_DET(v, w);
}

/** \} */

/** \name Single precision 3D vector methods
 *  \{
 */

/** \internal
 *  \brief Set 3D vector.
 *  \param d vector to set
 *  \param x x coordinate to set
 *  \param y y coordinate to set
 *  \param z z coordinate to set
 *  \ingroup math
 */
static inline void GIvec3f_set(GIfloat d[3], GIfloat x, GIfloat y, GIfloat z)
{
    GI_VEC3_SET(d, x, y, z);
}

/** \internal
 *  \brief Copy 3D vector.
 *  \param d vector take copy
 *  \param s vector to copy from
 *  \ingroup math
 */
static inline void GIvec3f_copy(GIfloat d[3], const GIfloat s[3])
{
    GI_VEC3_COPY(d, s);
}

/** \internal
 *  \brief compare 3D vectors.
 *  \param v first vector
 *  \param w second vector
 *  \retval GI_TRUE if equal
 *  \retval GI_FALSE if not equal
 *  \ingroup math
 */
static inline GIboolean GIvec3f_equal(const GIfloat v[3], const GIfloat w[3])
{
    return GI_VEC3_EQUAL(v, w);
}

/** \internal
 *  \brief Sum of 3D vectors.
 *  \param d vector to store sum \a v + \a w
 *  \param v first vector
 *  \param w second vector
 *  \ingroup math
 */
static inline void GIvec3f_add(GIfloat d[3], const GIfloat v[3], const GIfloat w[3])
{
    GI_VEC3_ADD(d, v, w);
}

/** \internal
 *  \brief Difference of 3D vectors.
 *  \param d vector to store difference \a v - \a w
 *  \param v first vector
 *  \param w second vector
 *  \ingroup math
 */
static inline void GIvec3f_sub(GIfloat d[3], const GIfloat v[3], const GIfloat w[3])
{
    GI_VEC3_SUB(d, v, w);
}

/** \internal
 *  \brief Scale 3D vector.
 *  \param d vector to store scaled vector
 *  \param v vector to scale
 *  \param s scalar value
 *  \ingroup math
 */
static inline void GIvec3f_scale(GIfloat d[3], const GIfloat v[3], GIfloat s)
{
    GI_VEC3_SCALE(d, v, s);
}

/** \internal
 *  \brief Add scaled 3D vector to other vector.
 *  \param d vector to store sum \a v + \a s*w
 *  \param v first vector
 *  \param w second vector (to be scaled)
 *  \param s scalar value
 *  \ingroup math
 */
static inline void GIvec3f_add_scaled(GIfloat d[3], const GIfloat v[3], const GIfloat w[3], GIfloat s)
{
    GI_VEC3_ADD_SCALED(d, v, w, s);
}

/** \internal
 *  \brief Negate 3D vector.
 *  \param d vector to store negative vector
 *  \param s vector to negate
 *  \ingroup math
 */
static inline void GIvec3f_negate(GIfloat d[3], const GIfloat s[3])
{
    GI_VEC3_NEGATE(d, s);
}

/** \internal
 *  \brief Round 3D vector.
 *  \param d vector to store rounded vector
 *  \param s vector to round
 *  \ingroup math
 */
static inline void GIvec3f_round(GIfloat d[3], const GIfloat s[3])
{
    GI_VEC3_ROUND(d, s);
}

/** \internal
 *  \brief Component-wise minimum of two 3D vectors.
 *  \param d vector to store minimum vector
 *  \param v first vector
 *  \param w second vector
 *  \ingroup math
 */
static inline void GIvec3f_min(GIfloat d[3], const GIfloat v[3], const GIfloat w[3])
{
    GI_VEC3_MIN(d, v, w);
}

/** \internal
 *  \brief Component-wise maximum of two 3D vectors.
 *  \param d vector to store maximum vector
 *  \param v first vector
 *  \param w second vector
 *  \ingroup math
 */
static inline void GIvec3f_max(GIfloat d[3], const GIfloat v[3], const GIfloat w[3])
{
    GI_VEC3_MAX(d, v, w);
}

/** \internal
 *  \brief Length of 3D vector.
 *  \param v vector
 *  \return eucildean norm of vector sqrt(<\a v,\a v>)
 *  \ingroup math
 */
static inline GIfloat GIvec3f_length(const GIfloat v[3])
{
    return GI_VEC3_LENGTH(v);
}

/** \internal
 *  \brief Squared length of 3D vector.
 *  \param v vector
 *  \return squared euclidean norm of vector <\a v,\a v>
 *  \ingroup math
 */
static inline GIfloat GIvec3f_length_sqr(const GIfloat v[3])
{
    return GI_VEC3_LENGTH_SQR(v);
}

/** \internal
 *  \brief Distance between 3D vectors.
 *  \param v first vector
 *  \param w second vector
 *  \return Euclidean distance between vectors
 *  \ingroup math
 */
static inline GIfloat GIvec3f_dist(const GIfloat v[3], const GIfloat w[3])
{
    GIfloat vec[3];
    GI_VEC3_SUB(vec, w, v);
    return GI_VEC3_LENGTH(vec);
}

/** \internal
 *  \brief Squared distance between 3D vectors.
 *  \param v first vector
 *  \param w second vector
 *  \return squared euclidean distance between vectors
 *  \ingroup math
 */
static inline GIfloat GIvec3f_dist_sqr(const GIfloat v[3], const GIfloat w[3])
{
    GIfloat vec[3];
    GI_VEC3_SUB(vec, w, v);
    return GI_VEC3_LENGTH_SQR(vec);
}

/** \internal
 *  \brief Normalize 3D vector.
 *  \param v vector to normalize
 *  \ingroup math
 */
static inline void GIvec3f_normalize(GIfloat v[3])
{
    GIfloat fInvNorm = 1.0f / GI_VEC3_LENGTH(v);
    v[0] *= fInvNorm; v[1] *= fInvNorm; v[2] *= fInvNorm;
}

/** \internal
 *  \brief Dot product of 3D vectors.
 *  \param v first vector
 *  \param w second vector
 *  \return dot product <\a v,\a w>
 *  \ingroup math
 */
static inline GIfloat GIvec3f_dot(const GIfloat v[3], const GIfloat w[3])
{
    return GI_VEC3_DOT(v, w);
}

/** \internal
 *  \brief Cross product of 3D vectors.
 *  \param d vector to store cross product \a v x \a w
 *  \param v first vector
 *  \param w second vector
 *  \ingroup math
 */
static inline void GIvec3f_cross(GIfloat d[3], const GIfloat v[3], const GIfloat w[3])
{
    GI_VEC3_CROSS(d, v, w);
}

/** \{ */

/** \name Double precision 3D vector methods
 *  \{
 */

/** \internal
 *  \brief Set 3D vector.
 *  \param d vector to set
 *  \param x x coordinate to set
 *  \param y y coordinate to set
 *  \param z z coordinate to set
 *  \ingroup math
 */
static inline void GIvec3d_set(GIdouble d[3], GIdouble x, GIdouble y, GIdouble z)
{
	GI_VEC3_SET(d, x, y, z);
}

/** \internal
 *  \brief Copy 3D vector.
 *  \param d vector take copy
 *  \param s vector to copy from
 *  \ingroup math
 */
static inline void GIvec3d_copy(GIdouble d[3], const GIdouble s[3])
{
    GI_VEC3_COPY(d, s);
}

/** \internal
 *  \brief compare 3D vectors.
 *  \param v first vector
 *  \param w second vector
 *  \retval GI_TRUE if equal
 *  \retval GI_FALSE if not equal
 *  \ingroup math
 */
static inline GIboolean GIvec3d_equal(const GIdouble v[3], const GIdouble w[3])
{
    return GI_VEC3_EQUAL(v, w);
}

/** \internal
 *  \brief Sum of 3D vectors.
 *  \param d vector to store sum \a v + \a w
 *  \param v first vector
 *  \param w second vector
 *  \ingroup math
 */
static inline void GIvec3d_add(GIdouble d[3], const GIdouble v[3], const GIdouble w[3])
{
    GI_VEC3_ADD(d, v, w);
}

/** \internal
 *  \brief Difference of 3D vectors.
 *  \param d vector to store difference \a v - \a w
 *  \param v first vector
 *  \param w second vector
 *  \ingroup math
 */
static inline void GIvec3d_sub(GIdouble d[3], const GIdouble v[3], const GIdouble w[3])
{
    GI_VEC3_SUB(d, v, w);
}

/** \internal
 *  \brief Scale 3D vector.
 *  \param d vector to store scaled vector
 *  \param v vector to scale
 *  \param s scalar value
 *  \ingroup math
 */
static inline void GIvec3d_scale(GIdouble d[3], const GIdouble v[3], GIdouble s)
{
    GI_VEC3_SCALE(d, v, s);
}

/** \internal
 *  \brief Add scaled 3D vector to other vector.
 *  \param d vector to store sum \a v + \a s*w
 *  \param v first vector
 *  \param w second vector (to be scaled)
 *  \param s scalar value
 *  \ingroup math
 */
static inline void GIvec3d_add_scaled(GIdouble d[3], const GIdouble v[3], const GIdouble w[3], GIdouble s)
{
    GI_VEC3_ADD_SCALED(d, v, w, s);
}

/** \internal
 *  \brief Negate 3D vector.
 *  \param d vector to store negative vector
 *  \param s vector to negate
 *  \ingroup math
 */
static inline void GIvec3d_negate(GIdouble d[3], const GIdouble s[3])
{
    GI_VEC3_NEGATE(d, s);
}

/** \internal
 *  \brief Round 3D vector.
 *  \param d vector to store rounded vector
 *  \param s vector to round
 *  \ingroup math
 */
static inline void GIvec3d_round(GIdouble d[3], const GIdouble s[3])
{
    GI_VEC3_ROUND(d, s);
}

/** \internal
 *  \brief Component-wise minimum of two 3D vectors.
 *  \param d vector to store minimum vector
 *  \param v first vector
 *  \param w second vector
 *  \ingroup math
 */
static inline void GIvec3d_min(GIdouble d[3], const GIdouble v[3], const GIdouble w[3])
{
    GI_VEC3_MIN(d, v, w);
}

/** \internal
 *  \brief Component-wise maximum of two 3D vectors.
 *  \param d vector to store maximum vector
 *  \param v first vector
 *  \param w second vector
 *  \ingroup math
 */
static inline void GIvec3d_max(GIdouble d[3], const GIdouble v[3], const GIdouble w[3])
{
    GI_VEC3_MAX(d, v, w);
}

/** \internal
 *  \brief Length of 3D vector.
 *  \param v vector
 *  \return eucildean norm of vector sqrt(<\a v,\a v>)
 *  \ingroup math
 */
static inline GIdouble GIvec3d_length(const GIdouble v[3])
{
    return GI_VEC3_LENGTH(v);
}

/** \internal
 *  \brief Squared length of 3D vector.
 *  \param v vector
 *  \return squared euclidean norm of vector <\a v,\a v>
 *  \ingroup math
 */
static inline GIdouble GIvec3d_length_sqr(const GIdouble v[3])
{
    return GI_VEC3_LENGTH_SQR(v);
}

/** \internal
 *  \brief Distance between 3D vectors.
 *  \param v first vector
 *  \param w second vector
 *  \return Euclidean distance between vectors
 *  \ingroup math
 */
static inline GIdouble GIvec3d_dist(const GIdouble v[3], const GIdouble w[3])
{
    GIdouble vec[3];
    GI_VEC3_SUB(vec, w, v);
    return GI_VEC3_LENGTH(vec);
}

/** \internal
 *  \brief Squared distance between 3D vectors.
 *  \param v first vector
 *  \param w second vector
 *  \return squared euclidean distance between vectors
 *  \ingroup math
 */
static inline GIdouble GIvec3d_dist_sqr(const GIdouble v[3], const GIdouble w[3])
{
    GIdouble vec[3];
    GI_VEC3_SUB(vec, w, v);
    return GI_VEC3_LENGTH_SQR(vec);
}

/** \internal
 *  \brief Normalize 3D vector.
 *  \param v vector to normalize
 *  \ingroup math
 */
static inline void GIvec3d_normalize(GIdouble v[3])
{
    GIdouble dInvNorm = 1.0f / GI_VEC3_LENGTH(v);
    v[0] *= dInvNorm; v[1] *= dInvNorm; v[2] *= dInvNorm;
}

/** \internal
 *  \brief Dot product of 3D vectors.
 *  \param v first vector
 *  \param w second vector
 *  \return dot product <\a v,\a w>
 *  \ingroup math
 */
static inline GIdouble GIvec3d_dot(const GIdouble v[3], const GIdouble w[3])
{
    return GI_VEC3_DOT(v, w);
}

/** \internal
 *  \brief Cross product of 3D vectors.
 *  \param d vector to store cross product \a v x \a w
 *  \param v first vector
 *  \param w second vector
 *  \ingroup math
 */
static inline void GIvec3d_cross(GIdouble d[3], const GIdouble v[3], const GIdouble w[3])
{
    GI_VEC3_CROSS(d, v, w);
}

/** \{ */

#endif

