uniform vec3 color = vec3(1.0, 1.0, 1.0);
uniform sampler2D textureData;

in vec2 interpolatedTexCoord;
in vec3 transformedPos;

out vec4 fragmentColor;

void main() {
//    fragmentColor.rgb = color * texture(textureData, interpolatedTexCoord).rgb;
//    fragmentColor.a = texture(textureData, interpolatedTexCoord).a;
    fragmentColor = vec4(1, transformedPos.z, 1, 1);
}
