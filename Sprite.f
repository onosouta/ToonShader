#version 330

uniform sampler2D tex;	//�e�N�X�`��
in vec2 tex_coord;		//�e�N�X�`�����W

out vec4 out_color;

void main()
{
	out_color = texture(tex, tex_coord);
}