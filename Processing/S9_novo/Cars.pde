

public class Cars {
  public boolean stopped = false;
  public boolean vertical;
  Direction direction;
  private float speed = random(4, 6);
  private float posX, posY;
  private color paint = color(random(360), random(100), random(60, 100));

  public float limitX = 0, limitY = 0, roadWidth;

  private float carW, carH, offsetX, offsetY;

  public Cars(Direction direction, float roadWidth, float centerX, float centerY, float limitX, float limitY) {
    this.direction = direction;
    this.roadWidth = roadWidth;
    this.posX = centerX;
    this.posY = centerY;

    this.limitX = limitX;
    this.limitY = limitY;
    
    this.vertical = this.direction.isVertical();

    switch(direction) {
    case NORTH:
      this.posY = height;
      this.posX += roadWidth*.25;
      this.carW = this.roadWidth/3;
      this.carH = this.carW*2;
      this.offsetX = -this.carW/2;
      break;
    case SOUTH:
      this.posY = 0;
      this.posX -= roadWidth*.25;
      this.carW = -this.roadWidth/3;
      this.carH = this.carW*2;
      this.offsetX = -this.carW/2;
      break;
    case EAST:
      this.posX = 0;
      this.posY += roadWidth*.25;
      this.carH = this.roadWidth/3;
      this.carW = -this.carH*2;
      this.offsetY = -this.carH/2;
      break;
    default:
      this.posX = width;
      this.posY -= roadWidth*.25;
      this.carH = this.roadWidth/3;
      this.carW = this.carH*2;
      this.offsetY = -this.carH/2;
      break;
    }
  }

  private void drawCar() {

    fill(0);
    if (this.vertical) {
      rect(this.posX + this.offsetX*1.25, this.posY + this.offsetX*-.25, this.carW*1.25, this.carH/4, abs(this.roadWidth*.05));
      rect(this.posX + this.offsetX*1.25, this.posY + this.offsetX*-2.5, this.carW*1.25, this.carH/4, abs(this.roadWidth*.05));
    } else {
      rect(this.posX + this.carW*.65, this.posY + this.offsetY*1.25, this.carW/4, this.carH*1.25, abs(this.roadWidth*.05));
      rect(this.posX + this.carW*.05, this.posY + this.offsetY*1.25, this.carW/4, this.carH*1.25, abs(this.roadWidth*.05));
    }
    fill(this.paint);
    rect(this.posX + offsetX, this.posY + offsetY, this.carW, this.carH, abs(this.roadWidth/20));
    
    fill(#33ffff);
    if (this.vertical) {
      rect(this.posX + this.offsetX*.75, this.posY + -this.offsetX, this.carW*.75, this.carH/7, abs(this.roadWidth*.05));
      rect(this.posX + this.offsetX*.75, this.posY + this.offsetX*-2.5, this.carW*.75, this.carH/8, abs(this.roadWidth*.05));
    } else {
      rect(this.posX + this.carW*.65, this.posY + this.offsetY*.75, this.carW/8, this.carH*.75, abs(this.roadWidth*.05));
      rect(this.posX + this.carW*.25, this.posY + this.offsetY*.75, this.carW/7, this.carH*.75, abs(this.roadWidth*.05));
    }
  }

  private void reset() {
    this.speed = random(4, 6);
    this.paint = color(random(360), random(90), random(60, 100));
    switch(direction) {
    case NORTH:
      this.posY = height;
      break;
    case SOUTH:
      this.posY = 0;
      break;
    case EAST:
      this.posX = 0;
      break;
    default:
      this.posX = width;
      break;
    }
  }

  void draw() {
    if (this.stopped == false) {
      switch(this.direction) {
      case NORTH:
        this.posY -= this.speed;
        this.posY = constrain(posY, 0, height);
        if (this.posY == 0) this.reset();
        break;
      case SOUTH:
        this.posY += this.speed;
        this.posY = constrain(posY, 0, height);
        if (this.posY >= height) this.reset();
        break;
      case EAST:
        this.posX += this.speed;
        this.posX = constrain(posX, 0, width);
        if (this.posX >= width) this.reset();
        break;
      default:
        this.posX -= this.speed;
        this.posX = constrain(posX, 0, width);
        if (this.posX <= 0) this.reset();
        break;
      }
    } else {
      switch(this.direction) {
      case NORTH:
        this.posY -= this.speed;
        this.posY = constrain(posY, this.limitY, height);
        if (this.posY == 0) this.reset();
        break;
      case SOUTH:
        this.posY += this.speed;
        this.posY = constrain(posY, 0, this.limitY);
        if (this.posY >= height) this.reset();
        break;
      case EAST:
        this.posX += this.speed;
        this.posX = constrain(this.posX, 0, this.limitX);
        if (this.posX >= width) this.reset();
        break;
      default:
        this.posX -= this.speed;
        this.posX = constrain(this.posX, this.limitX, width);
        if (this.posX <= 0) this.reset();
        break;
      }
    }

    this.drawCar();
  }
}
