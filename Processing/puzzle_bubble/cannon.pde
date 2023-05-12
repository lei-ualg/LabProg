class Cannon {
  float angle = 0;
  float previous_angle = -10;
  float next_angle = 10;
  boolean moving = false;
  int cooldown = 0;
  PVector pos = new PVector(0, 0);

  Cannon(float x, float y) {
    this.pos.set(x, y);
  }

  Cannon() {
    this.pos.set(width/2, height-(WALL*4));
  }


  void draw() {
    if ((cooldown/(FRAMERATE/2)) >= 2) {
      this.cooldown=0;
    }
    if (cooldown != 0) cooldown++;

    this.angle = constrain(angle, -60, 60);

    //if (moving || (angle%10.0 != 0)) {
    //  switch (keyCode) {
    //  case LEFT:
    //    if ( (angle!=int(angle)) || (angle > previous_angle))
    //      this.angle -= 45.0/FRAMERATE;
    //    this.angle = constrain(angle, previous_angle, angle);
    //    break;
    //  case RIGHT:
    //    if ((angle!=int(angle)) || (angle < next_angle))
    //      this.angle += 45.0/FRAMERATE;
    //    this.angle = constrain(angle, angle, next_angle);
    //    break;
    //  default:
    //    if (angle % 10.0 != 0) {
    //      if (angle - int(angle) < 0)
    //        this.angle -= 45.0 / FRAMERATE;
    //      else
    //        this.angle += 45.0 / FRAMERATE;
    //      this.angle = constrain(this.angle, previous_angle, next_angle);
    //    }
    //    break;
    //  }
    //  if ((angle==int(angle)) && (int(angle)%10 == 0)) {
    //    this.moving = false;
    //    this.previous_angle = max(int(angle-10), -60);
    //    this.next_angle = min(int(angle+10), 60);
    //  }
    //}

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
    if (cooldown%30 != 0) fill(40, 40, 40);
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
