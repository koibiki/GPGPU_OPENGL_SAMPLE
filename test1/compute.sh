#version 430 core

layout (local_size_x = 32, local_size_y = 32) in;

layout (rgba32f, binding = 0) uniform image2D input_image;
layout (rgba32f, binding = 1) uniform image2D output_image;

shared vec4 scanline[32][32];

void main(void){
    ivec2 pos = ivec2(gl_GlobalInvocationID.xy);
    int i = pos.x % 32;
    int j = pos.y % 32;
    vec4 color = imageLoad(input_image, pos);
    scanline[i][j] = color;
    barrier();
    imageStore(output_image, opos.xy, scanline[i][j]);
}