# University of Washington, Programming Languages, Homework 6, hw6runner.rb

# This is the only file you turn in, so do not modify the other files as
# part of your solution.


class MyPiece < Piece
  # The constant All_My_Pieces should be declared here=
   All_My_Pieces = [ [[[0, 0], [1, 0], [0, 1], [1, 1]]],  # square (only needs one)
               rotations([[0, 0], [-1, 0], [1, 0], [0, -1]]), # T
               [[[0, 0], [-1, 0], [1, 0], [2, 0]], # long (only needs two)
               [[0, 0], [0, -1], [0, 1], [0, 2]]],
               rotations([[0, 0], [0, -1], [0, 1], [1, 1]]), # L
               rotations([[0, 0], [0, -1], [0, 1], [-1, 1]]), # inverted L
               rotations([[0, 0], [-1, 0], [0, -1], [1, -1]]), # S
               rotations([[0, 0], [1, 0], [0, -1], [-1, -1]]), # Z
               rotations([[0, 0], [-1, 0], [1, 0], [0, -1], [-1, -1]]),# T+1
               [[[0, 0], [-1, 0], [-2, 0], [1, 0], [2, 0]], 
               [[0, 0], [0, -1], [0, -2], [0, 1], [0, 2]]],# 5 long
               rotations([[0, 0], [1, 0], [0, -1]])]                  
  # your enhancements here
  CHEAT_BLOCK = [[[0, 0]]]

  def initialize (point_array, board)
    super(point_array, board)
  end

  def all_rotations
    @all_rotations
  end

  def self.next_piece (board)
      MyPiece.new(All_My_Pieces.sample, board) # [[[0, 0], [1, 0], [0, 1], [1, 1]]]
  end

  
  def self.next_cheat_piece (board)
      MyPiece.new(CHEAT_BLOCK, board) # [[[0, 0], [1, 0], [0, 1], [1, 1]]]
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


  def rotate_180_degrees
    if !game_over? and @game.is_running?
      @current_block.move(0, 0, 2)
    end
    draw
  end

  def next_piece
    if (@cheat)
       @current_block = MyPiece.next_cheat_piece(self)
       @cheat = false
    else
       @current_block = MyPiece.next_piece(self)
    end
    @current_pos = nil
  end


  def store_current
    all_pieces = MyPiece::All_My_Pieces
    locations = @current_block.current_rotation
    current_block_data = @current_block.all_rotations

    pos = all_pieces.index(current_block_data)

    if pos == nil
      block_numbers =0

    elsif pos <7
      block_numbers = 3

    elsif pos >=7 and pos <=8
        block_numbers = 4

    else 
        block_numbers = 2

    end 

    displacement = @current_block.position

    (0..block_numbers).each{|index| 
      current = locations[index];

      @grid[current[1]+displacement[1]][current[0]+displacement[0]] = 
      @current_pos[index]
    }
    remove_filled
    @delay = [@delay - 2, 80].max
  end

  def alter_cheat_flag
    if @score >= 100 and @cheat== false
      @score -= 100
      @cheat = true
    end
  end

  def self.next_cheat_piece (board)
    MyPiece.new([[[0, 0]]], board)
  end
# in MyBoard:
  

end

class MyTetris < Tetris
  # your enhancements here
  def set_board
    @canvas = TetrisCanvas.new
    @board = MyBoard.new(self)
    @canvas.place(@board.block_size * @board.num_rows + 3,
                  @board.block_size * @board.num_columns + 6, 24, 80)
    @board.draw
  end

	def key_bindings
		super()
		@root.bind('u', proc {@board.rotate_180_degrees})
    @root.bind('c', proc {@board.alter_cheat_flag})
	end

end
