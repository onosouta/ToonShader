#version 330

uniform sampler2D toon_tex;	//テクスチャ
uniform sampler2D tex;

in vec3 position;	//座標
in vec3 normal;		//法線
in vec2 tex_coord;	//テクスチャ座標

out vec4 out_color;

//平行光源
struct DirectionalLight
{
	vec3 direction;
	vec3 diffuse_color;		//拡散反射色
	vec3 specular_color;	//鏡面反射色
};

uniform vec3 camera_pos;					//カメラ座標
uniform vec3 ambient;						//環境光
uniform DirectionalLight directional_light;	//平行光源

uniform vec4 edge_color;

void main()
{
	vec3 N = normalize(normal);							//法線
	vec3 L = normalize(-directional_light.direction);	//光源へのベクトル
	vec3 V = normalize(camera_pos - position);			//カメラへのベクトル
	vec3 R = normalize(reflect(-L, N));					//反射

	//フォンの反射

	vec3 phong = ambient;	//環境光

	float NdotL = dot(N, L);
	//if (NdotL > 0)
	//{
		//拡散反射
		float diffuse = clamp(NdotL, 0.0, 1.0);
			//directional_light.diffuse_color * NdotL;

		//鏡面反射
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