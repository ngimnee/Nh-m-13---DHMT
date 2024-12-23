/*========== FULL ==========*/
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

#include <glew.h>
#include <freeglut.h>

#include <Vector_Matrix.h>


using namespace std;

//Thêm tam giác màu
static const float coloredTriangle[] = {
	//position			//colors
	 1.0, -1.0,  0.0,	1.0, 0.0, 0.0,  //bottom right
	-1.0, -1.0,  0.0,	0.0, 1.0, 0.0,  //bottom left
	 0.0,  1.0,  0.0,	0.0, 0.0, 1.0   //top
};

typedef struct
{
	float xyzw[4];
	float normal[4];
} Vertex;

Vertex Vertices[] =
{
	// v0-v1-v2 (front)
	{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 0, 0, 1, 0 } },
	{ { -0.5f,	 0.5f,	0.5f, 1.0 },{ 0, 0, 1, 0 } },
	{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 0, 0, 1, 0 } },
	// v2-v3-v0
	{ { -0.5f,	-0.5f,	0.5f, 1.0 },{ 0, 0, 1, 0 } },
	{ {  0.5f,	-0.5f,	0.5f, 1.0 },{ 0, 0, 1, 0 } },
	{ {  0.5f,	 0.5f,	0.5f, 1.0 },{ 0, 0, 1, 0 } },

	// v0-v3-v4 (right)
	{ { 0.5f,	 0.5f,	 0.5f, 1.0 },{ 1, 0, 0, 0 } },
	{ { 0.5f,	-0.5f,   0.5f, 1.0 },{ 1, 0, 0, 0 } },
	{ { 0.5f,	-0.5f,  -0.5f, 1.0 },{ 1, 0, 0, 0 } },
	// v4-v5-v0
	{ { 0.5f,	-0.5f,	-0.5f, 1.0 },{ 1, 0, 0, 0 } },
	{ { 0.5f,	 0.5f,	-0.5f, 1.0 },{ 1, 0, 0, 0 } },
	{ { 0.5f,	 0.5f,   0.5f, 1.0 },{ 1, 0, 0, 0 } },

	// v0-v5-v6 (top)
	{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 0, 1, 0, 0 } },
	{ {  0.5f,	0.5f,	-0.5f, 1.0 },{ 0, 1, 0, 0 } },
	{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 0, 1, 0, 0 } },
	// v6-v1-v0
	{ { -0.5f,	0.5f,	-0.5f, 1.0 },{ 0, 1, 0, 0 } },
	{ { -0.5f,	0.5f,	 0.5f, 1.0 },{ 0, 1, 0, 0 } },
	{ {  0.5f,	0.5f,	 0.5f, 1.0 },{ 0, 1, 0, 0 } },

	// v1-v6-v7 (left)
	{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ -1, 0, 0, 0 } },
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ -1, 0, 0, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ -1, 0, 0, 0 } },
	// v7-v2-v1
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ -1, 0, 0, 0 } },
	{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ -1, 0, 0, 0 } },
	{ { -0.5f,	 0.5f,	 0.5f, 1.0 },{ -1, 0, 0, 0 } },

	// v7-v4-v3 (bottom)
	{ { -0.5f,	 -0.5f,	-0.5f, 1.0 },{ 0,-1, 0, 0 } },
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 0,-1, 0, 0 } },
	{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 0,-1, 0, 0 } },
	// v3-v2-v7
	{ {  0.5f,	-0.5f,	 0.5f, 1.0 },{ 0,-1, 0, 0 } },
	{ { -0.5f,	-0.5f,	 0.5f, 1.0 },{ 0,-1, 0, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 0,-1, 0, 0 } },

	// v4-v7-v6 (back)
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	{ { -0.5f,	-0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	// v6-v5-v4
	{ { -0.5f,	 0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	{ {  0.5f,	 0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } },
	{ {  0.5f,	-0.5f,	-0.5f, 1.0 },{ 0, 0,-1, 0 } }
};

const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t NormalOffset = sizeof(Vertices[0].xyzw);


//Định nghĩa stack cho ma trận
class MatrixStack {
	int    index;
	int    size;
	mat4* matrices;

public:
	MatrixStack(int numMatrices = 32) :index(0), size(numMatrices)
	{
		matrices = new mat4[numMatrices];
	}

	~MatrixStack()
	{
		delete[]matrices;
	}

	// phép toán đẩy vào
	mat4& push(const mat4& m) {
		assert(index + 1 < size);
		matrices[index++] = m;
		return matrices[index];
	}

	// phép toán lấy ra
	mat4& pop(void) {
		assert(index - 1 >= 0);
		index--;
		return matrices[index];
	}
};

MatrixStack  mvstack;

int CurrentWidth = 700,
CurrentHeight = 700;

GLuint
VaoId[2],
VboId[2],
VertexShaderId,
FragmentShaderId,
ProgramId;

mat4
model_mat_cpp,
view_mat_cpp,
projection_mat_cpp;

int
model_mat_location,
view_mat_location,
projection_mat_location;

//Dùng biến đổi mô hình
float
r[] = { 0.0f, 0.0f, 0.0f },
s[] = { 1.0f, 1.0f, 1.0f },
t[] = { 0.0f, 0.0f, 0.0f };

//Sử dụng cho camera
int midWindowX;
int midWindowY;


bool keys[256]; // Array to keep track of pressed keys
bool mouseLocked = true;
float yaw = 90.0f;
float pitch = 0.0f;

float cameraX = -7.0f;
float cameraY = 0.0f;
float cameraZ = -2.0f;
float moveSpeed = 0.5f;
float jumpSpeed = 0.2f;
float gravity = 0.010f;
bool isJumping = false;
bool isGrounded = true;

//Dùng kiểm tra tịnh tiến, quay, co giãn
bool
translated = false,
rotated = false,
scaled = false;

//===================== Khai báo các biến sử dụng để vẽ =========================//
float Alpha = 0.0f;

//Thiết lập chỉ mục cho menu
enum {
	windown1,
	windownJoint_z
};
GLfloat windown_rotate[windownJoint_z]{
	0.0//windown1

};
GLint rotate_windown = windown1;

enum {
	table0,
	Work_TableJointx,
	Quit
};
GLfloat work_tablex[Work_TableJointx] = {
	0.0
};
//doi tuong tinh tien
GLfloat work_chairx = 0.0;
GLfloat work_chairz = 0.0;

enum {
	ngankeo0,
	ngankeoJoint
};
GLfloat ngankeo_z[ngankeoJoint]{
	0.0 // ngan keo 0
};
GLint ngankeo = ngankeo0;

enum {
	tu1,
	tu2,
	canhtuJoint
};
GLfloat angle_canhtu[canhtuJoint] = {
	1, //tu 1
	1  //tu 2
};
GLint angle_tu_y = tu1;

//==================== Kết thúc khai báo các biến vẽ =========================//
// ------------------------------------------//
string ReadShaderSourceFile(string fileName) {
	fstream reader(fileName.c_str());
	string line;
	string code = "";
	while (getline(reader, line)) {
		code += line + "\n";
	}
	reader.close();
	return code;
}

//-------------------------------------------//
void CreatVaoVbo()
{
	// Tạo và liên kết VAO và VBO cho tam giác có màu
	glGenVertexArrays(2, &VaoId[0]);
	glGenBuffers(2, &VboId[0]);

	// Thiết lập VAO và VBO cho coloredTriangle
	glBindVertexArray(VaoId[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VboId[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(coloredTriangle), coloredTriangle, GL_DYNAMIC_DRAW);

	// Cấu hình thuộc tính đỉnh cho vị trí (3 float) và màu sắc (3 float)
	// Layout location 0 cho vertex_position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	// Layout location 1 cho vertex_color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

	// Bật các thuộc tính đỉnh
	glEnableVertexAttribArray(0); // Bật vertex_position
	glEnableVertexAttribArray(1); // Bật vertex_color

	// Thiết lập VAO và VBO cho mảng Vertices
	glBindVertexArray(VaoId[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VboId[1]);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

	// Cấu hình thuộc tính đỉnh cho vị trí và vector pháp tuyến
	// Layout location 0 cho vertex_position
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, (void*)0);
	// Layout location 2 cho vertex_normal
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)NormalOffset);

	// Bật thuộc tính đỉnh
	glEnableVertexAttribArray(0); // Bật vertex_position
	glEnableVertexAttribArray(2); // Bật vertex_normal

	// Bật kiểm tra độ sâu và ẩn con trỏ chuột
	glEnable(GL_DEPTH_TEST);
	glutSetCursor(GLUT_CURSOR_NONE);
}
//---------------------------------------------//
void CreatShaders()
{
	string vertexSrc = ReadShaderSourceFile("./vs.shader");
	string fragmentSrc = ReadShaderSourceFile("./fs.shader");

	const GLchar* VertexShader = vertexSrc.c_str();
	const GLchar* FragmentShader = fragmentSrc.c_str();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);
}
//--------------------------------------------//
void CloseFunc()
{
	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId[0]);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId[0]);
}
//--------------------------------------------------------//
//---------------------- Ánh sáng -----------------------//
#pragma region light
bool light1 = true, light2 = true;

