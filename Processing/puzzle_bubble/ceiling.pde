class Ceiling {
  PVector pos= new PVector(0, 0);
  PVector original_pos= new PVector(0, 0);
  BubbleGrid grid;
  int timer;
  int step=0;
  float grid_height = 0;
  float step_size = 0;

  Ceiling(PVector pos) {
    this.pos = new PVector(pos.x, pos.y);
    this.original_pos = new PVector(pos.x, pos.y);
    this.grid = new BubbleGrid(pos);
    this.step_size = (grid.cells[1][1].pos.y)-(grid.cells[0][0].pos.y);
    this.grid_height = step_size*15 + pos.y + (BUBBLE_DIAMETER/2*cos(radians(30)));
  }

  void add_step() {
    this.pos.y += step_size;
    this.step++;

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
    this.grid.ceiling_down(step_size);
  }

  void reset() {
    this.pos = new PVector(original_pos.x, original_pos.y);
    this.grid = new BubbleGrid(pos);
    this.step = 0;
    this.timer = 0;
  }

  void victory() {
    if (grid.cells[0] != null) {
      for (int col = 0; col < grid.cells[0].length; col++) {
        if (col==0) continue;
        else if (grid.cells[0][col].bubble != null)
          return;
      }
      GAME_OVER = true;
      VICTORY = true;
    }
  }

  void draw() {
    victory();
    if ((timer/FRAMERATE) >= 10) {
      this.timer=0;
      this.add_step();
    }
    timer++;
    rectMode(CORNER);
    fill(40, 90, 70);
    rect(pos.x, pos.y, BUBBLE_DIAMETER*10, -(WALL+(step_size*step)));
    fill(color(0, 0, 20));
    rect(pos.x, pos.y, BUBBLE_DIAMETER*10, WALL);
    stroke(0);
    strokeWeight(2);
    line(pos.x, grid_height, pos.x+BUBBLE_DIAMETER*10, grid_height);
    // line(10,pos.y+WALL,10,pos.y+WALL+grid_height);
    noStroke();
    grid.draw();
  }
}
