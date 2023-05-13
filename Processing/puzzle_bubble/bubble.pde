class Bubble {
  color bubble_color = random_bubble_color();
  
  boolean fired = false;
  boolean falling = false;
  boolean is_next = false;
  
  PVector pos = new PVector(0, 0);
  PVector velocity= new PVector(0, 0);

  Bubble(float x, float y, boolean is_next) {
    this.is_next = is_next;
    this.pos = new PVector(x, y);
    this.velocity = new PVector(0, 0);
  }
  // Deepclone
  Bubble(Bubble original) {
    this.bubble_color = original.bubble_color;
    
    this.pos = new PVector(original.pos.x, original.pos.y);
    this.velocity = new PVector(original.velocity.x, original.velocity.y);
  }
  
  Bubble(PVector grid_pos, Bubble original) {
    this.bubble_color = original.bubble_color;
    this.pos = new PVector(grid_pos.x,grid_pos.y);
  }

  void update() {
    if (fired) {
      pos.add(velocity);
      if (pos.x < WALL + BUBBLE_DIAMETER/2 || pos.x > width - WALL - BUBBLE_DIAMETER/2) {
        velocity.x *= -1;
      }
    }
    
    if (falling) 
      pos.y += 5;
  }
  
  boolean is_outside() {
    return (pos.y > height+BUBBLE_DIAMETER/2);
  }

  void fire(int angle) {
    this.fired = true;
    float speed = 10;
    velocity = PVector.fromAngle(radians(angle));
    velocity.mult(speed);
  }

  void draw() {
    update();
    stroke(0);
    strokeWeight(2);
    fill(bubble_color);
    if (is_next)
      circle(pos.x-BUBBLE_DIAMETER*2, pos.y+BUBBLE_DIAMETER/2, BUBBLE_DIAMETER);
    else
      circle(pos.x, pos.y, BUBBLE_DIAMETER);
    noStroke();
  }
}
