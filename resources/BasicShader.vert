layout (location = 0) in highp vec4 position;
layout (location = 1) in highp vec2 textureCoord;

uniform highp mat4 projectionMat;
uniform highp mat4 transformationMat;

out vec2 interpolatedTextureCoord;
out vec3 transformedPos;

void main() {
    // calculate position
    vec4 transformedPos4 = transformationMat * position;
    transformedPos = transformedPos4.xyz / transformedPos4.w;

    gl_Position = projectionMat * transformedPos4;

    // map texture cordinate
    interpolatedTextureCoord = textureCoord;
}