void updateLightUniforms() {
	//light1 = 1; light2 = 1;
	glUniform1i(glGetUniformLocation(ProgramId, "enable_light_1"), light1 ? 0 : 1);
	glUniform1i(glGetUniformLocation(ProgramId, "enable_light_2"), light2 ? 1 : 0);
}

void onl1() {
	light1 = true;
	updateLightUniforms();
}

void offl1() {
	light1 = false;
	updateLightUniforms();
}

void onl2() {
	light2 = true;
	updateLightUniforms();
}

void offl2() {
	light2 = false;
	updateLightUniforms();
}
#pragma endregion
//===================================================== Tạo các đối tượng =========================================//
//-------------- Hàm gọi màu trong vs.shader ----------------------//
void setInt(const string& name, int value) {
	glUniform1i(glGetUniformLocation(ProgramId, name.c_str()), value);
}
//----------- Tạo khối hộp cube đơn vị ---------//
void cube()
{
	mvstack.push(model_mat_cpp);
	mat4 instance = identity_mat4();
	mat4 model_cube = model_mat_cpp * instance;
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_cube.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	model_mat_cpp = mvstack.pop();
}

//-------------ve phong lam viec-----------
#pragma region room and door
void room()
{

	mvstack.push(model_mat_cpp);
	// trần nhà
	//FillColor(lemon);
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0, 2.9, -3.5)) * scale(vec3(5.0, 0.01, 7.0));
	setInt("color", 14);
	cube();
	model_mat_cpp = mvstack.pop();

	// tường trái 
	mvstack.push(model_mat_cpp);
	setInt("color", 15);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0, 0.9, 0)) * scale(vec3(5.0, 4.0, 0.01));
	cube();
	model_mat_cpp = mvstack.pop();

	// sàn 
	mvstack.push(model_mat_cpp);
	setInt("color", 15);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0, -1.1, -3.5)) * scale(vec3(5.0, 0.01, 7.0));
	cube();
	model_mat_cpp = mvstack.pop();

	// mặt trước
	//mảnh tường to thứ nhất
	mvstack.push(model_mat_cpp);
	setInt("color", 15);
	model_mat_cpp = model_mat_cpp * translate(vec3(-2.5, 1.65, -3.5)) * scale(vec3(0.01, 2.5, 7.0));
	cube();
	model_mat_cpp = mvstack.pop();

	//mảnh tường nhỏ bên trái
	mvstack.push(model_mat_cpp);
	setInt("color", 15);
	model_mat_cpp = model_mat_cpp * translate(vec3(-2.5, -0.35, -0.5)) * scale(vec3(0.01, 1.5, 1));
	cube();
	model_mat_cpp = mvstack.pop();
	
	//mảnh tường nhỏ bên phải 
	mvstack.push(model_mat_cpp);
	setInt("color", 15);
	model_mat_cpp = model_mat_cpp * translate(vec3(-2.5, -0.35, -4.5)) * scale(vec3(0.01, 1.5, 5));
	cube();
	model_mat_cpp = mvstack.pop();

	model_mat_cpp = mvstack.pop();

	// mặt sau 
	mvstack.push(model_mat_cpp);
	setInt("color", 15);
	model_mat_cpp = model_mat_cpp * translate(vec3(2.5, 0.9, -3.5)) * scale(vec3(0.01, 4.0, 7.0));
	cube();
	model_mat_cpp = mvstack.pop();

	// tường phải 
//  mảnh tường to trên
	mvstack.push(model_mat_cpp);
	setInt("color", 15);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0, 2.15, -7)) * scale(vec3(5.0, 1.5, 0.01));
	cube();
	model_mat_cpp = mvstack.pop();
	//mảnh tường to dưới
	mvstack.push(model_mat_cpp);
	setInt("color", 15);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0,-0.35, -7)) * scale(vec3(5.0, 1.5, 0.01));
	cube();
	model_mat_cpp = mvstack.pop();
	//mảnh tường to trái
	mvstack.push(model_mat_cpp);
	setInt("color", 15);
	model_mat_cpp = model_mat_cpp * translate(vec3(1, 0.9, -7)) * scale(vec3(3, 1.0, 0.01));
	cube();
	model_mat_cpp = mvstack.pop();
	// mảnh tường nhỏ  phải
	mvstack.push(model_mat_cpp);
	setInt("color", 15);
	model_mat_cpp = model_mat_cpp * translate(vec3(-2, 0.9, -7)) * scale(vec3(1, 1.0, 0.01));
	cube();
	model_mat_cpp = mvstack.pop();
}

//------------cửa chính--------------
float door_angle = 0.0f;
void door() {
	mvstack.push(model_mat_cpp);
	// Xoay cánh cửa
	mvstack.push(model_mat_cpp);
	setInt("color", 18);
	model_mat_cpp = model_mat_cpp
		* translate(vec3(-2.5, -0.35, -1.5)) // Đặt cửa gần khung trái
		* translate(vec3(-0.025, 0.0, 0.5))   // Đưa về điểm xoay (bản lề)
		* rotate_y(door_angle)              // Xoay cửa quanh bản lề
		* translate(vec3(0.025, 0.0, -0.5))    // Đưa cửa về vị trí ban đầu
		* scale(vec3(0.05, 1.5, 1.0));      // Kích thước cửa (dày, cao, rộng)   
	cube();  // Vẽ cánh cửa
	model_mat_cpp = mvstack.pop();

	// Tay nắm cửa hình chữ nhật
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp
		* translate(vec3(-2.53, -0.3, -1)) // Đặt vị trí tay nắm trên cánh cửa
			* rotate_y(door_angle)              // Xoay cửa quanh bản lề
			* translate(vec3(0.01, 0.0, -0.4))   // Đưa về điểm xoay (bản lề)
			* translate(vec3(0.01, 0.0, -0.4))   // Đưa cửa về vị trí ban đầu
			* scale(vec3(0.14, 0.4, 0.05));      // Kích thước tay nắm hình chữ nhật (dài, rộng, dày)
	setInt("color", 2); // Tay nắm có màu khác
	cube();  // Vẽ tay nắm
	model_mat_cpp = mvstack.pop();

	// Khung cửa trái
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-2.5, -0.35, -1)) * scale(vec3(0.05, 1.5, 0.05));  // Khung trái, cao hơn cánh cửa
	setInt("color", 1);
	cube();
	model_mat_cpp = mvstack.pop();

	// Khung cửa phải
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-2.5, -0.35, -2)) * scale(vec3(0.05, 1.5, 0.05));  // Khung phải
	setInt("color", 1);
	cube();
	model_mat_cpp = mvstack.pop();

	// Khung cửa trên
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-2.5, 0.4, -1.5)) * scale(vec3(0.05, 0.05, 1.0)); // Khung trên
	setInt("color", 1);
	cube();
	model_mat_cpp = mvstack.pop();

	model_mat_cpp = mvstack.pop();
}
#pragma endregion

