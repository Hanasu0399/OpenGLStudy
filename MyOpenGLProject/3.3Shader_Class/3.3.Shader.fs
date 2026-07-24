#version 330 core
in vec3 ourColor;
out vec4 FragColor;
in vec3 ourPos;
in vec2 TexCoord;
uniform sampler2D Texture1;
uniform sampler2D Texture2;
uniform float setAlpha;


void main(){
    vec4 color1=texture(Texture1,TexCoord);
    vec4 color2=texture(Texture2,vec2(TexCoord.x,TexCoord.y));
    vec3 m = color1.rgb * color2.rgb;
    //FragColor = vec4(ourColor,1.0f);
    vec3 finalColor=mix(color1.rgb , m , color2.a);
    //FragColor = vec4( finalColor , setAlpha);
    FragColor = mix(texture(Texture1,TexCoord),texture(Texture2,TexCoord),setAlpha);

}