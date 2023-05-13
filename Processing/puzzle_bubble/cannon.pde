class Cannon {
  float angle = 0;
  boolean moving = false;
  boolean cooldown = false;
  int timer = 0;
  PVector pos = new PVector(0, 0);

  Cannon(float x, float y) {
    this.pos.set(x, y);
  }

  Cannon() {
    this.pos.set(width/2, height-(WALL*4));
  }

  void draw() {
    if ((timer/(FRAMERATE/2)) >= 1) {
      this.timer = 0;
      this.cooldown=false;
    }
    if (timer > 0) this.timer++;

    this.angle = constrain(angle, -60, 60);

    if (moving) {
      switch (keyCode) {
      case LEFT:
        this.angle -= 45.0/FRAMERATE;
        this.angle = constrain(this.angle, -60, 60);
        break;
      case RIGHT:
        this.angle += 45.0/FRAMERATE;
        this.angle = constrain(this.angle, -60, 60);
        break;
      }
    }

    fill(40, 90, 70);
    if (cooldown) fill(40, 40, 40);
    push();
    stroke(0);
    strokeWeight(1);
    translate(pos.x, pos.y);
    rotate(radians(angle));
    beginShape();
    vertex(0, BUBBLE_DIAMETER*.7);
    vertex(BUBBLE_DIAMETER*.2, BUBBLE_DIAMETER);
    vertex(BUBBLE_DIAMETER*.2, BUBBLE_DIAMETER*1.4);
    vertex(0, BUBBLE_DIAMETER*1.2);
    vertex(-BUBBLE_DIAMETER*.2, BUBBLE_DIAMETER*1.4);
    vertex(-BUBBLE_DIAMETER*.2, BUBBLE_DIAMETER);
    endShape(CLOSE);
    rect(0, 0, WALL/4, BUBBLE_DIAMETER*2);
    triangle(0, BUBBLE_DIAMETER*-1.4, -BUBBLE_DIAMETER*.15, -BUBBLE_DIAMETER, BUBBLE_DIAMETER*.15, -BUBBLE_DIAMETER);
    pop();
  }
}
