layout (location = 0) in highp vec4 position;
layout (location = 1) in highp vec2 textureCoord;
layout (location = 8) in mat4 instancedTransformMat;

uniform highp mat4 projectMat;
uniform highp mat4 transformMat;

out vec2 interpolatedTextureCoord;
out vec3 transformedPos;

void main() {
    // calculate position
    vec4 transformedPos4 = transformMat * instancedTransformMat * position;
    transformedPos = transformedPos4.xyz / transformedPos4.w;

    gl_Position = projectMat * transformedPos4;

    // map texture cordinate
    interpolatedTextureCoord = textureCoord;
}
