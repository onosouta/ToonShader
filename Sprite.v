#version 330

uniform mat4 world_transform;	//ワールド変換行列
uniform mat4 view_projection;	//ビュー射影変換行列

layout(location = 0) in vec3 in_pos;	//x, y, z
layout(location = 1) in vec3 in_normal;	//x, y, z 法線
layout(location = 2) in vec2 in_tex;	//u, v

out vec2 tex_coord;	//テクスチャ座標

void main()
{
	vec4 pos = vec4(in_pos, 1.0);

	vec4 out_pos =
		pos *
		world_transform *	//ワールド変換
		view_projection;	//ビュー射影行列

	gl_Position = out_pos;
	tex_coord = in_tex;
}