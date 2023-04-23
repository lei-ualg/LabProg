class RoadIntersection {
  TrafficLight trafficlights[] = new TrafficLight[4];

  float centerX = width/2, centerY = height/2, roadWidth = width/5;

  float greenDuration;

  Cars[] traffic = new Cars[4];

  int exercise, timer = 0;

  RoadIntersection(float centerX, float centerY, int exercise, float greenDuration, float roadWidth) {
    this.centerX = centerX;
    this.centerY = centerY;
    this.roadWidth = roadWidth;

    this.exercise = exercise;
    this.greenDuration = greenDuration;

    trafficlights[0] = new TrafficLight(this.centerX, this.centerY+TL_H*1.25, TL_W, TL_H, Direction.NORTH, 0);
    trafficlights[1] = new TrafficLight(this.centerX, this.centerY-TL_H*1.25, TL_W, TL_H, Direction.SOUTH, 0);
    trafficlights[2] = new TrafficLight(this.centerX-TL_H*1.5, this.centerY, TL_W, TL_H, Direction.EAST, 0);
    trafficlights[3] = new TrafficLight(this.centerX+TL_H*1.5, this.centerY, TL_W, TL_H, Direction.WEST, 0);
    this.nextDirection(true);

    this.traffic[0] = new Cars(Direction.NORTH, this.roadWidth, this.centerX, this.centerY, this.centerX, (this.centerY+TL_H*1.25));
    this.traffic[1] = new Cars(Direction.SOUTH, this.roadWidth, this.centerX, this.centerY, this.centerX, this.centerY-TL_H*1.25);
    this.traffic[2] = new Cars(Direction.EAST, this.roadWidth, this.centerX, this.centerY, this.centerX-TL_H*1.5, this.centerY);
    this.traffic[3] = new Cars(Direction.WEST, this.roadWidth, this.centerX, this.centerY, this.centerX+TL_H*1.5, this.centerY);
  }

  RoadIntersection(int exercise, float greenDuration) {
    this.exercise = exercise;

    this.greenDuration = greenDuration;

    trafficlights[0] = new TrafficLight(this.centerX+roadWidth/1.5, this.centerY+TL_H*2.5, TL_W, TL_H, Direction.NORTH, 0);
    trafficlights[1] = new TrafficLight(this.centerX-roadWidth/1.5, this.centerY-TL_H*2.5, TL_W, TL_H, Direction.SOUTH, 0);
    trafficlights[2] = new TrafficLight(this.centerX-TL_H*2.5, this.centerY+roadWidth/1.5, TL_W, TL_H, Direction.EAST, 0);
    trafficlights[3] = new TrafficLight(this.centerX+TL_H*2.5, this.centerY-roadWidth/1.5, TL_W, TL_H, Direction.WEST, 0);
    this.nextDirection(true);
    this.traffic[0] = new Cars(Direction.NORTH, this.roadWidth, this.centerX, this.centerY, this.trafficlights[0].x, this.trafficlights[0].y);
    this.traffic[1] = new Cars(Direction.SOUTH, this.roadWidth, this.centerX, this.centerY, this.trafficlights[1].x, this.trafficlights[1].y);
    this.traffic[2] = new Cars(Direction.EAST, this.roadWidth, this.centerX, this.centerY, this.trafficlights[2].x, this.trafficlights[2].y);
    this.traffic[3] = new Cars(Direction.WEST, this.roadWidth, this.centerX, this.centerY, this.trafficlights[3].x, this.trafficlights[3].y);
  }

  private void nextDirection(boolean vertical) {
    for (int i = 0; i<trafficlights.length; i++)
      if (this.trafficlights[i].direction.isVertical() == vertical)
        this.trafficlights[i].nextLight();
  }

  private void toggleTraffic() {
    for(int i = 0; i < trafficlights.length; i++) {
      switch(trafficlights[i].direction) {
      case NORTH:
        if (trafficlights[i].currentIndex != 2 && traffic[i].posY >= trafficlights[i].y)
            traffic[i].stopped = true;
        else
            traffic[i].stopped = false;
        break;
      case SOUTH:
        if (trafficlights[i].currentIndex != 2 && traffic[i].posY <= trafficlights[i].y)
            traffic[i].stopped = true;
        else
            traffic[i].stopped = false;
        break;
      case EAST:
      if (trafficlights[i].currentIndex != 2 && traffic[i].posX <= trafficlights[i].x)
            traffic[i].stopped = true;
        else
            traffic[i].stopped = false;
        break;
      default:if (trafficlights[i].currentIndex != 2 && traffic[i].posX >= trafficlights[i].x)
            traffic[i].stopped = true;
        else
            traffic[i].stopped = false;
        break;
      }
    }
  }

  void sync() {
    for (int i = 0; i<trafficlights.length; i+=2) {
      switch(trafficlights[i].currentIndex) {
      case 2:
        this.greenDuration /= 2;
        this.nextDirection(trafficlights[i].direction.isVertical());
        return;
      case 1:
        this.greenDuration *= 2;
        this.nextDirection(true);
        this.nextDirection(false);
        return;
      default:
        break;
      }
    }
  }

  void draw() {
    this.toggleTraffic();
    fill(ROAD_COLOR);
    rect(0, this.centerY - roadWidth/2, width, roadWidth);
    if (exercise > 1) {
      rect(this.centerX- roadWidth/2, 0, roadWidth, height);
      stroke(#ddaa33);
      strokeWeight(4);
      strokeCap(SQUARE);
      rect(this.centerX-roadWidth/2, this.centerY- roadWidth/2, roadWidth, roadWidth);

      for (int i=0; i < roadWidth-roadWidth/20; i+=20) {
        strokeWeight(roadWidth/20);
        line(this.centerX-roadWidth, roadWidth/10+this.centerY-roadWidth/2+i, this.centerX-roadWidth+roadWidth/3, roadWidth/10+this.centerY-roadWidth/2+i);
        line(this.centerX+roadWidth/1.5, roadWidth/10+this.centerY-roadWidth/2+i, (this.centerX+roadWidth/1.5)+roadWidth/3, roadWidth/10+this.centerY-roadWidth/2+i);
        line(roadWidth/10+this.centerX-roadWidth/2+i, this.centerY-roadWidth, roadWidth/10+this.centerX-roadWidth/2+i, this.centerY-roadWidth/1.5);
        line(roadWidth/10+this.centerX-roadWidth/2+i, this.centerY+roadWidth/1.5, roadWidth/10+this.centerX-roadWidth/2+i, this.centerY+roadWidth);
      }
      noStroke();
    }

    if ((timer/FRAMERATE) >= this.greenDuration) {
      this.timer=0;
      this.sync();
    }
    this.timer++;

    switch (exercise) {
    case 1:
      this.trafficlights[2].draw();
      this.traffic[2].draw();
      break;
    case 2:
      this.trafficlights[0].draw();
      this.trafficlights[2].draw();
      this.traffic[0].draw();
      this.traffic[2].draw();
      break;
    default:
      for (int i=0; i<trafficlights.length; i++) {
        this.trafficlights[i].draw();
        this.traffic[i].draw();
      }
      break;
    }
    
      stroke(#ddaa33);
    point(this.centerX+roadWidth/1.5, this.centerY+TL_H*2.5);
      noStroke();
  }
}
