This project implements four airbrushes: constant, linear, quadratic, and the smudge brush.

I put helper functions that are useful for all brushes (or all brushes except the smudge brush)
into the Brush class.

These include:
```
int Brush::squareMagnitude(int x, int y);

int Brush::mixRGBChannel(float brushIntensity, float canvasIntensity, float maskValue, float alpha);

RGBA Brush::mixColor(RGBA canvasColor, float maskValue);
```

I used polymorphism to have Canvas2D use just one `m_brush` member variable of type Brush.

For the smudge brush, I used an automatic storage solution:
I added `std::vector<RGBA> m_paintBuffer` to the SmudgeBrush class, and I created
a function `makePaintBuffer()` that gets called alongside `makeMask()` in the SmudgeBrush constructor. This way,
the paint buffer is automatically deleted when the user switches to a new brush type, and is initialized whenever
the user switches to the SmudgeBrush.
