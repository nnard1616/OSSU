#lang racket
(provide (all-defined-out))

(define (pow1 x y)
  (if (= y 0)
      1
      (* x (pow1 x (- y 1)))))


