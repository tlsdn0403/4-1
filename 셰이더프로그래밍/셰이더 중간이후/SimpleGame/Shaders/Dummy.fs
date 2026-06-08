#version 330

layout(location=0) out vec4 FragColor;
uniform sampler2D u_AhnTex;

in float v_Color;	
in vec2 v_Tex;
float c_PI  = 3.1415926;
mat2 rotate2D(float radian)
{

	return mat2(cos(radian), -sin(radian), sin(radian), cos(radian));
}

void Frag(){
	vec2 newTex = rotate2D(-c_PI/2.0) * v_Tex;

	FragColor = texture(u_AhnTex, newTex);
}
void main()
{
	FragColor = vec4(v_Color, v_Color, v_Color, 1.0);
}
