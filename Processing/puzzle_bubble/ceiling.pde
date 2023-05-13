class Ceiling {
  BubbleGrid grid = new BubbleGrid();
  int timer;
  int step=0;
  PVector pos= new PVector(WALL, BUBBLE_DIAMETER*step);
  float grid_height = 0;
  float step_size = 0;

  Ceiling() {
    this.grid_height = PVector.dist(grid.cells[0][0].pos,grid.cells[grid.cells.length-1][0].pos) + BUBBLE_DIAMETER/2 + grid.cells[0][0].pos.y;
    this.step_size = (grid_height-WALL)/15;
  }

  void add_step() {
    this.pos.y += step_size;
    this.step++;
    this.grid.step = step;

    if (grid.cells[1] != null) {
      for (int col = 0; col < grid.cells[grid.cells.length-step].length; col++) {
        if (col==0) continue;
        else if (grid.cells[grid.cells.length-step][col].bubble != null)
          GAME_OVER = true;
      }
      grid.cells[grid.cells.length-step] = null;
    } else {
      GAME_OVER = true;
    }

    for (int row = 0; row < grid.cells.length; row++) {
      if (grid.cells[row] == null) continue;
      for (int col = 0; col < grid.cells[row].length; col++) {
        if (row%2==1 && col==0) continue;
        this.grid.cells[row][col].pos.y += step_size;
        if (grid.cells[row][col].bubble != null) this.grid.cells[row][col].bubble.pos.y += step_size;
      }
    }
  }

  void draw() {
    if ((timer/FRAMERATE) >= 10) {
      this.timer=0;
      this.add_step();
    }
    timer++;
    rectMode(CORNER);
    fill(color(0, 0, 30));
    rect(WALL, 0, width-WALL*2, WALL+ (step_size*step));
    fill(color(0, 0, 20));
    rect(pos.x, pos.y, width-WALL*2, WALL);
    stroke(0);
    strokeWeight(2);
    line(WALL,grid_height,width-WALL,grid_height);
    noStroke();
    grid.draw();
  }
}
