#version 330

layout(location=0) out vec4 FragColor;
uniform sampler2D u_AhnTex;

in float v_Grey;	
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
    FragColor = vec4(v_Grey, v_Grey, v_Grey, 1.0); // 알파값이 투명해지지 않도록 수정
}