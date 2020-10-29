#version 330

uniform mat4 world_transform;	//���[���h�ϊ��s��
uniform mat4 view_projection;	//�r���[�ˉe�ϊ��s��

uniform mat4 transforms[96];	//�s��p���b�g

layout(location = 0) in vec3 in_pos;	//x, y, z
layout(location = 1) in vec3 in_normal;	//x, y, z �@��
layout(location = 2) in uvec4 in_bone;	//�{�[��
layout(location = 3) in vec4 in_weight;	//�E�F�C�g
layout(location = 4) in vec2 in_tex;	//u, v

out vec3 position;		//���W
out vec3 normal;		//�@��
out vec2 tex_coord;		//�e�N�X�`�����W

void main()
{
	vec4 pos = vec4(in_pos, 1.0);

	//�ʒu�̃X�L�j���O
	vec4 skin_pos;
	skin_pos = (pos * transforms[in_bone.x]) * in_weight.x;
	skin_pos += (pos * transforms[in_bone.y]) * in_weight.y;
	skin_pos += (pos * transforms[in_bone.z]) * in_weight.z;
	skin_pos += (pos * transforms[in_bone.w]) * in_weight.w;

	skin_pos = skin_pos * world_transform;		//���[���h�ϊ�
	gl_Position = skin_pos * view_projection;	//�r���[�ˉe�s��

	position = skin_pos.xyz;

	//�@���̃X�L�j���O
	vec4 skin_normal = vec4(in_normal, 0.0);
	skin_normal =
		(skin_normal * transforms[in_bone.x]) * in_weight.x +
		(skin_normal * transforms[in_bone.y]) * in_weight.y +
		(skin_normal * transforms[in_bone.z]) * in_weight.z +
		(skin_normal * transforms[in_bone.w]) * in_weight.w;

	normal = (skin_normal * world_transform).xyz;

	tex_coord = in_tex;
}