#version 330

uniform mat4 world_transform;	//ワールド変換行列
uniform mat4 view_projection;	//ビュー射影変換行列

uniform mat4 transforms[96];	//行列パレット

layout(location = 0) in vec3 in_pos;	//x, y, z
layout(location = 1) in vec3 in_normal;	//x, y, z 法線
layout(location = 2) in uvec4 in_bone;	//ボーン
layout(location = 3) in vec4 in_weight;	//ウェイト
layout(location = 4) in vec2 in_tex;	//u, v

out vec3 position;		//座標
out vec3 normal;		//法線
out vec2 tex_coord;		//テクスチャ座標

void main()
{
	vec4 pos = vec4(in_pos, 1.0);

	//位置のスキニング
	vec4 skin_pos;
	skin_pos = (pos * transforms[in_bone.x]) * in_weight.x;
	skin_pos += (pos * transforms[in_bone.y]) * in_weight.y;
	skin_pos += (pos * transforms[in_bone.z]) * in_weight.z;
	skin_pos += (pos * transforms[in_bone.w]) * in_weight.w;

	skin_pos = skin_pos * world_transform;		//ワールド変換
	gl_Position = skin_pos * view_projection;	//ビュー射影行列

	position = skin_pos.xyz;

	//法線のスキニング
	vec4 skin_normal = vec4(in_normal, 0.0);
	skin_normal =
		(skin_normal * transforms[in_bone.x]) * in_weight.x +
		(skin_normal * transforms[in_bone.y]) * in_weight.y +
		(skin_normal * transforms[in_bone.z]) * in_weight.z +
		(skin_normal * transforms[in_bone.w]) * in_weight.w;

	normal = (skin_normal * world_transform).xyz;

	tex_coord = in_tex;
}