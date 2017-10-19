#!/usr/bin/env python
# -*- coding: utf-8 -*-
import re

s = 'azcbobobegghakl'
s2 = 'abcbcd'

# problem 1
print("Number of vowels: ", sum(map(lambda x: True if x == 'a' or x == 'e' or
                                                      x == 'i' or x == 'o' or
                                                      x == 'u' else False, s)))

# problem 2
print("Number of times bob occurs is: ", len(re.findall('(?=bob)', s)))

# problem 3
max_alpha = ''
temp_alpha = ''
prev = s[0]
for c in s[1:]:
  if c >= prev:
    temp_alpha += prev
  else:
    temp_alpha += prev
    if len(temp_alpha) > len(max_alpha):
      max_alpha = temp_alpha
    temp_alpha = ''
  prev = c

print("Longest substring in alphabetical order is: ", max_alpha)