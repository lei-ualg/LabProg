class Bubble {
  Color b_color;

  boolean fired = false;
  boolean falling = false;
  boolean is_next = false;

  int points = 0;

  PVector pos = new PVector(0, 0);
  PVector velocity= new PVector(0, 0);
  PVector gravity = new PVector(0, 0);

  Bubble(float x, float y, boolean is_next, Color b_color) {
    this.is_next = is_next;
    this.pos = new PVector(x, y);
    this.velocity = new PVector(0, 0);

    this.b_color = b_color;
  }
  // Deepclone
  Bubble(Bubble original) {
    this.b_color = original.b_color;

    this.pos = new PVector(original.pos.x, original.pos.y);
    this.velocity = new PVector(original.velocity.x, original.velocity.y);
  }

  Bubble(BubbleCell cell, Color b_color) {
    this.b_color = b_color;
    this.pos = new PVector(cell.pos.x, cell.pos.y);
  }

  void setPointsDisplay(int points) {
    this.points = points;
    this.falling = true;
  }

  void update() {
    if (fired) {
      pos.add(velocity);
      if (pos.x < WALL + BUBBLE_DIAMETER/2 || pos.x > width - WALL - BUBBLE_DIAMETER/2) {
        velocity.x *= -1;
      }
    }

    if (falling) {
      gravity.y += 0.2;
      pos.add(gravity);
    }
  }

  boolean is_outside() {
    return (pos.y > height+BUBBLE_DIAMETER/2);
  }

  void fire(int angle) {
    this.fired = true;
    float speed = 10;
    gravity = PVector.fromAngle(radians(90));
    gravity.mult(speed);

    velocity = PVector.fromAngle(radians(angle));
    velocity.mult(speed);
  }

  void draw() {
    update();
    stroke(0);
    strokeWeight(2);
    fill(b_color.value);
    if (is_next)
      circle(pos.x-BUBBLE_DIAMETER*2, pos.y+BUBBLE_DIAMETER/2, BUBBLE_DIAMETER);
    else
      circle(pos.x, pos.y, BUBBLE_DIAMETER);

    if (points > 0 && falling) {
      fill(0);
      textSize(BUBBLE_DIAMETER/3);
      textAlign(CENTER, CENTER);
      text("+"+points, pos.x, pos.y);
    }
    noStroke();
  }
}
