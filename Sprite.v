#version 330

uniform mat4 world_transform;	//���[���h�ϊ��s��
uniform mat4 view_projection;	//�r���[�ˉe�ϊ��s��

layout(location = 0) in vec3 in_pos;	//x, y, z
layout(location = 1) in vec3 in_normal;	//x, y, z �@��
layout(location = 2) in vec2 in_tex;	//u, v

out vec2 tex_coord;	//�e�N�X�`�����W

void main()
{
	vec4 pos = vec4(in_pos, 1.0);

	vec4 out_pos =
		pos *
		world_transform *	//���[���h�ϊ�
		view_projection;	//�r���[�ˉe�s��

	gl_Position = out_pos;
	tex_coord = in_tex;
}