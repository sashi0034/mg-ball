uniform vec3 color = vec3(1.0, 1.0, 1.0);
uniform sampler2D textureData;

in vec2 interpolatedTexCoord;

out vec4 fragmentColor;

void main() {
//    fragmentColor.rgb = color * texture(textureData, interpolatedTexCoord).rgb;
//    fragmentColor.a = texture(textureData, interpolatedTexCoord).a;
    fragmentColor = vec4(1, 0.5, 1, 1);
}
