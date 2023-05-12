class Ceiling {
  BubbleGrid grid = new BubbleGrid();
  int timer;
  int step=0;
  PVector pos= new PVector(WALL, BUBBLE_DIAMETER*step);

  Ceiling() {
  }

  void add_step() {
    this.pos.y += BUBBLE_DIAMETER;
    this.step++;
    this.grid.step = step;

    if (grid.cells.length>1) {
      for (int col = 0; col < grid.cells[grid.cells.length-1].length; col++) {
        if (col==0) continue;
        else if (grid.cells[grid.cells.length-1][col].bubble != null)
          GAME_OVER = true;
      }
      grid.cells[grid.cells.length-1] = null;
    } else {
      GAME_OVER = true;
    }

    for (int row = 0; row < grid.cells.length; row++) {
      if (grid.cells[row] == null) continue;
      for (int col = 0; col < grid.cells[row].length; col++) {
        if (row%2==1 && col==0) continue;
        this.grid.cells[row][col].pos.y += BUBBLE_DIAMETER;
        if (grid.cells[row][col].bubble != null) this.grid.cells[row][col].bubble.pos.y += BUBBLE_DIAMETER;
      }}
  }

  void draw() {
    if ((timer/FRAMERATE) >= 10) {
      this.timer=0;
      //this.add_step();
    }
    timer++;
    rectMode(CORNER);
    fill(color(0, 0, 30));
    rect(WALL, 0, width-WALL*2, WALL+ (BUBBLE_DIAMETER*step));
    fill(color(0, 0, 20));
    rect(pos.x, pos.y, width-WALL*2, WALL);
    grid.draw();
  }
}
