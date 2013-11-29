//*********************************************************************************
//	
//	Module :	hl_vector3.h
//	
//	Purpose :	
//	
//	Last Modified $Date: $
//	
//	$Revision: $
//	
//	Copyright (C) 29-Mar-02 Richard A. Nutman
//	
//	Author :  Nutty
//	
//*********************************************************************************

#ifndef _HL_VECTOR3_H_
#define _HL_VECTOR3_H_

//*********************************************************************************
//	Include Files
//*********************************************************************************

#include "hl_types.h"

#include <math.h>

//*********************************************************************************
//	Macros
//*********************************************************************************

//*********************************************************************************
//	Types
//*********************************************************************************

//*********************************************************************************
//	Constants
//*********************************************************************************

//*********************************************************************************
//	Classes
//*********************************************************************************

//*********************************************************************************
//	
//*********************************************************************************

class C_Vector3
{
//*********************************************************************************
//	Types
//*********************************************************************************
protected:

//*********************************************************************************
//	Constructors / Destructor
//*********************************************************************************
public:

	C_Vector3(void)
	{}

	C_Vector3(const f32 v)
	{
		m_x = m_y = m_z = v;
	}	

	C_Vector3(const f32 x, const f32 y, const f32 z)
	{
		m_x = x;	m_y = y;	m_z = z;
	}

	C_Vector3(const C_Vector3 &vec)
	{
		m_x = vec.m_x;	m_y = vec.m_y;	m_z = vec.m_z;
	}

	C_Vector3(const C_Vector3 *const vec)
	{
		m_x = vec->m_x;		m_y = vec->m_y;		m_z = vec->m_z;
	}

	C_Vector3(const f32 *ptr)
	{
		m_x = *(ptr++);
		m_y = *(ptr++);
		m_z = *ptr;
	}

	C_Vector3(const C_Vector3 &u, const C_Vector3 &v)
	{
		//Do cross product in constructor.
		this->Cross(u, v);
	}

	~C_Vector3()
	{}

//*********************************************************************************
//	Accessors
//*********************************************************************************
public:

	f32 Dot(const C_Vector3 &v)
	{
		return ((m_x * v.m_x) + (m_y * v.m_y) + (m_z * v.m_z));		
	}

	C_Vector3& Cross(const C_Vector3 &v)
	{
		const C_Vector3
			u = *this;

		this->Cross(u, v);

		return *this;
	}

	C_Vector3& Cross(const C_Vector3 &u, const C_Vector3 &v)
	{
		m_x = (u.m_y * v.m_z) - (u.m_z * v.m_y);
		m_y = (u.m_x * v.m_z) - (u.m_z * v.m_x);
		m_z = (u.m_x * v.m_y) - (u.m_y * v.m_x);

		return *this;
	}

	f32 Length(void)
	{
		const f32
			mag = (m_x * m_x) + (m_y * m_y) + (m_z * m_z);

		return sqrtf(mag);
	}

	f32 SqLength(void)
	{
		return ((m_x * m_x) + (m_y * m_y) + (m_z * m_z));
	}


	void Normalize(void)
	{
		const f32
			scale = 1.0f / Length();

		m_x *= scale;
		m_y *= scale;
		m_z *= scale;
	}

//*********************************************************************************
//	Operators
//*********************************************************************************
public:

	C_Vector3& operator =(const C_Vector3 &rhs)
	{
		m_x = rhs.m_x;
		m_y = rhs.m_y;
		m_z = rhs.m_z;

		return *this;
	}


	C_Vector3 operator +(const C_Vector3 &rhs)
	{
		C_Vector3
			d;

		d.m_x += rhs.m_x;
		d.m_y += rhs.m_y;
		d.m_z += rhs.m_z;

		return d;
	}

	C_Vector3 operator -(const C_Vector3 &rhs)
	{
		C_Vector3
			d;

		d.m_x -= rhs.m_x;
		d.m_y -= rhs.m_y;
		d.m_z -= rhs.m_z;

		return d;
	}

	C_Vector3 operator *(const f32 v)
	{
		C_Vector3
			d;

		d.m_x *= v;
		d.m_y *= v;
		d.m_z *= v;

		return d;
	}

	C_Vector3 operator *(const C_Vector3 &v)
	{
		C_Vector3
			d;

		d.m_x *= v.m_x;
		d.m_y *= v.m_y;
		d.m_z *= v.m_z;

		return d;
	}

	C_Vector3 operator /(const f32 v)
	{
		C_Vector3
			d;

		d.m_x /= v;
		d.m_y /= v;
		d.m_z /= v;

		return d;
	}

	C_Vector3 operator /(const C_Vector3 &v)
	{
		C_Vector3
			d;

		d.m_x /= v.m_x;
		d.m_y /= v.m_y;
		d.m_z /= v.m_z;

		return d;
	}

	
	//Joint mathematical and assignment.
	C_Vector3& operator += (const C_Vector3 &rhs)
	{
		m_x += rhs.m_x;
		m_y += rhs.m_y;
		m_z += rhs.m_z;

		return *this;
	}


	C_Vector3& operator -= (const C_Vector3 &rhs)
	{
		m_x -= rhs.m_x;
		m_y -= rhs.m_y;
		m_z -= rhs.m_z;

		return *this;
	}

	C_Vector3& operator *= (const C_Vector3 &rhs)
	{
		m_x *= rhs.m_x;
		m_y *= rhs.m_y;
		m_z *= rhs.m_z;

		return *this;
	}

	C_Vector3& operator *= (const float v)
	{
		m_x *= v;
		m_y *= v;
		m_z *= v;

		return *this;
	}

	C_Vector3& operator /= (const C_Vector3 &rhs)
	{
		m_x /= rhs.m_x;
		m_y /= rhs.m_y;
		m_z /= rhs.m_z;

		return *this;
	}

	C_Vector3& operator /= (const float v)
	{
		m_x /= v;
		m_y /= v;
		m_z /= v;

		return *this;
	}






//*********************************************************************************
//	Helper Functions
//*********************************************************************************
public:

//*********************************************************************************
//	Constants
//*********************************************************************************
public:

//*********************************************************************************
//	Data Members
//*********************************************************************************
public:

	f32		m_x, m_y, m_z;


};


//*********************************************************************************
//	Externs
//*********************************************************************************

//*********************************************************************************
//	Prototypes
//*********************************************************************************

#endif /* _HL_VECTOR3_H_ */
