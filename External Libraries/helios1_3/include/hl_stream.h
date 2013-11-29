//*********************************************************************************
//	
//	Module :	hl_stream.h
//	
//	Purpose :	
//	
//	Last Modified $Date: $
//	
//	$Revision: $
//	
//	Copyright (C) 19-Dec-01 Richard A. Nutman
//	
//	Author :  Nutty
//	
//*********************************************************************************

#ifndef _HL_STREAM_H_
#define _HL_STREAM_H_

//*********************************************************************************
//	Include Files
//*********************************************************************************

#include "hl_types.h"

#include <fstream.h>


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

class C_FileStream
{
//*********************************************************************************
//	Types
//*********************************************************************************
public:

	enum E_OpenMode
	{
		E_OPEN_READING	= ios::in,
		E_OPEN_WRITING  = ios::out,
		E_OPEN_APPEND	= ios::app

	};

	enum E_AccessMode
	{
		E_TEXT,
		E_BINARY

	};

	enum E_SeekMode
	{
		E_SEEK_BEGINING	= ios::beg,
		E_SEEK_CURRENT		= ios::cur,
		E_SEEK_END			= ios::end
	};

//*********************************************************************************
//	Constructors / Destructor
//*********************************************************************************
public:

	C_FileStream();
	C_FileStream(const s8 *const filename, const E_OpenMode open_mode, const E_AccessMode access_mode);

	~C_FileStream()
	{}

//*********************************************************************************
//	Accessors
//*********************************************************************************
public:

	bool IsOpen(void) const;

	bool Open(const s8 *const filename, const E_OpenMode open_mode, const E_AccessMode access_mode);
	void Close(void);

	s32 Read(void *const dest, const u32 length);		//Read arbitrary data in bytes. Returns actual bytes read.

	s32 Write(const void *const src, const u32 length);

	void Seek(const E_SeekMode mode, const s32 offset);

	s32 Tell(void);


	//NOT IMPLEMENTED YET!

//	void SetCompressedStreamBuild(const bool build_compressed_stream);
//	void UseCompressedStream(const bool use_compressed_stream);


private:

//	static void AddDataToStream(void *const src, const u32 length);

//	static void FinishStream(void);


//*********************************************************************************
//	Operators
//*********************************************************************************
public:

	//Read operators on our types.
	friend C_FileStream& operator>>(C_FileStream &s, u8 &d);
	friend C_FileStream& operator>>(C_FileStream &s, s8 &d);
	friend C_FileStream& operator>>(C_FileStream &s, u16 &d);
	friend C_FileStream& operator>>(C_FileStream &s, s16 &d);
	friend C_FileStream& operator>>(C_FileStream &s, u32 &d);
	friend C_FileStream& operator>>(C_FileStream &s, s32 &d);
	friend C_FileStream& operator>>(C_FileStream &s, f32 &d);
	friend C_FileStream& operator>>(C_FileStream &s, f64 &d);

	//Write operators on out types. Writing accepts const vars!
	friend C_FileStream& operator<<(C_FileStream &s, const u8 &d);
	friend C_FileStream& operator<<(C_FileStream &s, const s8 &d);
	friend C_FileStream& operator<<(C_FileStream &s, const u16 &d);
	friend C_FileStream& operator<<(C_FileStream &s, const s16 &d);
	friend C_FileStream& operator<<(C_FileStream &s, const u32 &d);
	friend C_FileStream& operator<<(C_FileStream &s, const s32 &d);
	friend C_FileStream& operator<<(C_FileStream &s, const f32 &d);
	friend C_FileStream& operator<<(C_FileStream &s, const f64 &d);

	


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

	fstream
		m_stream;

//	bool
//		m_use_compressed_stream,
//		m_build_compressed_stream;

};


//*********************************************************************************
//	Externs
//*********************************************************************************

//*********************************************************************************
//	Prototypes
//*********************************************************************************

#endif /* _HL_STREAM_H_ */
