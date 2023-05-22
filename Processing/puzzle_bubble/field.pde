class Field {
  Ceiling ceiling;
  Cannon cannon;

  Bubble loaded;
  Bubble waiting;

  ArrayList<Bubble> fired = new ArrayList<Bubble>();

  Field() {
    this.ceiling = new Ceiling(new PVector(WALL, TITLE_BANNER+WALL));
    this.cannon = new Cannon();
    this.loaded = new Bubble(cannon.pos.x, cannon.pos.y, false, this.ceiling.grid.random_color());
    this.waiting = new Bubble(cannon.pos.x, cannon.pos.y, true, this.ceiling.grid.random_color());
  }

  void keyPressed() {
    if (key == '1' || key == '2' || key == '3' || key == '4') {

      this.ceiling.reset();
      this.loaded = new Bubble(cannon.pos.x, cannon.pos.y, false, this.ceiling.grid.random_color());
      this.waiting = new Bubble(cannon.pos.x, cannon.pos.y, true, this.ceiling.grid.random_color());

      switch(key) {
      case '1':
        LEVEL = 1;
        this.ceiling.grid.loadLevel();
        break;
      case '2':
        LEVEL = 2;
        this.ceiling.grid.loadLevel();
        break;
      case '3':
        LEVEL = 3;
        this.ceiling.grid.loadLevel();
        break;
      case '4':
        LEVEL = 4;
        this.ceiling.grid.loadLevel();
        break;
      default :
        break;
      }
    }


    if (!cannon.cooldown && !cannon.moving && keyCode == ' ') {
      this.cannon.cooldown = true;
      this.cannon.timer++;

      this.fired.add(new Bubble(loaded));
      fired.get(fired.size()-1).fire((int)this.cannon.angle-90);
      loaded = new Bubble(waiting);
      waiting = new Bubble(cannon.pos.x, cannon.pos.y, true, this.ceiling.grid.random_color());
    }

    if (!cannon.cooldown && (keyCode == LEFT || keyCode == RIGHT))
      this.cannon.moving = true;
  }

  void keyReleased() {
    if (keyCode == LEFT || keyCode == RIGHT)
      this.cannon.moving = false;
  }

  BubbleCell nearest_cell(Bubble bubble, int row, int col) {
    BubbleCell cell = null;
    float nearest = Float.MAX_VALUE;
    for (BubbleCell neighbor : ceiling.grid.neighbors(row, col)) {
      float distance = PVector.dist(neighbor.pos, bubble.pos);
      if (nearest > distance) {
        cell = neighbor;
        nearest = distance;
      }
    }
    return cell;
  }

  BubbleCell nearest_cell(Bubble bubble) {
    BubbleCell cell = null;
    float nearest = Float.MAX_VALUE;
    for (BubbleCell c : ceiling.grid.cells[0]) {
      float distance = PVector.dist(bubble.pos, c.pos);
      if (nearest > distance) {
        cell= c;
        nearest = distance;
      }
    }
    return cell;
  }

  void collision_detector() {
    ArrayList<Bubble> bubbles_collisions = new ArrayList<Bubble>();
    for (int i = 0; i < fired.size(); i++) {
      BubbleCell cell = null;
      boolean collided = false;
      if (dist(0, fired.get(i).pos.y, 0, ceiling.pos.y) < BUBBLE_DIAMETER/2+WALL*1.5) {
        collided = true;
        cell = nearest_cell(fired.get(i));
      } else {
        for (int row = 0; row < ceiling.grid.cells.length; row++) {
          if (ceiling.grid.cells[row] == null) continue;
          for (int col = 0; col < ceiling.grid.cells[row].length; col++) {
            if (row%2==1 && col==0) continue;
            else if (ceiling.grid.cells[row][col].hasBubble() && PVector.dist(ceiling.grid.cells[row][col].pos, fired.get(i).pos) < BUBBLE_DIAMETER*1) {
              collided = true;
              cell = nearest_cell(fired.get(i), row, col);
            }
          }
        }
      }
      if (collided) {
        if (cell.bubble != null)
          GAME_OVER = true;
        else {

          cell.setBubble(fired.get(i));
          bubbles_collisions.add(fired.get(i));

          ArrayList<BubbleCell> chain = this.ceiling.grid.same_color_chain(cell, new ArrayList<BubbleCell>());
          if (chain.size() >= 4) {
            int points = (25 * (int)pow(2, chain.size()-4));
            SCORE += chain.size() * points;
            for (BubbleCell c : chain) {
              c.setPointsDisplay(points);
            }
            this.ceiling.grid.drop_bubbles(cell);
          }
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