//---------ve window-------
#pragma region window
void windown(float tmp) {
	//khung tren
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(1.6, 0.275, -0.9)) * scale(vec3(1.05, 0.05, 0.05));
	setInt("color", 1);
	cube();
	//khung duoi
	model_mat_cpp = mvstack.pop();
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(1.6, -0.35, -0.9)) * scale(vec3(1.05, 0.05, 0.05));
	setInt("color", 1);
	cube();
	model_mat_cpp = mvstack.pop();
	//khung trai
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(2.1, -0.05, -0.9)) * scale(vec3(0.05, 0.65, 0.05));
	setInt("color", 1);
	cube();
	model_mat_cpp = mvstack.pop();
	//khung phai
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(1.05, -0.04, -0.9)) * scale(vec3(0.05, 0.67, 0.05));
	setInt("color", 1);
	cube();
	model_mat_cpp = mvstack.pop();

	//kinh
	mvstack.push(model_mat_cpp); 
	model_mat_cpp = model_mat_cpp
		* translate(vec3(1.58, -0.04, -0.9))   // Vị trí trung tâm giữa các khung
		* translate(vec3(0.0, 0.3, 0))
		* rotate_x(tmp)
		* translate(vec3(0.0, -0.3, 0))
		* scale(vec3(1.0, 0.6, 0.02));
	setInt("color", 9);
	cube();
	model_mat_cpp = mvstack.pop();

	//tay nam
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp
		* translate(vec3(1.55, 0.25, -0.89))
		* rotate_x(tmp)
		* translate(vec3(0.0, -0.25, 0.0))
		* translate(vec3(0.0, -0.15, 0.0))
		* scale(vec3(0.1, 0.02, 0.02));
	setInt("color", 1);
	cube();
	model_mat_cpp = mvstack.pop();

}
void windowns(float tx, float ty, float tz, float sx, float sy, float sz, float tmp, int j) {

	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(tx, ty, tz)) * scale(vec3(sx, sy, sz)) * rotate_y(360 / j);
	windown(tmp);
	model_mat_cpp = mvstack.pop();
}
#pragma endregion

//-----------------ve camera-------------
#pragma region camera
bool switch_camera = true;
float camera_angle = 0.0f;
float camera_direction = 1.0f;
void camera() {
	mvstack.push(model_mat_cpp);

	// Base
	mvstack.push(model_mat_cpp);
	setInt("color", 99);
	model_mat_cpp = model_mat_cpp * scale(vec3(0.03, 0.03, 0.12));
	cube();
	model_mat_cpp = mvstack.pop();
	// camera
	mvstack.push(model_mat_cpp);
	setInt("color", 2);
	model_mat_cpp = model_mat_cpp * rotate_y(camera_angle) * translate(vec3(0.0, 0.0, 0.1)) * scale(vec3(0.1, 0.1, 0.2));
	cube();
	model_mat_cpp = mvstack.pop();

	model_mat_cpp = mvstack.pop();
}
void cameras(float tx, float ty, float tz, float sx, float sy, float sz) {
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(tx, ty, tz)) * scale(vec3(sx, sy, sz));
	camera();
	model_mat_cpp = mvstack.pop();
}
#pragma endregion

void light() {
	mvstack.push(model_mat_cpp);
	//bong
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(1.35, 3, 0)) * scale(vec3(0.05, 0.05, 1.86));
	setInt("color", 98);
	cube();
	model_mat_cpp = mvstack.pop();
	//de
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(1.42, 3, 0)) * scale(vec3(0.03, 0.1, 2));
	setInt("color", 1);
	cube();
	model_mat_cpp = mvstack.pop();
	//tai phai
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(1.35, 3,- 0.95)) * scale(vec3(0.1, 0.1, 0.07));
	setInt("color", 1);
	cube();
	model_mat_cpp = mvstack.pop();
	//tai trai
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(1.35, 3, 0.95)) * scale(vec3(0.1, 0.1, 0.07));
	setInt("color", 1);
	cube();
	model_mat_cpp = mvstack.pop();
	model_mat_cpp = mvstack.pop();
}

void lights(float tx, float ty, float tz, float sx, float sy, float sz, int tmp) {
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(tx, ty, tz)) * scale(vec3(sx, sy, sz)) * rotate_z(90.0f * tmp);
	light();
	model_mat_cpp = mvstack.pop();
}
#pragma endregion

//--------------ve ghe lam viec------------
#pragma region chair
void chair() {
	mvstack.push(model_mat_cpp);

	//mat ghe
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0, 0.0, 0.08)) * scale(vec3(0.6, 0.05, 0.77));
	setInt("color", 1);
	cube();
	model_mat_cpp = mvstack.pop();

	//tua lung
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.0, 0.3, -0.275)) * scale(vec3(0.5, 0.6, 0.02));
	setInt("color", 1);
	cube();
	model_mat_cpp = mvstack.pop();

	//tay vin trai
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-0.275, 0.325, -0.275)) * scale(vec3(0.05, 0.6, 0.05));
	setInt("color", 2);
	cube();
	model_mat_cpp = mvstack.pop();

	//tay vin phai
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.275, 0.325, -0.275)) * scale(vec3(0.05, 0.6, 0.05));
	setInt("color", 2);
	cube();
	model_mat_cpp = mvstack.pop();

	//chan phai tren
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.275, -0.325, 0.375)) * scale(vec3(0.05, 0.6, 0.05));
	setInt("color", 2);
	cube();
	model_mat_cpp = mvstack.pop();

	//chan trai tren
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-0.275, -0.325, 0.375)) * scale(vec3(0.05, 0.6, 0.05));
	setInt("color", 2);
	cube();
	model_mat_cpp = mvstack.pop();

	//chan phai duoi
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.275, -0.325, -0.275)) * scale(vec3(0.05, 0.6, 0.05));
	setInt("color", 2);
	cube();
	model_mat_cpp = mvstack.pop();

	//chan trai duoi
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-0.275, -0.325, -0.275)) * scale(vec3(0.05, 0.6, 0.05));
	setInt("color", 2);
	cube();
	model_mat_cpp = mvstack.pop();

	model_mat_cpp = mvstack.pop();
}
#pragma endregion

//---------------------------------------//
void chairs(float tx, float ty, float tz, float sx, float sy, float sz, int j) {
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(work_chairx, 0.0, work_chairz)) * translate(vec3(tx, ty, tz)) * scale(vec3(sx, sy, sz)) * rotate_y(360 / j);
	chair();
	model_mat_cpp = mvstack.pop();
}

