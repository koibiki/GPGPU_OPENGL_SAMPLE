uniform sampler2D texture;
void main(void)
{
    vec2 pos = gl_TexCoord[0].st;
    //gl_FragColor = vec4(1,1,0,0);
    vec4 fColor = texture2D(texture, vec2(pos.x, pos.y));
    fColor.r = 0.0;
    fColor.g = fColor.g + 0.1;
    fColor.b = fColor.b + 0.2;
    fColor.a = fColor.a + 0.3;
    gl_FragColor = fColor;
}