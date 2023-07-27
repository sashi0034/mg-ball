uniform vec3 color = vec3(1.0, 1.0, 1.0);
uniform sampler2D textureData;

in vec2 interpolatedTextureCoord;
in vec3 transformedPos;

out vec4 fragmentColor;

void main() {
    fragmentColor.rgb = color * texture(textureData, interpolatedTextureCoord).rgb * transformedPos.z;
    fragmentColor.a = 1;
}