//--------------ve ban-------------
#pragma region Ve cai ban

#define chieucaoban 0.7
#define chieudaimat 1
#define chieurongmat 0.6
#define dodaymatban 0.01
#define dodaychanban 0.05
#define chieudaingan 0.8
#define chieurongngan 0.4
#define chieucaongan 0.5

namespace ban {
	void matban()
	{
		mvstack.push(model_mat_cpp);
		setInt("color", 1);
		mat4 instance = identity_mat4();
		instance = translate(vec3(0.0, chieucaoban, chieurongmat / 2.0)) *
			scale(vec3(chieudaimat, dodaymatban, chieurongmat));

		mat4 model_torso = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}

	void chanban()
	{
		mvstack.push(model_mat_cpp);
		setInt("color", 2);
		mat4 instance = identity_mat4();
		instance = translate(vec3(0, chieucaoban / 2.0, 0)) * scale(vec3(dodaychanban, chieucaoban, dodaychanban));

		mat4 model_left_upper_arm = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_left_upper_arm.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}

	void nganban()
	{
		mvstack.push(model_mat_cpp);
		setInt("color", 1);
		mat4 instance = identity_mat4();
		instance = translate(vec3(0.25, chieucaongan - 1, chieurongmat / 2.0)) * scale(vec3((chieudaimat - (dodaychanban * 2.0)) / 2, dodaymatban, chieurongmat - (dodaychanban * 2.0)));
		mat4 model_torso = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}

	void tamchanban() {
		mvstack.push(model_mat_cpp);
		setInt("color", 1);
		mat4 instance = identity_mat4();
		instance = translate(vec3(0.25, chieucaoban - 0.14, chieurongmat / 2 - 0.3)) * scale(vec3((chieudaimat - (dodaychanban * 2.0)) / 2, 0.28, dodaymatban));

		mat4 model_torso = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}
	void veban() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(0, -1, 0));
		ban::matban();

		// Chan ban 1
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(-chieudaimat / 2.0 + dodaychanban, 0, dodaychanban));
		ban::chanban();
		model_mat_cpp = mvstack.pop();

		// chan ban 2
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(-chieudaimat / 2.0 + dodaychanban, 0, chieurongmat - dodaychanban));
		ban::chanban();
		model_mat_cpp = mvstack.pop();

		// Chan ban 3
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(chieudaimat / 2.0 - dodaychanban, 0, dodaychanban));
		ban::chanban();
		model_mat_cpp = mvstack.pop();

		// chan ban 4
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(chieudaimat / 2.0 - dodaychanban, 0, chieurongmat - dodaychanban));
		ban::chanban();
		model_mat_cpp = mvstack.pop();

		// Chan ban 5
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(-chieudaimat / 2.0 + dodaychanban + 0.5, 0, dodaychanban));
		ban::chanban();
		model_mat_cpp = mvstack.pop();

		// Chan ban 6
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(-chieudaimat / 2.0 + dodaychanban + 0.5, 0.5, chieurongmat - dodaychanban)) * scale(vec3(0.8, 0.28, 0.8));
		ban::chanban();
		model_mat_cpp = mvstack.pop();

		//tam chan ban
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(0, -0.7, 0)) * scale(vec3(1.0, 2.0, 1.0));
		ban::tamchanban();
		model_mat_cpp = mvstack.pop();

		//tam chan ban ben
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(0.48, 0.21, chieurongmat)) * scale(vec3(1.0, 0.7, 1.2)) * rotate_y(90);
		ban::tamchanban();
		model_mat_cpp = mvstack.pop();

		//tam chan ban giua
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(0.03, 0.21, chieurongmat)) * scale(vec3(1.0, 0.7, 1.2)) * rotate_y(90);
		ban::tamchanban();
		model_mat_cpp = mvstack.pop();

		model_mat_cpp = mvstack.pop();
	}
}

void veban(float tx, float ty, float tz, float sx, float sy, float sz, GLfloat ngankeo) {
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(tx, ty, tz)) * scale(vec3(sx, sy, sz));
	ban::veban();

	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0, 0, ngankeo));
	ban::nganban();
	model_mat_cpp = mvstack.pop();

	model_mat_cpp = mvstack.pop();

}
#pragma endregion

//-----------ve ban sofa--------------
#pragma region Ve cai bansofa
namespace bansofa {
	void matbansofa() {
		mvstack.push(model_mat_cpp);
		setInt("color", 2);
		mat4 instance = identity_mat4();
		instance = translate(vec3(0.0, 0.5, 0.6/ 2.0)) *
			scale(vec3(1, 0.05, 0.6));

		mat4 model_torso = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}
	void chanbansofa()
	{
		mvstack.push(model_mat_cpp);
		setInt("color", 10);
		mat4 instance = identity_mat4();
		instance = translate(vec3(0, 0.5 / 2.0, 0)) * scale(vec3(0.17, 0.5, 0.4));

		mat4 model_left_upper_arm = model_mat_cpp * instance;

		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_left_upper_arm.m);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		model_mat_cpp = mvstack.pop();
	}
	void vebansofa() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(0, -1, 0));
		bansofa::matbansofa();

		// Chan ban 1
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(-1 / 2.0 + 0.17, 0, 0.3));
		bansofa::chanbansofa();
		model_mat_cpp = mvstack.pop();

		// Chan ban 2
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(1 / 2.0 - 0.17, 0, 0.3));
		bansofa::chanbansofa();
		model_mat_cpp = mvstack.pop();
		

		/*
		// chan ban 2
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(-1 / 2.0 + 0.2, 0, 0.6 - 0.2));
		bansofa::chanbansofa();
		model_mat_cpp = mvstack.pop();


		// Chan ban 3
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(1 / 2.0 - 0.2, 0, 0.2));
		bansofa::chanbansofa();
		model_mat_cpp = mvstack.pop();

		// chan ban 4
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(1 / 2.0 - 0.2, 0, 0.6 - 0.2));
		bansofa::chanbansofa();
		model_mat_cpp = mvstack.pop();
		*/

		model_mat_cpp = mvstack.pop();
		 
	}
}
void vebansofa(float tx, float ty, float tz, float sx, float sy, float sz,int j) {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(tx, ty, tz)) * scale(vec3(sx, sy, sz)) * rotate_y(-180 / j);
		bansofa::vebansofa();
		model_mat_cpp = mvstack.pop();
}

//--------------ve dong ho--------------
#pragma region clock
float hour_angle = 0.0f;
float min_angle = 15.0f;
namespace dongho {
	void mat() {
		mvstack.push(model_mat_cpp);
		setInt("color", 98);
		model_mat_cpp = model_mat_cpp * scale(vec3(1, 1, 0.1));
		cube();
		model_mat_cpp = mvstack.pop();
	}

	void vien() {
		mvstack.push(model_mat_cpp);
		setInt("color", 1);
		model_mat_cpp = model_mat_cpp * scale(vec3(0.1, 1, 0.1));
		cube();
		model_mat_cpp = mvstack.pop();
	}

	void hour_index() {
		mvstack.push(model_mat_cpp);
		setInt("color", 99);
		model_mat_cpp = model_mat_cpp * scale(vec3(0.02, 0.06, 0.01));
		cube();
		model_mat_cpp = mvstack.pop();
	}

