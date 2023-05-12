class Field {
  Cannon cannon = new Cannon();
  Ceiling ceiling = new Ceiling();

  Bubble loaded = new Bubble(cannon.pos.x, cannon.pos.y, false);
  Bubble waiting = new Bubble(cannon.pos.x, cannon.pos.y, true);

  ArrayList<Bubble> fired = new ArrayList<Bubble>();

  ArrayList<PVector> closest_indexes = new ArrayList<PVector>();
  ArrayList<PVector> closest_cells = new ArrayList<PVector>();

  Field() {
  }

  void keyPressed() {
    if (cannon.cooldown%30 == 0 && !cannon.moving && keyCode == ' ') {
      this.cannon.cooldown++;

      this.fired.add(new Bubble(loaded));
      this.closest_cells.add(new PVector(0, 0));
      this.closest_indexes.add(new PVector(0, 0));
      fired.get(fired.size()-1).fire(int(this.cannon.angle-90));
      loaded = new Bubble(waiting);
      waiting = new Bubble(cannon.pos.x, cannon.pos.y, true);
    }

    if (cannon.cooldown%30 == 0 && (keyCode == LEFT || keyCode == RIGHT))
      this.cannon.moving = true;
  }

  void keyReleased() {
    if (keyCode == LEFT || keyCode == RIGHT)
      this.cannon.moving = false;
  }

  void closest_cell() {
    for (int i = 0; i < fired.size(); i++) {
      float closest_dist = PVector.dist(closest_cells.get(i), fired.get(i).pos);
      for (int row = 0; row < ceiling.grid.cells.length; row++) {
        for (int col = 0; col < ceiling.grid.cells[row].length; col++) {
          if (row%2==1 && col==0) continue;
          float dist_new = PVector.dist(ceiling.grid.cells[row][col].pos, fired.get(i).pos);
          if (dist_new < closest_dist) {
            closest_cells.set(i, ceiling.grid.cells[row][col].pos);
            closest_indexes.set(i, new PVector(row, col));
            closest_dist = dist_new;
          }
        }
      }
    }
  }

  void collision_detector() {
    ArrayList<Bubble> bubbles_collisions = new ArrayList<Bubble>();
    for (int i = 0; i < fired.size(); i++) {
      boolean collided = false;
      if (dist(0, fired.get(i).pos.y, 0, ceiling.pos.y) < BUBBLE_DIAMETER/2+WALL*1.5) {
        collided = true;
      } else {
        for (int row = 0; row < ceiling.grid.cells.length; row++)
          for (int col = 0; col < ceiling.grid.cells[row].length; col++) {
            if (row%2==1 && col==0) continue;
            else if (ceiling.grid.cells[row][col].bubble != null && PVector.dist(ceiling.grid.cells[row][col].pos, fired.get(i).pos) < BUBBLE_DIAMETER) {
              collided = true;
            }
          }
      }
      if (collided == true) {
        if (this.ceiling.grid.cells[int(closest_indexes.get(i).x)][int(closest_indexes.get(i).y)].bubble != null)
          GAME_OVER = true;
        else {
          this.ceiling.grid.cells[int(closest_indexes.get(i).x)][int(closest_indexes.get(i).y)].bubble = new Bubble(closest_cells.get(i), fired.get(i));
          bubbles_collisions.add(fired.get(i));
        }
      }
    }
    fired.removeAll(bubbles_collisions);
  }


  void draw() {
    closest_cell();
    collision_detector();

    cannon.draw();
    loaded.draw();
    waiting.draw();


    ceiling.draw();
    for (int i = 0; i < fired.size(); i++) {
      fired.get(i).draw();
      push();
      fill(hue(fired.get(i).bubble_color), saturation(fired.get(i).bubble_color), brightness(fired.get(i).bubble_color), 70);
      circle(closest_cells.get(i).x, closest_cells.get(i).y, BUBBLE_DIAMETER);
      pop();
    }
  }
}
