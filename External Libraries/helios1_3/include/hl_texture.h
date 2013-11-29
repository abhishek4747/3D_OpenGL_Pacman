//*********************************************************************************
//	
//	Module :	hl_texture.h
//	
//	Purpose :	
//	
//	Last Modified $Date: $
//	
//	$Revision: $
//	
//	Copyright (C) 11/08/01 Richard A. Nutman
//	
//	Author :  Nutty
//	
//*********************************************************************************

#ifndef _HL_TEXTURE_H_
#define _HL_TEXTURE_H_

//*********************************************************************************
//	Include Files
//*********************************************************************************

#ifndef _HL_CORE_H_
#include "hl_core.h"
#endif	//_HL_CORE_H_

#include <GL/gl.h>

//*********************************************************************************
//	Macros
//*********************************************************************************

//NEW DEFINES FOR CUBEMAPPING!
#define	GL_NORMAL_MAP_ARB						0x8511
#define	GL_REFLECTION_MAP_ARB					0x8512
#define	GL_TEXTURE_CUBE_MAP_ARB					0x8513
#define	GL_TEXTURE_BINDING_CUBE_MAP_ARB			0x8514
#define	GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB		0x8515
#define	GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB		0x8516
#define	GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB		0x8517
#define	GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB		0x8518
#define	GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB		0x8519
#define	GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB		0x851A
#define	GL_PROXY_TEXTURE_CUBE_MAP_ARB			0x851B
#define	GL_MAX_CUBE_MAP_TEXTURE_SIZE_ARB		0x851C

//The defines.
#define GL_TEXTURE0_ARB							0x84C0
#define GL_TEXTURE1_ARB							0x84C1
#define GL_TEXTURE2_ARB							0x84C2
#define GL_TEXTURE3_ARB							0x84C3
#define GL_MAX_TEXTURE_UNITS_ARB				0x84E2


#define GL_TEXTURE_WRAP_R						0x8072

#define GL_CLAMP_TO_EDGE_EXT					0x812F


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

class C_Texture
{
//*********************************************************************************
//	Types
//*********************************************************************************
protected:

//*********************************************************************************
//	Constructors / Destructor
//*********************************************************************************
public:

	//Create texture of no type.
	C_Texture();
	
	//Creates texture of type. No data yet.
	C_Texture(const GLenum target);			

	~C_Texture();

//*********************************************************************************
//	Accessors
//*********************************************************************************
public:

	//Sets the target type of the texture.
	bool SetTarget(const GLenum target);

	//Loads from filename.
	bool Load(const s8 *const filename, const GLenum internal_format);

	//Sets current texture state to this texture.
	void Bind(void) const;

	//Binds the texture to a specific texture unit. Current active texture unit after calling this,
	//Is the same as the texture unit parameter passed in.
	void Bind(const GLenum texture_unit) const;

	//Texture updating functions.
	bool Instantiate(const u32 width, const u32 height, const GLenum internal_format);

	//Updates from back buffer, glTexCopySubImage.
	bool Update(void);						//Uses current target.
	bool Update(const GLenum target);		//Target cubemap direction. etc..

	//Updates image of texture from arbitrary data.
	bool Update(const u8 *const image, const u32 width, const u32 height, const u32 depth);
	bool Update(const GLenum target, const u8 *const image, const u32 width, const u32 height, const u32 depth);

	void Delete(void);		//Deletes the texture from GL's system.

//*********************************************************************************
//	Operators
//*********************************************************************************
public:

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
private:


	GLenum
		m_internal_format;

	u32
		m_width,
		m_height,
		m_depth;

	u32
		m_id;

	GLenum
		m_target;

};


//*********************************************************************************
//	Externs
//*********************************************************************************

//*********************************************************************************
//	Prototypes
//*********************************************************************************

#endif /* _HL_TEXTURE_H_ */

