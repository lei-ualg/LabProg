class TrafficLight {
  public float x, y, w, h;

  public Direction direction;

  private Light[] lights = new Light[3];

  private int currentIndex;

  TrafficLight(float x, float y, float w, float h, Direction direction, int startingLight) {
    this.x = x;
    this.y = y;
    this.w = w;
    this.h = h;
    this.direction = direction;

    // Posicoes vao ser redefinidas em draw
    this.lights[0] = new Light(0, 0, w/2, RED_LIGHT);
    this.lights[1] = new Light(0, 0, w/2, YELLOW_LIGHT);
    this.lights[2] = new Light(0, 0, w/2, GREEN_LIGHT);

    this.lights[startingLight].toggleLight();

    this.currentIndex = startingLight;
  }

  public void nextLight() {
    this.lights[currentIndex].toggleLight();
    this.currentIndex = Math.floorMod(this.currentIndex-1, lights.length);
    this.lights[currentIndex].toggleLight();
  }

  public void draw() {
    fill(TRAFFICLIGHT_COLOR);
    push();
    translate(this.x + this.w / 2, this.y + this.h / 2);

    float newX = this.w;
    float newY = this.h;


    switch (direction) {
    case WEST:
      rotate(-HALF_PI);
      newX -= this.w*.5;
      newY -= this.h*2.25;
      break;
    case NORTH:
      newX -= this.w*2;
      newY -= this.h*2.5;
      break;
    case EAST:
      rotate(HALF_PI);
      newX -= this.w*2.5;
      newY -= this.h*1.75;
      break;
    case SOUTH:
      rotate(PI);
      newX -= this.w;
      newY -= this.h*1.5;
      break;
    }
    rect(newX, newY, this.w, this.h, this.w/5);
    for (int i = 0; i<lights.length; i++) {
      lights[i].x = (newX)+(this.w/2);
      lights[i].y = (newY)+(this.h/2) + ((this.h*.3)*(i-1));
      lights[i].draw();
    }
    pop();
  }
}
