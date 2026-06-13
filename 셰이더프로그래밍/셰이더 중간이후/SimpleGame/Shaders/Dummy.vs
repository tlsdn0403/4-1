#version 330

uniform float u_Time;
uniform vec4 u_DropInfo[200]; // vec4(x, y, lT, sT)

in vec3 a_Pos;
out float v_Color;
out vec2 v_Tex;
float c_PI = 3.141592;

void Flag()
{
	v_Tex = vec2(a_Pos.x + 0.5, 1.0 - (a_Pos.y + 0.5));

	float weight = a_Pos.x + 0.5;
	float newX = a_Pos.x;
	float newY = a_Pos.y * (1 - weight * 0.5) 
				- sin(a_Pos.x * c_PI * 2 - u_Time) * 0.25 * weight;

	vec4 final = vec4(newX, newY, 0.0, 1.0);	

	float color = (1 + sin(a_Pos.x * c_PI * 2 - u_Time)) / 2;
	v_Color = color;
	gl_Position = final;
}

void Circles()
{
	float accum = 0;

	for (int i = 0; i < 200; ++i)
	{
		vec2 center = u_DropInfo[i].xy - vec2(0.5, 0.5);
		vec2 pos = a_Pos.xy;

		float lTime = max(u_DropInfo[i].z, 0.001);
		float sTime = u_DropInfo[i].w;
		float nTime = u_Time - sTime;

		if (nTime > 0)
		{
			float lTime_normalize = fract(nTime/lTime);
			float oneMinus = 1.0 - lTime_normalize;
			float t = lTime_normalize * lTime;

			float d = distance(center, pos);

			float range = t / 5.0;

			float fade = 5.0 * clamp(range - d, 0, 1.0);
			
			float sinValue = pow(abs(sin(d * 4 * c_PI * 8 - t * 2)), 3.0);

			accum += sinValue * fade * oneMinus;
		}
	}

	v_Color = accum;

	//gl_Position = vec4(a_Pos, 1);
	gl_Position = vec4(a_Pos.x, a_Pos.y + accum * 0.1, a_Pos.z, 1);
}

void main()
{
	Circles();
}
