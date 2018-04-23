## Copyright (C) 2017 Nathan
## 
## This program is free software; you can redistribute it and/or modify it
## under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 3 of the License, or
## (at your option) any later version.
## 
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
## 
## You should have received a copy of the GNU General Public License
## along with this program.  If not, see <http://www.gnu.org/licenses/>.

## -*- texinfo -*- 
## @deftypefn {} {@var{retval} =} laff_axpy (@var{input1}, @var{input2})
##
## @seealso{}
## @end deftypefn

## Author: Nathan <Nathan@COEUS>
## Created: 2017-11-06

function [y_out] = laff_axpy (alpha, x, y)

%get dimensions
[m_x, n_x] = size(x);
[m_y, n_y] = size(y);

%make sure we have vectors
if ( m_x ~= 1 && n_x ~= 1 ) || ( m_y ~= 1 && n_y ~= 1 )
  y_out = 'FAILED';
  return
elseif size(alpha) ~= size(5)
  y_out = 'FAILED';
  return
else
  y = laff_scal(alpha, laff_copy(x, y)) + y;
end

y_out = y;
return
endfunction
