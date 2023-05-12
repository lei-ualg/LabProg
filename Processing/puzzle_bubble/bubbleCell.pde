class BubbleCell {
  Bubble bubble = null;
  float radius = BUBBLE_DIAMETER/2;
  PVector pos;

  BubbleCell(PVector pos) {
    this.pos = new PVector(pos.x, pos.y);
  }

  void draw() {
    //push();
    //stroke(0);
    //strokeWeight(.5);
    //noFill();
    fill(0,0,0,30);
    circle(pos.x,pos.y,radius*2);
    if (bubble != null) bubble.draw();
    //pop();
  }
}
