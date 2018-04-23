# University of Washington, Programming Languages, Homework 6, hw6runner.rb

# This is the only file you turn in, so do not modify the other files as
# part of your solution.

class MyPiece < Piece
  # The constant All_My_Pieces should be declared here
  All_My_Pieces = [[[[0, 0], [1, 0], [0, 1], [1, 1]]],  # square (only needs one)
  rotations([[0, 0], [-1, 0], [1, 0], [0, -1]]), # T
  [[[0, 0], [-1, 0], [1, 0], [2, 0]], # long (only needs two)
  [[0, 0], [0, -1], [0, 1], [0, 2]]],
  rotations([[0, 0], [0, -1], [0, 1], [1, 1]]), # L
  rotations([[0, 0], [0, -1], [0, 1], [-1, 1]]), # inverted L
  rotations([[0, 0], [-1, 0], [0, -1], [1, -1]]), # S
  rotations([[0, 0], [1, 0], [0, -1], [-1, -1]]), # Z
  rotations([[0, 0], [1, 0], [-1, 0], [0, 1], [-1, 1]]),
  [[[0, 0], [-1, 0], [-2, 0], [1, 0], [2, 0]], # long long (only needs two)
  [[0, 0], [0, -1], [0, -2], [0, 1], [0, 2]]],
  rotations([[0, 0], [0, 1], [1, 0]])]
  # your enhancements here

  # the size of piece is needed. 
  # it's always 4 before, but the additional 3 pieces has different size.
  def initialize (point_array, board, piece_size)
    super(point_array, board)
    @piece_size = piece_size
  end
  attr_accessor :piece_size
  # class method to choose the next piece
  def self.next_piece (board)
    if board.cheat
      board.cheat_off
      MyPiece.new([[[0, 0]]], board, 1)
    else
      sample = All_My_Pieces.sample
      MyPiece.new(sample, board, sample[0].length)
    end
  end
end

class MyBoard < Board
  # your enhancements here
  def initialize (game)
    @grid = Array.new(num_rows) {Array.new(num_columns)}
    @current_block = MyPiece.next_piece(self)
    @score = 0
    @game = game
    @delay = 500
    @cheat = false
  end

  # helper functions for cheating
  def cheat_on
    if @score >= 100 and @cheat == false
      @cheat = true
      @score -= 100
    end
  end

  def cheat_off
    @cheat = false
  end

  attr_accessor :cheat

  # method to rotate a block 180 degree.
  def rotate_counter_180_degree
    if !game_over? and @game.is_running?
      @current_block.move(0, 0, 2)
    end
    draw
  end

  # override next_piece
  def next_piece
    @current_block = MyPiece.next_piece(self)
    @current_pos = nil
  end

  # The provided store_current method has a fixed range (0..3), 
  # since the classic pieces has all size 4. but that causes crash when
  # size of piece is not 4. especially less then 4.
  # So I did small modify to the original code.
  def store_current
    locations = @current_block.current_rotation
    displacement = @current_block.position
    (0..@current_block.piece_size - 1).each{|index| 
      current = locations[index];
      @grid[current[1]+displacement[1]][current[0]+displacement[0]] = 
      @current_pos[index]
    }
    remove_filled
    @delay = [@delay - 2, 80].max
  end
end

class MyTetris < Tetris
  # your enhancements here
  def set_board
    @canvas = TetrisCanvas.new
    @board = MyBoard.new(self)   # set board to MyBoard
    @canvas.place(@board.block_size * @board.num_rows + 3,
                  @board.block_size * @board.num_columns + 6, 24, 80)
    @board.draw
  end

  def key_bindings  
    @root.bind('n', proc {self.new_game}) 

    @root.bind('p', proc {self.pause}) 

    @root.bind('q', proc {exitProgram})
    
    @root.bind('a', proc {@board.move_left})
    @root.bind('Left', proc {@board.move_left}) 
    
    @root.bind('d', proc {@board.move_right})
    @root.bind('Right', proc {@board.move_right}) 

    @root.bind('s', proc {@board.rotate_clockwise})
    @root.bind('Down', proc {@board.rotate_clockwise})

    @root.bind('w', proc {@board.rotate_counter_clockwise})
    @root.bind('Up', proc {@board.rotate_counter_clockwise}) 
    
    @root.bind('space' , proc {@board.drop_all_the_way})
    # add key bindings 'u' and 'c'
    @root.bind('u', proc {@board.rotate_counter_180_degree})
    @root.bind('c', proc {@board.cheat_on})
  end
end