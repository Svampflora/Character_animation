#version 330

in vec2 uv;
in vec4 color;

out vec4 finalColor;

void main()
{
    vec2 p = uv * 2.0 - 1.0;

    float d = dot(p, p);

    if (d > 1.0)
        discard;

    float alpha = 1.0 - smoothstep(0.8, 1.0, sqrt(d));

    finalColor = vec4(color.rgb, color.a * alpha);
}