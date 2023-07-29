uniform vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
uniform sampler2D textureData;

in vec2 interpolatedTexCoord;

out vec4 fragmentColor;

void main() {
    fragmentColor = color * texture(textureData, interpolatedTexCoord);
}
