//*********************************************************************************
//	
//	Module :	hl_core.h
//	
//	Purpose :	
//	
//	Last Modified $Date: $
//	
//	$Revision: $
//	
//	Copyright (C) 24/03/01 Richard A. Nutman
//	
//	Author :  Nutty
//	
//*********************************************************************************

#ifndef _HL_CORE_H_
#define _HL_CORE_H_

//*********************************************************************************
//	Include Files
//*********************************************************************************

#ifndef _WINDOWS_
#include <windows.h>
#endif	//_WINDOWS_

#ifndef _HL_TYPES_H_
#include "hl_types.h"
#endif


//*********************************************************************************
//	Macros
//*********************************************************************************

//*********************************************************************************
//	Types
//*********************************************************************************

//This structure must be filled out entirely, and passed to helios to initialize itself.
typedef struct
{
	//Helios memory management.
	bool	f_AllocateMemory;			//True if helios should allocate it's own memory.
	void*	f_UserMemory;				//IF above false, use this pointer as helio's memory.
	u32		f_MemorySize;				//Tells helios how much memory to use, or how big the given array is.






}S_HeliosInitStruct;


//This structure holds the information about how the window should be.
typedef struct
{
	u32		f_WindowWidth;				//In pixels.
	u32		f_WindowHeight;				//"    "

	s32		f_WindowPosX;				//Window position on screen. Ignored if fullscreen.
	s32		f_WindowPosY;				

	u32		f_ColorDepth;				//In bits per pixels.
	u32		f_ZBufferDepth;				//Zbuffer size.
	u32		f_StencilDepth;				//Stencil buffer size.
	u32		f_DestAlphaDepth;			//Destination alpha depth.

	f32		f_WindowFOV;				//Field of view, in degrees.

	bool	f_Fullscreen;				//True for fullscreen mode.

	bool	f_SizableWindow;			//If true, window can be resized.

}S_HeliosWindowStruct;


enum EMouseButtons
{
	LEFT_BUTTON_DOWN = 1,
	RIGHT_BUTTON_DOWN = 2
};


typedef void (*S_HeliosWindowResizeCB)(const u32 width, const u32 height);


//*********************************************************************************
//	Constants
//*********************************************************************************

//*********************************************************************************
//	Classes
//*********************************************************************************

//*********************************************************************************
//	
//*********************************************************************************

class C_HeliosApp
{
//*********************************************************************************
//	Types
//*********************************************************************************
protected:

	

//*********************************************************************************
//	Constructors / Destructor
//*********************************************************************************
public:

	C_HeliosApp()			{}
	~C_HeliosApp();



//*********************************************************************************
//	Accessors
//*********************************************************************************
public:


	/*	This function initializes the helios engine. Sets all customizable settings.
	*/
	s32	Initialize(const S_HeliosInitStruct *const info);


	/*	Closes the render window if open, and does a heap release, effectivly auto deleting
		everything!
	*/
	s32	Shutdown(void);


	/*	Opens Helios' Render window. Only 1 window allowed. If the settings for the window need to change.
		Close, then reopen the window with new settings. N.B.!!! A ReleaseAllObjects is performed, so you will need
		to reload everything. This is so optimizations to data can be done, with the display settings known.
	*/
	s32	OpenWindow(const S_HeliosWindowStruct *const info);


	/*	Closes the Helios render window. Does not terminate the engine. 
	*/
	void CloseWindow(void);

	

	/*	This function makes helios lose all objects! 3D, 2D, textures.. everything. Basically does
		a heap reset!  Controversial method. No de-allocation occurs.. Helios just resets it's own heap, and
		Then on reloading, just overwrites all previous stuff. It works! Honest!

		For example, in a game.. call this between frontend and maingame, and at end of maingame, back into frontend.
		That will remove all frontend stuff, ready to load the game up.. then when going back to frontend, call this again
		to release everything ready to load the frontend up.
	*/
	void ReleaseAllObjects(void);


	//returns 0, if windows has requested a shutdown.
	s32 UpdateSystem(void);


	void StartRender(void);


	void FlipBuffers(void);

	bool IsAppActive(void)	{	return m_active;	}



	//Query stuff!
	f32 GetDeltaFrameTime(void) const;
	void ResetFrameTimers(void);
	u32 GetNumberTextureUnits(void) const;
	void GetWindowSize(u32 &width, u32 &height) const;


	//Interaction stuff!
	bool GetKey(const u8 key) const;					//Returns true if key is pressed.
	bool GetKeyDown(const u8 key) const;				//Returns true if key has just been pressed.
	bool GetKeyUp(const u8 key) const;					//Returns true if key has just been released.

	void GetMousePos(f32 &x_rot, f32 &y_rot) const;
	u32 GetMouseButtons(void) const;
	void SetGameMouse(const bool game_mouse);

	void SetGameMouseSpeed(const f32 speed);



	//Returns true if the extension specified exists.
	bool IsExtensionPresent(const s8 *const extension);


	//Give the engine a callback function to call when resizing. Dont call if not bothered.
	void SetWindowResizeCB(S_HeliosWindowResizeCB cb);
	

private:

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	void WindowInit(void);

	static void ResizeWindow(const u32 width, const u32 height);



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

	static HDC			m_hDC;				// Private GDI Device Context
	static HGLRC		m_hRC;				// Permanent Rendering Context
	static HWND			m_hWnd;				// Holds Our Window Handle
	static HINSTANCE	m_hInstance;		// Holds The Instance Of The Application

	static bool			m_active;			//Specifies weather app is active.


	static u8
		m_keys_held[256],
		m_keys_pressed[256],
		m_keys_released[256];

	//static bool			m_keys[256];		//List of key states.

	static S_HeliosWindowStruct	s_m_WindowInfo;


	LARGE_INTEGER 
		m_time,
		m_last_time, 
		m_diff,
		m_frequency;

	f32
		m_frame_time;			//In seconds!

	u32
		m_number_texture_units;

	f32
		m_mouse_speed,
		m_y_rot,
		m_x_rot;

	bool
		m_game_mouse;			//If true, then the mouse is used ALA 1st person shooter, and turned off!

	static u32
		m_mouse_buttons;

	static S_HeliosWindowResizeCB
		m_resize_cb;

};


//*********************************************************************************
//	Externs
//*********************************************************************************

//*********************************************************************************
//	Prototypes
//*********************************************************************************

#endif /* _HL_CORE_H_ */
