﻿layout (location = 0) in highp vec2 position;
layout (location = 1) in highp vec2 texCoord;
layout (location = 8) in highp mat3 instTransformMat;
layout (location = 11) in highp vec4 instTexRect;

out vec2 interpolatedTexCoord;

uniform highp vec2 screenSize;

void main() {
    // calculate position
    vec3 transformedPos3 = instTransformMat * vec3(position, 1);

    gl_Position.xy = (transformedPos3.xy / screenSize) * 2 + vec2(-1, 1);
    gl_Position.z = 0.5;
    gl_Position.w = 1;

    // calculate texture cordinate
    interpolatedTexCoord.x = instTexRect.x + texCoord.x * instTexRect.z;
    interpolatedTexCoord.y = 1 - (instTexRect.y + instTexRect.w) + texCoord.y * instTexRect.w;
}
