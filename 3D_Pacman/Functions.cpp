#include "Functions.h"

vf origin;
color4 red, blue, green, yellow, purple, pink, white, black, grey, navyblue;

GLuint texture[10];
GLUquadricObj *quadratic;	// Storage For Our Quadratic Objects
GLUquadric *sphere;

bool fraudEnv;

GLuint g_cubemap; 

GLuint CubeMapDefines[6] = {

GL_TEXTURE_CUBE_MAP_POSITIVE_X_ARB,
GL_TEXTURE_CUBE_MAP_NEGATIVE_X_ARB,
GL_TEXTURE_CUBE_MAP_POSITIVE_Y_ARB,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Y_ARB,
GL_TEXTURE_CUBE_MAP_POSITIVE_Z_ARB,
GL_TEXTURE_CUBE_MAP_NEGATIVE_Z_ARB
};

float CubeMapRots[6][4] = {			//4, cos it's angle, then XYZ component of that angle.
	{	-90.0f,		0.0f,	1.0f,	0.0f	},
	{	90.0f,		0.0f,	1.0f,	0.0f	},

	{	-90.0f,		1.0f,	0.0f,	0.0f	},
	{	90.0f,		1.0f,	0.0f,	0.0f	},

	{	180.0f,		1.0f,	0.0f,	0.0f	},
	{	180.0f,		0.0f,	0.0f,	1.0f	},
};

color4::color4(){
	this->init(0.,0.,0.,1.,1.);
}

color4::color4(float r, float g, float b, float a, float max){
	this->init(r,g,b,a,max);
}

color4::~color4(){
}

void color4::init(float r, float g, float b, float a, float max){
	this->r = r/max, this->g = g/max, this->b = b/max, this->a = a/max;
}

int random (int low, int high) {
	srand(time(0)*rand());
    if (low > high) return high;
    return low + (std::rand() % (high - low + 1));
}

bool fInit(){
	for (int i = 0; i < 3; i++)
		origin.push_back(0.f);
	red		= color4(1.f,0.f,0.f);
	green	= color4(0.f,1.f,0.f);
	blue	= color4(0.f,0.f,1.f);
	yellow	= color4(1.f,1.f,0.f);
	purple	= color4(160.f,  32.f,	240.f,  255.f,  255.f);
	pink	= color4(255.f, 105.f,	180.f,  255.f,  255.f); 
	grey	= color4(105.f, 105.f,	105.f,  255.f,  255.f);
	navyblue= color4(0.f,	0.f,	128.f,	255.f,	255.f);
	white	= color4(1.f,1.f,1.f);
	black   = color4(0.f,0.f,0.f);
	return true;
}

void newl(){
	cout<<endl;
}

void DrawEllipsoid(float fA, float fB, float fC, unsigned int uiStacks, unsigned int uiSlices){
	float tStep = (PI) / (float)uiSlices;
	float sStep = (PI) / (float)uiStacks;
	for(float t = -PI/2; t <= (PI/2)+.0001; t += tStep){
		glBegin(GL_TRIANGLE_STRIP);
		for(float s = -PI; s <= PI+.0001; s += sStep){
			glVertex3f(fA * cos(t) * cos(s), fB * cos(t) * sin(s), fC * sin(t));
			glVertex3f(fA * cos(t+tStep) * cos(s), fB * cos(t+tStep) * sin(s), fC * sin(t+tStep));
		}
		glEnd();
	}
}

bool IsExtensionSupported(const char *const _string){
	const char
		*ptr, *src_ptr;

	bool
		found = FALSE;

	src_ptr = (const char*) glGetString(GL_EXTENSIONS);
	
	while((ptr = strchr((const char*) src_ptr, 'G')) != NULL)
	{
		if(strncmp(_string, ptr, strlen(_string)) == 0)
		{
			found = TRUE;
			break;
		}
		else
		{
			src_ptr = ptr+1;
		}
	}

	return found;
}

void RenderSphere(void){
	//Disable cube maps, so 2D textures take over.
	glDisable(GL_TEXTURE_CUBE_MAP_ARB);	

	//Enable some auto texture coords.
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

	//Draw sphere.
	gluSphere(sphere, 2.0f, 32, 32);


	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);	
}
