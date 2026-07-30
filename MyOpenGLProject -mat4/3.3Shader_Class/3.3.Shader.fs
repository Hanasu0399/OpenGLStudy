#version 330 core
in vec3 ourColor;
out vec4 FragColor;
in vec3 ourPos;
void main(){
    FragColor = vec4(ourColor,1.0f);

}