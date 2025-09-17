shader_type canvas_item;

uniform float Progress : hint_range(0, 1.0) = 0.0;
uniform vec2 GridScale = vec2(1.0);
uniform float GradualRange = 1.0;
uniform vec2 Anchor = vec2(0.5);
uniform vec3 OverColor : source_color = vec3(0.0);

void fragment() {
	vec2 _uv = UV * GridScale;
	vec2 uvGrid = floor(_uv);
	_uv = fract(_uv);
	_uv = _uv * 2.0 - 1.0;

	vec2 anchorGrid = floor(Anchor * GridScale);
	vec2 relativeGrid = uvGrid - anchorGrid;

	float startDistance = length(relativeGrid);
	float endDistance = startDistance + GradualRange;

	float edgeDistance = max(
		max(
			distance(anchorGrid, vec2(0.0)),
			distance(anchorGrid, vec2(GridScale.x, 0.0))
		),
		max(
			distance(anchorGrid, vec2(GridScale.x, GridScale.y)),
			distance(anchorGrid, vec2(0.0, GridScale.y))
		)
	);
	edgeDistance += GradualRange;

	float over = smoothstep(startDistance, endDistance, Progress * edgeDistance);
	float alpha = step(abs(_uv.x), over) * step(abs(_uv.y), over);
	COLOR = vec4(OverColor, alpha);
}
