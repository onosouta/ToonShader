#version 330

uniform sampler2D tex;	//テクスチャ
in vec2 tex_coord;		//テクスチャ座標

out vec4 out_color;

void main()
{
	out_color = texture(tex, tex_coord);
}