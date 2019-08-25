#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;

uniform vec3 lightPos;
uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 viewPos;

struct Material {
    //vec3 ambient;
    //vec3 diffuse;
    sampler2D diffuse;
    sampler2D specular;
    //vec3 specular;
    float shininess;
    sampler2D emission;
};

in vec2 TexCoords;

struct Light {
    vec4 vector;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform Light light;

void main()
{
    //ambient
    vec3 ambient = vec3(texture(material.diffuse, TexCoords)) * light.ambient;

    //diffuse
    vec3 norm = normalize(Normal);
    vec3 lightDir = vec3(1.0);
    if (light.vector.w == 1.0)
    {
        lightDir = normalize(vec3(light.vector) - FragPos);  
    }
    else if (light.vector.w == 0.0)
    {
        lightDir = normalize(vec3(-light.vector));
    }
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff  * light.diffuse * vec3(texture(material.diffuse, TexCoords));

    //specular
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = vec3(texture(material.specular, TexCoords)) * spec * light.specular;

    vec3 emission = texture(material.emission, TexCoords).rgb;

    vec3 result = (ambient + diffuse + specular);
    FragColor = vec4(result, 1.0);
    //FragColor.rgb = norm;
    //FragColor.a = 1.0f;
}