	void truc() {
		mvstack.push(model_mat_cpp);
		setInt("color", 99);
		model_mat_cpp = model_mat_cpp * scale(vec3(0.06, 0.06, 0.12));
		cube();
		model_mat_cpp = mvstack.pop();
	}

	void kim() {
		mvstack.push(model_mat_cpp);
		setInt("color", 3);
		model_mat_cpp = model_mat_cpp * translate(vec3(0, 0.11, 0.08)) * scale(vec3(0.02, 0.25, 0.02));
		cube();
		model_mat_cpp = mvstack.pop();
	}

	void vedongho(float tx, float ty, float tz, float sx, float sy, float sz) {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(tx, ty, tz)) * scale(vec3(sx, sy, sz));

		mvstack.push(model_mat_cpp);
		dongho::mat();
		model_mat_cpp = mvstack.pop();

		//ve vien 1
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(0.45, 0, 0.05));
		dongho::vien();
		model_mat_cpp = mvstack.pop();

		//ve vien 2
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(-0.45, 0, 0.05));
		dongho::vien();
		model_mat_cpp = mvstack.pop();

		//ve vien 3
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(0, 0.45, 0.05)) * rotate_y(90) * rotate_x(90);
		dongho::vien();
		model_mat_cpp = mvstack.pop();

		//ve vien 4
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(0, -0.45, 0.05)) * rotate_y(90) * rotate_x(90);
		dongho::vien();
		model_mat_cpp = mvstack.pop();

		//index
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(0, 0.34, 0.06));
		dongho::hour_index();
		model_mat_cpp = mvstack.pop();

		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(0.34, 0, 0.06)) * rotate_z(90);
		dongho::hour_index();
		model_mat_cpp = mvstack.pop();

		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(-0.34, 0, 0.06)) * rotate_z(-90);
		dongho::hour_index();
		model_mat_cpp = mvstack.pop();

		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(0, -0.34, 0.06));
		dongho::hour_index();
		model_mat_cpp = mvstack.pop();

		//truc
		dongho::truc();

		//kim gio
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * rotate_z(hour_angle) * scale(vec3(1.4, 1, 1));
		dongho::kim();
		model_mat_cpp = mvstack.pop();

		//kim phut
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * rotate_z(min_angle) * scale(vec3(1, 1.4, 1));
		dongho::kim();
		model_mat_cpp = mvstack.pop();

		model_mat_cpp = mvstack.pop();
	}
}
#pragma endregion

//-------------ve tu----------------
#pragma region Ve cai tu

#define chieucaotu 1.2
#define chieungangtu 0.8
#define chieurongtu 0.5
#define dodaytu 0.01

namespace tu {
	void san() {
		mvstack.push(model_mat_cpp);
		setInt("color", 1);
		model_mat_cpp = model_mat_cpp * scale(vec3(chieungangtu, dodaytu, chieurongtu));
		cube();
		model_mat_cpp = mvstack.pop();
	}
	void canhbentu()
	{
		mvstack.push(model_mat_cpp);
		setInt("color", 1);
		model_mat_cpp = model_mat_cpp * scale(vec3(dodaytu, chieucaotu, chieurongtu));
		cube();
		model_mat_cpp = mvstack.pop();
	}
	void matlungtu()
	{
		mvstack.push(model_mat_cpp);
		setInt("color", 1);
		model_mat_cpp = model_mat_cpp * translate(vec3(0, chieucaotu / 2.0, chieurongtu / 2.0)) * scale(vec3(chieungangtu, chieucaotu, dodaytu));
		cube();
		model_mat_cpp = mvstack.pop();
	}
	void vetu()
	{
		mvstack.push(model_mat_cpp);
		//noctu
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(0, chieucaotu, 0));
		tu::san();
		model_mat_cpp = model_mat_cpp * translate(vec3(0, chieucaotu - 1.5, 0));
		tu::san();
		model_mat_cpp = model_mat_cpp * translate(vec3(0, chieucaotu - 1.55, 0));
		tu::san();
		model_mat_cpp = model_mat_cpp * translate(vec3(0, chieucaotu - 1.56, 0));
		tu::san();
		model_mat_cpp = mvstack.pop();
		tu::san();

		//ben trai tu
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(chieungangtu / 2.0, chieucaotu / 2.0, 0));
		tu::canhbentu();
		model_mat_cpp = mvstack.pop();

		//ben phai tu
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(-chieungangtu / 2.0, chieucaotu / 2.0, 0));
		tu::canhbentu();
		model_mat_cpp = mvstack.pop();

		//back cua tu
		tu::matlungtu();

		model_mat_cpp = mvstack.pop();

	}

	void canhtu()
	{
		float chieucaocanh = chieucaotu - dodaytu;
		mvstack.push(model_mat_cpp);
		setInt("color", 17);
		model_mat_cpp = model_mat_cpp * scale(vec3(chieungangtu / 2.0, chieucaocanh, dodaytu));
		cube();
		model_mat_cpp = mvstack.pop();
		mvstack.push(model_mat_cpp);
		setInt("color", 17);
		model_mat_cpp = model_mat_cpp * scale(vec3(chieungangtu / 2.0 - 0.04, chieucaocanh - 0.03, dodaytu)) * translate(vec3(0, 0, 0.01));
		cube();
		model_mat_cpp = mvstack.pop();
	}

	//tay nam tu
	/*void taynamtu() {
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(chieungangtu / 2.0 - 0.06, chieucaocanh - 0.04, dodaytu)) * scale(vec3(0.1, 0.02, 0.02));
		setInt("color", 1);
		cube();
		model_mat_cpp = mvstack.pop();
	}*/
}
void draw_tu(float tx, float ty, float tz, float sx, float sy, float sz, GLfloat angle_canh1)
{
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(tx, ty, tz)) * scale(vec3(sx, sy, sz));
	tu::vetu();
	// canh tu 1 - canh trai
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.4, 0.6, -0.24)) * rotate_y(angle_canh1) * translate(vec3(-0.2, 0, 0));
	tu::canhtu();
	model_mat_cpp = mvstack.pop();
	// canh tu 2 - canh phai
	GLfloat angle_canh2 = angle_canh1 * (-1);
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-0.4, 0.6, -0.24)) * rotate_y(angle_canh2) * translate(vec3(0.2, 0, 0));
	tu::canhtu();
	model_mat_cpp = mvstack.pop();

	model_mat_cpp = mvstack.pop();
}
#pragma endregion

