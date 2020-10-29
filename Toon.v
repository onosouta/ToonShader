#version 330

uniform mat4 world_transform;	//���[���h�ϊ��s��
uniform mat4 view_projection;	//�r���[�ˉe�ϊ��s��
uniform bool edge = true;

layout(location = 0) in vec3 in_pos;	//x, y, z
layout(location = 1) in vec3 in_normal;	//x, y, z �@��
layout(location = 2) in vec2 in_tex;	//u, v

out vec3 position;		//���W
out vec3 normal;		//�@��
out vec2 tex_coord;		//�e�N�X�`�����W

void main()
{
	vec3 p = in_pos;
	
	normal = (vec4(in_normal, 0.0) * world_transform).xyz;
	if (edge)
	{
		p += normal * 1.0;
	}

	vec4 pos = vec4(p, 1.0);

	pos = pos * world_transform;			//���[���h�ϊ�
	gl_Position = pos *	view_projection;	//�r���[�ˉe�s��

	position = pos.xyz;
	tex_coord = in_tex;
}