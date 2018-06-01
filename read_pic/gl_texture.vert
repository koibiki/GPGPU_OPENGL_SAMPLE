//#version 400
//顶点着色器输入
vec2 Position;
varying vec2 TexCoord;

//顶点着色器的输出，这个变量会进入片元着色器
varying vec2 fragTexCoord;

void main() {
  // Copy the input to the fragment shader
  fragTexCoord =TexCoord.xy;

  // Calculate the final position on screen
  // Note the visible portion of the screen is in <-1,1> range for x and y coordinates
  gl_Position = vec4(Position.x,Position.y, 0.0, 1.0);
}
