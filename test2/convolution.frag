#extension GL_ARB_texture_rectangle : enable

uniform sampler2DRect texture;
uniform float fRadius;
float nWidth = 3.0;
float nHeight =  3.0;

void main(void){
    vec2 pos = gl_TexCoord[0].st;
    vec4 fSum = vec4(0.0,0.0,0.0,0.0);
    vec4 fTotal=vec4(0.0,0.0,0.0,0.0);
    vec4 vec4Result=vec4(0.0,0.0,0.0,0.0);

    //邻近元素求和 坐标值家0.5 以防计算误差
    for (float ii = pos.x - fRadius;ii< pos.x + fRadius + 0.5; ii += 1.0){
        for (float jj=pos.y - fRadius; jj < pos.y + fRadius + 0.5; jj +=1.0){
            if (ii >=0.0 && jj >=0.0 && ii < nWidth &&jj < nHeight) {
                fSum += texture2DRect(texture, vec2(ii, jj));
                fTotal += vec4(1.0,1.0,1.0,1.0);
            }
        }
    }
    //求的邻近 元素的均值
    vec4Result=fSum / fTotal;
    //将结果写入帧缓存对应像素
    gl_FragColor=vec4Result;
}