//--------------ve quat tran----------------
#pragma region draw ceiling fan
//CEILING FAN quạt trần: chiều cao quạt là 2, độ dài bề ngang là 5 (đã làm tròn) tâm tại (0,0,0) là tâm của base_đỉnh của quạt
bool switch_fan = false;
namespace fan {
	void fan_blade_x()
	{
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(0, 0, 0))
			* scale(vec3(2.0f, 0.1f, 0.6f)) * rotate_x(30);
		setInt("color", 16);
		cube();
		model_mat_cpp = mvstack.pop();
	}
	void fan_blade_z()
	{
		mvstack.push(model_mat_cpp);
		setInt("color", 16);
		model_mat_cpp = model_mat_cpp * translate(vec3(0, 0, 0))
			* scale(vec3(0.6f, 0.1f, 2.0f)) * rotate_z(30);
		cube();

		model_mat_cpp = mvstack.pop();
	}
	void fan_base()
	{
		mvstack.push(model_mat_cpp);
		setInt("color", 16);
		model_mat_cpp = model_mat_cpp * translate(vec3(0, 0, 0))
			* scale(vec3(0.8f, 0.2f, 0.8f));
		cube();
		model_mat_cpp = mvstack.pop();
	}
	void ceiling_fan()
	{
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * scale(vec3(0.3, 0.3, 0.3));
		//base dequat
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(0, -0.1, 0));
		fan::fan_base();
		model_mat_cpp = mvstack.pop();
		//Downrod tru quat
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(0, -0.9, 0))
			* scale(vec3(0.2f, 1.4f, 0.2f));
		setInt("color", 6);
		cube();
		model_mat_cpp = mvstack.pop();
		//Motor Housing bau quat
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * translate(vec3(0, -1.7, 0));
		fan::fan_base();
		model_mat_cpp = mvstack.pop();
		//fan blade 1
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * rotate_y(Alpha)
			* translate(vec3(1.4, -1.7, 0));
		fan::fan_blade_x();
		model_mat_cpp = mvstack.pop();
		//fan blade 2
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * rotate_y(Alpha)
			* translate(vec3(-1.4, -1.7, 0));
		fan::fan_blade_x();
		model_mat_cpp = mvstack.pop();
		//fan blade 3
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * rotate_y(Alpha)
			* translate(vec3(0, -1.7, 1.4));
		fan::fan_blade_z();
		model_mat_cpp = mvstack.pop();
		//fan blade 4
		mvstack.push(model_mat_cpp);
		model_mat_cpp = model_mat_cpp * rotate_y(Alpha)
			* translate(vec3(0, -1.7, -1.4));
		fan::fan_blade_z();
		model_mat_cpp = mvstack.pop();
		model_mat_cpp = mvstack.pop();
	}
}
void quat(float qx, float qy, float qz) {
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(qx, qy, qz));
	fan::ceiling_fan();
	model_mat_cpp = mvstack.pop();
}
#pragma endregion

//---------------ve sofa---------------
GLfloat ghe_sofax = 0.0;
GLfloat ghe_sofaz = 0.0;
#pragma endregion
void drawSofa() {
	mvstack.push(model_mat_cpp);

	//ngồi
	setInt("color", 20);
	model_mat_cpp = model_mat_cpp * translate(vec3(0, 0.1, 0)) * scale(vec3(1.5, 0.2, 0.7)); // Adjust size
	cube(); // Draw the seat
	model_mat_cpp = mvstack.pop();

	// đệm ngồi
	mvstack.push(model_mat_cpp);
	setInt("color", 19); // Set color for the seat
	model_mat_cpp = model_mat_cpp * translate(vec3(0, 0.25, 0.05)) * scale(vec3(1.3, 0.1, 0.6)); // Adjust size
	cube(); // Draw the seat
	model_mat_cpp = mvstack.pop();

	// tựa lưng
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0, 0.4, -0.3)) * scale(vec3(1.5, 0.72, 0.1)); // Adjust size and position
	setInt("color", 20); // Set color for the backrest
	cube(); // Draw the backrest
	model_mat_cpp = mvstack.pop();

	// vịn trái
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-0.7, 0.35, 0)) * scale(vec3(0.1, 0.35, 0.7)); // Adjust size and position
	setInt("color", 20); // Set color for the left armrest
	cube(); // Draw the left armrest
	model_mat_cpp = mvstack.pop();

	// vịn phải
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.7, 0.35, 0)) * scale(vec3(0.1, 0.35, 0.7)); // Adjust size and position
	setInt("color", 20); // Set color for the right armrest
	cube(); // Draw the right armrest
	model_mat_cpp = mvstack.pop();
}
void sofa(float tx, float ty, float tz, float sx, float sy, float sz, int j) {
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(ghe_sofax, -0.1, ghe_sofaz)) * translate(vec3(tx, ty, tz)) * scale(vec3(sx, sy, sz)) * rotate_y(-180 / j);
	drawSofa();
	model_mat_cpp = mvstack.pop();
}

//--------ve dieu hoa---------
#pragma region air conditioner
//conditioner size= (2,3,8.4) 
bool _switch_con = false;
float angle_conditioner = 0.0f;
float angle_conditioners = 1.0f;
void conditioner()
{
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * scale(vec3(0.2, 0.2, 0.2));//giam size di 1/4 
	//hộp to
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(11, -0.5, -9)) * scale(vec3(8.4, 2.3, 2));
	setInt("color", 98);
	cube();
	model_mat_cpp = mvstack.pop();
	//hộp nhỏ
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(11, -1.8, -9)) * scale(vec3(8.4, 0.5, 1.6));
	setInt("color", 98);
	cube();
	model_mat_cpp = mvstack.pop();
	//hộp dưới
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(11, -2, -9)) * scale(vec3(8.4, 0.1, 2));
	setInt("color", 98);
	cube();
	model_mat_cpp = mvstack.pop();
	//canh ben trai
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(6.8, -0.67, -9)) * scale(vec3(0.01, 2.7, 2));
	setInt("color", 2);
	cube();
	model_mat_cpp = mvstack.pop();
	//canh ben phai
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(15.2, -0.67, -9)) * scale(vec3(0.01, 2.7, 2));
	setInt("color", 2);
	cube();
	model_mat_cpp = mvstack.pop();
	//cua
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp
		* translate(vec3(11, -1.82, -8.0))
		* translate(vec3(0.0, -0.25, 0.0))
		* rotate_x(angle_conditioner)
		* translate(vec3(0.0, 0.25, 0.0))
		* scale(vec3(8.4, 0.4, 0.01));
	mvstack.push(model_mat_cpp);
	setInt("color", 2);
	cube();
	model_mat_cpp = mvstack.pop();
	model_mat_cpp = mvstack.pop();
	model_mat_cpp = mvstack.pop();
}
void dieuhoa(float qx, float qy, float qz) {
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(qx, qy, qz));
	conditioner();
	model_mat_cpp = mvstack.pop();
}
#pragma endregion

//ve laptop
#pragma region laptop
bool switch_lap = false;
float lap_angle = 0.0f;
void laptop() {
	mvstack.push(model_mat_cpp);
	//ban phim
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0.2, 0.6, 0.4)) * scale(vec3(0.12, 0.02, 0.27));
	setInt("color", 10);
	cube();
	model_mat_cpp = mvstack.pop();

	//man hinh
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp
		* translate(vec3(0.2, 0.62, 0.4))   // Vị trí trung tâm giữa các khung
		* translate(vec3(-0.06, 0.0, 0.0))
		* rotate_z(lap_angle)
		* translate(vec3(0.06, 0.0, 0.0))
		* scale(vec3(0.12, 0.01, 0.27));
	setInt("color", 10);
	cube();
	model_mat_cpp = mvstack.pop();
	model_mat_cpp = mvstack.pop();
}
void laptops(float tx, float ty, float tz, float sx, float sy, float sz) {

	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(tx, ty, tz)) * scale(vec3(sx, sy, sz));
	laptop();
	model_mat_cpp = mvstack.pop();
}
#pragma endregion

