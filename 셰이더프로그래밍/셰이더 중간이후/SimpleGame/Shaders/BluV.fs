#version 330

layout(location=0) out vec4 FragColor;


in vec2 v_Tex;

// 블러를 할 대상이 될 텍스처
uniform sampler2D u_Texture;
uniform float weight[5] = float[] (0.227027, 0.1945946, 0.1216216, 0.054054, 0.016216);

void main()
{             
    vec2 tex_offset = 1.0 / textureSize(u_Texture, 0); // gets size of single texel
    vec3 result = texture(u_Texture, v_Tex).rgb * weight[0]; // current fragment's contribution

    for(int i = 1; i < 5; ++i)
    {
        // 주변을 샘플링하여 필터를 씌운값을 더함 , 여기서는 세로의 값만 더함
        result += texture(u_Texture, v_Tex + vec2(0.0, tex_offset.y * i)).rgb * weight[i];
        result += texture(u_Texture, v_Tex - vec2(0.0, tex_offset.y * i)).rgb * weight[i];
    }

    FragColor = vec4(result, 1.0);
}