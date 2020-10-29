#version 330

uniform sampler2D tex;	//�e�N�X�`��

in vec3 position;	//���W
in vec3 normal;		//�@��
in vec2 tex_coord;	//�e�N�X�`�����W

out vec4 out_color;

//���s����
struct DirectionalLight
{
	vec3 direction;
	vec3 diffuse_color;		//�g�U���ːF
	vec3 specular_color;	//���ʔ��ːF
};

uniform vec3 camera_pos;					//�J�������W
uniform vec3 ambient;						//����
uniform DirectionalLight directional_light;	//���s����

void main()
{
	vec3 N = normalize(normal);							//�@��
	vec3 L = normalize(-directional_light.direction);	//�����ւ̃x�N�g��
	vec3 V = normalize(camera_pos - position);			//�J�����ւ̃x�N�g��
	vec3 R = normalize(reflect(-L, N));					//����

	//�t�H���̔���

	vec3 phong = ambient;	//����

	float NdotL = dot(N, L);
	if (NdotL > 0)
	{
		//�g�U����
		vec3 diffuse = directional_light.diffuse_color * NdotL;

		//���ʔ���
		vec3 specular =
			directional_light.specular_color *
			pow(max(0.0, dot(R, V)), 10.0);

		phong += diffuse + specular;
	}

	out_color = texture(tex, tex_coord) * vec4(phong, 1.0);
}