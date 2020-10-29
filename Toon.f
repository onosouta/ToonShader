#version 330

uniform sampler2D toon_tex;	//�e�N�X�`��
uniform sampler2D tex;

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

uniform vec4 edge_color;

void main()
{
	vec3 N = normalize(normal);							//�@��
	vec3 L = normalize(-directional_light.direction);	//�����ւ̃x�N�g��
	vec3 V = normalize(camera_pos - position);			//�J�����ւ̃x�N�g��
	vec3 R = normalize(reflect(-L, N));					//����

	//�t�H���̔���

	vec3 phong = ambient;	//����

	float NdotL = dot(N, L);
	//if (NdotL > 0)
	//{
		//�g�U����
		float diffuse = clamp(NdotL, 0.0, 1.0);
			//directional_light.diffuse_color * NdotL;

		//���ʔ���
		//vec3 specular =
			//directional_light.specular_color *
			//pow(max(0.0, dot(R, V)), 10.0);

		//phong += diffuse + specular;
	//}

	if (edge_color.a > 0.0)
	{
		out_color = edge_color;
	}
	else
	{
		out_color = texture(tex, tex_coord) * texture(toon_tex, vec2(diffuse, 0.0));
		//out_color = texture(tex, tex_coord) * vec4(phong, 1.0);
	}
}