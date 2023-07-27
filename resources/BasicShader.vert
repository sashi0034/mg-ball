layout (location = 0) in vec4 position;
layout (location = 1) in vec2 textureCoordinates;

// 0
uniform mat4 transformationMat;
// 1
uniform mat4 projectionMat;

out vec2 interpolatedTexCoord;
// out vec3 transformedPos;

void main() {
    // calculate position
    vec4 transformedPos4 = transformationMat * position;
    // transformedPos = transformedPos4.xyz / transformedPos4.w;

    gl_Position = projectionMat * transformedPos4;

    // map texture cordinate
    interpolatedTexCoord = textureCoordinates;
}
