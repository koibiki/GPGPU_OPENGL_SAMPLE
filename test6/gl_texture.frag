//#version 400
// 需要注意opengl纹理输入
uniform sampler2D Texture;

// 来自顶点着色器
vec2 fragTexCoord;
//输出
vec4 FragmentColor;

void main() {
  // Lookup the color in Texture on coordinates given by fragTexCoord
  vec3 pColor = texture2D(Texture, fragTexCoord.xy).rgb;
	//转换成灰度图像
  float gray=pColor.r*0.2126+ 0.7152* pColor.g + 0.0722*pColor.b;
  gl_FragColor =vec4(gray, gray,gray, 1.0);
}