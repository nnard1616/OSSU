#lang racket

(provide (all-defined-out)) ;; so we can put tests in a second file

;; put your code below

; Problem 1
(define (sequence low high stride)
        (cond [(>  low high) null]
              [(<= low high) (cons low (sequence (+ low stride)
                                                 high
                                                 stride))]))
; Problem 2                                                 
(define (string-append-map strings suffix)
        (map (lambda (s) (string-append s suffix)) strings))

; Problem 3 
(define (list-nth-mod xs n) 
        (cond [(< n 0)    (error "list-nth-mod: negative number")]
              [(null? xs) (error "list-nth-mod: empty list")]
              [(>= n (length xs)) (list-nth-mod xs (modulo n (length xs)))] 
              [(= n 0 ) (car xs) ]
              [#t (list-nth-mod (cdr xs) (- n 1))]))

; Problem 4
(define (stream-for-n-steps stream n)
        (cond [(= n 0) null]
              [#t (cons (car (stream)) 
                        (stream-for-n-steps (cdr (stream)) (- n 1)))]))

; Problem 5
(define funny-number-stream 
  (letrec ([f (lambda(x)
                (cons x (lambda () (f (cond 
                                        [(= (modulo x 5) 4) (* -1 (+ x 1))]
                                        [(< x 0) (+ (* -1 x) 1)]
                                        [#t (+ x 1)])))))])
 
    (lambda () (f 1))))

; Problem 6 
(define dan-then-dog
  (letrec ([f (lambda(x) 
                (cons x (lambda () (f (cond
                                        [(string=? x "dog.jpg") "dan.jpg"]
                                        [(string=? x "dan.jpg") "dog.jpg"])))))])
    (lambda () (f "dan.jpg"))))

; Problem 7
(define (stream-add-zero stream)
        (lambda () (cons
                      (cons 0 (car (stream)))
                      (stream-add-zero (cdr (stream))))))

; Problem 8 BUGGED?
(define (cycle-lists xs ys)
  (letrec ([f (lambda (n) (cons (cons (list-nth-mod xs n)
                                      (list-nth-mod ys n))
                                (lambda() (f (+ n 1)))))])
    (lambda () (f 0))))

; Problem 9 BUGGED
(define (vector-assoc v vec)
  (letrec ([f (lambda(n) 
                (if (= n (vector-length vec))
                    #f                                  ;end of vector
                    (let ([item (vector-ref vec n)])
                      (if (pair? item)                  ;pair?
                          (cond [(equal? v (car item)) item] ;did we find it?
                                [#t (f (+ n 1))])       ;keep looking
                          (f (+ n 1))))))])             ;not a pair
    (f 0)))

; Problem 10 BUGGED
(define (cached-assoc xs n)
  (letrec ([cache (make-vector n #f)]
           [slot 0]
           [f (lambda (iv)
                (let ([cached (vector-assoc iv cache)])
                  (if cached                                     ;if in cache?
                      cached                                     ;then: return item
                      (let ([item (assoc iv xs)])                ;else: not in cache, look in list
                        (if item                                 ;if item found in list?
                            (begin (set! slot                    ;then: update cache slot 
                                         (modulo (+ slot 1) 
                                                 (vector-length cache)))
                                   (vector-set! cache slot item) ;      save in cache slot
                                   item)                         ;      return found item
                            #f   )))))])                         ;else: item not found
    (lambda (i) (f i))))

