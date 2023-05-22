class BubbleCell {
  Bubble bubble = null;
  float radius = BUBBLE_DIAMETER/2;
  int points = 0;
  int timer = 0;
  PVector pos;
  int row, col;
  color last_color = color(0, 0, 0);

  BubbleCell(PVector pos, int row, int col) {
    this.pos = new PVector(pos.x, pos.y);
    this.row = row;
    this.col = col;
  }

  void setBubble(Bubble bubble) {
    this.bubble = new Bubble(this, bubble.b_color);
  }

  void setBubble(Color b_color) {
    this.bubble = new Bubble(this, b_color);
  }

  void removeBubble() {
    this.bubble = null;
  }

  boolean hasBubble() {
    return this.bubble != null;
  }

  void setPointsDisplay(int points) {
    this.last_color = this.bubble.b_color.value;
    this.removeBubble();
    this.points = points;
    this.timer = 0;
  }

  void draw() {
    if ((timer/FRAMERATE) >= .5) {
      this.timer=0;
      this.points=0;
    }
    timer++;
    if (points > 0) {
      fill(last_color);
      textSize(BUBBLE_DIAMETER/3);
      textAlign(CENTER, CENTER);
      text("+"+points, pos.x, pos.y);
    }
    fill(0, 0, 0, 30);
    circle(pos.x, pos.y, radius*2);
    if (bubble != null) bubble.draw();
  }
}
