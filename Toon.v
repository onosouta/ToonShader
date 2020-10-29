#version 330

uniform mat4 world_transform;	//ワールド変換行列
uniform mat4 view_projection;	//ビュー射影変換行列
uniform bool edge = true;

layout(location = 0) in vec3 in_pos;	//x, y, z
layout(location = 1) in vec3 in_normal;	//x, y, z 法線
layout(location = 2) in vec2 in_tex;	//u, v

out vec3 position;		//座標
out vec3 normal;		//法線
out vec2 tex_coord;		//テクスチャ座標

void main()
{
	vec3 p = in_pos;
	
	normal = (vec4(in_normal, 0.0) * world_transform).xyz;
	if (edge)
	{
		p += normal * 1.0;
	}

	vec4 pos = vec4(p, 1.0);

	pos = pos * world_transform;			//ワールド変換
	gl_Position = pos *	view_projection;	//ビュー射影行列

	position = pos.xyz;
	tex_coord = in_tex;
}