//============================================ Hết tạo các đối tượng ================================//
//-----------------------------------//
void DisplayFunc(void)
{
	model_mat_cpp = identity_mat4();
	model_mat_location = glGetUniformLocation(ProgramId, "model_mat_shader");
	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	if (translated)
	{
		model_mat_cpp = model_mat_cpp * translate(vec3(t[0], t[1], t[2]));
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	}
	if (rotated)
	{
		model_mat_cpp = model_mat_cpp * rotate_x(r[0])
			* rotate_y(r[1])
			* rotate_z(r[2]);
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	}
	if (scaled)
	{
		model_mat_cpp = model_mat_cpp * scale(vec3(s[0], s[1], s[2]));
		glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_mat_cpp.m);
	}

	glMatrixMode(GL_MODELVIEW);


	// Các tham số của hàm lookat
	vec3	eye(cameraX, cameraY, cameraZ),
		at(cameraX + sin(yaw), cameraY - pitch, cameraZ - cos(yaw) - 0.3f),
		up(0.0f, 1.0f, 0.0f);

	view_mat_cpp = lookat(eye, at, up);
	view_mat_location = glGetUniformLocation(ProgramId, "view_mat_shader");
	glUniformMatrix4fv(view_mat_location, 1, GL_FALSE, view_mat_cpp.m);

	float
		znear = 0.1f,
		zfar = 100.0f,
		fov = 90.0f,
		aspect = (float)CurrentWidth / CurrentHeight;
	projection_mat_cpp = perspective(fov, aspect, znear, zfar);
	projection_mat_location = glGetUniformLocation(ProgramId, "projection_mat_shader");
	glUniformMatrix4fv(projection_mat_location, 1, GL_FALSE, projection_mat_cpp.m);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClearColor(1.0, 1.0, 1.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//-----------------draw------------------
	room();
	door();


	lights(13.5, 1.15, -2.6, 4.5, 1.2, 1.9, 1);
	windowns(-2.5, 0.975, -5.5, 0.95, 1.6, 1.65, windown_rotate[windown1], 1);


	vebansofa(0.5, 0.1, -1.3, 1.6, 1.2, 1.5, 2);
	sofa(2.0, -1.0, -1.45, 1.2, 1.2, 1.9, 2.0);		//sofa dài
	sofa(0.6, -1.0, -2.7, 0.6, 1.0, 1.1, -180);		//sofa ngắn
	//sofa(0.6f, -1.0f, -0.5f, 1.0f, 1.0f, 1.0f, -1);
	quat(0.5, 2.9, -3.5);

	dieuhoa(-2.3, 2.55, -5);
	laptops(0.1, -0.55, -5.1, 1.5, 0.5, 1);
	
	//camera
	cameras(2.2, 2.8, -6.95, 1.0, 1.0, 1.0);

	//ban lam viec
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(work_tablex[table0], 0.1f, -5.5f)) * rotate_y(90);
	veban(-0.5, 0, 0, 1.6, 1.2, 1.2, ngankeo_z[ngankeo]);
	model_mat_cpp = mvstack.pop();

	//ghe lam viec
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(1.2f, -0.5f, -6.2f)) * rotate_y(-90);
	chairs(1.5f, 0.0f, 0.2f, 0.9, 0.8, 0.4, 1);
	model_mat_cpp = mvstack.pop();

	//dong ho
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3()) * scale(vec3(0.4, 0.4, 0.4)) * rotate_y(180);
	dongho::vedongho(0, 4.5, 0.2, 1, 1, 1);
	model_mat_cpp = mvstack.pop();
	
	//tu 
	//tu 1
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(2.25, -chieucaotu + 0.005, -5.5)) * rotate_y(90);
	draw_tu(0, 0.1, 0, 1.5, 1.5, 0.8, angle_canhtu[tu1]);
	model_mat_cpp = mvstack.pop();
	//tu 2
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(2.25, -chieucaotu + 0.005, -5.5)) * rotate_y(90);
	draw_tu(-1.0, 0.1, 0, 1.0, 1.35, 0.8, angle_canhtu[tu2]);
	model_mat_cpp = mvstack.pop();


	glutSwapBuffers();
}
//--------------Các hàm cho cam--------------//
void handleMouseMove(int x, int y) {
	if (mouseLocked) {
		int deltaX = x - midWindowX;
		int deltaY = y - midWindowY;

		yaw += deltaX * 0.001f;
		pitch += deltaY * 0.001f;

		if (pitch > 1.5f) pitch = 1.5f;
		else if (pitch < -1.5f) pitch = -1.5f;

		glutWarpPointer(midWindowX, midWindowY);
	}
	glutPostRedisplay();
}
void handleKeyRelease(unsigned char key, int x, int y) {
	keys[key] = false;
	glutPostRedisplay();
}
void updateCamera() {
	if (isJumping) {
		cameraY += jumpSpeed;
		jumpSpeed -= gravity;
		if (cameraY <= 0.0f) {
			cameraY = 0.0f;
			isJumping = false;
			isGrounded = true;
			jumpSpeed = 0.2f;
		}
	}
	glutPostRedisplay();
}
// ------------------------------------------//
void ReshapeFunc(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;
	midWindowX = Width / 2;//
	midWindowY = Height / 2;//
	glViewport(0, 0, CurrentWidth, CurrentHeight);
}
// ------------------------------------------//
bool phim1 = true, phim2 = true;
void IdleFunc(void)
{
	updateCamera();
	//------light-----on/off
	if (phim1) {
		onl1(); glutPostRedisplay();
	}
	else {
		offl1(); glutPostRedisplay();
	}
	if (phim2) {
		onl2(); glutPostRedisplay();
	}
	else {
		offl2();
		glutPostRedisplay();
	}

	//fan
	if (switch_fan) {
		Alpha += 5.0f;
		if (Alpha > 360.0f) {
			Alpha -= 360.0f;
		}
		glutPostRedisplay();
	}
	else {
		glutPostRedisplay();
	}

	//conditioner
	if (_switch_con) {
		angle_conditioner += angle_conditioners * 0.02f;
		if (angle_conditioner <= -0.5f || angle_conditioner >= 95.0f) {
			angle_conditioners = -angle_conditioners;
		}
		glutPostRedisplay();
	}


	// camera
	if (switch_camera) {
		camera_angle += camera_direction * 0.1f;  // Cap nhat goc quayy
		if (camera_angle >= 60.0f || camera_angle <= -60.0f) {
			camera_direction = -camera_direction;
		}
	glutPostRedisplay();
	}

	// dong ho
	hour_angle += 0.005; // Tăng góc lên mỗi lần gọi hàm
	if (hour_angle >= 360) {
		hour_angle = 0; // Nếu góc lớn hơn hoặc bằng 360 độ, đặt lại về 0 độ
	}
	min_angle += 0.006;
	if (min_angle >= 360) {
		min_angle = 0;
	}
	glutPostRedisplay();
}
// ------------------------------------------
void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		glutLeaveMainLoop();
		break;
		//----camera------------
	case 'W':
	case 'w':
		cameraX += sin(yaw) * moveSpeed;
		cameraZ -= cos(yaw) * moveSpeed;
		break;
	case 'S':
	case 's':
		cameraX -= sin(yaw) * moveSpeed;
		cameraZ += cos(yaw) * moveSpeed;
		break;
	case 'D':
	case 'd':
		cameraX += sin(yaw - 3.1415926535 / 2) * moveSpeed;
		cameraZ -= cos(yaw - 3.1415926535 / 2) * moveSpeed;
		break;
	case 'A':
	case 'a':
		cameraX += sin(yaw + 3.1415926535 / 2) * moveSpeed;
		cameraZ -= cos(yaw + 3.1415926535 / 2) * moveSpeed;
		break;
	case ' ':
		if (isGrounded) {
			isJumping = true;
			isGrounded = false;
		}
		keys[key] = true;
		break;

	//-----light---
	case 'C':
	case 'c'://on/off light1
		if (phim1) phim1 = false;
		else phim1 = true;
		break;
	case 'V':
	case 'v'://on/of light2
		if (phim2) phim2 = false;
		else phim2 = true;
		break;

	//-----light---
	case 'x':
		r[0] -= 10.0f;
		rotated = true;
		break;
	case 'X':
		r[0] += 10.0f;
		rotated = true;
		break;

	case 'y':
		r[1] -= 10.0f;
		rotated = true;
		break;
	case 'Y':
		r[1] += 10.0f;
		rotated = true;
		break;

	case 'z':
		r[2] -= 10.0f;
		rotated = true;
		break;
	case 'Z':
		r[2] += 10.0f;
		rotated = true;
		break;

	case '=':
	case '+':
		s[0] *= 1.05f;
		s[1] *= 1.05f;
		s[2] *= 1.05f;
		scaled = true;
		break;

	case '-':
	case '_':
		s[0] /= 1.05f;
		s[1] /= 1.05f;
		s[2] /= 1.05f;
		scaled = true;
		break;

	case 'j':
		t[0] -= 0.05f;
		translated = true;
		break;
	case 'l':
		t[0] += 0.05f;
		translated = true;
		break;
	case 'i':
		t[1] += 0.05f;
		translated = true;
		break;
	case ',':
		t[1] -= 0.05f;
		translated = true;
		break;
	case 'h':
		t[2] -= 0.05f;
		translated = true;
		break;
	case 'g':
		t[2] += 0.05f;
		translated = true;
		break;

	//cửa
	case '/'://mở cửa
		door_angle += 2.0f;
		if (door_angle >= 150) door_angle = 150.0f;
		break;
	case '?'://đóng cửa
		door_angle -= 2.0f;
		if (door_angle <= 0) door_angle = 0;
		break;

	//windows
	case '6':
		windown_rotate[rotate_windown] += 1.5;
		if (windown_rotate[rotate_windown] >= 90.0) { windown_rotate[rotate_windown] = 90.0; }
		break;
	case '7':
		windown_rotate[rotate_windown] -= 1.5;
		if (windown_rotate[rotate_windown] <= 0.0) { windown_rotate[rotate_windown] = 0.0; }
		break;

	// camera
	case '2':
		if (switch_camera) {
			switch_camera = false;
			break;
		}
		else {
			switch_camera = true;
			break;
		}

	// ghế làm việc
	case 'f':
		if (work_chairx <= 1.3) {
			work_chairx += 0.1;
		}
		break;
	case 'r':
		if (work_chairx >= -1.75) {
			work_chairx -= 0.1;
		}
		break;
	case 'u':
		if (work_chairz <= 2.5) {
			work_chairz += 0.1;
		}
		break;
	case 'p':
		if (work_chairz >= -0.7) {
			work_chairz -= 0.1;
		}
		break;

	//tủ tài liệu
	case 't':
		angle_canhtu[angle_tu_y] -= 2.0f;
		if (angle_canhtu[angle_tu_y] <= -90) angle_canhtu[angle_tu_y] = -90;
		break;
	case 'T':
		angle_canhtu[angle_tu_y] += 2.0f;
		if (angle_canhtu[angle_tu_y] >= 0) angle_canhtu[angle_tu_y] = 0;
		break;

	//fan
	case 'q':
		if (switch_fan) switch_fan = false;
		else switch_fan = true;
		break;

	//sofa
	case 'F':
		if (ghe_sofaz <= -0.1) {
			ghe_sofaz += 0.1;
		}
		break;
	case 'R':
		if (ghe_sofaz >= -1.2) {
			ghe_sofaz -= 0.1;
		}
		break;
	case 'P':
		if (ghe_sofax <= -0.01) {
			ghe_sofax += 0.1;
		}
		break;
	case 'U':
		if (ghe_sofax >= -1.6) {
			ghe_sofax -= 0.1;
		}
		break;

	//dieu hoa
	case '1':
		if (_switch_con) {
			_switch_con = false;
			break;
		}
		else {
			_switch_con = true;
			break;
		}
		break;
	case 'm':
		lap_angle += 2;
		if (lap_angle >= 100.0) lap_angle = 100.0;
		break;
	case 'M':
		lap_angle -= 2;
		if (lap_angle <= 0.0) lap_angle = 0.0;
		break;
	}
}
// ----------------------------------------
// Xử lý phím đặc biệt
void SpecialFunc(int key, int x, int y)
{

	switch (key)
	{
	case GLUT_KEY_LEFT:
		t[0] -= 0.05f;
		translated = true;
		break;
	case GLUT_KEY_RIGHT:
		t[0] += 0.05f;
		translated = true;
		break;
	case GLUT_KEY_UP:
		t[1] += 0.05f;
		translated = true;
		break;
	case GLUT_KEY_DOWN:
		t[1] -= 0.05f;
		translated = true;
		break;
	case GLUT_KEY_ALT_R:
		t[2] -= 0.05f;
		translated = true;
		break;
	case GLUT_KEY_CTRL_R:
		t[2] += 0.05f;
		translated = true;
		break;
	}
}
void danhsachlenh() {
	cout << "Chuot di chuyen huong camera " << endl;
	cout << "/ : mo cua chinh " << endl;
	cout << "? : dong cua chinh " << endl;
	cout << "6 : mo cua so " << endl;
	cout << "7 : dong cua so" << endl;
	cout << "g : tinh tien vat the ve gan camera" << endl;
	cout << "h : tinh tien vat the ra xa camera  " << endl;
	cout << "w : tien camera len  " << endl;
	cout << "s : lui camera xuong  " << endl;
	cout << "a : xoay camera sang trai  " << endl;
	cout << "d : xoay camera sang phai  " << endl;
	cout << "+ : phong to " << endl;
	cout << "- : thu nho " << endl;
	cout << ", : dua camera len tren " << endl;
	cout << "i : dua camera xuong duoi " << endl;
	cout << "c : bat, tat den dien " << endl;
	cout << "v : ngay, dem " << endl;
	cout << "r : di chuyen ghe lam viec sang phai " << endl;
	cout << "f : di chuyen ghe lam viec sang trai " << endl;
	cout << "u : di chuyen ghe lam viec tien len (tien lai gan cua chinh)" << endl;
	cout << "p : di chuyen ghe lam viec lui xuong (lui ra xa cua chinh)" << endl;
	cout << "t : mo tu tai lieu" << endl;
	cout << "T : dong tu tai lieu" << endl;
	cout << "q : bat/tat quat tran" << endl;
	cout << "m : mo laptop" << endl;
	cout << "M : dong laptop" << endl;
	cout << "1 : bat dieu hoa" << endl;
	cout << "R : di chuyen ghe sofa sang phai " << endl;
	cout << "F : di chuyen ghe sofa sang trai " << endl;
	cout << "U : di chuyen ghe sofa tien len (tien lai gan cua chinh)" << endl;
	cout << "P : di chuyen ghe sofa lui xuong (lui ra xa cua chinh)" << endl;
	cout << endl;
}
// ------------------------------------------
int main(int argc, char* argv[])
{
	danhsachlenh();
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(CurrentWidth, CurrentHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("MO HINH PHONG LAM VIEC -- GROUP 13");

	glewExperimental = GL_TRUE;
	glewInit();

	CreatVaoVbo();
	CreatShaders();

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);
	glutPassiveMotionFunc(handleMouseMove);//camera
	glutKeyboardFunc(KeyboardFunc);
	glutSpecialFunc(SpecialFunc);
	glutKeyboardUpFunc(handleKeyRelease);//camera
	glutCloseFunc(CloseFunc);

	// Attach the menu to the middle mouse button
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutMainLoop();
	return 0;
}

