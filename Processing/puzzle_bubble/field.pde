class Field {
  Cannon cannon = new Cannon();
  Ceiling ceiling = new Ceiling();

  Bubble loaded = new Bubble(cannon.pos.x, cannon.pos.y, false);
  Bubble waiting = new Bubble(cannon.pos.x, cannon.pos.y, true);

  ArrayList<Bubble> fired = new ArrayList<Bubble>();

  Field() {
  }

  void keyPressed() {
    if (!cannon.cooldown && !cannon.moving && keyCode == ' ') {
      this.cannon.cooldown = true;
      this.cannon.timer++;

      this.fired.add(new Bubble(loaded));
      fired.get(fired.size()-1).fire(int(this.cannon.angle-90));
      loaded = new Bubble(waiting);
      waiting = new Bubble(cannon.pos.x, cannon.pos.y, true);
    }

    if (!cannon.cooldown && (keyCode == LEFT || keyCode == RIGHT))
      this.cannon.moving = true;
  }

  void keyReleased() {
    if (keyCode == LEFT || keyCode == RIGHT)
      this.cannon.moving = false;
  }

  PVector nearest_cell(Bubble bubble, int row, int col) {
    PVector rowcol = new PVector(0, 0);
    float nearest = Float.MAX_VALUE;
    for (int r = row - 1; r <= row + 1; r++) {
      if (ceiling.grid.cells[max(r-1, 0)] == null) continue;
      for (int c = col - 1; c <= col + 1; c++) {
        if (((r == row + 1 || r == row - 1) && c == col + (r%2==0?1:-1)) || (c==col && r==row)) continue;
        if (r >= 0 && r < 15 && c >= (r % 2 == 0 ? 0 : 1) && c < 10) {
          float distance = PVector.dist(ceiling.grid.cells[r][c].pos, bubble.pos);
          if (nearest > distance) {
            rowcol.set(r, c);
            nearest = distance;
          }
        }
      }
    }
    return rowcol;
  }

  int nearest_cell(Bubble bubble) {
    int col = 0;
    float nearest = Float.MAX_VALUE;
    for (int c = 0; c<ceiling.grid.cells[0].length; c++) {
      float distance = PVector.dist(bubble.pos, ceiling.grid.cells[0][c].pos);
      if (nearest > distance) {
        col= c;
        nearest = distance;
      }
    }
    return col;
  }

  void collision_detector() {
    ArrayList<Bubble> bubbles_collisions = new ArrayList<Bubble>();
    for (int i = 0; i < fired.size(); i++) {
      int r = 0, c = 0;
      boolean collided = false;
      if (dist(0, fired.get(i).pos.y, 0, ceiling.pos.y) < BUBBLE_DIAMETER/2+WALL*1.5) {
        collided = true;
        r = 0;
        c = nearest_cell(fired.get(i));
      } else {
        for (int row = 0; row < ceiling.grid.cells.length; row++) {
          if (ceiling.grid.cells[row] == null) continue;
          for (int col = 0; col < ceiling.grid.cells[row].length; col++) {
            if (row%2==1 && col==0) continue;
            else if (ceiling.grid.cells[row][col].bubble != null && PVector.dist(ceiling.grid.cells[row][col].pos, fired.get(i).pos) < BUBBLE_DIAMETER*1) {
              collided = true;
              PVector pos = nearest_cell(fired.get(i), row, col);
              r = int(pos.x);
              c = int(pos.y);
            }
          }
        }
      }
      if (collided) {
        if (this.ceiling.grid.cells[r][c].bubble != null)
          GAME_OVER = true;
        else {
          this.ceiling.grid.cells[r][c].bubble = new Bubble(ceiling.grid.cells[r][c].pos, fired.get(i));
          bubbles_collisions.add(fired.get(i));
        }
      }
    }
    fired.removeAll(bubbles_collisions);
  }


  void draw() {
    collision_detector();

    cannon.draw();
    loaded.draw();
    waiting.draw();

    ceiling.draw();
    for (Bubble bubble : fired)
      bubble.draw();
  }
}
